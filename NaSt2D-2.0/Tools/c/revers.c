/*     revers.c */
/********************************************************************/
/*     Program for data output in reverse order                     */
/*     -1. -1. -1. labelled the input end                           */
/*------------------------------------------------------------------*/
/*     Programm zur Datenausgabe in umgekehrter Folge               */
/*     -1. -1. -1. kennzeichnet das Eingabeende                     */
/********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define VOL1 1000   /* 1st dimension row    - Zeilenindex i  */
#define VOL2 3      /* 2nd dimension column - Spaltenindex j */

int main(void) 
{
   int    i=0,in=0,j;
   float  array[VOL1][VOL2];
   FILE   *fpein;
   FILE   *fpaus;
   char   *input="ein";           /* input file  */
   char   *output="aus";          /* output file */

   fpein=fopen(input,"r");        /* opening the files */
   fpaus=fopen(output,"w");
   if ((fpein==NULL)||(fpaus==NULL)) {
      printf("Error on opening the files\n");
      return(-1);                 /* EXIT_ERROR_input_file */
                                     }

   for(i=0; i < VOL1; i++) {      /* read in array */
      for(j=0; j < VOL2; j++) fscanf(fpein,"%f ", &array[i][j]);
      in=i;
      if((array[i][0] == array[i][1]) && (array[i][0] == array[i][2])) break;
                           }

   for(i=in; i >= 0; i--) {       /* write array in revers order */
      for(j=0; j < VOL2; j++) fprintf(fpaus,"%3.8f ",array[i][j]);
      fprintf(fpaus,"\n");
                          }

   printf("revers EXIT_SUCCESS\n");
   fclose(fpein);
   fclose(fpaus);
   return EXIT_SUCCESS;
}

