#include <stdio.h>                                                                                                                                                          
#include <unistd.h>                                                                                                                                                         
#include <stdlib.h>                                                                                                                                                         

struct P {
        float MaxCoef;  // Coef max, pour determiner colonne
        float Coef_S;   // Coef s/r, pour determiner ligne  
        float MinCoef;  //                                  
        int numC;       // Num de lq colonne selectionnee   
        int numL;       // Num ligne selectionnee           
        int *pivot;     // Pour noter les pivots            
}par;                                                       

void Normal(  float **tab, int C);
void Reduire( float **tab, int L, int C);
int  ChoixL(  float **tab, int l, int c);
int  ChoixC(  float **tab, int l, int c);  
void AfficheTab( float **tab, int l, int c);
void Conclue( float **tab, int l, int c);   

