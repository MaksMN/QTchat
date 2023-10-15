#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QTextBrowser>
#include <QWidget>
#include "circularqueue.h"

class Console
{
private:
    static QTextBrowser *_console;
    static CircularQueue<QString, int> _lines;

public:
    Console();
    static void setConsole(QTextBrowser *console);
    static void writeLine(QString line);
};

#endif // CONSOLE_H
