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
    ui->gridLayout->addWidget(recipeCard4,0,3);
    ui->gridLayout->addWidget(recipeCard5,1,0);
    ui->gridLayout->addWidget(recipeCard6,1,1);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addRecipeButton_clicked()
{
    // Tworzenie nowego przepisu
    RecipeCard *newRecipe = RecipeCard::createRecipeCard("Nowy przepis", "Opis nowego przepisu", ":/images/placeholder.svg", this);

    // Obliczenie indeksu wiersza i kolumny dla nowego przepisu
    int column = ui->gridLayout->count() % 4; // % 3 zapewnia cyklowanie kolumn
    int row = ui->gridLayout->count() / 4;    // Liczenie wierszy na podstawie ilości przepisów

    // Dodanie przepisu do siatkowego układu
    ui->gridLayout->addWidget(newRecipe, row, column);
}

