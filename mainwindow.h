#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "ingredient.h"
#include "recipe.h"

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

    void on_exitButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<Ingredient*> *allIngredients = new QVector<Ingredient*>;
    QVector<Recipe*> *allRecipes = new QVector<Recipe*>;

    void csvWrite();
    void csvRead();
    void processIngredient(QString line);
    void processRecipe(QString line);
};
#endif // MAINWINDOW_H
