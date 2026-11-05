#ifndef MATERIAU_HPP
#define MATERIAU_HPP

#include <string>

/**
 * @file materiau.hpp
 * @brief Structure représentant un matériau thermique.
 *
 * Cette structure regroupe les propriétés thermiques
 * nécessaires à la résolution de l'équation de la chaleur.
 * Elle est utilisée aussi bien pour les simulations en une
 * dimension (barre) que pour les simulations en deux
 * dimensions (plaque).
 */
struct Materiau {

    /**
     * @brief Nom du matériau.
     *
     * Chaîne de caractères utilisée principalement pour
     * l'affichage et l'identification du matériau lors
     * de l'exécution du programme.
     */
    std::string nom;

    /**
     * @brief Conductivité thermique du matériau.
     *
     * Paramètre exprimé en W·m$^{-1}$·K$^{-1}$, caractérisant
     * la capacité du matériau à conduire la chaleur.
     */
    double lambda;

    /**
     * @brief Masse volumique du matériau.
     *
     * Paramètre exprimé en kg·m$^{-3}$, intervenant dans
     * le terme volumique $\rho c$ de l'équation de la chaleur.
     */
    double rho;

    /**
     * @brief Capacité thermique massique.
     *
     * Paramètre exprimé en J·kg$^{-1}$·K$^{-1}$, représentant
     * l'énergie nécessaire pour élever la température du
     * matériau d'un Kelvin.
     */
    double c;
};

#endif 
