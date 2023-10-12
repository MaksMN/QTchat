#ifndef WIDGETLABEL_H
#define WIDGETLABEL_H
#include <QLabel>
#include <QObject>
#include <QWidget>
#include "user.h"

typedef unsigned int uint;
typedef unsigned long long ullong;

class WidgetList;

class WidgetLabel : public QLabel
{
private:
    WidgetList *_widget;
    uint _index;

public:
    explicit WidgetLabel(WidgetList *widget, uint index, QString text, QWidget *parent = nullptr);
    uint index();
    void deselect();

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // WIDGETLABEL_H
