/*     marker.c */
/********************************************************************/
/*     Program for data output with marking the vortex areas        */
/*     -1. -1. -1. labelled the input end                           */
/*------------------------------------------------------------------*/
/*     Programm zur Datenausgabe mit Markierung der Wirbelbereiche  */
/*     -1. -1. -1. kennzeichnet das Eingabeende                     */
/********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define VOL1 20000   /* 1st dimension row    - Zeilenindex i  */
#define VOL2 3       /* 2nd dimension column - Spaltenindex j */

int main(void) 
{
   int    i,in,j,mark[VOL1];
   float  seg,array[VOL1][VOL2];
   FILE   *fpein;
   FILE   *fpaus;
   char   *input="ein";                 /* input file  */
   char   *output="aus";                /* output file */

   fpein=fopen(input,"r");              /* opening the files */
   fpaus=fopen(output,"w");
   if ((fpein==NULL)||(fpaus==NULL)) {
      printf("Error on opening the files\n");
      return(-1);                       /* EXIT_ERROR_input_file */
                                     }

   for(i=0; i < VOL1; i++) {            /* read in array */
      for(j=0; j < VOL2; j++) fscanf(fpein,"%f ", &array[i][j]);
      in=i;
      if((array[i][0] == -1.) && (array[i][1] == -1.) && (array[i][2] == -1.)) break;
                           }
   seg = array[in-1][0];

   for(i=0; i < in; i++) mark[i] = 0;   /* initialization of mark_file */

   for(i=2; i < in; i++) {              /* marking the vortex areas */
      if((array[i][0] == seg)) mark[i+1] = 1;
      if((array[i][0] == array[i-1][0]) && (array[i][0] == array[i-2][0])) {
	mark[i] = 2;
	mark[i-1] = 2;
	mark[i-2] = 2;	
                                                                           }
                         }

   for(i=1; i < in; i++) {
      if ((mark[i] == 2) && (mark[i-1] == 0)) mark[i] = 3;     /* begin of vortex area */
      if ((mark[i] == 0) && (mark[i-1] == 2)) mark[i] = 3;     /* end of vortex area */
                         }

   for(i=0; i < in; i++) {             /* write out array */
        if((mark[i] == 1) || (mark[i] == 3)) fprintf(fpaus,"      \n");  
        for(j=0; j < VOL2; j++) fprintf(fpaus,"%3.8f ",array[i][j]);
        fprintf(fpaus,"\n");
                         }

   printf("marker EXIT_SUCCESS\n");
   fclose(fpein);
   fclose(fpaus);
   return EXIT_SUCCESS;
}

