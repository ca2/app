//
//  estatus.h
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 29/02/20.
//
#pragma once


inline bool succeeded(::i64 i)
{

   return i >= 0;

}


inline bool failed(::i64 i)
{

   return !succeeded(i);

}


class e_status
{
public:
   
   
   ::enum_status        m_estatus;
   
   
   e_status() { m_estatus = ::undefined; }
   e_status(::enum_status estatus): m_estatus(estatus){}
   e_status(bool b) : m_estatus(b ? success : error_failed){}
   e_status(i32 i) : m_estatus((::enum_status) i) {}
   e_status(i64 i) : m_estatus((::enum_status) i) {}
   
   operator ::enum_status & () { return m_estatus; }
   operator ::enum_status () const { return m_estatus; }
   
   operator bool() const { return succeeded(); }
   
   bool operator !() const { return failed();}

   bool succeeded() const { return ::succeeded(m_estatus); }

   bool failed() const { return ::failed(m_estatus); }

   int error_status() const { return succeeded() ? 0 : (int)m_estatus; }

   e_status & operator =(enum_status estatus) { m_estatus = estatus; return *this; }
   e_status & operator =(const e_status & estatus) { m_estatus = estatus; return *this; }
   e_status & operator =(bool b) { m_estatus = b ? success : error_failed; return *this; }

   bool operator ==(enum_status estatus) const { return m_estatus == estatus; }
   bool operator ==(const e_status& estatus) const { return m_estatus == estatus; }

   
};



inline bool succeeded(const ::e_status & estatus)
{

   return succeeded((::i64)estatus.m_estatus);

}


inline bool failed(const ::e_status & estatus)
{

   return !succeeded(estatus);

}

inline bool succeeded(const ::e_status & estatus, int iRange)
{

   return (::i64)estatus.m_estatus >= (::i64)SUCCESS_STATUS(iRange).m_estatus
      && (::i64)estatus.m_estatus < ((::i64)SUCCESS_STATUS(iRange).m_estatus + (::i64)STATUS_RANGE);

}


inline bool failed(const ::e_status & estatus, int iRange)
{

   return (::i64)estatus.m_estatus >= (::i64)FAILURE_STATUS(iRange).m_estatus
      && (::i64)estatus.m_estatus < ((::i64)FAILURE_STATUS(iRange).m_estatus + (::i64)STATUS_RANGE);

}


inline void defer_failed(::e_status & estatus, int iRange)
{

   if (!::failed(estatus))
   {

      estatus = FAILURE_STATUS(iRange);

   }

}


inline void defer_failed(::e_status & estatus, ::e_status     estatusDeferred)
{

   if (!::failed(estatus))
   {

      estatus = estatusDeferred;

   }

}


inline bool status_io_succeeded(const ::e_status & estatus) { return ::succeeded(estatus, STATUS_RANGE_IO); }

inline bool status_io_failed(const ::e_status & estatus) { return ::failed(estatus, STATUS_RANGE_IO); }


inline void defer_authentication_failure(::e_status & estatus) { ::defer_failed(estatus, STATUS_RANGE_AUTHENTICATION); }

