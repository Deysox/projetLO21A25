//
// Created by barnab on 13/10/2025.
//

#ifndef PROJETLO21A25_EXCEPTIONS_H
#define PROJETLO21A25_EXCEPTIONS_H
#include <string>
#include <exception>

using std::exception;

/**
 * Exception signalant un coup invalide lors du placement d'une tuile dans un plateau.
 */
class PlacementException : public exception {
    string message_;
public:
    explicit PlacementException(const string& message) : message_(message) {}
    PlacementException() : message_("Erreur lors du placement de la tuile sur le plateau") {}

    [[nodiscard]] const char* what() const noexcept override
    {

        return message_.c_str();

    }
};

/**
 * Exception signalant un accès incorrect à une case d'une tuile.
 */
class TileException : public exception {
    string message_;
public:
    explicit TileException(const string& message) : message_(message) {}
    TileException() : message_("Erreur lors du placement de la tuile sur le plateau") {}

    [[nodiscard]] const char* what() const noexcept override
    {

        return message_.c_str();

    }
};



#endif //PROJETLO21A25_EXCEPTIONS_H