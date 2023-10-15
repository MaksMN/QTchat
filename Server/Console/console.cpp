#include "console.h"
QTextBrowser *Console::_console = nullptr;
CircularQueue<QString, int> Console::_lines(255);

Console::Console() {}

void Console::setConsole(QTextBrowser *console)
{
    _console = console;
}

void Console::writeLine(QString line)
{
    if (_console == nullptr) {
        QDebug("Console not found");
    }
    _lines.push_front(line);
    QString lines;
    for (int i = 0; i < _lines.decue().size(); ++i) {
        lines += _lines[i] + '\n';
    }
    _console->setText(lines);
}
