#ifndef PROJETLO21A25_SCORE_H
#define PROJETLO21A25_SCORE_H

#include <list>
#include "../Plateau/board.h"
#include "../Plateau/boardmanager.h"
#include "../Joueurs/player.h"
#include "../Tuiles/cell.h"

namespace Marilou
{

	struct ScoreVariants
	{
		bool habitations = false;
		bool marches = false;
		bool casernes = false;
		bool temples = false;
		bool jardins = false;
	};

	/**
	 * Interface de base pour tout calcul de score.
	 */
	class Score
	{
	public:
		virtual ~Score() = default;
		virtual int compute(const Barnabe::Player &player,
							const ScoreVariants &variants) const = 0;
	};

	/**
	 * Score des pierres (cubes).
	 */
	class ScorePierre : public Score
	{
	public:
		int compute(const Barnabe::Player &player,
					const ScoreVariants &variants) const override;
	};

	/**
	 * Chaque sous-classe gère une couleur (ou un groupe de couleurs).
	 */
	class ScoreCouleur : public Score
	{
	public:
		virtual ~ScoreCouleur() = default;
	};

	/**
	 * Habitations (BLEU).
	 */
	class ScoreBleu : public ScoreCouleur
	{
	public:
		int compute(const Barnabe::Player &player,
					const ScoreVariants &variants) const override;
	};

	/**
	 * Marchés (JAUNE).
	 */
	class ScoreJaune : public ScoreCouleur
	{
	public:
		int compute(const Barnabe::Player &player,
					const ScoreVariants &variants) const override;
	};

	/**
	 * Casernes (ROUGE).
	 */
	class ScoreRouge : public ScoreCouleur
	{
	public:
		int compute(const Barnabe::Player &player,
					const ScoreVariants &variants) const override;
	};

	/**
	 * Temples (VIOLET).
	 */
	class ScoreViolet : public ScoreCouleur
	{
	public:
		int compute(const Barnabe::Player &player,
					const ScoreVariants &variants) const override;
	};

	/**
	 * Jardins (VERT).
	 */
	class ScoreVert : public ScoreCouleur
	{
	public:
		int compute(const Barnabe::Player &player,
					const ScoreVariants &variants) const override;
	};

	/**
	 * ScoreGeneral : Strategy Adapt Class.
	 *
	 * - CONT joue le rôle du conteneur de stratégies (par défaut std::list<const Score*>).
	 * - ScoreGeneral n'a aucune connaissance des classes concrètes.
	 * - Pour ajouter un nouveau scoreur, on crée une nouvelle classe dérivant de Score
	 *   et on l'ajoute via addScore() dans le code client.
	 */
	template <class CONT = std::list<const Score *>>
	class ScoreGeneral : public Score
	{
		CONT scores;

	public:
		ScoreGeneral() = default;

		explicit ScoreGeneral(const CONT &c) : scores(c) {}

		// Accès au conteneur interne pour configuration fine.
		CONT &getContainer() { return scores; }
		const CONT &getContainer() const { return scores; }

		// Ajout d'une stratégie de score.
		void addScore(const Score *s) { scores.push_back(s); }

		int compute(const Barnabe::Player &player,
					const ScoreVariants &variants) const override
		{
			int total = 0;
			for (const Score *s : scores)
				total += s->compute(player, variants);
			return total;
		}
	};

} // namespace Marilou

#endif // PROJETLO21A25_SCORE_H
