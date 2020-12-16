#include "downloadwidget.h"
#include "ui_downloadwidget.h"
#include <QStringList>
#include <QFileInfo>
#include <QCoreApplication>
#include <QMessageBox>
#include <QDir>

DownloadWidget::DownloadWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DownloadWidget),
    m_process(NULL)
{
    ui->setupUi(this);

    m_server = new DownloadServer();
    connect(m_server, &DownloadServer::sigAssetsFinished, this, &DownloadWidget::assetFinished);
    connect(m_server, &DownloadServer::sigHandleFinished, this, &DownloadWidget::downloadFinished);
    connect(m_server, &DownloadServer::sigProcessUpdate, this, &DownloadWidget::downloadProgress);
}

DownloadWidget::~DownloadWidget()
{
    delete ui;
}

void DownloadWidget::downloadProgress(float value)
{
    if(100.0 - value*100 < 0.1)
        ui->progressBar->setValue(100);
    else
        ui->progressBar->setValue(value*100);
}

void DownloadWidget::downloadFinished()
{
    ui->label->setText("解压中..");

    QString _assetDir = QCoreApplication::applicationDirPath() + "/data";
    QDir _dir(_assetDir+"/assets");
    if(_dir.exists())
        _dir.removeRecursively();

    m_process = new QProcess(this);
    QString _exePath = QCoreApplication::applicationDirPath()+"/bandizip/bz.exe";
    QString _zipPath = m_server->GetAssetsFilePath();

    QString _cmd = "\"" + _exePath + "\"" + " x -o:" + "\"" +_assetDir + "\"" + " " + "\"" +_zipPath + "\"";
    //QString _cmd = _exePath + " c " + _zipPath + " " + _assetDir;
    m_process->start(_cmd);

    if(!m_process->waitForStarted(3000))
    {
        //QMessageBox::warning(this,"警告","解压程序启动失败");
    }

    if(!m_process->waitForFinished(6000000))
    {
        this->hide();
        //QMessageBox::warning(this,"警告","解压失败");
    }
    else
    {
        this->hide();
    }


    QFile::remove(_zipPath);


    _dir.setPath(_assetDir+"/import");
    if(_dir.exists())
        _dir.removeRecursively();

    _zipPath = m_server->GetSaveFilePath();

    _cmd = "\"" + _exePath + "\"" + " x -o:" + "\"" +_assetDir + "\"" + " " + "\"" +_zipPath + "\"";
    m_process->start(_cmd);

    if(!m_process->waitForStarted(3000))
    {
        //QMessageBox::warning(this,"警告","解压程序启动失败");
    }

    if(!m_process->waitForFinished(6000000))
    {
        this->hide();
        //QMessageBox::warning(this,"警告","解压失败");
    }
    else
    {
        this->hide();
    }


    QFile::remove(_zipPath);
    this->close();
}

void DownloadWidget::assetFinished()
{
    ui->label->setText("下载工业数据..");
}
