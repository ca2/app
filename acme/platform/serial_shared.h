#pragma once


namespace serial
{


   struct port_info
   {

      /*! Address of the serial port (this can be passed to the constructor of serial). */
      string port;

      /*! Human readable description of serial device if available. */
      string description;

      /*! Hardware ID (e.g. VID:PID of USB serial devices) or "n/a" if not available. */
      string hardware_id;

   };


} // namespace serial



