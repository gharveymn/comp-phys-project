/*     neighbor.c */
/********************************************************************/
/*     Program to search the neighbor points of isolines            */
/*     -1. -1. -1. labelled the input end                           */
/*------------------------------------------------------------------*/
/*     Programm zur Suche der Nachbarpunkte von Isolinien           */
/*     -1. -1. -1. kennzeichnet das Eingabeende                     */
/********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define VOL1 1000   /* 1st dimension row    - Zeilenindex  i */
#define VOL2 5      /* 2nd dimension column - Spaltenindex j */

int main(void) 
{
   int    i=0,in=0,j,ii,iprint;
   float  array[VOL1][VOL2],min;
   FILE   *fpein;
   FILE   *fpaus;
   char   *input="ein";                            /* input file  */
   char   *output="aus";                           /* output file */

   fpein=fopen(input,"r");                         /* opening the files */
   fpaus=fopen(output,"w");
   if ((fpein==NULL)||(fpaus==NULL)) {
      printf("Error on opening the files\n");
      return(-1);                                  /* EXIT_ERROR_input_file */
                                     }

   for(i=0; i < VOL1; i++) {                       /* read in array */
      for(j=0; j < VOL2-2; j++) fscanf(fpein,"%f ", &array[i][j]);
      array[i][3]=0.;
      array[i][4]=1000.;
      in=i-1;
      if((array[i][0] == array[i][1]) && (array[i][0] == array[i][2])) break;
                           }

   i=0;                                            /* Start point */
   array[i][3]=1.;
   for(j=0; j < VOL2-2; j++) fprintf(fpaus,"%3.8f ",array[i][j]);
   fprintf(fpaus,"\n");

   iprint=0;
   for(ii=1; ii<=in+1; ii++) {
   min=array[0][4];
   for(i=1; i<=in; i++) {                          /* calculation of distances */
   array[i][4]=sqrt((array[i][0]-array[iprint][0])*(array[i][0]-array[iprint][0]) + 
                    (array[i][1]-array[iprint][1])*(array[i][1]-array[iprint][1]));
   if(array[i][3] == 0. && array[i][4] < min) min=array[i][4];
                        }

   for(i=1; i<=in; i++) {                          /* write at minimum distanc */
   if(array[i][3] == 0. && array[i][4] == min) {
      iprint=i;
      for(j=0; j < VOL2-2; j++) fprintf(fpaus,"%3.8f ",array[i][j]);	
      fprintf(fpaus,"\n");
      array[i][3]=1.;
                                               }
                        }
                             }

   printf("neighbor EXIT_SUCCESS\n");
   fclose(fpein);
   fclose(fpaus);
   return EXIT_SUCCESS;
}














