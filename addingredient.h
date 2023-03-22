#ifndef ADDINGREDIENT_H
#define ADDINGREDIENT_H

#include <QDialog>
#include <QVector>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QRadioButton>

#include "ingredient.h"

namespace Ui {
class AddIngredient;
}

class AddIngredient : public QDialog
{
    Q_OBJECT

public:
    explicit AddIngredient(QWidget *parent = nullptr);
    AddIngredient(QVector<Ingredient*> *allIngredients);
    AddIngredient(QVector<Ingredient*> *allIngredients, Ingredient *editIng, bool editing, int pos);
    ~AddIngredient();

private slots:
    void on_cancelButton_clicked();

    void on_addButton_clicked();

    void on_enterName_textChanged(const QString &arg1);

    void on_enterCalories_valueChanged(double arg1);

    void on_enterMeasurementGrams_toggled(bool checked);

    void on_enterMeasurementMillilitres_toggled(bool checked);

private:
    Ui::AddIngredient *ui;
    QString ingredientName;
    double ingredientCalories = 0.0;
    bool ingredientInGrams = true;
    QVector<Ingredient*> *allIngredients;
    Ingredient *editIng;
    bool editing = false;
    int pos;
};

#endif // ADDINGREDIENT_H
