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
 * Software is furnished to do so, topic to the following conditions:
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
#pragma once


#include "acme/primitive/primitive/particle.h"
////#include "acme/exception/exception.h"


//#include <limits>
//#include <vector>
//#include <string>
//#include <cstring>
//#include <sstream>
//#include <exception>
//#include <stdexcept>
//#include <serial/v8stdint.h>

#define THROW(exceptionClass, message) throw ::exception( exceptionClass(__FILE__, __LINE__, (message) ) )

namespace serial
{


   /*!
    * Enumeration defines the possible ebytesizes for the serial port.
    */
   enum enum_byte_size
   {
      e_byte_size_five = 5,
      e_byte_size_six = 6,
      e_byte_size_seven = 7,
      e_byte_size_eight = 8
   };

   /*!
    * Enumeration defines the possible eparity types for the serial port.
    */
   enum enum_parity
   {
      e_parity_none = 0,
      e_parity_odd = 1,
      e_parity_even = 2,
      e_parity_mark = 3,
      e_parity_space = 4
   };

   /*!
    * Enumeration defines the possible stopbit types for the serial port.
    */
   enum enum_stop_bit
   {
      e_stop_bit_one = 1,
      e_stop_bit_two = 2,
      e_stop_bit_one_point_five
   };

   /*!
    * Enumeration defines the possible eflowcontrol types for the serial port.
    */
   enum enum_flow_control
   {
      e_flow_control_none = 0,
      e_flow_control_software,
      e_flow_control_hardware
   };

   /*!
    * Structure for setting the timeout of the serial port, times are
    * in ::times.
    *
    * In order to disable the interbyte timeout, set it to timeout::maximum().
    */
   struct CLASS_DECL_ACME timeout
   {
#ifdef maximum
# undef maximum
#endif
      static u32 maximum()
      {
         return numeric_info<u32>::maximum();
      }
      /*!
       * Convenience function to generate timeout structs using a
       * single absolute timeout.
       *
       * \lparam timeout A long that defines the time in ::times until a
       * timeout occurs after a call to read or write is made.
       *
       * \return timeout struct that represents this simple timeout provided.
       */
      virtual timeout simpleTimeout(const class time & time);

      /*! Number of ::times between bytes received to timeout on. */
      class ::time m_timeInterByteTimeout;
      /*! A constant number of ::times to wait after method read. */
      class ::time m_timeReadTimeoutConstant;
      /*! A multiplier against the number of requested bytes to wait after
       *  method read.
       */
      u32 m_uReadTimeoutMultiplier;
      /*! A constant number of ::times to wait after method write. */
      class ::time m_timeWriteTimeoutConstant;
      /*! A multiplier against the number of requested bytes to wait after
       *  method write.
       */
      u32 m_uWriteTimeoutMultiplier;


      explicit timeout (const class time & timeInterByteTimeout=0_ms,
         const class time & timeReadTimeoutConstant=0_ms,
                        u32 uReadTimeoutMultiplier=0,
         const class time & timeWriteTimeoutConstant=0_ms,
                        u32 uWriteTimeoutMultiplier=0)
         : m_timeInterByteTimeout(timeInterByteTimeout),
           m_timeReadTimeoutConstant(timeReadTimeoutConstant),
           m_uReadTimeoutMultiplier(uReadTimeoutMultiplier),
           m_timeWriteTimeoutConstant(timeWriteTimeoutConstant),
           m_uWriteTimeoutMultiplier(uWriteTimeoutMultiplier)
      {}
      timeout(std::nullptr_t) : timeout() { }
   };

   /*!
    * Class that provides a portable serial port interface.
    */
   class CLASS_DECL_ACME serial :
      virtual public particle
   {
   public:



      ///__creatable_from_library(acme_directory, ::acme_directory, "acme_windows_common");


      /*!
       * Creates a serial matter and opens the port if a port is specified,
       * otherwise it remains closed until serial::serial::open is called.
       *
       * \lparam port A string containing the address of the serial port,
       *        which would be something like 'COM1' on Windows and '/dev/ttyS0'
       *        on Linux.
       *
       * \lparam baudrate An unsigned 32-bit integer that represents the baudrate
       *
       * \lparam timeout A serial::timeout struct that defines the timeout
       * conditions for the serial port. \see serial::timeout
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
       * \throw ::exception( serial::port_not_opened_exception
       * \throw ::exception( serial::io_exception
       * \throw ::exception( invalid_argument
       */
      serial ();

      /*! Destructor */
      virtual ~serial ();


      virtual void initialize_serial(
         const string &port = "",
         u32 baudrate = 9600,
         struct timeout timeout = nullptr,
         enum_byte_size ebytesize = e_byte_size_eight,
         enum_parity eparity = e_parity_none,
         enum_stop_bit estopbit = e_stop_bit_one,
         enum_flow_control eflowcontrol = e_flow_control_none);

      /*!
       * Opens the serial port as long as the port is set and the port isn't
       * already open.
       *
       * If the port is provided to the constructor then an explicit call to open
       * is not needed.
       *
       * \see serial::serial
       *
       * \throw ::exception( invalid_argument
       * \throw ::exception( serial::serial_exception
       * \throw ::exception( serial::io_exception
       */
      virtual void
      open ();

      /*! Gets the open status of the serial port.
       *
       * \return Returns true if the port is open, false otherwise.
       */
      virtual bool
      isOpen () const;

      /*! Closes the serial port. */
      virtual void close ();

      //virtual void readLock();
      //virtual void readUnlock();
      //virtual void writeLock();
      //virtual void writeUnlock();

      virtual ::particle * read_synchronization();
      virtual ::particle * write_synchronization();

      /*! Return the number of characters in the buffer. */
      virtual size_t
      available ();

      /*! Block until there is serial data to read or read_timeout_constant
       * number of ::times have elapsed. The return value is true when
       * the function exits with the port in a readable state, false otherwise
       * (due to timeout or select interruption). */
      virtual bool
      waitReadable ();

      /*! Block for a period of time corresponding to the transmission time of
       * count characters at present serial settings. This may be used in con-
       * junction with waitReadable to read larger blocks of data from the
       * port. */
      virtual void
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
       *      ::times elapsed between receiving bytes from the serial port
       *      exceeded the inter byte timeout.
       *    * The total timeout expired, which is calculated by multiplying the
       *      read timeout multiplier by the number of requested bytes and then
       *      added to the read timeout constant.  If that total number of
       *      ::times elapses after the initial call to read a timeout will
       *      occur.
       *  * An exception occurred, in this case an actual exception will be thrown.
       *
       * \lparam buffer An u8 array of at least the requested size.
       * \lparam size_i32 A size_t defining how many bytes to be read.
       *
       * \return A size_t representing the number of bytes read as a result of the
       *         call to read.
       *
       * \throw ::exception( serial::port_not_opened_exception
       * \throw ::exception( serial::serial_exception
       */
      virtual size_t
      read (u8 *buffer, size_t size);

      /*! Read a given amount of bytes from the serial port into a give buffer.
       *
       * \lparam buffer A matter to a vector of u8.
       * \lparam size_i32 A size_t defining how many bytes to be read.
       *
       * \return A size_t representing the number of bytes read as a result of the
       *         call to read.
       *
       * \throw ::exception( serial::port_not_opened_exception
       * \throw ::exception( serial::serial_exception
       */
      virtual size_t
      read (memory &buffer, size_t size = 1);

      /*! Read a given amount of bytes from the serial port into a give buffer.
       *
       * \lparam buffer A matter to a string.
       * \lparam size_i32 A size_t defining how many bytes to be read.
       *
       * \return A size_t representing the number of bytes read as a result of the
       *         call to read.
       *
       * \throw ::exception( serial::port_not_opened_exception
       * \throw ::exception( serial::serial_exception
       */
      virtual size_t
      read (string &buffer, size_t size = 1);

      /*! Read a given amount of bytes from the serial port and return a string
       *  containing the data.
       *
       * \lparam size_i32 A size_t defining how many bytes to be read.
       *
       * \return A string containing the data read from the port.
       *
       * \throw ::exception( serial::port_not_opened_exception
       * \throw ::exception( serial::serial_exception
       */
      virtual string
      read (size_t size = 1);

      /*! Reads in a line or until a given delimiter has been processed.
       *
       * Reads from the serial port until a single line has been read.
       *
       * \lparam buffer A string matter used to store the data.
       * \lparam size_i32 A maximum length of a line, defaults to 65536 (2^16)
       * \lparam eol A string to match against for the EOL.
       *
       * \return A size_t representing the number of bytes read.
       *
       * \throw ::exception( serial::port_not_opened_exception
       * \throw ::exception( serial::serial_exception
       */
      virtual size_t
      readline (string &buffer, size_t size = 65536, string eol = "\n");

      /*! Reads in a line or until a given delimiter has been processed.
       *
       * Reads from the serial port until a single line has been read.
       *
       * \lparam size_i32 A maximum length of a line, defaults to 65536 (2^16)
       * \lparam eol A string to match against for the EOL.
       *
       * \return A string containing the line.
       *
       * \throw ::exception( serial::port_not_opened_exception
       * \throw ::exception( serial::serial_exception
       */
      virtual string
      readline (size_t size = 65536, string eol = "\n");

      /*! Reads in multiple lines until the serial port times out.
       *
       * This requires a timeout > 0 before it can be run. It will read until a
       * timeout occurs and return a list of strings.
       *
       * \lparam size_i32 A maximum length of combined lines, defaults to 65536 (2^16)
       *
       * \lparam eol A string to match against for the EOL.
       *
       * \return A vector<string> containing the lines.
       *
       * \throw ::exception( serial::port_not_opened_exception
       * \throw ::exception( serial::serial_exception
       */
      virtual string_array
      readlines (size_t size = 65536, string eol = "\n");

      /*! Write a string to the serial port.
       *
       * \lparam data A const matter containing the data to be written
       * to the serial port.
       *
       * \lparam size_i32 A size_t that indicates how many bytes should be written from
       * the given data buffer.
       *
       * \return A size_t representing the number of bytes actually written to
       * the serial port.
       *
       * \throw ::exception( serial::port_not_opened_exception
       * \throw ::exception( serial::serial_exception
       * \throw ::exception( serial::io_exception
       */
      virtual size_t
      write (const u8 *data, size_t size);

      /*! Write a string to the serial port.
       *
       * \lparam data A const matter containing the data to be written
       * to the serial port.
       *
       * \return A size_t representing the number of bytes actually written to
       * the serial port.
       *
       * \throw ::exception( serial::port_not_opened_exception
       * \throw ::exception( serial::serial_exception
       * \throw ::exception( serial::io_exception
       */
      virtual size_t
      write (const memory &data);

      /*! Write a string to the serial port.
       *
       * \lparam data A const matter containing the data to be written
       * to the serial port.
       *
       * \return A size_t representing the number of bytes actually written to
       * the serial port.
       *
       * \throw ::exception( serial::port_not_opened_exception
       * \throw ::exception( serial::serial_exception
       * \throw ::exception( serial::io_exception
       */
      virtual size_t
      write (const string &data);

      /*! Sets the serial port identifier.
       *
       * \lparam port A const string matter containing the address of the
       * serial port, which would be something like 'COM1' on Windows and
       * '/dev/ttyS0' on Linux.
       *
       * \throw ::exception( invalid_argument
       */
      virtual void setPort (const string &port);


      virtual void _setPort(const string& port);

      /*! Gets the serial port identifier.
       *
       * \see serial::setPort
       *
       * \throw ::exception( invalid_argument
       */
      virtual string
      getPort () const;

      /*! Sets the timeout for reads and writes using the timeout struct.
       *
       * There are two timeout conditions described here:
       *  * The inter byte timeout:
       *    * The inter_byte_timeout component of serial::timeout defines the
       *      maximum amount of time, in ::times, between receiving bytes on
       *      the serial port that can pass before a timeout occurs.  Setting this
       *      to zero will prevent inter byte timeouts from occurring.
       *  * Total time timeout:
       *    * The constant and multiplier component of this timeout condition,
       *      for both read and write, are defined in serial::timeout.  This
       *      timeout occurs if the total time since the read or write call was
       *      made exceeds the specified time in ::times.
       *    * The limit is defined by multiplying the multiplier component by the
       *      number of requested bytes and adding that product to the constant
       *      component.  In this way if you want a read call, for example, to
       *      timeout after exactly one second regardless of the number of bytes
       *      you asked for then set the read_timeout_constant component of
       *      serial::timeout to 1000 and the read_timeout_multiplier to zero.
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
       * \lparam timeout A serial::timeout struct containing the inter byte
       * timeout, and the read and write timeout constants and multipliers.
       *
       * \see serial::timeout
       */
      virtual void set_timeout (const struct timeout &timeout);
      /*! Sets the timeout for reads and writes. */
      virtual void set_timeout(const class ::time & inter_byte_timeout, const class ::time & read_timeout_constant,
                  u32 read_timeout_multiplier, const class ::time & write_timeout_constant,
                  u32 write_timeout_multiplier)
      {
         struct timeout timeout(inter_byte_timeout, read_timeout_constant,
                         read_timeout_multiplier, write_timeout_constant,
                         write_timeout_multiplier);
         return set_timeout(timeout);
      }

      /*! Gets the timeout for reads in seconds.
       *
       * \return A timeout struct containing the inter_byte_timeout, and read
       * and write timeout constants and multipliers.
       *
       * \see serial::setTimeout
       */
      virtual struct timeout getTimeout () const;

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
       * \throw ::exception( invalid_argument
       */
      virtual void
      setBaudrate (u32 baudrate);

      /*! Gets the baudrate for the serial port.
       *
       * \return An integer that sets the baud rate for the serial port.
       *
       * \see serial::setBaudrate
       *
       * \throw ::exception( invalid_argument
       */
      virtual u32
      getBaudrate () const;

      /*! Sets the ebytesize for the serial port.
       *
       * \lparam ebytesize Size of each byte in the serial transmission of data,
       * default is e_byte_size_eight, possible values are: fivebits, sixbits, sevenbits,
       * e_byte_size_eight
       *
       * \throw ::exception( invalid_argument
       */
      virtual void
      setBytesize (enum_byte_size ebytesize);

      /*! Gets the ebytesize for the serial port.
       *
       * \see serial::setBytesize
       *
       * \throw ::exception( invalid_argument
       */
      virtual enum_byte_size
      getBytesize () const;

      /*! Sets the eparity for the serial port.
       *
       * \lparam eparity Method of eparity, default is e_parity_none, possible values
       * are: e_parity_none, eparity_odd, eparity_even
       *
       * \throw ::exception( invalid_argument
       */
      virtual void
      setParity (enum_parity eparity);

      /*! Gets the eparity for the serial port.
       *
       * \see serial::setParity
       *
       * \throw ::exception( invalid_argument
       */
      virtual enum_parity
      getParity () const;

      /*! Sets the estopbit for the serial port.
       *
       * \lparam estopbit Number of stop bits used, default is e_stop_bit_one,
       * possible values are: e_stop_bit_one, e_stop_bit_one_point_five, estopbit_two
       *
       * \throw ::exception( invalid_argument
       */
      virtual void
      setStopbits (enum_stop_bit estopbit);

      /*! Gets the estopbit for the serial port.
       *
       * \see serial::setStopbits
       *
       * \throw ::exception( invalid_argument
       */
      virtual enum_stop_bit
      getStopbits () const;

      /*! Sets the flow control for the serial port.
       *
       * \lparam eflowcontrol Type of eflowcontrol used, default is e_flow_control_none,
       * possible values are: e_flow_control_none, e_flow_control_software,
       * e_flow_control_hardware
       *
       * \throw ::exception( invalid_argument
       */
      virtual void
      setFlowcontrol (enum_flow_control eflowcontrol);

      /*! Gets the flow control for the serial port.
       *
       * \see serial::setFlowcontrol
       *
       * \throw ::exception( invalid_argument
       */
      virtual enum_flow_control
      getFlowcontrol () const;

      /*! Flush the input and output buffers */
      virtual void
      flush ();

      /*! Flush only the input buffer */
      virtual void
      flushInput ();

      /*! Flush only the output buffer */
      virtual void
      flushOutput ();

      /*! Sends the RS-232 break signal.  See tcsendbreak(3). */
      virtual void
      sendBreak (int time);

      /*! Set the break condition to a given level.  Defaults to true. */
      virtual void
      setBreak (bool level = true);

      /*! Set the RTS handshaking line to the given level.  Defaults to true. */
      virtual void
      setRTS (bool level = true);

      /*! Set the DTR handshaking line to the given level.  Defaults to true. */
      virtual void
      setDTR (bool level = true);

      /*!
       * Blocks until CTS, DSR, RI, CD changes or something interrupts it.
       *
       * Can throw ::exception( an exception if an error occurs while waiting.
       * You can check the status of CTS, DSR, RI, and CD once this returns.
       * Uses TIOCMIWAIT via ioctl if available (mostly only on Linux) with a
       * resolution of less than +-1ms and as good as +-0.2ms.  Otherwise a
       * polling method is used which can give +-2ms.
       *
       * \return Returns true if one of the lines changed, false if something else
       * occurred.
       *
       * \throw ::exception( serial_exception
       */
      virtual bool
      waitForChange ();

      /*! Returns the current status of the CTS line. */
      virtual bool
      getCTS ();

      /*! Returns the current status of the DSR line. */
      virtual bool
      getDSR ();

      /*! Returns the current status of the RI line. */
      virtual bool
      getRI ();

      /*! Returns the current status of the CD line. */
      virtual bool getCD ();

      // Read common function
      virtual size_t _read(u8 *buffer, size_t size);
      
      // Write common function
      virtual size_t _write(const u8 *data, size_t length);


      virtual void _flush();


      virtual void _flushOutput();

      virtual void _flushInput();


   };



   //::exception exception(const string& description);
   //::exception io_exception(string file, int line, int errnum);
   //::exception io_exception_descripton(string file, int line, const char* description);
   //::exception port_opened_exception_descripton(string file, int line, const char* description);

   class serial_exception : public ::exception
   {
   //   
   //   // Disable copy constructors
   //   serial_exception& operator=(const serial_exception&);
   //   
   //   string e_what_;

   public:

      serial_exception(const string & description) :
         ::exception(error_serial)
      {
//         ::string_stream str;
  //       str << "serial_exception " << description << " failed.";
    //     e_what_ = str;
      }
   //   serial_exception (const serial_exception& other) : e_what_(other.e_what_) {}
   //   virtual ~serial_exception() noexcept {}
   //   virtual const char* what () const noexcept
   //   {
   //      return e_what_.c_str();
   //   }
   };

   class io_exception : public ::exception
   {
//      // Disable copy constructors
//      io_exception& operator=(const io_exception&);
//      string file_;
//      int line_;
//      string e_what_;
//      int errno_;
   public:
      explicit io_exception(string file, int line, int errnum) :
         ::exception(error_serial_io)
      {
         //: file_(file), line_(line), errno_(errnum)
//            ::string_stream str;
//#if defined(_WIN32) && !defined(__MINGW32__)
//         char error_str [1024];
//         strerror_s(error_str, 1024, errnum);
//#else
//         char * error_str = strerror(errnum);
//#endif
//         str << "IO Exception (" << errno_ << "): " << error_str;
//         set_file(file_);
//         m_iLine = line_;
//         e_what_ = str;
      }

      explicit io_exception(string file, int line, const char * description) :
         ::exception(error_serial_io)
      {
//         ::string_stream str;
//         str << "IO Exception: " << description;
//         set_file(file_);
//         m_iLine = line_;
//         e_what_ = str;
      }
//      virtual ~io_exception() noexcept {}
//      io_exception (const io_exception& other) : line_(other.line_), e_what_(other.e_what_), errno_(other.errno_) {}
//
//      int getErrorNumber () const
//      {
//         return errno_;
//      }
//
//      virtual const char* what () const noexcept
//      {
//         return e_what_.c_str();
//      }
   };

   class port_not_opened_exception : public ::exception
   {
      // Disable copy constructors
   //   const port_not_opened_exception& operator=(port_not_opened_exception);
   //   string e_what_;
   public:
      port_not_opened_exception (const char * description)
      {
         //::string_stream str;
         //str << "port_not_opened_exception " << description << " failed.";
         //e_what_ = str;
      }
   //   port_not_opened_exception (const port_not_opened_exception& other) : e_what_(other.e_what_) {}
   //   virtual ~port_not_opened_exception() noexcept {}
   //   virtual const char* what () const noexcept
   //   {
   //      return e_what_.c_str();
   //   }
   };


//   /* Lists the serial ports available on the system
//    *
//    * Returns a vector of available serial ports, each represented
//    * by a serial::port_info data structure:
//    *
//    * \return vector of serial::port_info.
//    */
//   CLASS_DECL_ACME array<port_info>  list_ports();



   //class scoped_read_lock
   //{
   //public:


   //   serial * m_pserial;


   //   scoped_read_lock(serial * pserial) : 
   //      m_pserial(pserial)
   //   {

   //      m_pserial->readLock();

   //   }


   //   ~scoped_read_lock()
   //   {

   //      m_pserial->readUnlock();

   //   }

   //};


   //class scoped_write_lock
   //{
   //public:

   //   serial* m_pserial;


   //   scoped_write_lock(serial * pserial) :
   //      m_pserial(pserial)
   //   {
   //      
   //      m_pserial->writeLock();

   //   }


   //   ~scoped_write_lock()
   //   {

   //      m_pserial->writeUnlock();

   //   }

   //};


} // namespace serial



