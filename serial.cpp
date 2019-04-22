#include "serial.h"
#include "ui_serial.h"

Serial::Serial(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Serial)
{
    ui->setupUi(this);

    ui->lePorta->setText(m_parameters.porta);
    ui->cbData->setCurrentText(QString("%0").arg(m_parameters.data));
    ui->cbParity->setCurrentText(QString(m_parameters.parity));
    ui->cbStop->setCurrentText(QString("%0").arg(m_parameters.stop));
    ui->cbBaud->setCurrentText(QString("%0").arg(m_parameters.baud));

    connect(ui->pbSalvar, &QPushButton::clicked,
            this, [this] () {
        m_parameters.porta = ui->lePorta->text();
        m_parameters.data = ui->cbData->currentText().toInt();
        m_parameters.parity = ui->cbParity->currentText()[0];
        m_parameters.stop = ui->cbStop->currentText().toInt();
        m_parameters.baud = ui->cbBaud->currentText().toInt();
        m_parameters.addr = ui->sbAddr->value();
        hide();
    });
}

Serial::~Serial()
{
    delete ui;
}

Param Serial::getParameters()
{
    return m_parameters;
}
