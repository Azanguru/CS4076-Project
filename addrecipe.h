#ifndef ADDRECIPE_H
#define ADDRECIPE_H

#include <QDialog>
#include "recipe.h"

namespace Ui {
class AddRecipe;
}

class AddRecipe : public QDialog
{
    Q_OBJECT

public:
    explicit AddRecipe(QWidget *parent = nullptr);
    AddRecipe(QVector<Recipe*> *allRecipes);
    ~AddRecipe();

private slots:

    void on_arConfirmCancel_clicked();

    void on_arFavourite_clicked();

private:
    Ui::AddRecipe *ui;
    QVector<Recipe*> *allRecipes;
    QString name;
    QString cuisine;
    QString instructions;
    QVector<Ingredient*> ingredientList;
    double totalCalories;
    double time;
    bool starred = false;
};

#endif // ADDRECIPE_H
