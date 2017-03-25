/*    IsoFarb.c */
/***************************************************************************/
/* Program IsoFarb.c: isolines + color-coded distribution of PSI, P etc.   */
/*                                                                         */
/* start with:   clink -a IsoFarb                                          */
/*-------------------------------------------------------------------------*/
/* input:       lines ni, columns nj of the matrix zmat, resp. nj1, ni1    */
/*              number of vortex areas nto                                 */
/*              car color ifa=0/any, i.e. white/yellow                     */
/*              gdf-file of the data matrix zmat[j][i]  =  isolines        */
/*              gdf-file of the data matrix zmat1[j][i] =  pressure        */
/* attention:   zmat1 will be included in the graph of graf3,              */
/*              should also correspond in size !!!                         */
/*              in graf3 are the limits of zmat1;                          */
/*              with dZ1min and dZ1max you can restrict these limits       */
/*              and therewith exclude single values; the values should be  */
/*              chosen so, that achromatic areas are not produced;         */
/*              in metafl the output file: "pscl","pdf","png","gif" etc.   */
/* handling:    in XV AutoCrop and save                                    */
/*              in GIMP: Picture Modus RGB / magi/*wand / color            */
/*              213,213,213 = d5d5d5 on white background and save          */
/*              in XV to 8-Bit color depth and full color compress         */
/***************************************************************************/
/* Programm IsoFarb.c: Isolinien + Farbfl. der Datenmatrix PSI, P etc.     */
/*                                                                         */
/* starten mit:  clink -a IsoFarb                                          */
/*-------------------------------------------------------------------------*/
/* Eingeben:    Zeilen ni, Spalten nj der Matrix zmat, bezw. nj1, ni1      */
/*              Anzahl der Totwassergebiete nto                            */
/*              Autofarbe ifa=0/beliebig, d.h. weiss/gelb                  */
/*              gdf-file der Datenmatrix zmat[j][i]    Isolinien           */
/*              gdf-file der Datenmatrix zmat1[j][i]   Druck               */
/* Achtung:     zmat1 wird in die Diagramm-Flaeche von graf3 eingepasst,   */
/*              muss also mit der Diagramm-Flaeche korrespondieren !!!     */
/*              in graf3 die zmat1-Grenzen;                                */
/*              mit dZ1min und dZ1max lassen sich die Z-Grenzen einengen   */
/*              und damit Einzelwerte ausgrenzen; die Werte sind so zu     */
/*              waehlen, dass keine farblosen Flaechen entstehen;          */
/*              in metafl Ausgabe-file: "pscl","pdf","png","gif" etc.      */
/* Bearbeitung: in XV AutoCrop abspeichern                                 */
/*              in GIMP: Bild Modus RGB / Zauberstab / Farbe               */
/*              213,213,213 = d5d5d5  auf weissem Hintergrund, abspeichern */
/*              in xXV auf 8-Bit Farbtiefe und full color komprimieren     */
/***************************************************************************/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dislin.h"

#define mm 500          /* maximum dimension of static matrix and vectors  */
                        /* stack overflow follows from a to large value mm */
main()
{
   /*--------------------------- settings ---------------------------------*/
   int   ni=204,nj=417;          /* limits of matrix zmat[j][i] = input1   */
   int   ni1=120,nj1=240;        /* limits of matrix zmat1[j][i] = input2  */
   int   nto=0;                  /* number of vortex areas nto             */
   int   ifa=1;                  /* car color ifa=0/any, i.e. white/yellow */
   float Z1min=0.614831984;      /* minimum color value                    */
   float Z1max=0.641207993;      /* maximum color value                    */
   float dZ1min=0.1;             /* shift value                            */
   float dZ1max=0.;              /* shift value                            */
   /*----------------------------------------------------------------------*/
   int   i,j,n,na,nn=1;
   float zmat[mm][mm],zmat1[nj1][ni1],xray[mm],yray[mm];
   char  a[255];
   FILE  *fpein1;
   FILE  *fpein2;
   char  *input1="Isoli.gdf";                      /* input1 file */
   char  *input2="Druck.gdf";                      /* input2 file */

#include "autoBdatInc.c"                           /* program part autoBdatInc.c */

   fpein1=fopen(input1,"r");                       /* opening the files */
   fpein2=fopen(input2,"r");
   if(fpein1 == NULL || fpein2 == NULL) {
      printf("Error on opening the files\n");
      return(-1);                                  /* EXIT_ERROR_input_files */
                                        }

   Z1min=Z1min+dZ1min*(Z1max-Z1min);
   Z1max=Z1max-dZ1max*(Z1max-Z1min);

   for(i=0; i <= 2; i++) fgets(a,255,fpein1);
   for(j=0; j <= nj-1; j++)
      for(i=0; i <= ni-1; i++)
         fscanf(fpein1,"%f",&zmat[j][i]);          /* read in zmat[mm][mm] */
/*--------- checkup print: field value zmat[j][i] -------------------------------*/
   printf("1st line, 3rd and 5th field value zmat: %f %f\n",zmat[0][2],zmat[0][4]);

   for(i=0; i <= 2; i++) fgets(a,255,fpein2);
   for(j=0; j <= nj1-1; j++)
      for(i=0; i <= ni1-1; i++)
         fscanf(fpein2,"%f",&zmat1[j][i]);         /* read in zmat1[nj1][ni1] */
/*--------- checkup print: field value zmat1[j][i] ---------------------------------*/
   printf("1st line, 3rd and 5th field value zmat1: %f %f\n",zmat1[0][2],zmat1[0][4]);

   setpag("da4l");
//   page(2710,690);
   metafl("pscl");
   disini();
   pagera();
   bmpfnt("complex");
   psfont("Helvetica");
   pagfll(255);
   nobgd();
   autres(ni1,nj1);
   axspos(100,720);
   ax3len(2100,700,700);
   labels("none","xy");
   ticks(0,"xy");
   penwid(1.);
   graf3(2.,8.,2.,2.,0.,2.,0.,1.,Z1min,Z1max,Z1min,50.);
   crvmat((float *) zmat1,nj1,ni1,1,1);

   if(nto > 0) {                                  /* vortex marker */
   penwid(1.);
   color("yellow");
   for(j=2; j <= 2*nto; j=j+2) {
      n=(int) zmat[j][0];
      for(i=0; i <= n-1; i++) {
         xray[i] = zmat[i][j];
         yray[i] = zmat[i][j+1];
                              }
   shdpat((long) 16);
   shdcrv(xray,yray,n,xray,yray,nn);
                               }
               }

//   penwid(1.);
   penwid(0.3);
   color("black");
   nochek();
   na=2*nto+3;
   for(j=na-1; j <= ni-1; j=j+2) {               /* isoline plot */
      n=(int) zmat[j][0];
      for(i=0; i <= n-1; i++) {
         xray[i] = zmat[i][j];
         yray[i] = zmat[i][j+1];
                              }
      curve(xray,yray,n);
                                 }

   title();
   penwid(3.);
   color("cyan");
   shdpat((long) 0);
   rectan(100,20,2275,705);                      /* flow area framing */

#include "autoBplotInc.c"                        /* program part autoBplotInc.c */

   height(36);
   messag("-",2240,680);
   messag("+",2240,30);
   angle(90);
   messag("pressure",2225,500);

   disfin();
   fclose(fpein1);
   fclose(fpein2);
   printf("flag EXIT_SUCCESS\n");
   return EXIT_SUCCESS;
}















