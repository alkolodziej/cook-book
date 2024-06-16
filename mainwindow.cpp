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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Define the file path for storing the recipes
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(appDataPath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    recipeFilePath = appDataPath + "/recipes.json";

    qDebug() << "Recipe file path: " << recipeFilePath; // Debug message

    // Initialize container widget and layout
    containerWidget = new QWidget(this);
    gridLayout = new QGridLayout(containerWidget);
    containerWidget->setLayout(gridLayout);
    ui->scrollArea->setWidget(containerWidget);
    ui->scrollArea->setWidgetResizable(true);

    // Load recipes from the JSON file
    loadRecipes();
}

MainWindow::~MainWindow()
{
    saveRecipes();
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
    connect(newRecipe, &RecipeCard::recipeDeleted, this, &MainWindow::handleRecipeDeleted);

    int count = gridLayout->count();
    int column = count % 4;
    int row = count / 4;

    gridLayout->addWidget(newRecipe, row, column);

    ui->addRecipeButton->setEnabled(true);
}

void MainWindow::handleRecipeDeleted(RecipeCard *recipeCard)
{
    gridLayout->removeWidget(recipeCard); // Remove widget from layout
    recipeCard->deleteLater(); // Delete widget from memory

    // Update layout after removing widget
    updateLayout();
}

void MainWindow::handleRecipeDialogClosed()
{
    ui->addRecipeButton->setEnabled(true);
}

void MainWindow::on_searchLineEdit_textChanged(const QString &arg1)
{
    for (int i = 0; i < containerWidget->children().size(); ++i) {
        QWidget *widget = qobject_cast<QWidget*>(containerWidget->children().at(i));
        RecipeCard *recipeCard = qobject_cast<RecipeCard*>(widget);
        if (recipeCard) {
            bool match = recipeCard->getRecipeName().contains(arg1, Qt::CaseInsensitive) || recipeCard->getRecipeDescription().contains(arg1, Qt::CaseInsensitive);
            recipeCard->setVisible(match);
        }
    }
    updateLayout();
}

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

    for (const QJsonValue &value : recipeArray) {
        QJsonObject obj = value.toObject();
        QString name = obj["name"].toString();
        QString description = obj["description"].toString();
        QString pic = obj["pic"].toString();
        QString recipe = obj["recipe"].toString();

        RecipeCard *newRecipe = RecipeCard::createRecipeCard(name, description, pic, recipe, this);
        connect(newRecipe, &RecipeCard::recipeDeleted, this, &MainWindow::handleRecipeDeleted);

        int count = gridLayout->count();
        int column = count % 4;
        int row = count / 4;

        gridLayout->addWidget(newRecipe, row, column);
    }
}

void MainWindow::saveRecipes() const
{
    QJsonArray recipeArray;
    for (int i = 0; i < containerWidget->children().size(); ++i) {
        QWidget *widget = qobject_cast<QWidget*>(containerWidget->children().at(i));
        RecipeCard *recipeCard = qobject_cast<RecipeCard*>(widget);
        if (recipeCard) {
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

void MainWindow::handleRecipeEdited(const QString &name, const QString &description, const QString &imagePath, const QString &recipe)
{
    // Update the recipe details in the UI
    for (int i = 0; i < containerWidget->children().size(); ++i) {
        QWidget *widget = qobject_cast<QWidget*>(containerWidget->children().at(i));
        RecipeCard *recipeCard = qobject_cast<RecipeCard*>(widget);
        if (recipeCard && recipeCard->getRecipeName() == name) {
            recipeCard->setRecipe(name, description, imagePath, recipe);
        }
    }

    // Save the updated recipes
    saveRecipes();
}


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
