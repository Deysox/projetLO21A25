//
// Created by GAUTIER--BONNEAU on 05/12/2025.
//

#ifndef TESTSAUVEGARDE_SAVEMANAGER_H
#define TESTSAUVEGARDE_SAVEMANAGER_H




#include <string>

#include "GameMemento.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Amalena
{
    class savemanager
    {
        GameMemento* gameMemento;

    public:
        savemanager(GameMemento* g):gameMemento(g){};
        ~savemanager()=default;
        savemanager(const savemanager& s)=delete;
        savemanager& operator=(const savemanager& s)=delete;
        void save() ;
        void restore();
        json tojson();
        void fromjson(json data);
    };
}


#endif //TESTSAUVEGARDE_SAVEMANAGER_H