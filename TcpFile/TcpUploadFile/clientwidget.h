#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QtNetwork/QTcpSocket>
#include <QFile>

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
    void on_btn_conntct_clicked();
    void on_ready_read();

private:
    Ui::ClientWidget *ui;
    QTcpSocket m_socket;

    QFile* m_file;
    bool m_isStart;
    qint64 m_fileSize;
    QString m_fileName;
    qint64 m_recieveSize;
};

#endif // CLIENTWIDGET_H
