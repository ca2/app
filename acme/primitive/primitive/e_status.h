//
//  estatus.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 29/02/20.
//
#pragma once


//#include "acme/parallelization/synchronization_result.h"

//
//inline bool succeeded(::i64 i)
//{
//
//   return i >= 0;
//
//}


//inline bool failed(::i64 i)
//{
//
//   return !succeeded(i);
//
//}
//

class e_status
{
public:


   using ENUM_TAG = ENUM_TYPE_TAG;
   
   
   ::enum_status        m_eenum;
   
   
   constexpr e_status() { m_eenum = ::undefined; }
   constexpr e_status(::enum_status estatus): m_eenum(estatus){}
   constexpr e_status(const ::e_status & estatus): m_eenum(estatus.m_eenum){}
   constexpr explicit e_status(bool b) : m_eenum(b ? success : error_failed){}
   constexpr explicit e_status(i32 i) : m_eenum((::enum_status) i) {}
   constexpr explicit e_status(i64 i) : m_eenum((::enum_status) i) {}
   

   constexpr ::enum_status as_estatus() const { return m_eenum; }


   constexpr ::i64 as_i64() const { return (::i64) m_eenum; }
   constexpr ::u64 as_u64() const { return (::u64) m_eenum; }


   constexpr bool is_set() const { return this->succeeded(); }
   
   //operator int() const { return this->succeeded(); }
   
   //bool operator !() const { return failed();}

   constexpr explicit operator bool() const noexcept { return this->ok(); }

   constexpr bool ok() const { return succeeded(); }

   
   constexpr bool succeeded() const { return (::i64)m_eenum >= 0; }

   constexpr bool failed() const { return !succeeded(); }

   //bool signaled() const { return ::signaled(*this); }

   //::i32 signaled_index() const { return ::signaled_index(*this); }

   //bool abandoned() const { return ::abandoned(*this); }

   //::i32 abandoned_index() const { return ::abandoned_index(*this); }

   //bool wait_timeout() const { return ::wait_timeout(*this); }

   constexpr bool succeeded(::i64 iRange) const
   {
      return (::i64)m_eenum >= (::i64)SUCCESS_STATUS(iRange).m_eenum
         && (::i64)m_eenum < ((::i64)SUCCESS_STATUS(iRange).m_eenum + (::i64)STATUS_RANGE);

   }

   constexpr bool failed(::i64 iRange) const
   {

      return (::i64)m_eenum >= (::i64)FAILURE_STATUS(iRange).m_eenum
         && (::i64)m_eenum < ((::i64)FAILURE_STATUS(iRange).m_eenum + (::i64)STATUS_RANGE);

   }


   constexpr int error_status() const { return succeeded() ? 0 : (int)(::i64)m_eenum; }

   //int exit_code() const { return succeeded() ? 0 : (int)_status_exit_code(m_eenum); }

   constexpr e_status& operator =(const e_status & estatus) { m_eenum = estatus.as_estatus(); return *this; }

   constexpr bool operator ==(enum_status estatus) const { return m_eenum == estatus; }
   constexpr bool operator ==(const e_status& estatus) const { return m_eenum == estatus; }
   constexpr bool operator <(const e_status& estatus) const { return m_eenum < estatus.as_estatus(); }
   constexpr bool operator <(const enum_status& estatus) const { return m_eenum < estatus; }
   constexpr bool operator >(const e_status& estatus) const { return m_eenum > estatus.as_estatus(); }
   constexpr bool operator >(const enum_status& estatus) const { return m_eenum > estatus; }



   constexpr bool is_exit_status() const
   {

      return m_eenum > error_exit_start && m_eenum < error_exit_end;

   }


   int exit_code() const
   {

      if (this->succeeded())
      {

         return 0;

      }

#ifdef WINDOWS

      return (::i32)-(::i64)m_eenum;

#else

      if (this->m_eenum >= -125)
      {

         return (::i32)-(::i64)(this->m_eenum);

      }
      else
      {

         return 125;

      }

#endif

   }


   
   /// @brief synchronization signaled index
   /// @return signaled index. For single synchronization object 0 if signaled or -1 if not signaled. For array of synchronization objects, the lowest? index of a signaled object or -1 if none of objects are signaled.
   constexpr ::i32 signaled_index() const
   {

      return (m_eenum >= signaled_base && m_eenum < signaled_end) ? (::i32)((::i64)m_eenum - (::i64)signaled_base) : -1;

   }

   /// @brief is synchronization signaled?
   /// @return if synchronization is signaled. For single synchronization object true if signaled. For array of synchronization object, true if at least one? (or all?) object(s?) is signaled.
   /// 
   constexpr bool signaled()const
   {

      return signaled_index() >= 0;

   }

   /// @brief synchronization abandoned index
   /// @return abandoned index
   constexpr ::i32 abandoned_index()const
   {

      return (m_eenum >= abandoned_base && m_eenum < abandoned_end) ? (::i32)((::i64)m_eenum - (::i64)abandoned_base) : -1;

   }

   /// @brief is synchronization abandoned?
   /// @return if it is abandoned
   constexpr bool abandoned()const
   {

      return abandoned_index() >= 0;

   }

   /// @brief is synchronization timed out?
   /// @return if it is timed out
   constexpr bool wait_timeout() const
   {

      return m_eenum == error_wait_timeout;

   }


   inline void defer_failed(const ::e_status & estatusError)
   {

      if (!failed())
      {

         m_eenum = estatusError.m_eenum;

      }

   }


   inline void defer_failed(int iRange)
   {

      defer_failed(FAILURE_STATUS(iRange));

   }

   constexpr bool io_succeeded() const { return succeeded(STATUS_RANGE_IO); }

   constexpr bool io_failed() const { return failed(STATUS_RANGE_IO); }


   inline void defer_authentication_failure() { defer_failed(STATUS_RANGE_AUTHENTICATION); }

   constexpr ::e_status worst(const ::e_status & e) const;

};


//inline bool succeeded(const ::e_status& estatus)
//{
//
//   return succeeded((::i64)estatus.m_eenum);
//
//}


//inline bool failed(const ::e_status & estatus)
//{
//
//   return !succeeded(estatus);
//
//}

//inline bool succeeded(const ::e_status & estatus, int iRange)
//{
//
//   return (::i64)estatus.m_eenum >= (::i64)SUCCESS_STATUS(iRange).m_eenum
//      && (::i64)estatus.m_eenum < ((::i64)SUCCESS_STATUS(iRange).m_eenum + (::i64)STATUS_RANGE);
//
//}


//inline bool failed(const ::e_status & estatus, ::i64 iRange)
//{
//
//   return (::i64)estatus.m_eenum >= (::i64)FAILURE_STATUS(iRange).m_eenum
//      && (::i64)estatus.m_eenum < ((::i64)FAILURE_STATUS(iRange).m_eenum + (::i64)STATUS_RANGE);
//
//}




//
//
//inline void defer_authentication_failure(::e_status& estatus) { ::defer_failed(estatus, STATUS_RANGE_AUTHENTICATION); }
//
//
//CLASS_DECL_ACME::e_status worst(const ::e_status & e1, const ::e_status & e2);
//


CLASS_DECL_ACME::e_status errno_status(int nErrno);
CLASS_DECL_ACME::e_status failed_errno_status(int nErrno);



