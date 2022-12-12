// Created by camilo on 2022-11-11 21:16 <3ThomasBorregaardSorensen!!
#pragma once


struct u32hash
{

   ::u32 m_u;


   template < typename T >
   u32hash(const T* p) : m_u((::u32)(::uptr)p) {}
   template < primitive_integral INTEGRAL >
   u32hash(INTEGRAL i) : m_u((::u32)i) {}
   template < a_enum ENUM >
   u32hash(const ::enumeration < ENUM > & e) : m_u((::u32)e.m_eenum) {}
   u32hash(::f32 f) : m_u(*(::u32 *)&f) {}
   u32hash(::f64 d) : m_u(((::u32*)&d)[0]| ((::u32*)&d)[1]) {}
   template < typename T >
   u32hash(const ::pointer < T >& t) : m_u((::u32)(::uptr)t.m_p) {}
   u32hash(const ::u32hash& u32hash) : m_u(u32hash.m_u) {}
   u32hash() {}

};


namespace comparison
{


   template < typename TYPE >
   class comparison
   {
   public:


      using EQUALITY = for_type < TYPE >;
      using ORDERING = for_type < TYPE >;


      constexpr bool equals(const TYPE & a, const TYPE & b) const { return a == b; }
      constexpr ::std::strong_ordering order(const TYPE & a, const TYPE & b) const { return a <=> b; }


   };


   template < primitive_fundamental TYPE >
   class comparison < TYPE >
   {
   public:


      using EQUALITY = for_type < TYPE >;
      using ORDERING = for_type < TYPE >;


      constexpr bool equals(TYPE a, TYPE b) const { return a == b; }
      constexpr ::std::strong_ordering order(TYPE a, TYPE b) const { return a <=> b; }


   };


   //template < primitive_character CHARACTER >
   //class comparison :
   //   public comparison < CHARACTER >
   //{
   //public:
   //
   //
   //   //using EQUALITY_TRAITS = EQUALITY_TRAITS_TAG;
   //   //using COMPARISON_TRAITS = COMPARISON_TRAITS_TAG;
   //
   //
   //   //constexpr bool equals(CHARACTER a, CHARACTER b) const { return a == b; }
   //   //constexpr ::std::strong_ordering compare(CHARACTER a, CHARACTER b) const { return a <=> b; }
   //
   //
   //};




} // namespace comparison



