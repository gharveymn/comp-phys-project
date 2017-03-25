c***********************************************************************
c     Program creates input files for GNUPLOT and DISLIN
c-------------------------------------------------------
c
c     mod = 1  GNUPLOT-3D data
c           2  GNUPLOT isolines (for PSI, ZETA, etc.)
c           3  DISLIN-3D data
c           4  DISLIN vector-data with scaling (sclf)
c           5  DISLIN isolines (for PSI, ZETA, etc.)
c           6  DISLIN isolines from GNUPLOT isolines
c           7  Profile data x(i),y(j),z(i,j) for i or j constant
c     epar     input field, e.g. U,V,UV,TEMP,P,PSI,ZETA etc.
c     ipr      interpolation either at x or at y constant
c     ixmax    maximum number of points in x-direction
c     iymax    maximum number of points in y-direction
c     xlength  grid length in x-direction [-]
c     ylength  grid length in y-direction [-]
c     delxw    thickness of viscous sublayer west, east [-]
c     delyw    thickness of viscous sublayer north, south [-]
c     isoa     iso initial value
c     isoe     iso end valua
c     diso     iso increment
c     sclf     vector scaling factor
c
c     input file    <Dat.in> should contain:
c     generally:    mod,epar,ipr,ixmax,iymax,xlength,ylength,delxw,delyw
c                   z(i,j)                            mod= 1,3
c                   an addend z0 (for mod 3) free selectable
c                           = U(i,j)                       4
c                           = PSI(i,j) or ZETA(i,j)        2 resp. 5
c     additionally: V(i,j)                                 4
c                   isoa,isoe,diso                         2 resp. 5
c                   sclf                                   4
c                   ik,jk                                  7
c                   ik resp. jk specify the interpolation position
c     attention:    the other value ik or jk should be -1
c
c     in event of                                     mod= 6
c     generally:    mod,epar,ipr,ixmax,iymax,xlength,ylength,delxw,delyw
c                   GNUPLOT data file
c                   with -1. -1. -1.   after "each" record
c                        -2. -2. -2.   the data end
c
c***********************************************************************
c     Programm erstellt Eingabedateien fuer GNUPLOT und DISLIN
c-------------------------------------------------------------
c
c     mod = 1  GNUPLOT-3D-Daten
c           2  GNUPLOT-Isolinien (fuer PSI, ZETA etc.)
c           3  DISLIN-3D-Daten
c           4  DISLIN-Vektor-Daten mit Skalierung (sclf)
c           5  DISLIN-Isolinien (fuer PSI, ZETA etc.)
c           6  DISLIN-Isolinien aus GNUPLOT-Isolinien
c           7  Profildaten x(i),y(j),z(i,j) fuer i oder j konstant
c     epar     Eingabefeld, z.B. U,V,UV,TEMP,P,PSI,ZETA etc.
c     ipr      Interpolation entweder bei x oder bei y konstant
c     ixmax    max. Punktezahl in x-Richtung
c     iymax    max. Punktezahl in y-Richtung
c     xlength  Gebietslaenge in x-Richtung [-] 
c     ylength  Gebietslaenge in y-Richtung [-] 
c     delxw    Dicke der viskosen Unterschicht W,O [-] 
c     delyw    Dicke der viskosen Unterschicht N,S [-] 
c     isoa     iso-Anfangswert
c     isoe     iso-Endwert
c     diso     iso-Inkrement
c     sclf     Vektor Skalierungsfaktor
c
c     Eingabefile   <Dat.in> muss enthalten:
c     allgemein:    mod,epar,ipr,ixmax,iymax,xlength,ylength,delxw,delyw
c                   z(i,j)                            mod= 1,3
c                   ein Additionswert z0 (fuer mod 3) ist frei waehlbar
c                           = U(i,j)                       4
c                           = PSI(i,j) oder ZETA(i,j)      2 bzw.5
c     zusaetzlich:  V(i,j)                                 4
c                   isoa,isoe,diso                         2 bzw.5
c                   sclf                                   4
c                   ik,jk                                  7
c                   ik oder jk spezifizieren die Interpolations-Stelle
c     Achtung:      der andere Wert ik oder jk muss -1 sein
c
c     im Fall                                         mod= 6
c     allgemein:    mod,epar,ipr,ixmax,iymax,xlength,ylength,delxw,delyw
c                   GNUPLOT-Datenfile 
c                   mit  -1. -1. -1.   nach "jedem" Datenblock
c                        -2. -2. -2.   als Datenende   
c***********************************************************************
      program Datgen
c
      real INTERPOL,iso,isoa,isoe,
     C integ0,integ1,integn,integz
      character*4 par(4),epar,ipr
      dimension x(2000),y(2000),zz(2000),xx1(4000),yy1(4000)
      dimension x1(4000000),x2(4000000),y1(4000000),
     C y2(4000000),x3(4000000),y3(4000000)
      dimension alf(2000,2000),v(2000,2000),w(2000,2000),
     C z(2000,2000)
c     defined is as maximum number of value couples per isoline section
c     data nn/ 2000/
c     common dfeld(nn,nn),xx(2*nn),yy(2*nn)
      common dfeld(2000,2000),xx(4000),yy(4000)
      common/ii/i1,i2
      equivalence (alf,dfeld)
      open (unit=1,file='Dat.in')
      open (unit=2,file='Dat.out')
      open (unit=3,file='Dat.out1')
c
c     settings:
c-------------------- limitation of vector output:
c     ii resp. jj = 2 considered only every second vector value
c
c-------------------- isoline PSI resp. ZETA:
c     ip = 1/2        simply or multiple interpolation
c     io = 1/0        isolines put in order or not,
c                     put in order is important for closed isolines
c
c-------------------- DISLIN-3D data for diagram sections
c     xa,xe,ya,ye     are the section coordinates
c
c     z0              addend value (for mod 3), free selectable
c------------------------------------------------------------------
      data ii,jj,ip,io/ 8, 3, 2, 1/
      data xa,xe,ya,ye/ 2.,8.,0.,2./
      data nn,isp,iemax/ 2000, 1, 1/
      data xmin,ymin,z0/ 0., 0., 0./
      data iad,par/ 0,'U','ZETA','PSI','HEAT'/
c
      read(1,*) mod,epar,ipr,ixmax,iymax,xlength,ylength,delxw,delyw
      if(xe.le.0.) xe=xlength
      if(ye.le.0.) ye=ylength
      if(mod.ne.3) z0=0.
      if(mod.eq.6) goto 400
      if(epar.eq.par(2)) iad=-1
      if(epar.eq.par(3).or.epar.eq.par(4)) iad=+1
      ixmax=ixmax+iad 
      iymax=iymax+iad
      if(ixmax.gt.nn.or.iymax.gt.nn)
     C stop 'field dimensioning to small'
      do 10 j=1,iymax
  10  read(1,*) (z(i,j),i=1,ixmax)
c----------- Kontrollausdruck
      write(2,*) 'first and last field value with z0 in ',epar,': ',
     C z(1,1),z(ixmax,iymax),' z0 = ',z0
      do 20 j=1,iymax
      do 20 i=1,ixmax
      z(i,j)=z(i,j)+z0
      if(z(i,j).ne.0..or.z(i,j).ne.z0) zmin=z(i,j)
  20  continue
      zmax=zmin
      do 30 j=1,iymax
      do 30 i=1,ixmax
      if(z(i,j).eq.0..or.z(i,j).eq.z0) goto 30
      zmin=min(z(i,j),zmin)
      zmax=max(z(i,j),zmax)
  30  continue
      dx=(xlength-2.*delxw)/real(ixmax-1)
      dy=(ylength-2.*delyw)/real(iymax-1)
      xmin=xmin+delxw
      x(1)=xmin
      do 40 i=2,ixmax
  40  x(i)=x(i-1)+dx
      ymin=ymin+delyw
      y(1)=ymin
      do 50 j=2,iymax
  50  y(j)=y(j-1)+dy
      goto (60,220,80,100,220,400,550), mod
c
c------------------------------------------- GNUPLOT-3D data
  60  write(2,*) 'z-limits without 0. resp. z0: ',zmin,zmax
      do 70 i=1,ixmax
      do 70 j=1,iymax
  70  write(2,*) x(i),y(j),z(i,j)
      goto 600
c-------------------------------- DISLIN-3D data (diagram section)
  80  write(2,*) 'diagram section xa,xe,ya,ye: ',xa,xe,ya,ye
      write(2,*) 'z-limits without 0. resp. z0: ',zmin,zmax
      write(2,*) '%GCL-ASC'
      write(2,*) '%DATA'
      ia=ixmax*(xa/xlength)+1
      ie=ixmax*(xe/xlength)
      ja=iymax*(ya/ylength)+1
      je=iymax*(ye/ylength)
      write(2,*) je-ja+1,'// number of lines ',ie-ia+1,
     C ' number of columns ',je-ja+1
      do 90 i=ia,ie
  90  write(2,*) (z(i,j),j=ja,je)
      goto 600
c
c------------------------------------------- vector data
 100  nn=ixmax*iymax
      pi=2.*asin(1.)
      do 110 j=1,iymax
 110  read(1,*) (v(i,j),i=1,ixmax)
      read(1,*) sclf
c----------- checkup print
      write(2,*) 'first and last field value V ',
     C v(1,1),v(ixmax,iymax),' sclf = ',sclf
      do 120 i=1,ixmax
      do 120 j=1,iymax
 120  w(i,j)=sqrt(z(i,j)**2 + v(i,j)**2)
      in=0
      do 200 i=1,ixmax,ii
      do 200 j=1,iymax,jj
      in=in+1  
      if(z(i,j)) 170,130,180
 130  if(v(i,j)) 140,150,160
 140  alf(i,j)=-pi
      goto 190
 150  alf(i,j)=0.
      goto 190
 160  alf(i,j)=pi
      goto 190
 170  alf(i,j)=pi-atan(abs(v(i,j)/z(i,j)))
      if(v(i,j).ge.0.) goto 190
      alf(i,j)=pi+atan(abs(v(i,j)/z(i,j)))
      goto 190
 180  alf(i,j)=atan(abs(v(i,j)/z(i,j)))
      if(v(i,j).ge.0.) goto 190
      alf(i,j)=-atan(abs(v(i,j)/z(i,j)))
 190  continue
c----------- checkup print
c      write(2,*) in,x(i),y(j),w(i,j),alf(i,j),alf(i,j)*180./pi
      x1(in)=x(i)
      y1(in)=y(j)
      x2(in)=x(i)+w(i,j)*sclf*cos(alf(i,j))
      y2(in)=y(j)+w(i,j)*sclf*sin(alf(i,j))
      x3(in)=x(i)+w(i,j)*0.95*sclf*cos(alf(i,j))
 200  y3(in)=y(j)+w(i,j)*0.95*sclf*sin(alf(i,j))
      write(2,*) '%GCL-ASC'
      write(2,*) '%DATA'
      write(2,*) '6// scaling ',sclf,' max. ',
     C in,' xStart, yStart, xEnd, yEnd ...'
      do 210 i=1,in
 210  write(2,*) x1(i),y1(i),x2(i),y2(i),x3(i),y3(i)
      goto 600
c
c------------------------------------GNUPLOT-isoline data
 220  write(2,*) 'iso-limits without 0.: ',zmin,zmax
      read(1,*) isoa,isoe,diso
c----------- checkup print
      write(2,*) 'start, end, incr. ',
     C isoa,isoe,diso
      iso=isoa
 230  ij=1
c----------- interpolation at x constant
      if(ipr.eq.'y') goto 270
      do 260 i=1,ixmax
      do 240 j=1,iymax
 240  zz(j)=z(i,j)
      yy(ij)=INTERPOL(iso,y,zz,iymax,3,is,iflag)
      xx(ij)=x(i)
      if(iflag.eq.0) ij=ij+1
      if(ip.eq.1) goto 260
      if(is.ge.iymax) goto 260
 250  yy(ij)=INTERPOL(iso,y,zz,iymax,is+1,is,iflag)
      xx(ij)=x(i)
      if(iflag.eq.0) ij=ij+1
      if(is.ge.iymax) goto 260
      goto 250
 260  continue
      goto 310
c----------- interpolation at y constant
 270  do 300 j=1,iymax
      do 280 i=1,ixmax
 280  zz(i)=z(i,j)
      xx(ij)=INTERPOL(iso,x,zz,ixmax,3,is,iflag)
      yy(ij)=y(j)
      if(iflag.eq.0) ij=ij+1
      if(ip.eq.1) goto 300
      if(is.ge.ixmax) goto 300
 290  xx(ij)=INTERPOL(iso,x,zz,ixmax,is+1,is,iflag)
      yy(ij)=y(j)
      if(iflag.eq.0) ij=ij+1
      if(is.ge.ixmax) goto 300
      goto 290
 300  continue
 310  ie=ij-1
      if(ie.le.2.or.io.eq.0) goto 330
      ie1=2*nn
      if(ipr.eq.'x') call ORDNE(xx,yy,ie,xx1,yy1,ie1)
      if(ipr.eq.'y') call ORDNE(yy,xx,ie,yy1,xx1,ie1)
      ie=ie1
      do 320 i=1,ie
      xx(i)=xx1(i)
 320  yy(i)=yy1(i)
 330  if(ie.le.0) goto 370
      goto (600,340,600,600,360), mod
 340  do 350 i=1,ie
 350  write(2,*) xx(i),yy(i),iso
      write(2,*) '     '
      goto 370
 360  call FELD(isp,ispe,ie,iemax,iso)
 370  iso=iso+diso
      if(iso.le.isoe*1.0001) goto 230
      if(mod.lt.5) goto 600
c--------- int(dfeld(isp,1)) contains the number of values of column isp
c--------- dfeld(isp,2)      contains the iso-values of column isp
 380  if(iemax.lt.ispe) iemax=ispe
      write(2,*) '%GCL-ASC'
      write(2,*) '%DATA'
      write(2,*) ispe,'// number of lines ',
     C iemax,' number of columns ',ispe
      do 390 i=1,ispe
      np=nint(dfeld(i,1))
c----------- checkup print
 390  write(3,*) 'line,number,level: ',i,np,dfeld(i,2)
      do 395 i=1,iemax
 395  write(2,*) (dfeld(i,isp),isp=1,ispe)
      goto 600
c---------------------------- conversation of GNUPLOT-data to DISLIN-data
 400  do 410 i=1,nn
      read(1,*) xx(i),yy(i),isoa
      if(xx(i).eq.-1..and.yy(i).eq.-1..and.isoa.eq.-1.) goto 420
      iso=isoa
      if(xx(i).eq.-2..and.yy(i).eq.-2..and.iso.eq.-2.) goto 380
 410  continue
 420  ie=i-1
      call FELD(isp,ispe,ie,iemax,iso)
      goto 400
c------------------------------------------- profile data
 550  read(1,*) ik,jk
      write(2,*) epar,'at position i,j: ',ik,jk
      if(ik.ge.1.and.ik.le.ixmax.and.jk.eq.-1) goto 580
      if(jk.ge.1.and.jk.le.iymax.and.ik.eq.-1) goto 560
      stop 'input failure'
 560  write(2,*) 'i,x(i),z(i,',jk,'),y[jk]=',y(jk)
      write(2,*) ' '
      i1=0
      i2=0
      integz=0.
      do 570 i=1,ixmax-1
      write(2,*) i,x(i),z(i,jk)
      if(abs(z(i,jk)).gt.0..and.i1.eq.0) i1=i-1
      if(abs(z(i,jk)).gt.0..and.i1.gt.0) i2=i+1
      integ0=z(i,jk)
      integ1=z(i+1,jk)
 570  integz=integz+0.5*(integ0+integ1)
      integz=integz/float(i2-i1+1)
      write(2,*) ixmax,x(ixmax),z(ixmax,jk)
      write(2,*) ' '
      write(2,*) 'range of integration, mean value ',
     C epar,'position j ',jk
      write(2,*) i1,i2,integz
      goto 600
 580  write(2,*) 'j,y(j),z(',ik,',j),x[ik]=',x(ik)
      write(2,*) ' '
      i1=0
      i2=0
      integz=0.
      do 590 j=1,iymax-1
      write(2,*) j,y(j),z(ik,j)
      if(abs(z(ik,j)).gt.0..and.i1.eq.0) i1=j-1
      if(abs(z(ik,j)).gt.0..and.i1.gt.0) i2=j+1
      integ0=z(ik,j)
      integ1=z(ik,j+1)
 590  integz=integz+0.5*(integ0+integ1)
      integz=integz/float(i2-i1+1)
      write(2,*) iymax,y(iymax),z(ik,iymax)
      write(2,*) ' '
      write(2,*) 'range of integration, mean value ',
     C epar,', position i ',ik
      write(2,*) i1,i2,integz
 600  stop 'ok'
      end
c*********************************************************************
c
      real function INTERPOL(x,YY,XX,ie,ia,is,iflag)
c
c---- linear interpolation of the function YY(XX) at position x
c     boundary interpolation allowed, extrapolation not allowed
c
c---- lineare Interpolation der Funktion YY(XX) an der Stelle x
c     Randinterpolation zugelassen, Extrapolation nicht
c
      dimension XX(ie),YY(ie)
c
      do 10 i=ia,ie
      is=i
      if(XX(i).eq.XX(i-1)) goto 10
      if(x.le.XX(i-1).and.x.ge.XX(i)) goto 20
      if(x.ge.XX(i-1).and.x.le.XX(i)) goto 20
  10  continue
      iflag=1
      INTERPOL=0.
      return
  20  iflag=0
      INTERPOL=YY(i)+(YY(i)-YY(i-1))/(XX(i)-XX(i-1))*(x-XX(i))
c----------- checkup print
c      write(2,*) 'INTERPOL ',x,INTERPOL
      return
      end
c*********************************************************************
c
      subroutine ORDNE(X1,Y1,ie1,X2,Y2,ie2)
c
c---- closed isolines put in order
c---- Ordnen von geschlossenen Isolinien
c
      dimension X1(ie1),Y1(ie1),X2(ie2),Y2(ie2)
      common/ii/i1,i2
c
      i1=1
      iflag=1
      do 30 i=1,ie1
      if(i.ge.2.and.X1(i).eq.X1(i-1).and.
     C iflag.eq.1) goto 10
      goto 30
  10  i1=i-1
      iflag=2
      if(i.ge.3.and.X1(i).eq.X1(i-1).
     C and.X1(i).eq.X1(i-2).and.iflag.eq.2) goto 20
      goto 30
  20  iflag=3
  30  continue
      i2=1
      iflag=1
      do 60 i=1,ie1
      j=ie1+1-i
      if(j.le.ie1-1.and.X1(j).eq.X1(j+1).
     C and.iflag.eq.1) goto 40
      goto 60
  40  i2=j+1
      iflag=2
      if(j.le.ie1-2.and.X1(j).eq.X1(j+1).
     C and.X1(j).eq.X1(j+2).and.iflag.eq.2) goto 50
      goto 60
  50  iflag=3
  60  continue
      goto (70,90,150), iflag
c------------------------------- simplex
  70  do 80 i=1,ie1
      X2(i)=X1(i)
  80  Y2(i)=Y1(i)
      ie2=ie1
      return
c------------------------------- twofold
  90  do 100 i=1,i1-1
      X2(i)=X1(i)
 100  Y2(i)=Y1(i)
      ij=i-1
      do 110 i=i1,i2-1,2
      ij=ij+1
      X2(ij)=X1(i)
 110  Y2(ij)=Y1(i)
      do 120 i=i1,i2-1,2
      j=i1+i2-i
      ij=ij+1
      X2(ij)=X1(j)
 120  Y2(ij)=Y1(j)
      do 130 i=i1,i2-1,2
      ij=ij+1
      X2(ij)=X1(i)
 130  Y2(ij)=Y1(i)
      do 140 i=i2+1,ie1
      ij=ij+1
      X2(ij)=X1(i)
 140  Y2(ij)=Y1(i)
      ie2=ij
      return
c------------------------------- triple
 150  do 160 i=1,i1-1
      X2(i)=X1(i)
 160  Y2(i)=Y1(i)    
      ij=i-1
      do 170 i=i1,i2-1,3
      ij=ij+1
      X2(ij)=X1(i)
 170  Y2(ij)=Y1(i)
      do 180 i=i1,i2-1,3
      j=i1+i2-i
      ij=ij+1
      X2(ij)=X1(j)
 180  Y2(ij)=Y1(j)
      do 190 i=i1,i2-1,3
      ij=ij+1
      X2(ij)=X1(i+1)
 190  Y2(ij)=Y1(i+1)
      do 200 i=i2+1,ie1
      ij=ij+1
      X2(ij)=X1(i)
 200  Y2(ij)=Y1(i)
      ie2=ij
      return
      end
c*********************************************************************
c
      subroutine FELD(isp,ispe,ie,iemax,iso)
c
      real iso
      common dfeld(2000,2000),xx(4000),yy(4000)
c
      isp=isp+2
      ispe=isp+1
      dfeld(isp,1)=ie
      dfeld(isp+1,1)=ie
      dfeld(isp,2)=iso
      dfeld(isp+1,2)=iso
      if(iemax.lt.ie) iemax=ie
      do 10 i=1,ie
      dfeld(i,isp)=xx(i)
  10  dfeld(i,isp+1)=yy(i)
      return
      end
c*********************************************************************
