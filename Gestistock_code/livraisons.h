#ifndef LIVRAISONS_H
#define LIVRAISONS_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
class Livraisons
        {
public:
            Livraisons();
            Livraisons(int,QString,QString,int,int,QDate,QString);
            int Get_id_livraison(){return id_livraison;}
              QString Get_adresse(){return adresse;}
               QString Get_facturation(){return facturation;}
               QDate Get_datelivraison(){return datelivraison;}
               int Get_cin_e(){return cin_e;}
               int Get_id_commande(){return id_commande;}
               QString Get_maps(){return maps;}

               void Set_id_livraison(int id_livraison){this->id_livraison=id_livraison;}
               void Set_adresse(QString adresse){this->adresse=adresse;}
               void Set_facturation(QString facturation){this->facturation=facturation;}
               void Set_id_commande(int id_commande){this->id_commande=id_commande;}
               void Set_datelivraison(QDate datelivraison){this->datelivraison=datelivraison;}
               void Set_cin_e(int cin_e){this->cin_e=cin_e;}
                void Set_maps(QString maps){this->maps=maps;}
               bool ajouterL();
               QSqlQueryModel * afficherL(); //  retour hakeka ala khater bech n affichi intefrace QT
               bool supprimerL(int);
               bool modifierL(int,QString,QString,int,QDate,QString);
               QSqlQueryModel* rechercherL (const QString &aux);
               void on_supprimer_slim_2_clicked();
               void on_Af_rechercher_slim_2_textChanged();
               void on_S_rechercher_2_slim_textChanged();
               void on_modifierL_slim_clicked();

private:
               int id_livraison;
               QString adresse;
               QString facturation;
               int cin_e;
               int id_commande;
               QDate datelivraison;
                QString maps;

        };
#endif // LIVRAISONS_H
