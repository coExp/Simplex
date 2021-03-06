#include "simplex.h"

// --- Normalise la ligne ----------------------------------------------
// 	Diviser tous les coefs de la ligne pivot par le pivot
void Normal(float **tab, int C)
{
	int j;
	float coef;

	coef =  tab[par.numL][par.numC];
	for( j=0; j<C; j++) 
		tab[par.numL][j] /= coef;	
}

// --- Reduit la matrice --------------------------------------------	
// 	Multiplier et soustraire une valeur ad´equate toutes les lignes
//	restantes de fa¸con `a obtenir des 0 sur la colone pivot en dehors du
//	pivot
void Reduire(float **tab, int L, int C)
{
	int i,j;
	float coef;

	for ( i = 0; i < L; i++ )
	{
	   if ( i == par.numL ) 
	      i++;

	   if ( i == L ) 
	      break;
		
	   coef = tab[i][par.numC];

	   for ( j = 0; j < C; j++ )
	   {
		tab[i][j] -= (tab[par.numL][j] * coef);
	   }	
	}
}

// --- Choisit la ligne pour le pivot -------------------------------
int ChoixL(float **tab, int l, int c)
{
	int i;
	float coef;

	par.numL = -1; 
	par.Coef_S = 0;
	for (i=0; i<l-1; i++)	
	{
		if( tab[i][par.numC] > 0 ) 
		{
			coef =  tab[i][c-1] / tab[i][par.numC] ;
			if ( ((par.numL==-1) || (coef<par.Coef_S)) && (coef>0) ) 
			{
				par.Coef_S = coef;
				par.numL = i;
			}
		}
	}
	return par.numL;
}

// --- Choisit la colonne pour le pivot -----------------------------
int ChoixC(float **tab, int l, int c)
{
	int j;

	par.MaxCoef = 0; 
	par.numC = -1;
	for (j=0; j < c ; j++) 
	{
		if( tab[l-1][j] > par.MaxCoef ) 
		{
			par.MaxCoef = tab[l-1][j]; 
			par.numC = j;
		}
	}	
	return par.numC;
}

int main(int argc , char **argv)
{
	int nbrC, nbrL, nbr;
	int i,j;
	float **tab;

	FILE *ptr;

	if ( argc != 2 ) 
		showHelp(), exit ( EXIT_FAILURE );

	if ( ( ptr = fopen( argv[1], "r+" ) ) == NULL ) 
		showHelp(), exit ( EXIT_FAILURE );

	// Lit le nombre de colonnes et de lignes
	fscanf(ptr, "%d %d", &nbrL, &nbrC);

	// Alloue la même pour les coefs
	tab = (float **) malloc( sizeof(float *) * nbrL );
	for( i = 0; i < nbrL; i++)
		tab[i] = malloc(sizeof(float) * nbrC);

	// Utile pour lire les résultats : enregistre les pivot
	par.pivot = (int *) malloc( sizeof(int)* nbrC );
	for( j = 0; j < nbrC; j++)
		par.pivot[j] = -1;

	// Lit le fichier 
	for( i = 0; i < nbrL ; i++)
	{
		for ( j = 0; j < nbrC; j++) 		
			fscanf(ptr, "%f", &tab[i][j] );		
	}
	
	printf("\n--- Table (%d,%d) : ---------\n", nbrL, nbrC);
	AfficheTab(tab, nbrL, nbrC);

	for ( nbr = 0; ; nbr++ )
	{
		// Choisit colonne du pivot
		if ( ChoixC(tab, nbrL, nbrC)  == -1 )
		{
			printf("--- End ---------\n"); 
			break;
		}

		// Choisit ligne du pivot
		if ( ChoixL(tab, nbrL, nbrC) == -1 )
		{
			printf("--- Unbound ---------\n"); 
			break;	
		}

		// Normalise la ligne pivot
		par.pivot[par.numC] = par.numL;
		Normal(tab, nbrC);
		printf("\t(%d)Normalise =>  Row: %d  Col: %d  MinCoef: %.2f  MaxCoef: %.2f  Coef_S: %.2f \n",nbr, par.numL, par.numC, par.MinCoef, par.MaxCoef, par.Coef_S);
		AfficheTab(tab, nbrL, nbrC);

		// Réduit la matrice 
		printf("\t(%d)Reduce: \n", nbr);
		Reduire(tab, nbrL, nbrC);
		AfficheTab(tab, nbrL, nbrC);
	}

	printf("\n--- Conclusion ---------\n");
	Conclue(tab, nbrL, nbrC);	
	fclose(ptr);

	exit ( EXIT_SUCCESS );
}

// --- Affiche une conclusion ---------------------------------------
void Conclue(float **tab, int l, int c)
{
	int j;

	for ( j = 0; j < c-l; j++)
	{
		if ( par.pivot[j]!= -1)
			printf("\tx%d = %.2f \n",j+1, tab[par.pivot[j]][c-1]);
		else
			printf("\tx%d = %.2f \n ",j+1, 0.0 );
	}
	printf("\tMax = %.2f\n", -tab[l-1][c-1]);
}

// --- Affiche le tableau -------------------------------------------
void AfficheTab(float **tab, int l, int c )
{
	int i,j;
	for ( i = 0; i < l; i++ ) 
	{
		printf("\t");
		for ( j = 0; j < c; j++ ) 
		{
			if ( tab[i][j] > -10 ) 
				printf(" ");
			if ( tab[i][j] < 10 ) 
				printf(" ");
			printf("%.2f ", tab[i][j] );
			if ((tab[i][j]>=0)) printf(" ");
			printf("|");
		}
		printf("\n");
	}
}

// --- Show a simple help message -----------------------------------
void showHelp( void )
{
	printf("solving simplex equation\n");
	printf("Usage: simlex FILE");
	printf("\n\tExample: Looking for the max of 2.X + Y");
	printf("\n\t         Under constraints: X - Y <= 3 ");
	printf("\n\t                            X + 2.Y <= 6");
	printf("\n\t                            -X + 2.Y <= 2");
	printf("\n\t         the FILE is:");
	printf("\n\t            4 6 ");
	printf("\n\t            1.0  -1.0 1.0 0.0 0.0 3 ");
	printf("\n\t            1.0  2.0  0.0 1.0  0.0 6");
	printf("\n\t            -1.0  2.0  0.0 0.0 1.0 2");
	printf("\n\t            2.0  1.0 0.0 0.0 0.0 0.0");
	printf("\n");
}
