#ifndef PROJETLO21A25_MENU_H
#define PROJETLO21A25_MENU_H
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QString>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include "../UI/init.h"
namespace Eloise {
    class MenuQt : public QWidget {
        Q_OBJECT
    public:
        /*
         *constructor of MenuQt
         *handles to creation of the button, the layouts and the connections
         *@param QWidget*
         */
        explicit MenuQt(QWidget* parent = 0);
        signals:
        private slots:
        void boutonLancerGameClique();
        void boutonReprendreGameClique();
        void boutonAfficherReglesClique();
        //void OnGameParameterReady(int nbPlayers, QString variante, QStringList names );
        //void OnSoloGameParameterReady(QString name, QString Variante, int level);
    private:
        QPushButton* boutonLancerGame;
        QPushButton* boutonReprendreGame;
        QPushButton* boutonAfficherRegles;
        init* initWidget;
    };
}
#endif //PROJETLO21A25_MENU_H

