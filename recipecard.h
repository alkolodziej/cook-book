#ifndef RECIPECARD_H
#define RECIPECARD_H

#include <QWidget>
#include <QPixmap>

namespace Ui {
class RecipeCard;
}

class RecipeCard : public QWidget
{
    Q_OBJECT

public:
    explicit RecipeCard(QWidget *parent = nullptr);
    ~RecipeCard();

    void setRecipe(const QString &name, const QString &description, const QString &image, const QString &recipe);

    QString getRecipeName() const;
    QString getRecipeDescription() const;
    QString getRecipeImagePath() const;
    QString getRecipeText() const;

    static RecipeCard* createRecipeCard(const QString &name, const QString &description, const QString &imagePath, const QString &recipe, QWidget *parent = nullptr);

signals:
    void recipeDeleted(RecipeCard *recipeCard); // Signal to notify deletion

private slots:
    void on_pushButtonDelete_clicked(); // Slot for handling delete button click
    void on_pushButtonDownload_clicked(); // Slot for handling download button click

private:
    Ui::RecipeCard *ui;
    QString recipeName;
    QString recipeDescription;
    QString imagePath; // Save image path as string
    QString recipeText;
};

#endif // RECIPECARD_H
