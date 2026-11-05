#ifndef BARRE_HPP
#define BARRE_HPP

#include "materiau.hpp"
#include "sdl.hpp"

/** 
 * @file barre.hpp
 * @brief Résolution de l'équation de la chaleur dans une barre 1D.
 *
 * Ce fichier contient les fonctions nécessaires à la simulation
 * de la diffusion thermique dans une barre unidimensionnelle,
 * ainsi que la définition du terme source associé.
 */

/**
 * @brief Résout l'équation de la chaleur dans une barre 1D.
 *
 * Cette fonction lance la simulation numérique de la diffusion
 * thermique dans une barre pour un matériau donné. Elle calcule
 * l'évolution temporelle de la température et assure l'affichage
 * graphique à l'aide de la classe Sdl.
 *
 * @param m Matériau étudié (propriétés thermiques).
 * @param s Objet Sdl utilisé pour l'affichage graphique.
 * @return true si la simulation s'est déroulée correctement,
 *         false si l'utilisateur a interrompu l'exécution.
 */
bool resoudre_chaleur(const Materiau& m, Sdl& s);

/**
 * @brief Terme source de chaleur.
 *
 * Cette fonction définit le terme source $F(x,t)$ de l'équation
 * de la chaleur. Elle modélise un apport de chaleur dépendant
 * de la position spatiale et des paramètres temporels.
 *
 * @param x Position spatiale.
 * @param tmax Temps maximal de la simulation.
 * @param f_val Intensité de la source de chaleur.
 * @return Valeur du terme source au point considéré.
 */
double source_F(double x, double tmax, double f_val);

#endif 
