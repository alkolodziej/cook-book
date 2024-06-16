#include "recipecard.h"
#include "ui_recipecard.h"
#include "recipedetailwindow.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDebug>

// Constructor for RecipeCard
RecipeCard::RecipeCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeCard)
{
    ui->setupUi(this);

    // Connect the delete button click signal to the slot
    connect(ui->pushButtonDelete, &QPushButton::clicked, this, &RecipeCard::on_pushButtonDelete_clicked);
    // Connect the download button click signal to the slot
    connect(ui->pushButtonDownload, &QPushButton::clicked, this, &RecipeCard::on_pushButtonDownload_clicked);
    // Connect the see recipe button click signal to the slot (uncomment to enable)
    // connect(ui->pushButtonSeeRecipe, &QPushButton::clicked, this, &RecipeCard::on_pushButtonSeeRecipe_clicked);
}

// Destructor for RecipeCard
RecipeCard::~RecipeCard()
{
    delete ui;
}

// Set the recipe details for the RecipeCard
void RecipeCard::setRecipe(const QString &name, const QString &description, const QString &image, const QString &recipe)
{
    recipeName = name;
    recipeDescription = description;
    imagePath = image;
    recipeText = recipe;

    // Update UI elements with the provided details
    ui->titleLabel->setText(recipeName);
    ui->descriptionLabel->setText(recipeDescription);
    QPixmap pixmap(imagePath);
    ui->imageLabel->setPixmap(pixmap);
}

// Get the name of the recipe
QString RecipeCard::getRecipeName() const
{
    return recipeName;
}

// Get the description of the recipe
QString RecipeCard::getRecipeDescription() const
{
    return recipeDescription;
}

// Get the image path of the recipe
QString RecipeCard::getRecipeImagePath() const
{
    return imagePath;
}

// Get the recipe text
QString RecipeCard::getRecipeText() const
{
    return recipeText;
}

// Static method to create a new RecipeCard
RecipeCard* RecipeCard::createRecipeCard(const QString &name, const QString &description, const QString &imagePath, const QString &recipe, QWidget *parent)
{
    RecipeCard *newRecipeCard = new RecipeCard(parent);
    newRecipeCard->setRecipe(name, description, imagePath, recipe);
    return newRecipeCard;
}

// Slot for handling delete button click
void RecipeCard::on_pushButtonDelete_clicked()
{
    emit recipeDeleted(this); // Emit the recipeDeleted signal with this RecipeCard instance
}

// Slot for handling download button click
void RecipeCard::on_pushButtonDownload_clicked()
{
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString fileName = desktopPath + "/" + recipeName + ".txt";

    QFile file(fileName);

    // Try to open the file for writing
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        // Write the recipe details to the file
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

// Slot for handling see recipe button click
void RecipeCard::on_pushButtonSeeRecipe_clicked()
{
    qDebug() << "See recipe clicked";
    RecipeDetailWindow *detailWindow = new RecipeDetailWindow();
    detailWindow->setRecipeDetails(recipeName, recipeDescription, imagePath, recipeText);

    // Connect the recipeEdited signal from the detail window to update this recipe card
    connect(detailWindow, &RecipeDetailWindow::recipeEdited, this, [=](const QString &originalName, const QString &name, const QString &description, const QString &imagePath, const QString &recipe) {
        if (originalName == recipeName) {  // Ensure we are editing the correct recipe
            setRecipe(name, description, imagePath, recipe);
            emit recipeEdited(originalName, name, description, imagePath, recipe);  // Emit the recipeEdited signal
        }
    });

    detailWindow->show(); // Show the detail window
}
