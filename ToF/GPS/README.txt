Diamond Systems Hercules III board supports a Condor C2626 GPS receiver.
This chip produces an ASCII-encoded NMEA 0183 stream on a 2-wire RS-232
connection to the Top Cliff I/O Chipset on the motherboard and a pulse-
per-second (PPS) signal routed to one of the I/O connectors. The plan is
to obtain both accurate system time and position information from this
chip. This is easier said than done, but I think we have identified a
set of programs that should do the trick.

Background:

ntpd is pretty much the standard for maintaining accurate system time.
It can obtain time references from a variety of sources, including
the internet, but a field-deployable instrument cannot count on constant
network connectivity, so the option of using a GPS source is very attractive.

There are several hurdles to using ntpd as shipped with QNX 6.5.0.

  1: ntpd can use the NMEA 0183 serial stream directly from the
     serial port. There are two problems with this. First, only
     one process can read from a serial device without loss of
     data, so that means while ntpd could obtain the time information
     it needs, we would lose the position data. Second, to maintain
     accurate timing, ntpd also needs to use the PPS signal, and
     specifically requires a particular PPS API that Linux supports
     but QNX does not.
  2: A former QNX employee developed a QNX resource manager called
     pps to implement the PPS API. It requires that the PPS signal
     be routed to the DCD pin of the I/O mapped /dev/ser1 port.
     It is possible that the version of ntpd shipped with QNX 6.5
     supports both NMEA and PPS, so between pps and ntpd, we
     could have accurate time. But we would not have access to the
     position data.
  3: The program gpsd is designed to deal with this issue. It reads
     the NMEA and PPS data and produces a JSON-encoded output stream
     that multiple programs can read, including ntpd. It also requires
     the PPS API, so the pps program is still required. The problem
     is in getting the data to ntpd. The version of ntpd shipped with
     QNX does not support the JSON-encoded stream. The gpsd and ntpd
     source code also provides a shared-memory interface, but only
     with the SYSV IPC functions, not the POSIX functions supported
     by QNX. So we need to port a more recent version of ntpd.
     
Where I got the source code:
  pps: http://cs.nyu.edu/~bacon/pps/
    Written by David Bacon: http://cs.nyu.edu/~bacon/cv/cv/index.html
  gpsd: http://www.catb.org/gpsd/
    Browse: http://git.savannah.gnu.org/cgit/gpsd.git
    Clone: git://git.sv.gnu.org/gpsd.git
  scons: Build tool required by gpsd
    http://www.scons.org/download.php
    Retrieved scons-2.4.1.tar.gz
  ntpd:
    https://www.eecis.udel.edu/~mills/ntp/html/index.html
    http://www.ntp.org/downloads.html
    Retrieved ntp-4.2.8p4.tar.gz

CHANGES:
  pps:
    Manually limit to just /dev/ser1 to produce /dev/pps1
    Patch timepps.h to #include <time.h>: ntpd's configure
      script needs this or it fails.
  scons:
  gpsd:
    Numerous patches required. Documented in Evernote ####
    Minimal build to support only devices and exports we need.
  ntpd:
    Various minor issues:
      Patch sys/timepps.h (from pps) to #include <time.h>
      export CPPFLAGS=-I/usr/local/include
      export ACCEPT_INFERIOR_RM_PROGRAM=yes
      ./configure
      sntp/libevent/signal.c: conditionaled-out use of SA_RESTART
      sntp/main.c: conditionally defined EX_USAGE (should be from sysexits.h)

CONFIGURATION for GCToF:
  Route PPS signal to DCD on /dev/ser1
  Run devc-serpci to pick up Top Cliff UARTs. (currently /dev/ser11)
  Create soft-link for ntpd, gpsd:
    # ln -sP /dev/ser11 /dev/gps1
  Run pps to monitor /dev/ser1, provide /dev/pps1
    # pps
  Run gpsd to monitor /dev/gps1, /dev/pps1, generate JSON stream
    # gpsd /dev/gps1 /dev/pps1
  Run ntpd to listen to gpsd stream, /dev/pps1

ntp.conf
https://www.freebsd.org/cgi/man.cgi?query=ntp.conf&sektion=5
  # by default act only as a basic NTP client
  restrict -4 default nomodify nopeer noquery notrap
  restrict -6 default nomodify nopeer noquery notrap
  
  # allow NTP messages from the loopback address, useful for debugging
  restrict 127.0.0.1
  restrict ::1
  # Explicitly allow messages from peers as necessary

  # Sync to gpsd's JSON interface tied to /dev/gps1
  server 127.127.46.1 mode 1
  # fudge time1 should be set to cover prop delay of data
  # from the chip through the JSON output
  # Presumably can calibrate relative to PPS
  fudge 127.127.46.1 time1 0.0

  # Get PPS info directly from /dev/pps1
  server 127.127.22.1

  # Drift File
  driftfile /etc/ntp/ntp.drift