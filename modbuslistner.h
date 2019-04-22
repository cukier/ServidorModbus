#ifndef MODBUSLISTNER_H
#define MODBUSLISTNER_H

#include <QThread>
#include <QMutex>

#include "libmodbus/src/modbus.h"

class ModbusListner : public QThread
{
    Q_OBJECT
public:
    explicit ModbusListner(modbus_t *modbusCtx, modbus_mapping_t *modbusMappin);

    void run() override;

signals:
    void newMap();

public slots:

private:
    modbus_t *ctx;
    modbus_mapping_t *mb_mapping;

    QMutex mutex;
};

#endif // MODBUSLISTNER_H
