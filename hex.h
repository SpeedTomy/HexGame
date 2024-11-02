
#ifndef HEX_HEX_H
#define HEX_HEX_H

#define RESET_COLOR "\033[0m" // Réinitialiser la couleur
#define FG_RED "\033[31m"     // Rouge
#define FG_BLUE "\033[34m"    // Bleu
#define FG_MAGENTA "\033[35m" // Magenta
#define JOUEUR_BLEU 1
#define JOUEUR_ROUGE 0

// Cette fonction est responsable du chargement des données d'une partie précédemment sauvegardée.
// Elle prend en paramètres des pointeurs vers les variables qui vont stocker la taille du plateau,
// le plateau lui-même, le nombre de tours, le joueur actuel, le mode de jeu, un tableau de mémoire et le plateau de verification.
void charger(int *taille, char ***plateau, int *nombreTours, int *joueurActuel, int *mode, int Memoire[10]);

// Cette fonction permet de sauvegarder les données d'une partie en cours. Elle prend
// en paramètres la taille du plateau, le plateau lui-même, le nombre de tours, le joueur actuel,
// le mode de jeu et un tableau de mémoire.
void sauvegarder(int taille, char **plateau, int nombreTours, int joueurActuel, int mode, int Memoire[10]);

//  Cette fonction affiche le plateau de jeu hexagonale pour le jeu hex. Elle prend
//  en paramètres la taille du plateau, le plateau lui-même
//  et un tableau de mémoire.
void affichage(int taille, char **plateau, int *Memoire);

// Cette fonction initialise le plateau de jeu.
// Elle prend en paramètres la taille du plateau,
// le plateau lui-même et le mode de jeu.
void initier(int taille, char **plateau, int mode);

// Cette fonction convertit une lettre en un entier
// correspondant à sa position dans l'alphabet.
int permute(char lettre);

// Cette fonction permet au joueur de placer un pion sur le plateau. Elle prend en paramètres la
// taille du plateau, le plateau lui-même, le joueur actuel, un pointeur vers le nombre de tours,
// un pointeur vers le droit de jouer, le mode de jeu et un tableau de mémoire.
void placer(int taille, char **plateau, int joueur, int *tour, int *droit, int mode, int *Memoire, int **plateau_verif);

// Cette fonction permet au joueur de jouer le coup special retirer un pion du plateau. Elle prend en paramètres la taille
// du plateau, le plateau lui-même, le joueur actuel, un pointeur vers le nombre de tours, un pointeur vers
// le droit de jouer, le mode de jeu et un tableau de mémoire.
void special_enlev(int taille, char **plateau, int joueur, int *tour, int *droit, int mode, int *Memoire, int **plateau_verif);

// Cette fonction vérifie la validité des coordonnées entrées par le joueur.
// Elle prend en paramètres une chaîne de caractères représentant les
// coordonnées, un pointeur vers l'index de lecture, un pointeur vers la
// ligne correspondante et la taille du plateau.
int verifierCoordonnees(char *chaine, int *index, int *lig, int taille);

// Cette fonction vérifie si l'un des joueurs a gagné la partie.
// Elle prend en paramètres la taille du plateau, le plateau lui-même,
// un tableau de vérification du plateau et le joueur actuel.
int gagner(int taille, char **plateau, int **plateau_verif, int joueur);

// Cette fonction recherche la valeur minimale parmi un ensemble
// d'éléments spécifiques du plateau. Elle prend en paramètres le
// plateau de vérification, la taille du plateau, les coordonnées
// x et y.
int recherche_mini(int **plateau_verif, int taille, int x, int y);

// Cette fonction trouve la valeur minimale dans un tableau donné.
//  Elle prend en paramètres un tableau et sa longueur.
int MIN(int My_array[], int len);

#endif // HEX_HEX_H
