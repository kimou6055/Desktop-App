#include "fournisseurs.h"
//#include<QCameraInfo>
//#include<QString>
#include<QSqlQuery>
//#include<QtDebug>
#include<QObject>
#include<QSqlQueryModel>
#include<QPdfWriter>
#include<QMessageBox>
#include<QSystemTrayIcon>
#include<QPainter>
//#include<QPrinter>


fournisseurs::fournisseurs()
{

    id_fournisseurs=0;
    nom=" ";
    adresse=" ";

    categorie=" ";
    logo=" ";
    num=0;

}

fournisseurs::fournisseurs(int id_fournisseurs,QString nom,QString adresse,QString categorie,QString logo,int num)
{
 this->id_fournisseurs=id_fournisseurs;
   this->nom=nom;
    this->adresse=adresse;
    this->categorie=categorie;
    this->logo=logo;
    this->num=num;

}

int fournisseurs::getid_fournisseurs(){return id_fournisseurs;}
QString fournisseurs::getnom(){return nom;}
QString fournisseurs::getadresse(){return adresse;}
QString fournisseurs::getcategorie(){return categorie;}
QString fournisseurs::getlogo(){return logo;}
int fournisseurs::getnum(){return num;}




void fournisseurs::setid_fournisseurs(int id_fournisseurs){this->id_fournisseurs=id_fournisseurs  ;}
void fournisseurs::setnom(QString nom){this->nom=nom  ;}
void fournisseurs::setadresse(QString adresse){this->adresse=adresse   ;}
void fournisseurs::setcategorie(QString categorie){this->categorie=categorie ;}
void fournisseurs::setlogo(QString logo){this->logo=logo   ;}
void fournisseurs::setnum(int num){this->num=num   ;}


bool fournisseurs::ajouterf()
{
    bool test=false;
    QSqlQuery query;

        QString id_string=QString::number(id_fournisseurs);
        QString num_string=QString::number(num);

          query.prepare("INSERT INTO FOURNISSEURS (id_fournisseurs , nom , adresse , categorie , logo , num) "
                        "VALUES (:id_fournisseurs, :nom, :adresse , :categorie, :logo , :num )");
          query.bindValue(0 , id_string);
          query.bindValue(1 , nom);
          query.bindValue(2 , adresse);
          query.bindValue(3 ,categorie);
          query.bindValue(4 ,logo);
          query.bindValue(5, num_string);


          if (query.exec())
              test=true;
    return test;
}


QSqlQueryModel * fournisseurs ::afficherf()
{

    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select id_fournisseurs, nom, adresse, categorie, num from FOURNISSEURS");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_fournisseurs"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("categorie "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("num"));

        return model;
}

bool fournisseurs::modifierjf (int id_fournisseurs ,QString nom , QString adresse  ,QString categorie ,QString logo, int num)
{
    QSqlQuery query;

    query.prepare("UPDATE FOURNISSEURS SET nom= :nom,adresse= :adresse, categorie= :categorie, logo= :logo, num= :num  where id_fournisseurs= :id_fournisseurs ");
    query.bindValue(":id_fournisseurs", id_fournisseurs);
     query.bindValue(":nom",nom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":categorie",categorie);
    query.bindValue(":logo",logo);
    query.bindValue(":num",num);

            return    query.exec();
}

bool fournisseurs :: supprimerf(int id_fournisseurs)
{

    QSqlQuery query;
    query.prepare("DELETE from FOURNISSEURS where id_fournisseurs = :id_fournisseurs ");
    query.bindValue(":id_fournisseurs",id_fournisseurs);
    return    query.exec();

}

QSqlQueryModel* fournisseurs::rechercherf (const QString &aux)

{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("select id_fournisseurs, nom, adresse, categorie, num from FOURNISSEURS where ((id_fournisseurs || nom || adresse || categorie || logo) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_fournisseurs"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("categorie "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("num"));


    return model;
}


void  fournisseurs::genererPDF(){

                         QPdfWriter pdf("C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/qt/Fournisseurs/integration/test/liste.pdf");
                         QPainter painter(&pdf);

                        int i = 4000;
                             painter.setPen(Qt::red);
                             painter.setFont(QFont("Arial", 30));
                             painter.drawText(500,1500,"Liste Des FOURNISSEURS");
                             painter.setPen(Qt::black);
                             painter.setFont(QFont("Arial", 15));
                            // painter.drawText(1100,2000,afficheDC);
                             painter.drawRect(100,100,7300,2600);

                             painter.drawRect(0,3000,9600,500);
                             painter.setFont(QFont("Arial", 9));
                             painter.drawText(200,3300,"id");
                             painter.drawText(1300,3300,"nom");
                             painter.drawText(2200,3300,"numéro");
                             painter.drawText(3200,3300,"catégorie");

                             QSqlQuery query;
                             query.prepare("select * from FOURNISSEURS");
                             query.exec();
                             while (query.next())
                             {
                                 painter.drawText(200,i,query.value(0).toString());
                                 painter.drawText(1300,i,query.value(1).toString());
                                 painter.drawText(2200,i,query.value(5).toString());
                                 painter.drawText(3200,i,query.value(3).toString());

                                i = i + 500;
                             }


          int reponse = QMessageBox::Yes;
              if (reponse == QMessageBox::Yes)
              {
                  QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                  notifyIcon->show();
                 notifyIcon->setIcon(QIcon("C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/qt/Fournisseurs/charte_graphique/icon.gif"));

                  notifyIcon->showMessage("GESTION DES  FOURNISSEURS ","Liste fournisseurs pret dans PDF",QSystemTrayIcon::Information,15000);

                  painter.end();
              }
              if (reponse == QMessageBox::No)
              {
                   painter.end();
              }
}

