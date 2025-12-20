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
    /**
     * Classe Menu pour Qt
     */
    class MenuQt : public QWidget {
        Q_OBJECT
    public:
        /**
         * Constructeur
         * @param parent pointeur sur QWidget
         */
        explicit MenuQt(QWidget* parent = 0);
        private slots:
        /**
         * Slot pour lancer une partie
         */
        void boutonLancerGameClique();
        /**
         * Slot pour reprendre une partie
         */
        void boutonReprendreGameClique();
        /**
         * Slot pour afficher les règles
         */
        void boutonAfficherReglesClique();

    private:
        /**
         * Bouton pour lancer une partie
         */
        QPushButton* boutonLancerGame;
        /**
         * Bouton pour reprendre une partie
         */
        QPushButton* boutonReprendreGame;
        /**
         * Bouton pour afficher les règles
         */
        QPushButton* boutonAfficherRegles;

    };
}
#endif //PROJETLO21A25_MENU_H

