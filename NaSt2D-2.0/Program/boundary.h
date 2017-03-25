//*****************************************************************boundary.h
void SETBCOND(REAL **U,REAL **V,REAL **P,REAL **TEMP,REAL **KA,
              REAL **EP,int **FLAG,REAL KAI,REAL EPI,REAL Re,
              int imax,int jmax,int wW,int wO,int wN,int wS,
              int tmod,REAL delxw,REAL delyw,REAL cmu);

void SETSPECBCOND(char* problem,REAL **U,REAL **V,REAL **P,REAL **TEMP,
                  REAL **KA,REAL **EP,int imax,int jmax,REAL delx,
                  REAL dely,REAL delxw,REAL delyw,REAL UI,REAL VI,
                  REAL KAI,REAL EPI);

