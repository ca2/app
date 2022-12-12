// Created by camilo on 2022-12-07 22:49 <3ThomasBorregaardSorensen!!
#pragma once



template < typename RANGE_TYPE >
class comparable_range :
   public RANGE_TYPE
{
public:

   
   using RANGE = comparable_range < RANGE_TYPE >;


   using RANGE_ITERATOR = RANGE_TYPE::RANGE_ITERATOR;
   using iterator = RANGE_TYPE::iterator;
   using const_iterator = RANGE_TYPE::const_iterator;

   
   using RAW_RANGE = ::range < RANGE_ITERATOR >;
   using CONST_RAW_RANGE = RANGE_TYPE::CONST_RAW_RANGE;





   
   using ITEM_POINTER = get_type_item_pointer < RANGE_ITERATOR >::type;

   using ITEM = dereference < ITEM_POINTER >;


   using RANGE_TYPE::RANGE_TYPE;


   explicit comparable_range(enum_no_initialize) : RANGE_TYPE(e_no_initialize) {}
   explicit comparable_range(nullptr_t) : RANGE_TYPE(nullptr) {}
   explicit comparable_range() {}
   comparable_range(const comparable_range & range) : RANGE_TYPE(range) {}
   comparable_range(comparable_range && range) : RANGE_TYPE(::move(range)) { }
   comparable_range(::range < const_iterator > constrange) : RANGE_TYPE((RANGE_TYPE)constrange) {}
   template < primitive_integral INTEGRAL >
   comparable_range(const_iterator begin, INTEGRAL count, bool bNullTerminated = false) : RANGE_TYPE(begin, count, bNullTerminated) {}
   comparable_range(const_iterator begin, const_iterator end, bool bNullTerminated = false) : RANGE_TYPE(begin, end, bNullTerminated) {}
   comparable_range(const_iterator begin) : RANGE_TYPE(begin, span_zero_item(begin), true) {}


   comparable_range & operator = (const comparable_range & comparable_range) { RANGE_TYPE::operator=(comparable_range); return *this; }
   comparable_range & operator = (comparable_range && comparable_range) { RANGE_TYPE::operator=(::move(comparable_range)); return *this; }


   using RANGE_TYPE::_order;

   constexpr ::std::strong_ordering _order(RANGE range) const
   {

      return _order(range, ::comparison::comparison < ITEM >());

   }

   using RANGE_TYPE::order;

   constexpr ::std::strong_ordering order(RANGE range) const
   {

      return RANGE_TYPE::order(range, ::comparison::comparison < ITEM >());

   }


   constexpr ::std::strong_ordering operator<=>(RANGE range) const
   {

      return this->order(range);

   }


};


//template < typename RANGE_ITERATOR >
//using range = comparable_range < range_base < RANGE_ITERATOR > >;

//
//template < typename RANGE_TYPE >
//class comparable_range :
//   public comparable_range < RANGE_TYPE >
//{
//public:
//
//   using RANGE_ITERATOR = RANGE_TYPE::ITERATOR_TYPE;
//
//   using ITEM = RANGE_ITERATOR::ITEM;
//
//
//   using RANGE_ITERATOR = RANGE_ITERATOR::RANGE_ITERATOR;
//
//   using CONST_RAW_RANGE = range < RANGE_ITERATOR >;
//
//   using ITERATOR_TYPE = RANGE_ITERATOR;
//
//   using RANGE_ITERATOR = RANGE_ITERATOR::RANGE_ITERATOR;
//
//   typedef RANGE_ITERATOR const_iterator;
//
//   bool m_bDeclaredNullTerminated = false;
//
//
//   
//   using comparable_range < RANGE_TYPE >::comparable_range;
//
//
//   comparable_range(const ITEM * pitem) : range(pitem, span_zero_item(data)), m_bDeclaredNullTerminated(true) {}
//   comparable_range(RANGE_ITERATOR data) : comparable_range((const ITEM *)data) {}
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
//   RANGE_ITERATOR find(CONST_RAW_RANGE range, strsize iStart = 0, strsize nCount = -1, RANGE_ITERATOR * ppszTail = nullptr) const RELEASENOTHROW
//   {
//
//      return find(range, iStart, nCount, ppszTail, ::equals_const_reference < ITEM >);
//
//   }
//
//
//   using comparable_range < RANGE_TYPE >::_scan;
//
//   constexpr RANGE_ITERATOR _scan(CONST_RAW_RANGE range) noexcept
//   {
//
//      return _scan(range, ::equals_const_reference < ITEM >);
//
//   }
//
//   using comparable_range < RANGE_TYPE >::scan;
//
//     constexpr RANGE_ITERATOR scan(CONST_RAW_RANGE range) noexcept
//     {
//
//        return scan(range, ::equals_const_reference < ITEM >);
//
//     }
//
//     using comparable_range < RANGE_TYPE >::_span;
//
//   constexpr RANGE_ITERATOR _span(CONST_RAW_RANGE range) noexcept
//   {
//
//      return _span(range, ::equals_const_reference < ITEM >);
//
//   }
//
//   using comparable_range < RANGE_TYPE >::span;
//
//   constexpr RANGE_ITERATOR span(CONST_RAW_RANGE range) noexcept
//   {
//
//      return span(range, ::equals_const_reference < ITEM >);
//
//   }
//
//   using comparable_range < RANGE_TYPE >::_skip;
//
//   constexpr RANGE_ITERATOR _skip(const ITEM & item) noexcept
//   {
//
//      return _skip(item, ::equals_const_reference < ITEM >);
//
//   }
//
//   using comparable_range < RANGE_TYPE >::skip;
//
//   constexpr RANGE_ITERATOR skip(const ITEM & item) noexcept
//   {
//
//      return skip(item, ::equals_const_reference < ITEM >);
//
//   }
//
//   using comparable_range < RANGE_TYPE >::_rear_find_item;
//
//     constexpr RANGE_ITERATOR _rear_find_item(ITEM item) noexcept
//     {
//
//        return _rear_find_item(item, ::equals_const_reference < ITEM >);
//
//     }
//
//
//     using comparable_range < RANGE_TYPE >::rear_find_item;
//
//   constexpr RANGE_ITERATOR rear_find_item(ITEM item) noexcept
//   {
//
//      return rear_find_item(item, ::equals_const_reference < ITEM >);
//
//   }
//
//   using comparable_range < RANGE_TYPE >::_rear_scan;
//
//   constexpr RANGE_ITERATOR _rear_scan(CONST_RAW_RANGE range) noexcept
//   {
//
//      return _rear_scan(range, ::equals_const_reference < ITEM >);
//
//   }
//
//   using comparable_range < RANGE_TYPE >::rear_scan;
//
//   constexpr RANGE_ITERATOR rear_scan(CONST_RAW_RANGE range) noexcept
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