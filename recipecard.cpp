#include "recipecard.h"
#include "ui_recipecard.h"
#include "recipedetailwindow.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDebug>

RecipeCard::RecipeCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeCard)
{
    ui->setupUi(this);

    // Connect delete button click to deleteRecipe slot
    connect(ui->pushButtonDelete, &QPushButton::clicked, this, &RecipeCard::on_pushButtonDelete_clicked);
    // Connect download button click to downloadRecipe slot
    connect(ui->pushButtonDownload, &QPushButton::clicked, this, &RecipeCard::on_pushButtonDownload_clicked);
    // Connect see recipe button click to seeRecipe slot
    // connect(ui->pushButtonSeeRecipe, &QPushButton::clicked, this, &RecipeCard::on_pushButtonSeeRecipe_clicked);

}

RecipeCard::~RecipeCard()
{
    delete ui;
}

void RecipeCard::setRecipe(const QString &name, const QString &description, const QString &image, const QString &recipe)
{
    recipeName = name;
    recipeDescription = description;
    imagePath = image;
    recipeText = recipe;

    ui->titleLabel->setText(recipeName);
    ui->descriptionLabel->setText(recipeDescription);
    QPixmap pixmap(imagePath);
    ui->imageLabel->setPixmap(pixmap);
}

QString RecipeCard::getRecipeName() const
{
    return recipeName;
}

QString RecipeCard::getRecipeDescription() const
{
    return recipeDescription;
}

QString RecipeCard::getRecipeImagePath() const
{
    return imagePath;
}

QString RecipeCard::getRecipeText() const
{
    return recipeText;
}

RecipeCard* RecipeCard::createRecipeCard(const QString &name, const QString &description, const QString &imagePath, const QString &recipe, QWidget *parent)
{
    RecipeCard *newRecipeCard = new RecipeCard(parent);
    newRecipeCard->setRecipe(name, description, imagePath, recipe);
    return newRecipeCard;
}

void RecipeCard::on_pushButtonDelete_clicked()
{
    emit recipeDeleted(this);
}

void RecipeCard::on_pushButtonDownload_clicked()
{
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString fileName = desktopPath + "/" + recipeName + ".txt";

    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "Title: " << recipeName << "\n";
        out << "Description: " << recipeDescription << "\n";
        out << "Image Path: " << imagePath << "\n";
        out << "Recipe: " << recipeText << "\n";
        file.close();
        qDebug() << "Recipe saved to " << fileName;
    } else {
        qDebug() << "Could not open file " << fileName << " for writing.";
    }
}

void RecipeCard::on_pushButtonSeeRecipe_clicked()
{
    qDebug() << "See recipe clicked";
    RecipeDetailWindow *detailWindow = new RecipeDetailWindow();
    detailWindow->setRecipeDetails(recipeName, recipeDescription, imagePath, recipeText);

    connect(detailWindow, &RecipeDetailWindow::recipeEdited, this, [=](const QString &originalName, const QString &name, const QString &description, const QString &imagePath, const QString &recipe) {
        if (originalName == recipeName) {  // Ensure we are editing the correct recipe
            setRecipe(name, description, imagePath, recipe);
            emit recipeEdited(originalName, name, description, imagePath, recipe);  // Emit the signal
        }
    });

    detailWindow->show();
}
