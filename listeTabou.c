#include <stdio.h>
#include <stdlib.h>
#include "listeTabou.h"

//initialise la liste tabou donnée en paramètre
void ListeTabouInit(struct ListeTabou* listeTabou, int nb_objets)
{
    listeTabou->N = nb_objets;
    listeTabou->dernier = 0;
    listeTabou->liste = malloc(listeTabou->N*sizeof(int)*2);
}

//supprime le plus vieil élément de la liste
void supprimerElementListeTabou(struct ListeTabou* listeTabou)
{
	if (listeTabou->dernier != 0)
    {
        listeTabou->dernier--;
    }
}

//ajoute un nouveau mouvement à la liste
void ajouterMouvementListeTabou(struct ListeTabou* listeTabou, int element0, int element1)
{
    if (!listeTabouPleine(listeTabou))
    {
        int mouvement[2] = {element0, element1};

        listeTabou->liste[listeTabou->dernier] = mouvement;
        listeTabou->dernier++;
    }
}

//renvoie 0 si la liste est pleine
int listeTabouPleine(struct ListeTabou* listeTabou)
{
    if (listeTabou->dernier == listeTabou->N) return 0;
    else return 1;
}

//retourne 0 si le mouvement est dans la liste
int mouvementDansListeTabou(struct ListeTabou* listeTabou, int element0, int element1)
{
    int trouve = 1;
    int i = 0;

    while (trouve == 1 && i < listeTabou->dernier)
    {
        if(listeTabou->liste[i][0] == element0 && listeTabou->liste[i][1] == element1)
        {
            trouve = 0;
        }

        i++;
    }
    
	return trouve;
}
