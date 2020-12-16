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
    void downloadAssetsProgress(float);
    void downloadImportProgress(float);
    void downloadAssetsFinished();
    void downloadImportFinished();

private:
    void unpressed(const QString& zip, const QString& unpressDir);

private:
    Ui::DownloadWidget *ui;
    DownloadServer* m_assetServer;
    DownloadServer* m_importServer;
    QProcess* m_process;
    QString m_7zPath;
};

#endif // DOWNLOADWIDGET_H
