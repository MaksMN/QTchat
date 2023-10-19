#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QWidget>
#include "user.h"
#include <memory>
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
    void setUser(std::shared_ptr<chat::User> user);
    ullong userID();

private:
    ullong _userID;
    std::shared_ptr<chat::User> _user = nullptr;
    Ui::UserWidget *ui;
};

#endif // USERWIDGET_H
