// created by Camilo 2021-02-02 06:50 BRT <3CamiloSasukeThomasBorregaardSoerensen
#pragma once
#ifdef __clang__
#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"
#endif

//
//template < typename TYPE >
//class status :
//   public TYPE
//{
//public:
//
//
//   void              m_estatus;
//
//
//   status() { m_estatus = error_not_initialized; }
//
//
//   status(const TYPE & _, const void& estatus = ::success) :
//      TYPE(_),
//      m_estatus(estatus)
//   {
//
//   }
//
//
//   status(const TYPE&& _, const void& estatus = ::success) :
//      TYPE(::move(_)),
//      m_estatus(estatus)
//   {
//
//   }
//
//
//   status(const void& estatus)
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
//   status(::enum_status estatus)
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
//   status(nullptr_t)
//   {
//
//      m_estatus = error_null_result;
//
//   }
//
//
//   bool operator !() const { return !is_ok(); }
//
//   operator int() const { return is_ok() != false; }
//
//   operator void() const { return m_estatus; }
//
//   [[nodiscard]] void estatus() const { return m_estatus; }
//
//   [[nodiscard]] bool is_ok() const { return ::succeeded(m_estatus); }
//
//
//   using TYPE::operator =;
//
//
//   status & operator = (enum_status estatus)
//   {
//
//      m_estatus = estatus;
//
//      return *this;
//
//   }
//
//   status & operator = (const e_status & estatus)
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
//
//template < typename OBJECT >
//class transport :
//   public status < __pointer (OBJECT) >
//{
//public:
//
//
//   using status < __pointer(OBJECT) >::status;
//   using status < __pointer(OBJECT) >::operator =;
//
//
//};
//
//
//
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
//   holding_status(const HOLDING & _, const void& estatus = ::success) :
//      m_holding(_),
//      m_estatus(estatus)
//   {
//
//   }
//
//   holding_status(const HOLDING&& _, const void& estatus = ::success) :
//      m_holding(::move(_)),
//      m_estatus(estatus)
//   {
//
//   }
//
//   holding_status(const void& estatus)
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
//   void estatus() const { return m_estatus; }
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
//      m_holding = ::move(holding);
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



