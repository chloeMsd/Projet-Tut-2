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
#define AFFICHER_HEURISTIQUES 1
#define AFFICHER_METAHEURISTIQUES 0

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

		//heuristiques
		if (AFFICHER_HEURISTIQUES)
		{
			printf("\n\n"); 
			printf("<INSTANCE %d>---------------------\n\n",i+1);
			printf("Ordonnancement       aleatoire  |  decroissant  |  ratio v/p  |  ratio v/d sta  | ratio v/d dyn  |  croissant\n", i+1);
			
			afficherHeuristiques(instance);
		}

		//metaheuristiques
		if (AFFICHER_HEURISTIQUES)
		{
			afficherMetaheuristiques(instance);
		}

		//metaheuristique
		/*
		afficherSolution(instance, Metaheuristique_Tabou(instance, 3, 10, 50, 1));
		afficherSolution(instance, Metaheuristique_RL(instance, 3));
		*/
	}
	
	//fermeture du fichier
	fclose(parser->fichier);

	return 0;
}
