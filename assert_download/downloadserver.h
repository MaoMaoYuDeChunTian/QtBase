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

    void RequestData(QUrl url, const QString& saveFilePath);
    void downloadFileAsync(QUrl url, const QString& saveFilePath);
    QString GetSaveFilePath()const;

public slots:
    void onHttpFinished();
    void onHttpReadyRead();
    void OnReplyProgress(qint64 bytesRead, qint64 totalBytes);

signals:
    void sigHandleFinished();
    void sigProcessUpdate(float);

protected:
    QFile *openFileForWrite(const QString &fileName);

private:
    QNetworkAccessManager m_manager;
    QNetworkReply*m_reply;
    QFile* m_file;
    QString m_saveFilePath;
};

#endif // DOWNLOADSERVER_H
