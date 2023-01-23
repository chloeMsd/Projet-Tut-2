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

//indique si on affiche les valeurs du parseur ou non 
#define AFFICHER_PARSEUR 1

int main(int argc, char **argv)
{
	//alocation des espaces mémoire pour le Parser et l'Instance
	struct Parser* parser = (struct Parser*) malloc(sizeof(struct Parser));
	struct Instance* instance = (struct Instance*) malloc(sizeof(struct Instance));
	
	//ouverture du fichier et récupération du nombre d'instances
	parser->fichier = fopen(FICHIER, "r");
    fscanf(parser->fichier, "%d", &parser->nb_instances);

	printf("\n--- DEMARRAGE DU PROGRAMME ---\n\nNombre d'instances à lire : %d\n\n", parser->nb_instances);

	for (size_t l = 0; l < parser->nb_instances; l++)
	{
		//Lecture du fichier et initialisation du parseur
		ParserLireInstance(parser, AFFICHER_PARSEUR);

		//création de l'instance
		InstanceInitFromParser(instance, parser);
		PrintInstance(instance);

		/*
			//heuristiques
			int *liste = solutionHeuristique(instance,1,0);
			
			//metaheuritsique

			//afficherSolution(instance, Metaheuristique_Tabou(instance, methode, dynamique, 10, 50, 1));
			afficherSolution(instance, Metaheuristique_RL(instance, METHODE, DYNAMIQUE));
		*/
	}
	
	//fermeture du fichier
	fclose(parser->fichier);

	return 0;
}
