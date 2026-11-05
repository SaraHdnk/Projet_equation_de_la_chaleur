#include <iostream>
#include <exception>
#include <vector>

#include "barre.hpp"
#include "plaque.hpp"
#include "materiau.hpp"
#include "solveur.hpp"
#include "sdl.hpp"
#include "interface.hpp"

/**
 * @file main.cpp
 * @brief Point d'entrée du programme de simulation thermique.
 *
 * L'utilisateur sélectionne un matériau via une interface console.
 * Le programme affiche ensuite successivement la diffusion thermique
 * dans une barre unidimensionnelle puis dans une plaque bidimensionnelle.
 */

int main(int argc, char** argv)
{
    try {
        /* =========================
           Liste des matériaux
           ========================= */
        std::vector<Materiau> liste = {
            {"cuivre",        389.0, 8940.0,  380.0},
            {"fer",            80.2, 7874.0,  440.0},
            {"verre",           1.2, 2530.0,  840.0},
            {"polystyrene",     0.1, 1040.0, 1200.0}
        };

        int mat_id = choisir_materiau();   // 1 à 4
        const Materiau& mat = liste[mat_id - 1];

        /* =========================
           Choix utilisateur (console)
           ========================= */

        std::cout << "\nMateriau choisi : " << mat.nom << std::endl;

        /* =========================
           Initialisation SDL
           ========================= */
        Sdl fenetre_barre(1001, 400);

        /* =========================
           Simulation 1D : Barre
           ========================= */
        std::cout << "\n--- Simulation 1D : Barre ---\n";

        if (!resoudre_chaleur(mat, fenetre_barre)) {
            fenetre_barre.quit();
            return 0;
        }

        fenetre_barre.wait(3000);
        fenetre_barre.quit();

        /* =========================
           Simulation 2D : Plaque
           ========================= */

        Sdl fenetre_plaque(1001, 1001);
        std::cout << "\n--- Simulation 2D : Plaque ---\n";

        if (!resoudre_chaleur_plaque(mat, fenetre_plaque)) {
            fenetre_plaque.quit();
            return 0;
        }

        fenetre_plaque.wait(1000);
        fenetre_plaque.quit();
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }

    (void) argc;
    (void) argv;
    return 0;
}