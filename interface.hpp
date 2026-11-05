/**
 * @file interface.hpp
 * @brief Ce fichier définit les fonctions nécessaires à l'interaction avec l'utilisateur.
 *
 * Il permet de recueillir les paramètres initiaux de la simulation, à savoir
 * la nature du matériau utilisé.
 */

#ifndef INTERFACE_HPP
#define INTERFACE_HPP



/**
 * @brief Demande à l'utilisateur de sélectionner le matériau constituant l'objet.
 * @return Un entier représentant le matériau choisi : 1 pour le cuivre, 2 pour le fer, 
 * 3 pour le verre et 4 pour le polystyrène.
 */
int choisir_materiau();

#endif