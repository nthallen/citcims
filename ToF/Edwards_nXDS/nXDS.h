#ifndef NXDS_H_INCLUDED
#define NXDS_H_INCLUDED

  #include <termios.h>

  /* Definitions for Selector/Selectee classes for Edwards nXDS Driver */
  #include <stdint.h>
  extern uint8_t nxds_absent;

  #define N_NXDS_DRIVES 2
  
  /*
   * status:
   *   0: Drive not responding
   *   1: Deceleration
   *   2: Acceleration/running
   *   3: Standby speed
   *   4: Normal speed
   *   5: Above ramp speed
   *   6: Above overload speed
   *   7: Warning
   *   8: Fault
   *   9: Over voltage trip
   *  10: Over current trip
   *  11: Over temp trip
   *  12: Under temp trip
   *  13: Power stage fault
   *  14: Overload time out
   *  15: Acceleration time out
   */
  typedef struct __attribute__((__packed__)) {
    uint16_t link_voltage; // 809: 0-5000 x 0.1V
    int16_t motor_current; // 809: +/- 300 x 0.1A
    int16_t motor_power; // 809: +/- 15000 x 0.1W
    uint16_t status; // 802: see above
    //uint8_t pump_temp; // 808: 0-150 C
    uint8_t controller_temp; // 808: 0-150 C
    uint8_t motor_freq; // 802: 0-255 Hz
    uint8_t pump_on; // non-zero if commanded on
    uint8_t fill; // for alignment
  } nXDS_TM_t;
  
  typedef struct __attribute__((__packed__)) {
    nXDS_TM_t drive[N_NXDS_DRIVES];
  } nXDS_t;

  #ifdef __cplusplus
    extern "C" {
  #endif
      extern void nxds_init_options(int argc, char **argv);
  #ifdef __cplusplus
    };
  #endif

  #ifndef NXDS_HIDE_INTERNALS
  #ifdef __cplusplus
    #include "SerSelector.h"
    #include <queue>
    #include <deque>

    enum nX_rep_status_t { nX_rep_ok, nX_rep_incomplete, nX_rep_error };
    enum CmdRestrictions_t { CR_none, CR_write_in_stop, CR_read_in_start };
    
    // Command Request Object
    class command_request {
      public:
        command_request();
        bool init(uint8_t drive, uint8_t qualifier, uint16_t address,
          bool read, uint16_t value = 0);
        const char *ascii_escape();
        int write(int fd);
        bool active;
        bool persistent;
        unsigned req_sz, rep_sz;
        static const unsigned int max_cmd_bytes = 23;
        uint8_t req_buf[max_cmd_bytes];
        const char *error_msg;
        long TO_msecs;
        CmdRestrictions_t CmdRestrictions;
        uint8_t drive;
        uint8_t device;
        uint8_t req_qual;
        uint8_t req_type;
        uint16_t address;
        uint16_t value;
        bool read;
        static const int master_device = 55;
      private:
    };
    
    class nXDS : public Ser_Sel {
      public:
        nXDS(const char *path, nXDS_t *nX_TM);
        ~nXDS();
        command_request *new_command_req();
        void enqueue_command(command_request *);
        void enqueue_poll(command_request *);
        void enqueue_poll(uint8_t drive, uint8_t qualifier, uint16_t address);
        void enqueue_request(uint8_t drive, uint8_t qualifier,
          uint16_t address, bool read, uint16_t value = 0);
        nX_rep_status_t process_reply();
        void free_command(command_request *);
        int ProcessData(int flag);
        Timeout *GetTimeout();
        bool submit_req(command_request *req);
        static const unsigned nX_DevNo[N_NXDS_DRIVES];
      private:
        void update_termios();
        static const unsigned nX_bufsize = 50;
        static const unsigned cmd_gflag = 1;
        nXDS_t *nX_TM_p;
        Timeout backoff_TO[N_NXDS_DRIVES];
        uint16_t backoff_secs[N_NXDS_DRIVES];
        std::deque<command_request *> cmds;
        std::deque<command_request *> cmd_free;
        std::deque<command_request *> polls;
        std::deque<command_request *>::const_iterator cur_poll;
        command_request *pending;
        termios termios_s;
        Timeout TO;
        bool post_reply_delay;
    };
    
    class nXDS_cmd : public Ser_Sel {
      public:
        nXDS_cmd(nXDS *nX);
        ~nXDS_cmd();
        int ProcessData(int flag);
      private:
        nXDS *nX;
    };

    class nXDS_TM : public Selectee {
      public:
        nXDS_TM(nXDS_t *data, const char *remnode = 0,
          const char *remexp = 0);
        nXDS_TM();
        ~nXDS_TM();
        void init(nXDS_t *data, const char *remnode,
          const char *remexp);
        void Connect();
        int ProcessData(int flag);
        Timeout *GetTimeout();
      protected:
        send_id TMid;
        static const char *NXDS_TM_NAME;
        const char *remote;
        nXDS_t *TM_data;
        Timeout TO;
    };

  #endif // __cplusplus
  #endif // NXDS_HIDE_INTERNALS
#endif // NXDS_H_INCLUDED
