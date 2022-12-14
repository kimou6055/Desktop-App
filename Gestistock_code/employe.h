#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlQueryModel>
#include <QApplication>
#include <QMessageBox>
#include <QTableView>
#include <qmessagebox.h>
#include <QIntValidator>
#include <QSqlQuery>
#include <QScrollBar>
#include <qfiledialog.h>
#include <QTextDocument>
#include <QTextStream>
#include <QComboBox>


class Employe
{
public:
    Employe(); //Constructeur par défaut

    Employe(int, QString, QString, QString, QString, float); //Constructeur parametré
    int getCIN();
    QString getNom();
    QString getPrenom();
    QString getEmail();
    QString getPoste();
    float getSalaire();

    void setCIN(int);
    void setNom(QString);
    void setPrenom(QString);
    void setEmail(QString);
    void setPoste(QString);
    void setSalaire(float);


    bool ajouter();
    QSqlQueryModel* afficher();        //Ensemble des informations et le resultat = resultat d'une requete (Query) de type Sql (retourner un tab)
    bool supprimer(int);
    bool modifier(int);
    QSqlQueryModel* Find_Employe();
    QSqlQueryModel* recherche_employe(QString search);
    QSqlQueryModel * tri();
    QSqlQueryModel * tri2();

private:
    int cin;
    QString nom, prenom, Email,poste;
    float Salaire;
};

#endif // EMPLOYE_H
