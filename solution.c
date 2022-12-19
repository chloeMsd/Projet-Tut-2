#include <stdio.h>
#include <stdlib.h>
#include "instance.h"
#include "parser.h"
#include "solution.h"

int SolutionFonctionObjectif(struct Instance instance, struct Solution solution){
	int valeur=0;
	for (int i=0; i<instance->N; i++){
		if (solution[i]==1){
			valeur= p_tot + instcance->p[i];
		}
	}
	return valeur;
}

int* SolutionCalculDimension(struct Instance instance, struct Solution solution){
	//on cree un tableau de M cases c'est le totale des poids pour chaque dimension
	int *s=malloc(instance->M*sizeof(int));
	for (int i=0; i<instance->N; i++){
		if (solution[i]==1){
			for (int j=0; j<instance->M;j++){
				int a=s[j];
				free(s[j]);
				s[j]= a + instance->r[j][i];
			}
		}
	}
	return s;
}
int SolutionTestFaisabilité(struct Instance instance, struct Solution solution){
	//retourne 0 si c'est ok pour toutes les dimensions et retourne 1 sinon
	//on cree un tableau avec M cases (1 case = 1 dimensions)
	int *s=SolutionCalulDimension(instance,solution);
	for (int j=0; j<instance->M;j++){
		if (s[j] > instance->b[j]){
			return 1;
		}
	} 
	free(s);
	return 0;
}

void SolutionAfficher(struct Instance instance, struct Solution solution){
	if (SolutionTestFaisabilité==0){
		for (int i=0; i<instance->N; i++){
			printf("%d ",solution[i]);
		}
	}
}

void SolutionEcrire(struct Instance instance, struct Solution solution){
	if (SolutionTestFaisabilité==0){
		FILE *f=fopen("solution.txt","w+");
		if (f){
			for (int i=0; i<instance->N;i++){
				fprintf(f, "%d ",solution[i]);
			}
		}
		fclose(f);
	}
}

