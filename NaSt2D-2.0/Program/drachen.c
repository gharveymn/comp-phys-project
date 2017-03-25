//*****************************************************************drachen.c
//* FLAG -Belegung fuer die Drachenumstroemung: gehoert zu flag.c          */

  int idra=0;

  if( strcmp(problem,"drachen") == 0 ) idra=1; 

  if(idra > 0)
  {
  if( strcmp(flagfile, "kein") == 0) {
  switch(idra)
   {
  case 1:                                        /* Drachenumstroemung */
    printf("FLAG-Belegung analytisch\n");        /* Analytisches Setzen der FLAG-Belegung */
      for (i=1; i<=imax; i++){
        for (j=1; j<=jmax; j++){
	 x = (i-0.5)*delx+delxw;
	 y = (j-0.5)*dely+delyw;
	 if (x >=  0.58895*y -0.45018     && y >=  2.4674 && y <= 2.4837  && x <=  1.4652)    FLAG[i][j] = C_B; /*  1 */    
	 if (x >=  0.93363*y -1.30625     && y >=  2.4837 && y <= 2.5741  && x <=  1.4652)    FLAG[i][j] = C_B; /*  2 */    
	 if (x >=  1.01403*y -1.51323     && y >=  2.5741 && y <= 2.6881  && x <=  1.4652)    FLAG[i][j] = C_B; /*  3 */      
	 if (x >=  1.19874*y -2.00974     && y >=  2.6881 && y <= 2.7993  && x <=  1.4652)    FLAG[i][j] = C_B; /*  4 */      
         if (x >=  1.15938*y -1.89954     && y >=  2.7993 && y <= 2.9022  && x <=  1.4652)    FLAG[i][j] = C_B; /*  5 */      
	 if (x >=  1.46524*y -2.78722     && y >=  2.9022 && y <= 2.9200  && x <=  0.58605*y -0.14016)   FLAG[i][j] = C_B; /*  6 */    
	 if (x >=  1.46524*y -2.78722     && y >=  2.9200 && y <= 2.9578  && x <=  0.64815*y -0.32150)   FLAG[i][j] = C_B; /*  7 */    
	 if (x >=  1.46524*y -2.78722     && y >=  2.9578 && y <= 2.9770  && x <= -0.34896*y +2.62775)   FLAG[i][j] = C_B; /*  8 */    
	 if (x >=  1.4652 && y >=  2.8770 && y <=  2.9022 && x <=  0.58605*y -0.14016)        FLAG[i][j] = C_B; /*  9 */    
	 if (x >=  1.4652 && y >=  2.7881 && y <=  2.8770 && x <=  0.53318*y +0.01193)        FLAG[i][j] = C_B; /* 10 */    
	 if (x >=  1.4652 && y >=  2.6978 && y <=  2.7881 && x <=  0.19712*y +0.94891)        FLAG[i][j] = C_B; /* 11 */    
	 if (x >=  1.4652 && y >=  2.6370 && y <=  2.6978 && x <=  0.04770*y +1.35202)        FLAG[i][j] = C_B; /* 12 */    
	 if (x >=  1.4652 && y >=  2.6059 && y <=  2.6370 && x <= -0.76206*y +3.48734)        FLAG[i][j] = C_B; /* 13 */     
	 if (x >=  1.5681 && y >=  2.5630 && y <= -0.07625*x +2.72547     && x <= 1.6363)     FLAG[i][j] = C_B; /* 14 */    
	 if (x >=  1.6363 && y >=  2.5630 && y <= -3.92706*x +9.02655     && x <= 1.6459)     FLAG[i][j] = C_B; /* 15 */    
	 if (x >=  1.4919 && y >=  2.01041*x -0.49862     && y <= 2.5630  && x <= 1.5111)     FLAG[i][j] = C_B; /* 16 */    
	 if (x >=  1.5111 && y >=  0.26747*x +2.13512     && y <= 2.5630  && x <= 1.5526)     FLAG[i][j] = C_B; /* 17 */    
	 if (x >=  1.5526 && y >= -0.55975*x +3.41947     && y <= 2.5630  && x <= 1.5844)     FLAG[i][j] = C_B; /* 18 */    
	 if (x >=  1.5844 && y >= -0.86547*x +3.90386     && y <= 2.5630  && x <= 1.6067)     FLAG[i][j] = C_B; /* 19 */    
	 if (x >=  1.6067 && y >=  0.58007*x +1.58130     && y <= 2.5630  && x <= 1.6348)     FLAG[i][j] = C_B; /* 20 */
	 if (x >=  1.6348 && y >=  3.00900*x -2.38951     && y <= 2.5630  && x <= 1.6459)     FLAG[i][j] = C_B; /* 21 */    
	 if (x >=  1.4652 && y >=  2.5630 && y <=  2.6059 && x <= 1.5681)                     FLAG[i][j] = C_B; /* 22 */    
	 if (x >=  1.4652 && y >=  2.3993 && y <=  2.4244 && x <= 1.5844)                     FLAG[i][j] = C_B; /* 23 */
	 if (x >=  1.4652 && y >=  2.3704 && y <=  2.6059 && x <= 1.4919)                     FLAG[i][j] = C_B; /* 24 */
	 if (x >=  1.4919 && y >=  2.4244 && y <= -4.20798*x +8.77858     && x <=  1.5044)    FLAG[i][j] = C_B; /* 25 */    
	 if (x >=  1.5044 && y >=  2.4244 && y <= -0.06017*x +2.53862     && x <=  1.5526)    FLAG[i][j] = C_B; /* 26 */    
	 if (x >=  1.5526 && y >=  2.4244 && y <=  0.60135*x +1.51154     && x <=  1.5822)    FLAG[i][j] = C_B; /* 27 */    
	 if (x >=  1.5822 && y >=  2.4244 && y <=  0.33735*x +1.92925     && x <=  1.6237)    FLAG[i][j] = C_B; /* 28 */    
	 if (x >=  1.6237 && y >=  2.4244 && y <= -0.57658*x +3.41319     && x <=  1.6570)    FLAG[i][j] = C_B; /* 29 */ 
	 if (x >=  1.6570 && y >=  2.4244 && y <=-11.13320*x +20.9055     && x <=  1.6600)    FLAG[i][j] = C_B; /* 30 */  
	 if (x >=  1.5844 && y >= -0.05618*x +2.48831     && y <=  2.4244 && x <=  1.6378)    FLAG[i][j] = C_B; /* 31 */    
	 if (x >=  1.6378 && y >=  1.26577*x +0.32323     && y <=  2.4244 && x <=  1.6600)    FLAG[i][j] = C_B; /* 32 */   
	 if (x >=  1.4844 && y >=  2.3704 && y <=  2.3993 && x <=  0.71626*y -0.20893)        FLAG[i][j] = C_B; /* 33 */     
	 if (x >=  1.4844 && y >=  2.2881 && y <=  2.3704 && x <= -0.05346*y +1.61563)        FLAG[i][j] = C_B; /* 34 */ 
	 if (x >=  1.4844 && y >=  2.2185 && y <=  2.2881 && x <= -0.35201*y +2.29874)        FLAG[i][j] = C_B; /* 35 */    
	 if (x >=  1.4844 && y >=  2.1259 && y <=  2.2185 && x <= -0.42333*y +2.45695)        FLAG[i][j] = C_B; /* 36 */      
	 if (x >=  1.4844 && y >=  2.0911 && y <=  2.1259 && x <= -0.63419*y +2.90523)        FLAG[i][j] = C_B; /* 37 */    
	 if (x >= -1.48288*y +4.58525     && y >=  2.0756 && y <=  2.0911 && x <= -0.63419*y +2.90523)   FLAG[i][j] = C_B; /* 38 */      
	 if (x >= -1.48288*y +4.58525     && y >=  2.0452 && y <=  2.0756 && x <=  0.04934*y +1.48648)   FLAG[i][j] = C_B; /* 39 */   
	 if (x >= -1.48288*y +4.58525     && y >=  2.0356 && y <=  2.0452 && x <=  2.15621*y -2.82248)   FLAG[i][j] = C_B; /* 40 */      
	 if (x >= -1.50958*y +4.64109     && y >=  2.0911 && y <=  2.2059 && x <=  1.4844)    FLAG[i][j] = C_B; /* 41 */      
	 if (x >= -1.36226*y +4.31612     && y >=  2.2059 && y <=  2.3119 && x <=  1.4844)    FLAG[i][j] = C_B; /* 42 */      
	 if (x >= -1.18853*y +3.91447     && y >=  2.3119 && y <=  2.4148 && x <=  1.4844)    FLAG[i][j] = C_B; /* 43 */     
	 if (x >= -0.78707*y +2.94501     && y >=  2.4148 && y <=  2.4674 && x <=  1.4844)    FLAG[i][j] = C_B; /* 44 */      
			       }
                             }
    break;
  default:
    return;
   }
  if(pflag == 1){                 /* Ausgabe der FLAG-Matrix zur Kontrolle und Aenderung   */
   fp = fopen(vecfile, "w");      /* ausdrucken mit : a2ps -1 -r -o file.ps -l750 file.out */
   for(j=1;j<=jmax;j+=1) {
    for(i=1;i<=imax;i+=1){
     itemp = FLAG[i][j];
     fprintf(fp,"%d ",itemp);
    }
     fprintf(fp,"\n");
    }
     fprintf(fp,"\n");
   fclose(fp);
   printf("Ausgabe der FLAG-Matrix zur Kontrolle und fuer das Einlesen von drachen.flag\n");
   exit(0);
                 }
                                   }
   else {                                    /* Einlesen der FLAG-Belegung von "drachen.flag" */
     fp = fopen(flagfile, "r");              /* unabhaengig von pflag, wenn file vorhanden */
     printf("FLAG-Belegung einlesen\n");
     printf("jmax=%d " "imax=%d\n",jmax,imax);
     for (j=1; j<=jmax; j++){
       cst[0] = '\0';
       k = 0;
	for (i=1; cst[k] != '\n'; i++){
	    k = 0;
	    while (!isspace((cst[k] = getc(fp))))
	    k++;
	    cst[k+1] = '\0';
	    if (k!=0)
	      FLAG[i][j] = atoi(cst);
	    else
	    i--;
                                      }
                            }
     fclose(fp);
        }
  }
