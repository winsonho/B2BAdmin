#include "newaccountwidget.h"
#include "ui_newaccountwidget.h"
#include "dbhandler.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QZXing.h>
#include <QJsonDocument>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonObject>
#include <QDesktopServices>

QString profileID = nullptr;

NewAccountWidget::NewAccountWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewAccountWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
#ifdef GLOBAL_SITE
    ui->lblServer->setText("Global Server");
#else
    ui->lblServer->setText("China Server");
#endif
    m_BrandModel = new QSqlQueryModel();
    m_ProfileModel = new QSqlQueryModel();

    mBrand = ui->cbBrand;
    mChannelName = ui->txtChannelName;
    mChannelCode = ui->txtChannelCode;
    mUserName = ui->txtUserName;
    mPassword = ui->txtPassword;
    mHash = ui->txtHash;
    mProfile = ui->cbProfile;
    mCreate = ui->btnCreate;
    mConvert = ui->btnConvert;

    // setup radio button
    mHostGroup = new QButtonGroup(this);
    mRbDev = ui->rbDev;
    mRbBeta = ui->rbBeta;
    mRbPR = ui->rbPR;

    mHostGroup->addButton(mRbDev, HOST::DEV);
    mHostGroup->addButton(mRbBeta, HOST::BETA);
    mHostGroup->addButton(mRbPR, HOST::PR);
    mRbDev->setChecked(true);
    mPassword->installEventFilter(this);

    connect(mHostGroup, SIGNAL(buttonClicked(int)), this, SLOT(onHostClicked(int)));
    connect(mCreate, SIGNAL(clicked()), this, SLOT(onCreateClicked()));
    connect(mConvert, SIGNAL(clicked()), this, SLOT(onConvertClicked()));

    // setup network manager
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    mQRCodeView.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    onHostClicked(0);
}

NewAccountWidget::~NewAccountWidget()
{
    delete ui;
}

bool NewAccountWidget::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == event->FocusOut && object == mPassword)
    {
        getHash();
    }

    return false;
}

void NewAccountWidget::onHostClicked(int idx)
{
    qDebug() << "onHostClicked() : " << idx;

    DBHandler::connectDB((HOST)idx);
    m_BrandModel->setQuery("select name from sys_channel_brand", DBHandler::getDBHandler());
    mBrand->setModel(m_BrandModel);

    //m_ProfileModel->setQuery("select name, id from sys_channel_profiles", DBHandler::getDBHandler());
    m_ProfileModel->setQuery("select name from sys_channel_profiles", DBHandler::getDBHandler());
    mProfile->setModel(m_ProfileModel);
}

void NewAccountWidget::onCreateClicked()
{
    if (!checkData())
    {
        return;
    }

    // create account
    if (createAccount())
    {
        QString str = "Account: " + mUserName->toPlainText() + " created!!";
        QMessageBox::information(NULL, "information", str, QMessageBox::Ok);

        QString data = QString("channel_code=%1/username=%2/password=%3").arg(mChannelCode->toPlainText()).arg(mUserName->toPlainText()).arg(mPassword->toPlainText());
        qDebug() << data;
        QImage barcode = QZXing::encodeData(data);

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

        QString title = QString("%1-%2").arg(mUserName->toPlainText()).arg(host);
        mQRCodeView.setDescription(title);
        mQRCodeView.setImage(barcode);
        mQRCodeView.show();
        close();
    }
}

void NewAccountWidget::onConvertClicked()
{
    QDesktopServices::openUrl(QUrl("https://www.browserling.com/tools/bcrypt"));
}

bool NewAccountWidget::checkData()
{
    bool ret = true;
    if (mBrand->currentText().isEmpty())
    {
        showErrorDialog("Brand name can't be empty");
        ret = false;
    }

    if (mChannelName->toPlainText().isEmpty())
    {
        showErrorDialog("Channel name can't be empty");
        ret = false;
    }

    if (mChannelCode->toPlainText().isEmpty())
    {
        showErrorDialog("Channel code can't be empty");
        ret = false;
    }

    if (mUserName->toPlainText().isEmpty())
    {
        showErrorDialog("User name can't be empty");
        ret = false;
    }

    if (mPassword->toPlainText().isEmpty())
    {
        showErrorDialog("Password can't be empty");
        ret = false;
    }

    if (mHash->toPlainText().isEmpty())
    {
        showErrorDialog("Hash still empty, wait for Bcrypt API to return or manually convert on web!");
        ret = false;
    }

    if (mProfile->currentText().isEmpty())
    {
        showErrorDialog("Profile can't be empty");
        ret = false;
    }

    // check account exist or not.

    //DBHandler::closeDB();
    QSqlQuery q(DBHandler::getDBHandler());

    QString queryStr;
    queryStr = QString("SELECT count(account) FROM sys_channel_users WHERE account = '%1'").arg(mUserName->toPlainText());
    qDebug() << "check user account exist or not id : " << queryStr;
    q.exec(queryStr);
    if (q.next())
    {
        if (q.value(0).toInt() != 0)
        {
            showErrorDialog("Account alreay exist!!");
            mUserName->setFocus();
            ret = false;
        }
    }

//    queryStr = QString("SELECT count(*) FROM sys_channel_profiles WHERE `name` = '%1' and `code` = '%2'").arg(mChannelName->toPlainText()).arg(mChannelCode->toPlainText());
//    q.exec(queryStr);
//    if (q.next())
//    {
//        if (q.value(0).toInt() != 0)
//        {
//            showErrorDialog("channel name and code alreay exist!!");
//            mChannelName->setFocus();
//            ret = false;
//        }
//    }

    queryStr = QString("select id from sys_channel_profiles WHERE name = '%1'").arg(mProfile->currentText());
    qDebug() << "get profileID id : " << queryStr;
    q.exec(queryStr);
    if (q.next())
    {
        profileID = q.value(0).toString();
        qDebug() << profileID;
    }
    else
    {
        showErrorDialog("Reference channel profile not exist!!");
        ret = false;
    }

    //profileID = mProfile->model()->data(mProfile->model()->index(mProfile->currentIndex(), 1), Qt::DisplayRole).toString();
    return ret;
}

void NewAccountWidget::showErrorDialog(QString str)
{
    QMessageBox::critical(NULL, "cirtical", str, QMessageBox::Ok);
}

bool NewAccountWidget::createAccount()
{
    bool ret = true;
    //DBHandler::closeDB();
    QSqlQuery q(DBHandler::getDBHandler());

    QString queryStr;

    // insert brand name
    queryStr = QString("INSERT IGNORE INTO sys_channel_brand (`name`) VALUES ('%1')").arg(mBrand->currentText());
    qDebug() << "insert brand name : " << queryStr;
    if (!q.exec(queryStr))
    {
        showErrorDialog(q.lastError().text());
        ret = false;
    }

    // Get Brand id
    QString brandID;

    queryStr = QString("SELECT id FROM sys_channel_brand WHERE name = '%1'").arg(mBrand->currentText());
    qDebug() << "get barnd id : " << queryStr;
    q.exec(queryStr);
    if (q.next())
    {
        brandID = q.value(0).toString();
        qDebug() << brandID;
    }
    else
    {
        showErrorDialog(q.lastError().text());
        ret = false;
    }

    // insert profile
    queryStr = QString("INSERT IGNORE INTO sys_channel_profiles (`syschannelbrand_id`, `name`, `code`, `expired_date`) VALUES ('%1', '%2', '%3', '2100-01-01 07:59:59')").arg(brandID).arg(mChannelName->toPlainText()).arg(mChannelCode->toPlainText());
    qDebug() << " insert profile : " << queryStr;
    if (!q.exec(queryStr))
    {
        showErrorDialog("insert sys_channel_profiles error: " + q.lastError().text());
        ret = false;
    }


    // get channel id
    QString channelID;
    queryStr = QString("SELECT id FROM sys_channel_profiles WHERE name = '%1'").arg(mChannelName->toPlainText());
    qDebug() << " get profile id : " << queryStr;
    q.exec(queryStr);
    if (q.next())
    {
        channelID = q.value(0).toString();
        qDebug() << channelID;
    }
    else
    {
        showErrorDialog(q.lastError().text());
        ret = false;
    }

    // insert channel user
    queryStr = QString("INSERT INTO sys_channel_users (`account`, `password`, `syschannelprofiles_id`) "
                       "VALUES ('%1', '%2', '%3')").arg(mUserName->toPlainText()).arg(mHash->toPlainText()).arg(channelID);
    qDebug() << "insert channel user : " << queryStr;
    if (!q.exec(queryStr))
    {
        showErrorDialog("insert sys_channel_users error: " +q.lastError().text());
        ret = false;
    }

//    // get reference channel profile id
//    // Get profile id
//    QString profileID;

//    queryStr = QString("select id from sys_channel_profiles WHERE name = '%1'").arg(mProfile->currentText());
//    qDebug() << "get profileID id : " << queryStr;
//    q.exec(queryStr);
//    if (q.next())
//    {
//        profileID = q.value(0).toString();
//        qDebug() << profileID;
//    }
//    else
//    {
//        showErrorDialog(q.lastError().text());
//        ret = false;
//    }

    // insert channel profile
//    QString profileID = mProfile->model()->data(mProfile->model()->index(mProfile->currentIndex(), 1), Qt::DisplayRole).toString();
    qDebug() << "profile id: " << profileID;
    queryStr = QString("INSERT IGNORE INTO usr_channel_profile_settings(syschannelprofiles_id, verison, json_value) "
                       "SELECT '%1', verison, json_value FROM usr_channel_profile_settings WHERE syschannelprofiles_id = '%2'").arg(channelID).arg(profileID);
    qDebug() << "insert channel profile : " << queryStr;
    if (!q.exec(queryStr))
    {
        showErrorDialog("insert usr_channel_profile_settings error: " + q.lastError().text());
        ret = false;
    }

    // update and sync channel profile
    queryStr = QString("UPDATE usr_channel_profile_settings SET update_time = NOW() WHERE syschannelprofiles_id = '%1'").arg(channelID);
    qDebug() << "update and sync channel profile : " << queryStr;
    if (!q.exec(queryStr))
    {
        showErrorDialog(q.lastError().text());
        ret = false;
    }

    QString data = "text to be encoded";
    QImage barcode = QZXing::encodeData(data);

    return ret;

}

bool NewAccountWidget::getHash()
{
    qDebug() << "getHash";

    QUrl serviceUrl = QUrl("https://bcrypt.org/api/generate-hash.json");
    QUrlQuery postData;
    postData.addQueryItem("password", mPassword->toPlainText());
    postData.addQueryItem("cost","10");

    QNetworkRequest networkRequest(serviceUrl);

    manager->post(networkRequest, postData.toString(QUrl::FullyEncoded).toUtf8());
    return true;
}

void NewAccountWidget::replyFinished(QNetworkReply *reply)
{
    QByteArray response_data = reply->readAll();
    QJsonDocument json = QJsonDocument::fromJson(response_data);
    qDebug() << json;
    QJsonObject rootObj = json.object();
    mHash->setPlainText(rootObj["hash"].toString());
    reply->deleteLater();
}
