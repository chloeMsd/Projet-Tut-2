#include <stdio.h>
#include <stdlib.h>
#include "instance.h"
#include "parser.h"


int SolutionFonctionObjectif(struct Instance* instance, int* solution){
	int valeur=0;
	for (int i=0; i<instance->N; i++)
	{
		if (solution[i] == 1)
		{
			valeur= valeur + instance->p[i];
		}
	}
	return valeur;
}

int* SolutionCalculDimension(struct Instance* instance, int* solution){
	//on cree un tableau de M cases c'est le totale des poids pour chaque dimension
	int *s=malloc(instance->M*sizeof(int));

	for (size_t i = 0; i < instance->M; i++)
	{
		s[i] = 0;
	}

	for (int i=0; i<instance->N; i++)
	{
		if (solution[i] == 1)
		{
			for (int j=0; j<instance->M;j++)
			{
				s[j] += instance->r[j][i];
			}
		}
	}
	return s;
}

int SolutionTestFaisabilite(struct Instance* instance, int* solution){
	//retourne 0 si c'est ok pour toutes les dimensions et retourne 1 sinon
	//on cree un tableau avec M cases (1 case = 1 dimensions)
	int *s = SolutionCalculDimension(instance,solution);
	for (int j=0; j<instance->M;j++)
	{
		if (s[j] > instance->b[j])
		{
			return 1;
		}
	} 
	free(s);
	return 0;
}

void SolutionAfficher(struct Instance* instance, int* solution){
	if ( SolutionTestFaisabilite(instance, solution) ){
		for (int i=0; i < instance->N; i++){
			printf("%d ",solution[i]);
		}
	}
}

void SolutionEcrire(struct Instance* instance, int* solution){
	if (SolutionTestFaisabilite==0){
		FILE *f=fopen("solution.txt","w+");
		if (f){
			for (int i=0; i<instance->N;i++){
				fprintf(f, "%d ",solution[i]);
			}
		}
		fclose(f);
	}
}


