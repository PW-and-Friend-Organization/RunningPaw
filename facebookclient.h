#ifndef FACEBOOKCLIENT_H
#define FACEBOOKCLIENT_H

#include <QObject>

class FacebookClient : public QObject
{
    Q_OBJECT

public:
    QString m_accessToken;
    QString m_sName;
    QString m_sId;

public:
    explicit FacebookClient(QObject *parent = 0);

    void SetAccessToken(QString s);
    void GetUserProfileInfo();

signals:

public slots:

};

#endif // FACEBOOKCLIENT_H
