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
    Popup(const QString &button1Text, const QString &button2Text, const QString &message);
    Popup(const QString &buttonText, const QString &message);
    ~Popup();

private slots:
    void on_button1_clicked();

    void on_button2_clicked();

private:
    Ui::Popup *ui;
};

#endif // POPUP_H
