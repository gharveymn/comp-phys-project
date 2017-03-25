//*****************************************************************init.h
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
                   int *wO,int *wN,int *wS,REAL *delxw,REAL *delyw);

void INIT_UVP(char *problem,
              REAL **U,REAL **V,REAL **P,REAL **TEMP,REAL **KA,
              REAL **EP,int imax,int jmax,REAL delx,REAL dely,
	      REAL delxw,REAL delyw,REAL UI,REAL VI,REAL TI,
	      REAL KAI,REAL EPI);

REAL **RMATRIX(int nrl,int nrh,int ncl,int nch);

void FREE_RMATRIX(REAL** m,int nrl,int nrh,int ncl,int nch);

int **IMATRIX(int nrl,int nrh,int ncl,int nch);

void FREE_IMATRIX(int** m,int nrl,int nrh,int ncl,int nch);

void SCHREIBE_ERG_bin(REAL t_end,REAL **U,REAL **V,REAL **P,REAL **TEMP,REAL **F,
                      REAL **G,REAL **NUT,REAL **KA,REAL **EP,int **FLAG,int imax,
		      int jmax,int tmod,char* file);

int LESE_ERG_bin(REAL *t_anf,REAL **U,REAL **V,REAL **P,REAL **TEMP,REAL **F,
                 REAL **G,REAL **NUT,REAL **KA,REAL **EP,int **FLAG,int imax,
		 int jmax,int tmod,char* file);
