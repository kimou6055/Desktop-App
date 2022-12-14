#include "menu2.h"
#include "ui_menu2.h"
#include<QSystemTrayIcon>

menu2::menu2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menu2)
{
    ui->setupUi(this);
    w= new MainWindow(this);
}

menu2::~menu2()
{
    delete ui;
}
void menu2::on_Menu_fournisseurs_clicked()
    {
      //QDialog::hide();

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->setIcon(QIcon("C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/charte graphique/icon.gif"));

     notifyIcon->showMessage("Menu ","Gestion des fournisseurs ouverte",QSystemTrayIcon::Information,15000);

     w->show();

    }
