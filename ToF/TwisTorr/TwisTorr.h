#ifndef TWISTORR_H_INCLUDED
#define TWISTORR_H_INCLUDED

  #include <termios.h>

  /* Definitions for Selector/Selectee classes for Agilent TwisTorr Driver */
  #include <stdint.h>
  extern char *agilent_path;
  extern uint8_t agilent_absent;

  #define N_TWISTORR_DRIVES 3
  
  /*
   * flags:
   *   1: window 0 Start/Stop
   *   2: window 1 Low Speed
   *   4: window 106 water cooling
   *   8: window 107 active stop
   *  10: window 122 vent valve on/off
   *  20: window 123 vent valve operation
   *  80: Not responding
   */
  typedef struct __attribute__((__packed__)) {
    float pump_current; // window 200 (mA dc)
    float pump_voltage; // window 201 (V dc)
    float pump_power;   // window 202 (W)
    float driving_freq; // window 203 (Hz)
    float pump_temperature; // window 204 (0-70, what resolution?)
    float pump_status; // window 205 (0-6)
    float rotation_speed; // window 210 (100-963/1010)
    float error_status; // window 206
    unsigned char flags;
    unsigned char fill[3]; // For alignment
  } TwisTorr_TM_t;
  
  typedef struct __attribute__((__packed__)) {
    TwisTorr_TM_t drive[N_TWISTORR_DRIVES];
  } TwisTorr_t;

  #ifdef __cplusplus
    #include "SerSelector.h"
    #include <queue>
    #include <deque>

    enum TT_rep_status_t { TT_rep_ok, TT_rep_incomplete, TT_rep_error, TT_rep_win_disabled };
    enum CmdRestrictions_t { CR_none, CR_write_in_stop, CR_read_in_start };
    
    // Command Request Object
    class command_request {
      public:
        command_request();
        bool init(uint8_t device, uint16_t window, bool read,
          const uint8_t *data = 0);
        TT_rep_status_t process_reply(uint8_t *rep, unsigned nb);
        const char *ascii_escape();
        int write(int fd);
        void set_fl_ptr(float *fl_ptr);
        void set_bit_ptr(uint8_t *bit_ptr, uint8_t bit_mask);
        void default_read_action();
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
        uint16_t window;
        bool read;
      private:
        float *fl_ptr;
        uint8_t *bit_ptr;
        uint8_t bit_mask;
        uint8_t cmd_type; // 'L', 'N' or 'A'
    };
    
    class TwisTorr : public Ser_Sel {
      public:
        TwisTorr(const char *path, TwisTorr_t *TT_TM);
        ~TwisTorr();
        command_request *new_command_req();
        void enqueue_command(command_request *);
        void enqueue_poll(command_request *);
        void enqueue_poll_float(uint8_t device, uint16_t window, float *ptr);
        void enqueue_poll_bit(uint8_t device, uint16_t window, uint8_t *ptr, uint8_t mask);
        void free_command(command_request *);
        int ProcessData(int flag);
        Timeout *GetTimeout();
        bool submit_req(command_request *req);
        static const unsigned TT_DevNo[N_TWISTORR_DRIVES];
      private:
        void update_termios();
        static const unsigned TT_bufsize = 50;
        static const unsigned cmd_gflag = 1;
        TwisTorr_t *TT_TM_p;
        Timeout backoff_TO[N_TWISTORR_DRIVES];
        uint16_t backoff_secs[N_TWISTORR_DRIVES];
        std::deque<command_request *> cmds;
        std::deque<command_request *> cmd_free;
        std::deque<command_request *> polls;
        std::deque<command_request *>::const_iterator cur_poll;
        command_request *pending;
        termios termios_s;
        Timeout TO;
    };
    
    class TwisTorr_cmd : public Ser_Sel {
      public:
        TwisTorr_cmd(TwisTorr *TT);
        ~TwisTorr_cmd();
        int ProcessData(int flag);
      private:
        TwisTorr *TT;
    };

  #endif // __cplusplus
#endif // TWISTORR_H_INCLUDED
