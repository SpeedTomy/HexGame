#include<Bibliotheque.h>

// Fonction permettant de créer une matrice d'adjacence//
void init_board(int n, int board[n][n]) 
    {
        int i, j;
        for (i = 0; i < n; i++) 
        {
            for (j = 0; j < n; j++) 
            {
                // initialiser la matrice d'adjacence pour chaque hexagone
                if (i == 0 || j == 0 || i == n - 1 || j == n - 1) 
                {
                    // si l'hexagone est sur le bord du plateau, le marquer comme connecté à la bordure
                    board[i][j] = -1;
                } else 
                {
                    // sinon, le marquer comme non connecté
                    board[i][j] = 0;
                }
            }
        }
    }