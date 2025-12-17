#include "cell.h"
#include <sstream>

namespace Barnabe {
    string Cell::displayTop(unsigned int height) const {
        stringstream ss;
        // Mode d'affichage, entre normal et inversé selon le type de quartier
        string ansi_start = type == Type::PLACE ? "\033[7;3" : "\033[0;3"; // Début de la séquence ANSI pour la coloration
        // dans le terminal
        ss << ansi_start;
        ss << ansiColorCodes[color] << "m"; // Ajout de la couleur
        ss << "/" << to_string(height) << akroTypeCodes[type] << "\\"; // Ajout des caractères de la tuile

        ss << "\033[0m"; // Fermeture de la séquence ANSI
        return ss.str();
    }

    string Cell::displayBottom() const {
        stringstream ss;
        // Mode d'affichage, entre normal et inversé selon le type de quartier
        string ansi_start = type == Type::PLACE ? "\033[7;3" : "\033[0;3"; // Début de la séquence ANSI pour la coloration
        ss << ansi_start;
        ss << ansiColorCodes[color] + "m"; // Ajout de la couleur
        ss << "\\" << akroColorCodes[color] << "_/"; // Ajout des caractères de la tuile

        ss << "\033[0m"; // Fermeture de la séquence ANSI
        return ss.str();
    }

}