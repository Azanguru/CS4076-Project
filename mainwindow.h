#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "ingredient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addIngredientButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<Ingredient*> *allIngredients = new QVector<Ingredient*>;
};
#endif // MAINWINDOW_H
