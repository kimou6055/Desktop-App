#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
#include <QWidget>
#include <QFileDialog>
#include <QTextDocument>
#include <QDebug>
#include <QtPrintSupport/QPrinter>
#include "produits.h"
#include <QString>
produits::produits()
{
     type="";
    prix="";
     quntite="";


}
int produits::getid_produits(){return id;}
void produits::setid(int id){this->id=id;}

QString produits::gettype(){return type;}
void produits::settype(QString type){this->type=type;}

QString produits::getquntite(){return quntite;}
void produits::setquntite(QString quntite){this->quntite=quntite;}

QString produits::getprix(){return prix;}
void produits::setprix(QString prix){this->prix=prix;}





produits::produits(int id,QString type,QString prix,QString quntite)
{
    this->id=id;
     this->type=type;
    this->prix=prix;
     this->quntite=quntite;

}
QSqlQueryModel* produits::afficherProd()
{
    QSqlQueryModel* model=new QSqlQueryModel() ;


    model->setQuery("SELECT* FROM PRODUITS");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID"));

return model;

}
bool produits::ajouterProd()
{


   QSqlQuery query;

     query.prepare("INSERT INTO PRODUITS (TYPE ,PRIX , QUANTITE,ID) "
                   "VALUES ( :type, :prix, :quantite, :id)" );
     query.bindValue(":id", id);
     query.bindValue(":type",type );
     query.bindValue(":prix", prix);
     query.bindValue(":quantite",quntite);



     return query.exec();



   // return test;
}
 bool produits::modidier()
 {
     QSqlQuery query;
     query.prepare("UPDATE PRODUITS SET TYPE=:type ,PRIX=:prix ,QUANTITE=:quantite,ID=:id");
     query.bindValue(":id", id);
     query.bindValue(":type",type );
     query.bindValue(":prix", prix);
     query.bindValue(":quantite",quntite);
      return query.exec();


 }

bool produits::supprimerProd(int id)
{
QSqlQuery query;
query.prepare("DELETE FROM PRODUITS WHERE ID=:0 ");
query.bindValue(":0",id);
return  query.exec();
}
