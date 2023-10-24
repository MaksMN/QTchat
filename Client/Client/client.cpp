#include "client.h"
#include <QEventLoop>
#include <QJsonArray>
#include <QTimer>
#include "mainwindow.h"

void Client::Update()
{
    if (!socketWait)
        return;
    int offset = mainWindow->getTopUserItem() + 1;
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
}
QJsonDocument Client::send(QJsonDocument json, int timeout)
{
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
    timer.setInterval(2000); // Интервал в миллисекундах (1000 мс = 1 сек)
    timer.setSingleShot(false); // Установите в true, если нужен однократный запуск таймера

    QObject::connect(&timer, &QTimer::timeout, [&]() {
        if (!socketWait) {
            timer.stop();
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
