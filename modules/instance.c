#include <stdio.h>
#include <stdlib.h>
#include "instance.h"

//initialise l'instance donnée en paramètre
void InstanceInitFromParser(struct Instance* instance, struct Parser* parser, int afficherInstance)
{
    //initialisation du nombre d'objets
    instance->N = parser->N;

    //initialisation du nombre de dimensions
    instance->M = parser->M;

    //initialisation de p
    instance->p = malloc(sizeof(int)*parser->N);
    memcpy(instance->p, parser->p, sizeof(int)*parser->N);

    //initialisation de r
    instance->r = malloc(sizeof(int*)*parser->M);
    for (int i = 0; i < parser->M; i++){
        instance->r[i] = malloc(instance->N * sizeof(int));
        memcpy(instance->r[i], parser->r[i], sizeof(int) * parser->N);
    }

    //initialisation de b
    instance->b = malloc(sizeof(int)*parser->M);
    memcpy(instance->b, parser->b, sizeof(int)*parser->M);

    if(afficherInstance) PrintInstance(instance);
}

//libère les ressources allouées par l'instance donnée en paramètre
void InstanceFinalize(struct Instance* instance)
{
    free(instance->p);
    free(instance->r);
    free(instance->b);
}

//ajoute les valeurs des objets de la dimension numéro index
void addToPoidsObjets(struct Instance* instance, int* valeurs, int index)
{
    instance->r[index] = valeurs;
}
