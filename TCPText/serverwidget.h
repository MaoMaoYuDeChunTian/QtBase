#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>

namespace Ui {
class ServerWidget;
}

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWidget(QWidget *parent = 0);
    ~ServerWidget();

private slots:
    void on_pushButton_send_clicked();

    void on_pushButton_close_clicked();

private:
    Ui::ServerWidget *ui;

    QTcpServer* m_tcpServer;
    QTcpSocket* m_tcpSocket;
};

#endif // SERVERWIDGET_H
