c*********************************************************
c     Program to search the neighbor points of isolines
c     -1. -1. -1. labelled the input end
c*--------------------------------------------------------
c     Programm zur Suche der Nachbarpunkte von Isolinien
c     -1. -1. -1. kennzeichnet das Eingabeende
c*********************************************************
      program Neighbor
c
      parameter (n=10000)
      dimension a(n),b(n),c(n),d(n),e(n)
      real min
      open (unit=1,file='ein')
      open (unit=2,file='aus')
c
      do 10 i=1,n
      read(1,*) a(i),b(i),c(i) 
      d(i)=0.
      e(i)=1000.
      if(a(i).eq.-1..and.b(i).eq.-1..and.c(i).eq.-1.) goto 20
   10 continue
   20 in=i-1
      write(2,*) a(1),b(1),c(1)

      iprint=1
      do 70 ii=1,in-1
      min=e(1)
      do 30 i=2,in
   30 e(i)=sqrt((a(i)-a(iprint))**2 + (b(i)-b(iprint))**2)
      do 40 i=2,in
   40 if(d(i).eq.0..and.e(i).lt.min) min=e(i)
      do 50 i=2,in
      if(d(i).eq.0..and.e(i).eq.min) goto 60
   50 continue
   60 write(2,*) a(i),b(i),c(i)
      iprint=i
      d(i)=1.
   70 continue
 
      stop 'ok'
      end
c**********************************************************











