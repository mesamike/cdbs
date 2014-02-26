#ifndef DIST_H
#define DIST_H

#define RADIANS_PER_DEGREE 0.017453293
#define DEGREES_PER_RADIAN 57.295780
#define EARTH_RADIUS       3956

typedef struct {
   float distance;
   float bearing;
} polar_coords;

typedef struct {
   double lat;
   double lon;
} spherical_coords;

polar_coords get_geodelta(spherical_coords from, spherical_coords to);

#endif
