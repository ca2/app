#pragma once


//template < typename ENUM >
//inline bool __enum_is_failed(const ENUM & e) { return !(long long)e; }


template < typename ENUM >
class enumeration
{
public:

   
   using ENUM_TYPE_TAG = enum_type_t;

   using ENUM_TYPE = ENUM;


   ENUM  m_eenum;


   constexpr enumeration() { m_eenum = (ENUM) 0; }
   constexpr enumeration(enum_null) { m_eenum = (ENUM)0; }
   constexpr enumeration(const ::std::initializer_list < ENUM > & list )
   {

      m_eenum = (ENUM) 0; 
      
      for (auto & e : list)
      {

         add(e);

      }
   
   }
   constexpr enumeration(ENUM e) { m_eenum = e; }
   //template < primitive_integral INTEGRAL >
   //enumeration(INTEGRAL i) { m_eenum = (ENUM) i; }
   constexpr enumeration(const enumeration & e) { m_eenum = e.m_eenum; }

   constexpr  void add(ENUM e) { m_eenum = (ENUM)(e | m_eenum); }

   constexpr  enumeration & operator |= (ENUM e) { add(e); return *this; }
   constexpr  enumeration & operator &= (ENUM e) { m_eenum = (ENUM) (m_eenum & e); return *this; }

   constexpr  enumeration & operator |= (const enumeration & e) { m_eenum = (ENUM) (e.m_eenum | m_eenum); return *this; }
   constexpr  enumeration & operator &= (const enumeration & e) { m_eenum = (ENUM) (m_eenum & e.m_eenum); return *this; }

   constexpr  enumeration & operator += (ENUM e) { return operator |= (e); }
   constexpr  enumeration & operator -= (ENUM e) { return operator &= ((ENUM)~(long long)(e)); }

   constexpr  enumeration & operator += (const enumeration & e) { return operator |= ((ENUM)e.m_eenum); }
   constexpr  enumeration & operator -= (const enumeration & e) { return operator &= ((ENUM)~(long long)(e.m_eenum)); }

   constexpr  enumeration & operator ^= (ENUM e) { toggle(e);  return *this; }
   constexpr  enumeration & operator ^= (const enumeration & e) { toggle(e);  return *this; }

//   inline enumeration operator + (ENUM e) const { return (ENUM)(m_eenum | e); }
   constexpr  enumeration operator - (ENUM e) const { return (ENUM)(m_eenum & ~((long long)e)); }

   //template < typename TYPE >
   //enumeration operator + (const TYPE & t) const { auto copy = *this; copy.add(t); return copy; }

   //IMPL_OPERATOR_PLUS(enumeration);

   template < typename TYPE > \
   enumeration operator + (const TYPE & t) const
   { 
      auto copy = *this;
      copy.add(t);
      return copy; 
   }

   constexpr  enumeration operator | (ENUM e) const { return (ENUM)(m_eenum | e); }
   constexpr  enumeration operator & (ENUM e) const { return (ENUM)(m_eenum & e); }

   constexpr  enumeration operator | (const enumeration & e) const { return (ENUM)(m_eenum | e.m_eenum); }
   constexpr  enumeration operator & (const enumeration & e) const { return (ENUM)(m_eenum & e.m_eenum); }

   constexpr  bool is(ENUM e) const { return (long long)(m_eenum & e) == (long long)e; }
   constexpr  bool has(ENUM e) const { return is(e); }
   constexpr  bool is_clear(ENUM e) const { return !(m_eenum & e); }

   constexpr void erase(ENUM e) { operator -= (e); }
   constexpr void add(const enumeration & e) { operator += (e); }
   constexpr void unset(const enumeration & e) { erase(e); }
   constexpr void set(const enumeration & e) { add(e); }
   constexpr void erase(const enumeration & e) { operator -= (e); }
   constexpr void clear() { m_eenum = (ENUM) 0; }

   constexpr void set(ENUM e, bool bSet) { if(bSet) set(e); else unset(e); }
   constexpr void toggle(ENUM e) { if (is(e)) unset(e); else set(e); }

   constexpr enumeration & operator = (const enumeration & e) { m_eenum = e.m_eenum; return *this; }


   constexpr bool operator == (const enumeration & e) const { return m_eenum == e.m_eenum; }
   constexpr bool operator == (ENUM e) const { return m_eenum == e; }


   constexpr ENUM & eflag() { return (ENUM &)m_eenum; }
   constexpr ENUM eflag() const { return (ENUM)m_eenum; }

   constexpr bool operator !()
   {

      return !((ENUM)m_eenum);

   }

   constexpr operator ENUM & ()
   {
      return (ENUM &)m_eenum;
   }

   constexpr operator ENUM() const
   {

      return (ENUM)m_eenum;
   }


   constexpr enumeration & operator ++(int)
   {

      m_eenum = (ENUM)((long long) m_eenum + 1);

      return *this;

   }


   constexpr enumeration & operator %=(const ENUM & eenum)
   {

      m_eenum = (ENUM)((long long) m_eenum % (long long) eenum);

      return *this;

   }

   constexpr enumeration& rotate(const ENUM& eenum)
   {

      if ((long long) m_eenum < 0)
      {

         m_eenum = (ENUM) 0;

      }

      this->operator++(0);

      return this->operator %=(eenum);

   }

};




#define DECLARE_ENUMERATION(ENUMERATION, ENUM) \
constexpr  ENUM operator | (ENUM e, ENUM f) { return (ENUM) ((unsigned long long)e | (unsigned long long)f); } \
template < primitive_integral INTEGRAL > \
constexpr  ENUM operator | (ENUM e, INTEGRAL i) { return (ENUM) ((unsigned long long)e | (unsigned long long)i); } \
template < primitive_integral INTEGRAL > \
constexpr  ENUM operator | (INTEGRAL i, ENUM e) { return (ENUM) ((unsigned long long)i | (unsigned long long)e); } \
constexpr  ENUM operator & (ENUM e, ENUM f) { return (ENUM) ((unsigned long long)e & (unsigned long long)f); } \
template < primitive_integral INTEGRAL > \
constexpr  ENUM operator & (ENUM e, INTEGRAL i) { return (ENUM) ((unsigned long long)e & (unsigned long long)i); } \
template < primitive_integral INTEGRAL > \
constexpr  ENUM operator & (INTEGRAL i, ENUM e) { return (ENUM) ((unsigned long long)i & (unsigned long long)e); } \
using ENUMERATION = ::enumeration < ENUM >


