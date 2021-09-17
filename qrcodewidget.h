#ifndef QRCODEWIDGET_H
#define QRCODEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QImage>

namespace Ui {
class QRCodeWidget;
}

class QRCodeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QRCodeWidget(QWidget *parent = nullptr);
    void setImage(QImage image);
    void setDescription(QString desc) ;
    ~QRCodeWidget();

private slots:
    void onSaveClicked();

private:
    Ui::QRCodeWidget *ui;
    QImage m_Image;
    QLabel* m_QRcode;
    QPushButton* m_btnSave;
};

#endif // QRCODEWIDGET_H
