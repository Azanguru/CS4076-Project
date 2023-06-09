#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addingredient.h"
#include "ingredient.h"
#include "addrecipe.h"
#include "recipe.h"
#include "popup.h"
#include "filtersearch.h"

#include <QVector>
#include <QFile>
#include <QPushButton>
#include <QLabel>

using namespace std;

bool popupReturn = false;

struct {
    QString cuisineName = "";
    unsigned int calLimit : 13;
    unsigned int timeLimit : 8;
} fsStruct;

int option = 0;

union {
    int a;
    float b;
    char c;
    bool d;
} myUnion;

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

void MainWindow::processIngredient(QString &line)
{
    QStringList list = line.split(",");
    Ingredient *in = new Ingredient(list.at(0), 100*(list.at(1).toDouble()), 0, list.at(3).toInt());
    allIngredients->append(in);
}

void MainWindow::processRecipe(QString &line)
{
    QStringList list = line.split(",");
    QVector<Ingredient*> ingredients;
    int numberOfIngredients = list.at(6).toInt();
    int i = 0, j = 6;
    while (i < numberOfIngredients)
    {
        Ingredient *in = new Ingredient(QString(list.at(j+1)), 100*list.at(j+2).toDouble(), list.at(j+3).toDouble(), list.at(j+4).toInt());
        ingredients.append(in);
        i++;
        j += 4;
    }
    Recipe *r = new Recipe(list.at(0), ingredients, list.at(2), list.at(3).toDouble(), list.at(4).toInt(), list.at(1), list.at(5).toInt());
    r->resetCalories();
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
    deleteWidgetsFromLayout(ui->ingGrid);
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
    ui->pages->setCurrentIndex(1);
    ui->vrViewStarred->setChecked(false);
    displayRecipes(allRecipes);
}

void MainWindow::displayRecipes(QVector<Recipe*> *recipes) // maybe use templates/arrays with pointers here??
{
    int size = recipes->size();
    for (int i = 0; i < size; i++)
    {
        QLabel *name = new QLabel(recipes->at(i)->getName());
        QLabel *cuisine = new QLabel("Cuisine: " + recipes->at(i)->getCuisine());
        int cals = recipes->at(i)->getTotalCalories();
        QLabel *calories = new QLabel("Calories: " + QString::number(cals));
        int mins = recipes->at(i)->getTime();
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

        connect(viewRecipe, &QPushButton::clicked, [=](){ viewRecipesButtonPressed(i, 0, recipes); } );
        connect(editRecipe, &QPushButton::clicked, [=](){ viewRecipesButtonPressed(i, 1, recipes); } );
        connect(deleteRecipe, &QPushButton::clicked, [=](){ viewRecipesButtonPressed(i, 2, recipes); } );
        ui->recGrid->addWidget(name, i, 0);
        ui->recGrid->addWidget(cuisine, i, 1);
        ui->recGrid->addWidget(calories, i, 2);
        ui->recGrid->addWidget(time, i, 3);
        ui->recGrid->addWidget(viewRecipe, i, 4);
        ui->recGrid->addWidget(editRecipe, i, 5);
        ui->recGrid->addWidget(deleteRecipe, i, 6);

        ui->scrollAreaWidgetContents_2->setLayout(ui->recGrid);
    }
}

void MainWindow::viewRecipesButtonPressed(int row, int val, QVector<Recipe*> *recipes)
{
    int pos;
    for (int i = 0; i < allRecipes->size(); i++)
    {
        if (allRecipes->at(i) == recipes->at(row)) { pos = i; }
    }
    switch (val)
    {
    case 0:
    {
        Recipe* thisRecipe = recipes->at(row);
        ui->pages->setCurrentIndex(4);
        ui->vrRecipeLabel->setText(thisRecipe->getName());
        ui->vrCuisineLabel->setText("Cuisine: " + thisRecipe->getCuisine());
        ui->vrTimeLabel->setText("Time to make: " + QString::number(thisRecipe->getTime()) + " mins");
        ui->vrCalsLabel->setText("Calories: " + QString::number(thisRecipe->getTotalCalories()));
        QString inst = "Instructions:\n" + thisRecipe->getInstructions().replace("//nl", "\n");
        inst.replace("£", ",");
        ui->vrInstrTextEdit->setPlainText(inst);
        int size = thisRecipe->getIngredientList().size();

        QLabel *title = new QLabel("Ingredients:");
        title->setIndent(5);
        title->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        title->setStyleSheet("font-weight: bold");
        ui->vrGrid->addWidget(title, 0, 0);
        for (int i = 1; i <= size; i++)
        {
            Ingredient *current = thisRecipe->getIngredientList().at(i-1);
            QLabel *ingName = new QLabel(current->getName());
            QLabel *ingAmount;
            ingName->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
            ingName->setIndent(5);
            if (current->measuredInGrams()) { ingAmount = new QLabel(QString::number(current->getAmount()) + "g  "); }
            else { ingAmount = new QLabel(QString::number(current->getAmount()) + "ml  "); }
            ui->vrGrid->addWidget(ingName, i, 0);
            ui->vrGrid->addWidget(ingAmount, i, 1);
            ui->scrollAreaWidgetContents_3->setLayout(ui->vrGrid);
        }
        break;
    }
    case 1:
    {
        AddRecipe addRecipe = AddRecipe(allRecipes, allIngredients, recipes->at(row), true, pos);
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
        if (popupReturn) { allRecipes->removeAt(pos); }
        this->on_vrBack_clicked();
        this->on_viewRecipesButton_clicked();
        break;
    }
    }
}

void MainWindow::on_vrBack_clicked()
{
    ui->pages->setCurrentIndex(0);
    deleteWidgetsFromLayout(ui->recGrid);
    ui->vrViewStarred->setHidden(false);
}

void MainWindow::on_vrBack_2_clicked()
{
    ui->pages->setCurrentIndex(1);
    ui->vrViewStarred->setChecked(false);
    deleteWidgetsFromLayout(ui->vrGrid);
}

void MainWindow::deleteWidgetsFromLayout(QLayout *layout)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        QWidget* widget;
        if (widget = item->widget()) { delete widget; }
        delete item;
    }
}

void MainWindow::on_vrViewStarred_stateChanged(int arg1)
{
    deleteWidgetsFromLayout(ui->recGrid);
    if (ui->vrViewStarred->isChecked())
    {
        QVector<Recipe*> *starredRecipes = new QVector<Recipe*>();
        int size = allRecipes->size();
        for (int i = 0; i < size; i++)
        {
            if (allRecipes->at(i)->getStarred())
            {
                starredRecipes->append(allRecipes->at(i));
            }
        }
        displayRecipes(starredRecipes);
    } else {
        displayRecipes(allRecipes);
    }
}

void MainWindow::on_filterSearchButton_clicked()
{
    ui->fsCalorieSlider->setValue(0);
    ui->fsCuisineEnter->setText("");
    ui->fsTimeEnter->setCurrentIndex(0);
    ui->pages->setCurrentIndex(2);
}

void MainWindow::on_fsBack_clicked()
{
    ui->pages->setCurrentIndex(0);
}

void MainWindow::on_fsSearch_clicked()
{
    QVector<Recipe*> *selectedRecipes;

    if ((fsStruct.cuisineName == "") && (fsStruct.calLimit != 0) && (fsStruct.timeLimit == 0)) {
        QVector<double> vector;
        for (int i = 0; i < allRecipes->size(); i++)
        {
            vector.append(allRecipes->at(i)->getTotalCalories());
        }
        SingleSearch<double> ss = SingleSearch<double>(fsStruct.calLimit, vector, allRecipes);
        selectedRecipes = ss.search();

    } else if ((fsStruct.cuisineName == "") && (fsStruct.calLimit == 0) && (fsStruct.timeLimit != 0)) {
        QVector<int> vector;
        for (int i = 0; i < allRecipes->size(); i++)
        {
            vector.append(allRecipes->at(i)->getTime());
        }
        SingleSearch<int> ss = SingleSearch<int>(fsStruct.timeLimit, vector, allRecipes);
        selectedRecipes = ss.search();

    } else {
        CombinedSearch cs = CombinedSearch(allRecipes, fsStruct.cuisineName, fsStruct.calLimit, fsStruct.timeLimit);
        selectedRecipes = cs.search();
    }

    ui->pages->setCurrentIndex(1);
    ui->vrViewStarred->setChecked(false);
    displayRecipes(selectedRecipes);
    ui->vrViewStarred->setHidden(true);
}

void MainWindow::on_fsCuisineEnter_textChanged(const QString &arg1)
{
    fsStruct.cuisineName = arg1;
}

void MainWindow::on_fsTimeEnter_currentIndexChanged(int index)
{
    fsStruct.timeLimit = index * 15;
}

void MainWindow::on_fsCalorieSlider_valueChanged(int value)
{
    fsStruct.calLimit = value;
    if (value != 0)
    {
        ui->fsCalorieDisplay->setText("Calorie Limit: " + QString::number(value));
    } else {
        ui->fsCalorieDisplay->setText("No Calorie Limit");
    }
}

void MainWindow::on_unionBack_clicked()
{
    ui->pages->setCurrentIndex(0);
}

void MainWindow::on_pushButton_clicked()
{
    ui->pages->setCurrentIndex(5);
    srand((unsigned) time(NULL));
    myUnion.a = rand() % 100;
    ui->unionLabel->setText(QString::number(myUnion.a));
}

void MainWindow::on_changeUnionType_clicked()
{
    option++;
    if (option > 3) { option = 0; }

    switch (option) {
    case 0 : ui->unionLabel->setText(QString::number(myUnion.a)); break;
    case 1 : ui->unionLabel->setText(QString::number(myUnion.b)); break;
    case 2 : ui->unionLabel->setText(QString(myUnion.c)); break;
    case 3 : QString str; myUnion.d ? str = "true" : str = "false"; ui->unionLabel->setText(str); break;
    }
}

