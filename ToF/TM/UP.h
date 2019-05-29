#ifndef UP_H_INCLUDED
#define UP_H_INCLUDED

#include <time.h>

typedef struct __attribute__((__packed__)) {
  double Time;
  float Latitude;
  float Longitude;
  float GPS_MSL_Alt;
  float WGS_84_Alt;
  float Press_Alt;
  float Radar_Alt;
  float Grnd_Spd;
  float True_Airspeed;
  float Indicated_Airspeed;
  float Mach_Number;
  float Vert_Velocity;
  float True_Heading;
  float Track;
  float Drift;
  float Pitch;
  float Roll;
  float Side_Slip;
  float Angle_of_Attack;
  float Ambient_Temp;
  float Dew_Point;
  float Total_Temp;
  float Static_Press;
  float Dynamic_Press;
  float Cabin_Pressure;
  float Wind_Speed;
  float Wind_Direction;
  float Vert_Wind_Spd;
  float Solar_Zenith;
  float Sun_Elev_AC;
  float Sun_Az_Grd;
  float Sun_Az_AC;
} ChemWAD_t;
extern ChemWAD_t ChemWAD;

#endif
