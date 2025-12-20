//
// Created by elobo on 10/12/2025.
//
#include "gameQt.h"
#include "../Joueurs/playerQt.h"
#include "../Chantier/river.h"
#include"../Chantier/riverQT.h"
#include <iostream>
#include <vector>
#include "../Tuiles/deck.h"
#include "../Joueurs/player.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QString>
#include <QDialog>
#include <QLineEdit>
#include <QtGui>
#include <QMessageBox>
#include <QObject>
#include <QInputDialog>
#include <string>
namespace Eloise {
    //static attributs init
    GameQt* GameQt::instanceQt = nullptr;

    void GameQt::addEachPlayerToGame() {
        for (size_t i = 0; i < nb_players; i++) {
            QString qname = QInputDialog::getText(parent, "Player Name",
                                                  QString("Name of player %1:").arg(i + 1));
            addPlayer(qname.toStdString());
        }
    }
    void GameQt::displayCurrentPlayerInfo() {
        QString info = QString("Current player: %1\nStones: %2")
                               .arg(QString::fromStdString(players[current_player]->getName()))
                               .arg(players[current_player]->getStones());
        QMessageBox::information(parent, "Player Turn", info);
    }
    bool GameQt::actionsPlayer(Amalena::River* river_copy,BoardManager* board_copy) {
        //pour abandonner la partie
        QMessageBox msgBox;
        msgBox.setText("Do you want to abandon the game ?");
        QPushButton *yesButton = msgBox.addButton("Yes", QMessageBox::YesRole);
        QPushButton *noButton  = msgBox.addButton("No", QMessageBox::NoRole);
        msgBox.exec();
        //on appelle abandonGame() puis on renvoie false et on sort
        if (msgBox.clickedButton() == yesButton) {
            abandonGame();
            return false;
        }
        else{
            Tile* tile = nullptr;
            char satisfied = 'N';
            do {
                //pioche
                tile = &pickRiver();
                //placement de la tuile
                players[current_player]->playTurn(*tile);
                QMessageBox msgbox;
                msgbox.setText("Are you satisfied of your move?");
                QPushButton *yesButton = msgbox.addButton("Yes", QMessageBox::YesRole);
                QPushButton *noButton = msgbox.addButton("No", QMessageBox::NoRole);
                msgbox.exec();
                //si satisfait on peut sortir de la boucle
                if (msgbox.clickedButton() == yesButton) {
                    satisfied = 'Y';
                } else {
                    //rollback plateau
                    players[current_player]->setBoard(*board_copy);
                    QMessageBox optionBox;
                    //2 options de rollback
                    optionBox.setText("Pick another tile (A) or choose another place (B)?");
                    QPushButton *A_btn = optionBox.addButton("A", QMessageBox::AcceptRole);
                    QPushButton *B_btn = optionBox.addButton("B", QMessageBox::AcceptRole);
                    optionBox.exec();
                    //nouvelle pioche
                    if (optionBox.clickedButton() == A_btn) {
                        //copie de copie
                        Amalena::River* temp_river = new Amalena::River(*river_copy);
                        //rollback rivière
                        *river = *temp_river;
                        //nouvelle pioche
                        Tile* new_tile = &pickRiver();
                        //nouveau placement
                        players[current_player]->playTurn(*new_tile);
                        delete temp_river;
                    }
                    else {
                        //nouveau placement
                        players[current_player]->playTurn(*tile);
                    }
                    QMessageBox finalBox;
                    finalBox.setText("Are you satisfied now?");
                    QPushButton *yesFinal = finalBox.addButton("Yes", QMessageBox::YesRole);
                    QPushButton *noFinal = finalBox.addButton("No", QMessageBox::NoRole);
                    finalBox.exec();
                    if (finalBox.clickedButton() == yesFinal) {
                        satisfied = 'Y';
                    }
                }
            } while (satisfied == 'N');
            return true;
        }
    }

    void GameQt::addPlayer(const string& name) {
        if (nb_players > nb_players_max)
        {
            throw MaxPlayerException();
        }
        else {
            PlayerQt* p = new PlayerQt(name);
            players.push_back(p);
        }
    }

void GameQt::displayRiver() {

   /* riverWindow = new Amalena::riverQT(parent, *river);
    riverWindow->setWindowTitle("Rivière");
    riverWindow->resize(800, 200);
    riverWindow->setAttribute(Qt::WA_DeleteOnClose); // auto-supprime à la fermeture
    riverWindow->show();*/
   if (!riverWindow)
    {
        riverWindow = new Amalena::riverQT(parent, *river);
        riverWindow->setWindowTitle("Rivière");
        riverWindow->resize(800, 200);
        riverWindow->setAttribute(Qt::WA_DeleteOnClose); // auto-supprime à la fermeture
        riverWindow->show();
    }else
    {
    riverWindow->updateDisplay();
        riverWindow->show();
    }

}
 /*   void GameQt::displayRiver() {
    QString riverStr = QString::fromStdString(river->toString());
    QMessageBox::information(parent, "River", riverStr);
}  */
Tile& GameQt::chooseTileRiver() {
    int position = 1;

        do {
            position = QInputDialog::getInt(parent, "Pick a Tile",
                                            "Write the position of the tile you want (first tile at position 1):",
                                            1, 1, static_cast<int>(river->getSize()), 1);
            //vérification du nombre de pierres par rapport à la position
            if (players[current_player]->getStones() < static_cast<size_t>(position - 1)) {
                QMessageBox::warning(parent, "Not enough stones",
                                     "You don't have enough stones, select another position.");
            }
        } while (players[current_player]->getStones() < static_cast<size_t>(position - 1));
        //on récupère la tuile grâce à giveTile()
        Tile& chosen_tile = river->giveTile(position);
        //mise à jour des pierres
        size_t newStones = players[current_player]->getStones() - (position - 1);
        players[current_player]->setStones(newStones);
        return chosen_tile;
    }

    void GameQt::askNameSoloGame(){
        QString qname = QInputDialog::getText(parent, "Player Name", "What is your name?");
        addPlayer(qname.toStdString());
    }

    void GameQt::architectCreation(int difficulty) {
        PlayerQt* architect = new ArchitectQt("Architect", difficulty);
        players.push_back(architect);
    }
    void GameQt::architectPlaySoloGame(){
        QMessageBox::information(parent, "Architect's Turn", "Architect is playing");
        //pointeur sur la tuile choisie et sa position
        Tile* chosen_tile_ptr = nullptr;
        int chosen_pos = 1;
        int pos = 1;
        //boucle pour trouver la première tuile avec une cellule PLACE
        for (auto& t : *river) {
            for (const Cell* cell : t) {
                if (cell->getType() == Type::PLACE) {
                    chosen_tile_ptr = &t;
                    chosen_pos = pos;
                    break;
                }
            }
            if (chosen_tile_ptr) break;
            ++pos;
        }
        //si on a pas trouvé ou pas assez de pierres on prend la première tuile
        if (!chosen_tile_ptr || (chosen_pos - 1) > players[current_player]->getStones()) {
            chosen_tile_ptr = &*river->begin();
            chosen_pos = 1;
        }
        //mise à jour des pierres
        players[current_player]->addStones(-static_cast<int>(chosen_pos - 1));
        //ajout de la tuile au vecteur
        players[current_player]->playTurn(*chosen_tile_ptr);
    }

    bool GameQt::realPlayerPlaySoloGame(BoardManager* board_copy,Amalena::River* river_copy){
        QMessageBox msgBox;
        msgBox.setText("Do you want to abandon the game ?");
        QPushButton *yesButton = msgBox.addButton("Yes", QMessageBox::YesRole);
        QPushButton *noButton  = msgBox.addButton("No", QMessageBox::NoRole);
        msgBox.exec();
        //abandon de la partie ==> on appelle abandonGame() et on retourne false
        if (msgBox.clickedButton() == yesButton) {
            abandonGame();
            return false;
        }
        else {
            Tile* tile = nullptr;
            QMessageBox::information(parent, "Your Turn", QString("Stones: %1").arg(players[0]->getStones()));
            //enregsitrement des pierres pour pouvoir rollback
            int stones_before = players.at(0)->getStones();
            int architect_stones_before = players.at(1)->getStones();
            char satisfied = 'N';
            do {
                //pioche
                tile = &pickRiver();
                //affectation des pierres
                int stones_after = players.at(0)->getStones();
                int stones_lost = stones_before - stones_after;
                players.at(1)->addStones(stones_lost);
                //placement
                players[current_player]->playTurn(*tile);
                QMessageBox msgbox;
                msgbox.setText("Are you satisfied of your move?");
                QPushButton *yesButton = msgbox.addButton("Yes", QMessageBox::YesRole);
                QPushButton *noButton = msgbox.addButton("No", QMessageBox::NoRole);
                msgbox.exec();
                //si satisfait on sort de la boucle
                if (msgbox.clickedButton() == yesButton) {
                    satisfied = 'Y';
                } else {
                    //si pas satisfait rollback plateau
                    players[current_player]->setBoard(*board_copy);
                    QMessageBox optionBox;
                    //2 options de rollback
                    optionBox.setText("Pick another tile (A) or choose another place (B)?");
                    QPushButton *A_btn = optionBox.addButton("A", QMessageBox::AcceptRole);
                    QPushButton *B_btn = optionBox.addButton("B", QMessageBox::AcceptRole);
                    optionBox.exec();
                    //nouvelle pioche
                    if (optionBox.clickedButton() == A_btn) {
                        //rollabck des pierres
                        players.at(0)->setStones(stones_before);
                        players.at(1)->setStones(architect_stones_before);
                        //copie de copie
                        Amalena::River* temp_river = new Amalena::River(*river_copy);
                        //rollback rivière
                        *river = *temp_river;
                        //nouvelle pioche
                        Tile* new_tile = &pickRiver();
                        //nouvelle affectation de pierres
                        int new_stones_after = players.at(0)->getStones();
                        int new_stones_lost = stones_before - new_stones_after;
                        players.at(1)->addStones(new_stones_lost);
                        //nouveau placement
                        players[current_player]->playTurn(*new_tile);
                        delete temp_river;
                    }
                    else {
                        //nouveau placement
                        players[current_player]->playTurn(*tile);
                    }
                    QMessageBox finalBox;
                    finalBox.setText("Are you satisfied now?");
                    QPushButton *yesFinal = finalBox.addButton("Yes", QMessageBox::YesRole);
                    QPushButton *noFinal = finalBox.addButton("No", QMessageBox::NoRole);
                    finalBox.exec();
                    if (finalBox.clickedButton() == yesFinal) {
                        satisfied = 'Y';
                    }
                }
            } while (satisfied == 'N');
            return true;
        }
    }

    string GameQt::displayAbandonGame1() {
        QMessageBox::information(parent, "Abandon game 1", "Temporary abandon of the game.");
        QString id = QInputDialog::getText(
            parent,
            "Save game",
            "Choose a pseudo for your game:",
            QLineEdit::Normal,
            ""
        );
        return id.toStdString();
    }

    void GameQt::displayAbandonGame2(){
        QMessageBox::information(parent, "Abandon game 2", "Registration of game successful.");
    }
}