#include "serverwidget.h"
#include "ui_serverwidget.h"
#include <QHostAddress>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);

    m_socket = NULL;
    ui->btn_choose->setEnabled(false);
    ui->btn_send->setEnabled(false);

    m_server.listen(QHostAddress::Any,8080);
    m_server.connect(&m_server,&QTcpServer::newConnection,[=]
    {
        m_socket = m_server.nextPendingConnection();
        quint16 _port = m_socket->peerPort();
        QHostAddress _address = m_socket->peerAddress();
        ui->textEdit->append(QString("[%1 port%2]连接成功").arg(_address.toString()).arg(_port));

        ui->btn_choose->setEnabled(true);
        ui->btn_send->setEnabled(false);

        m_socket->connect(m_socket,&QTcpSocket::readyRead,[=]{
            QByteArray _bty = m_socket->readAll();
            ui->textEdit->setText(_bty);
        });
    });


    m_timer.connect(&m_timer,&QTimer::timeout,[=]{
        m_timer.stop();
        sendDate();
    });
}

ServerWidget::~ServerWidget()
{
    delete ui;
}

void ServerWidget::sendDate()
{
    if(nullptr == m_file || nullptr == m_socket)
        return;

    qint64 len = 0;

    do
    {
        char _buffer[4*1024] = {0};
        len = m_file->read(_buffer,sizeof(_buffer));
        m_socket->write(_buffer,len);
        m_readSize += len;

    }while (len > 0);

    if(m_readSize == m_fileSize)
    {
        ui->textEdit->append("文件发送完毕");

        m_socket->disconnectFromHost();
        m_socket->close();
        ui->btn_choose->setEnabled(false);
        ui->btn_send->setEnabled(false);
    }
}

void ServerWidget::on_btn_choose_clicked()
{
    QString _filePath = QFileDialog::getOpenFileName(this,"文件名","../");
    if(_filePath.isEmpty())
        return;

    QFileInfo _info(_filePath);

    m_readSize = 0;
    m_fileName = _info.fileName();
    m_filePath = _info.filePath();
    m_fileSize = _info.size();

    ui->btn_send->setEnabled(true);
    ui->textEdit->append("待发送文件："+m_fileName);
}

void ServerWidget::on_btn_send_clicked()
{
    if(nullptr == m_socket)
         return;

    m_file = new QFile(m_filePath);
    if(!m_file->open(QIODevice::ReadOnly))
    {
        delete m_file;
        m_file = nullptr;
        return;
    }

    qint64 _len = m_socket->write(QString("%1##%2").arg(m_fileName).arg(m_fileSize).toUtf8());
    if(_len > 0)
    {
        //发送真正的文件
        //利用定时器防止粘包
        m_timer.start(20);
    }
    else
    {
        QMessageBox::about(this,"提示","发送文件失败！");
        m_file->close();
        delete m_file;
        m_file = nullptr;
    }
}
