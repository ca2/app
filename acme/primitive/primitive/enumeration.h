#pragma once


//template < typename ENUM >
//inline bool __enum_is_failed(const ENUM & e) { return !(::i64)e; }


template < typename ENUM >
class enumeration
{
public:

   
   using ENUM_TAG = ENUM_TYPE_TAG;

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
   constexpr  enumeration & operator -= (ENUM e) { return operator &= ((ENUM)~(i64)(e)); }

   constexpr  enumeration & operator += (const enumeration & e) { return operator |= ((ENUM)e.m_eenum); }
   constexpr  enumeration & operator -= (const enumeration & e) { return operator &= ((ENUM)~(i64)(e.m_eenum)); }

   constexpr  enumeration & operator ^= (ENUM e) { toggle(e);  return *this; }
   constexpr  enumeration & operator ^= (const enumeration & e) { toggle(e);  return *this; }

//   inline enumeration operator + (ENUM e) const { return (ENUM)(m_eenum | e); }
   constexpr  enumeration operator - (ENUM e) const { return (ENUM)(m_eenum & ~((i64)e)); }

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

   constexpr  bool is(ENUM e) const { return (i64)(m_eenum & e) == (i64)e; }
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

      m_eenum = (ENUM)((::i64) m_eenum + 1);

      return *this;

   }


   constexpr enumeration & operator %=(const ENUM & eenum)
   {

      m_eenum = (ENUM)((::i64) m_eenum % (::i64) eenum);

      return *this;

   }

   constexpr enumeration& rotate(const ENUM& eenum)
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
constexpr  ENUM operator | (ENUM e, ENUM f) { return (ENUM) ((::u64)e | (::u64)f); } \
template < primitive_integral INTEGRAL > \
constexpr  ENUM operator | (ENUM e, INTEGRAL i) { return (ENUM) ((::u64)e | (::u64)i); } \
template < primitive_integral INTEGRAL > \
constexpr  ENUM operator | (INTEGRAL i, ENUM e) { return (ENUM) ((::u64)i | (::u64)e); } \
constexpr  ENUM operator & (ENUM e, ENUM f) { return (ENUM) ((::u64)e & (::u64)f); } \
template < primitive_integral INTEGRAL > \
constexpr  ENUM operator & (ENUM e, INTEGRAL i) { return (ENUM) ((::u64)e & (::u64)i); } \
template < primitive_integral INTEGRAL > \
constexpr  ENUM operator & (INTEGRAL i, ENUM e) { return (ENUM) ((::u64)i & (::u64)e); } \
using ENUMERATION = ::enumeration < ENUM >


template < typename ENUM > struct raw_enum_of_struct { using type = ENUM; };
template < typename ENUM > struct raw_enum_of_struct<::enumeration <ENUM>> { using type = ENUM; };
template < typename ENUM >
using raw_enum_of = typename raw_enum_of_struct<ENUM>::type;


template < primitive_enum ENUM >
inline ::i64 as_i64(const ENUM & e) { return (::i64)(::raw_enum_of<ENUM>) e; }


