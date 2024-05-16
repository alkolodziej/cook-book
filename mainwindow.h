#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "recipecard.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addRecipeButton_clicked();

private:
    Ui::MainWindow *ui;
    int column;
    int row;
};
#endif // MAINWINDOW_H
