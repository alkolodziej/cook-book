#include "recipeadd.h"
#include "ui_recipeadd.h"

RecipeAdd::RecipeAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecipeAdd)
{
    ui->setupUi(this);
}

RecipeAdd::~RecipeAdd()
{
    delete ui;
}

void RecipeAdd::on_saveButton_clicked()
{
    QString recipeName = ui->lineEdit->text();
    QString recipeDescription = ui->textEdit->toPlainText();

    if (!recipeName.isEmpty() && !recipeDescription.isEmpty())
    {
        // Emitowanie sygnału z danymi o nowym przepisie
        emit recipeAdded(recipeName, recipeDescription);
        close();
    }
    else
    {
        QMessageBox::warning(this, "Błąd", "Wypełnij wszystkie pola przed zapisaniem przepisu.");
    }
}

void RecipeAdd::on_cancelButton_clicked()
{
    emit rejected();
    close();
}

