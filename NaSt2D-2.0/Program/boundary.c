//*****************************************************************boundary.c
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "datadef.h"
#include "init.h"

/*-----------------------------------------------------------------*/
/* Belegung der Randwerte in der aeusseren Randschicht nach den    */
/* Werten der Flags wW,wO,wN und wS                                */
/* 1 = Rutschbedingung               2 = Haftbedingung             */
/* 3 = Aus/Ein-Stroembedingung       4 = periodische Randbed.      */
/* 5 = Log. Wandgesetz                                             */
/* Hinderniszellen (Haftbeding., wenn laminar bzw. Log. Wandgesetz,*/
/* wenn turbulent. Fuer die Temperatur werden ueberall adiabatische*/
/* Randbedingungen gesetzt.                                        */
/*-----------------------------------------------------------------*/
void SETBCOND(REAL **U,REAL **V,REAL **P,REAL **TEMP,REAL **KA,
              REAL **EP,int **FLAG,REAL KAI,REAL EPI,REAL Re,
              int imax,int jmax,int wW,int wO,int wN,int wS,
              int tmod,REAL delxw,REAL delyw,REAL cmu)
{
  int i,j;
  REAL DUDYW,DUDYW1,DVDXW,DVDXW1;
  REAL ReT,Rey,fmuw,fmu,epw;
  REAL **DU,**DV,**DKA,**DEP;

   DU = RMATRIX(0,imax+1,0,jmax+1);
   DV = RMATRIX(0,imax+1,0,jmax+1);
  DKA = RMATRIX(0,imax+1,0,jmax+1);
  DEP = RMATRIX(0,imax+1,0,jmax+1);

                    /*    Universelles Logarithmisches Wandgesetz    */
                    /*----------Berechnung der Inkremente------------*/
 
 if(delxw > 0){                      /* Westrand */
  for(j=0;j<=jmax+1;j++){            /*----------*/
        DVDXW = fabs(V[0][j]+V[1][j])/(2.*delxw);
        DV[0][j] = 0.0;
        if(DVDXW > 0.0) DV[0][j] = 2.*sqrt(DVDXW/Re)*
                        (2.44*log10(delxw*sqrt(Re*DVDXW))+5.5);    
      fmu = 1.;                  /* k,epsilon Modell */
      if(tmod == 2){             /* Low Reynolds Number Modell */
        Rey = Re*delxw*sqrt(0.5*fabs(KA[0][j]+KA[1][j]));
        fmuw = 1.e-10;               
        if(Rey > 0.0) fmuw = (1.-exp(-0.0165*Rey));
        ReT = 0.0;
        epw = (EP[0][j]+EP[1][j]);
        if(epw != 0.0) ReT = 0.5*Re*(KA[0][j]+KA[1][j])*(KA[0][j]+KA[1][j])/epw;
        fmu = fmuw*fmuw;
        if(ReT != 0.0) fmu = fmuw*fmuw*(1.+20.5/ReT);
        if(fmu > 1.) fmu = 1.;
      }
     if(fmu > 0.0){
        DKA[0][j] = 2.*DVDXW/(Re*sqrt(cmu*fmu)); 
        DEP[0][j] = 2.*DVDXW/(Re*cmu*fmu)*sqrt(DVDXW/Re);
     }
     else {
        DKA[0][j] = 0.0;
        DEP[0][j] = 0.0;
     }
                                     /* Ostrand */
                                     /*---------*/
        DVDXW = fabs(V[imax+1][j]+V[imax][j])/(2.*delxw);
        DV[imax+1][j] = 0.0;
        if(DVDXW > 0.0) DV[imax+1][j] = 2.*sqrt(DVDXW/Re)*
                        (2.44*log10(delxw*sqrt(Re*DVDXW))+5.5);    
      fmu = 1.;                      /* k,epsilon Modell */
      if(tmod == 2){                 /* Low Reynolds Number Modell */
        Rey = Re*delxw*sqrt(0.5*fabs(KA[imax+1][j]+KA[imax][j]));
        fmuw = 1.e-10;               
        if(Rey > 0.0) fmuw = (1.-exp(-0.0165*Rey));
        ReT = 0.0;
        epw = (EP[imax+1][j]+EP[imax][j]);
        if(epw != 0.0) ReT = 0.5*Re*(KA[imax+1][j]+KA[imax][j])*
                             (KA[imax+1][j]+KA[imax][j])/epw;
        fmu = fmuw*fmuw;
        if(ReT != 0.) fmu = fmuw*fmuw*(1.+20.5/ReT);
        if(fmu > 1.) fmu = 1.;
      }
     if(fmu > 0.0){
        DKA[imax+1][j] = 2.*DVDXW/(Re*sqrt(cmu*fmu)); 
        DEP[imax+1][j] = 2.*DVDXW/(Re*cmu*fmu)*sqrt(DVDXW/Re);
     }
     else {
        DKA[imax+1][j] = 0.0;
        DEP[imax+1][j] = 0.0;
     }
  }
 }

 if(delyw > 0){                      /* Sued-Rand */
  for(i=0;i<=imax+1;i++){            /*-----------*/
        DUDYW = fabs(U[i][0]+U[i][1])/(2.*delyw);
        DU[i][0] = 0.0;
        if(DUDYW > 0.0) DU[i][0] = 2.*sqrt(DUDYW/Re)*
                        (2.44*log10(delyw*sqrt(Re*DUDYW))+5.5);    
      fmu = 1.;                  /* k,epsilon Modell */
      if(tmod == 2){             /* Low Reynolds Number Modell */
        Rey = Re*delyw*sqrt(0.5*fabs(KA[i][0]+KA[i][1]));
        fmuw = 1.e-10;               
        if(Rey > 0.) fmuw = (1.-exp(-0.0165*Rey));
        ReT = 0.0;
        epw = (EP[i][0]+EP[i][1]);
        if(epw != 0.0) ReT = 0.5*Re*(KA[i][0]+KA[i][1])*(KA[i][0]+KA[i][1])/epw;
        fmu = fmuw*fmuw;
        if(ReT != 0.) fmu = fmuw*fmuw*(1.+20.5/ReT);
        if(fmu > 1.) fmu = 1.;
      }
     if(fmu > 0.0){
        DKA[i][0] = 2.*DUDYW/(Re*sqrt(cmu*fmu)); 
        DEP[i][0] = 2.*DUDYW/(Re*cmu*fmu)*sqrt(DUDYW/Re);
     }
     else {
        DKA[i][0] = 0.0;
        DEP[i][0] = 0.0;
     }
                                     /* Nord-Rand */
                                     /*-----------*/
        DUDYW = fabs(U[i][jmax+1]+U[i][jmax])/(2.*delyw);
        DU[i][jmax+1] = 0.0;
        if(DUDYW > 0.0) DU[i][jmax+1] = 2.*sqrt(DUDYW/Re)*
                        (2.44*log10(delyw*sqrt(Re*DUDYW))+5.5);    
      fmu = 1.;                          /* k,epsilon Modell */
      if(tmod == 2){                     /* Low Reynolds Number Modell */
        Rey = Re*delyw*sqrt(0.5*fabs(KA[i][jmax+1]+KA[i][jmax]));
        fmuw = 1.e-10;               
        if(Rey > 0.) fmuw = (1.-exp(-0.0165*Rey));
        ReT = 0.0;
        epw = (EP[i][jmax+1]+EP[i][jmax]);
        if(epw != 0.0) ReT = 0.5*Re*(KA[i][jmax+1]+KA[i][jmax])*
                             (KA[i][jmax+1]+KA[i][jmax])/epw;
        fmu = fmuw*fmuw;
        if(ReT != 0.) fmu = fmuw*fmuw*(1.+20.5/ReT);
        if(fmu > 1.) fmu = 1.;
      }
     if(fmu > 0.0){
        DKA[i][jmax+1] = 2.*DUDYW/(Re*sqrt(cmu*fmu)); 
        DEP[i][jmax+1] = 2.*DUDYW/(Re*cmu*fmu)*sqrt(DUDYW/Re);
     }
     else {
        DKA[i][jmax+1] = 0.0;
        DEP[i][jmax+1] = 0.0;
     }
   }
  }

                       /* Belegung der Randwerte an den Hinderniszellen */
 if(delyw > 0){        /*-----------------------------------------------*/
 for(i=1;i<=imax;i++)
   for(j=1;j<=jmax;j++)
     if(FLAG[i][j] & 0x000f)   /* Die Maskierung mit 0x000ffiltert genau   */
                               /* die Hinderniszellen heraus, die zu Fluid-*/
                               /* zellen in der jeweiligen Himmelsrichtung */
                               /* benachbart sind.                         */
   switch (FLAG[i][j]){
      case B_N:  { 
	DUDYW = fabs(U[i][j]+U[i][j+1])/(2.*delyw);
        DU[i][j] = 0.0;
        if(DUDYW > 0.0) DU[i][j] = 2.*sqrt(DUDYW/Re)*
		        (2.44*log10(delyw*sqrt(Re*DUDYW))+5.5);    
        DUDYW1 = fabs(U[i-1][j]+U[i-1][j+1])/(2.*delyw);
        DU[i-1][j] = 0.0;
        if(DUDYW1 > 0.0) DU[i-1][j] = 2.*sqrt(DUDYW1/Re)*
		         (2.44*log10(delyw*sqrt(Re*DUDYW1))+5.5);  
       fmu = 1.;            /* k,epsilon Modell */
       if(tmod == 2){       /* Low Reynolds Number Modell */
	 Rey = Re*delyw*sqrt(0.5*fabs(KA[i][j]+KA[i][j+1]));
	 fmuw = 1.e-10;               
	 if(Rey > 0.) fmuw = (1.-exp(-0.0165*Rey));
         ReT = 0.0;
         epw = (EP[i][j]+EP[i][j+1]);
         if(epw != 0.0) ReT = 0.5*Re*(KA[i][j]+KA[i][j+1])*
                              (KA[i][j]+KA[i][j+1])/epw;
	 fmu = fmuw*fmuw;
	 if(ReT != 0.) fmu = fmuw*fmuw*(1.+20.5/ReT);
	 if(fmu > 1.) fmu = 1.;
       }
      if(fmu > 0.0){
        DKA[i][j] = 2.*DUDYW/(Re*sqrt(cmu*fmu)); 
        DEP[i][j] = 2.*DUDYW/(Re*cmu*fmu)*sqrt(DUDYW/Re);
       }
      else {
	DKA[i][j] = 0.0;
	DEP[i][j] = 0.0;
      }
     break;
   }
     case B_S:  { 
       DUDYW = fabs(U[i][j]+U[i][j-1])/(2.*delyw);
       DU[i][j] = 0.0;
       if(DUDYW > 0.0) DU[i][j] = 2.*sqrt(DUDYW/Re)*
                       (2.44*log10(delyw*sqrt(Re*DUDYW))+5.5);    
       DUDYW1 = fabs(U[i-1][j]+U[i-1][j-1])/(2.*delyw);
       DU[i-1][j] = 0.0;
       if(DUDYW1 > 0.0) DU[i-1][j] = 2.*sqrt(DUDYW1/Re)*
                        (2.44*log10(delyw*sqrt(Re*DUDYW1))+5.5);  
      fmu = 1.;             /* k,epsilon Modell */
      if(tmod == 2){        /* Low Reynolds Number Modell */
         Rey = Re*delyw*sqrt(0.5*fabs(KA[i][j]+KA[i][j-1]));
         fmuw = 1.e-10;               
         if(Rey > 0.) fmuw = (1.-exp(-0.0165*Rey));
         ReT = 0.0;
         epw = (EP[i][j]+EP[i][j-1]);
         if(epw != 0.0) ReT = 0.5*Re*(KA[i][j]+KA[i][j-1])*
                              (KA[i][j]+KA[i][j-1])/epw;
         fmu = fmuw*fmuw;
         if(ReT != 0.) fmu = fmuw*fmuw*(1.+20.5/ReT);
         if(fmu > 1.) fmu = 1.;
       }
      if(fmu > 0.0){
       DKA[i][j] = 2.*DUDYW/(Re*sqrt(cmu*fmu)); 
       DEP[i][j] = 2.*DUDYW/(Re*cmu*fmu)*sqrt(DUDYW/Re);
       }
      else {
        DKA[i][j] = 0.0;
        DEP[i][j] = 0.0;
      }
     break;
  }
     default :  break;
  }
 }
                       /* allgemeine Belegung der Randwerte */
                       /*-entsprechend den Randbedingungen--*/

  for(j=0;j<=jmax+1;j++){                   /* Westrand */
                                            /*----------*/
    if(wW == 1 ){                           /* free-slip / rutschen */
      U[0][j] = 0.0;                        /* u = 0     */
      V[0][j] = (4.* V[1][j]- V[2][j])/3.;  /* dv/dn = 0 */
     KA[0][j] = 0.0;                        /* k = 0     */
     EP[0][j] = (4.*EP[1][j]-EP[2][j])/3.;  /* de/dn = 0 */
    }
    if(wW == 2 ){                           /* no-slip / haften */
      U[0][j] = 0.0;                        /* u = 0     */
      V[0][j] = (-1.0)* V[1][j];            /* v=0 auf Rand durch Mittelung */
     KA[0][j] = 0.0;                        /* k = 0     */
     EP[0][j] = (-1.0)*EP[1][j];            /* e=0 auf Rand durch Mittelung */
    }
    if(wW == 3){                            /* outflow / ein/aus-stroemen */
      U[0][j] = (4.* U[1][j]- U[2][j])/3.;  /* du/dn = 0 */
      V[0][j] = (4.* V[1][j]- V[2][j])/3.;  /* dv/dn = 0 */
     KA[0][j] = (4.*KA[1][j]-KA[2][j])/3.;  /* dk/dn = 0 */
     EP[0][j] = (4.*EP[1][j]-EP[2][j])/3.;  /* de/dn = 0 */
    }
    if(wW == 4 ){                           /* periodic / periodisch */
      U[0][j] =  U[imax-1][j];
      V[0][j] =  V[imax-1][j];              /* Ueberlappung der ersten    */ 
      V[1][j] =  V[imax][j];                /* und letzten inneren Zellen */    
     KA[1][j] = KA[imax][j];    
     EP[1][j] = EP[imax][j];    
      P[1][j] =  P[imax][j];     
    }
    if(wW == 5 ){                           /* Log. Wandgesetz */
      U[0][j] =  -U[1][j] +  DU[0][j];
      V[0][j] =  -V[1][j] +  DV[0][j];
     KA[0][j] = -KA[1][j] + DKA[0][j]; 
     EP[0][j] = -EP[1][j] + DEP[0][j];
    }
   TEMP[0][j] = (4.*TEMP[1][j]-TEMP[2][j])/3.;    /* dT/dn = 0 */

                                                /* Ostrand */
                                                /*---------*/
    if(wO == 1 ){                               /* free-slip / rutschen */
      U[imax+1][j] = 0.0;                                  /* u = 0     */
      V[imax+1][j] = (4.* V[imax][j]- V[imax-1][j])/3.;    /* dv/dn = 0 */ 
     KA[imax+1][j] = 0.0;                                  /* k = 0     */
     EP[imax+1][j] = (4.*EP[imax][j]-EP[imax-1][j])/3.;    /* de/dn = 0 */ 
    }
    if(wO == 2 ){                           /* no-slip / haften */
        U[imax][j] = 0.0;                   /* u = 0     */
      V[imax+1][j] = (-1.0)* V[imax][j];    /* v=0 auf Rand durch Mittelung */
       KA[imax][j] = 0.0;                   /* k = 0     */
     EP[imax+1][j] = (-1.0)*EP[imax][j];    /* e=0 auf Rand durch Mittelung */
    }
    if(wO == 3){                            /* outflow / ein/aus-stroemen */
      U[imax+1][j] = (4.* U[imax][j]- U[imax-1][j])/3.;    /* du/dn = 0 */
      V[imax+1][j] = (4.* V[imax][j]- V[imax-1][j])/3.;    /* dv/dn = 0 */
     KA[imax+1][j] = (4.*KA[imax][j]-KA[imax-1][j])/3.;    /* dk/dn = 0 */
     EP[imax+1][j] = (4.*EP[imax][j]-EP[imax-1][j])/3.;    /* de/dn = 0 */
    }
    if(wO == 4 ){                           /* periodic / periodisch */
      U[imax+1][j] =  U[2][j];
      V[imax+1][j] =  V[2][j];              /* Ueberlappung der ersten    */
       KA[imax][j] = KA[1][j];              /* und letzten inneren Zellen */   
       EP[imax][j] = EP[1][j];
        P[imax][j] =  P[1][j]; 
    }
    if(wO == 5 ){                                      /* Log. Wandgesetz */
      U[imax+1][j] =  -U[imax][j] +  DU[imax+1][j];
      V[imax+1][j] =  -V[imax][j] +  DV[imax+1][j];
     KA[imax+1][j] = -KA[imax][j] + DKA[imax+1][j];
     EP[imax+1][j] = -EP[imax][j] + DEP[imax+1][j];
   }
   TEMP[imax+1][j] = (4.*TEMP[imax][j]-TEMP[imax-1][j])/3.;  /* dT/dn = 0 */
  }

  for(i=0;i<=imax+1;i++){                   /* Sued-Rand */
                                            /*-----------*/
    if(wS == 1 ){                           /* free-slip | rutschen */
      V[i][0] = 0.0;                        /* v = 0     */
      U[i][0] = (4.* U[i][1]- U[i][2])/3.;  /* du/dn = 0 */ 
     KA[i][0] = 0.0;                        /* k = 0     */
     EP[i][0] = (4.*EP[i][1]-EP[i][2])/3.;  /* de/dn = 0 */ 
    }
    if(wS == 2 ){                           /* no-slip | haften */
      V[i][0] = 0.0;                        /* v = 0     */
      U[i][0] = (-1.0)* U[i][1];            /* u=0 auf Rand durch Mittelung */
     KA[i][0] = 0.0;                        /* k = 0     */
     EP[i][0] = (-1.0)*EP[i][1];            /* e=0 auf Rand durch Mittelung */
    }
    if(wS == 3){                            /* outflow | aus/ein-stroemen */
      V[i][0] =  (4.*V[i][1]- V[i][2])/3.;  /* dv/dn = 0 */ 
      U[i][0] =  (4.*U[i][1]- U[i][2])/3.;  /* du/dn = 0 */ 
     KA[i][0] = (4.*KA[i][1]-KA[i][2])/3.;  /* dk/dn = 0 */ 
     EP[i][0] = (4.*EP[i][1]-EP[i][2])/3.;  /* de/dn = 0 */ 
    }
    if(wS == 4 ){                           /* periodic | periodisch */
      V[i][0] =  V[i][jmax-1];
      U[i][0] =  U[i][jmax-1];              /* Ueberlappung der ersten    */
      U[i][1] =  U[i][jmax];                /* und letzten inneren Zellen */ 
     KA[i][1] = KA[i][jmax];
     EP[i][1] = EP[i][jmax];
      P[i][1] =  P[i][jmax];
    }
    if(wS == 5 ){                           /* Log. Wandgesetz */
      U[i][0] =  -U[i][1] +  DU[i][0];
      V[i][0] =  -V[i][1] +  DV[i][0];
     KA[i][0] = -KA[i][1] + DKA[i][0];
     EP[i][0] = -EP[i][1] + DEP[i][0];
   }
   TEMP[i][0] = (4.*TEMP[i][1]-TEMP[i][2])/3.;    /* dT/dn = 0 */  

                                                         /* Nord-Rand */
                                                         /*-----------*/
    if(wN == 1 ){                                        /* free-slip / rutschen */
      V[i][jmax]   = 0.0;                                /* v = 0     */
      U[i][jmax+1] = (4.* U[i][jmax]- U[i][jmax-1])/3.;  /* du/dn = 0 */ 
     KA[i][jmax]   = 0.0;                                /* k = 0     */
     EP[i][jmax+1] = (4.*EP[i][jmax]-EP[i][jmax-1])/3.;  /* de/dn = 0 */ 
    }
    if(wN == 2 ){                                        /* no-slip / haften */
      V[i][jmax]   = 0.0;                                /* v = 0     */
      U[i][jmax+1] = (-1.0)* U[i][jmax];     /* u=0 auf Rand durch Mittelung */
     KA[i][jmax]   = 0.0;                                /* k = 0     */
     EP[i][jmax+1] = (-1.0)*EP[i][jmax];     /* e=0 auf Rand durch Mittelung */
    }
    if(wN == 3){                                     /* outflow / austroemen */
      V[i][jmax+1] =  (4.*V[i][jmax]- V[i][jmax-1])/3.;         /* dv/dn = 0 */ 
      U[i][jmax+1] =  (4.*U[i][jmax]- U[i][jmax-1])/3.;         /* du/dn = 0 */ 
     EP[i][jmax+1] = (4.*EP[i][jmax]-EP[i][jmax-1])/3.;         /* de/dn = 0 */ 
     KA[i][jmax+1] = (4.*KA[i][jmax]-KA[i][jmax-1])/3.;         /* dk/dn = 0 */ 
    }
    if(wN == 4 ){                                   /* periodic / periodisch */
      V[i][jmax]   =  V[i][1];
      U[i][jmax+1] =  U[i][2];                 /* Ueberlappung der ersten    */
     EP[i][jmax]   = EP[i][1];                 /* und letzten inneren Zellen */  
     KA[i][jmax+1] = KA[i][2];
      P[i][jmax+1] =  P[i][2];
         }
    if(wN == 5 ){                                         /* Log. Wandgesetz */
      U[i][jmax+1] =  -U[i][jmax] +  DU[i][jmax+1];
      V[i][jmax+1] =  -V[i][jmax] +  DV[i][jmax+1];
     KA[i][jmax+1] = -KA[i][jmax] + DKA[i][jmax+1];
     EP[i][jmax+1] = -EP[i][jmax] + DEP[i][jmax+1];
    }
   TEMP[i][jmax+1] = (4.*TEMP[i][jmax]-TEMP[i][jmax-1])/3.;     /* dT/dn = 0 */ 
  }

                   /*     Belegung der Randwerte an den Hinderniszellen    */
                   /* fuer den laminaren/turbulenten Fall: Haftbedingungen */
                   /*------------------------------------------------------*/
 if(tmod <= 1){  
 for(i=1;i<=imax;i++)
   for(j=1;j<=jmax;j++)
     if(FLAG[i][j] & 0x000f)   /* Die Maskierung mit 0x000ffiltert genau   */
                               /* die Hinderniszellen heraus, die zu Fluid-*/
                               /* zellen in der jeweiligen Himmelsrichtung */
                               /* benachbart sind.                         */
       switch (FLAG[i][j]){
          case B_N:  { 
		        V[i][j]   =   0.0;
                        U[i][j]   =   -U[i][j+1];
                        U[i-1][j] =   -U[i-1][j+1];
                       KA[i][j]   =   0.0;
                       EP[i][j]   =   EP[i][j+1];
                     TEMP[i][j]   = TEMP[i][j+1];
                     break;
	             }
          case B_O:  { 
		        U[i][j]   =   0.0;
                        V[i][j]   =   -V[i+1][j];
                        V[i][j-1] =   -V[i+1][j-1];
                       KA[i][j]   =   0.0;
                       EP[i][j]   =   EP[i+1][j];
                     TEMP[i][j]   = TEMP[i+1][j];
                     break;
	             }
          case B_S:  { 
		        V[i][j-1] =   0.0;
                        U[i][j]   =   -U[i][j-1];
                        U[i-1][j] =   -U[i-1][j-1];
                       KA[i][j]   =   0.0;
                       EP[i][j]   =   EP[i][j-1];
                     TEMP[i][j]   = TEMP[i][j-1];
                     break;
	             }
          case B_W:  { 
		        U[i-1][j] =   0.0;
                        V[i][j]   =   -V[i-1][j];
                        V[i][j-1] =   -V[i-1][j-1];
                       KA[i-1][j] =   0.0;
                       EP[i][j]   =   EP[i-1][j];
                     TEMP[i][j]   = TEMP[i-1][j];
                     break;
	             }
          case B_NO: { 
		        V[i][j]   =  0.0;
                        U[i][j]   =  0.0;
                        V[i][j-1] =  -V[i+1][j-1];
                        U[i-1][j] =  -U[i-1][j+1];
                       KA[i][j]   = 0.5*(KA[i][j+1]+KA[i+1][j]);
                       EP[i][j]   = 0.5*(EP[i][j+1]+EP[i+1][j]);
                     TEMP[i][j]   = 0.5*(TEMP[i][j+1]+TEMP[i+1][j]);
                     break;
	             }
          case B_SO: { 
		        V[i][j-1] =  0.0;
                        U[i][j]   =  0.0;
                        V[i][j]   =  -V[i+1][j];
                        U[i-1][j] =  -U[i-1][j-1];
                       KA[i][j]   = 0.5*(KA[i][j-1]+KA[i+1][j]);
                       EP[i][j]   = 0.5*(EP[i][j-1]+EP[i+1][j]);
                     TEMP[i][j]   = 0.5*(TEMP[i][j-1]+TEMP[i+1][j]);
                     break;
                     }
          case B_SW: { 
		        V[i][j-1] =  0.0;
                        U[i-1][j] =  0.0;
                        V[i][j]   =  -V[i-1][j];
                        U[i][j]   =  -U[i][j-1];
                       KA[i][j]   = 0.5*(KA[i][j-1]+KA[i-1][j]);
                       EP[i][j]   = 0.5*(EP[i][j-1]+EP[i-1][j]);
                     TEMP[i][j]   = 0.5*(TEMP[i][j-1]+TEMP[i-1][j]);
                     break;
	             }
          case B_NW: { 
		        V[i][j]   =  0.0;
                        U[i-1][j] =  0.0;
                        V[i][j-1] =  -V[i-1][j-1];
                        U[i][j]   =  -U[i][j+1];
                       KA[i][j]   = 0.5*(KA[i][j+1]+KA[i-1][j]);
                       EP[i][j]   = 0.5*(EP[i][j+1]+EP[i-1][j]);
                     TEMP[i][j]   = 0.5*(TEMP[i][j+1]+TEMP[i-1][j]);
                     break;
	             }
	  default :  break;
	 }
 }

                       /* Belegung der Randwerte an den Hinderniszellen    */
                       /* fuer den turbulenten Fall: Univ. Log. Wandgesetz */
 if(tmod == 2){        /*--------------------------------------------------*/
 for(i=1;i<=imax;i++)
   for(j=1;j<=jmax;j++)
     if(FLAG[i][j] & 0x000f)   /* Die Maskierung mit 0x000ffiltert genau   */
                               /* die Hinderniszellen heraus, die zu Fluid-*/
                               /* zellen in der jeweiligen Himmelsrichtung */
                               /* benachbart sind.                         */
       switch (FLAG[i][j]){
          case B_N:  { 
		        V[i][j]   =  0.0;                       /* v = 0     */
                        U[i][j]   =  -U[i][j+1]   +  DU[i][j];    
                        U[i-1][j] =  -U[i-1][j+1] +  DU[i-1][j];  
		       KA[i][j]   = -KA[i][j+1]   + DKA[i][j]; 
		       EP[i][j]   = -EP[i][j+1]   + DEP[i][j];
 		     TEMP[i][j]   = TEMP[i][j+1];               /* dT/dn = 0 */  
                     break;
	             }
          case B_O:  { 
		        U[i][j]   =   0.0;                      /* u = 0     */
                        V[i][j]   =   -V[i+1][j];      /* v=0 auf Rand durch Mittelung */    
                        V[i][j-1] =   -V[i+1][j-1];    /* v=0 auf Rand durch Mittelung */
                       KA[i][j]   =  -KA[i+1][j];      /* k=0 auf Rand durch Mittelung */
                       EP[i][j]   =   EP[i+1][j];              /* de/dn = 0 */
                     TEMP[i][j]   = TEMP[i+1][j];              /* dT/dn = 0 */
                     break;
	             }
          case B_S:  { 
                        V[i][j-1] = 0.0;                       /* v = 0     */
                        U[i][j]   = -U[i][j-1]   +  DU[i][j];    
                        U[i-1][j] = -U[i-1][j-1] +  DU[i-1][j];  
                       KA[i][j]   = -KA[i][j-1]  + DKA[i][j]; 
                       EP[i][j]   = -EP[i][j-1]  + DEP[i][j];
                     TEMP[i][j]   = TEMP[i][j-1];              /* dT/dn = 0 */ 
                     break;
	             }
          case B_W:  { 
                        U[i-1][j] =   0.0;                     /* u = 0     */	
                        V[i][j]   =   -V[i-1][j];     /* v=0 auf Rand durch Mittelung */
                        V[i][j-1] =   -V[i-1][j-1];   /* v=0 auf Rand durch Mittelung */
                       KA[i][j]   =  -KA[i-1][j];     /* k=0 auf Rand durch Mittelung */
                       EP[i][j]   =   EP[i-1][j];              /* de/dn = 0 */
                     TEMP[i][j]   = TEMP[i-1][j];              /* dT/dn = 0 */
                     break;
	             }
          case B_NO: { 
		        V[i][j]   =  0.0;
                        U[i][j]   =  0.0;
                        V[i][j-1] =  -V[i+1][j-1];
                        U[i-1][j] =  -U[i-1][j+1];
                       KA[i][j]   = 0.5*(KA[i][j+1]+KA[i+1][j]);     /* Mittelwert */
                       EP[i][j]   = 0.5*(EP[i][j+1]+EP[i+1][j]);     /* Mittelwert */
                     TEMP[i][j]   = 0.5*(TEMP[i][j+1]+TEMP[i+1][j]); /* Mittelwert */
                     break;
	             }
          case B_SO: { 
		        V[i][j-1] =  0.0;
                        U[i][j]   =  0.0;
                        V[i][j]   =  -V[i+1][j];
                        U[i-1][j] =  -U[i-1][j-1];
                       KA[i][j]   = 0.5*(KA[i][j-1]+KA[i+1][j]);
                       EP[i][j]   = 0.5*(EP[i][j-1]+EP[i+1][j]);
                     TEMP[i][j]   = 0.5*(TEMP[i][j-1]+TEMP[i+1][j]);
                     break;
                     }
          case B_SW: { 
		        V[i][j-1] =  0.0;
                        U[i-1][j] =  0.0;
                        V[i][j]   =  -V[i-1][j];
                        U[i][j]   =  -U[i][j-1];
                       KA[i][j]   = 0.5*(KA[i][j-1]+KA[i-1][j]);
                       EP[i][j]   = 0.5*(EP[i][j-1]+EP[i-1][j]);
                     TEMP[i][j]   = 0.5*(TEMP[i][j-1]+TEMP[i-1][j]);
                     break;
	             }
          case B_NW: { 
		        V[i][j]   =  0.0;
                        U[i-1][j] =  0.0;
                        V[i][j-1] =  -V[i-1][j-1];
                        U[i][j]   =  -U[i][j+1];
                       KA[i][j]   = 0.5*(KA[i][j+1]+KA[i-1][j]);
                       EP[i][j]   = 0.5*(EP[i][j+1]+EP[i-1][j]);
                     TEMP[i][j]   = 0.5*(TEMP[i][j+1]+TEMP[i-1][j]);
                     break;
	             }
	  default :  break;
	 }
  }
 FREE_RMATRIX(DU,0,imax+1,0,jmax+1);
 FREE_RMATRIX(DV,0,imax+1,0,jmax+1);
 FREE_RMATRIX(DKA,0,imax+1,0,jmax+1);
 FREE_RMATRIX(DEP,0,imax+1,0,jmax+1);
}

/*-----------------------------------------------------------------*/
/* Belegung problemabhaengiger Randbedingungen                     */
/*-----------------------------------------------------------------*/
void SETSPECBCOND(char* problem,REAL **U,REAL **V,REAL **P,REAL **TEMP,
                  REAL **KA,REAL **EP,int imax,int jmax,REAL delx,
                  REAL dely,REAL delxw,REAL delyw,REAL UI,REAL VI,
                  REAL KAI,REAL EPI)
{
  int i,j;
  REAL wert1,wert2,x,y;

  if ((strcmp(problem,"tropfen1")==0) || (strcmp(problem,"tropfen2")==0) || 
      (strcmp(problem,"damm")==0))
     return;

 /*-----------------------------------------------------------*/
 /* Driven Cavity bzw. Nischenstroemung: oberer Rand nach     */
 /* rechts mit U = 1.0 bewegt                                 */
 /*-----------------------------------------------------------*/
  else if(strcmp(problem, "dcavity")==0)
    {
     for(i=0;i<=imax;i++)
        U[i][jmax+1] = 2.0-U[i][jmax]; /* Ueber Topf mit UI gezogenes Band */
     return;
    }

 /*----------------------------------------------------------------------*/
 /* Backstep oder Wassersturz: konstante Einstroemprofile UI,VI,KAI,EPI  */
 /*                            links zwischen wert1 und wert2            */
 /*----------------------------------------------------------------------*/

  else if(strcmp(problem, "backstep")==0 || strcmp(problem, "wafa")==0)
    {
          if(strcmp(problem, "backstep")==0)
            {
             wert1 = 0.75; wert2 = 1.5;   /* Einstroembereich links */
            }
          if(strcmp(problem, "wafa")==0)
            {
             wert1 = 5.00; wert2 = 7.5;   /* Einstroembereich links */
            }
     for(j=0;j<=jmax+1;j++){
     y = (j-0.5)*dely+delyw;
   if(y > wert1 && y <= wert2){
        U[0][j] = UI;
        V[0][j] = VI;
       KA[0][j] = KAI;
       EP[0][j] = EPI;
      }
     }
     return;
    }

 /*-----------------------------------------------------------------*/
 /* Hindernisstroemung: konstante Einstroemprofile UI,KAI,EPI links */
 /*-----------------------------------------------------------------*/
  else if( strcmp(problem, "autoA")==0   || strcmp(problem, "autoB")==0   ||
           strcmp(problem, "autoC")==0   || strcmp(problem, "autoD")==0   ||
           strcmp(problem, "autoE")==0   || strcmp(problem, "balken")==0  ||
           strcmp(problem, "drachen")==0 || strcmp(problem, "duese")==0   || 
           strcmp(problem, "kreis")==0   || strcmp(problem, "ventilD")==0 || 
           strcmp(problem, "ventilK")==0 || strcmp(problem, "ventilP")==0 ||
           strcmp(problem, "ventilR")==0 )
    {
     for(j=0;j<=jmax+1;j++){
        U[0][j] = UI;
        V[0][j] = 2*VI-V[1][j];
       KA[0][j] = KAI;
       EP[0][j] = EPI;
       }
     return;
    }

 /*-----------------------------------------------------------------*/
 /* Hindernisstroemung: konstante Einstroemprofile VI,KAI,EPI unten */
 /*-----------------------------------------------------------------*/
  else if (strcmp(problem, "ventilE")==0 || strcmp(problem, "ventilL")==0 )
    {
     for(i=0;i<=imax+1;i++){
        U[i][0] = 2*UI-U[i][1];
        V[i][0] = VI;
       KA[i][0] = KAI;
       EP[i][0] = EPI;
       }
     return;
    }
 
 /*-----------------------------------------------------------*/
 /* Einstroembereich fuer Spritzguss: Mitte links, U = 1.0    */
 /*-----------------------------------------------------------*/
  else if(strcmp(problem, "spritzguss")==0){
     for (j=(int)(0.4*jmax)+1;j<=(int)(0.6*jmax);j++)
        U[0][j] = 1.0;
     return;
    }

 /*------------------------------------------------------------------------*/
 /* Natural Convection oder Fluidtrap: links TEMP = 0.5 rechts TEMP = -0.5 */
 /*                                    oben und unten adiabatisch          */
 /*------------------------------------------------------------------------*/
  else if(strcmp(problem, "convection")==0 || strcmp(problem, "fluidtrap")==0)
    {
     for(j=0; j<=jmax+1; j++){
	TEMP[0][j]      = 2*(0.5)-TEMP[1][j];                     /* beheizte Wand  */
	TEMP[imax+1][j] = 2*(-0.5)-TEMP[imax][j];                 /* gekuehlte Wand */
       }
     for(i=0;i<=imax+1;i++){
	TEMP[i][0]      = (4.*TEMP[i][1]-TEMP[i][2])/3.;
	TEMP[i][jmax+1] = (4.*TEMP[i][jmax]-TEMP[i][jmax-1])/3.;  /* adiabatische Waende */
       }
     return;
    }

 /*----------------------------------------------------------*/
 /* Rayleigh-Benard-Flow: oben TEMP = -0.5 unten TEMP = 0.5  */
 /*                       links und rechts adiabatisch       */
 /*----------------------------------------------------------*/
  else if(strcmp(problem, "rayleigh")==0)
    {
     for(j=0; j<=jmax+1; j++){
	TEMP[0][j]      = (4.*TEMP[1][j]-TEMP[2][j])/3.;         
	TEMP[imax+1][j] = (4.*TEMP[imax][j]-TEMP[imax-1][j])/3.; /* adiabatische Waende */
       }
     for(i=0;i<=imax+1;i++){
	TEMP[i][0]      = 2*(0.5)-TEMP[i][1];                    /* beheizte Wand  */
	TEMP[i][jmax+1] = 2*(-0.5)-TEMP[i][jmax];                /* gekuehlte Wand */
       }
     return;
    }

 /*------*/
 /* ELSE */
 /*------*/
  printf("Problem %s nicht definiert!\n", problem);
  return;
}

