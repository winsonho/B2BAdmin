#include "qrcodewidget.h"
#include "common.h"
#include "ui_qrcodewidget.h"
#include <QPixmap>
#include <QFileDialog>

QRCodeWidget::QRCodeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QRCodeWidget)
{
    ui->setupUi(this);
    m_QRcode = ui->QRCode;
    m_btnSave = ui->btnSave;
    connect(m_btnSave, SIGNAL(clicked()), this, SLOT(onSaveClicked()));
}

QRCodeWidget::~QRCodeWidget()
{
    delete ui;
}

void QRCodeWidget::setImage(QImage image)
{
    m_Image = image;
    m_QRcode->setPixmap(QPixmap::fromImage(image));
}

void QRCodeWidget::onSaveClicked()
{
    QString imagePath = QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                "",
                tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" )
                );

    qDebug() << imagePath;

    if (ui->widget->grab().save(imagePath))
        close();
}

void QRCodeWidget::setDescription(QString desc)
{
    ui->title->setText(desc);
}
