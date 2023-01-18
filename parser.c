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
		
		parser->N = malloc(parser->nb_instances*sizeof(int));
		parser->M = malloc(parser->nb_instances*sizeof(int));
		parser->solutions[2] = malloc(parser->nb_instances*sizeof(int));
		parser->x = malloc(parser->nb_instances*sizeof(int));
		parser->p = malloc(parser->nb_instances*sizeof(int));
		parser->r = malloc(parser->nb_instances*sizeof(int));
		parser->b = malloc(parser->nb_instances*sizeof(int));

        //on lit les premieres infos du fichier
		for (int l=0; l<parser->nb_instances; l++){
			fscanf(parser->fichier, "%d %d %d %d", &parser->N[l], &parser->M[l], &parser->solutions[l][0], &parser->solutions[l][1]);
			
			parser->x[l] = malloc(parser->N[l]*sizeof(int));
			parser->p[l]=malloc(parser->N[l]*sizeof(int));
			parser->r[l]=malloc(parser->M[l]*sizeof(int*)); //appeler avec r[i][j]
			for (int i=0;i<parser->M[l];i++){
				parser->r[l][i]=malloc(parser->N[l]*sizeof(int));
			}
			parser->b[l]=malloc(parser->M[l]*sizeof(int));
			for (int j=0;j<parser->N[l];j++){
				fscanf(parser->fichier,"%d",&parser->x[l][j]);
			}
			for (int j=0;j<parser->N[l];j++){
				fscanf(parser->fichier,"%d",&parser->p[l][j]);
			}
			for (int k=0;k<parser->M[l];k++){
				for (int j=0;j<parser->N[l];j++){
					fscanf(parser->fichier,"%d",&parser->r[l][k][j]);
				}
			}
			for (int i=0;i<parser->M[l];i++){
				fscanf(parser->fichier,"%d",&parser->b[l][i]);
			}
		}
    }
    fclose(parser->fichier);
}
