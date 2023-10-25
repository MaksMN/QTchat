#include "client.h"
#include <QEventLoop>
#include <QJsonArray>
#include <QTimer>
#include "SimpleIni.h"
#include "commands.h"
#include "mainwindow.h"
Client::Client()
{
    CSimpleIniA ini; // https://github.com/brofield/simpleini/tree/master
    SI_Error rc = ini.LoadFile("server.ini");
    if (rc < 0) {
    } else {
        QString svaddr = ini.GetValue("DB", "server", "127.0.0.1");
        serverAddress.setAddress(svaddr);
        QString port = ini.GetValue("DB", "port", "7777");
        serverPort = static_cast<qint16>(port.toInt());
    }
}

void Client::Update()
{
    if (!socketWait)
        return;

    // список пользователей
    int offset = getTopUserItem() + 1;
    QJsonObject request;
    request["command"] = "getUsers";
    request["TopUserItem"] = offset;
    QJsonDocument jsonDoc(request);
    QJsonDocument response = send(jsonDoc, 3);

    QVector<std::shared_ptr<chat::User>> users;
    if (response.isArray()) {
        auto jsonArray = response.array();
        for (const QJsonValue &value : jsonArray) {
            std::shared_ptr<chat::User> user = std::make_shared<chat::User>();
            user->deserialiseJson(value.toObject());
            users.push_back(user);
        }
    }

    QMetaObject::invokeMethod(mainWindow,
                              "updateUsers",
                              Qt::QueuedConnection,
                              Q_ARG(QVector<std::shared_ptr<chat::User>>, users));

    Commands command = public_chat;
    QMetaObject::invokeMethod(mainWindow,
                              "getCommand",
                              Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(Commands, command));
    // публичные сообщения
    if (command == public_chat) {
        int offset = getTopMessageItem();
        QJsonObject request;
        request["command"] = "getPubMessages";
        request["TopMessageItem"] = offset;
        QJsonDocument jsonDoc(request);
        QJsonDocument response = send(jsonDoc, 3);

        QVector<std::shared_ptr<chat::Message>> messages;
        if (response.isArray()) {
            auto jsonArray = response.array();
            for (const QJsonValue &value : jsonArray) {
                std::shared_ptr<chat::Message> message = std::make_shared<chat::Message>();
                QJsonArray jArray = value.toArray();
                QJsonDocument jDocument(jArray);
                message->deserialiseJson(jDocument);
                messages.push_back(message);
            }
        }
        QMetaObject::invokeMethod(mainWindow,
                                  "updateMessages",
                                  Qt::QueuedConnection,
                                  Q_ARG(QVector<std::shared_ptr<chat::Message>>, messages));
    }
    // личные сообщения
    if (command == private_chat) {
        qlonglong current_user_id;
        QMetaObject::invokeMethod(mainWindow,
                                  "getCurrentUserID",
                                  Qt::BlockingQueuedConnection,
                                  Q_RETURN_ARG(qlonglong, current_user_id));
        qlonglong selected_user_id;
        QMetaObject::invokeMethod(mainWindow,
                                  "getSelectedUserID",
                                  Qt::BlockingQueuedConnection,
                                  Q_RETURN_ARG(qlonglong, selected_user_id));
        int offset = getTopMessageItem();
        QJsonObject request;
        request["command"] = "getPrivateMessages";
        request["TopMessageItem"] = offset;
        request["reader_id"] = current_user_id;
        request["interlocutor_id"] = selected_user_id;

        QJsonDocument jsonDoc(request);
        QJsonDocument response = send(jsonDoc, 3);

        QVector<std::shared_ptr<chat::Message>> messages;
        if (response.isArray()) {
            auto jsonArray = response.array();
            for (const QJsonValue &value : jsonArray) {
                std::shared_ptr<chat::Message> message = std::make_shared<chat::Message>();
                QJsonArray jArray = value.toArray();
                QJsonDocument jDocument(jArray);
                message->deserialiseJson(jDocument);
                messages.push_back(message);
            }
        }
        QMetaObject::invokeMethod(mainWindow,
                                  "updateMessages",
                                  Qt::QueuedConnection,
                                  Q_ARG(QVector<std::shared_ptr<chat::Message>>, messages));
    }
}

int Client::getTopUserItem()
{
    int result;
    QMetaObject::invokeMethod(mainWindow,
                              "getTopUserItem",
                              Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(int, result));
    return result;
}

int Client::getTopMessageItem()
{
    int result;
    QMetaObject::invokeMethod(mainWindow,
                              "getTopMessageItem",
                              Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(int, result));
    return result;
}

QJsonDocument Client::addSessionInJson(QJsonDocument &json)
{
    qlonglong user_id;
    QMetaObject::invokeMethod(mainWindow,
                              "getCurrentUserID",
                              Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(qlonglong, user_id));
    qlonglong user_session_key;
    QMetaObject::invokeMethod(mainWindow,
                              "getCurrentUserSessionKey",
                              Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(qlonglong, user_session_key));
    auto jobject = json.object();
    jobject["user_id"] = user_id;
    jobject["user_session_key"] = user_session_key;
    QJsonDocument jdoc(jobject);
    return jdoc;
}

QJsonDocument Client::send(QJsonDocument json, int timeout, bool add_session)
{
    if (add_session)
        json = addSessionInJson(json);
    QByteArray message = json.toJson();
    QUdpSocket udpSocket;
    udpSocket.writeDatagram(message, serverAddress, serverPort);

    auto start = std::chrono::steady_clock::now();
    int elapsedSeconds = 0;

    while (socketWait) {
        if (udpSocket.hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(udpSocket.pendingDatagramSize());
            udpSocket.readDatagram(datagram.data(), datagram.size());

            if (datagram.size() == 0)
                continue;

            QJsonParseError error;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(datagram, &error);
            if (error.error != QJsonParseError::NoError)
                continue;
            if (!jsonDoc.isNull()) {
                if (!jsonDoc.isEmpty()) {
                    if (jsonDoc["session"] == "fail") {
                        QJsonDocument jdoc;
                        close();
                        return jdoc;
                    }
                    return jsonDoc;
                }
            }
        }
        if (timeout > 0) {
            auto current = std::chrono::steady_clock::now();
            elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(current - start)
                                 .count();
            if (elapsedSeconds >= timeout) {
                QJsonObject jsonObject;
                jsonObject["response"] = "timeout";
                QJsonDocument jsonDoc(jsonObject);
                return jsonDoc;
                break;
            }
        }
    }
    udpSocket.close();
    QJsonObject jsonObject;
    jsonObject["response"] = "fail";
    QJsonDocument jsonDoc(jsonObject);
    return jsonDoc;
}
void Client::close()
{
    socketWait = false;
}

void Client::handleMainWindowClosed()
{
    close();
    this->quit();
    this->wait();
}

void Client::run()
{
    QTimer timer;
    timer.setInterval(1000); // Интервал в миллисекундах (1000 мс = 1 сек)
    timer.setSingleShot(false); // Установите в true, если нужен однократный запуск таймера

    QObject::connect(&timer, &QTimer::timeout, [&]() {
        if (!socketWait) {
            timer.stop();
            QMetaObject::invokeMethod(mainWindow, "app_close_no", Qt::QueuedConnection);
            return;
        }

        Update();
    });

    timer.start();

    QEventLoop loop;
    loop.exec();
}

Client::Client(MainWindow *_mainWindow, QObject *parent)
    : QThread(parent)
    , mainWindow(_mainWindow)
{}
