//*****************************************************************flag.c
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "datadef.h"

/*----------------------------------------------------------------------*/
/* Belegung des Flagfeldes in Abhaengigkeit des Problemparameters       */
/*----------------------------------------------------------------------*/
void INIT_FLAG(char *problem,int **FLAG,int pflag,int imax,int jmax,
               REAL delx,REAL dely,REAL delxw,REAL delyw,int *ibound,
               char *vecfile,char *flagfile)
{

  char cst[30];
  int  i,j,k;
  int  low,up,itemp;                                              /* balken         */
  REAL mx,my,x,y,rad1,ske,fak1,fak2,fak3;                         /* kreis          */
  REAL hoehe,laenge;                                              /* backstep, wafa */
  REAL pi=2.*asin(1.0),fako,faku,xmue1,xmue2,ymueob,ymueun;       /* duese          */
  FILE *fp;

                   /* Startinitialisierung         */
                   /*------------------------------*/
                   /* aeussere Randschicht auf C_B */
                   /*------------------------------*/
  for(i=0;i<=imax+1;i++)
    {
     FLAG[i][0]      = C_B;
     FLAG[i][jmax+1] = C_B;
    }
  for(j=1;j<=jmax;j++)
    {
     FLAG[0][j]      = C_B;
     FLAG[imax+1][j] = C_B;
    }
                   /* innere Zellen zunaechst als Fluidzellen */
                   /*-----------------------------------------*/
  for(i=1;i<=imax;i++)
     for(j=1;j<=jmax;j++)
        FLAG[i][j] = C_F;

                   /* Problemabhaengige Hinderniszellen im Inneren */
                   /*----------------------------------------------*/

#include "cars.c"                    /* Autoumstroemung            */
#include "drachen.c"                 /* Drachenumstroemung         */
#include "valves.c"                  /* Ventildurchstroemung       */

                                     /* Stroemung ueber eine Stufe */

  if(strcmp(problem,"backstep") == 0 || strcmp(problem,"wafa") == 0)
    {
      if(strcmp(problem,"backstep") == 0)
        {
         hoehe  = 0.75;laenge = 7.50; /* Stufenabmessung */
        }
      if(strcmp(problem,"wafa") == 0)
        {
         hoehe  = 5.00;laenge = 5.00; /* Stufenabmessung */
        }
     for (i=0;i<=imax+1;i++){
        x = (i-0.5)*delx+delxw;
        for (j=0;j<=jmax+1;j++){
         y = (j-0.5)*dely+delyw;
         if(y <= hoehe && x <= laenge){
           FLAG[i][j] = C_B;
        }
       }
      }
    }

                          /* Hindernisstrasse mit schraegem Balken */
  if(strcmp(problem,"balken") == 0)
    {
     low = 2*jmax/5;        /* unterer und oberer Rand des Balkens */
     up  = 3*jmax/5;
     FLAG[low][low]     = C_B;
     FLAG[low][low+1]   = C_B;
     FLAG[up][up-1]     = C_B;
     FLAG[up][up]       = C_B;
     for (i=low+1;i<=up-1;i++)
        for (j=i-1;j<=i+1;j++)
           FLAG[i][j] = C_B;
    }

                                     /* Stroemung durch eine Duese */
  if(strcmp(problem,"duese") == 0)
    {
     xmue1 = 6.935;
     xmue2 = 8.;
    ymueob = 6.;
    ymueun = 4.;
     for (i=0;i<=imax+1;i++){
        x = (i-0.5)*delx+delxw;
        fako = -2.*sin((2.*x+1.5*pi*pi-4.)/pi)+8.;
        faku = +2.*sin((2.*x+1.5*pi*pi-4.)/pi)+2.;
         if(x > xmue1){
	   fako = ymueob;
	   faku = ymueun;
	 }
	for (j=0;j<=jmax+1;j++){
         y = (j-0.5)*dely+delyw;
         if(x >= 2.0 && x <= xmue2 && (y >= fako || y <= faku)){
           FLAG[i][j] = C_B;
        }
       }
      }
    }

                     /* Stroemung in teilweise getrennten Raeumen */
  if(strcmp(problem,"fluidtrap") == 0)
    {
     for(i=9*imax/22+1;i<=13*imax/22;i++)
       {
	for(j=1;j<=4*jmax/11;j++)
           FLAG[i][j] = C_B;
        for(j=8*jmax/11+1;j<=jmax;j++)
           FLAG[i][j] = C_B;
       }
    }

                                    /* Hindernisstrasse mit Kreis */
  if(strcmp(problem,"kreis") == 0)
    {
  if(strcmp(flagfile, "kein") == 0){
    printf("FLAG-Belegung analytisch\n");        /* Analytisches Setzen der FLAG-Belegung */
      mx = 3.0;                                  /* Mittelpunkt x-Richtung */
      my = 2.5;                                  /* Mittelpunkt y-Richtung */
      rad1 = 0.5;                                /* Radius */
      ske = mx+7.0*rad1;                         /* Laenge des Halbkreis-Dreieck-Profils 4D */
      for (i=1; i<=imax; i++){
        for (j=1; j<=jmax; j++){
           x = (i-0.5)*delx+delxw;
           y = (j-0.5)*dely+delyw;
           fak1 = (x-mx)*(x-mx)+(y-my)*(y-my);   /* Kreis */
//           fak2 = rad1*(x-ske)/(mx-ske)+my;    /* Stromlinienkoerper oben */
//           fak3 =-rad1*(x-ske)/(mx-ske)+my;    /* Stromlinienkoerper unten */
//           if (fak1 <= rad1*rad1 && x <= mx)   /* Halbkreis links */
//           if (fak1 <= rad1*rad1 && x >= mx)   /* Halbkreis rechts */
           if (fak1 <= rad1*rad1)                /* Kreis */
              FLAG[i][j] = C_B;
//           if (y <= fak2 && y >= fak3 && x > mx && x <= ske) /* Halbkreis-Dreieck-Profil */
//            FLAG[i][j] = C_B;
	                       }
                             }
  if(pflag == 1){                 /*Ausgabe der FLAG-Matrix zur Kontrolle und Aenderung    */
   fp = fopen(vecfile, "w");      /* bearbeiten mit : a2ps -1 -r -o file.ps -l750 file.out */
   for(j=1;j<=jmax;j+=1) {
    for(i=1;i<=imax;i+=1){
     itemp = FLAG[i][j];
     fprintf(fp,"%d ",itemp);
    }
     fprintf(fp,"\n");
    }
     fprintf(fp,"\n");
   fclose(fp);
   printf("Ausgabe der FLAG-Matrix zur Kontrolle und fuer das Einlesen von kreis.flag\n");
   exit(0);
                 }
                                   }
   else {                                   /* Einlesen der FLAG-Belegung von "kreis.flag"  */
     fp = fopen(flagfile, "r");             /* unabhaengig von pflag, wenn file vorhanden   */
     printf("FLAG-Belegung einlesen\n");
     printf("jmax=%d " "imax=%d\n",jmax,imax);
     for (j=1; j<=jmax; j++){
       cst[0] = '\0';
       k = 0;
	for (i=1; cst[k] != '\n'; i++){
	    k = 0;
	    while (!isspace((cst[k] = getc(fp))))
	    k++;
	    cst[k+1] = '\0';
	    if (k!=0)
	      FLAG[i][j] = atoi(cst);
	    else
	    i--;
                                      }
                            }
     fclose(fp);
        }
    }                                       /* Ende des Problems "kreis" */


                               /* Behaelter mit kreisfoermigem Hindernis */
  if(strcmp(problem,"spritzguss") == 0)
    {
     mx = jmax*dely/2;
     my = jmax*dely/2;
     rad1 = jmax*dely/6;
     for (i=1;i<=imax;i++)
        for (j=1;j<=jmax;j++)
          {
           x = (i-0.5)*delx;
           y = (j-0.5)*dely;
           if ((x-mx)*(x-mx)+(y-my)*(y-my) <= rad1*rad1)
              FLAG[i][j] = C_B;
	  }
    }

                  /* Testausdruck zur Kontrolle der Gebietsform */
                  /*--------------------------------------------*/
  printf ("\nGeometrie des Gebietes:\n\n");
  for(j=jmax+1;j>=0;j--)
    {
     for(i=0;i<=imax+1;i++)
        if (!(FLAG[i][j] & C_F))
           printf("**");
        else
           printf("  ");
     printf ("\n");
    }
  printf ("\n");
  printf ("\n");
                  /* Bestimmung der Randzellen-Flags */
                  /*---------------------------------*/
  (*ibound) = 0;
  for(i=1;i<=imax;i++)
     for(j=1;j<=jmax;j++){
        if (!(FLAG[i][j] & C_F))
           (*ibound)++;
                  /* In dieser Formel wird das jeweilige Bit auf 1 gesetzt,   */
		  /* wenn die entsprechende Nachbarzelle eine Fluidzelle ist. */
        FLAG[i][j] += ((FLAG[i-1][j] & C_F)*B_W + (FLAG[i+1][j] & C_F)*B_O +
                       (FLAG[i][j-1] & C_F)*B_S + (FLAG[i][j+1] & C_F)*B_N)/C_F;
        switch (FLAG[i][j]){
           case 0x0003:
           case 0x0007:
           case 0x000b:
           case 0x000c:
           case 0x000d:
           case 0x000e:
           case 0x000f:{
                     printf("Unerlaubte Hinderniszelle [%d][%d]\n",i,j);
                     exit(0);
                    }
	 }
      }
}

