#include <stdio.h>

struct P {
	float MaxCoef;	// Coef max, pour determiner colonne
	float Coef_S;	// Coef s/r, pour determiner ligne
	float MinCoef; 	// 
	int numC;	// Num de lq colonne selectionnee
	int numL;	// Num ligne selectionnee
	int *pivot;	// Pour noter les pivots
}par;


void AfficheTab(float **tab, int l, int c);
void Conclue(float **tab, int l, int c);

// --- Normalise la ligne ----------------------------------------------
// 	Diviser tous les coefs de la ligne pivot par le pivot
void Normal(float **tab, int L, int C)
{
	int j;
	float coef;

	coef =  tab[par.numL][par.numC];
	for(j=0; j<C; j++) 
		tab[par.numL][j] /= coef;//par.Coef_S ;
	
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

main(int argc , char **argv)
{
	int nbrC, nbrL;
	int i,j;
	float **tab;

	FILE *ptr;

	if ( argc < 2 ) 
		return;

	if ( ( ptr = fopen( argv[1], "r+" ) ) == NULL ) 
		return;

	// Lit le nombre de collonne et de lignes
	fscanf(ptr, "%d %d", &nbrL, &nbrC);

	// Alloue la meme pour les coefs
	tab = (float **) malloc( sizeof(float *) * nbrL );
	for( i = 0; i < nbrL; i++)
		tab[i] = malloc(sizeof(float) * nbrC);

	// Utile pour lire les resultats : enregistre les pivot
	par.pivot = (int *) malloc( sizeof(int)* nbrC );
	for( j = 0; j < nbrC; j++)
		par.pivot[j] = -1;

	// Lit le fichier 
	for( i = 0; i < nbrL ; i++)
	{
		for ( j = 0; j < nbrC; j++) 		
			fscanf(ptr, "%f", &tab[i][j] );		
	}
	
	printf("\n--- Tableau en entree (%d,%d) : ---------\n", nbrL, nbrC);
	AfficheTab(tab, nbrL, nbrC);

	for ( int nbr = 0; ; nbr++ )
	{
		// Choisit colonne du pivot
		if ( ChoixC(tab, nbrL, nbrC)  == -1 )
		{
			printf("--- Fin ---------\n"); 
			break;
		}

		// Choisit ligne du pivot
		if ( ChoixL(tab, nbrL, nbrC) == -1 )
		{
			printf("--- Non Borne ---------\n"); 
			break;	
		}

		// Normalise la ligne pivot
		par.pivot[par.numC] = par.numL;
		Normal(tab, nbrL, nbrC);
		printf("\t(%d)Normalise :  Lig: %d  Col: %d  MinCoef: %.2f  MaxCoef: %.2f  Coef_S: %.2f \n",nbr, par.numL, par.numC, par.MinCoef, par.MaxCoef, par.Coef_S);
		AfficheTab(tab, nbrL, nbrC);

		// Reduit la matrice 
		printf("\t(%d)Reduit : \n", nbr);
		Reduire(tab, nbrL, nbrC);
		AfficheTab(tab, nbrL, nbrC);
	}

	printf("\n--- Conclusion ---------\n");
	Conclue(tab, nbrL, nbrC);	
	fclose(ptr);
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
