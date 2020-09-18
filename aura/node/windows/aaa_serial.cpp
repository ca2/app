#include "framework.h"
#include "aura/platform/serial.h"
#include "serial.h"
#include "aura/platform/serial_impl.h"
#include "aura/os/windows_common/file.h"


/* Copyright 2012 William Woodall and John Harrison */


using serial::Serial;
using serial::Timeout;
using serial::bytesize_t;
using serial::parity_t;
using serial::stopbits_t;
using serial::flowcontrol_t;
using serial::SerialException;
using serial::PortNotOpenedException;
using serial::IOException;

inline wstring _prefix_port_if_needed(const wstring & wstrInput)
{

   wstring wstr(wstrInput);

   windows_get_alternate_path(wstr);
   
   return wstr;

}

Serial::SerialImpl::SerialImpl (::object * pobject, const string &port, unsigned long baudrate,
                                bytesize_t bytesize,
                                parity_t parity, stopbits_t stopbits,
                                flowcontrol_t flowcontrol)
   : ::object(pobject), m_wstrPort (port), m_hFile (INVALID_HANDLE_VALUE), m_bOpened (false),
     m_ulBaudrate (baudrate), m_parity (parity),
     m_bytesize (bytesize), m_stopbits (stopbits), m_flowcontrol (flowcontrol)
{
   if (m_wstrPort.empty () == false)
      open ();
   m_hMutexRead = CreateMutex(nullptr, false, nullptr);
   m_hMutexWrite = CreateMutex(nullptr, false, nullptr);
}

Serial::SerialImpl::~SerialImpl ()
{
   this->close();
   CloseHandle(m_hMutexRead);
   CloseHandle(m_hMutexWrite);
}

void
Serial::SerialImpl::open ()
{
   if (m_wstrPort.empty ())
   {
      __throw(invalid_argument_exception("Empty port is invalid."));
   }
   if (m_bOpened == true)
   {
      __throw(SerialException ("Serial port already open."));
   }

   // See: https://github.com/wjwwood/serial/issues/84
   wstring port_with_prefix = _prefix_port_if_needed(m_wstrPort);
   LPCWSTR p_port = port_with_prefix.c_str();

   m_hFile = CreateFileW(p_port,

                         GENERIC_READ | GENERIC_WRITE,
                         0,
                         0,
                         OPEN_EXISTING,
                         FILE_ATTRIBUTE_NORMAL,
                         0);

   if (m_hFile == INVALID_HANDLE_VALUE)
   {
      DWORD errno_ = get_last_error();
      string str;
      switch (errno_)
      {
      case ERROR_FILE_NOT_FOUND:
         // Use this->getPort to convert to a std::string
         str.Format("Specified port, %d, does not exist.", this->getPort());
         THROW(IOException, str);
      default:
         str.Format("Unknown error opening the serial port: %d",  errno_);
         THROW(IOException, str);
      }
   }

   reconfigurePort();

   m_bOpened = true;

}


void Serial::SerialImpl::reconfigurePort ()
{
   if (m_hFile == INVALID_HANDLE_VALUE)
   {
      // Can only operate on a valid file descriptor
      THROW (IOException, "Invalid file descriptor, is the serial port open?");
   }

   DCB dcbSerialParams = {0};

   xxf_zero(dcbSerialParams);

   dcbSerialParams.DCBlength=sizeof(dcbSerialParams);

   if (!GetCommState(m_hFile, &dcbSerialParams))
   {
      //error getting state
      THROW (IOException, "Error getting the serial port state.");
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
   if (m_bytesize == eightbits)
      dcbSerialParams.ByteSize = 8;
   else if (m_bytesize == sevenbits)
      dcbSerialParams.ByteSize = 7;
   else if (m_bytesize == sixbits)
      dcbSerialParams.ByteSize = 6;
   else if (m_bytesize == fivebits)
      dcbSerialParams.ByteSize = 5;
   else
      __throw(invalid_argument_exception("invalid char len"));

   // setup stopbits
   if (m_stopbits == stopbits_one)
      dcbSerialParams.StopBits = ONESTOPBIT;
   else if (m_stopbits == stopbits_one_point_five)
      dcbSerialParams.StopBits = ONE5STOPBITS;
   else if (m_stopbits == stopbits_two)
      dcbSerialParams.StopBits = TWOSTOPBITS;
   else
      __throw(invalid_argument_exception("invalid stop bit"));

   // setup parity
   if (m_parity == parity_none)
   {
      dcbSerialParams.Parity = NOPARITY;
   }
   else if (m_parity == parity_even)
   {
      dcbSerialParams.Parity = EVENPARITY;
   }
   else if (m_parity == parity_odd)
   {
      dcbSerialParams.Parity = ODDPARITY;
   }
   else if (m_parity == parity_mark)
   {
      dcbSerialParams.Parity = MARKPARITY;
   }
   else if (m_parity == parity_space)
   {
      dcbSerialParams.Parity = SPACEPARITY;
   }
   else
   {
      __throw(invalid_argument_exception("invalid parity"));
   }

   // setup flowcontrol
   if (m_flowcontrol == flowcontrol_none)
   {
      dcbSerialParams.fOutxCtsFlow = false;
      dcbSerialParams.fRtsControl = 0x00;
      dcbSerialParams.fOutX = false;
      dcbSerialParams.fInX = false;
   }
   if (m_flowcontrol == flowcontrol_software)
   {
      dcbSerialParams.fOutxCtsFlow = false;
      dcbSerialParams.fRtsControl = 0x00;
      dcbSerialParams.fOutX = true;
      dcbSerialParams.fInX = true;
   }
   if (m_flowcontrol == flowcontrol_hardware)
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
      THROW (IOException, "Error setting serial port settings.");
   }

   // Setup timeouts
   COMMTIMEOUTS timeouts = {0};
   timeouts.ReadIntervalTimeout = m_timeout.inter_byte_timeout;
   timeouts.ReadTotalTimeoutConstant = m_timeout.read_timeout_constant;
   timeouts.ReadTotalTimeoutMultiplier = m_timeout.read_timeout_multiplier;
   timeouts.WriteTotalTimeoutConstant = m_timeout.write_timeout_constant;
   timeouts.WriteTotalTimeoutMultiplier = m_timeout.write_timeout_multiplier;
   if (!SetCommTimeouts(m_hFile, &timeouts))
   {
      THROW (IOException, "Error setting timeouts.");
   }


   // Compensate for the stopbits_one_point_five enum being equal to int 3,
   // and not 1.5.
   // Update byte_time_ based on the new settings.

   if (m_stopbits == stopbits_one_point_five)
   {

      m_uiByteTimeNs = (u32)(((((u64)1000LL * 1000LL * 1000LL) *(1 + m_bytesize + m_parity)) + (1500LL*1000LL*1000LL))/((u64)(m_ulBaudrate)));

   }
   else
   {

      m_uiByteTimeNs = (u32) ((((u64)1000LL * 1000LL * 1000LL) *(1 + m_bytesize + m_parity + m_stopbits))/((u64)(m_ulBaudrate)));

   }

}


void
Serial::SerialImpl::close ()
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
            str.Format("Error while closing serial port: %d", get_last_error());
            THROW (IOException, str);
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

bool
Serial::SerialImpl::isOpen () const
{
   return m_bOpened;
}

size_t
Serial::SerialImpl::available ()
{
   if (!m_bOpened)
   {
      return 0;
   }
   COMSTAT cs;
   if (!ClearCommError(m_hFile, nullptr, &cs))
   {
      string str;
      str.Format("Error while checking status of the serial port: %d", get_last_error());
      THROW (IOException, str);
   }
   return static_cast<size_t>(cs.cbInQue);
}

bool
Serial::SerialImpl::waitReadable (u32 /*timeout*/)
{
   THROW (IOException, "waitReadable is not implemented on Windows.");
   return false;
}

void
Serial::SerialImpl::waitByteTimes (size_t count)
{
   //THROW (IOException, "waitByteTimes is not implemented on Windows.");
   duration dur;
   dur.m_iNanoseconds = count * m_uiByteTimeNs;
   dur.normalize();
   sleep(dur);

}

size_t
Serial::SerialImpl::read (u8 *buf, size_t size)
{
   if (!m_bOpened)
   {
      __throw(PortNotOpenedException ("Serial::read"));
   }
   DWORD bytes_read;
   if (!ReadFile(m_hFile, buf, static_cast<DWORD>(size), &bytes_read, nullptr))
   {
      string ss;
      ss.Format("Error while reading from the serial port: %d", get_last_error());
      THROW (IOException, ss);
   }
   return (size_t) (bytes_read);
}

size_t
Serial::SerialImpl::write (const u8 *data, size_t length)
{
   if (m_bOpened == false)
   {
      __throw(PortNotOpenedException ("Serial::write"));
   }
   DWORD bytes_written;
   if (!WriteFile(m_hFile, data, static_cast<DWORD>(length), &bytes_written, nullptr))
   {
      string str;
      str.Format("Error while writing to the serial port: %d", get_last_error());
      THROW (IOException, str);
   }
   return (size_t) (bytes_written);
}

size_t Serial::SerialImpl::readline(string &buffer, size_t size, string eol)
{
   ScopedReadLock lock(this);
   size_t eol_len = (size_t)eol.length();
   u8 *buffer_ = static_cast<u8*>
                      (alloca(size * sizeof(u8)));
auto tickStart = ::tick::now();
   size_t read_so_far = 0;
   while (true)
   {
      size_t bytes_read = read(buffer_ + read_so_far, 1);
      read_so_far += bytes_read;
      if (bytes_read == 0)
      {
         if (tickStart.elapsed() > m_timeout.read_timeout_constant)
         {
            break;
         }
         // Timeout occured on reading 1 byte
         Sleep(max(100, m_timeout.read_timeout_constant / 10));
         if (!::thread_get_run())
         {
            break;
         }
         continue;
      }
auto tickStart = ::tick::now();
      if (string(reinterpret_cast<const char*>
                 (buffer_ + read_so_far - eol_len), eol_len) == eol)
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

void
Serial::SerialImpl::setPort (const string &port)
{
   m_wstrPort = wstring(port);
}

string
Serial::SerialImpl::getPort () const
{
   return string(m_wstrPort);
}

void
Serial::SerialImpl::setTimeout (serial::Timeout &timeout)
{
   m_timeout = timeout;
   if (m_bOpened)
   {
      reconfigurePort ();
   }
}

serial::Timeout
Serial::SerialImpl::getTimeout () const
{
   return m_timeout;
}

void
Serial::SerialImpl::setBaudrate (unsigned long baudrate)
{
   m_ulBaudrate = baudrate;
   if (m_bOpened)
   {
      reconfigurePort ();
   }
}

unsigned long
Serial::SerialImpl::getBaudrate () const
{
   return m_ulBaudrate;
}

void
Serial::SerialImpl::setBytesize (serial::bytesize_t bytesize)
{
   m_bytesize = bytesize;
   if (m_bOpened)
   {
      reconfigurePort ();
   }
}

serial::bytesize_t
Serial::SerialImpl::getBytesize () const
{
   return m_bytesize;
}

void
Serial::SerialImpl::setParity (serial::parity_t parity)
{
   m_parity = parity;
   if (m_bOpened)
   {
      reconfigurePort ();
   }
}

serial::parity_t
Serial::SerialImpl::getParity () const
{
   return m_parity;
}

void
Serial::SerialImpl::setStopbits (serial::stopbits_t stopbits)
{
   m_stopbits = stopbits;
   if (m_bOpened)
   {
      reconfigurePort ();
   }
}

serial::stopbits_t
Serial::SerialImpl::getStopbits () const
{
   return m_stopbits;
}

void
Serial::SerialImpl::setFlowcontrol (serial::flowcontrol_t flowcontrol)
{
   m_flowcontrol = flowcontrol;
   if (m_bOpened)
   {
      reconfigurePort ();
   }
}

serial::flowcontrol_t
Serial::SerialImpl::getFlowcontrol () const
{
   return m_flowcontrol;
}

void
Serial::SerialImpl::flush ()
{
   if (m_bOpened == false)
   {
      __throw(PortNotOpenedException ("Serial::flush"));
   }
   FlushFileBuffers (m_hFile);
}

void
Serial::SerialImpl::flushInput ()
{
   THROW (IOException, "flushInput is not supported on Windows.");
}

void
Serial::SerialImpl::flushOutput ()
{
   THROW (IOException, "flushOutput is not supported on Windows.");
}

void
Serial::SerialImpl::sendBreak (int /*duration*/)
{
   THROW (IOException, "sendBreak is not supported on Windows.");
}

void
Serial::SerialImpl::setBreak (bool level)
{
   if (m_bOpened == false)
   {
      __throw(PortNotOpenedException ("Serial::setBreak"));
   }
   if (level)
   {
      EscapeCommFunction (m_hFile, SETBREAK);
   }
   else
   {
      EscapeCommFunction (m_hFile, CLRBREAK);
   }
}

void
Serial::SerialImpl::setRTS (bool level)
{
   if (m_bOpened == false)
   {
      __throw(PortNotOpenedException ("Serial::setRTS"));
   }
   if (level)
   {
      EscapeCommFunction (m_hFile, SETRTS);
   }
   else
   {
      EscapeCommFunction (m_hFile, CLRRTS);
   }
}

void
Serial::SerialImpl::setDTR (bool level)
{
   if (m_bOpened == false)
   {
      __throw(PortNotOpenedException ("Serial::setDTR"));
   }
   if (level)
   {
      EscapeCommFunction (m_hFile, SETDTR);
   }
   else
   {
      EscapeCommFunction (m_hFile, CLRDTR);
   }
}

bool
Serial::SerialImpl::waitForChange ()
{
   if (m_bOpened == false)
   {
      __throw(PortNotOpenedException ("Serial::waitForChange"));
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
Serial::SerialImpl::getCTS ()
{
   if (m_bOpened == false)
   {
      __throw(PortNotOpenedException ("Serial::getCTS"));
   }
   DWORD dwModemStatus;
   if (!GetCommModemStatus(m_hFile, &dwModemStatus))
   {
      THROW (IOException, "Error getting the status of the CTS line.");
   }

   return (MS_CTS_ON & dwModemStatus) != 0;
}

bool
Serial::SerialImpl::getDSR ()
{
   if (m_bOpened == false)
   {
      __throw(PortNotOpenedException ("Serial::getDSR"));
   }
   DWORD dwModemStatus;
   if (!GetCommModemStatus(m_hFile, &dwModemStatus))
   {
      THROW (IOException, "Error getting the status of the DSR line.");
   }

   return (MS_DSR_ON & dwModemStatus) != 0;
}

bool
Serial::SerialImpl::getRI()
{
   if (m_bOpened == false)
   {
      __throw(PortNotOpenedException ("Serial::getRI"));
   }
   DWORD dwModemStatus;
   if (!GetCommModemStatus(m_hFile, &dwModemStatus))
   {
      THROW (IOException, "Error getting the status of the RI line.");
   }

   return (MS_RING_ON & dwModemStatus) != 0;
}

bool
Serial::SerialImpl::getCD()
{
   if (m_bOpened == false)
   {
      __throw(PortNotOpenedException ("Serial::getCD"));
   }
   DWORD dwModemStatus;
   if (!GetCommModemStatus(m_hFile, &dwModemStatus))
   {
      // Error in GetCommModemStatus;
      THROW (IOException, "Error getting the status of the CD line.");
   }

   return (MS_RLSD_ON & dwModemStatus) != 0;
}

void
Serial::SerialImpl::readLock()
{
   if (WaitForSingleObject(m_hMutexRead, INFINITE) != WAIT_OBJECT_0)
   {
      THROW (IOException, "Error claiming read ::mutex.");
   }
}

void
Serial::SerialImpl::readUnlock()
{
   if (!ReleaseMutex(m_hMutexRead))
   {
      THROW (IOException, "Error releasing read ::mutex.");
   }
}

void
Serial::SerialImpl::writeLock()
{
   if (WaitForSingleObject(m_hMutexWrite, INFINITE) != WAIT_OBJECT_0)
   {
      THROW (IOException, "Error claiming write ::mutex.");
   }
}

void
Serial::SerialImpl::writeUnlock()
{
   if (!ReleaseMutex(m_hMutexWrite))
   {
      THROW (IOException, "Error releasing write ::mutex.");
   }
}



