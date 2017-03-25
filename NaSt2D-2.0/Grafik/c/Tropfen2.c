/*    Tropfen2.c */
/*******************************************************************/
/* Program for generating the droplet images                       */
/*                                                                 */
/* start with: clink -a Tropfen2                                   */
/*-----------------------------------------------------------------*/
/*             limited on nj output-pictures resp. time steps      */
/*             in metafl output-file: "pscl","pdf","png" etc.      */
/* attention:  mark input end with: stop 5 stop 5                  */
/*-----------------------------------------------------------------*/
/* rename pictures under LINUX in indicated sequence:              */
/* for i in disli_*; do mv $i disl_0${i#disli_}; done              */
/* for i in dislin_*; do mv $i disl_00${i#dislin_}; done           */
/*******************************************************************/
/* Programm zur Erzeugung der Tropfenbilder                        */
/*                                                                 */
/* starten mit: clink -a Tropfen2                                  */
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
   int   i,n,ip,j;
   float xlength,ylength,time1,time2,xp,yp;
   char  a[4],c[8];
   FILE  *fpein;
   FILE  *ftemp;                             
   char  *input="tropfen.str";               /* input file */
   char  *temp="dat.temp";                   /* temporary file */
   fpein=fopen(input,"r");                   /* opening the input file */
   if(fpein == NULL) {
      printf("Error on opening the input file\n");
      return(-1);                            /* EXIT_ERROR_files */
                     }

   fscanf(fpein,"%s %f %s %f %s %s %s %s %s %s %s %s %s %d",
                &a,&xlength,&a,&ylength,&a,&a,&a,&a,&a,&a,&a,&a,&a,&n);
   if(n != 3) return(-2);                    /* DATA inconsistent */
   for(j=1; j <= nj; j++) {
   setpag("da4l");
//   page(2700,1550);
   metafl("gif");
   disini();
   pagera();
//   psfont("Helvetica");
   pagfll(255);
   axspos(280,1800);
   axslen(2200,1650);
   labels("none","xy");
   ticks(0,"xy");
   penwid(1.);
   color("black");
                                   /* stream area xlength times ylength */
   graf(0.,xlength,0.,xlength,0.,ylength,0.,ylength);
/* symboles draw for N=3 streaklines */
   hsymbl(8);
   nochek();
   color("blue");

      fscanf(fpein,"%s %f %s %d",&a,&time1,&a,&ip);
      if(strcmp(a,"stop") == 0) break;
      for(i=1; i <= ip; i++) {
         fscanf(fpein,"%f %f",&xp,&yp);
         rlsymb(21,xp,yp);                    /* streakline symbol plot */
                             }
   color("red");
      fscanf(fpein,"%s %f %s %d",&a,&time2,&a,&ip);
      if(time2 != time1) printf("Time %f %f\n",time2,time1);
      for(i=1; i <= ip; i++) {
         fscanf(fpein,"%f %f",&xp,&yp);
         rlsymb(21,xp,yp);                     
                             }
   color("green");
      fscanf(fpein,"%s %f %s %d",&a,&time2,&a,&ip);
      if(time2 != time1) printf("Time %f %f\n",time2,time1);
      for(i=1; i <= ip; i++) {
         fscanf(fpein,"%f %f",&xp,&yp);
         rlsymb(21,xp,yp);                     
                             }                             
   color("black");
   messag("Time:",290,200);
   ftemp=fopen(temp,"w+");                    /* opening the temporary file */
   fprintf(ftemp,"%f\n",time1);
   rewind(ftemp);
   fscanf(ftemp,"%s",&c);
   fclose(ftemp);
   messag(c,490,200);
   disfin();                         }
   fclose(fpein);
   printf("Tropfen2 EXIT_SUCCESS\n");
   return EXIT_SUCCESS;
}

