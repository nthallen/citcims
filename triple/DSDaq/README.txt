Diamond Systems Data Acquisition Driver Library

The basic idea here is to create a library for use by the driver itself and clients.
There is no reason these couldn't be two libraries, but since we need both client
and server on the system, they can be combined.

dsdaq.h will define the client api

dsdaqdrv.h will define the driver api

dsdaqmsg.h will define the message structure