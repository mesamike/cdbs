#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cdbs.h"

FILE *facfile;
FILE *appfile;
FILE *antfile;
FILE *appidxfile;
FILE *facidxfile;

int get_fac(unsigned long fac_id, facility *fac)
{
   char buffer[BUFF_SIZE];
   fseek(facidxfile, 0, SEEK_SET);
   while (fgets(buffer, BUFF_SIZE, facidxfile)) {
      long idx_fac_id = atol(strtok(buffer, "|"));
      long idx_offs =  atol(strtok(0,"|"));
      if(idx_fac_id == fac_id) {
         fseek(facfile, idx_offs, SEEK_SET);
         fgets(buffer, BUFF_SIZE, facfile);
         parse_facility(buffer, fac);
         return 1;
      }
   }
   return 0;
}

int get_app(unsigned long app_id, application *app)
{
   char buffer[BUFF_SIZE];
   fseek(appidxfile, 0, SEEK_SET);
   while (fgets(buffer, BUFF_SIZE, appidxfile)) {
      long idx_app_id = atol(strtok(buffer, "|"));
      long idx_offs =  atol(strtok(0,"|"));
      if(idx_app_id == app_id) {
         fseek(appfile, idx_offs, SEEK_SET);
         fgets(buffer, BUFF_SIZE, appfile);
         parse_application(buffer, app);
         return 1;
      }
   }
   return 0;
}

int main ()
{
   char buffer[BUFF_SIZE];	
   facility fac;
   application app;
   am_ant_sys ant;


   if(!(facfile = fopen("fac.dat", "r")))
      perror("fac.dat"), exit(1);
   if(!(appfile = fopen("appl.dat", "r")))
      perror("appl.dat"), exit(1);
   if(!(antfile = fopen("ant.dat", "r")))
      perror("ant.dat"), exit(1);
   if(!(appidxfile = fopen("appidx.dat", "r")))
      perror("appidx.dat"), exit(1);
   if(!(facidxfile = fopen("facidx.dat", "r")))
      perror("facidx.dat"), exit(1);

   while (fgets(buffer, BUFF_SIZE, antfile)) {
      parse_am_ant_sys(buffer, &ant);
      if(get_app(ant.app_id, &app)) {
         if(get_fac(app.fac_id, &fac)) {
            float lat = (ant.lat_dir == 'N'?1.0:-1.0) * (ant.lat_deg + ant.lat_min/60.0 + ant.lat_sec/3600);
            float lon = (ant.lon_dir == 'E'?1.0:-1.0) * (ant.lon_deg + ant.lon_min/60.0 + ant.lon_sec/3600);
            printf("%ld|%ld|%f|%s|%s|%s|%c|%f|%7.4f|%8.4f|%s|\n",
               app.app_id, app.fac_id, app.fac_freq, fac.fac_callsign, app.comm_state,
               app.comm_city, ant.hours_operation, ant.power, lat, lon, fac.fac_status);
         } /* else fprintf(stderr, "Cant find facility %lu\n", app.fac_id); */
      } /* else fprintf(stderr, "Can't find app_id %lu\n", ant.app_id); */  
   }
   fclose(antfile);
   fclose(appfile);
   fclose(facfile);
   fclose(appidxfile);
   fclose(facidxfile);
   return 0;
}

