#ifndef RECIPEADD_H
#define RECIPEADD_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class RecipeAdd;
}

// RecipeAdd class definition
class RecipeAdd : public QDialog
{
    Q_OBJECT

public:
    // Constructor
    explicit RecipeAdd(QWidget *parent = nullptr);
    // Destructor
    ~RecipeAdd();

signals:
    // Signal emitted when a recipe is added
    void recipeAdded(const QString &name, const QString &description, const QString &pic, const QString &recipe);
    // Signal emitted when the dialog is closed
    void rejected();

protected:
    // Override closeEvent to handle dialog close event
    void closeEvent(QCloseEvent *event) override;

private slots:
    // Slot for handling the Cancel button click
    void handleCancelButton();
    // Slot for handling the Save button click
    void handleSaveButton();

private:
    Ui::RecipeAdd *ui;  // User interface object
};

#endif // RECIPEADD_H
