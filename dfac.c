#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cdbs.h"

FILE *infile;
FILE *callhistfile;
static char callhistory[256];


void get_callsigns(int facid)
{
   callsign_hist ch;
   char buff[BUFF_SIZE];
   char prev[64];

   if(!(callhistfile = fopen("call_sign_history.dat", "r")))
      perror("call_sign_history.dat"), exit(1);

   bzero(callhistory, sizeof(callhistory));
   bzero(prev, sizeof(prev));

   /* run through call history file looking for entries that match our facility id */
   while(fgets(buff, BUFF_SIZE, callhistfile)) {
      parse_callhist(buff, &ch);
      if(ch.fac_id == facid) {
         char *call = ch.callsign;
         /* if callsign starts with D (deleted), remove the D */
         if(call[0] == 'D') call++;
         /* if we found a callsign previously and it's different from new one, save it */
         if(strlen(prev) && strcmp(prev, ch.callsign)) {
            if(strlen(callhistory))
               strcat(callhistory, ", ");
            strcat(callhistory, prev);
          }
          /* callsign from current entry becomes previous call sign next time around */
          if(strlen(call) < 5)  /* filter out temporary callsigns */
             strcpy(prev, call);
          // else strcpy(prev, ""); /* don't save previous call sign again next time around */
      }
   }
   /* no more call signs found, don't save the last one we 
      found because it's the same as the current facility callsign */

   fclose(callhistfile);
}


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
         *strchr(buffer,'\n') = 0;
         *strrchr(buffer,'|') = 0;
         *strrchr(buffer,'^') = 0;
         get_callsigns(fac.facility_id);
         printf("%s%s\n",buffer, callhistory); 
      }
          
   }
   fclose(infile);
   return 0;
}

