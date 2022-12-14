#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "fournisseurs.h"
#include "finance.h"
#include "Client.h"
#include "livraisons.h"
#include "commandes.h"
#include <QMainWindow>
#include<QVBoxLayout>
#include<QScopedPointer>
#include<QPushButton>
#include "arduino.h"
#include "employe.h"
#include "smtp.h"
#include <string>
#include <cstring>
#include <cctype>
#include <QMessageBox>
#include <iostream>
#include <bitset>
#include <sstream>
#include <algorithm>
#include "produits.h"
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
//Oussama gammoudi
struct Position {
    int x;
    int y;
};


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int checkLogin(QString a, QString b, QString c);
    //farah
      void afficher();
      QSortFilterProxyModel *proxy_p;

private slots:
    //Med Karim Akkari
    void update_arduino1();

    void on_ajouterf_clicked();
    void on_supprimerf_clicked();
    void on_modifierf_clicked();
    void on_historiquef_clicked();
    void on_trierf_clicked();
    void on_generer_pdf_clicked();
    void on_A_recherche_textChanged();
    void on_S_recherche_textChanged();
    void on_imprimerf_clicked();
    void on_m_id_fournisseur_textChanged();
    void on_revenir_menu_clicked();
    void on_Hide_fournisseurs_se_connecter_clicked();
    void on_Hide_fournisseurs_verouiller_clicked();
    void on_Hide_fournisseurs_verouiller_2_clicked();
    void on_Hide_fournisseurs_verouiller_3_clicked();
    void on_Hide_fournisseurs_verouiller_4_clicked();
    void on_Hide_fournisseurs_verouiller_5_clicked();
    void on_Hide_fournisseurs_verouiller_6_clicked();


    void on_Hide_fournisseurs_se_connecter_2_clicked();

    void on_Hide_fournisseurs_se_connecter_3_clicked();
    void on_Hide_fournisseurs_se_connecter_4_clicked();
    void on_Hide_fournisseurs_se_connecter_5_clicked();
    void on_Hide_fournisseurs_se_connecter_6_clicked();

    //Oussama gammoudi
    void on_pushButton_AjouterEmploye_clicked();

    void on_pushButton_SupprimerEmploye_clicked();

    void on_pushButton_ModifierEmploye_clicked();

    void on_pushButton_Excel_clicked();

    void on_lineEdit_Recherche_textChanged(const QString &arg1);

    //Cryptage

    void on_pushButton_encrypt_clicked();
    void on_pushButton_decrypt_clicked();

    void on_actionReset_Fields_triggered();
    void on_actionClear_Plain_Text_triggered();
    void on_actionClear_Encrypted_Text_triggered();
    void on_actionExit_triggered();
    void on_actionAbout_Qt_triggered();

    void on_comboBox_currentTextChanged(const QString &arg1);

   //Mailing
    void on_send_mail_clicked();



    void on_tri_clicked();

    void on_tri2_clicked();

   // Med Brahim Abdelbeki
    void on_pb_ajouter_BRAHIM_clicked();

    void on_pb_supprimer_BRAHIM_clicked();

    void on_Modifier_BRAHIM_clicked();

    void on_Recherche_BRAHIM_textChanged();

    void on_pushButton_BRAHIM_clicked();



    void on_pdf_but_BRAHIM_clicked();

    void on_Trier_F_BRAHIM_clicked();

    void on_m_ID_Facture_BRAHIM_textChanged();

    void on_Imprimer_but_BRAHIM_clicked();

    //nour thraya


    void on_Ajouterclient_NOUR_clicked();

    void on_pushButton_2_NOUR_clicked();

    void on_choix_cin_NOUR_clicked();

    void on_tableView_2_NOUR_clicked(const QModelIndex &index);



    void on_comboBox_NOUR_activated(const QString );


    void on_pushButton_3_NOUR_clicked();

    void on_pushButton_4_NOUR_clicked();
    void update_label();
    void on_detect_clicked();


    void on_Recherche_NOUR_textChanged(const QString &arg1);

    //slim drira

    void on_ajouter_slim_clicked();

    void on_supprimer_slim_clicked();

    void on_A_quitter_slim_clicked();

    void on_A_quitter2_slim_clicked();

    void on_A_quitter3_slim_clicked();

    void on_A_quitter4_slim_clicked();

    void on_A_quitter5_slim_clicked();

    void on_ajouter_2_slim_clicked();

    void on_Af_rechercher_slim_textChanged();

    void on_A_idlivraison_2_slim_textChanged();

    void on_S_rechercher_slim_textChanged();

    void on_trier_2_slim_clicked();

    void on_modifier_slim_clicked();



    void on_m_idcommande_slim_textChanged();

    void on_A_quitter4_2_slim_clicked();

    void on_supprimer_2_slim_clicked();

    void on_Af_rechercher_2_slim_textChanged();


    void on_S_rechercher_2_slim_textChanged();

    void on_modifierL_slim_clicked();

    void on_A_quitter5_2_slim_clicked();

    void on_A_quitter3_2_slim_clicked();

    void on_m_idlivraison_slim_textChanged();

    void on_tableView_2_slim_clicked(const QModelIndex &index);

    void on_ajouter_3_slim_clicked();

    void update_label_slim();   // slot permettant la mise à jour du label état de la lampe 1,
    // ce slot est lancé à chaque réception d'un message de Arduino

    void on_detect_slim_clicked();   // bouton ON

   //Farah battikh

    void on_ajo_clicked();

    void on_sup_returnPressed();

    void on_tableView_3_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_mod_clicked();

    void on_pb_qrcode_clicked();

    void on_lineEdit_produit_textChanged(const QString &arg1);



    void on_comboBox_2_currentIndexChanged(int index);

    void on_pushButton_camera_clicked();

private:
    Ui::MainWindow *ui;
    fournisseurs F;
    QByteArray data; // variable contenant les données reçues

    Arduino A; // objet temporaire

     //Oussama gammoudi
    Employe E;

    //Cryptage
    QString ewCaesarCipher(QString plainText, int key);
        QString dwCaesarCipher(QString encryptedText, int key);

        QString ewPlayfair(QString plainText, QString secret);
        QString dwPlayfair(QString encryptedText, QString secret);

        char pfMatrix[5][5];
        bool inSameRow(Position p1, Position p2);
        bool inSameColumn(Position p1, Position p2);
        void normalizePFString(std::string &str);
        void normalizePFSecret(std::string &secret);
        void populatePFMatrix(std::string secret);
        std::string encryptPFString(std::string plainStdText);
        std::string decryptPFString(std::string encryptedStdText);
        Position findPositionByChar(char ch);
        char findCharByPosition(Position p);

        QString ewDES(QString plainText, std::string key);
        QString dwDES(QString encryptedText, std::string key);
        std::vector<std::string> keyPreparation(std::string key);
        QString DESEncryption(std::string dataBlock, std::vector< std::string > keys);
        std::string apply_xor(std::string str1, std::string str2);
        std::string apply_func_F(std::string str1, std::string str2);
        std::string apply_func_E(std::string str);

        QString ewIDES(QString plainText, std::string key);
        QString dwIDES(QString encryptedText, std::string key);
        std::vector< std::string > textToBinaryAscii(std::string str);
        std::string binaryAsciiToText(std::string str);
        std::string charToBinaryAscii(char ch);
        char binaryAsciiToChar(std::string binaryAscii);

        double ewRSA(double msg, double p, double q);
        double dwRSA(double msg, double p, double q);
        double RSAEncryption(double msg, double n, double e);
        double RSADecryption(double msg, double n, double d);
        std::pair<double, double> RSAKeys(double p, double q);
        int gcd(int a, int h);

        QString ewRC4(QString msg, QString key);
        QString dwRC4(QString msg, QString key);
        QString RC4Encryption(std::vector< std::bitset<8> > msg_bytes, std::vector< std::bitset<8> > keys);
        std::vector< std::bitset<8> > keysGenerator(int msg_length, std::vector<int> s);
        std::vector< std::bitset<8> > bytesOfMessage(std::string msg);
       //brahim
         Finance Fi;

        //nour
          Client c;

        //slim
          Commandes C;
          Livraisons L;

          //farah
          produits p;
          int selected_p=0;


};



#endif // MAINWINDOW_H
