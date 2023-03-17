#include "popup.h"
#include "ui_popup.h"

Popup::Popup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Popup)
{
    ui->setupUi(this);
}

Popup::Popup(QString message) :
    ui(new Ui::Popup)
{
    ui->setupUi(this);
    ui->popupText->setText(message);
}

Popup::~Popup()
{
    delete ui;
}

void Popup::on_exitButton_clicked()
{
    this->close();
}

