#ifndef PROJETLO21A25_SCORE_H
#define PROJETLO21A25_SCORE_H

#include <list>
#include "../Plateau/board.h"
#include "../Plateau/boardmanager.h"
#include "../Joueurs/player.h"
#include "../Tuiles/cell.h"

namespace Marilou
{

	/**
	 * Structure regroupant les variantes de scoring activables pour une partie.
	 * Chaque booléen indique si la variante associée à un type de quartier est utilisée.
	 */
	struct ScoreVariants
	{
		bool home = false;
		bool market = false;
		bool barrack = false;
		bool temple = false;
		bool garden = false;
	};

	/**
	 * Enumération des niveaux de difficulté de l'architecte solo.
	 * Chaque valeur correspond à un mode de calcul de score différent.
	 */
	enum class ArchitectDifficulty
	{
		HIPPODAMOS, // facile
		METAGENES,	// moyen
		CALLICRATES // difficile
	};

	/**
	 * Interface de base pour tout calcul de score.
	 * Toute startégie de scoring doit dériver de cette classe et redéfinir compute().
	 */
	class Score
	{
	public:
		virtual ~Score() = default;

		/**
		 * Calcule le score associé à un joueur selon la stratégie implémentée.
		 * @param player Joueur dont on veut calculer le score
		 * @param variants Variantes de scoring actuellement activées
		 * @return Score entier obtenu par le joueur
		 */
		virtual int compute(const Eloise::Player &player,
							const ScoreVariants &variants) const = 0;
	};

	/**
	 * Stratégie de score pour les pierres (carrières).
	 * Le score correspond typiquement au nombre de pierres détenues par le joueur.
	 */
	class ScorePierre : public Score
	{
	public:
		int compute(const Eloise::Player &player,
					const ScoreVariants &variants) const override;
	};

	/**
	 * Stratégie de score dédiée à l'architecte solo.
	 * Le calcul parcourt l'ensemble des tuiles de l'architecte et applique les règles
	 * de scoring spécifiques à la difficulté.
	 */
	class ScoreArchitecte : public Score
	{
		ArchitectDifficulty difficulty;

	public:
		/**
		 * @param d Difficluté de l'architecte (facile, moyen, difficile)
		 */
		explicit ScoreArchitecte(ArchitectDifficulty d): difficulty(d){}

		/**
		 * Calcule le score Architecte en fonction de ses tuiles et de la difficulté
		 * @param player Architecte dont on veut calculer le score
		 * @param variants Variantes de scoring
		 * @return Score entier de l'architecte
		 */
		int compute(const Eloise::Player &player,const ScoreVariants &variants) const override;
	};

	/**
	 * Classe abstraite de base pour les stratégies de score liées aux quartiers/couleurs
	 * Chaque sous-classe implémente le calcul pour un type de quartier en particulier
	 */
	class ScoreCouleur : public Score
	{
	public:
		virtual ~ScoreCouleur() = default;
	};

	/**
	 * Stratégie de score pour les habitations (quartiers BLEU).
	 * Le calcul prend en compte la disposition des quartiers bleus et les variantes associées.
	 */
	class ScoreBleu : public ScoreCouleur
	{
	public:
		int compute(const Eloise::Player &player,
					const ScoreVariants &variants) const override;
	};

	/**
	 * Stratégie de score pour les marchés (quartiers JAUNE).
	 * Le calcul prend en compte l'isolement ou la proximité des marchés et les variantes associées.
	 */
	class ScoreJaune : public ScoreCouleur
	{
	public:
		int compute(const Eloise::Player &player,
					const ScoreVariants &variants) const override;
	};

	/**
	 * Stratégie de score pour les casernes (quartiers ROUGE).
	 * Le calcul prend en compte la position en périphérie et les variantes associées.
	 */
	class ScoreRouge : public ScoreCouleur
	{
	public:
		int compute(const Eloise::Player &player,
					const ScoreVariants &variants) const override;
	};

	/**
	 * Stratégie de score pour les temples (quartiers VIOLET).
	 * Le calcul prend en compte l'entourage des temples et les variantes associées.
	 */
	class ScoreViolet : public ScoreCouleur
	{
	public:
		int compute(const Eloise::Player &player,
					const ScoreVariants &variants) const override;
	};

	/**
	 * Stratégie de score pour les jardins (quartiers VERT).
	 * Le calcul prend en compte la position des jardins et les variantes associées.
	 */
	class ScoreVert : public ScoreCouleur
	{
	public:
		int compute(const Eloise::Player &player,
					const ScoreVariants &variants) const override;
	};

	/**
	 * ScoreGeneral : Strategy Adapt Class.
	 *
	 * - CONT joue le rôle du conteneur de stratégies (par défaut std::list<const Score*>).
	 * - ScoreGeneral n'a aucune connaissance des classes concrètes.
	 * - Pour ajouter un nouveau scoreur, on crée une nouvelle classe dérivant de Score
	 *   et on l'ajoute via addScore() dans le code client.
	 *
	 * Cette classe permet d'agréger plusieurs stratégies de score et de sommer leurs résultats.
	 */
	template <class CONT = std::list<const Score *>>
	class ScoreGeneral : public Score
	{
		CONT scores;

	public:
		/**
		 * Constructeur par défaut : crée un agrégateur vide.
		 */
		ScoreGeneral() = default;

		/**
		 * Constructeur à partir d'un conteneur de stratégies déjà configuré.
		 * @param c Conteneur de pointeurs vers des objets Score
		 */
		explicit ScoreGeneral(const CONT &c) : scores(c) {}

		/**
		 * Constructeur à partir d'un conteneur de stratégies déjà configuré.
		 * @param c Conteneur de pointeurs vers des objets Score
		 */
		CONT &getContainer() { return scores; }

		/**
		 * @return Référence constante vers le conteneur interne de stratégies
		 */
		const CONT &getContainer() const { return scores; }

		/**
		 * Ajoute une nouvelle stratégie de score à l'agrégateur.
		 * @param s Pointeur vers une stratégie de score (non possédée)
		 */
		void addScore(const Score *s) { scores.push_back(s); }

		/**
		 * Calcule le score total en sommant les contributions de chaque stratégie.
		 * @param player Joueur dont on veut calculer le score
		 * @param variants Variantes de scoring à transmettre à chaque stratégie
		 * @return Somme des scores calculés par toutes les stratégies agrégées
		 */
		int compute(const Eloise::Player &player,
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