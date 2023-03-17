#ifndef RECIPE_H
#define RECIPE_H

#include <QObject>
#include "ingredient.h"

class Recipe : public QObject
{
    Q_OBJECT

private:
    QString name;
    QString cuisine;
    QString instructions;
    QVector<Ingredient> ingredientList;
    double totalCalories;
    double time;

    double calorieCalc();

public:
    explicit Recipe(QObject *parent = nullptr);
    Recipe(QString name, QVector<Ingredient>, QString instructions, double time, QString cuisine);
    Recipe(QString name, QVector<Ingredient>, QString instructions, double time);
    Recipe(QString name, QVector<Ingredient>, QString instructions);
    Recipe(QString name, QVector<Ingredient>, double time);
    Recipe(QString name, QVector<Ingredient>);

    void setName(QString name);
    void setCuisine(QString cuisine);
    void setIngredientList(QVector<Ingredient>);
    void setTotalCalories(double totalCalories);
    void setTime(double time);
    void setInstructions(QString instructions);

    QString getName();
    QString getCuisine();
    QString getInstructions();
    QVector<Ingredient> getIngredientList();
    double getTotalCalories();
    double getTime();

signals:

};

#endif // RECIPE_H
