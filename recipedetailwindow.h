#ifndef RECIPEDETAILWINDOW_H
#define RECIPEDETAILWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QTextBrowser>

namespace Ui {
class RecipeDetailWindow;
}

class RecipeDetailWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RecipeDetailWindow(QWidget *parent = nullptr);
    ~RecipeDetailWindow();

    void setRecipeDetails(const QString &name, const QString &description, const QString &imagePath, const QString &recipe);

private:
    Ui::RecipeDetailWindow *ui;
};

#endif // RECIPEDETAILWINDOW_H
