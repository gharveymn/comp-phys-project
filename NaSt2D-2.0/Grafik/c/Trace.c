/*    Trace.c */
/********************************************************************/
/* Program for displaying of tracelines                             */
/*                                                                  */
/* start with:  clink -a Trace                                      */
/*------------------------------------------------------------------*/
/*              limited on nj traceline points; with nj it is       */
/*              possible to cut the last physically false points    */
/*              in the diagram                                      */
/*              in metafl output-file: "pscl","pdf","png" etc.      */
/* attention:   mark input end with: stop 5 stop 5                  */
/********************************************************************/
/* Programm zur Darstellung von Bahnlinien                          */
/*                                                                  */
/* starten mit: clink -a Trace                                      */
/*------------------------------------------------------------------*/
/*              Begrenzt auf nj Bahnlinien-Punkte; mit nj ist es    */
/*              moeglich, die letzten, physikalisch falschen Punkte */
/*              in der Darstellung wegzulassen                      */
/*              in metafl den Ausgabe-file: "pscl","pdf","png" etc. */
/* Achtung:     Input-Ende kennzeichnen: stop 5 stop 5              */
/********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dislin.h"

#define nj 50000       /* limit of traceline points */

main()
{
   /*--------------------------- settings -------------------------*/
   int   n1=5;                  /* points of obstacle definition   */
                                /* obstacle coordinates = balken   */
   float xray1[]={6.5833,9.9167,9.9167,6.5833,6.5833};
   float yray1[]={4.05,5.95,5.85,3.95,4.05};
   /*--------------------------------------------------------------*/
   int   ip,j,nn=1;
   float xlength,ylength,time,xp,yp;
   char  a[4];
   FILE  *fpein;
   char  *input="balken.tra";                  /* input file */
   fpein=fopen(input,"r");                     /* opening the file */
   if(fpein == NULL) {
      printf("Error on opening the file\n");
      return(-1);                              /* EXIT_ERROR_file */
                     }

   fscanf(fpein,"%s %f %s %f",&a,&xlength,&a,&ylength);
//   setpag("da4l");
   page(2700,1550);
   metafl("pscl");
   disini();
   pagera();
   psfont("Helvetica");
   pagfll(255);
   axspos(250,1270);
   axslen(2200,1100);
   labels("float","xy");
   labdig(-1,"xy");
   ticks(1,"xy");
   ticpos("labels","xy");
   name("x  [-]","x");
   name("y  [-]","y");
   namdis(60,"x");
   penwid(1.);
   color("black");
                                               /* stream area xlength times ylength */
   graf(0.,xlength,0.,xlength,0.,ylength,0.,ylength);
//   graf(0.,20.,0.,5.,0.,ylength,0.,2.);
   setclr(229);
   shdpat((long) 16);
   shdcrv(xray1,yray1,n1,xray1,yray1,nn);
   hsymbl(1);
   nochek();
   color("blue");

   for(j=1; j <= nj; j++) {
      fscanf(fpein,"%s %f %s %d",&a,&time,&a,&ip);
      if(strcmp(a,"stop") == 0) break;
      if(ip == 0) continue;
      fscanf(fpein,"%f %f",&xp,&yp);
      rlsymb(21,xp,yp);                        /* traceline symbol plot */
      if(j == nj) printf("nj = %d to small\n",nj);
      if(feof(fpein)) break;
                          }
   fclose(fpein);
   disfin();
   printf("flag EXIT_SUCCESS\n");
   return EXIT_SUCCESS;
}
