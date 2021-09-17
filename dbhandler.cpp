#include "dbhandler.h"
#include <QSqlError>
#include <QSqlQuery>

DBSettings gChinaDevSetting = DBSettings("40.73.117.59", "himirror_b2b_api_dev", "tool_user", "Pw20190619");
DBSettings gChinaBetaSetting = DBSettings("40.73.117.59", "himirror_b2b_api_beta", "tool_user", "Pw20190619");
DBSettings gChinaPRSetting = DBSettings("40.73.108.191", "himirror_b2b_api", "tool_user", "Pw20190619");

DBSettings gGlobalDevSetting = DBSettings("himirrorapidb.mysql.database.azure.com", "himirror_b2b_api_dev", "tool_user@himirrorapidb", "Pw20190619");
DBSettings gGlobalBetaSetting = DBSettings("himirrorapidb.mysql.database.azure.com", "himirror_b2b_api_beta", "tool_user@himirrorapidb", "Pw20190619");
DBSettings gGlobalPRSetting = DBSettings("20.189.76.97", "himirror_b2b_api", "tool_user", "Pw20190619");

#ifndef GLOBAL_SITE
    DBSettings gDBSettings[HOST::HOSTCOUNT] = {gChinaDevSetting, gChinaBetaSetting, gChinaPRSetting};
#else
    DBSettings gDBSettings[HOST::HOSTCOUNT] = {gGlobalDevSetting, gGlobalBetaSetting, gGlobalPRSetting};
#endif

//DBHandler::DBHandler()
//{
//    mDBDev = QSqlDatabase::addDatabase("QMYSQL");
//}

QSqlDatabase DBHandler::mDB;
HOST DBHandler::mCurrentHost = HOSTCOUNT;

QString ConnectionName = QString::fromLatin1("HiMirrorB2B");

QSqlDatabase& DBHandler::getDBHandler()
{
    connectDB(mCurrentHost);
    return mDB;
}

bool DBHandler::connectDB(HOST host)
{
    bool ret = false;

    if (host != mCurrentHost)
    {
        closeDB();
    }
    else
    {
        if (mDB.isOpen())
            return true;
    }

    if (!QSqlDatabase::contains(ConnectionName))
    {
        mDB = QSqlDatabase::addDatabase("QMYSQL", ConnectionName);
    }
    else
    {
        mDB = QSqlDatabase::database(ConnectionName);
    }

    mDB.setHostName(gDBSettings[host].mHost);
    mDB.setUserName(gDBSettings[host].mUserName);
    mDB.setPassword(gDBSettings[host].mPassword);
    mDB.setDatabaseName(gDBSettings[host].mDBName);
    ret = mDB.open();

    if (!ret)
    {
        qCritical() << mDB.lastError();
    }
    else
    {
        mCurrentHost = host;
        qDebug() << mDB.databaseName() << " DB connection success!";
    }

    return ret;

}

void DBHandler::closeDB()
{
    qDebug() << "Close DB";

    if (mDB.isOpen())
        mDB.close();
    QSqlDatabase::removeDatabase(ConnectionName);
}

