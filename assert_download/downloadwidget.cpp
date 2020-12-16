#include "downloadwidget.h"
#include "ui_downloadwidget.h"
#include <QStringList>
#include <QFileInfo>
#include <QCoreApplication>
#include <QMessageBox>
#include <QDir>
#include <QDebug>

static int count = 0;
DownloadWidget::DownloadWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DownloadWidget)
{
    ui->setupUi(this);

    m_assetServer = new DownloadServer();
    m_importServer = new DownloadServer();
    connect(m_assetServer, &DownloadServer::sigHandleFinished, this, &DownloadWidget::downloadAssetsFinished);
    connect(m_assetServer, &DownloadServer::sigProcessUpdate, this, &DownloadWidget::downloadAssetsProgress);
    connect(m_importServer, &DownloadServer::sigHandleFinished, this, &DownloadWidget::downloadImportFinished);
    connect(m_importServer, &DownloadServer::sigProcessUpdate, this, &DownloadWidget::downloadImportProgress);

    m_7zPath = QCoreApplication::applicationDirPath()+"/7z.exe";
//    m_assetServer->downloadFileAsync(QUrl("http://ideavr.top/download/avatar-assets/ceshi.zip")
//                                     ,QDir::homePath()+"/AppData/Roaming/Ideavr/assets.zip");
//    m_importServer->downloadFileAsync(QUrl("http://ideavr.top/download/avatar-assets/ceshi1.zip")
//                                      ,QDir::homePath()+"/AppData/Roaming/Ideavr/import.zip");
//    m_7zPath = QCoreApplication::applicationDirPath()+"/bandizip/bz.exe";
    m_assetServer->downloadFileAsync(QUrl("http://gdi-update.obs.cn-east-2.myhuaweicloud.com/avatar_asset/assets.zip")
                                     ,QDir::homePath()+"/AppData/Roaming/Ideavr/assets.zip");
    m_importServer->downloadFileAsync(QUrl("http://gdi-update.obs.cn-east-2.myhuaweicloud.com/avatar_asset/import.zip")
                                      ,QDir::homePath()+"/AppData/Roaming/Ideavr/import.zip");
}

DownloadWidget::~DownloadWidget()
{
    delete ui;
}

void DownloadWidget::downloadAssetsProgress(float value)
{
    if(100.0 - value*100 < 0.1)
        ui->asset_pgr->setValue(100);
    else
        ui->asset_pgr->setValue(value*100);
}

void DownloadWidget::downloadImportProgress(float value)
{
    if(100.0 - value*100 < 0.1)
        ui->import_pgr->setValue(100);
    else
        ui->import_pgr->setValue(value*100);
}

void DownloadWidget::downloadAssetsFinished()
{
    unpressed(m_assetServer->getSavePath(),QCoreApplication::applicationDirPath() + "/data/assets");

    ++count;
    if(count == 2){
        this->close();
    }
}

void DownloadWidget::downloadImportFinished()
{
    unpressed(m_importServer->getSavePath(),QCoreApplication::applicationDirPath() + "/data/import");

    ++count;
    if(count == 2){
        this->close();
    }
}

void DownloadWidget::unpressed(const QString &zip, const QString &unpressDir)
{
    QDir _dir(unpressDir);
    if(_dir.exists())
        _dir.removeRecursively();

    QString _cmd = "\"" + m_7zPath + "\"" + " x " + "\"" +zip + "\"" + " -o\"" + unpressDir + "\"";
    // QString _cmd = "\"" + m_7zPath + "\"" + " x -o:" + "\"" +unpressDir + "\"" + " " + "\"" +zip + "\"";
    m_process = new QProcess(this);
    m_process->start(_cmd);

    if(m_process->waitForStarted(3000))
    {

    }
    if(m_process->waitForFinished(6000000))
    {

    }
    QFile::remove(zip);
}
