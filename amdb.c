#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cdbs.h"

FILE *authfile;

print_line(power *pwr, authorization *auth)
{
         printf("%ld|%ld|%04d|%s|%s|%s|", 
            auth->app_id, auth->fac_id, (unsigned)auth->freq, auth->callsign, auth->state, auth->city);
         if(pwr->d) printf("%.0f", pwr->d);
         putchar('|');
         if(pwr->n) printf("%.0f", pwr->n);
         putchar('|');
         if(pwr->c) printf("%.0f", pwr->c);

         printf("|%.4f|%.4f|%s|\n", auth->lat, auth->lon, auth->status);
}       
       


main ()
{
   authorization auth, auth2;
   unsigned long cur_app_id = 0;
   power pwr;
   float watts;
   char buffer[BUFF_SIZE];

   if(!(authfile = fopen("auths.dat", "r")))
      perror("auths.dat"), exit(1);

   while(fgets(buffer, BUFF_SIZE, authfile)) {
      memcpy(&auth2, &auth, sizeof(authorization));
      parse_authorization(buffer, &auth); 
      if(auth.app_id != cur_app_id) {
         if(cur_app_id) print_line(&pwr, &auth2);
         cur_app_id = auth.app_id;
         bzero(&pwr, sizeof(power));
      }


      watts = auth.power*1000.0;
      switch(auth.hours_operation) {
         case 'U': pwr.d = pwr.n = watts; break;
         case 'D': pwr.d = watts; break;
         case 'N': pwr.n = watts; break;
         case 'R': 
         case 'C': pwr.c = watts; break;
      }
   }
   print_line(&pwr, &auth2);
   fclose(authfile);
   return 0;
}

