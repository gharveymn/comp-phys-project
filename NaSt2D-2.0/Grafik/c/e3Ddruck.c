/*    e3Ddruck.c */
/*************************************************************************/
/* Program e3Ddruck.c: surface grid of data matrix (PSI, P etc.)         */
/*                                                                       */
/* start with:    clink -a e3Ddruck                                      */
/*************************************************************************/
/* input:     lines ni, columns nj of the data matrix zmat[j][i]         */
/*            desired lines ni1, columns nj1 of the data matrix zmat1    */
/*            gdf-file with data matrix zmat[j][i] = 3D-data             */
/* attention: the points of data matrix zmat1[j][i] were interpolated    */
/*            bilinear from zmat and form the surface grid               */
/*            in metafl the output file: "pscl","pdf","png","gif" etc.   */
/*************************************************************************/
/* Programm e3Ddruck.for: Oberflaechengitter der Datenmatrix (PSI,P etc.)*/
/*                                                                       */
/* starten mit:   clink -a e3Ddruck                                      */
/*************************************************************************/
/* Eingeben:  Zeilen ni, Spalten nj der Datenmatrix zmat[j][i]           */
/*            gewuenschte Zeilen ni1, Spalten nj1 der Datenmatrix zmat1  */
/*            gdf-file mit der Datenmatrix zmat[j][i] = 3D-Daten         */
/* Achtung:   die Punkte der Datenmatrix zmat1[j][i] werden bilinear     */
/*            aus zmat interpoliert und bilden das Oberflaechengitter    */
/*            in metafl Ausgabe-file: "pscl","pdf","png","gif" etc.      */
/*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "dislin.h"

#define mm 500     /* maximum dimension of static matrix and vectors */

main()
{
   /*----------------------- settings --------------------------*/
   int    ni=100,nj=100;    /* limits of matrix zmat = input    */
   int    ni1=40,nj1=40;    /* limits of matrix zmat1 = drawed  */
   float  Xmin=0.;          /* limit of coordinate system       */
   float  Xmax=1.;          /* limit of coordinate system       */
   float  Ymin=0.;          /* limit of coordinate system       */
   float  Ymax=1.;          /* limit of coordinate system       */
   float  Zmin=0.999899;    /* limit of coordinate system       */
   float  Zmax=1.000101;    /* limit of coordinate system       */
   /*-----------------------------------------------------------*/
   int    i,i1,i2,j,j1,j2,k,l;
   float  xray2[4]={0.,0.,1.,1.},yray2[4]={1.,0.,0.,1.}; /* coordinate system */
   float  zray2[4]={0.9999,0.9999,0.9999,0.9999};
   float  zmat[mm][mm],zmat1[nj1][ni1],xray[mm],yray[mm],xray1[mm],yray1[mm];
   float  b,dx,dx1,dy,dy1;
   char   a[255];
   FILE   *fpein;
   char   *input="Druck.gdf";                            /* input file */

   fpein=fopen(input,"r");                               /* opening the file */
   if(fpein == NULL) {
      printf("Error on opening the file\n");
      return(-1);                                        /* EXIT_ERROR_input_file */
                     }

   for(i=0; i <= 2; i++) fgets(a,255,fpein);
   for(j=0; j <= nj-1; j++)
      for(i=0; i <= ni-1; i++)
         fscanf(fpein,"%f",&zmat[j][i]);                 /* read in zmat[mm][mm] */
/*--------- checkup print: field value zmat[j][i] -------------------------------*/
   printf("1st line, 3rd and 5th field value zmat: %10.8f %10.8f\n",zmat[0][2],zmat[0][4]);

   xray[0]=xray1[0]=yray[0]=yray1[0]=0.;
   {dx=Xmax/(ni-1); dy=Ymax/(nj-1);}
   for(i=1; i <= ni-1; i++) xray[i]=xray[i-1]+dx;
   for(j=1; j <= nj-1; j++) yray[j]=yray[j-1]+dy;
   {dx1=Xmax/(ni1-1); dy1=Ymax/(nj1-1);}
   for(i=1; i <= ni1-1; i++) xray1[i]=xray1[i-1]+dx1;
   for(j=1; j <= nj1-1; j++) yray1[j]=yray1[j-1]+dy1;
   b=1./(dx*dy);

   for(k=0; k <= ni1-1; k++)                             /*  Bilinear interpolation */
      for(l=0; l <= nj1-1; l++) {
         for(i=0; i <= ni-2; i++)
            if(xray1[k] >= xray[i] && xray1[k] <= xray[i+1]) break;
            if(i > ni-1) i=ni-1;
            {i1=i; i2=i+1;}
            for(j=0; j <= nj-2; j++)
               if(yray1[l] >= yray[j] && yray1[l] <= yray[j+1]) break;
               if(j > nj-1) j=nj-1;
               {j1=j; j2=j+1;}
         zmat1[l][k]=b*((xray[i2]-xray1[k])*(yray[j2]-yray1[l])*zmat[j1][i1]+
                        (xray1[k]-xray[i1])*(yray[j2]-yray1[l])*zmat[j1][i2]+
                        (xray[i2]-xray1[k])*(yray1[l]-yray[j1])*zmat[j2][i1]+
                        (xray1[k]-xray[i1])*(yray1[l]-yray[j1])*zmat[j2][i2]);
                                }
/*--------- checkup print: field value zmat1[j][i] -------------------------------*/
   printf("1st line, 3rd and 5th field value zmat1: %10.8f %10.8f\n",zmat1[0][2],zmat1[0][4]);

//   setpag("da4p");
//   page(1700,1600);
   page(1800,1700);
   metafl("ps");
   disini();
   reset("all");
   pagera();
   setvlt("rain");
   eushft("german","!");
   psfont("Times-Italic");
   complx();
   shdcha();
   pagfll(0);
   nobgd();
   pagorg("bottom");
   origin(0,0);
   penwid(7.);
   color("red");
   line(920,435,1045,485);
   line(1510,655,1620,695);
   penwid(0.5);
   color("white");
   axspos(0,0);
   axslen(2000,2000);
   ticks(0,"xy");
   ticks(1,"z");
   ticlen(80,16);
   labels("none","xy");
   labdig(4,"z");
   labdis(50,"z");
   namjus("left","y");
   namdis(150,"x");
   namdis(150,"y");
   namdis(100,"z");
   hname(80);
   name("<-- Fluid flow","x");
   name("   Cavity deep","y");
   name("Pressure [bar]","z");
   height(40);
   messag("Wall",1550,760);

   view3d(8.,7.,2.,"abs");
   graf3d(Xmin,Xmax,0.,1.,Ymin,Ymax,0.,1.,Zmin,Zmax,0.9998,0.0001);
   penwid(7.);
   color("red");
   curv3d(xray2,yray2,zray2,4);
   penwid(0.5);
   color("white");
   box3d();
   grid3d(5,5,"bottom");
   penwid(1.);
   nochek();
   surclr(88,12);
   surmat((float *) zmat1,nj1,ni1,1,1);
   color("black");
   shdpat((long) 16);
   rectan(400,200,100,100);

   disfin();
   fclose(fpein);
   printf("flag EXIT_SUCCESS\n");
   return EXIT_SUCCESS;
}







