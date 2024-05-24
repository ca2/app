// created by Camilo 2021-02-02 06:50 BRT <3CamiloSasukeThomasBorregaardSoerensen
#pragma once
#ifdef __clang__
#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"
#endif


#include "acid/constant/status.h"


template < typename TYPE >
class status :
   public TYPE
{
public:


   ::e_status              m_estatus;


   status() { m_estatus = error_not_initialized; }


   status(const TYPE & _, const ::e_status & estatus = ::success) :
      TYPE(_),
      m_estatus(estatus)
   {

   }


   status(const TYPE&& _, const ::e_status & estatus = ::success) :
      TYPE(::transfer(_)),
      m_estatus(estatus)
   {

   }


   status(const ::e_status & estatus) :
      m_estatus(estatus == error_not_initialized ? error_failed : estatus.m_eenum)
   {

   }


   status(::enum_status estatus) :
      m_estatus(estatus == error_not_initialized ? error_failed : estatus)
   {

   }


   status(nullptr_t) :
      m_estatus(error_null_result)
   {

   }


   bool nok() const { return !is_ok(); }

   bool ok() const { return is_ok() != false; }

   [[nodiscard]] ::enum_status estatus() const { return m_estatus.m_eenum; }

   [[nodiscard]] bool is_ok() const { return m_estatus.succeeded(); }


   status & operator = (enum_status estatus)
   {

      m_estatus = estatus;

      return *this;

   }


   status & operator = (const e_status & estatus)
   {

      m_estatus = estatus;

      return *this;

   }


   status & operator = (const TYPE & payload)
   {

      (*((TYPE*)(this))) = payload;

      m_estatus = ::success;

      return *this;

   }


};


template < typename T >
class particle_of :
   virtual public ::particle
{
public:

   T     m_payload;

};


template < typename TYPE >
using status_pointer = ::pointer < ::particle_of < TYPE > >;

//template < typename OBJECT >
//class transport :
//   public status < ::pointer<OBJECT> >
//{
//public:
//
//
//   using status < ::pointer<OBJECT >>:status;
//   using status < ::pointer<OBJECT >>:operator =;
//
//
//};



//template < typename HOLDING >
//class holding_status
//{
//public:
//
//
//   HOLDING                 m_holding;
//   void              m_estatus;
//
//
//   holding_status() { m_estatus = error_not_initialized; }
//
//
//   holding_status(const HOLDING & _, const ::e_status & estatus = ::success) :
//      m_holding(_),
//      m_estatus(estatus)
//   {
//
//   }
//
//   holding_status(const HOLDING&& _, const ::e_status & estatus = ::success) :
//      m_holding(::transfer(_)),
//      m_estatus(estatus)
//   {
//
//   }
//
//   holding_status(const ::e_status & estatus)
//   {
//
//      if (estatus == error_not_initialized)
//      {
//
//         m_estatus = ::error_failed;
//
//      }
//      else
//      {
//
//         m_estatus = estatus;
//
//      }
//
//   }
//
//
//   holding_status(::enum_status estatus)
//   {
//
//      if (estatus == error_not_initialized)
//      {
//
//         estatus = ::error_failed;
//
//      }
//
//      m_estatus = estatus;
//
//   }
//
//
//   holding_status(nullptr_t)
//   {
//
//      m_estatus = error_null_result;
//
//   }
//
//
//   bool operator !() const { return !is_ok(); }
//
//   operator bool() const { return is_ok(); }
//
//   operator int() const { return is_ok() != false; }
//
//   ::e_status estatus() const { return m_estatus; }
//
//   operator HOLDING() const { return m_holding; }
//
//   HOLDING holding() const { return m_holding; }
//
//   bool is_ok() const { return ::succeeded(m_estatus); }
//
//
//   holding_status & operator = (const HOLDING & holding)
//   {
//
//      m_estatus = ::success;
//
//      m_holding = (holding);
//
//      return *this;
//
//   }
//
//
//   holding_status & operator = (HOLDING && holding)
//   {
//
//      m_estatus = ::success;
//
//      m_holding = ::transfer(holding);
//
//      return *this;
//
//   }
//
//
//   holding_status & operator = (enum_status estatus)
//   {
//
//      m_estatus = estatus;
//
//      return *this;
//
//   }
//
//
//   holding_status & operator = (const e_status & estatus)
//   {
//
//      m_estatus = estatus;
//
//      return *this;
//
//   }
//
//
//};
//

#ifdef __clang__
#pragma clang diagnostic pop
#endif



