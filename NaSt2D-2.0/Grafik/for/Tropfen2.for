c********************************************************************
c
c Programm zur Erzeugung der Tropfenbilder
c
c starten mit:        dlink -a Tropfen2
c********************************************************************
c                  Begrenzt auf nJ Ausgabebilder bzw. Zeitschritte
c                  in METAFL den Ausgabe-file: 'PSCL','PDF','PNG' etc.
c                  Input-Ende kennzeichnen: STOP 5 STOP 5
c
      PROGRAM Tropfen2
      CHARACTER*4 A,B
      CHARACTER*8 C
      DATA B,nJ/ "STOP",1000/
      OPEN(unit=1,file='tropfen.str')
      OPEN(unit=2,file='Dat.out')
c
      READ(1,*) A,xlength,A,ylength,A,A,A,A,A,A,A,A,A,N
      IF(N.ne.3) STOP 'Daten nicht konsistent'
      DO J=1,nJ
c
      CALL SETPAG('DA4L')
      CALL METAFL('PNG')
      CALL DISINI
      CALL PAGERA
      CALL PAGFLL(255)
      CALL AXSPOS(280,1800)
      CALL AXSLEN(2200,1650)
      CALL LABELS('NONE','xy')
      CALL TICKS(0,'xy')
      CALL PENWID(1.)
      CALL COLOR('BLACK')
      CALL GRAF(0.,xlength,0.,xlength,0.,ylength,0.,ylength)
c------- Symbole zeichnen fuer N=3 Streaklines
      CALL HSYMBL(8)
      CALL COLOR('BLUE')
      READ(1,*) A,time1,A,iP
      IF(A.EQ.B) STOP
        DO I=1,iP
          READ(1,*) XP,YP
          CALL RLSYMB(21,XP,YP)
        END DO
      CALL COLOR('RED')
        READ(1,*) A,time2,A,iP
        IF(time2.ne.time1) STOP 'Time'
        DO I=1,iP
          READ(1,*) XP,YP
          CALL RLSYMB(21,XP,YP)
        END DO
      CALL COLOR('GREEN')
        READ(1,*) A,time2,A,iP
        IF(time2.ne.time1) STOP 'Time'
        DO I=1,iP
          READ(1,*) XP,YP
          CALL RLSYMB(21,XP,YP)
        END DO
      CALL COLOR('BLACK')
      CALL MESSAG('Zeit:',290,200)
      WRITE(2,*) time1
      CLOSE(2)
      OPEN (unit=3,file='Dat.out')
      READ(3,*) C
      CALL MESSAG(C,490,200)
      CLOSE(3)
      OPEN (unit=2,file='Dat.out')
      CALL DISFIN
      END DO
      END
c********************************************************************











