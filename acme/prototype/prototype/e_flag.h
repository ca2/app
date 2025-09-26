// Camilo Sasuke Thomas Borregaard Soerensen 2020-03-08
#pragma once


#include "acme/constant/flag.h"


DECLARE_ENUMERATION(e_flag, enum_flag);


inline bool __enum_is_ok(const ::enum_flag& e) { return (e & e_flag_success) != 0; }
inline bool __enum_is_failed(const ::enum_flag& e) { return (e & e_flag_failure) != 0 || (e & e_flag_timeout) != 0; }


//class CLASS_DECL_ACME e_flag
//{
//public:
//
//
//   enum_flag         m_eflag;
//
//
//   e_flag() { m_eflag = e_flag_none; }
//   e_flag(const std::initializer_list < enum_flag >& list_base) { m_eflag = e_flag_none; for (auto& e : list_base) add(e); }
//   e_flag(enum_flag e) { m_eflag = e; }
//   e_flag(long long i) { m_eflag = (enum_flag)i; }
//   e_flag(const e_flag& e) { m_eflag = e.m_eflag; }
//
//   inline void add(enum_flag e) { m_eflag = (enum_flag)(e | m_eflag); }
//
//   inline e_flag& operator |= (enum_flag e) { add(e); return *this; }
//   inline e_flag& operator &= (enum_flag e) { m_eflag = (enum_flag)(m_eflag & e); return *this; }
//
//   inline e_flag& operator |= (const e_flag& e) { m_eflag = (enum_flag)(e.m_eflag | m_eflag); return *this; }
//   inline e_flag& operator &= (const e_flag& e) { m_eflag = (enum_flag)(m_eflag & e.m_eflag); return *this; }
//
//   inline e_flag& operator += (enum_flag e) { return operator |= (e); }
//   inline e_flag& operator -= (enum_flag e) { return operator &= ((enum_flag)~(long long)(e)); }
//
//   inline e_flag& operator += (const e_flag& e) { return operator |= ((enum_flag)e.m_eflag); }
//   inline e_flag& operator -= (const e_flag& e) { return operator &= ((enum_flag)~(long long)(e.m_eflag)); }
//
//   inline e_flag& operator ^= (const e_flag& e) { toggle(e);  return *this; }
//
//   inline e_flag operator + (const e_flag& t) const { auto copy = *this; copy.add(t); return copy; }
//
//   inline e_flag operator - (enum_flag e) const { return (enum_flag)(m_eflag & ~((long long)e)); }
//
//   inline e_flag operator | (enum_flag e) const { return (enum_flag)(m_eflag | e); }
//   inline e_flag operator & (enum_flag e) const { return (enum_flag)(m_eflag & e); }
//
//   inline bool is(enum_flag e) const { return (long long)(m_eflag & e) == (long long)e; }
//   inline bool has(enum_flag e) const { return is(e); }
//
//   void erase(enum_flag e) { operator -= (e); }
//   void add(const e_flag& e) { operator += (e); }
//   void unset(const e_flag& e) { erase(e); }
//   void set(const e_flag& e) { add(e); }
//   void erase(const e_flag& e) { operator -= (e); }
//   void clear() { m_eflag = (enum_flag)0; }
//
//   void set(enum_flag e, bool bSet) { if (bSet) set(e); else unset(e); }
//   void toggle(enum_flag e) { if (is(e)) unset(e); else set(e); }
//
//   e_flag& operator = (const e_flag& e) { m_eflag = e.m_eflag; return *this; }
//
//
//   bool operator == (const e_flag& e) const { return m_eflag == e.m_eflag; }
//   bool operator == (enum_flag e) const { return m_eflag == e; }
//
//
//   enum_flag& eflag() { return (enum_flag&)m_eflag; }
//   enum_flag eflag() const { return (enum_flag)m_eflag; }
//
//
//   operator enum_flag& ()
//   {
//
//      return (enum_flag&)m_eflag;
//
//   }
//
//
//   operator enum_flag() const
//   {
//
//      return (enum_flag)m_eflag;
//
//   }
//
//
//   e_flag& operator ++(int)
//   {
//
//      m_eflag = (enum_flag)((long long)m_eflag + 1);
//
//      return *this;
//
//   }
//
//
//   e_flag& operator %=(const enum_flag& eenum)
//   {
//
//      m_eflag = (enum_flag)((long long)m_eflag % (long long)eenum);
//
//      return *this;
//
//   }
//
//
//   e_flag& rotate(const enum_flag& eenum)
//   {
//
//      if ((long long)m_eflag < 0)
//      {
//
//         m_eflag = (enum_flag)0;
//
//      }
//
//      this->operator ++(0);
//
//      return this->operator %=(eenum);
//
//   }
//
//
//#if !defined(__OBJC__) && !defined(__cplusplus_winrt)
//
//   IMPL_OPERATOR_PLUS(e_flag);
//
//#endif
//
//
//};
//



