#ifndef PLAQUE_HPP
#define PLAQUE_HPP

#include <string>
#include <vector>

#include "sdl.hpp"
#include "materiau.hpp"

/**
 * @file plaque.hpp
 * @brief Simulation de la diffusion de la chaleur dans une plaque 2D.
 *
 * Ce fichier contient les déclarations des fonctions permettant
 * de résoudre numériquement l'équation de la chaleur dans une
 * plaque bidimensionnelle, ainsi que la définition du terme
 * source associé.
 */

/**
 * @brief Résout l'équation de la chaleur dans une plaque 2D.
 *
 * Cette fonction lance la simulation numérique de la diffusion
 * thermique dans une plaque bidimensionnelle pour un matériau
 * donné. Elle calcule l'évolution temporelle de la température
 * et assure l'affichage graphique à l'aide de la classe Sdl.
 *
 * @param m Matériau étudié (propriétés thermiques).
 * @param s Objet Sdl utilisé pour l'affichage graphique.
 * @return true si la simulation se déroule normalement,
 *         false si l'utilisateur interrompt l'exécution.
 */
bool resoudre_chaleur_plaque(const Materiau& m, Sdl& s);

/**
 * @brief Terme source de chaleur pour la plaque 2D.
 *
 * Cette fonction définit le terme source $F(x,y)$ de l'équation
 * de la chaleur dans le cas bidimensionnel. La source est non
 * nulle uniquement dans certaines zones de la plaque, ce qui
 * permet de modéliser un apport de chaleur localisé.
 *
 * @param x Coordonnée spatiale selon l'axe $x$.
 * @param y Coordonnée spatiale selon l'axe $y$.
 * @param tmax Temps maximal de la simulation.
 * @param f_val Intensité de la source thermique.
 * @return Valeur du terme source au point considéré.
 */
double source_F_plaque(double x, double y, double tmax, double f_val);

#endif 
