#ifndef NEWACCOUNTWIDGET_H
#define NEWACCOUNTWIDGET_H

#include "common.h"
#include <QWidget>
#include <QButtonGroup>
#include <QRadioButton>
#include <QModelIndex>
#include <QTableView>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QComboBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include "qrcodewidget.h"

namespace Ui {
class NewAccountWidget;
}

class NewAccountWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NewAccountWidget(QWidget *parent = nullptr);
    ~NewAccountWidget();

private slots:
    void onHostClicked(int idx);
    void onCreateClicked();
    void onConvertClicked();
    void replyFinished(QNetworkReply *reply);

protected:
    bool eventFilter(QObject *object, QEvent *event);

private:
    bool checkData();
    void showErrorDialog(QString str);
    bool createAccount();
    bool getHash();

private:
    Ui::NewAccountWidget *ui;
    QSqlQueryModel *m_BrandModel;
    QSqlQueryModel *m_ProfileModel;
    QButtonGroup *mHostGroup;
    QRadioButton *mRbDev;
    QRadioButton *mRbBeta;
    QRadioButton *mRbPR;
    QComboBox* mBrand;
    QComboBox* mProfile;
    QPlainTextEdit* mChannelName;
    QPlainTextEdit* mChannelCode;
    QPlainTextEdit* mUserName;
    QPlainTextEdit* mPassword;
    QPlainTextEdit* mHash;
    QPushButton* mCreate;
    QPushButton* mConvert;
    QNetworkAccessManager *manager;
    QRCodeWidget mQRCodeView;
};

#endif // NEWACCOUNTWIDGET_H
