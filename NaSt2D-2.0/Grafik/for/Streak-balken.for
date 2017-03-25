c********************************************************************
c Program for displaying of streaklines
c
c start with:   dlink -a Streak
c-----------------------------------------------------------------
c               limited on nJ output-pictures resp. time steps
c               in METAFL output-file: 'PSCL','PDF','PNG' etc.
c attention:    mark input end with: stop 5 stop 5
c-----------------------------------------------------------------
c rename pictures under LINUX in indicated sequence: 
c for i in disli_* ; do mv $i disl_0${i#disli_} ; done
c for i in dislin_* ; do mv $i disl_00${i#dislin_} ; done
c********************************************************************
c Programm zur Darstellung von Streichlinien
c
c starten mit:  dlink -a Streak
c-----------------------------------------------------------------
c               Begrenzt auf nJ Ausgabebilder bzw. Zeitschritte
c               in METAFL den Ausgabe-file: 'PSCL','PDF','PNG' etc.
c Achtung:      Input-Ende kennzeichnen: stop 5 stop 5
c-----------------------------------------------------------------
c Umbenennen der Bilder unter LINUX in angegebener Reihenfolge: 
c for i in disli_* ; do mv $i disl_0${i#disli_} ; done
c for i in dislin_* ; do mv $i disl_00${i#dislin_} ; done
c********************************************************************
c
      PROGRAM Streak
      CHARACTER*4 A,B
      CHARACTER*8 C
      PARAMETER (N1=5,NN=1)
      DIMENSION XRAY1(N1),YRAY1(N1)
      DATA B,nJ/ 4Hstop,5000/
      DATA XRAY1/ 6.5833,9.9167,9.9167,6.5833,6.5833/
      DATA YRAY1/ 4.05  ,5.95  ,5.85  ,3.95  ,4.05/
      OPEN(unit=1,file='balken.str')
      OPEN(unit=2,file='Temp')
c
      READ(1,*) A,xlength,A,ylength,A,A,A,A,A,A,A,A,A,N
      DO J=1,nJ
c      CALL SETPAG('DA4L')
      CALL PAGE(2700,1550)
      CALL METAFL('PNG')
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
      DO iN=1,N
      READ(1,*) A,time,A,iP
      IF(A.EQ.B) STOP 'data end'
      DO I=1,iP
          READ(1,*) XP,YP
          CALL RLSYMB(21,XP,YP)
        END DO
      END DO
      CALL COLOR('BLACK')
      CALL MESSAG('Time:',290,120)
      WRITE(2,100) time
      CLOSE(2)
      OPEN (unit=3,file='Temp')
      READ(3,*) C
      CALL MESSAG(C,490,120)
      CLOSE(3)
      OPEN (unit=2,file='Temp')
      CALL DISFIN
      END DO
  100 FORMAT(1f5.2)
c  100 FORMAT(1f6.1)
      STOP 'OK'
      END
c********************************************************************











