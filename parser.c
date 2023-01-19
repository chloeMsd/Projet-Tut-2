#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

//initialise le parser
void ParserInitFromFile(struct Parser* parser, char* filename)
{
    parser->fichier = fopen(filename, "r");

    if (parser->fichier)
    {
        //on lit le nombre d'instances
        fscanf(parser->fichier, "%d", &parser->nb_instances);
		
        //on lit les premieres infos du fichier
		fscanf(parser->fichier, "%d %d %d %d", &parser->N, &parser->M, &parser->solutions[0], &parser->solutions[1]);
		
		parser->x= malloc(parser->N*sizeof(int));
		parser->p=malloc(parser->N*sizeof(int));
		parser->r=malloc(parser->M*sizeof(int*)); //appeler avec r[i][j]
		for (int i=0;i<parser->M;i++){
			parser->r[i]=malloc(parser->N*sizeof(int));
		}
		parser->b=malloc(parser->M*sizeof(int));
		for (int j=0;j<parser->N;j++){
			fscanf(parser->fichier,"%d",&parser->x[j]);
		}
		for (int j=0;j<parser->N;j++){
			fscanf(parser->fichier,"%d",&parser->p[j]);
		}
		for (int k=0;k<parser->M;k++){
			for (int j=0;j<parser->N;j++){
				fscanf(parser->fichier,"%d",&parser->r[k][j]);
			}
		}
		for (int i=0;i<parser->M;i++){
			fscanf(parser->fichier,"%d",&parser->b[i]);
		}
    }
    fclose(parser->fichier);
}
