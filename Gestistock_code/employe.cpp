#include "employe.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlQueryModel>


Employe::Employe() //Set default value  au niveau du constructeur par defaut
{

    this->cin= 0;
    this->nom= " ";
    this->prenom= " ";
    this->Email= " ";
    this->poste= " ";
    this->Salaire= 0;
}

Employe::Employe(int cin, QString nom, QString prenom, QString Email, QString poste, float Salaire) //Attribuer les valeurs saisis au attribut de la classe
{
    this->cin= cin;
    this->nom= nom;
    this->prenom = prenom;
    this->Email= Email;
    this->poste= poste;
    this->Salaire= Salaire;
}

int Employe::getCIN(){return cin;}
QString Employe::getNom(){return nom;}
QString Employe::getPrenom(){return prenom;}
QString Employe::getEmail(){return Email;}
QString Employe::getPoste(){return poste;}
float Employe::getSalaire(){return Salaire;}


void Employe::setCIN(int cin){this->cin= cin;}
void Employe::setNom(QString nom){this->nom= nom;}
void Employe::setPrenom(QString prenom){this->prenom= prenom;}
void Employe::setEmail(QString Email){this->Email= Email;}
void Employe::setPoste(QString poste){this->poste= poste;}
void Employe::setSalaire(float Salaire){this->Salaire= Salaire;}




bool Employe::ajouter(){
    QSqlQuery query; //variable à utliser pour l'execution de ma requete
    QString cin_string = QString::number(cin);
    QString salaire_string = QString::number(Salaire);




   //Je prépare ma requete d'insertion : Insert dans la table Employes

    query.prepare("Insert into Employes (cin, NOM, prenom, Email, poste, salaire)"
                  "values(:cin, :nom, :prenom, :Email, :poste, :salaire)");
    //values(?, ?, ?, .....);

    //Inserer les valeurs des champs
    query.bindValue(":cin", cin_string);                            //query.bindValue(0, cin);
    query.bindValue(":nom", nom);                           //query.bindValue(1, nom);
    query.bindValue(":prenom", prenom);                    //query.bindValue(2, prenom);
    query.bindValue(":Email", Email);
    query.bindValue(":poste", poste);
    query.bindValue(":salaire", salaire_string);


    return query.exec();
}

QSqlQueryModel* Employe::afficher()
{
   QSqlQueryModel* model= new QSqlQueryModel();

         model->setQuery("SELECT* FROM EMPLOYES");
         /*model->setHeaderData(0, Qt::Horizontal, QObject::tr("Name"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("Salary"));*/


    return model;
}

bool Employe::supprimer(int)
{
    QSqlQuery query;
    query.prepare("Delete from Employes where cin= :cin");
    query.bindValue(":cin", cin);

    return query.exec();
}

bool Employe::modifier(int cin)
{
    QSqlQuery query;
    QString cin_string = QString::number(cin);
    QString salaire_string = QString::number(Salaire);
    //QString poste;
    query.prepare("UPDATE Employes SET poste=:poste, salaire=:salaire WHERE cin=:cin ");

    query.bindValue(":cin", cin_string);

    query.bindValue(":poste", poste);
    query.bindValue(":salaire", salaire_string);


    return query.exec();
}


QSqlQueryModel * Employe::Find_Employe() //EXCEL
{
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT cin, nom, prenom, Email, poste, Salaire FROM EMPLOYES");

    query.exec();
    model->setQuery(query);
    return model;
}

QSqlQueryModel * Employe::recherche_employe(QString search)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString qry="select * from employes where cin like '%"+search+"%' or nom like '%"+search+"%' or prenom like '%"+search+"%' or Salaire like '%"+search+"%' ";
    qDebug()<<qry;
    model->setQuery(qry);
    return model;
}

QSqlQueryModel * Employe::tri()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM employes ORDER BY NOM");
        return model;
}


QSqlQueryModel * Employe::tri2()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM employes ORDER BY SALAIRE");
        return model;
}
