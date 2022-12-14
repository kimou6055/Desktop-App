#ifndef COMMANDES_H
#define COMMANDES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
class Commandes
{

public:
    Commandes();
    Commandes(int,int,QString,QString,QString,QDate,int);
      int Get_id_commande(){return id_commande;}
      int Get_quantite(){return quantite;}
       QString Get_encaissement(){return encaissement;}
       QString Get_service(){return service;}
       QString Get_reclamation(){return reclamation;}
       QDate Get_datecommande(){return datecommande;}
       int Get_cin_c(){return cin_c;}


       void Set_id_commande(int id_commande){this->id_commande=id_commande;}
       void Set_quantite(int quantite){this->quantite=quantite;}
       void Set_encaissement(QString encaissement){this->encaissement=encaissement;}
       void Set_service(QString service){this->service=service;}
       void Set_reclamation(QString reclamation){this->reclamation=reclamation;}
       void Set_datecommande(QDate datecommande){this->datecommande=datecommande;}
       void Set_cin_c(int cin_c){this->cin_c=cin_c;}

       bool ajouter();
       QSqlQueryModel * afficher();
       bool supprimer(int);
       bool modifier(int,int,QString,QString,QString,QDate,int);
  QSqlQueryModel * rechercher (const QString &aux); //  retour hakeka ala khater bech n affichi intefrace QT
  void on_supprimer_slim_clicked();
  void on_modifier_slim_clicked();
  void on_m_idcommande_slim_textChanged();



private:
       int id_commande;
       int quantite;
       QString encaissement;
       QString service;
       QString reclamation;
       QDate datecommande;
       int cin_c;
   };



#endif // COMMANDES_H
