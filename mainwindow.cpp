#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addingredient.h"
#include "ingredient.h"
#include "addrecipe.h"
#include "recipe.h"
#include "popup.h"

#include <QVector>
#include <QFile>
#include <QPushButton>
#include <QLabel>

using namespace std;

bool popupReturn = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Read all data from csvs
    csvRead();
    ui->setupUi(this);
    ui->pages->setCurrentIndex(0);
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
    Ingredient *in = new Ingredient(list.at(0), 100*(list.at(1).toDouble()), 0, list.at(3).toInt());
    allIngredients->append(in);
}

void MainWindow::processRecipe(QString line)
{
    QStringList list = line.split(",");
    QVector<Ingredient*> ingredientList;
    int numberOfIngredients = list.at(6).toInt();
    int i = 0, j = 6;
    while (i < numberOfIngredients)
    {
        Ingredient *in = new Ingredient(list.at(j++), 100*list.at(j++).toDouble(), list.at(j++).toDouble(), list.at(j++).toInt());
        ingredientList.append(in);
        i++;
    }
    Recipe *r = new Recipe(list.at(0), ingredientList, list.at(2), list.at(3).toDouble(), list.at(4).toInt(), list.at(1), list.at(5).toInt());
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
            out << allIngredients->at(i) << "\n";
        }
    }
    ingredientsFile.close();

    QFile recipesFile = QFile("recipes.csv");
    recipesFile.open(QIODevice::WriteOnly | QIODevice::Text);
    if (!allRecipes->isEmpty())
    {
        QTextStream out = QTextStream(&recipesFile);
        int size = allRecipes->size();
        for (int i = 0; i < size; i++)
        {
            out << allRecipes->at(i) << "\n";
        }
    }
    recipesFile.close();
}

void MainWindow::on_viewIngredientsButton_clicked()
{
        ui->pages->setCurrentIndex(3);

        int size = allIngredients->size();
        for (int i = 0; i < size; i++)
        {
            QLabel *name = new QLabel(allIngredients->at(i)->getName());
            int cals = allIngredients->at(i)->getCaloricValue() * 100;
            QLabel *calories = new QLabel("Calories per 100g/ml: " + QString::number(cals));
            QPushButton *editIngredient = new QPushButton("Edit");
            QPushButton *deleteIngredient = new QPushButton("Delete");

            name->setIndent(5);
            name->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
            calories->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

            connect(editIngredient, &QPushButton::clicked, [=](){ viewIngredientsButtonPressed(i, true); } );
            connect(deleteIngredient, &QPushButton::clicked, [=](){ viewIngredientsButtonPressed(i, false); } );
            ui->ingGrid->addWidget(name, i, 0);
            ui->ingGrid->addWidget(calories, i, 1);
            ui->ingGrid->addWidget(editIngredient, i, 2);
            ui->ingGrid->addWidget(deleteIngredient, i, 3);

            ui->scrollAreaWidgetContents->setLayout(ui->ingGrid);
        }
}

void MainWindow::viewIngredientsButtonPressed(int row, bool val)
{
    if (val)
    {
        AddIngredient addIngredient = AddIngredient(allIngredients, allIngredients->at(row), true, row);
        addIngredient.setModal(true);
        addIngredient.exec();
    } else {
        Popup popup = Popup("Cancel", "Confirm", "Are you sure you want to delete this ingredient?");
        popup.setModal(true);
        popup.exec();
        if (popupReturn) { allIngredients->removeAt(row); }
    }
    this->on_viBack_clicked();
    this->on_viewIngredientsButton_clicked();
}

void MainWindow::on_viBack_clicked()
{
        ui->pages->setCurrentIndex(0);
        while (QLayoutItem* item = ui->ingGrid->takeAt(0))
        {
            QWidget* widget;
            if (widget = item->widget()) { delete widget; }
            delete item;
        }
}

void MainWindow::on_addRecipeButton_clicked()
{
    AddRecipe addRecipe = AddRecipe(allRecipes, allIngredients);
    addRecipe.setModal(true);
    addRecipe.exec();
}


void MainWindow::on_actionSave_triggered()
{
    this->csvWrite();
}


void MainWindow::on_actionDelete_triggered()
{
    Popup *confirmation = new Popup("Cancel", "Confirm", "Are you sure you want to delete the saved data (this cannot be undone)?");
    confirmation->setModal(true);
    confirmation->exec();
    delete confirmation;

    if(popupReturn) {
        QFile file("ingredients.csv");
        file.open(QFile::WriteOnly|QFile::Truncate);

        QFile file2("recipes.csv");
        file2.open(QFile::WriteOnly|QFile::Truncate);
    }
}


void MainWindow::on_actionSave_Exit_triggered()
{
    csvWrite();
    this->close();
}


void MainWindow::on_actionExit_triggered()
{
    Popup *confirmation = new Popup("Cancel", "Proceed", "Are you sure you want to exit without saving (all unsaved data will be lost)?");
    confirmation->setModal(true);
    confirmation->exec();
    delete confirmation;

    if(popupReturn) {
        this->close();
    }
}


void MainWindow::on_viewRecipesButton_clicked()
{
    ui->pages->setCurrentIndex(3);

    int size = allRecipes->size();
    for (int i = 0; i < size; i++)
    {
        QLabel *name = new QLabel(allRecipes->at(i)->getName());
        QLabel *cuisine = new QLabel("Cuisine: " + allRecipes->at(i)->getCuisine());
        int cals = allRecipes->at(i)->getTotalCalories();
        QLabel *calories = new QLabel("Calories: " + QString::number(cals));
        int mins = allRecipes->at(i)->getTime();
        QLabel *time = new QLabel("Time to make: " + QString::number(mins) + " mins");
        QPushButton *viewRecipe = new QPushButton("View");
        QPushButton *editRecipe = new QPushButton("Edit");
        QPushButton *deleteRecipe = new QPushButton("Delete");

        name->setStyleSheet("font-weight: bold");
        name->setIndent(5);
        name->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        cuisine->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        calories->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        time->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

        connect(viewRecipe, &QPushButton::clicked, [=](){ viewRecipesButtonPressed(i, 0); } );
        connect(editRecipe, &QPushButton::clicked, [=](){ viewRecipesButtonPressed(i, 1); } );
        connect(deleteRecipe, &QPushButton::clicked, [=](){ viewRecipesButtonPressed(i, 2); } );
        ui->recGrid->addWidget(name, i, 0);
        ui->recGrid->addWidget(cuisine, i, 1);
        ui->recGrid->addWidget(calories, i, 2);
        ui->recGrid->addWidget(time, i, 3);
        ui->recGrid->addWidget(viewRecipe, i, 4);
        ui->recGrid->addWidget(editRecipe, i, 5);
        ui->recGrid->addWidget(deleteRecipe, i, 6);

        ui->scrollAreaWidgetContents->setLayout(ui->recGrid);
    }
}

void MainWindow::viewRecipesButtonPressed(int row, int val)
{
    switch (val)
    {
    case 0:
    {
        break;
    }
    case 1:
    {
        AddRecipe addRecipe = AddRecipe(allRecipes, allIngredients, allRecipes->at(row), true, row);
        addRecipe.setModal(true);
        addRecipe.exec();
        this->on_vrBack_clicked();
        this->on_viewRecipesButton_clicked();
        break;
    }
    case 2:
    {
        Popup popup = Popup("Cancel", "Confirm", "Are you sure you want to delete this recipe?");
        popup.setModal(true);
        popup.exec();
        if (popupReturn) { allRecipes->removeAt(row); }
        this->on_vrBack_clicked();
        this->on_viewRecipesButton_clicked();
        break;
    }
    }
}

void MainWindow::on_vrBack_clicked()
{
    ui->pages->setCurrentIndex(0);
    while (QLayoutItem* item = ui->recGrid->takeAt(0))
    {
        QWidget* widget;
        if (widget = item->widget()) { delete widget; }
        delete item;
    }
}

