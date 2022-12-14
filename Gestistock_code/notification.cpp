#include "notification.h"




#include <QSystemTrayIcon>
#include<QString>
Notification::Notification()
{

}

void Notification::notification_ajoutproduit()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

    //notifyIcon->setIcon(QIcon("C:/Users/asus/Desktop/pdf/logo_projet"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des produit ","nouveau produit est ajouté ",QSystemTrayIcon::Information,15000);
}



void Notification::notification_supprimerproduit(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des produits ","Un produit est supprimé",QSystemTrayIcon::Information,15000);
}





void Notification::notification_modifierproduit(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des produits ","nouveau produit est modifié",QSystemTrayIcon::Information,15000);

}

