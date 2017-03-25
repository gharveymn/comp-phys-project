
c*******************************************************************
c     Straight line calculation from sequent point couples
c     the input <9999. 1.>  separates the records
c     the input <99999. 1.> stops the calculation
c------------------------------------------------------------
c     Geradenberechnung aus aufeinander folgenden Punktepaaren
c     die Eingabe <9999. 1.>  trennt die Eingabesaetze
c     die Eingabe <99999. 1.> beendet die Rechnung
c------------------------------------------------------------
      program Flag
      open (unit=1,file='Dat.in')
      open (unit=2,file='Dat.out')
c
      data i,sep,end/ 0, 9999., 99999./
c
  10  read(1,*) x,y
      if(x.eq.sep) goto 20
      if(x.eq.end) goto 30
      if(i.eq.1) goto 22 
      i=i+1
      x1=x
      y1=y
      goto 10
  22  x2=x
      y2=y
      if(x1.eq.x2) goto 24
      if(y1.eq.y2) goto 26
      z1=(y1-y2)/(x1-x2)
      z2=y1-x1*(y1-y2)/(x1-x2)
      z3=1./z1
      z4=-z2/z1
      write(2,100) z1,z2,z3,z4
      x1=x2
      y1=y2
      goto 10
  24  write(2,200) x1,y1,y2
      x1=x2
      y1=y2
      goto 10
  26  write(2,300) y1,x1,x2
      x1=x2
      y1=y2
      goto 10
  20  i=0
      write(2,*) 'sep'
      goto 10
  30  stop
 100  format('y = ',1F10.5,' *x + ',1F10.5,3x,'x = ',1F10.5,
     * ' *y + ',1F10.5)
 200  format('vertical   at x = ',1F10.5,' in-between y: ',2F10.5)
 300  format('horizontal at y = ',1F10.5,' in-between x: ',2F10.5)
      end
c*********************************************************************
