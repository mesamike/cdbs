#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cdbs.h"

FILE *infile;

main ()
{
   char buffer[1024];	
   char buffer2[1024];	
   facility fac;

   infile = fopen("facility.dat", "r");
   while (fgets(buffer, 1024, infile)) {
      strcpy(buffer2, buffer);
      parse_facility(buffer2, &fac);

      if(
         !strcmp(fac.fac_service, "AM") && 
         !strcmp(fac.fac_country, "US") && 
              (!strcmp(fac.fac_status, "LICEN") || 
               !strcmp(fac.fac_status, "LICSL") || 
               !strcmp(fac.fac_status, "INTOP") || 
               !strcmp(fac.fac_status, "PTANF") || 
               !strcmp(fac.fac_status, "CPOFF")) &&
         (
            (fac.fac_callsign[0] == 'K') || 
            (fac.fac_callsign[0] == 'W') ||
            ((fac.fac_callsign[0] == 'D') && ((fac.fac_callsign[1] == 'K')||(fac.fac_callsign[1]='W'))) 
         )  

      ) {

#if 0
      if(!strcmp(fac.fac_service, "AM")&& (strlen(fac.fac_status) || strcmp(fac.fac_country, "US")) &&
	 ( (fac.fac_callsign[0] == 'K') ||
	   (fac.fac_callsign[0] == 'W') ||
	   (((fac.fac_callsign[0] == 'C') || (fac.fac_callsign[0] == 'V')) &&
	      !strcmp(fac.fac_country, "CA"))
	   )) {
#endif
         printf(" %s",buffer); 
      }
          
   }
   fclose(infile);
   return 0;
}

