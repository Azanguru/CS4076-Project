#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <QObject>

class Ingredient : public QObject
{
    Q_OBJECT

private:
    QString name;
    double caloricValue;
    double amount;
    bool measureInGrams;

public:
    explicit Ingredient(QObject *parent = nullptr);
    Ingredient(const Ingredient& ing);
    Ingredient(QString name, double calories, double amount, bool measureInGrams);

    void setName(QString newName);
    void setCaloricValue(double calories);
    void setAmount(double grams);
    void setMeasurement(bool measurement);

    QString getName();
    double getCaloricValue();
    double getAmount();
    bool measuredInGrams();

signals:

};

#endif // INGREDIENT_H
