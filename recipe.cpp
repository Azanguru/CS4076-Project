#include "recipe.h"
#include "ingredient.h"

Recipe::Recipe(QObject *parent)
    : QObject{parent}
{

}

Recipe::Recipe(QString name, QVector<Ingredient> ingredientList, QString instructions, double time, QString cuisine)
{
    this->name = name;
    this->cuisine = cuisine;
    this->instructions = instructions;
    this->ingredientList = ingredientList;
    this->time = time;
    totalCalories = calorieCalc();
}

Recipe::Recipe(QString name, QVector<Ingredient> ingredientList, QString instructions, double time)
{
    Recipe(name, ingredientList, instructions, time, "Unspecified");
}

Recipe::Recipe(QString name, QVector<Ingredient> ingredientList, QString instructions)
{
    Recipe(name, ingredientList, instructions, 0, "Unspecified");
}

Recipe::Recipe(QString name, QVector<Ingredient> ingredientList, double time)
{
    Recipe(name, ingredientList, "", time, "Unspecified");
}

Recipe::Recipe(QString name, QVector<Ingredient> ingredientList)
{
    Recipe(name, ingredientList, "", 0, "Unspecified");
}

// Getters and Setters
QString Recipe::getName() { return name; }

QString Recipe::getCuisine() { return cuisine; }

QString Recipe::getInstructions() { return instructions; }

QVector<Ingredient> Recipe::getIngredientList() { return ingredientList; }

double Recipe::getTotalCalories() { return totalCalories; }

double Recipe::getTime() { return time; }

void Recipe::setName(QString name) { this->name = name; }

void Recipe::setCuisine(QString cuisine) { this->name = name; }

void Recipe::setInstructions(QString instructions) { this->instructions = instructions; }

void Recipe::setIngredientList(QVector<Ingredient> ingredientList) { this->ingredientList = ingredientList; }

void Recipe::setTime(double time) { this->time = time; }


double Recipe::calorieCalc() // Private method to calculate the amount of calories in a recipe according to the ingredients
{
    double total = 0;
    for (int i = 0; i < ingredientList.size(); i++)
    {
        Ingredient in = ingredientList[i];
        total = total + in.getCaloricValue() * in.getAmount();
    }
    return total;
}