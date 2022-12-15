#include <stdio.h>
#include <stdlib.h>
#include "instance.h"

//initialise l'instance donnée en paramètre
void InstanceInit(struct Instance* instance, int nb_objets, int dim)
{
    instance->nombre_objets = nb_objets;
    instance->dimension = dim;
    instance->solution_optimale = malloc(sizeof(int)*nb_objets);
    instance->valeurs_objets = malloc(sizeof(int)*nb_objets);
    instance->poids_objets = malloc(sizeof(int*)*dim);
    for (int i = 0; i < dim; i++)
	{
        instance->poids_objets[i] = malloc(instance->nombre_objets * sizeof(int));
    }
    instance->poids_maximum = malloc(sizeof(int)*dim);
}

//libère les ressources allouées par l'instance donnée en paramètre
void InstanceFinalize(struct Instance* instance)
{
    free(instance->solution_optimale);
    free(instance->valeurs_objets);
    free(instance->poids_objets);
    free(instance->poids_maximum);
}

void SetSolutionsOptimales(struct Instance* instance, int solution1, int solution2)
{
    instance->valeurs_solution[0] = solution1;
    instance->valeurs_solution[1] = solution2;
}

void SetSolution(struct Instance* instance, int* valeurs)
{
    instance->solution_optimale = valeurs;
}

void SetValeursObjets(struct Instance* instance, int* valeurs)
{
    instance->valeurs_objets = valeurs;
}

void addToPoidsObjets(struct Instance* instance, int* valeurs, int index)
{
    //allocation dynamique du tableau
    
    
    instance->poids_objets[index] = valeurs;
}

void SetPoidsMaximum(struct Instance* instance, int* valeurs)
{
    instance->poids_maximum = valeurs;
}

void PrintInstance(struct Instance* instance)
{
    printf("-- INSTANCE --\n");
    printf("Nombre objets : %d\n", instance->nombre_objets);
    printf("Dimension : %d\n", instance->dimension);
	printf("Solution 1 : %d\nSolution 2 : %d\n", instance->valeurs_solution[0], instance->valeurs_solution[1]);
    
    printf("Solutions : [");
	for (int i = 0; i < instance->nombre_objets; i++)
	{
		printf("%d",instance->solution_optimale[i]); 
        if (i+1 < instance->nombre_objets) printf(",");
	}
	printf("]\n");
    
    printf("Valeurs objets : [");
	for (int i = 0; i < instance->nombre_objets; i++)
	{
		printf("%d",instance->valeurs_objets[i]); 
        if (i+1 < instance->nombre_objets) printf(",");
	}
	printf("]\n");
    
    printf("Poids objets : [\n\n");
	for (int i = 0; i < instance->dimension; i++)
	{
        printf("[");
        for (int j = 0; j < instance->nombre_objets; j++)
        {
            printf("%d", instance->poids_objets[i][j]); 
            if (i+1 < instance->nombre_objets) printf(",");
        }
	    printf("]\n\n");
	}
	printf("]\n\n");

    printf("Poids maximaux : [");
	for (int i = 0; i < instance->dimension; i++)
	{
		printf("%d",instance->poids_maximum[i]); 
        if (i+1 < instance->dimension) printf(",");
	}
	printf("]\n");
}