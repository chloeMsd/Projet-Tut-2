#include "instance.h"
#include <stdio.h>


void afficherListe(int* liste, int taille)
{
    printf("[");

    for (int i = 0; i < taille-1; i++)
    {
        if (liste[i] == taille-1) printf("%d]", liste[i]);
        else printf("%d, ", liste[i]);
    }
}

//entrée :      instance dont on doit trier les éléments
//sortie :      une liste triée de taille N dont chaque valeur représente l'indice d'un objet
int* ordonancementAleatoire(struct Instance* instance)
{
    int* indices = malloc(sizeof(int)*instance->N);

    for (int i = 0; i < instance->N-1; i++)
    {
        indices[i] = i;
    }

    printf("liste d'indices initiale : ["); 
    afficherListe(indices, instance->N);

    for (int i = 0; i < instance->N-1; i++)
    {
        int j = rand() % (instance->N-i) + i;
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    printf("liste d'indices triés aléatoirement : ["); 
    afficherListe(indices, instance->N);

    return indices;
}
