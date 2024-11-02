#include "hex.c"

int main()
{
    // Declaration objet
    int SIZE = 0, i = 0, j = 0, jeu = 0, joueur = 0, gagne = 0, d1 = 0, d = 0, rep3 = 0, mode = 0, loop = 1, **plateau_verif = NULL;
    char rep1 = 0, rep2 = 0;
    char **plateau = NULL;
    bool erreur = false;
    // Tableau qui va gérer la mémoire
    int Memoire[10] = {0};
    // case 0 : coup w jouable pour joueur 1, case 1: coup w jouable pour joeur 2
    // case 2 : coup r jouable pour joueur 1, case 3 : coup r jouable pour joueur 2
    // case 4 et 5 : ligne et colonne de la case de r pour joueur 1
    // case 6 et 7 : Ligne et colonne de la case de r pour joueur 2
    // case 8 : compteur de r pour joueur 1, case 9 : compteur de r pour joueur 2

    // Le programme tourne tant que le joueur n'a pas quitté le menu
    do
    {
        printf("\n\nBienvenu sur le jeu Hex\n\nQue voulez vous faire?\n - 1 Nouvelle partie\n - 2 Reprendre partie\n - 3 Quitter\n");

        // On demande ce que le joueur veut faire
        do
        {
            printf("Selectionnez votre reponse en entrant 1,2 ou 3.\n");
            if (scanf("%d", &rep3) != 1)
            {
                printf("Erreur : Veuillez entrer un entier.\n");

                // Vider le flux d'entrée
                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
            }
            else if (rep3 < 1 || rep3 > 3)
            {
                printf("Erreur : La taille doit etre comprise entre 1 et 3.\n");
            }
        } while (rep3 < 1 || rep3 > 3);
        do
        {
            // Le programme suit le choix du joueur
            if (rep3 == 1)
            {
                printf("\n Quel mode voulez vous choisir ?\n\n - 1 Standard\n - 2 Aleatoire\n - 3 Coups speciaux\n");

                // On demande le mode de jeu
                do
                {
                    printf("Selectionnez votre reponse en entrant 1,2 ou 3.\n");
                    if (scanf("%d", &mode) != 1)
                    {
                        printf("Erreur : Veuillez entrer un entier.\n");

                        // Vider le flux d'entrée
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF)
                            ;
                    }
                    else if (mode < 1 || mode > 3)
                    {
                        printf("Erreur : La taille doit etre comprise entre 1 et 3.\n");
                    }
                } while (mode < 1 || mode > 3);

                // On demande la taille du plateau de jeu
                do
                {
                    printf("Selectionnez la dimension du plateau de jeu en entrant un entier compris entre 9 et 14\n");
                    if (scanf("%d", &SIZE) != 1)
                    {
                        printf("Erreur : Veuillez entrer un entier.\n");

                        // Vider le flux d'entrée
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF)
                            ;
                    }
                    else if (SIZE < 9 || SIZE > 14)
                    {
                        printf("Erreur : La taille doit etre comprise entre 9 et 14.\n");
                    }
                } while (SIZE < 9 || SIZE > 14);

                // On créer le plateau de jeu
                plateau = (char **)malloc(sizeof(char *) * SIZE);
                for (i = 0; i < SIZE; i++)
                {
                    plateau[i] = (char *)malloc(sizeof(char) * SIZE);
                }

                // On créer le tableau de verification qui va servir pour la fonction gagner
                plateau_verif = (int **)malloc(sizeof(int *) * SIZE);
                for (i = 0; i < SIZE; i++)
                {
                    plateau_verif[i] = (int *)malloc(sizeof(int) * SIZE);
                }
                // On initialise le plateau dépendant de si le mode est aléatoire ou non
                if (mode == 1 || mode == 3)
                {
                    initier(SIZE, plateau, 1);
                }

                else if (mode == 2)
                {
                    initier(SIZE, plateau, 2);
                }
            }
            else if (rep3 == 2)
            {

                charger(&SIZE, &plateau, &d, &d1, &mode, Memoire);
                // On créer le tableau de verification qui va servir pour la fonction gagner
                plateau_verif = (int **)malloc(sizeof(int *) * SIZE);
                for (i = 0; i < SIZE; i++)
                {
                    plateau_verif[i] = (int *)malloc(sizeof(int) * SIZE);
                }
                gagne = gagner(SIZE, plateau, plateau_verif, 1);
                if (gagne)
                {
                    affichage(SIZE, plateau, Memoire);
                    printf("C'etait Rouge qui avait gagne\n");
                    gagne = 0;
                    d1 = 0;
                    d = 0;
                    mode = 0;
                    SIZE = 0;
                    rep3 = 0;
                    break;
                }
                else
                {
                    gagne = gagner(SIZE, plateau, plateau_verif, 0);
                    if (gagne)
                    {
                        affichage(SIZE, plateau, Memoire);
                        printf("C'etait Bleu qui avait gagne\n");
                        gagne = 0;
                        d1 = 0;
                        d = 0;
                        mode = 0;
                        SIZE = 0;
                        rep3 = 0;
                        break;
                    }
                }
            }
            else if (rep3 == 3)
            {
                printf("Au revoir !\n");
                return 1;
            }

            affichage(SIZE, plateau, Memoire);

            // Le jeu tourne tant qu'un joueur n'a pas gagné
            while (gagne == 0)
            {
                d1 = 2 * ((d + 1) / 2);
                if (d1 == d)
                {
                    // permet au joueur 1 de jouer sur le plateau
                    printf("C'est au joueur rouge de jouer\n");
                    placer(SIZE, plateau, 1, &d, &d1, mode, Memoire, plateau_verif);
                    gagne = gagner(SIZE, plateau, plateau_verif, 1);
                    if (gagne)
                    {
                        printf("Felicitation Rouge, vous avez gagne\n");
                    }
                }
                else
                {
                    // permet au joueur 0 de jouer sur le plateau
                    printf("C'est au joueur bleu de jouer\n");
                    placer(SIZE, plateau, 0, &d, &d1, mode, Memoire, plateau_verif);
                    gagne = gagner(SIZE, plateau, plateau_verif, 0);
                    if (gagne)
                    {
                        printf("Felicitation Rouge, vous avez gagne\n");
                    }
                }
                d = d + 1;
                if (Memoire[8] > 0)
                {
                    Memoire[8] -= 1;
                }
                if (Memoire[9] > 0)
                {
                    Memoire[9] -= 1;
                }
            }

            // Si un joueur a gagné, on demande si ils veulent sauvegarder et s'ils veulent rejouer
            if (gagne == 1)
            {
                // On demande au joueur s'il veut sauvegarder
                do
                {
                    if (!erreur)
                    {
                        printf("Voulez-vous sauvegarder la partie? (Y/N): ");
                    }
                    if (scanf(" %c", &rep2) != 1 || getchar() != '\n')
                    {
                        printf("Erreur : Veuillez entrer un seul caractere.\n");
                        erreur = true;

                        // Vider le flux d'entrée
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF)
                            ;
                    }
                    else if (rep2 != 'Y' && rep2 != 'N' && rep2 != 'n' && rep2 != 'y')
                    {
                        printf("Erreur : Veuillez entrer uniquement 'Y' ou 'N'.\n");
                        erreur = true;
                    }
                    else
                    {
                        erreur = false;
                    }
                } while (erreur);

                if (rep2 == 'Y')
                {
                    sauvegarder(SIZE, plateau, d, d1, mode, Memoire);
                }
                // On demande s'il veut rejouer au jeu
                do
                {
                    if (!erreur)
                    {
                        printf("Voulez vous rejouer au jeu? Y ou N\n");
                        ;
                    }
                    if (scanf(" %c", &rep1) != 1 || getchar() != '\n')
                    {
                        printf("Erreur : Veuillez entrer un seul caractere.\n");
                        erreur = true;

                        // Vider le flux d'entrée
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF)
                            ;
                    }
                    else if (rep1 != 'Y' && rep1 != 'N' && rep1 != 'n' && rep1 != 'y')
                    {
                        printf("Erreur : Veuillez entrer uniquement 'Y' ou 'N'.\n");
                        erreur = true;
                    }
                    else
                    {
                        erreur = false;
                    }
                } while (erreur);

                gagne = 0;
                d1 = 0;
                d = 0;
                mode = 0;
                SIZE = 0;
                rep3 = 1;
                if (rep1 == 'Y')
                {
                    jeu = 0;
                }
                else
                {
                    jeu = 1;
                    //    on vide le buffer
                    for (i = 0; i < SIZE; i++)
                    {
                        free(plateau[i]);
                        free(plateau_verif[i]);
                    }
                    free(plateau);
                    free(plateau_verif);
                }
            }
        } while (jeu == 0);
    } while (loop);

    return 0;
}
