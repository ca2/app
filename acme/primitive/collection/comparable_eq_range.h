// From comparable_range by camilo on 2022-12-07 22:49 <3ThomasBorregaardSorensen!!
#pragma once



template < typename RANGE_TYPE >
class comparable_eq_range :
   public RANGE_TYPE
{
public:

   
   using RANGE = comparable_eq_range < RANGE_TYPE >;


   using RANGE_ITERATOR = RANGE_TYPE::RANGE_ITERATOR;
   using iterator = RANGE_TYPE::iterator;
   using const_iterator = RANGE_TYPE::const_iterator;

   
   using RAW_RANGE = ::range < RANGE_ITERATOR >;
   using CONST_RAW_RANGE = RANGE_TYPE::CONST_RAW_RANGE;


   using ITEM_POINTER = get_type_item_pointer < RANGE_ITERATOR >::type;

   using ITEM = dereference < ITEM_POINTER >;


   using RANGE_TYPE::RANGE_TYPE;


   explicit comparable_eq_range(enum_no_initialize) : RANGE_TYPE(e_no_initialize) {}
   explicit comparable_eq_range(nullptr_t) : RANGE_TYPE(nullptr) {}
   explicit comparable_eq_range() {}
   comparable_eq_range(const comparable_eq_range & range) : RANGE_TYPE(range) {}
   comparable_eq_range(comparable_eq_range && range) : RANGE_TYPE(::move(range)) { }
   comparable_eq_range(::range < const_iterator > constrange) : RANGE_TYPE(constrange) {}
   template < primitive_integral INTEGRAL >
   comparable_eq_range(const_iterator begin, INTEGRAL count, bool bNullTerminated = false) : RANGE_TYPE(begin, count, bNullTerminated) {}
   comparable_eq_range(const_iterator begin, const_iterator end, bool bNullTerminated = false) : RANGE_TYPE(begin, end, bNullTerminated) {}
   comparable_eq_range(const_iterator begin) : RANGE_TYPE(begin, span_zero_item(begin), true) {}


   comparable_eq_range & operator = (const comparable_eq_range & comparable_eq_range) { RANGE_TYPE::operator=(comparable_eq_range); return *this; }
   comparable_eq_range & operator = (comparable_eq_range && comparable_eq_range) { RANGE_TYPE::operator=(::move(comparable_eq_range)); return *this; }


   using RANGE_TYPE::_equals;

   constexpr bool _equals(RANGE range) const
   {

      return this->_equals(range, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::equals;

   constexpr bool equals(RANGE range) const
   {

      return this->equals(range, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::_equals_start;

   constexpr bool _equals_start(RANGE range, memsize start) const
   {

      return this->_equals_start(range, start, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::equals_start;

   constexpr bool equals_start(RANGE range, memsize start) const
   {

      return this->equals_start(range, start, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::_equals_start_count;

   constexpr bool _equals_start_count(RANGE range, memsize start, memsize count) const
   {

      return this->_equals_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::equals_start_count;

   constexpr bool equals_start_count(RANGE range, memsize start, memsize count) const
   {

      return this->equals_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }




   using RANGE_TYPE::_find;

   constexpr const_iterator _find(RANGE range) const
   {

      return this->_find(range, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::find;

   constexpr const_iterator find(RANGE range) const
   {

      return this->find(range, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::_find_start;

   constexpr const_iterator _find_start(RANGE range, memsize start) const
   {

      return this->_find_start(range, start, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::find_start;

   constexpr const_iterator find_start(RANGE range, memsize start) const
   {

      return this->find_start(range, start, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::_find_start_count;

   constexpr const_iterator _find_start_count(RANGE range, memsize start, memsize count) const
   {

      return this->_find_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::find_start_count;

   constexpr const_iterator find_start_count(RANGE range, memsize start, memsize count) const
   {

      return this->find_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::_rear_find;

   constexpr const_iterator _rear_find(RANGE range) const
   {

      return this->_rear_find(range, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::rear_find;

   constexpr const_iterator rear_find(RANGE range) const
   {

      return this->rear_find(range, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::_rear_find_start;

   constexpr const_iterator _rear_find_start(RANGE range, memsize start) const
   {

      return this->_rear_find_start(range, start, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::rear_find_start;

   constexpr const_iterator rear_find_start(RANGE range, memsize start) const
   {

      return this->rear_find_start(range, start, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::_rear_find_start_count;

   constexpr const_iterator _rear_find_start_count(RANGE range, memsize start, memsize count) const
   {

      return this->_rear_find_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::rear_find_start_count;

   constexpr const_iterator rear_find_start_count(RANGE range, memsize start, memsize count) const
   {

      return this->rear_find_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::_scan;

   constexpr const_iterator _scan(RANGE range) const
   {

      return this->_scan(range, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::scan;

   constexpr const_iterator scan(RANGE range) const
   {

      return this->scan(range, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::_scan_start;

   constexpr const_iterator _scan_start(RANGE range, memsize start) const
   {

      return this->_scan_start(range, start, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::scan_start;

   constexpr const_iterator scan_start(RANGE range, memsize start) const
   {

      return this->scan_start(range, start, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::_scan_start_count;

   constexpr const_iterator _scan_start_count(RANGE range, memsize start, memsize count) const
   {

      return this->_scan_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::scan_start_count;

   constexpr const_iterator scan_start_count(RANGE range, memsize start, memsize count) const
   {

      return this->scan_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }



   using RANGE_TYPE::_span;

   constexpr const_iterator _span(RANGE range) const
   {

      return this->_span(range, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::span;

   constexpr const_iterator span(RANGE range) const
   {

      return this->span(range, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::_span_start;

   constexpr const_iterator _span_start(RANGE range, memsize start) const
   {

      return this->_span_start(range, start, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::span_start;

   constexpr const_iterator span_start(RANGE range, memsize start) const
   {

      return this->span_start(range, start, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::_span_start_count;

   constexpr const_iterator _span_start_count(RANGE range, memsize start, memsize count) const
   {

      return this->_span_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::span_start_count;

   constexpr const_iterator span_start_count(RANGE range, memsize start, memsize count) const
   {

      return this->span_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::_skip;

   constexpr const_iterator _skip(const ITEM & item) const
   {

      return this->_skip(item, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::skip;

   constexpr const_iterator skip(const ITEM & item) const
   {

      return this->skip(item, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::_skip_start;

   constexpr const_iterator _skip_start(const ITEM & item, memsize start) const
   {

      return this->_skip_start(item, start, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::skip_start;

   constexpr const_iterator skip_start(const ITEM & item, memsize start) const
   {

      return this->skip_start(item, start, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::_skip_start_count;

   constexpr const_iterator _skip_start_count(const ITEM & item, memsize start, memsize count) const
   {

      return this->_skip_start_count(item, start, count, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::skip_start_count;

   constexpr const_iterator skip_start_count(const ITEM & item, memsize start, memsize count) const
   {

      return this->skip_start_count(item, start, count, ::comparison::comparison < ITEM >());

   }




   using RANGE_TYPE::_rear_find_item;

   constexpr const_iterator _rear_find_item(const ITEM & item) const
   {

      return this->_rear_find_item(item, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::rear_find_item;

   constexpr const_iterator rear_find_item(const ITEM & item) const
   {

      return this->rear_find_item(item, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::_rear_find_item_start;

   constexpr const_iterator _rear_find_item_start(const ITEM & item, memsize start) const
   {

      return this->_rear_find_item_start(item, start, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::rear_find_item_start;

   constexpr const_iterator rear_find_item_start(const ITEM & item, memsize start) const
   {

      return this->rear_find_item_start(item, start, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::_rear_find_item_start_count;

   constexpr const_iterator _rear_find_item_start_count(const ITEM & item, memsize start, memsize count) const
   {

      return this->_rear_find_item_start_count(item, start, count, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::rear_find_item_start_count;

   constexpr const_iterator rear_find_item_start_count(const ITEM & item, memsize start, memsize count) const
   {

      return this->rear_find_item_start_count(item, start, count, ::comparison::comparison < ITEM >());

   }



   using RANGE_TYPE::_rear_scan;

   constexpr const_iterator _rear_scan(RANGE range) const noexcept
   {

      return this->_rear_scan(range, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::rear_scan;

   constexpr const_iterator rear_scan(RANGE range) const noexcept
   {

      return this->rear_scan(range, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::rear_scan_start;

   constexpr const_iterator rear_scan_start(RANGE range, memsize start) const
   {

      return this->rear_scan_start(range, start, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::_rear_scan_start_count;

   constexpr const_iterator _rear_scan_start_count(RANGE range, memsize start, memsize count) const
   {

      return this->_rear_scan_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::rear_scan_start_count;

   constexpr const_iterator rear_scan_start_count(RANGE range, memsize start, memsize count) const
   {

      return this->rear_scan_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::_begins;

   constexpr bool _begins(RANGE range) const
   {

      return this->_begins(range, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::begins;

   constexpr bool begins(RANGE range) const
   {

      return this->begins(range, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::_begins_start;

   constexpr bool _begins_start(RANGE range, memsize start) const
   {

      return this->_begins_start(range, start, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::begins_start;

   constexpr bool begins_start(RANGE range, memsize start) const
   {

      return this->begins_start(range, start, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::_begins_start_count;

   constexpr bool _begins_start_count(RANGE range, memsize start, memsize count) const
   {

      return this->_begins_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::begins_start_count;

   constexpr bool begins_start_count(RANGE range, memsize start, memsize count) const
   {

      return this->begins_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }



   using RANGE_TYPE::_ends;

   constexpr bool _ends(RANGE range) const
   {

      return this->_ends(range, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::ends;

   constexpr bool ends(RANGE range) const
   {

      return this->ends(range, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::_ends_start;

   constexpr bool _ends_start(RANGE range, memsize start) const
   {

      return this->_ends_start(range, start, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::ends_start;

   constexpr bool ends_start(RANGE range, memsize start) const
   {

      return this->ends_start(range, start, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::_ends_start_count;

   constexpr bool _ends_start_count(RANGE range, memsize start, memsize count) const
   {

      return this->_ends_start_count(range, start, count, ::comparison::comparison < ITEM >());

   }


   using RANGE_TYPE::ends_start_count;

   constexpr bool ends_start_count(RANGE range, memsize start, memsize count) const
   {

      return this->ends_start_count(range, start, count, ::comparison::comparison < ITEM >());

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
//      return _equals(range, ::comparison::comparison < ITEM >());
//
//   }
//
//   using comparable_range < RANGE_TYPE >::equals;
//
//   constexpr bool equals(CONST_RAW_RANGE range) const
//   {
//
//      return range<const ITEM>(*this).compare(range, equals <const ITEM>);
//
//   }
//
//
//   using comparable_range < RANGE_TYPE >::_order;
//
//   constexpr ::std::strong_ordering _order(CONST_RAW_RANGE range) const
//   {
//
//      return _order(range, ::compare_const_reference < ITEM >);
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
//      return compare(range, ::compare_const_reference < ITEM >);
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
//      return find(range, iStart, nCount, ppszTail, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using comparable_range < RANGE_TYPE >::_scan;
//
//   constexpr RANGE_ITERATOR _scan(CONST_RAW_RANGE range) noexcept
//   {
//
//      return _scan(range, ::comparison::comparison < ITEM >());
//
//   }
//
//   using comparable_range < RANGE_TYPE >::scan;
//
//     constexpr RANGE_ITERATOR scan(CONST_RAW_RANGE range) noexcept
//     {
//
//        return scan(range, ::comparison::comparison < ITEM >());
//
//     }
//
//     using comparable_range < RANGE_TYPE >::_span;
//
//   constexpr RANGE_ITERATOR _span(CONST_RAW_RANGE range) noexcept
//   {
//
//      return _span(range, ::comparison::comparison < ITEM >());
//
//   }
//
//   using comparable_range < RANGE_TYPE >::span;
//
//   constexpr RANGE_ITERATOR span(CONST_RAW_RANGE range) noexcept
//   {
//
//      return span(range, ::comparison::comparison < ITEM >());
//
//   }
//
//   using comparable_range < RANGE_TYPE >::_skip;
//
//   constexpr RANGE_ITERATOR _skip(const ITEM & item) noexcept
//   {
//
//      return _skip(item, ::comparison::comparison < ITEM >());
//
//   }
//
//   using comparable_range < RANGE_TYPE >::skip;
//
//   constexpr RANGE_ITERATOR skip(const ITEM & item) noexcept
//   {
//
//      return skip(item, ::comparison::comparison < ITEM >());
//
//   }
//
//   using comparable_range < RANGE_TYPE >::_rear_find_item;
//
//     constexpr RANGE_ITERATOR _rear_find_item(ITEM item) noexcept
//     {
//
//        return _rear_find_item(item, ::comparison::comparison < ITEM >());
//
//     }
//
//
//     using comparable_range < RANGE_TYPE >::rear_find_item;
//
//   constexpr RANGE_ITERATOR rear_find_item(ITEM item) noexcept
//   {
//
//      return rear_find_item(item, ::comparison::comparison < ITEM >());
//
//   }
//
//   using comparable_range < RANGE_TYPE >::_rear_scan;
//
//   constexpr RANGE_ITERATOR _rear_scan(CONST_RAW_RANGE range) noexcept
//   {
//
//      return _rear_scan(range, ::comparison::comparison < ITEM >());
//
//   }
//
//   using comparable_range < RANGE_TYPE >::rear_scan;
//
//   constexpr RANGE_ITERATOR rear_scan(CONST_RAW_RANGE range) noexcept
//   {
//
//      return rear_scan(range, ::comparison::comparison < ITEM >());
//
//   }
//
//};
//
//
//


//template < typename ITEM >
//inline bool _range_begins(::range < const ITEM * > range, ::range < const ITEM * > rangePrefix)
//{
//
//   return range._begins(rangePrefix);
//
//}
//template < typename ITEM >
//inline bool range_begins(::range < const ITEM * > range, ::range < const ITEM * > rangePrefix)
//{
//
//   return range.begins(rangePrefix);
//
//}
//template < typename ITEM >
//inline bool _range_ends(::range < const ITEM * > range, ::range < const ITEM * > rangeSuffix)
//{
//
//   return range._ends(rangeSuffix);
//
//}
//template < typename ITEM, ::comparison::equality < ITEM > EQUALITY >
//inline bool range_ends(::range < const ITEM * > range, ::range < const ITEM * > rangeSuffix, EQUALITY equality)
//{
//
//   return range.ends(rangeSuffix);
//
//}

