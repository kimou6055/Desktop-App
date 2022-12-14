#include "Client.h"

#include<QtDebug>
#include <QFileDialog>
#include <QSystemTrayIcon>
#include<QDesktopServices>


Client::Client()
{

}
Client::Client(int cin,QString nom,QString prenom,QString adresse,QString email,int nbr_point,int num_telephone,int id_commandes)
{
    this->cin=cin;
    this->nom=nom;
    this->prenom=prenom;
    this->adresse=adresse;
    this->email=email;
    this->nbr_point=nbr_point;
    this->num_telephone=num_telephone;
    this->id_commandes=id_commandes;

}


QSqlQueryModel * Client::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
         model->setQuery("SELECT * FROM CLIENTS");

        // QString g=QString::number()
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("email"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("nbr_point"));
         model->setHeaderData(6, Qt::Horizontal, QObject::tr("num_telephone"));
         model->setHeaderData(7, Qt::Horizontal, QObject::tr("id commandes"));


    return model;
}


bool Client::supprimer(int cin)
{
    QSqlQuery query;
    QString res=QString::number(cin);
    query.prepare("Delete from clients where CIN=:cin");
    query.bindValue(":cin",res);

    return query.exec();
}


bool Client::ajouter()
{
    QSqlQuery query;
    QString cinn= QString::number(cin);
    QString nbr_points= QString::number(nbr_point);
    QString num_telephones= QString::number(num_telephone);


    query.prepare("INSERT INTO CLIENTS(cin, nom, prenom,adresse,email,nbr_point,num_telephone,id_commande) "
                  "VALUES (:cin, :nom, :prenom,:adresse,:email, :nbr_point, :num_telephone, :id_commande)");
    query.bindValue(":cin", cinn);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":email", email);
    query.bindValue(":nbr_point", nbr_points);
    query.bindValue(":num_telephone", num_telephones);
    query.bindValue(":id_commande", id_commandes);



    return query.exec();
   // return test;

}

Client Client::SelectModif(int cin)
{
    QSqlQuery query;
    QString res=QString::number(cin);
    query.prepare("Select * from CLIENTS where CIN=:cin");
    query.bindValue(":cin",res);
    query.exec();
    query.next();
    int cinval=query.value(0).toInt();
    QString nomval=query.value(1).toString();
    QString prenomval=query.value(2).toString();
    QString adresseval=query.value(3).toString();
    QString emailval=query.value(4).toString();
    int nbr_pointval=query.value(5).toInt();
    int num_telephoneval=query.value(6).toInt();
    int commandesval=query.value(7).toInt();


    Client C(cinval,nomval,prenomval,adresseval,emailval,nbr_pointval,num_telephoneval,commandesval);

    return C;
}




bool Client::Modifer(int cin,QString nom, QString prenom,QString adresse,QString email,int nbr_point,int num_telephone,int id_commande)
   {
    QSqlQuery query;
       QString cin_string=QString::number(cin);
       QString nbr_point_string=QString::number(nbr_point);
       QString num_telephone_string=QString::number(num_telephone);
       QString id_commandes_string=QString::number(id_commande);

       query.prepare("UPDATE CLIENTS SET nom= :nom, prenom= :prenom,adresse= :adresse,nbr_point= :nbr_point,num_telephone= :num_telephone,email= :email, id_commande= :id_commande where CIN=:cin");
       query.bindValue(":cin", cin_string);
       query.bindValue(":nom", nom);
       query.bindValue(":prenom", prenom);
       query.bindValue(":adresse", adresse);
       query.bindValue(":nbr_point", nbr_point_string);
       query.bindValue(":num_telephone", num_telephone_string);
       query.bindValue(":email", email);
       query.bindValue(":id_commande", id_commandes_string);

       return query.exec();

}

/*QSqlQueryModel * Client::rechercher(QString mot)
{
     QSqlQuery query;
     query.prepare("SELECT * FROM CLIENTS where ((NOM like :NOMC) or (PRENOM like :NOMC) or (ADRESSE like :NOMC) or "
        "(NBR_POINT like :NOMC) or (CIN like :NOMC) or (NUM_TELEPHONE like :NOMC) or (EMAIL like :NOMC) or (ID_COMMANDE like :COMMANDESC)) ");
     query.bindValue(":NOMC", mot);
     query.exec();

    QSqlQueryModel * model= new QSqlQueryModel();
         model->setQuery(query);


    return model;
}
*/

QSqlQueryModel* Client::rechercher(const QString &aux)

{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("select * from CLIENTS where ((CIN || NOM || PRENOM || ADRESSE || EMAIL|| NBR_POINT|| NUM_TELEPHONE||ID_COMMANDE) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nbr_point "));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("num_telephone "));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("aux "));



    return model;
}


//**********************TRI******************************* //


QSqlQueryModel * Client::afficherTricinAsc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
         model->setQuery("SELECT * FROM CLIENTS order by cin ASC");
    return model;
}

QSqlQueryModel * Client::afficherTrinomAsc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
         model->setQuery("SELECT * FROM CLIENTS order by nom ASC");
    return model;
}

QSqlQueryModel * Client::afficherTri_prenom_Asc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
         model->setQuery("SELECT * FROM CLIENTS order by prenom ASC");
    return model;
}

QSqlQueryModel * Client::afficherTri_adresse_Asc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
         model->setQuery("SELECT * FROM CLIENTS order by adresse ASC");
    return model;
}

QSqlQueryModel * Client::afficherTri_email_Asc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
         model->setQuery("SELECT * FROM CLIENTS order by email ASC");
    return model;
}

QSqlQueryModel * Client::afficherTri_nbr_point_Asc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
         model->setQuery("SELECT * FROM CLIENTS order by nbr_point ASC");
    return model;
}

QSqlQueryModel * Client::afficherTri_num_telephone_Asc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
         model->setQuery("SELECT * FROM CLIENTS order by num_telephone ASC");
    return model;
}

QSqlQueryModel * Client::afficherTri_commandes_Asc()
{
    QSqlQueryModel * model= new QSqlQueryModel();
         model->setQuery("SELECT * FROM CLIENTS order by id_commandes ASC");
    return model;
}

void Client::ajoutPoint()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT CIN FROM CLIENTS");

       int x= model->rowCount();

         int i=0;
        for(i;i<x;i++)
         {
            QVariant  y= model->index(i,0).data();


            QSqlQueryModel * model2= new QSqlQueryModel();
            QString cintest=QString::number( y.toInt());

            QSqlQuery query;
            model2->setQuery("SELECT * FROM COMMANDES WHERE CIN_C = '"+cintest+"' ");

            int x2= model2->rowCount();
            int points=0;

            if(x2==0){
                points=0;}

            else{

               points =x2 *100/5;
            }
             qDebug()<<points;
               QString nbr_point_string=QString::number(points);

              query.prepare("UPDATE CLIENTS SET nbr_point= :nbr_point WHERE CIN = '"+cintest+"'");
              query.bindValue(":nbr_point", nbr_point_string);

               query.exec();

         }







}

