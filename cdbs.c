#include <string.h>
#include <stdlib.h>
#include "cdbs.h"
#include <stdio.h>

void parse_callhist(char *buffer, callsign_hist *ch)
{
   char *p1=buffer, *p2;


   /* begin date */
   *(p2 = strchr(p1, '|')) = 0;
   strcpy (ch->begin_date, p1);
 
   /* callsign */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   strcpy (ch->callsign, p1);

   /* hist_id */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ch->hist_id = atoi(p1);

   /* seq_id */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ch->seq_id = atoi(p1);

   /* fac_id */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ch->fac_id = atoi(p1);

   /* change_date */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   strcpy(ch->change_date, p1);

}



void parse_application(char *buffer, application *ap)
{
   char *p1=buffer, *p2;

   *(p2 = strchr(p1, '|')) = 0;
   strcpy(ap->app_arn, p1);
   
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   strcpy(ap->app_service, p1);
   
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ap->app_id = atoi(p1);
   
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ap->fac_id = atoi(p1);
   
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   strcpy(ap->file_prefix, p1);
   
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   strcpy(ap->comm_city, p1);
   
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   strcpy(ap->comm_state, p1);
   
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ap->fac_freq = atof(p1);
   
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   if(strlen(p1))
      ap->channel = atoi(p1);
   else
      ap->channel = 0;
   
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   strcpy(ap->callsign, p1);
   
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   strcpy(ap->gen_app_svc, p1);
   
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   strcpy(ap->app_type, p1);
   
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ap->paper_filed_ind = *p1;
   
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   strcpy(ap->last_change_date, p1);

}
   
void parse_am_ant_sys(char *buffer, am_ant_sys *ant)
{	
   char *p1=buffer, *p2;
   *(p2 = strchr(p1, '|')) = 0;
   strcpy(ant->ant_mode, p1);
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->ant_sys_id = atoi(p1);
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->app_id = atoi(p1);
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->aug_cnt = atoi(p1);
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->bad_data_switch = *p1;
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->dom_pattern = *p1;
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->dummy_data_switch = *p1;
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->efficiency_restricted = atof(p1);
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->efficiency_theoretical = atof(p1);
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   strcpy(ant->feed_circ_other, p1);
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   strcpy(ant->feed_circ_type, p1);
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->hours_operation = *p1;
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->lat_deg =  atoi(p1);
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->lat_dir = *p1;
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->lat_min =  atoi(p1);
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->lat_sec =  atof(p1);
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->lon_deg =  atoi(p1);
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->lon_dir = *p1;
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->lon_min =  atoi(p1);
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->lon_sec =  atof(p1);
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->q_factor =  atof(p1);
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->q_factor_custom_ind = *p1;
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   if(strlen(p1)) 
      ant->power =  atof(p1);
   else
      ant->power = 0.0;

   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->rms_augmented =  atof(p1);
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->rms_standard =  atof(p1);
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->rms_theoretical =  atof(p1);
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->tower_cnt =  atoi(p1);
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->eng_rec_type = *p1;
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->biased_lat =  atof(p1);
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->biased_long =  atof(p1);
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   strcpy(ant->mainkey, p1);
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->am_dom_status = *p1;
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->lat_whole_secs =  atoi(p1);
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->lon_whole_secs =  atoi(p1);
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->ant_dir_ind = *p1;
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   ant->grandfathered_ind = *p1;
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   strcpy(ant->specified_hours_range, p1);
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   strcpy(ant->last_change_date, p1);
}

void parse_authorization(char *buffer, authorization *auth)
{

   /* fac_id */
   auth->fac_id = atol(strtok(buffer, "|"));

   /* app_id */
   auth->app_id = atol(strtok(0, "|"));

   /* freq */
   auth->freq = atof(strtok(0, "|")); 

   /* call sign */
   strcpy(auth->callsign, strtok(0, "|"));

   /* state */
   strcpy(auth->state, strtok(0, "|"));
 
   /* city */
   strcpy(auth->city, strtok(0, "|"));

   /* hours of operation */
   auth->hours_operation = strtok(0, "|")[0];

   /* power */
   auth->power = atof(strtok(0, "|"));

   /* latitude */
   auth->lat = atof(strtok(0, "|"));

   /* longitude */
   auth->lon = atof(strtok(0, "|"));

   /* status */
   strcpy(auth->status, strtok(0, "|"));
}

void parse_facility(char *buffer, facility *fac)
{
   char *p1=buffer, *p2;

   /* comm_city */
   *(p2 = strchr(p1, '|')) = 0;
   strcpy(fac->comm_city, p1);

   /* comm_state */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   strcpy(fac->comm_state, p1);
   
   /*eeo_rpt_ind */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   
   /*fac_address1 */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;

   /* fac_address2 */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   
   /* fac_callsign */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   strcpy(fac->fac_callsign, p1);

  /* fac_channel */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;

   /* fac_city */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   
   /*fac_country */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   strcpy(fac->fac_country, p1);

   /* fac_frequency */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   fac->fac_frequency = atoi(p1);

   /* fac_service */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   strcpy(fac->fac_service, p1);

   /* fac_state */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   
   /* fac_status_date */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;

   /* fac_type */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   strcpy(fac->fac_type, p1);

   /* facility_id */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   fac->facility_id = atoi(p1);

   /* lic_expiration_date */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;

   /* fac_status */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   strcpy(fac->fac_status, p1);

   /* fac_zip1 */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;

   /* fac_zip2 */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;

   /* station_type */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;

   /* assoc_facility_id */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;

   /* callsign_eff_date */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;

   /* unused1 */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;

   /* unused2 */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;

   /* last_change_date */
   p1 = p2+1;
   *(p2 = strchr(p1, '|')) = 0;
   strcpy(fac->last_change_date, p1);
}
   
   
