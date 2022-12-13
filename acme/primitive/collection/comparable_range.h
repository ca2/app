// Created by camilo on 2022-12-07 22:49 <3ThomasBorregaardSorensen!!
#pragma once



template < typename RANGE_TYPE >
class comparable_range :
   public RANGE_TYPE
{
public:

   
   using BASE_RANGE = RANGE_TYPE;

   using THIS_RANGE = ::comparable_range < BASE_RANGE >;



   using this_iterator = BASE_RANGE::this_iterator;
   using iterator = BASE_RANGE::iterator;
   using const_iterator = BASE_RANGE::const_iterator;

   
   using THIS_RAW_RANGE = BASE_RANGE::THIS_RAW_RANGE;
   using RAW_RANGE = BASE_RANGE::RAW_RANGE;
   using CONST_RAW_RANGE = BASE_RANGE::CONST_RAW_RANGE;

   using ITEM_POINTER = get_type_item_pointer < this_iterator >::type;

   using ITEM = dereference < ITEM_POINTER >;


   using BASE_RANGE::BASE_RANGE;


   comparable_range(enum_no_initialize) : RANGE_TYPE(e_no_initialize) {}
   comparable_range(nullptr_t) : RANGE_TYPE(nullptr) {}
   comparable_range() {}
   template<typed_range<iterator> RANGE>
   comparable_range(const RANGE &range) : BASE_RANGE(range) {}
   template<typed_range<const_iterator> RANGE>
   comparable_range(const RANGE &range) : BASE_RANGE(range) {}
   explicit comparable_range(const THIS_RANGE & range) : BASE_RANGE(range) {}
   explicit comparable_range(THIS_RANGE && range) : BASE_RANGE(::move(range)) {}
   template < primitive_integral INTEGRAL >
   comparable_range(const_iterator begin, INTEGRAL count, e_range erange = e_range_read_only_block) : BASE_RANGE(begin, count, erange) {}
   comparable_range(const_iterator begin, const_iterator end, e_range erange = e_range_read_only_block) : BASE_RANGE(begin, end, erange) {}
   comparable_range(const_iterator begin) : BASE_RANGE(begin, span_zero_item(begin), e_range_null_terminated | e_range_read_only_block) {}


   template < primitive_range RANGE >
   comparable_range & operator = (const RANGE & range) { BASE_RANGE::operator=(range); return *this; }
   comparable_range & operator = (const THIS_RANGE & range) { BASE_RANGE::operator=(range); return *this; }
   comparable_range & operator = (THIS_RANGE && range) { BASE_RANGE::operator=(::move(range)); return *this; }


   using BASE_RANGE::_order;

   constexpr ::std::strong_ordering _order(CONST_RAW_RANGE range) const
   {

      return _order(range, ::comparison::comparison < ITEM >());

   }


   using BASE_RANGE::order;

   constexpr ::std::strong_ordering order(CONST_RAW_RANGE range) const
   {

      return RANGE_TYPE::order(range, ::comparison::comparison < ITEM >());

   }


   constexpr ::std::strong_ordering operator<=>(CONST_RAW_RANGE range) const
   {

      return this->order(range);

   }


};


//template < typename this_iterator >
//using range = comparable_range < range_base < this_iterator > >;

//
//template < typename RANGE_TYPE >
//class comparable_range :
//   public comparable_range < RANGE_TYPE >
//{
//public:
//
//   using this_iterator = RANGE_TYPE::ITERATOR_TYPE;
//
//   using ITEM = this_iterator::ITEM;
//
//
//   using this_iterator = this_iterator::this_iterator;
//
//   using CONST_RAW_RANGE = range < this_iterator >;
//
//   using ITERATOR_TYPE = this_iterator;
//
//   using this_iterator = this_iterator::this_iterator;
//
//   typedef this_iterator const_iterator;
//
//   bool m_bDeclaredNullTerminated = false;
//
//
//   
//   using comparable_range < RANGE_TYPE >::comparable_range;
//
//
//   comparable_range(const ITEM * pitem) : range(pitem, span_zero_item(data)), m_bDeclaredNullTerminated(true) {}
//   comparable_range(this_iterator data) : comparable_range((const ITEM *)data) {}
//
//
//   using comparable_range < RANGE_TYPE >::_equals;
//
//   constexpr bool _equals(CONST_RAW_RANGE range) const
//   {
//
//      return _equals(range, ::equals_const_reference < ITEM >);
//
//   }
//
//   using comparable_range < RANGE_TYPE >::equals;
//
//   constexpr bool equals(CONST_RAW_RANGE range) const
//   {
//
//      return range<const ITEM>(*this).compare(range, equals_const_reference <const ITEM>);
//
//   }
//
//
//   using comparable_range < RANGE_TYPE >::_order;
//
//   constexpr ::std::strong_ordering _order(CONST_RAW_RANGE range) const
//   {
//
//      return _order(range, ::compare < ITEM >);
//
//   }
//
//   using comparable_range < RANGE_TYPE >::compare;
//
//   constexpr ::std::strong_ordering compare(CONST_RAW_RANGE range) const
//   {
//
//      return range<const ITEM>(*this).compare(range, compare_const_reference <const ITEM>);
//
//   }
//
//
//   constexpr ::std::strong_ordering operator<=>(CONST_RAW_RANGE range) const
//   {
//
//      return compare(range, ::compare < ITEM >);
//
//   }
//
//
//   using comparable_range < RANGE_TYPE >::find;
//
//
//   this_iterator find(CONST_RAW_RANGE range, strsize iStart = 0, strsize nCount = -1, this_iterator * ppszTail = nullptr) const RELEASENOTHROW
//   {
//
//      return find(range, iStart, nCount, ppszTail, ::equals_const_reference < ITEM >);
//
//   }
//
//
//   using comparable_range < RANGE_TYPE >::_scan;
//
//   constexpr this_iterator _scan(CONST_RAW_RANGE range) noexcept
//   {
//
//      return _scan(range, ::equals_const_reference < ITEM >);
//
//   }
//
//   using comparable_range < RANGE_TYPE >::scan;
//
//     constexpr this_iterator scan(CONST_RAW_RANGE range) noexcept
//     {
//
//        return scan(range, ::equals_const_reference < ITEM >);
//
//     }
//
//     using comparable_range < RANGE_TYPE >::_span;
//
//   constexpr this_iterator _span(CONST_RAW_RANGE range) noexcept
//   {
//
//      return _span(range, ::equals_const_reference < ITEM >);
//
//   }
//
//   using comparable_range < RANGE_TYPE >::span;
//
//   constexpr this_iterator span(CONST_RAW_RANGE range) noexcept
//   {
//
//      return span(range, ::equals_const_reference < ITEM >);
//
//   }
//
//   using comparable_range < RANGE_TYPE >::_skip;
//
//   constexpr this_iterator _skip(const ITEM & item) noexcept
//   {
//
//      return _skip(item, ::equals_const_reference < ITEM >);
//
//   }
//
//   using comparable_range < RANGE_TYPE >::skip;
//
//   constexpr this_iterator skip(const ITEM & item) noexcept
//   {
//
//      return skip(item, ::equals_const_reference < ITEM >);
//
//   }
//
//   using comparable_range < RANGE_TYPE >::_rear_find_item;
//
//     constexpr this_iterator _rear_find_item(ITEM item) noexcept
//     {
//
//        return _rear_find_item(item, ::equals_const_reference < ITEM >);
//
//     }
//
//
//     using comparable_range < RANGE_TYPE >::rear_find_item;
//
//   constexpr this_iterator rear_find_item(ITEM item) noexcept
//   {
//
//      return rear_find_item(item, ::equals_const_reference < ITEM >);
//
//   }
//
//   using comparable_range < RANGE_TYPE >::_rear_scan;
//
//   constexpr this_iterator _rear_scan(CONST_RAW_RANGE range) noexcept
//   {
//
//      return _rear_scan(range, ::equals_const_reference < ITEM >);
//
//   }
//
//   using comparable_range < RANGE_TYPE >::rear_scan;
//
//   constexpr this_iterator rear_scan(CONST_RAW_RANGE range) noexcept
//   {
//
//      return rear_scan(range, ::equals_const_reference < ITEM >);
//
//   }
//
//};
//
//
//



//}