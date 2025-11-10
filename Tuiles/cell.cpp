#include "cell.h"

namespace Marilou {
    ostream &Cell::displayTop(ostream &f, unsigned int height) const {
        string output;
        if (type != Type::PLACE) { output = "\033[0;3";} else { output = "\033[4";}
        output += ansiColorCodes[color] + "m";
        output += "/" + to_string(height) + akroTypeCodes[type] + "\\";

        output += "\033[0m";
        f << output;
        return f;
    }

}