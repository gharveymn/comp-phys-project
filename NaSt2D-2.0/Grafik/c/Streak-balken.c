/*    Streak-balken.c */
/*******************************************************************/
/* Program for displaying of streaklines                           */
/*                                                                 */
/* start with: clink -a Streak                                     */
/*-----------------------------------------------------------------*/
/*             limited on nj output-pictures resp. time steps      */
/*             in metafl output-file: "pscl","pdf","png" etc.      */
/* attention:  mark input end with: stop 5 stop 5                  */
/*-----------------------------------------------------------------*/
/* rename pictures under LINUX in indicated sequence:              */
/* for i in disli_*; do mv $i disl_0${i#disli_}; done              */
/* for i in dislin_*; do mv $i disl_00${i#dislin_}; done           */
/*******************************************************************/
/* Programm zur Darstellung von Streichlinien                      */
/*                                                                 */
/* starten mit: clink -a Streak                                    */
/*-----------------------------------------------------------------*/
/*             Begrenzt auf nj Ausgabebilder bzw. Zeitschritte     */
/*             in metafl den Ausgabe-file: "pscl","pdf","png" etc. */
/* Achtung:    Input-Ende kennzeichnen: stop 5 stop 5              */
/*-----------------------------------------------------------------*/
/* Umbenennen der Bilder unter LINUX in angegebener Reihenfolge:   */
/* for i in disli_*; do mv $i disl_0${i#disli_}; done              */
/* for i in dislin_*; do mv $i disl_00${i#dislin_}; done           */
/*******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dislin.h"

#define nj 1000       /* limit of output-pictures resp. time steps */

main()
{
   /*--------------------------- settings -------------------------*/
   int   n1=5;                  /* points of obstacle definition   */
                                /* obstacle coordinates = balken   */
   float xray1[]={6.5833,9.9167,9.9167,6.5833,6.5833};
   float yray1[]={4.05,5.95,5.85,3.95,4.05};
   /*--------------------------------------------------------------*/
   int   i,in,ip,j,n,nn=1,status;
   float xlength,ylength,time,xp,yp;
   char  a[4],c[4];
   FILE  *fpein1;
   FILE  *fpein2;
   FILE  *fpaus;
   char  *input1="balken.str";                /* input1 file */
   char  *input2="Temp";                      /* input2 file */
   char  *output="Temp";                      /* output file */
   fpein1=fopen(input1,"r");                  /* opening the files */
   fpaus=fopen(output,"w");
   if(fpein1 == NULL || fpaus == NULL) {
      printf("Error on opening the files\n");
      return(-1);                              /* EXIT_ERROR_files */
                                       }

   fscanf(fpein1,"%s %f %s %f %s %s %s %s %s %s %s %s %s %d",
                &a,&xlength,&a,&ylength,&a,&a,&a,&a,&a,&a,&a,&a,&a,&n);
   for(j=1; j <= nj; j++) {
//   setpag("da4l");
   page(2700,1550);
   metafl("png");
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

   for(in=1; in <= n; in++) {
      fscanf(fpein1,"%s %f %s %d",&a,&time,&a,&ip);
      if(strcmp(a,"stop") == 0) break;
      for(i=1; i <= ip; i++) {
         fscanf(fpein1,"%f %f",&xp,&yp);
         rlsymb(21,xp,yp);                    /* streakline symbol plot */
                             }
                            }
   color("black");
   messag("Time:",290,120);
   fprintf(fpaus,"%5.2f \n",time);
   fclose(fpaus);
   fpein2=fopen(input2,"r");
   fscanf(fpein2,"%s",&c);
   messag(c,490,120);
   fclose(fpein2);
   fpaus=fopen(output,"w");
   disfin();
   if(feof(fpein1)) break;
                          }

   fclose(fpein1);
   fclose(fpaus);                                    /* rename pictures */
   status=system("for i in disli_*; do mv $i disl_0${i#disli_}; done");
   status=system("for i in dislin_*; do mv $i disl_00${i#dislin_}; done");
   printf("Streak-balken EXIT_SUCCESS\n");
   return EXIT_SUCCESS;
}

