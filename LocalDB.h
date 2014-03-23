#ifndef LOCALDB_H
#define LOCALDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QFile>
#include "UserProfile.h"

#define UP_TABLE        "rp_user_profile"
#define UP_USERNAME     "user_name"
#define UP_PASSWORD     "password"
#define UP_LOGINSTATUS  "login_status"
#define UP_EXPGAIN      "exp_gain"
#define UP_DISTANCE     "total_distance"
#define UP_DURATION     "total_time_in_sec"
#define UP_SPEED        "average_speed"

class LocalDB : public QObject
{
public:
    LocalDB(){}
    ~LocalDB(){}

    bool openDB(){
        // Find QSLite driver
        db = QSqlDatabase::addDatabase("QSQLITE");

        // NOTE: File exists in the application private folder, in Symbian Qt implementation
        db.setDatabaseName("my.db.sqlite");

        // Open databasee
        return db.open();
    }

    void closeDB(){
        db.close();
        return;
    }

    bool deleteDB(){
        // Close database
        db.close();

        // Remove created database binary file
        return QFile::remove("my.db.sqlite");
    }

    bool create_user_profile_Table(){
        QSqlQuery query;

        query.exec("create table " UP_TABLE " ("
                   UP_USERNAME " varchar(20), "
                   UP_PASSWORD " varchar(20), "
                   UP_LOGINSTATUS " int, "
                   UP_EXPGAIN " int, "
                   UP_DISTANCE " int, "
                   UP_DURATION " int, "
                   UP_SPEED " float"
                   ")");

        return true;
    }

    QSqlError lastError(){
        // If opening database has failed user can ask
        // error description by QSqlError::text()
        return db.lastError();
    }

    bool get_login_user(UserProfile *pUserProfile)
    {
        QSqlQuery query("SELECT "
                        UP_USERNAME ", "
                        UP_PASSWORD ", "
                        UP_EXPGAIN ", "
                        UP_DISTANCE ", "
                        UP_DURATION ", "
                        UP_SPEED
                        " FROM " UP_TABLE
                        " WHERE " UP_LOGINSTATUS "=1" );

        while (query.next()) {
            pUserProfile->sUserName = query.value(UP_USERNAME).toString();
            pUserProfile->sPassword = query.value(UP_PASSWORD).toString();
            pUserProfile->nExpGain = query.value(UP_EXPGAIN).toInt();
            pUserProfile->nTotalDistance = query.value(UP_DISTANCE).toInt();
            pUserProfile->nTotalTimeInSec = query.value(UP_DURATION).toInt();
            pUserProfile->dAverageSpeed = query.value(UP_SPEED).toDouble();

            pUserProfile->nLoginStatus = 1;

            return true;
        }

        return false;
    }

    bool is_user_exist(QString sUserName, QString sPassword)
    {
        QSqlQuery query("SELECT "
                        UP_USERNAME ", "
                        UP_PASSWORD ", "
                        UP_LOGINSTATUS
                        " FROM " UP_TABLE );
        while (query.next()){
            if( query.value(UP_USERNAME).toString() == sUserName &&
                query.value(UP_PASSWORD).toString() == sPassword )
                return true;
            else
                return false;
        }

        return true;
    }

    bool create_user(UserProfile *pUserProfile)
    {
        QSqlQuery query;
        QString sQuery;
        QString sValues;

        sValues = QString("'%1', '%2', %3, %4, %5, %6, %7")
                    .arg(pUserProfile->sUserName)
                    .arg(pUserProfile->sPassword)
                    .arg(pUserProfile->nLoginStatus)
                    .arg(pUserProfile->nExpGain)
                    .arg(pUserProfile->nTotalDistance)
                    .arg(pUserProfile->nTotalTimeInSec)
                    .arg(pUserProfile->dAverageSpeed );

        sQuery = QString("insert into " UP_TABLE "("
                         UP_USERNAME ", "
                         UP_PASSWORD ", "
                         UP_LOGINSTATUS ","
                         UP_EXPGAIN ", "
                         UP_DISTANCE ", "
                         UP_DURATION ", "
                         UP_SPEED ") "
                         "values( "
                         "%1"
                         ")"
                         " FROM " UP_TABLE
                         " WHERE " UP_LOGINSTATUS "=1" )
                        .arg(sValues);

        query.exec(sQuery);

        return true;
    }

private:
    QSqlDatabase db;
};

#endif // LOCALDB_H
