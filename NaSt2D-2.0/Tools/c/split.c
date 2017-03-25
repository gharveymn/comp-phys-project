/*     split.c */
/********************************************************************/
/*     Program for data splitting up in isplit sequences            */
/*     isplit = number of splits [1,in+1]                           */
/*     -1. -1. -1. labelled the input end                           */
/*------------------------------------------------------------------*/
/*     Programm zur Datenausgabe in isplit Folgen                   */
/*     isplit = Anzahl der Splits [1,in+1]                          */
/*     -1. -1. -1. kennzeichnet das Eingabeende                     */
/********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define VOL1 1000   /* 1st dimension row    - Zeilenindex  i */
#define VOL2 3      /* 2nd dimension column - Spaltenindex j */

int main(void) 
{
   int    i=0,i1=0,in=0,j,isplit,iprint;
   float  array[VOL1][VOL2];
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

   fscanf(fpein,"%d ", &isplit);                   /* read in isplit */
   for(i=0; i < VOL1; i++) {                       /* read in array */
      for(j=0; j < VOL2; j++) fscanf(fpein,"%f ", &array[i][j]);
      in=i-1;
      if((array[i][0] == array[i][1]) && (array[i][0] == array[i][2])) break;
                           }
   if(isplit < 1 || isplit > in+1) {
      printf("Error isplit out-of-limits\n");
      return(-1);                                  /* EXIT_ERROR_isplit */
                                   }

   for(iprint=1; iprint<=in+1; iprint++) {
      for(i=i1; i <= in; i+=isplit) {              /* write spltted array  */
      for(j=0; j < VOL2; j++) fprintf(fpaus,"%3.8f ",array[i][j]);
      fprintf(fpaus,"\n");
                                    }
   if(isplit == iprint) iprint=in+1;
   i1=i1+1;
   fprintf(fpaus,"      \n");
                                         }

   printf("split EXIT_SUCCESS\n");
   fclose(fpein);
   fclose(fpaus);
   return EXIT_SUCCESS;
}














