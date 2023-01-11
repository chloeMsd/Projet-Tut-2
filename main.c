#include <stdio.h>
#include <stdlib.h>
#include "solution.c"
#include "instance.c"
#include "parser.c"
#include "heuristique.c"
#include "methaheuristiques.c"
#include "affichage.c"

int main(int argc, char **argv)
{
	//création du parser
	struct Parser* parser = (struct Parser*) malloc(sizeof(struct Parser));
	ParserInitFromFile(parser, "MKP-Instances/_mknapcb1_res.txt");

	//création de l'instance
	struct Instance* instance1 = (struct Instance*) malloc(sizeof(struct Instance));
	InstanceInit(instance1, parser->N, parser->M);
	
	//attribution des variables
	SetSolutionsOptimales(instance1, parser->solutions[0], parser->solutions[1]);
	
	SetSolution(instance1, parser->x);

	SetValeursObjets(instance1, parser->p);
	
	SetPoidsMaximum(instance1, parser->b);
	
	for (size_t i = 0; i < parser->M; i++)
	{
		addToPoidsObjets(instance1, parser->r[i], i);
	}
	
	//affichage de l'instance
	//PrintInstance(instance1);
	
	//test solution
	int* solution = malloc(sizeof(int)*instance1->N);
	
	for (size_t i = 0; i < instance1->N; i++)
	{
		solution[i] = instance1->x[i];
	}
	
	int a = SolutionFonctionObjectif(instance1, solution);
	printf("valeur fonction objectif : %d \n",a);
	
	int *s = SolutionCalculDimension(instance1,solution);
	for (size_t i = 0; i < instance1->M; i++){
		printf("valeur pour chaque dimension : %d \n",s[i]);
	}
	
	printf("solution faisable (oui=0 , non=1) : %d \n", SolutionTestFaisabilite(instance1,solution));
	
	SolutionAfficher(instance1, solution);
	
	//heuristiques
	for (size_t i = 0; i < 10; i++)
	{
		int *liste;
		liste = solutionHeuristique(instance1,1);
	}
	
	//metaheuritsique

	//afficherSolution(instance1, Metaheuristique_RL(instance1, 1));
	afficherSolution(instance1, Metaheuristique_Tabou(instance1, 1, 10, 50, 1));

	printf("\n");
	return 0;
}
