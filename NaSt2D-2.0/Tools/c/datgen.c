/*    datgen.c */
/****************************************************************************/
/*    Program creates input files for GNUPLOT and DISLIN                    */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*    mod = 1  GNUPLOT-3D data                                              */
/*          2  GNUPLOT isolines (for PSI, ZETA, etc.)                       */
/*          3  DISLIN-3D data                                               */
/*          4  DISLIN vector-data with scaling (sclf)                       */
/*          5  DISLIN isolines (for PSI, ZETA, etc.)                        */
/*          6  DISLIN isolines from GNUPLOT isolines                        */
/*          7  Profile data x[i],y[j],z[j][i] for i or j constant           */
/*    epar     input field, e.g. U,V,UV,TEMP,P,PSI,ZETA etc.                */
/*    ipr      interpolation either at x or at y constant                   */
/*    ixmax    maximum number of points in x-direction                      */
/*    iymax    maximum number of points in y-direction                      */
/*    xlength  grid length in x-direction [-]                               */
/*    ylength  grid length in y-direction [-]                               */
/*    delxw    thickness of viscous sublayer west, east [-]                 */
/*    delyw    thickness of viscous sublayer north, south [-]               */
/*    isoa     iso initial value                                            */
/*    isoe     iso end valua                                                */
/*    diso     iso increment                                                */
/*    sclf     vector scaling factor                                        */
/*                                                                          */
/*    input file    <Dat.in> should contain:                                */
/*    generally:    mod,epar,ipr,ixmax,iymax,xlength,ylength,delxw,delyw    */
/*                  z[j][i]                           mod= 1,3              */
/*                  an addend z0 (for mod 3) free selectable                */
/*                          = U[j][i]                      4                */
/*                          = PSI[j][i] or ZETA[j][i]      2 resp. 5        */
/*    additionally: V[j][i]                                4                */
/*                  isoa,isoe,diso                         2 resp. 5        */
/*                  sclf                                   4                */
/*                  ik,jk                                  7                */
/*                  ik resp. jk specify the interpolation position          */
/*    attention:    the other value ik or jk should be -1                   */
/*                                                                          */
/*    in event of                                     mod= 6                */
/*    generally:    mod,epar,ipr,ixmax,iymax,xlength,ylength,delxw,delyw    */
/*                  GNUPLOT data file                                       */
/*                  with -1. -1. -1.   after "each" record                  */
/*                       -2. -2. -2.   the data end                         */
/*                                                                          */
/****************************************************************************/
/*    Programm erstellt Eingabedateien fuer GNUPLOT und DISLIN              */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*    mod = 1  GNUPLOT-3D-Daten                                             */
/*          2  GNUPLOT-Isolinien (fuer PSI, ZETA etc.)                      */
/*          3  DISLIN-3D-Daten                                              */
/*          4  DISLIN-Vektor-Daten mit Skalierung (sclf)                    */
/*          5  DISLIN-Isolinien (fuer PSI, ZETA etc.)                       */
/*          6  DISLIN-Isolinien aus GNUPLOT-Isolinien                       */
/*          7  Profildaten x[i],y[j],z[j][i] fuer i oder j konstant         */
/*    epar     Eingabefeld, z.B. U,V,UV,TEMP,P,PSI,ZETA etc.                */
/*    ipr      Interpolation entweder bei x oder bei y konstant             */
/*    ixmax    max. Punktezahl in x-Richtung                                */
/*    iymax    max. Punktezahl in y-Richtung                                */
/*    xlength  Gebietslaenge in x-Richtung [-]                              */
/*    ylength  Gebietslaenge in y-Richtung [-]                              */
/*    delxw    Dicke der viskosen Unterschicht W,O [-]                      */
/*    delyw    Dicke der viskosen Unterschicht N,S [-]                      */
/*    isoa     iso-Anfangswert                                              */
/*    isoe     iso-Endwert                                                  */
/*    diso     iso-Inkrement                                                */
/*    sclf     Vektor Skalierungsfaktor                                     */
/*                                                                          */
/*    Eingabefile   <Dat.in> muss enthalten:                                */
/*    allgemein:    mod,epar,ipr,ixmax,iymax,xlength,ylength,delxw,delyw    */
/*                  z([j][i]                          mod= 1,3              */
/*                  ein Additionswert z0 (fuer mod 3) ist frei waehlbar     */
/*                          = U[j][i]                      4                */
/*                          = PSI[j][i] oder ZETA[j][i]    2 bzw.5          */
/*    zusaetzlich:  V[j][i]                                4                */
/*                  isoa,isoe,diso                         2 bzw.5          */
/*                  sclf                                   4                */
/*                  ik,jk                                  7                */
/*                  ik oder jk spezifizieren die Interpolations-Stelle      */
/*    Achtung:      der andere Wert ik oder jk muss -1 sein                 */
/*                                                                          */
/*    im Fall von                                     mod= 6                */
/*    allgemein:    mod,epar,ipr,ixmax,iymax,xlength,ylength,delxw,delyw    */
/*                  GNUPLOT-Datenfile                                       */
/*                  mit  -1. -1. -1.   nach "jedem" Datenblock              */
/*                       -2. -2. -2.   als Datenende                        */
/****************************************************************************/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*    datgen.h */
/****************************************************************************/
double INTERPOL(float,double *,double *,int,int);
int ORDNE(float *,float *,int,float *,float *);
int is,iflag,ie1;

int main(void)
{
   extern int is,iflag,ie1;

   /*----------------------------------- settings ------------------------------------*/
   int    nn=51;        /* set nn = max(ixmax,iymax)+1, at mod=6 higher here and     */
                         /* in Dat.in, if necessary                                   */
   int    ip=2;          /* ip = 1 or 2: simply or multiple interpolation of isolines */
   int    io=1;          /* io = 1 or 0: isolines put in order or not,                */
                         /* put in order is important for closed isolines             */
   int    ii=20,jj=3;    /* limitation of vector output: example jj=2 considered in   */
                         /* y-direction only every second vector value (for mod 4)    */
   float  xa=0.,xe=2.;   /* DISLIN-3D data for diagram sections                       */
   float  ya=0.,ye=1.;   /* xa,xe,ya,ye are the section coordinates                   */
   float  z0=50.;        /* z0 = addend value (for mod 3), free selectable            */
   /*---------------------------------------------------------------------------------*/
   int    i,j,i1,i2,ia,ie,ja,je,ij,in,ik,jk,ispe,ixmax,iymax,np,mod;
   int    iad=0,isp=0,iemax=0,dis=2;
   float  iso,isoa,isoe,diso,integ0,integ1,integn,integz;
   float  xlength,ylength,delxw,delyw,zmin,zmax,dx,dy,sclf;
   float  x1[nn*nn],x2[nn*nn],x3[nn*nn],y1[nn*nn],y2[nn*nn],y3[nn*nn];
   float  alf[nn][nn],v[nn][nn],w[nn][nn],z[nn][nn],dfeld[2*nn][2*nn];
   float  xx[2*nn],yy[2*nn],xx1[2*nn],yy1[2*nn];
   float  xmin=0.,ymin=0.,pi=2.*asin(1.);
   double x[nn],y[nn],zz[nn];
   char   epar[4],ipr[4],*par[]={"U","ZETA","PSI","HEAT"},*def[]={"%GCL-ASC","%DATA"};
   FILE   *fpein;
   FILE   *fpaus1;
   FILE   *fpaus2;
   char   *input="Dat.in";               /* input   file */
   char   *output1="Dat.out";            /* output1 file */
   char   *output2="Dat.out1";           /* output2 file */

   fpein=fopen(input,"r");               /* opening the files */
   fpaus1=fopen(output1,"w");
   fpaus2=fopen(output2,"w");
   if((fpein==NULL)||(fpaus1==NULL)||(fpaus2==NULL)) {
      printf("Error on opening the files\n");
      return(-1);                        /* EXIT_ERROR_input_files */
                                                     }

                                         /* read in 1st line */
   fscanf(fpein,"%d %s %s %d %d %f %f %f %f",&mod,&epar,&ipr,&ixmax,&iymax,&xlength,&ylength,&delxw,&delyw);
   if(xe <= 0.) xe=xlength;
   if(ye <= 0.) ye=ylength;
   if(mod != 3) z0=0.;
   if(mod == 5) {mod=2; dis=5;}
   if(mod != 6) {
      if(strcmp(epar,par[1]) == 0) iad=-1;
      if(strcmp(epar,par[2]) == 0 || strcmp(epar,par[3]) == 0) iad=+1;
      ixmax=ixmax+iad;
      iymax=iymax+iad;
      if(ixmax > nn || iymax > nn) {
         printf("Field dimensioning to small\n");
         return(-1);                    /* EXIT_ERROR_field_dimensioning */
                                   }

      for(j=0; j <= iymax-1; j++)
         for(i=0; i <= ixmax-1; i++)
            fscanf(fpein,"%f",&z[j][i]);         /* read in z[nn][nn]    */
//*--------- checkup print: first and last field value z[j][i] ----------*/
      fprintf(fpaus1,"first and last field value of %s %f %f with z0 = %f\n",epar,z[0][0],z[iymax-1][ixmax-1],z0);
      for(j=0; j <= iymax-1; j++)
         for(i=0; i <= ixmax-1; i++) {
            z[j][i]=z[j][i]+z0;                  /* add z0 */
            if(z[j][i] == 0. || z[j][i] != z0) zmin=z[j][i];
                                     }
      zmax=zmin;
      for(j=0; j <= iymax-1; j++)
         for(i=0; i <= ixmax-1; i++)
         if(z[j][i] != 0. && z[j][i] != z0) {
            if(z[j][i] < zmin) zmin=z[j][i];     /* search for zmin and zmax */
            if(z[j][i] > zmax) zmax=z[j][i];
                                            }

      dx=(xlength-2.*delxw)/(float)(ixmax-1);    /* coordinates x[j] and y[i] */
      dy=(ylength-2.*delyw)/(float)(iymax-1);
      xmin=xmin+delxw;
      x[0]=xmin;
      for(i=1; i <= ixmax-1; i++) x[i]=x[i-1]+dx;
      ymin=ymin+delyw;
      y[0]=ymin;
      for(j=1; j <= iymax-1; j++) y[j]=y[j-1]+dy;
                }

   switch(mod)
   {
      case 1:           /* GNUPLOT-3D data */
      /* -------------------------------------------------------- */
               fprintf(fpaus1,"z-limits without 0. resp. z0: %f %f\n",zmin,zmax);
               for(i=0; i <= ixmax-1; i++)
                  for(j=0; j <= iymax-1; j++) fprintf(fpaus1,"%f %f %f\n",x[i],y[j],z[j][i]);
               break;

      case 2:           /* GNUPLOT isolines (for PSI, ZETA, etc.) */
      /* -------------------------------------------------------- */
               fprintf(fpaus1,"iso-limits without 0.: %f %f\n",zmin,zmax);
               fscanf(fpein,"%f %f %f",&isoa,&isoe,&diso);
               fprintf(fpaus1,"start, end, incr.: %f %f %f\n",isoa,isoe,diso);
               iso=isoa;
               while(iso <= isoe*1.0001){
                  ij=0;
                  if(strcmp(ipr,"x") == 0) {                  /* interpolation at x constant */
                  for(i=0; i <= ixmax-1; i++) {
                     for(j=0; j <= iymax-1; j++) zz[j]=z[j][i];
                     yy[ij]=INTERPOL(iso,&y[0],&zz[0],iymax,3);
                     xx[ij]=x[i];
                     if(iflag == 0) ij++;
                     if(is >= iymax) continue;
                     if(ip == 2) {
                        do{yy[ij]=INTERPOL(iso,&y[0],&zz[0],iymax,is+1);
                           xx[ij]=x[i];
                           if(iflag == 0) ij++;
                          }while(is < iymax);
                                 }
                                              }
                                           }
                  if(strcmp(ipr,"y") == 0) {                  /* interpolation at y constant */
                  for(j=0; j <= iymax-1; j++) {
                     for(i=0; i <= ixmax-1; i++) zz[i]=z[j][i];
                     xx[ij]=INTERPOL(iso,&x[0],&zz[0],ixmax,3);
                     yy[ij]=y[j];
                     if(iflag == 0) ij++;
                     if(is >= ixmax) continue;
                     if(ip == 2) {
                        do{xx[ij]=INTERPOL(iso,&x[0],&zz[0],ixmax,is+1);
                           yy[ij]=y[j];
                           if(iflag == 0) ij++;
                          }while(is < ixmax);
                                 }
                                              }
                                           }
                  ie=ij;
                  if(ie > 2 && io == 1) {            /* closed isolines put in order */
                  ie1=2*nn;
                  if(strcmp(ipr,"x") == 0) ORDNE(&xx[0],&yy[0],ie,&xx1[0],&yy1[0]);
                  if(strcmp(ipr,"y") == 0) ORDNE(&yy[0],&xx[0],ie,&yy1[0],&xx1[0]);
                  ie=ie1;
                  for(i=0; i <= ie-1; i++) {xx[i]=xx1[i]; yy[i]=yy1[i];}
                                        }
                  if(ie > 0) {
                     if(dis == 2) {
                        for(i=0; i <= ie-1; i++) fprintf(fpaus1,"%f %f %f\n",xx[i],yy[i],iso);
                        fprintf(fpaus1,"      \n");
                                  }

                     if(dis == 5) {                  /* case 5: DISLIN isolines (for PSI, ZETA, etc.) */
                     if(iemax < ie-1) iemax=ie-1;
                     isp=isp+2;
                     ispe=isp+1;
                     dfeld[0][isp]=ie;
                     dfeld[0][isp+1]=ie;
                     dfeld[1][isp]=iso;
                     dfeld[1][isp+1]=iso;
                     for(j=0; j <= ie; j++) {dfeld[isp][j]=xx[j]; dfeld[isp+1][j]=yy[j];}
                                  }
                             }
                  iso=iso+diso;
                                        }
                  if(dis == 2) break;

                  if(iemax < ispe) iemax=ispe;       /* case 5: DISLIN isolines (for PSI, ZETA, etc.) */
                  fprintf(fpaus1,"%s\n",def[0]);
                  fprintf(fpaus1,"%s\n",def[1]);
                  fprintf(fpaus1,"%d // number of lines %d  number of columns %d\n",ispe+1,iemax+1,ispe+1);
                  for(j=0; j <= iemax; j++) {
                     for(isp=0; isp <= ispe; isp++) fprintf(fpaus1,"%f ",dfeld[isp][j]);
                     fprintf(fpaus1,"\n");
                                            }
                  /*--------- checkup print: ----------*/
                  for(j=0; j <= ispe; j++) {
                     np=(int)(dfeld[0][j]);
                     fprintf(fpaus2,"line,number,level: %d %d %f\n",j,np,dfeld[1][j]);
                                           }
               break;

      case 3:           /* DISLIN-3D data (diagram section) */
      /* -------------------------------------------------------- */
               fprintf(fpaus1,"diagram section xa,xe,ya,ye: %f %f %f %f\n",xa,xe,ya,ye);
               fprintf(fpaus1,"z-limits without 0. resp. z0: %f %f\n",zmin,zmax);
               fprintf(fpaus1,"%s\n", def[0]);
               fprintf(fpaus1,"%s\n", def[1]);
               ia=ixmax*(xa/xlength);
               ie=ixmax*(xe/xlength);
               ja=iymax*(ya/ylength);
               je=iymax*(ye/ylength);
               fprintf(fpaus1,"%d // number of lines  %d  number of columns %d\n",je-ja,ie-ia,je-ja);
               for (i = ia; i <= ie-1; i++){
                  for (j = ja; j <= je-1; j++) fprintf(fpaus1,"%f ",z[j][i]);
                  fprintf(fpaus1,"\n");
                                           }
               break; 

      case 4:           /* DISLIN vector-data with scaling (sclf) */
      /* -------------------------------------------------------- */
               for(j=0; j <= iymax-1; j++)
                  for(i=0; i <= ixmax-1; i++) fscanf(fpein,"%f",&v[j][i]);         /* read in v[nn][nn] */
               fscanf(fpein,"%f",&sclf);
               /*--------- checkup print: first and last field value z[j][i] ----------*/
               fprintf(fpaus1,"first and last field value of V %f %f sclf = %f\n",v[0][0],v[iymax-1][ixmax-1],sclf);
               for(i=0; i <= ixmax-1; i++)
                  for(j=0; j <= iymax-1; j++) w[j][i]=sqrt(z[j][i]*z[j][i] + v[j][i]*v[j][i]);
               in=-1;
               for(i=0; i <= ixmax-1; i=i+ii) {            /* increase the start value of i generates towards x moving vectors */
                  for(j=0; j <= iymax-1; j=j+jj) {         /* increase the start value of j generates towards y moving vectors */
                  in++;
                  if(z[j][i] < 0.) {
                     if(v[j][i] >= 0.) alf[j][i]=pi-atan(fabs(v[j][i]/z[j][i]));
                     if(v[j][i] < 0.)  alf[j][i]=pi+atan(fabs(v[j][i]/z[j][i]));
                                   }
                  if(z[j][i] == 0.) {
                     if(v[j][i] < 0.)  alf[j][i]=-pi;
                     if(v[j][i] == 0.) alf[j][i]=0.;
                     if(v[j][i] > 0.)  alf[j][i]=pi;
                                    }
                  if(z[j][i] > 0.) {
                     if(v[j][i] >= 0.) alf[j][i]=atan(fabs(v[j][i]/z[j][i]));
                     if(v[j][i] < 0.)  alf[j][i]=-atan(fabs(v[j][i]/z[j][i]));
                                   }
               /*--------- checkup print: ----------*/
//               fprintf(fpaus1,"%d %f %f %f %f %f\n",in,x[i],y[j],w[j][i],alf[j][i],alf[j][i]*180./pi);

               x1[in]=x[i];
               y1[in]=y[j];
               x2[in]=x[i]+w[j][i]*sclf*cos(alf[j][i]);
               y2[in]=y[j]+w[j][i]*sclf*sin(alf[j][i]);
               x3[in]=x[i]+w[j][i]*0.95*sclf*cos(alf[j][i]);
               y3[in]=y[j]+w[j][i]*0.95*sclf*sin(alf[j][i]);
                                                 }
                                              }
               fprintf(fpaus1,"%s\n",def[0]);
               fprintf(fpaus1,"%s\n",def[1]);
               fprintf(fpaus1,"%d // scaling %f  max. %d  xStart, yStart, xEnd, yEnd ...\n",6,sclf,in);
               for(i=0; i <= in; i++) fprintf(fpaus1,"%f %f %f %f %f %f\n",x1[i],y1[i],x2[i],y2[i],x3[i],y3[i]);
               break; 

      case 6:           /* DISLIN isolines from GNUPLOT isolines */
      /* ------------------------------------------------------- */

      for(i=0; i <= 2*nn-1; i++) {
                  fscanf(fpein,"%f %f %f",&xx[i],&yy[i],&isoa);            /* read in line by line */
                  if(xx[i] == -1. && yy[i] == -1. && isoa == -1.) {        /* end of block */
                     ie=i-1;
                     if(iemax < ie) iemax=ie;
                     isp=isp+2;
                     ispe=isp+1;
                     dfeld[0][isp]=ie;
                     dfeld[0][isp+1]=ie;
                     dfeld[1][isp]=iso;
                     dfeld[1][isp+1]=iso;
                     for(j=0; j <= ie; j++) {dfeld[isp][j]=xx[j]; dfeld[isp+1][j]=yy[j];}
                     i=-1;
                                                                  }
                  iso=isoa;
                  if(xx[i] == -2. && yy[i]  == -2. && iso == -2.) {        /* end of file */
                     if(iemax < ispe) iemax=ispe;
                     fprintf(fpaus1,"%s\n",def[0]);
                     fprintf(fpaus1,"%s\n",def[1]);
                     fprintf(fpaus1,"%d // number of lines %d  number of columns %d\n",ispe+1,iemax+1,ispe+1);
                     for(j=0; j <= iemax; j++) {
                        for(isp=0; isp <= ispe; isp++) fprintf(fpaus1,"%f ",dfeld[isp][j]);
                        fprintf(fpaus1,"\n");
                                               }
                     /*--------- checkup print: ----------*/
                     for(j=0; j <= ispe; j++) {
                        np=(int)(dfeld[0][j]);
                        fprintf(fpaus2,"line,number,level: %d %d %f\n",j,np,dfeld[1][j]);
                                              }
               break;
                                                                  }
                                        }
               break; 

      case 7:           /* Profile data x[i],y[j],z[j][i] for i or j constant */
      /* -------------------------------------------------------------------- */
               fscanf(fpein,"%d %d",&ik,&jk);
               fprintf(fpaus1,"%s at position i,j: %d %d\n",epar,ik,jk);
               i1=-1;
               i2=-1;
               integz=0.;
               if(ik >= 0 && ik <= ixmax-1 && jk == -1) {
                  fprintf(fpaus1,"j,y[j],z[j][ %d ],x[ik]= %f\n\n",ik,x[ik]);
                  for(j=0 ; j <= iymax-2; j++) {                         /* i=ik constant */
                     fprintf(fpaus1,"%d %f %f\n",j,y[j],z[j][ik]);
                     if(fabs(z[j][ik]) > 0. && i1 == -1) i1=j-1;
                     if(fabs(z[j][ik]) > 0. && i1 > -1)  i2=j+1;
                     integ0=z[j][ik];
                     integ1=z[j+1][ik];
                     integz=integz+0.5*(integ0+integ1);
                                               }
                  integz=integz/(float)(i2-i1+1);
                  fprintf(fpaus1,"%d %f %f\n\n",iymax-1,y[iymax-1],z[iymax-1][ik]);
                  fprintf(fpaus1,"range of integration, mean value %s position i %d\n",epar,ik);
                  fprintf(fpaus1,"%d %d %f\n",i1,i2,integz);
                                                        }
               else if(jk >= 0 && jk <= iymax-1 && ik == -1) {
                  fprintf(fpaus1,"i,x[i],z[ %d ][i],y[jk]= %f\n\n",jk,y[jk]);
                  for(i=0 ; i <= ixmax-2; i++) {                         /* j=jk constant */
                     fprintf(fpaus1,"%d %f %f\n",i,x[i],z[jk][i]);
                     if(fabs(z[jk][i]) > 0. && i1 == -1) i1=i-1;
                     if(fabs(z[jk][i]) > 0. && i1 > -1)  i2=i+1;
                     integ0=z[jk][i];
                     integ1=z[jk][i+1];
                     integz=integz+0.5*(integ0+integ1);
                                               }
                  integz=integz/(float)(i2-i1+1);
                  fprintf(fpaus1,"%d %f %f\n\n",ixmax-1,x[ixmax-1],z[jk][ixmax-1]);
                  fprintf(fpaus1,"range of integration, mean value %s , position i %d\n",epar,jk);
                  fprintf(fpaus1,"%d %d %f\n",i1,i2,integz);
                                                             }
               else {
                  printf("Error input failure ik,jk: %d %d\n",ik,jk);
                  return(-1);     /* EXIT_ERROR_ik,jk */
                    }
               break; 

      default:
               printf("Error invalid value mod: mod = %d, dis = %d\n",mod,dis);
               return(-1);       /* EXIT_ERROR_mod */
   }

   printf("datgen EXIT_SUCCESS\n");
   fclose(fpein);
   fclose(fpaus1);
   fclose(fpaus2);
   return EXIT_SUCCESS;
}

/*-------------------------------------------------------------*/
/*  Linear interpolation of the function YY(XX) at position x  */
/*  boundary interpolation allowed, extrapolation not allowed  */
/*                                                             */
/*  Lineare Interpolation der Funktion YY(XX) an der Stelle x  */
/*  Randinterpolation zugelassen, Extrapolation nicht          */
/*-------------------------------------------------------------*/
double INTERPOL(float x,double *YY,double *XX,int ie,int ia)
{
   extern is,iflag;
   int i;
   double INTERPOL;

   for(i=ia-1; i <= ie-1; i++) {
      is=i+1;
      if(XX[i] == XX[i-1]) continue;
      if((x <= XX[i-1] && x >= XX[i]) || (x >= XX[i-1] && x <= XX[i])) {
         iflag=0;
         INTERPOL=YY[i]+(YY[i]-YY[i-1])/(XX[i]-XX[i-1])*(x-XX[i]);
         return INTERPOL;
                                                                       }
                               }
   iflag=1;
   INTERPOL=0.;
   return INTERPOL;
}

/*---------------------------------------------------------------------*/
/*  Closed isolines put in order / Ordnen von geschlossenen Isolinien  */
/*---------------------------------------------------------------------*/
int ORDNE(float *X1,float *Y1,int ie,float *X2,float *Y2)
{
   extern ie1;
   int i,j,ij,i1,i2,flag;

   i1=0;
   flag=1;
   for(i=0; i <= ie-1; i++) {
      if(i >= 1 && X1[i] == X1[i-1] && flag == 1) {
         i1=i;
         flag=2;
         if(i >= 2 && X1[i] == X1[i-1] && X1[i] == X1[i-2] && flag == 2) flag=3;
                                                  }
                            }
   i2=0;
   flag=1;
   for(i=0; i <= ie-1; i++) {
      j=ie-1-i;
      if(j <= ie-2 && X1[j] == X1[j+1] && flag == 1) {
         i2=j+2;
         flag=2;
         if(j <= ie-3 && X1[j] == X1[j+1] && X1[j] == X1[j+2] && flag == 2) flag=3;
                                                     }
                            }

   switch(flag)
   {
      case 1:           /* simplex */
      /* -------------------------------------------------------- */
               for(i=0; i <= ie-1; i++) {X2[i]=X1[i]; Y2[i]=Y1[i];}
               ie1=ie;
               break; 

      case 2:           /* twofold */
      /* -------------------------------------------------------- */
               for(i=0; i <= i1-2; i++) {X2[i]=X1[i]; Y2[i]=Y1[i];}
               ij=i-1;
               for(i=i1-1; i <= i2-2; i=i+2) {ij=ij+1; X2[ij]=X1[i]; Y2[ij]=Y1[i];}
               for(i=i1-1; i <= i2-2; i=i+2) {j=i1+i2-2-i; ij=ij+1; X2[ij]=X1[j]; Y2[ij]=Y1[j];}
               for(i=i1-1; i <= i2-2; i=i+2) {ij=ij+1; X2[ij]=X1[i]; Y2[ij]=Y1[i];}
               for(i=i2; i <= ie-1; i++)     {ij=ij+1; X2[ij]=X1[i]; Y2[ij]=Y1[i];}
               ie1=ij+1;
               break;

      case 3:           /* triple */
      /* -------------------------------------------------------- */
               for(i=0; i <= i1-2; i++) {X2[i]=X1[i]; Y2[i]=Y1[i];}
               ij=i-1;
               for(i=i1-1; i <= i2-2; i=i+3) {ij=ij+1; X2[ij]=X1[i]; Y2[ij]=Y1[i];}
               for(i=i1-1; i <= i2-2; i=i+3) {j=i1+i2-2-i; ij=ij+1; X2[ij]=X1[j]; Y2[ij]=Y1[j];}
               for(i=i1-1; i <= i2-2; i=i+3) {ij=ij+1; X2[ij]=X1[i+1]; Y2[ij]=Y1[i+1];}
               for(i=i2; i <= ie-1; i++)     {ij=ij+1;  X2[ij]=X1[i]; Y2[ij]=Y1[i];}
               ie1=ij+1;
               break; 

      default:
               printf("Error invalid value flag: flag = %d\n",flag);
               return(-1);       /* EXIT_ERROR_flag */
   }
return;
}















