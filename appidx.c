#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cdbs.h"

FILE *appfile;
char buffer[BUFF_SIZE];	

main ()
{
   long idx;
   application ap;
   appfile = fopen("appl.dat", "r");
   idx = ftell(appfile);
   while (fgets(buffer, BUFF_SIZE, appfile)) {
      parse_application(buffer, &ap);
      printf("%ld|%ld|\n", ap.app_id, idx);
      idx = ftell(appfile);
   }
   fclose(appfile);
   return 0;
}

