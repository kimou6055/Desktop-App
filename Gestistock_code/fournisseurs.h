#ifndef FOURNISSEURS_H
#define FOURNISSEURS_H


#include<QSqlQueryModel>
#include<QPainter>

class fournisseurs
{
public:

   fournisseurs();
   fournisseurs(int,QString,QString,QString,QString,int);

   int getid_fournisseurs();
   QString getnom();
    QString getadresse();
   QString getcategorie();
   QString getlogo();
   int getnum();




   void setid_fournisseurs(int);
   void setnom(QString);
   void setadresse(QString);
   void setcategorie(QString);
   void setlogo(QString);
   void setnum(int);

bool rechercher(int);
    bool ajouterf();
    QSqlQueryModel * afficherf();
 bool modifierjf(int id_fournisseurs ,QString nom , QString adresse  ,QString categorie ,QString logo, int num);

  bool supprimerf(int);

  QSqlQueryModel * rechercherf (const QString &aux);
  void genererPDF();

   private :
   QString nom,adresse;
   QString categorie,logo;
   int id_fournisseurs, num;

};



#endif // FOURNISSEURS_H
