#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "recipecard.h"
#include "recipeadd.h"
#include "recipedetailwindow.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

// MainWindow constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Define the file path for storing the recipes in the application data directory
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(appDataPath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    recipeFilePath = appDataPath + "/recipes.json";

    qDebug() << "Recipe file path: " << recipeFilePath; // Debug message to print the recipe file path

    // Initialize the container widget and grid layout for displaying recipe cards
    containerWidget = new QWidget(this);
    gridLayout = new QGridLayout(containerWidget);
    containerWidget->setLayout(gridLayout);
    ui->scrollArea->setWidget(containerWidget);
    ui->scrollArea->setWidgetResizable(true);

    // Load recipes from the JSON file
    loadRecipes();
}

// MainWindow destructor
MainWindow::~MainWindow()
{
    saveRecipes(); // Save recipes before closing the application
    delete ui;
}

// Slot for adding a new recipe
void MainWindow::on_addRecipeButton_clicked()
{
    RecipeAdd *recipeAddDialog = new RecipeAdd(this);

    ui->addRecipeButton->setEnabled(false); // Disable the add button while the dialog is open

    // Connect the recipe added signal to the handler
    connect(recipeAddDialog, &RecipeAdd::recipeAdded, this, &MainWindow::handleRecipeAdded);
    // Connect the rejected signal to the handler
    connect(recipeAddDialog, &RecipeAdd::rejected, this, &MainWindow::handleRecipeDialogClosed);

    recipeAddDialog->show();
}

// Handler for adding a new recipe
void MainWindow::handleRecipeAdded(const QString &name, const QString &description, const QString &pic, const QString &recipe)
{
    // Create a new RecipeCard and connect its signals to the appropriate handlers
    RecipeCard *newRecipe = RecipeCard::createRecipeCard(name, description, pic, recipe, this);
    connect(newRecipe, &RecipeCard::recipeDeleted, this, &MainWindow::handleRecipeDeleted);
    connect(newRecipe, &RecipeCard::recipeEdited, this, &MainWindow::handleRecipeEdited);

    // Add the new RecipeCard to the grid layout
    int count = gridLayout->count();
    int column = count % 4;
    int row = count / 4;

    gridLayout->addWidget(newRecipe, row, column);

    ui->addRecipeButton->setEnabled(true); // Re-enable the add button
}

// Handler for deleting a recipe
void MainWindow::handleRecipeDeleted(RecipeCard *recipeCard)
{
    gridLayout->removeWidget(recipeCard); // Remove the widget from the layout
    recipeCard->deleteLater(); // Delete the widget from memory

    // Update the layout after removing the widget
    updateLayout();
}

// Handler for when the recipe dialog is closed
void MainWindow::handleRecipeDialogClosed()
{
    ui->addRecipeButton->setEnabled(true); // Re-enable the add button
}

// Slot for handling search text changes
void MainWindow::on_searchLineEdit_textChanged(const QString &arg1)
{
    // Iterate through the children of the container widget
    for (int i = 0; i < containerWidget->children().size(); ++i) {
        QWidget *widget = qobject_cast<QWidget*>(containerWidget->children().at(i));
        RecipeCard *recipeCard = qobject_cast<RecipeCard*>(widget);
        if (recipeCard) {
            // Check if the recipe name or description matches the search text
            bool match = recipeCard->getRecipeName().contains(arg1, Qt::CaseInsensitive) || recipeCard->getRecipeDescription().contains(arg1, Qt::CaseInsensitive);
            recipeCard->setVisible(match);
        }
    }
    updateLayout(); // Update the layout to reflect the changes
}

// Load recipes from the JSON file
void MainWindow::loadRecipes()
{
    QFile file(recipeFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for reading:" << recipeFilePath;
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    QJsonArray recipeArray = document.array();

    // Iterate through the JSON array and create RecipeCards
    for (const QJsonValue &value : recipeArray) {
        QJsonObject obj = value.toObject();
        QString name = obj["name"].toString();
        QString description = obj["description"].toString();
        QString pic = obj["pic"].toString();
        QString recipe = obj["recipe"].toString();

        // Create a new RecipeCard and add it to the grid layout
        RecipeCard *newRecipe = RecipeCard::createRecipeCard(name, description, pic, recipe, this);
        connect(newRecipe, &RecipeCard::recipeDeleted, this, &MainWindow::handleRecipeDeleted);
        connect(newRecipe, &RecipeCard::recipeEdited, this, &MainWindow::handleRecipeEdited);

        int count = gridLayout->count();
        int column = count % 4;
        int row = count / 4;

        gridLayout->addWidget(newRecipe, row, column);
    }
}

// Save recipes to the JSON file
void MainWindow::saveRecipes() const
{
    QJsonArray recipeArray;
    // Iterate through the children of the container widget
    for (int i = 0; i < containerWidget->children().size(); ++i) {
        QWidget *widget = qobject_cast<QWidget*>(containerWidget->children().at(i));
        RecipeCard *recipeCard = qobject_cast<RecipeCard*>(widget);
        if (recipeCard) {
            // Create a JSON object for each recipe
            QJsonObject obj;
            obj["name"] = recipeCard->getRecipeName();
            obj["description"] = recipeCard->getRecipeDescription();
            obj["pic"] = recipeCard->getRecipeImagePath();
            obj["recipe"] = recipeCard->getRecipeText();

            recipeArray.append(obj);
        }
    }

    QJsonDocument document(recipeArray);
    QFile file(recipeFilePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.write(document.toJson());
        file.close();
    } else {
        qDebug() << "Could not open file for writing:" << recipeFilePath;
    }
}

// Handler for editing a recipe
void MainWindow::handleRecipeEdited(const QString &originalName, const QString &name, const QString &description, const QString &imagePath, const QString &recipe)
{
    // Update the recipe details in the UI
    for (int i = 0; i < containerWidget->children().size(); ++i) {
        QWidget *widget = qobject_cast<QWidget*>(containerWidget->children().at(i));
        RecipeCard *recipeCard = qobject_cast<RecipeCard*>(widget);
        if (recipeCard && recipeCard->getRecipeName() == originalName) {
            recipeCard->setRecipe(name, description, imagePath, recipe);
        }
    }

    // Save the updated recipes
    saveRecipes();
}

// Update the layout of the recipe cards
void MainWindow::updateLayout()
{
    // Remove all items from the layout
    QLayoutItem *item;
    while ((item = gridLayout->takeAt(0)) != nullptr) {
        delete item;
    }

    // Re-add all visible widgets to the layout
    int visibleCount = 0;
    for (int i = 0; i < containerWidget->children().size(); ++i) {
        QWidget *widget = qobject_cast<QWidget*>(containerWidget->children().at(i));
        if (widget && widget->isVisible()) {
            int column = visibleCount % 4;
            int row = visibleCount / 4;
            gridLayout->addWidget(widget, row, column);
            visibleCount++;
        }
    }
}
