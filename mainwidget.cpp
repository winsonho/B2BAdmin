#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "dbhandler.h"
#include <QSqlQueryModel>
#include <QJsonDocument>
#include "version.h"

#include <QZXing.h>
#include <QMenu>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

    QString version = QString("v %1.%2").arg(MAJOR).arg(MINOR) ;
    //qInfo("\n\n%s\n\n", version.toLocal8Bit().data()) ;
    ui->version->setText(version);

#ifdef GLOBAL_SITE
    ui->lblServer->setText("Global Server");
#else
    ui->lblServer->setText("China Server");
#endif
    mBtnHidden = ui->btnHidden;
    mBtnHidden->setStyleSheet("QPushButton{background:transparent;border-width: 0px;font: 20px;}");
    mBtnHidden->setFlat(true);
    connect(mBtnHidden,SIGNAL(clicked()), this, SLOT(onHiddenClicked()));

    mTvChannel = ui->tvChannel ;
    connect(mTvChannel, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onChannelSelected(QModelIndex)));

    connect(ui->btnConnect, SIGNAL(clicked()), this, SLOT(onConnectClicked()));
    connect(ui->btnNewAccount, SIGNAL(clicked()), this, SLOT(onNewClicked()));

    // setup radio button
    mHostGroup = new QButtonGroup(this);
    mRbDev = ui->rbDev;
    mRbBeta = ui->rbBeta;
    mRbPR = ui->rbPR;

    mHostGroup->addButton(mRbDev, HOST::DEV);
    mHostGroup->addButton(mRbBeta, HOST::BETA);
    mHostGroup->addButton(mRbPR, HOST::PR);
    mRbDev->setChecked(true);
    m_Model = new QSqlQueryModel();
    mTvChannel->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(mTvChannel, SIGNAL(customContextMenuRequested(QPoint)), SLOT(customMenuRequested(QPoint)));

    mHiddenON = false;
    mClickCount = 0 ;
}

MainWidget::~MainWidget()
{
    delete ui;
    DBHandler::closeDB();
    deleteLater();
}

void MainWidget::customMenuRequested(QPoint pos){
    QModelIndex index = mTvChannel->indexAt(pos);

    if (index.isValid() && mHiddenON)
    {
        QMenu *menu=new QMenu(this);
        menu->addAction("Delete", this, SLOT(onDelete()));
        menu->popup(mTvChannel->viewport()->mapToGlobal(pos));
    }
}

void MainWidget::onHiddenClicked()
{
    if (mHiddenON)
        return;

    if (mClickCount == 0)
    {
        mStartTime.restart() ;
        ++mClickCount;
    }
    else
    {
        if (!mStartTime.hasExpired(5000))
        {
            ++mClickCount;
            if (mClickCount > 10)
            {
                QMessageBox::information(NULL, "information", "You are admin now!!!!", QMessageBox::Ok);
                mHiddenON = true;
                mClickCount = 0;
            }
        }
        else
        {
            mClickCount = 0;
        }
    }
}

void MainWidget::onConnectClicked()
{   
    DBHandler::connectDB((HOST)mHostGroup->checkedId());

    m_Model->setQuery("SELECT brand_name, profile_name, accounts, syschannelprofiles_id, json_value, activation_status, language_code FROM client_channel_info", DBHandler::getDBHandler());
    m_Model->setHeaderData(0, Qt::Horizontal, "Brand");
    m_Model->setHeaderData(1, Qt::Horizontal, "ChannelName");
    m_Model->setHeaderData(2, Qt::Horizontal, "User Names");
    m_Model->setHeaderData(3, Qt::Horizontal, "Profile ID");

    mTvChannel->setModel(m_Model);
    mTvChannel->setColumnWidth(0, 100);
    mTvChannel->setColumnWidth(1, 200);
    mTvChannel->setColumnWidth(2, 250);
    mTvChannel->setColumnWidth(3, 300);
    mTvChannel->setColumnHidden(4, true);
    mTvChannel->setColumnHidden(5, true);
    mTvChannel->setColumnHidden(6, true);
    mTvChannel->setWordWrap(true);
    mTvChannel->resizeRowsToContents();
//    mTvChannel->resizeColumnsToContents();

}

void MainWidget::onNewClicked()
{
    qDebug() << "onNewClicked()";
    mNewView.show();
}

void MainWidget::onChannelSelected(QModelIndex index)
{
    m_Model->setQuery("SELECT brand_name, profile_name, accounts, syschannelprofiles_id, json_value, activation_status, language_code FROM client_channel_info", DBHandler::getDBHandler());

    QJsonParseError e;
    QString id = mTvChannel->model()->data(mTvChannel->model()->index(index.row(), 3), Qt::DisplayRole).toString();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(mTvChannel->model()->data(mTvChannel->model()->index(index.row(), 4) , Qt::DisplayRole).toByteArray(), &e);
    QString profile_name = mTvChannel->model()->data(mTvChannel->model()->index(index.row(), 1), Qt::DisplayRole).toString();

    if(e.error == QJsonParseError::NoError && !jsonDoc.isNull())
    {
        ChannelProfile* profile = new ChannelProfile() ;
        profile->setConfig(jsonDoc, id, profile_name);
        profile->show();
    }
    else
    {
        qCritical() << e.errorString();
    }
}

void MainWidget::onDelete()
{
    QModelIndex index = mTvChannel->currentIndex();
    QString id = mTvChannel->model()->data(mTvChannel->model()->index(index.row(), 3), Qt::DisplayRole).toString();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Warning", "Do you really want to delete it?\nMake sure the site is correct and the account is correct!!",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QString host;
        switch(mHostGroup->checkedId()){
            case 0:
                host = "DEV";
                break;
            case 1:
                host = "QA";
                break;
            case 2:
                host = "PR";
                break;
        }

        QString account = mTvChannel->model()->data(mTvChannel->model()->index(index.row(), 1), Qt::DisplayRole).toString();
        QString str = QString("Deleting channle: [%1] in [%2] site.\nPlease confirm it. You CAN NOT revert the deletion!!!").arg(account).arg(host);

        QMessageBox::StandardButton reply;

        reply = QMessageBox::question(this, "Warning", str,
                                    QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            if (deleteRecord(id, account))
            {
                QString str = QString("Channel account : %1 in %2 site deleted!!").arg(account).arg(host);
                QMessageBox::information(NULL, "Information", str, QMessageBox::Ok);
                onConnectClicked();
            }
        }
    }
}

bool MainWidget::deleteRecord(QString id, QString account)
{
    QSqlQuery q(DBHandler::getDBHandler());

    QString queryStr;

    // check skin analysis record
    queryStr = QString("SELECT count(*) FROM usr_skinanalysis WHERE syschannelprofiles_id = '%1'").arg(id);
    q.exec(queryStr);
    if (q.next())
    {
        int cnt = q.value(0).toInt();
        if (cnt != 0)
        {
            QString str = QString("Account: %1 skin analysis count: %2 > 0").arg(account).arg(cnt);
            showErrorDialog(str);
            return false;
        }
    }
    else
    {
        showErrorDialog(q.lastError().text());
        return false;
    }

    // check hiskin record
    queryStr = QString("SELECT count(*) FROM usr_hiskin WHERE syschannelprofiles_id = '%1'").arg(id);
    q.exec(queryStr);
    if (q.next())
    {
        int cnt = q.value(0).toInt();
        if (cnt != 0)
        {
            QString str = QString("Account: %1 HiSkin count: %2 > 0").arg(account).arg(cnt);
            showErrorDialog(str);
            return false;
        }
    }
    else
    {
        showErrorDialog(q.lastError().text());
        return false;
    }

    // delete legal
    queryStr = QString("DELETE FROM usr_channel_legal WHERE syschannelprofiles_id = '%1'").arg(id);
    qDebug() << "delete legal : " << queryStr;
    if (!q.exec(queryStr))
    {
        showErrorDialog(q.lastError().text());
        return false;
    }

    // delete usr_channel_product_concerns_list
    queryStr = QString("DELETE FROM usr_channel_product_concerns_list WHERE syschannelprofiles_id = '%1'").arg(id);
    qDebug() << "delete usr_channel_product_concerns_list : " << queryStr;
    if (!q.exec(queryStr))
    {
        showErrorDialog(q.lastError().text());
        return false;
    }

    // delete usr_channel_profile_settings
    queryStr = QString("DELETE FROM usr_channel_profile_settings WHERE syschannelprofiles_id = '%1'").arg(id);
    qDebug() << "delete usr_channel_profile_settings : " << queryStr;
    if (!q.exec(queryStr))
    {
        showErrorDialog(q.lastError().text());
        return false;
    }

    // delete sys_channel_users
    queryStr = QString("DELETE FROM sys_channel_users WHERE syschannelprofiles_id = '%1'").arg(id);
    qDebug() << "delete sys_channel_users : " << queryStr;
    if (!q.exec(queryStr))
    {
        showErrorDialog(q.lastError().text());
        return false;
    }

    // delete sys_channel_profiles
    queryStr = QString("DELETE FROM sys_channel_profiles WHERE id = '%1'").arg(id);
    qDebug() << "delete sys_channel_profiles : " << queryStr;
    if (!q.exec(queryStr))
    {
        showErrorDialog(q.lastError().text());
        return false;
    }

    return true;
}

void MainWidget::showErrorDialog(QString str)
{
    QMessageBox::critical(NULL, "cirtical", str, QMessageBox::Ok);
}
