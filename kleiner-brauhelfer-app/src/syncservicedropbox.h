#ifndef SYNCSERVICEDROPBOX_H
#define SYNCSERVICEDROPBOX_H

#include "syncservice.h"
#include <QObject>
#include <QSettings>
#include <QNetworkReply>
#include <QStringListModel>

/**
 * @brief Dropbox synchronization service
 */
class SyncServiceDropbox : public SyncService
{
    Q_OBJECT

    Q_PROPERTY(QString accessToken READ accessToken WRITE setAccessToken NOTIFY accessTokenChanged)
    Q_PROPERTY(QString filePathServer READ filePathServer WRITE setFilePathServer NOTIFY filePathServerChanged)
    Q_PROPERTY(QStringListModel* folderContent READ folderContent NOTIFY accessTokenChanged)

public:

    /**
     * @brief Dropbox synchronization service
     * @param settings Settings
     */
    SyncServiceDropbox(QSettings *settings);
    ~SyncServiceDropbox();

    /**
     * @brief  Synchronizes the file
     * @param direction Direction to synchronize
     * @note See getState() for details about the synchronization state
     * @return True on success
     */
    bool synchronize(SyncDirection direction) Q_DECL_OVERRIDE;

    /**
     * @brief Gets the folder content
     * @return List of files
     */
    QStringListModel *folderContent();

    /**
     * @brief Gets the server access token
     * @return Access token
     */
    QString accessToken() const;

    /**
     * @brief Sets the server access token
     * @param token Access token
     */
    void setAccessToken(const QString &token);

    /**
     * @brief Gets the database path on the server
     * @return Database path
     */
    QString filePathServer() const;

    /**
     * @brief Sets the database path on the server
     * @param filePath Database path
     */
    void setFilePathServer(const QString &filePath);

signals:

    /**
     * @brief Emitted if access token was changed
     * @param token Access token
     */
    void accessTokenChanged(const QString &token);

    /**
     * @brief Emitted if database path on the server changed
     * @param filePath Database path
     */
    void filePathServerChanged(const QString &filePath);

private slots:
    void error(QNetworkReply::NetworkError error);
    void sslErrors(const QList<QSslError>& errors);

private:

    bool downloadFile();
    bool uploadFile();
    QString getServerRevision();
    QString getLocalRevision() const;
    void setLocalRevision(const QString &revision);
    QNetworkAccessManager* _netManager;
    QNetworkReply* _netReply;
    QStringListModel* _fileContent;
};

#endif // SYNCSERVICEDROPBOX_H
