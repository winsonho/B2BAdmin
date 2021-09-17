#ifndef MYSTYLESHEET_H
#define MYSTYLESHEET_H
#include <QString>
QString myStyleSheet = " \
        QComboBox { \
        border: 1px solid gray; \
        border-radius: 3px; \
        padding: 1px 18px 1px 3px; \
        min-width: 6em; \
        font-size: 20pt; \
    } \
     \
    QComboBox:!editable { \
        selection-background-color: blue; \
    } \
     \
    QWidget { \
        background-color: #333333; \
        color: #fffff8; \
    } \
     \
    QTableWidget { \
        gridline-color: #fffff8; \
        font-size: 18pt; \
    } \
     \
    QTableWidget QTableCornerButton::section { \
        background-color: #646464; \
        border: 1px solid #fffff8; \
    } \
     \
    QHeaderView::section { \
        background-color: #646464; \
        padding: 4px; \
        font-size: 18pt; \
        border-style: none; \
        border-bottom: 1px solid #fffff8; \
        border-right: 1px solid #fffff8; \
    } \
     \
    QHeaderView::section:horizontal \
    { \
        border-top: 1px solid #fffff8; \
    } \
     \
    QHeaderView::section:vertical \
    { \
        border-left: 1px solid #fffff8; \
    } \
     \
    QGroupBox { \
        background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, \
                                          stop: 0 #E0E0E0, stop: 1 #FFFFFF); \
        border: 2px solid gray; \
        border-radius: 5px; \
        margin-top: 1ex; \
    } \
     \
    QPushButton { \
        background-color: red; \
        border-style: outset; \
        border-width: 2px; \
        border-radius: 10px; \
        border-color: beige; \
        font: bold 18px; \
        padding: 6px; \
    } \
     \
    QPushButton:pressed { \
        background-color: rgb(224, 0, 0); \
        border-style: inset; \
    } \
     \
    QCheckBox { \
        spacing: 5px;   \
    } \
      \
    QCheckBox::indicator { \
        width: 30px; \
        height: 30px; \
    } \
     \
    QCheckBox::indicator:unchecked { \
        image: url(:/images/ic_checkbox_uncheck.png); \
    } \
     \
    QCheckBox::indicator:checked { \
        image: url(:/images/ic_checkbox_check.png); \
    } \
     \
    QCheckBox::indicator:disabled { \
        background-color: gray; \
    } \
     \
    QRadioButton { \
        spacing: 5px; \
        font-size: 20px; \
        color: rgb(24, 220, 88); \
    } \
      \
    QRadioButton::indicator { \
        width: 30px; \
        height: 30px \
    } \
     \
    QRadioButton::indicator:checked { \
        image: url(:/images/icon_face_recognition_ok.png); \
    } \
      \
    QRadioButton::indicator:unchecked { \
        image: url(:/images/icon_face_recognition_not_ok.png); \
    } \
     \
    QTabBar::tab:selected, QTabBar::tab:hover { \
       color::#618BE5; \
       background:red; \
    } \
     \
    ";

QString myChinaStyleSheet = " \
        QComboBox { \
        border: 1px solid gray; \
        border-radius: 3px; \
        padding: 1px 18px 1px 3px; \
        min-width: 6em; \
        font-size: 20pt; \
    } \
     \
    QComboBox:!editable { \
        selection-background-color: blue; \
    } \
     \
    QWidget { \
        background-color: #fffff8; \
        color: #333333; \
    } \
     \
    QTableWidget { \
        gridline-color: #fffff8; \
        font-size: 18pt; \
    } \
     \
    QTableWidget QTableCornerButton::section { \
        background-color: #646464; \
        border: 1px solid #fffff8; \
    } \
     \
    QHeaderView::section { \
        background-color: #646464; \
        padding: 4px; \
        font-size: 18pt; \
        border-style: none; \
        border-bottom: 1px solid #fffff8; \
        border-right: 1px solid #fffff8; \
    } \
     \
    QHeaderView::section:horizontal \
    { \
        border-top: 1px solid #fffff8; \
    } \
     \
    QHeaderView::section:vertical \
    { \
        border-left: 1px solid #fffff8; \
    } \
     \
    QGroupBox { \
        background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, \
                                          stop: 0 #E0E0E0, stop: 1 #FFFFFF); \
        border: 2px solid gray; \
        border-radius: 5px; \
        margin-top: 1ex; \
    } \
     \
    QPushButton { \
        background-color: red; \
        border-style: outset; \
        border-width: 2px; \
        border-radius: 10px; \
        border-color: beige; \
        font: bold 18px; \
        padding: 6px; \
    } \
     \
    QPushButton:pressed { \
        background-color: rgb(224, 0, 0); \
        border-style: inset; \
    } \
     \
    QCheckBox { \
        spacing: 5px;   \
    } \
      \
    QCheckBox::indicator { \
        width: 30px; \
        height: 30px; \
    } \
     \
    QCheckBox::indicator:unchecked { \
        image: url(:/images/ic_checkbox_uncheck.png); \
    } \
     \
    QCheckBox::indicator:checked { \
        image: url(:/images/ic_checkbox_check.png); \
    } \
     \
    QCheckBox::indicator:disabled { \
        background-color: gray; \
    } \
     \
    QRadioButton { \
        spacing: 5px; \
        font-size: 20px; \
        color: rgb(24, 220, 88); \
    } \
      \
    QRadioButton::indicator { \
        width: 30px; \
        height: 30px \
    } \
     \
    QRadioButton::indicator:checked { \
        image: url(:/images/icon_face_recognition_ok.png); \
    } \
      \
    QRadioButton::indicator:unchecked { \
        image: url(:/images/icon_face_recognition_not_ok.png); \
    } \
     \
    ";

#endif // MYSTYLESHEET_H
