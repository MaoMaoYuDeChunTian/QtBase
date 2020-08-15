#include "serverwidget.h"
#include "ui_serverwidget.h"

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget),
    m_tcpSocket(nullptr)
{
    ui->setupUi(this);

    m_tcpServer = new QTcpServer(this);
    m_tcpServer->listen(QHostAddress::Any,8080);
    m_tcpServer->connect(m_tcpServer,&QTcpServer::newConnection,
                         [=]()
                         {
                            m_tcpSocket = m_tcpServer->nextPendingConnection();
                            QString _ip = m_tcpSocket->peerAddress().toString();
                            quint16 _port = m_tcpSocket->peerPort();
                            ui->textEdit_receive->setText(QString("连接成功 ip：%1-port:%2").arg(_ip).arg(_port));
                            m_tcpSocket->write("服务器连接成功");

                            m_tcpSocket->connect(m_tcpSocket,&QTcpSocket::readyRead,
                                                 [=]()
                                                 {
                                                    ui->textEdit_receive->append(m_tcpSocket->readAll());
                                                 }
                                                 );
                         }

                         );
}

ServerWidget::~ServerWidget()
{
    delete ui;
}

void ServerWidget::on_pushButton_send_clicked()
{
    if(m_tcpSocket)
        m_tcpSocket->write(ui->textEdit_send->toPlainText().toUtf8().data());
}

void ServerWidget::on_pushButton_close_clicked()
{
    if(m_tcpSocket)
    {
        m_tcpSocket->disconnectFromHost();
        m_tcpSocket->close();
    }
}
