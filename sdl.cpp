#include "sdl.hpp"
#include <SDL.h>
#include <vector>
#include <algorithm>
#include <stdexcept>

/**
 * @file sdl.cpp
 * @brief Implémentation de la classe Sdl.
 *
 * Ce fichier contient l'implémentation des méthodes de la classe
 * Sdl, chargée de la gestion de l'affichage graphique des simulations
 * thermiques à l'aide de la bibliothèque SDL.
 */

/**
 * @brief Constructeur de la classe Sdl.
 *
 * Initialise la bibliothèque SDL, crée une fenêtre graphique ainsi
 * qu'un renderer associé, qui seront utilisés pour l'affichage des
 * résultats des simulations.
 *
 * @param w Largeur de la fenêtre.
 * @param h Hauteur de la fenêtre.
 */
Sdl::Sdl(int w, int h)
{
    w_ = w;
    h_ = h;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error("Erreur lors de l'initialisation de SDL");
    }

    win_ = SDL_CreateWindow(
        "Simulation",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        w_,
        h_,
        0
    );

    if (!win_) {
        SDL_Quit();
        throw std::runtime_error("Erreur creation fenetre SDL");
    }

    ren_ = SDL_CreateRenderer(win_, -1, 0);
    if (!ren_) {
        SDL_DestroyWindow(win_);
        SDL_Quit();
        throw std::runtime_error("Erreur creation renderer SDL");
    }
}

/**
 * @brief Destructeur de la classe Sdl.
 *
 * Libère les ressources allouées par SDL, notamment la fenêtre
 * et le renderer, puis termine l'utilisation de la bibliothèque.
 */
Sdl::~Sdl()
{
    SDL_DestroyRenderer(ren_);
    SDL_DestroyWindow(win_);
    SDL_Quit();
}

/**
 * @brief Accès au renderer SDL.
 *
 * @return Pointeur vers le renderer SDL.
 */
SDL_Renderer* Sdl::getRenderer() const
{
    return ren_;
}

/**
 * @brief Affichage de la simulation 1D (barre).
 *
 * Cette méthode affiche la distribution de température le long
 * d'une barre unidimensionnelle. La température est représentée
 * par un code couleur allant du bleu (température basse) au rouge
 * (température élevée).
 *
 * @param u Vecteur contenant les températures le long de la barre.
 */
void Sdl::sim_barre(const std::vector<double>& u)
{
    SDL_SetRenderDrawColor(ren_, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(ren_);

    for (size_t i = 0; i < u.size(); i++) {

        /**
         * Normalisation de la température pour l'affichage :
         * - bleu pour les températures proches de 286.15 K
         * - rouge pour les températures proches de 296.15 K
         */
        int r = static_cast<int>(
            255 * (u[i] - 286.15) / (296.15 - 286.15)
        );

        r = std::max(0, std::min(255, r));
        int b = 255 - r;

        SDL_SetRenderDrawColor(ren_, r, 0, b, SDL_ALPHA_OPAQUE);

        SDL_RenderDrawLine(ren_, static_cast<int>(i), 200,
                                 static_cast<int>(i), 280);
    }

    SDL_RenderPresent(ren_);
}

/**
 * @brief Affichage de la simulation 2D (plaque).
 *
 * Cette méthode affiche la distribution de température dans une
 * plaque bidimensionnelle. Chaque point de la grille est coloré
 * en fonction de sa température, selon un code couleur allant
 * du bleu au rouge.
 *
 * @param u Matrice contenant les températures de la plaque.
 */
void Sdl::sim_plaque(const std::vector<std::vector<double>>& u)
{
    SDL_SetRenderDrawColor(ren_, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(ren_);

    size_t nb_rows = u.size();
    size_t nb_col  = u[0].size();

    for (size_t i = 0; i < nb_rows; i++) {
        for (size_t j = 0; j < nb_col; j++) {

            /**
             * Normalisation de la température pour l'affichage :
             * - bleu pour les températures basses
             * - rouge pour les températures élevées
             */
            int r = static_cast<int>(
                255 * (u[i][j] - 286.15) / (290.15 - 286.15)
            );

            r = std::max(0, std::min(255, r));
            int b = 255 - r;

            SDL_SetRenderDrawColor(ren_, r, 0, b, SDL_ALPHA_OPAQUE);

            SDL_RenderDrawPoint(ren_,
                                static_cast<int>(i),
                                static_cast<int>(j));
        }
    }

    SDL_RenderPresent(ren_);
}

/**
 * @brief Introduit une pause dans l'exécution.
 *
 * @param t Durée de la pause en millisecondes.
 */
void Sdl::wait(int t)
{
    SDL_Delay(t);
}

/**
 * @brief Gestion des événements SDL.
 *
 * Cette méthode interroge la file d'événements SDL et vérifie si
 * l'utilisateur a demandé la fermeture de la fenêtre.
 *
 * @return true si la simulation doit continuer, false sinon.
 */
bool Sdl::continuer()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return false;
    }
    return true;
}

/**
 * @brief Fermeture explicite de l'environnement SDL.
 */
void Sdl::quit()
{
    SDL_Quit();
}
