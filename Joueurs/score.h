#ifndef PROJETLO21A25_SCORE_H
#define PROJETLO21A25_SCORE_H

#include <list>
#include "../Plateau/board.h"
#include "../Plateau/boardmanager.h"
#include "../Joueurs/player.h"
#include "../Tuiles/cell.h"

namespace Marilou {

struct ScoreVariants {
    bool habitations = false;
    bool marches     = false;
    bool casernes    = false;
    bool temples     = false;
    bool jardins     = false;
};

/**
 * Classe abstraite de base pour tout calcul de score.
 */
class Score {
public:
    virtual ~Score() = default;

    virtual int compute(const Eloise::Player& player,
                        const ScoreVariants& variants) const = 0;
};

/**
 * Score des pierres (cubes).
 */
class ScorePierre : public Score {
public:
    int compute(const Eloise::Player& player,
                const ScoreVariants& variants) const override;
};

/**
 * Chaque sous-classe gère une couleur (ou un groupe de couleurs).
 */
class ScoreCouleur : public Score {
public:
    virtual ~ScoreCouleur() = default;
};

/**
 * Habitations (BLEU).
 */
class ScoreBleu : public ScoreCouleur {
public:
    int compute(const Eloise::Player& player,
                const ScoreVariants& variants) const override;
};

/**
 * Marchés (JAUNE).
 */
class ScoreJaune : public ScoreCouleur {
public:
    int compute(const Eloise::Player& player,
                const ScoreVariants& variants) const override;
};

/**
 * Casernes (ROUGE).
 */
class ScoreRouge : public ScoreCouleur {
public:
    int compute(const Eloise::Player& player,
                const ScoreVariants& variants) const override;
};

/**
 * Temples (VIOLET).
 */
class ScoreViolet : public ScoreCouleur {
public:
    int compute(const Eloise::Player& player,
                const ScoreVariants& variants) const override;
};

/**
 * Jardins (VERT).
 */
class ScoreVert : public ScoreCouleur {
public:
    int compute(const Eloise::Player& player,
                const ScoreVariants& variants) const override;
};

/**
 * Score général : agrège un ensemble polymorphe de ScoreCouleur
 * + un ScorePierre.
 */
class ScoreGeneral : public Score {
    std::list<ScoreCouleur*> couleurs;
    ScorePierre scorePierre;

public:
    ScoreGeneral();
    ~ScoreGeneral();

    int compute(const Eloise::Player& player,
                const ScoreVariants& variants) const override;
};

} // namespace Marilou

#endif //PROJETLO21A25_SCORE_H