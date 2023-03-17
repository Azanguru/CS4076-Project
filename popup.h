#ifndef POPUP_H
#define POPUP_H

#include <QDialog>

namespace Ui {
class Popup;
}

class Popup : public QDialog
{
    Q_OBJECT

public:
    explicit Popup(QWidget *parent = nullptr);
    Popup(QString message);
    ~Popup();

private slots:
    void on_exitButton_clicked();

private:
    Ui::Popup *ui;
};

#endif // POPUP_H
