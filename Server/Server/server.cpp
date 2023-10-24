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

QJsonObject Server::registerUser(QJsonObject json)
{
    std::shared_ptr<chat::User> user = std::make_shared<chat::User>();
    user->deserialiseJson(json);

    QJsonObject result;
    QMetaObject::invokeMethod(mainThread,
                              "registerUser",
                              Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(QJsonObject, result),
                              Q_ARG(std::shared_ptr<chat::User>, user));
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
                    QJsonObject jsonObject = jsonDoc.object();

                    // обработка входящих данных
                    jsonObject = serverHandle(jsonObject);
                    // Отправляем ответ клиенту
                    QJsonDocument jsonDocument(jsonObject);
                    QByteArray response = jsonDocument.toJson();
                    udpSocket.writeDatagram(response, senderAddress, senderPort);
                }
            }
        }
    }
}

QJsonObject Server::serverHandle(QJsonObject json)
{
    QJsonObject response;
    if (json["command"].toString() == "register") {
        return registerUser(json);
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
