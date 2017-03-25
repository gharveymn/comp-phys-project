/*    kontur.c */
/********************************************************************/
/*    Program for contour conversion from FIG-data                  */
/*                                                                  */
/*    xlength,ylength:             grid dimension for NaSt2D-2.0    */
/*    xREmin,xREmax,yREmin,yREmax: wrapping rectangle from XFIG     */
/*    xa,ya,ye:                    favored positioning in the grid  */
/*                                 xe follows by proportionality    */
/*    the input  <9999. 1.>  separates the records                  */
/*    the input  <99999. 1.> stops the calculation                  */
/*------------------------------------------------------------------*/
/*    Programm zur Kontur-Umrechnung aus FIG-Daten                  */
/*                                                                  */
/*    xlength,ylength:             Gitterdimension fuer NaSt2D      */
/*    xREmin,xREmax,yREmin,yREmax: einhuellendes Rechteck aus FIG   */
/*    xa,ya,ye:                    gewuenschte Platzierung im Gitter*/
/*                                 xe folgt aus Proportionalitaet   */
/*    die Eingabe <9999. 1.>  trennt die Eingabesaetze              */
/*    die Eingabe <99999. 1.> beendet die Rechnung                  */
/********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define in  1000
#define sep 9999.
#define end 99999.

int main(void) 
{
   int   i,ii=0;
   float mass,xlength=10.,ylength=5.,xa=3.,ya=0.,ye=1.;
   float xREmin=15.,xREmax=8925.,yREmin=15.,yREmax=2775.;
   float x0,y0,x1,y1;
   FILE  *fpein;
   FILE  *fpaus;
   char  *input="Dat.in";               /* input file  */
   char  *output="Dat.out";             /* output file */

   mass=(ye-ya)/(yREmax-yREmin);

   fpein=fopen(input,"r");              /* opening the files */
   fpaus=fopen(output,"w");
   if ((fpein==NULL)||(fpaus==NULL)) {
      printf("Error on opening the files\n");
      return(-1);                       /* EXIT_ERROR_input_file */
                                     }

   for(i=0; i<=in; i++) {
      fscanf(fpein,"%f %f", &x0,&y0);   /* read in line */
      if(x0 == sep) {                   /* separator */
         fprintf(fpaus,"sep\n");
         continue;
                    }
      if(x0 == end) {                   /* data end */
         {i=in; ii=3;}
         break;
                    }
      x1=(x0-xREmin)*mass+xa;           /* scaling */
      y1=(yREmax-y0)*mass;
      fprintf(fpaus,"%1.4f %1.4f\n",x1,y1);
                        }

   if(ii != 3) {
      printf("Error define_in to small\n");
      return(-1);                       /* EXIT_ERROR_define_in */
               }

   printf("kontur EXIT_SUCCESS\n");
   fclose(fpein);
   fclose(fpaus);
   return EXIT_SUCCESS;
}

