//*****************************************************************main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "datadef.h"
#include "init.h"
#include "flag.h"
#include "boundary.h"
#include "uvp.h"
#include "turbulence.h"
#include "visual.h"
#include "surface.h"

/*----------------------------------------------------------------- */
/*                 H A U P T A L G O R I T H M U S                  */
/*------------------------------------------------------------------*/
int main(int argc, char *Inputfile[1])
{
  int i,j;
  REAL xlength,ylength,delx,dely,t_anf = 0.0,t_end,t_endvg,delt,tau,t;
  REAL t_rest,tks,del_trace,del_inj,del_streak,del_vec;
  REAL pos1x,pos2x,pos1y,pos2y;
  int  imax,jmax,ikx,jky,wW,wO,wN,wS,itermax,itersor=0,schreibe,N;
  REAL Re,Pr,GX,GY,UI,VI,TI,beta;
  REAL eps,omg,gamma,res;
  int  pflag,tmod,p_bound;
  REAL **U,**V,**P,**PSI,**ZETA,**RHS,**F,**G,**TEMP,**HEAT;
  REAL u1,u2,t1 = 1.e-04,t2,grad=1.e+03,gradstat = 1.e-04;  /*Rechenende bei grad<gradstat*/
  REAL **NUT,**KA,**EP,KAI,EPI,delxw,delyw;
  REAL cmu = 0.09,cep = 0.07,c1 = 0.126,c2 = 1.92;          /*Bedingung: cmu<c1; c2>1.*/
  int  **FLAG,ppc,ifull=0,isurf=0,ibound=0;
  char problem[30],flagfile[30],infile[30],outfile[30];
  char vecfile[30],zeitfile[30],tracefile[30],streakfile[30];
  struct particleline *Particlelines;
  int lese_fall,cycle;
  FILE *fp;

 /* Lese Problemparameter, wenn unbekanntes Problem oder unbekannte */
 /* Eingabedatei, dann Programmabbruch                              */
 /*-----------------------------------------------------------------*/
  if(READ_PARAMETER(Inputfile[1],problem,
                     &pflag,&xlength,&ylength,&imax,&jmax,&delx,&dely,
                     &t_end,&delt,&tau,&del_trace,&del_inj,&del_streak,
                     &del_vec,vecfile,zeitfile,tracefile,streakfile,
                     flagfile,infile,outfile,&N,&pos1x,&pos1y,&pos2x,
                     &pos2y,&itermax,&eps,&omg,&gamma,&p_bound,&Re,&Pr,
                     &beta,&GX,&GY,&UI,&VI,&TI,&tmod,&KAI,&EPI,&wW,&wO,
                     &wN,&wS,&delxw,&delyw) != 0 )
                     return(1); 

 /* Speicher fuer benoetigte Felder allokieren und U,V,P initialisieren */
 /*---------------------------------------------------------------------*/
  U    = RMATRIX(0,imax+1,0,jmax+1);
  V    = RMATRIX(0,imax+1,0,jmax+1);
  F    = RMATRIX(0,imax+1,0,jmax+1);
  G    = RMATRIX(0,imax+1,0,jmax+1);
  P    = RMATRIX(0,imax+1,0,jmax+1);
  TEMP = RMATRIX(0,imax+1,0,jmax+1);
  NUT  = RMATRIX(0,imax+1,0,jmax+1);
  KA   = RMATRIX(0,imax+1,0,jmax+1);
  EP   = RMATRIX(0,imax+1,0,jmax+1);
  PSI  = RMATRIX(0,imax,0,jmax);
  ZETA = RMATRIX(1,imax-1,1,jmax-1);
  HEAT = RMATRIX(0,imax,0,jmax);
  RHS  = RMATRIX(0,imax+1,0,jmax+1); 
  FLAG = IMATRIX(0,imax+1,0,jmax+1);
  ppc  = 4;                             

                                      /* Einlesen von Startwerten */
  lese_fall = LESE_ERG_bin(&t_anf,U,V,P,TEMP,F,G,NUT,KA,EP,FLAG,imax,jmax,tmod,infile);

  if( lese_fall > 0 ) return(1);      /* Fehler beim Einlesen */
  if( lese_fall < 0 ){                /* keine Startwerte gelesen, dann */
                                      /* Werte initialisieren*/

     INIT_UVP(problem,U,V,P,TEMP,KA,EP,imax,jmax,delx,dely,delxw,delyw,UI,VI,TI,KAI,EPI);
     INIT_FLAG(problem,FLAG,pflag,imax,jmax,delx,dely,delxw,delyw,&ibound,vecfile,flagfile);
                     }
 
                /* Partikel setzen fuer Streaklines oder Particle-Tracing */
                /*--------------------------------------------------------*/
  if (strcmp(streakfile,"kein") || strcmp(tracefile,"kein"))
     Particlelines = SET_PARTICLES(N,pos1x,pos1y,pos2x,pos2y);

                /* Partikel setzen fuer freie Randwertprobleme */
                /*---------------------------------------------*/
  if (!strcmp(problem,"tropfen1") || !strcmp(problem,"tropfen2") || 
      !strcmp(problem,"damm"))
     Particlelines = INIT_PARTICLES(&N,imax,jmax,delx,dely,ppc,problem,U,V);

  if( lese_fall < 0 ){ /* keine Startwerte gelesen, dann Randbedingungen und Turbulenz*/
  SETBCOND(U,V,P,TEMP,KA,EP,FLAG,KAI,EPI,Re,imax,jmax,wW,wO,wN,wS,tmod,delxw,delyw,cmu);
  SETSPECBCOND(problem,U,V,P,TEMP,KA,EP,imax,jmax,delx,dely,delxw,delyw,UI,VI,KAI,EPI);
  if(tmod > 0){
  COMP_NUT(cmu,Re,delx,dely,delxw,delyw,NUT,KA,EP,FLAG,tmod,imax,jmax);
  COMP_KAEP(U,V,NUT,KA,EP,FLAG,tmod,imax,jmax,delt,delx,dely,delxw,delyw,GX,GY,
            gamma,Re,cmu,cep,c1,c2,KAI,EPI);
              }
                     }

		/* Z e i t s c h l e i f e */
                /*-------------------------*/

  ikx = imax/2;                     /*Kontrollstelle fuer U,P,grad geeignet waehlen, */
  jky = jmax/2;                     /*damit grad != 0; Standard ist imax/2 und jmax/2*/

  t_endvg=t_end;
  tks = 3.;                        /* waehlbare Minimalzeit fuer das Schleifenende   */
  if (strcmp(zeitfile,"kein"))
    fp = fopen(zeitfile, "wb");
  for(t=t_anf,cycle=0; t < t_end; t+=delt,cycle++)
  {
   if(t_end == 29.3 && t > tks && fabs(grad) < gradstat) t_end=t;
   COMP_delt(&delt, t, imax, jmax, delx, dely, U, V, Re, Pr, tau, &schreibe,
             del_trace, del_inj, del_streak, del_vec);
 printf("t = %f :   ",t);

 if(delt < 1.e-08){
    printf("WARNUNG WARNUNG WARNUNG *** delt zu klein *** mit: %g\n",delt); 
    printf("Abhilfe eventuell durch:\n");
    printf(" -- Verkleinerung von tau, aber >1.e-10 \n");
    printf(" -- imax und jmax aendern, \n"); 
    printf(" -- delxw und delyw ueberpruefen, \n"); 
    printf(" -- eps, omg und gamma ueberpruefen, \n"); 
                  }
 /* Bei freien Randwertproblemen Fluidzellen bestimmen und */
   /* Werte am freien Rand belegen                           */
   /*--------------------------------------------------------*/
   if (!strcmp(problem,"tropfen1") || !strcmp(problem,"tropfen2")   || 
       !strcmp(problem,"damm")     || !strcmp(problem,"spritzguss") || 
       !strcmp(problem,"wafa"))
     {
      MARK_CELLS(FLAG,imax,jmax,delx,dely,&ifull,&isurf,
                 N,Particlelines);
      SET_UVP_SURFACE(U,V,P,FLAG,GX,GY,imax,jmax,Re,delx,dely,delt);
     }
   else
      ifull = imax*jmax-ibound;

   COMP_TEMP(U,V,TEMP,FLAG,imax,jmax,delt,delx,dely,gamma,Re,Pr);
   COMP_FG(U,V,TEMP,F,G,NUT,KA,FLAG,tmod,imax,jmax,delt,delx,dely,GX,
           GY,gamma,Re,beta);
   COMP_RHS(F,G,RHS,FLAG,imax,jmax,delt,delx,dely);

   if (ifull > 0)
      itersor = POISSON(P,RHS,FLAG,imax,jmax,delx,dely,
                        eps,itermax,omg,&res,ifull,p_bound);

   if(cycle % 1 == 0 || 0){                       /* Wie oft Kontrollausgabe ? */
   if (strcmp(zeitfile,"kein"))
     fprintf(fp,"t,U,P,grad = %f %f %f %1.5g\n",t,U[ikx][jky],P[ikx][jky],grad);
     t_rest = (t_end-t)*100./(t_end-t_anf);
     t2 = t;
     u2 = U[ikx][jky];                /* geeignete Wahl der Kontrollgeschwindigkeit */
     grad = (u2-u1)/(t2-t1);
     t1 = t2;
     u1 = u2;
     printf("Restlaufzeit %5.1f Proz.  SOR-Iterationen %3d  U-Gradient %1.5g\n",
            t_rest,itersor,grad);
                          }
   ADAP_UV(U,V,F,G,P,FLAG,imax,jmax,delt,delx,dely);
   if(U[ikx][jky] == 0.) {
     printf("ikx,iky rearrange, so that the gradient not zero, see time loop in main.c\n");
     printf("ikx,iky aendern, damit Gradient nicht NULL, siehe Zeitschleife in main.c\n");
/* return(0); here deactivate and follow search algorithm activate */
/* return(0); hier deaktivieren und folgenden Suchalgorithmus aktivieren */
//     return(0);
                        }
 /* With activation of the follow term find the applicable values for ikx,iky */
 /* Mit der Aktivierung des folgenden Ausdruckes die geeigneten Werte ikx,iky finden */
  /*
  for(i=1;i<=imax;i++)
  for(j=1;j<=jmax;j++){
     if(U[i][j] !=0.) printf("ikx,jky choose: i %d j %d U %1.5g V %1.5g\n",i,j,U[i][j],V[i][j]);
                      }
  */
   SETBCOND(U,V,P,TEMP,KA,EP,FLAG,KAI,EPI,Re,imax,jmax,wW,wO,wN,wS,tmod,delxw,delyw,cmu);
   SETSPECBCOND(problem,U,V,P,TEMP,KA,EP,imax,jmax,delx,dely,delxw,delyw,UI,VI,KAI,EPI);

  if(tmod > 0){
  COMP_NUT(cmu,Re,delx,dely,delxw,delyw,NUT,KA,EP,FLAG,tmod,imax,jmax);
  COMP_KAEP(U,V,NUT,KA,EP,FLAG,tmod,imax,jmax,delt,delx,dely,delxw,delyw,GX,GY,
            gamma,Re,cmu,cep,c1,c2,KAI,EPI);
              }
   if (!strcmp(problem,"tropfen1") || !strcmp(problem,"tropfen2")   || 
       !strcmp(problem,"damm")     || !strcmp(problem,"spritzguss") || 
       !strcmp(problem,"wafa"))
      SET_UVP_SURFACE(U,V,P,FLAG,GX,GY,imax,jmax,Re,delx,dely,delt);

   if ((schreibe & 8) && strcmp(vecfile,"kein"))
     {
      COMPPSIZETA(U,V,PSI,ZETA,FLAG,imax,jmax,delx,dely);
      COMP_HEAT(U,V,TEMP,HEAT,FLAG,Re,Pr,imax,jmax,delx,dely);
	
      OUTPUTVEC(U,V,P,TEMP,NUT,KA,EP,PSI,ZETA,HEAT,FLAG,t,xlength,
                ylength,Re,imax,jmax,tmod,vecfile,delxw,delyw,
                wW,wO,wN,wS);
     }
   if ((schreibe & 8) && strcmp(outfile,"kein"))
      SCHREIBE_ERG_bin(t_end,U,V,P,TEMP,F,G,NUT,KA,EP,FLAG,imax,jmax,tmod,outfile);
   if (strcmp(tracefile,"kein"))
      PARTICLE_TRACING(tracefile,t,xlength,ylength,imax,jmax,delx,dely,delt,U,V,FLAG,
                     N,Particlelines,schreibe);
   if (strcmp(streakfile,"kein"))
      STREAKLINES(streakfile,schreibe,xlength,ylength,imax,jmax,delx,dely,delt,t,
                  U,V,FLAG,N,Particlelines);

  }           /* Ende der Zeitschleife */

 if (strcmp(vecfile,"kein"))
   {
	
    COMPPSIZETA(U,V,PSI,ZETA,FLAG,imax,jmax,delx,dely);
    COMP_HEAT(U,V,TEMP,HEAT,FLAG,Re,Pr,imax,jmax,delx,dely);
    OUTPUTVEC(U,V,P,TEMP,NUT,KA,EP,PSI,ZETA,HEAT,FLAG,t,xlength,
              ylength,Re,imax,jmax,tmod,vecfile,delxw,delyw,
              wW,wO,wN,wS);
   }
 if (strcmp(outfile,"kein"))
    SCHREIBE_ERG_bin(t_end,U,V,P,TEMP,F,G,NUT,KA,EP,FLAG,imax,jmax,tmod,outfile);

 if (strcmp(zeitfile,"kein"))
   fclose(fp);

 /* Freigeben des allokierten Speichers */
 /*-------------------------------------*/
  FREE_RMATRIX(U,0,imax+1,0,jmax+1);
  FREE_RMATRIX(V,0,imax+1,0,jmax+1);
  FREE_RMATRIX(F,0,imax+1,0,jmax+1);
  FREE_RMATRIX(G,0,imax+1,0,jmax+1);
  FREE_RMATRIX(P,0,imax+1,0,jmax+1);
  FREE_RMATRIX(TEMP,0,imax+1,0,jmax+1);
  FREE_RMATRIX(NUT,0,imax+1,0,jmax+1);
  FREE_RMATRIX(KA,0,imax+1,0,jmax+1);
  FREE_RMATRIX(EP,0,imax+1,0,jmax+1);
  FREE_RMATRIX(PSI,0,imax,0,jmax);
  FREE_RMATRIX(ZETA,1,imax-1,1,jmax-1);
  FREE_RMATRIX(HEAT,0,imax,0,jmax);
  FREE_RMATRIX(RHS, 0,imax+1,0,jmax+1);
  FREE_IMATRIX(FLAG,0,imax+1,0,jmax+1);

  if(t_end == t_endvg) printf("\n\n Programmende nach vorgegebener Endzeit t_end = %5.2f\n",t_end);
  if(fabs(grad) <= gradstat) printf("\n\n Programmende bei stationaerer Stroemung, t_end = %5.2f\n",t_end);
  return(0);
}
