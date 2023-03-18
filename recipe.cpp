#include "recipe.h"
#include "ingredient.h"

Recipe::Recipe(QObject *parent)
    : QObject{parent}
{

}

Recipe::Recipe(QString name, QVector<Ingredient*> ingredientList, QString instructions, double totalCalories, double time, QString cuisine,
               bool starred = false)
{
    this->name = name;
    this->cuisine = cuisine;
    this->instructions = instructions;
    this->ingredientList = ingredientList;
    this->time = time;
    this->totalCalories = totalCalories;
    this->starred = starred;
}

Recipe::Recipe(QString name, QVector<Ingredient*> ingredientList, QString instructions, double time, QString cuisine)
{
//    this->name = name;
//    this->cuisine = cuisine;
//    this->instructions = instructions;
//    this->ingredientList = ingredientList;
//    this->time = time;
    totalCalories = calorieCalc();
    Recipe(name, ingredientList, instructions, totalCalories, time, cuisine);
}

// Constructors
Recipe::Recipe(QString name, QVector<Ingredient*> ingredientList, QString instructions, double time)
{
    Recipe(name, ingredientList, instructions, time, "Unspecified");
}

Recipe::Recipe(QString name, QVector<Ingredient*> ingredientList, QString instructions)
{
    Recipe(name, ingredientList, instructions, 0, "Unspecified");
}

Recipe::Recipe(QString name, QVector<Ingredient*> ingredientList, double time)
{
    Recipe(name, ingredientList, "", time, "Unspecified");
}

Recipe::Recipe(QString name, QVector<Ingredient*> ingredientList)
{
    Recipe(name, ingredientList, "", 0, "Unspecified");
}

// Getters and Setters
QString Recipe::getName() const { return name; }

QString Recipe::getCuisine() const { return cuisine; }

QString Recipe::getInstructions() const { return instructions; }

QVector<Ingredient*> Recipe::getIngredientList() const { return ingredientList; }

double Recipe::getTotalCalories() const { return totalCalories; }

double Recipe::getTime() const { return time; }

bool Recipe::getStarred() const { return starred; }

void Recipe::setName(QString name) { this->name = name; }

void Recipe::setCuisine(QString cuisine) { this->name = name; }

void Recipe::setInstructions(QString instructions) { this->instructions = instructions; }

void Recipe::setIngredientList(QVector<Ingredient*> ingredientList) { this->ingredientList = ingredientList; }

void Recipe::setTime(double time) { this->time = time; }

void Recipe::setStarred(bool starred) { this->starred = starred; }


double Recipe::calorieCalc() // Private method to calculate the amount of calories in a recipe according to the ingredients
{
    double total = 0;
    for (int i = 0; i < ingredientList.size(); i++)
    {
        Ingredient *in = ingredientList[i];
        total = total + in->getCaloricValue() * in->getAmount();
    }
    return total;
}
