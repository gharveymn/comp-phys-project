C****************************************************************************
C     Program to delete of repeately occuring data points                   
C     -1. -1. -1. labelled the input end                                    
C---------------------------------------------------------------------------
C     Programm zum Loeschen mehrfach hintereinander liegender Datenpunkte   
C     -1. -1. -1. kennzeichnet das Eingabeende                              
C****************************************************************************
      program Delete
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
   20 in=i-1
      write(2,*) a(1),b(1),c(1)

      in=in+1
      do 30 i=2,in
   30 if(a(i).ne.a(i-1).or.b(i).ne.b(i-1)) write(2,*) a(i),b(i),c(i)
 
      stop 'ok'
      end
c*******************************************************************











