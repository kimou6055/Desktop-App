#include "livraisons.h"
#include<QtDebug>
#include <QDate>
#include <QString>
Livraisons::Livraisons()
{

}
Livraisons::Livraisons(int id_livraison,QString adresse,QString facturation,int cin_e,int id_commande,QDate datelivraison, QString maps)
{
    this->id_livraison=id_livraison;
    this->adresse=adresse;
    this->facturation=facturation;
    this->cin_e=cin_e;
    this->id_commande=id_commande;
    this->datelivraison=datelivraison;

}


QSqlQueryModel * Livraisons::afficherL()
{
    QSqlQueryModel * model= new QSqlQueryModel();
         model->setQuery("SELECT * FROM LIVRAISONS");
         qDebug()<<"connection";
        // QString g=QString::number()
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_livraison"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("adresse"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("facturation"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("cin_e"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_commande"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("datelivraison"));


    return model;
}

bool Livraisons :: supprimerL(int id_livraison)
{

    QSqlQuery query;
    query.prepare("DELETE from LIVRAISONS where id_livraison=:id_livraison ");
    query.bindValue(":id_livraison",id_livraison);
    return    query.exec();

}

bool Livraisons::modifierL(int id_livraison,QString adresse,QString facturation,int cin_e,QDate datelivraison,QString maps)
    {
        QSqlQuery query;

        query.prepare("UPDATE LIVRAISONS SET ADRESSE=:ADRESSE,FACTURATION=:FACTURATION,CIN_E=:CIN_E,DATELIVRAISON=:DATELIVRAISON where ID_LIVRAISON=:ID_LIVRAISON");
        query.bindValue(":ID_LIVRAISON", id_livraison);
        query.bindValue(":ADRESSE",adresse);
        query.bindValue(":FACTURATION", facturation);
        query.bindValue(":CIN_E",cin_e);
        query.bindValue(":DATELIVRAISON",datelivraison);



                return    query.exec();
    }
  bool Livraisons::ajouterL()
  {
      QSqlQuery query;

      QString id_livraison_2=QString::number(id_livraison);
      QString cin_e_2=QString::number(cin_e);
      QString id_commande_2=QString::number(id_commande);


            query.prepare("INSERT INTO LIVRAISONS ( ID_LIVRAISON , ADRESSE ,  FACTURATION , CIN_E , ID_COMMANDE,  DATELIVRAISON) "
                          "VALUES (:id_livraison,:adresse,:facturation,:cin_e,:id_commande,:datelivraison)");
            query.bindValue(":id_livraison", id_livraison_2);
            query.bindValue(":adresse",adresse);
            query.bindValue(":facturation", facturation);
            query.bindValue(":cin_e",cin_e_2);
            query.bindValue(":id_commande",id_commande_2);
            query.bindValue(":datelivraison",datelivraison);


      return query.exec();

  }
  QSqlQueryModel* Livraisons::rechercherL (const QString &aux)

  {
      QSqlQueryModel* model = new QSqlQueryModel();

      model->setQuery("select * from LIVRAISONS where ((id_livraison || adresse || facturation || cin_e || id_commande || datelivraison) LIKE '%"+aux+"%')");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_livraison"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("adresse"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("facturation"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("cin_e"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("id_commande"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("datelivraison"));


      return model;
  }

