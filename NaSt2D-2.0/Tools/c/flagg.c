/*    flag.c */
/********************************************************************/
/*    Straight line calculation from sequent point couples          */
/*    the input <9999. 1.>  separates the records                   */
/*    the input <99999. 1.> stops the calculation                   */
/*------------------------------------------------------------------*/
/*    Geradenberechnung aus aufeinander folgenden Punktepaaren      */
/*    die Eingabe <9999. 1.>  trennt die Eingabesaetze              */
/*    die Eingabe <99999. 1.> beendet die Rechnung                  */
/********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define in  100
#define sep 9999.
#define end 99999.

int main(void) 
{
   int   i,ii=0;
   float x,x1,x2,y,y1,y2,z1,z2,z3,z4;
   FILE  *fpein;
   FILE  *fpaus;
   char  *input="Dat.in";                /* input file  */
   char  *output="Dat.out";              /* output file */

   fpein=fopen(input,"r");               /* opening the files */
   fpaus=fopen(output,"w");
   if ((fpein==NULL)||(fpaus==NULL)) {
      printf("Error on opening the files\n");
      return(-1);                        /* EXIT_ERROR_input_file */
                                     }
   for(i=0; i<=in; i++) {
   if(ii == 0) {
      fscanf(fpein,"%f %f", &x,&y);      /* read in 1st line */
      {x1=x; y1=y; ii=1;}
               }

   if(ii == 1) {
      fscanf(fpein,"%f %f", &x,&y);      /* read in next line */
      if(x == sep) {                     /* separator */
         ii=0;
         fprintf(fpaus,"sep\n");
         continue;
                   }
      if(x == end) {                     /* data end */
         {i=in; ii=3;}
         break;
                   }
      {x2=x; y2=y;}
               }

      if(x1 == x2) {                     /* vertical line */
         fprintf(fpaus,"vertical  at  x = %1.5f    in-between  y: %1.5f %1.5f\n",x1,y1,y2);
         {x1=x2; y1=y2;}
         continue;
                   }
      if(y1 == y2) {                     /* horizontal line */
         fprintf(fpaus,"horizontal at y = %1.5f    in-between  x: %1.5f %1.5f\n",y1,x1,x2);
         {x1=x2; y1=y2;}
         continue;
                   }
      if(x1 != x2 && y1 != y2) {         /* straight line */
         {z1=(y1-y2)/(x1-x2); z2=y1-x1*(y1-y2)/(x1-x2); z3=1./z1; z4=-z2/z1;}
         fprintf(fpaus,"y = %1.5f *x + %1.5f   x = %1.5f *y + %1.5f\n",z1,z2,z3,z4);
         {x1=x2; y1=y2;}
         continue;
                               }
                        }

   if(ii != 3) {
      printf("Error define_in to small\n");
      return(-1);                        /* EXIT_ERROR_define_in */
               }

   printf("flag EXIT_SUCCESS\n");
   fclose(fpein);
   fclose(fpaus);
   return EXIT_SUCCESS;
}

