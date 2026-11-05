#include "barre.hpp" 
#include "materiau.hpp"
#include "solveur.hpp"
#include "sdl.hpp"

#include <cmath>
#include <iostream>

/**
 * @file barre.cpp
 * @brief Simulation de la diffusion de la chaleur dans une barre 1D.
 *
 * Ce fichier contient l'implémentation des fonctions permettant
 * de résoudre numériquement l'équation de la chaleur dans une barre
 * unidimensionnelle et d'afficher l'évolution de la température
 * à l'aide de la bibliothèque SDL.
 */

/* =========================
   Paramètres de la simulation
   ========================= */

/**
 * @brief Longueur de la barre.
 */
const double L = 1.0;

/**
 * @brief Nombre de points du maillage spatial.
 */
const int N = 1001;

/**
 * @brief Pas de discrétisation spatiale.
 */
const double dx = L / (N - 1);

/**
 * @brief Temps total de la simulation.
 */
const double t_max = 16.0;

/**
 * @brief Pas de temps.
 */
const double dt = t_max / 100;

/**
 * @brief Température initiale (en Kelvin).
 */
const double u0 = 13.0 + 273.15;

/**
 * @brief Intensité de la source thermique (en Kelvin).
 */
const double f = 80.0 + 273.15;

/* =========================
   Terme source
   ========================= */

/**
 * @brief Terme source de chaleur.
 *
 * Cette fonction définit le terme source $F(x)$ de l'équation de la
 * chaleur. La source est non nulle uniquement dans certaines zones
 * de la barre, ce qui permet de créer des régions chauffées localement.
 *
 * @param x Position spatiale dans la barre.
 * @param tmax Temps maximal de la simulation.
 * @param f_val Intensité de la source thermique.
 * @return Valeur du terme source au point considéré.
 */
double source_F(double x, double tmax, double f_val)
{
    if (x >= L / 10.0 && x <= 2.0 * L / 10.0) {
        return tmax * std::pow(f_val, 2);
    }
    if (x >= 5.0 * L / 10.0 && x <= 6.0 * L / 10.0) {
        return 0.75 * tmax * std::pow(f_val, 2);
    }
    return 0.0;
}

/* =========================
   Résolution de l'équation de la chaleur
   ========================= */

/**
 * @brief Résout l'équation de la chaleur dans une barre 1D.
 *
 * Cette fonction résout numériquement l'équation de la chaleur dans
 * une barre unidimensionnelle à l'aide d'un schéma implicite et
 * d'un solveur tridiagonal de Thomas. L'évolution temporelle de la
 * température est affichée en temps réel à l'aide de la classe Sdl.
 *
 * @param m Matériau étudié (propriétés thermiques).
 * @param s Objet Sdl utilisé pour l'affichage graphique.
 * @return true si la simulation se termine normalement.
 */
bool resoudre_chaleur(const Materiau& m, Sdl& s)
{
    /* Diffusivité thermique */
    double alpha = m.lambda / (m.rho * m.c);

    /* Coefficient numérique */
    double z = alpha * dt / (dx * dx);

    /**
     * @brief Vecteur des températures.
     *
     * Le vecteur u contient la température à chaque point du maillage.
     * Il est initialisé à la température initiale u0.
     */
    std::vector<double> u(N, u0);

    /* Boucle temporelle */
    for (double t = 0; t < t_max; t += dt) {

        /**
         * @brief Coefficients de la matrice tridiagonale.
         *
         * a : sous-diagonale
         * b : diagonale
         * c : sur-diagonale
         */
        std::vector<double> a(N, -z);
        std::vector<double> b(N, 1 + 2 * z);
        std::vector<double> c(N, -z);

        /**
         * @brief Second membre du système linéaire.
         */
        std::vector<double> B(N);

        /* Construction du second membre */
        for (int i = 1; i < N; i++) {
            B[i] = u[i] + (dt / (m.rho * m.c)) * source_F(i * dx, t_max, f);
        }

        /* Condition aux limites de Neumann */
        b[0] = 1.0;
        c[0] = -1.0;
        B[0] = 0.0;

        /* Condition aux limites de Dirichlet */
        b[N - 1] = 1.0;
        a[N - 1] = 0.0;
        B[N - 1] = u0;

        /* Résolution du système tridiagonal */
        solveur_thomas(a, b, c, B);

        /* Mise à jour du vecteur température */
        u = B;

        /* Affichage SDL */
        s.sim_barre(u);
        s.wait(20);

        /* Gestion des événements */
        if (!s.continuer()) return false;
    }
   
    return true;
}

