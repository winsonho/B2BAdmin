#ifndef DBHANDLER_H
#define DBHANDLER_H
#include <QSqlDatabase>
#include "common.h"

class DBSettings {
friend class DBHandler;
public:
    DBSettings(QString host, QString dbName, QString username, QString password)
    {
        mHost = host;
        mDBName = dbName;
        mUserName = username;
        mPassword = password;
    }

private:
    QString mHost;
    QString mDBName;
    QString mUserName;
    QString mPassword;

};

class DBHandler
{

public:
    static QSqlDatabase& getDBHandler() ;
    static bool connectDB(HOST host);
    static void closeDB();

private:
    static QSqlDatabase mDB;
    static HOST mCurrentHost;

};

#endif // DBHANDLER_H
