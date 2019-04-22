#ifndef SERIAL_H
#define SERIAL_H

#include <QWidget>

namespace Ui {
class Serial;
}

class Param {
public:
    QString porta = "COM2";
    int baud = 19200;
    int data = 8;
    QChar parity = 'N';
    int stop = 1;
    int addr = 1;
};

class Serial : public QWidget
{
    Q_OBJECT

public:
    explicit Serial(QWidget *parent = nullptr);
    ~Serial();

    Param getParameters();

private:
    Ui::Serial *ui;
    Param m_parameters;
};

#endif // SERIAL_H
