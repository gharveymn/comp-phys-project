/*    Profil-circle.c */
/**********************************************************************/
/*  Program for displaying of profile lines                           */
/*                                                                    */
/*  start with:   clink -a Profil                                     */
/*--------------------------------------------------------------------*/
/*  preset onto kp profiles U(y) with n points in y-direction         */
/*  at position x+x0, which are serially located in the input-file    */
/*  in metafl output-file: "pscl","pdf","png" etc.                    */
/**********************************************************************/
/*  Programm zur Darstellung von Profillinien                         */
/*                                                                    */
/*  starten mit:  clink -a Profil                                     */
/*--------------------------------------------------------------------*/
/*  eingestellt auf kp Profile U(y) mit n Punkten in y-Richtung       */
/*  an der Stelle x+x0, die im Eingabe-file hintereinander liegen     */
/*  in metafl den Ausgabe-file: "pscl","pdf","png" etc.               */
/**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "dislin.h"

#define mm 500                 /* maximum dimension of xray[], yray[] */

/*    Profil.h */
/**********************************************************************/
void PLOT(int,float,float *,float *,int);

main()
{
   /*----------------------------- settings --------------------------*/
   int   n=100;                    /* number of points in y-direction */
   int   kp=9;                     /* number of profil data sets      */
   int   n1=29;                    /* points of obstacle definition   */
   float x0=-0.5;                  /* free eligible                   */
                                   /* obstacle coordinates = circle   */
   float xray1[]={2.0,2.02,2.05,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,2.95,
                  2.98,3.0,2.98,2.95,2.9,2.8,2.7,2.6,2.5,2.4,2.3,2.2,2.1,
                  2.05,2.02,2.0};
   float yray1[]={2.5,2.64,2.717944947,2.8,2.9,2.958257569,2.989897949,
                  3.0,2.989897949,2.958257569,2.9,2.8,2.717944947,2.64,
                  2.5,2.36,2.28205505,2.2,2.1,2.041742431,2.010102051,2.0,
                  2.010102051,2.041742431,2.1,2.2,2.28205505,2.36,2.5};
   /*-----------------------------------------------------------------*/
   int   i,k,temp,nn=1;
   float x,xprof[n],yprof[n];
   FILE  *fpein;
   char  *input="profil.in";                  /* input file */

   fpein=fopen(input,"r");                    /* opening the files */
   if(fpein == NULL) {
      printf("Error on opening the file\n");
      exit(-1);                               /* EXIT_ERROR_input_file */
                     }

//   setpag("da4l");
   page(2900,1000);
   metafl("pscl");
   disini();
   pagera();
   psfont("Helvetica");
   pagfll(255);
   axspos(250,800);
   axslen(2400,600);
   labels("none","xy");
   ticks(40,"x");
   ticks(0,"y");
   ticpos("revers","xy");
   penwid(0.3);
   color("black");
   graf(0.,20.,0.,20.,0.,5.,0.,5.);           /* stream area 20 times 5 */
   setclr(229);
   shdpat((long) 16);
   shdcrv(xray1,yray1,n1,xray1,yray1,nn);
   nochek();

   for(k=0; k <= kp-1; k++) {
      fscanf(fpein,"%f",&x);
      for(i=0; i <= n-1; i++) fscanf(fpein,"%f %f %f",&temp,&yprof[i],&xprof[i]);
      PLOT(k,x+x0,&xprof[0],&yprof[0],n);     /* funktion void PLOT() */
                            }

   disfin();
   fclose(fpein);
   printf("flag EXIT_SUCCESS\n");
   return EXIT_SUCCESS;
}

/* Plot of profile lines f(y) at position z    */
/* forward flow = blue , backward flow = green */
void PLOT(int k,float z,float *xprof,float *yprof,int n)
{
   int   i,i1=0,i2=0,i3=0,i4=0,j=0,l;
   float xray[mm],yray[mm];

   for(i=0; i <= n-1; i++) {
      if(xprof[i] == 0 && j == 0)    /* profile will 0 */
         {i1=i+1; j=1;}
      if(xprof[i]  < 0 && j == 0)    /* profile will negative */
         {i1=i+1; j=2;}
      if(xprof[i]  > 0 && j == 1)    /* profile up 0 to positive */
         {i2=i+1; j=3;}
      if(xprof[i]  > 0 && j == 2)    /* profile up negative to positive */
         {i2=i+1; j=6;}
      if(xprof[i] == 0 && j == 2)    /* profile up negative to 0 */
         {i2=i+1; j=5;}
      if(xprof[i]  < 0 && j == 5)    /* profile up 0 to negative */
         {i3=i+1; j=7;}
      if(xprof[i]  > 0 && j == 7)    /* profile up negative to positive */
         {i4=i+1; j=8;}
                           }
   penwid(1.);
   color("blue");

   switch(j)
   {
      case 0:  /* all values >0 */
               for(i=0; i <= n-1; i++) {
                  xray[i]=xprof[i]+z;
                  yray[i]=yprof[i];
                                       }
               curve(xray,yray,n);
               break;

      case 3:  /* values >0 and =0 */
               for(i=0; i <= n-1; i++) {
                  xray[i]=xprof[i]+z;
                  yray[i]=yprof[i];
                                       }
               curve(xray,yray,i1);
               l=-1;
               for(i=i2-2; i <= n-1; i++) {
                  l=l+1;
                  xray[l]=xprof[i]+z;
                  yray[l]=yprof[i];
                                          }
               curve(xray,yray,l+1);
               break;

      case 6:  /* values >0 and <0 */
               for(i=0; i <= n-1; i++) {
                  xray[i]=xprof[i]+z;
                  yray[i]=yprof[i];
                                       }
               curve(xray,yray,i1);
               l=-1;
               i2=i2-1;
               for(i=i1-1; i <= i2-1; i++) {
                  l=l+1;
                  xray[l]=xprof[i]+z;
                  yray[l]=yprof[i];
                                           }
               color("green");
               curve(xray,yray,l+1);
               color("blue");
               l=-1;
               for(i=i2-1; i <= n-1; i++) {
                  l=l+1;
                  xray[l]=xprof[i]+z;
                  yray[l]=yprof[i];
                                          }
               curve(xray,yray,l+1);
               break;

      case 8:  /* values >0 and =0 and <0 */
               for(i=0; i <= n-1; i++) {
                  xray[i]=xprof[i]+z;
                  yray[i]=yprof[i];
                                       }
               curve(xray,yray,i1);
               l=-1;
               i2=i2-1;
               for(i=i1-1; i <= i2-1; i++) {
                  l=l+1;
                  xray[l]=xprof[i]+z;
                  yray[l]=yprof[i];
                                           }
               color("green");
               curve(xray,yray,l+1);
               l=-1;
               i4=i4-1;
               for(i=i3-1; i <= i4-1; i++) {
                  l=l+1;
                  xray[l]=xprof[i]+z;
                  yray[l]=yprof[i];
                                           }
               curve(xray,yray,l+1);
               l=-1;
               for(i=i4-1; i <= n-1; i++) {
                  l=l+1;
                  xray[l]=xprof[i]+z;
                  yray[l]=yprof[i];
                                          }
               color("blue");
               curve(xray,yray,l+1);
               break;

      default:
               printf("k,j,i1,i2,i3,i4: %d %d %d %d %d %d\n",k,j,i1,i2,i3,i4);
               exit(-1);     /* EXIT_ERROR_j */
   }
}

