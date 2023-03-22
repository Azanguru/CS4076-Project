#include "addingredient.h"
#include "ui_addingredient.h"

#include "ingredient.h"
#include "popup.h"
#include <QVector>

AddIngredient::AddIngredient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddIngredient)
{
    ui->setupUi(this);
}

AddIngredient::AddIngredient(QVector<Ingredient*> *allIngredients) :
    ui(new Ui::AddIngredient)
{
    this->allIngredients = allIngredients;
    ui->setupUi(this);
}

AddIngredient::AddIngredient(QVector<Ingredient*> *allIngredients, Ingredient *editIng, bool editing, int pos) :
    ui(new Ui::AddIngredient)
{
    this->allIngredients = allIngredients;
    this->editIng = editIng;
    this->editing = editing;
    this->pos = pos;
    ui->setupUi(this);
    ui->enterName->setText(editIng->getName());
    ui->enterCalories->setValue(editIng->getCaloricValue()*100);
    if (!editIng->measuredInGrams()) { ui->enterMeasurementMillilitres->toggle(); }
}

AddIngredient::~AddIngredient()
{
    delete ui;
}

void AddIngredient::on_cancelButton_clicked()
{
    this->close();
}


void AddIngredient::on_addButton_clicked()
{

    if ((!ingredientName.isNull()) && (ingredientCalories != 0.0))
    {
        int size = allIngredients->size();
        bool found = false;
        for (int i = 0; i < size; i++)
        {
            if (ingredientName.toUpper() == (*allIngredients)[i]->getName().toUpper()) {
                found = true;

                Popup *exists = new Popup("Ok", "Ingredient already exists with that name");
                exists->setModal(true);
                exists->exec();
                delete exists;

                break;
            }
        }

        if (!found && !editing)
        {
            Ingredient *in =  new Ingredient(ingredientName, ingredientCalories, 0.0, ingredientInGrams);
            allIngredients->append(in);

            Popup *success = new Popup("Ok", "Ingredient added successfully!");
            success->setModal(true);
            success->exec();
            delete success;

            this->close();
        } else if (!found && editing) {
            Ingredient *in =  new Ingredient(ingredientName, ingredientCalories, 0.0, ingredientInGrams);
            allIngredients->replace(pos, in);

            Popup *success = new Popup("Ok", "Ingredient edited successfully!");
            success->setModal(true);
            success->exec();
            delete success;

            this->close();
        }

    } else {
        Popup *missingInfo = new Popup("Ok", "Ingredient name and/or caloric value is/are missing. Please ensure these are entered correctly and try again.");
        missingInfo->setModal(true);
        missingInfo->exec();
        delete missingInfo;
    }
}

void AddIngredient::on_enterName_textChanged(const QString &arg1)
{
    ingredientName = arg1;
}


void AddIngredient::on_enterCalories_valueChanged(double arg1)
{
    ingredientCalories = arg1;
}


void AddIngredient::on_enterMeasurementGrams_toggled(bool checked)
{
    ingredientInGrams = true;
}


void AddIngredient::on_enterMeasurementMillilitres_toggled(bool checked)
{
    ingredientInGrams = false;
}
