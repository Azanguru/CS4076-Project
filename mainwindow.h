#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "ingredient.h"
#include "recipe.h"

extern bool popupReturn;

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

    void on_viewIngredientsButton_clicked();

    void on_viBack_clicked();

    void on_addRecipeButton_clicked();

    void on_actionSave_triggered();

    void on_actionDelete_triggered();

    void on_actionSave_Exit_triggered();

    void on_actionExit_triggered();

    void on_viewRecipesButton_clicked();

    void on_vrBack_clicked();

private:
    Ui::MainWindow *ui;
    QVector<Ingredient*> *allIngredients = new QVector<Ingredient*>;
    QVector<Recipe*> *allRecipes = new QVector<Recipe*>;

    void csvWrite();
    void csvRead();
    void processIngredient(QString line);
    void processRecipe(QString line);
    void viewIngredientsButtonPressed(int row, bool val);
    void viewRecipesButtonPressed(int row, int val);
};
#endif // MAINWINDOW_H
