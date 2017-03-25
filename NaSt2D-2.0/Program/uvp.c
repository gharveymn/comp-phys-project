//*****************************************************************uvp.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "datadef.h"
#include "init.h"

/*---------------------------------------------------------------*/
/* Berechnung der Temperatur zum neuen Zeitpunkt                 */
/*---------------------------------------------------------------*/
void COMP_TEMP(REAL **U,REAL **V,REAL **TEMP,int **FLAG,
	       int imax,int jmax,REAL delt,REAL delx,REAL dely,
	       REAL gamma,REAL Re,REAL Pr)
{
 int  i,j;
 REAL LAPLT, DUTDX, DVTDY,indelx2,indely2;
 REAL **T2;

 T2 = RMATRIX(0,imax+1,0,jmax+1);

 indelx2 = 1./delx/delx;
 indely2 = 1./dely/dely;

 for(i=1;i<=imax;i++)
    for(j=1;j<=jmax;j++)
      /*              nur in Fluidzellen                */
      /*------------------------------------------------*/
       if( (FLAG[i][j] & C_F) && (FLAG[i][j] < C_E) ){

	  LAPLT = (TEMP[i+1][j]-2.0*TEMP[i][j]+TEMP[i-1][j])*indelx2 +
		  (TEMP[i][j+1]-2.0*TEMP[i][j]+TEMP[i][j-1])*indely2;

	  DUTDX = ((U[i][j]*0.5*(TEMP[i][j]+TEMP[i+1][j]) -
	          U[i-1][j]*0.5*(TEMP[i-1][j]+TEMP[i][j])) +
		  gamma*(fabs(U[i][j])*0.5*(TEMP[i][j]-TEMP[i+1][j]) -
		  fabs(U[i-1][j])*0.5*(TEMP[i-1][j]-TEMP[i][j])))/delx;

	  DVTDY = ((V[i][j]*0.5*(TEMP[i][j]+TEMP[i][j+1]) -
		  V[i][j-1]*0.5*(TEMP[i][j-1]+TEMP[i][j])) +
		  gamma*(fabs(V[i][j])*0.5*(TEMP[i][j]-TEMP[i][j+1]) -
		  fabs(V[i][j-1])*0.5*(TEMP[i][j-1]-TEMP[i][j])))/dely;

	  T2[i][j] = TEMP[i][j]+delt*(LAPLT/Re/Pr - DUTDX - DVTDY);
	 }

 for(i=1;i<=imax;i++)
    for(j=1;j<=jmax;j++)
       if( (FLAG[i][j] & C_F) && (FLAG[i][j] < C_E) )
	  TEMP[i][j] = T2[i][j];

 FREE_RMATRIX(T2,0,imax+1,0,jmax+1);
}

/*----------------------------------------------------------------*/
/* Berechnung der F- und G-Werte                                  */
/*----------------------------------------------------------------*/
void COMP_FG(REAL **U,REAL **V,REAL **TEMP,REAL **F,REAL **G,
             REAL **NUT,REAL **KA,int **FLAG,int tmod,
             int imax,int jmax,REAL delt,REAL delx,REAL dely,
             REAL GX,REAL GY,REAL gamma,REAL Re,REAL beta)
{
 int  i,j;
 REAL indelx2,indely2;
 REAL NUPP,NUPM,NUMP,DU2DX,DUVDY,DUVDX,DV2DY,LAPLU,LAPLV,LAPLUM,LAPLVM;
 REAL DNUDUDXDX,DNUDVDYDY,DNUDUDYDVDXDY,DNUDVDXDUDYDX;

 indelx2 = 1./(delx*delx);
 indely2 = 1./(dely*dely);

 for (i=1;i<=imax-1;i++)
    for (j=1;j<=jmax;j++)
       /*              nur in Fluidzellen                */
       /*------------------------------------------------*/
        if( (FLAG[i][j] & C_F) && (FLAG[i][j] < C_E) ){

                                   /* laminar */
                                   /*---------*/   
          DU2DX = ((U[i][j]+U[i+1][j])*(U[i][j]+U[i+1][j])+
	          gamma*fabs(U[i][j]+U[i+1][j])*(U[i][j]-U[i+1][j])-
	          (U[i-1][j]+U[i][j])*(U[i-1][j]+U[i][j])-
	   	  gamma*fabs(U[i-1][j]+U[i][j])*(U[i-1][j]-U[i][j]))
                  *0.25/delx;

          DUVDY = ((V[i][j]+V[i+1][j])*(U[i][j]+U[i][j+1])+
                  gamma*fabs(V[i][j]+V[i+1][j])*(U[i][j]-U[i][j+1])-
	          (V[i][j-1]+V[i+1][j-1])*(U[i][j-1]+U[i][j])-
	          gamma*fabs(V[i][j-1]+V[i+1][j-1])*(U[i][j-1]-U[i][j]))
                  *0.25/dely;

       if(tmod == 0){

          LAPLU = (U[i+1][j]-2.0*U[i][j]+U[i-1][j])*indelx2+
	          (U[i][j+1]-2.0*U[i][j]+U[i][j-1])*indely2;

          F[i][j] = U[i][j] + delt*(LAPLU/Re - DU2DX - DUVDY + GX) -
		    delt*beta*GX*(TEMP[i][j]+TEMP[i+1][j])*0.5;
                    }
       if(tmod > 0){
                                   /* turbulent */
                                   /*-----------*/
 
          NUPP = 1./Re+0.25*(NUT[i+1][j+1]+NUT[i][j+1]+NUT[i+1][j]+NUT[i][j]);

          NUPM = 1./Re+0.25*(NUT[i+1][j-1]+NUT[i][j-1]+NUT[i+1][j]+NUT[i][j]);

          DNUDUDYDVDXDY = (NUPP*((U[i][j+1]-U[i][j])/dely+(V[i+1][j]-
                          V[i][j])/delx)-NUPM*((U[i][j]-U[i][j-1])/dely+
                          (V[i+1][j-1]-V[i][j-1])/delx))/dely;

          DNUDUDXDX = ((1./Re+NUT[i+1][j])*(U[i+1][j]-U[i][j])-
                      (1./Re+NUT[i][j])*(U[i][j]-U[i-1][j]))*indelx2; 

          LAPLUM = 2.*DNUDUDXDX+DNUDUDYDVDXDY-2./3.*(KA[i+1][j]-KA[i][j])/delx;
   
          F[i][j] = U[i][j] + delt*(LAPLUM - DU2DX - DUVDY + GX) -
		    delt*beta*GX*(TEMP[i][j]+TEMP[i+1][j])*0.5;
                    }
         }
       else
          F[i][j] = U[i][j];

 for (i=1;i<=imax;i++)
    for (j=1;j<=jmax-1;j++)
       /* nur wenn beide an Kante angrenzenden Zellen Fluid enthalten */
       if( ((FLAG[i][j] & C_F) && (FLAG[i][j] < C_E)) &&
           ((FLAG[i][j+1] & C_F) && (FLAG[i][j+1] < C_E)) ){

                                   /* laminar */
                                   /*---------*/
          DV2DY = ((V[i][j]+V[i][j+1])*(V[i][j]+V[i][j+1])+
	   	  gamma*fabs(V[i][j]+V[i][j+1])*(V[i][j]-V[i][j+1])-
	          (V[i][j-1]+V[i][j])*(V[i][j-1]+V[i][j])-
	   	  gamma*fabs(V[i][j-1]+V[i][j])*(V[i][j-1]-V[i][j]))
	          *0.25/dely;

          DUVDX = ((U[i][j]+U[i][j+1])*(V[i][j]+V[i+1][j])+
	   	  gamma*fabs(U[i][j]+U[i][j+1])*(V[i][j]-V[i+1][j])-
	   	  (U[i-1][j]+U[i-1][j+1])*(V[i-1][j]+V[i][j])-
	   	  gamma*fabs(U[i-1][j]+U[i-1][j+1])*(V[i-1][j]-V[i][j]))
	          *0.25/delx;

       if(tmod == 0){

          LAPLV = (V[i+1][j]-2.0*V[i][j]+V[i-1][j])*indelx2+
	          (V[i][j+1]-2.0*V[i][j]+V[i][j-1])*indely2;

          G[i][j] = V[i][j] + delt*(LAPLV/Re - DUVDX - DV2DY + GY) -
		    delt*beta*GY*(TEMP[i][j]+TEMP[i][j+1])*0.5;
                    }
       if(tmod > 0){
                                   /* turbulent */
                                   /*-----------*/  

          NUPP = 1./Re+0.25*(NUT[i+1][j+1]+NUT[i][j+1]+NUT[i+1][j]+NUT[i][j]);

          NUMP = 1./Re+0.25*(NUT[i-1][j+1]+NUT[i][j+1]+NUT[i-1][j]+NUT[i][j]);

          DNUDVDXDUDYDX = (NUPP*((V[i+1][j]-V[i][j])/delx+(U[i][j+1]-
                          U[i][j])/dely)-NUMP*((V[i][j]-V[i-1][j])/delx+
                          (U[i-1][j+1]-U[i-1][j])/dely))/delx;  

          DNUDVDYDY = ((1./Re+NUT[i][j+1])*(V[i][j+1]-V[i][j])-
                      (1./Re+NUT[i][j])*(V[i][j]-V[i][j-1]))*indely2;

          LAPLVM = 2.*DNUDVDYDY+DNUDVDXDUDYDX-2./3.*(KA[i][j+1]-KA[i][j])/dely;

          G[i][j] = V[i][j] + delt*(LAPLVM - DUVDX - DV2DY + GY) -
		    delt*beta*GY*(TEMP[i][j]+TEMP[i][j+1])*0.5;
                     }
         }
       else
          G[i][j] = V[i][j];

                                   /* F und G am Rand */
                                   /*-----------------*/ 
 for (j=1;j<=jmax;j++){
    F[0][j]    = U[0][j];
    F[imax][j] = U[imax][j];
  }

 for (i=1;i<=imax;i++){
    G[i][0]    = V[i][0];
    G[i][jmax] = V[i][jmax];
  }
 }


/*-------------------------------------------------------------*/
/*  Berechnung der rechten Seite f"ur die Druckkorrektur RHS   */
/*-------------------------------------------------------------*/
void COMP_RHS(REAL **F,REAL **G,REAL **RHS,int **FLAG,int imax,
              int jmax,REAL delt,REAL delx,REAL dely)
{
 int i,j;

 for (i=1;i<=imax;i++)
    for (j=1;j<=jmax;j++)
       if ((FLAG[i][j] & C_F) && (FLAG[i][j] < 0x0100))
                                        /* nur fuer innere Fluidzellen */
          RHS[i][j] = ((F[i][j]-F[i-1][j])/delx+(G[i][j]-G[i][j-1])/dely)/delt;
}

/*-------------------------------------------------------------*/
/*  L"osung der Poissongleichung f"ur den Druck P              */
/*  mit rechter Seite RHS                                      */
/*  zur"uckgegeben wird Anzahl der Iterationen iter            */
/*-------------------------------------------------------------*/
int POISSON(REAL **P,REAL **RHS,int **FLAG,int imax,int jmax,
            REAL delx,REAL dely,REAL eps,int itermax,
            REAL omg,REAL *res,int ifull,int p_bound)
{
 int i,j,iter;
 REAL indelx2,indely2;
 REAL add,beta_2,beta_mod;
 REAL p0 = 0.;          /* beliebig waehlbar */


 indelx2 = 1./(delx*delx);
 indely2 = 1./(dely*dely);
 beta_2 = -omg/(2.0*(indelx2+indely2));

 for (i=1;i<=imax;i++)
   for (j=1;j<=jmax;j++)
     if (FLAG[i][j] & C_F)
       p0 += P[i][j]*P[i][j];

 p0 = sqrt(p0/ifull);
 if (p0 < 0.0001)
   p0 = 1.;
                                            /* SOR-Zyklus */
                                            /*------------*/
 for (iter=1;iter<=itermax;iter++){
    if (p_bound == 1)
                        /* erste Art der Randbehandlung beim Druck */
                        /* Modifikation der Gleichung am Rand      */
                        /*-----------------------------------------*/
      {
                        /* Relaxation ueber Fluidzellen */
                        /*------------------------------*/
       for (i=1;i<=imax;i+=1)
          for (j=1;j<=jmax;j+=1)
                        /* Normale Gleichung im Inneren */
             if (FLAG[i][j] == 0x001f)
                P[i][j] = (1.-omg)*P[i][j] - 
                          beta_2*((P[i+1][j]+P[i-1][j])*indelx2 +
                          (P[i][j+1]+P[i][j-1])*indely2 - RHS[i][j]);

                        /* Modifizierte Gleichung in Randnaehe */
                        /*-------------------------------------*/
             else if ((FLAG[i][j] & C_F) && (FLAG[i][j] < 0x0100)){
                beta_mod = -omg/((eps_O+eps_W)*indelx2+(eps_N+eps_S)*indely2);
                P[i][j] = (1.-omg)*P[i][j] -
                          beta_mod*( (eps_O*P[i+1][j]+eps_W*P[i-1][j])*indelx2 +
                                     (eps_N*P[i][j+1]+eps_S*P[i][j-1])*indely2 -
                                     RHS[i][j]);
	      }
                         /* Berechnung des Residuums */
                         /*--------------------------*/
       *res = 0.0;

       for (i=1;i<=imax;i++)
          for (j=1;j<=jmax;j++)
             if ((FLAG[i][j] & C_F) && (FLAG[i][j] < 0x0100))
                         /* nur ueber Fluidzellen */
                         /*-----------------------*/
                {
                 add =  (eps_O*(P[i+1][j]-P[i][j]) -
                         eps_W*(P[i][j]-P[i-1][j])) * indelx2 +
                        (eps_N*(P[i][j+1]-P[i][j]) -
                         eps_S*(P[i][j]-P[i][j-1])) * indely2 - RHS[i][j];
                 *res += add*add;
 	        }

        *res = sqrt((*res)/ifull)/p0;
                         /* Abbruchkriterium erfuellt? */
                         /*----------------------------*/
        if((*res) > 1.e20){
        printf("res: %g\n",(*res));
        printf("Abhilfe eventuell durch:\n");
        printf(" -- Verkleinerung von tau, aber >1.e-10 \n");
        printf(" -- imax und jmax aendern, \n"); 
        printf(" -- delxw und delyw ueberpruefen, \n"); 
        printf(" -- eps, omg und gamma ueberpruefen, \n"); 
        exit(0);
        }

        if (*res<eps)
           return iter;
       }

    else if (p_bound == 2)
                         /* zweite Art der Randbehandlung beim Druck     */
                         /* Uebertragen der Druckwerte auf Randschicht   */
                         /* und dann in allen Zellen die selbe Gleichung */
                         /*----------------------------------------------*/
      {
                         /* Setzen der Randwerte mit              */
                         /* Neumannscher Randbedingung 2. Ordnung */
                         /*---------------------------------------*/

    for (i=1;i<=imax;i+=1){
       P[i][0]      = P[i][1];
       P[i][jmax+1] = P[i][jmax];
      }

    for (j=1;j<=jmax;j+=1){
       P[0][j]      = P[1][j];
       P[imax+1][j] = P[imax][j];
      }
                         /* und an den Raendern der Hinderniszellen */
                         /*-----------------------------------------*/
       for (i=1;i<=imax;i+=1)
          for (j=1;j<=jmax;j+=1)
             if (FLAG[i][j] >=B_N && FLAG[i][j] <=B_SO)
                switch (FLAG[i][j])
	          {
 	case B_N: { P[i][j] = P[i][j+1];                 break;}
        case B_O: { P[i][j] = P[i+1][j];                 break;}
        case B_S: { P[i][j] = P[i][j-1];                 break;}
        case B_W: { P[i][j] = P[i-1][j];                 break;}
        case B_NO:{ P[i][j] = 0.5*(P[i][j+1]+P[i+1][j]); break;}
        case B_SO:{ P[i][j] = 0.5*(P[i][j-1]+P[i+1][j]); break;}
        case B_SW:{ P[i][j] = 0.5*(P[i][j-1]+P[i-1][j]); break;}
        case B_NW:{ P[i][j] = 0.5*(P[i][j+1]+P[i-1][j]); break;}
        default:                                         break;}

                         /* Relaxation ueber Fluidzellen */
                         /*------------------------------*/
       for (i=1;i<=imax;i+=1)
          for (j=1;j<=jmax;j+=1)
             if ((FLAG[i][j] & C_F) && (FLAG[i][j] < 0x0100))
                P[i][j] = (1.-omg)*P[i][j] -
                          beta_2*((P[i+1][j]+P[i-1][j])*indelx2 +
                          (P[i][j+1]+P[i][j-1])*indely2 - RHS[i][j]);

                         /* Berechnung des Residuums */
                         /*--------------------------*/
       *res = 0.0;
       for (i=1;i<=imax;i++)
          for (j=1;j<=jmax;j++)
             if ((FLAG[i][j] & C_F) && (FLAG[i][j] < 0x0100))   
                            /* nur ueber Fluidzellen */
                            /*-----------------------*/
                {
                 add =  (P[i+1][j]-2*P[i][j]+P[i-1][j])*indelx2+
                        (P[i][j+1]-2*P[i][j]+P[i][j-1])*indely2-RHS[i][j];
                 *res += add*add;
 	        }

        *res = sqrt((*res)/ifull)/p0;
                         /* Abbruchkriterium erfuellt? */
                         /*----------------------------*/
        if((*res) > 1.e20){
        printf("res: %g\n",(*res));
        exit(0);
        }

        if (*res<eps)
           return iter;
       }
    }
 return iter;
}

/*---------------------------------------------------------------*/
/*  Berechnung der neuen Geschwindigkeiten                       */
/*---------------------------------------------------------------*/
void ADAP_UV (REAL **U,REAL **V,REAL **F,REAL **G,REAL **P,int **FLAG,
              int imax,int jmax,REAL delt,REAL delx,REAL dely)
{
 int i,j;

 for (i=1;i<=imax-1;i++)
    for (j=1;j<=jmax;j++)
       /* nur wenn beide an Kante angrenzenden Zellen Fluid enthalten */
       if( ((FLAG[i][j] & C_F) && (FLAG[i][j] < C_E)) &&
           ((FLAG[i+1][j] & C_F) && (FLAG[i+1][j] < C_E)) )
          U[i][j] = F[i][j]-(P[i+1][j]-P[i][j])*delt/delx;

 for (i=1;i<=imax;i++)
    for (j=1;j<=jmax-1;j++)
       /* nur wenn beide an Kante angrenzenden Zellen Fluid enthalten */
       if( ((FLAG[i][j] & C_F) && (FLAG[i][j] < C_E)) &&
           ((FLAG[i][j+1] & C_F) && (FLAG[i][j+1] < C_E)) )
          V[i][j] = G[i][j]-(P[i][j+1]-P[i][j])*delt/dely;
}


/*------------------------------------------------------------*/
/* COMP_delt berechnet aus den Stabilitaetskriterien die neue */
/* Zeitschrittweite und setzt das flag schreibe, wenn ein     */
/* Schreibvorgang folgen soll.                                */
/*------------------------------------------------------------*/
void COMP_delt(REAL *delt, REAL t, int imax, int jmax, REAL delx, REAL dely,
               REAL **U, REAL **V, REAL Re, REAL Pr, REAL tau, int *schreibe,
               REAL del_trace, REAL del_inj, REAL del_streak, REAL del_vec){
  int i, j;
  REAL umax, vmax, deltu, deltv, deltRePr;
  REAL t_trace, t_inj, t_streak, t_vec, t_neu; 

 /*------------------------------------------------*/
 /* delt gemaess der Stabilitaetsformeln bestimmen */
 /*------------------------------------------------*/
  if(tau >= 1.0e-10){ /* sonst keine Zeitschrittweitensteuerung */
    umax = 1.0e-10; vmax = 1.0e-10;  /*Verhindert eventuelles divide by zero*/
    for(i=0; i<=imax+1; i++) for(j=1; j<=jmax+1; j++)
      if(fabs(U[i][j]) > umax)
        umax = fabs(U[i][j]);

    for(i=1; i<=imax+1; i++) for(j=0; j<=jmax+1; j++)
      if(fabs(V[i][j]) > vmax)
        vmax = fabs(V[i][j]);

    deltu = delx/umax; deltv = dely/vmax; 
    if(Pr < 1)	deltRePr = 1/(1/(delx*delx)+1/(dely*dely))*Re*Pr/2.;
    else	deltRePr = 1/(1/(delx*delx)+1/(dely*dely))*Re/2.;

    if(deltu<deltv)  /* Minimum von deltu, deltv, deltRePr berechnen */
      if(deltu<deltRePr) *delt = deltu;
      else 	       *delt = deltRePr;
    else
      if(deltv<deltRePr) *delt = deltv;
      else 	       *delt = deltRePr;
    *delt = tau*(*delt); /* Sicherheitsfaktor der Zeitschrittweitensteuerung */
   if((*delt) < 1.e-08){
    printf("WARNUNG WARNUNG WARNUNG *** delt zu klein *** mit umax,vmax,deltu,deltv,deltRePr,delt:\n %g %g %g %f %g %g\n",umax,vmax,deltu,deltv,deltRePr,*delt); 
    }  
  }

 /*-----------------------------------------------------------------*/
 /* feststellen, ob bestimmtes Ausgabe-delt angesteuert werden muss */
 /*-----------------------------------------------------------------*/
  *schreibe = 0;
  t_neu = t + (*delt);
  t_trace = t_inj = t_streak = t_vec = t_neu + 1.0e+10;

  if( (int)(t/del_trace)!=(int)(t_neu/del_trace) ){
    t_trace = (int)(t_neu/del_trace) * del_trace;
    *schreibe += 1;
  }
  if( (int)(t/del_inj)!=(int)(t_neu/del_inj) ){
    t_inj = (int)(t_neu/del_inj) * del_inj;
    *schreibe += 2;
  }
  if( (int)(t/del_streak)!=(int)(t_neu/del_streak) ){
    t_streak = (int)(t_neu/del_streak) * del_streak;
    *schreibe += 4;
  }
  if( (int)(t/del_vec)!=(int)(t_neu/del_vec) ){
    t_vec = (int)(t_neu/del_vec) * del_vec;
    *schreibe += 8;
  }
}


