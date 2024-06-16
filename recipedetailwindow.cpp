#include "recipedetailwindow.h"
#include "ui_recipedetailwindow.h"

RecipeDetailWindow::RecipeDetailWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeDetailWindow)
{
    ui->setupUi(this);
    connect(ui->editButton, &QPushButton::clicked, this, &RecipeDetailWindow::on_editButton_clicked);
    connect(ui->saveButton, &QPushButton::clicked, this, &RecipeDetailWindow::on_saveButton_clicked);
}

RecipeDetailWindow::~RecipeDetailWindow()
{
    delete ui;
}

void RecipeDetailWindow::setRecipeDetails(const QString &name, const QString &description, const QString &imagePath, const QString &recipe)
{
    originalName = name;  // Add this line
    ui->recipeNameLineEdit->setText(name);
    ui->recipeDescriptionBrowser->setText(description);
    ui->recipeTextBrowser->setText(recipe);

    currentImagePath = imagePath;
    QPixmap pixmap(imagePath);
    ui->recipeImageLabel->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Disable editing initially
    ui->recipeNameLineEdit->setReadOnly(true);
    ui->recipeDescriptionBrowser->setReadOnly(true);
    ui->recipeTextBrowser->setReadOnly(true);
}

void RecipeDetailWindow::on_editButton_clicked()
{
    // Enable editing
    ui->recipeNameLineEdit->setReadOnly(false);
    ui->recipeDescriptionBrowser->setReadOnly(false);
    ui->recipeTextBrowser->setReadOnly(false);

    // Enable save button
    ui->saveButton->setEnabled(true);
}

void RecipeDetailWindow::on_saveButton_clicked()
{
    // Save the edited details
    QString editedName = ui->recipeNameLineEdit->text();
    QString editedDescription = ui->recipeDescriptionBrowser->toPlainText();
    QString editedRecipe = ui->recipeTextBrowser->toPlainText();
    // Emit the signal to notify that the recipe was edited
    emit recipeEdited(originalName, editedName, editedDescription, currentImagePath, editedRecipe);
    // Disable editing again
    ui->recipeNameLineEdit->setReadOnly(true);
    ui->recipeDescriptionBrowser->setReadOnly(true);
    ui->recipeTextBrowser->setReadOnly(true);

    // Disable save button
    ui->saveButton->setEnabled(false);
}
