#include "finance.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QPainter>
#include <QPdfWriter>
#include <QMessageBox>
#include <QSystemTrayIcon>

Finance::Finance()
{
ID_Facture=0;
Prix=0;
Statistique=0;
}
Finance::Finance(int ID_Facture,QDate Date_Facture,QString Reference,float Prix,float Statistique,float Budget)
{
    this->ID_Facture=ID_Facture;
    this->Date_Facture=Date_Facture;
    this->Reference=Reference;
    this->Prix=Prix;
    this->Statistique=Statistique;
    this->Budget=Budget;
}
int Finance::getID_Facture_BRAHIM(){return ID_Facture;}
QDate Finance::getDate_Facture_BRAHIM(){return Date_Facture;}
QString Finance::getReference_BRAHIM(){return Reference;}
float Finance::getPrix_BRAHIM(){return Prix;}
float Finance::getStatistique_BRAHIM(){return Statistique;}
float Finance::getBudget_BRAHIM(){return Budget;}
void Finance::setID_Facture_BRAHIM(int ID_Facture){this->ID_Facture=ID_Facture;}
void Finance::setDate_Facture_BRAHIM(QDate Date_Facture){this->Date_Facture=Date_Facture;}
void Finance::setReference_BRAHIM(QString Reference){this->Reference=Reference;}
void Finance::setPrix_BRAHIM(float Prix){this->Prix=Prix;}
void Finance::setStatistique_BRAHIM(float Statistique){this->Statistique=Statistique;}
void Finance::setBudget_BRAHIM(float Budget){this->Budget=Budget;}
bool Finance::ajouter_BRAHIM()
{
    QString ID_string= QString::number(ID_Facture);
    QString Prix_String= QString::number(Prix);
    Finance f;
    f.Associer_BRAHIM();
    float bdg=f.getBudget_BRAHIM();
    float calcul=(getPrix_BRAHIM()*100)/bdg;
    bdg-=getPrix_BRAHIM();
     QSqlQuery quer;

     QString Budget_String= QString::number(bdg);
     quer.prepare("UPDATE CAPITALE SET Budget=:bdg");
     quer.bindValue(":bdg", Budget_String);
      quer.exec();


    QString Statistique_String= QString::number(calcul);
    QSqlQuery query;



          query.prepare("INSERT INTO FINANCES (ID_FACTURE, DATE_FACTURE, REFERENCE, PRIX, STATISTIQUE)"
                        "VALUES (:id, :date, :reff, :prx, :stat)"
                        );
          query.bindValue(":id", ID_string);
          query.bindValue(":date", Date_Facture);
          query.bindValue(":reff", Reference);
          query.bindValue(":prx", Prix_String);
          query.bindValue(":stat", Statistique_String);
          query.exec();

         query.prepare( "INSERT INTO HISTORIQUES (HID, HDATE, HREF, HPRIX, HSTAT)"
          "VALUES (:id, :date, :reff, :prx, :stat)"
                        );

          query.bindValue(":id", ID_string);
          query.bindValue(":date", Date_Facture);
          query.bindValue(":reff", Reference);
          query.bindValue(":prx", Prix_String);
          query.bindValue(":stat", Statistique_String);
          return query.exec();
}
bool Finance::supprimer_BRAHIM(int ID_Facture)
{
    QSqlQuery query;
          query.prepare("Delete from FINANCES where ID_Facture=:ID_Facture");
          query.bindValue(":ID_Facture", ID_Facture);
          return query.exec();
}
QSqlQueryModel* Finance::afficher_BRAHIM()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT* FROM FINANCES");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Reference"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prix"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("Statistique"));
    return model;
}
QSqlQueryModel* Finance::historique_BRAHIM()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT* FROM HISTORIQUES");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Reference"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prix"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("Statistique"));

    return model;
}
bool Finance::modifier_BRAHIM(int ID_Facture, QDate Date_Facture,QString Reference, float Prix, float Statistique )
{
    QSqlQuery query;
    QString ID_string= QString::number(ID_Facture);
    QString Prix_String= QString::number(Prix);
    QString Statistique_String= QString::number(Statistique);
    query.prepare("UPDATE FINANCES SET Reference=:reff, Prix=:prx, Statistique=:stat where ID_Facture=:id");
    query.bindValue(":id", ID_string);
    query.bindValue(":date", Date_Facture);
    query.bindValue(":reff", Reference);
    query.bindValue(":prx", Prix_String);
    query.bindValue(":stat", Statistique_String);
    return query.exec();
}
QSqlQueryModel* Finance::rechercher1_BRAHIM (const QString &aux)

{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("select * from FINANCES where (( ID_Facture || extract (year from date_facture) || extract (month from date_facture)|| extract (day from date_facture)|| REFERENCE || PRIX || STATISTIQUE) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Reference"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Statistique"));


    return model;
}
QSqlQueryModel* Finance::rechercher_par_date_BRAHIM (const QString &aux)

{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("select * from FINANCES WHERE ((extract (year from date_facture) || extract (month from date_facture) || extract (day from date_facture))LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Reference"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Statistique"));


    return model;
}
QSqlQueryModel* Finance::rechercher_BRAHIM (const QString &aux1,const QString &aux)

{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("select * from FINANCES where ("+aux1+" LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Reference"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Statistique"));


    return model;
}


QSqlQueryModel * Finance::Associer_BRAHIM()
{
       QSqlQueryModel* model = new QSqlQueryModel();
       model->setQuery("select BUDGET from CAPITALE");
       setBudget_BRAHIM(model->data(model->index(0,0)).toFloat());
       return model;
}
bool Finance::modifierBudget_BRAHIM(float Budget)
{
    QSqlQuery query;
    QString Budget_String= QString::number(Budget);
    query.prepare("UPDATE CAPITALE SET Budget=:bdg");
    query.bindValue(":bdg", Budget_String);
    return query.exec();
}
void  Finance::pdf_BRAHIM(){

                         QPdfWriter pdf("C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/qt/Fournisseurs/integration/test/facture.pdf");
                         QPainter painter(&pdf);

                        int i = 4000;
                             painter.setPen(Qt::red);
                             painter.setFont(QFont("Arial", 30));
                             painter.drawText(500,1500,"Liste Des Factures");
                             painter.setPen(Qt::black);
                             painter.setFont(QFont("Arial", 15));
                            // painter.drawText(1100,2000,afficheDC);
                             painter.drawRect(100,100,7300,2600);

                             painter.drawRect(0,3000,9600,500);
                             painter.setFont(QFont("Arial", 9));
                             painter.drawText(200,3300,"id");
                             painter.drawText(1300,3300,"date");
                             painter.drawText(3400,3300,"reference");
                             painter.drawText(4400,3300,"prix");
                             painter.drawText(5000,3300,"statistique");

                             QSqlQuery query;
                             query.prepare("select * from FINANCES");
                             query.exec();
                             while (query.next())
                             {
                                 painter.drawText(200,i,query.value(0).toString());
                                 painter.drawText(1300,i,query.value(1).toString());
                                 painter.drawText(3400,i,query.value(2).toString());
                                 painter.drawText(4400,i,query.value(3).toString());
                                 painter.drawText(5000,i,query.value(4).toString());

                                i = i + 500;
                             }


          int reponse = QMessageBox::Yes;
              if (reponse == QMessageBox::Yes)
              {
                  QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                  notifyIcon->show();
                 notifyIcon->setIcon(QIcon("C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/charte graphique/icon.gif"));

                  notifyIcon->showMessage("Finance ","Liste factures pret dans PDF",QSystemTrayIcon::Information,15000);

                  painter.end();
              }
              if (reponse == QMessageBox::No)
              {
                   painter.end();
              }
}
