#ifndef RECIPEDETAILWINDOW_H
#define RECIPEDETAILWINDOW_H

#include <QWidget>

namespace Ui {
class RecipeDetailWindow;
}

// RecipeDetailWindow class definition
class RecipeDetailWindow : public QWidget
{
    Q_OBJECT

public:
    // Constructor
    explicit RecipeDetailWindow(QWidget *parent = nullptr);
    // Destructor
    ~RecipeDetailWindow();
    // Set the recipe details
    void setRecipeDetails(const QString &name, const QString &description, const QString &imagePath, const QString &recipe);

private slots:
    // Slot for handling edit button click
    void on_editButton_clicked();
    // Slot for handling save button click
    void on_saveButton_clicked();

signals:
    // Signal to notify that the recipe is edited
    void recipeEdited(const QString &originalName, const QString &name, const QString &description, const QString &imagePath, const QString &recipe);

private:
    Ui::RecipeDetailWindow *ui;  // User interface object
    QString currentImagePath;  // Current image path
    QString originalName;  // Original name of the recipe
};

#endif // RECIPEDETAILWINDOW_H
