/*    drag.c */
/*************************************************************************************/
/*    Program Drag calculates the drag coefficient of obstacles on base of           */
/*    dimensionless pressure in the increment iv before and behind the obstacle      */
/*    contour at a flow oncoming from left (W) and rightwards gutting (O)            */
/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*    epar          input field = FLAG resp. P                                       */
/*    ixmax         maximum number of points in x-direction = max. columns           */
/*    iymax         maximum number of points in y-direction = max. rows              */
/*    uinf          approach velocity [km/h]                                         */
/*    rhoinf        ambient density [kg/m3]                                          */
/*    pinf          ambient pressure [bar]                                           */
/*    iv            increment to reference position (>= 1)                           */
/*                                                                                   */
/*    input file    <Flag.in> should contain:                                        */
/*                  epar,ixmax,iymax                                                 */
/*                  FLAG[ii][jj]                                                     */
/*                                                                                   */
/*    attention     obstacle cells in FLAG[ii][jj] are to mark                       */
/*                  with <0>, fluid cells with <2>                                   */
/*                                                                                   */
/*    input file    <Dat.in> should contain:                                         */
/*                  epar,ixmax,iymax                                                 */
/*                  P[ii][jj]                                                        */
/*************************************************************************************/
/*    Programm Drag berechnet den Widerstands-Beiwert von Hindernissen auf der Basis */
/*    des dimensionslosen Druckes im Inkrement iv vor und nach der Hindernis-        */
/*    Kontur bei Anstroemung von links (W) und Abstroemung nach rechts (O)           */
/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*    epar          Eingabefeld = FLAG bzw. P                                        */
/*    ixmax         max. Punktezahl in x-Richtung = max. Spaltenzahl                 */
/*    iymax         max. Punktezahl in y-Richtung = max. Zeilenzahl                  */
/*    iv            Inkrement zur Referenzstelle (>= 1)                              */
/*    uinf          Anstroemgeswchwindigkeit [km/h]                                  */
/*    rhoinf        Umgebungsdichte [kg/m3]                                          */
/*    pinf          Umgebungsdruck [bar]                                             */
/*                                                                                   */
/*    Eingabefile   <Flag.in> muss enthalten:                                        */
/*                  epar,ixmax,iymax                                                 */
/*                  FLAG[ii][jj]                                                     */
/*                                                                                   */
/*    Achtung       Hindernis-Zellen in FLAG[ii][jj] sind mit <0> ,                  */
/*                  Fluid-Zellen sind mit <2> zu kennzeichnen                        */
/*                                                                                   */
/*    Eingabefile   <Dat.in> muss enthalten:                                         */
/*                  epar,ixmax,iymax                                                 */
/*                  P[ii][jj]                                                        */
/*************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define n  1000
#define nn 2000

int main(void) 
{
   int    iv=2,ixmax,iymax,ii,jj,check,k,kn,irev;
   int    il[n],ir[n],j[n],FLAG[nn][nn];
   float  CPl[n],CPr[n],P[nn][nn];
   double fak,uinf=100.,rhoinf=1.188,pinf=1.01325;
   double suml,sumr,CPlm,CPrm;
   char   epar[4],*par[]={"FLAG","P"};
   FILE   *fpein1;
   FILE   *fpein2;
   FILE   *fpaus;
   char   *input1="Flag.in";            /* input1 file */
   char   *input2="Dat.in";             /* input2 file */
   char   *output="Cpv.out";            /* output file */

   fak = 2.*3.6*3.6*1.e+05*pinf/(rhoinf*uinf*uinf);

   fpein1=fopen(input1,"r");            /* opening the files */
   fpein2=fopen(input2,"r");
   fpaus=fopen(output,"w");
   if ((fpein1==NULL)||(fpein2==NULL)||(fpaus==NULL)) {
      printf("Error on opening the files\n");
      return(-1);                       /* EXIT_ERROR_input_files */
                                                      }

   fscanf(fpein1,"%s %d %d", &epar,&ixmax,&iymax);   /* read in 1st line */
   if(strcmp(epar,par[0]) != 0) {
      printf("File <Flag.in> wrong\n");
      return(-1);                       /* EXIT_ERROR_input_file_Flag.in */
                                }
   fscanf(fpein2,"%s %d %d", &epar,&ixmax,&iymax);   /* read in 1st line */
   if(strcmp(epar,par[1]) != 0) {
      printf("File <Dat.in> wrong\n");
      return(-1);                       /* EXIT_ERROR_input_file_Dat.in  */
                                }

   for(ii=0; ii <= iymax-1; ii++)
      for(jj=0; jj <= ixmax-1; jj++)
         fscanf(fpein1,"%d ", &FLAG[ii][jj]);    /* read in FLAG[nn][nn] */
//*----------- checkup print: first and last field value FLAG -----------*/
//   printf("checkup1: %d %d\n",FLAG[0][0],FLAG[iymax-1][ixmax-1]);

   for(ii=0; ii <= iymax-1; ii++)
      for(jj=0; jj <= ixmax-1; jj++)
         fscanf(fpein2,"%f ", &P[ii][jj]);       /* read in P[nn][nn]    */
//*----------- checkup print: first and last field value P --------------*/
//   printf("checkup2: %f %f\n",P[0][0],P[iymax-1][ixmax-1]);

   k=-1;
   for(ii=0; ii <= iymax-1; ii++)
      for(jj=0; jj <= ixmax-1; jj++)
      if(FLAG[ii][jj] != 2) {              /* mark iv left from obstacle */
      k=k+1;
      il[k]=jj-iv;
      j[k]=ii;
      break;
                            }
   k=-1;
   for(ii=0; ii <= iymax-1; ii++)
      for(jj=0; jj <= ixmax-1; jj++) {
      irev=ixmax-1-jj;
      if(FLAG[ii][irev] != 2) {            /* mark iv right from obstacle */
      k=k+1;
      ir[k]=irev+iv;
      break;
                              }
                                     }
   kn=k;                                   /* drag coeff. left and right*/
   for(k=0; k <= kn; k++) {CPl[k]=2.*P[j[k]][il[k]]+fak; CPr[k]=2.*P[j[k]][ir[k]]+fak;}

   {suml=CPl[0]; sumr=CPr[0];}             /* mean value left and right*/
   for(k=1; k <= kn; k++) {suml=suml+CPl[k]; sumr=sumr+CPr[k];}
   {CPlm=suml/(kn+1); CPrm=sumr/(kn+1);}

   printf("CPlm = %f CPrm = %f\n\n",CPlm,CPrm);
   printf("Drag coefficient = %f\n\n",CPlm-CPrm); 
   fprintf(fpaus," k j il CPl ir CPr \n\n");
   for(k=0; k <= kn; k++)
      fprintf(fpaus,"%d %d %d %f %d %f\n", k,j[k],il[k],CPl[k],ir[k],CPr[k]);

   printf("flag EXIT_SUCCESS\n");
   fclose(fpein1);
   fclose(fpein2);
   fclose(fpaus);
   return EXIT_SUCCESS;
}

