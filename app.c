#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cdbs.h"

FILE *infile;

int main ()
{
   char buffer[1024];	
   char buffer2[1024];	
   application ap;

   infile = fopen("application.dat", "r");
   while (fgets(buffer, 1024, infile)) {
      strcpy(buffer2, buffer);
      parse_application(buffer2, &ap);
      if(!strcmp(ap.app_service, "AM")&& (ap.fac_freq>0) &&
	  ( !strncmp(ap.app_type, "ML", 2) 
	  || !strncmp(ap.app_type, "MML", 3) 
	  || !strncmp(ap.app_type, "STA", 3) 
          || !strncmp(ap.app_type, "L", 1) 
          || !strncmp(ap.app_type, "Z", 1) 
          || !strncmp(ap.app_type, "NP", 2) 
          || !strncmp(ap.app_type, "MP", 2)) 
      ) {
         printf(" %s",buffer); 
      }
          
   }
   fclose(infile);
   return 0;
}

   
