#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cdbs.h"

FILE *facfile;
char buffer[BUFF_SIZE];	

int main ()
{
   long idx;
   facility fac;
   facfile = fopen("fac.dat", "r");
   idx = ftell(facfile);
   while (fgets(buffer, BUFF_SIZE, facfile)) {
      parse_facility(buffer, &fac);
      printf("%d|%ld|\n", fac.facility_id, idx);
      idx = ftell(facfile);
   }
   fclose(facfile);
   return 0;
}

