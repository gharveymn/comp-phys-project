//*****************************************************************init.c
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "datadef.h"

/*------------------------------------------------------------------*/
/* Einlesen der Problemparameter aus der Datei Inputfile            */
/*------------------------------------------------------------------*/
int READ_PARAMETER(char *Inputfile,char *problem,
                   int *pflag,REAL *xlength,REAL *ylength,int *imax,
                   int *jmax,REAL *delx,REAL *dely,REAL *t_end,
                   REAL *delt,REAL *tau,REAL *del_trace,REAL *del_inj,
                   REAL *del_streak,REAL *del_vec,char *vecfile,
                   char *zeitfile,char *tracefile,char *streakfile,
                   char *flagfile,char *infile,char *outfile,
                   int *N,REAL *pos1x,REAL *pos1y,REAL *pos2x,
                   REAL *pos2y,int *itermax,REAL *eps,REAL *omg,
                   REAL *gamma,int *p_bound,REAL *Re,REAL *Pr,
                   REAL *beta,REAL *GX,REAL *GY,REAL *UI,REAL *VI,
                   REAL *TI,int *tmod,REAL *KAI,REAL *EPI,int *wW,
                   int *wO,int *wN,int *wS,REAL *delxw,REAL *delyw){
  char c;
  FILE *fp;

 /* Durch Inputfile spezifizierte Eingabedatei oeffnen */
 /*----------------------------------------------------*/
  if ((fp = fopen(Inputfile, "r")) == NULL)
    {
     printf("Fehler beim Oeffnen der Eingabedatei\n");
     return(1);
    }

 /* Einlesen des Problemtyps und Abfrage ob Problemtyp definiert */
 /*--------------------------------------------------------------*/
  fscanf(fp, "%s", problem);
     for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c)); /* Zeilenende finden */
  if( strcmp(problem, "autoA")      && strcmp(problem, "autoB")      &&
      strcmp(problem, "autoC")      && strcmp(problem, "autoD")      &&
      strcmp(problem, "autoE")      && strcmp(problem, "backstep")   && 
      strcmp(problem, "balken")     && strcmp(problem, "convection") && 
      strcmp(problem, "damm")       && strcmp(problem, "dcavity")    && 
      strcmp(problem, "drachen")    && strcmp(problem, "duese")      && 
      strcmp(problem, "fluidtrap")  && strcmp(problem, "kreis")      && 
      strcmp(problem, "rayleigh")   && strcmp(problem, "spritzguss") && 
      strcmp(problem, "tropfen1")   && strcmp(problem, "tropfen2")   && 
      strcmp(problem, "ventilD")    && strcmp(problem, "ventilE")    && 
      strcmp(problem, "ventilK")    && strcmp(problem, "ventilL")    && 
      strcmp(problem, "ventilP")    && strcmp(problem, "ventilR")    && 
      strcmp(problem, "wafa"))
  {
    printf("Problem %s nicht definiert!\n", problem);
    printf("Waehle aus autoA\n");      printf("           autoB\n");
    printf("           autoC\n");      printf("           autoD\n");
    printf("           autoE\n");      printf("           backstep\n");
    printf("           balken\n");     printf("           convection\n");
    printf("           damm\n");       printf("           dcavity\n");
    printf("           drachen\n");    printf("           duese\n");      
    printf("           fluidtrap\n");  printf("           kreis\n");      
    printf("           rayleigh\n");   printf("           spritzguss\n"); 
    printf("           tropfen1\n");   printf("           tropfen2\n");   
    printf("           ventilD\n");    printf("           ventilE\n");    
    printf("           ventilK\n");    printf("           ventilL\n");    
    printf("           ventilP\n");    printf("           ventilR\n");    
    printf("           wafa\n");
        return(1);
  }

 /* zeilenweises Einlesen der Eingabedatei "*.par" */
 /*------------------------------------------------*/
  fscanf(fp, "%s", flagfile);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, "%s", infile);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, "%s", outfile);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));

  fscanf(fp, "%d", pflag);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, INREAL, xlength);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, INREAL, ylength);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, "%d", imax);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, "%d", jmax);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));

  fscanf(fp, INREAL, t_end); 
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
        if((*t_end) <= 0.) (*t_end) = 29.3; /*maximale Endzeit fuer stationaere Stroemung*/
  fscanf(fp, INREAL, delt); 
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, INREAL, tau); 
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));

  fscanf(fp, INREAL, del_trace);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, INREAL, del_inj);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, INREAL, del_streak);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, INREAL, del_vec);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));

  fscanf(fp, "%s", vecfile); 
     for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, "%s", zeitfile); 
     for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, "%s", tracefile); 
     for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, "%s", streakfile); 
     for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  printf("\n%s %s\n",tracefile,streakfile);
        if(*tracefile != *"kein" && *streakfile != *"kein"){
        printf("\nFehler: tracelines und streaklines in getrennten Laeufen berechnen\n\n");
        return(1);
        }

  fscanf(fp, "%d", N);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, INREAL, pos1x);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, INREAL, pos1y);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, INREAL, pos2x);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, INREAL, pos2y);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));

  fscanf(fp, "%d", itermax); 
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, INREAL, eps); 
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, INREAL, omg); 
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, INREAL, gamma); 
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, "%d", p_bound);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
 
  fscanf(fp, INREAL, Re);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, INREAL, Pr);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, INREAL, beta);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, INREAL, GX);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, INREAL, GY);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, INREAL, UI);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, INREAL, VI);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, INREAL, TI);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));

  fscanf(fp, "%d", tmod); 
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, INREAL, KAI); 
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, INREAL, EPI); 
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));

  fscanf(fp, "%d", wW);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, "%d", wO);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, "%d", wN);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, "%d", wS);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
  fscanf(fp, INREAL, delxw);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));
 fscanf(fp, INREAL, delyw);
        for(fscanf(fp,"%c",&c);c!='\n';fscanf(fp,"%c",&c));

  (*delx) = (*xlength)/(*imax); 
  if((*wO) == 5 || (*wW) == 5) (*delx) = ((*xlength)-2.*(*delxw))/(*imax);
  (*dely) = (*ylength)/(*jmax);
  if((*wN) == 5 || (*wS) == 5) (*dely) = ((*ylength)-2.*(*delyw))/(*jmax);

 /* Eingabefile schliessen */
  fclose(fp);

 /* Kontrollausgabe der eingelesenen Groessen */
 /*-------------------------------------------*/
  printf("\nProblem: %s\n",problem);
  printf("pflag=%d (1: FLAG-Matrix-Ausgabe und Programm-Stopp)\n",(*pflag));
  printf("\nxlength=%.3e  ylength=%.3e  imax=%d  jmax=%d\n",
					(*xlength),(*ylength),(*imax),(*jmax));
  printf("delx=%.3e dely=%.3e\n", (*delx),(*dely));
  printf("t_end=%.3e delt=%.3e tau=%.3e\n", (*t_end),(*delt),(*tau));
  printf("del_trace=%.3e del_inj=%.3e del_streak=%.3e del_vec=%.3e\n",
                            (*del_trace),(*del_inj),(*del_streak),(*del_vec));
  printf("vecfile: %s zeitfile: %s\n",vecfile,zeitfile);
  printf("flagfile: %s infile: %s outfile: %s\n",flagfile,infile,outfile);
  printf("tracefile: %s streakfile: %s\n",tracefile,streakfile);

  printf("N=%d pos1x=%.3e pos1y=%.3e pos2x=%.3e pos2y=%.3e\n",
                            (*N),(*pos1x),(*pos1y),(*pos2x),(*pos2y));
  printf("itermax=%d eps=%.3e omg=%.3e gamma=%.3e, p_bound=%d\n",
			    (*itermax),(*eps),(*omg),(*gamma),(*p_bound));
  printf("Re=%.3e Pr=%.3e beta=%.3e GX=%.3e GY=%.3e\n",
			    (*Re),(*Pr),(*beta),(*GX),(*GY));
  printf("UI=%.3e VI=%.3e TI=%.3e\n",
                            (*UI),(*VI),(*TI));
  printf("tmod=%d KAI=%.3e EPI=%.3e\n",
                            (*tmod),(*KAI),(*EPI));
  printf("wW=%d wO=%d wN=%d wS=%d\n\n",
                            (*wW),(*wO),(*wN),(*wS));

  if(((*wW) == 5 || (*wO) == 5) && (*delxw) == 0.0){
     printf("Fehler: Universelles Logarithmisches Wandgesetz mit delxw = %f\n\n",(*delxw));
     return(1);
    }

  if(((*wN) == 5 || (*wS) == 5) && (*delyw) == 0.0){
     printf("Fehler: Universelles Logarithmisches Wandgesetz mit delyw = %f\n\n",(*delyw));
     return(1);
    } 

  if(((*wW) == 2 || (*wO) == 2) && (*delxw) > 0.0){
     printf("Fehler: Haftbedingung mit delxw = %f\n\n",(*delxw));
     return(1);
    }

  if(((*wN) == 2 || (*wS) == 2) && (*delyw) > 0.0){
     printf("Fehler: Haftbedingung mit delyw = %f\n\n",(*delyw));
     return(1);
    }

  if((*tmod) == 2 && ((*delxw) == 0.0 && (*delyw) == 0.0)){
     printf("Fehler: Low Reynolds Number Modell mit delxw = %f und delyw = %f\n\n",(*delxw),(*delyw));
     return(1);
    }

  if((*tmod) == 0 && ((*delxw) > 0.0 && (*delyw) > 0.0)){
     printf("Fehler: laminar mit delxw = %f und delyw = %f\n\n",(*delxw),(*delyw));
     return(1);
    }

  if((*p_bound !=1) && (*p_bound != 2)){
     printf("p_bound muss den Wert 1 oder 2 haben!\n");
     return(1);
    }

  return(0);
}

/*---------------------------------------------------------------*/
/* Initialisierung der Anfangswerte fuer U,V,P,TEMP,KA und EP    */
/*---------------------------------------------------------------*/
void INIT_UVP(char *problem,
              REAL **U,REAL **V,REAL **P,REAL **TEMP,REAL **KA,
              REAL **EP,int imax,int jmax,REAL delx,REAL dely,
	      REAL delxw,REAL delyw,REAL UI,REAL VI,REAL TI,
	      REAL KAI,REAL EPI)
{
  int i,j;
  REAL x,y,hoehe,xmue2,ymueob,ymueun;

 /* Schleife durchlaeuft ALLE Zellen */
 /*----------------------------------*/
  for(i=0;i<=imax+1;i++)
    for(j=0;j<=jmax+1;j++)
      {
	U[i][j] = UI;
	V[i][j] = VI;
	P[i][j] = 0.0;
     TEMP[i][j] = TI;
       KA[i][j] = KAI;
       EP[i][j] = EPI;
      }

 /* Bei backstep wird in der unteren Haelfte U,KA,EP = 0.0 gesetzt */
 /*----------------------------------------------------------------*/
    hoehe = 0.75;
 if(strcmp(problem, "backstep")==0)
    for(i=0;i<=imax+1;i++)
      for(j=0;j<=jmax+1;j++){
       y = (j-0.5)*dely+delyw;
     if(y <= hoehe){
        U[i][j] = 0.0;
       KA[i][j] = 0.0;
       EP[i][j] = 0.0;
        }
       }

 /* Bei duese wird nach der Muendung oben und unten U = 0.0 und    */
 /*                                   KA,EP gleich KAI,EPI gesetzt */
 /*----------------------------------------------------------------*/
   xmue2  = 8.;
   ymueob = 6.;
   ymueun = 4.;
 if(strcmp(problem, "duese")==0)
    for(i=0;i<=imax+1;i++){
     x = (i-0.5)*delx+delxw;
      for(j=0;j<=jmax+1;j++){
       y = (j-0.5)*dely+delyw;
     if(x >= xmue2 && (y >= ymueob || y <= ymueun)){
        U[i][j] = 0.0;
       KA[i][j] = KAI;
       EP[i][j] = EPI;
        }
      }
    }
}

/*-------------------------------------------------------------------------*/
/* Schreiben der (Zwischen-)Ergebnisse in Binary-Datei                     */
/*-------------------------------------------------------------------------*/
void SCHREIBE_ERG_bin(REAL t_end,REAL **U,REAL **V,REAL **P,REAL **TEMP,REAL **F,
                      REAL **G,REAL **NUT,REAL **KA,REAL **EP,int **FLAG,int imax,
		      int jmax,int tmod,char* file)
{
 int i;
 FILE *fp;

 fp = fopen(file, "wb"); 

 fwrite(&imax, sizeof(int), 1, fp);
 fwrite(&jmax, sizeof(int), 1, fp);

   fwrite(&t_end, sizeof(REAL), 1, fp);
 for(i=0;i<=imax+1;i+=1)
   fwrite(U[i], sizeof(REAL), jmax+2, fp);
 for(i=0;i<=imax+1;i+=1)
   fwrite(V[i], sizeof(REAL), jmax+2, fp);
 for(i=0;i<=imax+1;i+=1)
   fwrite(P[i], sizeof(REAL), jmax+2, fp);
 for(i=0;i<=imax+1;i+=1)
   fwrite(TEMP[i], sizeof(REAL), jmax+2, fp);
 for(i=0;i<=imax+1;i+=1)
   fwrite(F[i], sizeof(REAL), jmax+2, fp);
 for(i=0;i<=imax+1;i+=1)
   fwrite(G[i], sizeof(REAL), jmax+2, fp);
 if(tmod > 0){
 for(i=0;i<=imax+1;i+=1)
   fwrite(NUT[i], sizeof(REAL), jmax+2, fp);
 for(i=0;i<=imax+1;i+=1)
   fwrite(KA[i], sizeof(REAL), jmax+2, fp);
 for(i=0;i<=imax+1;i+=1)
   fwrite(EP[i], sizeof(REAL), jmax+2, fp);
             }
 for(i=0;i<=imax+1;i+=1)
   fwrite(FLAG[i], sizeof(int), jmax+2, fp);
 fclose(fp);
}

/*-------------------------------------------------------------------------*/
/* Lesen der (Zwischen-)Ergebnisse aus Binary-Datei                        */
/*-------------------------------------------------------------------------*/
int LESE_ERG_bin(REAL *t_anf,REAL **U,REAL **V,REAL **P,REAL **TEMP,REAL **F,
                 REAL **G,REAL **NUT,REAL **KA,REAL **EP,int **FLAG,int imax,
         	 int jmax,int tmod,char* file)
{
 int i,j;
 FILE *fp;

 if(strcmp(file, "kein") == 0) return(-1);

 if( (fp = fopen(file,"rb")) == NULL){
   printf("Fehler in LESE_ERG_bin: File %s kann nicht gelesen werden!\n", file);
   return(1);
                                     }
 fread(&i, sizeof(int), 1, fp);
 fread(&j, sizeof(int), 1, fp);

 if(i!=imax || j!=jmax){
    printf("ACHTUNG: gelesener Ergebnisfile ist nicht problemkonsistent!\n");
    printf("imax = %d  jmax = %d\n", i, j);
    return(2);
                       }
   fread(t_anf, sizeof(REAL), 1, fp);
 for(i=0;i<=imax+1;i+=1)
   fread(U[i], sizeof(REAL), jmax+2, fp);
 for(i=0;i<=imax+1;i+=1)
   fread(V[i], sizeof(REAL), jmax+2, fp);
 for(i=0;i<=imax+1;i+=1)
   fread(P[i], sizeof(REAL), jmax+2, fp);
 for(i=0;i<=imax+1;i+=1)
   fread(TEMP[i], sizeof(REAL), jmax+2, fp);
 for(i=0;i<=imax+1;i+=1)
   fread(F[i], sizeof(REAL), jmax+2, fp);
 for(i=0;i<=imax+1;i+=1)
   fread(G[i], sizeof(REAL), jmax+2, fp);
 if(tmod > 0){
 for(i=0;i<=imax+1;i+=1)
   fread(NUT[i], sizeof(REAL), jmax+2, fp);
 for(i=0;i<=imax+1;i+=1)
   fread(KA[i], sizeof(REAL), jmax+2, fp);
 for(i=0;i<=imax+1;i+=1)
   fread(EP[i], sizeof(REAL), jmax+2, fp);
             }
 for(i=0;i<=imax+1;i+=1)
   fread(FLAG[i], sizeof(int), jmax+2, fp);
 fclose(fp);

 return(0);
}


/*-------------------------------------------------------------------------*/
/* RMATRIX reserviert Speicherplatz fuer eine Matrix mit Grenzen	   */
/* [nrl,nrh]x[ncl,nch]                                   		   */
/*-------------------------------------------------------------------------*/
REAL **RMATRIX(int nrl,int nrh,int ncl,int nch)
{
  int i;
  REAL **m;
  if((m = (REAL**) malloc((unsigned) (nrh-nrl+1)*sizeof(double*))) == NULL)
     {	
      printf("kein speicher\n");
      exit(0);
     }
  m -= nrl;
  for(i=nrl;i<=nrh;i++)
    {
     if((m[i] = (REAL*) malloc((unsigned) (nch-ncl+1)*sizeof(double)))==NULL)
       {	
        printf("kein speicher\n");
        exit(0);
       }
     m[i] -= ncl;
    }
  return m;
}

/*-------------------------------------------------------------------------*/
/* FREE_RMATRIX gibt Speicherplatz der durch RMATRIX allokierten Matrix m  */
/* wieder frei              						   */
/*-------------------------------------------------------------------------*/
void FREE_RMATRIX(REAL** m,int nrl,int nrh,int ncl,int nch)
{
  int i;
  for (i=nrh;i>=nrl;i--) free((void*) (m[i]+ncl));
  free((char*) (m+nrl));
}

/*-------------------------------------------------------------------------*/
/* IMATRIX reserviert Speicherplatz fuer eine Matrix mit Grenzen	   */
/* [nrl,nrh]x[ncl,nch]                                   		   */
/*-------------------------------------------------------------------------*/
int **IMATRIX(int nrl,int nrh,int ncl,int nch)
{
  int i;
  int **m;
  if((m = (int**) malloc((unsigned) (nrh-nrl+1)*sizeof(int*))) == NULL)
     {
      printf("kein speicher\n");
      exit(0);
     }
  m -= nrl;
  for(i=nrl;i<=nrh;i++)
    {
     if((m[i] = (int*) malloc((unsigned) (nch-ncl+1)*sizeof(int)))==NULL)
       {
        printf("kein speicher\n");
        exit(0);
       }
     m[i] -= ncl;
    }
  return m;
}

/*-------------------------------------------------------------------------*/
/* FREE_IMATRIX gibt Speicherplatz der durch IMATRIX allokierten Matrix m  */
/* wieder frei              						   */
/*-------------------------------------------------------------------------*/
void FREE_IMATRIX(int** m,int nrl,int nrh,int ncl,int nch)
{
  int i;
  for (i=nrh;i>=nrl;i--) free((char*) (m[i]+ncl));
  free((char*) (m+nrl));
}
