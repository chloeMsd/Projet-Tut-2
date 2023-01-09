#include "instance.h"
#include <stdio.h>


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

int valeurDimensionCritique(struct Instance* instance)
{
    int dimCritique = instance->b[0];

    for (size_t i = 1; i < instance->M; i++)
    {
        if (instance->b[i] < dimCritique)
        {
            dimCritique = instance->b[i];
        }
    }
    
    return dimCritique;
}

float ratioValeurPoids(struct Instance* instance, int indice)
{
    return (float) instance->p[indice] / (float) sommePoids(instance, indice);
}

float ratioValeurDimension(struct Instance* instance, int indice)
{
    return (float) instance->p[indice] / (float) valeurDimensionCritique(instance);
}

//METHODE NUMERO 1
//entrée :      instance dont on doit trier les éléments
//sortie :      une liste triée de taille N dont chaque valeur représente l'indice d'un objet
int* ordonancementAleatoire(struct Instance* instance)
{
    printf("\n\n--ordonancementAleatoire--");    

    int* indices = malloc(sizeof(int)*instance->N);

    for (int i = 0; i < instance->N; i++)
    {
        indices[i] = i;
    }

    printf("\n\nliste d'indices initiale : ["); 
    afficherListeInt(indices, instance->N);

    for (int i = 0; i < instance->N-1; i++)
    {
        int j = rand() % (instance->N-i) + i;
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    printf("\n\nliste d'indices triés aléatoirement : ["); 
    afficherListeInt(indices, instance->N);

    return indices;
}


//METHODE NUMERO 2
//entrée :      instance dont on doit trier les éléments
//sortie :      une liste triée de taille N dont chaque valeur représente l'indice d'un objet
int* ordonancementValeursDecroissantes(struct Instance* instance)
{
    printf("\n\n--ordonancementValeursDecroissantes--");     

    int* indices = malloc(sizeof(int)*instance->N);

    //on créé une liste de N indices de 0 à N-1
    for (int i = 0; i < instance->N; i++)
    {
        indices[i] = i;
    }

    printf("\n\nliste d'indices initiale : ["); 
    afficherListeInt(indices, instance->N);

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

    printf("\n\nliste d'indices triés selon leur valeur : ["); 
    afficherListeInt(indices, instance->N);

    int* listeValeurs = malloc(sizeof(int)*instance->N);

    for (size_t i = 0; i < instance->N; i++)
    {
        listeValeurs[i] = instance->p[indices[i]];
    }
    
    printf("\n\nliste des valeurs selon les indices triés selon leur valeur : ["); 
    afficherListeInt(listeValeurs, instance->N);


    return indices;
}



//METHODE NUMERO 3
//entrée :      instance dont on doit trier les éléments
//sortie :      une liste triée de taille N dont chaque valeur représente l'indice d'un objet
int* ordonancementRatioValeursPoids(struct Instance* instance)
{
    printf("\n\n--ordonancementRatioValeursPoids--");     

    int* indices = malloc(sizeof(int)*instance->N);

    //on créé une liste de N indices de 0 à N-1
    for (int i = 0; i < instance->N; i++)
    {
        indices[i] = i;
    }

    printf("\n\nliste d'indices initiale : ["); 
    afficherListeInt(indices, instance->N);

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

    printf("\n\nliste d'indices triés selon leur ratio : ["); 
    afficherListeInt(indices, instance->N);

    float* listeValeurs = malloc(sizeof(float)*instance->N);

    for (size_t i = 0; i < instance->N; i++)
    {
        listeValeurs[i] = ratioValeurPoids(instance, indices[i]);
    }
    
    printf("\n\nliste des ratios selon les indices triés selon leur ratio : ["); 
    afficherListeFloat(listeValeurs, instance->N);


    return indices;
}



//METHODE NUMERO 4
//entrée :      instance dont on doit trier les éléments
//sortie :      une liste triée de taille N dont chaque valeur représente l'indice d'un objet
int* ordonancementRatioValeursDimensionCritique(struct Instance* instance)
{
    printf("\n\n--ordonancementRatioValeursDimensionCritique--");     

    int* indices = malloc(sizeof(int)*instance->N);

    //on créé une liste de N indices de 0 à N-1
    for (int i = 0; i < instance->N; i++)
    {
        indices[i] = i;
    }

    printf("\n\nliste d'indices initiale : ["); 
    afficherListeInt(indices, instance->N);

    float valeurMax = 0;
    int indiceMax = 0;
    int tmp = 0;

    for (int compteur = 0; compteur < instance->N; compteur++)
    {
        //on récupère le ratio correspondant à l'indice à la position compteur
        valeurMax = ratioValeurDimension(instance, indices[compteur]);
        //on initialise l'indice correspondant à la valeur maximale
        indiceMax = compteur;

        for (int i = compteur+1; i < instance->N ; i++)
        {
            if (ratioValeurDimension(instance, indices[i]) >= valeurMax) 
            {
                valeurMax = ratioValeurDimension(instance, indices[i]);
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

    printf("\n\nliste d'indices triés selon leur ratio : ["); 
    afficherListeInt(indices, instance->N);

    float* listeValeurs = malloc(sizeof(float)*instance->N);

    for (size_t i = 0; i < instance->N; i++)
    {
        listeValeurs[i] = ratioValeurDimension(instance, indices[i]);
    }
    
    printf("\n\nliste des ratios selon les indices triés selon leur ratio : ["); (listeValeurs, instance->N);


    return indices;
}

int* solutionHeuristique(struct Instance* instance, int methode)
{
    int* indicesSolution;

    switch (methode)
    {
    case 1:
        indicesSolution = ordonancementAleatoire(instance);
        break;
    case 2:
        indicesSolution = ordonancementValeursDecroissantes(instance);
        break;
    case 3:
        indicesSolution = ordonancementRatioValeursPoids(instance);
        break;
    case 4:
        indicesSolution = ordonancementRatioValeursDimensionCritique(instance);
        break;
    
    default:
        break;
    }

    //on créé une liste de N valeurs à 0
    int* solutionDirecte = malloc(sizeof(int)*instance->N);
    for (int i = 0; i < instance->N; i++)
    {
        solutionDirecte[i] = 0;
    }

    printf("\n\nsolution heuristique initiale :");
    afficherListeInt(solutionDirecte,instance->N);

    for (size_t compteur = 0; compteur < instance->N; compteur++)
    {
        solutionDirecte[indicesSolution[compteur]] = 1;

        if(SolutionTestFaisabilite(instance, solutionDirecte) == 1)
        {
            solutionDirecte[indicesSolution[compteur]] = 0;
        }
    }

    printf("\n\nsolution heuristique :");
    afficherListeInt(solutionDirecte,instance->N);

    
    printf("\n\nindices des solutions :");
    afficherListeInt(indicesSolution,instance->N);

    return solutionDirecte;
}