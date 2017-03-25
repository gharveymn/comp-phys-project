c********************************************************************
c Program for displaying of profile lines
c
c start with:   dlink -a Profil
c-----------------------------------------------------------------
c preset onto KP profiles U(y) with N points in y-direction
c at position X+X0, which are serially located in the input-file
c in METAFL output-file: 'PSCL','PDF','PNG' etc.
c********************************************************************
c Programm zur Darstellung von Profillinien
c
c starten mit:  dlink -a Profil
c-----------------------------------------------------------------
c eingestellt auf KP Profile U(y) mit N Punkten in y-Richtung
c an der Stelle X+X0, die im Eingabe-file hintereinander liegen
c in METAFL den Ausgabe-file: 'PSCL','PDF','PNG' etc.
c********************************************************************
c
      PROGRAM Profil
      INTEGER TEMP
      PARAMETER (N1=29,N=100,NN=1,KP=9)
      DIMENSION XRAY1(N1),YRAY1(N1),XRAY(N),YRAY(N)
      DATA X0/ -0.5/
      DATA XRAY1/ 2.0,2.02,2.05,2.1,2.2,2.3,2.4,2.5,2.6,2.7,
     C 2.8,2.9,2.95,2.98,3.0,2.98,2.95,2.9,2.8,2.7,2.6,2.5,
     C 2.4,2.3,2.2,2.1,2.05,2.02,2.0/
      DATA YRAY1/ 2.5,2.64,2.717944947,2.8,2.9,2.958257569,
     C 2.989897949,3.0,2.989897949,2.958257569,2.9,2.8,
     C 2.717944947,2.64,2.5,2.36,2.28205505,2.2,2.1,
     C 2.041742431,2.010102051,2.0,2.010102051,2.041742431,
     C 2.1,2.2,2.28205505,2.36,2.5/
      OPEN(unit=1,file='profil.in')
c
c      CALL SETPAG('DA4L')
      CALL PAGE(2900,1000)
      CALL METAFL('PSCL')
      CALL DISINI
      CALL PAGERA
      CALL PSFONT('Helvetica')
      CALL PAGFLL(255)
      CALL AXSPOS(250,800)
      CALL AXSLEN(2400,600)
      CALL LABELS('NONE','xy')
      CALL TICKS(40,'x')
      CALL TICKS(0,'y')
      CALL TICPOS('REVERS','xy')
      CALL PENWID(0.3)
      CALL COLOR('BLACK')
      CALL GRAF(0.,20.,0.,20.,0.,5.,0.,5.)
      CALL SETCLR(229)
      CALL SHDPAT(16)
      CALL SHDCRV(XRAY1,YRAY1,N1,XRAY1,YRAY1,NN)
      CALL NOCHEK
      DO K=1,KP
      READ(1,*) X
      DO I=1,N
      READ(1,*) TEMP,YRAY(I),XRAY(I)
      END DO
      CALL PLOT(K,X+X0,XRAY,YRAY,N)
      END DO
      CALL DISFIN
      STOP 'OK'
      END
c********************************************************************
      SUBROUTINE PLOT(K,Z,XRAY,YRAY,N)
      DIMENSION XRAY(N),YRAY(N)
      I1=0
      I2=0
      I3=0
      I4=0
      J=0
      DO 80 I=1,N
      IF(XRAY(I).EQ.0..AND.J.EQ.0) GOTO 10
      IF(XRAY(I).LT.0..AND.J.EQ.0) GOTO 20
      IF(XRAY(I).GT.0..AND.J.EQ.1) GOTO 30
      IF(XRAY(I).GT.0..AND.J.EQ.2) GOTO 60
      IF(XRAY(I).EQ.0..AND.J.EQ.2) GOTO 40
      IF(XRAY(I).LT.0..AND.J.EQ.5) GOTO 50
      IF(XRAY(I).GT.0..AND.J.EQ.7) GOTO 70
      GOTO 80
c --- profile will 0
  10  I1=I
      J=1
      GOTO 80
c --- profile will negative
  20  I1=I
      J=2
      GOTO 80
c --- profile up 0 to positive
  30  I2=I
      J=3
      GOTO 80
c --- profile up negative to 0
  40  I2=I
      J=5
      GOTO 80
c --- profile up 0 to negative
  50  I3=I
      J=7
      GOTO 80
c --- profile up negative to positive
  60  I2=I
      J=6
      GOTO 80
c --- profile up negative to positive
  70  I4=I
      J=8
  80  END DO
      CALL PENWID(1.)
      CALL COLOR('BLUE')
      IF(J.EQ.0) GOTO 90
      IF(J.EQ.3) GOTO 100
      IF(J.EQ.6) GOTO 110
      IF(J.EQ.8) GOTO 120
      WRITE(6,*) 'K,J,I1,I2,I3,I4 ',K,J,I1,I2,I3,I4
      STOP 'J wrong'
c --- all values >0
  90  DO I=1,N
      XRAY(I)=XRAY(I)+Z
      END DO
      CALL CURVE(XRAY,YRAY,N)
      RETURN
c --- values >0 and =0
 100  DO I=1,N
      XRAY(I)=XRAY(I)+Z
      END DO
      CALL CURVE(XRAY,YRAY,I1)
      L=0
      DO I=I2-1,N
      L=L+1
      XRAY(L)=XRAY(I)
      YRAY(L)=YRAY(I)
      END DO
      CALL CURVE(XRAY,YRAY,L)
      RETURN
c --- values >0 and <0
 110  DO I=1,N
      XRAY(I)=XRAY(I)+Z
      END DO
      CALL CURVE(XRAY,YRAY,I1)
      L=0
      I2=I2-1
      DO I=I1,I2
      L=L+1
      XRAY(L)=XRAY(I)
      YRAY(L)=YRAY(I)
      END DO
      CALL COLOR('GREEN')
      CALL CURVE(XRAY,YRAY,L)
      CALL COLOR('BLUE')
      L=0
      DO I=I2,N
      L=L+1
      XRAY(L)=XRAY(I)
      YRAY(L)=YRAY(I)
      END DO
      CALL CURVE(XRAY,YRAY,L)
      RETURN
c --- values >0 and =0 and <0
 120  DO I=1,N
      XRAY(I)=XRAY(I)+Z
      END DO
      CALL CURVE(XRAY,YRAY,I1)
      L=0
      I2=I2-1
      DO I=I1,I2
      L=L+1
      XRAY(L)=XRAY(I)
      YRAY(L)=YRAY(I)
      END DO
      CALL COLOR('GREEN')
      CALL CURVE(XRAY,YRAY,L)
      L=0
      I4=I4-1
      DO I=I3,I4
      L=L+1
      XRAY(L)=XRAY(I)
      YRAY(L)=YRAY(I)
      END DO
      CALL CURVE(XRAY,YRAY,L)
      L=0
      DO I=I4,N
      L=L+1
      XRAY(L)=XRAY(I)
      YRAY(L)=YRAY(I)
      END DO
      CALL COLOR('BLUE')
      CALL CURVE(XRAY,YRAY,L)
      RETURN
      END
c********************************************************************










