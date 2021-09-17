#ifndef DIALOGEDITJSON_H
#define DIALOGEDITJSON_H

#include <QDialog>

namespace Ui {
class DialogEditJson;
}

class DialogEditJson : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditJson(QWidget *parent = nullptr);
    ~DialogEditJson();
    void setJson(QByteArray json);
    QByteArray getJson();

private slots:
    void onOKClicked(bool);

private:
    Ui::DialogEditJson *ui;
};

#endif // DIALOGEDITJSON_H
