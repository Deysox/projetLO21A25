//
// Created by barnab on 13/10/2025.
//

#ifndef PROJETLO21A25_EXCEPTIONS_H
#define PROJETLO21A25_EXCEPTIONS_H
#include <string>
#include <exception>
using namespace std;

namespace Barnabe {
    class PlacementException : public exception {
        string message_;
    public:
        explicit PlacementException(const string& message) : message_(message) {}
        PlacementException() : message_("Erreur lors du placement de la tuile sur le plateau") {}

        const char* what() const throw()
        {

            return message_.c_str();

        }
    };

    class TileException : public exception {
        string message_;
    public:
        explicit TileException(const string& message) : message_(message) {}
        TileException() : message_("Erreur lors du placement de la tuile sur le plateau") {}

        const char* what() const throw()
        {

            return message_.c_str();

        }
    };
}


#endif //PROJETLO21A25_EXCEPTIONS_H