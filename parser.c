#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

//lis une instance du fichier, stocke ses informations dans le parser. 
//si afficherParser = 1, il y aura un affichage des informations du parser dans la console.
void ParserLireInstance(struct Parser* parser, int afficherParser)
{
    if (parser->fichier)
    {
		//affichage
		if (afficherParser) printf("\n--- Parser ---\n\n");

		//poubelle pour se débarrasser des informations inutiles
		int trash;
		
		//récupération de N (nombre d'objets) et de M (nombre de dimensions)
		fscanf(parser->fichier, "%d %d %d %d", &parser->N, &parser->M, &trash, &trash);
		if (afficherParser) printf("N = %d\n\nM = %d\n\n", parser->N, parser->M);
		
		//suppression de la solution idéale
		for (int i=0;i<parser->N;i++){
			fscanf(parser->fichier,"%d",&trash);
		}

		//récupération de p (tableau des valeurs des objets)
		parser->p=malloc(parser->N*sizeof(int));
		for (int i=0;i<parser->N;i++){
			fscanf(parser->fichier,"%d",&parser->p[i]);
		}
		if (afficherParser) printf("Valeurs :\n"); afficherListeInteger(parser->p, parser->N);

		//récupération de r (tableau des poids des objets dans chaque dimension)
		parser->r=malloc(parser->M*sizeof(int*)); 
		for (int i=0;i<parser->M;i++){
			parser->r[i]=malloc(parser->N*sizeof(int));
			for (int j=0;j<parser->N;j++){
				fscanf(parser->fichier,"%d",&parser->r[i][j]);
			}
		}
		if (afficherParser) {
			for (int j=0;j<parser->M;j++){
				printf("Poids dim %d :\n", j); afficherListeInteger(parser->r[j], parser->N);
			}
		}
		
		//récupération de b (tableau des poids maximum du sac pour chaque dimension)
		parser->b=malloc(parser->M*sizeof(int));
		for (int i=0;i<parser->M;i++){
			fscanf(parser->fichier,"%d",&parser->b[i]);
		}
		if (afficherParser) printf("Poids max : "); afficherListeInteger(parser->b, parser->M);
    }
}
