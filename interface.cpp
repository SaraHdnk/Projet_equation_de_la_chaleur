/**
 * @file interface.cpp
 * @brief Implémentation d'une interface console structurée.
 */

#include "interface.hpp"
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Dessine une ligne de séparation dans la console.
 */
void dessiner_ligne()
{
    cout << "---------------------------------------------------" << endl;
}

/**
 * @brief Permet à l'utilisateur de choisir un matériau.
 *
 * L'utilisateur sélectionne le matériau étudié. La simulation
 * affichera ensuite automatiquement la diffusion thermique
 * dans une barre (1D) puis dans une plaque (2D).
 *
 * @return Indice du matériau choisi (entre 1 et 4).
 */
int choisir_materiau()
{
    string saisie;
    int choix = 0;

    cout << endl;
    dessiner_ligne();
    cout << "       SELECTION DU MATERIAU PHYSIQUE" << endl;
    dessiner_ligne();
    cout << " [1] Cuivre      (Conductivite elevee)" << endl;
    cout << " [2] Fer         (Conductivite moyenne)" << endl;
    cout << " [3] Verre       (Isolant)" << endl;
    cout << " [4] Polystyrene (Isolant fort)" << endl;
    dessiner_ligne();

    while (true) {
        cout << "Votre choix >> ";
        cin >> saisie;

        try {
            choix = stoi(saisie);
            if (choix >= 1 && choix <= 4)
                return choix;
        }
        catch (...) {
            // Ignore les erreurs de conversion
        }

        cout << "!! Choix invalide. Veuillez entrer un nombre entre 1 et 4 !!" << endl;
    }
}
