#include "instance.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//retourne la somme des poids de l'élément de l'instance à l'indice donné
int sommePoids(struct Instance* instance, int indice)
{
    int somme = 0;

    for (size_t dimension = 0; dimension < instance->M; dimension++)
    {
        somme += instance->r[dimension][indice];
    }

    return somme;
}

//entree :  l'instance
//          la solution
//sortie :  la dimension de l'instance qui a le moins de place
int valeurDimensionCritique(struct Instance* instance, int* solution)
{
    int* poids = SolutionCalculDimension(instance, solution);
    int dimCritique = instance->b[0]-poids[0];

    for (size_t i = 1; i < instance->M; i++)
    {
        afficherPoidsSolutionSac(instance, solution);
        
        if (instance->b[i]-poids[i] < dimCritique)
        {
            dimCritique = instance->b[i];
        }
    }
    
    printf("dimension critique : %d", dimCritique);
    return dimCritique;
}

float ratioValeurPoids(struct Instance* instance, int indice)
{
    return (float) instance->p[indice] / (float) sommePoids(instance, indice);
}

float ratioValeurDimension(struct Instance* instance, int* solution, int indice)
{
    return (float) instance->p[indice] / (float) valeurDimensionCritique(instance, solution);
}

int* nouveauTableauDeValeursNulles(int taille)
{
    int* indices = malloc(sizeof(int)*taille);

    //on créé une liste de N indices de 0 à N-1
    for (int i = 0; i < taille; i++)
    {
        indices[i] = i;
    }

    return indices;
}

//METHODE NUMERO 1
//entrée :      instance dont on doit trier les éléments
//sortie :      une liste triée de taille N dont chaque valeur représente l'indice d'un objet
int* ordonancementAleatoire(struct Instance* instance)
{
    int* indices = nouveauTableauDeValeursNulles(instance->N);

    for (int i = 0; i < instance->N-1; i++)
    {
        srand(time(0)); 

        int j = rand() % (instance->N-i) + i;
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    return indices;
}


//METHODE NUMERO 2
//entrée :      instance dont on doit trier les éléments
//sortie :      une liste triée de taille N dont chaque valeur représente l'indice d'un objet
int* ordonancementValeursDecroissantes(struct Instance* instance)
{
    int* indices = nouveauTableauDeValeursNulles(instance->N);

    int valeurMax = 0;
    int indiceMax = 0;
    int tmp = 0;

    for (int compteur = 0; compteur < instance->N; compteur++)
    {
        //on récupère la valeur correspondant à l'indice à la position compteur
        valeurMax = instance->p[indices[compteur]];
        //on initialise l'indice correspondant à la valeur maximale
        indiceMax = compteur;

        for (int i = compteur+1; i < instance->N ; i++)
        {
            if (instance->p[indices[i]] >= valeurMax) 
            {
                valeurMax = instance->p[indices[i]];
                indiceMax = i;
            }
        }

        //si on a trouvé une valeur supérieure, on échange les positions des deux indices
        if (indiceMax != compteur)
        {
            tmp = indices[compteur];
            indices[compteur] = indices[indiceMax];
            indices[indiceMax] = tmp;
        }
    }

    int* listeValeurs = malloc(sizeof(int)*instance->N);

    for (size_t i = 0; i < instance->N; i++)
    {
        listeValeurs[i] = instance->p[indices[i]];
    }
    
    return indices;
}



//METHODE NUMERO 3
//entrée :      instance dont on doit trier les éléments
//sortie :      une liste triée de taille N dont chaque valeur représente l'indice d'un objet
int* ordonancementRatioValeursPoids(struct Instance* instance)
{
    int* indices = nouveauTableauDeValeursNulles(instance->N);

    float valeurMax = 0;
    int indiceMax = 0;
    int tmp = 0;

    for (int compteur = 0; compteur < instance->N; compteur++)
    {
        //on récupère le ratio correspondant à l'indice à la position compteur
        valeurMax = ratioValeurPoids(instance, indices[compteur]);
        //on initialise l'indice correspondant à la valeur maximale
        indiceMax = compteur;

        for (int i = compteur+1; i < instance->N ; i++)
        {
            if (ratioValeurPoids(instance, indices[i]) >= valeurMax) 
            {
                valeurMax = ratioValeurPoids(instance, indices[i]);
                indiceMax = i;
            }
        }

        //si on a trouvé une valeur supérieure, on échange les positions des deux indices
        if (indiceMax != compteur)
        {
            tmp = indices[compteur];
            indices[compteur] = indices[indiceMax];
            indices[indiceMax] = tmp;
        }
    }

    float* listeValeurs = malloc(sizeof(float)*instance->N);

    for (size_t i = 0; i < instance->N; i++)
    {
        listeValeurs[i] = ratioValeurPoids(instance, indices[i]);
    }
    
    return indices;
}



//METHODE NUMERO 4
//entrée :      instance dont on doit trier les éléments, la solution actuelle
//sortie :      une liste triée de taille N dont chaque valeur représente l'indice d'un objet
int* ordonancementRatioValeursDimensionCritique(struct Instance* instance, int* solution)
{
    int* indices = nouveauTableauDeValeursNulles(instance->N);

    float valeurMax = 0;
    int indiceMax = 0;
    int tmp = 0;

    for (int compteur = 0; compteur < instance->N; compteur++)
    {
        //on récupère le ratio correspondant à l'indice à la position compteur
        valeurMax = ratioValeurDimension(instance, solution, indices[compteur]);
        //on initialise l'indice correspondant à la valeur maximale
        indiceMax = compteur;

        for (int i = compteur+1; i < instance->N ; i++)
        {
            if (ratioValeurDimension(instance, solution, indices[i]) >= valeurMax) 
            {
                valeurMax = ratioValeurDimension(instance, solution, indices[i]);
                indiceMax = i;
            }
        }

        //si on a trouvé une valeur supérieure, on échange les positions des deux indices
        if (indiceMax != compteur)
        {
            tmp = indices[compteur];
            indices[compteur] = indices[indiceMax];
            indices[indiceMax] = tmp;
        }
    }

    float* listeValeurs = malloc(sizeof(float)*instance->N);

    for (size_t i = 0; i < instance->N; i++)
    {
        listeValeurs[i] = ratioValeurDimension(instance, solution, indices[i]);
    }
    
    return indices;
}

int* triSelonMethode(struct Instance* instance, int* solution, int methode)
{
    int* liste;

    switch (methode)
    {
    case 1:
        liste = ordonancementAleatoire(instance);
        break;
    case 2:
        liste = ordonancementValeursDecroissantes(instance);
        break;
    case 3:
        liste = ordonancementRatioValeursPoids(instance);
        break;
    case 4:
        liste = ordonancementRatioValeursDimensionCritique(instance, solution);
        break;
    case 5:
        liste = ordonancementRatioValeursDimensionCritique(instance, solution);
        break;
    
    default:
        break;
    }
}

int* solutionHeuristique(struct Instance* instance, int methode, int dynamique)
{
    //on créé un tableau de N valeurs initialisées à 0
    int* solutionDirecte = malloc(sizeof(int)*instance->N);
    for (int i = 0; i < instance->N; i++)
    {
        solutionDirecte[i] = 0;
    }

    //on trie les indices
    int* indicesSolution = triSelonMethode(instance, solutionDirecte, methode);

    for (size_t compteur = 0; compteur < instance->N; compteur++)
    {
        //statique
        if (dynamique == 0)
        {
            solutionDirecte[indicesSolution[compteur]] = 1;

            if(SolutionTestFaisabilite(instance, solutionDirecte) == 1)
            {
                solutionDirecte[indicesSolution[compteur]] = 0;
            }
        }
        //dynamique
        else
        {
            //tant que l'élément est dans la liste, on regarde l'élément suivant
            int i = compteur;
            while (solutionDirecte[indicesSolution[i]]==1 && i<instance->N){i++;}
            
            solutionDirecte[indicesSolution[i]] = 1;

            if(SolutionTestFaisabilite(instance, solutionDirecte) == 1)
            {
                solutionDirecte[indicesSolution[i]] = 0;
            }
            //on trie les indices à la fin de chaque itération
            indicesSolution = triSelonMethode(instance, solutionDirecte, methode);
        }
    }
    
    return solutionDirecte;
}