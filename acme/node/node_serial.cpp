/* Copyright 2012 William Woodall and John Harrison */
#include "framework.h"
//
//#if defined(WINDOWS_DESKTOP) || defined(LINUX) || defined(MACOS)
//
//#if !defined(_WIN32) && !defined(__OpenBSD__) && !defined(__FreeBSD__)
//# include <alloca.h>
//#endif
//
//#if defined (__MINGW32__)
//# define alloca __builtin_alloca
//#endif
//
////#include "serial/serial.h"
//
//#ifdef _WIN32
//#include "windows/serial.h"
//#else
////#include "posix/serial.h"
//#endif
//
////using std::invalid_argument;
////using std::minimum;
////using std::numeric_limits;
////using std::vector;
////using std::size_t;
////using std::string;
////using serial::Timeout;
////using serial::serial;
////using serial::serial_exception;
////using serial::io_exception;
////using serial::enum_byte_size;
////using serial::enum_parity;
////using serial::enum_stop_bit;
////using serial::enum_flow_control;
//
//
//namespace serial
//{
//
//
////   class scoped_read_lock
////   {
////   public:
////
////      serial * m_pserial;
////
////
////      scoped_read_lock(serial * pserial) : m_pserial(pserial)
////      {
////         this->m_pserial->readLock();
////      }
////
////      ~scoped_read_lock()
////      {
////         this->m_pserial->readUnlock();
////      }
////
////   private:
////      // Disable copy constructors
////      scoped_read_lock(const scoped_read_lock &);
////
////      const scoped_read_lock & operator=(scoped_read_lock);
////
////   };
////
////   class scoped_write_lock
////   {
////   public:
////
////
////      serial * m_pserial;
////
////      scoped_write_lock(serial * pserial) : m_pserial(pserial)
////      {
////         this->m_pserial->writeLock();
////      }
////
////      ~scoped_write_lock()
////      {
////         this->m_pserial->writeUnlock();
////      }
////
////   private:
////      // Disable copy constructors
////      scoped_write_lock(const scoped_write_lock &);
////
////      const scoped_write_lock & operator=(scoped_write_lock);
////
////
////   };
//
//   serial::serial()
//   {
//
//   }
//
//
//   serial::~serial()
//   {
//   }
//
//
//   ::e_status serial::initialize_serial(const string & port, u32 baudrate, timeout timeout,
//      enum_byte_size ebytesize, enum_parity eparity, enum_stop_bit estopbit,
//   enum_flow_control eflowcontrol)
//   {
//
//      return ::success;
//
//   }
//
//
//timeout timeout::simpleTimeout(u32 uTimeout)
//   {
//#ifdef WINDOWS
//      return timeout(MAXDWORD, uTimeout, MAXDWORD, uTimeout, 0);
//#else
//      return timeout(maximum(), uTimeout, 0, uTimeout, 0);
//#endif
//   }
//
//
//   void
//   serial::open()
//   {
//
//   }
//
//   void
//   serial::close()
//   {
//
//   }
//
//
//   bool serial::isOpen() const
//   {
//
//      return false;
//
//   }
//
//
//   size_t serial::available()
//   {
//
//      return 0;
//
//   }
//
//
//   bool serial::waitReadable()
//   {
//
//      return false;
//
//   }
//
//
//   void serial::waitByteTimes(size_t count)
//   {
//
//   }
//
//
//   size_t serial::_read(u8 * buffer, size_t size)
//   {
//
//      return 0;
//
//   }
//
//
//   size_t serial::read(u8 * buffer, size_t size)
//   {
//
//      scoped_read_lock lock(this);
//
//      return _read(buffer, size);
//
//   }
//
//
//   size_t serial::read(memory & buffer, size_t size)
//   {
//      scoped_read_lock lock(this);
//      memory bufferRead;
//      bufferRead.set_size(size);
//      size_t bytes_read = this->read(bufferRead.get_data(), (size_t) bufferRead.get_size());
//      buffer.append(bufferRead);
//      return bytes_read;
//   }
//
//
//   size_t serial::read(string & buffer, size_t size)
//   {
//      scoped_read_lock lock(this);
//      u8 * buffer_ = new u8[size];
//      size_t bytes_read = this->read(buffer_, size);
//      buffer.append(reinterpret_cast<const char *>(buffer_), bytes_read);
//      delete[] buffer_;
//      return bytes_read;
//   }
//
//
//   string serial::read(size_t size)
//   {
//
//      string buffer;
//
//      this->read(buffer, size);
//
//      return buffer;
//
//   }
//
//
//   size_t serial::readline(string & buffer, size_t size, string eol)
//   {
//
//#ifdef WINDOWS
//
//      return this->readline(buffer, size, eol);
//
//#else
//
//      scoped_read_lock lock(this);
//      size_t eol_len = eol.length();
//      u8 * buffer_ = static_cast<u8 *>
//      (alloca(size * sizeof(u8)));
//      size_t read_so_far = 0;
//      while (true)
//      {
//         size_t bytes_read = this->_read(buffer_ + read_so_far, 1);
//         read_so_far += bytes_read;
//         if (bytes_read == 0)
//         {
//            break; // Timeout occured on reading 1 byte
//         }
//         if (string(reinterpret_cast<const char *>
//                    (buffer_ + read_so_far - eol_len), eol_len) == eol)
//         {
//            break; // EOL found
//         }
//         if (read_so_far == size)
//         {
//            break; // Reached the maximum read length
//         }
//      }
//      buffer.append(reinterpret_cast<const char *> (buffer_), read_so_far);
//      return read_so_far;
//
//#endif
//
//   }
//
//
//   string serial::readline(size_t size, string eol)
//   {
//
//      string buffer;
//
//      this->readline(buffer, size, eol);
//
//      return buffer;
//
//   }
//
//
//   string_array serial::readlines(size_t size, string eol)
//   {
//
//      scoped_read_lock lock(this);
//      string_array lines;
//      size_t eol_len = (size_t) eol.length();
//      u8 * buffer_ = static_cast<u8 *>
//      (alloca(size * sizeof(u8)));
//      size_t read_so_far = 0;
//      size_t start_of_line = 0;
//      while (read_so_far < size)
//      {
//         size_t bytes_read = this->_read(buffer_ + read_so_far, 1);
//         read_so_far += bytes_read;
//         if (bytes_read == 0)
//         {
//            if (start_of_line != read_so_far)
//            {
//               lines.push_back(
//                  string(reinterpret_cast<const char *> (buffer_ + start_of_line),
//                         read_so_far - start_of_line));
//            }
//            break; // Timeout occured on reading 1 byte
//         }
//         if (string(reinterpret_cast<const char *>
//                    (buffer_ + read_so_far - eol_len), eol_len) == eol)
//         {
//            // EOL found
//            lines.push_back(
//               string(reinterpret_cast<const char *> (buffer_ + start_of_line),
//                      read_so_far - start_of_line));
//            start_of_line = read_so_far;
//         }
//         if (read_so_far == size)
//         {
//            if (start_of_line != read_so_far)
//            {
//               lines.push_back(
//                  string(reinterpret_cast<const char *> (buffer_ + start_of_line),
//                         read_so_far - start_of_line));
//            }
//            break; // Reached the maximum read length
//         }
//      }
//
//      return lines;
//
//   }
//
//
//   size_t serial::write(const string & data)
//   {
//
//      scoped_write_lock lock(this);
//
//      return this->_write(reinterpret_cast<const u8 *>(data.c_str()), (size_t) data.length());
//
//   }
//
//
//   size_t serial::write(const memory & data)
//   {
//
//      scoped_write_lock lock(this);
//
//      return this->_write(data.get_data(), (size_t) data.size());
//
//   }
//
//
//   size_t serial::write(const u8 * data, size_t size)
//   {
//
//      scoped_write_lock lock(this);
//
//      return this->_write(data, size);
//
//   }
//
//
//   size_t serial::_write(const u8 * data, size_t length)
//   {
//
//      return write(data, length);
//
//   }
//
//
//   void serial::setPort(const string & port)
//   {
//      scoped_read_lock rlock(this);
//      scoped_write_lock wlock(this);
//      bool was_open = this->isOpen();
//      if (was_open) close();
//      this->setPort(port);
//      if (was_open) open();
//   }
//
//
//   string serial::getPort() const
//   {
//
//      return "";
//
//   }
//
//
//   void serial::set_timeout(const timeout & timeout)
//   {
//
//
//
//   }
//
//
//   timeout serial::getTimeout() const
//   {
//
//      return 0;
//
//   }
//
//
//   void serial::setBaudrate(u32 baudrate)
//   {
//
//      this->setBaudrate(baudrate);
//
//   }
//
//
//   u32 serial::getBaudrate() const
//   {
//
//      return 9600;
//
//   }
//
//
//   void serial::setBytesize(enum_byte_size ebytesize)
//   {
//
//   }
//
//
//   enum_byte_size serial::getBytesize() const
//   {
//
//      return e_byte_size_eight;
//
//   }
//
//
//   void serial::setParity(enum_parity eparity)
//   {
//
//   }
//
//
//   enum_parity serial::getParity() const
//   {
//
//      return e_parity_none;
//
//   }
//
//
//   void serial::setStopbits(enum_stop_bit estopbit)
//   {
//
//
//   }
//
//
//   enum_stop_bit serial::getStopbits() const
//   {
//
//      return e_stop_bit_one;
//
//   }
//
//
//   void serial::setFlowcontrol(enum_flow_control eflowcontrol)
//   {
//
//
//   }
//
//
//   enum_flow_control serial::getFlowcontrol() const
//   {
//
//      return e_flow_control_none;
//
//   }
//
//
//   void serial::flush()
//   {
//
//      scoped_read_lock rlock(this);
//      scoped_write_lock wlock(this);
//
//      _flush();
//
//   }
//
//
//   void serial::flushInput()
//   {
//
//      scoped_read_lock lock(this);
//
//      _flushInput();
//
//   }
//
//
//   void serial::flushOutput()
//   {
//
//      scoped_write_lock lock(this);
//
//      _flushOutput();
//
//   }
//
//
//   void serial::sendBreak(int duration)
//   {
//
//
//   }
//
//
//   void serial::setBreak(bool level)
//   {
//
//
//   }
//
//
//   void serial::setRTS(bool level)
//   {
//
//
//   }
//
//
//   void serial::setDTR(bool level)
//   {
//
//
//   }
//
//
//   bool serial::waitForChange()
//   {
//
//      return false;
//
//   }
//
//
//   bool serial::getCTS()
//   {
//
//      return false;
//
//   }
//
//
//   bool serial::getDSR()
//   {
//
//      return false;
//
//   }
//
//
//   bool serial::getRI()
//   {
//
//      return false;
//
//   }
//
//
//   bool serial::getCD()
//   {
//
//      return false;
//
//   }
//
//
//   void serial::readLock()
//   {
//
//
//   }
//
//
//   void serial::readUnlock()
//   {
//
//
//   }
//
//
//   void serial::writeLock()
//   {
//
//
//   }
//
//
//   void serial::writeUnlock()
//   {
//
//
//   }
//
//
//   void serial::_flush()
//   {
//
//   }
//
//
//   void serial::_flushOutput()
//   {
//
//
//   }
//
//
//   void serial::_flushInput()
//   {
//
//
//   }
//
//
//
//} // namespace serial
//
//#endif
//
