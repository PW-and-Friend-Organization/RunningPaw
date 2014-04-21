#include "localdb.h"
#include "runningpaw.h"
#include <QVector>
#include <QVariant>
#include <QDebug>

#define USER_TABLE "RP_USERS"



LocalDB::LocalDB(QObject *parent) :
    QObject(parent)
{
    rp_user_col_index.insert( id_rp_user_fb_id, "fb_id" );
    rp_user_col_index.insert( id_rp_user_fb_name, "fb_name" );
    rp_user_col_index.insert( id_rp_user_exp, "Exp" );
    rp_user_col_index.insert( id_rp_user_login_status, "LoginStatus" );
}

bool LocalDB::openDB()
{
    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE");

    // NOTE: File exists in the application private folder, in Symbian Qt implementation
    db.setDatabaseName("my.db.sqlite");

    // Open databasee
    return db.open();
}

void LocalDB::closeDB()
{
    db.close();
    return;
}

int LocalDB::CreateUserTable()
{
    QSqlQuery query;

    QString statement;

    statement.append("CREATE TABLE IF NOT EXISTS ").append(USER_TABLE).append("(")
            .append(rp_user_col_index.at(id_rp_user_fb_id)).append(" varchar(50), ")
            .append(rp_user_col_index.at(id_rp_user_fb_name)).append(" varchar(250), ")
            .append(rp_user_col_index.at(id_rp_user_exp)).append(" integer, ")
            .append(rp_user_col_index.at(id_rp_user_login_status)).append(" integer").append(");");

    query.exec( statement );

    return true;
}

int LocalDB::InsertUser(QString fb_id, QString fb_name, int Exp, int LoginStatus)
{
    QSqlQuery query;

    QString statement;
    QString sColumn;
    QString sValue;

    sColumn.append(rp_user_col_index.at(id_rp_user_fb_id)).append(",")
            .append(rp_user_col_index.at(id_rp_user_fb_name)).append(",")
            .append(rp_user_col_index.at(id_rp_user_exp)).append(",")
            .append(rp_user_col_index.at(id_rp_user_login_status));

    sValue.append("\'").append(fb_id).append("\', ")
          .append("\'").append(fb_name).append("\', ")
          .append(QString("%1").arg(Exp)).append(", ")
          .append(QString("%1").arg(LoginStatus));

    statement.append("INSERT INTO ").append(USER_TABLE).append("(")
            .append(sColumn).append(")VALUES(")
            .append(sValue).append(");");

    query.exec(statement);

    return true;
}

int LocalDB::UpdateUser(QString fb_id, QString fb_name, int Exp, int LoginStatus)
{
    QSqlQuery query;

    QString statement;
    QString sSet;
    QString sWhere;

    sSet.append(rp_user_col_index.at(id_rp_user_fb_name)).append("=\'").append(fb_name).append("\',")
        .append(rp_user_col_index.at(id_rp_user_exp)).append("=").append(QString("%1").arg(Exp)).append(",")
        .append(rp_user_col_index.at(id_rp_user_login_status)).append("=").append(QString("%1").arg(LoginStatus));

    sWhere.append(rp_user_col_index.at(id_rp_user_fb_id)).append("=\'").append(fb_id).append("\'");

    statement.append("UPDATE ").append(USER_TABLE).append(" SET ").append(sSet).append(" WHERE ").append(sWhere);

    query.exec(statement);

    return true;
}

int LocalDB::CheckIfUserLogin()
{
    QString statement;
    statement.append("Select * From ").append(USER_TABLE).append(" where ")
            .append(rp_user_col_index.at(id_rp_user_login_status)).append(" = 1;");

    QSqlQuery query(statement);
    QSqlRecord rec = query.record();

    while (query.next())
    {
        m_sFb_id = query.value( rec.indexOf(rp_user_col_index.at(id_rp_user_fb_id)) ).toString();
        m_sFb_name = query.value( rec.indexOf(rp_user_col_index.at(id_rp_user_fb_name)) ).toString();
        m_nExp = query.value( rec.indexOf(rp_user_col_index.at(id_rp_user_exp)) ).toInt();
        m_nLoginStatus = query.value( rec.indexOf(rp_user_col_index.at(id_rp_user_login_status)) ).toInt();
    }

    if( m_sFb_id != "")
    {
        theApp.facebookclient->m_sId = m_sFb_id;
        theApp.facebookclient->setName(m_sFb_name);
        theApp.facebookclient->setFound(m_nExp);
        theApp.notificationclient->setLoginFlag(QString("%1").arg(m_nLoginStatus));
        return true;
    }
    else
        return false;
}

int LocalDB::CreateFileFlow()
{
    QFile Fout("my.db.sqlite");
    if(Fout.exists())
    {
        qDebug()<< "my.db.sqlite file exist!";
    }

//    if( openDB() == true)
//    {
//        qDebug()<< "db is open";
//        if(Fout.exists())
//        {
//            qDebug()<< "my.db.sqlite file exist!";
//        }
//    }

    CreateUserTable();
//    closeDB();

//    if(Fout.exists())
//        qDebug()<< "my.db.sqlite file exist!";
//    else
//        qDebug()<< "my.db.sqlite is deleted!";

    return true;
}
