Orion Power Systems DC3000RT
http://www.orionpowersystems.com/3000VA-online-double-conversion-ups-DC3000RT.html

Model: DC3000RT
Comm: RS-232
comm_p: 2400/8/N/1; turn off all flow control.

Communication Documentation: "UPS Protocol For Online RT-RTX1~3K v0.4-1.pdf"

Collection:

Record Parameters returned from following queries:
  QMOD (Mode: returns 10 distinct values: PSYLBTFECD)
  QGS (General Status:
    (MMM.M HH.H LLL.L NN.N QQQ.Q DDD KKK.K VVV.V SSS.S XXX.X TTT.T
      b9b8b7b6b5b4b3b2b1b0a0a1<cr>
    (220.2 50.0 220.0 50.0 027.0 100 345.8 344.9 241.0 241.5 045.0
      100011000000<cr> [76 characters]
    (122.4 60.0 122.2 60.0 000.0 000 169.0 169.2 082.1 ---.- 016.5 100010000001
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
  QWS (Warning Status: 64 bits, 12 of which are defined)
    [66 characters]
    (00000000000000000000000000000000000000000000000000000000000000000010000001
  QBV (P battery information:
    (RRR.R NN MM CCC TTT<cr> [21 characters]
    (082.0 06 01 091 342
    RRR.R Battery Voltage V
    NN Battery piece number (01 to 20)
    MM Battery group number (01 to 99)
    CCC Battery capacity (000 100)
    TTT Battery remain time minutes
  QSK1 (Socket status inquiry: 0 or 1, single bit
  [QSK2 -- not supported in this model]
  
  The following queries would just log results, not enter them into telemetry
    QPI Protocol ID Inquiry (PI01 [6 chars]
    QMD Model inquiry
      (TTTTTTTTTTTTTTT WWWWWWW KK P/P MMM NNN RR BB.B <cr> [47 chars?]
      (###########3000 ###3000 80 1/1 120 120 06 12.0<cr> [48 chars, don't know about trailing space]
    QID UPS ID inquiry (ABCDEEFFGXXXXX<cr> [16 chars]
      (00000000000000
    QVFW Main CPU Firmware version inquiry (VERFW: <NNNNN.NN><cr> [19 chars?]
     (VERFW:01213.00 [16 chars]
    QBYV bypass voltage range inquiry (HHH LLL <cr> [10 chars]
      (130 085 [maybe 9]
    QBYF bypass frequency range inquiry (HH.H LL.L <cr> [11 or 12 chars]
      (63.0 57.0
    QRI UPS Rating Information (MMM.M QQQ SSS.S RR.R<cr> [22 chars]
      (120.0 025 072.0 60.0
    QFLAG Setting flag status inquiry [maybe 19 chars?]
      (EpbrashclnzDovegfjm [21 chars] n,z are not documented
    QHE (HHH LLL<cr> [9 chars]
      (130 114
    QFS Fault status 
      (02 120.3 59.9 002.7 60.0 020 004.8 249.6 249.6 082.1 020.7 00001000

Commands to issue:
  Response to all commands is either "(ACK<cr>" or "(NACK<cr>"
    T<n>: Test for specified time
    S<n>: Shutdown in <n> minutes
    S<n>R<m>: Shutdown and restore
    CS: Cancel Shutdown
    CT: Cancel Test
    SKON1: Turn on socket 1: SKON<n>: n=1[,2] (socket 2 not supported)
    SKOFF1: Turn off socket 1: SKOFF<n>: n=1[,2]
Commands not to issue:
  Remote turn on UPS: SON
  Remote turn off UPS: SOFF
  [Since Hercules will be powered through UPS, issuing this command
   while telemetry is active is likely to cause disk corruption. On
   the other hand, it might be useful to have a standalone utility,
   or a standalone mode of operation to issue this command when the
   system is otherwise inactive.]
   
When we enqueue a command or query, it needs to be associated with a particular
parser. Each of the queries seems to require a different parser, although a
few can be consolidated:
  parse_QMOD
  parse_QGS
  parse_QSW
  parse_QBV
  parse_QSK1
  parse_cmd
  parse_query
Parsers can be UPS public class methods to take advantage of UPS's Ser_Sel
parsing functions. I could create subclasses for each parser type or just
require a parser argument when the command is enqueued. I did this with the
Zaber driver.
  
The goal here is to detect line power outage, and then closely monitor the remaining battery hold time.  Shutting down power hungry parts of the instrument as the battery life decreases.  In the end, issuing the 'Shutdown and Restore' command, and immediately turning off the computer.  Upon restoration of power, computer should boot automatically, startup the algo, startup the instrument, and resume measurements.  QSK1 (and supposedly QSK2) are independently switchable sockets.  The appear to be able to switch large loads (eg. vacuum pump).  So I hope to use these for this purpose, though I need to figure out why only a single command works for this unit.  Otherwise, the protocol seems quite straightforward, and seems to work.

---------------------------------

Should base design on TwisTorr and/or Agilent
Command Queue lives in the UPS Ser_Sel class
  Commands are received via the UPS_cmd class, hence UPS_cmd needs
    access to the UPS device to invoke the enqueue command
  Telemetry query commands are enqueued once at the beginning.
    That could be done by the init routine.
    Could include some sort if ID query