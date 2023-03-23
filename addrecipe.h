#ifndef ADDRECIPE_H
#define ADDRECIPE_H

#include <QDialog>
#include <QComboBox>
#include "recipe.h"

namespace Ui {
class AddRecipe;
}

class AddRecipe : public QDialog
{
    Q_OBJECT

public:
    explicit AddRecipe(QWidget *parent = nullptr);
    AddRecipe(QVector<Recipe*> *allRecipes, QVector <Ingredient*> *allIngredients);
    AddRecipe(QVector<Recipe*> *allRecipes, QVector <Ingredient*> *allIngredients, Recipe* editRec, bool editing, int pos);
    ~AddRecipe();

public slots:
    void ingredientSelected(int);

    void ingredientAmountChanged(double);

private slots:

    void on_arConfirmCancel_clicked();

    void on_arFavourite_clicked();

    void on_arIngAddSlot_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_arCuisineEnter_textChanged(const QString &arg1);

    void on_arTimeEnter_valueChanged(int arg1);

    void on_arConfirmAdd_clicked();

private:
    Ui::AddRecipe *ui;
    QVector<Recipe*> *allRecipes;
    QVector<Ingredient*> *allIngredients;
    QString name;
    QString cuisine;
    QString instructions;
    QVector<Ingredient*> ingredientList;
    int time;
    bool starred = false;
    Recipe *editRec;
    bool editing = false;
    int pos;
};

#endif // ADDRECIPE_H
