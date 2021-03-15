#include "framework.h"
#include "acme/operating_system.h"
#include "acme/platform/serial.h"
#include "acme/os/windows_common/file.h"
#include "serial_impl.h"


/* Copyright 2012 William Woodall and John Harrison */


//using serial::serial;
//using serial::time_out;
//using enum_byte_size;
//using enum_parity;
//using enum_stop_bit;
//using enum_flow_control;
//using serial::serial_exception;
//using serial::port_not_opened_exception;
//using serial::io_exception;
//

namespace serial
{


   inline wstring _prefix_port_if_needed(const wstring& wstrInput)
   {

      wstring wstr(wstrInput);

      windows_get_alternate_path(wstr);

      return wstr;

   }

   serial_impl::serial_impl(const string& port, unsigned long baudrate,
      enum_byte_size ebytesize,
      enum_parity eparity, enum_stop_bit estopbit,
      enum_flow_control eflowcontrol)
      : m_wstrPort(port), m_hFile(INVALID_HANDLE_VALUE), m_bOpened(false),
      m_ulBaudrate(baudrate), m_eparity(eparity),
      m_ebytesize(ebytesize), m_estopbit(estopbit), m_eflowcontrol(eflowcontrol)
   {
      if (m_wstrPort.empty() == false)
         open();
      m_hMutexRead = CreateMutex(nullptr, false, nullptr);
      m_hMutexWrite = CreateMutex(nullptr, false, nullptr);
   }

   serial_impl::~serial_impl()
   {
      this->close();
      CloseHandle(m_hMutexRead);
      CloseHandle(m_hMutexWrite);
   }

   void
      serial_impl::open()
   {
      if (m_wstrPort.empty())
      {
         __throw(error_invalid_argument, "Empty port is invalid.");
      }
      if (m_bOpened == true)
      {
         __throw(serial_exception("serial port already open."));
      }

      // See: https://github.com/wjwwood/serial/issues/84
      wstring port_with_prefix = _prefix_port_if_needed(m_wstrPort);
      const widechar* p_port = port_with_prefix.c_str();

      m_hFile = CreateFileW(p_port,

         GENERIC_READ | GENERIC_WRITE,
         0,
         0,
         OPEN_EXISTING,
         FILE_ATTRIBUTE_NORMAL,
         0);

      if (m_hFile == INVALID_HANDLE_VALUE)
      {

         DWORD dwLastError = ::GetLastError();

         string str;

         switch (dwLastError)
         {
         case ERROR_FILE_NOT_FOUND:
            // Use this->getPort to convert to a std::string
            str.Format("Specified port, %d, does not exist.", this->getPort());
            __throw(serial_exception(str));
         default:
            str.Format("Unknown error opening the serial port: %d", dwLastError);
            __throw(serial_exception(str));
         }
      }

      reconfigurePort();

      m_bOpened = true;

   }


   void serial_impl::reconfigurePort()
   {
      if (m_hFile == INVALID_HANDLE_VALUE)
      {
         // Can only operate on a valid file descriptor
         __throw(serial_exception("Invalid file descriptor, is the serial port open?"));
      }

      DCB dcbSerialParams = { 0 };

      __zero(dcbSerialParams);

      dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

      if (!GetCommState(m_hFile, &dcbSerialParams))
      {
         //error getting state
         __throw(serial_exception("Error getting the serial port state."));
      }

      // setup baud rate
      switch (m_ulBaudrate)
      {
#ifdef CBR_0
      case 0:
         dcbSerialParams.BaudRate = CBR_0;
         break;
#endif
#ifdef CBR_50
      case 50:
         dcbSerialParams.BaudRate = CBR_50;
         break;
#endif
#ifdef CBR_75
      case 75:
         dcbSerialParams.BaudRate = CBR_75;
         break;
#endif
#ifdef CBR_110
      case 110:
         dcbSerialParams.BaudRate = CBR_110;
         break;
#endif
#ifdef CBR_134
      case 134:
         dcbSerialParams.BaudRate = CBR_134;
         break;
#endif
#ifdef CBR_150
      case 150:
         dcbSerialParams.BaudRate = CBR_150;
         break;
#endif
#ifdef CBR_200
      case 200:
         dcbSerialParams.BaudRate = CBR_200;
         break;
#endif
#ifdef CBR_300
      case 300:
         dcbSerialParams.BaudRate = CBR_300;
         break;
#endif
#ifdef CBR_600
      case 600:
         dcbSerialParams.BaudRate = CBR_600;
         break;
#endif
#ifdef CBR_1200
      case 1200:
         dcbSerialParams.BaudRate = CBR_1200;
         break;
#endif
#ifdef CBR_1800
      case 1800:
         dcbSerialParams.BaudRate = CBR_1800;
         break;
#endif
#ifdef CBR_2400
      case 2400:
         dcbSerialParams.BaudRate = CBR_2400;
         break;
#endif
#ifdef CBR_4800
      case 4800:
         dcbSerialParams.BaudRate = CBR_4800;
         break;
#endif
#ifdef CBR_7200
      case 7200:
         dcbSerialParams.BaudRate = CBR_7200;
         break;
#endif
#ifdef CBR_9600
      case 9600:
         dcbSerialParams.BaudRate = CBR_9600;
         break;
#endif
#ifdef CBR_14400
      case 14400:
         dcbSerialParams.BaudRate = CBR_14400;
         break;
#endif
#ifdef CBR_19200
      case 19200:
         dcbSerialParams.BaudRate = CBR_19200;
         break;
#endif
#ifdef CBR_28800
      case 28800:
         dcbSerialParams.BaudRate = CBR_28800;
         break;
#endif
#ifdef CBR_57600
      case 57600:
         dcbSerialParams.BaudRate = CBR_57600;
         break;
#endif
#ifdef CBR_76800
      case 76800:
         dcbSerialParams.BaudRate = CBR_76800;
         break;
#endif
#ifdef CBR_38400
      case 38400:
         dcbSerialParams.BaudRate = CBR_38400;
         break;
#endif
#ifdef CBR_115200
      case 115200:
         dcbSerialParams.BaudRate = CBR_115200;
         break;
#endif
#ifdef CBR_128000
      case 128000:
         dcbSerialParams.BaudRate = CBR_128000;
         break;
#endif
#ifdef CBR_153600
      case 153600:
         dcbSerialParams.BaudRate = CBR_153600;
         break;
#endif
#ifdef CBR_230400
      case 230400:
         dcbSerialParams.BaudRate = CBR_230400;
         break;
#endif
#ifdef CBR_256000
      case 256000:
         dcbSerialParams.BaudRate = CBR_256000;
         break;
#endif
#ifdef CBR_460800
      case 460800:
         dcbSerialParams.BaudRate = CBR_460800;
         break;
#endif
#ifdef CBR_921600
      case 921600:
         dcbSerialParams.BaudRate = CBR_921600;
         break;
#endif
      default:
         // Try to blindly assign it
         dcbSerialParams.BaudRate = m_ulBaudrate;
      }

      // setup char len
      if (m_ebytesize == e_byte_size_eight)
         dcbSerialParams.ByteSize = 8;
      else if (m_ebytesize == e_byte_size_seven)
         dcbSerialParams.ByteSize = 7;
      else if (m_ebytesize == e_byte_size_six)
         dcbSerialParams.ByteSize = 6;
      else if (m_ebytesize == e_byte_size_five)
         dcbSerialParams.ByteSize = 5;
      else
         __throw(error_invalid_argument, "invalid char len");

         // setup estopbit
         if (m_estopbit == e_stop_bit_one)
            dcbSerialParams.StopBits = ONESTOPBIT;
         else if (m_estopbit == e_stop_bit_one_point_five)
            dcbSerialParams.StopBits = ONE5STOPBITS;
         else if (m_estopbit == e_stop_bit_two)
            dcbSerialParams.StopBits = TWOSTOPBITS;
         else
            __throw(error_invalid_argument, "invalid stop bit");

            // setup eparity
            if (m_eparity == e_parity_none)
            {
               dcbSerialParams.Parity = NOPARITY;
            }
            else if (m_eparity == e_parity_even)
            {
               dcbSerialParams.Parity = EVENPARITY;
            }
            else if (m_eparity == e_parity_odd)
            {
               dcbSerialParams.Parity = ODDPARITY;
            }
            else if (m_eparity == e_parity_mark)
            {
               dcbSerialParams.Parity = MARKPARITY;
            }
            else if (m_eparity == e_parity_space)
            {
               dcbSerialParams.Parity = SPACEPARITY;
            }
            else
            {
               __throw(error_invalid_argument, "invalid eparity");
            }

            // setup eflowcontrol
            if (m_eflowcontrol == e_flow_control_none)
            {
               dcbSerialParams.fOutxCtsFlow = false;
               dcbSerialParams.fRtsControl = 0x00;
               dcbSerialParams.fOutX = false;
               dcbSerialParams.fInX = false;
            }
            if (m_eflowcontrol == e_flow_control_software)
            {
               dcbSerialParams.fOutxCtsFlow = false;
               dcbSerialParams.fRtsControl = 0x00;
               dcbSerialParams.fOutX = true;
               dcbSerialParams.fInX = true;
            }
            if (m_eflowcontrol == e_flow_control_hardware)
            {
               dcbSerialParams.fOutxCtsFlow = true;
               dcbSerialParams.fRtsControl = 0x03;
               dcbSerialParams.fOutX = false;
               dcbSerialParams.fInX = false;
            }

            // activate settings
            if (!SetCommState(m_hFile, &dcbSerialParams))
            {
               CloseHandle(m_hFile);
               __throw(serial_exception("Error setting serial port settings."));
            }

            // Setup timeouts
            COMMTIMEOUTS timeouts = { 0 };
            timeouts.ReadIntervalTimeout = (DWORD)m_timeout.m_millisInterByteTimeout.m_i;
            timeouts.ReadTotalTimeoutConstant = (DWORD)m_timeout.m_millisReadTimeoutConstant.m_i;
            timeouts.ReadTotalTimeoutMultiplier = m_timeout.m_uReadTimeoutMultiplier;
            timeouts.WriteTotalTimeoutConstant = (DWORD)m_timeout.m_millisWriteTimeoutConstant.m_i;
            timeouts.WriteTotalTimeoutMultiplier = m_timeout.m_uWriteTimeoutMultiplier;
            if (!SetCommTimeouts(m_hFile, &timeouts))
            {
               __throw(serial_exception("Error setting timeouts."));
            }


            // Compensate for the e_stop_bit_one_point_five enum being equal to int 3,
            // and not 1.5.
            // Update byte_time_ based on the new settings.

            if (m_estopbit == e_stop_bit_one_point_five)
            {

               m_uiByteTimeNs = (u32)(((((u64)1000LL * 1000LL * 1000LL) * (1 + m_ebytesize + m_eparity)) + (1500LL * 1000LL * 1000LL)) / ((u64)(m_ulBaudrate)));

            }
            else
            {

               m_uiByteTimeNs = (u32)((((u64)1000LL * 1000LL * 1000LL) * (1 + m_ebytesize + m_eparity + m_estopbit)) / ((u64)(m_ulBaudrate)));

            }

   }


   void
      serial_impl::close()
   {
      output_debug_string("\nSerial::serialimpl::close");
      if (m_bOpened == true)
      {
         output_debug_string("\nSerial::serialimpl::close open");
         if (m_hFile != INVALID_HANDLE_VALUE)
         {
            output_debug_string("\nSerial::serialimpl::close valid");
            int ret;
            ret = CloseHandle(m_hFile);
            if (ret == 0)
            {
               output_debug_string("\nSerial::serialimpl::close failed");
               string str;

               DWORD dwLastError = ::GetLastError();

               str.Format("Error while closing serial port: %d", dwLastError);
               __throw(error_io, str);
            }
            else
            {
               output_debug_string("\nSerial::serialimpl::close succesfully closed");
               m_hFile = INVALID_HANDLE_VALUE;
            }
         }
         m_bOpened = false;
      }

   }


   bool serial_impl::isOpen() const
   {

      return m_bOpened;

   }


   size_t serial_impl::available()
   {

      if (!m_bOpened)
      {

         return 0;

      }

      COMSTAT cs;

      if (!ClearCommError(m_hFile, nullptr, &cs))
      {

         string str;

         DWORD dwLastError = ::GetLastError();

         str.Format("Error while checking status of the serial port: %d", dwLastError);

         __throw(error_io, str);

      }

      return static_cast<size_t>(cs.cbInQue);

   }


   bool serial_impl::waitReadable(::millis /*timeout*/)
   {

      __throw(error_io, "waitReadable is not implemented on Windows.");

      return false;

   }


   void serial_impl::waitByteTimes(size_t count)
   {

      //__throw (io_exception, "waitByteTimes is not implemented on Windows.");
      duration dur;
      dur.m_nanos = count * m_uiByteTimeNs;
      dur.normalize();
      sleep(dur);

   }


   size_t serial_impl::read(u8* buf, size_t size)
   {

      if (!m_bOpened)
      {

         __throw(port_not_opened_exception("serial::read"));

      }

      DWORD bytes_read;

      if (!ReadFile(m_hFile, buf, static_cast<::u32>(size), &bytes_read, nullptr))
      {

         string ss;

         DWORD dwLastError = ::GetLastError();

         ss.Format("Error while reading from the serial port: %d", dwLastError);

         __throw(error_io, ss);

      }

      return (size_t)(bytes_read);

   }


   size_t serial_impl::write(const u8* data, size_t length)
   {

      if (m_bOpened == false)
      {

         __throw(port_not_opened_exception("serial::write"));

      }

      DWORD bytes_written;

      if (!WriteFile(m_hFile, data, static_cast<::u32>(length), &bytes_written, nullptr))
      {

         string str;

         DWORD dwLastError = ::GetLastError();

         str.Format("Error while writing to the serial port: %d", dwLastError);

         __throw(error_io, str);

      }

      return (size_t)(bytes_written);

   }


   size_t serial_impl::readline(string& buffer, size_t size, string eol)
   {

      scoped_read_lock lock(this);

      size_t eol_len = (size_t)eol.length();

      u8* buffer_ = static_cast <u8*> (alloca(size * sizeof(u8)));

      auto tickStart = ::millis::now();

      size_t read_so_far = 0;

      while (true)
      {

         size_t bytes_read = read(buffer_ + read_so_far, 1);

         read_so_far += bytes_read;

         if (bytes_read == 0)
         {

            if (tickStart.elapsed() > m_timeout.m_millisReadTimeoutConstant)
            {

               break;

            }

            // time_out occured on reading 1 byte
            sleep(maximum(100_ms, m_timeout.m_millisReadTimeoutConstant / 10));

            if (!::task_get_run())
            {

               break;

            }

            continue;

         }

         auto tickStart = ::millis::now();

         if (string(reinterpret_cast<const char*> (buffer_ + read_so_far - eol_len), eol_len) == eol)
         {

            break; // EOL found

         }

         if (read_so_far == size)
         {

            break; // Reached the maximum read length

         }

      }

      buffer.append(reinterpret_cast<const char*> (buffer_), read_so_far);

      return read_so_far;

   }


   void serial_impl::setPort(const string& port)
   {

      m_wstrPort = wstring(port);

   }


   string serial_impl::getPort() const
   {

      return string(m_wstrPort);

   }


   void serial_impl::set_timeout(timeout& timeout)
   {
      m_timeout = timeout;
      if (m_bOpened)
      {
         reconfigurePort();
      }
   }

   timeout
      serial_impl::getTimeout() const
   {
      return m_timeout;
   }

   void
      serial_impl::setBaudrate(unsigned long baudrate)
   {
      m_ulBaudrate = baudrate;
      if (m_bOpened)
      {
         reconfigurePort();
      }
   }

   unsigned long serial_impl::getBaudrate() const
   {

      return m_ulBaudrate;

   }


   void serial_impl::setBytesize(enum_byte_size ebytesize)
   {
   
      m_ebytesize = ebytesize;

      if (m_bOpened)
      {

         reconfigurePort();

      }

   }


   enum_byte_size serial_impl::getBytesize() const
   {
      
      return m_ebytesize;

   }


   void serial_impl::setParity(enum_parity eparity)
   {

      m_eparity = eparity;

      if (m_bOpened)
      {
         reconfigurePort();
      }
   }

   enum_parity
      serial_impl::getParity() const
   {
      return m_eparity;
   }

   void
      serial_impl::setStopbits(enum_stop_bit estopbit)
   {
      m_estopbit = estopbit;
      if (m_bOpened)
      {
         reconfigurePort();
      }
   }

   enum_stop_bit
      serial_impl::getStopbits() const
   {
      return m_estopbit;
   }


   void serial_impl::setFlowcontrol(enum_flow_control eflowcontrol)
   {
      m_eflowcontrol = eflowcontrol;
      if (m_bOpened)
      {
         reconfigurePort();
      }
   }

   enum_flow_control
      serial_impl::getFlowcontrol() const
   {
      return m_eflowcontrol;
   }

   void
      serial_impl::flush()
   {
      if (m_bOpened == false)
      {
         __throw(port_not_opened_exception("serial::flush"));
      }
      FlushFileBuffers(m_hFile);
   }

   void
      serial_impl::flushInput()
   {
      __throw(error_io, "flushInput is not supported on Windows.");
   }

   void
      serial_impl::flushOutput()
   {
      __throw(error_io, "flushOutput is not supported on Windows.");
   }

   void
      serial_impl::sendBreak(int /*duration*/)
   {
      __throw(error_io, "sendBreak is not supported on Windows.");
   }

   void
      serial_impl::setBreak(bool level)
   {
      if (m_bOpened == false)
      {
         __throw(port_not_opened_exception("serial::setBreak"));
      }
      if (level)
      {
         EscapeCommFunction(m_hFile, SETBREAK);
      }
      else
      {
         EscapeCommFunction(m_hFile, CLRBREAK);
      }
   }

   void
      serial_impl::setRTS(bool level)
   {
      if (m_bOpened == false)
      {
         __throw(port_not_opened_exception("serial::setRTS"));
      }
      if (level)
      {
         EscapeCommFunction(m_hFile, SETRTS);
      }
      else
      {
         EscapeCommFunction(m_hFile, CLRRTS);
      }
   }

   void
      serial_impl::setDTR(bool level)
   {
      if (m_bOpened == false)
      {
         __throw(port_not_opened_exception("serial::setDTR"));
      }
      if (level)
      {
         EscapeCommFunction(m_hFile, SETDTR);
      }
      else
      {
         EscapeCommFunction(m_hFile, CLRDTR);
      }
   }

   bool
      serial_impl::waitForChange()
   {
      if (m_bOpened == false)
      {
         __throw(port_not_opened_exception("serial::waitForChange"));
      }

      DWORD dwCommEvent;

      if (!SetCommMask(m_hFile, EV_CTS | EV_DSR | EV_RING | EV_RLSD))
      {
         // Error setting communications mask
         return false;
      }

      if (!WaitCommEvent(m_hFile, &dwCommEvent, nullptr))
      {
         // An error occurred waiting for the event.
         return false;
      }
      else
      {
         // Event has occurred.
         return true;
      }
   }

   bool
      serial_impl::getCTS()
   {
      if (m_bOpened == false)
      {
         __throw(port_not_opened_exception("serial::getCTS"));
      }
      DWORD dwModemStatus;
      if (!GetCommModemStatus(m_hFile, &dwModemStatus))
      {
         __throw(error_io, "Error getting the status of the CTS line.");
      }

      return (MS_CTS_ON & dwModemStatus) != 0;
   }

   bool
      serial_impl::getDSR()
   {
      if (m_bOpened == false)
      {
         __throw(port_not_opened_exception("serial::getDSR"));
      }

      DWORD dwModemStatus;

      if (!GetCommModemStatus(m_hFile, &dwModemStatus))
      {
         __throw(error_io, "Error getting the status of the DSR line.");
      }

      return (MS_DSR_ON & dwModemStatus) != 0;
   }

   bool
      serial_impl::getRI()
   {
      if (m_bOpened == false)
      {
         __throw(port_not_opened_exception("serial::getRI"));
      }

      DWORD dwModemStatus;

      if (!GetCommModemStatus(m_hFile, &dwModemStatus))
      {
         __throw(error_io, "Error getting the status of the RI line.");
      }

      return (MS_RING_ON & dwModemStatus) != 0;
   }

   bool
      serial_impl::getCD()
   {
      if (m_bOpened == false)
      {
         __throw(port_not_opened_exception("serial::getCD"));
      }

      DWORD dwModemStatus;

      if (!GetCommModemStatus(m_hFile, &dwModemStatus))
      {
         // Error in GetCommModemStatus;
         __throw(error_io, "Error getting the status of the CD line.");
      }

      return (MS_RLSD_ON & dwModemStatus) != 0;
   }

   void
      serial_impl::readLock()
   {
      if (WaitForSingleObject(m_hMutexRead, U32_INFINITE_TIMEOUT) != WAIT_OBJECT_0)
      {
         __throw(error_io, "Error claiming read ::mutex.");
      }
   }

   void
      serial_impl::readUnlock()
   {
      if (!ReleaseMutex(m_hMutexRead))
      {
         __throw(error_io, "Error releasing read ::mutex.");
      }
   }

   void
      serial_impl::writeLock()
   {
      if (WaitForSingleObject(m_hMutexWrite, U32_INFINITE_TIMEOUT) != WAIT_OBJECT_0)
      {
         __throw(error_io, "Error claiming write ::mutex.");
      }
   }

   void
      serial_impl::writeUnlock()
   {
      if (!ReleaseMutex(m_hMutexWrite))
      {
         __throw(error_io, "Error releasing write ::mutex.");
      }
   }



} // namespace serial

