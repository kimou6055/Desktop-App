#include "commandes.h"
#include<QtDebug>
#include <QDate>
Commandes::Commandes()
{

}
Commandes::Commandes(int id_commande,int quantite,QString encaissement,QString service,QString reclamation,QDate datecommande,int cin_c)
{
    this->id_commande=id_commande;
    this->quantite=quantite;
    this->encaissement=encaissement;
    this->service=service;
    this->reclamation=reclamation;
    this->datecommande=datecommande;
    this->cin_c=cin_c;

}


QSqlQueryModel * Commandes::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
         model->setQuery("SELECT * FROM COMMANDES");
         qDebug()<<"connection";
        // QString g=QString::number()
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_commande"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("quantite"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("encaissement"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("service"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("reclamation"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("datecommande"));
         model->setHeaderData(6, Qt::Horizontal, QObject::tr("cin_c"));
    return model;
}
bool Commandes :: supprimer(int id_commande)
{

    QSqlQuery query;
    query.prepare("DELETE from COMMANDES where id_commande = :id_commande ");
    query.bindValue(":id_commande",id_commande);
    return    query.exec();

}


bool Commandes::modifier(int id_commande ,int quantite , QString encaissement  ,QString service ,QString reclamation, QDate datecommande,int cin_c)
    {
        QSqlQuery query;

        query.prepare("UPDATE COMMANDES SET quantite= :quantite,encaissement= :encaissement,service= :service ,reclamation=:reclamation, datecommande= :datecommande,cin_c=:cin_c where id_commande=:id_commande ");
        query.bindValue(":id_commande", id_commande);
        query.bindValue(":quantite",quantite);
        query.bindValue(":encaissement", encaissement);
        query.bindValue(":service",service);
        query.bindValue(":reclamation",reclamation);
        query.bindValue(":datecommande",datecommande);
        query.bindValue(":cin_c",cin_c);

                return    query.exec();
    }
bool Commandes::ajouter()
{

    QSqlQuery query;


          query.prepare("INSERT INTO COMMANDES (id_commande , quantite ,  encaissement , service ,reclamation, datecommande, cin_c) "
                        "VALUES (:id_commande, :quantite, :encaissement , :service , :reclamation, :datecommande, :cin_c)");
          query.bindValue(":id_commande" , id_commande);
          query.bindValue(":quantite", quantite);
          query.bindValue(":encaissement",encaissement);
          query.bindValue(":service", service);
          query.bindValue(":reclamation", reclamation);
          query.bindValue(":datecommande", datecommande);
          query.bindValue(":cin_c", cin_c);


    return query.exec();

}
QSqlQueryModel* Commandes::rechercher (const QString &aux)

{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("select * from COMMANDES where ((id_commande || quantite || encaissement || service || reclamation || datecommande || cin_c) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_commandes"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("quantite"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("encaissement"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("service"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("reclamation"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("datecommande"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("cin_c "));


    return model;
}

