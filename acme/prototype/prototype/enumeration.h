// Refactored by camilo on 2026-05-30 03:10 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


struct hash32;


template < typename INTEGRAL >
concept prototype_integral = std::is_integral_v < ::decay < INTEGRAL > >;


template < typename CFLAG >
class c_flag
{
public:

   
   using CFLAG_TYPE_TAG = c_flag_type_t;

   using CFLAG_TYPE = CFLAG;

   using CFLAG_INT = std::underlying_type_t<CFLAG_TYPE>;


   CFLAG  m_cflag;


   constexpr c_flag() { m_cflag = (CFLAG) 0; }
   constexpr c_flag(const ::std::initializer_list < CFLAG > & list_base )
   {

      m_cflag = (CFLAG) 0; 
      
      for (auto & e : list_base)
      {

         add(e);

      }
   
   }
   template < typename THE_CFLAG >
   constexpr c_flag(THE_CFLAG e)
   requires (::std::is_same_v < THE_CFLAG,  CFLAG >
      && !prototype_integral<THE_CFLAG>)
   { m_cflag = (CFLAG) e; }
   //template < prototype_integral INTEGRAL >
   //c_flag(INTEGRAL i) { m_cflag = (CFLAG) i; }
   constexpr c_flag(const c_flag & e) { m_cflag = e.m_cflag; }

   //constexpr  void add(const c_flag & e) { m_cflag = e | m_cflag; }

   constexpr  c_flag & operator |= (const c_flag & e) { m_cflag = (CFLAG) ((CFLAG_INT)e.m_cflag | (CFLAG_INT)m_cflag); return *this; }
   constexpr  c_flag & operator &= (const c_flag & e) { m_cflag = (CFLAG) ((CFLAG_INT)m_cflag & (CFLAG_INT)e.m_cflag); return *this; }

   constexpr  c_flag & operator += (const c_flag & e) { return operator |= (e); }
   constexpr  c_flag & operator -= (const c_flag & e) { return operator &= (~e); }

   constexpr  c_flag & operator ^= (const c_flag & e) { toggle(e);  return *this; }

//   inline c_flag operator + (CFLAG e) const { return (CFLAG)(m_cflag | e); }
   constexpr  CFLAG operator - (const c_flag & e) const { return m_cflag & ~e; }

   //template < typename TYPE >
   //c_flag operator + (const TYPE & t) const { auto copy = *this; copy.add(t); return copy; }

   //IMPL_OPERATOR_PLUS(c_flag);

   template < typename TYPE > \
   CFLAG operator + (const TYPE & t) const
   {
      auto copy = *this;
      copy.add(t);
      return copy; 
   }

   constexpr  CFLAG operator | (const c_flag & e) const { return (CFLAG) ((CFLAG_INT) m_cflag | (CFLAG_INT) e.m_cflag); }
   constexpr  CFLAG operator & (const c_flag & e) const { return (CFLAG) ((CFLAG_INT) m_cflag & (CFLAG_INT) e.m_cflag); }

   constexpr  CFLAG operator | (const CFLAG & e) const { return (CFLAG) ((CFLAG_INT) m_cflag | (CFLAG_INT) e); }
   constexpr  CFLAG operator & (const CFLAG & e) const { return (CFLAG) ((CFLAG_INT) m_cflag & (CFLAG_INT) e); }

   constexpr  bool is(const c_flag & e) const { return (m_cflag & e) == e; }
   constexpr  bool has(c_flag e) const { return is(e); }
   constexpr  bool is_clear(const c_flag & e) const { return !(m_cflag & e); }
   constexpr  bool is_null() const { return m_cflag == (CFLAG)0; }
   constexpr  bool is_set() const { return !is_null(); }

   constexpr void erase(const c_flag & e) { operator -= (e); }
   constexpr void add(const c_flag & e) { operator += (e); }
   constexpr void unset(const c_flag & e) { erase(e); }
   constexpr void set(const c_flag & e) { add(e); }
   constexpr void clear() { m_cflag = (CFLAG) 0; }

   constexpr void set(const c_flag & e, bool bSet) { if(bSet) set(e); else unset(e); }
   constexpr void toggle(const c_flag & e) { if (is(e)) unset(e); else set(e); }

   constexpr c_flag & operator = (const c_flag & e) { m_cflag = e.m_cflag; return *this; }


   constexpr bool operator == (const c_flag & e) const { return m_cflag == e.m_cflag; }


   constexpr CFLAG & eflag() { return (CFLAG &)m_cflag; }
   constexpr CFLAG eflag() const { return (CFLAG)m_cflag; }

   constexpr bool operator !()
   {

      return !((CFLAG)m_cflag);

   }

   constexpr explicit operator bool() const {
      return this->is_set();
   }

   constexpr explicit operator ::i64() const {
      return (::i64)m_cflag;
   }

   constexpr explicit operator ::i32() const {
      return (::i32)m_cflag;
   }

   constexpr explicit operator ::u64() const {
      return (::u64)m_cflag;
   }

   constexpr explicit operator ::u32() const {
      return (::u32)m_cflag;
   }
   constexpr explicit operator ::hash32() const;


   constexpr explicit operator ::i16() const {
      return (::i64)m_cflag;
   }

   constexpr explicit operator ::i8() const {
      return (::i32)m_cflag;
   }

   constexpr explicit operator ::u16() const {
      return (::u16)m_cflag;
   }

   constexpr explicit operator ::u8() const {
      return (::u32)m_cflag;
   }

   // constexpr operator CFLAG & ()
   // {
   //    return (CFLAG &)m_cflag;
   // }
   //
   // constexpr operator CFLAG() const
   // {
   //
   //    return (CFLAG)m_cflag;
   // }


   constexpr CFLAG operator ~() const
   {

      return (CFLAG)(~(CFLAG_INT) m_cflag);


   }


   constexpr c_flag & operator ++(::i32)
   {

      m_cflag = (CFLAG)((CFLAG_INT) m_cflag + 1);

      return *this;

   }


   constexpr c_flag & operator %=(const CFLAG & eenum)
   {

      m_cflag = (CFLAG)((CFLAG_INT) m_cflag % (CFLAG_INT) eenum);

      return *this;

   }

   constexpr c_flag& rotate(const CFLAG& eenum)
   {

      if ((CFLAG_INT) m_cflag < 0)
      {

         m_cflag = (CFLAG) 0;

      }

      this->operator ++(0);

      return this->operator %=(eenum);

   }

   constexpr ::std::strong_ordering operator<=>(const c_flag & e) const
   {
      return (CFLAG_INT)m_cflag <=> (CFLAG_INT) e.m_cflag;
   }


};


template < typename ENUM >
class enumeration
{
public:


   using ENUM_TYPE_TAG = enum_type_t;

   using ENUM_TYPE = ENUM;

   using ENUM_INT = std::underlying_type_t<ENUM_TYPE>;


   ENUM  m_eenum;


   constexpr enumeration() { m_eenum = (ENUM) 0; }
   constexpr enumeration(const ::std::initializer_list < ENUM > & list_base )
   {

      m_eenum = (ENUM) 0;

      for (auto & e : list_base)
      {

         add(e);

      }

   }
   template < typename THE_ENUM >
   constexpr enumeration(THE_ENUM e)
   requires (::std::is_same_v < THE_ENUM,  ENUM >
      && !prototype_integral<THE_ENUM>)
   { m_eenum = (ENUM) e; }
   //template < prototype_integral INTEGRAL >
   //enumeration(INTEGRAL i) { m_eenum = (ENUM) i; }
   constexpr enumeration(const enumeration & e) { m_eenum = e.m_eenum; }

//    constexpr  void add(ENUM e) { m_eenum = (ENUM)(e | m_eenum); }
//
//    constexpr  enumeration & operator |= (ENUM e) { add(e); return *this; }
//    constexpr  enumeration & operator &= (ENUM e) { m_eenum = (ENUM) (m_eenum & e); return *this; }
//
//    constexpr  enumeration & operator |= (const enumeration & e) { m_eenum = (ENUM) (e.m_eenum | m_eenum); return *this; }
//    constexpr  enumeration & operator &= (const enumeration & e) { m_eenum = (ENUM) (m_eenum & e.m_eenum); return *this; }
//
//    constexpr  enumeration & operator += (ENUM e) { return operator |= (e); }
//    constexpr  enumeration & operator -= (ENUM e) { return operator &= ((ENUM)~(::i64)(e)); }
//
//    constexpr  enumeration & operator += (const enumeration & e) { return operator |= ((ENUM)e.m_eenum); }
//    constexpr  enumeration & operator -= (const enumeration & e) { return operator &= ((ENUM)~(::i64)(e.m_eenum)); }
//
//    constexpr  enumeration & operator ^= (ENUM e) { toggle(e);  return *this; }
//    constexpr  enumeration & operator ^= (const enumeration & e) { toggle(e);  return *this; }
//
// //   inline enumeration operator + (ENUM e) const { return (ENUM)(m_eenum | e); }
//    constexpr  enumeration operator - (ENUM e) const { return (ENUM)(m_eenum & ~((::i64)e)); }

   //template < typename TYPE >
   //enumeration operator + (const TYPE & t) const { auto copy = *this; copy.add(t); return copy; }

   //IMPL_OPERATOR_PLUS(enumeration);

   //template < typename TYPE > \
   //enumeration operator + (const TYPE & t) const
   //{
   //   auto copy = *this;
   //   copy.add(t);
   //   return copy;
   //}

   //constexpr  enumeration operator | (ENUM e) const { return (ENUM)(m_eenum | e); }
   //constexpr  enumeration operator & (ENUM e) const { return (ENUM)(m_eenum & e); }

   template < prototype_integral INTEGRAL >
   constexpr  enumeration operator + (INTEGRAL i) const { return (ENUM)((::std::underlying_type_t<ENUM>) m_eenum + i); }
   //constexpr  enumeration operator & (const enumeration & e) const { return (ENUM)(m_eenum & e.m_eenum); }

   constexpr bool is(ENUM e) const { return m_eenum == e; }
   //constexpr bool has(ENUM e) const { return is(e); }
   //constexpr bool is_clear(ENUM e) const { return !(m_eenum & e); }
   constexpr bool is_null() const { return !is_set(); }
   constexpr bool is_set() const { return !is_set(); }

   //constexpr void erase(ENUM e) { operator -= (e); }
   //constexpr void add(const enumeration & e) { operator += (e); }
   //constexpr void unset(const enumeration & e) { erase(e); }
   constexpr void set(const enumeration & e) { m_eenum = e; }
   //constexpr void erase(const enumeration & e) { operator -= (e); }
   constexpr void clear() { m_eenum = (ENUM) 0; }

   // constexpr void set(ENUM e, bool bSet) { if(bSet) set(e); else unset(e); }
   // constexpr void toggle(ENUM e) { if (is(e)) unset(e); else set(e); }

   constexpr enumeration & operator = (const enumeration & e) { m_eenum = e.m_eenum; return *this; }


   constexpr bool operator == (const enumeration & e) const { return m_eenum == e.m_eenum; }
   //constexpr bool operator == (ENUM e) const { return m_eenum == e; }


   constexpr ENUM & eflag() { return (ENUM &)m_eenum; }
   constexpr ENUM eflag() const { return (ENUM)m_eenum; }

   constexpr bool operator !()
   {

      return !((ENUM)m_eenum);

   }



   constexpr explicit operator bool() const {
      return this->is_set();
   }

   constexpr explicit operator ::i64() const {
      return (::i64)m_eenum;
   }

   constexpr explicit operator ::i32() const {
      return (::i32)m_eenum;
   }

   constexpr explicit operator ::u64() const {
      return (::u64)m_eenum;
   }

   constexpr explicit operator ::u32() const {
      return (::u32)m_eenum;
   }

   constexpr explicit operator ::hash32() const;

   constexpr explicit operator ::i16() const {
      return (::i64)m_eenum;
   }

   constexpr explicit operator ::i8() const {
      return (::i32)m_eenum;
   }

   constexpr explicit operator ::u16() const {
      return (::u16)m_eenum;
   }

   constexpr explicit operator ::u8() const {
      return (::u32)m_eenum;
   }


   //constexpr operator ENUM & ()
   //{
     // return (ENUM &)m_eenum;
   //}

   // constexpr operator ENUM() const
   // {
   //
   //    return (ENUM)m_eenum;
   // }


   enumeration & operator ++(::i32)
   {

      m_eenum = (ENUM)((ENUM_INT) m_eenum + 1);

      return *this;

   }


   enumeration & operator %=(const enumeration & eenum)
   {

      m_eenum = (ENUM)((ENUM_INT) m_eenum % (ENUM_INT) eenum.m_eenum);

      return *this;

   }

   enumeration& modulus(const enumeration & eenumMin, const enumeration & eenumMax)
   {

      m_eenum = (ENUM) ((ENUM_INT) eenumMin.m_eenum + ((m_eenum - eenumMin) % (eenumMax - eenumMin)));
      return *this;
   }

   enumeration& rotate(const enumeration & eenumMin, const enumeration & eenumMax)
   {
      operator++(0);
      return modulus(eenumMin, eenumMax);

   }

   enumeration& rotate(const enumeration & eenumMax)
   {
      return rotate((ENUM) 0, eenumMax);

   }

   constexpr ENUM_INT operator-(const enumeration & e) const
   {

      return (ENUM_INT)m_eenum - (ENUM_INT) e.m_eenum;

   }

   constexpr ::std::strong_ordering operator<=>(const enumeration & e) const
   {

      return (ENUM_INT)m_eenum <=> (ENUM_INT) e.m_eenum;

   }

};


#define DECLARE_C_FLAG(TYPE, CFLAG) \
using TYPE = ::c_flag < CFLAG >; \
constexpr CFLAG operator | (CFLAG e, CFLAG f) { return (CFLAG) ((::std::underlying_type_t<CFLAG>)e | (::std::underlying_type_t<CFLAG>)f); } \
constexpr CFLAG operator | (CFLAG e, const TYPE & f) { return (CFLAG) ((::std::underlying_type_t<CFLAG>)e | (::std::underlying_type_t<CFLAG>)f.m_cflag); } \
template < prototype_integral INTEGRAL > \
constexpr CFLAG operator | (CFLAG e, INTEGRAL i) { return (CFLAG) ((::std::underlying_type_t<CFLAG>)e | (::std::underlying_type_t<CFLAG>)i); } \
template < prototype_integral INTEGRAL > \
constexpr CFLAG operator | (INTEGRAL i, const TYPE & e) { return (CFLAG) ((::std::underlying_type_t<CFLAG>)i | (::std::underlying_type_t<CFLAG>)e.m_cflag); } \
constexpr CFLAG operator & (CFLAG e, CFLAG f) { return (CFLAG) ((::std::underlying_type_t<CFLAG>)e & (::std::underlying_type_t<CFLAG>)f); } \
constexpr CFLAG operator & (CFLAG e, const TYPE & f) { return (CFLAG) ((::std::underlying_type_t<CFLAG>)e & (::std::underlying_type_t<CFLAG>)f.m_cflag); } \
template < prototype_integral INTEGRAL > \
constexpr CFLAG operator & (CFLAG e, INTEGRAL i) { return (CFLAG) ((::std::underlying_type_t<CFLAG>)e & (::std::underlying_type_t<CFLAG>)i); } \
template < prototype_integral INTEGRAL > \
constexpr CFLAG operator & (INTEGRAL i, const TYPE & e) { return (CFLAG) ((::std::underlying_type_t<CFLAG>)i & (::std::underlying_type_t<CFLAG>)e.m_cflag); } \
constexpr CFLAG operator ~ (CFLAG e) { return (CFLAG) (~(::std::underlying_type_t<CFLAG>)e); }





#define DECLARE_ENUMERATION(ENUMERATION, ENUM) \
using ENUMERATION = ::enumeration < ENUM >; \
template < prototype_integral INTEGRAL > \
constexpr  ENUMERATION operator + (ENUM e, INTEGRAL i) { return (ENUM) ((::std::underlying_type_t<ENUM>)e + (::std::underlying_type_t<ENUM>)i); } \
constexpr auto operator - (ENUM e, ENUM f) { return ((::std::underlying_type_t<ENUM>)e - (::std::underlying_type_t<ENUM>)f); } \
constexpr auto operator - (ENUM e, const ENUMERATION & f) { return ((::std::underlying_type_t<ENUM>)e - (::std::underlying_type_t<ENUM>)f.m_eenum); } \
template < prototype_integral INTEGRAL > \
constexpr  ENUMERATION operator - (ENUM e, INTEGRAL i) { return (ENUM) ((::std::underlying_type_t<ENUM>)e & (::std::underlying_type_t<ENUM>)i); } \



//constexpr  ENUM operator + (ENUM e, ENUM f) { return (ENUM) ((::std::underlying_type_t<CFLAG>)e + (::std::underlying_type_t<CFLAG>)f); }
//template < prototype_integral INTEGRAL >
//constexpr  ENUM operator + (INTEGRAL i, ENUM e) { return (ENUM) ((::std::underlying_type_t<CFLAG>)i | (::std::underlying_type_t<CFLAG>)e); }
//constexpr  ENUM operator - (ENUM e, ENUM f) { return (ENUM) ((::std::underlying_type_t<CFLAG>)e & (::std::underlying_type_t<CFLAG>)f); }
//template < prototype_integral INTEGRAL >
//constexpr  ENUM operator - (INTEGRAL i, ENUM e) { return (ENUM) ((::std::underlying_type_t<CFLAG>)i & (::std::underlying_type_t<CFLAG>)e); }
