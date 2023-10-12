#include "widgetlabel.h"
#include "widgetlist.h"

WidgetLabel::WidgetLabel(WidgetList *widget, uint index, QString text, QWidget *parent)
    : QLabel(text, parent)
    , _widget(widget)
    , _index(index)
{}

void WidgetLabel::mousePressEvent(QMouseEvent *event)
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::blue);
    this->setPalette(palette);

    QLabel::mousePressEvent(event);
}
