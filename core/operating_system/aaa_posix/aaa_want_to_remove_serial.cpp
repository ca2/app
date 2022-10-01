/* Copyright 2012 William Woodall and John Harrison
 *
 * Additional Contributors: Christopher Baker @bakercp
 */

#include "framework.h"

 //#include <sstream>

#if !defined(_WIN32)

#include <stdio.h>
#include <string.h>
//#include <sstream>
#undef USE_MISC

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/signal.h>
#include <errno.h>
#include <paths.h>
#include <sysexits.h>
#include <termios.h>
#include <sys/param.h>
#include <pthread.h>

#if defined(__linux__)
# include <linux/serial.h>
#endif

#include <sys/select.h>
#include <sys/time.h>
#include <time.h>
#ifdef __MACH__
#include <AvailabilityMacros.h>
#include <mach/clock.h>
#include <mach/mach.h>
#endif

#include "serial.h"

#ifndef TIOCINQ
#ifdef FIONREAD
#define TIOCINQ FIONREAD
#else
#define TIOCINQ 0x541B
#endif
#endif

#if defined(MAC_OS_X_VERSION_10_3) && (MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_3)
#include <IOKit/serial/ioss.h>
#endif

using serial::durationTimer;
using serial::serial;
using serial::serial_exception;
using serial::port_not_opened_exception;
using serial::io_exception;


::durationTimer::durationTimer(const u32 ::duration)
   : expiry(timespec_now())
{
   i64 tv_nsec = expiry.tv_nsec + (::duration * 1e6);
   if (tv_nsec >= 1e9)
   {
      i64 sec_diff = tv_nsec / static_cast<int> (1e9);
      expiry.tv_nsec = tv_nsec % static_cast<int>(1e9);
      expiry.tv_sec += sec_diff;
   }
   else
   {
      expiry.tv_nsec = tv_nsec;
   }
}

i64
::durationTimer::remaining()
{
   timespec now(timespec_now());
   i64 ::duration = (expiry.tv_sec - now.tv_sec) * 1e3;
   ::duration += (expiry.tv_nsec - now.tv_nsec) / 1e6;
   return ::duration;
}

timespec
::durationTimer::timespec_now()
{
   timespec time;
# ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
   clock_serv_t cclock;
   mach_timespec_t mts;
   host_get_clock_service(mach_host_self(), SYSTEM_CLOCK, &cclock);
   clock_get_time(cclock, &mts);
   mach_port_deallocate(mach_task_self(), cclock);
   time.tv_sec = mts.tv_sec;
   time.tv_nsec = mts.tv_nsec;
# else
   clock_gettime(CLOCK_MONOTONIC, &time);
# endif
   return time;
}

timespec
timespec_from_ms(const u32 ::duration)
{
   timespec time;
   time.tv_sec = ::duration / 1e3;
   time.tv_nsec = (::duration - (time.tv_sec * 1e3)) * 1e6;
   return time;
}

serial::serial_impl::serial_impl(::object * pobject, const string & port, unsigned long baudrate,
   enum_byte_size ebytesize,
   enum_parity eparity, enum_stop_bit estopbit,
   enum_flow_control eflowcontrol)
   : object(pobject), m_strPort(port), m_iFd(-1), m_bOpened(false), m_bXonXoff(false), m_bRtsCts(false),
   m_ulBaudrate(baudrate), m_eparity(eparity),
   m_ebytesize(ebytesize), m_estopbit(estopbit), m_eflowcontrol(eflowcontrol)
{
   pthread_mutex_init(&this->m_mutexRead, nullptr);
   pthread_mutex_init(&this->m_mutexWrite, nullptr);
   if (m_strPort.empty() == false)
      open();
}

serial::serial_impl::~serial_impl()
{
   close();
   pthread_mutex_destroy(&this->m_mutexRead);
   pthread_mutex_destroy(&this->m_mutexWrite);
}

void
serial::serial_impl::open()
{
   if (m_strPort.empty())
   {
      throw ::exception(error_bad_argument, "Empty port is invalid."));
   }
   if (m_bOpened == true)
   {
      throw ::exception(serial_exception("serial port already open."));
   }

   m_iFd = ::open(m_strPort.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);

   if (m_iFd == -1)
   {
      switch (errno)
      {
      case EINTR:
         // Recurse because this is a recoverable error.
         open();
         return;
      case ENFILE:
      case EMFILE:
         THROW(io_exception, "Too many file handles open.");
      default:
         THROW(io_exception, errno);
      }
   }

   reconfigurePort();
   m_bOpened = true;
}

void
serial::serial_impl::reconfigurePort()
{
   if (m_iFd == -1)
   {
      // Can only operate on a valid file descriptor
      THROW(io_exception, "Invalid file descriptor, is the serial port open?");
   }

   struct termios options; // The options for the file descriptor

   if (tcgetattr(m_iFd, &options) == -1)
   {
      THROW(io_exception, "::tcgetattr");
   }

   // set up raw mode / no echo / binary
   options.c_cflag |= (tcflag_t)(CLOCAL | CREAD);
   options.c_lflag &= (tcflag_t)~(ICANON | ECHO | ECHOE | ECHOK | ECHONL |
      ISIG | IEXTEN); //|ECHOPRT

   options.c_oflag &= (tcflag_t)~(OPOST);
   options.c_iflag &= (tcflag_t)~(INLCR | IGNCR | ICRNL | IGNBRK);
#ifdef IUCLC
   options.c_iflag &= (tcflag_t)~IUCLC;
#endif
#ifdef PARMRK
   options.c_iflag &= (tcflag_t)~PARMRK;
#endif

   // setup baud rate
   bool custom_baud = false;
   speed_t baud;
   switch (m_ulBaudrate)
   {
#ifdef B0
   case 0: baud = B0; break;
#endif
#ifdef B50
   case 50: baud = B50; break;
#endif
#ifdef B75
   case 75: baud = B75; break;
#endif
#ifdef B110
   case 110: baud = B110; break;
#endif
#ifdef B134
   case 134: baud = B134; break;
#endif
#ifdef B150
   case 150: baud = B150; break;
#endif
#ifdef B200
   case 200: baud = B200; break;
#endif
#ifdef B300
   case 300: baud = B300; break;
#endif
#ifdef B600
   case 600: baud = B600; break;
#endif
#ifdef B1200
   case 1200: baud = B1200; break;
#endif
#ifdef B1800
   case 1800: baud = B1800; break;
#endif
#ifdef B2400
   case 2400: baud = B2400; break;
#endif
#ifdef B4800
   case 4800: baud = B4800; break;
#endif
#ifdef B7200
   case 7200: baud = B7200; break;
#endif
#ifdef B9600
   case 9600: baud = B9600; break;
#endif
#ifdef B14400
   case 14400: baud = B14400; break;
#endif
#ifdef B19200
   case 19200: baud = B19200; break;
#endif
#ifdef B28800
   case 28800: baud = B28800; break;
#endif
#ifdef B57600
   case 57600: baud = B57600; break;
#endif
#ifdef B76800
   case 76800: baud = B76800; break;
#endif
#ifdef B38400
   case 38400: baud = B38400; break;
#endif
#ifdef B115200
   case 115200: baud = B115200; break;
#endif
#ifdef B128000
   case 128000: baud = B128000; break;
#endif
#ifdef B153600
   case 153600: baud = B153600; break;
#endif
#ifdef B230400
   case 230400: baud = B230400; break;
#endif
#ifdef B256000
   case 256000: baud = B256000; break;
#endif
#ifdef B460800
   case 460800: baud = B460800; break;
#endif
#ifdef B576000
   case 576000: baud = B576000; break;
#endif
#ifdef B921600
   case 921600: baud = B921600; break;
#endif
#ifdef B1000000
   case 1000000: baud = B1000000; break;
#endif
#ifdef B1152000
   case 1152000: baud = B1152000; break;
#endif
#ifdef B1500000
   case 1500000: baud = B1500000; break;
#endif
#ifdef B2000000
   case 2000000: baud = B2000000; break;
#endif
#ifdef B2500000
   case 2500000: baud = B2500000; break;
#endif
#ifdef B3000000
   case 3000000: baud = B3000000; break;
#endif
#ifdef B3500000
   case 3500000: baud = B3500000; break;
#endif
#ifdef B4000000
   case 4000000: baud = B4000000; break;
#endif
   default:
      custom_baud = true;
      // OS X support
#if defined(MAC_OS_X_VERSION_10_4) && (MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_4)
      // Starting with Tiger, the IOSSIOSPEED ioctl can be used to set arbitrary baud rates
      // other than those specified by POSIX. The driver for the underlying serial hardware
      // ultimately determines which baud rates can be used. This ioctl sets both the input
      // and output speed.
      speed_t new_baud = static_cast<speed_t> (m_ulBaudrate);
      if (-1 == ioctl(m_iFd, IOSSIOSPEED, &new_baud, 1))
      {
         THROW(io_exception, errno);
      }
      // Linux Support
#elif defined(__linux__) && defined (TIOCSSERIAL)
      struct serial_struct ser;

      if (-1 == ioctl(m_iFd, TIOCGSERIAL, &ser))
      {
         THROW(io_exception, errno);
      }

      // set custom divisor
      ser.custom_divisor = ser.baud_base / static_cast<int> (m_ulBaudrate);
      // update flags
      ser.flags &= ~ASYNC_SPD_MASK;
      ser.flags |= ASYNC_SPD_CUST;

      if (-1 == ioctl(m_iFd, TIOCSSERIAL, &ser))
      {
         THROW(io_exception, errno);
      }
#else
      throw ::exception(invalid_argument("OS does not currently support custom bauds"));
#endif
   }
   if (custom_baud == false)
   {
#ifdef _BSD_SOURCE
      ::cfsetspeed(&options, baud);
#else
      ::cfsetispeed(&options, baud);
      ::cfsetospeed(&options, baud);
#endif
   }

   // setup char len
   options.c_cflag &= (tcflag_t)~CSIZE;
   if (m_ebytesize == e_byte_size_eight)
      options.c_cflag |= CS8;
   else if (m_ebytesize == sevenbits)
      options.c_cflag |= CS7;
   else if (m_ebytesize == sixbits)
      options.c_cflag |= CS6;
   else if (m_ebytesize == fivebits)
      options.c_cflag |= CS5;
   else
      throw ::exception(error_bad_argument, "invalid char len"));
   // setup estopbit
   if (m_estopbit == e_stop_bit_one)
      options.c_cflag &= (tcflag_t)~(CSTOPB);
   else if (m_estopbit == e_stop_bit_one_point_five)
      // ONE POINT32 FIVE same as TWO.. there is no POSIX support for 1.5
      options.c_cflag |= (CSTOPB);
   else if (m_estopbit == estopbit_two)
      options.c_cflag |= (CSTOPB);
   else
      throw ::exception(error_bad_argument, "invalid stop bit"));
   // setup eparity
   options.c_iflag &= (tcflag_t)~(INPCK | ISTRIP);
   if (m_eparity == e_parity_none)
   {
      options.c_cflag &= (tcflag_t)~(PARENB | PARODD);
   }
   else if (m_eparity == eparity_even)
   {
      options.c_cflag &= (tcflag_t)~(PARODD);
      options.c_cflag |= (PARENB);
   }
   else if (m_eparity == eparity_odd)
   {
      options.c_cflag |= (PARENB | PARODD);
   }
#ifdef CMSPAR
   else if (m_eparity == eparity_mark)
   {
      options.c_cflag |= (PARENB | CMSPAR | PARODD);
   }
   else if (m_eparity == eparity_space)
   {
      options.c_cflag |= (PARENB | CMSPAR);
      options.c_cflag &= (tcflag_t)~(PARODD);
   }
#else
   // CMSPAR is not defined on OSX. So do not support mark or space eparity.
   else if (m_eparity == eparity_mark || m_eparity == eparity_space)
   {
      throw ::exception(error_bad_argument, "OS does not support mark or space eparity"));
   }
#endif  // ifdef CMSPAR
   else
   {
      throw ::exception(error_bad_argument, "invalid eparity"));
   }
   // setup flow control
   if (m_eflowcontrol == e_flow_control_none)
   {
      m_bXonXoff = false;
      m_bRtsCts = false;
   }
   if (m_eflowcontrol == e_flow_control_software)
   {
      m_bXonXoff = true;
      m_bRtsCts = false;
   }
   if (m_eflowcontrol == e_flow_control_hardware)
   {
      m_bXonXoff = false;
      m_bRtsCts = true;
   }
   // xonxoff
#ifdef IXANY
   if (m_bXonXoff)
      options.c_iflag |= (IXON | IXOFF); //|IXANY)
   else
      options.c_iflag &= (tcflag_t)~(IXON | IXOFF | IXANY);
#else
   if (m_bXonXoff)
      options.c_iflag |= (IXON | IXOFF);
   else
      options.c_iflag &= (tcflag_t)~(IXON | IXOFF);
#endif
   // rtscts
#ifdef CRTSCTS
   if (m_bRtsCts)
      options.c_cflag |= (CRTSCTS);
   else
      options.c_cflag &= (unsigned long)~(CRTSCTS);
#elif defined CNEW_RTSCTS
   if (m_bRtsCts)
      options.c_cflag |= (CNEW_RTSCTS);
   else
      options.c_cflag &= (unsigned long)~(CNEW_RTSCTS);
#else
#error "OS Support seems wrong."
#endif

   // http://www.unixwiz.net/techtips/termios-vmin-vtime.html
   // this basically sets the read call up to be a polling read,
   // but we are using select to ensure there is data available
   // to read before each call, so we should never needlessly poll
   options.c_cc[VMIN] = 0;
   options.c_cc[VTIME] = 0;

   // activate settings
   ::tcsetattr(m_iFd, TCSANOW, &options);

   // Update byte_time_ based on the memory_new settings.
   u32 bit_time_ns = 1e9 / m_ulBaudrate;
   m_uiByteTimeNs = bit_time_ns * (1 + m_ebytesize + m_eparity + m_estopbit);

   // Compensate for the e_stop_bit_one_point_five enum being equal to int 3,
   // and not 1.5.
   if (m_estopbit == e_stop_bit_one_point_five)
   {
      m_uiByteTimeNs += ((1.5 - e_stop_bit_one_point_five) * bit_time_ns);
   }
}

void
serial::serial_impl::close()
{
   if (m_bOpened == true)
   {
      if (m_iFd != -1)
      {
         int ret;
         ret = ::close(m_iFd);
         if (ret == 0)
         {
            m_iFd = -1;
         }
         else
         {
            THROW(io_exception, errno);
         }
      }
      m_bOpened = false;
   }
}

bool
serial::serial_impl::isOpen() const
{
   return m_bOpened;
}

size_t
serial::serial_impl::available()
{
   if (!m_bOpened)
   {
      return 0;
   }
   int count = 0;
   if (-1 == ioctl(m_iFd, TIOCINQ, &count))
   {
      THROW(io_exception, errno);
   }
   else
   {
      return static_cast<size_t> (count);
   }
}

bool
serial::serial_impl::waitReadable(u32 timeout)
{
   // Setup a select call to block for serial data or a timeout
   fd_set readfds;
   FD_ZERO(&readfds);
   FD_SET(m_iFd, &readfds);
   timespec timeout_ts(timespec_from_ms(timeout));
   int r = pselect(m_iFd + 1, &readfds, nullptr, nullptr, &timeout_ts, nullptr);

   if (r < 0)
   {
      // Select was interrupted
      if (errno == EINTR)
      {
         return false;
      }
      // Otherwise there was some error
      THROW(io_exception, errno);
   }
   // Timeout occurred
   if (r == 0)
   {
      return false;
   }
   // This shouldn't happen, if r > 0 our fd has to be in the list!
   if (!FD_ISSET(m_iFd, &readfds))
   {
      THROW(io_exception, "select reports ready to read, but our fd isn't"
         " in the list, this shouldn't happen!");
   }
   // Data available to read.
   return true;
}

void
serial::serial_impl::waitByteTimes(size_t count)
{
   timespec wait_time = { 0, static_cast<long>(m_uiByteTimeNs * count) };
   pselect(0, nullptr, nullptr, nullptr, &wait_time, nullptr);
}

size_t
serial::serial_impl::read(u8 * buf, size_t size)
{
   // If the port is not open, throw ::exception(memory_new
   if (!m_bOpened)
   {
      throw ::exception(port_not_opened_exception("serial::read"));
   }
   size_t bytes_read = 0;

   // Calculate total timeout in ::durations t_c + (t_m * N)
   long total_timeout_ms = m_timeout.read_timeout_constant;
   total_timeout_ms += m_timeout.read_timeout_multiplier * static_cast<long> (size);
   ::durationTimer total_timeout((u32)total_timeout_ms);

   // Pre-fill buffer with available bytes
   {
      ssize_t bytes_read_now = ::read(m_iFd, buf, size);
      if (bytes_read_now > 0)
      {
         bytes_read = bytes_read_now;
      }
   }

   while (bytes_read < size)
   {
      i64 timeout_remaining_ms = total_timeout.remaining();
      if (timeout_remaining_ms <= 0)
      {
         // Timed out
         break;
      }
      // Timeout for the next select is whichever is less of the remaining
      // total read timeout and the inter-byte timeout.
      u32 timeout = minimum(static_cast<u32> (timeout_remaining_ms),
         m_timeout.inter_byte_timeout);
      // Wait for the device to be readable, and then attempt to read.
      if (waitReadable(timeout))
      {
         // If it's a fixed-length multi-byte read, insert a wait here so that
         // we can attempt to grab the whole thing in a single IO call. Skip
         // this wait if a non-maximum inter_byte_timeout is specified.
         if (size > 1 && m_timeout.inter_byte_timeout == Timeout::maximum())
         {
            size_t bytes_available = available();
            if (bytes_available + bytes_read < size)
            {
               waitByteTimes(size - (bytes_available + bytes_read));
            }
         }
         // This should be non-blocking returning only what is available now
         //  Then returning so that select can block again.
         ssize_t bytes_read_now =
            ::read(m_iFd, buf + bytes_read, size - bytes_read);
         // read should always return some data as select reported it was
         // ready to read when we get to this point.
         if (bytes_read_now < 1)
         {
            // Disconnected devices, at least on Linux, show the
            // behavior that they are always ready to read immediately
            // but reading returns nothing.
            throw ::exception( serial_exception("device reports readiness to read but returned no data (device disconnected?)"));
         }
         // Update bytes_read
         bytes_read += static_cast<size_t> (bytes_read_now);
         // If bytes_read == size then we have read everything we need
         if (bytes_read == size)
         {
            break;
         }
         // If bytes_read < size then we have more to read
         if (bytes_read < size)
         {
            continue;
         }
         // If bytes_read > size then we have over read, which shouldn't happen
         if (bytes_read > size)
         {
            throw ::exception( serial_exception("read over read, too many bytes where "
               "read, this shouldn't happen, might be "
               "a logical error!"));
         }
      }
   }
   return bytes_read;
}

size_t
serial::serial_impl::write(const u8 * data, size_t length)
{
   if (m_bOpened == false)
   {
      throw ::exception(port_not_opened_exception("serial::write"));
   }
   fd_set writefds;
   size_t bytes_written = 0;

   // Calculate total timeout in ::durations t_c + (t_m * N)
   long total_timeout_ms = m_timeout.write_timeout_constant;
   total_timeout_ms += m_timeout.write_timeout_multiplier * static_cast<long> (length);
   ::durationTimer total_timeout((u32)total_timeout_ms);

   bool first_iteration = true;
   while (bytes_written < length)
   {
      i64 timeout_remaining_ms = total_timeout.remaining();
      // Only consider the timeout if it's not the first iteration of the loop
      // otherwise a timeout of 0 won't be allowed through
      if (!first_iteration && (timeout_remaining_ms <= 0))
      {
         // Timed out
         break;
      }
      first_iteration = false;

      timespec timeout(timespec_from_ms((u32)timeout_remaining_ms));

      FD_ZERO(&writefds);
      FD_SET(m_iFd, &writefds);

      // Do the select
      int r = pselect(m_iFd + 1, nullptr, &writefds, nullptr, &timeout, nullptr);

      // Figure out what happened by looking at select's response 'r'
      /** Error **/
      if (r < 0)
      {
         // Select was interrupted, try again
         if (errno == EINTR)
         {
            continue;
         }
         // Otherwise there was some error
         THROW(io_exception, errno);
      }
      /** Timeout **/
      if (r == 0)
      {
         break;
      }
      /** Port ready to write **/
      if (r > 0)
      {
         // Make sure our file descriptor is in the ready to write list
         if (FD_ISSET(m_iFd, &writefds))
         {
            // This will write some
            ssize_t bytes_written_now =
               ::write(m_iFd, data + bytes_written, length - bytes_written);
            // write should always return some data as select reported it was
            // ready to write when we get to this point.
            if (bytes_written_now < 1)
            {
               // Disconnected devices, at least on Linux, show the
               // behavior that they are always ready to write immediately
               // but writing returns nothing.
               throw ::exception( serial_exception("device reports readiness to write but "
                  "returned no data (device disconnected?)"));
            }
            // Update bytes_written
            bytes_written += static_cast<size_t> (bytes_written_now);
            // If bytes_written == size then we have written everything we need to
            if (bytes_written == length)
            {
               break;
            }
            // If bytes_written < size then we have more to write
            if (bytes_written < length)
            {
               continue;
            }
            // If bytes_written > size then we have over written, which shouldn't happen
            if (bytes_written > length)
            {
               throw ::exception( serial_exception("write over wrote, too many bytes where "
                  "written, this shouldn't happen, might be "
                  "a logical error!"));
            }
         }
         // This shouldn't happen, if r > 0 our fd has to be in the list!
         THROW(io_exception, "select reports ready to write, but our fd isn't"
            " in the list, this shouldn't happen!");
      }
   }
   return bytes_written;
}

void
serial::serial_impl::setPort(const string & port)
{
   m_strPort = port;
}

string
serial::serial_impl::getPort() const
{
   return m_strPort;
}

void
serial::serial_impl::setTimeout(serial::Timeout & timeout)
{
   m_timeout = timeout;
}

serial::Timeout
serial::serial_impl::getTimeout() const
{
   return m_timeout;
}

void
serial::serial_impl::setBaudrate(unsigned long baudrate)
{
   m_ulBaudrate = baudrate;
   if (m_bOpened)
      reconfigurePort();
}

unsigned long
serial::serial_impl::getBaudrate() const
{
   return m_ulBaudrate;
}

void
serial::serial_impl::setBytesize(serial::enum_byte_size ebytesize)
{
   m_ebytesize = ebytesize;
   if (m_bOpened)
      reconfigurePort();
}

serial::enum_byte_size
serial::serial_impl::getBytesize() const
{
   return m_ebytesize;
}

void
serial::serial_impl::setParity(serial::enum_parity eparity)
{
   m_eparity = eparity;
   if (m_bOpened)
      reconfigurePort();
}

serial::enum_parity
serial::serial_impl::getParity() const
{
   return m_eparity;
}

void
serial::serial_impl::setStopbits(serial::enum_stop_bit estopbit)
{
   m_estopbit = estopbit;
   if (m_bOpened)
      reconfigurePort();
}

serial::enum_stop_bit
serial::serial_impl::getStopbits() const
{
   return m_estopbit;
}

void
serial::serial_impl::setFlowcontrol(serial::enum_flow_control eflowcontrol)
{
   m_eflowcontrol = eflowcontrol;
   if (m_bOpened)
      reconfigurePort();
}

serial::enum_flow_control
serial::serial_impl::getFlowcontrol() const
{
   return m_eflowcontrol;
}

void
serial::serial_impl::flush()
{
   if (m_bOpened == false)
   {
      throw ::exception(port_not_opened_exception("serial::flush"));
   }
   tcdrain(m_iFd);
}

void
serial::serial_impl::flushInput()
{
   if (m_bOpened == false)
   {
      throw ::exception(port_not_opened_exception("serial::flushInput"));
   }
   tcflush(m_iFd, TCIFLUSH);
}

void
serial::serial_impl::flushOutput()
{
   if (m_bOpened == false)
   {
      throw ::exception(port_not_opened_exception("serial::flushOutput"));
   }
   tcflush(m_iFd, TCOFLUSH);
}

void
serial::serial_impl::sendBreak(int duration)
{
   if (m_bOpened == false)
   {
      throw ::exception(port_not_opened_exception("serial::sendBreak"));
   }
   tcsendbreak(m_iFd, static_cast<int> (duration / 4));
}

void
serial::serial_impl::setBreak(bool level)
{
   if (m_bOpened == false)
   {
      throw ::exception(port_not_opened_exception("serial::setBreak"));
   }

   if (level)
   {
      if (-1 == ioctl(m_iFd, TIOCSBRK))
      {
         string str;
         str.format("setBreak failed on a call to ioctl(TIOCSBRK): %d %s", errno, strerror(errno));
         throw ::exception(serial_exception(str));
      }
   }
   else
   {
      if (-1 == ioctl(m_iFd, TIOCCBRK))
      {
         string ss;
         ss.Format("setBreak failed on a call to ioctl(TIOCCBRK): %d %s", errno, strerror(errno));
         throw ::exception(serial_exception(ss));
      }
   }
}

void
serial::serial_impl::setRTS(bool level)
{
   if (m_bOpened == false)
   {
      throw ::exception(port_not_opened_exception("serial::setRTS"));
   }

   int command = TIOCM_RTS;

   if (level)
   {
      if (-1 == ioctl(m_iFd, TIOCMBIS, &command))
      {
         text_stream ss;
         ss << "setRTS failed on a call to ioctl(TIOCMBIS): " << errno << " " << strerror(errno);
         throw ::exception(serial_exception(ss.str().c_str()));
      }
   }
   else
   {
      if (-1 == ioctl(m_iFd, TIOCMBIC, &command))
      {
         text_stream ss;
         ss << "setRTS failed on a call to ioctl(TIOCMBIC): " << errno << " " << strerror(errno);
         throw ::exception(serial_exception(ss.str().c_str()));
      }
   }
}

void
serial::serial_impl::setDTR(bool level)
{
   if (m_bOpened == false)
   {
      throw ::exception(port_not_opened_exception("serial::setDTR"));
   }

   int command = TIOCM_DTR;

   if (level)
   {
      if (-1 == ioctl(m_iFd, TIOCMBIS, &command))
      {
         text_stream ss;
         ss << "setDTR failed on a call to ioctl(TIOCMBIS): " << errno << " " << strerror(errno);
         throw ::exception(serial_exception(ss.str().c_str()));
      }
   }
   else
   {
      if (-1 == ioctl(m_iFd, TIOCMBIC, &command))
      {
         text_stream ss;
         ss << "setDTR failed on a call to ioctl(TIOCMBIC): " << errno << " " << strerror(errno);
         throw ::exception(serial_exception(ss.str().c_str()));
      }
   }
}

bool
serial::serial_impl::waitForChange()
{
#ifndef TIOCMIWAIT

   while (m_bOpened == true)
   {

      int status;

      if (-1 == ioctl(m_iFd, TIOCMGET, &status))
      {
         text_stream ss;
         ss << "waitForChange failed on a call to ioctl(TIOCMGET): " << errno << " " << strerror(errno);
         throw ::exception(serial_exception(ss.str().c_str()));
      }
      else
      {
         if (0 != (status & TIOCM_CTS)
            || 0 != (status & TIOCM_DSR)
            || 0 != (status & TIOCM_RI)
            || 0 != (status & TIOCM_CD))
         {
            return true;
         }
      }

      usleep(1000_ms);
   }

   return false;
#else
   int command = (TIOCM_CD | TIOCM_DSR | TIOCM_RI | TIOCM_CTS);

   if (-1 == ioctl(m_iFd, TIOCMIWAIT, &command))
   {
      string ss;
      ss.Format("waitForDSR failed on a call to ioctl(TIOCMIWAIT): %d %s", errno, strerror(errno));
      throw ::exception(serial_exception(ss.str().c_str()));
   }
   return true;
#endif
}

bool
serial::serial_impl::getCTS()
{
   if (m_bOpened == false)
   {
      throw ::exception(port_not_opened_exception("serial::getCTS"));
   }

   int status;

   if (-1 == ioctl(m_iFd, TIOCMGET, &status))
   {
      text_stream ss;
      ss << "getCTS failed on a call to ioctl(TIOCMGET): " << errno << " " << strerror(errno);
      throw ::exception(serial_exception(ss.str().c_str()));
   }
   else
   {
      return 0 != (status & TIOCM_CTS);
   }
}

bool
serial::serial_impl::getDSR()
{
   if (m_bOpened == false)
   {
      throw ::exception(port_not_opened_exception("serial::getDSR"));
   }

   int status;

   if (-1 == ioctl(m_iFd, TIOCMGET, &status))
   {
      text_stream ss;
      ss << "getDSR failed on a call to ioctl(TIOCMGET): " << errno << " " << strerror(errno);
      throw ::exception(serial_exception(ss.str().c_str()));
   }
   else
   {
      return 0 != (status & TIOCM_DSR);
   }
}

bool
serial::serial_impl::getRI()
{
   if (m_bOpened == false)
   {
      throw ::exception(port_not_opened_exception("serial::getRI"));
   }

   int status;

   if (-1 == ioctl(m_iFd, TIOCMGET, &status))
   {
      text_stream ss;
      ss << "getRI failed on a call to ioctl(TIOCMGET): " << errno << " " << strerror(errno);
      throw ::exception(serial_exception(ss.str().c_str()));
   }
   else
   {
      return 0 != (status & TIOCM_RI);
   }
}

bool
serial::serial_impl::getCD()
{
   if (m_bOpened == false)
   {
      throw ::exception(port_not_opened_exception("serial::getCD"));
   }

   int status;

   if (-1 == ioctl(m_iFd, TIOCMGET, &status))
   {
      text_stream ss;
      ss << "getCD failed on a call to ioctl(TIOCMGET): " << errno << " " << strerror(errno);
      throw ::exception(serial_exception(ss.str().c_str()));
   }
   else
   {
      return 0 != (status & TIOCM_CD);
   }
}

void
serial::serial_impl::readLock()
{
   int result = pthread_mutex_lock(&this->m_mutexRead);
   if (result)
   {
      THROW(io_exception, result);
   }
}

void
serial::serial_impl::readUnlock()
{
   int result = pthread_mutex_unlock(&this->m_mutexRead);
   if (result)
   {
      THROW(io_exception, result);
   }
}

void
serial::serial_impl::writeLock()
{
   int result = pthread_mutex_lock(&this->m_mutexWrite);
   if (result)
   {
      THROW(io_exception, result);
   }
}

void
serial::serial_impl::writeUnlock()
{
   int result = pthread_mutex_unlock(&this->m_mutexWrite);
   if (result)
   {
      THROW(io_exception, result);
   }
}

#endif // !defined(_WIN32)
