#include <stdio.h>
#include <stdlib.h>
#include "solution.c"
#include "instance.c"
#include "parser.c"
#include "heuristique.c"
#include "methaheuristiques.c"
#include "affichage.c"

//le nom du fichier dans lequel chercher les instances
#define FICHIER "MKP-Instances/_mknapcb1_res.txt"

//le nom de la methode utilisee en heuristique 
#define METHODE 1

//indique si l'heuristique doit etre utilisee de maniere dynamique
//1 = true, 0 = false
#define DYNAMIQUE 1

int main(int argc, char **argv)
{
	//création du parser
	struct Parser* parser = (struct Parser*) malloc(sizeof(struct Parser));
	ParserInitFromFile(parser, FICHIER);

	for (size_t l = 0; l < parser->nb_instances; l++)
	{
		//création de l'instance
		struct Instance* instance1 = (struct Instance*) malloc(sizeof(struct Instance));
		InstanceInit(instance1, parser->N[l], parser->M[l]);
		
		//attribution des variables
		SetSolutionsOptimales(instance1, parser->solutions[l][0], parser->solutions[l][1]);
		
		SetSolution(instance1, parser->x[l]);

		SetValeursObjets(instance1, parser->p[l]);
		
		SetPoidsMaximum(instance1, parser->b[l]);
		
		for (size_t i = 0; i < parser->M[l]; i++)
		{
			addToPoidsObjets(instance1, parser->r[l][i], i);
		}
		
		//affichage de l'instance
		PrintInstance(instance1);
		
		//heuristiques
		int *liste = solutionHeuristique(instance1,1,0);
		
		//metaheuritsique

		//afficherSolution(instance1, Metaheuristique_Tabou(instance1, methode, dynamique, 10, 50, 1));
		afficherSolution(instance1, Metaheuristique_RL(instance1, METHODE, DYNAMIQUE));

		printf("\n");
	}
	
	return 0;
}
