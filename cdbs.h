#ifndef CDBS_H
#define CDBS_H

#include "dist.h"

#define BUFF_SIZE 1024

typedef struct {
   char begin_date[20];
   char callsign[13];
   unsigned long hist_id;
   unsigned short seq_id;
   unsigned long fac_id;
   char change_date[20];
} callsign_hist;

typedef struct {
   unsigned long app_id;
   unsigned long fac_id;
   float freq;
   char callsign[13];
   char state[3];
   char city[80];
   char hours_operation;
   float power;
   float lat;
   float lon;
   char status[6];
} authorization;    

typedef struct {
   char app_arn[15];
   char app_service[2];
   unsigned long app_id;
   unsigned long fac_id;
   char file_prefix[7];
   char comm_city[80];
   char comm_state[3];
   float fac_freq;
   unsigned int channel;
   char callsign[13];
   char gen_app_svc[3];
   char app_type[5];
   char paper_filed_ind;
   char last_change_date[11];
} application;

typedef struct {
   char ant_mode[3];
   unsigned long ant_sys_id;
   unsigned long app_id;
   unsigned short aug_cnt;
   char bad_data_switch;
   char dom_pattern;
   char dummy_data_switch;
   float efficiency_restricted;
   float efficiency_theoretical;
   char feed_circ_other[255];
   char feed_circ_type[3];
   char hours_operation;
   int lat_deg;
   char lat_dir;
   int lat_min;
   float lat_sec;
   int lon_deg;
   char lon_dir;
   int lon_min;
   float lon_sec;
   float q_factor;
   char q_factor_custom_ind;
   float power;
   float rms_augmented;
   float rms_standard;
   float rms_theoretical;
   unsigned int tower_cnt;
   char eng_rec_type;
   float biased_lat;
   float biased_long;
   char mainkey[17];
   char am_dom_status;
   int lat_whole_secs;
   int lon_whole_secs;
   char ant_dir_ind;
   char grandfathered_ind;
   char specified_hours_range[26];
   char last_change_date[11];
} am_ant_sys;

typedef struct power_t {
   int flag;
   char *city;
   char *state;
   char *ant_id;
   float c;
   float d;
   float n;
   float p;
   float r;
   float u;
   polar_coords geodelta;
   struct power_t *next;
} power;

typedef struct {
   char comm_city[21];
   char comm_state[3];
   char eeo_rpt_ind;
   char fac_address1[41];
   char fac_address2[41];
   char fac_callsign[13];
   int  fac_channel;
   char fac_city[21];
   char fac_country[3];
   int  fac_frequency;
   char fac_service[3];
   char fac_state[3];
   char fac_status_date[20];
   char fac_type[4];
   int  facility_id;
   char lic_expiration_date[20];
   char fac_status[6];
   char fac_zip1[6];
   char fac_zip2[5];
   char station_type;
   int  assoc_facility_id;
   char callsign_eff_date[20];
   char unused1[0];
   char unused2[0];
   char last_change_date[20];
   power pwr;
} facility;


void parse_application(char *, application *);
void parse_am_ant_sys(char *, am_ant_sys *);
void parse_facility(char *, facility *);
void parse_authorization(char *, authorization *);
void parse_callhist(char *, callsign_hist *);
#endif
