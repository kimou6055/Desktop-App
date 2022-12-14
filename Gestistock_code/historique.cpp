#include "historique.h"
#include<QMessageBox>

Historique::Historique()
{
tmp="";
}
void Historique::save(QString id,QString nom,QString tel)
{    QFile file ("C:/Users/LEOPARD/Desktop/work/esprit_2eme_annee/ProjetCpp/qt/Fournisseurs/intégration/test/his.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out << id+"\n"+nom << "\n" +tel << "\n";


}





