#ifndef UPS_H_INCLUDED
#define UPS_H_INCLUDED
  #include <termios.h>
  #include <stdint.h>
  extern char *device_path;
  #ifdef __cplusplus
    extern "C" {
  #endif
      extern void ups_init_options( int argc, char **argv);
  #ifdef __cplusplus
    };
  #endif

  typedef struct __attribute__((__packed__)) {
    uint16_t QGS_V_in;
    uint16_t QGS_F_in;
    uint16_t QGS_V_out;
    uint16_t QGS_F_out;
    uint16_t QGS_I_out;
    uint16_t QGS_VBusP;
    uint16_t QGS_VBusN;
    uint16_t QGS_VBatP;
    uint16_t QGS_VBatN;
    uint16_t QGS_Tmax; // assume positive for now
    uint16_t QGS_Status;
    uint16_t QWS;
    uint16_t QBV_Vbat;
    uint8_t UPS_Response;
    uint8_t UPS_Response2;
    uint8_t QMOD;
    uint8_t QGS_LoadPct;
    uint8_t QBV_Piece;
    uint8_t QBV_Group;
    uint8_t QBV_Capacity;
    uint8_t QBV_Remain_Time;
  } UPS_TM_t;
  
  /* Bit Values for UPS_Response */
  #define UPSR_QMOD 0x01
  #define UPSR_QGS  0x02
  #define UPSR_QWS  0x04
  #define UPSR_QBV  0x08
  #define UPSR_QSK1 0x10
  #define UPSR_RESPONSES 0x1F
  #define UPSR_QSK1_ON 0x20
  
  /* Bit Values for QWS */
  #define QWS_a13 0x0001 // Charger alarm
  #define QWS_a12 0x0002 // Over temperature alarm
  #define QWS_a10 0x0004 // EPO enabled
  #define QWS_a8  0x0008 // Overload
  #define QWS_a7  0x0010 // Low battery
  #define QWS_a6  0x0020 // Battery overcharged
  #define QWS_a5  0x0040 // Input frequency unstable in bypass
  #define QWS_a2  0x0080 // Neutral and line wires oppositely connected
  #define QWS_a0  0x0100 // Battery disconnected
  #define QWS_a61 0x0200 // EEPROM operation error
  #define QWS_a60 0x0400 // Bypass unstable
  #define QWS_a54 0x0800 // P1 cut off pre-alarm

  #ifdef __cplusplus
    #include "SerSelector.h"
    #include <queue>
    #include <deque>

    class UPS_ser;
    class UPS_cmd_req;
    typedef int (UPS_ser::*UPS_parser)(UPS_cmd_req *cr);

    class UPS_cmd_req {
      public:
        UPS_cmd_req();
        bool init(const char *cmdquery, UPS_parser parser_in,
          unsigned reply_min);
        const char *ascii_escape();
        int write(int fd);
        static const unsigned int max_cmd_bytes = 20;
        uint8_t req_buf[max_cmd_bytes];
        unsigned rep_min;
        bool persistent;
        bool active;
        UPS_parser parser;
      private:
        unsigned req_sz;
    };
    
    class UPS_ser : public Ser_Sel {
      public:
        UPS_ser(const char *path, UPS_TM_t *UPS_TM);
        ~UPS_ser();
        UPS_cmd_req *new_command_req(const char *cmdquery,
              UPS_parser parser_in, unsigned reply_min);
        void enqueue_polls();
        void enqueue_command(UPS_cmd_req *);
        void enqueue_command(const char *cmdquery);
        void enqueue_query(const char *cmdquery, unsigned reply_min);
        void enqueue_poll(UPS_cmd_req *);
        void enqueue_poll(const char *cmdquery, UPS_parser parser_in,
              unsigned reply_min);
        void free_command(UPS_cmd_req *);
        int ProcessData(int flag);
        int parse_QMOD(UPS_cmd_req *cr);
        int parse_QGS(UPS_cmd_req *cr);
        int parse_QWS(UPS_cmd_req *cr);
        int parse_QBV(UPS_cmd_req *cr);
        int parse_QSK1(UPS_cmd_req *cr);
        int parse_cmd(UPS_cmd_req *cr);
        int parse_query(UPS_cmd_req *cr);
        Timeout *GetTimeout();
        bool submit_req(UPS_cmd_req *req);
      private:
        void update_termios();
        void set_response_bit(uint8_t mask);
        void clear_response_bit(uint8_t mask);
        int not_bin(uint16_t &word, int nbits);
        int not_fixed_1( unsigned int &val );
        int out_of_range(int val, const char *desc, int low, int high);
        static const unsigned tm_gflag = 0;
        static const unsigned cmd_gflag = 1;
        static const int reply_max = 80;
        UPS_TM_t *UPS_TMp;
        std::deque<UPS_cmd_req *> cmds;
        std::deque<UPS_cmd_req *> cmd_free;
        std::deque<UPS_cmd_req *> polls;
        std::deque<UPS_cmd_req *>::const_iterator cur_poll;
        UPS_cmd_req *pending;
        termios termios_s;
        Timeout TO;
    };

    class UPS_TM : public Selectee {
      public:
        UPS_TM(UPS_TM_t *data, const char *remnode = 0,
          const char *remexp = 0);
        UPS_TM();
        ~UPS_TM();
        void init(UPS_TM_t *data, const char *remnode,
          const char *remexp);
        void Connect();
        int ProcessData(int flag);
        Timeout *GetTimeout();
      protected:
        send_id TMid;
        static const char *UPS_TM_NAME;
        const char *remote;
        UPS_TM_t *TM_data;
        Timeout TO;
    };
    
    class UPS_cmd : public Ser_Sel {
      public:
        UPS_cmd(UPS_ser *UPS);
        ~UPS_cmd();
        int ProcessData(int flag);
      private:
        UPS_ser *UPS;
    };

  #endif // __cplusplus
#endif // UPS_H_INCLUDED
