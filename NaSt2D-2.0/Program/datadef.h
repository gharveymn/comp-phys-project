//*****************************************************************datadef.h
#define REAL double
#define INREAL "%lf"
#define OUTREAL %.3e

struct particle{
     REAL x;
     REAL y;
     struct particle *next;
};

struct particleline{
     int length;
     struct particle *Particles;
};

struct particle *partalloc(REAL x, REAL y);

                         /* Makros fuer Flagfeld in Hexadezimalschreibweise */
#define C_B     0x0000   /* = dezimal 0: Hinderniszelle */
#define B_N     0x0001   /* = dezimal 1: Hinderniszellen mit benachbarten */
#define B_S     0x0002   /* = dezimal 2: Fluid- bzw. leeren Zellen in der */
#define B_W     0x0004   /* = dezimal 4: jeweiligen Himmelsrichtung       */
#define B_O     0x0008   /* = dezimal 8: */
#define B_NW    0x0005   /* = dezimal 5: */
#define B_SW    0x0006   /* = dezimal 6: */
#define B_NO    0x0009   /* = dezimal 9: */
#define B_SO    0x000a   /* = dezimal 10: */

#define C_F     0x0010   /* = dezimal 16: Fluidzelle */

#define C_E     0x1000   /* = dezimal 4096: leere Zelle                   */
#define C_N     0x0800   /* = dezimal 2048: noerdl. Nachbarzelle ist leer */
#define C_S     0x0400   /* = dezimal 1024: suedl. Nachbarzelle ist leer  */
#define C_W     0x0200   /* = dezimal  512: westl. Nachbarzelle ist leer  */
#define C_O     0x0100   /* = dezimal  256: oestl. Nachbarzelle ist leer  */
#define C_WO    0x0300   /* = dezimal  768: */
#define C_NS    0x0c00   /* = dezimal 3072: */
#define C_SW    0x0600   /* = dezimal 1536: */
#define C_NW    0x0a00   /* = dezimal 2560: */
#define C_NO    0x0900   /* = dezimal 2304: */
#define C_SO    0x0500   /* = dezimal 1280: */
#define C_SWO   0x0700   /* = dezimal 1792: */
#define C_NSW   0x0e00   /* = dezimal 3584: */
#define C_NWO   0x0b00   /* = dezimal 2816: */
#define C_NSO   0x0d00   /* = dezimal 3328: */
#define C_NSWO  0x0f00   /* = dezimal 3840: */

/* Makros fuer POISSON, bestimmen ob Nachbarzelle in entsprechender Richtung */
/* Hinderniszelle ist oder nicht.                                            */
#define eps_O !(FLAG[i+1][j] < C_F)
#define eps_W !(FLAG[i-1][j] < C_F)
#define eps_N !(FLAG[i][j+1] < C_F)
#define eps_S !(FLAG[i][j-1] < C_F)
