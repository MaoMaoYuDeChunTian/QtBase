#ifndef DOWNLOADSERVER_H
#define DOWNLOADSERVER_H

#include <QObject>
#include <QFile>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class DownloadServer : public QObject
{
    Q_OBJECT
public:
    DownloadServer();

    void RequestData(QUrl url);
    void downloadFileAsync(QUrl url);
    QString GetSaveFilePath()const;
    QString GetAssetsFilePath()const;

public slots:
    void onHttpFinished();
    void onHttpReadyRead();
    void OnReplyProgress(qint64 bytesRead, qint64 totalBytes);
    void onImportFinished();

signals:
    void sigAssetsFinished();
    void sigHandleFinished();
    void sigProcessUpdate(float);

protected:
    QFile *openFileForWrite(const QString &fileName);

private:
    QNetworkAccessManager m_manager;
    QNetworkReply*m_reply;
    QFile* m_file;
    QString m_saveFilePath;
    QString m_assetFilePath;
};

#endif // DOWNLOADSERVER_H
