Modbus driver configuration
  Device IDs on the RS485 RTU bus are defined in the modbus class in modbus.h
  This driver currently supports various Watlow temperature controllers

Commands
  It's a little tricky to anticipate all the types of commands we might need.
  At the moment, we are only supporting set points on the PM6C modules, so
  the only information we need to convey is:
    Which device are we addressing (assuming there are more than one)
    Which channel (assuming there are two per device)
    What is the new setpoint
  The mapping between command channel number and Modbus device ID/channel
  is entirely arbitrary. They could be the same or not. We can sort it out
  between the modbus.cmd file and modbus_cmd::Process_Data()
    Sc:v
      c = channel number (1 => PM6C_1_ID channel 1
                          2 => PM6C_1_ID channel 2)
      v = setpoint value (float, centigrade)

To add support for a new device, we need to:
  Add the device ID to modbus.h
  Add the data fields to the TM structure Modbus_t
  Add the data polling requests to the Modbus constructor
  Add command channels to Modbus_cmd::Process_Data()
and of course:
  Add TM, collection and display definitions
  Add command definitions

Requirements for F4:
  Read Inputs 1-3 (registers 100, 104, 108) (Apparently fixed point temperature)
  Read operation mode status (register 200?) (0 => Terminate Profile, 1 => Pre-run Profile, 2 => Running Profile, 3 => Holding Profile, 255 => NACK)
  
  Write control channel 1-2 T setpoint (static temp, registers 300 and 319)
  Read setpoint 1-2 (300 and 319)
  Start temperature profile (register 1209?)
  Stop temperature profile (register 1217?)
  
  Upload temperature profile (man pages 93-102)