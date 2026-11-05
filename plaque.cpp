#include "plaque.hpp"
#include "materiau.hpp"
#include <cmath>
#include "solveur.hpp"
#include "sdl.hpp"

/**
 * @file plaque.cpp
 * @brief Simulation de la diffusion de la chaleur dans une plaque 2D.
 *
 * Ce fichier contient l'implémentation des fonctions permettant
 * de résoudre numériquement l'équation de la chaleur dans une
 * plaque bidimensionnelle à l'aide d'une méthode de décomposition
 * directionnelle (ADI), ainsi que l'affichage graphique via SDL.
 */

/* =========================
   Paramètres de la simulation
   ========================= */

/**
 * @brief Longueur du domaine spatial (plaque carrée).
 */
const double L = 1.0;

/**
 * @brief Nombre de points du maillage selon chaque direction.
 */
const int N = 1001;

/**
 * @brief Pas de discrétisation spatiale selon x.
 */
const double dx = L / (N - 1);

/**
 * @brief Pas de discrétisation spatiale selon y.
 */
const double dy = L / (N - 1);

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
   Terme source 2D
   ========================= */

/**
 * @brief Terme source de chaleur pour la plaque 2D.
 *
 * Cette fonction définit le terme source $F(x,y)$ de l'équation
 * de la chaleur dans le cas bidimensionnel. La source est non
 * nulle uniquement dans plusieurs zones localisées de la plaque,
 * permettant de créer des régions chauffées distinctes.
 *
 * @param x Coordonnée spatiale selon l'axe x.
 * @param y Coordonnée spatiale selon l'axe y.
 * @param tmax Temps maximal de la simulation.
 * @param f_val Intensité de la source thermique.
 * @return Valeur du terme source au point considéré.
 */
double source_F_plaque(double x, double y, double tmax, double f_val)
{
    if (x >= L / 6.0 && x <= 2.0 * L / 6.0 && y >= L / 6.0 && y <= 2.0 * L / 6.0) {
        return tmax * std::pow(f_val, 2);
    }
    else if (x >= 4.0 * L / 6.0 && x <= 5.0 * L / 6.0 && y >= L / 6.0 && y <= 2.0 * L / 6.0) {
        return tmax * std::pow(f_val, 2);
    }
    else if (x >= L / 6.0 && x <= 2.0 * L / 6.0 && y >= 4.0 * L / 6.0 && y <= 5.0 * L / 6.0) {
        return tmax * std::pow(f_val, 2);
    }
    else if (x >= 4.0 * L / 6.0 && x <= 5.0 * L / 6.0 && y >= 4.0 * L / 6.0 && y <= 5.0 * L / 6.0) {
        return tmax * std::pow(f_val, 2);
    }
    return 0.0;
}

/* =========================
   Résolution de l'équation de la chaleur en 2D
   ========================= */

/**
 * @brief Résout l'équation de la chaleur dans une plaque 2D.
 *
 * Cette fonction résout numériquement l'équation de la chaleur
 * dans une plaque bidimensionnelle à l'aide d'un schéma implicite
 * de type ADI (Alternating Direction Implicit). La résolution est
 * effectuée alternativement selon les directions x et y, ce qui
 * permet de réduire la complexité du problème.
 *
 * L'évolution temporelle de la température est affichée en temps
 * réel à l'aide de la classe Sdl.
 *
 * @param m Matériau étudié (propriétés thermiques).
 * @param s Objet Sdl utilisé pour l'affichage graphique.
 * @return true si la simulation se termine normalement.
 */
bool resoudre_chaleur_plaque(const Materiau& m, Sdl& s)
{
    /* Diffusivité thermique */
    double alpha = m.lambda / (m.rho * m.c);

    /* Coefficients numériques selon chaque direction */
    double z_x = alpha * dt / (2 * dx * dx);
    double z_y = alpha * dt / (2 * dy * dy);

    /**
     * @brief Champs de température.
     *
     * u      : température au temps courant
     * u_demi : température intermédiaire (schéma ADI)
     */
    std::vector<std::vector<double>> u(N, std::vector<double>(N, u0));
    std::vector<std::vector<double>> u_demi(N, std::vector<double>(N, u0));

    int compt = 0;

    /* Boucle temporelle */
    for (double t = 0; t < t_max; t += dt / 2) {
        compt++;

        /* Étape implicite selon x */
        if (compt % 2 == 1) {

            for (int i = 1; i < N - 1; i++) {

                std::vector<double> a(N, -z_x);
                std::vector<double> b(N, 1 + 2 * z_x);
                std::vector<double> c(N, -z_x);
                std::vector<double> B(N, u0);

                /* Condition aux limites de Neumann */
                b[0] = 1.0;
                c[0] = -1.0;
                B[0] = 0.0;

                for (int j = 1; j < N - 1; j++) {
                    B[j] = u[i][j]
                         + z_y * (u[i + 1][j] - 2 * u[i][j] + u[i - 1][j])
                         + (dt / (2 * m.rho * m.c))
                         * source_F_plaque(i * dx, j * dy, t_max, f);
                }

                /* Condition aux limites de Dirichlet */
                b[N - 1] = 1.0;
                a[N - 1] = 0.0;
                B[N - 1] = u0;

                solveur_thomas(a, b, c, B);

                for (int k = 0; k < N; k++) {
                    u_demi[i][k] = B[k];
                }
            }
        }
        /* Étape implicite selon y */
        else {

            for (int j = 1; j < N - 1; j++) {

                std::vector<double> a(N, -z_x);
                std::vector<double> b(N, 1 + 2 * z_x);
                std::vector<double> c(N, -z_x);
                std::vector<double> B(N, u0);

                /* Condition aux limites de Neumann */
                b[0] = 1.0;
                c[0] = -1.0;
                B[0] = 0.0;

                for (int i = 1; i < N - 1; i++) {
                    B[i] = u_demi[i][j]
                         + z_x * (u_demi[i][j + 1] - 2 * u_demi[i][j] + u_demi[i][j - 1])
                         + (dt / (2 * m.rho * m.c))
                         * source_F_plaque(i * dx, j * dy, t_max, f);
                }

                /* Condition aux limites de Dirichlet */
                b[N - 1] = 1.0;
                a[N - 1] = 0.0;
                B[N - 1] = u0;

                solveur_thomas(a, b, c, B);

                for (int k = 0; k < N; k++) {
                    u[k][j] = B[k];
                }
            }

            /* Affichage SDL */
            s.sim_plaque(u);
            s.wait(20);
            if (!s.continuer()) return false;
        }
    }

    return true;
}
