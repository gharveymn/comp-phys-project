c********************************************************************
c Program for displaying of tracelines
c
c start with:   dlink -a Trace
c-----------------------------------------------------------------
c               limited on nJ traceline points; with nJ it is 
c               possible to cut the last physically false points
c               in the diagram
c               in METAFL output-file: 'PSCL','PDF','PNG' etc.
c               mark input end with: stop 5 stop 5
c********************************************************************
c Programm zur Darstellung von Bahnlinien
c
c starten mit:  dlink -a Trace
c-----------------------------------------------------------------
c               Begrenzt auf nJ Bahnlinien-Punkte; mit nJ ist es
c               moeglich, die letzten, physikalisch falschen Punkte
c               in der Darstellung wegzulassen
c               in METAFL den Ausgabe-file: 'PSCL','PDF','PNG' etc.
c               Input-Ende kennzeichnen: stop 5 stop 5
c********************************************************************
c
      PROGRAM Trace
      CHARACTER*4 A,B
      PARAMETER (N1=5,NN=1)
      DIMENSION XRAY1(N1),YRAY1(N1)
      DATA B,nJ/ 4Hstop,50000/
      DATA XRAY1/ 6.5833,9.9167,9.9167,6.5833,6.5833/
      DATA YRAY1/ 4.05  ,5.95  ,5.85  ,3.95  ,4.05/
      OPEN(unit=1,file='balken.tra')
c
      READ(1,*) A,xlength,A,ylength
c      CALL SETPAG('DA4L')
      CALL PAGE(2700,1550)
      CALL METAFL('PSCL')
      CALL DISINI
      CALL PAGERA
      CALL PSFONT('Helvetica')
      CALL PAGFLL(255)
      CALL AXSPOS(250,1270)
      CALL AXSLEN(2200,1100)
      CALL LABELS('FLOAT','xy')
      CALL LABDIG(-1,'xy')
      CALL TICKS(1,'xy')
      CALL TICPOS('LABELS','xy')
      CALL NAME('x  [-]','x')
      CALL NAME('y  [-]','y')
      CALL NAMDIS(60,'x')
      CALL PENWID(1.)
      CALL COLOR('BLACK')
      CALL GRAF(0.,xlength,0.,xlength,0.,ylength,0.,ylength)
c      CALL GRAF(0.,20.,0.,5.,0.,ylength,0.,2.)
      CALL SETCLR(229)
      CALL SHDPAT(16)
      CALL SHDCRV(XRAY1,YRAY1,N1,XRAY1,YRAY1,NN)
c------- Symbol plot
      CALL HSYMBL(1)
      CALL NOCHEK
      CALL COLOR('BLUE')
      DO 10 J=1,nJ
      READ(1,*) A,time,A,iP
      IF(A.EQ.B) GOTO 20
      IF(iP.EQ.0) GOTO 10
      READ(1,*) XP,YP
      CALL RLSYMB(21,XP,YP)
      IF(J.EQ.nJ) GOTO 30
  10  CONTINUE
  20  CALL DISFIN
      STOP 'OK'
  30  WRITE(6,*) '   '
      WRITE(6,*) 'nJ to small'
      CALL DISFIN
      STOP 'nJ to small'
      END
c********************************************************************











