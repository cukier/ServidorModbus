#include "servidor.h"
#include "ui_servidor.h"

#include "serial.h"
#include "modbuslistner.h"
#include "memorymap.h"

#include <QDebug>

Servidor::Servidor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Servidor),
    serial(new Serial),
    ctx(nullptr),
    mb_mapping(nullptr),
    listner(nullptr),
    map(new MemoryMap(this))
{
    ui->setupUi(this);

    connect(ui->actionConfigurar, &QAction::triggered,
            this, [this] () {
        serial->setVisible(true);
    });

    connect(ui->pbConn, &QPushButton::clicked,
            this, &Servidor::onConn);

    if (map) {
        ui->tableView->setModel(map);
    }
}

Servidor::~Servidor()
{    
    if (listner) {
        disconnect(listner);
        listner->terminate();
        delete listner;
    }

    if (mb_mapping) {
        modbus_mapping_free(mb_mapping);
    }

    if (ctx) {
        modbus_close(ctx);
        modbus_free(ctx);
    }

    delete serial;
    delete ui;
}

void Servidor::onConn()
{
    if (isConn) {
        if (listner) {
            disconnect(listner);
            listner->terminate();
            delete listner;
            listner = nullptr;
        }

        if (mb_mapping) {
            modbus_mapping_free(mb_mapping);
            mb_mapping = nullptr;
        }

        if (ctx) {
            modbus_close(ctx);
            modbus_free(ctx);
            ctx = nullptr;
        }

        isConn = false;
        ui->pbConn->setText("Conectar");
        ui->statusbar->showMessage("Desconectado");
    } else {
        ctx = modbus_new_rtu(serial->getParameters().porta.toUtf8(),
                             serial->getParameters().baud,
                             serial->getParameters().parity.toLatin1(),
                             serial->getParameters().data,
                             serial->getParameters().stop);

        if (!ctx) {
            qDebug() << "<Servidor> erro ao criar servidor";
            return;
        }

        modbus_set_slave(ctx, serial->getParameters().addr);
        mb_mapping = modbus_mapping_new(10, 10, 1024, 1024);

        if (!mb_mapping) {
            qDebug() << "<Servidor> erro ao iniciar mapa";
            modbus_free(ctx);
            return;
        }

        int rc = modbus_connect(ctx);

        if (rc == -1) {
            modbus_free(ctx);
            modbus_mapping_free(mb_mapping);
            return;
        }

        isConn = true;
        listner = new ModbusListner(ctx, mb_mapping);
        connect(listner, &ModbusListner::newMap,
                this, &Servidor::onNewMap);
        listner->start();
        ui->pbConn->setText("Desconectar");
        ui->statusbar->showMessage("Conectado");
    }
}

void Servidor::onNewMap()
{
    qDebug() << "<Servidor> newMap";

    for (int i = 0; i < 200; ++i) {
        int col = i % 10;
        int lin = int(double(i) / 10);
        QModelIndex index = map->index(lin, col);
        quint16 val = mb_mapping->tab_registers[i];
        map->setData(index, val);
    }
}
