#include "facebookclient.h"

#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QEventLoop>
#include <QImageReader>
#include <QImage>
#include <QDebug>
#include <QJsonObject>

#define FACEBOOK_GRAPH_PATH "https://graph.facebook.com/"

FacebookClient::FacebookClient(QObject *parent) :
    QObject(parent)
{
}

void FacebookClient::SetAccessToken(QString s)
{
    m_accessToken = s;
    return;
}

void FacebookClient::GetUserProfileInfo()
{
    QNetworkAccessManager* nam = new QNetworkAccessManager(this);

    QString sRequestString = QString(FACEBOOK_GRAPH_PATH).append("me?access_token=").append(m_accessToken);
    QUrl url(sRequestString);
    QNetworkReply* reply = nam->get(QNetworkRequest(url));

    QEventLoop eventloop;
    connect(reply,SIGNAL(finished()),&eventloop,SLOT(quit()));
    eventloop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray reply_json = reply->readAll();
        QString val = QString::fromUtf8(reply_json);
        qDebug() << val;

        QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
        QJsonObject sett2 = d.object();
        QJsonValue value = sett2.value(QString("id"));
        qDebug() << value.toString();
    }
}
