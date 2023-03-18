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
    QVector<Ingredient*> ingredientList;
    double totalCalories;
    double time;
    bool starred;

    double calorieCalc();

public:
    explicit Recipe(QObject *parent = nullptr);
    Recipe(QString name, QVector<Ingredient*>, QString instructions, double totalCalories, double time, QString cuisine, bool starred);
    Recipe(QString name, QVector<Ingredient*>, QString instructions, double time, QString cuisine);
    Recipe(QString name, QVector<Ingredient*>, QString instructions, double time);
    Recipe(QString name, QVector<Ingredient*>, QString instructions);
    Recipe(QString name, QVector<Ingredient*>, double time);
    Recipe(QString name, QVector<Ingredient*>);

    void setName(QString name);
    void setCuisine(QString cuisine);
    void setIngredientList(QVector<Ingredient*>);
    void setTotalCalories(double totalCalories);
    void setTime(double time);
    void setInstructions(QString instructions);
    void setStarred(bool starred);

    QString getName() const;
    QString getCuisine() const;
    QString getInstructions() const;
    QVector<Ingredient*> getIngredientList() const;
    double getTotalCalories() const;
    double getTime() const;
    bool getStarred() const;

signals:

};

#endif // RECIPE_H
