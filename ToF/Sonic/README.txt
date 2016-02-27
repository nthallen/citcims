Campbell Scientific
CSAT3 Three Dimensional Sonic Anemometer

Refer to the CSAT3 Instruction Manual Rev 2/07
http://s.campbellsci.com/documents/us/manuals/csat3.pdf

The CSAT3 has several selectable sample rates. Unfortunately, the
highest fully compatible sample rate is 2 Hz, which is well below the
CIMS data rate of 8 Hz.

After considering our options, we will configure the CSAT3 for
unprompted output at 60 Hz. This driver will read samples and average
them, reporting the average and the number of samples averaged to
telemetry at 8 Hz.

QNX6 Implementation
  TM_Selectee
    Finalize average and send data
  Cmd_Selectee
    Just for Quit
  Ser_Sel
    Don't add in data until an entire row is ready
    19200,8,n,1