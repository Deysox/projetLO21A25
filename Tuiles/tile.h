#ifndef PROJETLO21A25_TUILE_H
#define PROJETLO21A25_TUILE_H
#include <array>
#include <vector>
#include "cell.h"

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
		std::vector<const Cell*>* cells;

	public:
		Tile() : cells(new std::vector<const Cell*>()) {id++;}
		~Tile();
		Tile(const Tile& p)=delete;
		Tile& operator=(Tile& p)=delete;

		/*
		 * Accesseur en lecture de la taille de la tuile en termes de nombres de cases.
		 * @return unsigned int
		 */
		unsigned int getSize() const {return cells->size();};
		/*
		 * Accesseur en lecture du vecteur contenant les vecteurs vers les cellules.
		 * @return const std::vector<const Cell*>*
		 */
		const std::vector<const Cell*>* getCells() const {return cells;}
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