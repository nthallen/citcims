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
    not_nfloat(&ChemWAD.MMS_Side_Slip) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.MMS_Angle_of_Attack) || not_str(",", 1) ||
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
    not_nfloat(&ChemWAD.Sun_Az_AC) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.jNO2) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.CH2O) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.C2H6) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.CO) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.CH4) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.WV_ppm) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.RHi) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.RHw) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.PAN) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.SO4) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.NO3) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.TotalOrganic) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Chloride) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.NH4) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.f43) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.f44) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.f57) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.f60) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.HCHO) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.n_mCPC) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.ufCN) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.coldCN) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.hotCN) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.drySCg_sub1) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.wetSCg_sub1) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.totalSCg) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.rawABSg) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.DilutionRatio) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.MMS_Static) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.MMS_StaticTemp) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.MMS_TAS) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.HCOOH) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.CL2) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.NOAA_WAS_CanNumber) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Acetonitrile) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Acetone) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Ethanol) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Isoprene_Furan) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Benzene) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Toluene) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Furfural) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.Catechol_MethFurfural) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.MaleicAnhydride) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.SO2_pptv) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.NO_pptv) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.NO) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.NOy) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.O3) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.BlackCarbon) || not_str(",", 1) ||
    not_nfloat(&ChemWAD.CO2)
  );
}

UserPkts::UserPkts(Selector *S) {
  UserPkts_UDP *UP;
  UP = new UserPkts_UDP(5104);
  UP->add_packet(new ChemWADpkt());
  S->add_child(UP);
  UDPs.push_back(UP);
}

