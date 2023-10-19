#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QListWidgetItem>
#include <QWidget>
#include "user.h"
#include <memory>
namespace Ui {
class UserWidget;
}

class CHATSTRUCTS_EXPORT UserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserWidget(QWidget *parent = nullptr);
    ~UserWidget();
    void Update(const std::shared_ptr<chat::User> &user);
    void Update();

    int id() const;
    void setId(int id);
    QListWidgetItem *item() const;
    std::shared_ptr<chat::User> user() const;
    void setUser(const std::shared_ptr<chat::User> &user);

private:
    int _id = -1;
    QListWidgetItem *_item{new QListWidgetItem()};
    std::shared_ptr<chat::User> _user = nullptr;
    Ui::UserWidget *ui;
};

#endif // USERWIDGET_H
