#ifndef FINANCE_H
#define FINANCE_H
#include <QSqlQueryModel>
#include <QString>
#include <QDate>
class Finance
{
public:
    Finance();
    Finance(int,QDate,QString,float,float,float);
    int getID_Facture_BRAHIM();
    QDate getDate_Facture_BRAHIM();
    QString getReference_BRAHIM();
    float getPrix_BRAHIM();
    float getStatistique_BRAHIM();
    float getBudget_BRAHIM();
    void setID_Facture_BRAHIM(int);
    void setDate_Facture_BRAHIM(QDate);
    void setReference_BRAHIM(QString);
    void setPrix_BRAHIM(float);
    void setStatistique_BRAHIM(float);
    void setBudget_BRAHIM(float);
    bool ajouter_BRAHIM();
    QSqlQueryModel* afficher_BRAHIM();
    QSqlQueryModel* historique_BRAHIM();
    bool supprimer_BRAHIM(int);
    bool modifier_BRAHIM(int,QDate,QString,float,float);
    bool modifierBudget_BRAHIM(float);
    QSqlQueryModel * rechercher_BRAHIM (const QString &aux1, const QString &aux);
    QSqlQueryModel * rechercher1_BRAHIM (const QString &aux);
    QSqlQueryModel * rechercher_par_date_BRAHIM (const QString &aux);
    QSqlQueryModel * Associer_BRAHIM();
    void pdf_BRAHIM();
private:
    int ID_Facture;
    QDate Date_Facture;
    float Prix,Statistique,Budget;
    QString Reference;


};

#endif // FINANCE_H
