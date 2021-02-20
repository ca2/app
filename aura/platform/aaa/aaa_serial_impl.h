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
using serial::Serial;
using serial::SerialException;
using serial::IOException;
using serial::bytesize_t;
using serial::parity_t;
using serial::stopbits_t;
using serial::flowcontrol_t;

class Serial::ScopedReadLock
{
public:
   ScopedReadLock(SerialImpl * pimpl) : pimpl_(pimpl)
   {
      this->pimpl_->readLock();
   }
   ~ScopedReadLock()
   {
      this->pimpl_->readUnlock();
   }
private:
   // Disable copy constructors
   ScopedReadLock(const ScopedReadLock &);
   const ScopedReadLock & operator=(ScopedReadLock);

   SerialImpl * pimpl_;
};

class Serial::ScopedWriteLock
{
public:
   ScopedWriteLock(SerialImpl * pimpl) : pimpl_(pimpl)
   {
      this->pimpl_->writeLock();
   }
   ~ScopedWriteLock()
   {
      this->pimpl_->writeUnlock();
   }
private:
   // Disable copy constructors
   ScopedWriteLock(const ScopedWriteLock &);
   const ScopedWriteLock & operator=(ScopedWriteLock);
   SerialImpl * pimpl_;
};

Serial::Serial(::object * pobject, const string & port, u32 baudrate, serial::Timeout timeout,
   bytesize_t bytesize, parity_t parity, stopbits_t stopbits,
   flowcontrol_t flowcontrol)
   : ::object(pobject),
   pimpl_(__new(SerialImpl(pobject, port, baudrate, bytesize, parity, stopbits, flowcontrol)))
{
   pimpl_->setTimeout(timeout);
}

Serial::~Serial()
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
Serial::open()
{
   pimpl_->open();
}

void
Serial::close()
{
   pimpl_->close();
}

bool
Serial::isOpen() const
{
   return pimpl_->isOpen();
}

size_t
Serial::available()
{
   return pimpl_->available();
}

bool
Serial::waitReadable()
{
   serial::Timeout timeout(pimpl_->getTimeout());
   return pimpl_->waitReadable(timeout.read_timeout_constant);
}

void
Serial::waitByteTimes(size_t count)
{
   pimpl_->waitByteTimes(count);
}

size_t
Serial::read_(u8 * buffer, size_t size)
{
   return this->pimpl_->read(buffer, size);
}

size_t
Serial::read(u8 * buffer, size_t size)
{
   ScopedReadLock lock(this->pimpl_);
   return this->pimpl_->read(buffer, size);
}

size_t
Serial::read(memory & buffer, size_t size)
{
   ScopedReadLock lock(this->pimpl_);
   memory bufferRead;
   bufferRead.set_size(size);
   size_t bytes_read = this->pimpl_->read(bufferRead.get_data(), (size_t)bufferRead.get_size());
   buffer.append(bufferRead);
   return bytes_read;
}

size_t
Serial::read(string & buffer, size_t size)
{
   ScopedReadLock lock(this->pimpl_);
   u8 * buffer_ = new u8[size];
   size_t bytes_read = this->pimpl_->read(buffer_, size);
   buffer.append(reinterpret_cast<const char *>(buffer_), bytes_read);
   delete[] buffer_;
   return bytes_read;
}

string
Serial::read(size_t size)
{
   string buffer;
   this->read(buffer, size);
   return buffer;
}

size_t
Serial::readline(string & buffer, size_t size, string eol)
{
#ifdef WINDOWS
   return this->pimpl_->readline(buffer, size, eol);
#else
   ScopedReadLock lock(this->pimpl_);
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
Serial::readline(size_t size, string eol)
{
   string buffer;
   this->readline(buffer, size, eol);
   return buffer;
}

string_array
Serial::readlines(size_t size, string eol)
{
   ScopedReadLock lock(this->pimpl_);
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
Serial::write(const string & data)
{
   ScopedWriteLock lock(this->pimpl_);
   return this->write_(reinterpret_cast<const u8 *>(data.c_str()),
      (size_t)data.length());
}

size_t
Serial::write(const memory & data)
{
   ScopedWriteLock lock(this->pimpl_);
   return this->write_(data.get_data(), (size_t)data.size());
}

size_t
Serial::write(const u8 * data, size_t size)
{
   ScopedWriteLock lock(this->pimpl_);
   return this->write_(data, size);
}

size_t
Serial::write_(const u8 * data, size_t length)
{
   return pimpl_->write(data, length);
}

void
Serial::setPort(const string & port)
{
   ScopedReadLock rlock(this->pimpl_);
   ScopedWriteLock wlock(this->pimpl_);
   bool was_open = pimpl_->isOpen();
   if (was_open) close();
   pimpl_->setPort(port);
   if (was_open) open();
}

string
Serial::getPort() const
{
   return pimpl_->getPort();
}

void
Serial::setTimeout(serial::Timeout & timeout)
{
   pimpl_->setTimeout(timeout);
}

serial::Timeout
Serial::getTimeout() const
{
   return pimpl_->getTimeout();
}

void
Serial::setBaudrate(u32 baudrate)
{
   pimpl_->setBaudrate(baudrate);
}

u32
Serial::getBaudrate() const
{
   return u32(pimpl_->getBaudrate());
}

void
Serial::setBytesize(bytesize_t bytesize)
{
   pimpl_->setBytesize(bytesize);
}

bytesize_t
Serial::getBytesize() const
{
   return pimpl_->getBytesize();
}

void
Serial::setParity(parity_t parity)
{
   pimpl_->setParity(parity);
}

parity_t
Serial::getParity() const
{
   return pimpl_->getParity();
}

void
Serial::setStopbits(stopbits_t stopbits)
{
   pimpl_->setStopbits(stopbits);
}

stopbits_t
Serial::getStopbits() const
{
   return pimpl_->getStopbits();
}

void
Serial::setFlowcontrol(flowcontrol_t flowcontrol)
{
   pimpl_->setFlowcontrol(flowcontrol);
}

flowcontrol_t
Serial::getFlowcontrol() const
{
   return pimpl_->getFlowcontrol();
}

void Serial::flush()
{
   ScopedReadLock rlock(this->pimpl_);
   ScopedWriteLock wlock(this->pimpl_);
   pimpl_->flush();
}

void Serial::flushInput()
{
   ScopedReadLock lock(this->pimpl_);
   pimpl_->flushInput();
}

void Serial::flushOutput()
{
   ScopedWriteLock lock(this->pimpl_);
   pimpl_->flushOutput();
}

void Serial::sendBreak(int duration)
{
   pimpl_->sendBreak(duration);
}

void Serial::setBreak(bool level)
{
   pimpl_->setBreak(level);
}

void Serial::setRTS(bool level)
{
   pimpl_->setRTS(level);
}

void Serial::setDTR(bool level)
{
   pimpl_->setDTR(level);
}

bool Serial::waitForChange()
{
   return pimpl_->waitForChange();
}

bool Serial::getCTS()
{
   return pimpl_->getCTS();
}

bool Serial::getDSR()
{
   return pimpl_->getDSR();
}

bool Serial::getRI()
{
   return pimpl_->getRI();
}

bool Serial::getCD()
{
   return pimpl_->getCD();
}
