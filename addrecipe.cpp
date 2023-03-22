#include "addrecipe.h"
#include "ui_addrecipe.h"
#include "mainwindow.h"
#include "recipe.h"
#include "ingredient.h"
#include "popup.h"

AddRecipe::AddRecipe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRecipe)
{
    ui->setupUi(this);
}

AddRecipe::AddRecipe(QVector<Recipe*> *allRecipes, QVector<Ingredient*> *allIngredients) :
    ui(new Ui::AddRecipe)
{
    this->allRecipes = allRecipes;
    this->allIngredients = allIngredients;
    ui->setupUi(this);
    ui->arFavourite->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(128, 128, 128)");
}

AddRecipe::~AddRecipe()
{
    delete ui;
}

void AddRecipe::on_arConfirmCancel_clicked()
{
    this->close();
}


void AddRecipe::on_arFavourite_clicked()
{
    starred = !starred;
    if (starred) {
        ui->arFavourite->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(194, 194, 0)");
    } else {
        ui->arFavourite->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(128, 128, 128)");
    }
}



void AddRecipe::on_arIngAddSlot_clicked()
{
    QHBoxLayout *hbox = new QHBoxLayout();
    QComboBox *combo = new QComboBox();
    QDoubleSpinBox *spin = new QDoubleSpinBox();

    for (int i = 0; i < allIngredients->size(); ++i)
    {
        combo->addItem(allIngredients->at(i)->getName());
    }

    combo->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
    spin->setMaximum(9999);
    hbox->addWidget(combo);
    hbox->addWidget(spin);

    ui->arIngVBox->addLayout(hbox);
    ui->scrollAreaWidgetContents->setLayout(ui->arIngVBox);
}


void AddRecipe::on_lineEdit_textChanged(const QString &arg1)
{
    name = arg1;
}


void AddRecipe::on_arCuisineEnter_textChanged(const QString &arg1)
{
    cuisine = arg1;
}


void AddRecipe::on_arTimeEnter_valueChanged(int arg1)
{
    double time = arg1;
}

void AddRecipe::on_arConfirmAdd_clicked()
{
    QList<QHBoxLayout*> listOfChildren = ui->arIngVBox->findChildren<QHBoxLayout*>();
    foreach (QHBoxLayout *hbox, listOfChildren)
    {
        QComboBox *box = hbox->findChild<QComboBox*>();
        QDoubleSpinBox *spinBox = hbox->findChild<QDoubleSpinBox*>();
        QString ingName = box->currentText();
        int size = allIngredients->size();

        for (int i = 0; i < size; i++)
        {
            if (ingName.toUpper() == allIngredients->takeAt(i)->getName().toUpper())
            {
                Ingredient *ing = new Ingredient(allIngredients->takeAt(i));
                ing->setAmount(spinBox->value());
                ingredientList.append(ing);
            }
        }
    }

    if ((!name.isNull()) && (ingredientList.size() != 0) && (!instructions.isNull()) && (time != 0))
    {
        if (!cuisine.isNull())
        {
            Recipe *r = new Recipe(name, ingredientList, instructions, time, cuisine, starred);
            allRecipes->append(r);

            Popup *success = new Popup("Ok", "Recipe added successfully!");
            success->setModal(true);
            success->exec();
            delete success;

            this->close();
        } else {
            Popup *success = new Popup("Cancel", "Confirm", "No cuisine has been specified, are you sure you want to add this recipe?");
            success->setModal(true);
            success->exec();
            delete success;

            if (popupReturn)
            {
                Recipe *r = new Recipe(name, ingredientList, instructions, time, starred);
                allRecipes->append(r);

                this->close();
            }
        }
    }
    Popup *incomplete = new Popup("Ok", "Please ensure all fields are filled out correctly.");
    incomplete->setModal(true);
    incomplete->exec();
    delete incomplete;
}

