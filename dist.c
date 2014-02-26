#include <math.h>
#include "dist.h"

polar_coords get_geodelta(spherical_coords from, spherical_coords to)
{
   polar_coords result;
   spherical_coords delta;
   double a;
   double PI = 4 * atan2(1,1);
                                                                                                
   from.lat *= RADIANS_PER_DEGREE;
   from.lon *= RADIANS_PER_DEGREE;
   to.lat *= RADIANS_PER_DEGREE;
   to.lon *= RADIANS_PER_DEGREE;
                                                                                                
   delta.lat = (to.lat - from.lat);
   delta.lon = (to.lon - from.lon);
   a = pow(sin(delta.lat/2), 2)
            + cos(from.lat)*cos(to.lat)*pow(sin(delta.lon/2), 2);
   result.distance = 2 * atan2(sqrt(a), sqrt(1-a));
   result.bearing =
         acos((sin(to.lat)-sin(from.lat)*cos(result.distance))/(sin(result.distance)*cos(from.lat)));
   if(sin(delta.lon) < 0)
      result.bearing = 2*PI - result.bearing;
                                                                                                
   result.distance *= EARTH_RADIUS;
   result.bearing *= DEGREES_PER_RADIAN;
                                                                                                
   return result;
}

