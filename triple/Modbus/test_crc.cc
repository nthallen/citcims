/*
 * test_crc.cc
 */
#include <stdint.h>
#include <stdio.h>
#include "crc.h"

void test_crc(unsigned char *req_buf, const unsigned req_sz) {
  uint16_t crc_calc = CRC16(req_buf, req_sz-2);
  unsigned short crc_rep = (req_buf[req_sz-1]<<8) + req_buf[req_sz-2];
  printf(crc_calc == crc_rep ? "OK:   " : "FAIL: ");
  for (unsigned i = 0; i < req_sz; ++i) {
    printf(" %02X", req_buf[i]);
  }
  if (crc_calc != crc_rep) {
    printf(": Calculated %02X %02X", crc_calc & 0xFF, crc_calc >> 8);
  }
  printf("\n");
}

int main(int argc, char **argv) {
  unsigned char rb1[] = { 0x01, 0x03, 0x00, 0xF0, 0x00, 0x02, 0xc4, 0x38 };
  unsigned char rb2[] = { 0x01, 0x03, 0x04, 0x06, 0x0b, 0x41, 0xe7, 0xfb, 0x63 };
  unsigned char rb3[] = { 0x01, 0x03, 0x04, 0x0c, 0x30, 0x41, 0xe7, 0x89, 0x76 };
  unsigned char rb4[] = { 0x01, 0x03, 0x04, 0x0e, 0xab, 0x41, 0xe7, 0xf9, 0x21 };
  unsigned char rb5[] = { 0x01, 0x03, 0x9d, 0xa8, 0x00, 0x02, 'j', 'G' };
  unsigned char rb6[] = { 0x01, 0x03, 0x04, 0x00, 0x00, 0x00, 0x00, 0xfa, '3' };
  test_crc(rb1, sizeof(rb1));
  test_crc(rb2, sizeof(rb2));
  test_crc(rb3, sizeof(rb3));
  test_crc(rb4, sizeof(rb4));
  test_crc(rb5, sizeof(rb5));
  test_crc(rb6, sizeof(rb6));
  return 0;
}
