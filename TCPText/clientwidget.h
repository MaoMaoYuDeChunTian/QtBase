#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QtNetwork/QTcpSocket>

namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = 0);
    ~ClientWidget();

private slots:
    void on_btn_connect_clicked();

    void on_pushButton_send_clicked();

    void on_pushButton_close_clicked();

private:
    Ui::ClientWidget *ui;

    QTcpSocket* m_tcpSocket;
};

#endif // CLIENTWIDGET_H
