c******************************************************************************
c     Program Drag calculates the drag coefficient of obstacles on base of
c     dimensionless pressure in the increment iv before and behind the obstacle
c     contour at a flow oncoming from left (W) and rightwards gutting (O)
c------------------------------------------------------------------
c
c     epar          input field FLAG resp. P
c     ixmax         maximum number of points in x-direction
c     iymax         maximum number of points in y-direction
c     uinf          approach velocity [km/h]
c     rhoinf        ambient density [kg/m3]
c     pinf          ambient pressure [bar]
c     iv            increment to reference position (>= 1)
c
c     input file    <Flag.in> should contain:
c                   epar,ixmax,iymax
c                   FLAG(i,j)
c
c     attention     obstacle cells in FLAG(i,j) are to mark
c                   with <0>, fluid cells with <2>
c
c     input file    <Dat.in> should contain:
c                   epar,ixmax,iymax
c                   P(i,j)
c***********************************************************************************
c     Programm Drag berechnet den Widerstands-Beiwert von Hindernissen auf der Basis 
c     des dimensionslosen Druckes im Inkrement iv vor und nach der Hindernis-
c     Kontur bei Anstroemung von links (W) und Abstroemung nach rechts (O)
c--------------------------------------------------------------------
c
c     epar          Eingabefeld FLAG bzw. P
c     ixmax         max. Punktezahl in x-Richtung
c     iymax         max. Punktezahl in y-Richtung
c     iv            Inkrement zur Referenzstelle (>= 1)
c     uinf          Anstroemgeswchwindigkeit [km/h]
c     rhoinf        Umgebungsdichte [kg/m3]
c     pinf          Umgebungsdruck [bar]
c
c     Eingabefile   <Flag.in> muss enthalten:
c                   epar,ixmax,iymax
c                   FLAG(i,j)
c
c     Achtung       Hindernis-Zellen in FLAG(i,j) sind mit <0> ,
c                   Fluid-Zellen sind mit <2> zu kennzeichnen
c
c     Eingabefile   <Dat.in> muss enthalten:
c                   epar,ixmax,iymax
c                   P(i,j)
c********************************************************************
      program Drag
c
      parameter (n=1000,nn=2000)
      integer FLAG(nn,nn)
      character*4 par(2),epar
      dimension il(n),ir(n),j(n),CPl(n),CPr(n),P(nn,nn)
c
      open (unit=1,file='Flag.in')
      open (unit=2,file='Dat.in')
      open (unit=3,file='Cpv.out')
      data par/ 'FLAG', 'P'/
      data iv,uinf,rhoinf,pinf/ 2, 100., 1.188, 1.01325/
      fak = 2.*3.6*3.6*1.e+05*pinf/(rhoinf*uinf*uinf)
c
      read(1,*) epar,ixmax,iymax
      if(epar.eq.par(1)) goto 10
      write(6,*) 'File <Flag.in> wrong'
      stop '1'
   10 read(2,*) epar,ixmax,iymax
      if(epar.eq.par(2)) goto 20
      write(6,*) 'File <Dat.in> wrong'
      stop '2'
   20 do 30 jj=1,iymax
   30 read(1,*) (FLAG(ii,jj),ii=1,ixmax)
c
c----------- checkup print
c      write(6,*) 'first and last field value FLAG ',
c     * FLAG(1,1),FLAG(ixmax,iymax)
c
      do 40 jj=1,iymax
   40 read(2,*) (P(ii,jj),ii=1,ixmax)
c
c----------- checkup print
c      write(6,*) 'first and last field value P ',
c     * P(1,1),P(ixmax,iymax)
c
      k=0
      do 60 jj=1,iymax
      do 50 ii=1,ixmax
      if(FLAG(ii,jj).eq.2) goto 50
      k=k+1
      il(k)=ii-iv
      j(k)=jj
      goto 60
   50 continue
   60 continue
      k=0
      do 80 jj=1,iymax
      do 70 ii=1,ixmax
      irev=ixmax+1-ii
      if(FLAG(irev,jj).eq.2) goto 70
      k=k+1
      ir(k)=irev+iv
      goto 80
   70 continue
   80 continue
      kn=k
      do 90 k=1,kn
      CPl(k)=2.*P(il(k),j(k))+fak
   90 CPr(k)=2.*P(ir(k),j(k))+fak
c
      suml=CPl(1)
      sumr=CPr(1)
      do 100 k=2,kn
      suml=suml+CPl(k)
  100 sumr=sumr+CPr(k)
      CPlm=suml/kn
      CPrm=sumr/kn
      write(6,*) ' CPlm = ',CPlm,' ,  CPrm = ',CPrm
      write(6,*) ' '
      write(6,*) ' Drag coefficient = ',CPlm-CPrm
      write(6,*) ' '
      write(3,*) ' k j il CPl ir CPr '
      write(3,*) ' '
      do 110 k=1,kn
  110 write(3,*) k,j(k),il(k),CPl(k),ir(k),CPr(k)
      stop 'ok'
      end
c*********************************************************************
