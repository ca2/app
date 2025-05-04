// Created by camilo on 2025-04-24 19:01 <3ThomasBorregaardSorensen!!
#pragma once


//template < typename ITERATOR_TYPE, int t_size >
//class const_string_range_static_array;
//
//template < typename ITERATOR_TYPE >
//class const_string_range_static_array < ITERATOR_TYPE, 0>
//{
//public:
//
//
//   const_string_range_static_array() = delete;
//
//   consteval character_count size() const { return 0; }
//
//   ::range < ITERATOR_TYPE >& element_at(int i) const { return *((::range < ITERATOR_TYPE >*)nullptr); }
//
//   void concatenate_to(::non_const < ITERATOR_TYPE >& p) const
//   {
//
//   }
//
//};
//
//
//template < typename ITERATOR_TYPE >
//class const_string_range_static_array < ITERATOR_TYPE, 1>
//{
//public:
//
//   using iterator = ::non_const < ITERATOR_TYPE >;
//
//   using RANGE = ::range < ITERATOR_TYPE >;
//
//   using ASCENDANT = void;
//
//   RANGE m_range;
//
//
//   const_string_range_static_array() = delete;
//
//
//   const_string_range_static_array(const RANGE& range) :
//      m_range(range)
//   {
//
//
//   }
//
//   //template < primitive_character CHARACTER, character_count n >
//   //const_string_range_static_array(const CHARACTER(&s)[n]) :
//   //   m_range(s)
//   //{
//
//
//   //}
//
//   ::range < ITERATOR_TYPE >& top() const { return (RANGE&)m_range; }
//
//   constexpr character_count size() const { return this->m_range.size(); }
//
//   template < primitive_character TARGET_CHARACTER >
//   character_count __utf_length(TARGET_CHARACTER* ptrigger, character_count*& plen) const
//   {
//
//      return top().__utf_length(ptrigger, plen);
//
//   }
//
//   template < primitive_character TARGET_CHARACTER >
//   void __utf_concatenate_to(TARGET_CHARACTER*& p, character_count*& plen) const
//   {
//
//      top().__utf_concatenate_to(p, plen);
//
//   }
//
//   void block_concatenate_to(iterator& p) const
//   {
//
//      top().block_concatenate_to(p);
//
//   }
//
//};
//
//
//template < typename ITERATOR_TYPE, int t_size >
//class const_string_range_static_array
//{
//public:
//
//   using iterator = ::non_const < ITERATOR_TYPE >;
//
//   using RANGE = ::range < ITERATOR_TYPE >;
//
//   using ASCENDANT = ::const_string_range_static_array < ITERATOR_TYPE, t_size - 1 >;
//
//   RANGE m_rangea[t_size];
//
//   const_string_range_static_array() = delete;
//
//   const_string_range_static_array(const ASCENDANT& a, const RANGE& range)
//   {
//
//      ascendant() = a;
//
//      top() = range;
//
//   }
//
//   auto& ascendant() const { return *(ASCENDANT*)this; }
//
//   auto& element_at(int i) const { return (RANGE&)m_rangea[i]; }
//
//   auto& top() const { return element_at(t_size - 1); }
//
//   character_count size() const
//   {
//
//      return ascendant().size() + top().size();
//
//   }
//
//   template < primitive_character TARGET_CHARACTER >
//   character_count __utf_length(TARGET_CHARACTER* ptrigger, character_count*& plen) const
//   {
//
//      auto n1 = ascendant().__utf_length(ptrigger, plen);
//
//      auto n2 = top().__utf_length(ptrigger, plen);
//
//      return n1 + n2;
//
//   }
//
//   template < primitive_character TARGET_CHARACTER >
//   void __utf_concatenate_to(TARGET_CHARACTER*& p, character_count*& plen) const
//   {
//
//      ascendant().__utf_concatenate_to(p, plen);
//
//      top().__utf_concatenate_to(p, plen);
//
//   }
//
//   void block_concatenate_to(iterator& p) const
//   {
//
//      ascendant().block_concatenate_to(p);
//
//      top().block_concatenate_to(p);
//
//   }
//
//
//
//};
//
