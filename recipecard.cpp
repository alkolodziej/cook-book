#include "recipecard.h"
#include "ui_recipecard.h"

RecipeCard::RecipeCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeCard)
{
    ui->setupUi(this);
}

RecipeCard::~RecipeCard()
{
    delete ui;
}

void RecipeCard::setRecipeName(const QString &name)
{
    ui->titleLabel->setText(name);
}

void RecipeCard::setRecipeDescription(const QString &description)
{
    ui->descriptionLabel->setText(description);
}

void RecipeCard::setRecipeImage(const QPixmap &image)
{
    ui->imageLabel->setPixmap(image);
}

RecipeCard* RecipeCard::createRecipeCard(const QString &name, const QString &description, const QString &imagePath, QWidget *parent)
{
    RecipeCard *recipeCard = new RecipeCard(parent);
    recipeCard->setRecipeName(name);
    recipeCard->setRecipeDescription(description);
    recipeCard->setRecipeImage(QPixmap(imagePath));
    return recipeCard;
}
