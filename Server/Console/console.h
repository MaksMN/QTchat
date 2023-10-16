#ifndef CONSOLE_H
#define CONSOLE_H

#include <QTextBrowser>
#include "circularqueue.h"

class Console
{
private:
    QTextBrowser *_console;
    CircularQueue<QString, int> _lines;

public:
    explicit Console(QTextBrowser *console);
    void setConsole(QTextBrowser *console);
    QTextBrowser *getConsole();
    void writeLine(QString &line);
    void writeLine(QString &&line);
};

#endif // CONSOLE_H
