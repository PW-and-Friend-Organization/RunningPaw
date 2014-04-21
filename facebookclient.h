#ifndef FACEBOOKCLIENT_H
#define FACEBOOKCLIENT_H

#include <QObject>

class FacebookClient : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int found READ found WRITE setFound NOTIFY foundChanged)

public:
    QString m_accessToken;
    QString m_sName;
    QString m_sId;
    int     m_nFound;

public:
    explicit FacebookClient(QObject *parent = 0);

    void SetAccessToken(QString s);
    void GetUserProfileInfo();

    QString name() const;
    void    setName(const QString &a);

    int     found() const;
    void    setFound(const int &a);

signals:
    void nameChanged();
    void foundChanged();

public slots:

};

#endif // FACEBOOKCLIENT_H
