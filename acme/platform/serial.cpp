#include "framework.h"
/* Copyright 2012 William Woodall and John Harrison */
#include "acme/platform/serial.h"
#include "acme/parallelization/synchronous_lock.h"
//#include "acme/prototype/prototype/function.h"
#include "acme/prototype/prototype/memory.h"
//#include "acme/prototype/collection/string_array.h"


#if !defined(_WIN32) && !defined(__BSD__)
# include <alloca.h>
#endif

#if defined (__MINGW32__)
# define alloca __builtin_alloca
#endif

namespace serial
{

   
   serial::serial()
   {
   }
   
   
   void serial::initialize_serial(const string& port, unsigned int baudrate, struct timeout timeout,
      enum_byte_size ebytesize, enum_parity eparity, enum_stop_bit estopbit,
      enum_flow_control eflowcontrol)
      //:
      //m_pimpl(__initialize_new serial_impl(port, baudrate, ebytesize, eparity, estopbit, eflowcontrol)))
   {
//      set_timeout(timeout;

      throw ::exception(error_no_factory);

   }


   serial::~serial()
   {

   }


   timeout timeout::simpleTimeout(const class time & time)
   {

      return 0;

   }

//#ifdef WINDOWS
//      return struct timeout(::time::infinite(), time, MAXDWORD, time, 0);
//#else
//      return ::serial::timeout(::time::infinite(), time, 0, time, 0);
//#endif
//   }


   void serial::open()
   {

      //m_pimpl->open();

   }


   void serial::close()
   {

      //m_pimpl->close();

   }


   bool serial::isOpen() const
   {
      
      //return m_pimpl->isOpen();
      return false;

   }


   size_t serial::available()
   {

      //return m_pimpl->available();
      
      return 0;

   }


   bool serial::waitReadable()
   {

      //timeout timeout(m_pimpl->getTimeout());
      // 
      //return m_pimpl->waitReadable(timeout.m_timeReadTimeoutConstant);

      return false;

   }


   void serial::waitByteTimes(size_t count)
   {
      
      //m_pimpl->waitByteTimes(count);

   }


   size_t serial::_read(unsigned char* buffer, size_t size)
   {

      //return this->m_pimpl->read(buffer, size);
      return 0;

   }


   size_t serial::read(unsigned char* buffer, size_t size)
   {
      
      synchronous_lock lock(read_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      return _read(buffer, size);

      //return 0;

   }

   
   size_t serial::read(memory& buffer, size_t size)
   {

      synchronous_lock lock(read_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      memory bufferRead;

      bufferRead.set_size(size);

      size_t bytes_read = _read(bufferRead.data(), (size_t)bufferRead.size());

      buffer.append(bufferRead);

      return bytes_read;

   }


   size_t serial::read(string& buffer, size_t size)
   {

      synchronous_lock lock(read_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      memory mem;
      
      mem.set_size(size);

      size_t bytes_read = _read(mem.data(), size);

      mem.set_size(bytes_read);
      
      buffer.append((const_char_pointer )mem.data(), bytes_read);

      return bytes_read;

   }


   string serial::read(size_t size)
   {

      string buffer;

      this->read(buffer, size);

      return buffer;

   }


   size_t serial::readline(string& buffer, size_t size, string eol)
   {

      return 0;

   }


   string serial::readline(size_t size, string eol)
   {
      
      string buffer;

      this->readline(buffer, size, eol);

      return buffer;

   }


   string_array_base serial::readlines(size_t size, string eol)
   {

      synchronous_lock lock(read_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      string_array_base lines;

      size_t eol_len = (size_t)eol.length();

      memory memory;

      memory.set_size(size * sizeof(unsigned char));

      unsigned char* buffer_ = static_cast<unsigned char*>(memory.data());

      size_t read_so_far = 0;

      size_t start_of_line = 0;

      while (read_so_far < size)
      {

         size_t bytes_read = this->_read(buffer_ + read_so_far, 1);

         read_so_far += bytes_read;

         if (bytes_read == 0)
         {

            if (start_of_line != read_so_far)
            {

               lines.add(string(reinterpret_cast<const_char_pointer >(buffer_ + start_of_line), read_so_far - start_of_line));

            }

            break; // timeout occured on reading 1 unsigned char

         }

         if (string(reinterpret_cast<const_char_pointer >(buffer_ + read_so_far - eol_len), eol_len) == eol)
         {

            // EOL found
            lines.add(string(reinterpret_cast<const_char_pointer >(buffer_ + start_of_line), read_so_far - start_of_line));

            start_of_line = read_so_far;

         }

         if (read_so_far == size)
         {

            if (start_of_line != read_so_far)
            {

               lines.add(string(reinterpret_cast<const_char_pointer >(buffer_ + start_of_line), read_so_far - start_of_line));

            }

            break; // Reached the maximum read length

         }

      }

      return lines;

   }

   
   size_t serial::write(const string& data)
   {

      synchronous_lock lock(write_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      return _write(reinterpret_cast<const unsigned char*>(data.c_str()), (size_t)data.length());

   }


   size_t serial::write(const memory& data)
   {

      synchronous_lock lock(write_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      return _write(data.data(), (size_t)data.size());

   }


   size_t serial::write(const unsigned char* data, size_t size)
   {
      
      synchronous_lock lock(write_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      return _write(data, size);

   }

   
   size_t serial::_write(const unsigned char* data, size_t length)
   {

      return 0;

   }


   void serial::setPort(const string& port)
   {

      synchronous_lock readlock(read_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      synchronous_lock writelock(write_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      bool was_open = isOpen();
      
      if (was_open)
      {

         close();

      }

      _setPort(port);

      if (was_open)
      {

         open();

      }

   }


   string serial::getPort() const
   {

      // return m_pimpl->getPort();

      return "";

   }


   void serial::set_timeout(const ::serial::timeout& timeout)
   {

      //m_pimpl->set_timeout(timeout);

   }


   struct timeout serial::getTimeout() const
   {

      return nullptr;

   }


   void serial::setBaudrate(unsigned int baudrate)
   {

      //m_pimpl->setBaudrate(baudrate);

   }


   unsigned int serial::getBaudrate() const
   {
      
      //return unsigned int(m_pimpl->getBaudrate());

      return 0;

   }


   void serial::setBytesize(enum_byte_size ebytesize)
   {

      //m_pimpl->setBytesize(ebytesize);

   }


   enum_byte_size serial::getBytesize() const
   {

      //return m_pimpl->getBytesize();

      return e_byte_size_eight;

   }


   void serial::setParity(enum_parity eparity)
   {

      //m_pimpl->setParity(eparity);

   }


   enum_parity serial::getParity() const
   {
      
      //return m_pimpl->getParity();

      return e_parity_none;


   }


   void serial::setStopbits(enum_stop_bit estopbit)
   {

      //m_pimpl->setStopbits(estopbit);

   }


   enum_stop_bit serial::getStopbits() const
   {

      //return m_pimpl->getStopbits();

      return e_stop_bit_one;

   }


   void serial::setFlowcontrol(enum_flow_control eflowcontrol)
   {

      //m_pimpl->setFlowcontrol(eflowcontrol);

   }


   enum_flow_control serial::getFlowcontrol() const
   {

      //return m_pimpl->getFlowcontrol();

      return e_flow_control_none;

   }

   
   void serial::flush()
   {
   
      synchronous_lock readlock(read_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      synchronous_lock writelock(write_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      _flush();

   }


   void serial::flushInput()
   {
      
      synchronous_lock readlock(read_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      _flushInput();

   }


   void serial::flushOutput()
   {

      synchronous_lock writelock(write_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      _flushOutput();

   }


   void serial::sendBreak(int time)
   {

      //m_pimpl->sendBreak(time);

   }


   void serial::setBreak(bool level)
   {

      //m_pimpl->setBreak(level);

   }


   void serial::setRTS(bool level)
   {

      //m_pimpl->setRTS(level);

   }


   void serial::setDTR(bool level)
   {
      
      //m_pimpl->setDTR(level);

   }


   bool serial::waitForChange()
   {
      
      //return m_pimpl->waitForChange();

      return false;

   }


   bool serial::getCTS()
   {

      //return m_pimpl->getCTS();

      return false;

   }


   bool serial::getDSR()
   {
      
      //return m_pimpl->getDSR();

      return false;

   }


   bool serial::getRI()
   {

      //return m_pimpl->getRI();

      return false;

   }


   bool serial::getCD()
   {
   
      //return m_pimpl->getCD();

      return false;

   }


   ::particle * serial::read_synchronization()
   {

      return nullptr;

   }


   ::particle * serial::write_synchronization()
   {

      return nullptr;

   }

   //void serial::writeLock()
   //{

   //}


   //void serial::writeUnlock()
   //{

   //}



   void serial::_setPort(const string &)
   {

   }


   void serial::_flush()
   {


   }


   void serial::_flushOutput()
   {


   }


   void serial::_flushInput()
   {


   }


} // namespace serial





namespace serial
{


//   class scoped_read_lock
//   {
//   public:
//
//      serial * m_pserial;
//
//
//      scoped_read_lock(serial * pserial) : m_pserial(pserial)
//      {
//         this->m_pserial->readLock();
//      }
//
//      ~scoped_read_lock()
//      {
//         this->m_pserial->readUnlock();
//      }
//
//   private:
//      // Disable copy constructors
//      scoped_read_lock(const scoped_read_lock &);
//
//      const scoped_read_lock & operator=(scoped_read_lock);
//
//   };
//
//   class scoped_write_lock
//   {
//   public:
//
//
//      serial * m_pserial;
//
//      scoped_write_lock(serial * pserial) : m_pserial(pserial)
//      {
//         this->m_pserial->writeLock();
//      }
//
//      ~scoped_write_lock()
//      {
//         this->m_pserial->writeUnlock();
//      }
//
//   private:
//      // Disable copy constructors
//      scoped_write_lock(const scoped_write_lock &);
//
//      const scoped_write_lock & operator=(scoped_write_lock);
//
//
//   };


//
//   void serial::initialize_serial(const string & port, unsigned int baudrate, timeout timeout,
//                                        enum_byte_size ebytesize, enum_parity eparity, enum_stop_bit estopbit,
//                                        enum_flow_control eflowcontrol)
//   {
//
//      return ::success;
//
//   }
//
//
//   timeout timeout::simpleTimeout(unsigned int uTimeout)
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
//   size_t serial::_read(unsigned char * buffer, size_t size)
//   {
//
//      return 0;
//
//   }
//
//
//   size_t serial::read(unsigned char * buffer, size_t size)
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
//   size_t serial::read(string & buffer, size_t
//   size)
//{
//   scoped_read_lock lock(this);
//   unsigned char * buffer_ = ___new unsigned char[size];
//   size_t bytes_read = this->read(buffer_, size);
//   buffer.append(reinterpret_cast
//   <const_char_pointer >(buffer_), bytes_read
//   );
//   delete[]
//   buffer_;
//   return
//   bytes_read;
//}
//
//
//string serial::read(size_t size)
//{
//
//   string buffer;
//
//   this->read(buffer, size);
//
//   return buffer;
//
//}
//
//
//size_t serial::readline(string & buffer, size_t
//size,
//string eol
//)
//{
//
//#ifdef WINDOWS
//
//return this->readline(buffer, size, eol);
//
//#else
//
//scoped_read_lock lock(this);
//size_t eol_len = eol.length();
//unsigned char * buffer_ = static_cast<unsigned char *>
//(alloca(size * sizeof(unsigned char)));
//size_t read_so_far = 0;
//while (true)
//{
//size_t bytes_read = this->_read(buffer_ + read_so_far, 1);
//read_so_far +=
//bytes_read;
//if (bytes_read == 0)
//{
//break; // Timeout occured on reading 1 unsigned char
//}
//if (string(reinterpret_cast
// <const_char_pointer >
//(buffer_
//+ read_so_far - eol_len), eol_len) == eol)
//{
//break; // EOL found
//}
//if (read_so_far == size)
//{
//break; // Reached the maximum read length
//}
//}
//buffer.append(reinterpret_cast
// <const_char_pointer >(buffer_), read_so_far
//);
//return
//read_so_far;
//
//#endif
//
//}
//
//
//string serial::readline(size_t size, string eol)
//{
//
//   string buffer;
//
//   this->readline(buffer, size, eol);
//
//   return buffer;
//
//}
//
//
//string_array_base serial::readlines(size_t size, string eol)
//{
//
//   scoped_read_lock lock(this);
//   string_array_base lines;
//   size_t eol_len = (size_t) eol.length();
//   unsigned char * buffer_ = static_cast<unsigned char *>
//   (alloca(size * sizeof(unsigned char)));
//   size_t read_so_far = 0;
//   size_t start_of_line = 0;
//   while (read_so_far < size)
//   {
//      size_t bytes_read = this->_read(buffer_ + read_so_far, 1);
//      read_so_far += bytes_read;
//      if (bytes_read == 0)
//      {
//         if (start_of_line != read_so_far)
//         {
//            lines.add(
//               string(reinterpret_cast<const_char_pointer >(buffer_ + start_of_line),
//                      read_so_far - start_of_line));
//         }
//         break; // Timeout occured on reading 1 unsigned char
//      }
//      if (string(reinterpret_cast<const_char_pointer >
//                 (buffer_ + read_so_far - eol_len), eol_len) == eol)
//      {
//         // EOL found
//         lines.add(
//            string(reinterpret_cast<const_char_pointer >(buffer_ + start_of_line),
//                   read_so_far - start_of_line));
//         start_of_line = read_so_far;
//      }
//      if (read_so_far == size)
//      {
//         if (start_of_line != read_so_far)
//         {
//            lines.add(
//               string(reinterpret_cast<const_char_pointer >(buffer_ + start_of_line),
//                      read_so_far - start_of_line));
//         }
//         break; // Reached the maximum read length
//      }
//   }
//
//   return lines;
//
//}
//
//
//size_t serial::write(const string & data)
//{
//
//   scoped_write_lock lock(this);
//
//   return this->_write(reinterpret_cast<const unsigned char *>(data.c_str()), (size_t) data.length());
//
//}
//
//
//size_t serial::write(const memory & data)
//{
//
//   scoped_write_lock lock(this);
//
//   return this->_write(data.get_data(), (size_t) data.size());
//
//}
//
//
//size_t serial::write(const unsigned char * data, size_t size)
//{
//
//   scoped_write_lock lock(this);
//
//   return this->_write(data, size);
//
//}
//
//
//size_t serial::_write(const unsigned char * data, size_t length)
//{
//
//   return write(data, length);
//
//}
//
//
//void serial::setPort(const string & port)
//{
//   scoped_read_lock rlock(this);
//   scoped_write_lock wlock(this);
//   bool was_open = this->isOpen();
//   if (was_open) close();
//   this->setPort(port);
//   if (was_open) open();
//}
//
//void serial::_setPort(const string & port)
//{
//
//}
//
//
//string serial::getPort() const
//{
//
//   return "";
//
//}
//
//
//void serial::set_timeout(const timeout & timeout)
//{
//
//
//
//}
//
//
//timeout serial::getTimeout() const
//{
//
//   return 0;
//
//}
//
//
//void serial::setBaudrate(unsigned int baudrate)
//{
//
//   this->setBaudrate(baudrate);
//
//}
//
//
//unsigned int serial::getBaudrate() const
//{
//
//   return 9600;
//
//}
//
//
//void serial::setBytesize(enum_byte_size ebytesize)
//{
//
//}
//
//
//enum_byte_size serial::getBytesize() const
//{
//
//   return e_byte_size_eight;
//
//}
//
//
//void serial::setParity(enum_parity eparity)
//{
//
//}
//
//
//enum_parity serial::getParity() const
//{
//
//   return e_parity_none;
//
//}
//
//
//void serial::setStopbits(enum_stop_bit estopbit)
//{
//
//
//}
//
//
//enum_stop_bit serial::getStopbits() const
//{
//
//   return e_stop_bit_one;
//
//}
//
//
//void serial::setFlowcontrol(enum_flow_control eflowcontrol)
//{
//
//
//}
//
//
//enum_flow_control serial::getFlowcontrol() const
//{
//
//   return e_flow_control_none;
//
//}
//
//
//void serial::flush()
//{
//
//   scoped_read_lock rlock(this);
//   scoped_write_lock wlock(this);
//
//   _flush();
//
//}
//
//
//void serial::flushInput()
//{
//
//   scoped_read_lock lock(this);
//
//   _flushInput();
//
//}
//
//
//void serial::flushOutput()
//{
//
//   scoped_write_lock lock(this);
//
//   _flushOutput();
//
//}
//
//
//void serial::sendBreak(int time)
//{
//
//
//}
//
//
//void serial::setBreak(bool level)
//{
//
//
//}
//
//
//void serial::setRTS(bool level)
//{
//
//
//}
//
//
//void serial::setDTR(bool level)
//{
//
//
//}
//
//
//bool serial::waitForChange()
//{
//
//   return false;
//
//}
//
//
//bool serial::getCTS()
//{
//
//   return false;
//
//}
//
//
//bool serial::getDSR()
//{
//
//   return false;
//
//}
//
//
//bool serial::getRI()
//{
//
//   return false;
//
//}
//
//
//bool serial::getCD()
//{
//
//   return false;
//
//}
//
//
//void serial::readLock()
//{
//
//
//}
//
//
//void serial::readUnlock()
//{
//
//
//}
//
//
//void serial::writeLock()
//{
//
//
//}
//
//
//void serial::writeUnlock()
//{
//
//
//}
//
//
//void serial::_flush()
//{
//
//}
//
//
//void serial::_flushOutput()
//{
//
//
//}
//
//
//void serial::_flushInput()
//{
//
//
//}
//


} // namespace serial

