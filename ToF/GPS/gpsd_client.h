/* gpsd_client.h */
#ifndef GPSD_CLIENT_H_INCLUDED
#define GPSD_CLIENT_H_INCLUDED

#include "gpsd_tm.h"

  #ifdef __cplusplus
    extern "C" {
  #endif
      extern void gpsd_init_options( int argc, char **argv);
  #ifdef __cplusplus
    };
  #endif
  
  extern const char *gpsd_remote_node;
  extern const char *gpsd_remote_exp;

  #ifdef __cplusplus
    #include "SerSelector.h"

    class gpsd_TM : public Selectee {
      public:
        gpsd_TM(gpsd_tm_t *data, const char *remnode = 0,
          const char *remexp = 0);
        gpsd_TM();
        ~gpsd_TM();
        void init(gpsd_tm_t *data, const char *remnode,
          const char *remexp);
        void Connect();
        int ProcessData(int flag);
        Timeout *GetTimeout();
      protected:
        send_id TMid;
        static const char *GPSD_TM_NAME;
        const char *remote;
        gpsd_tm_t *TM_data;
        Timeout TO;
    };
    
    class gpsd_client : public Selectee {
      public:
        gpsd_client(gpsd_tm_t *data);
        ~gpsd_client();
        int ProcessData(int flag);
      private:
        void set_data_bit(unsigned bit);
        void set_error_bit(unsigned bit);
        gpsd_tm_t *TM_data;
        struct gps_data_t gpsdata;
        int consecutive_error_count;
        int total_error_count;
        bool errors_suppressed;
        static const int consecutive_error_limit = 10;
        static const int total_error_limit = 50;
    };
    
    // I will try not to use this
    class gpsd_cmd : public Cmd_Selectee {
      public:
        gpsd_cmd(int gf);
        ~gpsd_cmd();
        int ProcessData(int flag); // set cmd_gflag instead of quitting immediately and clear read flags
      private:
        int cmd_gflag;
    };
  #endif // __cplusplus
#endif
