#pragma once
/* Copyright 2012 William Woodall and John Harrison */


////#include "serial/serial.h"
//
//#ifdef _WIN32
//#include "windows/windows_serial.h"
//#else
//#include "ansios/ansios_serial.h"
//#endif


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
using serial::Timeout;
using serial::serial;
using serial::serial_exception;
using serial::io_exception;
using serial::enum_byte_size;
using serial::enum_parity;
using serial::enum_stop_bit;
using serial::enum_flow_control;

class serial::scoped_read_lock
{
public:
   scoped_read_lock(serial_impl * pimpl) : pimpl_(pimpl)
   {
      this->pimpl_->readLock();
   }
   ~scoped_read_lock()
   {
      this->pimpl_->readUnlock();
   }
private:
   // Disable copy constructors
   scoped_read_lock(const scoped_read_lock &);
   const scoped_read_lock & operator=(scoped_read_lock);

   serial_impl * pimpl_;
};

class serial::scoped_write_lock
{
public:
   scoped_write_lock(serial_impl * pimpl) : pimpl_(pimpl)
   {
      this->pimpl_->writeLock();
   }
   ~scoped_write_lock()
   {
      this->pimpl_->writeUnlock();
   }
private:
   // Disable copy constructors
   scoped_write_lock(const scoped_write_lock &);
   const scoped_write_lock & operator=(scoped_write_lock);
   serial_impl * pimpl_;
};

serial::serial(::object * pobject, const string & port, u32 baudrate, serial::Timeout timeout,
   enum_byte_size ebytesize, enum_parity eparity, enum_stop_bit estopbit,
   enum_flow_control eflowcontrol)
   : ::object(pobject),
   pimpl_(__new(serial_impl(pobject, port, baudrate, ebytesize, eparity, estopbit, eflowcontrol)))
{
   pimpl_->setTimeout(timeout);
}

serial::~serial()
{
}

serial::Timeout Timeout::simpleTimeout(u32 timeout)
{
#ifdef WINDOWS
   return Timeout(MAXDWORD, timeout, MAXDWORD, timeout, 0);
#else
   return Timeout(maximum(), timeout, 0, timeout, 0);
#endif
}


void
serial::open()
{
   pimpl_->open();
}

void
serial::close()
{
   pimpl_->close();
}

bool
serial::isOpen() const
{
   return pimpl_->isOpen();
}

size_t
serial::available()
{
   return pimpl_->available();
}

bool
serial::waitReadable()
{
   serial::Timeout timeout(pimpl_->getTimeout());
   return pimpl_->waitReadable(timeout.read_timeout_constant);
}

void
serial::waitByteTimes(size_t count)
{
   pimpl_->waitByteTimes(count);
}

size_t
serial::read_(u8 * buffer, size_t size)
{
   return this->pimpl_->read(buffer, size);
}

size_t
serial::read(u8 * buffer, size_t size)
{
   scoped_read_lock lock(this->pimpl_);
   return this->pimpl_->read(buffer, size);
}

size_t
serial::read(memory & buffer, size_t size)
{
   scoped_read_lock lock(this->pimpl_);
   memory bufferRead;
   bufferRead.set_size(size);
   size_t bytes_read = this->pimpl_->read(bufferRead.get_data(), (size_t)bufferRead.get_size());
   buffer.append(bufferRead);
   return bytes_read;
}

size_t
serial::read(string & buffer, size_t size)
{
   scoped_read_lock lock(this->pimpl_);
   u8 * buffer_ = memory_new u8[size];
   size_t bytes_read = this->pimpl_->read(buffer_, size);
   buffer.append(reinterpret_cast<const char *>(buffer_), bytes_read);
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
serial::readline(string & buffer, size_t size, string eol)
{
#ifdef WINDOWS
   return this->pimpl_->readline(buffer, size, eol);
#else
   scoped_read_lock lock(this->pimpl_);
   size_t eol_len = eol.length();
   u8 * buffer_ = static_cast<u8 *>
      (alloca(size * sizeof(u8)));
   size_t read_so_far = 0;
   while (true)
   {
      size_t bytes_read = this->read_(buffer_ + read_so_far, 1);
      read_so_far += bytes_read;
      if (bytes_read == 0)
      {
         break; // Timeout occured on reading 1 byte
      }
      if (string(reinterpret_cast<const char *>
         (buffer_ + read_so_far - eol_len), eol_len) == eol)
      {
         break; // EOL found
      }
      if (read_so_far == size)
      {
         break; // Reached the maximum read length
      }
   }
   buffer.append(reinterpret_cast<const char *> (buffer_), read_so_far);
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
   scoped_read_lock lock(this->pimpl_);
   string_array lines;
   size_t eol_len = (size_t)eol.length();
   u8 * buffer_ = static_cast<u8 *>
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
               string(reinterpret_cast<const char *> (buffer_ + start_of_line),
                  read_so_far - start_of_line));
         }
         break; // Timeout occured on reading 1 byte
      }
      if (string(reinterpret_cast<const char *>
         (buffer_ + read_so_far - eol_len), eol_len) == eol)
      {
         // EOL found
         lines.push_back(
            string(reinterpret_cast<const char *> (buffer_ + start_of_line),
               read_so_far - start_of_line));
         start_of_line = read_so_far;
      }
      if (read_so_far == size)
      {
         if (start_of_line != read_so_far)
         {
            lines.push_back(
               string(reinterpret_cast<const char *> (buffer_ + start_of_line),
                  read_so_far - start_of_line));
         }
         break; // Reached the maximum read length
      }
   }
   return lines;
}

size_t
serial::write(const string & data)
{
   scoped_write_lock lock(this->pimpl_);
   return this->write_(reinterpret_cast<const u8 *>(data.c_str()),
      (size_t)data.length());
}

size_t
serial::write(const memory & data)
{
   scoped_write_lock lock(this->pimpl_);
   return this->write_(data.get_data(), (size_t)data.size());
}

size_t
serial::write(const u8 * data, size_t size)
{
   scoped_write_lock lock(this->pimpl_);
   return this->write_(data, size);
}

size_t
serial::write_(const u8 * data, size_t length)
{
   return pimpl_->write(data, length);
}

void
serial::setPort(const string & port)
{
   scoped_read_lock rlock(this->pimpl_);
   scoped_write_lock wlock(this->pimpl_);
   bool was_open = pimpl_->isOpen();
   if (was_open) close();
   pimpl_->setPort(port);
   if (was_open) open();
}

string
serial::getPort() const
{
   return pimpl_->getPort();
}

void
serial::setTimeout(serial::Timeout & timeout)
{
   pimpl_->setTimeout(timeout);
}

serial::Timeout
serial::getTimeout() const
{
   return pimpl_->getTimeout();
}

void
serial::setBaudrate(u32 baudrate)
{
   pimpl_->setBaudrate(baudrate);
}

u32
serial::getBaudrate() const
{
   return u32(pimpl_->getBaudrate());
}

void
serial::setBytesize(enum_byte_size ebytesize)
{
   pimpl_->setBytesize(ebytesize);
}

enum_byte_size
serial::getBytesize() const
{
   return pimpl_->getBytesize();
}

void
serial::setParity(enum_parity eparity)
{
   pimpl_->setParity(eparity);
}

enum_parity
serial::getParity() const
{
   return pimpl_->getParity();
}

void
serial::setStopbits(enum_stop_bit estopbit)
{
   pimpl_->setStopbits(estopbit);
}

enum_stop_bit
serial::getStopbits() const
{
   return pimpl_->getStopbits();
}

void
serial::setFlowcontrol(enum_flow_control eflowcontrol)
{
   pimpl_->setFlowcontrol(eflowcontrol);
}

enum_flow_control
serial::getFlowcontrol() const
{
   return pimpl_->getFlowcontrol();
}

void serial::flush()
{
   scoped_read_lock rlock(this->pimpl_);
   scoped_write_lock wlock(this->pimpl_);
   pimpl_->flush();
}

void serial::flushInput()
{
   scoped_read_lock lock(this->pimpl_);
   pimpl_->flushInput();
}

void serial::flushOutput()
{
   scoped_write_lock lock(this->pimpl_);
   pimpl_->flushOutput();
}

void serial::sendBreak(int duration)
{
   pimpl_->sendBreak(duration);
}

void serial::setBreak(bool level)
{
   pimpl_->setBreak(level);
}

void serial::setRTS(bool level)
{
   pimpl_->setRTS(level);
}

void serial::setDTR(bool level)
{
   pimpl_->setDTR(level);
}

bool serial::waitForChange()
{
   return pimpl_->waitForChange();
}

bool serial::getCTS()
{
   return pimpl_->getCTS();
}

bool serial::getDSR()
{
   return pimpl_->getDSR();
}

bool serial::getRI()
{
   return pimpl_->getRI();
}

bool serial::getCD()
{
   return pimpl_->getCD();
}
