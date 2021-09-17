#ifndef COMMON_H
#define COMMON_H
#include <QDebug>

typedef enum {
    DEV = 0,
    BETA,
    PR,
    HOSTCOUNT
} HOST;

typedef enum {
    BLACKSPOT = 0,
    DARKCIRCLE,
    FINE,
    PORE,
    TEXTURE,
    WRINKLE,
    ACNE,
    SKINCOLOR,
    INTENSITY,
    SENSITIVEZONE,
    STAINSTAGE,
    DARKCIRCLEGRAYSCALE,
    FOURV,
    FACTORSCOUNT
} FACTORS;

typedef enum {
    HYDRATION = 0,
    PIGMENTATION,
    HISKINFACTORSCOUNT
} HISKINFACTORS;

typedef enum {
    WEIGHT = 0,
    BMI,
    BMR,
    BONE_DENSITY,
    BWR,
    MMR,
    PDF,
    VF,
    SBSFACTORSCOUNT
} SBSFACTORS;

typedef enum {
    EN_US,
    ZH_TW,
    ZH_CN,
    ZH_HK,
    TH_TH,
    MS_MY,
    ID_ID,
    JA_JP,
    KO_KR,
    RU_RU,
    LANGUAGESCOUNT
} LANGUAGES;

typedef enum {
    EMAIL,
    PHONE,
    XIAOMI,
    LOGINTYPESCOUNT
} MEMBERLOGINTYPES;

typedef enum {
    ID_PHONE,
    ID_KEY,
    ID_EMAIL,
    ID_RANDOM,
    MEMBERIDTYPECOUNT
} MEMBERIDTYPES;


typedef enum {
    ONCE = 0,
    EVERYTIME,
    NO,
    SHOWTYPESCOUNT
} SHOWTYPES;

typedef enum {
    STANDARD = 0,
    BBYC,
    FLOWTYPESCOUNT
} FLOWTYPES;

typedef enum {
    QRCODE = 0,
    REPORTTYPESCOUNT
} REPORTTYPES;

typedef enum {
    ADMIN_ACCESS = 0,
    STANDARD_ACCESS,
    GUEST_ACCESS,
    ACCESSLEVELSCOUNT
} ACCESSLEVELS;

// to define is Global or China server
#define GLOBAL_SITE

#endif // COMMON_H
