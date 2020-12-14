#include "downloadserver.h"
#include <QDir>
#include <qcoreapplication.h>

DownloadServer::DownloadServer()
    :QObject()
    , m_reply(nullptr)
    , m_file(nullptr)
{
    m_saveFilePath = QDir::homePath()+"/AppData/Roaming/Ideavr/assets.zip";
    m_assetFilePath = "";
    downloadFileAsync(QUrl("http://gdi-update.obs.cn-east-2.myhuaweicloud.com/avatar_asset/assets.zip"));
}

void DownloadServer::RequestData(QUrl url)
{
    if (!url.isValid())
        return;

    QString _saveFilePath = QDir::cleanPath(m_saveFilePath);
    QFileInfo _downFileInfo(_saveFilePath);

    if (_downFileInfo.exists())
        QFile::remove(_saveFilePath);

    m_file = openFileForWrite(_saveFilePath);

    m_reply = m_manager.get(QNetworkRequest(url));
}

void DownloadServer::downloadFileAsync(QUrl url)
{
    RequestData(url);
    if (!m_reply)
        return;

    connect(m_reply, &QIODevice::readyRead, this,&DownloadServer::onHttpReadyRead);
    connect(m_reply, &QNetworkReply::finished, this,&DownloadServer::onHttpFinished);
    connect(m_reply, &QNetworkReply::downloadProgress,this, &DownloadServer::OnReplyProgress);
}

QString DownloadServer::GetSaveFilePath() const
{
    return m_saveFilePath;
}

QString DownloadServer::GetAssetsFilePath() const
{
    return m_assetFilePath;
}

void DownloadServer::onHttpFinished()
{
    if (!m_reply)
        return;

    QVariant statusCode = m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if (statusCode.toInt() != 200)
    {
        if (nullptr != m_file)
            m_file->remove();
    }
    if (nullptr != m_file)
    {
        m_file->close();
        delete m_file;
        m_file = nullptr;
    }

    m_reply->deleteLater();
    m_reply = Q_NULLPTR;

    emit sigAssetsFinished();

    m_assetFilePath = m_saveFilePath;
    m_saveFilePath = QDir::homePath()+"/AppData/Roaming/Ideavr/import.zip";

    RequestData(QUrl("http://gdi-update.obs.cn-east-2.myhuaweicloud.com/avatar_asset/import.zip"));
    if (!m_reply)
        return;

    connect(m_reply, &QIODevice::readyRead, this,&DownloadServer::onHttpReadyRead);
    connect(m_reply, &QNetworkReply::finished, this,&DownloadServer::onImportFinished);
    connect(m_reply, &QNetworkReply::downloadProgress,this, &DownloadServer::OnReplyProgress);
}

void DownloadServer::onHttpReadyRead()
{
    if (m_reply && m_file)
    {
        m_file->write(m_reply->readAll());
    }
}

void DownloadServer::OnReplyProgress(qint64 bytesRead, qint64 totalBytes)
{
    float _fpercent = bytesRead*1.0 / totalBytes;
    emit sigProcessUpdate(_fpercent);
}

void DownloadServer::onImportFinished()
{
    if (!m_reply)
        return;

    QVariant statusCode = m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if (statusCode.toInt() != 200)
    {
        if (nullptr != m_file)
            m_file->remove();
    }
    if (nullptr != m_file)
    {
        m_file->close();
        delete m_file;
        m_file = nullptr;
    }

    m_reply->deleteLater();
    m_reply = Q_NULLPTR;

    emit sigHandleFinished();
}

QFile *DownloadServer::openFileForWrite(const QString &fileName)
{
    QScopedPointer<QFile> _file(new QFile(fileName));
    if (!_file->open(QIODevice::WriteOnly)) {
        return Q_NULLPTR;
    }
    return _file.take();
}
