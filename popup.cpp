#include "popup.h"
#include "ui_popup.h"
#include "mainwindow.h"

Popup::Popup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Popup)
{
    ui->setupUi(this);
}

Popup::Popup(QString button1Text,  QString button2Text, QString message) :
    ui(new Ui::Popup)
{
    ui->setupUi(this);
    ui->button1->setText(button1Text);
    ui->button2->setText(button2Text);
    ui->popupText->setText(message);
}

Popup::Popup(QString buttonText, QString message) :
    ui(new Ui::Popup)
{
    ui->setupUi(this);
    ui->button2->setText(buttonText);
    ui->button1->setVisible(false);
    ui->popupText->setText(message);
}

Popup::~Popup()
{
    delete ui;
}

void Popup::on_button1_clicked()
{
    popupReturn = false;
    this->close();
}

void Popup::on_button2_clicked()
{
    popupReturn = true;
    this->close();
}
