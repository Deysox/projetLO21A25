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
    msgBox.exec();
    if (msgBox.clickedButton() == yesButton) {
        abandonGame();
        return false;
    }
    else{
        Tile* tile = nullptr;
        char satisfied = 'N';
        do {
            tile = &pickRiver();
            players[current_player]->playTurn(*tile);
            QMessageBox msgbox;
            msgBox.setText("Are you satisfied of your move?");
            QPushButton *yesButton = msgbox.addButton("Yes", QMessageBox::YesRole);
            QPushButton *noButton = msgbox.addButton("No", QMessageBox::NoRole);
            msgBox.exec();
            if (msgBox.clickedButton() == yesButton) {
                satisfied = 'Y';
            } else {
                players[current_player]->setBoard(*board_copy);
                QMessageBox optionBox;
                optionBox.setText("Pick another tile (A) or choose another place (B)?");
                QPushButton *A_btn = optionBox.addButton("A", QMessageBox::AcceptRole);
                QPushButton *B_btn = optionBox.addButton("B", QMessageBox::AcceptRole);
                optionBox.exec();

                if (optionBox.clickedButton() == A_btn) {
                    Amalena::River* temp_river = new Amalena::River(*river_copy);
                    *river = *temp_river;
                    Tile* new_tile = &pickRiver();
                    players[current_player]->playTurn(*new_tile);
                    delete temp_river;
                }
                else {
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
    if (nb_players == nb_players_max)
    {
        //Put an exception instead
        cout << "Can't add an additionnal player, you have reached the maximum.";
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

    Tile& chosen_tile = river->giveTile(position);
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
    if (!chosen_tile_ptr || (chosen_pos - 1) > players[current_player]->getStones()) {
        chosen_tile_ptr = &*river->begin();
        chosen_pos = 1;
    }
    players[current_player]->addStones(-static_cast<int>(chosen_pos - 1));
    players[current_player]->playTurn(*chosen_tile_ptr);
}

bool GameQt::realPlayerPlaySoloGame(BoardManager* board_copy,Amalena::River* river_copy){
    QMessageBox msgBox;
    msgBox.setText("Do you want to abandon the game ?");
    QPushButton *yesButton = msgBox.addButton("Yes", QMessageBox::YesRole);
    QPushButton *noButton  = msgBox.addButton("No", QMessageBox::NoRole);
    msgBox.exec();
    if (msgBox.clickedButton() == yesButton) {
        abandonGame();
        return false;
    }
    else {
        Tile* tile = nullptr;
        QMessageBox::information(parent, "Your Turn", QString("Stones: %1").arg(players[0]->getStones()));
        int stones_before = players.at(0)->getStones();
        int architect_stones_before = players.at(1)->getStones();
        char satisfied = 'N';
        do {
            tile = &pickRiver();
            int stones_after = players.at(0)->getStones();
            int stones_lost = stones_before - stones_after;
            players.at(1)->addStones(stones_lost);
            players[current_player]->playTurn(*tile);
            QMessageBox msgbox;
            msgBox.setText("Are you satisfied of your move?");
            QPushButton *yesButton = msgbox.addButton("Yes", QMessageBox::YesRole);
            QPushButton *noButton = msgbox.addButton("No", QMessageBox::NoRole);
            msgBox.exec();
            if (msgBox.clickedButton() == yesButton) {
                satisfied = 'Y';
            } else {
                players[current_player]->setBoard(*board_copy);
                QMessageBox optionBox;
                optionBox.setText("Pick another tile (A) or choose another place (B)?");
                QPushButton *A_btn = optionBox.addButton("A", QMessageBox::AcceptRole);
                QPushButton *B_btn = optionBox.addButton("B", QMessageBox::AcceptRole);
                optionBox.exec();
                if (optionBox.clickedButton() == A_btn) {
                    players.at(0)->setStones(stones_before);
                    players.at(1)->setStones(architect_stones_before);
                    Amalena::River* temp_river = new Amalena::River(*river_copy);
                    *river = *temp_river;
                    Tile* new_tile = &pickRiver();
                    int new_stones_after = players.at(0)->getStones();
                    int new_stones_lost = stones_before - new_stones_after;
                    players.at(1)->addStones(new_stones_lost);
                    players[current_player]->playTurn(*new_tile);
                    delete temp_river;
                }
                else {
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