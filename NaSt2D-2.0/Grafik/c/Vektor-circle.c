/*    Vektor.c */
/****************************************************************/
/*                                                              */
/* Program Vektor.c: Vector picture of the velocity w(u,v)      */
/*                                                              */
/* start with:   clink -a Vektor                                */
/*--------------------------------------------------------------*/
/* input:   lines ni, columns nj of input_file                  */
/*          flow area xlength,ylength                           */
/*          gdf-file of data matrix x1ray[ni],y1ray[ni], etc.   */
/*          in metafl the output-file: "pscl","pdf","png" etc.  */
/****************************************************************/
/*                                                              */
/* Programm Vektor.c: Vektorbild der Geschwindigkeit w(u,v)     */
/*                                                              */
/* starten mit:  clink -a Vektor                                */
/*--------------------------------------------------------------*/
/* Eingabe: Zeilen ni, Spalten nj des Input_Files               */
/*          Stroemungsgebiet xlength,ylength                    */
/*          gdf-file der Datenmatrix x1ray[ni],y1ray[ni],usw.   */
/*          in metafl den Ausgabe-file: "pscl","pdf","png" etc. */
/****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dislin.h"

main()
{
   /*----------------------------- settings --------------------------*/
   int   ni=849;                   /* line number of input_file       */
   int   n1=29;                    /* points of obstacle definition   */
   float xlength=20.,ylength=5.;   /* flow area                       */
                                   /* obstacle coordinates = circle   */
   float xray1[]={2.0,2.02,2.05,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,2.95,
                  2.98,3.0,2.98,2.95,2.9,2.8,2.7,2.6,2.5,2.4,2.3,2.2,2.1,
                  2.05,2.02,2.0};
   float yray1[]={2.5,2.64,2.717944947,2.8,2.9,2.958257569,2.989897949,
                  3.0,2.989897949,2.958257569,2.9,2.8,2.717944947,2.64,
                  2.5,2.36,2.28205505,2.2,2.1,2.041742431,2.010102051,2.0,
                  2.010102051,2.041742431,2.1,2.2,2.28205505,2.36,2.5};
   /*-----------------------------------------------------------------*/
   int   i,nj=6,nn=1;
   float x1ray[ni],y1ray[ni],x2ray[ni],y2ray[ni],x3ray[ni],y3ray[ni];
   char  a[255];
   FILE  *fpein;
   char  *input="vektorkreis.gdf";            /* input file */

   fpein=fopen(input,"r");                    /* opening the files */
   if(fpein == NULL) {
      printf("Error on opening the file\n");
      exit(-1);                               /* EXIT_ERROR_input_file */
                     }

   for(i=0; i <= 2; i++) fgets(a,255,fpein);
   for(i=0; i <= ni-1; i++) {                 /* read in line by line */
      fscanf(fpein,"%f %f %f %f %f %f",
             &x1ray[i],&y1ray[i],&x2ray[i],&y2ray[i],&x3ray[i],&y3ray[i]);
                            }
/*  checkup print:  x1ray etc. (line 1, rows 2,3,4) */
   printf("%10.8f %10.8f %10.8f\n",y1ray[0],x2ray[0],y2ray[0]);

//   setpag("da4l");
   page(2900,1000);
   metafl("pscl");
   disini();
   pagera();
   psfont("Helvetica");
   pagfll(255);
   nobgd();
   axspos(250,800);
   axslen(2400,600);
   labels("none","xy");
   ticks(0,"xy");
   penwid(1.);
   color("black");
   graf(0.,xlength,0.,xlength,0.,ylength,0.,ylength);   /* stream area */
   color("red");
   penwid(0.3);
   nochek();
   field(x1ray,y1ray,x2ray,y2ray,ni,0);
   color("black");
//   color("magenta");
   penwid(3.);
   field(x3ray,y3ray,x2ray,y2ray,ni,0);

   setclr(229);
   shdpat((long) 16);
   shdcrv(xray1,yray1,n1,xray1,yray1,nn);         /* obstacle = circle */
   color("black");
   curve(xray1,yray1,n1);
   title();
   penwid(3.);
   color("cyan");
   shdpat((long) 0);
//   rectan(250,200,2400,600);                                /* framingU */

   disfin();
   fclose(fpein);
   printf("flag EXIT_SUCCESS\n");
   return EXIT_SUCCESS;
}










