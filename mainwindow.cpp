#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "recipecard.h"
#include "recipeadd.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

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

void MainWindow::handleRecipeAdded(const QString &name, const QString &description, const QString &pic, const QString &recipe)
{
    RecipeCard *newRecipe = RecipeCard::createRecipeCard(name, description, pic, recipe, this);
    int column = ui->gridLayout->count() % 4;
    int row = ui->gridLayout->count() / 4;
    connect(newRecipe, &RecipeCard::recipeDeleted, this, &MainWindow::handleRecipeDeleted);

    ui->gridLayout->addWidget(newRecipe, row, column);

    ui->addRecipeButton->setEnabled(true);
}

void MainWindow::handleRecipeDeleted(RecipeCard *recipeCard)
{
    ui->gridLayout->removeWidget(recipeCard); // Remove widget from layout
    recipeCard->deleteLater(); // Delete widget from memory

    // Important: Update layout after removing widget
    ui->gridLayout->update();

}

void MainWindow::handleRecipeDialogClosed()
{
    ui->addRecipeButton->setEnabled(true);
}
