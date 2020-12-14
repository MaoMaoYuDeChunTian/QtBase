#ifndef DOWNLOADWIDGET_H
#define DOWNLOADWIDGET_H

#include <QWidget>
#include "downloadserver.h"
#include <QProcess>

namespace Ui {
class DownloadWidget;
}

class DownloadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DownloadWidget(QWidget *parent = 0);
    ~DownloadWidget();

public slots:
    void downloadProgress(float);
    void downloadFinished();
    void assetFinished();

private:
    Ui::DownloadWidget *ui;
    DownloadServer* m_server;
    QProcess* m_process;
};

#endif // DOWNLOADWIDGET_H
