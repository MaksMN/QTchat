#include "widgetlist.h"
#include "./ui_widgetlist.h"
#include "widgetlabel.h"

WidgetList::WidgetList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetList)
{
    ui->setupUi(this);
}

WidgetList::~WidgetList()
{
    delete ui;
}

void WidgetList::select(WidgetLabel *label)
{
    deselect();
    if (label != nullptr) {
        _selectedLabel = label;
        _selectedIndex = label->index();
    }
}

void WidgetList::deselect()
{
    _selectedLabel = nullptr;
    _selectedIndex = -1;
}
