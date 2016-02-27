#ifndef ZABER_INT_H_INCLUDED
#define ZABER_INT_H_INCLUDED

#include <vector>
#include "zaber.h"
#include "SerSelector.h"
#include "Timeout.h"

typedef struct {
  Timeout timeout;
  long int cmd_data;
  long int cmds_sent;
  long int replies_recd;
  long int timeouts;
  long int overwrites;
  long int late_replies;
  int state;
} cmd_stats_t;

class cmd_stat_c {
  public:
    cmd_stat_c();
    cmd_stats_t cmd_stats[N_DRIVES];
};

class Zaber;
typedef int (Zaber::*callinfn)(zaber_cmd *zc, Timeout *timeout);
typedef void (Zaber::*calloutfn)(zaber_cmd *zc);

class zcmd_def {
  public:
    zcmd_def();
    void init(const char *name, bool unsol,
              callinfn callin, calloutfn callout,
              bool valid = true);
    const char *cmd_name;
    bool unsolicited;
    callinfn cmd_callin;
    calloutfn cmd_callout;
    cmd_stat_c *stats;
};

class ZaberCmd : public Ser_Sel {
  public:
    ZaberCmd();
    ~ZaberCmd();
    int ProcessData(int flag);
    zaber_cmd *Command();
  private:
    zaber_cmd zc;
};

typedef struct {
  int state;
  int failing_cmd;
} drive_state_t;

class Zaber : public Ser_Sel {
  public:
    Zaber( const char *path, zaber_tms_t *data, ZaberCmd *ZCmc);
    ~Zaber();
    int ProcessData(int flag);
    Timeout *GetTimeout();
    void init();
    int invalid_callin( zaber_cmd *zc, Timeout *timeout );
    void invalid_callout( zaber_cmd *zc );
  private:
    void CmdsInit();
    void identify();
    void poll();
    void send_zcommand( zaber_cmd *zc );
    void send_command( drv_t drive, drv_t cmd, long int value );
    void receive_data( zaber_cmd *zc );
    void register_timeout( unsigned char cmd_index, unsigned drive );
    void register_reply( zaber_cmd *zc, int late_reply );
    cmd_stats_t *cmd_stats(unsigned char cmd, unsigned drive);
    int normal_callin( zaber_cmd *zc, Timeout *timeout );
    int reset_callin( zaber_cmd *zc, Timeout *timeout );
    int move_callin( zaber_cmd *zc, Timeout *timeout );
    int stop_callin( zaber_cmd *zc, Timeout *timeout );
    void renumber_callout( zaber_cmd *zc );
    void position_callout( zaber_cmd *zc );
    void devid_callout( zaber_cmd *zc );
    void version_callout( zaber_cmd *zc );
    void status_callout( zaber_cmd *zc );
    void voltage_callout( zaber_cmd *zc );
    void error_callout( zaber_cmd *zc );
    zaber_tms_t *TMdata;
    std::vector<zcmd_def> cmddefs;
    ZaberCmd *ZC;
    drive_state_t drive_state[N_DRIVES];
    Timeout TO;
    int n_writes, n_reads;
};

#endif
