#include "addrecipe.h"
#include "ui_addrecipe.h"

AddRecipe::AddRecipe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRecipe)
{
    ui->setupUi(this);
}

AddRecipe::AddRecipe(QVector<Recipe*> *allRecipes) :
    ui(new Ui::AddRecipe)
{
    this->allRecipes = allRecipes;
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

