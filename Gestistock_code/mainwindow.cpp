    #include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QMessageBox>
#include <QDebug>

#include<QDesktopServices>
#include<QPainter>
#include <QPrinter>
#include "fournisseurs.h"
#include "historique.h"
#include<QSystemTrayIcon>

#include <QIntValidator>
#include<QString>

#include<QVBoxLayout>

#include<QFileDialog>
#include <QSqlQuery>


#include<QPrintDialog>

#include<QVBoxLayout>

#include<QTimer>

#include <QTextStream>
#include<QDirModel>
#include<QRegularExpression>
#include <fstream>
#include <QtSvg/QSvgRenderer>
#include "qrcode.h"
#include <QValidator>
#include"notification.h"
#include "widget.h"
#include<QSqlQuery>
#include<QMessageBox>
#include<QtDebug>
#include<QObject>
#include <QWidget>
#include <QFileDialog>
#include <QTextDocument>
#include <QDebug>
#include <QtPrintSupport/QPrinter>
#include "produits.h"
#include <QString>
#include <QtDebug>
#include <QComboBox>
#include <QtWidgets>
#include <QPixmap>






//farah
using qrcodegen::QrCode;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow()
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //m= new menu2(this);
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).

     //oussama
     ui->lineEdit_CINE->setValidator(new QIntValidator(0, 999999, this));        //Controle de saisie sur le premier champ (CIN)
     //brahim
     ui->tableEmployes->setModel(E.afficher());
     ui->tab_f_BRAHIM->setModel(Fi.afficher_BRAHIM());
     ui->tab_f_2_BRAHIM->setModel(Fi.afficher_BRAHIM());
     ui->tab_fH_BRAHIM->setModel(Fi.historique_BRAHIM());

      //nour
     c.ajoutPoint();

     ui->tableView_NOUR->setModel(c.afficher());
     ui->tableView_2_NOUR->setModel(c.afficher());
     ui->comboBox_NOUR->addItem("cin");
     ui->comboBox_NOUR->addItem("nom");
     ui->comboBox_NOUR->addItem("prenom");
     ui->comboBox_NOUR->addItem("adresse");
     ui->comboBox_NOUR->addItem("email");
     ui->comboBox_NOUR->addItem("nbr_point");
     ui->comboBox_NOUR->addItem("num_telephone");
     ui->comboBox_NOUR->addItem("id_commande");

     //farah
     ui->tableView_3->setModel(p.afficherProd());
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_arduino1()
{


}


void MainWindow::on_ajouterf_clicked()
{
  ui->tableView->setModel(F.afficherf());
  ui->tableView_2->setModel(F.afficherf());

    int id=ui->l_id_fournisseur->text().toInt();
    int num=ui->l_num_fournisseur->text().toInt();

    QString nom=ui->l_nom_fournisseur->text();
    QString adresse=ui->l_adresse_fournisseur->text();
    QString logo=ui->l_adresse_fournisseur->text();
    QString categorie(ui->l_comboBox->currentText());
    //QString logo(ui->l_pushButton->currentfile());
    Historique h;
      h.save("id:"+ui->l_id_fournisseur->text(),"nom :"+ui->l_nom_fournisseur->text(),"numero telephone:"+ui->l_num_fournisseur->text());

      fournisseurs F(id, nom, adresse, categorie,logo,num);


bool test=F.ajouterf();

if(test)
{
    ui->tableView->setModel(F.afficherf()); //refresh
    ui->tableView_2->setModel(F.afficherf());
     ui->tableView->setModel(F.afficherf()); //refresh
     ui->tableView_2->setModel(F.afficherf());

     QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
     notifyIcon->show();
    notifyIcon->setIcon(QIcon("C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/qt/Fournisseurs/charte_graphique/icon.gif"));

     notifyIcon->showMessage("GESTION DES  FOURNISSEURS ","Nouveau fournisseur ajouté",QSystemTrayIcon::Information,15000);

}
ui->tableView->setModel(F.afficherf());
ui->tableView_2->setModel(F.afficherf());
}


void MainWindow::on_modifierf_clicked()
{ ui->tableView->setModel(F.afficherf());
    bool    test=F.modifierjf(ui->m_id_fournisseur->text().toInt(),ui->m_nom_fournisseur->text(),ui->m_adresse_fournisseur->text(),ui->m_comboBox_2->currentText(),ui->m_adresse_fournisseur->text(),ui->m_num_fournisseur->text().toInt());

    if (test)
          {
                  ui->tableView->setModel(F.afficherf()); //refresh
                  ui->tableView_2->setModel(F.afficherf());


              QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
              notifyIcon->show();
             notifyIcon->setIcon(QIcon("C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/qt/Fournisseurs/charte_graphique/icon.gif"));

              notifyIcon->showMessage("GESTION DES  FOURNISSEURS ","Fournisseur Modifié",QSystemTrayIcon::Information,15000);
    }
          else{
          QMessageBox::critical(nullptr,("ERROR404"),
                                  QObject::tr("modification non réussie"),
                                  QMessageBox::Cancel);}


    ui->tableView->setModel(F.afficherf());
    ui->tableView_2->setModel(F.afficherf());


}



void MainWindow::on_supprimerf_clicked()
{

    fournisseurs F1; F1.setid_fournisseurs(ui->S_recherche_supp->text().toInt());
    bool test=F1.supprimerf(F1.getid_fournisseurs());

    if(test)
    {
        ui->tableView->setModel(F.afficherf());
        ui->tableView_2->setModel(F.afficherf());



        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
        notifyIcon->show();
       notifyIcon->setIcon(QIcon("C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/qt/Fournisseurs/charte_graphique/icon.gif"));

        notifyIcon->showMessage("GESTION DES  FOURNISSEURS ","Fournisseur Supprimé",QSystemTrayIcon::Information,15000);
    }
    else
          {QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
          notifyIcon->showMessage("GESTION DES  FOURNISSEURS ","echec de suppression",QSystemTrayIcon::Information,15000);}

     ui->tableView->setModel(F.afficherf());
     ui->tableView_2->setModel(F.afficherf());

}
void MainWindow::on_historiquef_clicked()
    {
    QString link="C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/qt/Fournisseurs/integration/test/his.txt";
    QDesktopServices::openUrl(QUrl(link));
    }



void MainWindow::on_trierf_clicked()
{
        QSqlQueryModel * model= new QSqlQueryModel();



           model->setQuery("select id_fournisseurs, nom, adresse, categorie, num from FOURNISSEURS order by "+ui->A_comboBox->currentText()+" ");

           model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_fournisseur"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse "));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("categorie "));
           model->setHeaderData(4, Qt::Horizontal, QObject::tr("num"));

                   ui->tableView->setModel(model);
                    ui->tableView->show();

                    ;
}

void MainWindow::on_generer_pdf_clicked()
{
        fournisseurs f;
        f.genererPDF();
        QString link="C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/qt/Fournisseurs/integration/test/liste.pdf";
        QDesktopServices::openUrl(QUrl(link));
}
void MainWindow::on_A_recherche_textChanged()
{
    fournisseurs f;
        if(ui->A_recherche->text() == "")
            {
                ui->tableView->setModel(f.afficherf());
            }
            else
            {
                 ui->tableView->setModel(f.rechercherf(ui->A_recherche->text()));
            }

}

void MainWindow::on_S_recherche_textChanged()
{
    fournisseurs f;
        if(ui->S_recherche->text() == "")
            {
                ui->tableView_2->setModel(f.afficherf());
            }
            else
            {
                 ui->tableView_2->setModel(f.rechercherf(ui->S_recherche->text()));
            }

}
void MainWindow::on_imprimerf_clicked()
    {
    QPrinter printer;
    printer.setPrinterName("test");
    QPrintDialog dialog(&printer,this);
    if (dialog.exec()==QDialog::Rejected) return;
    }


void MainWindow::on_m_id_fournisseur_textChanged()
{

    QSqlQuery query;
    query.prepare("SELECT  nom FROM FOURNISSEURS WHERE id_fournisseurs= "+ui->m_id_fournisseur->text()+"");
    query.bindValue(":nom", ui->m_nom_fournisseur->text());
    if (query.exec() && query.next()) {
        ui->m_nom_fournisseur->setText(query.value(0).toString());
    }

    query.prepare("SELECT  adresse FROM FOURNISSEURS WHERE id_fournisseurs= "+ui->m_id_fournisseur->text()+"");
    query.bindValue(":adresse", ui->m_adresse_fournisseur->text());
    if (query.exec() && query.next()) {
        ui->m_adresse_fournisseur->setText(query.value(0).toString());
    }
    query.prepare("SELECT  categorie FROM FOURNISSEURS WHERE id_fournisseurs= "+ui->m_id_fournisseur->text()+"");
    query.bindValue(":categorie", ui->m_comboBox_2->currentText());
    if (query.exec() && query.next()) {
        ui->m_comboBox_2->setCurrentText(query.value(0).toString());
    }
    query.prepare("SELECT  num FROM FOURNISSEURS WHERE id_fournisseurs= "+ui->m_id_fournisseur->text()+"");
    query.bindValue(":num", ui->m_num_fournisseur->text());
    if (query.exec() && query.next()) {
        ui->m_num_fournisseur->setText(query.value(0).toString());
    }




}

void MainWindow::on_revenir_menu_clicked()
    {
     QMainWindow::close();

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->setIcon(QIcon("C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/qt/Fournisseurs/charte_graphique/icon.gif"));

     notifyIcon->showMessage("Menu ","Gestion des fournisseurs ouverte",QSystemTrayIcon::Information,15000);

    }



void MainWindow::on_Hide_fournisseurs_se_connecter_clicked()
{

    QString username=ui->Hide_fournisseurs_user->text();
    QString password=ui->Hide_fournisseurs_mdp->text();
    QString table="ADMIN_FOURNISSEURS";
     //data=A.read_from_arduino();
    //qDebug() << data;
   // if (((!ui->Hide_fournisseurs_user->text().isEmpty()) && (!ui->Hide_fournisseurs_mdp->text().isEmpty()))||data=="1")
if ((!ui->Hide_fournisseurs_user->text().isEmpty()) && (!ui->Hide_fournisseurs_mdp->text().isEmpty()))
{

QMessageBox msgBox;
//call checking from main.cpp

if (checkLogin(username, password,table) == 0)
{
qDebug() << "Success! Close dialog box";

QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
notifyIcon->show();
notifyIcon->setIcon(QIcon("C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/qt/Fournisseurs/charte_graphique/icon.gif"));

 notifyIcon->showMessage("Authentification éffectuée ","Gestion des Fournisseurs ouverte",QSystemTrayIcon::Information,15000);

    ui->Hide_fournisseurs_phrase->setVisible(false);
    ui->Hide_fournisseurs_username->setVisible(false);
    ui->Hide_fournisseurs_user->setVisible(false);
    ui->Hide_fournisseurs_mot_de_passe->setVisible(false);
    ui->Hide_fournisseurs_mdp->setVisible(false);
    ui->Hide_fournisseurs_se_connecter->setVisible(false);
    ui->Hide_fournisseurs->setVisible(false);
}else
{


    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
   notifyIcon->setIcon(QIcon("C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/qt/Fournisseurs/charte_graphique/icon.gif"));

   notifyIcon->showMessage("Authentification non effectuée ","echec de connexion vérifiez vos paramètres",QSystemTrayIcon::Information,15000);


;
}
}
else
{
qDebug() << "Invalid credential provided!";

}
}

void MainWindow::on_Hide_fournisseurs_verouiller_clicked()
{
     // A.write_to_arduino("0");
    ui->Hide_fournisseurs->setVisible(true);
    ui->Hide_fournisseurs_phrase->setVisible(true);
    ui->Hide_fournisseurs_username->setVisible(true);
    ui->Hide_fournisseurs_user->setVisible(true);
    ui->Hide_fournisseurs_mot_de_passe->setVisible(true);
    ui->Hide_fournisseurs_mdp->setVisible(true);
    ui->Hide_fournisseurs_se_connecter->setVisible(true);
     ui->Hide_fournisseurs_user->setText("");
     ui->Hide_fournisseurs_mdp->setText("");
}

void MainWindow::on_Hide_fournisseurs_verouiller_2_clicked()
{
     // A.write_to_arduino("0");
    ui->Hide_fournisseurs_2->setVisible(true);
    ui->Hide_fournisseurs_phrase_2->setVisible(true);
    ui->Hide_fournisseurs_username_2->setVisible(true);
    ui->Hide_fournisseurs_user_2->setVisible(true);
    ui->Hide_fournisseurs_mot_de_passe_2->setVisible(true);
    ui->Hide_fournisseurs_mdp_2->setVisible(true);
    ui->Hide_fournisseurs_se_connecter_2->setVisible(true);
     ui->Hide_fournisseurs_user_2->setText("");
     ui->Hide_fournisseurs_mdp_2->setText("");
}
void MainWindow::on_Hide_fournisseurs_verouiller_3_clicked()
{
     // A.write_to_arduino("0");
    ui->Hide_fournisseurs_3->setVisible(true);
    ui->Hide_fournisseurs_phrase_3->setVisible(true);
    ui->Hide_fournisseurs_username_3->setVisible(true);
    ui->Hide_fournisseurs_user_3->setVisible(true);
    ui->Hide_fournisseurs_mot_de_passe_3->setVisible(true);
    ui->Hide_fournisseurs_mdp_3->setVisible(true);
    ui->Hide_fournisseurs_se_connecter_3->setVisible(true);
     ui->Hide_fournisseurs_user_3->setText("");
     ui->Hide_fournisseurs_mdp_3->setText("");
}
void MainWindow::on_Hide_fournisseurs_verouiller_4_clicked()
{
     // A.write_to_arduino("0");
    ui->Hide_fournisseurs_4->setVisible(true);
    ui->Hide_fournisseurs_phrase_4->setVisible(true);
    ui->Hide_fournisseurs_username_4->setVisible(true);
    ui->Hide_fournisseurs_user_4->setVisible(true);
    ui->Hide_fournisseurs_mot_de_passe_4->setVisible(true);
    ui->Hide_fournisseurs_mdp_4->setVisible(true);
    ui->Hide_fournisseurs_se_connecter_4->setVisible(true);
     ui->Hide_fournisseurs_user_4->setText("");
     ui->Hide_fournisseurs_mdp_4->setText("");
}
void MainWindow::on_Hide_fournisseurs_verouiller_5_clicked()
{
     // A.write_to_arduino("0");
    ui->Hide_fournisseurs_5->setVisible(true);
    ui->Hide_fournisseurs_phrase_5->setVisible(true);
    ui->Hide_fournisseurs_username_5->setVisible(true);
    ui->Hide_fournisseurs_user_5->setVisible(true);
    ui->Hide_fournisseurs_mot_de_passe_5->setVisible(true);
    ui->Hide_fournisseurs_mdp_5->setVisible(true);
    ui->Hide_fournisseurs_se_connecter_5->setVisible(true);
     ui->Hide_fournisseurs_user_5->setText("");
     ui->Hide_fournisseurs_mdp_5->setText("");
}

void MainWindow::on_Hide_fournisseurs_verouiller_6_clicked()
{
     // A.write_to_arduino("0");
    ui->Hide_fournisseurs_6->setVisible(true);
    ui->Hide_fournisseurs_phrase_6->setVisible(true);
    ui->Hide_fournisseurs_username_6->setVisible(true);
    ui->Hide_fournisseurs_user_6->setVisible(true);
    ui->Hide_fournisseurs_mot_de_passe_6->setVisible(true);
    ui->Hide_fournisseurs_mdp_6->setVisible(true);
    ui->Hide_fournisseurs_se_connecter_6->setVisible(true);
     ui->Hide_fournisseurs_user_6->setText("");
     ui->Hide_fournisseurs_mdp_6->setText("");
}


void MainWindow::on_Hide_fournisseurs_se_connecter_2_clicked()
{

    QString username=ui->Hide_fournisseurs_user_2->text();
    QString password=ui->Hide_fournisseurs_mdp_2->text();
    QString table="ADMIN_COMMANDES";


if ((!ui->Hide_fournisseurs_user_2->text().isEmpty()) && (!ui->Hide_fournisseurs_mdp_2->text().isEmpty()))
{
QMessageBox msgBox;
//call checking from main.cpp

if (checkLogin(username, password,table) == 0)
{
qDebug() << "Success! Close dialog box";

QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
notifyIcon->show();
notifyIcon->setIcon(QIcon("C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/qt/Fournisseurs/charte_graphique/icon.gif"));

 notifyIcon->showMessage("Authentification éffectuée ","Gestion des Commandes ouverte",QSystemTrayIcon::Information,15000);

    ui->Hide_fournisseurs_phrase_2->setVisible(false);
    ui->Hide_fournisseurs_username_2->setVisible(false);
    ui->Hide_fournisseurs_user_2->setVisible(false);
    ui->Hide_fournisseurs_mot_de_passe_2->setVisible(false);
    ui->Hide_fournisseurs_mdp_2->setVisible(false);
    ui->Hide_fournisseurs_se_connecter_2->setVisible(false);
    ui->Hide_fournisseurs_2->setVisible(false);
}else
{


    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
   notifyIcon->setIcon(QIcon("C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/qt/Fournisseurs/charte_graphique/icon.gif"));

   notifyIcon->showMessage("Authentification non effectuée ","echec de connexion vérifiez vos paramètres",QSystemTrayIcon::Information,15000);


;
}
}
else
{
qDebug() << "Invalid credential provided!";

}
}

void MainWindow::on_Hide_fournisseurs_se_connecter_3_clicked()
{

    QString username=ui->Hide_fournisseurs_user_3->text();
    QString password=ui->Hide_fournisseurs_mdp_3->text();
    QString table="ADMIN_EMPLOYES";
if ((!ui->Hide_fournisseurs_user_3->text().isEmpty()) && (!ui->Hide_fournisseurs_mdp_3->text().isEmpty()))
{
QMessageBox msgBox;
//call checking from main.cpp

if (checkLogin(username, password,table) == 0)
{
qDebug() << "Success! Close dialog box";

QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
notifyIcon->show();
notifyIcon->setIcon(QIcon("C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/qt/Fournisseurs/charte_graphique/icon.gif"));

 notifyIcon->showMessage("Authentification éffectuée ","Gestion des Employes ouverte",QSystemTrayIcon::Information,15000);

    ui->Hide_fournisseurs_phrase_3->setVisible(false);
    ui->Hide_fournisseurs_username_3->setVisible(false);
    ui->Hide_fournisseurs_user_3->setVisible(false);
    ui->Hide_fournisseurs_mot_de_passe_3->setVisible(false);
    ui->Hide_fournisseurs_mdp_3->setVisible(false);
    ui->Hide_fournisseurs_se_connecter_3->setVisible(false);
    ui->Hide_fournisseurs_3->setVisible(false);
}else
{


    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
   notifyIcon->setIcon(QIcon("C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/qt/Fournisseurs/charte_graphique/icon.gif"));

   notifyIcon->showMessage("Authentification non effectuée ","echec de connexion vérifiez vos paramètres",QSystemTrayIcon::Information,15000);


;
}
}
else
{
qDebug() << "Invalid credential provided!";

}
}

 void MainWindow::on_Hide_fournisseurs_se_connecter_4_clicked()
{

    QString username=ui->Hide_fournisseurs_user_4->text();
    QString password=ui->Hide_fournisseurs_mdp_4->text();
    QString table="ADMIN_PRODUITS";
if ((!ui->Hide_fournisseurs_user_4->text().isEmpty()) && (!ui->Hide_fournisseurs_mdp_4->text().isEmpty()))
{
QMessageBox msgBox;
//call checking from main.cpp

if (checkLogin(username, password,table) == 0)
{
qDebug() << "Success! Close dialog box";

QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
notifyIcon->show();
notifyIcon->setIcon(QIcon("C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/qt/Fournisseurs/charte_graphique/icon.gif"));

 notifyIcon->showMessage("Authentification éffectuée ","Gestion des Produits ouverte",QSystemTrayIcon::Information,15000);

    ui->Hide_fournisseurs_phrase_4->setVisible(false);
    ui->Hide_fournisseurs_username_4->setVisible(false);
    ui->Hide_fournisseurs_user_4->setVisible(false);
    ui->Hide_fournisseurs_mot_de_passe_4->setVisible(false);
    ui->Hide_fournisseurs_mdp_4->setVisible(false);
    ui->Hide_fournisseurs_se_connecter_4->setVisible(false);
    ui->Hide_fournisseurs_4->setVisible(false);
}else
{


    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
   notifyIcon->setIcon(QIcon("C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/qt/Fournisseurs/charte_graphique/icon.gif"));

   notifyIcon->showMessage("Authentification non effectuée ","echec de connexion vérifiez vos paramètres",QSystemTrayIcon::Information,15000);


;
}
}
else
{
qDebug() << "Invalid credential provided!";

}
}

void MainWindow::on_Hide_fournisseurs_se_connecter_5_clicked()
{

    QString username=ui->Hide_fournisseurs_user_5->text();
    QString password=ui->Hide_fournisseurs_mdp_5->text();
    QString table="ADMIN_CLIENTS";
if ((!ui->Hide_fournisseurs_user_5->text().isEmpty()) && (!ui->Hide_fournisseurs_mdp_5->text().isEmpty()))
{
QMessageBox msgBox;
//call checking from main.cpp

if (checkLogin(username, password,table) == 0)
{
qDebug() << "Success! Close dialog box";

QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
notifyIcon->show();
notifyIcon->setIcon(QIcon("C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/qt/Fournisseurs/charte_graphique/icon.gif"));

 notifyIcon->showMessage("Authentification éffectuée ","Gestion des Clients ouverte",QSystemTrayIcon::Information,15000);

    ui->Hide_fournisseurs_phrase_5->setVisible(false);
    ui->Hide_fournisseurs_username_5->setVisible(false);
    ui->Hide_fournisseurs_user_5->setVisible(false);
    ui->Hide_fournisseurs_mot_de_passe_5->setVisible(false);
    ui->Hide_fournisseurs_mdp_5->setVisible(false);
    ui->Hide_fournisseurs_se_connecter_5->setVisible(false);
    ui->Hide_fournisseurs_5->setVisible(false);
}else
{


    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
   notifyIcon->setIcon(QIcon("C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/qt/Fournisseurs/charte_graphique/icon.gif"));

   notifyIcon->showMessage("Authentification non effectuée ","echec de connexion vérifiez vos paramètres",QSystemTrayIcon::Information,15000);


;
}
}
else
{
qDebug() << "Invalid credential provided!";

}
}

void MainWindow::on_Hide_fournisseurs_se_connecter_6_clicked()
{

    QString username=ui->Hide_fournisseurs_user_6->text();
    QString password=ui->Hide_fournisseurs_mdp_6->text();
    QString table="ADMIN_FINANCES";
if ((!ui->Hide_fournisseurs_user_6->text().isEmpty()) && (!ui->Hide_fournisseurs_mdp_6->text().isEmpty()))
{
QMessageBox msgBox;
//call checking from main.cpp

if (checkLogin(username, password,table) == 0)
{
qDebug() << "Success! Close dialog box";

QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
notifyIcon->show();
notifyIcon->setIcon(QIcon("C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/qt/Fournisseurs/charte_graphique/icon.gif"));

 notifyIcon->showMessage("Authentification éffectuée ","Gestion des Finances ouverte",QSystemTrayIcon::Information,15000);

    ui->Hide_fournisseurs_phrase_6->setVisible(false);
    ui->Hide_fournisseurs_username_6->setVisible(false);
    ui->Hide_fournisseurs_user_6->setVisible(false);
    ui->Hide_fournisseurs_mot_de_passe_6->setVisible(false);
    ui->Hide_fournisseurs_mdp_6->setVisible(false);
    ui->Hide_fournisseurs_se_connecter_6->setVisible(false);
    ui->Hide_fournisseurs_6->setVisible(false);
}else
{


    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
   notifyIcon->setIcon(QIcon("C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/qt/Fournisseurs/charte_graphique/icon.gif"));

   notifyIcon->showMessage("Authentification non effectuée ","echec de connexion vérifiez vos paramètres",QSystemTrayIcon::Information,15000);


;
}
}
else
{
qDebug() << "Invalid credential provided!";

}
}



int MainWindow::checkLogin(QString a, QString b, QString c)
{

QString aa = a;
QString bb = b;
QString var,var2;




QSqlQuery query;
query.prepare("SELECT login from "+c+" WHERE login = '"+aa+"' AND mdp =  '"+bb+"' ");
query.bindValue(":login", var);
if (query.exec() && query.next()) {
    var=query.value(0).toString();
}


query.prepare("SELECT mdp from "+c+" WHERE login = '"+aa+"' AND mdp =  '"+bb+"' ");
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

//Oussama gammoudi

void MainWindow::on_pushButton_AjouterEmploye_clicked()
{
    int cin= ui->lineEdit_CINE->text().toInt();
    QString nom= ui->lineEdit_NomE->text();
    QString prenom= ui->lineEdit_PrenomE->text();
    QString Email= ui->lineEdit_EmailE->text();
    QString poste= ui->lineEdit_PosteE->text();
    float salaire= ui->lineEdit_SalaireE->text().toFloat();


    Employe E(cin, nom, prenom, Email, poste, salaire);

    bool test= E.ajouter();
    if(test)
    {
        /*QMessageBox::information(nullptr, QObject::tr("Ajout Employé"),
                    QObject::tr("Employe Ajouté.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel)*/
        ui->tableEmployes->setModel(E.afficher());
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
            notifyIcon->show();
           notifyIcon->setIcon(QIcon("C:/Users/MSI GF63/Desktop/Projet_CPP_2A10"));

            notifyIcon->showMessage("GESTION DES  EMPLOYES ","Nouveau employé ajouté",QSystemTrayIcon::Information,15000);
    }

    else
        QMessageBox::critical(nullptr, QObject::tr("Ajout Employé"),
                    QObject::tr("Ajout echoué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }



void MainWindow::on_pushButton_SupprimerEmploye_clicked()
{
    Employe E1;
    E1.setCIN(ui->lineEdit_CinSuppression->text().toUInt());
    bool test= E1.supprimer(E1.getCIN());

    if(test)
    {
        /*QMessageBox::information(nullptr, QObject::tr("Suppression Employé"),
                    QObject::tr("Employe supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);*/
        ui->tableEmployes->setModel(E.afficher());
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
            notifyIcon->show();
           notifyIcon->setIcon(QIcon("C:/Users/MSI GF63/Desktop/Projet_CPP_2A10"));

            notifyIcon->showMessage("GESTION DES  EMPLOYES ","Employé supprimé",QSystemTrayIcon::Information,15000);
    }

    else
        QMessageBox::critical(nullptr, QObject::tr("Suppression Employé"),
                    QObject::tr("suppression echoué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_ModifierEmploye_clicked()
{
    int cin= ui->lineEdit_CinModification->text().toInt();
    QString nom= ui->lineEdit_NomE->text();
    QString prenom= ui->lineEdit_PrenomE->text();
    QString Email= ui->lineEdit_EmailE->text();
    QString poste= ui->lineEdit_PosteModification->text();
    float salaire= ui->lineEdit_SalaireModification->text().toFloat();
    Employe E(cin, nom, prenom, Email, poste, salaire);

    bool test= E.modifier(cin);
    if(test)
    {
        /*QMessageBox::information(nullptr, QObject::tr("Modification Employé"),
                    QObject::tr("Employe modifié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);*/
        ui->tableEmployes->setModel(E.afficher());
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
            notifyIcon->show();
           notifyIcon->setIcon(QIcon("C:/Users/MSI GF63/Desktop/Projet_CPP_2A10"));

            notifyIcon->showMessage("GESTION DES  EMPLOYES ","Employé modifié",QSystemTrayIcon::Information,15000);
    }

    else
        QMessageBox::critical(nullptr, QObject::tr("Modification Employé"),
                    QObject::tr("Modification echoué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}


void MainWindow::on_pushButton_Excel_clicked()
{
         Employe E;
               QSqlQueryModel * model=new QSqlQueryModel();
               model=E.Find_Employe();
               QString textData= " CIN                  NOM                 PRENOM            EMAIL         POSTE           SALAIRE\n ";
               int rows=model->rowCount();
               int columns=model->columnCount();
               for (int i = 0; i < rows; i++)
               {
                   for (int j = 0; j < columns; j++)
                   {
                       textData += model->data(model->index(i,j)).toString();
                       textData +=" ; ";
                   }
                   textData += "\n";
               }
               QString fileName = QFileDialog::getSaveFileName(this, "Export Excel", QString(), "*.csv");
               if (!fileName.isEmpty())
                   if (QFileInfo(fileName).suffix().isEmpty())
                       fileName.append(".csv");
               QFile csvfile(fileName);
               if(csvfile.open(QIODevice::WriteOnly|QIODevice::Truncate))
               {
                   QTextStream out(&csvfile);
                   out<<textData;
               }
               csvfile.close();

}


void MainWindow::on_lineEdit_Recherche_textChanged(const QString &arg1)
{
                Employe E;
                ui->tableEmployes->setModel(E.recherche_employe(ui->lineEdit_Recherche->text()));
}


void MainWindow::on_tri_clicked()
{
    ui->tableEmployes->setModel(E.tri());
}

void MainWindow::on_tri2_clicked()
{
    ui->tableEmployes->setModel(E.tri2());
}
//Mailing

void MainWindow::on_send_mail_clicked()
{
    Smtp* smtp = new Smtp("aura.forgetPass@gmail.com","Service100a","smtp.gmail.com",465);
       connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

       smtp->sendMail("aura.forgetPass@gmail.com",ui->rcpt->text(),ui->subject->text(),ui->msg->toPlainText());

}

//Cryptage ***************************************************************************************************

void MainWindow::on_pushButton_encrypt_clicked()
{
    QString plainText = ui->plainTextEdit_plain->toPlainText();
    QString encryptedText = "to be implemented";

    if(ui->comboBox->currentIndex() == 0)
    {
        int key = ui->lineEdit_CC_key->text().toInt();
        encryptedText = ewCaesarCipher(plainText, key);
    }
    else if(ui->comboBox->currentIndex() == 1)
    {
        QString secret = ui->lineEdit_PF_Secret->text();
        encryptedText = ewPlayfair(plainText, secret);
    }
    else if(ui->comboBox->currentIndex() == 2)
    {
        QString key = ui->lineEdit_DES_key->text();
        encryptedText = ewDES(plainText, key.toStdString());
    }
    else if(ui->comboBox->currentIndex() == 3)
    {
        double p = ui->RSA_lineEdit_p->text().toDouble();
        double q = ui->RSA_lineEdit_q->text().toDouble();
        double dbl = ewRSA(plainText.toDouble(), p, q);

        std::ostringstream strs;
        strs << dbl;
        encryptedText = QString::fromStdString(strs.str());

        std::pair<double, double> pair = RSAKeys(p, q);
        std::ostringstream strPrK;
        strPrK << pair.first;
        ui->RSA_lineEdit_prkey->setText(QString::fromStdString(strPrK.str()));
        std::ostringstream strPuK;
        strPuK << pair.second;
        ui->RSA_lineEdit_pukey->setText(QString::fromStdString(strPuK.str()));
    }
    else if(ui->comboBox->currentIndex() == 4)
    {
        QString key = ui->lineEdit_rc4_key->text();
        encryptedText = ewRC4(plainText, key);
    }
    else if(ui->comboBox->currentIndex() == 5)
    {
        QString key = ui->lineEdit_DES_key->text();
        encryptedText = ewIDES(plainText, key.toStdString());
    }
    ui->plainTextEdit_encrypted->document()->setPlainText(encryptedText);
}

void MainWindow::on_pushButton_decrypt_clicked()
{
    QString encryptedText = ui->plainTextEdit_encrypted->toPlainText();
    QString plainText = "to be implemented";

    if(ui->comboBox->currentIndex() == 0)
    {
        int key = ui->lineEdit_CC_key->text().toInt();
        plainText = dwCaesarCipher(encryptedText, key);
    }
    else if(ui->comboBox->currentIndex() == 1)
    {
        QString secret = ui->lineEdit_PF_Secret->text();
        plainText = dwPlayfair(encryptedText, secret);
    }
    else if(ui->comboBox->currentIndex() == 2)
    {
        QString key = ui->lineEdit_DES_key->text();
        plainText = dwDES(encryptedText, key.toStdString());
    }
    else if(ui->comboBox->currentIndex() == 3)
    {
        double p = ui->RSA_lineEdit_p->text().toDouble();
        double q = ui->RSA_lineEdit_q->text().toDouble();

        std::ostringstream pstr;
        pstr << dwRSA(encryptedText.toDouble(), p, q);
        plainText = QString::fromStdString(pstr.str());
    }
    else if(ui->comboBox->currentIndex() == 4)
    {
        QString key = ui->lineEdit_rc4_key->text();
        plainText = dwRC4(encryptedText, key);
    }
    else if(ui->comboBox->currentIndex() == 5)
    {
        QString key = ui->lineEdit_DES_key->text();
        plainText = dwIDES(encryptedText, key.toStdString());
    }
    ui->plainTextEdit_plain->document()->setPlainText(plainText);
}

void MainWindow::on_actionReset_Fields_triggered()
{
    ui->plainTextEdit_plain->clear();
    ui->plainTextEdit_encrypted->clear();
    ui->lineEdit_CC_key->clear();
}

void MainWindow::on_actionClear_Plain_Text_triggered()
{
    ui->plainTextEdit_plain->clear();
}

void MainWindow::on_actionClear_Encrypted_Text_triggered()
{
    ui->plainTextEdit_encrypted->clear();
}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1 == "Caesar Cipher")
    {
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if(arg1 == "Playfair")
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if(arg1 == "DES")
    {
        ui->stackedWidget->setCurrentIndex(2);
    }
    else if(arg1 == "RSA")
    {
        ui->stackedWidget->setCurrentIndex(3);
    }
    else if(arg1 == "RC4")
    {
        ui->stackedWidget->setCurrentIndex(4);
    }
    else if(arg1 == "DES with Text")
    {
        ui->stackedWidget->setCurrentIndex(2);
    }
}





// Caesar Cipher Methods

QString MainWindow::ewCaesarCipher(QString plainText, int key)
{
    std::string result = "";
    std::string plainStdText = plainText.toStdString();

    for (int i=0;i<plainText.length();i++)
    {
        if(plainStdText[i] == ' ')
        {
            result += ' ';
        }
        else if(std::isalpha(plainStdText[i]))
        {
            if (std::isupper(plainStdText[i]))
                result += char(int(plainStdText[i]+key-65)%26 +65);
            else
                result += char(int(plainStdText[i]+key-97)%26 +97);
        }
    }

    return QString::fromStdString(result);
}

QString MainWindow::dwCaesarCipher(QString encryptedText, int key)
{
    return ewCaesarCipher(encryptedText, 26-key);
}





// playfair Methods

QString MainWindow::ewPlayfair(QString plainText, QString secret)
{
    std::string plainStdText = plainText.toStdString();
    std::string secretStdText = secret.toStdString();

    normalizePFSecret(secretStdText);
    populatePFMatrix(secretStdText);
    normalizePFString(plainStdText);

    std::string encryptedText = encryptPFString(plainStdText);

    return QString::fromStdString(encryptedText);
}

QString MainWindow::dwPlayfair(QString encryptedText, QString secret)
{
    std::string encryptedStdText = encryptedText.toStdString();
    std::string secretStdText = secret.toStdString();

    normalizePFSecret(secretStdText);
    populatePFMatrix(secretStdText);

    std::string plainText = decryptPFString(encryptedStdText);

    return QString::fromStdString(plainText);
}

bool MainWindow::inSameRow(Position p1, Position p2)
{
    if(p1.x == p2.x)
        return true;
    return false;
}

bool MainWindow::inSameColumn(Position p1, Position p2)
{
    if(p1.y == p2.y)
        return true;
    return false;
}

void MainWindow::normalizePFString(std::string &str)
{
    std::string pure_str= "";
    // remove any non-alphabetical characters
    // convert string to lower case
    for(int i=0;i<str.size();++i)
    {
        if(isalpha(str[i]))
        {
            if(std::isupper(str[i]))
                str[i] = std::tolower(str[i]);
            pure_str += str[i];
        }
    }

    // separate duplicate characters
    for(int i=0 ; i<pure_str.size()-1 ; i+=2)
    {
        if(pure_str[i] == pure_str[i+1])
            pure_str.insert(pure_str.begin()+i+1, 'x');
    }

    // make string even
    if(pure_str.size()%2 !=0)
        pure_str += 'x';

    str = pure_str;
}

std::string MainWindow::encryptPFString(std::string plainStdText)
{
    std::string result = "";

    for(int i=0;i<plainStdText.size(); i+=2)
    {
        Position p1 = findPositionByChar(plainStdText[i]);
        Position p2 = findPositionByChar(plainStdText[i+1]);

        if(inSameRow(p1, p2))
        {
            if(p1.y == 4)
                p1.y = 0;
            else
                p1.y +=1;

            if(p2.y == 4)
                p2.y = 0;
            else
                p2.y +=1;

            result += findCharByPosition(p1);
            result += findCharByPosition(p2);
        }
        else if(inSameColumn(p1, p2))
        {
            if(p1.x == 4)
                p1.x = 0;
            else
                p1.x +=1;

            if(p2.x == 4)
                p2.x = 0;
            else
                p2.x +=1;

            result += findCharByPosition(p1);
            result += findCharByPosition(p2);
        }
        else
        {
            Position t1, t2;

            t1.x = p1.x;
            t1.y = p2.y;

            t2.x = p2.x;
            t2.y = p1.y;

            result += findCharByPosition(t1);
            result += findCharByPosition(t2);
        }
    }

    return result;
}

std::string MainWindow::decryptPFString(std::string encryptedStdText)
{
    std::string result = "";

    for(int i=0;i<encryptedStdText.size(); i+=2)
    {
        Position p1 = findPositionByChar(encryptedStdText[i]);
        Position p2 = findPositionByChar(encryptedStdText[i+1]);

        if(inSameRow(p1, p2))
        {
            if(p1.y == 0)
                p1.y = 4;
            else
                p1.y -=1;

            if(p2.y == 0)
                p2.y = 4;
            else
                p2.y -=1;

            result += findCharByPosition(p1);
            result += findCharByPosition(p2);
        }
        else if(inSameColumn(p1, p2))
        {
            if(p1.x == 0)
                p1.x = 4;
            else
                p1.x -=1;

            if(p2.x == 0)
                p2.x = 4;
            else
                p2.x -=1;

            result += findCharByPosition(p1);
            result += findCharByPosition(p2);
        }
        else
        {
            Position t1, t2;

            t1.x = p1.x;
            t1.y = p2.y;

            t2.x = p2.x;
            t2.y = p1.y;

            result += findCharByPosition(t1);
            result += findCharByPosition(t2);
        }
    }

    return result;
}

void MainWindow::normalizePFSecret(std::string &secret)
{
    std::string result = "";
    secret += "abcdefghiklmnopqrstuvwxyz";
    for(int i=0;i<secret.size();++i)
    {
        if(result.find(secret[i]) == std::string::npos)
            result += secret[i];
    }
    secret = result;
}

void MainWindow::populatePFMatrix(std::string secret)
{
    for(int i=0; i<5; ++i)
    {
        for(int j=0; j<5 ; ++j)
        {
            pfMatrix[i][j] = secret[j+5*i];
        }
    }
}

Position MainWindow::findPositionByChar(char ch)
{
    Position p;

    for(int i=0; i<5; ++i)
    {
        for(int j=0; j<5; ++j)
        {
            if(pfMatrix[i][j] == ch)
            {
                p.x = i;
                p.y = j;
            }
        }
    }

    return p;
}

char MainWindow::findCharByPosition(Position p)
{
    return pfMatrix[p.x][p.y];
}





// data 0000000100100011010001010110011110001001101010111100110111101111
// key  0001001100110100010101110111100110011011101111001101111111110001

// DES Methods

QString MainWindow::ewDES(QString plainText, std::string key)
{
    std::vector< std::string > keys = keyPreparation(key);

    QString encryptedText = DESEncryption(plainText.toStdString(), keys);

    return encryptedText;
}

QString MainWindow::dwDES(QString encryptedText, std::string key)
{
    std::vector< std::string > keys = keyPreparation(key);

    std::reverse(keys.begin(), keys.end());

    QString plainText = DESEncryption(encryptedText.toStdString(), keys);

    return plainText;
}

std::vector< std::string > MainWindow::keyPreparation(std::string key)
{
    // 0001001100110100010101110111100110011011101111001101111111110001

    std::string permutedKey = "";
    int PC1_permutations[56] = {
        57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4
    };

    for(int i=0;i<56; ++i)
    {
        permutedKey += key[PC1_permutations[i]-1];
    }

//    std::cout << key << std::endl;
//    std::cout << permutedKey << std::endl;
//    std::cout << permutedKey.length() << std::endl;


    int shifts[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

    std::vector< std::pair<std::string, std::string> > keys;

    std::string C0 = permutedKey.substr(0,28);
    std::string D0 = permutedKey.substr(28,56);

//    std::cout << "C0 : " << C0 << std::endl;
//    std::cout << "D0 : " << D0 << std::endl;

    keys.push_back(std::make_pair(C0, D0));

    for(int i=1 ; i<17 ; ++i)
    {
        std::string C = keys[i-1].first;
        std::string D = keys[i-1].second;

        C = C.substr(shifts[i-1], C.length()) + C.substr(0, shifts[i-1]);
        D = D.substr(shifts[i-1], D.length()) + D.substr(0, shifts[i-1]);

        keys.push_back(std::make_pair(C, D));

//        std::cout << "C" << i << " : " << C << std::endl;
//        std::cout << "D" << i << " : " << D << std::endl;
    }


    int PC2_permutations[48] = {
        14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
    };

    std::vector<std::string> finalKeys;

    for(int i=0;i<16;++i)
    {
        std::string k = keys[i+1].first + keys[i+1].second;
        std::string fk = "";

        for(int j=0;j<48;++j)
        {
            fk += k[PC2_permutations[j]-1];
        }
        finalKeys.push_back(fk);
//        std::cout << fk << std::endl;
    }

    std::cout << std::endl << ">[BEGIN] Keys generated Successfully" << std::endl << std:: endl;

    for(int i=0; i<finalKeys.size(); ++i)
    {
        std::cout << "Key " << i+1 << ": " << finalKeys[i] << std::endl;
    }

    std::cout << std::endl << ">[END] Keys generated Successfully" << std::endl << std:: endl;


    return finalKeys;
}

QString MainWindow::DESEncryption(std::string dataBlock, std::vector< std::string > keys)
{
    // 0000000100100011010001010110011110001001101010111100110111101111

    std::string permutedBlock = "";

    int initPermutation[64] = {
        58,    50,   42,    34,    26,   18,    10,    2,
        60,    52,   44,    36,    28,   20,    12,    4,
        62,    54,   46,    38,    30,   22,    14,    6,
        64,    56,   48,    40,    32,   24,    16,    8,
        57,    49,   41,    33,    25,   17,     9,    1,
        59,    51,   43,    35,    27,   19,    11,    3,
        61,    53,   45,    37,    29,   21,    13,    5,
        63,    55,   47,    39,    31,   23,    15,    7
    };

    for(int i=0 ; i<64 ; ++i)
    {
        permutedBlock += dataBlock[initPermutation[i]-1];
    }

    std::string L0 = permutedBlock.substr(0, 32);
    std::string R0 = permutedBlock.substr(32, 64);


    std::cout << "L0 : " << L0 << std::endl;
    std::cout << "R0 : " << R0 << std::endl;

    std::vector< std::pair<std::string, std::string> > data;
    data.push_back(std::make_pair(L0, R0));

    for(int i=1;i<17;++i)
    {
        std::string L = data[i-1].second;

        std::string R = apply_xor(
            data[i-1].first,
            apply_func_F(apply_func_E(data[i-1].second), keys[i-1])
        );

        data.push_back(std::make_pair(L, R));

        std::cout << "L" << i << " : " << L << std::endl;
        std::cout << "R" << i << " : " << R << std::endl;
    }

    std::string encryptedDataReversedKey = "";
    encryptedDataReversedKey += data[data.size()-1].second;
    encryptedDataReversedKey += data[data.size()-1].first;

    std::string finalPermutedBlock = "";

    int finalPermutation[64] = {
        40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41,  9, 49, 17, 57, 25
    };

    for(int i=0 ; i<64 ; ++i)
    {
        finalPermutedBlock += encryptedDataReversedKey[finalPermutation[i]-1];
    }

    return QString(finalPermutedBlock.c_str());
}

std::string MainWindow::apply_xor(std::string str1, std::string str2)
{
    if(str1.length() != str2.length())
        std::cout << "Error in XORed Strings, Length Not Equal" << std::endl;

    std::string result = "";
    for(int i=0;i<str1.length();++i)
    {
        if(str1[i] == str2[i])
            result += '0';
        else
            result += '1';
    }

    return result;
}

std::string MainWindow::apply_func_F(std::string str1, std::string str2)
{
    // result is 48 bit
    std::string result = apply_xor(str1, str2);

    int sboxes[8][4][16] =
    {
        {
            { 14,  4,  13,  1,   2, 15,  11,  8,   3, 10,   6, 12,   5,  9,   0,  7 },
            {  0, 15,   7,  4,  14,  2,  13,  1,  10,  6,  12, 11,   9,  5,   3,  8 },
            {  4,  1,  14,  8,  13,  6,   2, 11,  15, 12,   9,  7,   3, 10,   5,  0 },
            { 15, 12,   8,  2,   4,  9,   1,  7,   5, 11,   3, 14,  10,  0,   6, 13 }
        },
        {
            { 15,  1,   8, 14,   6, 11,   3,  4,   9,  7,   2, 13,  12,  0,   5, 10 },
            {  3, 13,   4,  7,  15,  2,   8, 14,  12,  0,   1, 10,   6,  9,  11,  5 },
            {  0, 14,   7, 11,  10,  4,  13,  1,   5,  8,  12,  6,   9,  3,   2, 15 },
            { 13,  8,  10,  1,   3, 15,   4,  2,  11,  6,   7, 12,   0,  5,  14,  9 }
        },
        {
            { 10,  0,   9, 14,   6,  3,  15,  5,   1, 13,  12,  7,  11,  4,   2,  8 },
            { 13,  7,   0,  9,   3,  4,   6, 10,   2,  8,   5, 14,  12, 11,  15,  1 },
            { 13,  6,   4,  9,   8, 15,   3,  0,  11,  1,   2, 12,   5, 10,  14,  7 },
            {  1, 10,  13,  0,   6,  9,   8,  7,   4, 15,  14,  3,  11,  5,   2, 12 }
        },
        {
            {  7, 13,  14,  3,   0,  6,   9, 10,   1,  2,   8,  5,  11, 12,   4, 15 },
            { 13,  8,  11,  5,   6, 15,   0,  3,   4,  7,   2, 12,   1, 10,  14,  9 },
            { 10,  6,   9,  0,  12, 11,   7, 13,  15,  1,   3, 14,   5,  2,   8,  4 },
            {  3, 15,   0,  6,  10,  1,  13,  8,   9,  4,   5, 11,  12,  7,   2, 14 }
        },
        {
            {  2, 12,   4,  1,   7, 10,  11,  6,   8,  5,   3, 15,  13,  0,  14,  9 },
            { 14, 11,   2, 12,   4,  7,  13,  1,   5,  0,  15, 10,   3,  9,   8,  6 },
            {  4,  2,   1, 11,  10, 13,   7,  8,  15,  9,  12,  5,   6,  3,   0, 14 },
            { 11,  8,  12,  7,   1, 14,   2, 13,   6, 15,   0,  9,  10,  4,   5,  3 }
        },
        {
            { 12,  1,  10, 15,   9,  2,   6,  8,   0, 13,   3,  4,  14,  7,   5, 11 },
            { 10, 15,   4,  2,   7, 12,   9,  5,   6,  1,  13, 14,   0, 11,   3,  8 },
            {  9, 14,  15,  5,   2,  8,  12,  3,   7,  0,   4, 10,   1, 13,  11,  6 },
            {  4,  3,   2, 12,   9,  5,  15, 10,  11, 14,   1,  7,   6,  0,   8, 13 }
        },
        {
            {  4, 11,   2, 14,  15,  0,   8, 13,   3, 12,   9,  7,   5, 10,   6,  1 },
            { 13,  0,  11,  7,   4,  9,   1, 10,  14,  3,   5, 12,   2, 15,   8,  6 },
            {  1,  4,  11, 13,  12,  3,   7, 14,  10, 15,   6,  8,   0,  5,   9,  2 },
            {  6, 11,  13,  8,   1,  4,  10,  7,   9,  5,   0, 15,  14,  2,   3, 12 }
        },
        {
            { 13,  2,   8,  4,   6, 15,  11,  1,  10,  9,   3, 14,   5,  0,  12,  7 },
            {  1, 15,  13,  8,  10,  3,   7,  4,  12,  5,   6, 11,   0, 14,   9,  2 },
            {  7, 11,   4,  1,   9, 12,  14,  2,   0,  6,  10, 13,  15,  3,   5,  8 },
            {  2,  1,  14,  7,   4, 10,   8, 13,  15, 12,   9,  0,   3,  5,   6, 11 }
        }
    };

    std::string output = "";
    std::string outerBits = "";
    std::string innerBits = "";

    for(int i=0, s=0 ; i<48 ; i+=6, s++)
    {
        outerBits += result[i];
        outerBits += result[i+5];

        innerBits += result[i+1];
        innerBits += result[i+2];
        innerBits += result[i+3];
        innerBits += result[i+4];

        int row = std::stoi(outerBits, nullptr, 2);
        int column = std::stoi(innerBits, nullptr, 2);

        int valInSBox = sboxes[s][row][column];

        output += std::bitset<4>(valInSBox).to_string();

        outerBits = "";
        innerBits = "";
    }

    std::string permutedOutput = "";

    int permutations[32] = {
        16,  7, 20, 21,
        29, 12, 28, 17,
         1, 15, 23, 26,
         5, 18, 31, 10,
         2,  8, 24, 14,
        32, 27,  3,  9,
        19, 13, 30,  6,
        22, 11,  4, 25
    };

    for(int i=0; i<32; ++i)
    {
        permutedOutput += output[permutations[i]-1];
    }

    return permutedOutput;
}

std::string MainWindow::apply_func_E(std::string str)
{
    std::string result = "";

    int ePermutations[48] = {
         32,     1,    2,     3,     4,    5,
          4,     5,    6,     7,     8,    9,
          8,     9,   10,    11,    12,   13,
         12,    13,   14,    15,    16,   17,
         16,    17,   18,    19,    20,   21,
         20,    21,   22,    23,    24,   25,
         24,    25,   26,    27,    28,   29,
         28,    29,   30,    31,    32,    1
    };

    for(int i=0;i<48;++i)
    {
        result += str[ePermutations[i]-1];
    }

    return result;
}


// improved DES with text Methods
QString MainWindow::ewIDES(QString plainText, std::string key)
{
    std::vector< std::string > keys = keyPreparation(key);
    std::vector< std::string > blocks = textToBinaryAscii(plainText.toStdString());

    QString encryptedText;

    for(int i=0; i<blocks.size(); ++i)
        encryptedText += DESEncryption(blocks[i], keys);

//    encryptedText = QString::fromStdString(binaryAsciiToText(encryptedText.toStdString()));

    return encryptedText;
}

QString MainWindow::dwIDES(QString encryptedText, std::string key)
{
    std::vector< std::string > keys = keyPreparation(key);
    std::reverse(keys.begin(), keys.end());

    std::string stdPlainText = encryptedText.toStdString();
    std::string allPlainText = "";

    for(int i=0; i<encryptedText.size()/64; ++i)
    {
        allPlainText += DESEncryption(stdPlainText.substr(i*64, 64), keys).toStdString();
    }

    return QString::fromStdString(binaryAsciiToText(allPlainText));
}

std::vector< std::string > MainWindow::textToBinaryAscii(std::string str)
{
    std::vector< std::string > blocksOfData;

    for(int i=0; i<str.size()/8; ++i)
    {
        std::string blockStr = str.substr(i*8, 8);
        std::string block = "";

        for(int i=0; i<8; ++i)
            block += charToBinaryAscii(blockStr[i]);

        blocksOfData.push_back(block);
    }

    if(str.size()%8 != 0)
    {
        int start = ((int)str.size()/8)*8;
        int length = (int)str.size()- start;

        std::string blockStr = str.substr(start, length);
        for(int i=0; i<(8-length); ++i)
            blockStr += " ";

        std::string block = "";
        for(int i=0; i<8; ++i)
            block += charToBinaryAscii(blockStr[i]);
        blocksOfData.push_back(block);
    }

    return blocksOfData;
}

std::string MainWindow::binaryAsciiToText(std::string str)
{
    std::string blocksOfData = "";

    for(int i=0; i<str.size()/64; ++i)
    {
        std::string blockStr = str.substr(i*64, 64);
        std::string block = "";

        for(int i=0; i<8; ++i)
        {
           std::string ascii = blockStr.substr(i*8, 8);
           block += binaryAsciiToChar(ascii);
        }
        blocksOfData += block;
    }

    return blocksOfData;
}

std::string MainWindow::charToBinaryAscii(char ch)
{
    return std::bitset<8>(int(ch)).to_string();
}

char MainWindow::binaryAsciiToChar(std::string binaryAscii)
{
    return char(std::bitset<8>(binaryAscii).to_ulong());
}





// RSA Methods

double MainWindow::ewRSA(double msg, double p, double q)
{
    // generate public as first, private as second key
    std::pair<double,double> keys = RSAKeys(p, q);

    double n = p*q;
    double e = keys.first;

    return RSAEncryption(msg, n, e);
}

double MainWindow::dwRSA(double msg, double p, double q)
{
    // generate public as first, private as second key
    std::pair<double,double> keys = RSAKeys(p, q);

    int n = p*q;
    int d = keys.second;

    return RSADecryption(msg, n, d);
}

double MainWindow::RSAEncryption(double msg, double n, double e)
{
    // Encryption c = (msg ^ e) % n
    double c = pow(msg, e);
    c = fmod(c, n);
    return c;
}

double MainWindow::RSADecryption(double msg, double n, double d)
{
    // Decryption m = (c ^ d) % n
    double m = pow(msg, d);
    m = fmod(m, n);
    return m;
}

std::pair<double, double> MainWindow::RSAKeys(double p, double q)
{
    // Finding public key; e stands for encrypt.
    double e = 2;
    double phi = (p-1)*(q-1);
    while (e < phi)
    {
        // e must be co-prime to phi and
        // smaller than phi.
        if (gcd(e, phi)==1)
            break;
        else
            e++;
    }

    // Private key (d stands for decrypt)
    // choosing d such that it satisfies
    // d*e = 1 + k * totient

    int d = e;
    while((int)(d*e)%((int)phi) != 1)
    {
        d++;
    }

    return std::make_pair(e, d);
}

int MainWindow::gcd(int a, int h)
{
    int temp;
    while (1)
    {
        temp = a%h;
        if (temp == 0)
          return h;
        a = h;
        h = temp;
    }
}





// RC4 Methods

QString MainWindow::ewRC4(QString msg, QString key)
{
    std::vector<int> k;

    // initialize key
    std::string stdCppKey = key.toStdString();
    for(int i=0; i<stdCppKey.length(); ++i)
        k.push_back(int(stdCppKey[i] - '0'));

    std::vector<int> s(256);
    std::vector<int> t(256);

    // initialize vector S to [0:255]
    for(int i=0; i<256; ++i)
        s[i] = i;

    // initialize vector T from key K
    for(int i=0; i<256; ++i)
        t[i] = k[i%k.size()];

    // initial Permutation Of S
    int j = 0;
    for(int i=0; i<256; ++i)
    {
        j = (j + s[i] + t[i])%256;
        std::swap(s[i], s[j]);
    }

    // prepare msg
    std::vector< std::bitset<8> > msg_bytes = bytesOfMessage(msg.toStdString());


    // generate a key for each byte of input
    // e.g input: 5 bytes, generates output: 5 bytes
    std::vector< std::bitset<8> > keys = keysGenerator((int)msg_bytes.size(), s);

    return RC4Encryption(msg_bytes, keys);

}

QString MainWindow::dwRC4(QString msg, QString key)
{
    return ewRC4(msg, key);
}

QString MainWindow::RC4Encryption(std::vector< std::bitset<8> > msg_bytes, std::vector< std::bitset<8> > keys)
{
    std::string result = "";
    for (int i = 0; i < msg_bytes.size(); ++i)
    {
        std::bitset<8> temp = std::bitset<8>(msg_bytes[i] ^ keys[i]);
        result += temp.to_string();
    }

    // Debugging output
    std::cout << "> Debugging Statements" << std::endl;

    std::cout << "I/P: " ;
    for(int t=0; t<msg_bytes.size(); ++t)
        std::cout << msg_bytes[t];
    std::cout << std::endl;

    std::cout << "Key: ";
    for(int t=0; t<keys.size(); ++t)
        std::cout << keys[t].to_string();
    std::cout << std::endl;
    std::cout << "O/P: " << result << std::endl;

    return QString::fromStdString(result);
}

std::vector< std::bitset<8> > MainWindow::keysGenerator(int msg_length, std::vector<int> s)
{
    std::vector< std::bitset<8> > keys(msg_length);

    int i=0, j=0, k=0;
    for (int lc = 0; lc < msg_length; ++lc)
    {
        i = (i+1)%256;
        j = (j+s[i])%256;
        std::swap(s[i], s[j]);
        k = s[(s[i]+s[j])%256];
        keys[lc] = std::bitset<8>(k);
    }

    return keys;
}

std::vector< std::bitset<8> > MainWindow::bytesOfMessage(std::string msg)
{
    std::vector< std::bitset<8> > msg_bytes;

    for(int i=0; i<(msg.length()/8); ++i)
    {
        std::string msg_byte = "";
        for(int j=0; j<8; ++j)
        {
            int idx = j + i*8;
            msg_byte += msg[idx];
        }
        msg_bytes.push_back(std::bitset<8>(msg_byte));
    }

    return msg_bytes;
}

//brahim abdelbeki

void MainWindow::on_pb_ajouter_BRAHIM_clicked()
{
    int ID_Facture=ui->le_id_BRAHIM->text().toInt();
    QDate Date_Facture=ui->le_df_BRAHIM->date();
    QString Reference=ui->le_rf_BRAHIM->text();
    float Prix=ui->le_cf_BRAHIM->text().toFloat();
    float Statistique=ui->le_sf_BRAHIM->text().toFloat();
    float Budget=ui->le_sb_BRAHIM->text().toFloat();
    Finance F(ID_Facture,Date_Facture,Reference,Prix,Statistique,Budget);
    F.ajouter_BRAHIM();
    bool test=F.ajouter_BRAHIM();
    if (test)
          {
                     ui->tab_f_BRAHIM->setModel(F.afficher_BRAHIM());
                     ui->tab_f_2_BRAHIM->setModel(F.afficher_BRAHIM());
                     ui->tab_fH_BRAHIM->setModel(F.historique_BRAHIM());


              QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
              notifyIcon->show();


              notifyIcon->showMessage("Gestion Des Factures ","Facture Ajouté",QSystemTrayIcon::Information,15000);
    }
          else{

        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
        notifyIcon->show();


        notifyIcon->showMessage("Gestion Des Factures ","Facture non Ajouté",QSystemTrayIcon::Information,15000);}
}

void MainWindow::on_pb_supprimer_BRAHIM_clicked()
{
    Finance f;
    f.setID_Facture_BRAHIM(ui->le_idfsupp_BRAHIM->text().toInt());
    f.supprimer_BRAHIM(f.getID_Facture_BRAHIM());
    ui->tab_f_BRAHIM->setModel(Fi.afficher_BRAHIM());
    ui->tab_f_2_BRAHIM->setModel(Fi.afficher_BRAHIM());

}

void MainWindow::on_Modifier_BRAHIM_clicked()
{
       Finance f;
       bool test=f.modifier_BRAHIM(ui->m_ID_Facture_BRAHIM->text().toInt(),ui->m_Date_Facture_BRAHIM->date(),ui->m_Reference_BRAHIM->text(),ui->m_Prix_BRAHIM->text().toFloat(),ui->m_Statistique_BRAHIM->text().toFloat());

    ui->tab_f_BRAHIM->setModel(f.afficher_BRAHIM());

     ui->tab_f_2_BRAHIM->setModel(f.afficher_BRAHIM());
     if (test)
           {
                   ui->tab_f_BRAHIM->setModel(Fi.afficher_BRAHIM()); //refresh
                   ui->tab_f_2_BRAHIM->setModel(Fi.afficher_BRAHIM());


               QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
               notifyIcon->show();


               notifyIcon->showMessage("Gestion Des Factures ","Facture Modifié",QSystemTrayIcon::Information,15000);
     }
           else{
         QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
         notifyIcon->show();


         notifyIcon->showMessage("Gestion Des Factures ","Facture non Modifié",QSystemTrayIcon::Information,15000);}


     ui->tab_f_BRAHIM->setModel(Fi.afficher_BRAHIM());
     ui->tab_f_2_BRAHIM->setModel(Fi.afficher_BRAHIM());

}

void MainWindow::on_Recherche_BRAHIM_textChanged()
{
    Finance f;

        if(ui->Recherche_BRAHIM->text() == "")
            {
                ui->tab_f_BRAHIM->setModel(f.afficher_BRAHIM());
            }
        else if(ui->ComboPapa_BRAHIM->currentText()=="Par Defaut")
        {
             ui->tab_f_BRAHIM->setModel(f.rechercher1_BRAHIM(ui->Recherche_BRAHIM->text()));
        }
        else if(ui->ComboPapa_BRAHIM->currentText()=="Date_Facture")
        {
            ui->tab_f_BRAHIM->setModel(f.rechercher_par_date_BRAHIM(ui->Recherche_BRAHIM->text()));
        }
        else if(ui->ComboPapa_BRAHIM->currentText()!="Par Defaut")
            {
                 ui->tab_f_BRAHIM->setModel(f.rechercher_BRAHIM(ui->ComboPapa_BRAHIM->currentText(),ui->Recherche_BRAHIM->text()));
            }

}

void MainWindow::on_pushButton_BRAHIM_clicked()
{
    Finance f;
    float Budget=ui->CapAd_BRAHIM->text().toFloat();
    f.modifierBudget_BRAHIM(Budget);
}

void MainWindow::on_pdf_but_BRAHIM_clicked()
{
            Finance f;
            f.pdf_BRAHIM();
            QString link="C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/qt/Fournisseurs/integration/test/facture.pdf";
            QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_Trier_F_BRAHIM_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();



       model->setQuery("select * from FINANCES order by "+ui->ComboTri_BRAHIM->currentText()+" ");

       model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("Reference"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prix"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("Statistique"));

               ui->tab_f_BRAHIM->setModel(model);
                ui->tab_f_BRAHIM->show();

}

void MainWindow::on_m_ID_Facture_BRAHIM_textChanged()
{
    QSqlQuery query;
    query.prepare("SELECT  date FROM FINANCES WHERE ID_FACTURE= "+ui->m_ID_Facture_BRAHIM->text()+"");
    query.bindValue(":date", ui->m_Date_Facture_BRAHIM->text());
    if (query.exec() && query.next()) {
        ui->m_Date_Facture_BRAHIM->setDate(query.value(0).toDate());
    }

    query.prepare("SELECT  reference FROM FINANCES WHERE ID_FACTURE= "+ui->m_ID_Facture_BRAHIM->text()+"");
    query.bindValue(":reference", ui->m_Reference_BRAHIM->text());
    if (query.exec() && query.next()) {
        ui->m_Reference_BRAHIM->setText(query.value(0).toString());
    }
    query.prepare("SELECT  prix FROM FINANCES WHERE ID_FACTURE= "+ui->m_ID_Facture_BRAHIM->text()+"");
    query.bindValue(":reference", ui->m_Prix_BRAHIM->text());
    if (query.exec() && query.next()) {
        ui->m_Prix_BRAHIM->setText(query.value(0).toString());
    }
    query.prepare("SELECT  Statistique FROM FINANCES WHERE ID_FACTURE= "+ui->m_ID_Facture_BRAHIM->text()+"");
    query.bindValue(":reference", ui->m_Statistique_BRAHIM->text());
    if (query.exec() && query.next()) {
        ui->m_Statistique_BRAHIM->setText(query.value(0).toString());
    }

}

void MainWindow::on_Imprimer_but_BRAHIM_clicked()
{
    QPrinter printer;
    printer.setPrinterName("Facture");
    QPrintDialog dialog(&printer,this);
    if (dialog.exec()==QDialog::Rejected) return;
}

//nour thraya

void MainWindow::on_Ajouterclient_NOUR_clicked()
{
    int cin=ui->linecin_NOUR->text().toInt();
     QString nom=ui->linenom_NOUR->text();
     QString prenom=ui->lineprenom_NOUR->text();
     QString adresse=ui->lineadresse_NOUR->text();
     QString email=ui->lineemail_NOUR->text();
     int nbr_point=ui->linenbr_point_NOUR->text().toInt();
     int num_telephone=ui->linenum_telephone_NOUR->text().toInt();


     Client c (cin,nom,prenom,adresse,email,nbr_point,num_telephone,0);


     bool test=c.ajouter();


       if(test)
         {  QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
           notifyIcon->show();
           notifyIcon->showMessage("GESTION CLIENTS ","Client ajouté.",QSystemTrayIcon::Information,15000);
           ui->tableView_NOUR->setModel(c.afficher());
       }
       else
          { QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
           notifyIcon->show();
           notifyIcon->showMessage("GESTION CLIENTS ","Client non ajouté.",QSystemTrayIcon::Information,15000);}



}

void MainWindow::on_pushButton_2_NOUR_clicked()
{
    Client c;
    c.Set_cin(ui->linecin_3_NOUR->text().toInt());
        bool test=c.supprimer(c.Get_cin());

        if(test)
           { QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
            notifyIcon->show();
            notifyIcon->showMessage("GESTION CLIENTS ","Client supprimé.",QSystemTrayIcon::Information,15000);;
        ui->tableView_NOUR->setModel(c.afficher());

        }
        else
           { QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
            notifyIcon->show();
            notifyIcon->showMessage("GESTION CLIENTS ","Client non supprimé.",QSystemTrayIcon::Information,15000);}

}




void MainWindow::on_tableView_2_NOUR_clicked(const QModelIndex &index)
{
   int cin=ui->tableView_2_NOUR->model()->data(index).toInt();
        Client C;

        C=C.SelectModif(cin);
        if(C.Get_cin()!=0)
        {

       ui->lineEdit_NOUR->setText(QString(QString::number(C.Get_cin())));

       ui->lineEdit_2_NOUR->setText(QString(C.Get_nom()));

       ui->lineEdit_3_NOUR->setText(QString(C.Get_prenom()));

       ui->lineEdit_4_NOUR->setText(QString(C.Get_adresse()));

       ui->lineEdit_5_NOUR->setText(QString(C.Get_email()));

       ui->lineEdit_6_NOUR->setText(QString(QString::number(C.Get_nbr_point())));

       ui->lineEdit_7_NOUR->setText(QString(QString::number(C.Get_num_telephone())));

       //ui->lineEdit_8_NOUR->setText(QString(QString::number(C.Get_id_commandes())));



        qDebug()<<C.Get_cin()<<"CinModif";
        }
}

void MainWindow::on_choix_cin_NOUR_clicked()
{
           int cin=ui->lineEdit_NOUR->text().toInt();
           QString nom=ui->lineEdit_2_NOUR->text();
           QString prenom=ui->lineEdit_3_NOUR->text();
           QString adresse=ui->lineEdit_4_NOUR->text();
           QString email=ui->lineEdit_5_NOUR->text();
           int nbr_point=ui->lineEdit_6_NOUR->text().toInt();
           int num_telephone=ui->lineEdit_7_NOUR->text().toInt();
           //int id_commande=ui->lineEdit_8_NOUR->text().toInt();


           bool test=false;


           //Client c(cin,nom,prenom,adresse,email,nbr_point,num_telephone,0);
           test=c.Modifer(cin,nom,prenom,adresse,email,nbr_point,num_telephone,0);

           if(test==true)
           {

             ui->tableView_2_NOUR->setModel(c.afficher()); //affichage automatique apres modification

             QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                        notifyIcon->show();
                        notifyIcon->showMessage("GESTION CLIENTS ","Client Modifié.",QSystemTrayIcon::Information,15000);

           }
           else
           {
               QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                          notifyIcon->show();
                          notifyIcon->showMessage("GESTION CLIENTS ","Client Non Modifié.",QSystemTrayIcon::Information,15000);

           }
}




void MainWindow::on_Recherche_NOUR_textChanged(const QString &arg1)
{
    Client c;
    if(ui->Recherche_NOUR->text() == ""){


            ui->tableView_NOUR->setModel(c.afficher());
             }
             else
            {
              ui->tableView_NOUR->setModel(c.rechercher(ui->Recherche_NOUR->text()));}
}



void MainWindow::on_comboBox_NOUR_activated(const QString )
{
    int value=ui->comboBox_NOUR->currentIndex();

        if (value==0)
        {
            ui->tableView_NOUR->setModel(c.afficherTricinAsc());
        }
     else   if (value==1)
        {
            ui->tableView_NOUR->setModel(c.afficherTrinomAsc());
        }

        else   if (value==2)
           {
               ui->tableView_NOUR->setModel(c.afficherTri_prenom_Asc());
           }
        else   if (value==3)
           {
               ui->tableView_NOUR->setModel(c.afficherTri_adresse_Asc());
           }
        else   if (value==4)
           {
               ui->tableView_NOUR->setModel(c.afficherTri_prenom_Asc());
           }
        else   if (value==5)
           {
               ui->tableView_NOUR->setModel(c.afficherTri_nbr_point_Asc());
           }
        else   if (value==6)
           {
               ui->tableView_NOUR->setModel(c.afficherTri_num_telephone_Asc());
           }

        else   if (value==7)
           {
               ui->tableView_NOUR->setModel(c.afficherTri_commandes_Asc());
           }

}



void MainWindow::on_pushButton_3_NOUR_clicked()
{
    QPrinter printer;
    QPrintDialog dialog(&printer, this);

    if (ui->tableView_NOUR->tabKeyNavigation())
    dialog.addEnabledOption(QAbstractPrintDialog::PrintSelection);

    if (dialog.exec() !=QDialog::Accepted)
    {return;}

}

void MainWindow::on_pushButton_4_NOUR_clicked()
{

    QString file_name=QFileDialog::getSaveFileName(this,"open a file","c://");
    QFile file(file_name);

    if (!file.open(QFile::ReadOnly |  QFile::Text))
    {QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
        notifyIcon->show();
        notifyIcon->showMessage("file  ","file not open.",QSystemTrayIcon::Information,15000);}

    QTextStream in (&file);
    QString text = in.readAll();
    ui->plainTextEdit_NOUR->setPlainText(text);




    file.close();


}

void MainWindow::update_label()
{
    data=A.read_from_arduino();

    if(data=="1")

    {
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                          notifyIcon->show();
                         notifyIcon->setIcon(QIcon("C:/Users/slimd/OneDrive/Bureau/charte graphique/icon.gif"));

                          notifyIcon->showMessage("Detection de fumée!!! ","DANGER!!!",QSystemTrayIcon::Warning,15000);
    }


}


void MainWindow::on_detect_clicked()   // implémentation du slot bouton on
{
     A.write_to_arduino("0"); //envoyer 0 à arduino
}



//slim drira

void MainWindow::update_label_slim()
{
    data=A.read_from_arduino();

    if(data=="1")

    {
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                          notifyIcon->show();
                         notifyIcon->setIcon(QIcon("C:/Users/slimd/OneDrive/Bureau/charte graphique/icon.gif"));

                          notifyIcon->showMessage("Detection de fumée!!! ","DANGER!!!",QSystemTrayIcon::Warning,15000);
    }




}

void MainWindow::on_detect_slim_clicked()   // implémentation du slot bouton on
{
     A.write_to_arduino("0"); //envoyer 0 à arduino
}


void MainWindow::on_ajouter_slim_clicked()
{

     int id_commande_slim=ui->A_idcommande_slim->text().toInt();
     int quantite_slim=ui->A_quantite_2_slim->text().toInt();
      QString encaissement(ui->A_encaissement_slim->currentText());
       QString service(ui->A_service_slim->currentText());
       QString reclamation=ui->A_reclamation_slim->text();
     QDate datecommande=ui->A_datecommande_slim->date();
     int cin_c=ui->A_cinclient_slim->text().toInt();

     Commandes C(id_commande_slim,quantite_slim,encaissement,service,reclamation,datecommande,cin_c);
     bool test=C.ajouter();



       if(test)
         {  QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
           notifyIcon->show();
          notifyIcon->setIcon(QIcon("C:/Users/slimd/OneDrive/Bureau/charte graphique/icon.gif"));

           notifyIcon->showMessage("GESTION DES COMMANDES","Ajout avec succés.",QSystemTrayIcon::Information,15000);
           ui->tableView_slim->setModel(C.afficher());



       }
       else
          { QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
           notifyIcon->show();
          notifyIcon->setIcon(QIcon("C:/Users/slimd/OneDrive/Bureau/charte graphique/icon.gif"));

           notifyIcon->showMessage("ERREUR ","Echec d'ajout.",QSystemTrayIcon::Information,15000);
       }



}

void MainWindow::on_A_quitter_slim_clicked()
{
    QApplication::quit();
}

void MainWindow::on_A_quitter2_slim_clicked()
{
    QApplication::quit();
}

void MainWindow::on_A_quitter3_slim_clicked()
{
    QApplication::quit();
}

void MainWindow::on_A_quitter4_slim_clicked()
{
    QApplication::quit();
}

void MainWindow::on_A_quitter5_slim_clicked()
{
    QApplication::quit();
}

void MainWindow::on_ajouter_2_slim_clicked()
{
    int id_livraison=ui->A_idlivraison_2_slim->text().toInt();
    QString adresse=ui->A_adresse_3_slim->text();
    QString facturation(ui->A_facturation_2_slim->currentText());
    int cin_e=ui->A_cinemploye_slim->text().toInt();
    int id_commande=ui->A_idcommande2_slim->text().toInt();
    QDate datelivraison=ui->A_datelivraison_2_slim->date();
    QString maps=ui->A_adresse_3_slim->text();



    Livraisons L(id_livraison,adresse,facturation,cin_e,id_commande,datelivraison,maps);
    bool test=L.ajouterL();



      if(test)
        {  QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
          notifyIcon->show();
         notifyIcon->setIcon(QIcon("C:/Users/slimd/OneDrive/Bureau/charte graphique/icon.gif"));

          notifyIcon->showMessage("GESTION DES  LIVRAISON ","Livraison Ajouté.",QSystemTrayIcon::Information,15000);
          ui->tableView_2_slim->setModel(L.afficherL());
      }
      else
         { QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
          notifyIcon->show();
         notifyIcon->setIcon(QIcon("C:/Users/slimd/OneDrive/Bureau/charte graphique/icon.gif"));

          notifyIcon->showMessage("ERREUR","Livraison non ajouté.",QSystemTrayIcon::Information,15000);
      }



}


void MainWindow::on_Af_rechercher_slim_textChanged()
{
    Commandes C;
            if(ui->Af_rechercher_slim->text() == "")
                {
                    ui->tableView_slim->setModel(C.afficher());
                }
                else
                {
                     ui->tableView_slim->setModel(C.rechercher(ui->Af_rechercher_slim->text()));
                }

    }

void MainWindow::on_S_rechercher_slim_textChanged()
{
    Commandes C;
            if(ui->S_rechercher_slim->text() == "")
                {
                    ui->S_tab_slim->setModel(C.afficher());
                }
                else
                {
                     ui->S_tab_slim->setModel(C.rechercher(ui->S_rechercher_slim->text()));
                }

}


void MainWindow::on_supprimer_slim_clicked()
{
    Commandes C;
    C.Set_id_commande(ui->S_rechercher_slim->text().toInt());
        bool test=C.supprimer(C.Get_id_commande());


        if(test)
           { QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
            notifyIcon->show();
           notifyIcon->setIcon(QIcon("C:/Users/slimd/OneDrive/Bureau/charte graphique/icon.gif"));

            notifyIcon->showMessage("GESTION DES  COMMANDES ","Commande supprimé.",QSystemTrayIcon::Information,15000);
        ui->tableView_slim->setModel(C.afficher());

        }
        else
           { QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
            notifyIcon->show();
           notifyIcon->setIcon(QIcon("C:/Users/slimd/OneDrive/Bureau/charte graphique/icon.gif"));

            notifyIcon->showMessage("ERREUR","Commande non supprimé.",QSystemTrayIcon::Information,15000);
        }

}
void MainWindow::on_A_idlivraison_2_slim_textChanged()
{
    QSqlQuery query;
    QSqlQueryModel * model= new QSqlQueryModel();


          model->setQuery("SELECT  id commande FROM commandes WHERE id_commande= ''");
             query.bindValue(":id_commande", ui->A_idcommande2_slim->text().toInt());
             if (query.exec() && query.next())
             {
                 ui->A_idcommande2_slim->text().toInt();
             }


}

void MainWindow::on_trier_2_slim_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();



       model->setQuery("select * from COMMANDES order by id_commande");

       model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_commande"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("quantite"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("encaissement"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("service"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("reclamation"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("datecommande"));
       model->setHeaderData(6, Qt::Horizontal, QObject::tr("cin_c"));


               ui->tableView_slim->setModel(model);
                ui->tableView_slim->show();
}






void MainWindow::on_modifier_slim_clicked()
{
    Commandes C;
    int id_commande=ui->m_idcommande_slim->text().toInt();
    QDate datecommande=ui->m_datecommande_slim->date();
    int cin_c=ui->m_cinclient_slim->text().toInt();
    QString reclamation=ui->m_reclamation_slim->text();
    QString encaissement(ui->m_encaissement_slim->currentText());
    int quantite=ui->m_quantite_slim->text().toInt();
    QString service(ui->m_service_slim->currentText());

    C.modifier(id_commande,quantite,encaissement,service,reclamation,datecommande,cin_c);
    ui->tableView_slim->setModel(C.afficher());

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                      notifyIcon->show();
                     notifyIcon->setIcon(QIcon("C:/Users/slimd/OneDrive/Bureau/charte graphique/icon.gif"));

                      notifyIcon->showMessage("GESTION DES  COMMANDES ","Commande Modifié.",QSystemTrayIcon::Information,15000);
}

void MainWindow::on_m_idcommande_slim_textChanged()
{
    QSqlQuery query;
        query.prepare("SELECT quantite FROM COMMANDES WHERE id_commande= "+ui->m_idcommande_slim->text()+"");
        query.bindValue(":quantite", ui->m_quantite_slim->text());
        if (query.exec() && query.next()) {
            ui->m_quantite_slim->setText(query.value(0).toString());
        }

        query.prepare("SELECT service FROM COMMANDES WHERE id_commande= "+ui->m_idcommande_slim->text()+"");
        query.bindValue(":service", ui->m_service_slim->currentText());
        if (query.exec() && query.next()) {
            ui->m_service_slim->setCurrentText(query.value(0).toString());
        }
        query.prepare("SELECT  encaissement FROM COMMANDES WHERE id_commande= "+ui->m_idcommande_slim->text()+"");
        query.bindValue(":encaissement", ui->m_encaissement_slim->currentText());
        if (query.exec() && query.next()) {
            ui->m_encaissement_slim->setCurrentText(query.value(0).toString());
        }
        query.prepare("SELECT  cin_c FROM COMMANDES WHERE id_commande= "+ui->m_idcommande_slim->text()+"");
        query.bindValue(":cin_c", ui->m_cinclient_slim->text());
        if (query.exec() && query.next()) {
            ui->m_cinclient_slim->setText(query.value(0).toString());
        }
        query.prepare("SELECT  datecommande FROM COMMANDES WHERE id_commande= "+ui->m_idcommande_slim->text()+"");
        query.bindValue("datecommande", ui->m_datecommande_slim->date());
        if (query.exec() && query.next()) {
            ui->m_datecommande_slim->setDate(query.value(0).toDate());
        }
        query.prepare("SELECT  reclamation FROM COMMANDES WHERE id_commande= "+ui->m_idcommande_slim->text()+"");
        query.bindValue(":reclamation", ui->m_reclamation_slim->text());
        if (query.exec() && query.next()) {
            ui->m_reclamation_slim->setText(query.value(0).toString());
        }
}

void MainWindow::on_A_quitter4_2_slim_clicked()
{
    QApplication::quit();

}
void MainWindow::on_m_idlivraison_slim_textChanged()
{
    QSqlQuery query;
        query.prepare("SELECT id_livraison FROM LIVRAISONS WHERE id_livraison= "+ui->m_idlivraison_slim->text()+"");
        query.bindValue(":id_livraison", ui->m_idlivraison_slim->text());
        if (query.exec() && query.next()) {
            ui->m_idlivraison_slim->setText(query.value(0).toString());
        }

        query.prepare("SELECT adresse FROM LIVRAISONS WHERE id_livraison= "+ui->m_idlivraison_slim->text()+"");
        query.bindValue(":adresse", ui->m_adresse_slim->text());
        if (query.exec() && query.next()) {
            ui->m_adresse_slim->setText(query.value(0).toString());
        }
        query.prepare("SELECT facturation FROM LIVRAISONS WHERE id_livraison= "+ui->m_idlivraison_slim->text()+"");
        query.bindValue(":facturation", ui->m_facturation_slim->currentText());
        if (query.exec() && query.next()) {
            ui->m_facturation_slim->setCurrentText(query.value(0).toString());
        }
        query.prepare("SELECT cin_e FROM LIVRAISONS WHERE id_livraison= "+ui->m_idlivraison_slim->text()+"");
        query.bindValue(":cin_e", ui->m_cinemploye_slim->text());
        if (query.exec() && query.next()) {
            ui->m_cinemploye_slim->setText(query.value(0).toString());
        }



        query.prepare("SELECT datelivraison FROM LIVRAISONS WHERE id_livraison= "+ui->m_idlivraison_slim->text()+"");
        query.bindValue(":datelivraison", ui->m_datelivraison_slim->text());
        if (query.exec() && query.next()) {
            ui->m_datelivraison_slim->setDate(query.value(0).toDate());

}


}

void MainWindow::on_supprimer_2_slim_clicked()
{
    Livraisons L;
    L.Set_id_livraison(ui->S_rechercher_2_slim->text().toInt());
        bool test=L.supprimerL(L.Get_id_livraison());


        if(test)
           {  QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
            notifyIcon->show();
           notifyIcon->setIcon(QIcon("C:/Users/slimd/OneDrive/Bureau/charte graphique/icon.gif"));

            notifyIcon->showMessage("GESTION DES  LIVRAISON ","Livraison supprimé.",QSystemTrayIcon::Information,15000);

        }
        else
           { QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
            notifyIcon->show();
           notifyIcon->setIcon(QIcon("C:/Users/slimd/OneDrive/Bureau/charte graphique/icon.gif"));

            notifyIcon->showMessage("ECHEC ","Livraison non supprimé.",QSystemTrayIcon::Information,15000);
}
}

void MainWindow::on_Af_rechercher_2_slim_textChanged()
{
    Livraisons L;
            if(ui->Af_rechercher_2_slim->text() == "")
                {
                    ui->tableView_2_slim->setModel(L.afficherL());
                }
                else
                {
                     ui->tableView_2_slim->setModel(L.rechercherL(ui->Af_rechercher_2_slim->text()));
                }
}

void MainWindow::on_S_rechercher_2_slim_textChanged()

{
    Livraisons L;
            if(ui->S_rechercher_2_slim->text() == "")
                {
                    ui->S_tab_2_slim->setModel(L.afficherL());
                }
                else
                {
                     ui->S_tab_2_slim->setModel(L.rechercherL(ui->S_rechercher_2_slim->text()));
                }
}

void MainWindow::on_modifierL_slim_clicked()
{
    Livraisons L;
    int id_livraison=ui->m_idlivraison_slim->text().toInt();
    QString adresse=ui->m_adresse_slim->text();
    QString facturation(ui->m_facturation_slim->currentText());
    int cin_e=ui->m_cinemploye_slim->text().toInt();

    QDate datelivraison=ui->m_datelivraison_slim->date();
    QString maps=adresse;


    L.modifierL(id_livraison,adresse,facturation,cin_e,datelivraison,maps);
    ui->tableView_2_slim->setModel(L.afficherL());

}

void MainWindow::on_A_quitter5_2_slim_clicked()
{
    QApplication::quit();


}

void MainWindow::on_A_quitter3_2_slim_clicked()
{
    QApplication::quit();

}

void MainWindow::on_tableView_2_slim_clicked(const QModelIndex &index)
{


    if (index.column()==1) {

        QSqlQueryModel* model = new QSqlQueryModel();
        model=(L.afficherL());
        int aux2=index.row();
        QModelIndex index = model->index(aux2, 1);
           QString aux=index.data().toString();

                QString link=aux;
                QDesktopServices::openUrl(QUrl(link));
}
}

void MainWindow::on_ajouter_3_slim_clicked()
{
    if (ui->comboBox_slim->currentText()=="ENG")
    {
        ui->Ajouter_l->setTabText(0,"Add order");
        ui->Ajouter_l->setTabText(1,"Add delivery");
        ui->Ajouter_l->setTabText(2,"View order");
        ui->Ajouter_l->setTabText(3,"View delivery");
        ui->Ajouter_l->setTabText(4,"Update order");
        ui->Ajouter_l->setTabText(5,"Update delivery");
        ui->Ajouter_l->setTabText(6,"Delete order");
        ui->Ajouter_l->setTabText(7,"Delete delivery");
        ui->Ajouter_l->setTabText(8,"Smoke detector");



        ui->label_9_slim->setText("Delivery ID");
        ui->label_30_slim->setText("Facturation");
        ui->label_33_slim->setText("Delivery Date");
        ui->label_32_slim->setText("ID Worker");
        ui->label_21_slim->setText("ID order");
        ui->label_29_slim->setText("Client Adress");
        ui->trier_2_slim->setText("Sort by id");
        ui->supprimer_slim->setText("Delete");
        ui->ajouter_3_slim->setText("Change");
        ui->label_3_slim->setText("ID Command");
        ui->label_22_slim->setText("ID Card Client");
        ui->trier_3_slim->setText("Sort by id");
        ui->A_quantite_slim->setText("Quantity");
        ui->label_19_slim->setText("Sold");
        ui->label_5_slim->setText("Client Complaint");
        ui->label_8_slim->setText("Client Order");
        ui->label_10_slim->setText("Search");
        ui->A_quitter3_slim->setText("Quit");
        ui->A_quitter3_2_slim->setText("Quit");
        ui->ajouter_2_slim->setText("Accept");
        ui->A_quitter2_slim->setText("Quit");
        ui->label_11_slim->setText("Enter ID order that u want to update");
        ui->label_23_slim->setText("Enter ID delivery that u  want to update");
        ui->label_17_slim->setText("Quantity");
        ui->label_24_slim->setText("Sold");
        ui->label_15_slim->setText("Client complaint");
        ui->label_16_slim->setText("Order date");
        ui->label_26_slim->setText("ID Card Client");

        ui->label_14_slim->setText("Delivery Date");
        ui->label_27_slim->setText("ID Card Worker");
        ui->label_12_slim->setText("Client Adress");
        ui->modifierL_slim->setText("Accept");
        ui->A_quitter4_2_slim->setText("Quit");
        ui->trier_slim->setText("Sort");
        ui->supprimer_slim->setText("Delete");
        ui-> label_31_slim->setText("Search");
        ui->label_18_slim->setText("Search");
        ui->supprimer_2_slim->setText("Delete");
        ui->detect_slim->setText("Neutral MQ2");


    }
    else if (ui->comboBox_slim->currentText()=="FR")
    {
        ui->Ajouter_l->setTabText(0,"Ajouter commande");
        ui->Ajouter_l->setTabText(1,"Ajouter livraison");
        ui->Ajouter_l->setTabText(2,"Afficher commande");
        ui->Ajouter_l->setTabText(3,"Afficher livraison");
        ui->Ajouter_l->setTabText(4,"Modifier commande");
        ui->Ajouter_l->setTabText(5,"Modifier livraison");
        ui->Ajouter_l->setTabText(6,"Supprimer commande");
        ui->Ajouter_l->setTabText(7,"Supprimer livraison");
        ui->Ajouter_l->setTabText(8,"Detecteur de fumée");


        ui->label_9_slim->setText("Id livraison");
        ui->label_30_slim->setText("Facturation");
        ui->label_33_slim->setText("date commande");
        ui->label_32_slim->setText("CIN employe");
        ui->label_21_slim->setText("ID commande");
        ui->label_29_slim->setText("Adresse");
        ui->trier_2_slim->setText("Trier");
        ui->supprimer_slim->setText("Supprimer");
        ui->ajouter_3_slim->setText("Changer");
        ui->label_3_slim->setText("ID Commande");
        ui->label_22_slim->setText("CIN Client");
        ui->trier_3_slim->setText("Trier");
        ui->A_quantite_slim->setText("Quantité");
        ui->label_19_slim->setText("Encaissement");
        ui->label_5_slim->setText("Reclamation Client");
        ui->label_8_slim->setText("Livraison client");
        ui->label_10_slim->setText("Rechercher");
        ui->A_quitter3_slim->setText("Quitter");
        ui->A_quitter3_2_slim->setText("Quitter");
        ui->ajouter_2_slim->setText("Accepter");
        ui->A_quitter2_slim->setText("Quitter");
        ui->label_11_slim->setText("Entre ID Commande Que vous voulez modifier");
        ui->label_23_slim->setText("Enter ID Livraison Que vous voulez modifier");
        ui->label_17_slim->setText("Quantité");
        ui->label_24_slim->setText("Encaissement");
        ui->label_15_slim->setText("Reclamation Client");
        ui->label_16_slim->setText("Date commande");
        ui->label_26_slim->setText("CIN Client");

        ui->label_14_slim->setText("Date livraison");
        ui->label_27_slim->setText("CIN employe");
        ui->label_12_slim->setText("Adresse");
        ui->modifierL_slim->setText("Accepter");
        ui->A_quitter4_2_slim->setText("Quitter");
        ui->trier_slim->setText("Trier");
        ui->supprimer_slim->setText("Supprimer");
        ui-> label_31_slim->setText("Rechercher");
        ui->label_18_slim->setText("Rechercher");
        ui->supprimer_2_slim->setText("Supprimer");
        ui->detect_slim->setText("Retablir le capteur neutre");



    }
}


//farah battikh

void MainWindow::afficher() //avec tri et recherche dynamique
{


    proxy_p = new QSortFilterProxyModel();
    proxy_p->setSourceModel(p.afficherProd());
        proxy_p->setFilterCaseSensitivity(Qt::CaseInsensitive);
        proxy_p->setFilterKeyColumn(selected_p); //selon colone from combobox
    ui->tableView_3->setModel(proxy_p);


}


void MainWindow::on_lineEdit_produit_textChanged(const QString &arg1)
{
    proxy_p->setFilterFixedString(arg1);


}



void MainWindow::on_ajo_clicked()
{
    Notification N;
    int id=ui->lineEdit->text().toInt();
    QString type=ui->lineEdit_2->text();
    QString prix=ui->lineEdit_3->text();
    QString quntite=ui->lineEdit_4->text();


    produits p (id,type,prix,quntite);
    bool test=p.ajouterProd();

    if(test){
        N.notification_ajoutproduit();
       // msgBox.setText("Bien, ajout avec succes.");
    ui->tableView_3->setModel(p.afficherProd());
    }
    //else
        //msgBox.setText("Erreur au niveau de l'ajout!");
        //msgBox.exec();


}

void MainWindow::on_sup_returnPressed()
{

}

void MainWindow::on_tableView_3_clicked(const QModelIndex &index)
{
    ui->lineEdit->setText(ui->tableView_3->model()->data(ui->tableView_3->model()->index(index.row(),3)).toString());
         ui->lineEdit_2->setText(ui->tableView_3->model()->data(ui->tableView_3->model()->index(index.row(),0)).toString());
          ui->lineEdit_3->setText(ui->tableView_3->model()->data(ui->tableView_3->model()->index(index.row(),2)).toString());
           ui->lineEdit_4->setText(ui->tableView_3->model()->data(ui->tableView_3->model()->index(index.row(),1)).toString());


}

void MainWindow::on_pushButton_clicked()
{
    produits p;
    Notification N;
    p.setid(ui->lineEdit ->text().toInt());
    bool test=p.supprimerProd(p.getid_produits());
    if(test){
        N.notification_supprimerproduit();
        ui->tableView_3->setModel(p.afficherProd());}
}

void MainWindow::on_mod_clicked()
{
    Notification N;
    int id=ui->lineEdit->text().toInt();
        QString type=ui->lineEdit_2->text();
        QString prix=ui->lineEdit_3->text();
        QString quntite=ui->lineEdit_4->text();


        produits p (id,type,prix,quntite );
        bool test=p.modidier();

        if(test){
            N.notification_modifierproduit();
           // msgBox.setText("Bien, ajout avec succes.");
        ui->tableView_3->setModel(p.afficherProd());
        }
        //else
            //msgBox.setText("Erreur au niveau de l'ajout!");
            //msgBox.exec();
}

void MainWindow::on_pb_qrcode_clicked()
{

    produits P;
   if(ui->tableView_3->currentIndex().row()==-1)
          QMessageBox::information(nullptr, QObject::tr("attention"),
                                   QObject::tr("Veuillez Choisir un produit du Tableau.\n"
                                               "Click Ok to exit."), QMessageBox::Ok);
      else
      {




                  P.setid(ui->lineEdit ->text().toInt());
                  P.settype(ui->lineEdit_2 ->text());
                  P.setprix(ui->lineEdit_3 ->text());
                  P.setquntite(ui->lineEdit_4 ->text());


        QString  rawQr = "TYPE:%1 PRIX:%2 QUANTITE:%3 ID:%4 " ;
           rawQr = rawQr.arg(P.getid_produits()).arg(P.getprix()).arg(P.getquntite()).arg(P.gettype());
           QrCode qr = QrCode::encodeText(rawQr.toUtf8().constData(), QrCode::Ecc::HIGH);



           std::ofstream myfile;
           myfile.open ("qrcode.svg") ;
           myfile << qr.toSvgString(1);
           myfile.close();
           QSvgRenderer svgRenderer(QString("qrcode.svg"));
           QPixmap pix( QSize(90, 90) );
           QPainter pixPainter( &pix );
           svgRenderer.render( &pixPainter );
           ui->labelqrcode->setPixmap(pix);
      }
}



void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    selected_p=ui->comboBox_2->currentIndex();
            afficher();
}



void MainWindow::on_pushButton_camera_clicked()
{
    Widget w ;
    w.setModal(true);
    w.exec();
}

