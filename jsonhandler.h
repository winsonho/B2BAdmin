#ifndef JSONHANDLER_H
#define JSONHANDLER_H
#include "common.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class JsonHandler
{
public:
    typedef enum{
        COMMON = 0,
        SKINANALYSIS,
        HISKIN,
        SBS,
        PRODUCT,
        BEAUTYBOX,
        THIRDPARTY,
        NEWS,
        NODECOUNT
    } NODES;

    static JsonHandler* getInstance();
    bool setDoc(QJsonDocument doc);
    void setDocDefault(QJsonDocument doc) { m_docDefault = doc; }
    QString getLanguage();
    bool isSkinAgeEnabled();
    bool isHiSkinEnabled();
    bool isProductEnabled();
    bool isSBSEnabled();
    bool isBeautyBoxEnabled();
    bool isNewsEnabled();
    bool isAppsEnabled();
    bool isAlexaEnabled();
    QJsonObject getNode(NODES node);
    QJsonObject getDefaultNode(NODES node);

//    QString getScoreType();
//    QJsonArray getFactors();
//    bool isPhoneNameEnabled();
//    QJsonDocument getUpadtedDoc(QString lang, bool bHiskin, bool bProduct, bool bSkinage, QString scoreType, QStringList factors, bool bPhoneName);

private:
    bool parseDoc();

private:
    JsonHandler();
    static JsonHandler* mInstance ;
    QJsonDocument m_doc;
    QJsonDocument m_docDefault;
    QJsonObject m_objRoot;
    QJsonObject m_objCommon;
    QJsonObject m_objHiskin;
    QJsonObject m_objProducts;
    QJsonObject m_objSkinAnalysis;
    QJsonObject m_objSBS;
    QJsonObject m_objBeautyBox;
    QJsonObject m_objHome;
    QJsonObject m_objApps;
//    QJsonObject m_objViewScoreFilter;
//    QJsonObject m_objAll_scenario;
//    QJsonObject m_objMember_login;
};

#endif // JSONHANDLER_H
