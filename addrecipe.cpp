#include "addrecipe.h"
#include "ui_addrecipe.h"
#include "mainwindow.h"
#include "recipe.h"
#include "ingredient.h"
#include "popup.h"

#define MAX_AMOUNT 9999

namespace counter
{
    static int count = 0;
}

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
    counter::count = 0;
}

AddRecipe::AddRecipe(QVector<Recipe*> *allRecipes, QVector<Ingredient*> *allIngredients, Recipe *editRec, bool editing, int pos) :
    ui(new Ui::AddRecipe)
{
    this->allRecipes = allRecipes;
    this->allIngredients = allIngredients;
    ui->setupUi(this);
    ui->arFavourite->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(128, 128, 128)");
    counter::count = 0;
    this->editRec = editRec;
    this->editing = editing;
    this->pos = pos;
    ui->lineEdit->setText(editRec->getName());
    ui->arCuisineEnter->setText(editRec->getCuisine());
    ui->arTimeEnter->setValue(editRec->getTime());
    if (editRec->getStarred()) { this->on_arFavourite_clicked(); }
    QString inst = editRec->getInstructions().replace("//nl", "\n");
    inst.replace("£", ",");
    ui->arInstrEnter->setPlainText(inst);
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

    int count = 0;
    while (count < allIngredients->size())
    {
        combo->addItem(allIngredients->at(count)->getName());
        count++;
    }

    combo->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
    spin->setMaximum(MAX_AMOUNT);
    combo->setObjectName(QString::number(counter::count));
    spin->setObjectName(QString::number(counter::count));
    hbox->addWidget(combo);
    hbox->addWidget(spin);
    counter::count++;

    connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(ingredientSelected(int)));
    connect(spin, SIGNAL(valueChanged(double)), this, SLOT(ingredientAmountChanged(double)));
    ui->arIngVBox->addLayout(hbox);
    ui->scrollAreaWidgetContents->setLayout(ui->arIngVBox);
    ingredientList.append(allIngredients->at(0));
}

void AddRecipe::ingredientSelected(int index)
{
    int pos = QObject::sender()->objectName().toInt();
    ingredientList.replace(pos, allIngredients->at(index));
}

void AddRecipe::ingredientAmountChanged(double value)
{
    int pos = QObject::sender()->objectName().toInt();
    ingredientList.at(pos)->setAmount(value);
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
    time = arg1;
}

void AddRecipe::on_arConfirmAdd_clicked()
{
    try {
        instructions = ui->arInstrEnter->toPlainText();
        instructions.replace("\n", "//nl");
        instructions.replace(",", "£");

        if ((!name.isNull()) && (ingredientList.size() != 0) && (!instructions.isNull()) && (time != 0))
        {
            int size = allRecipes->size();
            for (int i = 0; i < size; i++)
            {
                if ((!editing) && (name.toUpper() == (*allRecipes)[i]->getName().toUpper())) {
                    this->raiseException();
                }
            }

            if (!cuisine.isNull() && !editing)
            {
                Recipe *r = new Recipe(name, ingredientList, instructions, time, cuisine, starred);
                allRecipes->append(r);

                Popup *success = new Popup("Ok", "Recipe added successfully!");
                success->setModal(true);
                success->exec();
                delete success;

                this->close();
            } else if (!editing) {
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
            } else if (editing) {
                Recipe *r = new Recipe(name, ingredientList, instructions, time, cuisine, starred);
                allRecipes->replace(pos, r);

                Popup *success = new Popup("Ok", "Recipe edited successfully!");
                success->setModal(true);
                success->exec();
                delete success;

                this->close();
            }
        } else {
            Popup *incomplete = new Popup("Ok", "Please ensure all fields are filled out correctly.");
            incomplete->setModal(true);
            incomplete->exec();
            delete incomplete;
        }
    } catch (CustomException ex) {
        Popup *exists = new Popup("Ok", "Recipe already exists with that name");
        exists->setModal(true);
        exists->exec();
        delete exists;
    }
}
