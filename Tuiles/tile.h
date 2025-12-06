#ifndef PROJETLO21A25_TUILE_H
#define PROJETLO21A25_TUILE_H
#include <array>
#include <vector>
#include "cell.h"
#include <sstream>

using namespace std;

namespace Marilou {

	class Tile{
	public:
		Tile();
		~Tile();
		Tile(const Tile& p)=delete;
		Tile& operator=(Tile& p)=delete;
	};

	class StartingTile : public Tile {
		array <Marilou::Cell*, 4> cells;

		public :
			StartingTile(const array<Marilou::Cell*, 4>& c) : cells(c) {}
	};

	class ClassicTile : public Tile {
		array <Marilou::Cell*, 3> cells;

		public :
			ClassicTile(const array<Marilou::Cell*, 3>& c) : cells(c) {}
	};

	class AthenaTile : public Tile{
		Marilou::BicolorCell cell;

		public :
			AthenaTile(Marilou::BicolorCell c) : cell(c) {}
	};
}


namespace Barnabe {

	/*
	 * Classe abstraite représentant une tuile de Akropolis.
	 *
	 */
	class Tile{
	protected:
		/*
		 * Attribut statique servant à créer des identifiants pour les cases, permettant de connaître la tuile
		 * associée à une case.
		 * S'incrémente à chaque appel au constructeur.
		 */
		static int id;
		/*
		 * Pointeur vers un vecteur contenant les pointeurs vers les cellules qui composent la tuile.
		 */
		std::vector<const Cell*> cells;

	public:
		Tile() {id++;}
		virtual ~Tile();
		Tile(const Tile& p)=delete;
		Tile& operator=(Tile& p)=delete;

		/*
		 * Accesseur en lecture de la taille de la tuile en termes de nombres de cases.
		 * @return unsigned int
		 */
		unsigned int getSize() const {return cells.size();};

		const Cell* getCell(int i) const {
			if (i >= getSize()) throw TileException("Indice de la cellule incorrect");
			return cells[i];
		}

		//for Qt adaptation but to be modified
		string typeToString(Type t);

		string toString();

		/*
		 * Méthode permettant de calculer la position de chaque case composant la tuile à partir d'une position et une
		 * rotation données. Cette méthode est virtuelle pure, car cette méthode dépend de l'implémentation concrète de
		 * la tuile. C'est cette méthode définit la forme de la tuile.
		 * @param p Position de la tuile dans un éventuel plateau
		 * @param r Rotation de la tuile par rapport à une tuile "pivot", la première du vecteur cells par convention.
 		 * @return Vecteur de positions de la même taille que cells. La position i de ce vecteur correspond à la
 		 * position calculée de la case d'indice i dans l'attribut cells.
		 */
		virtual std::vector<Position> calculatePositions(Position p, Rotation r) const = 0;

		class const_iterator {
			vector<const Cell*>::const_iterator vec_iterator;
			friend class Tile;
			explicit const_iterator(vector<const Cell*>::const_iterator def) : vec_iterator(def) {}
		public:
			const_iterator& operator++() {
				vec_iterator++;
				return *this;
			}
			const_iterator operator++(int) {
				const_iterator old = *this;
				vec_iterator++;
				return old;
			}
			const Cell* operator*() const {
				return *vec_iterator;
			}
			bool operator==(const const_iterator & e) const {
				return vec_iterator == e.vec_iterator;
			}
			bool operator!=(const const_iterator & e) const {
				return vec_iterator != e.vec_iterator;
			}
		};

		// class const_iterator : public vector<const Cell*>::const_iterator {
		// 	friend class Tile;
		// };

		const_iterator begin() const {return const_iterator(cells.begin());}
		const_iterator end() const {return const_iterator(cells.end());}


	};

	class StartingTile : public Tile {
	public :
		StartingTile();
		virtual std::vector<Position> calculatePositions(Position p, Rotation r) const;

	};

	class ClassicTile : public Tile {
	public :
		ClassicTile(Color c1, Type t1, Color c2, Type t2, Color c3, Type t3);
		std::vector<Position> calculatePositions(Position p, Rotation r) const;

		friend ostream& operator<<(ostream& f, ClassicTile& c);


	};

	ostream& operator<<(ostream& f, ClassicTile& c);

	class AthenaTile : public Tile {
		BicolorCell* cell;

	public :
		AthenaTile(Color c1, Color c2, Type t);
		std::vector<Position> calculatePositions(Position p, Rotation r) const;
	};
}


#endif //PROJETLO21A25_TUILE_H