#include "channelprofile.h"
#include "ui_channelprofile.h"
#include "dbhandler.h"
#include "jsonhandler.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include "dialogeditjson.h"

QString gFactorStirngs[FACTORSCOUNT] = {
                                            "blackspot",
                                            "darkcircle",
                                            "fine",
                                            "pore",
                                            "texture",
                                            "wrinkle",
                                            "acne",
                                            "skincolor",
                                            "intensity",
                                            "sensitivezone",
                                            "stainstage",
                                            "darkcirclegrayscale",
                                            "fourv"
                                        };

QString gHiSkinFactorStirngs[HISKINFACTORSCOUNT] = {
                                                        "hydration",
                                                        "pigmentation"
                                                    };

QString gSBSFactorStirngs[SBSFACTORSCOUNT] = {
                                                    "weight",
                                                    "bmi",
                                                    "bmr",
                                                    "bone_density",
                                                    "bwr",
                                                    "mmr",
                                                    "pdf",
                                                    "vf"
                                              };

QString gLanguageStirngs[LANGUAGESCOUNT] = {
                                                "en-us",
                                                "zh-tw",
                                                "zh-cn",
                                                "zh-hk",
                                                "th-th",
                                                "ms-my",
                                                "id-id",
                                                "ja-jp",
                                                "ko-kr",
                                                "ru-ru"
                                            };

QString gMemberLoginStirngs[LOGINTYPESCOUNT] = {
                                                    "memberEmailPwd",
                                                    "memberPhonePwd",
                                                    "memberXiaoMiPwd"
                                                };


QString gMemberIDTypeStirngs[MEMBERIDTYPECOUNT] = {
                                                    "memberIDPhone",
                                                    "memberIDKey",
                                                    "memberIDEmail",
                                                    "random"
                                                };

QString gShowTypeStrings[SHOWTYPESCOUNT] = {
                                                "once",
                                                "everytime",
                                                "no"
                                            };

QString gFlowTypeStrings[FLOWTYPESCOUNT] = {
                                                "standard",
                                                "bbyc"
                                            };

QString gReportTypeStrings[REPORTTYPESCOUNT] = {
                                                    "qrcode"
                                                    "email"
                                                };


QString gAccessLevelStrings[ACCESSLEVELSCOUNT] = {
                                                    "admin",
                                                    "standard",
                                                    "guest"
                                                    };

ChannelProfile::ChannelProfile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChannelProfile)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    initView();
}

ChannelProfile::~ChannelProfile()
{
    delete ui;
}

void ChannelProfile::setConfig(QJsonDocument doc, QString id, QString profile_name)
{
    qDebug() << doc;
    qDebug() << id;
    qDebug() << profile_name;

    m_doc = doc;
    m_id = id;
    m_profile_name = profile_name;

    setWindowTitle(profile_name);
    setView(m_doc);
}

void ChannelProfile::initView()
{

    m_twMain = ui->tabWidget;

    initCommonTab();
    initSkinTab();
    initHiSkinTab();
    initSBSTab();
    initNewsTab();
    initAppTab();

    ui->tabWidget->setCurrentIndex(0);

    m_btnSave = ui->btnSave;
    connect(m_btnSave, SIGNAL(clicked(bool)), this, SLOT(onSaveClicked(bool)));

    m_btnReset = ui->btnReset;
    connect(m_btnReset, SIGNAL(clicked(bool)), this, SLOT(onResetClicked(bool)));

}

void ChannelProfile::initCommonTab()
{
    m_cbLanguage = ui->cbLanguage;

    m_chkHiSkin = ui->chkHiSkin;
    m_chkHiSkin->setChecked(false);
    m_chkProduct = ui->chkProduct;
    m_chkProduct->setChecked(false);
    m_chkSBS = ui->chkSBS;
    m_chkSBS->setChecked(false);

    m_chkNews = ui->chkNEWS;
    m_chkNews->setChecked(false);
    m_chkApp = ui->chkApp;
    m_chkApp->setChecked(false);
    m_chkBeautyBox = ui->chkBeautyBox;
    m_chkBeautyBox->setChecked(false);
    m_chkAlexa = ui->chkAlexa;
    m_chkAlexa->setChecked(false);
    m_txtRegion = ui->txtRegion;
    m_txtSalesEmail = ui->txtSalesEmail;
    m_txtRegUrl = ui->txtRegUrl;
    m_txtForgetUrl = ui->txtForgetUrl;


    // setup support language button
    m_btnLanguage[EN_US] = ui->btnEnUS;
    m_btnLanguage[ZH_TW] = ui->btnZhTW;
    m_btnLanguage[ZH_CN] = ui->btnZhCN;
    m_btnLanguage[ZH_HK] = ui->btnZhHK;
    m_btnLanguage[TH_TH] = ui->btnThTH;
    m_btnLanguage[MS_MY] = ui->btnMsMY;
    m_btnLanguage[ID_ID] = ui->btnIdID;
    m_btnLanguage[JA_JP] = ui->btnJaJP;
    m_btnLanguage[KO_KR] = ui->btnKoKR;
    m_btnLanguage[RU_RU] = ui->btnRuRU;

    for(int i=0; i<LANGUAGESCOUNT; i++)
    {
        m_cbLanguage->addItem(gLanguageStirngs[i]);
        connect(m_btnLanguage[i], SIGNAL(clicked(bool)), this, SLOT(onLanguageClicked(bool)));
    }

    // setup member login button
    m_btnMemberLogin[EMAIL] = ui->btnCommonEmail;
    m_btnMemberLogin[PHONE] = ui->btnCommonPhone;
    m_btnMemberLogin[XIAOMI] = ui->btnCommonXiaoMi;

    for(int i=0; i<LOGINTYPESCOUNT; i++)
    {
        connect(m_btnMemberLogin[i], SIGNAL(clicked(bool)), this, SLOT(onLoginTypeClicked(bool)));
    }

}

void ChannelProfile::initSkinTab()
{
    m_chkSkinAge = ui->chkSkinAge;
    m_chkSkinAge->setChecked(false);
    m_chkUploadImage = ui->chkUploadImage;
    m_chkUploadImage->setChecked(false);
    m_chkUploadImageUserDecide = ui->chkUploadImageUserDecide;
    m_chkUploadImageUserDecide->setChecked(false);
    m_chkLevelBar = ui->chkLevelBar;
    m_chkLevelBar->setChecked(false);
    m_chkSkinScanner = ui->chkSkinScanner;
    m_chkSkinScanner->setChecked(false);

    m_rbSkinPercentage = ui->rbSkinPercentage;
    m_rbSkinRawScore = ui->rbSkinRawCount;
    m_groupSkinScore = new QButtonGroup(this);
    m_groupSkinScore->addButton(m_rbSkinPercentage, 0);
    m_groupSkinScore->addButton(m_rbSkinRawScore, 1);
    m_rbSkinPercentage->setChecked(true);
    m_chkShowManual = ui->chkShowManual;
    m_chkShowManual->setChecked(false);
    m_chkManualMode = ui->chkManualMode;
    m_chkManualMode->setChecked(false);
    m_txtCountdown = ui->txtCountdown;
    m_txtCountdown->setValidator(new QRegExpValidator(QRegExp("[0-9]+")));
    m_txtCountdown->setText("0");

    m_chkSkinLastUser = ui->chkSkinLastUser;
    m_chkSkinLastUser->setChecked(false);
    m_chkSkinNecessary = ui->chkSkinNecessary;
    m_chkSkinNecessary->setChecked(false);
    m_chkSkinPhone = ui->chkSkinPhone;
    m_chkSkinPhone->setChecked(false);
    m_chkSkinKey = ui->chkSkinKey;
    m_chkSkinKey->setChecked(false);
    m_chkSkinEmail = ui->chkSkinEmail;
    m_chkSkinEmail->setChecked(false);
    m_chkSkinName = ui->chkSkinName;
    m_chkSkinName->setChecked(false);

    m_cbSkinPrivacy = ui->cbSkinPrivacy;
    m_cbSkinTOU = ui->cbSkinTOU;

    for(int i=0; i<SHOWTYPESCOUNT; i++)
    {
        m_cbSkinPrivacy->addItem(gShowTypeStrings[i]);
        m_cbSkinTOU->addItem(gShowTypeStrings[i]);
    }

    m_cbSkinFlowType = ui->cbSkinFlowType;
    for(int i=0; i<FLOWTYPESCOUNT; i++)
    {
        m_cbSkinFlowType->addItem(gFlowTypeStrings[i]);
    }

    m_chkSkinReport = ui->chkSkinReport;
    m_chkSkinReport->setChecked(false);
    m_chkSkinReportTypeQRcode = ui->chkSkinReportTypeQRcode;
    m_chkSkinReportTypeQRcode->setChecked(false);
    m_chkSkinReportTypeEmail = ui->chkSkinReportTypeEmail;
    m_chkSkinReportTypeEmail->setChecked(false);

//    m_cbSkinReportType = ui->cbSkinReportType;
//    for(int i=0; i<REPORTTYPESCOUNT; i++)
//    {
//        m_cbSkinReportType->addItem(gReportTypeStrings[i]);
//    }

//    m_chkSkinMemberAuth = ui->chkSkinMemberAuth;
//    m_chkSkinMemberAuth->setChecked(false);
//    m_chkSkinMemberProfile = ui->chkSkinMemberProfile;
//    m_chkSkinMemberProfile->setChecked(false);

    // setup factor buttons
    m_btnFactor[BLACKSPOT] = ui->btnBlackspot;
    m_btnFactor[DARKCIRCLE] = ui->btnDarkcircle;
    m_btnFactor[FINE] = ui->btnFine;
    m_btnFactor[PORE] = ui->btnPore;
    m_btnFactor[TEXTURE] = ui->btnTexture;
    m_btnFactor[WRINKLE] = ui->btnWrinkle;
    m_btnFactor[ACNE] = ui->btnAcne;
    m_btnFactor[SKINCOLOR] = ui->btnSkincolor;
    m_btnFactor[INTENSITY] = ui->btnIntensity;
    m_btnFactor[SENSITIVEZONE] = ui->btnSensitiveZone;
    m_btnFactor[STAINSTAGE] = ui->btnStainStage;
    m_btnFactor[DARKCIRCLEGRAYSCALE] = ui->btnDarkCircleGrayScale;
    m_btnFactor[FOURV] = ui->btnFourV;

    // connect factors signals
    for(int i=0 ; i<FACTORSCOUNT; i++)
    {
        connect(m_btnFactor[i], SIGNAL(clicked(bool)), this, SLOT(onSkinFactorClicked(bool)));
    }

}

void ChannelProfile::initHiSkinTab()
{
    m_rbHiSkinPercentage = ui->rbHiSkinPercentage;
    m_rbHiSkinRawScore = ui->rbHiSkinRawCount;
    m_groupHiSkinScore = new QButtonGroup(this);
    m_groupHiSkinScore->addButton(m_rbHiSkinPercentage, 0);
    m_groupHiSkinScore->addButton(m_rbHiSkinRawScore, 1);
    m_rbHiSkinPercentage->setChecked(true);
    m_chkHiSkinScanner = ui->chkHiSkinScanner;
    m_chkHiSkinScanner->setChecked(false);

    m_chkHiSkinLastUser = ui->chkHiSkinLastUser;
    m_chkHiSkinLastUser->setChecked(false);
    m_chkHiSkinNecessary = ui->chkHiSkinNecessary;
    m_chkHiSkinNecessary->setChecked(false);
    m_chkHiSkinPhone = ui->chkHiSkinPhone;
    m_chkHiSkinPhone->setChecked(false);
    m_chkHiSkinKey = ui->chkHiSkinKey;
    m_chkHiSkinKey->setChecked(false);
    m_chkHiSkinEmail = ui->chkHiSkinEmail;
    m_chkHiSkinEmail->setChecked(false);
    m_chkHiSkinName = ui->chkHiSkinName;
    m_chkHiSkinName->setChecked(false);

    m_cbHiSkinPrivacy = ui->cbHiSkinPrivacy;
    m_cbHiSkinTOU = ui->cbHiSkinTOU;
    for(int i=0; i<SHOWTYPESCOUNT; i++)
    {
        m_cbHiSkinPrivacy->addItem(gShowTypeStrings[i]);
        m_cbHiSkinTOU->addItem(gShowTypeStrings[i]);
    }

    m_chkHiSkinReport = ui->chkHiSkinReport;
    m_chkHiSkinReport->setChecked(false);
    m_chkHiSkinReportTypeQRcode = ui->chkHiSkinReportTypeQRcode;
    m_chkHiSkinReportTypeQRcode->setChecked(false);
    m_chkHiSkinReportTypeEmail = ui->chkHiSkinReportTypeEmail;
    m_chkHiSkinReportTypeEmail->setChecked(false);
//    m_cbHiSkinReportType = ui->cbHiSkinReportType;
//    for(int i=0; i<REPORTTYPESCOUNT; i++)
//    {
//        m_cbHiSkinReportType->addItem(gReportTypeStrings[i]);
//    }

//    m_chkHiSkinMemberAuth = ui->chkHiSkinMemberAuth;
//    m_chkHiSkinMemberAuth->setChecked(false);
//    m_chkHiSkinMemberProfile = ui->chkHiSkinMemberProfile;
//    m_chkHiSkinMemberProfile->setChecked(false);

    // setup factor buttons
    m_btnHiSkinFactor[HYDRATION] = ui->btnHydration;
    m_btnHiSkinFactor[PIGMENTATION] = ui->btnPigmentation;

    // connect factors signals
    for(int i=0 ; i<HISKINFACTORSCOUNT; i++)
    {
        connect(m_btnHiSkinFactor[i], SIGNAL(clicked(bool)), this, SLOT(onHiSkinFactorClicked(bool)));
    }
}

void ChannelProfile::initSBSTab()
{
//    m_rbSBSPercentage = ui->rbSBSPercentage;
//    m_rbSBSRawScore = ui->rbSBSRawCount;
//    m_groupSBSScore = new QButtonGroup(this);
//    m_groupSBSScore->addButton(m_rbSBSPercentage, 0);
//    m_groupSBSScore->addButton(m_rbSBSRawScore, 1);
//    m_rbSBSPercentage->setChecked(true);
    m_chkSBSScanner = ui->chkSBSScanner;
    m_chkSBSScanner->setChecked(false);

    m_chkSBSLastUser = ui->chkSBSLastUser;
    m_chkSBSLastUser->setChecked(false);
    m_chkSBSNecessary = ui->chkSBSNecessary;
    m_chkSBSNecessary->setChecked(false);
    m_chkSBSPhone = ui->chkSBSPhone;
    m_chkSBSPhone->setChecked(false);
    m_chkSBSKey = ui->chkSBSKey;
    m_chkSBSKey->setChecked(false);
    m_chkSBSEmail = ui->chkSBSEmail;
    m_chkSBSEmail->setChecked(false);
    m_chkSBSName = ui->chkSBSName;
    m_chkSBSName->setChecked(false);

    m_cbSBSPrivacy = ui->cbSBSPrivacy;
    m_cbSBSTOU = ui->cbSBSTOU;
    for(int i=0; i<SHOWTYPESCOUNT; i++)
    {
        m_cbSBSPrivacy->addItem(gShowTypeStrings[i]);
        m_cbSBSTOU->addItem(gShowTypeStrings[i]);
    }

    m_chkSBSReport = ui->chkSBSReport;
    m_chkSBSReportTypeQRcode = ui->chkSBSReportTypeQRcode;
    m_chkSBSReportTypeQRcode->setChecked(false);
    m_chkSBSReportTypeEmail = ui->chkSBSReportTypeEmail;
    m_chkSBSReportTypeEmail->setChecked(false);
//    m_cbSBSReportType = ui->cbSBSReportType;
//    for(int i=0; i<REPORTTYPESCOUNT; i++)
//    {
//        m_cbSBSReportType->addItem(gReportTypeStrings[i]);
//    }

//    m_chkSBSMemberAuth = ui->chkSBSMemberAuth;
//    m_chkSBSMemberAuth->setChecked(false);
//    m_chkSBSMemberProfile = ui->chkSBSMemberProfile;
//    m_chkSBSMemberProfile->setChecked(false);

    // setup factor buttons
    m_btnSBSFactor[WEIGHT] = ui->btnWeight;
    m_btnSBSFactor[BMI] = ui->btnBmi;
    m_btnSBSFactor[BMR] = ui->btnBmr;
    m_btnSBSFactor[BONE_DENSITY] = ui->btnBone_density;
    m_btnSBSFactor[BWR] = ui->btnBwr;
    m_btnSBSFactor[MMR] = ui->btnMmr;
    m_btnSBSFactor[PDF] = ui->btnPdf;
    m_btnSBSFactor[VF] = ui->btnVf;

    // connect factors signals
    for(int i=0 ; i<SBSFACTORSCOUNT; i++)
    {
        connect(m_btnSBSFactor[i], SIGNAL(clicked(bool)), this, SLOT(onSBSFactorClicked(bool)));
    }
}

void ChannelProfile::initNewsTab()
{
//    m_txtNewsUrl = ui->txtNewsUrl;
//    m_txtNewsName = ui->txtNewsName;
//    m_txtNewsType = ui->txtNewsType;
//    m_txtNewsSource = ui->txtNewsSource;
//    m_txtNewsLanguage = ui->txtNewsLanguage;
    m_btnNewsAdd = ui->btnNewsAdd;
    connect(m_btnNewsAdd, SIGNAL(clicked(bool)), this, SLOT(onNewsAddClicked(bool)));
    m_btnNewsDelete = ui->btnNewsDelete;
    connect(m_btnNewsDelete, SIGNAL(clicked(bool)), this, SLOT(onNewsDeleteClicked(bool)));
    m_tvNews = ui->tvNews;
}

void ChannelProfile::initAppTab()
{
//    m_txtAppName = ui->txtAppName;
//    m_txtAppIndex = ui->txtAppIndex;
//    m_chkAppEnable = ui->chkAppEnable;
//    m_txtAppPackage = ui->txtAppPackage;
    m_btnAppAdd = ui->btnAppAdd;
    connect(m_btnAppAdd, SIGNAL(clicked(bool)), this, SLOT(onAppAddClicked(bool)));
    m_btnAppDelete = ui->btnAppDelete;
    connect(m_btnAppDelete, SIGNAL(clicked(bool)), this, SLOT(onAppDeleteClicked(bool)));
    m_tvApp = ui->tvApp;
}

void ChannelProfile::setView(QJsonDocument doc)
{
    m_defaultSetting = getDefaultSettings();

    QJsonObject root = doc.object();
    JsonHandler::getInstance()->setDocDefault(m_defaultSetting);
    JsonHandler::getInstance()->setDoc(doc);

    setCommonTab();
    setSkinTab();
    setHiSkinTab();
    setSBSTab();
    setNewsTab();
    setAppTab();
}

void ChannelProfile::setCommonTab()
{
    QJsonObject objCommon = JsonHandler::getInstance()->getNode(JsonHandler::COMMON);

    // language
    int idx = m_cbLanguage->findText(objCommon["language"].toString());// JsonHandler::getInstance()->getLanguage());

    qDebug() << "combox language index = " << idx;

    if (idx != -1)
        m_cbLanguage->setCurrentIndex(idx);

    // hiskin
    m_chkHiSkin->setChecked(JsonHandler::getInstance()->isHiSkinEnabled());
    if (!m_chkHiSkin->isChecked())
        m_twMain->removeTab(m_twMain->indexOf(ui->tabHiSkin));
    connect(m_chkHiSkin, SIGNAL(clicked(bool)), this, SLOT(onHiSkinChecked(bool)));

    // product
    m_chkProduct->setChecked(JsonHandler::getInstance()->isProductEnabled());

    // sbs
    m_chkSBS->setChecked(JsonHandler::getInstance()->isSBSEnabled());
    if (!m_chkSBS->isChecked())
        m_twMain->removeTab(m_twMain->indexOf(ui->tabSBS));
    connect(m_chkSBS, SIGNAL(clicked(bool)), this, SLOT(onSBSChecked(bool)));

    // NEWS
    m_chkNews->setChecked(JsonHandler::getInstance()->isNewsEnabled());
    if (!m_chkNews->isChecked())
        m_twMain->removeTab(m_twMain->indexOf(ui->tabNews));
    connect(m_chkNews, SIGNAL(clicked(bool)), this, SLOT(onNewsChecked(bool)));

    // 3rd party
    m_chkApp->setChecked(JsonHandler::getInstance()->isAppsEnabled());
    connect(m_chkApp, SIGNAL(clicked(bool)), this, SLOT(onAppChecked(bool)));

    if (!m_chkApp->isChecked())
        m_twMain->removeTab(m_twMain->indexOf(ui->tabApp));

    // BeautyBox
    m_chkBeautyBox->setChecked(JsonHandler::getInstance()->isBeautyBoxEnabled());

    // Alexa
    m_chkAlexa->setChecked(JsonHandler::getInstance()->isAlexaEnabled());

    m_txtRegion->setText(objCommon["region"].toString());

    m_txtSalesEmail->setText(objCommon["sales_email"].toString());

    if (!objCommon["member_login"].toObject().isEmpty())
    {
        m_txtRegUrl->setText(objCommon["member_login"].toObject()["reg_url"].toString());
        m_txtForgetUrl->setText(objCommon["member_login"].toObject()["forget_password_url"].toString());

        QJsonArray factorArray = objCommon["member_login"].toObject()["login_type"].toArray();
        for (int i=0; i<factorArray.size(); i++)
        {
            m_LoginTypeList[i] = factorArray[i].toString();
            if (getLoginTypeIndex(m_LoginTypeList[i]) != -1)
                m_btnMemberLogin[getLoginTypeIndex(m_LoginTypeList[i])]->setText(QString("%1").arg(i+1));
        }
    }

    QJsonArray factorArray = objCommon["support_languages"].toArray();
    for (int i=0; i<factorArray.size(); i++)
    {
        m_LanguageList[i] = factorArray[i].toString();
        if (getLanguageIndex(m_LanguageList[i]) != -1)
            m_btnLanguage[getLanguageIndex(m_LanguageList[i])]->setText(QString("%1").arg(i+1));
    }

}

void ChannelProfile::setSkinTab()
{
    QJsonObject objSkin = JsonHandler::getInstance()->getNode(JsonHandler::SKINANALYSIS);

    m_chkSkinAge->setChecked(objSkin["skinage_is_enable"].toBool());
    m_chkUploadImage->setChecked(objSkin["upload_skinimage_is_enable"].toBool());
    m_chkUploadImageUserDecide->setChecked(objSkin["upload_skinimage_user_decide"].toBool());
    m_chkLevelBar->setChecked(objSkin["levelbar_is_enable"].toBool());

    // score type
    QString scoreType = objSkin["view_score_filter"].toObject()["all_scenario"].toObject()["type"].toString();
    if (scoreType == "rawscore")
    {
        m_rbSkinRawScore->setChecked(true);
    }
    else if (scoreType == "percentage")
    {
        m_rbSkinPercentage->setChecked(true);
    }

    QJsonArray factorArray = objSkin["detected_factor"].toArray();
    for (int i=0; i<factorArray.size(); i++)
    {
        m_SkinFactorList[i] = factorArray[i].toString();
        if (getSkinFactorIndex(m_SkinFactorList[i]) != -1)
            m_btnFactor[getSkinFactorIndex(m_SkinFactorList[i])]->setText(QString("%1").arg(i+1));
    }

    // take picture
    m_chkShowManual->setChecked(objSkin["take_picture"].toObject()["show_manual"].toBool());
    m_chkManualMode->setChecked(objSkin["take_picture"].toObject()["manual_mode"].toBool());
    qDebug() << objSkin["take_picture"].toObject()["countdown"].toInt();
    m_txtCountdown->setText(QString::number(objSkin["take_picture"].toObject()["countdown"].toInt()));

    m_chkSkinLastUser->setChecked(objSkin["show_last_user"].toBool());

    if (!objSkin["member_login"].toObject().isEmpty())
    {
        m_chkSkinScanner->setChecked(objSkin["member_login"].toObject()["scanner_is_enable"].toBool());
        m_chkSkinNecessary->setChecked(objSkin["member_login"].toObject()["necessary"].toBool());

        if (objSkin["member_login"].toObject()["info_columns"].toObject()["login_key"].toBool())
        {
            QJsonArray idArray = objSkin["member_login"].toObject()["login_type"].toArray();
            if (idArray.contains(gMemberIDTypeStirngs[ID_PHONE]))
                m_chkSkinPhone->setChecked(true);
            if (idArray.contains(gMemberIDTypeStirngs[ID_KEY]))
                m_chkSkinKey->setChecked(true);
            if (idArray.contains(gMemberIDTypeStirngs[ID_EMAIL]))
                m_chkSkinEmail->setChecked(true);

        }
        //m_chkSkinPhone->setChecked(objSkin["member_login"].toObject()["info_columns"].toObject()["login_key"].toBool());
        m_chkSkinName->setChecked(objSkin["member_login"].toObject()["info_columns"].toObject()["name"].toBool());
    }

    if (!objSkin["privacy"].toObject().isEmpty())
    {
        int idx = m_cbSkinPrivacy->findText(objSkin["privacy"].toObject()["show"].toString());

        if (idx != -1)
            m_cbSkinPrivacy->setCurrentIndex(idx);
    }

    if (!objSkin["term_of_use"].toObject().isEmpty())
    {
        int idx = m_cbSkinTOU->findText(objSkin["term_of_use"].toObject()["show"].toString());

        if (idx != -1)
            m_cbSkinTOU->setCurrentIndex(idx);
    }

    int idx = m_cbSkinFlowType->findText(objSkin["flow_type"].toString());

    if (idx != -1)
        m_cbSkinFlowType->setCurrentIndex(idx);

    // share report
    m_chkSkinReport->setChecked(!objSkin["share_report"].toObject().isEmpty());
    QJsonArray typeArray = objSkin["share_report"].toObject()["type"].toArray();
    for (int i=0; i<typeArray.size(); i++)
    {
        if (typeArray[i].toString() == "qrcode")
        {
            m_chkSkinReportTypeQRcode->setChecked(true);
        }
        if (typeArray[i].toString() == "email")
        {
            m_chkSkinReportTypeEmail->setChecked(true);
        }
    }

//    if (!objSkin["share_report"].toObject().isEmpty())
//    {



//        int idx = m_cbSkinReportType->findText(objSkin["share_report"].toObject()["type"].toString());

//        if (idx != -1)
//            m_cbSkinReportType->setCurrentIndex(idx);

//        m_chkSkinMemberAuth->setChecked(objSkin["share_report"].toObject()["need_member_auth"].toBool());
//        m_chkSkinMemberProfile->setChecked(objSkin["share_report"].toObject()["need_member_profile"].toBool());
//    }

}

void ChannelProfile::setHiSkinTab()
{
    QJsonObject objHiSkin = JsonHandler::getInstance()->getNode(JsonHandler::HISKIN);

    if (objHiSkin.isEmpty())
        objHiSkin = JsonHandler::getInstance()->getDefaultNode(JsonHandler::HISKIN);

    // score type
    QString scoreType = objHiSkin["view_score_filter"].toObject()["detail"].toObject()["type"].toString();
    if (scoreType == "rawscore")
    {
        m_rbHiSkinRawScore->setChecked(true);
    }
    else if (scoreType == "percentage")
    {
        m_rbHiSkinPercentage->setChecked(true);
    }

    QJsonArray factorArray = objHiSkin["detected_factor"].toArray();
    for (int i=0; i<factorArray.size(); i++)
    {
        m_HiSkinFactorList[i] = factorArray[i].toString();
        if (getHiSkinFactorIndex(m_HiSkinFactorList[i]) != -1)
            m_btnHiSkinFactor[getHiSkinFactorIndex(m_HiSkinFactorList[i])]->setText(QString("%1").arg(i+1));
    }

    m_chkHiSkinLastUser->setChecked(objHiSkin["show_last_user"].toBool());

    if (!objHiSkin["member_login"].toObject().isEmpty())
    {
        m_chkHiSkinScanner->setChecked(objHiSkin["member_login"].toObject()["scanner_is_enable"].toBool());
        m_chkHiSkinNecessary->setChecked(objHiSkin["member_login"].toObject()["necessary"].toBool());

        if (objHiSkin["member_login"].toObject()["info_columns"].toObject()["login_key"].toBool())
        {
            QJsonArray idArray = objHiSkin["member_login"].toObject()["login_type"].toArray();
            if (idArray.contains(gMemberIDTypeStirngs[ID_PHONE]))
                m_chkHiSkinPhone->setChecked(true);
            if (idArray.contains(gMemberIDTypeStirngs[ID_KEY]))
                m_chkHiSkinKey->setChecked(true);
            if (idArray.contains(gMemberIDTypeStirngs[ID_EMAIL]))
                m_chkHiSkinEmail->setChecked(true);

        }
//        if (!objHiSkin["member_login"].toObject()["info_columns"].toObject().isEmpty())
//            m_chkHiSkinPhone->setChecked(objHiSkin["member_login"].toObject()["info_columns"].toObject()["login_key"].toBool());
        if (!objHiSkin["member_login"].toObject()["info_columns"].toObject().isEmpty())
            m_chkHiSkinName->setChecked(objHiSkin["member_login"].toObject()["info_columns"].toObject()["name"].toBool());
    }

    if (!objHiSkin["privacy"].toObject().isEmpty())
    {
        int idx = m_cbHiSkinPrivacy->findText(objHiSkin["privacy"].toObject()["show"].toString());

        if (idx != -1)
            m_cbHiSkinPrivacy->setCurrentIndex(idx);
    }

    if (!objHiSkin["term_of_use"].toObject().isEmpty())
    {
        int idx = m_cbHiSkinTOU->findText(objHiSkin["term_of_use"].toObject()["show"].toString());

        if (idx != -1)
            m_cbHiSkinTOU->setCurrentIndex(idx);
    }

    // share report
    m_chkHiSkinReport->setChecked(!objHiSkin["share_report"].toObject().isEmpty());
    QJsonArray typeArray = objHiSkin["share_report"].toObject()["type"].toArray();
    for (int i=0; i<typeArray.size(); i++)
    {
        if (typeArray[i].toString() == "qrcode")
        {
            m_chkHiSkinReportTypeQRcode->setChecked(true);
        }
        if (typeArray[i].toString() == "email")
        {
            m_chkHiSkinReportTypeEmail->setChecked(true);
        }
    }
//    if (!objHiSkin["share_report"].toObject().isEmpty())
//    {
//        int idx = m_cbHiSkinReportType->findText(objHiSkin["share_report"].toObject()["type"].toString());

//        if (idx != -1)
//            m_cbHiSkinReportType->setCurrentIndex(idx);

////        m_chkHiSkinMemberAuth->setChecked(objHiSkin["share_report"].toObject()["need_member_auth"].toBool());
////        m_chkHiSkinMemberProfile->setChecked(objHiSkin["share_report"].toObject()["need_member_profile"].toBool());
//    }

}

void ChannelProfile::setSBSTab()
{
    QJsonObject objSBS = JsonHandler::getInstance()->getNode(JsonHandler::SBS);

    if (objSBS.isEmpty())
        objSBS = JsonHandler::getInstance()->getDefaultNode(JsonHandler::SBS);

//    // score type
//    QString scoreType = objSBS["view_score_filter"].toObject()["all_scenario"].toObject()["type"].toString();
//    if (scoreType == "rawscore")
//    {
//        m_rbSBSRawScore->setChecked(true);
//    }
//    else if (scoreType == "percentage")
//    {
//        m_rbSBSPercentage->setChecked(true);
//    }

    QJsonArray factorArray = objSBS["detected_factor"].toArray();
    for (int i=0; i<factorArray.size(); i++)
    {
        m_SBSFactorList[i] = factorArray[i].toString();
        if (getSBSFactorIndex(m_SBSFactorList[i]) != -1)
            m_btnSBSFactor[getSBSFactorIndex(m_SBSFactorList[i])]->setText(QString("%1").arg(i+1));
    }

    m_chkSBSLastUser->setChecked(objSBS["show_last_user"].toBool());

    if (!objSBS["member_login"].toObject().isEmpty())
    {
        m_chkSBSScanner->setChecked(objSBS["member_login"].toObject()["scanner_is_enable"].toBool());
        m_chkSBSNecessary->setChecked(objSBS["member_login"].toObject()["necessary"].toBool());

        if (objSBS["member_login"].toObject()["info_columns"].toObject()["login_key"].toBool())
        {
            QJsonArray idArray = objSBS["member_login"].toObject()["login_type"].toArray();
            if (idArray.contains(gMemberIDTypeStirngs[ID_PHONE]))
                m_chkSBSPhone->setChecked(true);
            if (idArray.contains(gMemberIDTypeStirngs[ID_KEY]))
                m_chkSBSKey->setChecked(true);
            if (idArray.contains(gMemberIDTypeStirngs[ID_EMAIL]))
                m_chkSBSEmail->setChecked(true);

        }
//        if (!objSBS["member_login"].toObject()["info_columns"].toObject().isEmpty())
//            m_chkSBSPhone->setChecked(objSBS["member_login"].toObject()["info_columns"].toObject()["login_key"].toBool());
        if (!objSBS["member_login"].toObject()["info_columns"].toObject().isEmpty())
            m_chkSBSName->setChecked(objSBS["member_login"].toObject()["info_columns"].toObject()["name"].toBool());
    }

    if (!objSBS["privacy"].toObject().isEmpty())
    {
        int idx = m_cbSBSPrivacy->findText(objSBS["privacy"].toObject()["show"].toString());

        if (idx != -1)
            m_cbSBSPrivacy->setCurrentIndex(idx);
    }

    if (!objSBS["term_of_use"].toObject().isEmpty())
    {
        int idx = m_cbSBSTOU->findText(objSBS["term_of_use"].toObject()["show"].toString());

        if (idx != -1)
            m_cbSBSTOU->setCurrentIndex(idx);
    }

    // share report
    m_chkSBSReport->setChecked(!objSBS["share_report"].toObject().isEmpty());
    QJsonArray typeArray = objSBS["share_report"].toObject()["type"].toArray();
    for (int i=0; i<typeArray.size(); i++)
    {
        if (typeArray[i].toString() == "qrcode")
        {
            m_chkSBSReportTypeQRcode->setChecked(true);
        }
        if (typeArray[i].toString() == "email")
        {
            m_chkSBSReportTypeEmail->setChecked(true);
        }
    }
//    if (!objSBS["share_report"].toObject().isEmpty())
//    {
//        int idx = m_cbSBSReportType->findText(objSBS["share_report"].toObject()["type"].toString());

//        if (idx != -1)
//            m_cbSBSReportType->setCurrentIndex(idx);

////        m_chkSBSMemberAuth->setChecked(objSBS["share_report"].toObject()["need_member_auth"].toBool());
////        m_chkSBSMemberProfile->setChecked(objSBS["share_report"].toObject()["need_member_profile"].toBool());
//    }

}

void ChannelProfile::setNewsTab()
{
    QJsonObject objCommon = JsonHandler::getInstance()->getNode(JsonHandler::COMMON);
    QJsonArray newsArray = objCommon["news"].toArray();

    QStringList header;

    header << "URL" << "Name" << "Type" << "Source" << "Language";

    //m_tvNews->setRowCount(1);
    m_tvNews->setColumnCount(5);
    m_tvNews->setHorizontalHeaderLabels(header);
    for (int i=0; i<newsArray.size(); i++)
    {
//        m_txtNewsUrl->setText(newsArray[i].toObject()["url"].toString());
//        m_txtNewsName->setText(newsArray[i].toObject()["name"].toString());
//        m_txtNewsType->setText(newsArray[i].toObject()["type"].toString());
//        m_txtNewsSource->setText(newsArray[i].toObject()["source"].toString());
//        m_txtNewsLanguage->setText(newsArray[i].toObject()["language"].toString());

        m_tvNews->insertRow(m_tvNews->rowCount());
        QTableWidgetItem *urlItem = new QTableWidgetItem(newsArray[i].toObject()["url"].toString());
        m_tvNews->setItem(i, 0, urlItem);

        QTableWidgetItem *nameItem = new QTableWidgetItem(newsArray[i].toObject()["name"].toString());
        m_tvNews->setItem(i, 1, nameItem);

        QTableWidgetItem *typeItem = new QTableWidgetItem(newsArray[i].toObject()["type"].toString());
        m_tvNews->setItem(i, 2, typeItem);

        QTableWidgetItem *sourceItem = new QTableWidgetItem(newsArray[i].toObject()["source"].toString());
        m_tvNews->setItem(i, 3, sourceItem);

        QTableWidgetItem *languageItem = new QTableWidgetItem(newsArray[i].toObject()["language"].toString());
        m_tvNews->setItem(i, 4, languageItem);

    }
    m_tvNews->resizeColumnsToContents();
}

void ChannelProfile::setAppTab()
{
    QJsonObject objApp = JsonHandler::getInstance()->getNode(JsonHandler::THIRDPARTY);

    QStringList header;

    header << "Name" << "Enable" << "Access_Level" << "Package_Name";

    //m_tvApp->setRowCount(1);
    m_tvApp->setColumnCount(4);
    m_tvApp->setHorizontalHeaderLabels(header);
    m_tvApp->resizeColumnsToContents();

    if (objApp.isEmpty())
        return;

    QJsonArray AppArray;
    AppArray= objApp["quick_link"].toArray();

    for (int i=0; i<AppArray.size(); i++)
    {
        m_tvApp->insertRow(m_tvApp->rowCount());
        QTableWidgetItem *urlItem = new QTableWidgetItem(AppArray[i].toObject()["name"].toString());
        m_tvApp->setItem(i, 0, urlItem);

        QCheckBox *enabled = new QCheckBox("Enable");
        enabled->setChecked(AppArray[i].toObject()["enable"].toBool());
        m_tvApp->setCellWidget(i, 1, enabled);

        QComboBox *level = new QComboBox();
        for (int i=0; i<ACCESSLEVELSCOUNT; i++)
            level->addItem(gAccessLevelStrings[i]);

        int idx = level->findText((AppArray[i].toObject()["access_level"].toString()));

        if (idx != -1)
            level->setCurrentIndex(idx);

        m_tvApp->setCellWidget(i, 2, level);

        QTableWidgetItem *languageItem = new QTableWidgetItem(AppArray[i].toObject()["package_name"].toString());
        m_tvApp->setItem(i, 3, languageItem);

    }
    m_tvApp->resizeColumnsToContents();
}


int ChannelProfile::getLoginTypeIndex(QString factor)
{
    int ret = -1;
    for (int i=0; i<LOGINTYPESCOUNT ; i++ )
    {
        if (gMemberLoginStirngs[i].compare(factor, Qt::CaseInsensitive) == 0)
        {
            ret = i;
            break;
        }
    }

    return ret;
}

int ChannelProfile::getLanguageIndex(QString factor)
{
    int ret = -1;
    for (int i=0; i<LANGUAGESCOUNT ; i++ )
    {
        if (gLanguageStirngs[i].compare(factor, Qt::CaseInsensitive) == 0)
        {
            ret = i;
            break;
        }
    }

    return ret;
}

int ChannelProfile::getSkinFactorIndex(QString factor)
{
    int ret = -1;
    for (int i=0; i<FACTORSCOUNT ; i++ )
    {
        if (gFactorStirngs[i].compare(factor, Qt::CaseInsensitive) == 0)
        {
            ret = i;
            break;
        }
    }

    return ret;
}

int ChannelProfile::getHiSkinFactorIndex(QString factor)
{
    int ret = -1;
    for (int i=0; i<HISKINFACTORSCOUNT ; i++ )
    {
        if (gHiSkinFactorStirngs[i].compare(factor, Qt::CaseInsensitive) == 0)
        {
            ret = i;
            break;
        }
    }

    return ret;
}

int ChannelProfile::getSBSFactorIndex(QString factor)
{
    int ret = -1;
    for (int i=0; i<SBSFACTORSCOUNT ; i++ )
    {
        if (gSBSFactorStirngs[i].compare(factor, Qt::CaseInsensitive) == 0)
        {
            ret = i;
            break;
        }
    }

    return ret;
}

bool ChannelProfile::updateConfig(QJsonDocument doc)
{

    QSqlQuery qUpdate(DBHandler::getDBHandler()) ;
    QString str = QString("update usr_channel_profile_settings set json_value = '%1' where syschannelprofiles_id='%2'").arg(doc.toJson(QJsonDocument::Compact).toStdString().data()).arg(m_id);

    return qUpdate.exec(str);

}

QJsonDocument ChannelProfile::getDefaultSettings()
{

    QJsonDocument doc;

    QSqlQuery q(DBHandler::getDBHandler());
    q.exec("select json_value from usr_channel_profile_settings where syschannelprofiles_id='SYSChannelProfilesDefault'");
    if (q.next())
    {
        doc = QJsonDocument::fromJson(q.value(0).toByteArray());
    }
    else
    {
        qDebug() << "QSqlQuery : " << q.lastQuery() << " failed.";
    }

    return doc;
}


void ChannelProfile::onSaveClicked(bool)
{
    if (!checkFactors())
    {
        return;
    }

    QJsonObject ObjRoot =  m_doc.object();
    qDebug() <<  m_doc.toJson(QJsonDocument::Compact);

    // Common
    QJsonObject ObjCommon = ObjRoot["common"].toObject();
    ObjCommon["language"] = m_cbLanguage->currentText();
    ObjCommon["region"] = m_txtRegion->text();
    ObjCommon["sales_email"] = m_txtSalesEmail->text();
    ObjCommon["alexa_is_enable"] = m_chkAlexa->isChecked();

    QJsonArray arrLanguage ;

    for(int i=0; i<m_LanguageList.size(); i++)
        arrLanguage.append(m_LanguageList[i+1]);

    ObjCommon["support_languages"] = arrLanguage;

    if (m_LoginTypeList.size() > 0)
    {
        QJsonObject ObjMemberlogin = ObjCommon["member_login"].toObject();

        ObjMemberlogin["reg_url"] = m_txtRegUrl->text();
        ObjMemberlogin["forget_password_url"] = m_txtForgetUrl->text();

        QJsonArray arrLoginType;
        for(int i=0; i<m_LoginTypeList.size(); i++)
            arrLoginType.append(QJsonValue(m_LoginTypeList[i+1]));

        ObjMemberlogin["login_type"] = QJsonValue(arrLoginType);
        ObjCommon["member_login"] = ObjMemberlogin;
    }

    if (m_chkBeautyBox->isChecked())
        ObjRoot["beauty_box"] = QJsonObject();
    else
        ObjRoot.remove("beauty_box");

    // News
    if (m_chkNews->isChecked() && m_tvNews->rowCount() > 0)
    {
        QJsonArray arrNews;
        for(int i=0; i<m_tvNews->rowCount(); i++)
        {
            QJsonObject objNewsItem = QJsonObject();
            objNewsItem["url"] = QJsonValue(m_tvNews->item(i, 0)->text());
            objNewsItem["name"] = QJsonValue(m_tvNews->item(i, 1)->text());
            objNewsItem["type"] = QJsonValue(m_tvNews->item(i, 2)->text());
            objNewsItem["source"] = QJsonValue(m_tvNews->item(i, 3)->text());
            objNewsItem["language"] = QJsonValue(m_tvNews->item(i, 4)->text());

            arrNews.append(objNewsItem);
        }
        ObjCommon["news"] = arrNews;
    }
    else
    {
        //ObjCommon.remove("news");
        ObjCommon["news"] = QJsonObject();
    }
    ObjRoot["common"] = ObjCommon;

    // 3rd party
    QJsonObject ObjHome = ObjRoot["home"].toObject();

    if (m_chkApp->isChecked())
    {
        QJsonArray arrApp;
        for(int i=0; i<m_tvApp->rowCount(); i++)
        {
            QJsonObject objAppItem = QJsonObject();
            objAppItem["name"] = QJsonValue(m_tvApp->item(i, 0)->text());
            objAppItem["enable"] = QJsonValue(qobject_cast<QCheckBox*>(m_tvApp->cellWidget(i,1))->isChecked());
            objAppItem["access_level"] = QJsonValue(qobject_cast<QComboBox*>(m_tvApp->cellWidget(i,2))->currentText());
            objAppItem["package_name"] = QJsonValue(m_tvApp->item(i, 3)->text());

            arrApp.append(objAppItem);
        }
        QJsonObject ObjThirdparty_apps = ObjHome["thirdparty_apps"].toObject();
        ObjThirdparty_apps["quick_link"] = arrApp;
        ObjHome["thirdparty_apps"] = ObjThirdparty_apps;
    }
    else
    {
        ObjHome.remove("thirdparty_apps");
    }

    ObjRoot["home"] = ObjHome;

    // skin analysis
    QJsonObject ObjSkin = ObjRoot["skin_analysis"].toObject();
    ObjSkin["skinage_is_enable"] = QJsonValue(m_chkSkinAge->isChecked());
    ObjSkin["levelbar_is_enable"] = QJsonValue(m_chkLevelBar->isChecked());
    ObjSkin["upload_skinimage_is_enable"] = QJsonValue(m_chkUploadImage->isChecked());
    ObjSkin["upload_skinimage_user_decide"] = QJsonValue(m_chkUploadImageUserDecide->isChecked());

    QJsonObject ObjView_score_filter = ObjSkin["view_score_filter"].toObject();
    QJsonObject ObjAll_scenario = ObjView_score_filter["all_scenario"].toObject();

    if (m_rbSkinPercentage->isChecked())
        ObjAll_scenario["type"] = QJsonValue("percentage");
    else
        ObjAll_scenario["type"] = QJsonValue("rawscore");

    ObjView_score_filter["all_scenario"] = ObjAll_scenario;
    ObjSkin["view_score_filter"] = ObjView_score_filter;

    QJsonArray arrSkinFactor;
    for(int i=0; i<m_SkinFactorList.size(); i++)
        arrSkinFactor.append(QJsonValue(m_SkinFactorList[i+1]));

    ObjSkin["detected_factor"] = arrSkinFactor;

    QJsonObject ObjTakePicture = ObjSkin["take_picture"].toObject();
    ObjTakePicture["show_manual"] = QJsonValue(m_chkShowManual->isChecked());
    ObjTakePicture["manual_mode"] = QJsonValue(m_chkManualMode->isChecked());
    ObjTakePicture["countdown"] = QJsonValue(m_txtCountdown->text().toInt());
    ObjSkin["take_picture"] = ObjTakePicture;

    ObjSkin["show_last_user"] = QJsonValue(m_chkSkinLastUser->isChecked());
    QJsonObject ObjMemberLogin = ObjSkin["member_login"].toObject();
    ObjMemberLogin["necessary"] = QJsonValue(m_chkSkinNecessary->isChecked());
    ObjMemberLogin["scanner_is_enable"] = QJsonValue(m_chkSkinScanner->isChecked());

    QJsonObject ObjInfo_columns = ObjMemberLogin["info_columns"].toObject();

    QJsonArray IDtype;
    if (m_chkSkinPhone->isChecked())
        IDtype.append(gMemberIDTypeStirngs[ID_PHONE]);
    if (m_chkSkinKey->isChecked())
        IDtype.append(gMemberIDTypeStirngs[ID_KEY]);
    if (m_chkSkinEmail->isChecked())
        IDtype.append(gMemberIDTypeStirngs[ID_EMAIL]);

    if (IDtype.count()==0)
    {
        IDtype.append(gMemberIDTypeStirngs[ID_RANDOM]);
        ObjInfo_columns["login_key"] = false;
    }
    else
    {
        ObjMemberLogin["login_type"] = IDtype;
        ObjInfo_columns["login_key"] = true;
    }


//    ObjInfo_columns["login_key"] = QJsonValue(m_chkSkinPhone->isChecked());
    ObjInfo_columns["name"] = QJsonValue(m_chkSkinName->isChecked());
    ObjMemberLogin["info_columns"] = ObjInfo_columns;
    ObjSkin["member_login"] = ObjMemberLogin;

    QJsonObject ObjPrivacy = ObjSkin["privacy"].toObject();
    ObjPrivacy["show"] = QJsonValue(m_cbSkinPrivacy->currentText());
    ObjSkin["privacy"] = ObjPrivacy;

    QJsonObject Objterm_of_use = ObjSkin["term_of_use"].toObject();
    Objterm_of_use["show"] = QJsonValue(m_cbSkinTOU->currentText());
    ObjSkin["term_of_use"] = Objterm_of_use;

    ObjSkin["flow_type"] = QJsonValue(m_cbSkinFlowType->currentText());

    if (m_chkSkinReport->isChecked())
    {
        QJsonObject ObjShare_report = ObjSkin["share_report"].toObject();
        QJsonArray type;
        //type.append(m_cbSkinReportType->currentText());
        if (m_chkSkinReportTypeQRcode->isChecked())
            type.append("qrcode");
        if (m_chkSkinReportTypeEmail->isChecked())
            type.append("email");

        ObjShare_report["type"] = QJsonValue(type);
//        ObjShare_report["need_member_auth"] = QJsonValue(m_chkSkinMemberAuth->isChecked());
//        ObjShare_report["need_member_profile"] = QJsonValue(m_chkSkinMemberProfile->isChecked());
        ObjSkin["share_report"] = ObjShare_report;
    }
    else
    {
       ObjSkin["share_report"] = QJsonObject();
    }

    ObjRoot["skin_analysis"] = ObjSkin;

    // HiSkin
    if (m_chkHiSkin->isChecked())
    {
        QJsonObject ObjHiSkin = ObjRoot["hiskin"].toObject();

        // set to default Json
        if (ObjHiSkin.isEmpty())
            ObjHiSkin = JsonHandler::getInstance()->getDefaultNode(JsonHandler::HISKIN);

        QJsonObject ObjView_score_filter = ObjHiSkin["view_score_filter"].toObject();
        QJsonObject ObjDetail = ObjView_score_filter["detail"].toObject();

        if (m_rbHiSkinPercentage->isChecked())
            ObjDetail["type"] = QJsonValue("percentage");
        else
            ObjDetail["type"] = QJsonValue("rawscore");

        ObjView_score_filter["detail"] = ObjDetail;
        ObjHiSkin["view_score_filter"] = ObjView_score_filter;

        QJsonArray arrHiSkinFactor;
        for(int i=0; i<m_HiSkinFactorList.size(); i++)
            arrHiSkinFactor.append(QJsonValue(m_HiSkinFactorList[i+1]));

        ObjHiSkin["detected_factor"] = arrHiSkinFactor;

        ObjHiSkin["show_last_user"] = QJsonValue(m_chkHiSkinLastUser->isChecked());
        QJsonObject ObjMemberLogin = ObjHiSkin["member_login"].toObject();
        ObjMemberLogin["necessary"] = QJsonValue(m_chkHiSkinNecessary->isChecked());
        ObjMemberLogin["scanner_is_enable"] = QJsonValue(m_chkHiSkinScanner->isChecked());

        QJsonObject ObjInfo_columns = ObjMemberLogin["info_columns"].toObject();

        QJsonArray IDtype;
        if (m_chkHiSkinPhone->isChecked())
            IDtype.append(gMemberIDTypeStirngs[ID_PHONE]);
        if (m_chkHiSkinKey->isChecked())
            IDtype.append(gMemberIDTypeStirngs[ID_KEY]);
        if (m_chkHiSkinEmail->isChecked())
            IDtype.append(gMemberIDTypeStirngs[ID_EMAIL]);

        if (IDtype.count()==0)
        {
            IDtype.append(gMemberIDTypeStirngs[ID_RANDOM]);
            ObjInfo_columns["login_key"] = false;
        }
        else
        {
            ObjMemberLogin["login_type"] = IDtype;
            ObjInfo_columns["login_key"] = true;
        }

        //ObjInfo_columns["login_key"] = QJsonValue(m_chkHiSkinPhone->isChecked());
        ObjInfo_columns["name"] = QJsonValue(m_chkHiSkinName->isChecked());
        ObjMemberLogin["info_columns"] = ObjInfo_columns;
        ObjHiSkin["member_login"] = ObjMemberLogin;

        QJsonObject ObjPrivacy = ObjHiSkin["privacy"].toObject();
        ObjPrivacy["show"] = QJsonValue(m_cbHiSkinPrivacy->currentText());
        ObjHiSkin["privacy"] = ObjPrivacy;

        QJsonObject Objterm_of_use = ObjHiSkin["term_of_use"].toObject();
        Objterm_of_use["show"] = QJsonValue(m_cbHiSkinTOU->currentText());
        ObjHiSkin["term_of_use"] = Objterm_of_use;

        if (m_chkHiSkinReport->isChecked())
        {
            QJsonObject ObjShare_report = ObjHiSkin["share_report"].toObject();
            QJsonArray type;
            //type.append(m_cbHiSkinReportType->currentText());
            if (m_chkHiSkinReportTypeQRcode->isChecked())
                type.append("qrcode");
            if (m_chkHiSkinReportTypeEmail->isChecked())
                type.append("email");
            ObjShare_report["type"] = QJsonValue(type);
//            ObjShare_report["need_member_auth"] = QJsonValue(m_chkHiSkinMemberAuth->isChecked());
//            ObjShare_report["need_member_profile"] = QJsonValue(m_chkHiSkinMemberProfile->isChecked());
            ObjHiSkin["share_report"] = ObjShare_report;
        }
        else
        {
           ObjHiSkin["share_report"] = QJsonObject();
        }
        ObjRoot["hiskin"] = ObjHiSkin;
    }
    else
    {
        ObjRoot["hiskin"] = QJsonObject();
    }

    // SBS
    if (m_chkSBS->isChecked())
    {
        QJsonObject ObjSBS = ObjRoot["sbs"].toObject();
        // set to default Json
        if (ObjSBS.isEmpty())
            ObjSBS = JsonHandler::getInstance()->getDefaultNode(JsonHandler::HISKIN);

//        QJsonObject ObjView_score_filter = ObjSBS["view_score_filter"].toObject();
//        QJsonObject ObjAll_scenario = ObjView_score_filter["all_scenario"].toObject();

//        if (m_rbSBSPercentage->isChecked())
//            ObjAll_scenario["type"] = QJsonValue("percentage");
//        else
//            ObjAll_scenario["type"] = QJsonValue("rawscore");

//        ObjView_score_filter["all_scenario"] = ObjAll_scenario;
//        ObjSBS["view_score_filter"] = ObjView_score_filter;

        QJsonArray arrSBSFactor;
        for(int i=0; i<m_SBSFactorList.size(); i++)
            arrSBSFactor.append(QJsonValue(m_SBSFactorList[i+1]));

        ObjSBS["detected_factor"] = arrSBSFactor;

        ObjSBS["show_last_user"] = QJsonValue(m_chkSBSLastUser->isChecked());
        QJsonObject ObjMemberLogin = ObjSBS["member_login"].toObject();
        ObjMemberLogin["necessary"] = QJsonValue(m_chkSBSNecessary->isChecked());
        ObjMemberLogin["scanner_is_enable"] = QJsonValue(m_chkSBSScanner->isChecked());

        QJsonObject ObjInfo_columns = ObjMemberLogin["info_columns"].toObject();
        QJsonArray IDtype;
        if (m_chkSBSPhone->isChecked())
            IDtype.append(gMemberIDTypeStirngs[ID_PHONE]);
        if (m_chkSBSKey->isChecked())
            IDtype.append(gMemberIDTypeStirngs[ID_KEY]);
        if (m_chkSBSEmail->isChecked())
            IDtype.append(gMemberIDTypeStirngs[ID_EMAIL]);

        if (IDtype.count()==0)
        {
            IDtype.append(gMemberIDTypeStirngs[ID_RANDOM]);
            ObjInfo_columns["login_key"] = false;
        }
        else
        {
            ObjMemberLogin["login_type"] = IDtype;
            ObjInfo_columns["login_key"] = true;
        }

        //ObjInfo_columns["login_key"] = QJsonValue(m_chkSBSPhone->isChecked());
        ObjInfo_columns["name"] = QJsonValue(m_chkSBSName->isChecked());
        ObjMemberLogin["info_columns"] = ObjInfo_columns;
        ObjSBS["member_login"] = ObjMemberLogin;

        QJsonObject ObjPrivacy = ObjSBS["privacy"].toObject();
        ObjPrivacy["show"] = QJsonValue(m_cbSBSPrivacy->currentText());
        ObjSBS["privacy"] = ObjPrivacy;

        QJsonObject Objterm_of_use = ObjSBS["term_of_use"].toObject();
        Objterm_of_use["show"] = QJsonValue(m_cbSBSTOU->currentText());
        ObjSBS["term_of_use"] = Objterm_of_use;

        if (m_chkSBSReport->isChecked())
        {
            QJsonObject ObjShare_report = ObjSBS["share_report"].toObject();
            QJsonArray type;
            if (m_chkSBSReportTypeQRcode->isChecked())
                type.append("qrcode");
            if (m_chkSBSReportTypeEmail->isChecked())
                type.append("email");
            //type.append(m_cbSBSReportType->currentText());
            ObjShare_report["type"] = QJsonValue(type);
//            ObjShare_report["need_member_auth"] = QJsonValue(m_chkSBSMemberAuth->isChecked());
//            ObjShare_report["need_member_profile"] = QJsonValue(m_chkSBSMemberProfile->isChecked());
            ObjSBS["share_report"] = ObjShare_report;
        }
        else
        {
           ObjSBS["share_report"] = QJsonObject();
        }
        ObjRoot["sbs"] = ObjSBS;
    }
    else
    {
        ObjRoot["sbs"] = QJsonObject();
    }

    qDebug() << "After----------------------------------------------------------------------------";
    qDebug() << "After----------------------------------------------------------------------------";
    qDebug() << "After----------------------------------------------------------------------------";
    qDebug() << "After----------------------------------------------------------------------------";
    QJsonDocument doc(ObjRoot);
    qDebug() << doc.toJson(QJsonDocument::Compact);

//    QJsonDocument doc = JsonHandler::getInstance()->getUpadtedDoc(m_cbLanguage->currentText(), m_chkHiSkin->isChecked(), m_chkProduct->isChecked(), m_chkSkinAge->isChecked(), scoreType, list, m_chkPhone->isChecked());

//    qDebug() << doc.toJson(QJsonDocument::Compact);

    QMessageBox msgBox;
    msgBox.setWindowTitle("Edit before upload?");
    msgBox.setText("Do you want to edit profile json before upload to database??");
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    bool bRet = false;
    if(msgBox.exec() == QMessageBox::Yes)
    {
        DialogEditJson dlg;// = new DialogEditJson();
        dlg.setJson(doc.toJson(QJsonDocument::Indented));
        dlg.setModal(true);
        if(dlg.exec() == QDialog::Accepted)
        {
            qDebug() << "accepted";
            qDebug() << dlg.getJson();
            QJsonDocument modifiedDoc = QJsonDocument::fromJson(dlg.getJson());
            bRet = updateConfig(modifiedDoc);
        }
        else
        {
            bRet = updateConfig(doc);
        }
    }
    else
    {
        bRet = updateConfig(doc);
    }

    //bool bRet = updateConfig(doc);
    if (bRet)
    {
        QMessageBox::information(NULL, "Info", "Update config to id: " + m_id + " OK!", QMessageBox::Ok);
    }
    else
    {
        showErrorDialog("update json to id: " + m_id + " failed!!");
    }
    close();
}

void ChannelProfile::onResetClicked(bool)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Confirmation");
    msgBox.setText("Are you sure to reset to default settings??");
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if(msgBox.exec() == QMessageBox::Yes)
    {
        setView(m_defaultSetting);
    }
}

bool ChannelProfile::checkFactors()
{

    bool ret = true;

    if (!checkCommon())
    {
        m_twMain->setCurrentIndex(m_twMain->indexOf(ui->tabCommon));
        return false;
    }

    if (!checkSkin())
    {
        m_twMain->setCurrentIndex(m_twMain->indexOf(ui->tabSkinAnalysis));
        return false;
    }

    if (m_chkHiSkin->isChecked() && !checkHiSkin())
    {
        m_twMain->setCurrentIndex(m_twMain->indexOf(ui->tabHiSkin));
        return false;
    }

    if (m_chkSBS->isChecked() && !checkSBS())
    {
        m_twMain->setCurrentIndex(m_twMain->indexOf(ui->tabSBS));
        return false;
    }

    if (m_chkNews->isChecked() && !checkNews())
    {
        m_twMain->setCurrentIndex(m_twMain->indexOf(ui->tabNews));
        return false;
    }

    if (m_chkApp->isChecked() && !checkApp())
    {
        m_twMain->setCurrentIndex(m_twMain->indexOf(ui->tabApp));
        return false;
    }

    return ret;
}


bool ChannelProfile::checkCommon()
{
    // check support language
    // check orders
    m_LanguageList.clear();

    for(int i=0; i<LANGUAGESCOUNT; i++)
    {
        qDebug() << m_btnLanguage[i]->text();
        if (m_btnLanguage[i]->text() != "X")
        {
            int idx = m_btnLanguage[i]->text().toInt();
            if (m_LanguageList[idx] != NULL)
            {
                QString str = "Supported Laguage order : " + QString("%1").arg(idx) + " is duplicated!!";
                showErrorDialog(str);
                return false;
            }
            else
            {
                m_LanguageList[idx] = gLanguageStirngs[i];
            }
        }
    }

    qDebug() << m_LanguageList;

    // check sequence
    for (int i=1; i<=m_LanguageList.count(); i++)
    {
        if (m_LanguageList[i] == NULL && i<m_LanguageList.count())
        {
            QString str = "Supported Language sequence : " + QString("%1").arg(i) + " is missing!!";
            showErrorDialog(str);
            return false;
        }
    }

    // check Login type
    m_LoginTypeList.clear();

    for(int i=0; i<LOGINTYPESCOUNT; i++)
    {
        qDebug() << m_btnMemberLogin[i]->text();
        if (m_btnMemberLogin[i]->text() != "X")
        {
            int idx = m_btnMemberLogin[i]->text().toInt();
            if (m_LoginTypeList[idx] != NULL)
            {
                QString str = "Member Login Type order : " + QString("%1").arg(idx) + " is duplicated!!";
                showErrorDialog(str);
                return false;
            }
            else
            {
                m_LoginTypeList[idx] = gMemberLoginStirngs[i];
            }
        }
    }

    qDebug() << m_LoginTypeList;

    // check sequence
    for (int i=1; i<=m_LoginTypeList.count(); i++)
    {
        if (m_LoginTypeList[i] == NULL && i<m_LoginTypeList.count())
        {
            QString str = "Member login type sequence : " + QString("%1").arg(i) + " is missing!!";
            showErrorDialog(str);
            return false;
        }
    }

    return true;
}

bool ChannelProfile::checkSkin()
{
    bool ret = true;
    QString str;

    // check at least 4 factors selected.
    int cnt=0;

    for(int i=0; i<FACTORSCOUNT; i++)
    {
        if (m_btnFactor[i]->text() != "X")
        {
            cnt++;
        }
    }

    if (cnt < 4)
    {
        str = "At least 4 Skin Analysis factors should be selected.";
        showErrorDialog(str);
        return false;
    }

    if (cnt > 9)
    {
        str = "Current UI only support up to 9 Skin Analysis factors.";
        showErrorDialog(str);
        return false;
    }

    // check orders
    m_SkinFactorList.clear();

    for(int i=0; i<FACTORSCOUNT; i++)
    {
        if (m_btnFactor[i]->text() != "X")
        {
            int idx = m_btnFactor[i]->text().toInt();
            if (m_SkinFactorList[idx] != NULL)
            {
                QString str = "Skin Analysis factors order : " + QString("%1").arg(idx) + " is duplicated!!";
                showErrorDialog(str);
                return false;
            }
            else
            {
                m_SkinFactorList[idx] = gFactorStirngs[i];
            }
        }
    }

    qDebug() << m_SkinFactorList;

    // check sequence
    for (int i=1; i<=m_SkinFactorList.count(); i++)
    {
        if (m_SkinFactorList[i].isEmpty() && i<m_SkinFactorList.count())
        {
            QString str = "Skin Analysis factors sequence : " + QString("%1").arg(i) + " is missing!!";
            showErrorDialog(str);
            return false;
        }
    }

    return ret;
}

bool ChannelProfile::checkHiSkin()
{
    // check HiSkin factor
    m_HiSkinFactorList.clear();

    for(int i=0; i<HISKINFACTORSCOUNT; i++)
    {
        if (m_btnHiSkinFactor[i]->text() != "X")
        {
            int idx = m_btnHiSkinFactor[i]->text().toInt();
            if (m_HiSkinFactorList[idx] != NULL)
            {
                QString str = "HiSkin factor order : " + QString("%1").arg(idx) + " is duplicated!!";
                showErrorDialog(str);
                return false;
            }
            else
            {
                m_HiSkinFactorList[idx] = gHiSkinFactorStirngs[i];
            }
        }
    }

    qDebug() << m_HiSkinFactorList;

    // check sequence
    for (int i=1; i<=m_HiSkinFactorList.count(); i++)
    {
        if (m_HiSkinFactorList[i].isEmpty() && i<m_HiSkinFactorList.count())
        {
            QString str = "HiSkin factor sequence : " + QString("%1").arg(i) + " is missing!!";
            showErrorDialog(str);
            return false;
        }
    }

    return true;
}

bool ChannelProfile::checkSBS()
{
    // check SBS factor
    m_SBSFactorList.clear();

    for(int i=0; i<SBSFACTORSCOUNT; i++)
    {
        if (m_btnSBSFactor[i]->text() != "X")
        {
            int idx = m_btnSBSFactor[i]->text().toInt();
            if (m_SBSFactorList[idx] != NULL)
            {
                QString str = "SBS factor order : " + QString("%1").arg(idx) + " is duplicated!!";
                showErrorDialog(str);
                return false;
            }
            else
            {
                m_SBSFactorList[idx] = gSBSFactorStirngs[i];
            }
        }
    }

    qDebug() << m_SBSFactorList;

    // check sequence
    for (int i=1; i<=m_SBSFactorList.count(); i++)
    {
        if (m_SBSFactorList[i].isEmpty() && i<m_SBSFactorList.count())
        {
            QString str = "SBS factor sequence : " + QString("%1").arg(i) + " is missing!!";
            showErrorDialog(str);
            return false;
        }
    }

    return true;
}

bool ChannelProfile::checkNews()
{
    for(int i=0; i<m_tvNews->rowCount(); i++)
    {
        for (int j=0; j<m_tvNews->columnCount(); j++)
        {
            if (m_tvNews->item(i, j)->text().isEmpty())
            {
                QString str = QString("News item (%1, %2) is empty").arg(i).arg(j);
                return false;
            }
        }
    }

    return true;
}

bool ChannelProfile::checkApp()
{
    for(int i=0; i<m_tvApp->rowCount(); i++)
    {
        for (int j=0; j<m_tvApp->columnCount() && j!=1; j++)
        {
            if (m_tvApp->item(i, j)->text().isEmpty())
            {
                QString str = QString("3rd party item (%1, %2) is empty").arg(i).arg(j);
                return false;
            }
        }
    }
    return true;
}


void ChannelProfile::showErrorDialog(QString str)
{
    QMessageBox::critical(NULL, "cirtical", str, QMessageBox::Ok);
}


void ChannelProfile::onSkinFactorClicked(bool)
{
    buttonClickHandle(FACTORSCOUNT);
}

void ChannelProfile::onLanguageClicked(bool){
    buttonClickHandle(LANGUAGESCOUNT);
}

void ChannelProfile::onLoginTypeClicked(bool){
    buttonClickHandle(LOGINTYPESCOUNT);
}

void ChannelProfile::onHiSkinFactorClicked(bool){
    buttonClickHandle(HISKINFACTORSCOUNT);
}

void ChannelProfile::onSBSFactorClicked(bool){
    buttonClickHandle(SBSFACTORSCOUNT);
}


void ChannelProfile::buttonClickHandle(int count)
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    if (button != NULL)
    {
        if (button->text() != "X") {
            int i = button->text().toInt();
            if (i < count)
            {
                button->setText(QString("%1").arg(i+1));
            }
            else
            {
                button->setText("X");
            }
        }
        else{
            button->setText("1");
        }
    }
}

void ChannelProfile::onNewsAddClicked(bool) {
    m_tvNews->insertRow(m_tvNews->rowCount());
}

void ChannelProfile::onNewsDeleteClicked(bool) {
    m_tvNews->removeRow(m_tvNews->currentRow());
}

void ChannelProfile::onAppAddClicked(bool) {
    m_tvApp->insertRow(m_tvApp->rowCount());
    QCheckBox *enabled = new QCheckBox("Enable");
    enabled->setChecked(true);
    m_tvApp->setCellWidget(m_tvApp->rowCount()-1, 1, enabled);

    QComboBox *level = new QComboBox();
    for (int i=0; i<ACCESSLEVELSCOUNT; i++)
        level->addItem(gAccessLevelStrings[i]);
    m_tvApp->setCellWidget(m_tvApp->rowCount()-1, 2, level);
    m_tvApp->resizeColumnsToContents();
}

void ChannelProfile::onAppDeleteClicked(bool) {
    m_tvApp->removeRow(m_tvApp->currentRow());
}

void ChannelProfile::onHiSkinChecked(bool checked) {
    if (checked)
        m_twMain->addTab(ui->tabHiSkin, "HiSkin");
    else
        m_twMain->removeTab(m_twMain->indexOf(ui->tabHiSkin));
}

void ChannelProfile::onSBSChecked(bool checked) {
    if (checked)
        m_twMain->addTab(ui->tabSBS, "SBS");
    else
        m_twMain->removeTab(m_twMain->indexOf(ui->tabSBS));
}

void ChannelProfile::onNewsChecked(bool checked) {
    if (checked)
        m_twMain->addTab(ui->tabNews, "News");
    else
        m_twMain->removeTab(m_twMain->indexOf(ui->tabNews));
}

void ChannelProfile::onAppChecked(bool checked) {
    if (checked)
        m_twMain->addTab(ui->tabApp, "3rd Party");
    else
        m_twMain->removeTab(m_twMain->indexOf(ui->tabApp));
}

