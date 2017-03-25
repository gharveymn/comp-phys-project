//*****************************************************************turbulence.c
#include <stdio.h>
#include <math.h>
#include "datadef.h"
#include "init.h"

/*---------------------------------------------------------------*/
/* Berechnung der turbulenten Viskosit"at                        */
/*---------------------------------------------------------------*/
void COMP_NUT(REAL cmu,REAL Re,REAL delx,REAL dely,REAL delxw,
              REAL delyw,REAL **NUT,REAL **KA,REAL **EP,
              int **FLAG,int tmod,int imax,int jmax)
{
 int  i,j;
 REAL dist,dist1,dist2,ReT,Rey,fmuw,fmu;

 for (j=0;j<=jmax+1;j++){
   for (i=0;i<=imax+1;i++)
       /*              nur in Fluidzellen                */
       /*------------------------------------------------*/
        if( (FLAG[i][j] & C_F) && (FLAG[i][j] < C_E) ){

    switch(tmod)
    {
    case 0:                         /* keine Turbulenz */
                                    /*-----------------*/
            NUT[i][j] = 0.0;
            break;
    case 1:                         /* k,epsilon Modell */
                                    /*------------------*/
            NUT[i][j] = 0.0;
            if(EP[i][j] != 0.0) NUT[i][j] = cmu*KA[i][j]*KA[i][j]/EP[i][j];
            break;
    case 2:                         /* Low Reynolds Number Modell */
                                    /*----------------------------*/
            dist1 = j*dely+delyw;
              if(j > jmax-j) dist1 = (jmax+1-j)*dely+delyw;
            if(delyw > 0.0) dist = dist1;
            dist2 = i*delx+delxw;
              if(i > imax-i) dist2 = (imax+1-i)*delx+delxw;
            if(delxw > 0.0) dist = dist2;
            if(delxw > 0.0 && delyw > 0.0){
              dist = dist1;
              if(dist2 < dist1) dist = dist2;
            }
            Rey = Re*dist*sqrt(fabs(KA[i][j]));
            fmuw = 1.e-10;
            if(Rey > 0.) fmuw = (1.-exp(-0.0165*Rey));
            ReT = 0.0;
            if(EP[i][j] != 0.0) ReT = Re*KA[i][j]*KA[i][j]/EP[i][j];
            fmu = fmuw*fmuw;
            if(ReT != 0.) fmu = fmuw*fmuw*(1.+20.5/ReT);
            if(fmu > 1.) fmu = 1.;
            NUT[i][j] = 0.0;
            if(EP[i][j] != 0.0) NUT[i][j] = cmu*fmu*KA[i][j]*KA[i][j]/EP[i][j];
            break;
    default:
            NUT[i][j] = 0.0;
    }
  }
 }
}

/*----------------------------------------------------------------*/
/* Berechnung der KA- und EP-Werte                                */
/*----------------------------------------------------------------*/
void COMP_KAEP(REAL **U,REAL **V,REAL **NUT,REAL **KA,REAL **EP,
               int **FLAG,int tmod,int imax,int jmax,REAL delt,
               REAL delx,REAL dely,REAL delxw,REAL delyw,
               REAL GX,REAL GY,REAL gamma,REAL Re,REAL cmu,
               REAL cep,REAL c1,REAL c2,REAL KAI,REAL EPI)
{
 int  i,j;
 REAL DUDX,DUDY,DVDX,DVDY,GRADU,DUKADX,DVKADY,DUEPDX,DVEPDY;
 REAL DNUTDKADXDX,DNUTDKADYDY,DNUTDEPDXDX,DNUTDEPDYDY;
 REAL dist,dist1,dist2,inka,indelx2,indely2,ReT,Rey,**KA2,**EP2;
 REAL fmuw,fmu,f1,f2;

 KA2 = RMATRIX(0,imax+1,0,jmax+1);
 EP2 = RMATRIX(0,imax+1,0,jmax+1);

 indelx2 = 1./(delx*delx);
 indely2 = 1./(dely*dely);

 for (j=1;j<=jmax;j++){
   for (i=1;i<=imax;i++)
      /*              nur in Fluidzellen                */
      /*------------------------------------------------*/
       if( (FLAG[i][j] & C_F) && (FLAG[i][j] < C_E) ){

    switch(tmod)
    {
    case 1:                         /* k,epsilon Modell */
                                    /*------------------*/
            fmu = 1.;
            f1  = 1.,
            f2  = 1.;
            break;
    case 2:                         /* Low Reynolds Number Modell */
                                    /*----------------------------*/
            dist1 = j*dely+delyw;
              if(j > jmax-j) dist1 = (jmax+1-j)*dely+delyw;
            if(delyw > 0.0) dist = dist1;
            dist2 = i*delx+delxw;
              if(i > imax-i) dist2 = (imax+1-i)*delx+delxw;
            if(delxw > 0.0) dist = dist2;
            if(delxw > 0.0 && delyw > 0.0){
              dist = dist1;
              if(dist2 < dist1) dist = dist2;
            }
            Rey = Re*dist*sqrt(fabs(KA[i][j]));
            fmuw = 1.e-10;          /* mit Rey=0. w"are fmu=0. EP unbestimmt */
            if(Rey > 0.) fmuw = (1.-exp(-0.0165*Rey));
            ReT = 0.0;
            if(EP[i][j] != 0.0) ReT = Re*KA[i][j]*KA[i][j]/EP[i][j];
            fmu = fmuw*fmuw;
            if(ReT != 0.) fmu = fmuw*fmuw*(1.+20.5/ReT);
            if(fmu > 1.) fmu = 1.;
            f1 = 1.+(0.05/fmu)*(0.05/fmu)*(0.05/fmu);
            f2 = 1.-exp(-ReT*ReT);
            break;
    default:
            fmu = 1.;
            f1  = 1.,
            f2  = 1.;
    }
          DNUTDKADXDX = 0.5*((NUT[i][j]+NUT[i+1][j])*(KA[i+1][j]-KA[i][j])-
                        (NUT[i][j]+NUT[i-1][j])*(KA[i][j]-KA[i-1][j]))*indelx2;

          DNUTDKADYDY = 0.5*((NUT[i][j]+NUT[i][j+1])*(KA[i][j+1]-KA[i][j])-
                        (NUT[i][j]+NUT[i][j-1])*(KA[i][j]-KA[i][j-1]))*indely2;

          DNUTDEPDXDX = 0.5*cep/cmu*((NUT[i][j]+NUT[i+1][j])*(EP[i+1][j]-
                        EP[i][j])-(NUT[i][j]+NUT[i-1][j])*(EP[i][j]-
                        EP[i-1][j]))*indelx2;

          DNUTDEPDYDY = 0.5*cep/cmu*((NUT[i][j]+NUT[i][j+1])*(EP[i][j+1]-
                        EP[i][j])-(NUT[i][j]+NUT[i][j-1])*(EP[i][j]-
                        EP[i][j-1]))*indely2; 

          DUDX = (U[i][j]-U[i-1][j])/delx;
          DVDY = (V[i][j]-V[i][j-1])/dely;

          DUDY = 0.25*((U[i][j+1]+U[i-1][j+1])-(U[i][j-1]+U[i-1][j-1]))/dely;
          DVDX = 0.25*((V[i+1][j]+V[i+1][j-1])-(V[i-1][j]+V[i-1][j-1]))/delx;

          GRADU = 2.*DUDX*DUDX+(DUDY+DVDX)*(DUDY+DVDX)+2.*DVDY*DVDY;

          DUKADX = ((U[i][j]*0.5*(KA[i][j]+KA[i+1][j]) -
                   U[i-1][j]*0.5*(KA[i-1][j]+KA[i][j])) +
                   gamma*(fabs(U[i][j])*0.5*(KA[i][j]-KA[i+1][j]) -
                   fabs(U[i-1][j])*0.5*(KA[i-1][j]-KA[i][j])))/delx;

          DVKADY = ((V[i][j]*0.5*(KA[i][j]+KA[i][j+1]) -
                   V[i][j-1]*0.5*(KA[i][j-1]+KA[i][j])) +
                   gamma*(fabs(V[i][j])*0.5*(KA[i][j]-KA[i][j+1]) -
                   fabs(V[i][j-1])*0.5*(KA[i][j-1]-KA[i][j])))/dely;

          DUEPDX = ((U[i][j]*0.5*(EP[i][j]+EP[i+1][j]) -
                   U[i-1][j]*0.5*(EP[i-1][j]+EP[i][j])) +
                   gamma*(fabs(U[i][j])*0.5*(EP[i][j]-EP[i+1][j]) -
                   fabs(U[i-1][j])*0.5*(EP[i-1][j]-EP[i][j])))/delx;

          DVEPDY = ((V[i][j]*0.5*(EP[i][j]+EP[i][j+1]) -
                   V[i][j-1]*0.5*(EP[i][j-1]+EP[i][j])) +
                   gamma*(fabs(V[i][j])*0.5*(EP[i][j]-EP[i][j+1]) -
                   fabs(V[i][j-1])*0.5*(EP[i][j-1]-EP[i][j])))/dely;

          KA2[i][j] = KA[i][j] + delt*(DNUTDKADXDX + DNUTDKADYDY - DUKADX -
                      DVKADY + NUT[i][j]*GRADU - EP[i][j]);

          inka = 0.;
          if(KA[i][j] != 0.0) inka = 1./KA[i][j];

          EP2[i][j] = EP[i][j] + delt*(DNUTDEPDXDX + DNUTDEPDYDY -
                      DUEPDX - DVEPDY + c1*KA[i][j]*GRADU - 
                      c2*EP[i][j]*EP[i][j]*inka);
         }
       else {
          KA2[i][j] = KA[i][j];
          EP2[i][j] = EP[i][j];
            }
 }
/* physikalisch richtig sind nur positive Werte von KA und EP */
  for(i=1;i<=imax;i++)
    for(j=1;j<=jmax;j++){
          KA[i][j] = KA2[i][j];
           if(KA[i][j] < 0.0) KA[i][j] = 0.0;         
	  EP[i][j] = EP2[i][j];
           if(EP[i][j] < 1.e-10) EP[i][j] = 1.e-10;       
    }

 FREE_RMATRIX(KA2,0,imax+1,0,jmax+1);
 FREE_RMATRIX(EP2,0,imax+1,0,jmax+1);

}
