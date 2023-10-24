#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QThread>
#include <QUdpSocket>
class MainWindow;
class Client : public QThread
{
    Q_OBJECT
private:
    QUdpSocket udpSocket;
    QByteArray datagram;
    qint16 serverPort = 7777;
    QHostAddress serverAddress{"127.0.0.1"};
    MainWindow *mainWindow;
    void run() override;
    bool socketWait = true;
    void Update();
    void clientSocket();

public:
    Client() {}

    explicit Client(MainWindow *_mainWindow, QObject *parent = nullptr);

    QJsonObject send(QJsonObject json, int timeout = 0);
    void close();

public slots:
    void handleMainWindowClosed();

signals:
    void mainWindowClosed();
};

#endif // CLIENT_H
