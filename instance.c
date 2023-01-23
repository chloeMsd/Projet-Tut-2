#include <stdio.h>
#include <stdlib.h>
#include "instance.h"

//initialise l'instance donnée en paramètre
void InstanceInitFromParser(struct Instance* instance, struct Parser* parser)
{
    //initialisation du nombre d'objets
    instance->N = parser->N;

    //initialisation du nombre de dimensions
    instance->M = parser->M;

    //allocation des espaces memoires nécessaires
    instance->p = malloc(sizeof(int)*parser->N);
    instance->r = malloc(sizeof(int*)*parser->M);
    for (int i = 0; i < parser->M; i++){
        instance->r[i] = malloc(instance->N * sizeof(int));
    }
    instance->b = malloc(sizeof(int)*parser->M);

    //copie des valeurs du parser dans l'instance
    memcpy(instance->p, parser->p, sizeof(int)*parser->N);
    memcpy(instance->r, parser->r, sizeof(int*)*parser->M*sizeof(int)*parser->N);
    memcpy(instance->b, parser->b, sizeof(int)*parser->M);
}

//libère les ressources allouées par l'instance donnée en paramètre
void InstanceFinalize(struct Instance* instance)
{
    free(instance->p);
    free(instance->r);
    free(instance->b);
}

void addToPoidsObjets(struct Instance* instance, int* valeurs, int index)
{
    //allocation dynamique du tableau
    
    
    instance->r[index] = valeurs;
}

//fonction qui affiche les valeurs de l'instance
void PrintInstance(struct Instance* instance)
{
    printf("-- INSTANCE --\n");
    printf("Nombre objets : %d\n", instance->N);
    printf("Dimension : %d\n", instance->M);

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