// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "recipecard.h"
#include "recipeadd.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addRecipeButton_clicked()
{
    RecipeAdd *recipeAddDialog = new RecipeAdd(this);

    ui->addRecipeButton->setEnabled(false);

    connect(recipeAddDialog, &RecipeAdd::recipeAdded, this, &MainWindow::handleRecipeAdded);
    connect(recipeAddDialog, &RecipeAdd::rejected, this, &MainWindow::handleRecipeDialogClosed);

    recipeAddDialog->show();
}

void MainWindow::handleRecipeAdded(const QString &name, const QString &description)
{

    RecipeCard *newRecipe = RecipeCard::createRecipeCard(name, description, ":/images/placeholder.svg", this);
    int column = ui->gridLayout->count() % 5;
    int row = ui->gridLayout->count() / 5;

    ui->gridLayout->addWidget(newRecipe, row, column);

    ui->addRecipeButton->setEnabled(true);
}

void MainWindow::handleRecipeDialogClosed()
{
    ui->addRecipeButton->setEnabled(true);
}
