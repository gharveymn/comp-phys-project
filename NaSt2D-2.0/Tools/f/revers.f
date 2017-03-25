c********************************************************************
c     Program for data output in reverse order
c     -1. -1. -1. labelled the input end
c--------------------------------------------------------------------
c     Programm zur Datenausgabe in umgekehrter Folge
c     -1. -1. -1. kennzeichnet das Eingabeende
c********************************************************************
      program Revers
c
      parameter (n=10000)      
      dimension a(n),b(n),c(n) 
      open (unit=1,file='ein')
      open (unit=2,file='aus')
c
      do 10 i=1,n      
      read(1,*) a(i),b(i),c(i) 
      if(a(i).eq.-1..and.b(i).eq.-1..and.c(i).eq.-1.) goto 20
   10 continue
   20 in=i
      do 30 i=1,in
      j=in-i+1
      write(2,*) a(j),b(j),c(j)  
   30 continue
      stop 'ok'
      end
c*********************************************************************




















