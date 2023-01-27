#include <stdio.h>
#include <stdlib.h>
#include "modules/solution.c"
#include "modules/instance.c"
#include "modules/parser.c"
#include "modules/heuristique.c"
#include "modules/methaheuristiques.c"
#include "modules/affichage.c"

//le nom du fichier dans lequel chercher les instances
#define FICHIER "MKP-Instances/_mknapcb1_res.txt"

//indique si on affiche les valeurs
#define AFFICHER_PARSEUR 0
#define AFFICHER_INSTANCE 0

//variables utilisées pour la métaheuristique Tabou
#define TABOU_TAILLE_LISTE 80
#define TABOU_NB_ITERATIONS 20
#define TABOU_ASPI 1

int main(int argc, char **argv)
{
	//alocation des espaces mémoire pour le Parser et l'Instance
	struct Parser* parser = (struct Parser*) malloc(sizeof(struct Parser));
	struct Instance* instance = (struct Instance*) malloc(sizeof(struct Instance));
	
	//ouverture du fichier et récupération du nombre d'instances
	parser->fichier = fopen(FICHIER, "r");
    fscanf(parser->fichier, "%d", &parser->nb_instances);

	printf("\n--- DEMARRAGE DU PROGRAMME ---\n\nNombre d'instances à lire : %d\n\n", parser->nb_instances);

	for (size_t i = 0; i < parser->nb_instances; i++)
	{
		//Lecture du fichier et initialisation du parseur
		ParserLireInstance(parser, AFFICHER_PARSEUR);

		//création de l'instance
		InstanceInitFromParser(instance, parser, AFFICHER_INSTANCE);

		//affichage
		printf("\n\n"); 
		printf("<INSTANCE %d>---------------------\n\n",i+1);
		printf("Ordonnancement       aleatoire  |  decroissant  |  ratio v/p  |  ratio v/d sta  | ratio v/d dyn  |  croissant\n", i+1);
		
		//heuristiques
		afficherHeuristiques(instance);
		
		//metaheuristiques
		afficherMetaheuristiques(instance, TABOU_NB_ITERATIONS, TABOU_TAILLE_LISTE, TABOU_ASPI);

		//désallocation de l'instance
		InstanceFinalize(instance);
	}
	
	//fermeture du fichier
	fclose(parser->fichier);

	return 0;
}

