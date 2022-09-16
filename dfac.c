#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cdbs.h"

FILE *infile;

int main ()
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
         (fac.fac_callsign[0] == 'D') 

      ) {

         printf(" %s",buffer); 
      }
          
   }
   fclose(infile);
   return 0;
}

