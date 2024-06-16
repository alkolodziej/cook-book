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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addRecipeButton_clicked();
    void handleRecipeAdded(const QString &name, const QString &description, const QString &pic, const QString &recipe);
    void handleRecipeDialogClosed();
    void handleRecipeDeleted(RecipeCard *recipeCard);
    void on_searchLineEdit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QScrollArea *scrollArea;
    QWidget *containerWidget;
    QGridLayout *gridLayout;
    QString recipeFilePath;

    void loadRecipes();
    void saveRecipes() const;
    void updateLayout();
};

#endif // MAINWINDOW_H
