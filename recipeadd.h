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
    void recipeAdded(const QString &name, const QString &description);
    void rejected();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::RecipeAdd *ui;
};

#endif // RECIPEADD_H
