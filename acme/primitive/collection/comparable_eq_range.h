// From comparable_range by camilo on 2022-12-07 22:49 <3ThomasBorregaardSorensen!!
#pragma once



//template < typename RANGE_TYPE >
//class comparable_eq_range :
//   public RANGE_TYPE
//{
//public:
//
//   
//   using BASE_RANGE = RANGE_TYPE;
//
//   using THIS_RANGE = ::comparable_eq_range < BASE_RANGE >;
//
//   
//   using this_iterator = typename BASE_RANGE::this_iterator;
//   using iterator = typename BASE_RANGE::iterator;
//   using const_iterator = typename BASE_RANGE::const_iterator;
//
//
//   using THIS_RAW_RANGE = typename BASE_RANGE::THIS_RAW_RANGE;
//   using RAW_RANGE = typename BASE_RANGE::RAW_RANGE;
//   using CONST_RAW_RANGE = typename BASE_RANGE::CONST_RAW_RANGE;
//
//
//   using ITEM_POINTER = typename get_type_item_pointer < this_iterator >::type;
//
//   using ITEM = dereference < ITEM_POINTER >;
//
//
//   //using BASE_RANGE::BASE_RANGE;
//
//
//   comparable_eq_range(enum_no_initialize) : BASE_RANGE(e_no_initialize) {}
//   comparable_eq_range(nullptr_t) : BASE_RANGE(nullptr) {}
//   comparable_eq_range() {}
//   template<typed_range<iterator> RANGE>
//   comparable_eq_range(const RANGE &range) : BASE_RANGE(range) {}
//   template<typed_range<const_iterator> RANGE>
//   comparable_eq_range(const RANGE &range) : BASE_RANGE(range) {}
//   template < primitive_integral INTEGRAL >
//   comparable_eq_range(const_iterator begin, INTEGRAL count) : BASE_RANGE(begin, count) {}
//   comparable_eq_range(const_iterator begin, const_iterator end) : BASE_RANGE(begin, end) {}
//   comparable_eq_range(const_iterator begin) : BASE_RANGE(begin, span_zero_item(begin)) {}
//
//
//   //template < primitive_range RANGE >
//   //comparable_eq_range & operator = (const RANGE & range) { BASE_RANGE::operator=(range); return *this; }
//   comparable_eq_range & operator = (const comparable_eq_range & range) { BASE_RANGE::operator=(range); return *this; }
//   comparable_eq_range & operator = (comparable_eq_range && range) { BASE_RANGE::operator=(::move(range)); return *this; }
//
//   using BASE_RANGE::_equals;
//
//   constexpr bool _equals(const CONST_RAW_RANGE & range) const
//   {
//
//      return this->_equals(range, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::equals;
//
//   constexpr bool equals(const CONST_RAW_RANGE & range) const
//   {
//
//      return this->equals(range, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::_equals_start;
//
//   constexpr bool _equals_start(const CONST_RAW_RANGE & range, memsize start) const
//   {
//
//      return this->_equals_start(range, start, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::equals_start;
//
//   constexpr bool equals_start(const CONST_RAW_RANGE & range, memsize start) const
//   {
//
//      return this->equals_start(range, start, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::_equals_start_count;
//
//   constexpr bool _equals_start_count(const CONST_RAW_RANGE & range, memsize start, memsize count) const
//   {
//
//      return this->_equals_start_count(range, start, count, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::equals_start_count;
//
//   constexpr bool equals_start_count(const CONST_RAW_RANGE & range, memsize start, memsize count) const
//   {
//
//      return this->equals_start_count(range, start, count, ::comparison::comparison < ITEM >());
//
//   }
//
//
//
//
//   using BASE_RANGE::_find;
//
//   constexpr const_iterator _find(const CONST_RAW_RANGE & range) const
//   {
//
//      return this->_find(range, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::find;
//
//   constexpr const_iterator find(const CONST_RAW_RANGE & range) const
//   {
//
//      return this->find(range, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::_find_start;
//
//   constexpr const_iterator _find_start(const CONST_RAW_RANGE & range, memsize start) const
//   {
//
//      return this->_find_start(range, start, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::find_start;
//
//   constexpr const_iterator find_start(const CONST_RAW_RANGE & range, memsize start) const
//   {
//
//      return this->find_start(range, start, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::_find_start_count;
//
//   constexpr const_iterator _find_start_count(const CONST_RAW_RANGE & range, memsize start, memsize count) const
//   {
//
//      return this->_find_start_count(range, start, count, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::find_start_count;
//
//   constexpr const_iterator find_start_count(const CONST_RAW_RANGE & range, memsize start, memsize count) const
//   {
//
//      return this->find_start_count(range, start, count, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::_rear_find;
//
//   constexpr const_iterator _rear_find(const CONST_RAW_RANGE & range) const
//   {
//
//      return this->_rear_find(range, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::rear_find;
//
//   constexpr const_iterator rear_find(const CONST_RAW_RANGE & range) const
//   {
//
//      return this->rear_find(range, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::_rear_find_start;
//
//   constexpr const_iterator _rear_find_start(const CONST_RAW_RANGE & range, memsize start) const
//   {
//
//      return this->_rear_find_start(range, start, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::rear_find_start;
//
//   constexpr const_iterator rear_find_start(const CONST_RAW_RANGE & range, memsize start) const
//   {
//
//      return this->rear_find_start(range, start, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::_rear_find_start_count;
//
//   constexpr const_iterator _rear_find_start_count(const CONST_RAW_RANGE & range, memsize start, memsize count) const
//   {
//
//      return this->_rear_find_start_count(range, start, count, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::rear_find_start_count;
//
//   constexpr const_iterator rear_find_start_count(const CONST_RAW_RANGE & range, memsize start, memsize count) const
//   {
//
//      return this->rear_find_start_count(range, start, count, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::_scan;
//
//   constexpr const_iterator _scan(const CONST_RAW_RANGE & range) const
//   {
//
//      return this->_scan(range, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::scan;
//
//   constexpr const_iterator scan(const CONST_RAW_RANGE & range) const
//   {
//
//      return this->scan(range, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::_scan_start;
//
//   constexpr const_iterator _scan_start(const CONST_RAW_RANGE & range, memsize start) const
//   {
//
//      return this->_scan_start(range, start, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::scan_start;
//
//   constexpr const_iterator scan_start(const CONST_RAW_RANGE & range, memsize start) const
//   {
//
//      return this->scan_start(range, start, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::_scan_start_count;
//
//   constexpr const_iterator _scan_start_count(const CONST_RAW_RANGE & range, memsize start, memsize count) const
//   {
//
//      return this->_scan_start_count(range, start, count, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::scan_start_count;
//
//   constexpr const_iterator scan_start_count(const CONST_RAW_RANGE & range, memsize start, memsize count) const
//   {
//
//      return this->scan_start_count(range, start, count, ::comparison::comparison < ITEM >());
//
//   }
//
//
//
//   using BASE_RANGE::_span;
//
//   constexpr const_iterator _span(const CONST_RAW_RANGE & range) const
//   {
//
//      return this->_span(range, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::span;
//
//   constexpr const_iterator span(const CONST_RAW_RANGE & range) const
//   {
//
//      return this->span(range, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::_span_start;
//
//   constexpr const_iterator _span_start(const CONST_RAW_RANGE & range, memsize start) const
//   {
//
//      return this->_span_start(range, start, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::span_start;
//
//   constexpr const_iterator span_start(const CONST_RAW_RANGE & range, memsize start) const
//   {
//
//      return this->span_start(range, start, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::_span_start_count;
//
//   constexpr const_iterator _span_start_count(const CONST_RAW_RANGE & range, memsize start, memsize count) const
//   {
//
//      return this->_span_start_count(range, start, count, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::span_start_count;
//
//   constexpr const_iterator span_start_count(const CONST_RAW_RANGE & range, memsize start, memsize count) const
//   {
//
//      return this->span_start_count(range, start, count, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::_rear_span;
//
//   constexpr const_iterator _rear_span(const CONST_RAW_RANGE & range) const noexcept
//   {
//
//      return this->_rear_span(range, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::rear_span;
//
//   constexpr const_iterator rear_span(const CONST_RAW_RANGE & range) const noexcept
//   {
//
//      return this->rear_span(range, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::rear_span_start;
//
//   constexpr const_iterator rear_span_start(const CONST_RAW_RANGE & range, memsize start) const
//   {
//
//      return this->rear_span_start(range, start, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::_rear_span_start_count;
//
//   constexpr const_iterator _rear_span_start_count(const CONST_RAW_RANGE & range, memsize start, memsize count) const
//   {
//
//      return this->_rear_span_start_count(range, start, count, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::rear_span_start_count;
//
//   constexpr const_iterator rear_span_start_count(const CONST_RAW_RANGE & range, memsize start, memsize count) const
//   {
//
//      return this->rear_span_start_count(range, start, count, ::comparison::comparison < ITEM >());
//
//   }
//
//   using BASE_RANGE::_skip;
//
//   constexpr const_iterator _skip(const ITEM & item) const
//   {
//
//      return this->_skip(item, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::skip;
//
//   constexpr const_iterator skip(const ITEM & item) const
//   {
//
//      return this->skip(item, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::_skip_start;
//
//   constexpr const_iterator _skip_start(const ITEM & item, memsize start) const
//   {
//
//      return this->_skip_start(item, start, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::skip_start;
//
//   constexpr const_iterator skip_start(const ITEM & item, memsize start) const
//   {
//
//      return this->skip_start(item, start, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::_skip_start_count;
//
//   constexpr const_iterator _skip_start_count(const ITEM & item, memsize start, memsize count) const
//   {
//
//      return this->_skip_start_count(item, start, count, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::skip_start_count;
//
//   constexpr const_iterator skip_start_count(const ITEM & item, memsize start, memsize count) const
//   {
//
//      return this->skip_start_count(item, start, count, ::comparison::comparison < ITEM >());
//
//   }
//
//
//
//
//   using BASE_RANGE::_rear_find_item;
//
//   constexpr const_iterator _rear_find_item(const ITEM & item) const
//   {
//
//      return this->_rear_find_item(item, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::rear_find_item;
//
//   constexpr const_iterator rear_find_item(const ITEM & item) const
//   {
//
//      return this->rear_find_item(item, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::_rear_find_item_start;
//
//   constexpr const_iterator _rear_find_item_start(const ITEM & item, memsize start) const
//   {
//
//      return this->_rear_find_item_start(item, start, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::rear_find_item_start;
//
//   constexpr const_iterator rear_find_item_start(const ITEM & item, memsize start) const
//   {
//
//      return this->rear_find_item_start(item, start, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::_rear_find_item_start_count;
//
//   constexpr const_iterator _rear_find_item_start_count(const ITEM & item, memsize start, memsize count) const
//   {
//
//      return this->_rear_find_item_start_count(item, start, count, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::rear_find_item_start_count;
//
//   constexpr const_iterator rear_find_item_start_count(const ITEM & item, memsize start, memsize count) const
//   {
//
//      return this->rear_find_item_start_count(item, start, count, ::comparison::comparison < ITEM >());
//
//   }
//
//
//
//   using BASE_RANGE::_rear_scan;
//
//   constexpr const_iterator _rear_scan(const CONST_RAW_RANGE & range) const noexcept
//   {
//
//      return this->_rear_scan(range, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::rear_scan;
//
//   constexpr const_iterator rear_scan(const CONST_RAW_RANGE & range) const noexcept
//   {
//
//      return this->rear_scan(range, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::rear_scan_start;
//
//   constexpr const_iterator rear_scan_start(const CONST_RAW_RANGE & range, memsize start) const
//   {
//
//      return this->rear_scan_start(range, start, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::_rear_scan_start_count;
//
//   constexpr const_iterator _rear_scan_start_count(const CONST_RAW_RANGE & range, memsize start, memsize count) const
//   {
//
//      return this->_rear_scan_start_count(range, start, count, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::rear_scan_start_count;
//
//   constexpr const_iterator rear_scan_start_count(const CONST_RAW_RANGE & range, memsize start, memsize count) const
//   {
//
//      return this->rear_scan_start_count(range, start, count, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::_begins;
//
//   constexpr bool _begins(const CONST_RAW_RANGE & range) const
//   {
//
//      return this->_begins(range, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::begins;
//
//   constexpr bool begins(const CONST_RAW_RANGE & range) const
//   {
//
//      return this->begins(range, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::_begins_start;
//
//   constexpr bool _begins_start(const CONST_RAW_RANGE & range, memsize start) const
//   {
//
//      return this->_begins_start(range, start, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::begins_start;
//
//   constexpr bool begins_start(const CONST_RAW_RANGE & range, memsize start) const
//   {
//
//      return this->begins_start(range, start, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::_begins_start_count;
//
//   constexpr bool _begins_start_count(const CONST_RAW_RANGE & range, memsize start, memsize count) const
//   {
//
//      return this->_begins_start_count(range, start, count, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::begins_start_count;
//
//   constexpr bool begins_start_count(const CONST_RAW_RANGE & range, memsize start, memsize count) const
//   {
//
//      return this->begins_start_count(range, start, count, ::comparison::comparison < ITEM >());
//
//   }
//
//
//
//   using BASE_RANGE::_ends;
//
//   constexpr bool _ends(const CONST_RAW_RANGE & range) const
//   {
//
//      return this->_ends(range, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::ends;
//
//   constexpr bool ends(const CONST_RAW_RANGE & range) const
//   {
//
//      return this->ends(range, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::_ends_start;
//
//   constexpr bool _ends_start(const CONST_RAW_RANGE & range, memsize start) const
//   {
//
//      return this->_ends_start(range, start, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::ends_start;
//
//   constexpr bool ends_start(const CONST_RAW_RANGE & range, memsize start) const
//   {
//
//      return this->ends_start(range, start, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::_ends_start_count;
//
//   constexpr bool _ends_start_count(const CONST_RAW_RANGE & range, memsize start, memsize count) const
//   {
//
//      return this->_ends_start_count(range, start, count, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using BASE_RANGE::ends_start_count;
//
//   constexpr bool ends_start_count(const CONST_RAW_RANGE & range, memsize start, memsize count) const
//   {
//
//      return this->ends_start_count(range, start, count, ::comparison::comparison < ITEM >());
//
//   }
//
//
//};
//

//template < typename this_iterator >
//using range = comparable_range < range_base < this_iterator > >;

//
//template < typename BASE_RANGE >
//class comparable_range :
//   public comparable_range < BASE_RANGE >
//{
//public:
//
//   using this_iterator = BASE_RANGE::ITERATOR_TYPE;
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
//   using comparable_range < BASE_RANGE >::comparable_range;
//
//
//   comparable_range(const ITEM * pitem) : range(pitem, span_zero_item(data)), m_bDeclaredNullTerminated(true) {}
//   comparable_range(this_iterator data) : comparable_range((const ITEM *)data) {}
//
//
//   using comparable_range < BASE_RANGE >::_equals;
//
//   constexpr bool _equals(const CONST_RAW_RANGE & range) const
//   {
//
//      return _equals(range, ::comparison::comparison < ITEM >());
//
//   }
//
//   using comparable_range < BASE_RANGE >::equals;
//
//   constexpr bool equals(const CONST_RAW_RANGE & range) const
//   {
//
//      return range<const ITEM>(*this).compare(range, equals <const ITEM>);
//
//   }
//
//
//   using comparable_range < BASE_RANGE >::_order;
//
//   constexpr ::std::strong_ordering _order(const CONST_RAW_RANGE & range) const
//   {
//
//      return _order(range, ::compare_const_reference < ITEM >);
//
//   }
//
//   using comparable_range < BASE_RANGE >::compare;
//
//   constexpr ::std::strong_ordering compare(const CONST_RAW_RANGE & range) const
//   {
//
//      return range<const ITEM>(*this).compare(range, compare_const_reference <const ITEM>);
//
//   }
//
//
//   constexpr ::std::strong_ordering operator<=>(const CONST_RAW_RANGE & range) const
//   {
//
//      return compare(range, ::compare_const_reference < ITEM >);
//
//   }
//
//
//   using comparable_range < BASE_RANGE >::find;
//
//
//   this_iterator find(const CONST_RAW_RANGE & range, strsize iStart = 0, strsize nCount = -1, this_iterator * ppszTail = nullptr) const RELEASENOTHROW
//   {
//
//      return find(range, iStart, nCount, ppszTail, ::comparison::comparison < ITEM >());
//
//   }
//
//
//   using comparable_range < BASE_RANGE >::_scan;
//
//   constexpr this_iterator _scan(const CONST_RAW_RANGE & range) noexcept
//   {
//
//      return _scan(range, ::comparison::comparison < ITEM >());
//
//   }
//
//   using comparable_range < BASE_RANGE >::scan;
//
//     constexpr this_iterator scan(const CONST_RAW_RANGE & range) noexcept
//     {
//
//        return scan(range, ::comparison::comparison < ITEM >());
//
//     }
//
//     using comparable_range < BASE_RANGE >::_span;
//
//   constexpr this_iterator _span(const CONST_RAW_RANGE & range) noexcept
//   {
//
//      return _span(range, ::comparison::comparison < ITEM >());
//
//   }
//
//   using comparable_range < BASE_RANGE >::span;
//
//   constexpr this_iterator span(const CONST_RAW_RANGE & range) noexcept
//   {
//
//      return span(range, ::comparison::comparison < ITEM >());
//
//   }
//
//   using comparable_range < BASE_RANGE >::_skip;
//
//   constexpr this_iterator _skip(const ITEM & item) noexcept
//   {
//
//      return _skip(item, ::comparison::comparison < ITEM >());
//
//   }
//
//   using comparable_range < BASE_RANGE >::skip;
//
//   constexpr this_iterator skip(const ITEM & item) noexcept
//   {
//
//      return skip(item, ::comparison::comparison < ITEM >());
//
//   }
//
//   using comparable_range < BASE_RANGE >::_rear_find_item;
//
//     constexpr this_iterator _rear_find_item(ITEM item) noexcept
//     {
//
//        return _rear_find_item(item, ::comparison::comparison < ITEM >());
//
//     }
//
//
//     using comparable_range < BASE_RANGE >::rear_find_item;
//
//   constexpr this_iterator rear_find_item(ITEM item) noexcept
//   {
//
//      return rear_find_item(item, ::comparison::comparison < ITEM >());
//
//   }
//
//   using comparable_range < BASE_RANGE >::_rear_scan;
//
//   constexpr this_iterator _rear_scan(const CONST_RAW_RANGE & range) noexcept
//   {
//
//      return _rear_scan(range, ::comparison::comparison < ITEM >());
//
//   }
//
//   using comparable_range < BASE_RANGE >::rear_scan;
//
//   constexpr this_iterator rear_scan(const CONST_RAW_RANGE & range) noexcept
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

