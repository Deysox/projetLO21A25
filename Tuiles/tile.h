#ifndef PROJETLO21A25_TUILE_H
#define PROJETLO21A25_TUILE_H
#include <array>
#include <vector>
#include "cell.h"
#include <sstream>
#include "board.h"

using namespace std;

// namespace Marilou {
//
// 	class Tile{
// 	public:
// 		Tile();
// 		~Tile();
// 		Tile(const Tile& p)=delete;
// 		Tile& operator=(Tile& p)=delete;
// 	};
//
// 	class StartingTile : public Tile {
// 		array <Marilou::Cell*, 4> cells;
//
// 		public :
// 			StartingTile(const array<Marilou::Cell*, 4>& c) : cells(c) {}
// 	};
//
// 	class ClassicTile : public Tile {
// 		array <Marilou::Cell*, 3> cells;
//
// 		public :
// 			ClassicTile(const array<Marilou::Cell*, 3>& c) : cells(c) {}
// 	};
//
// 	class AthenaTile : public Tile{
// 		Marilou::BicolorCell cell;
//
// 		public :
// 			AthenaTile(Marilou::BicolorCell c) : cell(c) {}
// 	};
// }


namespace Barnabe {

	/*
	 * Classe abstraite représentant une tuile de Akropolis.
	 *
	 */
	class Tile : protected Board {
	protected:
		/*
		 * Attribut statique servant à créer des identifiants pour les cases, permettant de connaître la tuile
		 * associée à une case.
		 * S'incrémente à chaque appel au constructeur.
		 */
		static int id;




	public:
		Tile() {id++;}
		virtual ~Tile();
		Tile(const Tile& p)=delete;
		Tile& operator=(Tile& p)=delete;

		void setCell(const Cell* c, Position pos);
		const Cell* getCell(Position pos);


		/*
		 * Méthode permettant de calculer la position de chaque case composant la tuile à partir d'une position et une
		 * rotation données. Cette méthode est virtuelle pure, car cette méthode dépend de l'implémentation concrète de
		 * la tuile. C'est cette méthode définit la forme de la tuile.
		 * @param p Position de la tuile dans un éventuel plateau
		 * @param r Rotation de la tuile par rapport à une tuile "pivot", la première du vecteur cells par convention.
 		 * @return Vecteur de positions de la même taille que cells. La position i de ce vecteur correspond à la
 		 * position calculée de la case d'indice i dans l'attribut cells.
		 */
		//virtual std::vector<Position> calculatePositions(Position p, Rotation r) const = 0;

		void rotate(Rotation r);
		void rotate();

		virtual void rotationHook() = 0;

		void placeIn(Board* b,Position pos,Rotation r = Rotation(0));

		Board::iterator begin() override {return Board::begin();}
		Board::iterator end() override {return Board::end();}

		Board::const_iterator begin() const override {return Board::cbegin();}
		Board::const_iterator end() const override {return Board::cend();}

		Board::const_iterator cbegin() const override {return Board::cbegin();}
		Board::const_iterator cend() const override {return Board::cend();}

		friend inline ostream& operator<<(ostream& f, Tile& t);

	};

	inline ostream& operator<<(ostream& f, Tile& t) {t.display(f,false); return f;}

	class StartingTile : public Tile {
	public :
		StartingTile();

		void rotationHook() override;


	};

	class ClassicTile : public Tile {
	public :
		ClassicTile(Color c1, Type t1, Color c2, Type t2, Color c3, Type t3);
		void rotationHook() override;


	};



	class AthenaTile : public Tile {
		BicolorCell* cell;

	public :
		AthenaTile(Color c1, Color c2, Type t);
		void rotationHook() override;

	};
}


#endif //PROJETLO21A25_TUILE_H