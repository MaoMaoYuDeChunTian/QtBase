#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include <QFile>
#include <QTimer>

namespace Ui {
class ServerWidget;
}

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWidget(QWidget *parent = 0);
    ~ServerWidget();

private:
    void sendDate();

private slots:
    void on_btn_choose_clicked();
    void on_btn_send_clicked();

private:
    Ui::ServerWidget *ui;
    QTcpServer m_server;
    QTcpSocket* m_socket;

    QFile* m_file;
    QString m_fileName;
    QString m_filePath;
    quint64 m_fileSize;
    quint64 m_readSize;
    QTimer m_timer;
};

#endif // SERVERWIDGET_H
