#include "recipe.h"
#include "ingredient.h"

// Constructors
Recipe::Recipe(QObject *parent)
    : QObject{parent}
{

}

Recipe::Recipe(QString name, QVector<Ingredient*> ingredientList, QString instructions, double totalCalories, int time, QString cuisine,
               bool starred = false)
{
    thisName = name;
    thisCuisine = cuisine;
    thisInstructions = instructions;
    this->ingredientList = ingredientList;
    this->time = time;
    this->totalCalories = totalCalories;
    this->starred = starred;
}

Recipe::Recipe(QString name, QVector<Ingredient*> ingredientList, QString instructions, int time, QString cuisine, bool starred)
    : Recipe(name, ingredientList, instructions, 0, time, cuisine, starred)
{
    totalCalories = calorieCalc();
}

Recipe::Recipe(QString name, QVector<Ingredient*> ingredientList, QString instructions, int time, bool starred)
    : Recipe(name, ingredientList, instructions, time, "Unspecified", starred) {}

//Overloaded Operators
QTextStream & operator<<(QTextStream &textStream, Recipe *recipe)
{
    int numberOfIngredients = recipe->getIngredientList().size();
    textStream << recipe->getName() << ",";
    textStream << recipe->getCuisine() << ",";
    textStream << recipe->getInstructions() << ",";
    textStream << recipe->getTotalCalories() << ",";
    textStream << recipe->getTime() << ",";
    textStream << (int)(recipe->getStarred()) << ",";
    textStream << numberOfIngredients << ",";
    for (int j = 0; j < numberOfIngredients; j++)
    {
        textStream << recipe->getIngredientList().at(j);
    }

    return textStream;
}

QTextStream & operator<<(QTextStream &textStream, Recipe &recipe)
{
    int numberOfIngredients = recipe.getIngredientList().size();
    textStream << recipe.getName() << ",";
    textStream << recipe.getCuisine() << ",";
    textStream << recipe.getInstructions() << ",";
    textStream << recipe.getTotalCalories() << ",";
    textStream << recipe.getTime() << ",";
    textStream << (int)(recipe.getStarred()) << ",";
    textStream << numberOfIngredients << ",";
    for (int j = 0; j < numberOfIngredients; j++)
    {
        textStream << recipe.getIngredientList().at(j) << ",";
    }

    return textStream;
}

// Getters and Setters
QString Recipe::getName() const { return name; }

QString Recipe::getCuisine() const { return cuisine; }

QString Recipe::getInstructions() const { return instructions; }

QVector<Ingredient*> Recipe::getIngredientList() const { return ingredientList; }

double Recipe::getTotalCalories() const { return totalCalories; }

int Recipe::getTime() const { return time; }

bool Recipe::getStarred() const { return starred; }

void Recipe::setName(QString name) { this->name = name; }

void Recipe::setCuisine(QString cuisine) { this->name = name; }

void Recipe::setInstructions(QString instructions) { this->instructions = instructions; }

void Recipe::setIngredientList(QVector<Ingredient*> ingredientList) { this->ingredientList = ingredientList; }

void Recipe::setTime(int time) { this->time = time; }

void Recipe::setStarred(bool starred) { this->starred = starred; }

void Recipe::resetCalories() { totalCalories = calorieCalc(); }

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
