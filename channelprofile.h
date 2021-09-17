#ifndef CHANNELPROFILE_H
#define CHANNELPROFILE_H

#include <QWidget>
#include "common.h"
#include <QWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QJsonDocument>
#include <QHash>
#include <QPushButton>
#include <QTableWidget>
#include <QStandardItemModel>

namespace Ui {
class ChannelProfile;
}

class ChannelProfile : public QWidget
{
    Q_OBJECT

public:
    explicit ChannelProfile(QWidget *parent = nullptr);
    ~ChannelProfile();
    void setConfig(QJsonDocument doc, QString id, QString profile_name);

private:
    void initView();
    void initCommonTab();
    void initSkinTab();
    void initHiSkinTab();
    void initSBSTab();
    void initNewsTab();
    void initAppTab();

    void setView(QJsonDocument doc);
    void setCommonTab();
    void setSkinTab();
    void setHiSkinTab();
    void setSBSTab();
    void setNewsTab();
    void setAppTab();

    QJsonDocument getDefaultSettings();
    bool checkFactors();
    bool checkCommon();
    bool checkSkin();
    bool checkHiSkin();
    bool checkSBS();
    bool checkNews();
    bool checkApp();

    int getSkinFactorIndex(QString factor);
    int getHiSkinFactorIndex(QString factor);
    int getSBSFactorIndex(QString factor);
    int getLoginTypeIndex(QString factor);
    int getLanguageIndex(QString factor);
    bool updateConfig(QJsonDocument doc);

    void buttonClickHandle(int count);

private slots:
    void onResetClicked(bool);
    void onSaveClicked(bool);
    void onSkinFactorClicked(bool);
    void onLanguageClicked(bool);
    void onLoginTypeClicked(bool);
    void onHiSkinFactorClicked(bool);
    void onSBSFactorClicked(bool);
    void onNewsAddClicked(bool);
    void onNewsDeleteClicked(bool);
    void onAppAddClicked(bool);
    void onAppDeleteClicked(bool);
    void onHiSkinChecked(bool checked);
    void onSBSChecked(bool checked);
    void onNewsChecked(bool checked);
    void onAppChecked(bool checked);
    void showErrorDialog(QString str);

private:
    Ui::ChannelProfile *ui;
    QTabWidget* m_twMain;
    // common
    QComboBox* m_cbLanguage;
    QCheckBox* m_chkHiSkin;
    QCheckBox* m_chkProduct;
    QCheckBox* m_chkSBS;
    QCheckBox* m_chkNews;
    QCheckBox* m_chkApp;
    QCheckBox* m_chkBeautyBox;
    QCheckBox* m_chkAlexa;
    QLineEdit* m_txtRegion;
    QLineEdit* m_txtRegUrl;
    QLineEdit* m_txtForgetUrl;
    QPushButton* m_btnLanguage[LANGUAGESCOUNT];
    QHash<int, QString> m_LanguageList;
    QPushButton* m_btnMemberLogin[LOGINTYPESCOUNT];
    QHash<int, QString> m_LoginTypeList;
    QLineEdit* m_txtSalesEmail;


    // Skin Analysis
    QCheckBox* m_chkSkinAge;
    QCheckBox* m_chkUploadImage;
    QCheckBox* m_chkUploadImageUserDecide;
    QCheckBox* m_chkLevelBar;
    QCheckBox* m_chkSkinScanner;

    QRadioButton* m_rbSkinPercentage;
    QRadioButton* m_rbSkinRawScore;
    QPushButton* m_btnFactor[FACTORSCOUNT];

    QHash<int, QString> m_SkinFactorList;
    QButtonGroup* m_groupSkinScore;

    QCheckBox* m_chkSkinLastUser;
    QCheckBox* m_chkSkinNecessary;
    QCheckBox* m_chkSkinPhone;
    QCheckBox* m_chkSkinKey;
    QCheckBox* m_chkSkinEmail;
    QCheckBox* m_chkSkinName;

    QComboBox* m_cbSkinPrivacy;
    QComboBox* m_cbSkinTOU;
    QComboBox* m_cbSkinFlowType;

    QCheckBox* m_chkSkinReport;
    //QComboBox* m_cbSkinReportType;
    QCheckBox* m_chkSkinReportTypeQRcode;
    QCheckBox* m_chkSkinReportTypeEmail;
//    QCheckBox* m_chkSkinMemberAuth;
//    QCheckBox* m_chkSkinMemberProfile;
    QCheckBox* m_chkShowManual;
    QCheckBox* m_chkManualMode;
    QLineEdit* m_txtCountdown;


    // HiSkin
    QCheckBox* m_chkHiSkinScanner;
    QRadioButton* m_rbHiSkinPercentage;
    QRadioButton* m_rbHiSkinRawScore;
    QPushButton* m_btnHiSkinFactor[HISKINFACTORSCOUNT];

    QHash<int, QString> m_HiSkinFactorList;
    QButtonGroup* m_groupHiSkinScore;

    QCheckBox* m_chkHiSkinLastUser;
    QCheckBox* m_chkHiSkinNecessary;
    QCheckBox* m_chkHiSkinPhone;
    QCheckBox* m_chkHiSkinKey;
    QCheckBox* m_chkHiSkinEmail;
    QCheckBox* m_chkHiSkinName;

    QComboBox* m_cbHiSkinPrivacy;
    QComboBox* m_cbHiSkinTOU;

    QCheckBox* m_chkHiSkinReport;
    //QComboBox* m_cbHiSkinReportType;
    QCheckBox* m_chkHiSkinReportTypeQRcode;
    QCheckBox* m_chkHiSkinReportTypeEmail;
//    QCheckBox* m_chkHiSkinMemberAuth;
//    QCheckBox* m_chkHiSkinMemberProfile;

    // SBS
    QCheckBox* m_chkSBSScanner;
//    QRadioButton* m_rbSBSPercentage;
//    QRadioButton* m_rbSBSRawScore;
    QPushButton* m_btnSBSFactor[SBSFACTORSCOUNT];

    QHash<int, QString> m_SBSFactorList;
//    QButtonGroup* m_groupSBSScore;

    QCheckBox* m_chkSBSLastUser;
    QCheckBox* m_chkSBSNecessary;
    QCheckBox* m_chkSBSPhone;
    QCheckBox* m_chkSBSKey;
    QCheckBox* m_chkSBSEmail;
    QCheckBox* m_chkSBSName;

    QComboBox* m_cbSBSPrivacy;
    QComboBox* m_cbSBSTOU;

    QCheckBox* m_chkSBSReport;
    //QComboBox* m_cbSBSReportType;
    QCheckBox* m_chkSBSReportTypeQRcode;
    QCheckBox* m_chkSBSReportTypeEmail;
//    QCheckBox* m_chkSBSMemberAuth;
//    QCheckBox* m_chkSBSMemberProfile;

    // NEWS
    QPushButton* m_btnNewsAdd;
    QPushButton* m_btnNewsDelete;
    QTableWidget* m_tvNews;

    // 3rd party
    QPushButton* m_btnAppAdd;
    QPushButton* m_btnAppDelete;
    QTableWidget* m_tvApp;

    QPushButton* m_btnSave;
    QPushButton* m_btnReset;

    QJsonDocument m_doc;
    QString m_id;
    QString m_profile_name;
    QJsonDocument m_defaultSetting;

};

#endif // CHANNELPROFILE_H
