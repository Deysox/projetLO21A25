cmake_minimum_required(VERSION 4.0)
project(projetLO21A25)

set(CMAKE_CXX_STANDARD 14)

include_directories(Chantier)
include_directories(Console)
include_directories(Gestion)
include_directories(Joueurs)
include_directories(Plateau)
include_directories(Tuiles)
include_directories(Utilitaires)

add_executable(projetLO21A25
        Console/console.cpp
        Console/console.h
        Joueurs/player.cpp
        Joueurs/player.h
        Joueurs/score.cpp
        Joueurs/score.h
        Plateau/boardmanager.h
        Plateau/board.cpp
        Plateau/board.h
        Tuiles/cell.cpp
        Tuiles/cell.h
        Tuiles/deck.cpp
        Tuiles/deck.h
        Tuiles/tile.cpp
        Tuiles/tile.h
        Utilitaires/exceptions.h
        Utilitaires/position.h
        Utilitaires/rotation.h
        main.cpp
        Utilitaires/position.cpp
        Plateau/boardmanager.cpp)
