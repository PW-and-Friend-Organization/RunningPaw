#ifndef LOCALDB_H
#define LOCALDB_H


#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QFile>
#include <QMap>
#include <QVector>

class LocalDB : public QObject
{
    Q_OBJECT

public:
    explicit LocalDB(QObject *parent = 0);

    bool openDB();
    void closeDB();

    int CreateUserTable();
    int InsertUser(QString fb_id, QString fb_name, int Exp, int LoginStatus);
    int CheckIfUserLogin();

    int CreateFileFlow();

public:
    QVector<QString> rp_user_col_index;

    enum{
        id_rp_user_fb_id,
        id_rp_user_fb_name,
        id_rp_user_exp,
        id_rp_user_login_status
    };

    QString m_sFb_id;
    QString m_sFb_name;
    int     m_nExp;
    int     m_nLoginStatus;

    QSqlDatabase db;

signals:

public slots:

};

#endif // LOCALDB_H
