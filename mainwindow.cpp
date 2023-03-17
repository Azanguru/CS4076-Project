#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addingredient.h"
#include "ingredient.h"

#include <QVector>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete allIngredients;
    delete ui;
}

void MainWindow::on_addIngredientButton_clicked()
{
    AddIngredient addIngredient = AddIngredient(allIngredients);
    addIngredient.setModal(true);
    addIngredient.exec();
}

