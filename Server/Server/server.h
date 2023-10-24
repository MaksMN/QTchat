#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QThread>
#include <QUdpSocket>
class MainThread;

class Server : public QThread
{
    Q_OBJECT
private:
    int port = 7777;
    void ConsoleWrite(const QString &line);
    bool waitFlag = true;

    QJsonObject registerUser(QJsonObject json);
    QJsonObject authUser(QJsonObject json);
    QJsonObject getUsers(QJsonObject json);

public:
    MainThread *mainThread = nullptr;
    explicit Server(QThread *parent = nullptr);

    void serverSocket();
    QJsonObject serverHandle(QJsonObject json);

    void run() override;
    void stop();

signals:
    void mainWindowClosed();
public slots:
    void handleMainWindowClosed();
};

#endif // SERVER_H
