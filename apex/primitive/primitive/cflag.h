#pragma once


template < typename ENUM >
inline bool __enum_is_failed(const ENUM & e) { return !(::i64)e; }

inline bool __enum_is_failed(const ::estatus & e);

template < typename ENUM >
class cflag :
   public memory_template < cflag < ENUM > >
{
public:


   ENUM  m_eenum;


   cflag() { m_eenum = (ENUM) 0; }
   cflag(const std::initializer_list < ENUM > & list ) { m_eenum = (ENUM) 0; for (auto & e : list) add(e); }
   cflag(ENUM e) { m_eenum = e; }
   cflag(::i64 i) { m_eenum = (ENUM) i; }
   cflag(const cflag & e) { m_eenum = e.m_eenum; }

   inline void add(ENUM e) { m_eenum = (ENUM)(e | m_eenum); }

   inline cflag & operator |= (ENUM e) { add(e); return *this; }
   inline cflag & operator &= (ENUM e) { m_eenum = (ENUM) (m_eenum & e); return *this; }

   inline cflag & operator |= (const cflag & e) { m_eenum = (ENUM) (e.m_eenum | m_eenum); return *this; }
   inline cflag & operator &= (const cflag & e) { m_eenum = (ENUM) (m_eenum & e.m_eenum); return *this; }

   inline cflag & operator += (ENUM e) { return operator |= (e); }
   inline cflag & operator -= (ENUM e) { return operator &= ((ENUM)~(i64)(e)); }

   inline cflag & operator += (const cflag & e) { return operator |= ((ENUM)e.m_eenum); }
   inline cflag & operator -= (const cflag & e) { return operator &= ((ENUM)~(i64)(e.m_eenum)); }

   inline cflag & operator ^= (const cflag & e) { toggle(e);  return *this; }

//   inline cflag operator + (ENUM e) const { return (ENUM)(m_eenum | e); }
   inline cflag operator - (ENUM e) const { return (ENUM)(m_eenum & ~((i64)e)); }

   //template < typename TYPE >
   //cflag operator + (const TYPE & t) const { auto copy = *this; copy.add(t); return copy; }

   IMPL_OPERATOR_PLUS(cflag);

   inline cflag operator | (ENUM e) const { return (ENUM)(m_eenum | e); }
   inline cflag operator & (ENUM e) const { return (ENUM)(m_eenum & e); }

   inline bool is(ENUM e) const { return (i64)(m_eenum & e) == (i64)e; }
   inline bool has(ENUM e) const { return is(e); }

   void remove(ENUM e) { operator -= (e); }
   void add(const cflag & e) { operator += (e); }
   void unset(const cflag & e) { remove(e); }
   void set(const cflag & e) { add(e); }
   void remove(const cflag & e) { operator -= (e); }
   void clear() { m_eenum = (ENUM) 0; }

   void set(ENUM e, bool bSet) { if(bSet) set(e); else unset(e); }
   void toggle(ENUM e) { if (is(e)) unset(e); else set(e); }

   cflag & operator = (const cflag & e) { m_eenum = e.m_eenum; return *this; }


   bool operator == (const cflag & e) const { return m_eenum == e.m_eenum; }
   bool operator == (ENUM e) const { return m_eenum == e; }


   ENUM & eflag() { return (ENUM &)m_eenum; }
   ENUM eflag() const { return (ENUM)m_eenum; }

   bool operator !()
   {

      return __enum_is_failed((ENUM)m_eenum);

   }

   operator ENUM & ()
   {
      return (ENUM &)m_eenum;
   }

   operator ENUM() const
   {

      return (ENUM)m_eenum;
   }


   cflag & operator ++(int)
   {

      m_eenum = (ENUM)((::i64) m_eenum + 1);

      return *this;

   }


   cflag & operator %=(const ENUM & eenum)
   {

      m_eenum = (ENUM)((::i64) m_eenum % (::i64) eenum);

      return *this;

   }

   cflag& rotate(const ENUM& eenum)
   {

      if ((::i64) m_eenum < 0)
      {

         m_eenum = (ENUM) 0;

      }

      this->operator++(0);

      return this->operator %=(eenum);

   }

};






