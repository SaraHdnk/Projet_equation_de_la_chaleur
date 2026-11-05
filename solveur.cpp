#include <vector>

/**
 * @file solveur.cpp
 * @brief Implémentation de l'algorithme de Thomas.
 *
 * Ce fichier contient l'implémentation d'un solveur numérique
 * permettant de résoudre des systèmes linéaires tridiagonaux,
 * typiquement obtenus lors de la discrétisation de l'équation
 * de la chaleur par un schéma implicite.
 */

/**
 * @brief Résout un système linéaire tridiagonal par l'algorithme de Thomas.
 *
 * Cette fonction résout un système linéaire de la forme $AX = d$,
 * où $A$ est une matrice tridiagonale définie par ses trois diagonales.
 *
 * Les vecteurs \c a, \c b et \c c représentent respectivement la
 * sous-diagonale, la diagonale principale et la sur-diagonale de
 * la matrice $A$.
 *
 * Le vecteur \c d correspond au second membre du système et est
 * modifié sur place pour contenir la solution $X$.
 *
 * @param a Sous-diagonale de la matrice tridiagonale (taille $n$).
 * @param b Diagonale principale de la matrice tridiagonale (taille $n$).
 * @param c Sur-diagonale de la matrice tridiagonale (taille $n$).
 * @param d Second membre du système, remplacé par la solution.
 */
void solveur_thomas(const std::vector<double>& a,
                    std::vector<double>& b,
                    const std::vector<double>& c,
                    std::vector<double>& d)
{
    int n = d.size();

    /* Phase de descente */
    for (int i = 1; i < n; i++) {
        double m = a[i] / b[i - 1];
        b[i] -= m * c[i - 1];
        d[i] -= m * d[i - 1];
    }

    /* Remontée */
    d[n - 1] /= b[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        d[i] = (d[i] - c[i] * d[i + 1]) / b[i];
    }
}

