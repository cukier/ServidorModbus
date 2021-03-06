#include "modbuslistner.h"

#include <QDebug>

ModbusListner::ModbusListner(modbus_t *modbusCtx, modbus_mapping_t *modbusMappin)
    : ctx(modbusCtx)
    , mb_mapping(modbusMappin)
{

}

void ModbusListner::run()
{
    if (!ctx) {
        qDebug() << "<ModbusListner> ctx nao existe";
        return;
    }

    int rc;
    quint8 query[MODBUS_TCP_MAX_ADU_LENGTH];

    for (;;) {
        do {
            QMutexLocker locker(&mutex);
            rc = modbus_receive(ctx, query);
        } while (rc == 0);

        if (rc == -1 && errno != EMBBADCRC) {
            continue;
        }

        {
            QMutexLocker locker(&mutex);
            rc = modbus_reply(ctx, query, rc, mb_mapping);
            emit newMap();
        }

        if (rc == -1) {
            break;
        }
    }
}
