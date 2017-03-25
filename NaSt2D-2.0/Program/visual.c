//*****************************************************************visual.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "datadef.h"
#include "visual.h"

/*--------------------------------------------------------------------------*/
/* OUTPUTVEC schreibt U,V,P,PSI,ZETA etc. in die Datei vecfile              */
/*--------------------------------------------------------------------------*/
void OUTPUTVEC(REAL **U,REAL **V,REAL **P,REAL **TEMP,REAL **NUT,REAL **KA,
               REAL **EP,REAL **PSI,REAL **ZETA,REAL **HEAT,int **FLAG,REAL t,
               REAL xlength,REAL ylength,REAL Re,int imax,int jmax,int tmod,
               char* vecfile,REAL delxw,REAL delyw,int wW,int wO,int wN,int wS)
{
 int i,j,itemp;
 REAL crand,sum;
 float temp,fdel=25./Re;
 float uinf=27.78,rhoinf=1.188,pinf=1.0,fak;     /* m/s, kg/m3, bar */
       fak = rhoinf*uinf*uinf/1.e+05;          /* bar */
 FILE *fp;
 fp = fopen(vecfile, "wb");

 fprintf(fp,"  xlength: %f",xlength);
 fprintf(fp,"  ylength: %f",ylength);
 fprintf(fp,"  imax: %d",imax);
 fprintf(fp,"  jmax: %d",jmax);
 fprintf(fp,"  tmod: %d",tmod);
 fprintf(fp,"  delxw: %f",delxw);
 fprintf(fp,"  delyw: %f\n",delyw);

/* Berechnung mittlere Dicke der viskosen Unterschicht */
/*-----------------------------------------------------*/
 if(wS == 5 || wW == 5 || wO == 5 || wN == 5){
  fprintf(fp,"\n");
  fprintf(fp,"Mittlere Dicke der viskosen Unterschicht\n");
 if(delxw > 0.0 && wW == 5){
  sum=0.;
  for(j=1;j<=jmax;j+=1){
        crand = fabs(V[0][j]);
        temp = delxw;
        if(crand > 0.0) temp = fdel/crand;
        sum = sum+temp;
   }
        temp=sum/jmax;
   fprintf(fp,"delxw_W: Vorgabe %f berechnet %f\n",delxw,temp);
  }
 if(delxw > 0.0 && wO == 5){
  sum=0.;
  for(j=1;j<=jmax;j+=1){
        crand = fabs(V[imax+1][j]);
        temp = delxw;
        if(crand > 0.0) temp = fdel/crand;
        sum = sum+temp;
   }
        temp=sum/jmax;
   fprintf(fp,"delxw_O: Vorgabe %f berechnet %f\n",delxw,temp);
  }
 if(delyw > 0.0 && wN == 5){
  sum=0.;
  for(i=1;i<=imax;i+=1){
        crand = fabs(U[i][jmax+1]);
        temp = delyw;
        if(crand > 0.0) temp = fdel/crand;
        sum = sum+temp;
   }
        temp=sum/imax;
   fprintf(fp,"delyw_N: Vorgabe %f berechnet %f\n",delyw,temp);
  }
 if(delyw > 0.0 && wS == 5){
  sum=0.;
  for(i=1;i<=imax;i+=1){
        crand = fabs(U[i][0]);
        temp = delyw;
        if(crand > 0.0) temp = fdel/crand;
        sum = sum+temp;
   }
        temp=sum/imax;
   fprintf(fp,"delyw_S: Vorgabe %f berechnet %f\n",delyw,temp);
  }
   fprintf(fp,"\n");
 }

/* Ausdrucken von U,V,P,TEMP,NUT,KA,EP,ZETA,PSI,HEAT und FLAG" */
/*--------------------------------------------------------------------------*/
 fprintf(fp,"U(x,y) [m/s]: \n");
// fprintf(fp,"U(x,y): \n");
 for(j=1;j<=jmax;j+=1) {
  for(i=1;i<=imax;i+=1){
   if( (FLAG[i][j] & C_F) && (FLAG[i][j] < C_E) ){
      temp = (U[i][j]+U[i-1][j])/2.0;
      temp = temp*uinf;}
   else                  temp = 0.0;
   fprintf(fp,"%f ",temp);
  }
   fprintf(fp,"\n");
 }
   fprintf(fp,"\n");

 fprintf(fp,"V(x,y) [m/s]: \n");
// fprintf(fp,"V(x,y): \n");
 for(j=1;j<=jmax;j+=1) {
  for(i=1;i<=imax;i+=1){
   if( (FLAG[i][j] & C_F) && (FLAG[i][j] < C_E) ){
      temp = (V[i][j]+V[i][j-1])/2.0;
      temp = temp*uinf;}
   else                  temp = 0.0;
   fprintf(fp,"%f ",temp);
  }
   fprintf(fp,"\n");
 }
   fprintf(fp,"\n");

 fprintf(fp,"P(x,y): \n");
 for(j=1;j<=jmax;j+=1) {
  for(i=1;i<=imax;i+=1){
   if( (FLAG[i][j] & C_F) && (FLAG[i][j] < C_E) )
      temp = P[i][j];
   else                  temp = 0.0;
   fprintf(fp,"%f ",temp);
  }
   fprintf(fp,"\n");
 }
   fprintf(fp,"\n");

 fprintf(fp,"P(x,y) [bar]: \n");
 for(j=1;j<=jmax;j+=1) {
  for(i=1;i<=imax;i+=1){
   if( (FLAG[i][j] & C_F) && (FLAG[i][j] < C_E) ){
      temp = P[i][j];
      temp = pinf+temp*fak;}
   else                  temp = 0.0;
   fprintf(fp,"%f ",temp);
  }
   fprintf(fp,"\n");
 }
   fprintf(fp,"\n");

 fprintf(fp,"Ptot(x,y) [bar]: \n");
 for(j=1;j<=jmax;j+=1) {
  for(i=1;i<=imax;i+=1){
   if( (FLAG[i][j] & C_F) && (FLAG[i][j] < C_E) ){
      temp = P[i][j];
      temp = pinf+temp*fak+(U[i][j]*U[i][j]+V[i][j]*V[i][j])*fak/2.;}
   else                  temp = 0.0;
   fprintf(fp,"%f ",temp);
  }
   fprintf(fp,"\n");
 }
   fprintf(fp,"\n");

 fprintf(fp,"TEMP(x,y): \n");
 for(j=1;j<=jmax;j+=1) {
  for(i=1;i<=imax;i+=1){
   if( (FLAG[i][j] & C_F) && (FLAG[i][j] < C_E) ) 
        temp = TEMP[i][j];
   else                  temp = -0.5;
   temp = TEMP[i][j];
//   fprintf(fp,"%f ",temp);
  }
   fprintf(fp,"\n");
 }
   fprintf(fp,"\n");

 if(tmod > 0){
 fprintf(fp,"NUT(x,y): \n");
 for(j=1;j<=jmax;j+=1) {
  for(i=1;i<=imax;i+=1){
   if( (FLAG[i][j] & C_F) && (FLAG[i][j] < C_E) )
        temp = NUT[i][j];
   else                  temp = 0.0;
//   fprintf(fp,"%f ",temp);
  }
   fprintf(fp,"\n");
 }
   fprintf(fp,"\n");

 fprintf(fp,"KA(x,y): \n");
 for(j=1;j<=jmax;j+=1) {
  for(i=1;i<=imax;i+=1){
   if( (FLAG[i][j] & C_F) && (FLAG[i][j] < C_E) )
        temp = KA[i][j];
   else                  temp = 0.0;
//   fprintf(fp,"%f ",temp);
  }
   fprintf(fp,"\n");
 }
   fprintf(fp,"\n");

 fprintf(fp,"EP(x,y): \n");
 for(j=1;j<=jmax;j+=1) {
  for(i=1;i<=imax;i+=1){
   if( (FLAG[i][j] & C_F) && (FLAG[i][j] < C_E) )
        temp = EP[i][j];
   else                  temp = 0.0;
//   fprintf(fp,"%f ",temp);
  }
   fprintf(fp,"\n");
 }
   fprintf(fp,"\n");
 }

 fprintf(fp,"ZETA(x,y): \n");
 for(j=1;j<=jmax-1;j+=1) {
  for(i=1;i<=imax-1;i+=1){
    temp = ZETA[i][j];
   fprintf(fp,"%f ",temp);
  }
   fprintf(fp,"\n");
 }
   fprintf(fp,"\n");

 fprintf(fp,"PSI(x,y): \n");
 for(j=0;j<=jmax;j+=1) {
  for(i=0;i<=imax;i+=1){
    temp = PSI[i][j];
   fprintf(fp,"%f ",temp);
  }
   fprintf(fp,"\n");
 }
   fprintf(fp,"\n");

 fprintf(fp,"HEAT(x,y): \n");
 for(j=0;j<=jmax;j+=1) {
  for(i=0;i<=imax;i+=1){
    temp = HEAT[i][j];
//   fprintf(fp,"%f ",temp);
  }
   fprintf(fp,"\n");
 }
   fprintf(fp,"\n");

/* Ausdrucken von FLAG fuer Inputfile "*.out" */
 fprintf(fp,"FLAG(x,y): \n");
 for(j=1;j<=jmax;j+=1) {
  for(i=1;i<=imax;i+=1){
   itemp = FLAG[i][j];
//   fprintf(fp,"%d ",itemp);
  }
   fprintf(fp,"\n");
 }
   fprintf(fp,"\n");

 fclose(fp);
}

/*-----------------------------------------------------*/
/* COMPPSIZETA berechnet die Strom- und Wirbelfunktion */
/*-----------------------------------------------------*/
void COMPPSIZETA(REAL **U,REAL **V,REAL **PSI,REAL **ZETA,int **FLAG,
                int imax,int jmax,REAL delx,REAL dely)
{
 int i,j;

 /* Berechnung der Wirbelfunkion ZETA= DU/DY - DV/DX am oberen rechten */
 /* Rand der Zelle (i,j) (nur wenn ringsum Fluidzellen liegen)         */
 /*--------------------------------------------------------------------*/
 for (i=1;i<=imax-1;i++)
    for (j=1;j<=jmax-1;j++)
        if( ((FLAG[i][j] & C_F) && (FLAG[i][j] < C_E))  &&
            ((FLAG[i+1][j] & C_F) && (FLAG[i+1][j] < C_E))  &&
            ((FLAG[i][j+1] & C_F) && (FLAG[i][j+1] < C_E))  &&
            ((FLAG[i+1][j+1] & C_F) && (FLAG[i+1][j+1] < C_E)) )
          ZETA[i][j] = (U[i][j+1]-U[i][j])/dely - (V[i+1][j]-V[i][j])/delx;
       else
          ZETA[i][j] = 0.0;

 /* Berechnung der Stromfunktion PSI = INTEG_Y U - INTEG_X V       */
 /* am oberen rechten Rand der Zelle (i,j)                         */
 /* (nur wenn beide darunterliegenden Zellen Fluidzellen sind)     */ 
 /*----------------------------------------------------------------*/
 for (i=0;i<=imax;i++)
   {
    PSI[i][0] = 0.0;
    for(j=1;j<=jmax;j++)
        if( ((FLAG[i][j] & C_F) && (FLAG[i][j] < C_E))  ||
            ((FLAG[i+1][j] & C_F) && (FLAG[i+1][j] < C_E)) )
          PSI[i][j] = PSI[i][j-1] + U[i][j]*dely;
       else
          PSI[i][j] = PSI[i][j-1];
  }

for (j=0;j<=jmax;j++)
   {
    for(i=1;i<=imax;i++)
        if( ((FLAG[i][j] & C_F) && (FLAG[i][j] < C_E))  ||
            ((FLAG[i][j+1] & C_F) && (FLAG[i][j+1] < C_E)) )
          PSI[i][j] = PSI[i-1][j] - V[i][j]*delx;
       else
          PSI[i][j] = PSI[i-1][j];
  }
}

/*-----------------------------------------------------*/
/* COMP_HEAT berechnet die Hitzefunktion               */
/*-----------------------------------------------------*/
void COMP_HEAT(REAL **U,REAL **V,REAL **TEMP,REAL **HEAT,int **FLAG,
               REAL Re,REAL Pr,int imax,int jmax,REAL delx,REAL dely)
{
 int i,j;

 /* Berechnung der Hitzefunktion HEAT = INTEG_Y DH/DY - INTEG_X DH/DX */
 /* in Gitterschnittpunkten                                           */
 /*-------------------------------------------------------------------*/
 for (i=0;i<=imax;i++)
   {
    HEAT[i][0] = 0.0;
    for(j=1;j<=jmax;j++)
        if( ((FLAG[i][j] & C_F) && (FLAG[i][j] < C_E))  ||
            ((FLAG[i+1][j] & C_F) && (FLAG[i+1][j] < C_E)) )
          HEAT[i][j] = HEAT[i][j-1] +
                       (U[i][j]*0.5*(TEMP[i+1][j]+TEMP[i][j])*Re*Pr -
                       (TEMP[i+1][j]-TEMP[i][j])/delx )*dely;
       else
          HEAT[i][j] = HEAT[i][j-1];
   }

for (j=0;j<=jmax;j++)
   {
    for(i=1;i<=imax;i++)
        if( ((FLAG[i][j] & C_F) && (FLAG[i][j] < C_E))  ||
            ((FLAG[i][j+1] & C_F) && (FLAG[i][j+1] < C_E)) )
          HEAT[i][j] = HEAT[i-1][j] -
                       (V[i][j]*0.5*(TEMP[i][j+1]+TEMP[i][j])*Re*Pr -
                       (TEMP[i][j+1]-TEMP[i][j])/dely )*delx;
       else
          HEAT[i][j] = HEAT[i-1][j];
  }
}

/*-------------------------------------------------------------------*/
/* PARTALLOC belegt Speicherplatz fuer ein Partikel und setzt die    */
/* seine Koordinaten auf x,y                                         */
/*-------------------------------------------------------------------*/
struct particle *PARTALLOC(REAL x, REAL y){
  struct particle *part;

  if((part=(struct particle *)malloc(sizeof(struct particle))) == NULL)
    {   
     printf("kein speicher\n");
     exit(0);
    }
  part->x = x; part->y = y;
  part->next = NULL;
  return( part );
}

/*------------------------------------------------------------------*/
/* SET_PARTICLES belegt den Speicherplats fuer die Partikellisten   */
/* und bestimmt die Koordinaten der jeweils ersten Partikel der     */
/* Listen, in dem auf der Strecke [(pos1x,pos1y);(pos2x,pos2y)]     */
/* N Partikel gleichmaessig verteilt werden.                        */
/* Zurueckgegeben wird der Zeiger auf die Partikelliste.            */
/*------------------------------------------------------------------*/
struct particleline *SET_PARTICLES(int N,REAL pos1x,REAL pos1y,
                                         REAL pos2x,REAL pos2y){
   int i;
   REAL hx,hy;
   struct particleline *Partlines;

   if((Partlines=(struct particleline *)
                 malloc((unsigned)(N) * sizeof(struct particleline))) == NULL)
     {  
      printf("kein speicher\n");
      exit(0);
     }
   Partlines -= 1;   /* damit Particlelines[1 bis N] */

   if (N>=2)
     {
      hx  = (pos2x-pos1x)/(N-1);
      hy  = (pos2y-pos1y)/(N-1);
      for(i=1; i<=N; i++){
         Partlines[i].length = 0;
         Partlines[i].Particles = 
             PARTALLOC(pos1x+hx*(i-1),pos1y+hy*(i-1)); /*Startpkte*/
         Partlines[i].Particles->next = 
             PARTALLOC(pos1x+hx*(i-1),pos1y+hy*(i-1));
         Partlines[i].length++;
       }
     }
   return(Partlines);
}/*End SET_PARTICLES*/

/*-------------------------------------------------------------*/
/* ADVANCE_PARTICLES bewegt die Partikel aus Partlines weiter  */
/*-------------------------------------------------------------*/
void ADVANCE_PARTICLES(int imax,int jmax,REAL delx,REAL dely,REAL delt,
                       REAL **U,REAL **V,int **FLAG,
                       int N,struct particleline *Partlines)
{
  int i, j, k;
  REAL x, y, x1, y1, x2, y2, u, v; 
  struct particle *part,*help;

  for(k=1;k<=N;k++){
     for(part=Partlines[k].Particles; part->next != NULL; part=part->next){
        /*-------------------------------------------------*/
        /* 1. Listenel. in Partline[i].Particles ist dummy */
        /*-------------------------------------------------*/
        x = part->next->x; y = part->next->y;

        /*--------------------------------------------*/
        /* Berechnung der neuen x-Koordinate: dx/dt=u */
        /*--------------------------------------------*/
        i = (int)(x/delx)+1;  j = (int)((y+0.5*dely)/dely)+1;

        x1 = (i-1)*delx;    y1 = ((j-1)-0.5)*dely;
        x2 = i*delx;        y2 = (j-0.5)*dely;
        /*-------------------------*/
        /* Bilineare Interpolation */
        /*-------------------------*/
        u = ((x2-x)*(y2-y)*U[i-1][j-1] +
             (x-x1)*(y2-y)*U[i][j-1]   +
             (x2-x)*(y-y1)*U[i-1][j]   +
             (x-x1)*(y-y1)*U[i][j])/delx/dely;

        /*--------------------------------------------*/
        /* Berechnung der neuen y-Koordinate: dy/dt=v */
        /*--------------------------------------------*/
        i = (int)((x+0.5*delx)/delx)+1; j = (int)(y/dely)+1;

        x1 = ((i-1)-0.5)*delx;    y1 = (j-1)*dely;
        x2 = (i-0.5)*delx;        y2 = j*dely;
        /*-------------------------*/
        /* Bilineare Interpolation */
        /*-------------------------*/
        v = ((x2-x)*(y2-y)*V[i-1][j-1] +
             (x-x1)*(y2-y)*V[i][j-1]   +
             (x2-x)*(y-y1)*V[i-1][j]   +
             (x-x1)*(y-y1)*V[i][j])/delx/dely;

        x += delt*u;   y += delt*v; 

        /*----------------------*/
        /* Neue Zelle bestimmen */
        /*----------------------*/
        i = (int)(x/delx)+1;   j = (int)(y/dely)+1;

        /*---------------------------------------------------------------*/
        /* Wenn neue Partikelposition ausserhalb des Gebiets, aushaengen */
        /*---------------------------------------------------------------*/
        if (x>=imax*delx || y>=jmax*dely || x<=0 || y<=0){
          help = part->next->next;
          free(part->next);
          part->next = help;
          Partlines[k].length--;
          if (help == NULL)
            break;     /* Wenn letztes Partikel der Liste ausgehaengt
                          wird Abbruch, da sonst in Schleife als naechstes
                          part = NULL und part->next nicht mehr existiert */
        }
        else{
          /*------------------------------------------------------------*/
          /* Sonderbehandlung, wenn neue Partikel-Position in Randzelle */
          /*------------------------------------------------------------*/
          if (FLAG[i][j] < C_F)
             ADVANCE_AT_BOUND(i,j,&x,&y,u,v,U,V,FLAG,delx,dely,delt);
            
          part->next->x = x; part->next->y = y;
         }
      }
   }
}/*End ADVANCE_PARTICLES*/

/*-----------------------------------------------------------------------*/
/* ADVANCE_AT_BOUND berechnet die neue Partikelposition eines Partikels, */
/* das in eine Hinderniszelle gelaufen ist (kann nur Eckzelle sein)      */
/* mit einem modifizierten Interpolationsalgorithmus                     */
/*-----------------------------------------------------------------------*/
void ADVANCE_AT_BOUND(int i,int j,REAL *x,REAL *y,REAL u,REAL v,
                      REAL **U,REAL **V,int **FLAG,
                      REAL delx,REAL dely,REAL delt)
{
 int ialt,jalt;
 REAL xalt,yalt;
 REAL ul,ur,vo,vu;
 REAL x1,x2,y1,y2;

 /* Zurueckrechnen der alten Position */
 xalt = (*x)-delt*u;          yalt = (*y)-delt*v;
 ialt = (int)(xalt/delx)+1;   jalt = (int)(yalt/dely)+1; 

 if (i != ialt){      /* neues x berechnen */
                      /* u auf rechter Gitterlinie in Hoehe yalt (ur) */
   if (FLAG[ialt+1][jalt] < C_F)
      ur = 0.0;       /* rechte Nachbarzelle Hindernis -> u rechts = 0 */
   else{
      if (yalt>= (jalt-0.5)*dely)     /* u-Zelle oben */
         if (FLAG[ialt+1][jalt+1] < C_F){
                      /* Zelle rechts oben Hindernis */
            y2 = jalt *dely;
            ur = U[ialt][jalt]*(y2-yalt)*2.0/dely;
           }
         else{        /* Zelle rechts oben kein Hindernis */
            y1 = (jalt-0.5)*dely;
            y2 = (jalt+0.5)*dely;
            ur = (U[ialt][jalt]*(y2-yalt)+U[ialt][jalt+1]*(yalt-y1))/dely;
           }
      else                        /* u-Zelle unten */
         if (FLAG[ialt+1][jalt-1] < C_F){
                      /* Zelle rechts unten Hindernis */
            y1 = (jalt-1.0)*dely;
            ur = U[ialt][jalt]*(yalt-y1)*2.0/dely;
           }
         else{        /* Zell rechts unten kein Hindernis */
            y1 = (jalt-1.5)*dely;
            y2 = (jalt-0.5)*dely;
            ur = (U[ialt][jalt-1]*(y2-yalt)+U[ialt][jalt]*(yalt-y1))/dely;
           }
     }
                      /* u auf linker Gitterlinie in Hoehe yalt (ul) */
   if (FLAG[ialt-1][jalt] < C_F)
      ul = 0.0;       /* rechte Nachbarzelle Hindernis -> u rechts = 0 */
   else{
      if (yalt>= (jalt-0.5)*dely)     /* u-Zelle oben */
         if (FLAG[ialt-1][jalt+1] < C_F){
                      /* Zelle links oben Hindernis */
            y2 = jalt *dely;
            ul = U[ialt-1][jalt]*(y2-yalt)*2.0/dely;
           }
         else{        /* Zelle links oben kein Hindernis */
            y1 = (jalt-0.5)*dely;
            y2 = (jalt+0.5)*dely;
            ul = (U[ialt-1][jalt]*(y2-yalt)+U[ialt-1][jalt+1]*(yalt-y1))/dely;
           }
      else                        /* u-Zelle unten */
         if (FLAG[ialt-1][jalt-1] < C_F){
                      /* Zelle links unten Hindernis */
            y1 = (jalt-1.0)*dely;
            ul = U[ialt-1][jalt]*(yalt-y1)*2.0/dely;
           }
         else{        /* Zell links unten kein Hindernis */
            y1 = (jalt-1.5)*dely;
            y2 = (jalt-0.5)*dely;
            ul = (U[ialt-1][jalt-1]*(y2-yalt)+U[ialt-1][jalt]*(yalt-y1))/dely;
           }
     }
   u = (ul*(ialt*delx-xalt)+ur*(xalt-(ialt-1)*delx))/delx;
   (*x) = xalt+u*delt;
  }      /* Ende neues x */

 if (j != jalt){      /* neues y berechnen */
                      /* v auf oberer Gitterlinie in Hoehe xalt (vo) */
   if (FLAG[ialt][jalt+1] < C_F)
      vo = 0.0;       /* obere Nachbarzelle Hindernis -> v oben = 0 */
   else{
      if (xalt>= (ialt-0.5)*delx)     /* v-Zelle rechts */
         if (FLAG[ialt+1][jalt+1] < C_F){
                      /* Zelle rechts oben Hindernis */
            x2 = ialt*delx;
            vo = V[ialt][jalt]*(x2-xalt)*2.0/delx;
           }
         else{        /* Zelle rechts oben kein Hindernis */
            x1 = (ialt-0.5)*delx;
            x2 = (ialt+0.5)*delx;
            vo = (V[ialt][jalt]*(x2-xalt)+V[ialt+1][jalt]*(xalt-x1))/delx;
           }
      else                        /* v-Zelle links */
         if (FLAG[ialt-1][jalt+1] < C_F){
                      /* Zelle links oben Hindernis */
            x1 = (ialt-1.0)*delx;
            vo = V[ialt][jalt]*(xalt-x1)*2.0/delx;
           }
         else{        /* Zell links oben Hindernis */
            x1 = (ialt-1.5)*delx;
            x2 = (ialt-0.5)*delx;
            vo = (V[ialt-1][jalt]*(x2-xalt)+V[ialt][jalt]*(xalt-x1))/delx;
           }
     }
                      /* v auf unterer Gitterlinie in Hoehe xalt (vu) */
   if (FLAG[ialt][jalt-1] < C_F)
      vu = 0.0;       /* untere Nachbarzelle Hindernis -> v unten = 0 */
   else{
      if (xalt>= (ialt-0.5)*delx)     /* v-Zelle rechts */
         if (FLAG[ialt+1][jalt-1] < C_F){
                      /* Zelle rechts unten Hindernis */
            x2 = ialt*delx;
            vu = V[ialt][jalt-1]*(x2-xalt)*2.0/delx;
           }
         else{        /* Zelle rechts unten kein Hindernis */
            x1 = (ialt-0.5)*delx;
            x2 = (ialt+0.5)*delx;
            vu = (V[ialt][jalt-1]*(x2-xalt)+V[ialt+1][jalt-1]*(xalt-x1))/delx;
           }
      else                        /* v-Zelle links */
         if (FLAG[ialt-1][jalt-1] < C_F){
                      /* Zelle links unten Hindernis */
            x1 = (ialt-1.0)*delx;
            vu = V[ialt][jalt-1]*(xalt-x1)*2.0/delx;
           }
         else{        /* Zelle links unten kein Hindernis */
            x1 = (ialt-1.5)*delx;
            x2 = (ialt-0.5)*delx;
            vu = (V[ialt-1][jalt-1]*(x2-xalt)+V[ialt][jalt-1]*(xalt-x1))/delx;
           }
     }
   v = (vu*(jalt*dely-yalt)+vo*(yalt-(jalt-1)*dely))/dely;
   (*y) = yalt+v*delt;
  }    /* Ende neues y */

 i = (int)((*x)/delx)+1;     j = (int)((*y)/dely)+1;
 if (FLAG[i][j] < C_F){
   printf(" MIST MIST MIST MIST\n");
   printf("  alte Position: (%e,%e) in Zelle (%d,%d) mit Flag %d\n",
                          xalt,yalt,ialt,jalt,FLAG[ialt][jalt]);
   printf(" korrigierte neue Position (%e,%e) in Zelle (%d,%d) mit Flag %d\n\n",
            (*x),(*y),i,j,FLAG[i][j]);
   }
}/* End ADVANCE_AT_BOUND */

/*--------------------------------------------------------------------*/
/* INJECT_PARTICLES injeziert neue Partikel fuer die Streaklines,     */
/* d.h. die Partikelpositionen des Dummys werden an neu erzeugte      */
/* Partikel uebergeben die zu am Anfang der jeweilige Liste ein-      */
/* haengt werden                                                      */
/*--------------------------------------------------------------------*/
void INJECT_PARTICLES(int N, struct particleline *Partlines){
  int i;
  struct particle *part;

  for(i=1; i<=N; i++){
    part = PARTALLOC(Partlines[i].Particles->x,Partlines[i].Particles->y);
    part->next = Partlines[i].Particles->next;
    Partlines[i].Particles->next = part;
    Partlines[i].length++;
  }
}/*End INJECT_PARTICLES*/

/*-----------------------------------------------------------------*/
/* WRITE_PARTICLES schreibt die aktuellen Partikelpositionen von   */
/* Partlines in die Datei partfile dazu                            */
/*-----------------------------------------------------------------*/
void WRITE_PARTICLES(char *partfile, REAL t, int N, struct particleline *Partlines)
{
  int i;
  FILE *fp;
  struct particle *part;

  fp = fopen(partfile,"ab");
  for(i=1; i<=N; i++){      /* Schreiben der Partikelpositionen */
    fprintf(fp,"Zeit %f Punktezahl %d\n",t,Partlines[i].length);
    for(part=Partlines[i].Particles; part->next != NULL; part=part->next)
      fprintf(fp,"%3.4f %3.4f\n", part->next->x, part->next->y);
  }
  fclose(fp);
}/*End  WRITE_PARTICLES*/

/*---------------------------------------------------------------------*/
/* WRITE_PARTICLES_bin schreibt die aktuellen Partikelpositionen von   */
/* Partlines in die Binary-Datei partfile dazu                         */
/*---------------------------------------------------------------------*/
void WRITE_PARTICLES_bin(char *partfile, int N, struct particleline *Partlines)
{
 int i;
 FILE *fp;
 float temp, temp2[2];
 struct particle *part;

 fp = fopen(partfile, "ab");
 for(i=1; i<=N; i++){      /* Schreiben der Partikelpositionen */
    temp=Partlines[i].length;
    fwrite(&temp, sizeof(float), 1, fp);
    part=Partlines[i].Particles;
    for(; part->next != NULL; part=part->next){
      temp2[0]=part->next->x;
      temp2[1]=part->next->y;
      fwrite(temp2, sizeof(float), 2, fp);
    }
 }
 fclose(fp);
}

/*----------------------------------------------------------------------*/
/* PARTICLE_TRACING bewegt die Partikel aus partlines fort und schreibt */
/* sie gegebenenfalls in outputfile                                     */
/*----------------------------------------------------------------------*/
void PARTICLE_TRACING(char* outputfile,REAL t,REAL xlength,REAL ylength,
                      int imax,int jmax,REAL delx,REAL dely,REAL delt,
                      REAL **U,REAL **V,int **FLAG,
                      int N, struct particleline *Partlines, int schreibe)
{
  FILE *fp;

  if(t == 0){
    fp = fopen(outputfile, "wb");
    fprintf(fp,"  xlength: %f",xlength);
    fprintf(fp,"  ylength: %f",ylength);
    fprintf(fp,"  imax: %d",imax);
    fprintf(fp,"  jmax: %d",jmax);
    fprintf(fp,"  delx: %g", delx);
    fprintf(fp,"  dely: %g", dely);
    fprintf(fp,"  N: %d\n", N);
//    fprintf(fp,"%d\n%d\n%f\n%f\n%d\n", imax, jmax, delx, dely, N);
    fclose(fp);
    WRITE_PARTICLES(outputfile,t,N,Partlines);
  }

  ADVANCE_PARTICLES(imax,jmax,delx,dely,delt,U,V,FLAG,N,Partlines);

  if(schreibe & 1)
    WRITE_PARTICLES(outputfile,t,N,Partlines);
    
}/*End PARTICLE_TRACING*/

/*-------------------------------------------------------------------*/
/* STREAKLINES bewegt die Partikel aus partlines und injeziert bzw,  */
/* schreibt gegebenenfalls Partikel                                  */
/*-------------------------------------------------------------------*/
void STREAKLINES(char* streakfile,int schreibe,REAL xlength,REAL ylength,
                 int imax, int jmax, REAL delx, REAL dely,REAL delt,REAL t,
                 REAL **U,REAL **V,int **FLAG,
                 int N, struct particleline *Partlines)
{
  FILE *fp;

  if(t==0){ /* Schreiben der ersten Partikelpositionen */
    fp = fopen(streakfile, "wb");
    fprintf(fp,"  xlength: %f",xlength);
    fprintf(fp,"  ylength: %f",ylength);
    fprintf(fp,"  imax: %d",imax);
    fprintf(fp,"  jmax: %d",jmax);
    fprintf(fp,"  delx: %g", delx);
    fprintf(fp,"  dely: %g", dely);
    fprintf(fp,"  N: %d\n", N);
    fclose(fp);
    WRITE_PARTICLES(streakfile,t,N,Partlines);
   }

  ADVANCE_PARTICLES(imax,jmax,delx,dely,delt,U,V,FLAG,N,Partlines);

  if(schreibe & 2)  INJECT_PARTICLES(N,Partlines);
  if(schreibe & 4)  WRITE_PARTICLES(streakfile,t,N,Partlines);

}/*End STREAKLINES*/
