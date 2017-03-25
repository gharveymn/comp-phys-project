c     marker.f 
c*******************************************************************
c     Program for data output with marking the vortex areas        *
c     -1. -1. -1. labelled the input end                           *
c------------------------------------------------------------------*
c     Programm zur Datenausgabe mit Markierung der Wirbelbereiche  *
c     -1. -1. -1. kennzeichnet das Eingabeende                     *
c*******************************************************************
      program Marker
c
      parameter (n=20000)      
      dimension a(n),b(n),c(n),mark(n) 
      open (unit=1,file='ein')
      open (unit=2,file='aus')
c
      do 10 i=1,n      
      read(1,*) a(i),b(i),c(i) 
      if(a(i).eq.-1..and.b(i).eq.-1..and.c(i).eq.-1.) goto 20
   10 continue
   20 in=i
      seg=a(in-1)
      do 30 i=1,in
   30 mark(i)=0
      do 50 i=3,in
      if(a(i).eq.seg) mark(i+1)=1
      if(a(i).eq.a(i-1).and.a(i).eq.a(i-2)) goto 40
      goto 50
   40 mark(i)  =2
      mark(i-1)=2
      mark(i-2)=2	
   50 continue
      do 60 i=1,in
      if(mark(i).eq.2.and.mark(i-1).eq.0) mark(i)=3
      if(mark(i).eq.0.and.mark(i-1).eq.2) mark(i)=3
   60 continue

      do 70 i=1,in
      if(mark(i).eq.1.or.mark(i).eq.3) write(2,*) '     '
      write(2,*) a(i),b(i),c(i)  
   70 continue
      stop 'ok'
      end
c*********************************************************************




















