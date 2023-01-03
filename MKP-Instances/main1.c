#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    FILE* fichier = NULL;
    fichier = fopen("_mknapcb1_res.txt", "r");
 
    if (fichier != NULL){
		int nbInst;
		fscanf(fichier, "%d", &nbInst);
		
		time_t begin = time( NULL );
		int N;
		int M, poubelle1, poubelle2;
		fscanf(fichier,"%d %d %d %d",&N,&M, &poubelle1, &poubelle2);
		int *x=malloc(N*sizeof(int));
		int *p=malloc(N*sizeof(int));
		int **r=malloc(M*sizeof(int*));
		for (int i=0;i<M;i++){
			r[i]=malloc(N*sizeof(int));
		}
		int *b=malloc(M*sizeof(int));
		int a;
		for (int j=0;j<N;j++){
			fscanf(fichier,"%d",&a);
			x[j]=a;
		}
		for (int j=0;j<N;j++){
			fscanf(fichier,"%d",&a);
			p[j]=a;
		}
		for (int k=0;k<M;k++){
			for (int j=0;j<N;j++){
				fscanf(fichier,"%d",&r[k][j]);
			}
		}
		for (int i=0;i<M;i++){
			fscanf(fichier,"%d",&a);
			b[i]=a;
		}
		
		printf("%d,%d\n",N,M);
		time_t end = time(NULL);
		unsigned long secondes = (unsigned long) difftime( end, begin );
		printf( "Finished in %ld sec\n", secondes );
		
		
		FILE *f=fopen("sortie.txt","w+");
		if (f){
			fprintf(f,"nom de l'instance et numero		-		%ld\n",secondes);
		}
		
		//on ecrit le timer dans un autre fichier
		fclose(f);
        fclose(fichier);
    }
    return 0;
}
//faire le timer du parser


