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


class CLASS_DECL_ACME e_status3
{
public:
   
   
   ::enum_status        m_estatus;
   
   
   e_status3() { m_estatus = ::undefined; }
   e_status3(::enum_status estatus): m_estatus(estatus){}
   e_status3(const ::e_status3 & estatus): m_estatus(estatus.m_estatus){}
   e_status3(bool b) : m_estatus(b ? success : error_failed){}
   e_status3(i32 i) : m_estatus((::enum_status) i) {}
   e_status3(i64 i) : m_estatus((::enum_status) i) {}
   
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

   int exit_code() const;

   e_status3& operator =(enum_status estatus) { m_estatus = estatus; return *this; }
   e_status3& operator =(const e_status3 & estatus) { m_estatus = (enum_status) estatus; return *this; }
   e_status3& operator =(bool b) { m_estatus = b ? success : error_failed; return *this; }

   bool operator ==(enum_status estatus) const { return m_estatus == estatus; }
   bool operator ==(const e_status3& estatus) const { return m_estatus == estatus; }
   bool operator <(const e_status3& estatus) const { return m_estatus < (enum_status) estatus; }
   bool operator <(const enum_status& estatus) const { return m_estatus < estatus; }
   bool operator >(const e_status3& estatus) const { return m_estatus > (enum_status) estatus; }
   bool operator >(const enum_status& estatus) const { return m_estatus > estatus; }

   
   
};



inline bool succeeded(const ::e_status3& estatus)
{

   return succeeded((::i64)estatus.m_estatus);

}


inline bool failed(const ::e_status3 & estatus)
{

   return !succeeded(estatus);

}

inline bool succeeded(const ::e_status3 & estatus, int iRange)
{

   return (::i64)estatus.m_estatus >= (::i64)SUCCESS_STATUS(iRange).m_estatus
      && (::i64)estatus.m_estatus < ((::i64)SUCCESS_STATUS(iRange).m_estatus + (::i64)STATUS_RANGE);

}


inline bool failed(const ::e_status3 & estatus, int iRange)
{

   return (::i64)estatus.m_estatus >= (::i64)FAILURE_STATUS(iRange).m_estatus
      && (::i64)estatus.m_estatus < ((::i64)FAILURE_STATUS(iRange).m_estatus + (::i64)STATUS_RANGE);

}


inline void defer_failed(::e_status3 & estatus, int iRange)
{

   if (!::failed(estatus))
   {

      estatus = FAILURE_STATUS(iRange);

   }

}


inline void defer_failed(::e_status3 & estatus, ::e_status3     estatusDeferred)
{

   if (!::failed(estatus))
   {

      estatus = estatusDeferred;

   }

}


inline bool status_io_succeeded(const ::e_status3& estatus) { return ::succeeded(estatus, STATUS_RANGE_IO); }

inline bool status_io_failed(const ::e_status3& estatus) { return ::failed(estatus, STATUS_RANGE_IO); }


inline void defer_authentication_failure(::e_status3& estatus) { ::defer_failed(estatus, STATUS_RANGE_AUTHENTICATION); }


CLASS_DECL_ACME ::e_status3 worst(enum_status e1, enum_status e2);
inline ::e_status3 worst(e_status3 e1, enum_status e2) { return worst((enum_status)e1, (enum_status)e2); }
inline ::e_status3 worst(enum_status e1, e_status3 e2) { return worst((enum_status)e1, (enum_status)e2); }
inline ::e_status3 worst(e_status3 e1, e_status3 e2) { return worst((enum_status)e1, (enum_status)e2); }


CLASS_DECL_ACME::e_status3 operator & (enum_status e1, enum_status e2);
inline ::e_status3 operator & (e_status3 e1, enum_status e2) { return( (enum_status)e1) &((enum_status)e2); }
inline ::e_status3 operator & (enum_status e1, e_status3 e2) { return((enum_status)e1) & ((enum_status)e2); }
inline ::e_status3 operator & (e_status3 e1, e_status3 e2) { return((enum_status)e1) & ((enum_status)e2); }



