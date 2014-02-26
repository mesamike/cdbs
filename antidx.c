#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cdbs.h"

FILE *antfile;
char buffer[BUFF_SIZE];	

main ()
{
   long idx;
   am_ant_sys ant;
   antfile = fopen("ant.dat", "r");
   idx = ftell(antfile);
   while (fgets(buffer, BUFF_SIZE, antfile)) {
      parse_am_ant_sys(buffer, &ant);
      printf("%lu|%ld|\n", ant.app_id, idx);
      idx = ftell(antfile);
   }
   fclose(antfile);
   return 0;
}

