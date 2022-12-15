#include <stdio.h>
#include <stdlib.h>
#include "instance.c"
#include "parser.c"

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
	InstanceFinalize(instance1);
	
	return 0;
}
