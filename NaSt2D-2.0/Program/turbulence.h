//*****************************************************************uvp.h
void COMP_NUT(REAL cmu,REAL Re,REAL delx,REAL dely,REAL delxw,
              REAL delyw,REAL **NUT,REAL **KA,REAL **EP,
              int **FLAG,int tmod,int imax,int jmax);

void COMP_KAEP(REAL **U,REAL **V,REAL **NUT,REAL **KA,REAL **EP,
               int **FLAG,int tmod,int imax,int jmax,REAL delt,
               REAL delx,REAL dely,REAL delxw,REAL delyw,REAL GX,
               REAL GY,REAL gamma,REAL Re,REAL cmu,REAL cep,
               REAL c1,REAL c2,REAL KAI,REAL EPI);
