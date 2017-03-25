c********************************************************************
c Program e3Ddruck.for: surface grid of the data matrix (PSI,P etc.)
c
c start with:    dlink -a e3Ddruck
c********************************************************************
c---- input:     given lines NI, columns NJ of the data matrix ZMAT
c                desired lines NI1, columns NJ1 of the data matrix ZMAT1
c                gdf-file with the data matrix ZMAT(NI,NJ) 3D-data
c---- attention: the points of data matrix ZMAT1(NI1,NJ1) were interpolated
c                bilinear from ZMAT and form the surface grid
c                in METAFL the output file: 'PSCL','PDF','PNG','GIF' etc.
c********************************************************************
c Programm e3Ddruck.for: Oberflaechengitter der Datenmatrix (PSI,P etc.)
c
c starten mit:   dlink -a e3Ddruck
c********************************************************************
c---- Eingeben:  gegebene Zeilen NI, Spalten NJ der Datenmatrix ZMAT
c                gewuenschte Zeilen NI1, Spalten NJ1 der Datenmatrix ZMAT1
c                gdf-file mit der Datenmatrix ZMAT(NI,NJ) 3D-Daten
c---- Achtung:   die Punkte der Datenmatrix ZMAT1(NI1,NJ1) werden bilinear
c                aus ZMAT interpoliert und bilden das Oberflaechengitter
c                in METAFL Ausgabe-file: 'PSCL','PDF','PNG','GIF' etc.
c********************************************************************
      PROGRAM e3Ddruck
      REAL INTERPOL
      CHARACTER*4 A
      PARAMETER (NI=100,NJ=100,NI1=40,NJ1=40)
      DIMENSION ZMAT(NI,NJ),ZMAT1(NI1,NJ1),
     1 XRAY(NI),YRAY(NJ),XRAY1(NI1),YRAY1(NJ1),
     2 XRAY2(4),YRAY2(4),ZRAY2(4)
      DATA XRAY(1),YRAY(1),XRAY1(1),YRAY1(1)/ 4*0./
      DATA XRAY2/ 0., 0., 1., 1./
      DATA YRAY2/ 1., 0., 0., 1./
      DATA ZRAY2/ 4*0.9999/
      DATA Xmin,Xmax,Ymin,Ymax/ 0., 1., 0., 1./
c      DATA Zmin,Zmax/ 0.999912024, 1.00059497/
      DATA Zmin,Zmax/ 0.999899, 1.000101/
      OPEN(UNIT=1,file='Druck.gdf')
c
      READ(1,*) A
      READ(1,*) A
      READ(1,*) A
      DO I=1,NI
       READ(1,*) (ZMAT(I,J),J=1,NJ)
      END DO
c------- checkup plot ZMAT(line 1, column 2,3),ZMAT(NI,NJ)
      WRITE(6,*) ZMAT(1,2),ZMAT(1,3),ZMAT(NI,NJ)
c
      DX=Xmax/(NI-1)
      DY=Ymax/(NJ-1)
      DO I=2,NI
      XRAY(I)=XRAY(I-1)+DX
      END DO
      DO J=2,NJ
      YRAY(J)=YRAY(J-1)+DY
      END DO
      DX1=Xmax/(NI1-1)
      DY1=Ymax/(NJ1-1)
      DO I=2,NI1
      XRAY1(I)=XRAY1(I-1)+DX1
      END DO
      DO J=2,NJ1
      YRAY1(J)=YRAY1(J-1)+DY1
      END DO
c
      DO I=1,NI1
      DO J=1,NJ1
      ZMAT1(I,J)=INTERPOL(XRAY1(I),YRAY1(J),ZMAT,XRAY,YRAY,DX,DY,NI,NJ)
      END DO
      END DO
c------- checkup plot ZMAT1(line 1, column 2,3)ZMAT1(NI1,NJ1)
      WRITE(6,*) ZMAT1(1,2),ZMAT1(1,3),ZMAT1(NI1,NJ1)
c------- page size: landscape or user defined

c      CALL SETPAG('DA4P')
c      CALL PAGE(1700,1600)
      CALL PAGE(1800,1700)
      CALL METAFL('PS')
      CALL DISINI
      CALL RESET('ALL')
      CALL PAGERA
      CALL SETVLT('RAIN')
      CALL EUSHFT('GERMAN','!')
      CALL PSFONT('Times-Italic')
      CALL COMPLX
      CALL SHDCHA
      CALL PAGFLL(0)
      CALL NOBGD
      CALL PAGORG('BOTTOM')
      CALL ORIGIN(0,0)
      CALL PENWID(7.)
      CALL COLOR('RED')
      CALL LINE(920,435,1045,485)
      CALL LINE(1510,655,1620,695)
      CALL PENWID(0.5)
      CALL COLOR('WHITE')
      CALL AXSPOS(0,0)
      CALL AXSLEN(2000,2000)
      CALL TICKS(0,'XY')
      CALL TICKS(1,'Z')
      CALL TICLEN(80,16)
      CALL LABELS('NONE','XY')
      CALL LABDIG(4,'Z')
      CALL LABDIS(50,'Z')
      CALL NAMJUS('LEFT','Y')
      CALL NAMDIS(150,'X')
      CALL NAMDIS(150,'Y')
      CALL NAMDIS(100,'Z')
      CALL HNAME(80)
      CALL NAME('<-- Fluid flow','X')
      CALL NAME('   Cavity deep','Y')
      CALL NAME('Pressure [bar]','Z')
      CALL HEIGHT(40)
      CALL MESSAG('Wall',1550,760)
c
      CALL VIEW3D(8.,7.,2.,'ABS')
      CALL GRAF3D(Xmin,Xmax,0.,1.,Ymin,Ymax,0.,1.,Zmin,Zmax,
     1 0.9998,0.0001)
      CALL PENWID(7.)
      CALL COLOR('RED')
      CALL CURV3D(XRAY2,YRAY2,ZRAY2,4)
      CALL PENWID(0.5)
      CALL COLOR('WHITE')
      CALL BOX3D
c      CALL GRID3D(5,5,'BOTTOM')
      CALL PENWID(1.)
      CALL NOCHEK
      CALL SURCLR(88,12)
      CALL SURMAT(ZMAT1,NI1,NJ1,1,1)
      CALL COLOR('BLACK')
      CALL SHDPAT(16)
      CALL RECTAN(400,200,100,100)
c
      CALL DISFIN
      END
c********************************************************************
c
      REAL FUNCTION INTERPOL(X,Y,ZMAT,XRAY,YRAY,DX,DY,NI,NJ)
c
c---- bilinear interpolation of function ZMAT at position X,Y
c
      DIMENSION ZMAT(NI,NJ),XRAY(NI),YRAY(NJ)
c
      DO 10 I=1,NI-1
      IF(X.GE.XRAY(I).AND.X.LE.XRAY(I+1)) GOTO 20
   10 CONTINUE
   20 IF(I.GT.NI-1) I=NI-1 
      I1=I
      I2=I+1
      DO 30 J=1,NJ-1
      IF(Y.GE.YRAY(J).AND.Y.LE.YRAY(J+1)) GOTO 40
   30 CONTINUE
   40 IF(J.GT.NJ-1) J=NJ-1
      J1=J
      J2=J+1
c
      INTERPOL=1./(DX*DY)*(
     1         (XRAY(I2)-X)*(YRAY(J2)-Y)*ZMAT(I1,J1)+
     2         (X-XRAY(I1))*(YRAY(J2)-Y)*ZMAT(I2,J1)+
     3         (XRAY(I2)-X)*(Y-YRAY(J1))*ZMAT(I1,J2)+
     4         (X-XRAY(I1))*(Y-YRAY(J1))*ZMAT(I2,J2))
      RETURN
      END
c*********************************************************************










