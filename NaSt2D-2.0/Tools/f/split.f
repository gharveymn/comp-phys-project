c********************************************************************
c     Program for data splitting up in isplit sequences
c     -1. -1. -1. labelled the input end
c--------------------------------------------------------------------
c     Programm zur Datenaufspaltung in isplit Folgen
c     -1. -1. -1. kennzeichnet das Eingabeende
c********************************************************************
      program Split
c
c     isplit = number of splits [2,8]
c
      parameter (n=10000)      
      dimension a(n),b(n),c(n) 
      open (unit=1,file='ein')
      open (unit=2,file='aus')
c
      read(1,*) isplit
      if(isplit.gt.8) stop ' isplit>8 '
      do 10 i=1,n
      read(1,*) a(i),b(i),c(i) 
      if(a(i).eq.-1..and.b(i).eq.-1..and.c(i).eq.-1.) goto 20
   10 continue
   20 in=i-1
      i1=1
      do 30 i=i1,in,isplit
      write(2,*) a(i),b(i),c(i)
   30 continue
      call isp(i1,in,isplit,a,b,c,n)
      if(isplit.eq.2) goto 40
      call isp(i1,in,isplit,a,b,c,n)
      if(isplit.eq.3) goto 40
      call isp(i1,in,isplit,a,b,c,n)
      if(isplit.eq.4) goto 40
      call isp(i1,in,isplit,a,b,c,n)
      if(isplit.eq.5) goto 40
      call isp(i1,in,isplit,a,b,c,n)
      if(isplit.eq.6) goto 40
      call isp(i1,in,isplit,a,b,c,n)
      if(isplit.eq.7) goto 40
      call isp(i1,in,isplit,a,b,c,n)
   40 stop 'ok'
      end
c*********************************************************************
      subroutine isp(i1,in,isplit,a,b,c,n)
c
      dimension a(n),b(n),c(n) 
      write(2,*) ' '
      i1=i1+1
      do 10 i=i1,in,isplit
      write(2,*) a(i),b(i),c(i)
   10 continue
      return
      end
c*********************************************************************
















