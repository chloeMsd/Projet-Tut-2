#include "instance.h"

//initialise l'instance donnée en paramètre
void InstanceInit(struct Instance instance, int nombre_objets, int dimension)
{
    instance.nombre_objets = nombre_objets;
    instance.dimension = dimension;
    instance.valeurs_solution[2];
    instance.solution = malloc(sizeof(int)*nombre_objets);
}

struct Instance InstanceNew(int nombre_objets, int dimension)
{
    struct Instance instance;
    InstanceInit(instance, nombre_objets, dimension);
    return instance;
}