Edwards README

This directory holds a driver for Edwards nXDS Scroll Pump.

  9600/8/1/N
  Max message size is 80 chars, include start and end chars
  All alpha must be sent in upper case. Response may contain lower case

  Commands start with '!'
  Query starts with '?'

  'S' indicates statis non-volatile memory
  'C' and 'V' refer to non-persistent data

  Command structure:

    * #
    * [to address]:[from address]
    * Start character ('!' or '?')
    * Command (upper case alpha, followed by)
    * 
      * an object number ([0-9]{3}), followed by
      * for some commands only, [space][additional characters]

    * terminating carriage return

  Must assign multidrop address before introducing pump into multidrop setup. Manual provides a detailed procedure.
  Apparently the identify query ?S801 has the longest reply, something like 292 chars including the echo.

  Command confirmation come as " #" after repeating the command number. Details listed on page 15. 0 is no error

  Commands: (In the examples I assume I am addressing device 01. I am using device #55 for the master)

    * Start pump: "#01:55!C802 1\r" Reply: "#55:01*C802 r\r" where r is return code
    * Stop pump: "#01:55!C802 0\r" Reply: "#55:01*C802 r\r"
    * Full Speed: "#01:55!C803 0\r" Reply: "#55:01*C803 r\r"
    * Standby Speed: "#01:55!C803 1\r" Reply: "#55:01*C803 r\r"
    * Set Standby Speed: "#01:55!C805 ##\r" "#55:01*C805 r\r"
    
  Return Codes (r):
    0: No error
    1: Invalid command for object ID
    2: Invalid query/command
    3: Missing parameter
    4: Parameter out of range
    5: Invalid command in current state

  Readbacks:

    * Pump and controller temp: ?V808 "#01:55?V808\r"
    * Link voltage, motor current /power: ?V809
    * Motor Frequency: ?V802  (includes system status)
        "#01:55?V802\r#55:01=V802 dd;0000;0000;0000;0000\r
        request: 12 chars
        response:
    * Identification ?S801 "#01:55?S801\r#55:01=S801 nXDS;D37479651A;30" 43 chars total
        request: 12 chars
        response: 30 chars
    * Service Status (just at startup)

Command Server Interface
  Command Syntax: \d+:\d+:\d+
    drive number: 0 to N_NXDS_DRIVES-1
    address: One of 802, 803 or 805
    value: As appropriate
    examples:
      0:802:1  # start pump on drive 0
      0:802:0  # stop pump on drive 0
      0:803:1  # drive 0 to standby speed
      0:803:0  # drive 0 to full speed
      1:805:70 # Set drive 1 standby speed to 70% of full speed

Driver status word:
  This is a uint16_t value pulled from various places:
    Bit 0: Set to 1 when the start command is issued. 0 when stop is issued.
    Bit 1: System status register 1 bit 0: Deceleration
    Bit 2: System status register 1 bit 1: Acceleration/running
    Bit 3: System status register 1 bit 2: Standby active
    Bit 4: System status register 1 bit 3: Above normal speed
    Bit 5: System status register 1 bit 4: Operating above the ramp speed threshold
    Bit 6: System status register 1 bit 5: Operating above the overload speed threshold
    Bit 7: System status register 2 bit 6: Warning condition
    Bit 8: System status register 2 bit 7: Fault condition
    Bit 9: Fault register bit 1: Over voltage trip
    Bit 10: Fault register bit 2: Over current trip
    Bit 11: Fault register bit 3: Over temperature trip
    Bit 12: Fault register bit 4: Under temperature trip
    Bit 13: Fault register bit 5: Power stage fault
    Bit 14: Fault register bit 14: Overload time out
    Bit 15: Fault register bit 15: Acceleration time out
    