#ifndef MENU_H
#define MENU_H
#include<QVBoxLayout>
#include<QScopedPointer>
#include<QPushButton>

#include <QDialog>



#include<QMessageBox>
//#include<QIntValidator>
//#include<QSqlQueryModel>
//#include<QSqlQuery>
//#include<QtDebug>
//#include<QObject>
//#include<QDate>
//#include<QTableWidget>
//#include<QPixmap>
//#include<QTextDocument>
#include<QDesktopServices>
#include<QPainter>
#include <QPrinter>
#include "fournisseurs.h"
#include "historique.h"
#include<QSystemTrayIcon>
//#include "QFile"
//#include "QTextStream"
#include"menu2.h"
#include<QString>

#include "mainwindow.h"
#include<QVBoxLayout>

#include<QFileDialog>
#include <QSqlQuery>

#include<QDateTime>
#include<QTimer>

#include<QPrintDialog>

#include<QVBoxLayout>


#include<QDateTime>
#include<QTimer>

namespace Ui {
class menu;
}

class menu : public QDialog
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();
int checkLogin(QString a, QString b);
private slots:
void on_welcome_se_connecter_clicked();
void on_Prob_connexion_clicked();

private:
    Ui::menu *ui;
    MainWindow* w;
    QByteArray data;
     Arduino A; // objet temporaire
};

#endif // MENU_H
