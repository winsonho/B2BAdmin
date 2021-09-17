#include "jsonhandler.h"


JsonHandler* JsonHandler::mInstance = 0;

JsonHandler::JsonHandler()
{

}

JsonHandler* JsonHandler::getInstance()
{
    if (mInstance == 0)
    {
        mInstance = new JsonHandler() ;
    }
    return mInstance ;
}

bool JsonHandler::setDoc(QJsonDocument doc)
{
    m_doc = doc;
    return parseDoc();
}

bool JsonHandler::parseDoc()
{
    m_objRoot = m_doc.object();
    m_objCommon = m_objRoot["common"].toObject();
    m_objHiskin = m_objRoot["hiskin"].toObject();
    m_objProducts = m_objRoot["products"].toObject();
    m_objSkinAnalysis = m_objRoot["skin_analysis"].toObject();
    m_objSBS = m_objRoot["sbs"].toObject();
    m_objBeautyBox = m_objRoot["beauty_box"].toObject();
    m_objHome = m_objRoot["home"].toObject();
    m_objApps = m_objHome["thirdparty_apps"].toObject();

//    m_objViewScoreFilter = m_objSkinAnalysis["view_score_filter"].toObject();
//    m_objAll_scenario = m_objViewScoreFilter["all_scenario"].toObject();
//    m_objMember_login = m_objSkinAnalysis["member_login"].toObject();
    return true;
}

QString JsonHandler::getLanguage()
{
    return m_objCommon["language"].toString();
}

bool JsonHandler::isSkinAgeEnabled()
{
    bool ret = false;
    if (!m_objSkinAnalysis.isEmpty())
    {
        ret = m_objSkinAnalysis["skinage_is_enable"].toBool();
    }
    qDebug() << "Skin Age isenabled: " << ret;
    return ret ;
}

bool JsonHandler::isHiSkinEnabled()
{
    bool ret = false;
    if (!m_objHiskin.isEmpty())
    {
        ret = !m_objHiskin.isEmpty();
    }
    qDebug() << "HiSkin is enabled: " << ret;
    return ret ;
}

bool JsonHandler::isProductEnabled()
{
    bool ret = false;
    if (!m_objProducts.isEmpty())
    {
        ret = !m_objProducts.isEmpty();
    }
    qDebug() << "Products is enabled: " << ret;
    return ret ;
}

bool JsonHandler::isSBSEnabled()
{
    bool ret = false;
    if (!m_objSBS.isEmpty())
    {
        ret = !m_objSBS.isEmpty();
    }
    qDebug() << "SBS is enabled: " << ret;
    return ret ;
}

bool JsonHandler::isBeautyBoxEnabled()
{
//    bool ret = false;
//    if (m_objBeautyBox.)
//    {
//        ret = !m_objBeautyBox.isEmpty();
//    }
//    qDebug() << "BeautyBox is enabled: " << ret;
//    return ret ;
    return m_objRoot["beauty_box"].isObject();
}

bool JsonHandler::isNewsEnabled()
{
    bool ret = false;
    if (m_objCommon["news"].toArray().size() > 0)
    {
        ret = true;
    }
    qDebug() << "News is enabled: " << ret;
    return ret ;
}

bool JsonHandler::isAppsEnabled()
{
    bool ret = false;

    if (!m_objApps.isEmpty())
    {
        ret = !m_objApps.isEmpty();
    }
    qDebug() << "3rd party Apps is enabled: " << ret;
    return ret ;
}

bool JsonHandler::isAlexaEnabled()
{
    bool ret = m_objCommon["alexa_is_enable"].toBool();
//    if (m_objCommon["alexa_is_enable"].toBool())
//    {

//    }
    qDebug() << "Alexa is enabled: " << ret;
    return ret ;
}


QJsonObject JsonHandler::getNode(NODES node)
{

    QJsonObject obj = QJsonObject();
    switch(node) {
        case COMMON:
            obj = m_objCommon;
            break;
        case SKINANALYSIS:
            obj = m_objSkinAnalysis;
            break;
        case HISKIN:
            obj = m_objHiskin;
            break;
        case SBS:
            obj = m_objSBS;
            break;
        case PRODUCT:
            obj = m_objProducts;
            break;
        case BEAUTYBOX:
            obj = m_objBeautyBox;
            break;
        case THIRDPARTY:
            obj = m_objApps;
            break;
        case NEWS:
            obj = m_objCommon["news"].toObject();
            break;
        default:
            qDebug() << "Wrong node type : " << node;
            break;
    }
    return obj;
}

QJsonObject JsonHandler::getDefaultNode(NODES node)
{
//    m_objRoot = m_doc.object();
//    m_objCommon = m_objRoot["common"].toObject();
//    m_objHiskin = m_objRoot["hiskin"].toObject();
//    m_objProducts = m_objRoot["products"].toObject();
//    m_objSkinAnalysis = m_objRoot["skin_analysis"].toObject();
//    m_objSBS = m_objRoot["sbs"].toObject();
//    m_objBeautyBox = m_objRoot["beauty_box"].toObject();
//    m_objApps = m_objRoot["thirdparty_apps"].toObject();

    QJsonObject objRoot = m_docDefault.object();
    QJsonObject obj = QJsonObject();

    switch(node) {
        case COMMON:
            obj = objRoot["common"].toObject();
            break;
        case SKINANALYSIS:
            obj = objRoot["skin_analysis"].toObject();
            break;
        case HISKIN:
            obj = objRoot["hiskin"].toObject();
            break;
        case SBS:
            obj = objRoot["sbs"].toObject();
            break;
        case PRODUCT:
            obj = objRoot["products"].toObject();
            break;
        case BEAUTYBOX:
            obj = objRoot["beauty_box"].toObject();
            break;
        case THIRDPARTY:
            obj = objRoot["home"].toObject()["thirdparty_apps"].toObject();
            break;
        case NEWS:
            obj = objRoot["common"].toObject()["news"].toObject();
            break;
        default:
            qDebug() << "Wrong node type : " << node;
            break;
    }
    return obj;
}


//QString JsonHandler::getScoreType()
//{
//    QString str;

//    if(!m_objAll_scenario.isEmpty())
//    {
//        str = m_objAll_scenario["type"].toString();
//    }

//    qDebug() << "Score type : " << str;
//    return str;
//}

//QJsonArray JsonHandler::getFactors()
//{
//    QJsonArray arr;

//    if(!m_objSkinAnalysis.isEmpty())
//    {
//        arr = m_objSkinAnalysis["detected_factor"].toArray();
//    }

//    qDebug() << "Skin analysis detected factors : " << arr;
//    return arr;
//}

//bool JsonHandler::isPhoneNameEnabled()
//{
//    bool ret = false;
//    if (!m_objMember_login.isEmpty())
//    {
//        ret = m_objMember_login["info_columns"].toObject()["login_key"].toBool();
//    }

//    qDebug() << "User profile phone and name is enabled: " << ret;
//    return ret;
//}

//QJsonDocument JsonHandler::getUpadtedDoc(QString lang, bool bHiskin, bool bProduct, bool bSkinage, QString scoreType, QStringList factors, bool bPhoneName)
//{
//    QJsonObject root = m_docDefault.object();
//    QJsonObject hiskin = root["hiskin"].toObject();
//    QJsonObject product = root["products"].toObject();

//    m_objCommon["language"] = lang;
//    m_objRoot["common"] = m_objCommon;

//    if (!bHiskin)
//    {
//        m_objHiskin = QJsonObject();
//    }
//    else
//    {
//        if (m_objHiskin.isEmpty())
//            m_objHiskin = hiskin;

//        // user profile for hiskin
//        QJsonObject member_login = m_objHiskin["member_login"].toObject();
//        QJsonObject info = member_login["info_columns"].toObject();

//        info["login_key"] = bPhoneName;
//        info["name"] = bPhoneName;

//        member_login["info_columns"] = info;
//        m_objHiskin["member_login"] = member_login;
//    }
//    m_objRoot["hiskin"] = m_objHiskin;

//    if (!bProduct)
//    {
//        m_objProducts = QJsonObject();
//    }
//    else
//    {
//        if (m_objProducts.isEmpty())
//            m_objProducts = product;
//    }
//    m_objRoot["products"] = m_objProducts;

//    m_objSkinAnalysis["skinage_is_enable"] = bSkinage;

//    m_objAll_scenario["type"] = scoreType;

//    m_objViewScoreFilter["all_scenario"] = m_objAll_scenario;
//    m_objSkinAnalysis["view_score_filter"] = m_objViewScoreFilter;

//    QJsonObject info = m_objMember_login["info_columns"].toObject();
//    info["login_key"] = bPhoneName;
//    info["name"] = bPhoneName;

//    m_objMember_login["info_columns"] = info;
//    m_objSkinAnalysis["member_login"] = m_objMember_login;

//    QJsonArray arr;
//    for(int i=0; i<factors.size(); i++)
//        arr.append(QJsonValue(factors[i]));

//    m_objSkinAnalysis["detected_factor"] = arr;

//    m_objRoot["skin_analysis"] = m_objSkinAnalysis;

//    QJsonDocument doc(m_objRoot);
//    return doc;
//}
