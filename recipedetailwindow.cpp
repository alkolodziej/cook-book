#include "recipedetailwindow.h"
#include "ui_recipedetailwindow.h"

// Constructor for RecipeDetailWindow
RecipeDetailWindow::RecipeDetailWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipeDetailWindow)
{
    ui->setupUi(this);

    // Connect edit button click signal to slot
    connect(ui->editButton, &QPushButton::clicked, this, &RecipeDetailWindow::on_editButton_clicked);
    // Connect save button click signal to slot
    connect(ui->saveButton, &QPushButton::clicked, this, &RecipeDetailWindow::on_saveButton_clicked);
}

// Destructor for RecipeDetailWindow
RecipeDetailWindow::~RecipeDetailWindow()
{
    delete ui;
}

// Set initial recipe details in the UI
void RecipeDetailWindow::setRecipeDetails(const QString &name, const QString &description, const QString &imagePath, const QString &recipe)
{
    originalName = name;  // Store the original recipe name
    ui->recipeNameLineEdit->setText(name);  // Set recipe name in the line edit
    ui->recipeDescriptionBrowser->setText(description);  // Set recipe description in the browser
    ui->recipeTextBrowser->setText(recipe);  // Set recipe text in the browser

    currentImagePath = imagePath;  // Store the current image path
    QPixmap pixmap(imagePath);  // Load image from path
    ui->recipeImageLabel->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));  // Display image in label

    // Disable editing initially
    ui->recipeNameLineEdit->setReadOnly(true);
    ui->recipeDescriptionBrowser->setReadOnly(true);
    ui->recipeTextBrowser->setReadOnly(true);
}

// Slot for handling edit button click
void RecipeDetailWindow::on_editButton_clicked()
{
    // Enable editing
    ui->recipeNameLineEdit->setReadOnly(false);
    ui->recipeDescriptionBrowser->setReadOnly(false);
    ui->recipeTextBrowser->setReadOnly(false);

    // Enable save button
    ui->saveButton->setEnabled(true);
}

// Slot for handling save button click
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
