#pragma once


//template < typename ENUM >
//inline bool __enum_is_failed(const ENUM & e) { return !(::i64)e; }


template < typename ENUM >
class enumeration
{
public:

   using ENUM_TYPE = ENUM;


   ENUM  m_eenum;


   enumeration() { m_eenum = (ENUM) 0; }
   enumeration(enum_null) { m_eenum = (ENUM)0; }
   enumeration(const ::std::initializer_list < ENUM > & list ) 
   {

      m_eenum = (ENUM) 0; 
      
      for (auto & e : list)
      {

         add(e);

      }
   
   }
   enumeration(ENUM e) { m_eenum = e; }
   //enumeration(::i64 i) { m_eenum = (ENUM) i; }
   enumeration(const enumeration & e) { m_eenum = e.m_eenum; }

   inline void add(ENUM e) { m_eenum = (ENUM)(e | m_eenum); }

   inline enumeration & operator |= (ENUM e) { add(e); return *this; }
   inline enumeration & operator &= (ENUM e) { m_eenum = (ENUM) (m_eenum & e); return *this; }

   inline enumeration & operator |= (const enumeration & e) { m_eenum = (ENUM) (e.m_eenum | m_eenum); return *this; }
   inline enumeration & operator &= (const enumeration & e) { m_eenum = (ENUM) (m_eenum & e.m_eenum); return *this; }

   inline enumeration & operator += (ENUM e) { return operator |= (e); }
   inline enumeration & operator -= (ENUM e) { return operator &= ((ENUM)~(i64)(e)); }

   inline enumeration & operator += (const enumeration & e) { return operator |= ((ENUM)e.m_eenum); }
   inline enumeration & operator -= (const enumeration & e) { return operator &= ((ENUM)~(i64)(e.m_eenum)); }

   inline enumeration & operator ^= (ENUM e) { toggle(e);  return *this; }
   inline enumeration & operator ^= (const enumeration & e) { toggle(e);  return *this; }

//   inline enumeration operator + (ENUM e) const { return (ENUM)(m_eenum | e); }
   inline enumeration operator - (ENUM e) const { return (ENUM)(m_eenum & ~((i64)e)); }

   //template < typename TYPE >
   //enumeration operator + (const TYPE & t) const { auto copy = *this; copy.add(t); return copy; }

   IMPL_OPERATOR_PLUS(enumeration);

   inline enumeration operator | (ENUM e) const { return (ENUM)(m_eenum | e); }
   inline enumeration operator & (ENUM e) const { return (ENUM)(m_eenum & e); }

   inline enumeration operator | (const enumeration & e) const { return (ENUM)(m_eenum | e.m_eenum); }
   inline enumeration operator & (const enumeration & e) const { return (ENUM)(m_eenum & e.m_eenum); }

   inline bool is(ENUM e) const { return (i64)(m_eenum & e) == (i64)e; }
   inline bool has(ENUM e) const { return is(e); }

   void erase(ENUM e) { operator -= (e); }
   void add(const enumeration & e) { operator += (e); }
   void unset(const enumeration & e) { erase(e); }
   void set(const enumeration & e) { add(e); }
   void erase(const enumeration & e) { operator -= (e); }
   void clear() { m_eenum = (ENUM) 0; }

   void set(ENUM e, bool bSet) { if(bSet) set(e); else unset(e); }
   void toggle(ENUM e) { if (is(e)) unset(e); else set(e); }

   enumeration & operator = (const enumeration & e) { m_eenum = e.m_eenum; return *this; }


   bool operator == (const enumeration & e) const { return m_eenum == e.m_eenum; }
   bool operator == (ENUM e) const { return m_eenum == e; }


   ENUM & eflag() { return (ENUM &)m_eenum; }
   ENUM eflag() const { return (ENUM)m_eenum; }

   bool operator !()
   {

      return !((ENUM)m_eenum);

   }

   operator ENUM & ()
   {
      return (ENUM &)m_eenum;
   }

   operator ENUM() const
   {

      return (ENUM)m_eenum;
   }


   enumeration & operator ++(int)
   {

      m_eenum = (ENUM)((::i64) m_eenum + 1);

      return *this;

   }


   enumeration & operator %=(const ENUM & eenum)
   {

      m_eenum = (ENUM)((::i64) m_eenum % (::i64) eenum);

      return *this;

   }

   enumeration& rotate(const ENUM& eenum)
   {

      if ((::i64) m_eenum < 0)
      {

         m_eenum = (ENUM) 0;

      }

      this->operator++(0);

      return this->operator %=(eenum);

   }

};




#define DECLARE_ENUMERATION(ENUMERATION, ENUM) \
inline ENUM operator | (ENUM e, ENUM f) { return (ENUM) ((::u64)e | (::u64)f); } \
template < primitive_integral INTEGRAL > \
inline ENUM operator | (ENUM e, INTEGRAL i) { return (ENUM) ((::u64)e | (::u64)i); } \
template < primitive_integral INTEGRAL > \
inline ENUM operator | (INTEGRAL i, ENUM e) { return (ENUM) ((::u64)i | (::u64)e); } \
inline ENUM operator & (ENUM e, ENUM f) { return (ENUM) ((::u64)e & (::u64)f); } \
template < primitive_integral INTEGRAL > \
inline ENUM operator & (ENUM e, INTEGRAL i) { return (ENUM) ((::u64)e & (::u64)i); } \
template < primitive_integral INTEGRAL > \
inline ENUM operator & (INTEGRAL i, ENUM e) { return (ENUM) ((::u64)i & (::u64)e); } \
using ENUMERATION = ::enumeration < ENUM >





