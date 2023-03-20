#ifndef POPUP_H
#define POPUP_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class Popup;
}

class Popup : public QDialog
{
    Q_OBJECT

public:
    explicit Popup(QWidget *parent = nullptr);
    Popup(QString button1Text, QString button2Text, QString message);
    Popup(QString buttonText, QString message);
    ~Popup();

private slots:
    void on_button1_clicked();

    void on_button2_clicked();

private:
    Ui::Popup *ui;
};

#endif // POPUP_H
