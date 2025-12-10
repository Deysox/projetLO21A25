//
// Created by elobo on 02/12/2025.
//
#include "game.h"
#include "../Chantier/river.h"
#include <iostream>
#include <vector>
#include "../Tuiles/deck.h"
#include "../Joueur/player.h"


//static attributs
size_t Game::nb_players_max = 4;

Game::Game(size_t nb_players) :
nb_players(nb_players),
deck(new Eloise::Deck(nb_players)),
pile(new Amalena::Pile(*deck)),
river(new Amalena::River(nb_players+2,*pile))
{
}

//free of players, river, pile, deck
//think of saving of information in order to resume games
Game::~Game(){
    for (auto& p: players) {
        delete p;
    }
    delete river;
    delete pile;
    delete deck;
}

void Game::displayPlayers() {
    for (auto player : players) {
        cout << player->getName() << "\n";
    }
}

Player* Game::getPlayer(size_t position) {
    if (position < nb_players) {
        return players.at(position);
    }
    else {
        //Put an exception instead
        cout << "Invalid position.";
        return nullptr;
    }
}

void Game::nextPlayer() {
    current_player++;
    current_player %= nb_players;
}

void Game::endGame() {
    //displaying of each player's score thanks to method of Player
}