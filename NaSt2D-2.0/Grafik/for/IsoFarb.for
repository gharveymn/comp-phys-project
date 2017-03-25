c*************************************************************************
c Program IsoFarb.for: isolines + color-coded distribution of PSI, P etc.
c
c start with:   dlink -a IsoFarb
c-----------------------------------------------------------------------
c--- input:     lines NI, columns NJ of the data matrix ZMAT
c               number of vortex areas NTO
c               car color IFA=0/any, i.e. white/yellow
c               gdf-file of the data matrix ZMAT(NI,NJ)      isolines
c               gdf-file of the data matrix ZMAT1(NI1,NJ1)   pressure
c--- attention: ZMAT1 will be included in the graph of GRAF3,
c               should also correspond in size !!!
c               in GRAF3 are the limits of ZMAT1;
c               with dZ1min and dZ1max you can restrict these limits
c               and therewith exclude single values; the values should be
c               chosen so, that achromatic areas are not produced;
c               in METAFL the output file: 'PSCL','PDF','PNG','GIF' etc.
c--- handling:  in XV AutoCrop and save
c               in GIMP: Picture Modus RGB / magic wand / color 213,213,213 =
c               d5d5d5 on white background and save
c               in XV to 8-Bit color depth and full color compress
c**************************************************************************
c Programm IsoFarb.for: Isolinien+Farbfl. der Datenmatrix PSI,Druck etc.
c
c starten mit:  dlink -a IsoFarb
c-----------------------------------------------------------------------
c--- Eingeben:  Zeilen NI, Spalten NJ der Datenmatrix ZMAT
c               Anzahl der Totwassergebiete NTO
c               Autofarbe IFA=0/beliebig, d.h. weiss/gelb
c               gdf-file der Datenmatrix ZMAT(NI,NJ)      Isolinien
c               gdf-file der Datenmatrix ZMAT1(NI1,NJ1)   Druck
c--- Achtung:   ZMAT1 wird in die Diagramm-Flaeche von GRAF3 eingepasst,
c               muss also mit der Diagramm-Flaeche korrespondieren !!!
c               in GRAF3 die ZMAT1-Grenzen;
c               mit dZ1min und dZ1max lassen sich die Z-Grenzen einengen
c               und damit Einzelwerte ausgrenzen; die Werte sind so zu
c               waehlen, dass keine farblosen Flaechen entstehen;
c               in METAFL Ausgabe-file: 'PSCL','PDF','PNG','GIF' etc.
c- Bearbeitung: in XV AutoCrop abspeichern
c               in GIMP: Bild Modus RGB / Zauberstab / Farbe 213,213,213 =
c               d5d5d5  auf weissem Hintergrund, dann abspeichern
c               in xXV auf 8-Bit Farbtiefe und full color komprimieren
c**************************************************************************
c
      PROGRAM IsoFarb
      CHARACTER*4 A
      PARAMETER (NI=417,NJ=204,NN=1,NTO=0,IFA=1)
      PARAMETER (NI1=240,NJ1=120)
      DIMENSION ZMAT(NI,NJ),XRAY(NI),YRAY(NI)
c  or DIMENSION ZMAT(NI,NJ),XRAY(NJ),YRAY(NJ)     //if NJ > NI
      DIMENSION ZMAT1(NI1,NJ1)
      DATA Z1min,Z1max/ 0.614831984,0.641207993/
      DATA dZ1min,dZ1max/ 0.1,0./
c
      INCLUDE 'autoBdatInc.for'
      OPEN(unit=1,file='Isoli.gdf')
      OPEN(UNIT=2,file='Druck.gdf')
      Z1min=Z1min+dZ1min*(Z1max-Z1min)
      Z1max=Z1max-dZ1max*(Z1max-Z1min)
c
      READ(1,*) A
      READ(1,*) A
      READ(1,*) A
      DO I=1,NI
       READ(1,*) (ZMAT(I,J),J=1,NJ)
      END DO
c------- checkup plot ZMAT(line 1, column 2,3,4)
c      WRITE(6,*) ZMAT(1,2),ZMAT(1,3),ZMAT(1,4)
c
      READ(2,*) A
      READ(2,*) A
      READ(2,*) A
      DO I=1,NI1
       READ(2,*) (ZMAT1(I,J),J=1,NJ1)
      END DO
c------- checkup plot ZMAT1(Zeile 1, Spalten 2,3,4)
c      WRITE(6,*) ZMAT1(1,2),ZMAT1(1,3),ZMAT1(1,4)
c------- page size: landscape or user defined
      CALL SETPAG('DA4L')
c      CALL PAGE(2710,690)
      CALL METAFL('PSCL')
      CALL DISINI
      CALL PAGERA
      CALL BMPFNT('COMPLEX')
      CALL PSFONT('Helvetica')
      CALL PAGFLL(255)
      CALL NOBGD
      CALL AUTRES(NI1,NJ1)
      CALL AXSPOS(100,720)
      CALL AX3LEN(2100,700,700)
      CALL LABELS('NONE','xy')
      CALL TICKS(0,'xy')
      CALL PENWID(1.)
      CALL GRAF3(2.,8.,2.,2.,0.,2.,0.,1.,Z1min,Z1max,
     1 Z1min,50.)
      CALL CRVMAT(ZMAT1,NI1,NJ1,1,1)
c------- vortex marker
      IF(NTO.eq.0) GOTO 20
      CALL PENWID(1.)
      CALL COLOR('YELLOW')
      IN=2*NTO+1
      DO I=3,IN,2
       CALL TOTW(I,ZMAT,XRAY,YRAY,NI,NJ,NN)
      END DO
  20  CONTINUE
c------- isoline plot
c      CALL PENWID(1.)
      CALL PENWID(0.3)
      CALL COLOR('BLACK')
      CALL NOCHEK
      NA=2*NTO+3
      DO I=NA,NJ,2
       N=INT(ZMAT(I,1))
        DO J=1,N
         XRAY(J) = ZMAT(J,I)
         YRAY(J) = ZMAT(J,I+1)
        END DO
       CALL CURVE(XRAY,YRAY,N)
      END DO
c------- flow area framing
      CALL TITLE
      CALL PENWID(3.)
      CALL COLOR('CYAN')
      CALL SHDPAT(0)
      CALL RECTAN(100,20,2275,705)
c------- car + text plot
      INCLUDE 'autoBplotInc.for'
c
      CALL HEIGHT(36)
      CALL MESSAG('-',2240,680)
      CALL MESSAG('+',2240,30)
      CALL ANGLE(90)
      CALL MESSAG('pressure',2225,500)
c
      CALL DISFIN
      END
c********************************************************************
      SUBROUTINE TOTW(I,ZMAT,XRAY,YRAY,NI,NJ,NN)
c
c------- plot of vortex areas as line I of ZMAT
      DIMENSION ZMAT(NI,NJ),XRAY(NI),YRAY(NI)
      N=INT(ZMAT(I,1))
      DO J=1,N
       XRAY(J) = ZMAT(J,I)
       YRAY(J) = ZMAT(J,I+1)
      END DO
c
      CALL SHDPAT(16)
      CALL SHDCRV(XRAY,YRAY,N,XRAY,YRAY,NN)
      RETURN
      END
c********************************************************************














