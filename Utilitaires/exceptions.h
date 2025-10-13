//
// Created by barnab on 13/10/2025.
//

#ifndef PROJETLO21A25_EXCEPTIONS_H
#define PROJETLO21A25_EXCEPTIONS_H
#include <string>
using namespace std;

namespace Barnabe {
    class PlateauException {
        string info;
    public:
        explicit PlateauException(const string& s) : info(s){}
        explicit PlateauException() : info("Erreur Plateau"){}
        const string& get_info() const {return info;}
    };
}


#endif //PROJETLO21A25_EXCEPTIONS_H