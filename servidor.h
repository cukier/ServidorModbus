#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <QMainWindow>
#include "libmodbus/src/modbus.h"

class Serial;
class ModbusListner;
class MemoryMap;

namespace Ui {
class Servidor;
}

class Servidor : public QMainWindow
{
    Q_OBJECT

public:
    explicit Servidor(QWidget *parent = nullptr);
    ~Servidor();

private slots:
    void onConn();

private:
    Ui::Servidor *ui;
    Serial *serial;
    modbus_t *ctx;
    modbus_mapping_t *mb_mapping;
    ModbusListner *listner;
    MemoryMap *map;

    bool isConn = false;
};

#endif // SERVIDOR_H
