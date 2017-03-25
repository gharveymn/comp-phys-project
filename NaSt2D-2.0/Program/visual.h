//*****************************************************************visual.h
void OUTPUTVEC(REAL **U,REAL **V,REAL **P,REAL **TEMP,REAL **NUT,REAL **KA,
               REAL **EP,REAL **PSI,REAL **ZETA,REAL **HEAT,int **FLAG,REAL t,
               REAL xlength,REAL ylength,REAL Re,int imax,int jmax,int tmod,
               char* vecfile,REAL delxw,REAL delyw,int wW,int wO,int wN,int wS);

void COMPPSIZETA(REAL **U,REAL **V,REAL **PSI,REAL **ZETA,int **FLAG,
                int imax,int jmax,REAL delx,REAL dely);

void COMP_HEAT(REAL **U,REAL **V,REAL **TEMP,REAL **HEAT,int **FLAG,
               REAL Re,REAL Pr,int imax,int jmax,REAL delx,REAL dely);

void ADVANCE_PARTICLES(int ibar,int jbar,REAL delx,REAL dely,REAL delt,
                       REAL **U,REAL **V,int **FLAG,
                       int N,struct particleline *Partlines);

void ADVANCE_AT_BOUND(int i,int j,REAL *x,REAL *y,REAL u,REAL v,
                      REAL **U,REAL **V,int **FLAG,
                      REAL delx,REAL dely,REAL delt);

void INJECT_PARTICLES(int N, struct particleline *Partlines);

void WRITE_PARTICLES(char *outputfile,REAL t,int N,struct particleline *Partlines);

void WRITE_PARTICLES_bin(char *partfile,int N,struct particleline *Partlines);

void PARTICLE_TRACING(char* tracefile,REAL t,REAL xlength,REAL ylength,
                      int imax,int jmax,REAL delx,REAL dely,REAL delt,
                      REAL **U,REAL **V,int **FLAG,
                      int N, struct particleline *Partlines, int schreibe);

void STREAKLINES(char* streakfile,int schreibe,REAL xlength,REAL ylength,
                 int imax, int jmax, REAL delx, REAL dely,REAL delt,REAL t,
                 REAL **U,REAL **V,int **FLAG,
                 int N, struct particleline *Partlines);

struct particle *PARTALLOC(REAL x, REAL y);

struct particleline *SET_PARTICLES(int N,REAL pos1x,REAL pos1y,
					 REAL pos2x,REAL pos2y);
