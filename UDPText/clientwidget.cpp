#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QHostAddress>

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);

    m_udpSocket = new QUdpSocket(this);
    m_udpSocket->bind(8080);

    m_udpSocket->connect(m_udpSocket,&QUdpSocket::readyRead,[=](){

        char _buffer[1024] = {0};
        QHostAddress _address;
        quint16 _port;

        int _len = m_udpSocket->readDatagram(_buffer,sizeof(_buffer),&_address,&_port);
        if(_len > 0)
        {
            ui->textEdit_read->setText(QString("ip%1:port%2 %3").arg(_address.toString()).arg(_port).arg(_buffer));
        }

    });
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_btn_send_clicked()
{
    m_udpSocket->writeDatagram(ui->textEdit_write->toPlainText().toUtf8()
                               ,QHostAddress(ui->lineEdit_ip->text()),ui->lineEdit_port->text().toInt());
}

void ClientWidget::on_btn_close_clicked()
{
    m_udpSocket->close();
}
