#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cdbs.h"

FILE *authfile;
FILE *callhistfile;
static char callhistory[256];


void get_callsigns(int facid, char *call)
{
   callsign_hist ch;
   char buffer[BUFF_SIZE];
   char prev[13];

   if(!(callhistfile = fopen("call_sign_history.dat", "r")))
      perror("call_sign_history.dat"), exit(1);
   
   bzero(callhistory, sizeof(callhistory));
   bzero(prev, sizeof(prev));

   /* run through call history file looking for entries that match our facility id */
   while(fgets(buffer, BUFF_SIZE, callhistfile)) {
      parse_callhist(buffer, &ch); 
      if(ch.fac_id == facid) { 

      /* if we found a callsign previously, save it */
         if(strlen(prev)) {
            if(strlen(callhistory))
               strcat(callhistory, ", ");
            strcat(callhistory, prev); 
          }
          /* callsign from current entry becomes previous call sign next time around */
          if(strlen(ch.callsign) < 7)  /* filter out temporary callsings, accept deleted callsigns */
             strcpy(prev, ch.callsign);
          else strcpy(prev, ""); /* don't save previous call sign again next time around */
      }
   }
   /* no more call signs found, don't save the last one we 
      found because it's the same as the current facility callsign */
   
   fclose(callhistfile);
}

int print_line(power *pwr, authorization *auth, char *callhist)
{
         printf("%ld|%ld|%04d|%s|%s|%s|", 
            auth->app_id, auth->fac_id, (unsigned)auth->freq, auth->callsign, auth->state, auth->city);
         if(pwr->d) printf("%.0f", pwr->d);
         putchar('|');
         if(pwr->n) printf("%.0f", pwr->n);
         putchar('|');
         if(pwr->c) printf("%.0f", pwr->c);

         printf("|%.4f|%.4f|%s|", auth->lat, auth->lon, auth->status);
        
         if(callhist) 
            printf("%s", callhist);

         putchar('\n');
}       
       


int main ()
{
   authorization auth, auth2;
   unsigned long cur_app_id = 0;
   power pwr;
   float watts;
   char buffer[BUFF_SIZE];

   if(!(authfile = fopen("auths.dat", "r")))
      perror("auths.dat"), exit(1);

   printf("APP_ID|FAC_ID|FREQ|CALL|STATE|COL|PWR_D|PWR_N|PWR_C|LAT|LON|STATUS|CALL_HIST\n");

   while(fgets(buffer, BUFF_SIZE, authfile)) {
      memcpy(&auth2, &auth, sizeof(authorization));
      parse_authorization(buffer, &auth); 
      if(auth.app_id != cur_app_id) {
         if(cur_app_id) print_line(&pwr, &auth2, callhistory);
         cur_app_id = auth.app_id;
         bzero(&pwr, sizeof(power));
      }


      get_callsigns(auth.fac_id, auth.callsign);
      watts = auth.power*1000.0;
      switch(auth.hours_operation) {
         case 'U': pwr.d = pwr.n = watts; break;
         case 'D': pwr.d = watts; break;
         case 'N': pwr.n = watts; break;
         case 'R': 
         case 'C': pwr.c = watts; break;
      }
   }

    

   print_line(&pwr, &auth2, callhistory);
   fclose(authfile);
   return 0;
}

