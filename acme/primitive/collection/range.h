// Refactored around 2022-09-12 by camilo <3ThomasBorregaardSorensen!!
#pragma once


template < typename ITERATOR_TYPE >
struct get_iterator_item
{

   using ITEM = typename ITERATOR_TYPE::ITEM;

};


template < typename ITEM_TYPE >
struct get_iterator_item< ITEM_TYPE * >
{

   using ITEM = ITEM_TYPE;

};


//template < typename ITEM_TYPE >
//struct get_type_item_pointer< const ITEM_TYPE * >
//{
//
//   using ITEM = ITEM_TYPE;
//
//};
//

template < typename TYPE >
struct get_type_item_pointer
{

   using type = typename TYPE::ITEM_POINTER;

};


template < typename TYPE >
struct get_type_item_pointer< TYPE * >
{

   using type = non_const < TYPE > *;

};


template < typename TYPE >
struct get_type_item_pointer< const TYPE * >
{

   using type = TYPE *;

};



template < typename iterator >
struct get_iterator
{

   using type = typename iterator::iterator;

};


template < typename TYPE >
struct get_iterator< TYPE * >
{

   using type = non_const < TYPE > *;

};


template < typename iterator >
struct get_const_iterator
{

   using type = iterator::const_iterator;

};


template < typename TYPE >
struct get_const_iterator< TYPE * >
{

   using type = const non_const < TYPE > *;

};



template < typename ITERATOR_TYPE >
class range
{
public:


   using RANGE_ITERATOR = ITERATOR_TYPE;
   using iterator = get_iterator < ITERATOR_TYPE >::type;
   using const_iterator = get_const_iterator < iterator >::type;


   using RANGE = ::range < iterator >;
   using CONST_RANGE = ::range < const_iterator >;


   using RAW_RANGE = ::range < iterator >;
   using CONST_RAW_RANGE = ::range < const_iterator >;


   using ITEM_POINTER = get_type_item_pointer<iterator>::type;

   using THIS_ITEM = get_iterator_item < ITERATOR_TYPE >::ITEM;
   using ITEM = non_const < THIS_ITEM >;
   using CONST_ITEM = add_const < THIS_ITEM >;

   
   RANGE_ITERATOR       m_begin;
   RANGE_ITERATOR       m_end;
   bool                 m_bNullTerminated;


   range(enum_no_initialize) {}
   range() : range(nullptr, nullptr, false) {}
   range(nullptr_t) : range() {}
   range(const RANGE & range) : m_begin((iterator)range.begin()), m_end((iterator)range.end()) {}
   range(const CONST_RANGE & range) : m_begin((iterator)range.begin()), m_end((iterator)range.end()) {}
   template < ::count count >
   range(const ITEM(&begin)[count], bool bNullTerminated = false) : range((const_iterator)begin, count, bNullTerminated) {}
   template < primitive_integral INTEGRAL >
   range(const_iterator begin, INTEGRAL count, bool bNullTerminated) : m_begin((RANGE_ITERATOR)begin), m_end((RANGE_ITERATOR)(begin + count)), m_bNullTerminated(bNullTerminated) {}
   range(const_iterator begin, const_iterator end, bool bNullTerminated = false) : m_begin((RANGE_ITERATOR)begin), m_end((RANGE_ITERATOR)end), m_bNullTerminated(bNullTerminated) {}
   template< ::comparison::equality < ITEM > EQUALITY >
   range(const_iterator begin, EQUALITY equality) : m_begin((RANGE_ITERATOR)begin), m_end((RANGE_ITERATOR)span_zero_item(begin, equality)), m_bNullTerminated(true) {}


   range & operator = (const range & range)
   { 
      
      m_begin = range.m_begin;
      m_end = range.m_end;
      m_bNullTerminated = range.m_bNullTerminated;
      
      return *this; 
   
   }


   range & operator = (range && range) 
   { 

      m_begin = range.m_begin;
      m_end = range.m_end;
      m_bNullTerminated = range.m_bNullTerminated;

      range.m_begin = nullptr;
      range.m_end = nullptr;

      return *this;

   }



   void add_initializer_list(const ::std::initializer_list < ITEM > & initializer_list)
   {

      // not implementable for ranges without allocation

   }


   constexpr bool is_null_terminated() const noexcept { return m_bNullTerminated; }


   constexpr auto offset_of(const_iterator p) const { return p - (const_iterator) this->begin(); }


   RANGE_ITERATOR & begin() { return m_begin; }
   RANGE_ITERATOR & end() { return m_end; }
   const RANGE_ITERATOR & begin() const { return m_begin; }
   const RANGE_ITERATOR & end() const { return m_end; }


   static consteval memsize item_size() { return sizeof(ITEM); }
   ::count size() const { return ::is_set(this->begin()) ? maximum(0, this->end() - this->begin()) : 0; }
   bool is_empty() const { return size() <= 0; }
   inline bool is_set() const { return !is_empty(); }


   inline bool operator !() const { return is_set(); }


   constexpr bool is_before_begin(const_iterator iterator) const
   {

      return ::iterator_is_before_begin(iterator, m_begin);

   }


   constexpr bool is_end(const_iterator iterator) const
   {

      return ::iterator_is_end(iterator, m_end);

   }

   constexpr bool iterator_ok(const_iterator iterator) const
   {

      return ::iterator_is_ok(iterator, m_begin, m_end);

   }

   //constexpr bool is_end() const
   //{

   //   return ::range_is_empty(m_begin, m_end);

   //}


   //constexpr bool is_ok(iterator iterator) const
   //{

   //   return ::range_is_ok(iterator, m_end);

   //}

   //constexpr bool is_ok() const
   //{

   //   return ::range_is_ok(m_begin, m_end);

   //}


   constexpr CONST_RANGE _start_range(memsize start) const
   {

      return { this->begin() + start, this->end() };

   }


   constexpr CONST_RANGE _start_count_range(memsize start, memsize count) const
   {

      return { this->begin() + start, ((count >= 0) ? ::clipped_add(this->begin(), start + count, this->begin(), this->end()) : ::clipped_add(this->end(), count, this->begin(), this->end()))};

   }

   
   static constexpr bool _initialize_equals(bool & b, CONST_RANGE range, CONST_RANGE rangeBlock)
   {

      if (range.size() != rangeBlock.size())
      {

         b = false;

         return false;

      }
      else if (range.is_empty())
      {

         b = true;

         return true;

      }

      return false;

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   static constexpr auto _static_equals(CONST_RANGE range, CONST_RANGE rangeBlock, EQUALITY equality)
   {

      while (range.begin() < range.end())
      {

         if (!equality.equals(*range.begin(), *rangeBlock.begin()))
         {

            return false;

         }

         range.begin()++;

         rangeBlock.begin()++;

      }

      return true;

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   static constexpr auto static_equals(CONST_RANGE range, CONST_RANGE rangeBlock, EQUALITY equality)
   {

      bool b;

      if (_initialize_equals(b, range, rangeBlock))
      {

         return b;

      }

      return _static_equals(range, rangeBlock, equality);

   }

   
   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr bool _equals(CONST_RANGE rangeBlock, EQUALITY equality) const
   {

      return _static_equals(*this, rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr bool equals(CONST_RANGE rangeBlock, EQUALITY equality) const
   {

      return static_equals(*this, rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr bool _equals_start(CONST_RANGE rangeBlock, memsize start, EQUALITY equality) const
   {

      return _static_equals(_start_range(start), rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr bool equals_start(CONST_RANGE rangeBlock, memsize start, EQUALITY equality) const
   {

      return static_equals(_start_range(start), rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr bool _equals_start_count(CONST_RANGE rangeBlock, memsize start, memsize count, EQUALITY equality) const
   {

      return _static_equals(_start_count_range(start, count), rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr bool equals_start_count(CONST_RANGE rangeBlock, memsize start, memsize count, EQUALITY equality) const
   {

      return static_equals(_start_count_range(start, count), rangeBlock, equality);

   }


   static constexpr bool _initialize_order(::std::strong_ordering & order, CONST_RANGE range, CONST_RANGE rangeBlock)
   {

      if (range.is_empty())
      {

         if (rangeBlock.is_empty())
         {

            order = ::std::strong_ordering::equal;

            return true;

         }
         else
         {

            order = ::std::strong_ordering::greater;

            return true;

         }

      }
      else if (rangeBlock.is_empty())
      {

         order = ::std::strong_ordering::less;

         return true;

      }

      return false;

   }

   template < ::comparison::ordering < ITEM > ORDERING >
   static constexpr auto _static_order(CONST_RANGE range, CONST_RANGE rangeBlock, ORDERING ordering)
   {

      do
      {

         auto order = ordering.order(*range.begin(), *rangeBlock.begin());

         if (order != 0)
         {

            return order;

         }

         range.begin()++;

         rangeBlock.begin()++;

      } while (!range.is_end(range.begin()) && !rangeBlock.is_end(rangeBlock.begin()));

      return range.size() <=> rangeBlock.size();

   }


   template < ::comparison::ordering < ITEM > ORDERING >
   static constexpr ::std::strong_ordering static_order(CONST_RANGE range, CONST_RANGE rangeBlock, ORDERING ordering)
   {

      std::strong_ordering order;

      if (_initialize_order(order, range, rangeBlock))
      {

         return order;

      }

      return _static_order(range, rangeBlock, ordering);

   }


   template < ::comparison::ordering < ITEM > ORDERING >
   constexpr ::std::strong_ordering _order(CONST_RANGE rangeBlock, ORDERING ordering) const
   {

      return _static_order(*this, rangeBlock, ordering);

   }


   template < ::comparison::ordering < ITEM > ORDERING >
   constexpr ::std::strong_ordering order(CONST_RANGE rangeBlock, ORDERING ordering) const
   {

      return static_order(*this, rangeBlock, ordering);

   }


   template < ::comparison::ordering < ITEM > ORDERING >
   constexpr ::std::strong_ordering _order_start(CONST_RANGE rangeBlock, memsize start, ORDERING ordering) const
   {

      return _static_order(_start_range(start), rangeBlock, ordering);

   }


   template < ::comparison::ordering < ITEM > ORDERING >
   constexpr ::std::strong_ordering order_start(CONST_RANGE rangeBlock, memsize start, ORDERING ordering) const
   {

      return static_order(_start_range(start), rangeBlock, ordering);

   }


   template < ::comparison::ordering < ITEM > ORDERING >
   constexpr ::std::strong_ordering _order_start_count(CONST_RANGE rangeBlock, memsize start, memsize count, ORDERING ordering) const
   {

      return _static_order(_start_count_range(start, count), rangeBlock, ordering);

   }


   template < ::comparison::ordering < ITEM > ORDERING >
   constexpr ::std::strong_ordering order_start_count(CONST_RANGE rangeBlock, memsize start, memsize count, ORDERING ordering) const
   {

      return static_order(_start_count_range(start, count), rangeBlock, ordering);

   }


   static bool _initialize_find(const_iterator & p, CONST_RANGE range, CONST_RANGE rangeBlock)
   {

      p = rangeBlock.begin();

      if (range.is_empty())
      {

         return true;

      }

      return false;

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   static const_iterator _static_find(CONST_RANGE range, CONST_RANGE rangeBlock, EQUALITY equality)
   {

      do
      {

         auto p = range.begin();

         auto pBlock = rangeBlock.begin();

         while(true)
         {

            if (!equality.equals(*p, *pBlock))
            {

               break;

            }

            p++;
            
            pBlock++;

            if (rangeBlock.is_end(pBlock))
            {

               return p;

            }
              
         }

         range.begin()++;

      } while (!range.is_end(range.begin()));

      return nullptr;

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   static const_iterator static_find(CONST_RANGE range, CONST_RANGE rangeBlock, EQUALITY equality)
   {

      const_iterator p;

      if (_initialize_find(p, range, rangeBlock))
      {

         return p;

      }

      return _static_find(range, rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator _find(CONST_RANGE rangeBlock, EQUALITY equality) const
   {

      return _static_find(*this, rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator find(CONST_RANGE rangeBlock, EQUALITY equality) const
   {

      return static_find(*this, rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator _find_start(CONST_RANGE rangeBlock, memsize start, EQUALITY equality) const
   {

      return _static_find(_start_range(start), rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator find_start(CONST_RANGE rangeBlock, memsize start, EQUALITY equality) const
   {

      return static_find(_start_range(start), rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator _find_start_count(CONST_RANGE rangeBlock, memsize start, memsize count, EQUALITY equality) const
   {

      return _static_find(_start_count_range(start, count), rangeBlock, equality);

   }


   static bool _initialize_rear_find(const_iterator & p, CONST_RANGE range, CONST_RANGE rangeBlock)
   {

      p = rangeBlock.end() - 1;

      if (range.is_empty())
      {

         return true;

      }

      return false;

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   static const_iterator _static_rear_find(CONST_RANGE range, CONST_RANGE rangeBlock, EQUALITY equality)
   {

      do
      {

         auto p = range.end();

         auto pBlock = rangeBlock.end()-1;

         while (true)
         {

            if (!equality.equals(*p, *pBlock))
            {

               break;

            }

            p--;

            pBlock--;

            if (rangeBlock.is_before_begin(pBlock))
            {

               return p - rangeBlock.size() + 1;

            }

         }

         range.begin()--;

      } while (!range.is_before_begin(range.end()));

      return nullptr;

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   static const_iterator static_rear_find(CONST_RANGE range, CONST_RANGE rangeBlock, EQUALITY equality)
   {

      const_iterator p;

      if (_initialize_rear_find(p, range, rangeBlock))
      {

         return p;

      }

      return _static_rear_find(range, rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator _rear_find(CONST_RANGE rangeBlock, EQUALITY equality) const
   {

      return _static_rear_find(*this, rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator rear_find(CONST_RANGE rangeBlock, EQUALITY equality) const
   {

      return static_rear_find(*this, rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator _rear_find_start(CONST_RANGE rangeBlock, memsize start, EQUALITY equality) const
   {

      return _static_rear_find(_start_range(start), rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator rear_find_start(CONST_RANGE rangeBlock, memsize start, EQUALITY equality) const
   {

      return static_rear_find(_start_range(start), rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator _rear_find_start_count(CONST_RANGE rangeBlock, memsize start, memsize count, EQUALITY equality) const
   {

      return _static_rear_find(_start_count_range(start, count), rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator rear_find_start_count(CONST_RANGE rangeBlock, memsize start, memsize count, EQUALITY equality) const
   {

      return static_rear_find(_start_count_range(start, count), rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator find_start_count(CONST_RANGE rangeBlock, memsize start, memsize count, EQUALITY equality) const
   {

      return static_find(_start_count_range(start, count), rangeBlock, equality);

   }


   static constexpr bool _initialize_scan(const_iterator & p, CONST_RANGE range, CONST_RANGE rangeBlock) noexcept
   {

      if (range.is_empty())
      {

         p = (const_iterator)range.begin();

         return true;

      }

      if (rangeBlock.is_empty())
      {

         p = (const_iterator)range.begin();

         return true;

      }

      return false;

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   static constexpr const_iterator _static_scan(CONST_RANGE range, CONST_RANGE rangeBlock, EQUALITY equality) noexcept
   {

      do
      {

         auto pBlockScan = range.begin();

         while (true)
         {

            if (equality.equals(*range.begin(), *pBlockScan))
            {

               // found a matching item...
               // continue scanning...

               break;

            }

            pBlockScan++;

            if (rangeBlock.is_end(pBlockScan))
            {

               // Iterated through all pBlock items 
               // and didn't find any that match *p

               // so p is the end of the scan for matching items...

               return range.begin();

            }

         };

         range.begin()++;

      } while (!range.is_end(range.begin()));

      // reached end of the scanning range...
      // each scanned item matched some item in range...
      // return address immediately after end of scanning...

      return range.begin();

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   static constexpr const_iterator static_scan(CONST_RANGE range, CONST_RANGE rangeBlock, EQUALITY equality) noexcept
   {

      const_iterator p;

      if (_initialize_scan(p, range, rangeBlock))
      {

         return p;

      }

      return _static_scan(range, rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator _scan(CONST_RANGE rangeBlock, EQUALITY equality) const
   {

      return _static_scan(*this, rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator scan(CONST_RANGE rangeBlock, EQUALITY equality) const
   {

      return static_scan(*this, rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator _scan_start(CONST_RANGE rangeBlock, memsize start, EQUALITY equality) const
   {

      return _static_scan(_start_range(start), rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator scan_start(CONST_RANGE rangeBlock, memsize start, EQUALITY equality) const
   {

      return static_scan(_start_range(start), rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator _scan_start_count(CONST_RANGE rangeBlock, memsize start, memsize count, EQUALITY equality) const
   {

      return _static_scan(_start_count_range(start, count), rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator scan_start_count(CONST_RANGE rangeBlock, memsize start, memsize count, EQUALITY equality) const
   {

      return static_scan(_start_count_range(start, count), rangeBlock, equality);

   }

   static constexpr bool _initialize_span(const_iterator & p, CONST_RANGE range, CONST_RANGE rangeBlock) noexcept
   {

      if (range.is_empty())
      {

         p = range.end();

         return true;

      }

      if (rangeBlock.is_empty())
      {

         p = range.end();

         return true;

      }

      return false;

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   static constexpr const_iterator _static_span(CONST_RANGE range, CONST_RANGE rangeBlock, EQUALITY equality) noexcept
   {

      do
      {

         auto pBlockScan = rangeBlock.begin();

         do
         {

            if (equality.equals(*range.begin(), *pBlockScan))
            {

               // found a matching item...
               // stop spanning and return address of the matching item 

               return range.begin();

            }

            pBlockScan++;

         } while (!rangeBlock.is_end(pBlockScan));

         // Didn't found matching item...
         // continue spanning...

         range.begin()++;

      } while (!range.is_end(range.begin()));

      // reached end of the spanning range...
      // and didn't find any matching items...
      // return address immediately after end of spanning range....

      return range.begin();

   }

   template < ::comparison::equality < ITEM > EQUALITY >
   static constexpr const_iterator static_span(CONST_RANGE range, CONST_RANGE rangeBlock, EQUALITY equality) noexcept
   {

      const_iterator p;

      if (_initialize_span(p, range, rangeBlock))
      {

         return p;

      }

      return _static_span(range, rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator _span(CONST_RANGE rangeBlock, EQUALITY equality) const
   {

      return _static_span(*this, rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator span(CONST_RANGE rangeBlock, EQUALITY equality) const
   {

      return static_span(*this, rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator _span_start(CONST_RANGE rangeBlock, memsize start, EQUALITY equality) const
   {

      return _static_span(_start_range(start), rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator span_start(CONST_RANGE rangeBlock, memsize start, EQUALITY equality) const
   {

      return static_span(_start_range(start), rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator _span_start_count(CONST_RANGE rangeBlock, memsize start, memsize count, EQUALITY equality) const
   {

      return _static_span(_start_count_range(start, count), rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator span_start_count(CONST_RANGE rangeBlock, memsize start, memsize count, EQUALITY equality) const
   {

      return static_span(_start_count_range(start, count), rangeBlock, equality);

   }


   static constexpr bool _initialize_skip(const_iterator & p, CONST_RANGE range) noexcept
   {

      if (range.is_empty())
      {

         p = range.end();

         return true;

      }

      return false;

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   static constexpr const_iterator _static_skip(CONST_RANGE range, const ITEM & item, EQUALITY equality) noexcept
   {

      do
      {

         if (!equality.equals(*range.begin(), item))
         {

            return range.begin();

         }

         range.begin()++;

      }while(!range.is_end(range.begin()));

      return range.begin();

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   static constexpr const_iterator static_skip(CONST_RANGE range, const ITEM & item, EQUALITY equality) noexcept
   {

      const_iterator p;

      if (_initialize_skip(p, range))
      {

         return p;

      }

      return _static_skip(range, item, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator _skip(const ITEM & item, EQUALITY equality) const
   {

      return _static_skip(*this, item, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator skip(const ITEM & item, EQUALITY equality) const
   {

      return static_skip(*this, item, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator _skip_start(const ITEM & item, memsize start, EQUALITY equality) const
   {

      return _static_skip(_start_range(start), item, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator skip_start(const ITEM & item, memsize start, EQUALITY equality) const
   {

      return static_skip(_start_range(start), item, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator _skip_start_count(const ITEM & item, memsize start, memsize count, EQUALITY equality) const
   {

      return _static_skip(_start_count_range(start, count), item, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator skip_start_count(const ITEM & item, memsize start, memsize count, EQUALITY equality) const
   {

      return static_skip(_start_count_range(start, count), item, equality);

   }


   static constexpr bool _initialize_find_item(const_iterator & p, CONST_RANGE range) noexcept
   {

      if (range.is_empty())
      {

         p = nullptr;

         return true;

      }

      return false;

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   static constexpr const_iterator _static_rear_find_item(CONST_RANGE range, const ITEM & item, EQUALITY equality) noexcept
   {

      do
      {

         if (equality.equals(*range.end(), item))
         {

            return range.end();

         }

         range.end()--;

      } while (!range.is_before_begin(range.end()));

      return nullptr;

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   static constexpr const_iterator static_rear_find_item(CONST_RANGE range, const ITEM & item, EQUALITY equality) noexcept
   {

      const_iterator p;

      if (_initialize_find_item(p, range))
      {

         return p;

      }

      range.end()--;

      return _static_rear_find_item(range, item, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator _rear_find_item(const ITEM & item, EQUALITY equality) const
   {

      return _static_rear_find_item(*this, item, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator rear_find_item(const ITEM & item, EQUALITY equality) const
   {

      return static_rear_find_item(*this, item, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator _rear_find_item_start(const ITEM & item, memsize start, EQUALITY equality) const
   {

      return _static_rear_find_item(_start_range(start), item, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator rear_find_item_start(const ITEM & item, memsize start, EQUALITY equality) const
   {

      return static_rear_find_item(_start_range(start), item, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator _rear_find_item_start_count(const ITEM & item, memsize start, memsize count, EQUALITY equality) const
   {

      return _static_rear_find_item(_start_count_range(start, count), item, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator rear_find_item_start_count(const ITEM & item, memsize start, memsize count, EQUALITY equality) const
   {

      return static_rear_find_item(_start_count_range(start, count), item, equality);

   }


   static constexpr bool _initialize_rear_scan(const_iterator & p, CONST_RANGE range, CONST_RANGE rangeBlock) noexcept
   {

      if (range.is_empty())
      {

         p = range.end() - 1;

         return true;

      }

      if (range.is_empty())
      {

         p = range.end() - 1;

         return true;

      }

      return false;

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   static constexpr const_iterator _static_rear_scan(CONST_RANGE range, CONST_RANGE rangeBlock, EQUALITY equality)noexcept
   {

      do
      {

         auto pBlockScan = range.begin();

         while (true)
         {

            if (equality.equals(*range.end(), *pBlockScan))
            {

               // found a matching item...
               // continue scanning...

               break;

            }

            pBlockScan++;

            if (rangeBlock.is_end(pBlockScan))
            {

               // Iterated through all pBlock items 
               // and didn't find any that match *p

               // so p is the end of the scan for matching items...

               return range.begin();

            }

         };

         range.end()--;

      } while (!range.is_before_begin(range.end()));

      // reached end of the scanning range...
      // each scanned item matched some item in range...
      // return address immediately after end of scanning...

      return range.is_set() ? range.begin() : nullptr;

   }
  

   template < ::comparison::equality < ITEM > EQUALITY >
   static constexpr const_iterator static_rear_scan(CONST_RANGE range, CONST_RANGE rangeBlock, EQUALITY equality) noexcept
   {

      const_iterator p;

      if (_initialize_rear_scan(p, range, rangeBlock))
      {

         return p;

      }

      range.end()--;

      return _static_rear_scan(range, rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator _rear_scan(CONST_RANGE rangeBlock, EQUALITY equality) const
   {

      return _static_rear_scan(*this, rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator rear_scan(CONST_RANGE rangeBlock, EQUALITY equality) const
   {

      return static_rear_scan(*this, rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator _rear_scan_start(CONST_RANGE rangeBlock, memsize start, EQUALITY equality) const
   {

      return _static_rear_scan(_start_range(start), rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator rear_scan_start(CONST_RANGE rangeBlock, memsize start, EQUALITY equality) const
   {

      return static_rear_scan(_start_range(start), rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator _rear_scan_start_count(CONST_RANGE rangeBlock, memsize start, memsize count, EQUALITY equality) const
   {

      return _static_rear_scan(_start_count_range(start, count), rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr const_iterator rear_scan_start_count(CONST_RANGE rangeBlock, memsize start, memsize count, EQUALITY equality) const
   {

      return static_rear_scan(_start_count_range(start, count), rangeBlock, equality);

   }



   static constexpr bool _initialize_contains(bool & b, CONST_RANGE range, CONST_RANGE rangeBlock) noexcept
   {

      if (rangeBlock.is_empty())
      {

         b = true;

         return true;

      }

      if (range.is_empty())
      {

         b = false;

         return true;

      }

      return false;

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   static constexpr bool _static_begins(CONST_RANGE range, CONST_RANGE rangeBlock, EQUALITY equality) noexcept
   {

      do
      {

         if (!equality.equals(*range.begin(), *rangeBlock.begin()))
         {

            return false;

         }

         range.begin()++;

         rangeBlock.begin()++;

      } while (!range.is_end(range.begin()) && !rangeBlock.is_end(rangeBlock.begin()));

      return true;

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   static constexpr bool static_begins(CONST_RANGE range, CONST_RANGE rangeBlock, EQUALITY equality) noexcept
   {

      bool b;

      if (_initialize_contains(b, range, rangeBlock))
      {

         return b;

      }

      return _static_begins(range, rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr bool _begins(CONST_RANGE rangeBlock, EQUALITY equality) const
   {

      return _static_begins(*this, rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr bool begins(CONST_RANGE rangeBlock, EQUALITY equality) const
   {

      return static_begins(*this, rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr bool _begins_start(CONST_RANGE rangeBlock, memsize start, EQUALITY equality) const
   {

      return _static_begins(_start_range(start), rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr bool begins_start(CONST_RANGE rangeBlock, memsize start, EQUALITY equality) const
   {

      return static_begins(_start_range(start), rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr bool _begins_start_count(CONST_RANGE rangeBlock, memsize start, memsize count, EQUALITY equality) const
   {

      return _static_begins(_start_count_range(start, count), rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr bool begins_start_count(CONST_RANGE rangeBlock, memsize start, memsize count, EQUALITY equality) const
   {

      return static_begins(_start_count_range(start, count), rangeBlock, equality);

   }




   template < ::comparison::equality < ITEM > EQUALITY >
   static constexpr bool _static_ends(CONST_RANGE range, CONST_RANGE rangeBlock, EQUALITY equality) noexcept
   {

      do
      {

         if (!equality.equals(*range.end(), *rangeBlock.end()))
         {

            return false;

         }

         range.end()--;

         rangeBlock.end()--;

      } while (!range.is_before_begin(range.end()) && !rangeBlock.is_before_begin(rangeBlock.end()));

      return true;

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   static constexpr bool static_ends(CONST_RANGE range, CONST_RANGE rangeBlock, EQUALITY equality) noexcept
   {

      bool b;

      if (_initialize_contains(b, range, rangeBlock))
      {

         return b;

      }

      return _static_ends(range, rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr bool _ends(CONST_RANGE rangeBlock, EQUALITY equality) const
   {

      return _static_ends(*this, rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr bool ends(CONST_RANGE rangeBlock, EQUALITY equality) const
   {

      return static_ends(*this, rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr bool _ends_start(CONST_RANGE rangeBlock, memsize start, EQUALITY equality) const
   {

      return _static_ends(_start_range(start), rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr bool ends_start(CONST_RANGE rangeBlock, memsize start, EQUALITY equality) const
   {

      return static_ends(_start_range(start), rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr bool _ends_start_count(CONST_RANGE rangeBlock, memsize start, memsize count, EQUALITY equality) const
   {

      return _static_ends(_start_count_range(start, count), rangeBlock, equality);

   }


   template < ::comparison::equality < ITEM > EQUALITY >
   constexpr bool ends_start_count(CONST_RANGE rangeBlock, memsize start, memsize count, EQUALITY equality) const
   {

      return static_ends(_start_count_range(start, count), rangeBlock, equality);

   }



   //constexpr bool _equals_prefix(bool & b, CONST_RANGE range) const
   //{

   //   return BASE_ARRAY::_equals_prefix(b, range);

   //}


   //using BASE_ARRAY::_equals_prefix;

   //template < ::comparison::equality < ITEM > EQUALITY >
   //constexpr auto _equals(CONST_RANGE range, EQUALITY equality) const
   //{

   //   return BASE_ARRAY::_equals(range, equality);

   //}

   //constexpr bool _equals(CONST_RANGE range) const
   //{

   //   return this->_equals(range, ::equals_const_reference < ITEM >);

   //}


   //template < ::comparison::equality < ITEM > EQUALITY >
   //constexpr bool equals(CONST_RANGE range, EQUALITY equality) const
   //{

   //   return BASE_ARRAY::equals(range, equality);

   //}

   //constexpr bool _initialize_order(::std::strong_ordering & ordering, CONST_RANGE range) const
   //{

   //   return BASE_ARRAY::_initialize_order(range, equality);

   //}


   //template < typename COMPARE >
   //constexpr auto _order(CONST_RANGE range, COMPARE compare) const
   //{

   //   return BASE_ARRAY::_order(range, equality);

   //}

   //template < typename COMPARE >
   //constexpr ::std::strong_ordering compare(CONST_RANGE range, COMPARE compare) const
   //{

   //   return BASE_ARRAY::compare(range, compare);

   //}


   //constexpr ::std::strong_ordering operator<=>(CONST_RANGE range) const
   //{

   //   return compare(range, ::compare_const_reference < ITEM >);

   //}


   //static bool _find_prefix(const_iterator & p, RANGE range, RANGE rangeScope)
   //{

   //   return BASE_ARRAY::_equals(range, equality);

   //}


   //template < ::comparison::equality < ITEM > EQUALITY >
   //static RANGE_ITERATOR _find(RANGE search)
   //{

   //   return BASE_ARRAY::_find(search, equality);

   //}


   //template < ::comparison::equality < ITEM > EQUALITY >
   //const_iterator find(RANGE range, EQUALITY equality) const
   //{

   //   return BASE_ARRAY::find(range, equality);

   //}


   //constexpr bool _scan_prefix(RANGE_ITERATOR & p, CONST_RANGE range) const noexcept
   //{

   //   return BASE_ARRAY::_scan_prefix(range, equality);

   //}


   //template < ::comparison::equality < ITEM > EQUALITY >
   //constexpr RANGE_ITERATOR _scan(CONST_RANGE range, EQUALITY equality) noexcept
   //{

   //   return BASE_ARRAY::_scan(range, equality);

   //}


   //constexpr RANGE_ITERATOR _scan(CONST_RANGE range) noexcept
   //{

   //   return _scan(range, ::equals_const_reference < ITEM >);

   //}


   //template < ::comparison::equality < ITEM > EQUALITY >
   //constexpr RANGE_ITERATOR scan(CONST_RANGE range, EQUALITY equality) noexcept
   //{

   //   return BASE_ARRAY::scan(range, equality);

   //}


   //constexpr RANGE_ITERATOR scan(CONST_RANGE range) noexcept
   //{

   //   return scan(range, ::equals_const_reference < ITEM >);

   //}


   //constexpr bool _span_prefix(RANGE_ITERATOR & p, CONST_RANGE range) noexcept
   //{

   //   return BASE_ARRAY::_span_prefix(range, equality);

   //}


   //template < ::comparison::equality < ITEM > EQUALITY >
   //constexpr RANGE_ITERATOR _span(CONST_RANGE range, EQUALITY equality) noexcept
   //{

   //   return BASE_ARRAY::_span(range, equality);

   //}


   //constexpr RANGE_ITERATOR _span(CONST_RANGE range) noexcept
   //{

   //   return _span(range, ::equals_const_reference < ITEM >);

   //}


   //template < ::comparison::equality < ITEM > EQUALITY >
   //constexpr RANGE_ITERATOR span(CONST_RANGE range, EQUALITY equality) noexcept
   //{

   //   return BASE_ARRAY::span(range, equality);

   //}


   //constexpr RANGE_ITERATOR span(CONST_RANGE range) noexcept
   //{

   //   return span(range, ::equals_const_reference < ITEM >);

   //}


   //template < ::comparison::equality < ITEM > EQUALITY >
   //constexpr RANGE_ITERATOR _skip(const ITEM & item, EQUALITY equality) noexcept
   //{

   //   return BASE_ARRAY::_skip(range, equality);

   //}


   //constexpr RANGE_ITERATOR _skip(const ITEM & item) noexcept
   //{

   //   return _skip(item, ::equals_const_reference < ITEM >);

   //}


   //template < ::comparison::equality < ITEM > EQUALITY >
   //constexpr RANGE_ITERATOR skip(const ITEM & item, EQUALITY equality) noexcept
   //{

   //   return BASE_ARRAY::skip(item, equality);

   //}


   //constexpr RANGE_ITERATOR skip(const ITEM & item) noexcept
   //{

   //   return skip(item, ::equals_const_reference < ITEM >);

   //}


   //template < ::comparison::equality < ITEM > EQUALITY >
   //constexpr RANGE_ITERATOR _rear_find_item(ITEM item, EQUALITY equality) noexcept
   //{

   //   return BASE_ARRAY::_rear_find_item(item, equality);

   //}


   //constexpr RANGE_ITERATOR _rear_find_item(ITEM item) noexcept
   //{

   //   return _rear_find_item(item, ::equals_const_reference < ITEM >);

   //}


   //template < ::comparison::equality < ITEM > EQUALITY >
   //constexpr RANGE_ITERATOR rear_find_item(ITEM item, EQUALITY equality) noexcept
   //{

   //   return BASE_ARRAY::rear_find_item(item, equality);

   //}


   //constexpr RANGE_ITERATOR rear_find_item(ITEM item) noexcept
   //{

   //   return rear_find_item(item, ::equals_const_reference < ITEM >);

   //}


   //constexpr bool _rear_scan_prefix(RANGE_ITERATOR & p, CONST_RANGE range) noexcept
   //{

   //   return BASE_ARRAY::_rear_scan_prefix(p, range);

   //}


   //template < ::comparison::equality < ITEM > EQUALITY >
   //constexpr RANGE_ITERATOR _rear_scan(CONST_RANGE range, EQUALITY equality) noexcept
   //{

   //   return BASE_ARRAY::_rear_scan(range, equality);

   //}


   //constexpr RANGE_ITERATOR _rear_scan(CONST_RANGE range) noexcept
   //{

   //   return _rear_scan(range, ::equals_const_reference < ITEM >);

   //}


   //template < ::comparison::equality < ITEM > EQUALITY >
   //constexpr RANGE_ITERATOR rear_scan(CONST_RANGE range, EQUALITY equality) noexcept
   //{

   //   return BASE_ARRAY::rear_scan(range, equality);

   //}



};



template < typename ITERATOR_TYPE >
auto begin(::range < ITERATOR_TYPE > & t)
{

   return t.begin();

}

template < typename ITERATOR_TYPE >
auto end(::range < ITERATOR_TYPE > & t)
{

   return t.begin();

}

template < primitive_range RANGE >
void end_scan_null(RANGE & range) 
{ 

   while (range.is_set(range.end()++)); 

}





template < typename ITEM, ::comparison::equality < ITEM > EQUALITY >
constexpr bool _initialize_range_contains_null_terminated(bool & b, ::range < const ITEM * > range, const ITEM * pzPrefix, EQUALITY equality)
{

   if (::is_empty(pzPrefix, equality))
   {

      b = true;

      return true;

   }

   if (range.is_empty())
   {

      b = false;

      return true;

   }


   return false;

}
template < typename ITEM, ::comparison::equality < ITEM > EQUALITY >
constexpr bool _range_begins_null_terminated(::range < const ITEM * > range, const ITEM * pzPrefix, EQUALITY equality)
{

   do
   {

      if (!equality(*range.begin(), *pzPrefix))
      {

         return false;

      }

      range.begins()++;

      pzPrefix++;

   } while (range.is_set() && equality(*pzPrefix, 0));

   return true;

}
template < typename ITEM, ::comparison::equality < ITEM > EQUALITY >
constexpr bool range_begins_null_terminated(::range < const ITEM * > range, const ITEM * pzPrefix, EQUALITY equality)
{

   bool b;

   if (_initialize_range_begins_null_terminated(b, range, pzPrefix, equality))
   {

      return b;

   }

   return _range_begin_null_terminated(range, pzPrefix, equality);

}


template < typename ITEM, ::comparison::equality < ITEM > EQUALITY >
constexpr bool null_terminated_ends(const ITEM * pz, const ITEM * pzSuffix, EQUALITY equality)
{

   return ::range<const ITEM *>(pz, equality).ends({ pzSuffix, span_zero_item(pzSuffix) }, equality);

}



