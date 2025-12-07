//
// Created by elobo on 06/12/2025.
//

//
// Created by elobo on 06/12/2025.
//

#include "gameQt.h"
#include "../Chantier/river.h"
#include <iostream>
#include <vector>
#include "../Tuiles/deck.h"
#include "../Joueur/player.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QString>
#include <QDialog>
#include <QLineEdit>
#include <QtGui>
#include <QMessageBox>
#include <Qobject>
#include <QInputDialog>
#include <string>

//static attributs init
GameQt* GameQt::instanceQt = nullptr;

Tile& GameQt::pickRiverQt(QWidget* parent) {
    QString riverStr = QString::fromStdString(river->toString());
    QMessageBox::information(parent, "River", riverStr);

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


void GameQt::manageGameQt(QWidget* parent) {
    for (size_t i = 0; i < nb_players; ++i) {
        QString qname = QInputDialog::getText(parent, "Player Name",
                                              QString("Name of player %1:").arg(i + 1));
        addPlayer(qname.toStdString());
    }

        while (!(river->stay1() && pile->isEmpty())) {
        QString info = QString("Current player: %1\nStones: %2")
                            .arg(QString::fromStdString(players[current_player]->getName()))
                            .arg(players[current_player]->getStones());
        QMessageBox::information(parent, "Player Turn", info);

        char satisfied = 'N';
        do {
            Tile* tile = &pickRiverQt(parent);
            players[current_player]->playTurnQt(*tile);

            QMessageBox msgBox;
            msgBox.setText("Are you satisfied with your move?");
            QPushButton *yesButton = msgBox.addButton("Yes", QMessageBox::YesRole);
            QPushButton *noButton  = msgBox.addButton("No", QMessageBox::NoRole);
            msgBox.exec();

            satisfied = (msgBox.clickedButton() == yesButton) ? 'Y' : 'N';

        } while (satisfied == 'N');

        nextPlayer();
    }
}

void GameQt::manageSoloGameQt(int difficulty, QWidget* parent) {
    QString qname = QInputDialog::getText(parent, "Player Name", "What is your name?");
    addPlayer(qname.toStdString());

    Player* architect = new Architect("Architect", difficulty);
    players.push_back(architect);

    while (!(river->stay1() && pile->isEmpty())) {

        if (current_player != 0) {
            QMessageBox::information(parent, "Architect's Turn", "Architect is playing...");

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

            // Passer au joueur suivant
            nextPlayer();

        } else {
            QMessageBox::information(parent, "Your Turn",
                                     QString("Stones: %1").arg(players[0]->getStones()));

            char satisfied = 'N';
            do {
                Tile* tile = &pickRiverQt(parent);

                players[0]->playTurnQt(*tile, parent);

                QMessageBox msgBox;
                msgBox.setText("Are you satisfied with your move?");
                QPushButton *yesButton = msgBox.addButton("Yes", QMessageBox::YesRole);
                QPushButton *noButton  = msgBox.addButton("No", QMessageBox::NoRole);
                msgBox.exec();

                satisfied = (msgBox.clickedButton() == yesButton) ? 'Y' : 'N';

            } while (satisfied == 'N');

            nextPlayer();
        }
    }
}

