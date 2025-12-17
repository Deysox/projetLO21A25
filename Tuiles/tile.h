#ifndef PROJETLO21A25_TUILE_H
#define PROJETLO21A25_TUILE_H
#include <array>
#include <vector>
#include "cell.h"
#include <sstream>

using namespace std;
namespace Barnabe {

	/**
	 * Classe abstraite représentant une tuile de Akropolis. Cette classe abstraite implémente les fonctions
	 * générales à tous les types de tuiles, comme les accesseurs en lecture et le système d'ID pour les cases.
	 *
	 * Pour définir un nouveau type de tuile, il suffit d'hériter de cette classe et redéfinir la méthode virtuelle pure
	 * calculatePositions() qui définit la forme de la tuile, et instancier les cellules dans le constructeur, dans
	 * l'ordre des positions.
	 *
	 * Tile gère le cycle de vie de Cell
	 */
	class Tile{
	protected:
		/**
		 * Attribut statique servant à créer des identifiants pour les cases, permettant de connaître la tuile
		 * associée à une case.
		 * S'incrémente à chaque appel au constructeur.
		 */
		static int id;
		/**
		 * Pointeur vers un vecteur contenant les pointeurs vers les cellules qui composent la tuile.
		 */
		std::vector<const Cell*> cells;

	public:
		/**
		 * Constructeur de la classe Tile. Lors de la construction d'une nouvelle tuile, l'identifiant id est
		 * incrémenté pour que les nouvelles cellules instanciées lors de la création de la tuile portent un id différent
		 * des cases précédentes.
		 */
		Tile() {id++;}

		/**
		 * Destructeur de la classe Tile. Désalloue les cellules contenues dans le vecteur cells.
		 */
		virtual ~Tile();

		/**
		 * Le constructeur par recopie de Tile est détruit.
		 */
		Tile(const Tile& p)=delete;
		/**
		 * L'opérateur d'affectation de Tile est détruit.
		 */
		Tile& operator=(Tile& p)=delete;

		/**
		 * Accesseur en lecture de la taille de la tuile en termes de nombres de cases.
		 * @return unsigned int
		 */
		unsigned int getSize() const {return cells.size();};

		/**
		 * Accesseur en lecture d'une case de la tuile. La case d'indice i est la case insérée en ième position
		 * lors de la création de la tuile, dépendant donc du type de tuile.
		 * @param i Indice
		 * @return Pointeur vers la case voulue
		 */
		const Cell* getCell(int i) const {
			if (i >= getSize()) throw TileException("Indice de la cellule incorrect");
			return cells[i];
		}

		/*
		 * A completer par la personne qui a fait cette fonction
		 */
		string typeToString(Type t);

		/*
		 * Pareillement
		 */
		string toString();

		/**
		 * Méthode permettant de calculer la position de chaque case composant la tuile à partir d'une position et une
		 * rotation données. Cette méthode est virtuelle pure, car cette méthode dépend de l'implémentation concrète de
		 * la tuile. C'est cette méthode définit la forme de la tuile.
		 * @param p Position de la tuile dans un éventuel plateau
		 * @param r Rotation de la tuile par rapport à une tuile "pivot", la première du vecteur cells par convention.
 		 * @return Vecteur de positions de la même taille que cells. La position i de ce vecteur correspond à la
 		 * position calculée de la case d'indice i dans l'attribut cells.
		 */
		virtual std::vector<Position> calculatePositions(const Position& p, const Rotation& r) const = 0;

		// class const_iterator {
		// 	vector<const Cell*>::const_iterator vec_iterator;
		// 	friend class Tile;
		// 	explicit const_iterator(vector<const Cell*>::const_iterator def) : vec_iterator(def) {}
		// public:
		// 	const_iterator& operator++() {
		// 		vec_iterator++;
		// 		return *this;
		// 	}
		// 	const_iterator operator++(int) {
		// 		const_iterator old = *this;
		// 		vec_iterator++;
		// 		return old;
		// 	}
		// 	const Cell* operator*() const {
		// 		return *vec_iterator;
		// 	}
		// 	bool operator==(const const_iterator & e) const {
		// 		return vec_iterator == e.vec_iterator;
		// 	}
		// 	bool operator!=(const const_iterator & e) const {
		// 		return vec_iterator != e.vec_iterator;
		// 	}
		// };

		/**
		 * Itérateur constant sur les cases contenues dans la tuile. L'ordre est déterminée par l'ordre d'ajout
		 * des cases à la tuile.
		 */
		class const_iterator : public vector<const Cell*>::const_iterator {
			friend class Tile;
			const_iterator(vector<const Cell*>::const_iterator ci) : vector<const Cell*>::const_iterator(ci) {}
		};

		/**
		 * @return const_iterator sur la première case
		 */
		const_iterator begin() const {return const_iterator(cells.begin());}
		/**
		 * @return const_iterator indiquant la fin de parcours
		 */
		const_iterator end() const {return const_iterator(cells.end());}

		/**
		 *
		 * @return const_iterator sur la première case
		 */
		const_iterator cbegin() const {return const_iterator(cells.begin());}

		/**
		 * @return const_iterator indiquant la fin de parcours
		 */
		const_iterator cend() const {return const_iterator(cells.end());}


	};

	/**
	 * Tuile de départ du jeu Akropolis.
	 */
	class StartingTile : public Tile {
	public :
		StartingTile();
		std::vector<Position> calculatePositions(const Position& p, const Rotation& r) const override;

	};

	/**
	 * Tuile normale du jeu Akropolis, contenant trois cases.
	 */
	class ClassicTile : public Tile {
	public :
		ClassicTile(Color c1, Type t1, Color c2, Type t2, Color c3, Type t3);
		std::vector<Position> calculatePositions(const Position& p, const Rotation& r) const override;

		friend ostream& operator<<(ostream& f, ClassicTile& c);


	};

	/**
	 * Opérateur d'agrégation d'une tuile classique à un flux de sortie.
	 * @param f Flux de sortie à agréger
	 * @param c Tuile à afficher
	 * @return Flux modifié
	 */
	ostream& operator<<(ostream& f, ClassicTile& c);

	/**
	 * Tuile bicolore de l'extension Akropolis Athena.
	 *
	 * Non utilisée dans la version finale.
	 */
	class AthenaTile : public Tile {
		BicolorCell* cell;

	public :
		AthenaTile(Color c1, Color c2, Type t);
		std::vector<Position> calculatePositions(const Position& p, const Rotation& r) const override;
	};
}


#endif //PROJETLO21A25_TUILE_H