#include <stdio.h>
#include <stdlib.h>
#include "solution.c"
#include "instance.c"
#include "parser.c"
#include "heuristique.c"
#include "methaheuristiques.c"

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
	PrintInstance(instance1);
	
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
	
	printf("solution faisable (oui=0 , non=1) : %d \n",SolutionTestFaisabilite(instance1,solution));
	
	SolutionAfficher(instance1, solution);
	
	//heuristiques
	int *liste;
	liste = ordonancementAleatoire(instance1);
	liste = ordonancementValeursDecroissantes(instance1);
	liste = ordonancementRatioValeursPoids(instance1);
	liste = ordonancementRatioValeursDimensionCritique(instance1);

	printf("\n");
	printf("erreur1");



	/*int* solu = Metaheuristique_RL(instance1);
	for (size_t i = 0; i < instance1->N; i++){
		printf("valeur pour chaque dimension : %d \n",solu[i]);
	}
	*/
	printf("erreur2");

	return 0;
}
