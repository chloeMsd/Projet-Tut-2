#include <stdio.h>
#include <stdlib.h>
#include "instance.h"

//initialise l'instance donnée en paramètre
void InstanceInit(struct Instance* instance, int nb_objets, int dim)
{
    instance->N = nb_objets;
    instance->M = dim;
    instance->x = malloc(sizeof(int)*nb_objets);
    instance->p = malloc(sizeof(int)*nb_objets);
    instance->r = malloc(sizeof(int*)*dim);
    for (int i = 0; i < dim; i++)
	{
        instance->r[i] = malloc(instance->N * sizeof(int));
    }
    instance->b = malloc(sizeof(int)*dim);
}

//libère les ressources allouées par l'instance donnée en paramètre
void InstanceFinalize(struct Instance* instance)
{
    free(instance->x);
    free(instance->p);
    free(instance->r);
    free(instance->b);
}

void SetSolutionsOptimales(struct Instance* instance, int solution1, int solution2)
{
    instance->solutions[0] = solution1;
    instance->solutions[1] = solution2;
}

void SetSolution(struct Instance* instance, int* valeurs)
{
    instance->x = valeurs;
}

void SetValeursObjets(struct Instance* instance, int* valeurs)
{
    instance->p = valeurs;
}

void addToPoidsObjets(struct Instance* instance, int* valeurs, int index)
{
    //allocation dynamique du tableau
    
    
    instance->r[index] = valeurs;
}

void SetPoidsMaximum(struct Instance* instance, int* valeurs)
{
    instance->b = valeurs;
}

void PrintInstance(struct Instance* instance)
{
    printf("-- INSTANCE --\n");
    printf("Nombre objets : %d\n", instance->N);
    printf("Dimension : %d\n", instance->M);
	printf("Solution 1 : %d\nSolution 2 : %d\n", instance->solutions[0], instance->solutions[1]);
    
    printf("Solutions : [");
	for (int i = 0; i < instance->N; i++)
	{
		printf("%d",instance->x[i]); 
        if (i+1 < instance->N) printf(",");
	}
	printf("]\n");
    
    printf("Valeurs objets : [");
	for (int i = 0; i < instance->N; i++)
	{
		printf("%d",instance->p[i]); 
        if (i+1 < instance->N) printf(",");
	}
	printf("]\n");
    
    printf("Poids objets : [\n\n");
	for (int i = 0; i < instance->M; i++)
	{
        printf("[");
        for (int j = 0; j < instance->N; j++)
        {
            printf("%d", instance->r[i][j]); 
            if (i+1 < instance->N) printf(",");
        }
	    printf("]\n\n");
	}
	printf("]\n\n");

    printf("Poids maximaux : [");
	for (int i = 0; i < instance->M; i++)
	{
		printf("%d",instance->b[i]); 
        if (i+1 < instance->M) printf(",");
	}
	printf("]\n");
}