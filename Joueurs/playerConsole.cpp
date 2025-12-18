//
// Created by elobo on 10/12/2025.
//
#include "playerConsole.h"

using namespace std;

namespace Eloise {

    void PlayerConsole::displayBoard() {
        cout << "\n" << board << endl;
    }

    void PlayerConsole::placeTile(const Tile& tile) {
        bool placed = false;
        while (!placed) {
            int x = 0, y = 0, r = 0;
            cout << "Choose a position (x,y) on your board where you want to put the tile." << endl;
            cout << "x : "; cin >> x;
            cout << "y : "; cin >> y;
            cout << "Choose the rotation of the tile (0 to 5), r : "; cin >> r;
            Position pos(x,y);
            Rotation rotation(r);
            try {
                //place() returns an int which corresponds to the stones earned
                addStones(board.place(&tile, pos, rotation));
                placed = true;
            }
            catch(const PlacementException& pe) {
                cout << "Error : " << pe.what() << "\n";
            }
            catch(const TileException& te) {
                cout << "Error : " << te.what() << "\n";
            }
        }
    }
}