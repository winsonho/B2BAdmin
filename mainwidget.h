#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "common.h"
#include <QWidget>
#include <QButtonGroup>
#include <QRadioButton>
#include <QModelIndex>
#include <QTableView>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include "newaccountwidget.h"
#include "qrcodewidget.h"
#include "channelprofile.h"
#include <QElapsedTimer>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

public slots:
    void customMenuRequested(QPoint pos);


private slots:
    void onHiddenClicked();
    void onConnectClicked();
    void onNewClicked();
    void onChannelSelected(QModelIndex index);
    void onDelete();

private:
    void showErrorDialog(QString str);
    bool deleteRecord(QString id, QString account);

private:
    Ui::MainWidget *ui;
    QTableView *mTvChannel;
    QSqlDatabase mDB;
    QPushButton *mBtnHidden;
    QSqlQueryModel *m_Model;
    QButtonGroup *mHostGroup;
    QRadioButton *mRbDev;
    QRadioButton *mRbBeta;
    QRadioButton *mRbPR;
    NewAccountWidget mNewView;
    QElapsedTimer mStartTime;
    int mClickCount;
    bool mHiddenON;
};

#endif // MAINWIDGET_H
