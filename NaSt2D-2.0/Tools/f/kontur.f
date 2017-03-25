
c*******************************************************************
c     Program for contour conversion from FIG-data
c
c     xlength,ylength:             grid dimension for NaSt2D-2.0
c     xREmin,xREmax,yREmin,yREmax: wrapping rectangle from XFIG
c     xa,ya,ye:                    favored positioning in the grid
c                                  xe follows by proportionality
c     the input  <9999. 1.>  separates the records
c     the input  <99999. 1.> stops the calculation
c-------------------------------------------------------------------
c     Programm zur Kontur-Umrechnung aus FIG-Daten
c
c     xlength,ylength:             Gitterdimension fuer NaSt2D
c     xREmin,xREmax,yREmin,yREmax: einhuellendes Rechteck aus FIG
c     xa,ya,ye:                    gewuenschte Platzierung im Gitter
c                                  xe folgt aus Proportionalitaet
c     die Eingabe <9999. 1.>  trennt die Eingabesaetze
c     die Eingabe <99999. 1.> beendet die Rechnung
c*******************************************************************
      program Kontur
c
      real mass
      open (unit=1,file='Dat.in')
      open (unit=2,file='Dat.out')
c
      data i,sep,end/ 0, 9999., 99999./
      data xlength,ylength,xREmin,xREmax,yREmin,yREmax,xa,ya,ye/
     C 10.,5.,15.,8925.,15.,2775.,3.,0.,1./
c
      mass=(ye-ya)/(yREmax-yREmin)
  10  read(1,*) x0,y0
      if(x0.eq.sep) goto 20
      if(x0.eq.end) goto 30
      x1=(x0-xREmin)*mass+xa
      y1=(yREmax-y0)*mass
      write(2,100) x1,y1
      goto 10
  20  i=0
      write(2,*) 'sep'
      goto 10
  30  stop
 100  format(1F7.4,2x,1F7.4)
      end
c*********************************************************************
