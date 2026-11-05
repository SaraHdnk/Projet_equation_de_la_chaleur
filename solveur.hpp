#ifndef SOLVEUR_HPP
#define SOLVEUR_HPP

#include <vector>

/**
 * @file solveur.hpp
 * @brief Résolution de systèmes linéaires tridiagonaux.
 *
 * Ce fichier contient la déclaration d'un solveur numérique
 * permettant de résoudre efficacement des systèmes linéaires
 * tridiagonaux issus de la discrétisation de l'équation de la chaleur.
 */

/**
 * @brief Résout un système linéaire tridiagonal par l'algorithme de Thomas.
 *
 * Cette fonction implémente l'algorithme de Thomas, une méthode
 * directe optimisée pour la résolution de systèmes linéaires
 * tridiagonaux de la forme $Ax = d$.
 *
 * Les vecteurs \c a, \c b et \c c représentent respectivement
 * la sous-diagonale, la diagonale et la sur-diagonale de la
 * matrice tridiagonale $A$.
 *
 * Le vecteur \c d représente le second membre du système et
 * est modifié sur place pour contenir la solution du système.
 *
 * @param a Sous-diagonale du système (taille N).
 * @param b Diagonale principale du système (taille N).
 * @param c Sur-diagonale du système (taille N).
 * @param d Second membre du système, remplacé par la solution.
 */
void solveur_thomas(const std::vector<double>& a,
                    std::vector<double>& b,
                    const std::vector<double>& c,
                    std::vector<double>& d);

#endif 
