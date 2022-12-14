
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include "menu.h"
#include<QSystemTrayIcon>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test=c.createconnect();


    menu m_menu;
   a.setStyle("fusion");



     if(test)
         m_menu.exec();

       else
     {QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
         notifyIcon->show();
        notifyIcon->setIcon(QIcon("C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/qt/Fournisseurs/charte_graphique/icon.gif"));
        notifyIcon->showMessage("Base de donnée ","database is not open",QSystemTrayIcon::Information,15000);}





   return a.exec();
}
