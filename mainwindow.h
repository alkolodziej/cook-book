#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QGridLayout>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "recipecard.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// MainWindow class definition
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor
    MainWindow(QWidget *parent = nullptr);
    // Destructor
    ~MainWindow();

private slots:
    // Slot for handling the Add Recipe button click
    void on_addRecipeButton_clicked();
    // Slot for handling the addition of a new recipe
    void handleRecipeAdded(const QString &name, const QString &description, const QString &pic, const QString &recipe);
    // Slot for handling the closing of the recipe dialog
    void handleRecipeDialogClosed();
    // Slot for handling the deletion of a recipe
    void handleRecipeDeleted(RecipeCard *recipeCard);
    // Slot for handling text changes in the search line edit
    void on_searchLineEdit_textChanged(const QString &arg1);
    // Slot for handling the editing of a recipe
    void handleRecipeEdited(const QString &originalName, const QString &name, const QString &description, const QString &imagePath, const QString &recipe);

private:
    Ui::MainWindow *ui;                    // User interface object
    QScrollArea *scrollArea;               // Scroll area for the recipes
    QWidget *containerWidget;              // Container widget for the grid layout
    QGridLayout *gridLayout;               // Grid layout to arrange RecipeCard widgets
    QString recipeFilePath;                // File path to save/load recipes

    // Method to load recipes from a file
    void loadRecipes();
    // Method to save recipes to a file
    void saveRecipes() const;
    // Method to update the layout of the recipes
    void updateLayout();
};

#endif // MAINWINDOW_H
