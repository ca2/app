#pragma once


// Camilo Sasuke Thomas Borregaard Sørensen 2020-04-15 // from ewindowflag
#pragma once


DECLARE_ENUMERATION(e_window_flag, enum_window_flag);

//class e_window_flag
//{
//public:
//
//
//   enum_window_flag       m_ewindowflag;
//
//
//   e_window_flag() { m_ewindowflag = (enum_window_flag)0; }
//   ewindowflag(const std::initializer_list < enum_window_flag >& list) { m_ewindowflag = (enum_window_flag)0; for (auto& e : list) add(e); }
//   ewindowflag(enum_window_flag e) { m_ewindowflag = e; }
//   ewindowflag(::i64 i) { m_ewindowflag = (enum_window_flag)i; }
//   ewindowflag(const ewindowflag& e) { m_ewindowflag = e.m_ewindowflag; }
//
//   inline void add(enum_window_flag e) { m_ewindowflag = (enum_window_flag)(e | m_ewindowflag); }
//
//   inline ewindowflag& operator |= (enum_window_flag e) { add(e); return *this; }
//   inline ewindowflag& operator &= (enum_window_flag e) { m_ewindowflag = (enum_window_flag)(m_ewindowflag & e); return *this; }
//
//   inline ewindowflag& operator |= (const ewindowflag& e) { m_ewindowflag = (enum_window_flag)(e.m_ewindowflag | m_ewindowflag); return *this; }
//   inline ewindowflag& operator &= (const ewindowflag& e) { m_ewindowflag = (enum_window_flag)(m_ewindowflag & e.m_ewindowflag); return *this; }
//
//   inline ewindowflag& operator += (enum_window_flag e) { return operator |= (e); }
//   inline ewindowflag& operator -= (enum_window_flag e) { return operator &= ((enum_window_flag)~(i64)(e)); }
//
//   inline ewindowflag& operator += (const ewindowflag& e) { return operator |= ((enum_window_flag)e.m_ewindowflag); }
//   inline ewindowflag& operator -= (const ewindowflag& e) { return operator &= ((enum_window_flag)~(i64)(e.m_ewindowflag)); }
//
//   inline ewindowflag& operator ^= (const ewindowflag& e) { toggle(e);  return *this; }
//
//   inline ewindowflag operator + (const ewindowflag& t) const { auto copy = *this; copy.add(t); return copy; }
//
//   inline ewindowflag operator - (enum_window_flag e) const { return (enum_window_flag)(m_ewindowflag & ~((i64)e)); }
//
//   //template < typename TYPE >
//   //ewindowflag operator + (const TYPE & t) const { auto copy = *this; copy.add(t); return copy; }
//
//
//   inline ewindowflag operator | (enum_window_flag e) const { return (enum_window_flag)(m_ewindowflag | e); }
//   inline ewindowflag operator & (enum_window_flag e) const { return (enum_window_flag)(m_ewindowflag & e); }
//
//   inline bool is(enum_window_flag e) const { return (i64)(m_ewindowflag & e) == (i64)e; }
//   inline bool has(enum_window_flag e) const { return is(e); }
//
//   void erase(enum_window_flag e) { operator -= (e); }
//   void add(const ewindowflag& e) { operator += (e); }
//   void unset(const ewindowflag& e) { erase(e); }
//   void set(const ewindowflag& e) { add(e); }
//   void erase(const ewindowflag& e) { operator -= (e); }
//   void clear() { m_ewindowflag = (enum_window_flag)0; }
//
//   void set(enum_window_flag e, bool bSet) { if (bSet) set(e); else unset(e); }
//   void toggle(enum_window_flag e) { if (is(e)) unset(e); else set(e); }
//
//   ewindowflag& operator = (const ewindowflag& e) { m_ewindowflag = e.m_ewindowflag; return *this; }
//
//
//   bool operator == (const ewindowflag& e) const { return m_ewindowflag == e.m_ewindowflag; }
//   bool operator == (enum_window_flag e) const { return m_ewindowflag == e; }
//
//
//   enum_window_flag& eflag() { return (enum_window_flag&)m_ewindowflag; }
//   enum_window_flag eflag() const { return (enum_window_flag)m_ewindowflag; }
//
//   operator enum_window_flag& ()
//   {
//      return (enum_window_flag&)m_ewindowflag;
//   }
//
//   operator enum_window_flag() const
//   {
//
//      return (enum_window_flag)m_ewindowflag;
//   }
//
//
//   ewindowflag& operator ++(int)
//   {
//
//      m_ewindowflag = (enum_window_flag)((::i64) m_ewindowflag + 1);
//
//      return *this;
//
//   }
//
//
//   ewindowflag& operator %=(const enum_window_flag& eenum)
//   {
//
//      m_ewindowflag = (enum_window_flag)((::i64) m_ewindowflag % (::i64) eenum);
//
//      return *this;
//
//   }
//
//   ewindowflag& rotate(const enum_window_flag& eenum)
//   {
//
//      if ((::i64) m_ewindowflag < 0)
//      {
//
//         m_ewindowflag = (enum_window_flag)0;
//
//      }
//
//      this->operator++(0);
//
//      return this->operator %=(eenum);
//
//   }
//
//#ifndef __OBJC__
//   IMPL_OPERATOR_PLUS(ewindowflag);
//#endif
//
//
//};




