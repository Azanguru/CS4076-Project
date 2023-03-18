#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addingredient.h"
#include "ingredient.h"

#include <QVector>
#include <QFile>
#include <QStringList>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Read all data from csvs
    csvRead();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addIngredientButton_clicked()
{
    AddIngredient addIngredient = AddIngredient(allIngredients);
    addIngredient.setModal(true);
    addIngredient.exec();
}


void MainWindow::on_exitButton_clicked()
{
    // Write all the data that needs to be saved to csvs (allIngredients and allRecipes)
    csvWrite();
    this->close();
}

void MainWindow::csvRead()
{
    QFile file1("ingredients.csv");
    file1.open(QIODevice::ReadOnly | QIODevice::Text);

    if (file1.exists())
    {
        QTextStream in1(&file1);
        while (!in1.atEnd())
        {
            QString line = in1.readLine();
            processIngredient(line);
        }
    }
    file1.close();

    QFile file2("recipes.csv");
    file2.open(QIODevice::ReadOnly | QIODevice::Text);

    if (file2.exists())
    {
        QTextStream in2(&file2);
        while (!in2.atEnd())
        {
            QString line = in2.readLine();
            processRecipe(line);
        }
    }
    file2.close();
}

void MainWindow::processIngredient(QString line)
{
    QStringList list = line.split(",");
    Ingredient *in = new Ingredient(list.at(0), 100*(list.at(1).toDouble()), 0, list.at(2).toInt());
    allIngredients->append(in);
}

void MainWindow::processRecipe(QString line)
{
    QStringList list = line.split(",");
    QVector<Ingredient*> ingredientList;
    int numberOfIngredients = list.at(5).toInt();
    int i = 0, j = 5;
    while (i < numberOfIngredients)
    {
        Ingredient *in = new Ingredient(list.at(j++), list.at(j++).toDouble(), list.at(j++).toDouble(), list.at(j++).toInt());
        ingredientList.append(in);
        i++;
    }
    Recipe *r = new Recipe(list.at(0), ingredientList, list.at(2), list.at(3).toDouble(), list.at(4).toDouble(), list.at(1));
    allRecipes->append(r);
}

void MainWindow::csvWrite()
{
    QFile ingredientsFile = QFile("ingredients.csv");
    ingredientsFile.open(QIODevice::WriteOnly | QIODevice::Text);
    if (!allIngredients->isEmpty())
    {
        QTextStream out = QTextStream(&ingredientsFile);
        int size = allIngredients->size();
        for (int i = 0; i < size; i++)
        {
            out << allIngredients->at(i)->getName() << ",";
            out << allIngredients->at(i)->getCaloricValue() << ",";
            out << allIngredients->at(i)->getAmount() << ",";
            out << allIngredients->at(i)->measuredInGrams() << "\n";
        }
    }
    ingredientsFile.close();

    QFile recipesFile = QFile("recipes.csv");
    recipesFile.open(QIODevice::WriteOnly | QIODevice::Text);
    if (!allRecipes->isEmpty())
    {
        QDataStream out = QDataStream(&recipesFile);
        int size = allRecipes->size();
        for (int i = 0; i < size; i++)
        {
            int numberOfIngredients = allRecipes->takeAt(i)->getIngredientList().size();
            out << allRecipes->takeAt(i)->getName() << ",";
            out << allRecipes->takeAt(i)->getCuisine() << ",";
            out << allRecipes->takeAt(i)->getInstructions() << ",";
            out << allRecipes->takeAt(i)->getTotalCalories() << ",";
            out << allRecipes->takeAt(i)->getTime() << ",";
            out << numberOfIngredients << ",";
            for (int j = 0; j < numberOfIngredients; j++)
            {
                out << allRecipes->takeAt(i)->getIngredientList()[j] << ",";
                Ingredient *in = allRecipes->takeAt(i)->getIngredientList()[j];
                out << in->getName() << ",";
                out << in->getCaloricValue() << ",";
                out << in->getAmount() << ",";
                out << in->measuredInGrams() << ",";
            }
            out << "\n";
        }
    }
    recipesFile.close();
}
