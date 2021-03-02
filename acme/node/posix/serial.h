/*!
 * \file serial/impl/unix.h
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
 * This provides a unix based pimpl for the serial class. This implementation is
 * based off termios.h and uses select for multiplexing the IO ports.
 *
 */

#if !defined(_WIN32)

#ifndef SERIAL_IMPL_UNIX_H
#define SERIAL_IMPL_UNIX_H


//#include <pthread.h>


   using serial::serial_exception;
   using serial::io_exception;

//namespace serial
//{
//
////   class MillisecondTimer
////   {
////   public:
////      MillisecondTimer(const u32 millis);
////      ::millis remaining();
////
////   private:
////      static timespec timespec_now();
////      timespec expiry;
////   };
//
//}

class serial::serial::serial_impl :
  virtual public matter
{
public:
  serial_impl (const string &port,
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
  setTimeout (Timeout &timeout);

  Timeout
  getTimeout () const;

  void
  setBaudrate (unsigned long baudrate);

  unsigned long
  getBaudrate () const;

  void
  setBytesize (enum_byte_size ebytesize);

  enum_byte_size
  getBytesize () const;

  void
  setParity (enum_parity eparity);

  enum_parity
  getParity () const;

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

protected:
  void reconfigurePort ();

private:
  string             m_strPort;               // Path to the file descriptor
  int                m_iFd;                    // The current file descriptor

  bool               m_bOpened;
  bool               m_bXonXoff;
  bool               m_bRtsCts;

  Timeout            m_timeout;           // Timeout for read operations
  unsigned long      m_ulBaudrate;    // Baudrate
  u32           m_uiByteTimeNs;     // Nanoseconds to transmit/receive a single byte

  enum_parity           m_eparity;           // Parity
  enum_byte_size         m_ebytesize;       // Size of the bytes
  enum_stop_bit         m_estopbit;       // Stop Bits
  enum_flow_control      m_eflowcontrol; // Flow Control

  // Mutex used to lock the read functions
  pthread_mutex_t    m_mutexRead;
  // Mutex used to lock the write functions
  pthread_mutex_t    m_mutexWrite;
};



#endif // SERIAL_IMPL_UNIX_H

#endif // !defined(_WIN32)
