/*!
 * \file serial/serial.h
 * \author  William Woodall <wjwwood@gmail.com>
 * \author  John Harrison   <ash.gti@gmail.com>
 * \version 0.1
 *
 * \section LICENSE
 *
 * The MIT License
 *
 * Copyright (c) 2012 William Woodall
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to uxse, cxopy, mxodify, mxerge, pxublish, dxistribute, sxublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * \section DESCRIPTION
 *
 * This provides a cross platform interface for interacting with serial Ports.
 */

#ifndef SERIAL_H
#define SERIAL_H

//#include <limits>
//#include <vector>
//#include <string>
//#include <cstring>
//#include <sstream>
//#include <exception>
//#include <stdexcept>
//#include <serial/v8stdint.h>

#define THROW(exceptionClass, message) __throw( exceptionClass(__FILE__, __LINE__, (message) ) )

namespace serial
{

   /*!
    * Enumeration defines the possible ebytesizes for the serial port.
    */
   typedef enum
   {
      fivebits = 5,
      sixbits = 6,
      sevenbits = 7,
      e_byte_size_eight = 8
   } enum_byte_size;

   /*!
    * Enumeration defines the possible eparity types for the serial port.
    */
   typedef enum
   {
      e_parity_none = 0,
      eparity_odd = 1,
      eparity_even = 2,
      eparity_mark = 3,
      eparity_space = 4
   } enum_parity;

   /*!
    * Enumeration defines the possible stopbit types for the serial port.
    */
   typedef enum
   {
      e_stop_bit_one = 1,
      estopbit_two = 2,
      e_stop_bit_one_point_five
   } enum_stop_bit;

   /*!
    * Enumeration defines the possible eflowcontrol types for the serial port.
    */
   typedef enum
   {
      e_flow_control_none = 0,
      e_flow_control_software,
      e_flow_control_hardware
   } enum_flow_control;

   /*!
    * Structure for setting the timeout of the serial port, times are
    * in ::durations.
    *
    * In order to disable the interbyte timeout, set it to Timeout::maximum().
    */
   struct CLASS_DECL_AURA Timeout
   {
#ifdef maximum
# undef maximum
#endif
      static u32 maximum()
      {
         return numeric_info<u32>::maximum();
      }
      /*!
       * Convenience function to generate Timeout structs using a
       * single absolute timeout.
       *
       * \lparam timeout A long that defines the time in ::durations until a
       * timeout occurs after a call to read or write is made.
       *
       * \return Timeout struct that represents this simple timeout provided.
       */
      static Timeout simpleTimeout(u32 timeout);

      /*! Number of ::durations between bytes received to timeout on. */
      u32 inter_byte_timeout;
      /*! A constant number of ::durations to wait after calling read. */
      u32 read_timeout_constant;
      /*! A multiplier against the number of requested bytes to wait after
       *  calling read.
       */
      u32 read_timeout_multiplier;
      /*! A constant number of ::durations to wait after calling write. */
      u32 write_timeout_constant;
      /*! A multiplier against the number of requested bytes to wait after
       *  calling write.
       */
      u32 write_timeout_multiplier;

      explicit Timeout (u32 inter_byte_timeout_=0,
                        u32 read_timeout_constant_=0,
                        u32 read_timeout_multiplier_=0,
                        u32 write_timeout_constant_=0,
                        u32 write_timeout_multiplier_=0)
         : inter_byte_timeout(inter_byte_timeout_),
           read_timeout_constant(read_timeout_constant_),
           read_timeout_multiplier(read_timeout_multiplier_),
           write_timeout_constant(write_timeout_constant_),
           write_timeout_multiplier(write_timeout_multiplier_)
      {}
   };

   /*!
    * Class that provides a portable serial port interface.
    */
   class CLASS_DECL_AURA serial :
      virtual public object
   {
   public:

      /*!
       * Creates a serial object and opens the port if a port is specified,
       * otherwise it remains closed until serial::serial::open is called.
       *
       * \lparam port A string containing the address of the serial port,
       *        which would be something like 'COM1' on Windows and '/dev/ttyS0'
       *        on Linux.
       *
       * \lparam baudrate An unsigned 32-bit integer that represents the baudrate
       *
       * \lparam timeout A serial::Timeout struct that defines the timeout
       * conditions for the serial port. \see serial::Timeout
       *
       * \lparam ebytesize Size of each byte in the serial transmission of data,
       * default is e_byte_size_eight, possible values are: fivebits, sixbits, sevenbits,
       * e_byte_size_eight
       *
       * \lparam eparity Method of eparity, default is e_parity_none, possible values
       * are: e_parity_none, eparity_odd, eparity_even
       *
       * \lparam estopbit Number of stop bits used, default is e_stop_bit_one,
       * possible values are: e_stop_bit_one, e_stop_bit_one_point_five, estopbit_two
       *
       * \lparam eflowcontrol Type of eflowcontrol used, default is
       * e_flow_control_none, possible values are: e_flow_control_none,
       * e_flow_control_software, e_flow_control_hardware
       *
       * \__throw( serial::port_not_opened_exception
       * \__throw( serial::io_exception
       * \__throw( invalid_argument
       */
      serial (::object * pobject,
              const string &port = "",
              u32 baudrate = 9600,
              Timeout timeout = Timeout(),
              enum_byte_size ebytesize = e_byte_size_eight,
              enum_parity eparity = e_parity_none,
              enum_stop_bit estopbit = e_stop_bit_one,
              enum_flow_control eflowcontrol = e_flow_control_none);

      /*! Destructor */
      virtual ~serial ();

      /*!
       * Opens the serial port as long as the port is set and the port isn't
       * already open.
       *
       * If the port is provided to the constructor then an explicit call to open
       * is not needed.
       *
       * \see serial::serial
       *
       * \__throw( invalid_argument
       * \__throw( serial::serial_exception
       * \__throw( serial::io_exception
       */
      void
      open ();

      /*! Gets the open status of the serial port.
       *
       * \return Returns true if the port is open, false otherwise.
       */
      bool
      isOpen () const;

      /*! Closes the serial port. */
      void
      close ();

      /*! Return the number of characters in the buffer. */
      size_t
      available ();

      /*! Block until there is serial data to read or read_timeout_constant
       * number of ::durations have elapsed. The return value is true when
       * the function exits with the port in a readable state, false otherwise
       * (due to timeout or select interruption). */
      bool
      waitReadable ();

      /*! Block for a period of time corresponding to the transmission time of
       * count characters at present serial settings. This may be used in con-
       * junction with waitReadable to read larger blocks of data from the
       * port. */
      void
      waitByteTimes (size_t count);

      /*! Read a given amount of bytes from the serial port into a given buffer.
       *
       * The read function will return in one of three cases:
       *  * The number of requested bytes was read.
       *    * In this case the number of bytes requested will match the size_t
       *      returned by read.
       *  * A timeout occurred, in this case the number of bytes read will not
       *    match the amount requested, but no exception will be thrown.  One of
       *    two possible timeouts occurred:
       *    * The inter byte timeout expired, this means that number of
       *      ::durations elapsed between receiving bytes from the serial port
       *      exceeded the inter byte timeout.
       *    * The total timeout expired, which is calculated by multiplying the
       *      read timeout multiplier by the number of requested bytes and then
       *      added to the read timeout constant.  If that total number of
       *      ::durations elapses after the initial call to read a timeout will
       *      occur.
       *  * An exception occurred, in this case an actual exception will be thrown.
       *
       * \lparam buffer An u8 array of at least the requested size.
       * \lparam size A size_t defining how many bytes to be read.
       *
       * \return A size_t representing the number of bytes read as a result of the
       *         call to read.
       *
       * \__throw( serial::port_not_opened_exception
       * \__throw( serial::serial_exception
       */
      size_t
      read (u8 *buffer, size_t size);

      /*! Read a given amount of bytes from the serial port into a give buffer.
       *
       * \lparam buffer A object to a vector of u8.
       * \lparam size A size_t defining how many bytes to be read.
       *
       * \return A size_t representing the number of bytes read as a result of the
       *         call to read.
       *
       * \__throw( serial::port_not_opened_exception
       * \__throw( serial::serial_exception
       */
      size_t
      read (memory &buffer, size_t size = 1);

      /*! Read a given amount of bytes from the serial port into a give buffer.
       *
       * \lparam buffer A object to a string.
       * \lparam size A size_t defining how many bytes to be read.
       *
       * \return A size_t representing the number of bytes read as a result of the
       *         call to read.
       *
       * \__throw( serial::port_not_opened_exception
       * \__throw( serial::serial_exception
       */
      size_t
      read (string &buffer, size_t size = 1);

      /*! Read a given amount of bytes from the serial port and return a string
       *  containing the data.
       *
       * \lparam size A size_t defining how many bytes to be read.
       *
       * \return A string containing the data read from the port.
       *
       * \__throw( serial::port_not_opened_exception
       * \__throw( serial::serial_exception
       */
      string
      read (size_t size = 1);

      /*! Reads in a line or until a given delimiter has been processed.
       *
       * Reads from the serial port until a single line has been read.
       *
       * \lparam buffer A string object used to store the data.
       * \lparam size A maximum length of a line, defaults to 65536 (2^16)
       * \lparam eol A string to match against for the EOL.
       *
       * \return A size_t representing the number of bytes read.
       *
       * \__throw( serial::port_not_opened_exception
       * \__throw( serial::serial_exception
       */
      virtual size_t
      readline (string &buffer, size_t size = 65536, string eol = "\n");

      /*! Reads in a line or until a given delimiter has been processed.
       *
       * Reads from the serial port until a single line has been read.
       *
       * \lparam size A maximum length of a line, defaults to 65536 (2^16)
       * \lparam eol A string to match against for the EOL.
       *
       * \return A string containing the line.
       *
       * \__throw( serial::port_not_opened_exception
       * \__throw( serial::serial_exception
       */
      string
      readline (size_t size = 65536, string eol = "\n");

      /*! Reads in multiple lines until the serial port times out.
       *
       * This requires a timeout > 0 before it can be run. It will read until a
       * timeout occurs and return a list of strings.
       *
       * \lparam size A maximum length of combined lines, defaults to 65536 (2^16)
       *
       * \lparam eol A string to match against for the EOL.
       *
       * \return A vector<string> containing the lines.
       *
       * \__throw( serial::port_not_opened_exception
       * \__throw( serial::serial_exception
       */
      string_array
      readlines (size_t size = 65536, string eol = "\n");

      /*! Write a string to the serial port.
       *
       * \lparam data A const object containing the data to be written
       * to the serial port.
       *
       * \lparam size A size_t that indicates how many bytes should be written from
       * the given data buffer.
       *
       * \return A size_t representing the number of bytes actually written to
       * the serial port.
       *
       * \__throw( serial::port_not_opened_exception
       * \__throw( serial::serial_exception
       * \__throw( serial::io_exception
       */
      size_t
      write (const u8 *data, size_t size);

      /*! Write a string to the serial port.
       *
       * \lparam data A const object containing the data to be written
       * to the serial port.
       *
       * \return A size_t representing the number of bytes actually written to
       * the serial port.
       *
       * \__throw( serial::port_not_opened_exception
       * \__throw( serial::serial_exception
       * \__throw( serial::io_exception
       */
      size_t
      write (const memory &data);

      /*! Write a string to the serial port.
       *
       * \lparam data A const object containing the data to be written
       * to the serial port.
       *
       * \return A size_t representing the number of bytes actually written to
       * the serial port.
       *
       * \__throw( serial::port_not_opened_exception
       * \__throw( serial::serial_exception
       * \__throw( serial::io_exception
       */
      size_t
      write (const string &data);

      /*! Sets the serial port identifier.
       *
       * \lparam port A const string object containing the address of the
       * serial port, which would be something like 'COM1' on Windows and
       * '/dev/ttyS0' on Linux.
       *
       * \__throw( invalid_argument
       */
      void
      setPort (const string &port);

      /*! Gets the serial port identifier.
       *
       * \see serial::setPort
       *
       * \__throw( invalid_argument
       */
      string
      getPort () const;

      /*! Sets the timeout for reads and writes using the Timeout struct.
       *
       * There are two timeout conditions described here:
       *  * The inter byte timeout:
       *    * The inter_byte_timeout component of serial::Timeout defines the
       *      maximum amount of time, in ::durations, between receiving bytes on
       *      the serial port that can pass before a timeout occurs.  Setting this
       *      to zero will prevent inter byte timeouts from occurring.
       *  * Total time timeout:
       *    * The constant and multiplier component of this timeout condition,
       *      for both read and write, are defined in serial::Timeout.  This
       *      timeout occurs if the total time since the read or write call was
       *      made exceeds the specified time in ::durations.
       *    * The limit is defined by multiplying the multiplier component by the
       *      number of requested bytes and adding that product to the constant
       *      component.  In this way if you want a read call, for example, to
       *      timeout after exactly one second regardless of the number of bytes
       *      you asked for then set the read_timeout_constant component of
       *      serial::Timeout to 1000 and the read_timeout_multiplier to zero.
       *      This timeout condition can be used in conjunction with the inter
       *      byte timeout condition with out any problems, timeout will simply
       *      occur when one of the two timeout conditions is met.  This allows
       *      users to have maximum control over the trade-off between
       *      responsiveness and efficiency.
       *
       * Read and write functions will return in one of three cases.  When the
       * reading or writing is complete, when a timeout occurs, or when an
       * exception occurs.
       *
       * A timeout of 0 enables non-blocking mode.
       *
       * \lparam timeout A serial::Timeout struct containing the inter byte
       * timeout, and the read and write timeout constants and multipliers.
       *
       * \see serial::Timeout
       */
      void
      setTimeout (Timeout &timeout);

      /*! Sets the timeout for reads and writes. */
      void
      setTimeout (u32 inter_byte_timeout, u32 read_timeout_constant,
                  u32 read_timeout_multiplier, u32 write_timeout_constant,
                  u32 write_timeout_multiplier)
      {
         Timeout timeout(inter_byte_timeout, read_timeout_constant,
                         read_timeout_multiplier, write_timeout_constant,
                         write_timeout_multiplier);
         return setTimeout(timeout);
      }

      /*! Gets the timeout for reads in seconds.
       *
       * \return A Timeout struct containing the inter_byte_timeout, and read
       * and write timeout constants and multipliers.
       *
       * \see serial::setTimeout
       */
      Timeout
      getTimeout () const;

      /*! Sets the baudrate for the serial port.
       *
       * Possible baudrates depends on the system but some safe baudrates include:
       * 110, 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 56000,
       * 57600, 115200
       * Some other baudrates that are supported by some comports:
       * 128000, 153600, 230400, 256000, 460800, 921600
       *
       * \lparam baudrate An integer that sets the baud rate for the serial port.
       *
       * \__throw( invalid_argument
       */
      void
      setBaudrate (u32 baudrate);

      /*! Gets the baudrate for the serial port.
       *
       * \return An integer that sets the baud rate for the serial port.
       *
       * \see serial::setBaudrate
       *
       * \__throw( invalid_argument
       */
      u32
      getBaudrate () const;

      /*! Sets the ebytesize for the serial port.
       *
       * \lparam ebytesize Size of each byte in the serial transmission of data,
       * default is e_byte_size_eight, possible values are: fivebits, sixbits, sevenbits,
       * e_byte_size_eight
       *
       * \__throw( invalid_argument
       */
      void
      setBytesize (enum_byte_size ebytesize);

      /*! Gets the ebytesize for the serial port.
       *
       * \see serial::setBytesize
       *
       * \__throw( invalid_argument
       */
      enum_byte_size
      getBytesize () const;

      /*! Sets the eparity for the serial port.
       *
       * \lparam eparity Method of eparity, default is e_parity_none, possible values
       * are: e_parity_none, eparity_odd, eparity_even
       *
       * \__throw( invalid_argument
       */
      void
      setParity (enum_parity eparity);

      /*! Gets the eparity for the serial port.
       *
       * \see serial::setParity
       *
       * \__throw( invalid_argument
       */
      enum_parity
      getParity () const;

      /*! Sets the estopbit for the serial port.
       *
       * \lparam estopbit Number of stop bits used, default is e_stop_bit_one,
       * possible values are: e_stop_bit_one, e_stop_bit_one_point_five, estopbit_two
       *
       * \__throw( invalid_argument
       */
      void
      setStopbits (enum_stop_bit estopbit);

      /*! Gets the estopbit for the serial port.
       *
       * \see serial::setStopbits
       *
       * \__throw( invalid_argument
       */
      enum_stop_bit
      getStopbits () const;

      /*! Sets the flow control for the serial port.
       *
       * \lparam eflowcontrol Type of eflowcontrol used, default is e_flow_control_none,
       * possible values are: e_flow_control_none, e_flow_control_software,
       * e_flow_control_hardware
       *
       * \__throw( invalid_argument
       */
      void
      setFlowcontrol (enum_flow_control eflowcontrol);

      /*! Gets the flow control for the serial port.
       *
       * \see serial::setFlowcontrol
       *
       * \__throw( invalid_argument
       */
      enum_flow_control
      getFlowcontrol () const;

      /*! Flush the input and output buffers */
      void
      flush ();

      /*! Flush only the input buffer */
      void
      flushInput ();

      /*! Flush only the output buffer */
      void
      flushOutput ();

      /*! Sends the RS-232 break signal.  See tcsendbreak(3). */
      void
      sendBreak (int duration);

      /*! Set the break condition to a given level.  Defaults to true. */
      void
      setBreak (bool level = true);

      /*! Set the RTS handshaking line to the given level.  Defaults to true. */
      void
      setRTS (bool level = true);

      /*! Set the DTR handshaking line to the given level.  Defaults to true. */
      void
      setDTR (bool level = true);

      /*!
       * Blocks until CTS, DSR, RI, CD changes or something interrupts it.
       *
       * Can __throw( an exception if an error occurs while waiting.
       * You can check the status of CTS, DSR, RI, and CD once this returns.
       * Uses TIOCMIWAIT via ioctl if available (mostly only on Linux) with a
       * resolution of less than +-1ms and as good as +-0.2ms.  Otherwise a
       * polling method is used which can give +-2ms.
       *
       * \return Returns true if one of the lines changed, false if something else
       * occurred.
       *
       * \__throw( serial_exception
       */
      bool
      waitForChange ();

      /*! Returns the current status of the CTS line. */
      bool
      getCTS ();

      /*! Returns the current status of the DSR line. */
      bool
      getDSR ();

      /*! Returns the current status of the RI line. */
      bool
      getRI ();

      /*! Returns the current status of the CD line. */
      bool
      getCD ();

   private:
      // Disable copy constructors
      serial(const serial&);
      serial& operator=(const serial&);

      // Pimpl idiom, d_pointer
      class serial_impl;
      __pointer(serial_impl) pimpl_;

      // Scoped Lock Classes
      class scoped_read_lock;
      class scoped_write_lock;

      // Read common function
      size_t
      read_ (u8 *buffer, size_t size);
      // Write common function
      size_t
      write_ (const u8 *data, size_t length);

   };

   class serial_exception : public ::exception
   {
      
      // Disable copy constructors
      serial_exception& operator=(const serial_exception&);
      
      string e_what_;

   public:

      serial_exception (const string & description)
      {
         ::string_stream str;
         str << "serial_exception " << description << " failed.";
         e_what_ = str;
      }
      serial_exception (const serial_exception& other) : e_what_(other.e_what_) {}
      virtual ~serial_exception() noexcept {}
      virtual const char* what () const noexcept
      {
         return e_what_.c_str();
      }
   };

   class io_exception : public ::exception
   {
      // Disable copy constructors
      io_exception& operator=(const io_exception&);
      string file_;
      int line_;
      string e_what_;
      int errno_;
   public:
      explicit io_exception (string file, int line, int errnum)
         : file_(file), line_(line), errno_(errnum)
      {
         ::string_stream str;
#if defined(_WIN32) && !defined(__MINGW32__)
         char error_str [1024];
         strerror_s(error_str, 1024, errnum);
#else
         char * error_str = strerror(errnum);
#endif
         str << "IO Exception (" << errno_ << "): " << error_str;
         set_file(file_);
         m_iLine = line_;
         e_what_ = str;
      }
      explicit io_exception (string file, int line, const ::string & description)
         : file_(file), line_(line), errno_(0)
      {
         ::string_stream str;
         str << "IO Exception: " << description;
         set_file(file_);
         m_iLine = line_;
         e_what_ = str;
      }
      virtual ~io_exception() noexcept {}
      io_exception (const io_exception& other) : line_(other.line_), e_what_(other.e_what_), errno_(other.errno_) {}

      int getErrorNumber () const
      {
         return errno_;
      }

      virtual const char* what () const noexcept
      {
         return e_what_.c_str();
      }
   };

   class port_not_opened_exception : public ::exception
   {
      // Disable copy constructors
      const port_not_opened_exception& operator=(port_not_opened_exception);
      string e_what_;
   public:
      port_not_opened_exception (const ::string & description)
      {
         ::string_stream str;
         str << "port_not_opened_exception " << description << " failed.";
         e_what_ = str;
      }
      port_not_opened_exception (const port_not_opened_exception& other) : e_what_(other.e_what_) {}
      virtual ~port_not_opened_exception() noexcept {}
      virtual const char* what () const noexcept
      {
         return e_what_.c_str();
      }
   };

   /*!
    * Structure that describes a serial device.
    */
   struct PortInfo
   {

      /*! Address of the serial port (this can be passed to the constructor of serial). */
      string port;

      /*! Human readable description of serial device if available. */
      string description;

      /*! Hardware ID (e.g. VID:PID of USB serial devices) or "n/a" if not available. */
      string hardware_id;

   };

   /* Lists the serial ports available on the system
    *
    * Returns a vector of available serial ports, each represented
    * by a serial::PortInfo data structure:
    *
    * \return vector of serial::PortInfo.
    */
   CLASS_DECL_AURA array<PortInfo>  list_ports();

} // namespace serial

#endif



