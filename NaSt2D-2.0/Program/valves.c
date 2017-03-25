//*****************************************************************valves.c
//* FLAG -Belegung fuer mehrere Ventile: gehoert zu flag.c        */

int ivent=0;

/*ventilL*/
  REAL hub,fak;                                  /* ventilL Hub, Neigungsfaktor  */
  REAL sbxr,sbxl,sbyo,sbyu,sbyuu,sbr;            /* ventilL Stabilisierungsblech */
  REAL sbyo1,sbyu1,sbyo2,sbyu2,sbyo3,sbyu3,sbyo4,sbyu4,sbyo5,sbyu5; /* ventilL Stabilisierungsblech */
  REAL sbxa,sbya,sbdy,sbza,sbzb;                 /* ventilL Stabilisierungsblech sin-Kurve */

  if( strcmp(problem,"ventilD") == 0 ) ivent=1; 
  if( strcmp(problem,"ventilE") == 0 ) ivent=2; 
  if( strcmp(problem,"ventilK") == 0 ) ivent=3; 
  if( strcmp(problem,"ventilL") == 0 ) ivent=4; 
  if( strcmp(problem,"ventilP") == 0 ) ivent=5; 
  if( strcmp(problem,"ventilR") == 0 ) ivent=6; 

  if(ivent > 0)
  {
  if( strcmp(flagfile, "kein") == 0) {
  switch(ivent)
   {
  case 1:                                        /* Durchgangs-Ventil */
    hub = 1.8217;                                /* Hub: 0. bis 1.8217 */
	 printf("FLAG-Belegung analytisch\n");   /* Analytisches Setzen der FLAG-Belegung   */
      for (i=1; i<=imax; i++){
        for (j=1; j<=jmax; j++){
	 x = (i-0.5)*delx+delxw;
	 y = (j-0.5)*dely+delyw;
	   if   (x >= 0.     && x <= 1.9260 && y >= -0.04081*x+5.)            FLAG[i][j] = C_B; /* oben */
	   if (((x >= 1.9260 && x <= 3.1441 && y >= -0.96412*x+6.77830)      || 
                (x >= 3.1441 && x <= 3.3801 && y >= -0.50975*x+5.34969)      || 
                (x >= 3.3801 && x <= 4.     && y >= 3.6267))                 && 
               ((x >= 3.4991 && x <= 4.     && y <= 4.3149)                  ||  
                (x >= 2.5170 && x <= 3.4991 && y <= -0.85857*x+7.31912)      ||
                (x >= 1.9260 && x <= 2.5170 && y <= 5.3281)))                 FLAG[i][j] = C_B; 
	   if (x >= 1.9260 && x <= 2.5170 && y >= 5.3281)                     FLAG[i][j] = C_B; 
	   if (x >= 2.5170 && x <= 3.4354 && y >= 1.14514*x+2.44577)          FLAG[i][j] = C_B; 
	   if (y >= 6.3798 && y <= 8.3470 && x <= 3.4354)                     FLAG[i][j] = C_B; 
	   if (x >= 3.4354 && x <= 3.7351 && y >= 8.3470)                     FLAG[i][j] = C_B; 
	   if (x >= 3.7351 && x <= 4.1284 && y >= -1.08594*x+12.40310)        FLAG[i][j] = C_B; 
	   if (x >= 4.1284 && x <= 5.8716 && y >= 7.9199)                     FLAG[i][j] = C_B; 
	   if (x >= 5.8716 && x <= 6.2649 && y >= 1.08594*x+1.54370)          FLAG[i][j] = C_B; 
	   if (x >= 6.2649 && x <= 6.5646 && y >= 8.3470)                     FLAG[i][j] = C_B; 
	   if (y >= 6.5843 && y <= 8.3470 && x >= 6.5843)                     FLAG[i][j] = C_B; 
	   if (x >= 6.5646 && x <= 8.0995 && y >= -1.03010*x+13.34649)        FLAG[i][j] = C_B; 
	   if (x >= 8.0995 && x <= 10.    && y >= -0.00168*x+5.01684)         FLAG[i][j] = C_B; 
	   if (x >= 0.     && x <= 1.3372 && y <= -0.07665*x+3.)              FLAG[i][j] = C_B; /* unten */
	   if (x >= 1.3372 && x <= 1.8474 && y <= -0.47648*x+3.53465)         FLAG[i][j] = C_B; 
	   if (x >= 1.8474 && x <= 2.5935 && y <= -1.03217*x+4.56123)         FLAG[i][j] = C_B; 
	   if (x >= 2.5935 && x <= 3.4991 && y <= -0.71742*x+3.74494)         FLAG[i][j] = C_B; 
	   if (x >= 3.4991 && x <= 4.6386 && y <= -0.17745*x+1.85550)         FLAG[i][j] = C_B; 
	   if (x >= 4.6386 && x <= 6.0140 && y <= 0.08856*x+0.62162)          FLAG[i][j] = C_B; 
	   if (x >= 6.0140 && x <= 6.4000 && y <= 0.37772*x-1.11741)          FLAG[i][j] = C_B; 
	   if (x >= 6.4000 && x <= 6.8006 && y <= 0.84598*x-4.11428)          FLAG[i][j] = C_B; 
	   if (x >= 6.8006 && x <= 7.0770 && y <= 1.03582*x-5.40528)          FLAG[i][j] = C_B; 
	   if (y >= 1.9252 && y <= 2.2886 && x >= 7.0770)                     FLAG[i][j] = C_B; 
           if (((x >= 7.0770 && x <= 7.3129 && y >= 0.)                      ||
                (x >= 6.2500 && x <= 7.0770 && y >= -1.56856*x+13.38931)     ||
                (x >= 6.     && x <= 6.2500 && y >= -0.16360*x+4.60830))     &&
	       ((x >= 6.     && x <= 6.4477 && y <= 4.3149)                  ||
                (x >= 6.4477 && x <= 7.3129 && y <= -1.49919*x+13.98123)))    FLAG[i][j] = C_B; 
           if (x >= 7.3129 && x <= 7.6276 && y <= -0.51223*x+6.76371)         FLAG[i][j] = C_B; 
           if (x >= 7.6276 && x <= 10.    && y <= 0.06045*x+2.39555)          FLAG[i][j] = C_B; 
           if  ((x >= 3.6161 && x <= 6.3839 && y >= hub+4.3149) &&
               ((x >= 3.6161 && x <= 3.6969 && y <= hub+7.50621*x-22.82829)  ||
                (x >= 3.6969 && x <= 4.2071 && y <= hub+0.16033*x+4.32868)   ||
                (x >= 4.2071 && x <= 4.6000 && y <= hub+1.03512*x+1.33664)   ||
                (x >= 4.6000 && x <= 5.4000 && y <= hub+6.0982)              ||
                (x >= 5.4000 && x <= 5.7929 && y <= hub-1.03512*x+11.68786)  ||
                (x >= 5.7929 && x <= 6.3035 && y <= hub-0.16020*x+5.93124)   ||
                (x >= 6.3035 && x <= 6.3839 && y <= hub-7.54353*x+52.47208))) FLAG[i][j] = C_B; /* Teller */
                	       }
                             }
    break;
  case 2:                                        /* Eck-Ventil */
    hub = 1.8330;                                /* Hub: 0. bis 1.8330 */
	 printf("FLAG-Belegung analytisch\n");   /* Analytisches Setzen der FLAG-Belegung   */
      for (i=1; i<=imax; i++){
        for (j=1; j<=jmax; j++){
	 x = (i-0.5)*delx+delxw;
	 y = (j-0.5)*dely+delyw;
           if   (x <= 1.5426 || y >= 9.0041)                                 FLAG[i][j] = C_B; /* links u. oben */
           if  ((x >= 1.8889 && x <= 2.4241 && y >= -1.50206*x+11.84133)    ||
                (x >= 2.4241 && x <= 3.8759 && y >= 8.2002)                 ||
                (x >= 3.8759 && x <= 4.4111 && y >= 1.50206*x+2.37838))      FLAG[i][j] = C_B; /* oben Mitte */
           if  ((y <= 9.0041 && y >= 7.1712 && x >= 4.7300)                 ||
                (x <= 4.9426 && x >= 4.7300 && y >= -1.66416*x+15.04267)    ||
                (x <= 5.2889 && x >= 4.9426 && y >= -0.62778*x+9.92026)     ||
                (x <= 8.5000 && x >= 5.2889 && y >= 6.6000))                 FLAG[i][j] = C_B; /* oben rechts */
           if  ((x <= 8.5000 && x >= 4.9426 && y <= 4.6000)                 ||
                (x <= 4.9426 && x >= 4.8167 && y <= -1.26529*x+10.85384)    ||
                (x <= 4.8167 && x >= 4.1900 && y <= 4.7593))                 FLAG[i][j] = C_B; /* unten rechts */
           if  ((y <= 4.7593 && y >= 0.     && x <= 2.1100)                 ||
                (x <= 1.6370 && x >= 1.5426 && y <= -1.02225*x+6.43272))     FLAG[i][j] = C_B; /* unten links */
           if (((x >= 1.7037 && x <= 1.8611 && y <= hub+1.02096*x+3.53448)  ||
                (x >= 1.8611 && x <= 2.3019 && y <= hub+5.4346)             ||
                (x >= 2.3019 && x <= 2.8370 && y <= hub+0.54083*x+4.83285)  ||
                (x >= 2.8370 && x <= 3.4630 && y <= hub+6.3672)             ||
                (x >= 3.4630 && x <= 3.9981 && y <= hub-0.54083*x+8.24011)  ||
                (x >= 3.9981 && x <= 4.4389 && y <= hub+5.4346)             ||
                (x >= 4.4389 && x <= 4.6000 && y <= hub-0.99752*x+9.86248)) &&
                (x >= 1.7037 && x <= 4.6000 && y >= hub+4.7593))             FLAG[i][j] = C_B; /* Teller */
                	       }
                             }
    break;
  case 3:                                        /* Koswa-Ventil */
    hub = 1.7660;                                /* Hub: 0. bis 1.7660 */
    fak = hub*0.5*sqrt(2.);                      /* sin/cos 45° */
	 printf("FLAG-Belegung analytisch\n");   /* Analytisches Setzen der FLAG-Belegung   */
      for (i=1; i<=imax; i++){
        for (j=1; j<=jmax; j++){
	 x = (i-0.5)*delx+delxw;
	 y = (j-0.5)*dely+delyw;
	   if   (x >= 0.     && x <=  1.6971 && y >=  4.)                    FLAG[i][j] = C_B; /* oben */
           if   (x >= 1.6971 && x <=  1.9236 && y >=  0.22472*x+3.61862)     FLAG[i][j] = C_B;
           if   (y >= 4.0509 && y <=  4.9438 && x <=  1.00000*y-2.12730)     FLAG[i][j] = C_B;
           if   (y >= 4.9438 && y <=  5.2169 && x <= -0.99963*y+7.75849)     FLAG[i][j] = C_B;
           if   (y >= 5.2169 && y <=  5.2500 && x <= -4.66766*y+26.89419)    FLAG[i][j] = C_B;
           if   (y >= 5.2500 && y <=  5.4120 && x <=  2.3890)                FLAG[i][j] = C_B;
           if   (x >= 0.     && x <=  2.3890 && y >=  5.4120)                FLAG[i][j] = C_B;
           if   (x >= 2.3890 && x <=  2.4511 && y >=  1.56843*x+1.66502)     FLAG[i][j] = C_B;
           if   (x >= 2.4511 && x <=  5.0639 && y >=  0.99579*x+3.06862)     FLAG[i][j] = C_B;
           if   (x >= 5.0639 && x <=  5.2011 && y >= -0.30467*x+9.65401)     FLAG[i][j] = C_B;
           if   (x >= 5.2011 && x <=  7.0694 && y >= -1.00000*x+13.27050)    FLAG[i][j] = C_B;
           if (((x >= 4.9954 && x <=  5.2011 && y <=  2.69276*x-5.93589)    ||
                (x >= 5.2011 && x <=  7.0694 && y <= -1.00000*x+13.27050))  &&
               ((x >= 4.9954 && x <=  6.5155 && y >= -1.00007*x+12.51123)   ||
                (x >= 6.5155 && x <=  7.0694 && y >=  0.37155*x+3.57448)))   FLAG[i][j] = C_B;
           if   (x >= 6.5155 && x <=  7.2011 && y >= -1.00000*x+13.27050)    FLAG[i][j] = C_B;
           if   (x >= 7.2009 && x <= 10.2    && y >=  6.0696)                FLAG[i][j] = C_B;
           if   (y >= 5.7399 && y <=  6.0696 && x >=  0.99970*y+1.13314)     FLAG[i][j] = C_B;
           if   (y >= 5.3167 && y <=  5.7399 && x >=  0.33176*y+4.96704)     FLAG[i][j] = C_B;
           if   (y >= 5.0556 && y <=  5.3167 && x >=  0.11183*y+6.13632)     FLAG[i][j] = C_B;
           if   (y >= 4.6991 && y <=  5.0556 && x >= -0.34811*y+8.46158)     FLAG[i][j] = C_B;
           if   (y >= 4.3750 && y <=  4.6991 && x >= -0.76581*y+10.42443)    FLAG[i][j] = C_B;
           if   (y >= 4.1156 && y <=  4.3750 && x >= -1.31573*y+12.83031)    FLAG[i][j] = C_B;
           if   (y >= 4.0000 && y <=  4.1156 && x >= -3.48875*y+21.77361)    FLAG[i][j] = C_B;
           if   (x >= 7.8186 && x <= 10.2    && y >=  4.)                    FLAG[i][j] = C_B;
           if   (x >= 0.     && x <=  2.0649 && y <=  2.)                    FLAG[i][j] = C_B; /* unten */
           if   (x >= 2.0649 && x <=  2.4062 && y <=  0.21711*x+1.55169)     FLAG[i][j] = C_B;
           if   (x >= 2.4062 && x <=  2.9600 && y <=  1.02185*x-0.38467)     FLAG[i][j] = C_B; 
           if   (x >= 2.9600 && x <=  3.9591 && y <=  1.16965*x-0.82217)     FLAG[i][j] = C_B; 
           if   (x >= 3.9591 && x <=  4.3000 && y <= -1.05192*x+7.97326)     FLAG[i][j] = C_B; 
           if   (x >= 4.3000 && x <=  4.6600 && y <= -0.86389*x+7.16473)     FLAG[i][j] = C_B; 
           if   (x >= 4.6600 && x <=  5.0000 && y <= -0.36794*x+4.85360)     FLAG[i][j] = C_B; 
           if   (x >= 5.0000 && x <=  5.6778 && y <=  3.0139)                FLAG[i][j] = C_B; 
           if   (x >= 5.6778 && x <=  7.1671 && y <= -0.68079*x+6.87929)     FLAG[i][j] = C_B; 
           if   (x >= 7.1671 && x <= 10.2    && y <=  2.)                    FLAG[i][j] = C_B; 
           if (((x >= 2.5752+fak && x <= 4.1852+fak && y >= -0.99994*(x-fak)+7.76014+fak)   ||
                (x >= 4.1852+fak && x <= 4.4769+fak && y >=  1.17004*(x-fak)-1.32164+fak))  &&
               ((x >= 2.5752+fak && x <= 2.9165+fak && y <=  0.85497*(x-fak)+2.98339+fak)   ||
                (x >= 2.9165+fak && x <= 4.4769+fak && y <= -1.00000*(x-fak)+8.39340+fak)))  FLAG[i][j] = C_B; /* Teller */
           if (((x >= 3.2464+fak && x <= 3.7766+fak && y <=  0.99981*(x-fak)+1.90121+fak)   ||
                (x >= 3.7766+fak && x <= 4.6772+fak && y <= -0.99989*(x-fak)+9.45328+fak))  &&
               ((x >= 3.2464+fak && x <= 4.1470+fak && y >= -1.00000*(x-fak)+8.39340+fak)   ||
                (x >= 4.1470+fak && x <= 4.6772+fak && y >=  1.00000*(x-fak)+0.09940+fak)))  FLAG[i][j] = C_B; 
           if (((x >= 3.7766+fak && x <= 4.2687+fak && y <=  0.13798*(x-fak)+5.15601+fak)   ||
                (x >= 4.2687+fak && x <= 4.7450+fak && y <= -1.00000*(x-fak)+10.01370+fak)) &&
               ((x >= 4.6772+fak && x <= 4.7450+fak && y >=  7.25811*(x-fak)-29.17103+fak)  ||
                (x >= 3.7766+fak && x <= 4.6772+fak && y >= -0.99989*(x-fak)+9.45328+fak)))  FLAG[i][j] = C_B; 
                	       }
                             }
    break;
  case 4:                                        /* Leser - Ventil */
    hub   = 1.45385;                             /* Hub: 0. bis 2.89230, normal ist 1.45385 */
    sbxr  = 38.;                                 /* Stabilisierungsblech xr, 38. bis 45. */   
    sbxl  = 25.;                                 /* Stabilisierungsblech xl, normal ist 25. */    
    sbyo  = 28.7923089;                          /* Stabilisierungsblech yo, normal ist 28.7923089 */   
    sbyu  = 28.5923089;                          /* Stabilisierungsblech yu, normal ist 28.5923089 */   
    sbyuu = 27.;                                 /* Stabilisierungsblech yuu, kleiner yu */   
    sbr   = 0.5*(sbyu-sbyuu)+0.125*(sbxr-sbxl)*(sbxr-sbxl)/(sbyu-sbyuu); /* Stabilisierungsblech Radius */          
    sbyo1 = 24.1923089;                          /* Stabilisierungsblech fuenf Bleche */       
    sbyu1 = 23.9923089;                          /* Stabilisierungsblech fuenf Bleche */
    sbyo2 = 26.4923089;                          /* Stabilisierungsblech fuenf Bleche */
    sbyu2 = 26.2923089;                          /* Stabilisierungsblech fuenf Bleche */
    sbyo3 = 28.7923089;                          /* Stabilisierungsblech fuenf Bleche */
    sbyu3 = 28.5923089;                          /* Stabilisierungsblech fuenf Bleche */
    sbyo4 = 31.0923089;                          /* Stabilisierungsblech fuenf Bleche */
    sbyu4 = 30.8923089;                          /* Stabilisierungsblech fuenf Bleche */
    sbyo5 = 33.3923089;                          /* Stabilisierungsblech fuenf Bleche */ 
    sbyu5 = 33.1923089;                          /* Stabilisierungsblech fuenf Bleche */
    pi    = 2.*asin(1.0);                        /* Stabilisierungsblech sin-Kurve */
    sbxa  = 15.;                                 /* Stabilisierungsblech sin-Kurve */
    sbya  = 27.3;                                /* Stabilisierungsblech sin-Kurve */
    sbdy  = 0.2;                                 /* Stabilisierungsblech sin-Kurve */
    sbza  = 1.5;                                 /* Stabilisierungsblech sin-Kurve */
    sbzb  = 3.35;                                /* Stabilisierungsblech sin-Kurve */
	 printf("FLAG-Belegung analytisch\n");        /* Analytisches Setzen der FLAG-Belegung   */
      for (i=1; i<=imax; i++){
        for (j=1; j<=jmax; j++){
	 x = (i-0.5)*delx+delxw;
	 y = (j-0.5)*dely+delyw;
	   if (y >=  0.      && y <=  1.20769 && x <= 11.33077)     FLAG[i][j] = C_B; /* lo 1 */
	   if (x <= 11.33077 && y <=  1.20769+1.01613*(11.33077-x)) FLAG[i][j] = C_B; /* lo 2 */
	   if (y <= 23.14615 && x <= 10.85385)                      FLAG[i][j] = C_B; /* lo 3 */
	   if (x <= 11.33077 && y >= 19.04615-1.01613*(10.85385-x)
	                                      && y <= 23.14615)     FLAG[i][j] = C_B; /* lo 4 */
	   if (y >= 19.53077 && y <= 20.97692 && x <= 11.33077)     FLAG[i][j] = C_B; /* lo 5 */
	   if (x <= 11.57692 && y >= 20.97692 && y <= 23.14615)     FLAG[i][j] = C_B; /* lo 6 */
	   if (y >= 20.97692 && y <= 27.00769 && x <= 11.57692
	                                      && x >= 10.60769)     FLAG[i][j] = C_B; /* lo 7 */
	   if (x >= 11.09231 && x <= 11.57692 && y <= 27.48462+
	                 0.98413*(11.09231-x) && y >= 23.14615)     FLAG[i][j] = C_B; /* lo 8 */
	   if (x >= 10.85385 && x <= 11.09231 && y <= 27.48462
	                                      && y >= 23.14615)     FLAG[i][j] = C_B; /* lo 9 */
	   if (x >= 10.60769 && x <= 10.85385 && y <= 27.24615-
	                 0.96875*(10.60769-x) && y >= 23.14615)     FLAG[i][j] = C_B; /* lo 10 */
	   if (y >= 23.14615 && y <= 27.24615 && x >= 10.60769
	                                              && x <= 11.)  FLAG[i][j] = C_B; /* lo 11 */
	   if (x >=  8.73846 && x <= 10.60769 && y <= 23.14615)     FLAG[i][j] = C_B; /* lo 12 */
	   if (x >=  5.54615 && x <=  8.73846 && y <= 26.33846-
	            sqrt(3.19231*3.19231-(8.73846-x)*(8.73846-x)))  FLAG[i][j] = C_B; /* lo 13 */
	   if (x <=  5.54615)                                       FLAG[i][j] = C_B; /* lo 14 */
	   if (x >=  5.54615 && x <=  7.71538 && y >= 31.10769+
	                    sqrt(3.3*3.3-(8.84615-x)*(8.84615-x)))  FLAG[i][j] = C_B; /* lo 15 */
	   if (y >= 34.20791 && y <= 37.12692 && x <=  7.71538)     FLAG[i][j] = C_B; /* lo 16 */
	   if (x >=  7.71538 && x <=  9.14615 && y >= 37.12692)     FLAG[i][j] = C_B; /* lo 17 */
	   if (y >= 37.12692 && y <= 37.61154 && x <=  9.14615)     FLAG[i][j] = C_B; /* lo 18 */
	   if (y >= 37.61154)                                       FLAG[i][j] = C_B; /* lo 19 */
	   if (y >= 37.12692 && y <= 37.61154 && x >= 22.66154)     FLAG[i][j] = C_B; /* lo 20 */
	   if (x >= 22.66154 && x <= 24.10769 && y >= 37.12692)     FLAG[i][j] = C_B; /* lo 21 */
	   if (y >= 36.90000 && y <= 37.12692 && x >= 24.10769)     FLAG[i][j] = C_B; /* lo 22 */
	   if (x >= 24.10769 && x <= 25.56154 && y >= 36.90000-
	          sqrt(1.45385*1.45385-(25.56154-x)*(25.56154-x)))  FLAG[i][j] = C_B; /* lo 23 */
	   if (x >= 25.56154 && x <= 100.     && y >= 35.44616-
	                                     0.10000*(25.56154-x))  FLAG[i][j] = C_B; /* lo 24 */
	   if (x >= 32.79231 && x <= 100.     && y >= 36.16923)     FLAG[i][j] = C_B; /* lo 25 */

	   if (y >=  0.      && y <=  1.20769 && x >= 20.49231)     FLAG[i][j] = C_B; /* ru 1 */
	   if (x >= 20.49231 && y <=  1.20769-1.00000*(20.49231-x)
	                                      && x <= 25.)          FLAG[i][j] = C_B; /* ru 2 */
	   if (y <= 21.22308 && x >= 20.97692)                      FLAG[i][j] = C_B; /* ru 3 */
	   if (x >= 20.49231 && y >= 19.53077+1.00000*(20.49231-x)
	                                      && y <= 21.22308)     FLAG[i][j] = C_B; /* ru 4 */
	   if (y >= 19.53077 && y <= 20.97692 && x >= 20.49231)     FLAG[i][j] = C_B; /* ru 5 */
	   if (x >= 20.25385 && y >= 20.97692 && y <= 21.22308)     FLAG[i][j] = C_B; /* ru 6 */
	   if (y >= 20.97692 && y <= 27.00769 && x >= 20.25385
	                                      && x <= 21.21539)     FLAG[i][j] = C_B; /* ru 7 */
	   if (x >= 20.25385 && x <= 20.73846 && y <= 27.00769-
	                 0.98413*(20.25385-x) && y >= 23.14615)     FLAG[i][j] = C_B; /* ru 8 */
	   if (x >= 20.73846 && x <= 20.97692 && y <= 27.48462
	                                      && y >= 23.14615)     FLAG[i][j] = C_B; /* ru 9 */
	   if (x >= 20.97692 && x <= 21.21539 && y <= 27.48462+
	                 1.00000*(20.97692-x) && y >= 23.14615)     FLAG[i][j] = C_B; /* ru 10 */
	   if (y >= 23.14615 && y <= 27.24615 && x <= 21.21539
	                                      && x >= 20.5)         FLAG[i][j] = C_B; /* ru 11 */
	   if (x >= 21.21539 && x <= 21.75981 && y <= 23.14615)     FLAG[i][j] = C_B; /* ru 12 */
	   if (x >= 21.75981 && x <= 23.38461 && y <= 23.64615-
	                  sqrt(1.7*1.7-(23.38461-x)*(23.38461-x)))  FLAG[i][j] = C_B; /* ru 13 */
	   if (x >= 23.38461 && x <= 38.81538 && y <= 21.94615+
	                                     0.04686*(23.38461-x))  FLAG[i][j] = C_B; /* ru 14 */
	   if (x >= 20.97692 && x <= 100.     && y <= 21.22308)     FLAG[i][j] = C_B; /* ru 15 */

	   if (x >=  9.88461 && x <= 21.70000 &&
	             y >= (hub+27.48462) && y <= (hub+29.65384))    FLAG[i][j] = C_B; /* mi 1 */
	   if ((y >= (hub+26.27692) && y <= (hub+27.96154)) &&
	      ((x >= -(hub-y+18.07692) && x <= -(hub-y+17.60000)) ||
	      (x >= (hub-y+49.18461) && x <= (hub-y+49.66154))))    FLAG[i][j] = C_B; /* mi 23 */
// Erweiterung: Stabilisierungsblech (Kreisbogen oder Blech: eventl. ausblenden)
///*------------
//	   if (x >= sbxl     && x <= sbxr     && y <= sbyo
//              && y >= sbyuu+sbr-sqrt(sbr*sbr-(x-0.5*(sbxr+sbxl))*(x-0.5*(sbxr+sbxl))))
//	                                                            FLAG[i][j] = C_B; /* ru Erw */
//	                                      && y >= sbyu)         FLAG[i][j] = C_B; /* ru Erw */
//	   if (x >= sbxl     && x <= sbxr     && y <= sbyo1
//	                                      && y >= sbyu1)        FLAG[i][j] = C_B; /* ru Erw */
//	   if (x >= sbxl     && x <= sbxr     && y <= sbyo2
//	                                      && y >= sbyu2)        FLAG[i][j] = C_B; /* ru Erw */
//	   if (x >= sbxl     && x <= sbxr     && y <= sbyo3
//	                                      && y >= sbyu3)        FLAG[i][j] = C_B; /* ru Erw */
//	   if (x >= sbxl     && x <= sbxr     && y <= sbyo4
//	                                      && y >= sbyu4)        FLAG[i][j] = C_B; /* ru Erw */
//	   if (x >= sbxl     && x <= sbxr     && y <= sbyo5
//	                                      && y >= sbyu5)        FLAG[i][j] = C_B; /* ru Erw */
	   if (x >= sbxl     && x <= sbxr     && y <= sbya+sbdy+sbza*sin((x+pi-sbxa)/sbzb)
              && y >= sbya+sbza*sin((x+pi-sbxa)/sbzb))              FLAG[i][j] = C_B; /* ru Erw */
//------------*/
			       }
                             }
    break;
  case 5:                                        /* Patent - Freifluss - Ventil */
    hub = 0.1;                                   /* Hub: 0. bis 1.8330 */
    fak = hub*0.5*sqrt(2.);                      /* sin/cos 45° */
	 printf("FLAG-Belegung analytisch\n");   /* Analytisches Setzen der FLAG-Belegung   */
      for (i=1; i<=imax; i++){
        for (j=1; j<=jmax; j++){
	 x = (i-0.5)*delx+delxw;
	 y = (j-0.5)*dely+delyw;
	   if   (x >= 0.     && x <=  1.3058 && y >=  4.)                    FLAG[i][j] = C_B; /* oben */
           if   (y >= 4.0000 && y <=  4.0300 && x <=  6.66662*y-25.36069)    FLAG[i][j] = C_B;
           if   (y >= 4.0300 && y <=  4.3051 && x <=  1.45402*y-4.35389)     FLAG[i][j] = C_B;
           if   (y >= 4.3051 && y <=  4.4070 && x <=  1.89009*y-6.23122)     FLAG[i][j] = C_B;
           if   (y >= 4.4070 && y <=  4.7862 && x <= -1.00000*y+6.50540)     FLAG[i][j] = C_B;
           if   (y >= 4.7862 && y <=  5.1397 && x <= -0.20000*y+2.67644)     FLAG[i][j] = C_B;
           if   (y >= 5.1397 && y <=  8.1808 && x <=  0.95337*y-3.25155)     FLAG[i][j] = C_B;
           if   (y >= 8.1808)                                                FLAG[i][j] = C_B;
           if   (y >= 7.8308 && y <=  8.1808 && x >= -0.83371*y+11.36824)    FLAG[i][j] = C_B;
           if (((y >= 7.2198 && y <=  7.8308 && x >=  0.23421*y+3.00557)    ||
                (y >= 5.6865 && y <=  7.2198 && x >= -1.00000*y+11.91630))  &&
               ((y >= 5.6865 && y <=  5.8295 && x <=  4.27272*y-18.06703)   ||
                (y >= 5.8295 && y <=  7.8308 && x <= -0.99995*y+12.67001)))  FLAG[i][j] = C_B;
           if   (y >= 5.8295 && y <=  7.8308 && x >= -0.99995*y+12.67001)    FLAG[i][j] = C_B;
           if   (y >= 5.4697 && y <=  5.8295 && x >= -1.00028*y+12.67192)    FLAG[i][j] = C_B;
           if   (y >= 4.5736 && y <=  5.4697 && x >=  0.88796*y+2.34383)     FLAG[i][j] = C_B;
           if  ((x >= 6.4050 && x <= 10.5200 && y <=  4.5736)               &&
               ((x >= 6.4050 && x <=  7.0880 && y >= -0.99985*x+10.97766)   ||
                (x >= 7.0880 && x <=  7.1834 && y >=  3.8907)               ||
                (x >= 7.1834 && x <= 10.5200 && y >=  0.03276*x+3.65539)))   FLAG[i][j] = C_B;
           if   (x >= 0.     && x <=  2.0649 && y <=  2.)                    FLAG[i][j] = C_B; /* unten */
           if   (x >= 0.0000 && x <=  0.6039 && y <=  2.0000)                FLAG[i][j] = C_B;
           if   (x >= 0.6039 && x <=  3.0000 && y <=  0.23960*x+1.85531)     FLAG[i][j] = C_B; 
           if   (x >= 3.0000 && x <=  3.1784 && y <=  0.67264*x+0.55617)     FLAG[i][j] = C_B; 
           if   (x >= 3.1784 && x <=  3.4170 && y <=  1.65256*x-2.55839)     FLAG[i][j] = C_B; 
           if   (x >= 3.4170 && x <=  4.0262 && y <= -1.00000*x+6.50540)     FLAG[i][j] = C_B; 
           if   (x >= 4.0262 && x <=  6.2298 && y <= -0.03853*x+2.63432)     FLAG[i][j] = C_B; 
           if   (x >= 6.2298 && x <=  8.2323 && y <= -0.09963*x+3.01495)     FLAG[i][j] = C_B; 
           if   (x >= 8.2323 && x <= 10.5200 && y <= -0.08515*x+2.89579)     FLAG[i][j] = C_B; 
           if (((x >= 1.8385+fak && x <= 3.6770+fak && y >= -1.00000*(x-fak)+6.50540+fak)   ||
                (x >= 3.6770+fak && x <= 4.1012+fak && y >=  1.00024*(x-fak)-0.84947+fak))  &&
               ((x >= 1.8385+fak && x <= 2.2627+fak && y <=  1.00023*(x-fak)+2.82797+fak)   ||
                (x >= 2.2627+fak && x <= 4.1012+fak && y <= -1.00000*(x-fak)+7.35390+fak)))  FLAG[i][j] = C_B; /* Teller */
           if (((x >= 2.6587+fak && x <= 3.7052+fak && y >= -1.00000*(x-fak)+7.35390+fak)   ||
                (x >= 3.7052+fak && x <= 4.3800+fak && y >=  0.99985*(x-fak)-0.05595+fak)   ||
                (x >= 4.3800+fak && x <= 4.4275+fak && y >= 12.06745*(x-fak)-48.53204+fak)) &&
               ((x >= 2.6587+fak && x <= 3.3334+fak && y <=  1.00000*(x-fak)+2.03650+fak)   ||
                (x >= 3.3334+fak && x <= 3.9066+fak && y <=  0.08287*(x-fak)+5.09367+fak)   ||
                (x >= 3.9066+fak && x <= 4.4275+fak && y <= -0.99981*(x-fak)+9.32325+fak)))  FLAG[i][j] = C_B; 
                	       }
                             }
    break;
  case 6:                                        /* Rhei - Ventil */
    hub = 1.1837;                                   /* Hub: 0. bis 1.1837 */
	 printf("FLAG-Belegung analytisch\n");   /* Analytisches Setzen der FLAG-Belegung   */
      for (i=1; i<=imax; i++){
        for (j=1; j<=jmax; j++){
	 x = (i-0.5)*delx+delxw;
	 y = (j-0.5)*dely+delyw;
	   if   (x >= 0.     && x <=  0.8244 && y >=  0.08163*x+4.25000)         FLAG[i][j] = C_B; /* oben */
           if   (x >= 0.8244 && x <=  1.4323 && y >= -0.29610*x+4.56141)         FLAG[i][j] = C_B;
           if   (x >= 1.4323 && x <=  2.1732 && y >= -0.79876*x+5.28136)         FLAG[i][j] = C_B;
           if   (x >= 2.1732 && x <=  2.6507 && y >= -0.95393*x+5.61857)         FLAG[i][j] = C_B;
           if   (x >= 2.6507 && x <=  3.0864 && y >= -0.15898*x+3.51141)         FLAG[i][j] = C_B;
           if   (x >= 3.0864 && x <=  3.2168 && y >=  6.96396*x-16.94717)        FLAG[i][j] = C_B;
           if   (x >= 3.2168 && x <=  3.3900 && y >=  5.51154*x-12.27503)        FLAG[i][j] = C_B;
           if   (x >= 3.3900 && x <=  3.6942 && y >=  8.1220)                    FLAG[i][j] = C_B;
           if   (x >= 3.6942 && x <=  4.1717 && y >= -1.20544*x+12.57515)        FLAG[i][j] = C_B;
           if   (x >= 4.1717 && x <=  5.8283 && y >=  7.5464)                    FLAG[i][j] = C_B;
           if   (x >= 5.8283 && x <=  6.3058 && y >=  1.20544*x+0.52071)         FLAG[i][j] = C_B;
           if   (x >= 6.3058 && x <=  6.6100 && y >=  8.1220)                    FLAG[i][j] = C_B;
           if   (x >= 6.6100 && x <=  6.6945 && y >= -8.58463*x+63.78892)        FLAG[i][j] = C_B;
           if   (x >= 6.6945 && x <=  6.9554 && y >= -1.74588*x+18.00689)        FLAG[i][j] = C_B;
           if   (x >= 6.9554 && x <=  7.4772 && y >= -0.69509*x+10.69826)        FLAG[i][j] = C_B;
           if   (x >= 7.4772 && x <=  8.7816 && y >= -0.55826*x+9.67515)         FLAG[i][j] = C_B;
           if   (x >= 8.7816 && x <=  9.3478 && y >= -0.52932*x+9.42096)         FLAG[i][j] = C_B;
           if   (x >= 9.3478 && x <= 10.0000 && y >= -0.34192*x+7.66920)         FLAG[i][j] = C_B; 
           if   (x >= 0.0000 && x <=  0.3887 && y <= -0.17546*x+2.25000)         FLAG[i][j] = C_B; /* unten */
           if   (x >= 0.3887 && x <=  0.9549 && y <= -0.24073*x+2.27537)         FLAG[i][j] = C_B;
           if   (x >= 0.9549 && x <=  1.7819 && y <= -0.49468*x+2.51787)         FLAG[i][j] = C_B;
           if   (x >= 1.7819 && x <=  2.4341 && y <= -0.90754*x+3.25355)         FLAG[i][j] = C_B;
           if   (x >= 2.4341 && x <=  3.2168 && y <= -0.52255*x+2.31644)         FLAG[i][j] = C_B;
           if   (x >= 3.2168 && x <=  3.9995 && y <=  0.6355)                    FLAG[i][j] = C_B;
           if   (x >= 3.9995 && x <=  4.7822 && y <=  0.40756*x-0.99455)         FLAG[i][j] = C_B;
           if   (x >= 4.7822 && x <=  5.4344 && y <=  0.83640*x-3.04533)         FLAG[i][j] = C_B;
           if   (x >= 5.4344 && x <=  5.8283 && y <=  2.23864*x-10.66566)        FLAG[i][j] = C_B;
           if   (x >= 5.8283 && x <=  6.4336 && y <=  4.4536)                    FLAG[i][j] = C_B;
           if   (x >= 6.4336 && x <=  6.6084 && y <= -5.70996*x+41.18918)        FLAG[i][j] = C_B;
           if   (x >= 6.6084 && x <=  7.1302 && y <= -1.22307*x+11.53806)        FLAG[i][j] = C_B;
           if   (x >= 7.1302 && x <=  8.0851 && y <= -0.57126*x+6.89053)         FLAG[i][j] = C_B;
           if   (x >= 8.0851 && x <=  8.9564 && y <= -0.05004*x+2.67638)         FLAG[i][j] = C_B;
           if   (x >= 8.9564 && x <= 10.0000 && y <=  0.02089*x+2.04111)         FLAG[i][j] = C_B;
           if (((x >= 3.0864 && x <=  3.2168 && y >= -0.15898*x+3.51141)        || /* Mitte */
                (x >= 3.2168 && x <=  3.7386 && y >=  0.17248*x+2.44517)        ||
                (x >= 3.7386 && x <=  4.1299 && y >=  0.81549*x+0.04122)        ||
                (x >= 4.1299 && x <=  4.1717 && y >= 10.89473*x-41.58505))      &&
               ((x >= 3.0864 && x <=  3.2168 && y <= -2.09126*x+10.36266)       ||
                (x >= 3.2168 && x <=  3.4168 && y <=  3.6355)                   ||
                (x >= 3.4168 && x <=  3.5638 && y <=  0.92721*x+0.46741)        ||
                (x >= 3.5638 && x <=  4.1717 && y <=  4.4536)))                  FLAG[i][j] = C_B;
           if  ((x >= 3.6107 && x <=  6.3893 && y >= hub+4.5000)                &&
               ((x >= 3.6107 && x <=  3.6968 && y <= hub+1.58420*x-0.72097)     ||
                (x >= 3.6968 && x <=  4.3047 && y <= hub+0.07616*x+4.85394)     ||
                (x >= 4.3047 && x <=  4.6961 && y <= hub+0.80812*x+2.56767)     ||
                (x >= 4.6961 && x <=  5.3039 && y <= hub+6.3627)                ||
                (x >= 5.3039 && x <=  5.6953 && y <= hub+-0.80812*x+10.64891)   ||
                (x >= 5.6953 && x <=  6.3032 && y <= hub+-0.07616*x+5.61558)    ||
                (x >= 6.3032 && x <=  6.3893 && y <= hub+-1.58420*x+15.12103)))  FLAG[i][j] = C_B; /* Teller */
                	       }
                             }
    break;
  default:    return;
   }
  if(pflag == 1){                    /* Ausgabe der FLAG-Matrix zur Kontrolle und Aenderung   */
   fp = fopen(vecfile, "w");         /* ausdrucken mit : a2ps -1 -r -o file.ps -l750 ventil.out */
   for(j=1;j<=jmax;j+=1) {
    for(i=1;i<=imax;i+=1){
     itemp = FLAG[i][j];
     fprintf(fp,"%d ",itemp);
    }
     fprintf(fp,"\n");
    }
     fprintf(fp,"\n");
   fclose(fp);
   printf("Ausgabe der FLAG-Matrix zur Kontrolle und fuer das Einlesen von ventil.flag\n");
   exit(0);
                 }
                                   }
   else {                                     /* Einlesen der FLAG-Belegung von "ventil.flag" */
     fp = fopen(flagfile, "r");               /* unabhaengig von pflag, wenn file vorhanden   */
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

