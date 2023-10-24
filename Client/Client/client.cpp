#include "client.h"
#include <QEventLoop>
#include <QTimer>
#include "commands.h"
#include "mainwindow.h"

void Client::clientSocket()
{
    QByteArray message = "Hello, server!";

    udpSocket.writeDatagram(message, serverAddress, serverPort);

    // Чтение сообщений от UDP-сервера

    while (socketWait && udpSocket.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket.pendingDatagramSize());
        udpSocket.readDatagram(datagram.data(), datagram.size());

        // Обработка полученного сообщения
        qDebug() << "Received message from server:" << datagram;
    }
}
void Client::Update()
{
    if (mainWindow->command == not_registered)
        return;
}
QJsonObject Client::send(QJsonObject json)
{
    QJsonObject jsonObject;
    QJsonDocument jsonDocument(json);
    QByteArray message = jsonDocument.toJson();
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
                if (jsonDoc.isObject()) {
                    QJsonObject jsonObject = jsonDoc.object();

                    return jsonObject;
                }
            }
            // Обработка полученного сообщения
            qDebug() << "Received message from server:" << datagram;
        }

        auto current = std::chrono::steady_clock::now();
        elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(current - start).count();
        if (elapsedSeconds >= 5) {
            QJsonObject jsonObject;
            jsonObject["response"] = "timeout";
            return jsonObject;
            break;
        }
    }
    jsonObject["response"] = "fail";
    return jsonObject;
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
        if (!socketWait)
            timer.stop();

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
