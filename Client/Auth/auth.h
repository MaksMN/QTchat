#ifndef AUTH_H
#define AUTH_H

#include <QDialog>
#include "client.h"
#include "user.h"

namespace Ui {
class Auth;
}

class Auth : public QDialog
{
    Q_OBJECT

public:
    explicit Auth(QWidget *parent = nullptr);
    ~Auth();

    bool authorized() const;

    std::shared_ptr<chat::User> user = nullptr;
    void setLabelMsgText(QString &text);

private slots:
    void on_regButton_clicked();

    void on_loginButton_clicked();

private:
    Ui::Auth *ui;
    bool _authorized = false;

    Client client{};
};

#endif // AUTH_H
