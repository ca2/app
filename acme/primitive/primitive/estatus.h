//
//  estatus.h
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 29/02/20.
//
#pragma once


#include "acme/parallelization/synchronization_result.h"


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
   e_status(const ::e_status & estatus): m_estatus(estatus.m_estatus){}
   e_status(bool b) : m_estatus(b ? success : error_failed){}
   e_status(i32 i) : m_estatus((::enum_status) i) {}
   e_status(i64 i) : m_estatus((::enum_status) i) {}
   

   operator ::enum_status () const { return m_estatus; }

   operator bool() const { return this->succeeded(); }
   
   operator int() const { return this->succeeded(); }
   
   bool operator !() const { return failed();}

   bool ok() const { return ::succeeded(m_estatus); }

   bool succeeded() const { return ::succeeded(m_estatus); }

   bool failed() const { return ::failed(m_estatus); }

   bool signaled() const { return ::signaled(m_estatus); }

   ::i32 signaled_index() const { return ::signaled_index(m_estatus); }

   bool abandoned() const { return ::abandoned(m_estatus); }

   ::i32 abandoned_index() const { return ::abandoned_index(m_estatus); }

   bool wait_timeout() const { return ::wait_timeout(m_estatus); }

   int error_status() const { return succeeded() ? 0 : (int)m_estatus; }

   int exit_code() const { return succeeded() ? 0 : (int)_status_exit_code(m_estatus); }

   e_status& operator =(enum_status estatus) { m_estatus = estatus; return *this; }
   e_status& operator =(const e_status & estatus) { m_estatus = (enum_status) estatus; return *this; }
   e_status& operator =(bool b) { m_estatus = b ? success : error_failed; return *this; }

   bool operator ==(enum_status estatus) const { return m_estatus == estatus; }
   bool operator ==(const e_status& estatus) const { return m_estatus == estatus; }
   bool operator <(const e_status& estatus) const { return m_estatus < (enum_status) estatus; }
   bool operator <(const enum_status& estatus) const { return m_estatus < estatus; }
   bool operator >(const e_status& estatus) const { return m_estatus > (enum_status) estatus; }
   bool operator >(const enum_status& estatus) const { return m_estatus > estatus; }


};


inline bool succeeded(const ::e_status& estatus)
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


inline bool status_io_succeeded(const ::e_status& estatus) { return ::succeeded(estatus, STATUS_RANGE_IO); }

inline bool status_io_failed(const ::e_status& estatus) { return ::failed(estatus, STATUS_RANGE_IO); }


inline void defer_authentication_failure(::e_status& estatus) { ::defer_failed(estatus, STATUS_RANGE_AUTHENTICATION); }


CLASS_DECL_ACME ::e_status worst(enum_status e1, enum_status e2);
inline ::e_status worst(e_status e1, enum_status e2) { return worst((enum_status)e1, (enum_status)e2); }
inline ::e_status worst(enum_status e1, e_status e2) { return worst((enum_status)e1, (enum_status)e2); }
inline ::e_status worst(e_status e1, e_status e2) { return worst((enum_status)e1, (enum_status)e2); }


CLASS_DECL_ACME::e_status operator & (enum_status e1, enum_status e2);
inline ::e_status operator & (e_status e1, enum_status e2) { return( (enum_status)e1) &((enum_status)e2); }
inline ::e_status operator & (enum_status e1, e_status e2) { return((enum_status)e1) & ((enum_status)e2); }
inline ::e_status operator & (e_status e1, e_status e2) { return((enum_status)e1) & ((enum_status)e2); }



