#include "console.h"
#include <QApplication>
#include <QScrollBar>
#include <QtDebug>

Console::Console(QTextBrowser *console)
    : _console(console)
{}

void Console::setConsole(QTextBrowser *console)
{
    _console = console;
}

QTextBrowser *Console::getConsole()
{
    return _console;
}

void Console::writeLine(QString &line)
{
    if (_console == nullptr) {
        qDebug() << line;
        return;
    }
    _lines.push_back(line);
    QString lines;
    for (int i = 0; i < _lines.size(); ++i) {
        lines += ">" + _lines[i] + '\n';
    }
    _console->setText(lines);
    QScrollBar *scrollBar = _console->verticalScrollBar();
    scrollBar->setValue(scrollBar->maximum());
    _console->moveCursor(QTextCursor::End);    
}

void Console::writeLine(QString &&line)
{
    writeLine(line);
}
