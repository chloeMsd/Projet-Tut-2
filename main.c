#include <stdio.h>
#include "instance.c"

int main(int argc, char **argv)
{
	//création de l'instance
	struct Instance* instance = (struct Instance*) malloc(sizeof(struct Instance));
	InstanceInit(instance, 10, 3);
	
	//attribution des variables
	SetSolutionsOptimales(instance, 56, 43);
	
	int solution[10] = { 0,1,1,1,0,0,1,0,1,0 };
	SetSolution(instance, solution);

	int valeurs[10] = { 0,1,2,3,4,5,6,7,8,9 };
	SetValeursObjets(instance, valeurs);
	
	int valeurs2[10] = { 10,11,12,13,14,15,16,17,18,19 };
	SetPoidsMaximum(instance, valeurs2);
	
	int** valeurs3 = malloc(30*sizeof(int));
	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<10; j++)
		{
			valeurs3[i][j] = i*10+j;
		}
	}
	SetPoidsObjets(instance, valeurs3);
	
	//affichage de l'instance
	PrintInstance(instance);
	InstanceFinalize(instance);
	
	return 0;
}
