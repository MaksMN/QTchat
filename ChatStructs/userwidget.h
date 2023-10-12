#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QWidget>
#include "user.h"
typedef unsigned int uint;
typedef unsigned long long ullong;
namespace Ui {
class UserWidget;
}

class CHATSTRUCTS_EXPORT UserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserWidget(QWidget *parent = nullptr);
    ~UserWidget();
    void setUser(chat::User *user);
    ullong userID();

private:
    ullong _userID;
    chat::User *_user;
    Ui::UserWidget *ui;
};

#endif // USERWIDGET_H
