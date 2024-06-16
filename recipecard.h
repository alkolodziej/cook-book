#ifndef RECIPECARD_H
#define RECIPECARD_H

#include <QWidget>
#include <QPixmap>

namespace Ui {
class RecipeCard;
}

// RecipeCard class definition
class RecipeCard : public QWidget
{
    Q_OBJECT

public:
    // Constructor
    explicit RecipeCard(QWidget *parent = nullptr);
    // Destructor
    ~RecipeCard();

    // Set the recipe details
    void setRecipe(const QString &name, const QString &description, const QString &image, const QString &recipe);

    // Get the recipe name
    QString getRecipeName() const;
    // Get the recipe description
    QString getRecipeDescription() const;
    // Get the recipe image path
    QString getRecipeImagePath() const;
    // Get the recipe text
    QString getRecipeText() const;

    // Static method to create a new RecipeCard
    static RecipeCard* createRecipeCard(const QString &name, const QString &description, const QString &imagePath, const QString &recipe, QWidget *parent = nullptr);

signals:
    // Signal to notify that the recipe card is deleted
    void recipeDeleted(RecipeCard *recipeCard);
    // Signal to notify that the recipe card is edited
    void recipeEdited(const QString &originalName, const QString &name, const QString &description, const QString &imagePath, const QString &recipe);

private slots:
    // Slot for handling delete button click
    void on_pushButtonDelete_clicked();
    // Slot for handling download button click
    void on_pushButtonDownload_clicked();
    // Slot for handling see recipe button click
    void on_pushButtonSeeRecipe_clicked();

private:
    Ui::RecipeCard *ui;  // User interface object
    QString recipeName;  // Recipe name
    QString recipeDescription;  // Recipe description
    QString imagePath;  // Path to the recipe image
    QString recipeText;  // Recipe text
};

#endif // RECIPECARD_H
