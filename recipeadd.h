#ifndef RECIPEADD_H
#define RECIPEADD_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class RecipeAdd;
}

class RecipeAdd : public QDialog
{
    Q_OBJECT

public:
    explicit RecipeAdd(QWidget *parent = nullptr);
    ~RecipeAdd();

signals:
    void recipeAdded(const QString &name, const QString &description, const QString &pic, const QString &recipe);
    void rejected();

protected:
    void closeEvent(QCloseEvent *event) override;  // Override closeEvent

private slots:
    void handleCancelButton();
    void handleSaveButton();

private:
    Ui::RecipeAdd *ui;
};

#endif // RECIPEADD_H
