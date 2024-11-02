#include "hex.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// Fonction permettant d'initialiser la matrice
void initier(int taille, char **plateau, int mode)
{
    srand(time(NULL));
    int i = 0, j = 0, N = (taille - 1) / 2;

    for (i = 0; i < taille; i++)
    {
        for (j = 0; j < taille; j++)
        {
            plateau[i][j] = 'O';
        }
    }
    if (mode == 2)
    {
        // Placement aléatoire des pions pour chaque joueur
        for (i = 0; i < N; i++)
        {
            // Placement des pions du joueur 1
            int row1, col1;
            do
            {
                row1 = rand() % taille;
                col1 = rand() % taille;
            } while (plateau[row1][col1] != 'O');

            plateau[row1][col1] = 4;

            // Placement des pions du joueur 2
            int row2, col2;
            do
            {
                row2 = rand() % taille;
                col2 = rand() % taille;
            } while (plateau[row2][col2] != 'O');

            plateau[row2][col2] = 5;
        }
    }
}

// Fonction permettant de sauvegarder la partie
void sauvegarder(int taille, char **plateau, int nombreTours, int joueurActuel, int mode, int Memoire[10])
{
    FILE *fichier = fopen("../sauvegarde.txt", "w"); // Ouverture du fichier en mode écriture

    if (fichier != NULL)
    {
        fprintf(fichier, "%d\n", taille); // Écriture de la taille du plateau
        for (int i = 0; i < taille; i++)
        {
            for (int j = 0; j < taille; j++)
            {
                fprintf(fichier, "%c ", plateau[i][j]); // Écriture de l'état de chaque case du plateau
            }
            fprintf(fichier, "\n");
        }
        fprintf(fichier, "%d\n", nombreTours);  // Écriture du nombre de tours
        fprintf(fichier, "%d\n", joueurActuel); // Écriture du joueur actuel
        fprintf(fichier, "%d\n", mode);         // Écriture du mode
        for (int i = 0; i < 10; i++)
        {
            fprintf(fichier, "%d ", Memoire[i]); // Écriture de l'état de chaque case du plateau
        }

        fclose(fichier); // Fermeture du fichier
        printf("La partie a ete sauvegardee.\n");
    }
    else
    {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
    }
}

// Fonction permetttant de charger la partie
void charger(int *taille, char ***plateau, int *nombreTours, int *joueurActuel, int *mode, int Memoire[10])
{
    FILE *fichier = fopen("../sauvegarde.txt", "r"); // Ouverture du fichier en mode lecture

    if (fichier != NULL)
    {
        fscanf(fichier, "%d", taille); // Lecture de la taille du plateau
        *plateau = (char **)malloc(sizeof(char *) * (*taille));
        for (int i = 0; i < *taille; i++)
        {
            (*plateau)[i] = (char *)malloc(sizeof(char) * (*taille));
            for (int j = 0; j < *taille; j++)
            {
                fscanf(fichier, " %c", &(*plateau)[i][j]); // Lecture de l'état de chaque case du plateau
            }
        }
        fscanf(fichier, "%d", nombreTours);  // Lecture du nombre de tours
        fscanf(fichier, "%d", joueurActuel); // Lecture du joueur actuel
        fscanf(fichier, "%d", mode);         // Lecture mode
        for (int i = 0; i < 10; i++)
        {
            fscanf(fichier, "%d", &Memoire[i]); // Écriture de l'état de chaque case du plateau
        }
        fclose(fichier); // Fermeture du fichier
        printf("La partie a ete chargee.\n");
    }
    else
    {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
    }
}

// Fonction permettant d'afficher une matrice
void affichage(int taille, char **plateau, int *Memoire)
{
    int numero;
    numero = 1;
    switch (taille)
    {
    case 9:
        printf("      A   B   C   D   E   F   G   H   I\n");
        printf(FG_RED);
        printf("       *   *   *   *   *   *   *   *   *\n");
        break;
    case 10:
        printf("      A   B   C   D   E   F   G   H   I   J\n");
        printf(FG_RED);
        printf("       *   *   *   *   *   *   *   *   *   *\n");
        break;
    case 11:
        printf("      A   B   C   D   E   F   G   H   I   J   K\n");
        printf(FG_RED);
        printf("       *   *   *   *   *   *   *   *   *   *   *\n");
        break;
    case 12:
        printf("      A   B   C   D   E   F   G   H   I   J   K   L\n");
        printf(FG_RED);
        printf("       *   *   *   *   *   *   *   *   *   *   *   *\n");
        break;
    case 13:
        printf("      A   B   C   D   E   F   G   H   I   J   K   L   M\n");
        printf(FG_RED);
        printf("       *   *   *   *   *   *   *   *   *   *   *   *   *\n");
        break;
    case 14:
        printf("      A   B   C   D   E   F   G   H   I   J   K   L   M   N\n");
        printf(FG_RED);
        printf("       *   *   *   *   *   *   *   *   *   *   *   *   *   *\n");
        break;
    default:
        printf("      A   B   C   D   E   F   G   H   I\n");
        printf(FG_RED);
        printf("       *   *   *   *   *   *   *   *   *\n");
        break;
    }
    for (int i = taille - 1; i >= 0; i--)
    {
        // Décalage horizontal pour former un parallélogramme
        for (int k = 0; k < taille - i - 1; k++)
        {
            printf("  ");
        }
        // numeroter les lignes
        printf(RESET_COLOR);
        if (numero < 10)
        {
            printf(" %d", numero);
        }
        else
        {
            printf("%d", numero);
        }
        numero += 1;
        printf(FG_BLUE);
        printf("   *");

        for (int j = 0; j < taille; j++)
        {
            printf(RESET_COLOR);
            if (plateau[i][j] == 4)
            {
                printf(FG_RED);
                printf("%4c", plateau[i][j]);
                printf(RESET_COLOR);
            }
            else
            {
                if (plateau[i][j] == 5)
                {
                    printf(FG_BLUE);
                    printf("%4c", plateau[i][j]);
                    printf(RESET_COLOR);
                }
                else
                {
                    if (plateau[i][j] == '0')
                    {
                        if (i == Memoire[4] && j == Memoire[5] && Memoire[8] == 0)
                        {
                            plateau[i][j] = 'O';
                            printf("%4c", plateau[i][j]);
                        }
                        else if (i == Memoire[6] && j == Memoire[7] && Memoire[9] == 0)
                        {
                            plateau[i][j] = 'O';
                            printf("%4c", plateau[i][j]);
                        }
                        else
                        {
                            printf(FG_MAGENTA);
                            printf("%4c", plateau[i][j]);
                            printf(RESET_COLOR);
                        }
                    }
                    else
                    {
                        printf("%4c", plateau[i][j]);
                    }
                }
            }
        }
        printf(FG_BLUE);
        printf("   *");
        printf("\n");
    }
    switch (taille)
    {
    case 9:
        printf(FG_RED);
        printf("                           *   *   *   *   *   *   *   *   *\n");
        break;
    case 10:
        printf(FG_RED);
        printf("                             *   *   *   *   *   *   *   *   *   *\n");
        break;
    case 11:
        printf(FG_RED);
        printf("                               *   *   *   *   *   *   *   *   *   *   *\n");
        break;
    case 12:
        printf(FG_RED);
        printf("                                 *   *   *   *   *   *   *   *   *   *   *   *\n");
        break;
    case 13:
        printf(FG_RED);
        printf("                                   *   *   *   *   *   *   *   *   *   *   *   *   *\n");
        break;
    case 14:
        printf(FG_RED);
        printf("                                     *   *   *   *   *   *   *   *   *   *   *   *   *   *\n");
        break;
    default:
        printf(FG_RED);
        printf("                           *   *   *   *   *   *   *   *   *\n");
        break;
    }
    printf(RESET_COLOR);
}

// fonction qui permet de convertir la colonne en chiffre
int permute(char lettre)
{
    int col;
    col = -1;
    switch (lettre)
    {
    case 'A':
        col = 0;
        break;
    case 'B':
        col = 1;
        break;
    case 'C':
        col = 2;
        break;
    case 'D':
        col = 3;
        break;
    case 'E':
        col = 4;
        break;
    case 'F':
        col = 5;
        break;
    case 'G':
        col = 6;
        break;
    case 'H':
        col = 7;
        break;
    case 'I':
        col = 8;
        break;
    case 'J':
        col = 9;
        break;
    case 'K':
        col = 10;
        break;
    case 'L':
        col = 11;
        break;
    case 'M':
        col = 12;
        break;
    case 'N':
        col = 13;
        break;
    default:
        break;
    }
    return col;
}

// Fonction qui permet de verifier les coordonnées rentrées
int verifierCoordonnees(char *chaine, int *index, int *lig, int taille)
{
    chaine[0] = toupper(chaine[0]);

    if (isalpha(chaine[0]))
    {
        if (strlen(chaine) != 2 && strlen(chaine) != 3)
        {
            printf("Attention, on ne peut pas jouer en dehors du plateau.\n");
            return 0;
        }
        else
        {
            *index = permute(chaine[0]);
            if (strlen(chaine) == 2)
            {
                if (isdigit(chaine[1]) == 1)
                {
                    sscanf(chaine, "%*[^0-9]%d%*[^0-9]", lig);
                }
                else
                {
                    printf("Attention, on ne peut pas jouer en dehors du plateau.\n");
                    return 0;
                }
            }
            else
            {
                if (isdigit(chaine[1]) == 1 && isdigit(chaine[2]) == 1)
                {
                    sscanf(chaine, "%*[^0-9]%d%*[^0-9]", lig);
                }
                else
                {
                    printf("Attention, on ne peut pas jouer en dehors du plateau.\n");
                    return 0;
                }
            }
        }
    }

    if (*index > taille - 1 || *lig > taille || *index < 0 || *lig <= 0)
    {
        printf("Attention, on ne peut pas jouer en dehors du plateau.\n");
        return 0;
    }

    return 1;
}

// Fonction qui permet de jouer le coup spécial "enlever"
void special_enlev(int taille, char **plateau, int joueur, int *tour, int *droit, int mode, int *Memoire, int **plateau_verif)
{
    char chaine1[100], pion_adv;
    int lig, index;

    if (joueur == 1)
    {
        if (Memoire[2] != 0)
        {
            printf("Vous avez deja utilise votre coup special enlever\n");
            placer(taille, plateau, joueur, tour, droit, mode, Memoire, plateau_verif);
            return;
        }
        else
        {
            pion_adv = 5;
        }
    }
    else
    {
        if (Memoire[3] != 0)
        {
            printf("Vous avez deja utilise votre coup special enlever\n");
            placer(taille, plateau, joueur, tour, droit, mode, Memoire, plateau_verif);
            return;
        }
        else
        {
            pion_adv = 4;
        }
    }

    do
    {
        printf("quelle case enlever?\n");
        scanf("%s", chaine1);
    } while (!(verifierCoordonnees(chaine1, &index, &lig, taille)));

    if (plateau[taille - lig][index] != pion_adv)
    {
        printf("Attention, on ne peut pas jouer en dehors du plateau. 6\n");
        special_enlev(taille, plateau, joueur, Memoire, droit, mode, Memoire, plateau_verif);
        return;
    }

    if (joueur == 1)
    {
        plateau[taille - lig][index] = '0';
        Memoire[2] = 1;
        Memoire[4] = taille - lig;
        Memoire[5] = index;
        Memoire[8] = 3;
        affichage(taille, plateau, Memoire);
    }
    else
    {
        plateau[taille - lig][index] = '0';
        Memoire[3] = 1;
        Memoire[6] = taille - lig;
        Memoire[7] = index;
        Memoire[9] = 3;
        affichage(taille, plateau, Memoire);
    }
}

// fonction qui permet de placer les pions
void placer(int taille, char **plateau, int joueur, int *tour, int *droit, int mode, int *Memoire, int **plateau_verif)
{
    char lettre;
    char chaine[100];
    int lig = 0, index = 0;

    printf("Entrez les coordonnees de la case voulue sous la forme LettreChiffre\n");
    scanf("%s", chaine);

    while (isalpha(chaine[0]) == 0)
    {
        printf("Attention, on ne peut pas jouer en dehors du plateau.\n");
        printf("Entrez les coordonnees de la case voulue sous la forme LettreChiffre\n");
        scanf("%s", chaine);
    }

    chaine[0] = toupper(chaine[0]);

    if (isalpha(chaine[0]))
    {
        if (chaine[0] != 'X' && chaine[0] != 'R' && chaine[0] != 'S' && chaine[0] != 'W')
        {
            while (!verifierCoordonnees(chaine, &index, &lig, taille))
            {
                printf("Attention, on ne peut pas jouer en dehors du plateau.\n");
                placer(taille, plateau, joueur, tour, droit, mode, Memoire, plateau_verif);
                return;
            }
        }
        else
        {
            if (strlen(chaine) == 1)
            {
                switch (chaine[0])
                {
                case 'X':
                    printf("Au revoir !\n");
                    //    on vide le buffer
                    for (int i = 0; i < taille; i++)
                    {
                        free(plateau[i]);
                        free(plateau_verif[i]);
                    }
                    free(plateau);
                    free(plateau_verif);
                    exit(1);
                    break;
                case 'R':
                    if (*tour >= 2 && mode == 3)
                    {
                        special_enlev(taille, plateau, joueur, Memoire, droit, mode, Memoire, plateau_verif);
                    }
                    else if (mode != 3)
                    {

                        printf("Vous ne pouvez pas jouer de coup speciaux dans ce mode\n");
                        placer(taille, plateau, joueur, tour, droit, mode, Memoire, plateau_verif);
                    }
                    else
                    {
                        printf("Attention, il n'est pas possible d'enlever un piont au premier tour\n");
                        placer(taille, plateau, joueur, tour, droit, mode, Memoire, plateau_verif);
                    }
                    return;
                    break;
                case 'S':
                    sauvegarder(taille, plateau, *tour, *droit, mode, Memoire);
                    placer(taille, plateau, joueur, tour, droit, mode, Memoire, plateau_verif);
                    return;
                    break;
                case 'W':
                    if (mode == 3)
                    {
                        if (joueur == 1)
                        {
                            if (Memoire[0] == 0)
                            {
                                Memoire[0] = 1;
                                placer(taille, plateau, joueur, tour, droit, mode, Memoire, plateau_verif);
                                placer(taille, plateau, joueur, tour, droit, mode, Memoire, plateau_verif);
                                return;
                            }
                            else
                            {
                                printf("Vous ne pouvez jouer ce coup qu'une seule fois par partie.\nC'est toujours au tour du joueur rouge de jouer\n");
                                placer(taille, plateau, joueur, tour, droit, mode, Memoire, plateau_verif);
                                return;
                            }
                        }
                        if (joueur == 0)
                        {
                            if (Memoire[1] == 0)
                            {
                                Memoire[1] = 1;
                                placer(taille, plateau, joueur, tour, droit, mode, Memoire, plateau_verif);
                                placer(taille, plateau, joueur, tour, droit, mode, Memoire, plateau_verif);
                                return;
                            }
                            else
                            {
                                printf("Vous ne pouvez jouer ce coup qu'une seule fois par partie.\nC'est toujours au tour du joueur bleu de jouer\n");
                                placer(taille, plateau, joueur, tour, droit, mode, Memoire, plateau_verif);
                                return;
                            }
                        }
                    }
                    else
                    {
                        printf("Vous ne pouvez pas jouer de coup speciaux dans ce mode\n");
                        placer(taille, plateau, joueur, tour, droit, mode, Memoire, plateau_verif);
                        return;
                    }
                    break;
                default:
                    break;
                }
            }
            else
            {
                printf("Attention, on ne peut pas jouer en dehors du plateau.PP\n");
                placer(taille, plateau, joueur, tour, droit, mode, Memoire, plateau_verif);
                return;
            }
        }
    }
    while (plateau[taille - lig][index] != 'O')
    {
        printf("Attention, case inaccessible\n");
        placer(taille, plateau, joueur, tour, droit, mode, Memoire, plateau_verif);
        return;
    }

    if (joueur == 1)
    {
        plateau[taille - lig][index] = 4;
    }
    else
    {
        plateau[taille - lig][index] = 5;
    }

    affichage(taille, plateau, Memoire);
    return;
}

// Fonction qui permet d'analyser une victoire
int gagner(int taille, char **plateau, int **plateau_verif, int joueur)
{
    int i = 0, j = 0, pion_joueur = 0, a = 0, b = 0;

    for (i = 0; i < taille; i++)
    {
        for (j = 0; j < taille; j++)
        {
            plateau_verif[i][j] = 0;
        }
    }

    if (joueur == 1)
    {
        pion_joueur = 4;
        for (int colonne = 0; colonne < taille; ++colonne)
        {
            if (plateau[taille - 1][colonne] == pion_joueur)
            {
                plateau_verif[0][colonne] = 1;
                a = +1;
            }
        }
        for (i = taille - 2; i >= 0; i--)
        {
            for (j = 0; j < taille; j++)
            {
                if (plateau[i][j] == pion_joueur && plateau_verif[taille - i - 1][j] == 0)
                {
                    if (recherche_mini(plateau_verif, taille, i, j) != 0)
                    {
                        plateau_verif[taille - 1 - i][j] = recherche_mini(plateau_verif, taille, i, j) + 1;
                    }
                }
            }
            for (j = taille - 1; j >= 0; j--)
            {
                if (plateau[i][j] == pion_joueur && plateau_verif[taille - 1 - i][j] == 0)
                {
                    if (recherche_mini(plateau_verif, taille, i, j) != 0)
                    {
                        plateau_verif[taille - 1 - i][j] = recherche_mini(plateau_verif, taille, i, j) + 1;
                    }
                }
            }
        }
        for (j = 0; j < taille; ++j)
        {
            b += plateau_verif[taille - 1][j];
        }
        if (b != 0 && a != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    else if (joueur == 0)
    {
        pion_joueur = 5;
        for (int ligne = 0; ligne < taille; ++ligne)
        {
            if (plateau[taille - ligne - 1][0] == pion_joueur)
            {
                plateau_verif[ligne][0] = 1;
                a += 1;
            }
        }
        for (i = 1; i < taille; i++)
        {
            for (j = taille - 1; j >= 0; j--)
            {
                if (plateau[j][i] == pion_joueur && plateau_verif[taille - 1 - j][i] == 0)
                {
                    if (recherche_mini(plateau_verif, taille, j, i) != 0)
                    {
                        plateau_verif[taille - 1 - j][i] = recherche_mini(plateau_verif, taille, j, i) + 1;
                    }
                }
            }
            for (j = 0; j < taille - 1; j++)
            {
                if (plateau[j][i] == pion_joueur && plateau_verif[taille - 1 - j][i] == 0)
                {
                    if (recherche_mini(plateau_verif, taille, j, i) != 0)
                    {
                        plateau_verif[taille - 1 - j][i] = recherche_mini(plateau_verif, taille, j, i) + 1;
                    }
                }
            }
        }
        for (i = 0; i < taille; ++i)
        {
            b += plateau_verif[i][taille - 1];
        }
        if (b != 0 && a != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

// Cette fonction trouve la valeur minimale dans un tableau donné.
int MIN(int My_array[], int len)
{
    int num = 100;
    for (int i = 0; i < len; i++)
    {
        if (My_array[i] < num && My_array[i] != 0)
        {
            num = My_array[i];
        }
    }
    if (num == 100)
    {
        return 0;
    }
    else
    {
        return num;
    }
}

// Cette fonction recherche la valeur minimale parmi un ensemble d'éléments spécifiques du plateau.
int recherche_mini(int **plateau_verif, int taille, int x, int y)
{
    int min = 0;
    if (x == taille - 1 && y != 0 && y != taille - 1)
    { // haut milieu
        int tableau[] = {plateau_verif[0][y - 1], plateau_verif[0][y + 1], plateau_verif[1][y], plateau_verif[1][y + 1]};
        int len = sizeof(tableau) / sizeof(int);
        for (int i = 0; i < len; ++i)
        {
            min = MIN(tableau, len);
        }
        return min;
    }
    if (x == taille - 1 && y == taille - 1)
    { // haut droit
        int tableau[] = {plateau_verif[0][taille - 2], plateau_verif[1][taille - 1], plateau_verif[1][taille - 2]};
        int len = sizeof(tableau) / sizeof(int);
        for (int i = 0; i < len; ++i)
        {
            min = MIN(tableau, len);
        }
        return min;
    }
    if (x == 0 && y == 0)
    { // bas gauche
        int tableau[] = {plateau_verif[taille - 2][0], plateau_verif[taille - 1][1], plateau_verif[taille - 2][1]};
        int len = sizeof(tableau) / sizeof(int);
        for (int i = 0; i < len; ++i)
        {
            min = MIN(tableau, len);
        }
        return min;
    }
    if (x == 0 && y != 0 && y != taille - 1)
    { // bas milieu
        int tableau[] = {plateau_verif[taille - 1][y - 1], plateau_verif[taille - 1][y + 1], plateau_verif[taille - 2][y], plateau_verif[y][y + 1]};
        int len = sizeof(tableau) / sizeof(int);
        for (int i = 0; i < len; ++i)
        {
            min = MIN(tableau, len);
        }
        return min;
    }
    if (x == 0 && y == taille - 1)
    { // bas droit
        int tableau[] = {plateau_verif[taille - 1][taille - 2], plateau_verif[taille - 2][taille - 1]};
        int len = sizeof(tableau) / sizeof(int);
        for (int i = 0; i < len; ++i)
        {
            min = MIN(tableau, len);
        }
        return min;
    }
    if (x != 0 && x != taille - 1 && y == 0)
    { // milieu gauche
        int tableau[] = {plateau_verif[taille - x][0], plateau_verif[taille - x - 2][0], plateau_verif[taille - x][1], plateau_verif[taille - x - 1][1]};
        int len = sizeof(tableau) / sizeof(int);
        for (int i = 0; i < len; ++i)
        {
            min = MIN(tableau, len);
        }
        return min;
    }
    if (x != 0 && x != taille - 1 && y == taille - 1)
    { // milieu droit
        int tableau[] = {plateau_verif[taille - x][taille - 1], plateau_verif[taille - x - 2][taille - 1], plateau_verif[taille - x - 1][taille - 2], plateau_verif[taille - x - 2][taille - 2]};
        int len = sizeof(tableau) / sizeof(int);
        for (int i = 0; i < len; ++i)
        {
            min = MIN(tableau, len);
        }
        return min;
    }
    if (x != 0 && x != taille - 1 && y != 0 && y != taille - 1)
    { // case milieu
        int tableau[] = {plateau_verif[taille - x - 2][y], plateau_verif[taille - x - 2][y + 1], plateau_verif[taille - x - 1][y + 1], plateau_verif[taille - x][y], plateau_verif[taille - x][y - 1], plateau_verif[taille - x - 1][y - 1]};
        int len = sizeof(tableau) / sizeof(int);
        for (int i = 0; i < len; ++i)
        {
            min = MIN(tableau, len);
        }
        return min;
    }
}