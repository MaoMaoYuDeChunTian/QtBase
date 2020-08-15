#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QtNetwork/QUdpSocket>

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
    void on_btn_send_clicked();

    void on_btn_close_clicked();

private:
    Ui::ServerWidget *ui;

    QUdpSocket* m_udpSocket;
};

#endif // SERVERWIDGET_H
