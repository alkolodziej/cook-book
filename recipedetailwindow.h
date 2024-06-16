#ifndef RECIPEDETAILWINDOW_H
#define RECIPEDETAILWINDOW_H

#include <QWidget>

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

private slots:
    void on_editButton_clicked();
    void on_saveButton_clicked();

signals:
    void recipeEdited(const QString &originalName, const QString &name, const QString &description, const QString &imagePath, const QString &recipe);

private:
    Ui::RecipeDetailWindow *ui;
    QString currentImagePath;
    QString originalName;  // Add this line
};

#endif // RECIPEDETAILWINDOW_H
