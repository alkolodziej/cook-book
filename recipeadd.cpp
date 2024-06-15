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
    QString recipeDescription = ui->lineEdit_2->text();
    QString recipePic = ui->lineEdit_3->text();
    QString recipe = ui->textEdit->toPlainText();

    if (!recipeName.isEmpty() && !recipeDescription.isEmpty() && !recipePic.isEmpty() && !recipe.isEmpty())
    {
        emit recipeAdded(recipeName, recipeDescription, recipePic, recipe);
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
