#ifndef HORIBA_H_INCLUDED
#define HORIBA_H_INCLUDED

#define HORIBA_MAX_CHANNELS 5

typedef struct __attribute__((__packed__)) {
  float SP;
  float RB;
} horiba_channel_t;

typedef struct __attribute__((__packed__)) {
  horiba_channel_t channel[HORIBA_MAX_CHANNELS];
  unsigned short HoribaS; // Status word
} horiba_tm_t;

#define HORIBA_CMD_S (1<<(2*HORIBA_MAX_CHANNELS))

#endif

