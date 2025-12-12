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
        //init to secure
        GameMemento* gameMemento = nullptr;

    public:
        //to save
        savemanager(GameMemento* g):gameMemento(g){};
        //to restore
        savemanager();
        ~savemanager()=default;
        savemanager(const savemanager& s)=delete;
        savemanager& operator=(const savemanager& s)=delete;
        void save() ;
        //void restore();
        GameMemento* restore();
        json tojson();
        void fromjson(json data);
    };
}


#endif //TESTSAUVEGARDE_SAVEMANAGER_H