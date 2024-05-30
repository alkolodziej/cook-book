#include "recipeadd.h"
#include "ui_recipeadd.h"

RecipeAdd::RecipeAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecipeAdd)
{
    ui->setupUi(this);

    // Explicitly connect signals to slots
    connect(ui->cancelButton, &QPushButton::clicked, this, &RecipeAdd::handleCancelButton);
    connect(ui->saveButton, &QPushButton::clicked, this, &RecipeAdd::handleSaveButton);
}

RecipeAdd::~RecipeAdd()
{
    delete ui;
}

void RecipeAdd::handleSaveButton()
{
    QString recipeName = ui->lineEdit->text();
    QString recipeDescription = ui->textEdit->toPlainText();

    if (!recipeName.isEmpty() && !recipeDescription.isEmpty())
    {
        emit recipeAdded(recipeName, recipeDescription);
        close();
    }
    else
    {
        QMessageBox::warning(this, "Error", "Please fill in all fields before saving the recipe.");
    }
}

void RecipeAdd::handleCancelButton()
{
    emit rejected();
    close();
}

void RecipeAdd::closeEvent(QCloseEvent *event)
{
    emit rejected();
    QDialog::closeEvent(event);  // Call the base class implementation
}
