#include "cell.h"

// namespace Marilou {
//     string Cell::displayTop(unsigned int height) const {
//         string output;
//         if (type != Type::PLACE) { output = "\033[0;3";} else { output = "\033[4";}
//         output += ansiColorCodes[color] + "m";
//         output += "/" + to_string(height) + akroTypeCodes[type] + "\\";
//
//         output += "\033[0m";
//         return output;
//     }
//
//     string Cell::displayBottom() const {
//         string output;
//         if (type != Type::PLACE) { output = "\033[0;3";} else { output = "\033[4";}
//         output += ansiColorCodes[color] + "m";
//         output += "\\" + akroColorCodes[color] + + "_/";
//
//         output += "\033[0m";
//         return output;
//     }
//
// }


namespace Barnabe {
    string Cell::displayTop(unsigned int height) const {
        string output;
        // Mode d'affichage, entre normal et inversé selon le type de quartier
        output = type == Type::PLACE ? "\033[7;3" : "\033[0;3";
        output += ansiColorCodes[color] + "m";
        output += "/" + to_string(height) + akroTypeCodes[type] + "\\";

        output += "\033[0m";
        return output;
    }

    string Cell::displayBottom() const {
        string output;
        // Mode d'affichage, entre normal et inversé selon le type de quartier
        output = type == Type::PLACE ? "\033[7;3" : "\033[0;3";
        output += ansiColorCodes[color] + "m";
        output += "\\" + akroColorCodes[color] + + "_/";

        output += "\033[0m";
        return output;
    }

}