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

    void setRecipeName(const QString &name);
    void setRecipeDescription(const QString &description);
    void setRecipeImage(const QPixmap &image);

    static RecipeCard* createRecipeCard(const QString &name, const QString &description, const QString &imagePath, QWidget *parent = nullptr);

private:
    Ui::RecipeCard *ui;
};

#endif // RECIPECARD_H
