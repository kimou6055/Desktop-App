#ifndef CLIENT_H
#define CLIENT_H
#include<QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include <QObject>

class Client
{
    QString nom,prenom,adresse,email;
    int cin,nbr_point,num_telephone,id_commandes;

public:
    Client();
    Client(int,QString,QString,QString,QString,int,int,int);
    int Get_cin(){return cin;}
    QString Get_nom(){return nom;}
    QString Get_prenom(){return prenom;}
    QString Get_adresse(){return adresse;}
    QString Get_email(){return email;}
    int Get_nbr_point(){return nbr_point;}
    int Get_num_telephone(){return num_telephone;}
    int Get_id_commandes(){return id_commandes;}


    void Set_cin(int cin){this->cin=cin;}
    void Set_nom(QString nom){this->nom=nom;}
    void Set_prenom(QString prenom){this->prenom=prenom;}
    void Set_adresse(QString adresse){this->adresse=adresse;}
    void Set_email(QString email){this->email=email;}
    void Set_nbr_point(int nbr_point){this->nbr_point=nbr_point;}
    void Set_num_telephone(int num_telephone){this->num_telephone=num_telephone;}
    void Set_id_commandes(int id_commandes){this->id_commandes=id_commandes;}


    bool ajouter();   // khater bech tokhrej true or false (nja7 l ajout wale)
    QSqlQueryModel * afficher(); //  retour hakeka ala khater bech n affichi intefrace QT
    bool supprimer(int);   // bool type de retour, w int eli bech yodkhlelha (cin)
  // dakhlelha cin (t modifie selon cin) w tkharajlek client
    Client SelectModif(int);
    bool Modifer(int cin,QString nom, QString prenom,QString adresse,QString email,int nbr_point,int num_telephone,int id_commande);
    QSqlQueryModel * rechercher(const QString &aux);
    QSqlQueryModel * afficherTricinAsc();
    QSqlQueryModel * afficherTrinomAsc();
    QSqlQueryModel * afficherTri_prenom_Asc();
    QSqlQueryModel * afficherTri_adresse_Asc();
    QSqlQueryModel * afficherTri_email_Asc();
    QSqlQueryModel * afficherTri_nbr_point_Asc();
    QSqlQueryModel * afficherTri_num_telephone_Asc();
    QSqlQueryModel * afficherTri_commandes_Asc();
    void ajoutPoint();





};



#endif // CLIENT_H
