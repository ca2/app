// Created by camilo on 2022-11-11 21:16 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/prototype/prototype/hash32.h"


namespace comparison
{

constexpr int get_bool_int( bool b){return b? 1:0;}

   template < typename TYPE >
   class comparison
   {
   public:


      using EQUALITY = for_type < TYPE >;
      using ORDERING = for_type < TYPE >;


      constexpr bool equals(const TYPE & a, const TYPE & b) const { return a == b; }
      constexpr auto order(const TYPE & a, const TYPE & b) const { return a <=> b; }


   };

template <  >
class comparison < bool >
{
public:


   using EQUALITY = for_type < bool >;
   using ORDERING = for_type < bool >;


   constexpr bool equals(bool a, bool b) const { return get_bool_int(a) == get_bool_int(b); }
   constexpr auto order(bool a, bool b) const { return get_bool_int(a) <=> get_bool_int(b); }
   

};


   template < primitive_fundamental TYPE >
   class comparison < TYPE >
   {
   public:


      using EQUALITY = for_type < TYPE >;
      using ORDERING = for_type < TYPE >;


      constexpr bool equals(TYPE a, TYPE b) const { return a == b; }
      constexpr auto order(TYPE a, TYPE b) const { return a <=> b; }


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



// block_cast and literal_cast work together
// block_cast converts from a potentially smaller literal type to a potentially larger block type through memory copy
// literal_cast converts from a potentially larger block type to a potentially smaller literal type through memory copy
// so the block type must be larger or equal in size to the literal type



template < typename LITERAL >
class literal_cast 
{
public:


	LITERAL m_literal;


	template < typename BLOCK >
	literal_cast(const BLOCK & block)
	{
		
		static_assert(sizeof(m_literal) <= sizeof(block));
		
		memory_copy(&m_literal, &block, sizeof(m_literal));
		
	}


	operator LITERAL &() { return m_literal; }

	operator const LITERAL &() const { return m_literal; }

	
};


template < typename BLOCK >
class block_cast 
{
public:


	BLOCK m_block{};


	template < typename LITERAL >
	block_cast(const LITERAL & literal)
	{
		
		static_assert(sizeof(m_block) >= sizeof(literal));
		
		memory_copy(&m_block, &literal, sizeof(literal));
		
	}

	operator BLOCK &() { return m_block; }

	operator const BLOCK &() const { return m_block; }

	
};



template < typename T1, typename T2>
T1 as(const T2& t2)
{

   return (T1)t2;

}


inline constexpr std::strong_ordering to_strong_ordering(std::partial_ordering po) {
   if (po == std::partial_ordering::less) {
      return std::strong_ordering::less;
   }
   else if (po == std::partial_ordering::equivalent) {
      return std::strong_ordering::equal; // Note: equivalent maps to equal for strong_ordering
   }
   else if (po == std::partial_ordering::greater) {
      return std::strong_ordering::greater;
   }
   // Handle the 'unordered' case if it's possible and needs specific handling,
   // otherwise, this indicates an invalid state for strong_ordering.
   // For example, you might throw an exception or return a default strong_ordering value
   // if 'unordered' is not expected.
   // throw std::runtime_error("Cannot convert unordered partial_ordering to strong_ordering");
   return std::strong_ordering::equal; // Or some other appropriate default/error handling
}



inline constexpr std::partial_ordering to_partial_ordering(std::strong_ordering strongordering) {
   if (strongordering == std::strong_ordering::less) {
      return std::partial_ordering::less;
   }
   else if (strongordering == std::strong_ordering::equal) {
      return std::partial_ordering::equivalent; // Note: equivalent maps to equal for strong_ordering
   }
   else if (strongordering == std::strong_ordering::greater) {
      return std::partial_ordering::greater;
   }
   // Handle the 'unordered' case if it's possible and needs specific handling,
   // otherwise, this indicates an invalid state for strong_ordering.
   // For example, you might throw an exception or return a default strong_ordering value
   // if 'unordered' is not expected.
   // throw std::runtime_error("Cannot convert unordered partial_ordering to strong_ordering");
   return std::partial_ordering::equivalent; // Or some other appropriate default/error handling
}



template < >
inline constexpr std::strong_ordering as <::std::strong_ordering, ::std::partial_ordering >(
   const std::partial_ordering& partialordering)
{

   return to_strong_ordering(partialordering);

}



template < >
inline constexpr std::partial_ordering as <::std::partial_ordering, ::std::strong_ordering >(
   const std::strong_ordering& strongordering)
{

   return to_partial_ordering(strongordering);

}