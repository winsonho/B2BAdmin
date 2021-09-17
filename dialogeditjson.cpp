#include "dialogeditjson.h"
#include "ui_dialogeditjson.h"
#include <QJsonDocument>
#include <QMessageBox>

DialogEditJson::DialogEditJson(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditJson)
{
    ui->setupUi(this);
    connect(ui->btnOK, SIGNAL(clicked(bool)), this, SLOT(onOKClicked(bool)));
    connect(ui->btnCancel, SIGNAL(clicked(bool)), this, SLOT(close()));
}

DialogEditJson::~DialogEditJson()
{
    delete ui;
}

void DialogEditJson::onOKClicked(bool)
{
    QJsonParseError e;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(ui->txtJson->toPlainText().toUtf8(), &e);

    if(e.error == QJsonParseError::NoError && !jsonDoc.isNull())
    {
        accept();
    }
    else
    {
        QMessageBox::critical(NULL, "Error", "Json format error !!", QMessageBox::Close);
    }
}

void DialogEditJson::setJson(QByteArray json)
{
    ui->txtJson->setPlainText(json);
}

QByteArray DialogEditJson::getJson()
{
   return ui->txtJson->toPlainText().toUtf8();
}
