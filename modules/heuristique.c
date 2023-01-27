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

//retourne la dimension de l'instance qui a le moins de place
int valeurDimensionCritique(struct Instance* instance, int* solution)
{
    int* poids = SolutionCalculDimension(instance, solution);
    int dimCritique = instance->b[0]-poids[0];

    for (size_t i = 1; i < instance->M; i++)
    {
        if (instance->b[i]-poids[i] < dimCritique)
        {
            dimCritique = instance->b[i];
        }
    }
    
    return dimCritique;
}

//retourne le ratio entre la valeur d'un objet de l'instance et la somme des poids de l'instance
float ratioValeurPoids(struct Instance* instance, int indice)
{
    return (float) instance->p[indice] / (float) sommePoids(instance, indice);
}

//retourne le ratio entre la valeur d'un objet de l'instance et la valeur de la dimension critique
float ratioValeurDimension(struct Instance* instance, int* solution, int indice)
{
    return (float) instance->p[indice] / (float) valeurDimensionCritique(instance, solution);
}

//retourne un tableau de valeurs nulles
int* nouveauTableauDeValeursNulles(int taille)
{
    int* indices = malloc(sizeof(int)*taille);

    //on créé une liste de N indices de 0 à N-1
    for (int i = 0; i < taille; i++)
    {
        indices[i] = 0;
    }

    return indices;
}

//retourne un tableau de 1 à n
int* nouveauTableauDeUnATaille(int taille)
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
    int* indices = nouveauTableauDeUnATaille(instance->N);

    srand(clock()); 
    
    for (int i = 0; i < instance->N-1; i++)
    {
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
    int* indices = nouveauTableauDeUnATaille(instance->N);

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
    int* indices = nouveauTableauDeUnATaille(instance->N);

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
    int* indices = nouveauTableauDeUnATaille(instance->N);

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

//METHODE NUMERO 6
//entrée :      instance dont on doit trier les éléments
//sortie :      une liste triée de taille N dont chaque valeur représente l'indice d'un objet
int* ordonancementValeursCroissantes(struct Instance* instance)
{
    int* indices = nouveauTableauDeUnATaille(instance->N);

    int valeurMax = 0;
    int indiceMax = 0;
    int tmp = 0;

    for (int compteur = 0; compteur < instance->N; compteur++)
    {
        //on récupère la valeur correspondant à l'indice à la position compteur
        valeurMax = instance->p[indices[compteur]];
        //on initialise l'indice correspondant à la valeur minimale
        indiceMax = compteur;

        for (int i = compteur+1; i < instance->N ; i++)
        {
            if (instance->p[indices[i]] <= valeurMax) 
            {
                valeurMax = instance->p[indices[i]];
                indiceMax = i;
            }
        }

        //si on a trouvé une valeur inférieure, on échange les positions des deux indices
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

//retourne une liste d'indices triés selon la méthode choisie
int* triSelonMethode(struct Instance* instance, int* solution, int methode)
{
    int* liste;

    switch (methode)
    {
    case 1:
        //aleatoire
        liste = ordonancementAleatoire(instance);
        break;
    case 2:
        //valeurs decroissantes
        liste = ordonancementValeursDecroissantes(instance);
        break;
    case 3:
        //ratio valeurs poids
        liste = ordonancementRatioValeursPoids(instance);
        break;
    case 4:
        //ratio valeurs dimension critique STATIQUE
        liste = ordonancementRatioValeursDimensionCritique(instance, solution);
        break;
    case 5:
        //ratio valeurs dimension critique DYNAMIQUE
        liste = ordonancementRatioValeursDimensionCritique(instance, solution);
        break;
    case 6:
        //valeurs croissantes
        liste = ordonancementValeursCroissantes(instance);
        break;

    default:
        break;
    }

    return liste;
}

//retourne la solution dans laquelle on essaye d'ajouter un objet
//si les poids de l'objet ne font pas déborder le sac, on l'ajoute.
int* ajouterObjetDansSacSiPlace(struct Instance* instance, int* solution, int indiceObjet)
{
    solution[indiceObjet] = 1;

    if(SolutionTestFaisabilite(instance, solution) == 1)
    {
        solution[indiceObjet] = 0;
    }

    return solution;
}

//retourne l'indice du premier objet trouvé qui n'est pas dans la solution 
int indicePremierElementPasDansLaSolution(struct Instance* instance, int* solution, int* indices)
{
    int i = 0;

    while (solution[indices[i]] == 1 && i < instance->N)
    {
        i++;
    }

    return i;
}

//renvoie une solution (tableau de 0 et 1) de l'instance avec une méthode choisie
int* solutionHeuristique(struct Instance* instance, int methode)
{
    int* solutionDirecte = nouveauTableauDeValeursNulles(instance->N);

    int* indicesSolution = triSelonMethode(instance, solutionDirecte, methode);
    
    for (size_t compteur = 0; compteur < instance->N; compteur++)
    {
        //dynamique
        if (methode == 5)
        {
            solutionDirecte = ajouterObjetDansSacSiPlace(instance, solutionDirecte, indicesSolution[indicePremierElementPasDansLaSolution(instance,solutionDirecte,indicesSolution)]);
            
            indicesSolution = triSelonMethode(instance, solutionDirecte, methode);
        }
        //dynamique
        else
        {
            solutionDirecte = ajouterObjetDansSacSiPlace(instance, solutionDirecte, indicesSolution[compteur]);
        }
    }
    
    return solutionDirecte;
}