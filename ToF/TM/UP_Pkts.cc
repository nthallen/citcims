#include "UP.h"
#include "UP_int.h"
#include "UP_Pkts.h"

ChemWADpkt::ChemWADpkt() : UserPkt("ChemWAD") {
  TM_init(&ChemWAD, sizeof(ChemWAD_t));
}

int ChemWADpkt::Process_Pkt() {
  return (
    not_ISO8601(&ChemWAD.Time, false) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Latitude) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Longitude) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.GPS_MSL_Alt) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.WGS_84_Alt) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Press_Alt) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Radar_Alt) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Grnd_Spd) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.True_Airspeed) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Indicated_Airspeed) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Mach_Number) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Vert_Velocity) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.True_Heading) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Track) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Drift) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Pitch) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Roll) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Side_Slip) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Angle_of_Attack) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Ambient_Temp) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Dew_Point) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Total_Temp) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Static_Press) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Dynamic_Press) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Cabin_Pressure) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Wind_Speed) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Wind_Direction) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Vert_Wind_Spd) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Solar_Zenith) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Sun_Elev_AC) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Sun_Az_Grd) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Sun_Az_AC)
  );
}

UserPkts::UserPkts(Selector *S) {
  UserPkts_UDP *UP;
  UP = new UserPkts_UDP(5104);
  UP->add_packet(new ChemWADpkt());
  S->add_child(UP);
  UDPs.push_back(UP);
}

