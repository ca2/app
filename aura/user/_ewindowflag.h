// Camilo Sasuke Tsumanuma 2020-04-15 // from ewindowflag
#pragma once




class ewindowflag
{
public:


   e_window_flag       m_ewindowflag;


   ewindowflag() { m_ewindowflag = (e_window_flag)0; }
   ewindowflag(const std::initializer_list < e_window_flag >& list) { m_ewindowflag = (e_window_flag)0; for (auto& e : list) add(e); }
   ewindowflag(e_window_flag e) { m_ewindowflag = e; }
   ewindowflag(::i64 i) { m_ewindowflag = (e_window_flag)i; }
   ewindowflag(const ewindowflag& e) { m_ewindowflag = e.m_ewindowflag; }

   inline void add(e_window_flag e) { m_ewindowflag = (e_window_flag)(e | m_ewindowflag); }

   inline ewindowflag& operator |= (e_window_flag e) { add(e); return *this; }
   inline ewindowflag& operator &= (e_window_flag e) { m_ewindowflag = (e_window_flag)(m_ewindowflag & e); return *this; }

   inline ewindowflag& operator |= (const ewindowflag& e) { m_ewindowflag = (e_window_flag)(e.m_ewindowflag | m_ewindowflag); return *this; }
   inline ewindowflag& operator &= (const ewindowflag& e) { m_ewindowflag = (e_window_flag)(m_ewindowflag & e.m_ewindowflag); return *this; }

   inline ewindowflag& operator += (e_window_flag e) { return operator |= (e); }
   inline ewindowflag& operator -= (e_window_flag e) { return operator &= ((e_window_flag)~(i64)(e)); }

   inline ewindowflag& operator += (const ewindowflag& e) { return operator |= ((e_window_flag)e.m_ewindowflag); }
   inline ewindowflag& operator -= (const ewindowflag& e) { return operator &= ((e_window_flag)~(i64)(e.m_ewindowflag)); }

   inline ewindowflag& operator ^= (const ewindowflag& e) { toggle(e);  return *this; }

   inline ewindowflag operator + (const ewindowflag& t) const { auto copy = *this; copy.add(t); return copy; }

   inline ewindowflag operator - (e_window_flag e) const { return (e_window_flag)(m_ewindowflag & ~((i64)e)); }

   //template < typename TYPE >
   //ewindowflag operator + (const TYPE & t) const { auto copy = *this; copy.add(t); return copy; }


   inline ewindowflag operator | (e_window_flag e) const { return (e_window_flag)(m_ewindowflag | e); }
   inline ewindowflag operator & (e_window_flag e) const { return (e_window_flag)(m_ewindowflag & e); }

   inline bool is(e_window_flag e) const { return (i64)(m_ewindowflag & e) == (i64)e; }
   inline bool has(e_window_flag e) const { return is(e); }

   void remove(e_window_flag e) { operator -= (e); }
   void add(const ewindowflag& e) { operator += (e); }
   void unset(const ewindowflag& e) { remove(e); }
   void set(const ewindowflag& e) { add(e); }
   void remove(const ewindowflag& e) { operator -= (e); }
   void clear() { m_ewindowflag = (e_window_flag)0; }

   void set(e_window_flag e, bool bSet) { if (bSet) set(e); else unset(e); }
   void toggle(e_window_flag e) { if (is(e)) unset(e); else set(e); }

   ewindowflag& operator = (const ewindowflag& e) { m_ewindowflag = e.m_ewindowflag; return *this; }


   bool operator == (const ewindowflag& e) const { return m_ewindowflag == e.m_ewindowflag; }
   bool operator == (e_window_flag e) const { return m_ewindowflag == e; }


   e_window_flag& eflag() { return (e_window_flag&)m_ewindowflag; }
   e_window_flag eflag() const { return (e_window_flag)m_ewindowflag; }

   operator e_window_flag& ()
   {
      return (e_window_flag&)m_ewindowflag;
   }

   operator e_window_flag() const
   {

      return (e_window_flag)m_ewindowflag;
   }


   ewindowflag& operator ++(int)
   {

      m_ewindowflag = (e_window_flag)((::i64) m_ewindowflag + 1);

      return *this;

   }


   ewindowflag& operator %=(const e_window_flag& eenum)
   {

      m_ewindowflag = (e_window_flag)((::i64) m_ewindowflag % (::i64) eenum);

      return *this;

   }

   ewindowflag& rotate(const e_window_flag& eenum)
   {

      if ((::i64) m_ewindowflag < 0)
      {

         m_ewindowflag = (e_window_flag)0;

      }

      this->operator++(0);

      return this->operator %=(eenum);

   }

#ifndef __OBJC__
   IMPL_OPERATOR_PLUS(ewindowflag);
#endif


};




