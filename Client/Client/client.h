#ifndef CLIENT_H
#define CLIENT_H

#include <QMutex>
#include <QObject>
#include <QThread>
#include <QUdpSocket>
class MainWindow;
class Client : public QThread
{
    Q_OBJECT
private:
    qint16 serverPort = 7777;
    QHostAddress serverAddress{"127.0.0.1"};
    MainWindow *mainWindow;
    void run() override;
    bool socketWait = true;
    void Update();
    int getTopUserItem();
    int getTopMessageItem();
    QJsonDocument addSessionInJson(QJsonDocument &json);
    QMutex mutex;

public:
    Client();

    explicit Client(MainWindow *_mainWindow, QObject *parent = nullptr);

    QJsonDocument send(QJsonDocument json, int timeout = 0, bool add_session = true);
    void close();

public slots:
    void handleMainWindowClosed();

signals:
    void mainWindowClosed();
};

#endif // CLIENT_H
