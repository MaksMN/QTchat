#ifndef WIDGETLIST_H
#define WIDGETLIST_H
#include <QWidget>

typedef unsigned int uint;
typedef unsigned long long ullong;
class WidgetLabel;
namespace Ui {
class WidgetList;
}

class WidgetList : public QWidget
{
    Q_OBJECT

private:
    WidgetLabel *_selectedLabel = nullptr;
    int _selectedIndex = -1;

public:
    explicit WidgetList(QWidget *parent = nullptr);
    ~WidgetList();

    void select(WidgetLabel *label);

    void deselect();

private:
    Ui::WidgetList *ui;
};

#endif // WIDGETLIST_H
