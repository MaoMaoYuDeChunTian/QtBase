#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QHostAddress>
#include <QStringList>

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget),
    m_isStart(true),
    m_file(nullptr),
    m_fileName(""),
    m_fileSize(0),
    m_recieveSize(0)
{
    ui->setupUi(this);

    m_socket.connect(&m_socket,&QTcpSocket::readyRead,this,&ClientWidget::on_ready_read);
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_btn_conntct_clicked()
{
    m_socket.connectToHost(QHostAddress(ui->edit_ip->text()),ui->edit_port->text().toInt());
}

void ClientWidget::on_ready_read()
{
    QByteArray _bty = m_socket.readAll();
    if(m_isStart)
    {
        m_isStart = false;
        QString _head = _bty;
        QStringList _list = _head.split("##");
        if(_list.count() != 2)
            return;

        m_fileName = _list[0];
        m_fileSize = _list.at(1).toInt();
        m_file = new QFile(m_fileName);
        if(!m_file->open(QIODevice::WriteOnly))
        {
            delete m_file;
            m_file = nullptr;
            return;
        }
    }
    else
    {
        if(nullptr == m_file)
            return;

        qint64 _len = m_file->write(_bty);
        m_recieveSize += _len;

        if(m_recieveSize == m_fileSize)
        {
            m_file->close();
            delete m_file;
            m_file = nullptr;
            ui->textEdit->append(QString("%1接收成功").arg(m_fileName));

            m_socket.disconnectFromHost();
            m_socket.close();
        }
    }
}
