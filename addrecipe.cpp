#include "addrecipe.h"
#include "ui_addrecipe.h"

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
//    for (int i = 0; i < allIngredients->size(); ++i) {
//        ui->arIng1->addItem(allIngredients->at(i)->getName());
//    }
//    for (int i = 0; i < allIngredients->size(); ++i) {
//        ui->arIng2->addItem(allIngredients->at(i)->getName());
//    }
//    for (int i = 0; i < allIngredients->size(); ++i) {
//        ui->arIng3->addItem(allIngredients->at(i)->getName());
//    }
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

    for (int i = 0; i < allIngredients->size(); ++i) {
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
