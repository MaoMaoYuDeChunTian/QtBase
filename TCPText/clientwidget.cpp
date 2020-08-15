#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QHostAddress>

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget),
    m_tcpSocket(nullptr)
{
    ui->setupUi(this);

    m_tcpSocket = new QTcpSocket(this);
    m_tcpSocket->connect(m_tcpSocket,&QTcpSocket::readyRead
                         ,[=]()
                         {
                            ui->textEdit_receive->setText(m_tcpSocket->readAll());
                         }
    );
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_btn_connect_clicked()
{
    m_tcpSocket->connectToHost(QHostAddress(ui->lineEdit_ip->text()),ui->lineEdit_port->text().toInt());
}

void ClientWidget::on_pushButton_send_clicked()
{
    m_tcpSocket->write(ui->textEdit_send->toPlainText().toUtf8().data());
}

void ClientWidget::on_pushButton_close_clicked()
{
    m_tcpSocket->disconnectFromHost();
    m_tcpSocket->close();
}
