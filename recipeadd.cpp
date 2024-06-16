#include "recipeadd.h"
#include "ui_recipeadd.h"

// Constructor for RecipeAdd dialog
RecipeAdd::RecipeAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecipeAdd)
{
    ui->setupUi(this);

    // Explicitly connect UI buttons to their respective slot functions
    connect(ui->cancelButton, &QPushButton::clicked, this, &RecipeAdd::handleCancelButton);
    connect(ui->saveButton, &QPushButton::clicked, this, &RecipeAdd::handleSaveButton);
}

// Destructor for RecipeAdd dialog
RecipeAdd::~RecipeAdd()
{
    delete ui;
}

// Slot function to handle the save button click
void RecipeAdd::handleSaveButton()
{
    // Retrieve text from input fields
    QString recipeName = ui->lineEdit->text();
    QString recipeDescription = ui->lineEdit_2->text();
    QString recipePic = ui->lineEdit_3->text();
    QString recipe = ui->textEdit->toPlainText();

    // Check if all fields are filled
    if (!recipeName.isEmpty() && !recipeDescription.isEmpty() && !recipePic.isEmpty() && !recipe.isEmpty())
    {
        // Emit the recipeAdded signal with the gathered information
        emit recipeAdded(recipeName, recipeDescription, recipePic, recipe);
        close(); // Close the dialog
    }
    else
    {
        // Show a warning message if any field is empty
        QMessageBox::warning(this, "Error", "Please fill in all fields before saving the recipe.");
    }
}

// Slot function to handle the cancel button click
void RecipeAdd::handleCancelButton()
{
    emit rejected(); // Emit the rejected signal
    close(); // Close the dialog
}

// Handle the event when the dialog is closed
void RecipeAdd::closeEvent(QCloseEvent *event)
{
    emit rejected(); // Emit the rejected signal
    QDialog::closeEvent(event);  // Call the base class implementation to properly handle the close event
}
