/*!
 * \file serial/impl/windows.h
 * \author  William Woodall <wjwwood@gmail.com>
 * \author  John Harrison <ash@greaterthaninfinity.com>
 * \version 0.1
 *
 * \section LICENSE
 *
 * The MIT License
 *
 * Copyright (c) 2012 William Woodall, John Harrison
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
 * This provides a windows implementation of the serial class interface.
 *
 */
#pragma once


namespace serial
{

   //using std::string;
   //using std::wstring;
   //using std::invalid_argument;

   //using serial::serial_exception;
   //using serial::io_exception;

   class serial_impl :
      virtual public matter
   {
   public:

      bool        m_bReadTimeout;

      serial_impl (
                  const string &port,
                  unsigned long baudrate,
                  enum_byte_size ebytesize,
                  enum_parity eparity,
                  enum_stop_bit estopbit,
                  enum_flow_control eflowcontrol);

      virtual ~serial_impl ();

      void
      open ();

      void
      close ();

      bool
      isOpen () const;

      size_t
      available ();

      bool
      waitReadable (::millis timeout);

      void
      waitByteTimes (size_t count);

      size_t
      read (u8 *buf, size_t size = 1);

      size_t
      write (const u8 *data, size_t length);

      void
      flush ();

      void
      flushInput ();

      void
      flushOutput ();

      void
      sendBreak (int duration);

      void
      setBreak (bool level);

      void
      setRTS (bool level);

      void
      setDTR (bool level);

      bool
      waitForChange ();

      bool
      getCTS ();

      bool
      getDSR ();

      bool
      getRI ();

      bool
      getCD ();

      void
      setPort (const string &port);

      string
      getPort () const;

      void
      set_timeout (timeout &timeout);

      timeout
      getTimeout () const;

      void
      setBaudrate (unsigned long baudrate);

      unsigned long
      getBaudrate () const;

      void
      setBytesize (enum_byte_size ebytesize);

      enum_byte_size
      getBytesize () const;

      void setParity (enum_parity eparity);

      enum_parity getParity () const;

      void
      setStopbits (enum_stop_bit estopbit);

      enum_stop_bit
      getStopbits () const;

      void
      setFlowcontrol (enum_flow_control eflowcontrol);

      enum_flow_control
      getFlowcontrol () const;

      void
      readLock ();

      void
      readUnlock ();

      void
      writeLock ();

      void
      writeUnlock ();

      virtual size_t
      readline(string &buffer, size_t size = 65536, string eol = "\n");


   protected:
      void reconfigurePort ();

   private:
      wstring           m_wstrPort;               // Path to the file descriptor
      HANDLE            m_hFile;

      bool              m_bOpened;

      timeout           m_timeout;           // timeout for read operations
      unsigned long     m_ulBaudrate;    // Baudrate
      u32          m_uiByteTimeNs;     // Nanoseconds to transmit/receive a single byte

      enum_parity          m_eparity;           // Parity
      enum_byte_size        m_ebytesize;       // Size of the bytes
      enum_stop_bit        m_estopbit;       // Stop Bits
      enum_flow_control     m_eflowcontrol; // Flow Control

      // Mutex used to lock the read functions
      HANDLE            m_hMutexRead;
      // Mutex used to lock the write functions
      HANDLE            m_hMutexWrite;
   };


   class serial_impl;


   class scoped_read_lock
   {
   public:


      scoped_read_lock(serial_impl* pimpl) : m_pimpl(pimpl)
      {
         this->m_pimpl->readLock();
      }
      ~scoped_read_lock()
      {
         this->m_pimpl->readUnlock();
      }
   private:
      // Disable copy constructors
      scoped_read_lock(const scoped_read_lock&);
      const scoped_read_lock& operator=(scoped_read_lock);

      serial_impl* m_pimpl;

   };


   class scoped_write_lock
   {
   public:
      scoped_write_lock(serial_impl* pimpl) : m_pimpl(pimpl)
      {
         this->m_pimpl->writeLock();
      }
      ~scoped_write_lock()
      {
         this->m_pimpl->writeUnlock();
      }
   private:
      // Disable copy constructors
      scoped_write_lock(const scoped_write_lock&);
      const scoped_write_lock& operator=(scoped_write_lock);
      serial_impl* m_pimpl;
   };


} // namespace serial



