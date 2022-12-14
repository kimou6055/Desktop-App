#include "menu.h"
#include "ui_menu.h"
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include<QSystemTrayIcon>
#include<QDesktopServices>
#include<QPrintDialog>
#include<QVBoxLayout>


#include<QDateTime>
#include<QTimer>
menu::menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
    this->setWindowTitle("Login");
    QObject::connect(ui->welcome_se_connecter, SIGNAL(clicked()), this, SLOT(on_welcome_se_connecter_clicked()));
    w= new MainWindow(this);

}

menu::~menu()
{
    delete ui;
}



void menu::on_welcome_se_connecter_clicked()
{

    QString username=ui->welcome_id->text();
    QString password=ui->welcome_mdp->text();
if ((!ui->welcome_id->text().isEmpty()) && (!ui->welcome_mdp->text().isEmpty()))
{
QMessageBox msgBox;
//call checking from main.cpp


if (checkLogin(username, password) == 0 )
{
qDebug() << "Success! Close dialog box";
QDialog::close();

QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
notifyIcon->show();
notifyIcon->setIcon(QIcon("C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/qt/Fournisseurs/charte_graphique/icon.gif"));

 notifyIcon->showMessage("Base de donnée ","database is open",QSystemTrayIcon::Information,15000);

w->show();


}else
{


    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
   notifyIcon->setIcon(QIcon("C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/qt/Fournisseurs/charte_graphique/icon.gif"));

   notifyIcon->showMessage("Login ","echec de connexion vérifiez vos paramètres",QSystemTrayIcon::Information,15000);


;
}
}
else
{
qDebug() << "Invalid credential provided!";

}
}

int menu::checkLogin(QString a, QString b)
{

QString aa = a;
QString bb = b;
QString var,var2;




QSqlQuery query;
query.prepare("SELECT login from ADMIN_GENERAL WHERE login = '"+aa+"' AND mdp =  '"+bb+"' ");
query.bindValue(":login", var);
if (query.exec() && query.next()) {
    var=query.value(0).toString();
}


query.prepare("SELECT mdp from ADMIN_GENERAL WHERE login = '"+aa+"' AND mdp =  '"+bb+"' ");
query.bindValue(":mdp", var2);
if (query.exec() && query.next()) {
    var2=query.value(0).toString();
}


if(var==aa && var2==bb)
{
    qDebug() << "Login success!";
     return 0;

}
else
{
    qDebug() << "Login FAILED!";
    return 1;
}
}

void menu::on_Prob_connexion_clicked()
    {
    QString link="https://mail.google.com/mail/u/0/#inbox?compose=GTvVlcRwPxHsPdhHVjkvqHPPNdbzDBgvRdjJFngrHSJdFKmKkfpRnbXpDFjLNMXSSlrWcsrVWVbjx";
    QDesktopServices::openUrl(QUrl(link));
    }




