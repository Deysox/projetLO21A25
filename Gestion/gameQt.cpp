//
// Created by elobo on 10/12/2025.
//
#include "gameQt.h"
#include "../Joueurs/playerQt.h"
#include "../Chantier/river.h"
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
        QMessageBox msgBox;
        msgBox.setText("Do you want to abandon the game ?");
        QPushButton *yesButton = msgBox.addButton("Yes", QMessageBox::YesRole);
        QPushButton *noButton  = msgBox.addButton("No", QMessageBox::NoRole);
        //if player clicked on yes he quits the game
        msgBox.exec();
        if (msgBox.clickedButton() == yesButton) {
            abandonGame();
            return false;
        }
        else{
            //char on which depends the loop
            char satisfied = 'N';
            do {
                //pickRiver() and playTurn() = main actions of turn
                Tile* tile = &pickRiver();
                players[current_player]->playTurn(*tile);
                QMessageBox msgBox;
                msgBox.setText("Are you satisfied with your move?");
                QPushButton *yesButton = msgBox.addButton("Yes", QMessageBox::YesRole);
                QPushButton *noButton  = msgBox.addButton("No", QMessageBox::NoRole);
                msgBox.exec();
                //if satisfied no need to continue
                if (msgBox.clickedButton() == yesButton) {
                    satisfied = 'Y';
                } else {
                    //if not satisfied player finds his old board
                    players[current_player]->setBoard(*board_copy);
                    QMessageBox optionBox;
                    optionBox.setText("Pick another tile (A) or choose another place (B)?");
                    QPushButton *A_btn = optionBox.addButton("A - Another tile", QMessageBox::AcceptRole);
                    QPushButton *B_btn = optionBox.addButton("B - Another place", QMessageBox::AcceptRole);
                    optionBox.exec();
                    //if player wants another tile the river comes back
                    if (optionBox.clickedButton() == A_btn) {
                        //copy of copy so that we always remember the original state of the river
                        Amalena::River* temp_river = new Amalena::River(*river_copy);
                        *river = *temp_river;
                        tile = &pickRiver();
                        delete temp_river;
                    }
                    //A or B : he places a tile again
                    players[current_player]->playTurn(*tile);
                    msgBox.setText("Are you satisfied now?");
                    msgBox.exec();
                }
            } while (satisfied == 'N');
            return true;
        }
    }

    void GameQt::addPlayer(const string& name) {
        if (nb_players == nb_players_max)
        {
            throw MaxPlayerException();
        }
        else {
            PlayerQt* p = new PlayerQt(name);
            players.push_back(p);
        }
    }

    void GameQt::displayRiver() {
        QString riverStr = QString::fromStdString(river->toString());
        QMessageBox::information(parent, "River", riverStr);
    }
    Tile& GameQt::chooseTileRiver() {
        int position = 1;

        do {
            position = QInputDialog::getInt(parent, "Pick a Tile",
                                            "Write the position of the tile you want (first tile at position 1):",
                                            1, 1, static_cast<int>(river->getSize()), 1);

            if (players[current_player]->getStones() < static_cast<size_t>(position - 1)) {
                QMessageBox::warning(parent, "Not enough stones",
                                     "You don't have enough stones, select another position.");
            }
        } while (players[current_player]->getStones() < static_cast<size_t>(position - 1));
        //river gives the chosen tile and updates
        Tile& chosen_tile = river->giveTile(position);
        //the number of stones left depends on the chosen tile (its position)
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
        Tile* chosen_tile_ptr = nullptr;
        int chosen_pos = 1;
        int pos = 1;
        //loop to browse the river and search for the first tile w/ a cell PLACE
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
        //if not enough stones or no PLACE then architect takes the first tile
        if (!chosen_tile_ptr || (chosen_pos - 1) > players[current_player]->getStones()) {
            chosen_tile_ptr = &*river->begin();
            chosen_pos = 1;
        }
        //update if stines
        players[current_player]->addStones(-(chosen_pos - 1));
        //tile placement thanks to playTurn()
        players[current_player]->playTurn(*chosen_tile_ptr);
    }

    bool GameQt::realPlayerPlaySoloGame(BoardManager* board_copy,Amalena::River* river_copy){
        QMessageBox msgBox;
        msgBox.setText("Do you want to abandon the game ?");
        QPushButton *yesButton = msgBox.addButton("Yes", QMessageBox::YesRole);
        QPushButton *noButton  = msgBox.addButton("No", QMessageBox::NoRole);
        msgBox.exec();
        //quit the game if yes clicked
        if (msgBox.clickedButton() == yesButton) {
            abandonGame();
            return false;
        }
        else {
            QMessageBox::information(parent, "Your Turn", QString("Stones: %1").arg(players[0]->getStones()));
            char satisfied = 'N';
            do {
                //saving of the amounts of stones before picking
                int stones_before = players.at(0)->getStones();
                int architect_stones_before = players.at(1)->getStones();
                //picks a tile in river
                Tile* tile = &pickRiver();
                int stones_after = players.at(0)->getStones();
                int stones_lost = stones_before - stones_after;
                //we give to the architect the stones that solo player lost
                players.at(1)->addStones(stones_lost);
                players[current_player]->playTurn(*tile);
                QMessageBox msgBox;
                msgBox.setText("Are you satisfied with your move?");
                QPushButton *yesButton = msgBox.addButton("Yes", QMessageBox::YesRole);
                QPushButton *noButton  = msgBox.addButton("No", QMessageBox::NoRole);
                msgBox.exec();
                //if satisfied no need to continue
                if (msgBox.clickedButton() == yesButton) {
                    satisfied = 'Y';
                } else {
                    //cancel of actions so old board and old amount of stones
                    players.at(0)->setBoard(*board_copy);
                    players.at(0)->setStones(stones_before);
                    players.at(1)->setStones(architect_stones_before);
                    QMessageBox optionBox;
                    //2 options of cancelling
                    optionBox.setText("Pick another tile (A) or choose another place (B)?");
                    QPushButton *A_btn = optionBox.addButton("A - Another tile", QMessageBox::AcceptRole);
                    QPushButton *B_btn = optionBox.addButton("B - Another place", QMessageBox::AcceptRole);
                    optionBox.exec();
                    //if A needs to pick again so river comes back as it was
                    if (optionBox.clickedButton() == A_btn) {
                        //copy of copy to always remember the original state of river
                        Amalena::River* temp_river = new Amalena::River(*river_copy);
                        *river = *temp_river;
                        //new picking
                        tile = &pickRiver();
                        delete temp_river;
                        //new update of stones for player and architect
                        int stones_after_new = players.at(0)->getStones();
                        players.at(1)->addStones(stones_before - stones_after_new);
                    }
                    //if both cases call of playTurn() to place tile again
                    players[current_player]->playTurn(*tile);
                }
            } while (satisfied == 'N');
            return true;
        }
    }

    string GameQt::displayAbandonGame1() {
        QMessageBox::information(parent, "Abandon game 1", "Temporary abandon of the game.");
        //input to choose pseudo of game
        QString id = QInputDialog::getText(
            parent,
            "Save game",
            "Choose a pseudo for your game:",
            QLineEdit::Normal,
            ""
        );
        //conversion of pseudo in string
        return id.toStdString();
    }

    void GameQt::displayAbandonGame2(){
        QMessageBox::information(parent, "Abandon game 2", "Registration of game successful.");
    }
}