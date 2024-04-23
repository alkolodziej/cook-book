#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    RecipeCard *recipeCard1 = RecipeCard::createRecipeCard("Pasta", "A delicious pasta recipe", ":/images/placeholder.svg", this);
    RecipeCard *recipeCard2 = RecipeCard::createRecipeCard("Pasta", "A delicious pasta recipe", ":/images/placeholder.svg", this);
    RecipeCard *recipeCard3 = RecipeCard::createRecipeCard("Pasta", "A delicious pasta recipe", ":/images/placeholder.svg", this);
    RecipeCard *recipeCard4 = RecipeCard::createRecipeCard("Pasta", "A delicious pasta recipe", ":/images/placeholder.svg", this);
    RecipeCard *recipeCard5 = RecipeCard::createRecipeCard("Pasta", "A delicious pasta recipe", ":/images/placeholder.svg", this);
    RecipeCard *recipeCard6 = RecipeCard::createRecipeCard("Pasta", "A delicious pasta recipe", ":/images/placeholder.svg", this);

    ui->gridLayout->addWidget(recipeCard1,0,0);
    ui->gridLayout->addWidget(recipeCard2,0,1);
    ui->gridLayout->addWidget(recipeCard3,0,2);
    ui->gridLayout->addWidget(recipeCard4,1,0);
    ui->gridLayout->addWidget(recipeCard5,1,1);
    ui->gridLayout->addWidget(recipeCard6,1,2);


}

MainWindow::~MainWindow()
{
    delete ui;
}

