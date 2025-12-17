#ifndef PROJETLO21A25_CASE_H
#define PROJETLO21A25_CASE_H

#include <iostream>
#include <map>
#include <string>

#include "../Utilitaires/rotation.h"
#include "../Utilitaires/position.h"

using namespace std;

namespace Barnabe {
	// Réécriture et poursuite de Tile et Cell à partir du travail de Marilou

	enum class Color { BLUE, YELLOW, RED, PURPLE, GREEN, GREY};
	enum class Type { DISTRICT, PLACE, QUARRY };

	static std::map<Color, string> ansiColorCodes = {{Color::BLUE, "4"},{Color::RED, "1"},{Color::GREEN, "2"},{Color::YELLOW, "3"},{Color::GREY, "7"}, {Color::PURPLE, "5"}};
	static std::map<Color, string> akroColorCodes = {{Color::BLUE, "h"},{Color::RED, "c"},{Color::GREEN, "j"},{Color::YELLOW, "m"},{Color::GREY, "_"},{Color::PURPLE, "t"}};
	static std::map<Type, string> akroTypeCodes = {{Type::DISTRICT, "Q"},{Type::PLACE, "P"},{Type::QUARRY, "C"}};

	/**
	 * Objet représentant une case sur un plateau d'Akropolis.
	 */
	class Cell{
		/**
		 * Identifiant partagé avec les autres cellules d'une même tuile.
		 * Sert à vérifier si deux cellules appartiennent à la même tuile pour les règles de placement.
		 */
		int id;
		/**
		 * Couleur de la case
		 */
		Color color;
		/**
		 * Type de la case
		 */
		Type type;

	public:
		/**
		 * Constructeur de la classe Cell
		 * @param i Identifiant de la case. Deux cases ayant un id identique seront considérées comme appartenant à la même tuile.
		 * @param c Couleur
		 * @param t Type
		 */
		Cell(int i, Color c, Type t): id(i), color(c), type(t) {}


		Cell(const Cell& c)
		: id(c.id), color(c.color), type(c.type) {

		}
		Cell& operator=(const Cell& c)= delete;

		/**
		 * Accesseur en lecture pour la couleur de la case.
		 * @return couleur de la case, type Color
		 */
		Color getColor() const { return color; }
		/**
		 * Renvoie la couleur de la case vue par une case voisine si l'on effectue un déplacement dans la
		 * direction r à partir de cette dernière.
		 * Sert pour gérer les cas de cases à plusieurs couleurs.
		 *
		 * Pour la classe Cell, elle est équivalente à getColor(), mais peut être redéfinie pour traiter les
		 * différents types de cases, notamment les cases bicolores.
		 *
		 * @param r Direction de la case actuelle à partir de la case dont on souhaite vérifier le voisinage
		 */
		virtual Color getEffectiveColor(const Rotation& r) const { return color; }
		/**
		 * Accesseur en lecture pour le type de la case
		 * @return type de la case, type Type
		 */
		Type getType() const { return type; }
		/**
		 * Accesseur en lecture pour l'identifiant de la case.
		 * @return id de la case, type int
		 */
		int getID() const { return id; }



		/**
		 * Renvoie la partie haute de l'affichage de la case.
		 *
		 * Format : "/xY\"
		 * - x : hauteur de la case dans le plateau
		 * - Y : type de la case (Q pour Quartier, C pour Carrière, P pour Place)
		 *
		 */
		virtual string displayTop(unsigned int height) const;

		/**
		 * Renvoie la partie basse de l'affichage de la case.
		 *
		 * Format : "\#$/"
		 * - # : Première couleur de la case
		 * - $ (pour les tuiles bicolores) : 2e couleur de la case
		 *
		 */
		virtual string displayBottom() const;
	};

	/**
	 * Extension du concept de case aux cases bicolores de l'extension Akropolis Athena.
	 *
	 * Non utilisé dans le projet, mais permet de donner un exemple de redéfinition d'une case.
	 */
	class BicolorCell : public Cell{
		/**
		 * Seconde couleur de la case
		 */
		Color secondaryColor;
		/**
		 * Rotation de la case bicolore.
		 * Une rotation d'angle 0° correspond à avoir la couleur principale sur l'hémisphère nord
		 * et la couleur secondaire sur l'hémisphère sud.
		 */
		Rotation rotation;

	public:
		/**
		 * Constructeur d'une case bicolore de l'extension Athena.
		 * @param i Identifiant de la case. Deux cases ayant un id identique seront considérées comme appartenant à la même tuile.
		 * @param c Couleur principale
		 * @param t Type
		 * @param sC Couleur secondaire
		 * @param r Rotation initiale
		 */
		BicolorCell(int i, Color c, Type t, Color sC, Rotation r): Cell(i,c,t), secondaryColor(sC), rotation(r) {};


		BicolorCell(const BicolorCell& c) = delete;
		BicolorCell& operator=(const BicolorCell& c)= delete;

		/**
		 * Accesseur en lecture pour la couleur secondaire.
		 * @return Color
		 */
		Color getSecondaryColor() const { return secondaryColor; }
		/**
		 * Accesseur en lecture pour la rotation.
		 * @return Rotation
		 */
		Rotation getRotation() const { return rotation; }
		/**
		 * Accesseur en écriture pour la rotation
		 * @param r Rotation à affecter
		 */
		void setRotation(Rotation r) { rotation = r;}
	};
}



#endif //PROJETLO21A25_CASE_H