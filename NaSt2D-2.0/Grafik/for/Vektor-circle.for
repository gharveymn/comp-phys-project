c*****************************************************************
c
c Program Vektor.for: Vector picture of the velocity w(u,v)
c start with:   dlink -a Vektor
c-----------------------------------------------------------------
c input:   lines NI, columns NJ, flow area XLENGTH,YLENGTH
c          gdf-file of data matrix X1RAY(NI),Y1RAY(NI), etc.
c          in METAFL the output-file: 'PSCL','PDF','PNG' etc.
c*****************************************************************
c
c Programm Vektor.for: Vektorbild der Geschwindigkeit w(u,v)
c starten mit:  dlink -a Vektor
c-----------------------------------------------------------------
c Eingabe: Zeilen NI, Spalten NJ, Stroemungsgebiet XLENGTH,YLENGTH
c          gdf-file der Datenmatrix X1RAY(NI),Y1RAY(NI),usw.
c          in METAFL den Ausgabe-file: 'PSCL','PDF','PNG' etc.
c*****************************************************************
c
      PROGRAM Vektor
      CHARACTER*4 A
      PARAMETER (NI=849,NJ=6,NN=1)
      PARAMETER (N1=29)
      PARAMETER (XLENGTH=20.,YLENGTH=5.)
      DIMENSION X1RAY(NI),Y1RAY(NI),X2RAY(NI),Y2RAY(NI),X3RAY(NI),
     1 Y3RAY(NI),XRAY1(N1),YRAY1(N1)
      DATA XRAY1/ 2.0,2.02,2.05,2.1,2.2,2.3,2.4,2.5,2.6,2.7,
     C 2.8,2.9,2.95,2.98,3.0,2.98,2.95,2.9,2.8,2.7,2.6,2.5,
     C 2.4,2.3,2.2,2.1,2.05,2.02,2.0/
      DATA YRAY1/ 2.5,2.64,2.717944947,2.8,2.9,2.958257569,
     C 2.989897949,3.0,2.989897949,2.958257569,2.9,2.8,
     C 2.717944947,2.64,2.5,2.36,2.28205505,2.2,2.1,
     C 2.041742431,2.010102051,2.0,2.010102051,2.041742431,
     C 2.1,2.2,2.28205505,2.36,2.5/
c
      OPEN(unit=1,file='vektorkreis.gdf')
c
      READ(1,*) A
      READ(1,*) A
      READ(1,*) A
      DO I=1,NI
       READ(1,*) X1RAY(I),Y1RAY(I),X2RAY(I),Y2RAY(I),X3RAY(I),
     1  Y3RAY(I)
      END DO
c------- checkup print X1RAY etc.(line 1, rows 2,3,4)
      WRITE(6,*) Y1RAY(1),X2RAY(1),Y2RAY(1)
      CALL PAGE(2900,1000)
      CALL METAFL('PSCL')
      CALL DISINI
      CALL PAGERA
      CALL PSFONT('Helvetica')
      CALL PAGFLL(255)
      CALL NOBGD
      CALL AXSPOS(250,800)
      CALL AXSLEN(2400,600)
      CALL LABELS('NONE','xy')
      CALL TICKS(0,'xy')
      CALL PENWID(1.)
      CALL COLOR('BLACK')
      CALL GRAF(0.,20.,0.,20.,0.,5.,0.,5.)
      CALL COLOR('RED')
      CALL PENWID(0.3)
      CALL NOCHEK
      CALL FIELD(X1RAY,Y1RAY,X2RAY,Y2RAY,NI,0)
      CALL COLOR('BLACK')
c      CALL COLOR('MAGENTA')
      CALL PENWID(3.)
      CALL FIELD(X3RAY,Y3RAY,X2RAY,Y2RAY,NI,0)
c------- framingU
      CALL SETCLR(229)
      CALL SHDPAT(16)
      CALL SHDCRV(XRAY1,YRAY1,N1,XRAY1,YRAY1,NN)
      CALL COLOR('BLACK')
      CALL CURVE(XRAY1,YRAY1,N1)
      CALL TITLE
      CALL PENWID(3.)
      CALL COLOR('CYAN')
      CALL SHDPAT(0)
c      CALL RECTAN(250,200,2400,600)
c
      CALL DISFIN
      END
c********************************************************************
