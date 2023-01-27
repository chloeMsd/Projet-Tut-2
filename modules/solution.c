#include <stdio.h>
#include <stdlib.h>
#include "instance.h"
#include "parser.h"

//Calcul la valeur du sac à partir d'une solution donnée
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

//Calcul pour chaque dimension du sac les poids de la solution
int* SolutionCalculDimension(struct Instance* instance, int* solution){
	
	//on cree un tableau de M cases, ce sera le totale des poids pour chaque dimension
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

//Test si la solution donnée respecte bien les dimensions du sac en terme de poids maximum
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

//Affiche la solution donnée si c'est une solution possible pour une certaine instance
void SolutionAfficher(struct Instance* instance, int* solution){
	if ( SolutionTestFaisabilite(instance, solution) ){
		for (int i=0; i < instance->N; i++){
			printf("%d ",solution[i]);
		}
	}
}

//Ecris dans un fichier la solution donnée si c'est une solution possible pour une certaine instance
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


