#ifndef PRODUITS_H
#define PRODUITS_H
#include <QString>
//#include <QSqlQuery>
#include <QSqlQueryModel>
#include <cstdlib>

class produits
{
private:
    QString type;
    QString prix;
    QString quntite;
    int id;


public:
   int getid_produits();
   QString getprix();
   QString getquntite();
   QString gettype();
   void setid(int);
   void setprix(QString);
   void setquntite(QString);
   void settype(QString);

    produits();
    produits(int,QString,QString,QString);
    bool ajouterProd();
    QSqlQueryModel* afficherProd();

    bool supprimerProd(int);
    bool modidier();

};

#endif // PRODUITS_H
