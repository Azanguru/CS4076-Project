#include "ingredient.h"

Ingredient::Ingredient(QObject *parent)
    : QObject{parent}
{

}

Ingredient::Ingredient(QString name, double calories, double amount, bool measureInGrams)
{
    this->name = name;
    caloricValue = calories / 100;
    this->amount = amount;
    this->measureInGrams = measureInGrams;
}

Ingredient::Ingredient(const Ingredient& ing) : name(ing.name), caloricValue(ing.caloricValue), amount(ing.amount), measureInGrams(ing.measureInGrams) {}

QString Ingredient::getName()
{
    return name;
}

void Ingredient::setName(QString newName)
{
    name = newName;
}

double Ingredient::getCaloricValue()
{
    return caloricValue;
}

void Ingredient::setCaloricValue(double calories)
{
    caloricValue = calories / 100;
}

double Ingredient::getAmount()
{
    return amount;
}

void Ingredient::setAmount(double grams)
{
    amount = grams;
}

bool Ingredient::measuredInGrams()
{
    return measureInGrams;
}

void Ingredient::setMeasurement(bool measurement)
{
    measureInGrams = measurement;
}
