#include "localdb.h"
#include "runningpaw.h"
#include <QVector>
#include <QVariant>

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
            .append(rp_user_col_index.at(id_rp_user_login_status)).append(" integer ").append(");");

    query.exec( statement );

    return true;
}

int LocalDB::InsertUser(QString fb_id, QString fb_name, int Exp, int LoginStatus)
{
    QSqlQuery query;

    QString statement;

    statement.append("INSERT INTO ").append(USER_TABLE).append("(")
            .append(rp_user_col_index.at(id_rp_user_fb_id)).append(", ")
            .append(rp_user_col_index.at(id_rp_user_fb_name)).append(", ")
            .append(rp_user_col_index.at(id_rp_user_exp)).append(", ")
            .append(rp_user_col_index.at(id_rp_user_login_status)).append(" VALUES(")
            .append("\'").append(fb_id).append("\', ")
            .append("\'").append(fb_name).append("\', ")
            .append(Exp).append(", ")
            .append(LoginStatus).append(");");

    query.exec(statement);

    return true;
}

int LocalDB::CheckIfUserLogin()
{
    QString statement;
    statement.append("Select * From ").append(USER_TABLE).append(" where ")
            .append(rp_user_col_index.at(4)).append(" = 1;");

    QSqlQuery query(statement);
    QSqlRecord rec = query.record();

    while (query.next())
    {
        m_sFb_id = query.value( rec.indexOf(rp_user_col_index.at(id_rp_user_fb_id)) ).toString();
        m_sFb_name = query.value( rec.indexOf(rp_user_col_index.at(id_rp_user_fb_name)) ).toString();
        m_nExp = query.value( rec.indexOf(rp_user_col_index.at(id_rp_user_exp)) ).toInt();
        m_nLoginStatus = query.value( rec.indexOf(rp_user_col_index.at(id_rp_user_login_status)) ).toInt();
    }

    if( m_sFb_id != 0)
        return true;
    else
        return false;
}
