#include "server.h"
#include "SimpleIni.h"
#include "mainthread.h"
#include "strings.h"
#include "user.h"

void Server::ConsoleWrite(const QString &line)
{
    QMetaObject::invokeMethod(mainThread,
                              "consoleWrite",
                              Qt::QueuedConnection,
                              Q_ARG(QString, line));
}

QJsonDocument Server::registerUser(QJsonDocument json)
{
    std::shared_ptr<chat::User> user = std::make_shared<chat::User>();
    user->deserialiseJson(json.object());

    QJsonDocument result;
    QMetaObject::invokeMethod(mainThread,
                              "registerUser",
                              Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(QJsonDocument, result),
                              Q_ARG(std::shared_ptr<chat::User>, user));
    return result;
}

QJsonDocument Server::authUser(QJsonDocument json)
{
    QJsonDocument result;
    QMetaObject::invokeMethod(mainThread,
                              "authUser",
                              Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(QJsonDocument, result),
                              Q_ARG(QString, json["login"].toString()),
                              Q_ARG(QString, json["pass"].toString()));
    return result;
}

QJsonDocument Server::getUsers(QJsonDocument json)
{
    QJsonDocument result;
    QMetaObject::invokeMethod(mainThread,
                              "getUsers",
                              Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(QJsonDocument, result),
                              Q_ARG(QJsonDocument, json));
    return result;
}

QJsonDocument Server::getPubMessages(QJsonDocument json)
{
    QJsonDocument result;
    QMetaObject::invokeMethod(mainThread,
                              "getPubMessages",
                              Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(QJsonDocument, result),
                              Q_ARG(QJsonDocument, json));
    return result;
}

QJsonDocument Server::getPrivateMessages(QJsonDocument json)
{
    QJsonDocument result;
    QMetaObject::invokeMethod(mainThread,
                              "getPrivateMessages",
                              Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(QJsonDocument, result),
                              Q_ARG(QJsonDocument, json));
    return result;
}

QJsonDocument Server::sendMessage(QJsonDocument json)
{
    QJsonDocument result;
    QMetaObject::invokeMethod(mainThread,
                              "sendMessage",
                              Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(QJsonDocument, result),
                              Q_ARG(QJsonDocument, json));
    return result;
}

Server::Server(QThread *parent)
    : QThread{parent}
{
    CSimpleIniA ini; // https://github.com/brofield/simpleini/tree/master
    SI_Error rc = ini.LoadFile("server.ini");
    if (rc < 0) {
        ConsoleWrite(Strings::t(Strings::SERVER_INI_NOTFOUND));
        ConsoleWrite(Strings::t(Strings::SERVER_USE_THE_SETTINGS));
    } else {
        port = atoi(ini.GetValue("GENERAL", "sv_port", "7777"));
    }
}

void Server::serverSocket()
{
    // Привязываем сокет к локальному адресу и порту
    QUdpSocket udpSocket;
    udpSocket.bind(QHostAddress::AnyIPv4, port);
    while (waitFlag) {
        // Ожидаем получение дейтаграммы
        while (udpSocket.hasPendingDatagrams()) {
            // Читаем дейтаграмму
            QByteArray datagram;
            datagram.resize(udpSocket.pendingDatagramSize());
            QHostAddress senderAddress;
            quint16 senderPort;
            if (!waitFlag)
                return;
            udpSocket.readDatagram(datagram.data(), datagram.size(), &senderAddress, &senderPort);
            if (datagram.size() == 0)
                continue;
            QJsonParseError error;
            QJsonDocument jsonDoc = QJsonDocument::fromJson(datagram, &error);
            if (error.error != QJsonParseError::NoError)
                continue;

            if (!jsonDoc.isNull()) {
                if (jsonDoc.isObject()) {
                    // обработка входящих данных
                    QJsonDocument jsonDocument;
                    jsonDocument = serverHandle(jsonDoc);
                    // Отправляем ответ клиенту                    
                    QByteArray response = jsonDocument.toJson();
                    udpSocket.writeDatagram(response, senderAddress, senderPort);
                }
            }
        }
    }
    udpSocket.close();
}

QJsonDocument Server::serverHandle(QJsonDocument json)
{
    QJsonDocument response;
    if (json["command"].toString() == "register") {
        return registerUser(json);
    }
    if (json["command"].toString() == "auth") {
        return authUser(json);
    }

    bool validate_session;
    QMetaObject::invokeMethod(mainThread,
                              "validateUserSession",
                              Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(bool, validate_session),
                              Q_ARG(QJsonDocument, json));
    if (!validate_session) {
        QJsonObject jobject;
        jobject["session"] = "fail";
        QJsonDocument jdoc(jobject);
        return jdoc;
    }
    if (json["command"].toString() == "getUsers") {
        return getUsers(json);
    }
    if (json["command"].toString() == "getPubMessages") {
        return getPubMessages(json);
    }

    if (json["command"].toString() == "getPrivateMessages") {
        return getPrivateMessages(json);
    }
    if (json["command"].toString() == "sendMessage") {
        return sendMessage(json);
    }

    return response;
}

void Server::run()
{
    serverSocket();
}

void Server::stop()
{
    waitFlag = false;
}

void Server::handleMainWindowClosed()
{
    this->stop();
    this->quit();
    this->wait();
}
