#include "recipedetailwindow.h"
#include "ui_recipedetailwindow.h"

RecipeDetailWindow::RecipeDetailWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeDetailWindow)
{
    ui->setupUi(this);
}

RecipeDetailWindow::~RecipeDetailWindow()
{
    delete ui;
}

void RecipeDetailWindow::setRecipeDetails(const QString &name, const QString &description, const QString &imagePath, const QString &recipe)
{
    ui->recipeNameLabel->setText(name);
    ui->recipeDescriptionBrowser->setText(description);
    ui->recipeTextBrowser->setText(recipe);

    QPixmap pixmap(imagePath);
    ui->recipeImageLabel->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
