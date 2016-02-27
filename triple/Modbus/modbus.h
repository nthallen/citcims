#ifndef MODBUS_H_INCLUDED
#define MODBUS_H_INCLUDED

#include <stdint.h>
extern char *modbus_path;

typedef struct __attribute__((__packed__)) {
  float PM6C_T1;
  float PM6C_SP1;
  float PM6C_T2;
  float PM6C_SP2;
  int16_t F4_IV1;
  int16_t F4_IV2;
  int16_t F4_IV3;
  int16_t F4_Op;
  int16_t F4_SP1;
  int16_t F4_SP2;
} Modbus_t;

#ifdef __cplusplus

#include "SerSelector.h"
#include <deque>
#include "crc.h"

enum MB_rep_status_t { MB_rep_ok, MB_rep_incomplete, MB_rep_error,
  MB_rep_MB_err };
class modbus;

class modbus_req {
  public:
    modbus_req(uint8_t device, uint8_t function_code,
      unsigned req_size, uint16_t rep_size);
    ~modbus_req();
    MB_rep_status_t process_reply(uint8_t *rep, unsigned nb);
    virtual void dispose(modbus *MB);
    int write(int fd);
    const char *ascii_escape();
    MB_rep_status_t reply_status;
    const char *error_msg;
    uint8_t MB_err_code;
    uint8_t *req_buf;
    unsigned rep_sz;
    unsigned req_sz;
    uint8_t devID;
  protected:
    virtual void process_pdu(uint8_t *rep) = 0;
    void crc_set();
    int crc_ok(uint8_t *rep, unsigned nb);
    uint16_t crc(uint8_t *buf, unsigned nb);
    void float_swap(uint8_t *dest, uint8_t *src);
    void word_swap(uint8_t *dest, uint8_t *src);
    unsigned reqb_sz;
};

class modbus_poll_float : public modbus_req {
  public:
    modbus_poll_float(uint8_t device, uint16_t address, float *dest);
    ~modbus_poll_float();
  protected:
    void process_pdu(uint8_t *rep);
  private:
    float *destination;
};

class modbus_poll_int : public modbus_req {
  public:
    modbus_poll_int(uint8_t device, uint16_t address, int16_t *dest);
    ~modbus_poll_int();
  protected:
    void process_pdu(uint8_t *rep);
  private:
    int16_t *destination;
};

class modbus_cmd_float : public modbus_req {
  public:
    modbus_cmd_float();
    ~modbus_cmd_float();
    void dispose(modbus *MB);
    void init(uint8_t device, uint16_t address, float arg);
  protected:
    void process_pdu(uint8_t *rep);
};

class modbus_cmd_int : public modbus_req {
  public:
    modbus_cmd_int();
    ~modbus_cmd_int();
    void dispose(modbus *MB);
    void init(uint8_t device, uint16_t address, int16_t arg);
  protected:
    void process_pdu(uint8_t *rep);
};

class modbus : public Ser_Sel {
  public:
    modbus(const char *path, Modbus_t *MB_TM);
    ~modbus();
    void queue_cmd_float(uint8_t device, uint16_t address, float value);
    void queue_cmd_int(uint8_t device, uint16_t address, int16_t value);
    int ProcessData(int flag);
    Timeout *GetTimeout();
    void check_cmd();
    void submit_req(modbus_req *req);
    std::deque<modbus_req *> polls;
    std::deque<modbus_cmd_float *> cmd_float_free;
    std::deque<modbus_cmd_int *> cmd_int_free;
    std::deque<modbus_req *> cmds;
    std::deque<modbus_req *>::const_iterator cur_poll;
    modbus_req *pending;
    // Device ID codes:
    static const uint8_t PM6C_1_ID = 1;
    static const uint8_t F4_1_ID = 2;
  private:
    Timeout TO;
};

class modbus_cmd : public Ser_Sel {
  public:
    modbus_cmd(modbus *MB_in);
    ~modbus_cmd();
    int ProcessData(int flag);
  private:
    modbus *MB;
};

#endif
#endif
