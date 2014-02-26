#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cdbs.h"

FILE *antfile;
char buffer[1024];	
char buffer2[1024];	


main ()
{
   am_ant_sys ant;

   antfile = fopen("am_ant_sys.dat", "r");
   while (fgets(buffer, 1024, antfile)) {
      strcpy(buffer2, buffer);
      parse_am_ant_sys(buffer2, &ant);
      if((ant.hours_operation != 'X') 
         && (ant.eng_rec_type == 'C')
         && ((ant.am_dom_status == 'L') ||
             (ant.am_dom_status == 'C') ||
             (ant.am_dom_status == 'M') ||
             (ant.am_dom_status == 'S') 
            ))
            printf("%s", buffer);
      }
   fclose(antfile);
   return 0;
}

