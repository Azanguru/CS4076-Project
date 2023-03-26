#include "popup.h"
#include "ui_popup.h"
#include "mainwindow.h"

#define BUTTON_1_PRESSED false
#define BUTTON_2_PRESSED true

Popup::Popup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Popup)
{
    ui->setupUi(this);
}

Popup::Popup(const QString &button1Text, const QString &button2Text, const QString &message) :
    ui(new Ui::Popup)
{
    ui->setupUi(this);
    ui->button1->setText(button1Text);
    ui->button2->setText(button2Text);
    ui->popupText->setText(message);
}

Popup::Popup(const QString &buttonText, const QString &message) :
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
    popupReturn = BUTTON_1_PRESSED;
    this->close();
}

void Popup::on_button2_clicked()
{
    popupReturn = BUTTON_2_PRESSED;
    this->close();
}
