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


    QString downloadDirPath = "";
#ifdef Q_OS_WIN32
    m_7zPath = QCoreApplication::applicationDirPath()+"/7z.exe";
    downloadDirPath = QDir::homePath()+"/AppData/Roaming/Ideavr";
#endif

#ifdef Q_OS_MAC
    m_7zPath = QCoreApplication::applicationDirPath()+"/7z.exe";
    downloadDirPath = QDir::homePath();
#endif

#ifdef Q_OS_LINUX
    m_7zPath = QCoreApplication::applicationDirPath()+"/7z";
    downloadDirPath = QDir::homePath();
#endif


    //  m_7zPath = QCoreApplication::applicationDirPath()+"/bandizip/bz.exe";



//    m_assetServer->downloadFileAsync(QUrl("http://ideavr.top/download/avatar-assets/ceshi.7z"),downloadDirPath+"/ceshi.7z");
//    m_importServer->downloadFileAsync(QUrl("http://ideavr.top/download/avatar-assets/ceshi1.7z"),downloadDirPath+"/ceshi1.7z");

    m_assetServer->downloadFileAsync(QUrl("http://ideavr.top/download/avatar-assets/assets.7z"),downloadDirPath+"/assets.7z");
    m_importServer->downloadFileAsync(QUrl("http://ideavr.top/download/avatar-assets/import.7z"),downloadDirPath+"/import.7z");

//    m_assetServer->downloadFileAsync(QUrl("http://gdi-update.obs.cn-east-2.myhuaweicloud.com/avatar_asset/assets.7z"),downloadDirPath+"/assets.7z");
//    m_importServer->downloadFileAsync(QUrl("http://gdi-update.obs.cn-east-2.myhuaweicloud.com/avatar_asset/import.7z"),downloadDirPath+"/import.7z");
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
        if(!isDirExist(QCoreApplication::applicationDirPath() + "/data/assets"))
        {
            this->hide();
            QMessageBox::warning(this,"警告","assets资源解压失败，没有权限，请尝试以管理员权限运行程序");
        }

        this->close();
    }
}

void DownloadWidget::downloadImportFinished()
{
    unpressed(m_importServer->getSavePath(),QCoreApplication::applicationDirPath() + "/data/import");

    ++count;
    if(count == 2){
        if(!isDirExist(QCoreApplication::applicationDirPath() + "/data/import"))
        {
            this->hide();
            QMessageBox::warning(this,"警告","import资源解压失败，没有权限，请尝试以管理员权限运行程序");
        }

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

        if(m_process->waitForFinished(6000000))

            QFile::remove(zip);
}

bool DownloadWidget::isDirExist(const QString &dirPath)
{
    QDir dir(dirPath);
    return dir.exists();
}


