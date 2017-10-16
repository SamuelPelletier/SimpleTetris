#include <stdio.h>
#include <stdlib.h>

#define HAUTEUR 10
#define LARGEUR 15
#define NB_PIECES 10
#define HAUTEUR_MAX_DES_PIECES 4

typedef struct
{
    int hauteur;
    int largeur;
    char* forme[HAUTEUR_MAX_DES_PIECES];
} Piece;

typedef struct
{
    char espace_jeu[HAUTEUR][LARGEUR];
} Grille;

void initialiseGrille(Grille* g);
char lireCase(Grille* g, int ligne, int colonne);
void afficheGrille(Grille* g);
void genererPieces(Piece tabPieces[]);
void affichePiece(Piece* piece);
void ecrireCase(Grille* grille, int ligne, int colonne, char caractere);
int hauteurMax(Grille* grille, int debutIntervalle, int finIntervalle);
void ecrirePiece(Grille* grille, Piece piece, int colonne, int hauteur);
Piece pieceAleatoire(Piece tabPieces[]);
void supprimerLigne(Grille* grille,int ligne);
void nettoyer(Grille* grille);
int hauteurExacte( Grille g, int col_gauche, Piece* piece );

int main()
{
    Grille grille = {};
    Piece tabPieces[NB_PIECES];
    initialiseGrille(&grille);
    genererPieces(tabPieces);

    for(int colonne,nbr_piece_pose = 0; colonne != -1; nbr_piece_pose++)
    {
        Piece piece = pieceAleatoire(tabPieces);
        affichePiece(&piece);
        afficheGrille(&grille);
        printf("Choisissez la colonne ou placer la piece (-1 pour quitter):");
        scanf("%d", &colonne);
        int hauteur_max = hauteurExacte(grille, colonne, &piece);
        if(piece.hauteur + hauteur_max-1 > HAUTEUR-1)
        {
            printf("Vous avez perdu >.<\nNombre de pieces posée: %d\n",nbr_piece_pose);
            initialiseGrille(&grille);
            nbr_piece_pose = -1;
        }
        else
        {
            ecrirePiece(&grille, piece, colonne, hauteur_max);
            nettoyer(&grille);
        }
    }
    return 0;
}

void initialiseGrille(Grille* g)
{
    for(int i=0; i < HAUTEUR; i++)
    {
        for(int j=0; j < LARGEUR; j++)
        {
            g->espace_jeu[i][j] = ' ';
        }
    }
}

char lireCase(Grille* g, int ligne, int colonne)
{
    if((ligne > HAUTEUR) || (colonne > LARGEUR) || (ligne < 0) || (colonne < 0) )
    {
        printf("ERREUR : Parametre hors grille");
    }
    return g->espace_jeu[ligne][colonne];
}

void afficheGrille(Grille* g)
{
    for(int i=HAUTEUR-1; i>=0; i--)
    {
        printf("||");
        for(int j = 0; j < LARGEUR; j++)
        {
            printf("%c",lireCase(g,i,j));
        }
        printf("||\n");
    }
    printf("||");
    for(int k=0; k < LARGEUR; k++)
    {
        printf("|");
    }
    printf("||\n");
    printf("||");
    for(int l=0; l < LARGEUR; l++)
    {
        char print = ' ';
        if(l == 0)
        {
            print = '0';
        }
        else if(l == 10)
        {
            print = '1';
        }
        printf("%c", print);
    }
    printf("||\n\n");
}

void genererPieces(Piece tabPieces[])
{
    tabPieces[0].hauteur = 2;
    tabPieces[0].largeur = 3;
    tabPieces[0].forme[1] = " @ ";
    tabPieces[0].forme[0] = "@@@";

    tabPieces[1].hauteur = 3;
    tabPieces[1].largeur = 2;
    tabPieces[1].forme[2] = "# ";
    tabPieces[1].forme[1] = "# ";
    tabPieces[1].forme[0] = "##";

    tabPieces[2].hauteur = 3;
    tabPieces[2].largeur = 2;
    tabPieces[2].forme[2] = " #";
    tabPieces[2].forme[1] = " #";
    tabPieces[2].forme[0] = "##";

    tabPieces[3].hauteur = 2;
    tabPieces[3].largeur = 3;
    tabPieces[3].forme[1] = "#  ";
    tabPieces[3].forme[0] = "###";

    tabPieces[4].hauteur = 2;
    tabPieces[4].largeur = 3;
    tabPieces[4].forme[1] = "  #";
    tabPieces[4].forme[0] = "###";

    tabPieces[5].hauteur = 4;
    tabPieces[5].largeur = 1;
    tabPieces[5].forme[3] = "l";
    tabPieces[5].forme[2] = "l";
    tabPieces[5].forme[1] = "l";
    tabPieces[5].forme[0] = "l";

    tabPieces[6].hauteur = 1;
    tabPieces[6].largeur = 4;
    tabPieces[6].forme[0] = "OOOO";

    tabPieces[7].hauteur = 2;
    tabPieces[7].largeur = 3;
    tabPieces[7].forme[1] = "XXX";
    tabPieces[7].forme[0] = " X ";

    tabPieces[8].hauteur = 3;
    tabPieces[8].largeur = 2;
    tabPieces[8].forme[2] = "LL";
    tabPieces[8].forme[1] = " L";
    tabPieces[8].forme[0] = " L";

    tabPieces[9].hauteur = 3;
    tabPieces[9].largeur = 2;
    tabPieces[9].forme[2] = "Z ";
    tabPieces[9].forme[1] = "ZZ";
    tabPieces[9].forme[0] = " Z";
}

void affichePiece(Piece* piece)
{
    for(int i=piece->hauteur-1; i>=0; i--)
    {
        printf("%s\n", piece->forme[i]);
    }
    printf("↑\n");
}

void ecrireCase(Grille* grille, int ligne, int colonne, char caractere)
{
    if((ligne > HAUTEUR) || (colonne > LARGEUR) || (ligne < 0) || (colonne < 0) )
    {
        printf("ERREUR : Parametre hors grille");
    }
    if((int)caractere != 32){
        grille->espace_jeu[ligne][colonne] = caractere;
    }
}

int hauteurMax(Grille* grille, int debutIntervalle, int finIntervalle)
{
    int hauteurMax = -1;
    for(int i=debutIntervalle; i < finIntervalle; i++)
    {
        int hauteurMaxTemp = 0;
        for(int j=HAUTEUR-1; j >= 0; j--)
        {

            if((int) lireCase(grille, j, i) != 32) // 32 : Correspond à la valeur espace en numérique
            {
                hauteurMaxTemp = j+1;
                break;
            }
        }
        if(hauteurMaxTemp != 0 && hauteurMax < hauteurMaxTemp)
        {
            hauteurMax = hauteurMaxTemp;
        }
    }
    return hauteurMax;
}

void ecrirePiece(Grille* grille, Piece piece, int colonne, int hauteur)
{
    hauteur = hauteur == -1 ? 0 : hauteur;
    if(piece.largeur + colonne > LARGEUR )
    {
        printf("ERREUR : Piece hors grille");
    }
    else
    {
        for(int i=0; i<piece.largeur; i++)
        {
            for(int j=0; j<piece.hauteur; j++)
            {
                ecrireCase(grille, hauteur+j, colonne+i,piece.forme[j][i]);
            }
        }
    }

}

Piece pieceAleatoire(Piece tabPieces[])
{
    int alea = rand()%NB_PIECES;
    return tabPieces[alea];
}

void supprimerLigne(Grille* grille,int ligne)
{
    for(int i=0; i<HAUTEUR-1; i++)
    {
        for(int j=0; j<LARGEUR; j++)
        {
            if(i == HAUTEUR-1)
            {
                grille->espace_jeu[i][j] = ' ';
            }
            else
            {
                grille->espace_jeu[i][j] = lireCase(grille, i+1, j);
            }
        }
    }
}

void nettoyer(Grille* grille)
{
    int nbr_element = 0;
    for(int i=0; i<HAUTEUR; i++)
    {
        nbr_element = 0;
        for(int j=0; j<LARGEUR; j++)
        {
            if((int)lireCase(grille, i, j) != 32)
            {
                nbr_element++;
            }
        }
        if(nbr_element == LARGEUR)
        {
            supprimerLigne(grille,i);
        }
    }
}

int hauteurExacte(Grille g, int col_gauche, Piece* piece ){
    int hauteurExacte = -1;
    for(int i=col_gauche; i < col_gauche+piece->largeur; i++)
    {
        int hauteurExacteTemp = 0;
        for(int j=HAUTEUR-1; j >= 0; j--)
        {

            if((int) lireCase(&g, j, i) != 32) // 32 : Correspond à la valeur espace en numérique
            {
                hauteurExacteTemp = j+1;
                break;
            }
        }
        if(hauteurExacteTemp != 0 && hauteurExacte < hauteurExacteTemp)
        {
            if((int)piece->forme[0][0] == 32 && (int) lireCase(&g, hauteurExacteTemp-1, col_gauche+1) == 32){
                hauteurExacteTemp--;
                if((int)piece->forme[1][0] == 32 && hauteurExacteTemp >= 2 && (int) lireCase(&g, hauteurExacteTemp-2, col_gauche+1) == 32){
                    hauteurExacteTemp--;
                }
            }
            hauteurExacte = hauteurExacteTemp;
        }
    }
    return hauteurExacte;
}
