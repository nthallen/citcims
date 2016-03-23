/* UPS_parsers.cc
 * Parsers all return false when they are done (either a
 *   complete record has been parsed or a syntax error has been
 *   encountered)
 * and true when the response is incomplete. The caller will
 * handle timeouts.
 */
#include <ctype.h>
#include "UPS.h"
#include "nortlib.h"

int UPS_ser::parse_QMOD(UPS_cmd_req *cr) {
  if (not_found('(')) {
    return 1;
  } else if (cp < nc) {
    const char modes[] = "PSYLBTFECD";
    uint8_t c = buf[cp++];
    int i;
    for (i=0; modes[i] != '\0'; ++i) {
      if (c == modes[i]) {
        UPS_TMp->QMOD = i;
	set_response_bit(UPSR_QMOD);
        report_ok();
        return 0;
      }
    }
    UPS_TMp->QMOD = i;
    report_err("Invalid status from QMOD");
    return 0;
  }
  return 1;
}

// Looking for int "." int and converting to a fixed float stored as 1 int
int UPS_ser::not_fixed_1( unsigned int &val ) {
  val = 0;
  if (cp >= nc)
    return 1;
  while (cp < nc && isspace(buf[cp]))
    ++cp;
  if (!isdigit(buf[cp])) {
    if (buf[cp] == '-') {
      while (cp < nc && (buf[cp] == '-' || buf[cp] == '.'))
	++cp;
      val = 9999;
      return 0;
    } else {
      report_err("Expected digit at columnt %d", cp);
      return 1;
    }
  }
  while (cp < nc && isdigit(buf[cp])) {
    val = val*10 + buf[cp++] - '0';
  }
  if (cp >= nc) {
    return 1;
  } else if (buf[cp] != '.') {
    report_err("Expected decimal in not_fixed_1 at column %d", cp);
    return 1;
  }
  if (!isdigit(buf[++cp])) {
    report_err("Expected digit after decimal in not_fixed_1 at column %d", cp);
    return 1;
  }
  val = val*10 + buf[cp++] - '0';
  if (!isspace(buf[cp])) {
    report_err("Expected end of field after decimal");
    return 1;
  }
  return 0;
}

int UPS_ser::not_bin(uint16_t &word, int nbits) {
  int nbits_in = nbits;
  while (cp < nc && isspace(buf[cp])) {
    ++cp;
  }
  word = 0;
  while (nbits > 0 && cp < nc && (buf[cp] == '0' || buf[cp] == '1')) {
    word = (word<<1) | (buf[cp++]-'0');
    --nbits;
  }
  if (nbits > 0) {
    if (cp < nc)
      report_err("Invalid bit in not_bin(%d) at column %d after %d bits",
	nbits_in, cp, nbits_in-nbits);
    return 1;
  }
  return 0;
}

/*
    (MMM.M HH.H LLL.L NN.N QQQ.Q DDD KKK.K VVV.V SSS.S XXX.X TTT.T
      b9b8b7b6b5b4b3b2b1b0<cr>
    MMM.M Input voltage V
    HH.H Input frequency Hz
    LLL.L Output voltage V
    NN.N Output frequency Hz
    QQQ.Q Output current A
    DDD Output load percent %
    KKK.K Positive BUS voltage V
    VVV.V Negative BUS voltage V
    SSS.S P Battery voltage V
    XXX.X N Battery voltage V
    TTT.T Max Temperature of the detecting pointers C
    b9-b0 (plus a1a0?)
*/
int UPS_ser::parse_QGS(UPS_cmd_req *cr) {
  unsigned int M, H, L, N, Q, K, V, S, X, T;
  int D;
  uint16_t ba;
  M = H = L = N = Q = K = V = S = X = T = 0;
  D = 0;
  if (not_found('(') ||
      not_fixed_1(M) ||
      not_fixed_1(H) ||
      not_fixed_1(L) ||
      not_fixed_1(N) ||
      not_fixed_1(Q) ||
      not_int(D) ||
      not_fixed_1(K) ||
      not_fixed_1(V) ||
      not_fixed_1(S) ||
      not_fixed_1(X) ||
      not_fixed_1(T) ||
      not_bin(ba, 12)) {
    nl_error(MSG_DBG(0),
    	"M:%d H:%d L:%d N:%d Q:%d D:%d K:%d V:%d S:%d X:%d T:%d",
    	M, H, L, N, Q, D, K, V, S, X, T);
    return cp >= nc;
  }
  UPS_TMp->QGS_V_in = M;
  UPS_TMp->QGS_F_in = H;
  UPS_TMp->QGS_V_out = L;
  UPS_TMp->QGS_F_out = N;
  UPS_TMp->QGS_I_out = Q;
  UPS_TMp->QGS_LoadPct = D;
  UPS_TMp->QGS_VBusP = K;
  UPS_TMp->QGS_VBusN = V;
  UPS_TMp->QGS_VBatP = S;
  UPS_TMp->QGS_VBatN = X;
  UPS_TMp->QGS_Tmax = T;
  UPS_TMp->QGS_Status = ba;
  set_response_bit(UPSR_QGS);
  report_ok();
  return 0;
}

int UPS_ser::parse_QWS(UPS_cmd_req *cr) {
  uint16_t A1, A2, A3, A4;
  if (not_found('(') ||
      not_bin(A1, 16) || // a0..a15, bit reversed
      not_bin(A2, 16) || // a16..a31, bit reversed
      not_bin(A3, 16) || // a32..a47, bit reversed
      not_bin(A4, 16)) { // a48..a63, bit reversed
    return cp >= nc;
  }
  UPS_TMp->QWS =
    ((A1>>2)&3) |
    ((A1>>3)&(1<<2)) |
    ((A1>>4)&(0xF<<3)) |
    ((A1>>6)&(1<<7)) |
    ((A1>>7)&(1<<8)) |
    ((A4<<7)&(3<<9)) |
    ((A4<<2)&(1<<11));
  set_response_bit(UPSR_QWS);
  report_ok();
  return 0;
}

int UPS_ser::out_of_range(int val, const char *desc, int low, int high) {
  if (val < low || val > high) {
    report_err("%s value %d is outside range (%d,%d)", desc, val, low, high);
    return 1;
  }
  return 0;
}

/**
 *  QBV: P battery information:
 *   (RRR.R NN MM CCC TTT<cr>
 *  RRR.R Battery Voltage V
 *  NN Battery piece number (01 to 20)
 *  MM Battery group number (01 to 99)
 *  CCC Battery capacity (000 100)
 *  TTT Battery remain time minutes
 */
int UPS_ser::parse_QBV(UPS_cmd_req *cr) {
  unsigned int R;
  int N, M, C, T;
  if (not_found('(') ||
      not_fixed_1(R) ||
      not_int(N) ||
      not_int(M) ||
      not_int(C) ||
      not_int(T)) {
    return cp >= nc;
  }
  UPS_TMp->QBV_Vbat = R;
  UPS_TMp->QBV_Piece = N;
  UPS_TMp->QBV_Group = M;
  UPS_TMp->QBV_Capacity = C;
  UPS_TMp->QBV_Remain_Time = T;
  set_response_bit(UPSR_QBV);
  if (!(out_of_range(N, "Battery Piece", 1, 20) ||
        out_of_range(M, "Battery Group", 1, 99) ||
        out_of_range(C, "Battery Capacity", 0, 100) ||
        out_of_range(T, "Battery remain time", 0, 999))) {
    report_ok();
  }
  return 0;
}

int UPS_ser::parse_QSK1(UPS_cmd_req *cr) {
  uint16_t N;
  if (not_found('(') || not_bin(N,1)) {
    return cp >= nc;
  }
  set_response_bit(UPSR_QSK1);
  if (N) {
    set_response_bit(UPSR_QSK1_ON);
  } else {
    clear_response_bit(UPSR_QSK1_ON);
  }
  return 0;
}

/**
 * Looking for (ACK or (NACK
 */
int UPS_ser::parse_cmd(UPS_cmd_req *cr) {
  if (not_found('(')) {
    return 1;
  } else {
    bool nack = false;
    if (cp < nc && buf[cp] == 'N') {
      nack = true;
      ++cp;
    }
    if (not_str("ACK\r")) {
      return cp >= nc;
    }
    if (nack) {
      nl_error(2, "NACK reported for command %s", cr->req_buf);
    }
    return 0;
  }
  return 1;
}

int UPS_ser::parse_query(UPS_cmd_req *cr) {
  if (not_found('(')) {
    return 1;
  } else {
    if (nc > cp && buf[nc-1] == '\r') {
      buf[nc-1] = '\0';
      nl_error(0, "%s: %s", cr->req_buf, ascii_escape((const char *)&buf[cp]));
      return 0;
    }
  }
  return 1;
}


