#include "framework.h"
/* Copyright 2012 William Woodall and John Harrison */


#include "acme/platform/serial.h"


#include "acme/operating_system.h"


#ifdef _WIN32
#include "acme/node/windows/serial_impl.h"
#else
#include "acme/node/ansios/serial_impl.h"
#endif


#if !defined(_WIN32) && !defined(__OpenBSD__) && !defined(__FreeBSD__)
# include <alloca.h>
#endif

#if defined (__MINGW32__)
# define alloca __builtin_alloca
#endif

//using std::invalid_argument;
//using std::minimum;
//using std::numeric_limits;
//using std::vector;
//using std::size_t;
//using std::string;
//using sTimeout;
//using serial::serial;
//using serial::serial_exception;
//using serial::io_exception;
//using serial::enum_byte_size;
//using serial::enum_parity;
//using serial::enum_stop_bit;
//using serial::enum_flow_control;

namespace serial
{

   
   serial::serial()
   {
   }
   
   
   
   ::e_status serial::open(const string& port, u32 baudrate, timeout timeout,
      enum_byte_size ebytesize, enum_parity eparity, enum_stop_bit estopbit,
      enum_flow_control eflowcontrol)
      //:
      //m_pimpl(__new(serial_impl(port, baudrate, ebytesize, eparity, estopbit, eflowcontrol)))
   {
      set_timeout(timeout);



      return ::error_failed;
   }

   serial::~serial()
   {
   }

   timeout timeout::simpleTimeout(u32 timeout)
   {
#ifdef WINDOWS
      return struct timeout(MAXDWORD, timeout, MAXDWORD, timeout, 0);
#else
      return struct timeout(maximum(), timeout, 0, timeout, 0);
#endif
   }


   void
      serial::open()
   {
      //m_pimpl->open();
   }

   void
      serial::close()
   {
      //m_pimpl->close();
   }

   bool
      serial::isOpen() const
   {
      //return m_pimpl->isOpen();
      return false;
   }

   size_t
      serial::available()
   {
      //return m_pimpl->available();
      return 0;
   }

   bool
      serial::waitReadable()
   {
      //timeout timeout(m_pimpl->getTimeout());
      //return m_pimpl->waitReadable(timeout.m_millisReadTimeoutConstant);
      return false;
   }

   void
      serial::waitByteTimes(size_t count)
   {
      m_pimpl->waitByteTimes(count);
   }

   size_t
      serial::read_(u8* buffer, size_t size)
   {
      //return this->m_pimpl->read(buffer, size);
      return 0;
   }


   size_t serial::read(u8* buffer, size_t size)
   {
      
      scoped_read_lock lock(mutex());

      return _read(buffer, size);

      //return 0;

   }

   size_t
      serial::read(memory& buffer, size_t size)
   {
      scoped_read_lock lock(mutex());
      memory bufferRead;
      bufferRead.set_size(size);
      size_t bytes_read = _read(bufferRead.get_data(), (size_t)bufferRead.get_size());
      buffer.append(bufferRead);
      return bytes_read;
   }

   size_t
      serial::read(string& buffer, size_t size)
   {
      scoped_read_lock lock(mutex());
      u8* buffer_ = new u8[size];
      size_t bytes_read = this->m_pimpl->read(buffer_, size);
      buffer.append(reinterpret_cast<const char*>(buffer_), bytes_read);
      delete[] buffer_;
      return bytes_read;
   }

   string
      serial::read(size_t size)
   {
      string buffer;
      this->read(buffer, size);
      return buffer;
   }

   size_t
      serial::readline(string& buffer, size_t size, string eol)
   {
#ifdef WINDOWS
      return this->m_pimpl->readline(buffer, size, eol);
#else
      scoped_read_lock lock(mutex());
      size_t eol_len = eol.length();
      u8* buffer_ = static_cast<u8*>
         (alloca(size * sizeof(u8)));
      size_t read_so_far = 0;
      while (true)
      {
         size_t bytes_read = this->read_(buffer_ + read_so_far, 1);
         read_so_far += bytes_read;
         if (bytes_read == 0)
         {
            break; // timeout occured on reading 1 byte
         }
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
#endif
   }

   string
      serial::readline(size_t size, string eol)
   {
      string buffer;
      this->readline(buffer, size, eol);
      return buffer;
   }

   string_array
      serial::readlines(size_t size, string eol)
   {
      scoped_read_lock lock(mutex());
      string_array lines;
      size_t eol_len = (size_t)eol.length();
      u8* buffer_ = static_cast<u8*>
         (alloca(size * sizeof(u8)));
      size_t read_so_far = 0;
      size_t start_of_line = 0;
      while (read_so_far < size)
      {
         size_t bytes_read = this->read_(buffer_ + read_so_far, 1);
         read_so_far += bytes_read;
         if (bytes_read == 0)
         {
            if (start_of_line != read_so_far)
            {
               lines.push_back(
                  string(reinterpret_cast<const char*> (buffer_ + start_of_line),
                     read_so_far - start_of_line));
            }
            break; // timeout occured on reading 1 byte
         }
         if (string(reinterpret_cast<const char*>
            (buffer_ + read_so_far - eol_len), eol_len) == eol)
         {
            // EOL found
            lines.push_back(
               string(reinterpret_cast<const char*> (buffer_ + start_of_line),
                  read_so_far - start_of_line));
            start_of_line = read_so_far;
         }
         if (read_so_far == size)
         {
            if (start_of_line != read_so_far)
            {
               lines.push_back(
                  string(reinterpret_cast<const char*> (buffer_ + start_of_line),
                     read_so_far - start_of_line));
            }
            break; // Reached the maximum read length
         }
      }
      return lines;
   }

   size_t
      serial::write(const string& data)
   {
      scoped_write_lock lock(this->m_pimpl);
      return this->write_(reinterpret_cast<const u8*>(data.c_str()),
         (size_t)data.length());
   }

   size_t
      serial::write(const memory& data)
   {
      scoped_write_lock lock(this->m_pimpl);
      return this->write_(data.get_data(), (size_t)data.size());
   }

   size_t
      serial::write(const u8* data, size_t size)
   {
      scoped_write_lock lock(this->m_pimpl);
      return this->write_(data, size);
   }

   size_t
      serial::write_(const u8* data, size_t length)
   {
      return m_pimpl->write(data, length);
   }

   void
      serial::setPort(const string& port)
   {
      scoped_read_lock rlock(this->m_pimpl);
      scoped_write_lock wlock(this->m_pimpl);
      bool was_open = m_pimpl->isOpen();
      if (was_open) close();
      m_pimpl->setPort(port);
      if (was_open) open();
   }

   string
      serial::getPort() const
   {
      return m_pimpl->getPort();
   }

   void
      serial::setTimeout(timeout& timeout)
   {
      m_pimpl->set_timeout(timeout);
   }

   timeout
      serial::getTimeout() const
   {
      return m_pimpl->getTimeout();
   }

   void
      serial::setBaudrate(u32 baudrate)
   {
      m_pimpl->setBaudrate(baudrate);
   }

   u32
      serial::getBaudrate() const
   {
      return u32(m_pimpl->getBaudrate());
   }

   void
      serial::setBytesize(enum_byte_size ebytesize)
   {
      m_pimpl->setBytesize(ebytesize);
   }

   enum_byte_size
      serial::getBytesize() const
   {
      return m_pimpl->getBytesize();
   }

   void
      serial::setParity(enum_parity eparity)
   {
      m_pimpl->setParity(eparity);
   }

   enum_parity
      serial::getParity() const
   {
      return m_pimpl->getParity();
   }

   void
      serial::setStopbits(enum_stop_bit estopbit)
   {
      m_pimpl->setStopbits(estopbit);
   }

   enum_stop_bit
      serial::getStopbits() const
   {
      return m_pimpl->getStopbits();
   }

   void
      serial::setFlowcontrol(enum_flow_control eflowcontrol)
   {
      m_pimpl->setFlowcontrol(eflowcontrol);
   }

   enum_flow_control
      serial::getFlowcontrol() const
   {
      return m_pimpl->getFlowcontrol();
   }

   void serial::flush()
   {
      scoped_read_lock rlock(this->m_pimpl);
      scoped_write_lock wlock(this->m_pimpl);
      m_pimpl->flush();
   }

   void serial::flushInput()
   {
      scoped_read_lock lock(mutex());
      m_pimpl->flushInput();
   }

   void serial::flushOutput()
   {
      scoped_write_lock lock(this->m_pimpl);
      m_pimpl->flushOutput();
   }

   void serial::sendBreak(int duration)
   {
      m_pimpl->sendBreak(duration);
   }

   void serial::setBreak(bool level)
   {
      m_pimpl->setBreak(level);
   }

   void serial::setRTS(bool level)
   {
      m_pimpl->setRTS(level);
   }

   void serial::setDTR(bool level)
   {
      m_pimpl->setDTR(level);
   }

   bool serial::waitForChange()
   {
      return m_pimpl->waitForChange();
   }

   bool serial::getCTS()
   {
      return m_pimpl->getCTS();
   }

   bool serial::getDSR()
   {
      return m_pimpl->getDSR();
   }

   bool serial::getRI()
   {
      return m_pimpl->getRI();
   }

   bool serial::getCD()
   {
      return m_pimpl->getCD();
   }


} // namespace serial



