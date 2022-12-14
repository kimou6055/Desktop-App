#ifndef MENU2_H
#define MENU2_H

#include <QDialog>
#include <QMainWindow>
#include "mainwindow.h"

namespace Ui {
class menu2;
}

class menu2 : public QDialog
{
    Q_OBJECT

public:
    explicit menu2(QWidget *parent = nullptr);
    ~menu2();


private slots:
    void on_Menu_fournisseurs_clicked();


private:
    Ui::menu2 *ui;
    MainWindow* w;
};

#endif // MENU2_H
