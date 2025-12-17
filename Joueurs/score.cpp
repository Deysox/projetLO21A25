#include "score.h"
#include <stack>
#include <map>

using namespace Barnabe;


static bool isDistrictOfColor(const Cell* c, Color col) {
    return c != nullptr && c->getType() == Type::DISTRICT && c->getColor() == col;
}

static int starsForColor(Color c) {
    switch (c) {
        case Color::BLUE:   return 1;
        case Color::GREEN:  return 3;
        case Color::YELLOW:
        case Color::RED:
        case Color::PURPLE: return 2;
        default:            return 0;
    }
}

static const Board& getBoardFromPlayer(const Player& player) {
    return *(player.getBoard().getBoard());
}
/*
static int countStarsForColor(const Board& board, Color color) {
    int stars = 0;

    for (auto it = board.begin(); it != board.end(); ++it) {
        auto pair = *it;
        const Cell* cell = pair.second;
        if (!cell) continue;

        if (cell->getType() == Type::PLACE &&
            cell->getColor() == color) {
            stars += starsForColor(color);
        }
    }

    return stars;
}

// ===== ScorePierre =====

int Marilou::ScorePierre::compute(const Player& player,const ScoreVariants& ) const {
    return player.getStones();
}

// ===== ScoreBleu : Habitations =====

int Marilou::ScoreBleu::compute(const Player& player,const ScoreVariants& variants) const
{
    const Board& board = getBoardFromPlayer(player);

    int stars = countStarsForColor(board, Barnabe::Color::BLUE);
    if (stars == 0) return 0;

    std::map<Position, bool> visited;
    int bestValue = 0;

    for (auto it = board.begin(); it != board.end(); ++it) {
        auto pair = *it;
        Position pos = pair.first;
        const Cell* cell = pair.second;
        if (!isDistrictOfColor(cell, Color::BLUE)) continue;

        if (visited[pos]) continue;

        std::stack<Position> st;
        st.push(pos);
        visited[pos] = true;
        int componentValue = 0;

        while (!st.empty()) {
            Position p = st.top();
            st.pop();

            unsigned int h = board.getHeight(p);
            componentValue += static_cast<int>(h);

            std::vector<Position> neighbors = {
                Position(p.x + 1, p.y),
                Position(p.x - 1, p.y),
                Position(p.x,     p.y + 1),
                Position(p.x,     p.y - 1),
                Position(p.x + 1, p.y - 1),
                Position(p.x - 1, p.y + 1)
            };

            for (const auto& n : neighbors) {
                if (visited[n]) continue;
                const Cell* nc = board.getCell(n);
                if (!isDistrictOfColor(nc, Color::BLUE)) continue;
                visited[n] = true;
                st.push(n);
            }
        }

        if (componentValue > bestValue)
            bestValue = componentValue;
    }

    int score = bestValue * stars;

    // Variante : valeur du plus grand groupe >= 10 -> double
    if (variants.habitations && bestValue >= 10 && score > 0)
        score *= 2;

    return score;
}

// ===== ScoreJaune : Marchés =====

int Marilou::ScoreJaune::compute(const Barnabe::Player& player,
                        const ScoreVariants& variants) const {
    const Board& board = getBoardFromPlayer(player);

    int stars = countStarsForColor(board, Color::YELLOW);
    if (stars == 0) return 0;

    int value = 0;

    for (auto it = board.begin(); it != board.end(); ++it) {
        auto pair = *it;
        Position pos = pair.first;
        const Cell* cell = pair.second;
        if (!isDistrictOfColor(cell, Color::YELLOW)) continue;

        bool hasAdjacentMarket = false;
        std::vector<Position> neighbors = {
            Position(pos.x + 1, pos.y),
            Position(pos.x - 1, pos.y),
            Position(pos.x,     pos.y + 1),
            Position(pos.x,     pos.y - 1),
            Position(pos.x + 1, pos.y - 1),
            Position(pos.x - 1, pos.y + 1)
        };
        for (const auto& n : neighbors) {
            const Cell* nc = board.getCell(n);
            if (isDistrictOfColor(nc, Color::YELLOW)) {
                hasAdjacentMarket = true;
                break;
            }
        }
        if (hasAdjacentMarket) continue;

        value += static_cast<int>(board.getHeight(pos));
    }

    int score = value * stars;

    // Variante : s'il existe un marché adjacent à une place jaune, double
    if (variants.marches && score > 0) {
        bool hasMarketAdjacentToPlace = false;

        for (auto it = board.begin(); it != board.end() && !hasMarketAdjacentToPlace; ++it) {
            auto pair = *it;
            Position pos = pair.first;
            const Cell* cell = pair.second;
            if (!isDistrictOfColor(cell, Color::YELLOW)) continue;

            std::vector<Position> neighbors = {
                Position(pos.x + 1, pos.y),
                Position(pos.x - 1, pos.y),
                Position(pos.x,     pos.y + 1),
                Position(pos.x,     pos.y - 1),
                Position(pos.x + 1, pos.y - 1),
                Position(pos.x - 1, pos.y + 1)
            };
            for (const auto& n : neighbors) {
                const Cell* nc = board.getCell(n);
                if (nc != nullptr &&
                    nc->getType() == Type::PLACE &&
                    nc->getColor() == Color::YELLOW) {
                    hasMarketAdjacentToPlace = true;
                    break;
                }
            }
        }

        if (hasMarketAdjacentToPlace)
            score *= 2;
    }

    return score;
}

// ===== ScoreRouge : Casernes =====

static bool isOnPeriphery(const Board& board, const Position& pos) {
    auto corners = board.getCorners();
    Position tl = corners.first;
    Position br = corners.second;

    return pos.x == tl.x || pos.x == br.x ||
           pos.y == tl.y || pos.y == br.y;
}

int Marilou::ScoreRouge::compute(const Barnabe::Player& player,
                        const ScoreVariants& variants) const {
    const Board& board = getBoardFromPlayer(player);

    int stars = countStarsForColor(board, Color::RED);
    if (stars == 0) return 0;

    int value = 0;

    for (auto it = board.begin(); it != board.end(); ++it) {
        auto pair = *it;
        Position pos = pair.first;
        const Cell* cell = pair.second;
        if (!isDistrictOfColor(cell, Color::RED)) continue;

        if (!isOnPeriphery(board, pos)) continue;

        value += static_cast<int>(board.getHeight(pos));
    }

    int score = value * stars;

    // Variante : une caserne avec 3 ou 4 vides adjacents -> double
    if (variants.casernes && score > 0) {
        bool satisfiesVariant = false;

        for (auto it = board.begin(); it != board.end(); ++it) {
            auto pair = *it;
            Position pos = pair.first;
            const Cell* cell = pair.second;
            if (!isDistrictOfColor(cell, Color::RED)) continue;

            int emptyAdj = 0;
            std::vector<Position> neighbors = {
                Position(pos.x + 1, pos.y),
                Position(pos.x - 1, pos.y),
                Position(pos.x,     pos.y + 1),
                Position(pos.x,     pos.y - 1),
                Position(pos.x + 1, pos.y - 1),
                Position(pos.x - 1, pos.y + 1)
            };
            for (const auto& n : neighbors) {
                const Cell* nc = board.getCell(n);
                if (nc == nullptr)
                    emptyAdj++;
            }
            if (emptyAdj == 3 || emptyAdj == 4) {
                satisfiesVariant = true;
                break;
            }
        }

        if (satisfiesVariant)
            score *= 2;
    }

    return score;
}

// ===== ScoreViolet : Temples =====

int Marilou::ScoreViolet::compute(const Barnabe::Player& player,
                         const ScoreVariants& variants) const {
    const Board& board = getBoardFromPlayer(player);

    int stars = countStarsForColor(board, Color::PURPLE);
    if (stars == 0) return 0;

    int value = 0;

    for (auto it = board.begin(); it != board.end(); ++it) {
        auto pair = *it;
        Position pos = pair.first;
        const Cell* cell = pair.second;
        if (!isDistrictOfColor(cell, Color::PURPLE)) continue;

        bool fullySurrounded = true;
        std::vector<Position> neighbors = {
            Position(pos.x + 1, pos.y),
            Position(pos.x - 1, pos.y),
            Position(pos.x,     pos.y + 1),
            Position(pos.x,     pos.y - 1),
            Position(pos.x + 1, pos.y - 1),
            Position(pos.x - 1, pos.y + 1)
        };
        for (const auto& n : neighbors) {
            const Cell* nc = board.getCell(n);
            if (nc == nullptr) {
                fullySurrounded = false;
                break;
            }
        }
        if (!fullySurrounded) continue;

        value += static_cast<int>(board.getHeight(pos));
    }

    int score = value * stars;

    // Variante : au moins un temple sur un niveau >= 2 -> double
    if (variants.temples && score > 0) {
        bool hasTempleAboveGround = false;
        for (auto it = board.begin(); it != board.end(); ++it) {
            auto pair = *it;
            Position pos = pair.first;
            const Cell* cell = pair.second;
            if (!isDistrictOfColor(cell, Color::PURPLE)) continue;

            if (board.getHeight(pos) >= 2) {
                hasTempleAboveGround = true;
                break;
            }
        }
        if (hasTempleAboveGround)
            score *= 2;
    }

    return score;
}

// ===== ScoreVert : Jardins =====

int Marilou::ScoreVert::compute(const Barnabe::Player& player,
                       const ScoreVariants& variants) const {
    const Board& board = getBoardFromPlayer(player);

    int stars = countStarsForColor(board, Color::GREEN);
    if (stars == 0) return 0;

    int value = 0;

    for (auto it = board.begin(); it != board.end(); ++it) {
        auto pair = *it;
        Position pos = pair.first;
        const Cell* cell = pair.second;
        if (!isDistrictOfColor(cell, Color::GREEN)) continue;

        value += static_cast<int>(board.getHeight(pos));
    }

    int score = value * stars;

    // Variante : jardin adjacent à un lac (case vide entourée de cases non vides)
    if (variants.jardins && score > 0) {
        bool hasGardenAdjacentToLake = false;

        for (auto it = board.begin(); it != board.end() && !hasGardenAdjacentToLake; ++it) {
            auto pair = *it;
            Position pos = pair.first;
            const Cell* cell = pair.second;
            if (!isDistrictOfColor(cell, Color::GREEN)) continue;

            std::vector<Position> neighbors = {
                Position(pos.x + 1, pos.y),
                Position(pos.x - 1, pos.y),
                Position(pos.x,     pos.y + 1),
                Position(pos.x,     pos.y - 1),
                Position(pos.x + 1, pos.y - 1),
                Position(pos.x - 1, pos.y + 1)
            };

            for (const auto& n : neighbors) {
                const Cell* nc = board.getCell(n);
                if (nc != nullptr) continue;

                // n est vide : vérifier s'il est entouré
                bool surrounded = true;
                std::vector<Position> n2 = {
                    Position(n.x + 1, n.y),
                    Position(n.x - 1, n.y),
                    Position(n.x,     n.y + 1),
                    Position(n.x,     n.y - 1),
                    Position(n.x + 1, n.y - 1),
                    Position(n.x - 1, n.y + 1)
                };
                for (const auto& p2 : n2) {
                    const Cell* c2 = board.getCell(p2);
                    if (c2 == nullptr) {
                        surrounded = false;
                        break;
                    }
                }

                if (surrounded) {
                    hasGardenAdjacentToLake = true;
                    break;
                }
            }
        }

        if (hasGardenAdjacentToLake)
            score *= 2;
    }

    return score;
}

// ===== ScoreGeneral =====

Marilou::ScoreGeneral::ScoreGeneral()
    : couleurs(), scorePierre() {
    // On instancie ici les différentes stratégies de ScoreCouleur
    couleurs.push_back(new ScoreBleu());
    couleurs.push_back(new ScoreJaune());
    couleurs.push_back(new ScoreRouge());
    couleurs.push_back(new ScoreViolet());
    couleurs.push_back(new ScoreVert());
}

Marilou::ScoreGeneral::~ScoreGeneral() {
    for (ScoreCouleur* sc : couleurs)
        delete sc;
    couleurs.clear();
}

int Marilou::ScoreGeneral::compute(const Barnabe::Player& player,const ScoreVariants& variants) const {
    int total = 0;

    // Somme des scores de toutes les couleurs (polymorphe)
    for (ScoreCouleur* sc : couleurs) {
        total += sc->compute(player, variants);
    }

    // Ajout du score des pierres
    total += scorePierre.compute(player, variants);

    return total;
}

*/