#ifndef SDL_HPP
#define SDL_HPP

#include <SDL.h>
#include <vector>

/**
 * @file sdl.hpp
 * @brief Gestion de la visualisation graphique avec SDL.
 *
 * Cette classe encapsule l'utilisation de la bibliothèque SDL
 * afin de gérer l'affichage graphique des résultats des simulations
 * thermiques. Elle permet de visualiser l'évolution de la température
 * aussi bien dans le cas d'une barre unidimensionnelle que dans le cas
 * d'une plaque bidimensionnelle.
 *
 * L'objectif de cette classe est d'isoler les appels à SDL du reste
 * du code afin de simplifier l'architecture et d'améliorer la
 * maintenabilité du projet.
 */
class Sdl {
private:
    /**
     * @brief Pointeur vers la fenêtre SDL.
     */
    SDL_Window* win_;

    /**
     * @brief Pointeur vers le renderer SDL.
     *
     * Le renderer est utilisé pour dessiner les éléments graphiques
     * représentant la distribution de température.
     */
    SDL_Renderer* ren_;

    /**
     * @brief Largeur de la fenêtre SDL.
     */
    int w_;

    /**
     * @brief Hauteur de la fenêtre SDL.
     */
    int h_;

public:
    /**
     * @brief Constructeur de la classe Sdl.
     *
     * Initialise la bibliothèque SDL, crée la fenêtre graphique
     * ainsi que le renderer associé.
     *
     * @param w Largeur de la fenêtre.
     * @param h Hauteur de la fenêtre.
     */
    Sdl(int w, int h);

    /**
     * @brief Destructeur de la classe Sdl.
     *
     * Libère les ressources associées à SDL, notamment la fenêtre
     * et le renderer.
     */
    ~Sdl();

    /**
     * @brief Accès au renderer SDL.
     *
     * @return Pointeur vers le renderer SDL.
     */
    SDL_Renderer* getRenderer() const;

    /**
     * @brief Affichage de la simulation 1D (barre).
     *
     * Cette fonction affiche l'évolution de la température le long
     * d'une barre unidimensionnelle à partir du vecteur de températures.
     *
     * @param u Vecteur contenant les températures le long de la barre.
     */
    void sim_barre(const std::vector<double>& u);

    /**
     * @brief Affichage de la simulation 2D (plaque).
     *
     * Cette fonction affiche l'évolution de la température dans une
     * plaque bidimensionnelle à partir d'une matrice de températures.
     *
     * @param u Matrice contenant les températures de la plaque.
     */
    void sim_plaque(const std::vector<std::vector<double>>& u);

    /**
     * @brief Pause l'exécution pendant un temps donné.
     *
     * Cette fonction introduit un délai afin de contrôler la vitesse
     * d'affichage des simulations.
     *
     * @param t Durée de la pause en millisecondes.
     */
    static void wait(int t);

    /**
     * @brief Gestion des événements SDL.
     *
     * Cette fonction traite les événements SDL (fermeture de la fenêtre,
     * interactions utilisateur, etc.) et indique si la simulation doit
     * se poursuivre.
     *
     * @return true si la simulation continue, false sinon.
     */
    bool continuer();

    /**
     * @brief Fermeture propre de l'environnement SDL.
     *
     * Cette fonction détruit la fenêtre et le renderer SDL et
     * met fin à l'utilisation de la bibliothèque graphique.
     */
    void quit();
};

#endif 
