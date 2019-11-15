#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TAILLE 3
#define REMPLISSAGE ' '
#define ROND 'O'
#define CROIX 'X'

//Prototypes
void InitialisationGrilleMorpion(char c_GrilleMorpion[TAILLE][TAILLE], char c_Remplissage);
void AffichageGrilleMorpion (char c_GrilleMorpion[TAILLE][TAILLE]);
void GestionDuTourDuJoueur(int n_BoolJ1,char c_GrilleMorpion[TAILLE][TAILLE]);
int ConditionDeVictoire(char c_GrilleMorpion[TAILLE][TAILLE]);

int main()
{
    char c_GrilleMorpion[TAILLE][TAILLE];

    InitialisationGrilleMorpion(c_GrilleMorpion,REMPLISSAGE);

    int n_BoolJ1=1;
    int n_BoolFinDuJeu=0;
    int n_Resultat=0;

    AffichageGrilleMorpion(c_GrilleMorpion);

    while (n_BoolFinDuJeu==0)
    {
        GestionDuTourDuJoueur(n_BoolJ1,c_GrilleMorpion);
        n_Resultat=ConditionDeVictoire(c_GrilleMorpion);
        AffichageGrilleMorpion(c_GrilleMorpion);
        if (n_Resultat==1)
        {
            //Seul le joueur qui vient de joué peut avoir gagné.
            if (n_BoolJ1==1)
            {
                printf("Le Joueur 1 a gagne !");
            }
            else
            {
                printf("Le Joueur 2 a gagne !");
            }
            n_BoolFinDuJeu=1;
        }
        else if (n_Resultat==2)
        {
            printf("Plus de coups possibles c'est une egalite.");
            n_BoolFinDuJeu=1;
        }
        else
        {
            n_BoolJ1= -n_BoolJ1;
        }
    }
    return 0;
}


void InitialisationGrilleMorpion(char c_GrilleMorpion[TAILLE][TAILLE], char c_Remplissage)
//BUT : Initialiser la grille du Morpion.
//ENTREE : La grille à initialiser et le caractère de remplissage.
//SORTIE : La grille initialisée.
{
    int n_I, n_J;
    for (n_I=0; n_I<TAILLE; n_I++)
	{
		for (n_J=0; n_J<TAILLE; n_J++)
		{
			c_GrilleMorpion[n_I][n_J] = REMPLISSAGE;
		}
	}
}

void AffichageGrilleMorpion (char c_GrilleMorpion[TAILLE][TAILLE])
//BUT : Afficher la grille du morpion.
//ENTREE : La grille du morpion.
//SORTIE : La grille du morpion affichée.
{
    int n_I, n_J;
    printf("     1   2   3\n");
    for (n_I=0; n_I<TAILLE; n_I++)
	{
	    printf("   _____________");
	    printf("\n %d ",n_I+1);
		for (n_J=0; n_J<TAILLE; n_J++)
		{
		    printf("|");
			printf("%3c",c_GrilleMorpion[n_I][n_J]);
		}
		printf("|");
		printf("\n");
	}
	printf("   _____________\n");
}

void GestionDuTourDuJoueur(int n_BoolJ1,char c_GrilleMorpion[TAILLE][TAILLE])
//BUT : Gérer le tour d'un joueur.
//ENTREE : La coordonnée où mettre la marque du joueur.
//SORTIE : Le tableau du Morpion avancé et les conditions de victoire.
{
    char c_CaractereDuJoueur;
    if (n_BoolJ1==1)
    {
        c_CaractereDuJoueur=CROIX;
        printf("Joueur 1 v");
    }
    else
    {
        c_CaractereDuJoueur=ROND;
        printf("Joueur 2 v");
    }
    int n_BoolEntreeValide=0;

    while (n_BoolEntreeValide==0)
    {
        printf("euillez entrer les coordonnees de la case dans laquelle vous souhaitez entrer votre %c.\nSous la forme XY.\n",c_CaractereDuJoueur);
        int n_Coordonnees;
        scanf("%d",&n_Coordonnees);
        fflush(stdin);
        if ((n_Coordonnees>10 && n_Coordonnees<14)||(n_Coordonnees>20 && n_Coordonnees<24)||(n_Coordonnees>30 && n_Coordonnees<34))
        {
            int n_XMorpion = n_Coordonnees%10;
            int n_YMorpion = n_Coordonnees/10;
            if(c_GrilleMorpion[n_XMorpion-1][n_YMorpion-1]==REMPLISSAGE)
            {
            	c_GrilleMorpion[n_XMorpion-1][n_YMorpion-1]=c_CaractereDuJoueur;
            	n_BoolEntreeValide=1;
            }
            else
            {
                printf("Entree invalide, cette case est deja prise. V");
            }
        }
        else
        {
            printf("Entree invalide. V");
        }
    }
}

int ConditionDeVictoire(char c_GrilleMorpion[TAILLE][TAILLE])
//BUT : Définir si la partie est terminée ou non.
//ENTREE : La grille du morpion après une action d'un joueur.
//SORTIE : 0 si la partie n'est pas finit, 1 si on a un gagnant, 2 si c'est une égalité.
{
    //On vérifie les colonnes
    if (((c_GrilleMorpion[0][0]==c_GrilleMorpion[0][1])&&(c_GrilleMorpion[0][0]==c_GrilleMorpion[0][2])&&(c_GrilleMorpion[0][0]!=REMPLISSAGE)) || ((c_GrilleMorpion[1][0]==c_GrilleMorpion[1][1])&&(c_GrilleMorpion[1][0]==c_GrilleMorpion[1][2])&&(c_GrilleMorpion[1][0]!=REMPLISSAGE)) || ((c_GrilleMorpion[2][0]==c_GrilleMorpion[2][1])&&(c_GrilleMorpion[2][0]==c_GrilleMorpion[2][2])&&(c_GrilleMorpion[2][0]!=REMPLISSAGE)))
    {
        //Nous avons un gagnant, on retourne 1.
        return 1;
    }
    //On vérifie les lignes.
    else if (((c_GrilleMorpion[0][0]==c_GrilleMorpion[1][0])&&(c_GrilleMorpion[0][0]==c_GrilleMorpion[2][0])&&(c_GrilleMorpion[0][0]!=REMPLISSAGE)) || ((c_GrilleMorpion[0][1]==c_GrilleMorpion[1][1])&&(c_GrilleMorpion[0][1]==c_GrilleMorpion[2][1])&&(c_GrilleMorpion[0][1]!=REMPLISSAGE)) || ((c_GrilleMorpion[0][2]==c_GrilleMorpion[1][2])&&(c_GrilleMorpion[0][2]==c_GrilleMorpion[2][2])&&(c_GrilleMorpion[0][2]!=REMPLISSAGE)))
    {
        //Nous avons un gagnant, on retourne 1.
        return 1;
    }
    //On vérifie les diagonales.
    else if (((c_GrilleMorpion[0][0]==c_GrilleMorpion[1][1])&&(c_GrilleMorpion[0][0]==c_GrilleMorpion[2][2])&&(c_GrilleMorpion[0][0]!=REMPLISSAGE)) || ((c_GrilleMorpion[2][0]==c_GrilleMorpion[1][1])&&(c_GrilleMorpion[2][0]==c_GrilleMorpion[0][2])&&(c_GrilleMorpion[2][0]!=REMPLISSAGE)))
    {
        //Nous avons un gagnant, on retourne 1.
        return 1;
    }
    else
    {
        //Si nous n'avons pas de vainqueur on vérifie si la grille est pleine.
        int n_BoolFin=1;//De base on dit que c'est la fin et si une case est vide, ce n'est pas la fin.
        int n_I=0;
        int n_J=0;
        for (n_I=0;n_I<TAILLE;n_I++)
        {
            for (n_J=0;n_J<TAILLE;n_J++)
            {
                if (c_GrilleMorpion[n_I][n_J]==REMPLISSAGE)
                {
                    n_BoolFin=0;
                }
            }
        }
        if (n_BoolFin==1)
        {
            //Si c'est la fin ici, c'est une égalité.
            return 2;
        }
    }
    //Si on est arrivé jusque là on continue, la partie n'est pas finie.
    return 0;
}
