// Refactored around 2022-09-12 by camilo <3ThomasBorregaardSørensen!!
#pragma once


enum enum_range : ::i32
{

   e_range_none = 0,
   e_range_string = 1,
   e_range_scoped_string_allocation = 2,

};

template < typename TYPE >
auto & get(TYPE * p)
{

   return *p;

}

template < typename TYPE >
auto & get(const TYPE * p)
{

   return *p;

}


DECLARE_ENUMERATION(e_range, enum_range);


template < primitive_range RANGE >
constexpr RANGE _start_end_range(const RANGE & range, memsize start, typename RANGE::const_iterator end)
{

   return {
           ::clipped_add(range.begin(), start, range.begin(), range.end()),
           ::clipped_add(range.begin(), end - range.begin(), range.begin(), range.end())
   };

}


template < primitive_range RANGE >
constexpr RANGE _start_count_range(const RANGE & range, memsize start, memsize count)
{

   return {
      ::clipped_add(range.begin(), start, range.begin(), range.end()),
      ((count >= 0) ? ::clipped_add(range.begin(), start + count, range.begin(), range.end()) :
      ::clipped_add(range.end(), count, range.begin(), range.end())) };

}


template<typename ITERATOR_TYPE>
struct get_iterator_item_struct
{

   using ITEM = typename ITERATOR_TYPE::ITEM;

};


template<typename ITEM_TYPE>
struct get_iterator_item_struct<ITEM_TYPE *>
{

   using ITEM = ITEM_TYPE;

};


template<typename ITEM_TYPE>
using get_iterator_item = typename get_iterator_item_struct < ITEM_TYPE >::ITEM;


template<typename TYPE>
struct get_type_item_pointer_struct
{

   using type = typename TYPE::ITEM_POINTER;

};


template<typename TYPE>
struct get_type_item_pointer_struct<TYPE *>
{

   using type = non_const<TYPE> *;

};


template<typename TYPE>
struct get_type_item_pointer_struct<const TYPE *>
{

   using type = TYPE *;

};


template<typename TYPE>
using get_type_item_pointer = typename get_type_item_pointer_struct < TYPE >::type;



template<typename iterator>
struct get_iterator_struct
{

   using type = typename iterator::iterator;

};


template<typename TYPE>
struct get_iterator_struct<TYPE *>
{

   using type = non_const<TYPE> *;

};

template<typename TYPE >
using get_iterator = typename get_iterator_struct < TYPE >::type;



template<typename iterator>
struct get_const_iterator_struct
{

   using type = typename iterator::const_iterator;

};


template<typename TYPE>
struct get_const_iterator_struct<TYPE *>
{

   using type = const non_const<TYPE> *;

};


template<typename TYPE >
using get_const_iterator = typename get_const_iterator_struct < TYPE >::type;



template<typename ITERATOR_TYPE>
class range
{
public:


   using this_iterator = ITERATOR_TYPE;
   using iterator = get_iterator<ITERATOR_TYPE>;
   using const_iterator = get_const_iterator<iterator>;


   using THIS_RAW_RANGE = ::range<ITERATOR_TYPE>;
   using RAW_RANGE = ::range<iterator>;
   using CONST_RAW_RANGE = ::range<const_iterator>;


   using THIS_RANGE = ::range<ITERATOR_TYPE>;
   using RANGE = ::range<iterator>;
   using CONST_RANGE = ::range<const_iterator>;


   using ITEM_POINTER = get_type_item_pointer<iterator>;


   using THIS_ITEM = get_iterator_item<ITERATOR_TYPE>;
   using ITEM = non_const<THIS_ITEM>;
   using CONST_ITEM = add_const<THIS_ITEM>;
   using ARG_ITEM = argument_of < ITEM >;


   this_iterator     m_begin;
   this_iterator     m_end;
   e_range           m_erange = e_range_none;


   constexpr range(enum_no_initialize)
   {
   }

   constexpr range(enum_zero_initialize) : range(nullptr, nullptr)
   {

   };

   constexpr range() : range(nullptr, nullptr)
   {
   }

   constexpr range(nullptr_t) : range()
   {
   }

   constexpr range(const range & range) : m_begin(range.m_begin), m_end(range.m_end), m_erange(range.m_erange) {}
   constexpr range(range && range) : m_begin(range.m_begin), m_end(range.m_end), m_erange(range.m_erange) { range.m_begin = nullptr; range.m_end = nullptr; }

   template<typed_range<iterator> RANGE>
   constexpr range(const RANGE & range) : m_begin((this_iterator)range.begin()), m_end((this_iterator)range.end()), m_erange(range.m_erange)
   {
   }

   template<typed_range<const_iterator> RANGE>
   constexpr range(const RANGE & range) : m_begin((this_iterator)range.m_begin), m_end((this_iterator)range.m_end), m_erange(range.m_erange)
   {
   }

   template<typename TYPE>
   constexpr range(TYPE *& p) : m_begin((this_iterator)p), m_end((this_iterator)find_first_null_character(p))
   {
   }

   template<::count count>
   constexpr range(const ITEM(&array)[count]) : range(array, count)
   {
   }

   template<primitive_integral INTEGRAL>
   constexpr range(const_iterator begin, INTEGRAL count) : m_begin(
      (this_iterator)begin), m_end((this_iterator)(begin + count))
   {
   }

   constexpr range(const_iterator begin, const_iterator end) : m_begin(
      (this_iterator)begin), m_end((this_iterator)end)
   {
   }

   template<::comparison::equality<ITEM> EQUALITY>
   constexpr range(const_iterator begin, EQUALITY equality) : m_begin(
      (this_iterator)begin), m_end((this_iterator)find_first_null_character(begin, equality))
   {
   }


   range & operator =(const range & range)
   {

      m_begin = range.m_begin;
      m_end = range.m_end;
      m_erange = range.m_erange;

      return *this;

   }


   range & operator=(range && range)
   {

      m_begin = range.m_begin;
      m_end = range.m_end;
      range.m_begin = nullptr;
      range.m_end = nullptr;

      return *this;

   }


   void add_initializer_list(const ::std::initializer_list<ITEM> & initializer_list)
   {

      // not implementable for ranges without allocation

   }


   bool is_string() const { return m_erange & e_range_string; }
   void set_string_flag() { m_erange |= e_range_string; }
   void clear_string_flag() { m_erange -= e_range_string; }


   constexpr auto offset_of(const_iterator p) const
   {
      return p - (const_iterator)this->begin();
   }


   this_iterator & begin()
   {
      return m_begin;
   }

   this_iterator & end()
   {
      return m_end;
   }

   const_iterator & begin() const
   {
      return (const_iterator &)m_begin;
   }

   const_iterator & end() const
   {
      return (const_iterator &)m_end;
   }

   this_iterator & begin(this_iterator begin)
   {
      return m_begin = begin;
   }

   this_iterator & end(this_iterator end)
   {
      return m_end = end;
   }

   auto & first();
   auto & first() const;

   constexpr this_iterator data()
   {
      return m_begin;
   }


   constexpr const this_iterator data() const
   {
      return m_begin;
   }


   static consteval memsize item_size()
   {
      return sizeof(ITEM);
   }

   constexpr ::count size() const
   {
      return ::is_set(this->begin()) ? maximum(0, this->end() - this->begin()) : 0;
   }

   constexpr bool is_empty() const
   {
      return size() <= 0;
   }

   constexpr  bool is_set() const
   {
      return !is_empty();
   }


   inline bool operator!() const
   {
      return is_empty();
   }


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


   constexpr THIS_RAW_RANGE _start_range(memsize start) const
   {

      return {
         this->begin() + start, this->end()
      };

   }

   constexpr THIS_RAW_RANGE _end_range(const_iterator end) const
   {

      return {
              this->begin(), end
      };

   }



   constexpr THIS_RAW_RANGE _start_count_range(memsize start, memsize count) const
   {

      return {
         this->begin() + start,
         ((count >= 0) ? ::clipped_add(this->begin(), start + count, this->begin(), this->end()) : ::clipped_add(
            this->end(), count, this->begin(), this->end())) };

   }


   static constexpr bool _initialize_equals(bool & b, const THIS_RAW_RANGE & range, const THIS_RAW_RANGE & rangeBlock)
   {

      if (range.size() != rangeBlock.size())
      {

         b = false;

         return true;

      }
      else if (range.is_empty())
      {

         b = true;

         return true;

      }

      return false;

   }


   template<::comparison::equality<ITEM> EQUALITY>
   static constexpr bool _static_equals(THIS_RAW_RANGE range, THIS_RAW_RANGE rangeBlock, EQUALITY equality)
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


   template<::comparison::equality<ITEM> EQUALITY>
   static constexpr bool static_equals(const THIS_RAW_RANGE & range, const THIS_RAW_RANGE & rangeBlock, EQUALITY equality)
   {

      bool b;

      if (_initialize_equals(b, range, rangeBlock))
      {

         return b;

      }

      return _static_equals(range, rangeBlock, equality);

   }


   template<::comparison::equality<ITEM> EQUALITY>
   constexpr bool _equals(const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) const
   {

      return _static_equals(*this, rangeBlock, equality);

   }


   template<::comparison::equality<ITEM> EQUALITY>
   constexpr bool equals(const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) const
   {

      return static_equals(*this, rangeBlock, equality);

   }


   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr bool _equals_start(const THIS_RAW_RANGE &rangeBlock, memsize start, EQUALITY equality) const
   //   {
   //
   //      return _static_equals(_start_range(start), rangeBlock, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr bool equals_start(const THIS_RAW_RANGE &rangeBlock, memsize start, EQUALITY equality) const
   //   {
   //
   //      return static_equals(_start_range(start), rangeBlock, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr bool
   //   _equals_start_count(const THIS_RAW_RANGE &rangeBlock, memsize start, memsize count, EQUALITY equality) const
   //   {
   //
   //      return _static_equals(_start_count_range(start, count), rangeBlock, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr bool
   //   equals_start_count(const THIS_RAW_RANGE &rangeBlock, memsize start, memsize count, EQUALITY equality) const
   //   {
   //
   //      return static_equals(_start_count_range(start, count), rangeBlock, equality);
   //
   //   }


   static constexpr bool
      _initialize_order(::std::strong_ordering & order, const THIS_RAW_RANGE & range, const THIS_RAW_RANGE & rangeBlock)
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

   template<::comparison::ordering<ITEM> ORDERING>
   static constexpr auto _static_order(THIS_RAW_RANGE range, THIS_RAW_RANGE rangeBlock, ORDERING ordering)
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


   template<::comparison::ordering<ITEM> ORDERING>
   static constexpr ::std::strong_ordering
      static_order(const THIS_RAW_RANGE & range, const THIS_RAW_RANGE & rangeBlock, ORDERING ordering)
   {

      std::strong_ordering order(::std::strong_ordering::less);

      if (_initialize_order(order, range, rangeBlock))
      {

         return order;

      }

      return _static_order(range, rangeBlock, ordering);

   }


   template<::comparison::ordering<ITEM> ORDERING>
   constexpr ::std::strong_ordering _order(const THIS_RAW_RANGE & rangeBlock, ORDERING ordering) const
   {

      return _static_order(*this, rangeBlock, ordering);

   }


   template<::comparison::ordering<ITEM> ORDERING>
   constexpr ::std::strong_ordering order(const THIS_RAW_RANGE & rangeBlock, ORDERING ordering) const
   {

      return static_order(*this, rangeBlock, ordering);

   }


   //   template<::comparison::ordering<ITEM> ORDERING>
   //   constexpr ::std::strong_ordering
   //   _order_start(const THIS_RAW_RANGE &rangeBlock, memsize start, ORDERING ordering) const
   //   {
   //
   //      return _static_order(_start_range(start), rangeBlock, ordering);
   //
   //   }
   //
   //
   //   template<::comparison::ordering<ITEM> ORDERING>
   //   constexpr ::std::strong_ordering
   //   order_start(const THIS_RAW_RANGE &rangeBlock, memsize start, ORDERING ordering) const
   //   {
   //
   //      return static_order(_start_range(start), rangeBlock, ordering);
   //
   //   }
   //
   //
   //   template<::comparison::ordering<ITEM> ORDERING>
   //   constexpr ::std::strong_ordering
   //   _order_start_count(const THIS_RAW_RANGE &rangeBlock, memsize start, memsize count, ORDERING ordering) const
   //   {
   //
   //      return _static_order(_start_count_range(start, count), rangeBlock, ordering);
   //
   //   }
   //
   //
   //   template<::comparison::ordering<ITEM> ORDERING>
   //   constexpr ::std::strong_ordering
   //   order_start_count(const THIS_RAW_RANGE &rangeBlock, memsize start, memsize count, ORDERING ordering) const
   //   {
   //
   //      return static_order(_start_count_range(start, count), rangeBlock, ordering);
   //
   //   }


   static bool _initialize_find(const_iterator & p, const THIS_RAW_RANGE & range, const THIS_RAW_RANGE & rangeBlock)
   {

      if (range.is_empty())
      {

         p = nullptr;

         return true;

      }

      return false;

   }


   template<::comparison::equality<ITEM> EQUALITY>
   static const_iterator _static_find(THIS_RAW_RANGE range, const THIS_RAW_RANGE & rangeBlock, EQUALITY equality)
   {

      auto pEnd = range.end() - rangeBlock.size();

      do
      {

         auto p = range.begin();

         auto pBlock = rangeBlock.begin();

         while (true)
         {

            if (!equality.equals(*p, *pBlock))
            {

               break;

            }

            pBlock++;

            if (rangeBlock.is_end(pBlock))
            {

               return range.begin();

            }

            p++;

         }

         range.begin()++;

      } while (range.begin() <= pEnd);

      return nullptr;

   }


   template<::comparison::equality<ITEM> EQUALITY>
   static const_iterator static_find(const THIS_RAW_RANGE & range, const THIS_RAW_RANGE & rangeBlock, EQUALITY equality)
   {

      const_iterator p;

      if (_initialize_find(p, range, rangeBlock))
      {

         return p;

      }

      return _static_find(range, rangeBlock, equality);

   }


   template<::comparison::equality<ITEM> EQUALITY>
   constexpr const_iterator _find(const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) const
   {

      return _static_find(*this, rangeBlock, equality);

   }


   template<::comparison::equality<ITEM> EQUALITY>
   constexpr const_iterator find(const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) const
   {

      return static_find(*this, rangeBlock, equality);

   }


   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator _find_start(const THIS_RAW_RANGE &rangeBlock, memsize start, EQUALITY equality) const
   //   {
   //
   //      return _static_find(_start_range(start), rangeBlock, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator find_start(const THIS_RAW_RANGE &rangeBlock, memsize start, EQUALITY equality) const
   //   {
   //
   //      return static_find(_start_range(start), rangeBlock, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator
   //   _find_start_count(const THIS_RAW_RANGE &rangeBlock, memsize start, memsize count, EQUALITY equality) const
   //   {
   //
   //      return _static_find(_start_count_range(start, count), rangeBlock, equality);
   //
   //   }


   static bool _initialize_rear_find(const_iterator & p, const THIS_RAW_RANGE & range, const THIS_RAW_RANGE & rangeBlock)
   {

      if (rangeBlock.is_empty())
      {

         p = range.end();

         return true;

      }

      if (range.is_empty())
      {

         p = nullptr;

         return true;

      }

      return false;

   }


   template<::comparison::equality<ITEM> EQUALITY>
   static const_iterator _static_rear_find(THIS_RAW_RANGE range, const THIS_RAW_RANGE & rangeBlock, EQUALITY equality)
   {

      do
      {

         auto p = range.end();

         auto pBlock = rangeBlock.end() - 1;

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

               return p + 1;

            }

         }

         range.end()--;

      } while (!range.is_before_begin(range.end()));

      return nullptr;

   }


   template<::comparison::equality<ITEM> EQUALITY>
   static const_iterator
      static_rear_find(const THIS_RAW_RANGE & range, const THIS_RAW_RANGE & rangeBlock, EQUALITY equality)
   {

      const_iterator p;

      if (_initialize_rear_find(p, range, rangeBlock))
      {

         return p;

      }

      return _static_rear_find(range, rangeBlock, equality);

   }


   template<::comparison::equality<ITEM> EQUALITY>
   constexpr const_iterator _rear_find(const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) const
   {

      return _static_rear_find(*this, rangeBlock, equality);

   }


   template<::comparison::equality<ITEM> EQUALITY>
   constexpr const_iterator rear_find(const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) const
   {

      return static_rear_find(*this, rangeBlock, equality);

   }


   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator _rear_find_start(const THIS_RAW_RANGE &rangeBlock, memsize start, EQUALITY equality) const
   //   {
   //
   //      return _static_rear_find(_start_range(start), rangeBlock, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator rear_find_start(const THIS_RAW_RANGE &rangeBlock, memsize start, EQUALITY equality) const
   //   {
   //
   //      return static_rear_find(_start_range(start), rangeBlock, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator
   //   _rear_find_start_count(const THIS_RAW_RANGE &rangeBlock, memsize start, memsize count, EQUALITY equality) const
   //   {
   //
   //      return _static_rear_find(_start_count_range(start, count), rangeBlock, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator
   //   rear_find_start_count(const THIS_RAW_RANGE &rangeBlock, memsize start, memsize count, EQUALITY equality) const
   //   {
   //
   //      return static_rear_find(_start_count_range(start, count), rangeBlock, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator
   //   find_start_count(const THIS_RAW_RANGE &rangeBlock, memsize start, memsize count, EQUALITY equality) const
   //   {
   //
   //      return static_find(_start_count_range(start, count), rangeBlock, equality);
   //
   //   }


   static constexpr bool
      _initialize_skip_any_character_in(const_iterator & p, const THIS_RAW_RANGE & range, const THIS_RAW_RANGE & rangeBlock) noexcept
   {

      if (range.is_empty())
      {

         p = (const_iterator)range.begin();

         return true;

      }

      if (rangeBlock.is_empty())
      {

         p = (const_iterator)range.end();

         return true;

      }

      return false;

   }


   template<::comparison::equality<ITEM> EQUALITY>
   static constexpr const_iterator
      _static_skip_any_character_in(THIS_RAW_RANGE range, const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) noexcept
   {

      do
      {

         auto pBlockScan = rangeBlock.begin();

         while (true)
         {

            if (equality.equals(*range.begin(), *pBlockScan))
            {

               // found a matching item...
               // continue skip_any_character_inning...

               break;

            }

            pBlockScan++;

            if (rangeBlock.is_end(pBlockScan))
            {

               // Iterated through all pBlock items
               // and didn't find any that match *p

               // so p is the end of the skip_any_character_in for matching items...

               return range.begin();

            }

         };

         range.begin()++;

      } while (!range.is_end(range.begin()));

      // reached end of the skip_any_character_inning range...
      // each skip_any_character_inned item matched some item in range...
      // return address immediately after end of skip_any_character_inning...

      return range.begin();

   }


   template<::comparison::equality<ITEM> EQUALITY>
   static constexpr const_iterator
      static_skip_any_character_in(const THIS_RAW_RANGE & range, const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) noexcept
   {

      const_iterator p;

      if (_initialize_skip_any_character_in(p, range, rangeBlock))
      {

         return p;

      }

      return _static_skip_any_character_in(range, rangeBlock, equality);

   }


   template<::comparison::equality<ITEM> EQUALITY>
   constexpr const_iterator _skip_any_character_in(const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) const
   {

      return _static_skip_any_character_in(*this, rangeBlock, equality);

   }


   template<::comparison::equality<ITEM> EQUALITY>
   constexpr const_iterator skip_any_character_in(const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) const
   {

      return static_skip_any_character_in(*this, rangeBlock, equality);

   }


   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator _skip_any_character_in_start(const THIS_RAW_RANGE &rangeBlock, memsize start, EQUALITY equality) const
   //   {
   //
   //      return _static_skip_any_character_in(_start_range(start), rangeBlock, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator skip_any_character_in_start(const THIS_RAW_RANGE &rangeBlock, memsize start, EQUALITY equality) const
   //   {
   //
   //      return static_skip_any_character_in(_start_range(start), rangeBlock, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator
   //   _skip_any_character_in_start_count(const THIS_RAW_RANGE &rangeBlock, memsize start, memsize count, EQUALITY equality) const
   //   {
   //
   //      return _static_skip_any_character_in(_start_count_range(start, count), rangeBlock, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator
   //   skip_any_character_in_start_count(const THIS_RAW_RANGE &rangeBlock, memsize start, memsize count, EQUALITY equality) const
   //   {
   //
   //      return static_skip_any_character_in(_start_count_range(start, count), rangeBlock, equality);
   //
   //   }

   static constexpr bool
      _initialize_find_first_character_in(const_iterator & p, const THIS_RAW_RANGE & range, const THIS_RAW_RANGE & rangeBlock) noexcept
   {

      if (range.is_empty())
      {

         p = nullptr;

         return true;

      }

      if (rangeBlock.is_empty())
      {

         p = range.begin();

         return true;

      }

      return false;

   }


   template<::comparison::equality<ITEM> EQUALITY>
   static constexpr const_iterator
      _static_find_first_character_in(THIS_RAW_RANGE range, const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) noexcept
   {

      do
      {

         auto pBlockScan = rangeBlock.begin();

         do
         {

            if (equality.equals(*range.begin(), *pBlockScan))
            {

               // found a matching item...
               // stop find_first_character_inning and return address of the matching item

               return range.begin();

            }

            pBlockScan++;

         } while (!rangeBlock.is_end(pBlockScan));

         // Didn't found matching item...
         // continue find_first_character_inning...

         range.begin()++;

      } while (!range.is_end(range.begin()));

      // reached end of the find_first_character_inning range...
      // and didn't find any matching items...
      // return address immediately after end of find_first_character_inning range....

      return nullptr;

   }

   template<::comparison::equality<ITEM> EQUALITY>
   static constexpr const_iterator
      static_find_first_character_in(const THIS_RAW_RANGE & range, const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) noexcept
   {

      const_iterator p;

      if (_initialize_find_first_character_in(p, range, rangeBlock))
      {

         return p;

      }

      return _static_find_first_character_in(range, rangeBlock, equality);

   }


   template<::comparison::equality<ITEM> EQUALITY>
   constexpr const_iterator _find_first_character_in(const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) const
   {

      return _static_find_first_character_in(*this, rangeBlock, equality);

   }


   template<::comparison::equality<ITEM> EQUALITY>
   constexpr const_iterator find_first_character_in(const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) const
   {

      return static_find_first_character_in(*this, rangeBlock, equality);

   }


   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator _find_first_character_in_start(const THIS_RAW_RANGE &rangeBlock, memsize start, EQUALITY equality) const
   //   {
   //
   //      return _static_find_first_character_in(_start_range(start), rangeBlock, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator find_first_character_in_start(const THIS_RAW_RANGE &rangeBlock, memsize start, EQUALITY equality) const
   //   {
   //
   //      return static_find_first_character_in(_start_range(start), rangeBlock, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator
   //   _find_first_character_in_start_count(const THIS_RAW_RANGE &rangeBlock, memsize start, memsize count, EQUALITY equality) const
   //   {
   //
   //      return _static_find_first_character_in(_start_count_range(start, count), rangeBlock, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator
   //   find_first_character_in_start_count(const THIS_RAW_RANGE &rangeBlock, memsize start, memsize count, EQUALITY equality) const
   //   {
   //
   //      return static_find_first_character_in(_start_count_range(start, count), rangeBlock, equality);
   //
   //   }


   static constexpr bool
      _initialize_rear_find_first_character_in(const_iterator & p, const THIS_RAW_RANGE & range, const THIS_RAW_RANGE & rangeBlock) noexcept
   {

      if (range.is_empty())
      {

         p = nullptr;

         return true;

      }

      if (rangeBlock.is_empty())
      {

         p = range.end();

         return true;

      }

      return false;

   }


   template<::comparison::equality<ITEM> EQUALITY>
   static constexpr const_iterator
      _static_rear_find_first_character_in(THIS_RAW_RANGE range, const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) noexcept
   {

      do
      {

         auto pBlockScan = rangeBlock.begin();

         do
         {

            if (equality.equals(*range.end(), *pBlockScan))
            {

               // found a matching item...
               // stop find_first_character_inning and return address of the matching item

               return range.end();

            }

            pBlockScan++;

         } while (!rangeBlock.is_end(pBlockScan));

         range.end()--;

      } while (!range.is_before_begin(range.end()));

      return nullptr;

   }


   template<::comparison::equality<ITEM> EQUALITY>
   static constexpr const_iterator
      static_rear_find_first_character_in(THIS_RAW_RANGE range, const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) noexcept
   {

      const_iterator p;

      if (_initialize_rear_find_first_character_in(p, range, rangeBlock))
      {

         return p;

      }

      range.end()--;

      return _static_rear_find_first_character_in(range, rangeBlock, equality);

   }


   template<::comparison::equality<ITEM> EQUALITY>
   constexpr const_iterator _rear_find_first_character_in(const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) const
   {

      return _static_rear_find_first_character_in(*this, rangeBlock, equality);

   }


   template<::comparison::equality<ITEM> EQUALITY>
   constexpr const_iterator rear_find_first_character_in(const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) const
   {

      return static_rear_find_first_character_in(*this, rangeBlock, equality);

   }


   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator _rear_find_first_character_in_start(const THIS_RAW_RANGE & rangeBlock, memsize start, EQUALITY equality) const
   //   {
   //
   //      return _static_rear_find_first_character_in(_start_range(start), rangeBlock, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator rear_find_first_character_in_start(const THIS_RAW_RANGE & rangeBlock, memsize start, EQUALITY equality) const
   //   {
   //
   //      return static_rear_find_first_character_in(_start_range(start), rangeBlock, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator
   //      _rear_find_first_character_in_start_count(const THIS_RAW_RANGE & rangeBlock, memsize start, memsize count, EQUALITY equality) const
   //   {
   //
   //      return _static_rear_find_first_character_in(_start_count_range(start, count), rangeBlock, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator
   //      rear_find_first_character_in_start_count(const THIS_RAW_RANGE & rangeBlock, memsize start, memsize count, EQUALITY equality) const
   //   {
   //
   //      return static_rear_find_first_character_in(_start_count_range(start, count), rangeBlock, equality);
   //
   //   }


   static constexpr bool _initialize_skip(const_iterator & p, const THIS_RAW_RANGE & range) noexcept
   {

      if (range.is_empty())
      {

         p = range.end();

         return true;

      }

      return false;

   }


   template<::comparison::equality<ITEM> EQUALITY>
   static constexpr const_iterator _static_skip(THIS_RAW_RANGE range, ARG_ITEM item, EQUALITY equality) noexcept
   {

      do
      {

         if (!equality.equals(*range.begin(), item))
         {

            return range.begin();

         }

         range.begin()++;

      } while (!range.is_end(range.begin()));

      return range.begin();

   }


   template<::comparison::equality<ITEM> EQUALITY>
   static constexpr const_iterator
      static_skip(const THIS_RAW_RANGE & range, ARG_ITEM item, EQUALITY equality) noexcept
   {

      const_iterator p;

      if (_initialize_skip(p, range))
      {

         return p;

      }

      return _static_skip(range, item, equality);

   }


   template<::comparison::equality<ITEM> EQUALITY>
   constexpr const_iterator _skip(ARG_ITEM item, EQUALITY equality) const
   {

      return _static_skip(*this, item, equality);

   }


   template<::comparison::equality<ITEM> EQUALITY>
   constexpr const_iterator skip(ARG_ITEM item, EQUALITY equality) const
   {

      return static_skip(*this, item, equality);

   }


   static constexpr bool _initialize_rear_skip(const_iterator & p, const THIS_RAW_RANGE & range) noexcept
   {

      if (range.is_empty())
      {

         p = nullptr;

         return true;

      }

      return false;

   }


   template<::comparison::equality<ITEM> EQUALITY>
   static constexpr const_iterator _static_rear_skip(THIS_RAW_RANGE range, ARG_ITEM  item, EQUALITY equality) noexcept
   {

      while (true)
      {

         range.end()--;

         if (range.is_before_begin(range.end()))
         {

            return nullptr;

         }

         if (!equality.equals(*range.end(), item))
         {

            return range.begin();

         }

      }

      return nullptr;

   }


   template<::comparison::equality<ITEM> EQUALITY>
   static constexpr const_iterator
      static_rear_skip(const THIS_RAW_RANGE & range, ARG_ITEM  item, EQUALITY equality) noexcept
   {

      const_iterator p;

      if (_initialize_rear_skip(p, range))
      {

         return p;

      }

      return _static_rear_skip(range, item, equality);

   }


   template<::comparison::equality<ITEM> EQUALITY>
   constexpr const_iterator _rear_skip(ARG_ITEM  item, EQUALITY equality) const
   {

      return _static_rear_skip(*this, item, equality);

   }


   template<::comparison::equality<ITEM> EQUALITY>
   constexpr const_iterator rear_skip(ARG_ITEM  item, EQUALITY equality) const
   {

      return static_rear_skip(*this, item, equality);

   }


   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator _skip_start(ARG_ITEM item, memsize start, EQUALITY equality) const
   //   {
   //
   //      return _static_skip(_start_range(start), item, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator skip_start(ARG_ITEM item, memsize start, EQUALITY equality) const
   //   {
   //
   //      return static_skip(_start_range(start), item, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator _skip_start_count(ARG_ITEM item, memsize start, memsize count, EQUALITY equality) const
   //   {
   //
   //      return _static_skip(_start_count_range(start, count), item, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator skip_start_count(ARG_ITEM item, memsize start, memsize count, EQUALITY equality) const
   //   {
   //
   //      return static_skip(_start_count_range(start, count), item, equality);
   //
   //   }


   static constexpr bool _initialize_find_item(const_iterator & p, const THIS_RAW_RANGE & range) noexcept
   {

      if (range.is_empty())
      {

         p = nullptr;

         return true;

      }

      return false;

   }


   //   template<::comparison::equality<ITEM> EQUALITY>
   //static constexpr const_iterator
   //static_skip(const THIS_RAW_RANGE &range, ARG_ITEM item, EQUALITY equality) noexcept
   //{

   //   const_iterator p;

   //   if (_initialize_skip(p, range))
   //   {

   //      return p;

   //   }

   //   return _static_skip(range, item, equality);

   //}


   //template<::comparison::equality<ITEM> EQUALITY>
   //constexpr const_iterator _skip(ARG_ITEM item, EQUALITY equality) const
   //{

   //   return _static_skip(*this, item, equality);

   //}


   //template<::comparison::equality<ITEM> EQUALITY>
   //constexpr const_iterator skip(ARG_ITEM item, EQUALITY equality) const
   //{

   //   return static_skip(*this, item, equality);

   //}


   static constexpr bool _initialize_rear_find(const_iterator & p, const THIS_RAW_RANGE & range) noexcept
   {

      if (range.is_empty())
      {

         p = nullptr;

         return true;

      }

      return false;

   }


   template<::comparison::equality<ITEM> EQUALITY>
   static constexpr const_iterator
      _static_rear_find(THIS_RAW_RANGE range, ARG_ITEM  item, EQUALITY equality) noexcept
   {

      while (true)
      {

         range.end()--;

         if (range.is_before_begin(range.end()))
         {

            return nullptr;

         }

         if (equality.equals(*range.end(), item))
         {

            return range.end();

         }

      }

      return nullptr;

   }



   template<::comparison::equality<ITEM> EQUALITY>
   static constexpr const_iterator
      static_rear_find(THIS_RAW_RANGE range, ARG_ITEM item, EQUALITY equality) noexcept
   {

      const_iterator p;

      if (_initialize_find_item(p, range))
      {

         return p;

      }

      range.end()--;

      return _static_rear_find(range, item, equality);

   }


   template<::comparison::equality<ITEM> EQUALITY>
   constexpr const_iterator _rear_find(ARG_ITEM item, EQUALITY equality) const
   {

      return _static_rear_find(*this, item, equality);

   }


   template<::comparison::equality<ITEM> EQUALITY>
   constexpr const_iterator rear_find(ARG_ITEM item, EQUALITY equality) const
   {

      return static_rear_find(*this, item, equality);

   }


   //   template<::comparison::equality<ITEM> EQUALITY>
   //static constexpr const_iterator
   //static_skip(const THIS_RAW_RANGE &range, ARG_ITEM item, EQUALITY equality) noexcept
   //{

   //   const_iterator p;

   //   if (_initialize_skip(p, range))
   //   {

   //      return p;

   //   }

   //   return _static_skip(range, item, equality);

   //}


   //template<::comparison::equality<ITEM> EQUALITY>
   //constexpr const_iterator _skip(ARG_ITEM item, EQUALITY equality) const
   //{

   //   return _static_skip(*this, item, equality);

   //}


   //template<::comparison::equality<ITEM> EQUALITY>
   //constexpr const_iterator skip(ARG_ITEM item, EQUALITY equality) const
   //{

   //   return static_skip(*this, item, equality);

   //}

//   template<::comparison::equality<ITEM> EQUALITY>
//   constexpr const_iterator _rear_find_item_start(ARG_ITEM item, memsize start, EQUALITY equality) const
//   {
//
//      return _static_rear_find_item(_start_range(start), item, equality);
//
//   }
//
//
//   template<::comparison::equality<ITEM> EQUALITY>
//   constexpr const_iterator rear_find_item_start(ARG_ITEM item, memsize start, EQUALITY equality) const
//   {
//
//      return static_rear_find_item(_start_range(start), item, equality);
//
//   }
//
//
//   template<::comparison::equality<ITEM> EQUALITY>
//   constexpr const_iterator
//   _rear_find_item_start_count(ARG_ITEM item, memsize start, memsize count, EQUALITY equality) const
//   {
//
//      return _static_rear_find_item(_start_count_range(start, count), item, equality);
//
//   }
//
//
//   template<::comparison::equality<ITEM> EQUALITY>
//   constexpr const_iterator
//   rear_find_item_start_count(ARG_ITEM item, memsize start, memsize count, EQUALITY equality) const
//   {
//
//      return static_rear_find_item(_start_count_range(start, count), item, equality);
//
//   }


   static constexpr bool
      _initialize_rear_skip_any_character_in(const_iterator & p, const THIS_RAW_RANGE & range, const THIS_RAW_RANGE & rangeBlock) noexcept
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


   template<::comparison::equality<ITEM> EQUALITY>
   static constexpr const_iterator
      _static_rear_skip_any_character_in(THIS_RAW_RANGE range, const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) noexcept
   {

      do
      {

         auto pBlockScan = rangeBlock.begin();

         while (true)
         {

            if (equality.equals(*range.end(), *pBlockScan))
            {

               // found a matching item...
               // continue skip_any_character_inning...

               break;

            }

            pBlockScan++;

            if (rangeBlock.is_end(pBlockScan))
            {

               // Iterated through all pBlock items
               // and didn't find any that match *p

               // so p is the end of the skip_any_character_in for matching items...

               return range.end() + 1;

            }

         };

         range.end()--;

      } while (!range.is_before_begin(range.end()));

      // reached end of the skip_any_character_inning range...
      // each skip_any_character_inned item matched some item in range...
      // return address immediately after end of skip_any_character_inning...

      return range.begin();

   }


   template<::comparison::equality<ITEM> EQUALITY>
   static constexpr const_iterator
      static_rear_skip_any_character_in(THIS_RAW_RANGE range, const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) noexcept
   {

      const_iterator p;

      if (_initialize_rear_skip_any_character_in(p, range, rangeBlock))
      {

         return p;

      }

      range.end()--;

      return _static_rear_skip_any_character_in(range, rangeBlock, equality);

   }


   template<::comparison::equality<ITEM> EQUALITY>
   constexpr const_iterator _rear_skip_any_character_in(const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) const
   {

      return _static_rear_skip_any_character_in(*this, rangeBlock, equality);

   }


   template<::comparison::equality<ITEM> EQUALITY>
   constexpr const_iterator rear_skip_any_character_in(const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) const
   {

      return static_rear_skip_any_character_in(*this, rangeBlock, equality);

   }


   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator _rear_skip_any_character_in_start(const THIS_RAW_RANGE &rangeBlock, const_iterator end, EQUALITY equality) const
   //   {
   //
   //      return _static_rear_skip_any_character_in(_end_range(end), rangeBlock, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator rear_skip_any_character_in_start(const THIS_RAW_RANGE &rangeBlock, memsize start, EQUALITY equality) const
   //   {
   //
   //      return static_rear_skip_any_character_in(_start_range(start), rangeBlock, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator
   //   _rear_skip_any_character_in_start_count(const THIS_RAW_RANGE &rangeBlock, memsize start, memsize count, EQUALITY equality) const
   //   {
   //
   //      return _static_rear_skip_any_character_in(_start_count_range(start, count), rangeBlock, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr const_iterator
   //   rear_skip_any_character_in_start_count(const THIS_RAW_RANGE &rangeBlock, memsize start, memsize count, EQUALITY equality) const
   //   {
   //
   //      return static_rear_skip_any_character_in(_start_count_range(start, count), rangeBlock, equality);
   //
   //   }


   static constexpr bool
      _initialize_contains(bool & b, const THIS_RAW_RANGE & range, const THIS_RAW_RANGE & rangeBlock) noexcept
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


   template<::comparison::equality<ITEM> EQUALITY>
   static constexpr bool _static_begins(THIS_RAW_RANGE range, THIS_RAW_RANGE rangeBlock, EQUALITY equality) noexcept
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

      return rangeBlock.is_end(rangeBlock.begin());

   }


   template<::comparison::equality<ITEM> EQUALITY>
   static constexpr bool
      static_begins(const THIS_RAW_RANGE & range, const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) noexcept
   {

      bool b;

      if (_initialize_contains(b, range, rangeBlock))
      {

         return b;

      }

      return _static_begins(range, rangeBlock, equality);

   }


   template<::comparison::equality<ITEM> EQUALITY>
   constexpr bool _begins(const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) const
   {

      return _static_begins(*this, rangeBlock, equality);

   }


   template<::comparison::equality<ITEM> EQUALITY>
   constexpr bool begins(const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) const
   {

      return static_begins(*this, rangeBlock, equality);

   }


   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr bool _begins_start(const THIS_RAW_RANGE &rangeBlock, memsize start, EQUALITY equality) const
   //   {
   //
   //      return _static_begins(_start_range(start), rangeBlock, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr bool begins_start(const THIS_RAW_RANGE &rangeBlock, memsize start, EQUALITY equality) const
   //   {
   //
   //      return static_begins(_start_range(start), rangeBlock, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr bool
   //   _begins_start_count(const THIS_RAW_RANGE &rangeBlock, memsize start, memsize count, EQUALITY equality) const
   //   {
   //
   //      return _static_begins(_start_count_range(start, count), rangeBlock, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr bool
   //   begins_start_count(const THIS_RAW_RANGE &rangeBlock, memsize start, memsize count, EQUALITY equality) const
   //   {
   //
   //      return static_begins(_start_count_range(start, count), rangeBlock, equality);
   //
   //   }


   template<::comparison::equality<ITEM> EQUALITY>
   static constexpr bool _static_ends(THIS_RAW_RANGE range, THIS_RAW_RANGE rangeBlock, EQUALITY equality) noexcept
   {

      range.end()--;

      rangeBlock.end()--;

      do
      {

         if (!equality.equals(*range.end(), *rangeBlock.end()))
         {

            return false;

         }

         range.end()--;

         rangeBlock.end()--;

         if (rangeBlock.is_before_begin(rangeBlock.end()))
         {

            return true;

         }

      } while (!range.is_before_begin(range.end()));

      return false;

   }


   template<::comparison::equality<ITEM> EQUALITY>
   static constexpr bool
      static_ends(const THIS_RAW_RANGE & range, const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) noexcept
   {

      bool b;

      if (_initialize_contains(b, range, rangeBlock))
      {

         return b;

      }

      return _static_ends(range, rangeBlock, equality);

   }


   template<::comparison::equality<ITEM> EQUALITY>
   constexpr bool _ends(const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) const
   {

      return _static_ends(*this, rangeBlock, equality);

   }


   template<::comparison::equality<ITEM> EQUALITY>
   constexpr bool ends(const THIS_RAW_RANGE & rangeBlock, EQUALITY equality) const
   {

      return static_ends(*this, rangeBlock, equality);

   }


   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr bool _ends_start(const THIS_RAW_RANGE &rangeBlock, memsize start, EQUALITY equality) const
   //   {
   //
   //      return _static_ends(_start_range(start), rangeBlock, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr bool ends_start(const THIS_RAW_RANGE &rangeBlock, memsize start, EQUALITY equality) const
   //   {
   //
   //      return static_ends(_start_range(start), rangeBlock, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr bool
   //   _ends_start_count(const THIS_RAW_RANGE &rangeBlock, memsize start, memsize count, EQUALITY equality) const
   //   {
   //
   //      return _static_ends(_start_count_range(start, count), rangeBlock, equality);
   //
   //   }
   //
   //
   //   template<::comparison::equality<ITEM> EQUALITY>
   //   constexpr bool
   //   ends_start_count(const THIS_RAW_RANGE &rangeBlock, memsize start, memsize count, EQUALITY equality) const
   //   {
   //
   //      return static_ends(_start_count_range(start, count), rangeBlock, equality);
   //
   //   }



   //constexpr bool _equals_prefix(bool & b, const THIS_RAW_RANGE & range) const
   //{

   //   return BASE_ARRAY::_equals_prefix(b, range);

   //}


   //using BASE_ARRAY::_equals_prefix;

   //template < ::comparison::equality < ITEM > EQUALITY >
   //constexpr auto _equals(const THIS_RAW_RANGE & range, EQUALITY equality) const
   //{

   //   return BASE_ARRAY::_equals(range, equality);

   //}

   //constexpr bool _equals(const THIS_RAW_RANGE & range) const
   //{

   //   return this->_equals(range, ::equals_const_reference < ITEM >);

   //}


   //template < ::comparison::equality < ITEM > EQUALITY >
   //constexpr bool equals(const THIS_RAW_RANGE & range, EQUALITY equality) const
   //{

   //   return BASE_ARRAY::equals(range, equality);

   //}

   //constexpr bool _initialize_order(::std::strong_ordering & ordering, const THIS_RAW_RANGE & range) const
   //{

   //   return BASE_ARRAY::_initialize_order(range, equality);

   //}


   //template < typename COMPARE >
   //constexpr auto _order(const THIS_RAW_RANGE & range, COMPARE compare) const
   //{

   //   return BASE_ARRAY::_order(range, equality);

   //}

   //template < typename COMPARE >
   //constexpr ::std::strong_ordering compare(const THIS_RAW_RANGE & range, COMPARE compare) const
   //{

   //   return BASE_ARRAY::compare(range, compare);

   //}


   //constexpr ::std::strong_ordering operator<=>(const THIS_RAW_RANGE & range) const
   //{

   //   return compare(range, ::compare_const_reference < ITEM >);

   //}


   //static bool _find_prefix(const_iterator & p, const ::string & str, const ::string & strScope)
   //{

   //   return BASE_ARRAY::_equals(range, equality);

   //}


   //template < ::comparison::equality < ITEM > EQUALITY >
   //static this_iterator _find(RANGE search)
   //{

   //   return BASE_ARRAY::_find(search, equality);

   //}


   //template < ::comparison::equality < ITEM > EQUALITY >
   //const_iterator find(const ::string & str, EQUALITY equality) const
   //{

   //   return BASE_ARRAY::find(range, equality);

   //}


   //constexpr bool _skip_any_character_in_prefix(this_iterator & p, const THIS_RAW_RANGE & range) const noexcept
   //{

   //   return BASE_ARRAY::_skip_any_character_in_prefix(range, equality);

   //}


   //template < ::comparison::equality < ITEM > EQUALITY >
   //constexpr this_iterator _skip_any_character_in(const THIS_RAW_RANGE & range, EQUALITY equality) noexcept
   //{

   //   return BASE_ARRAY::_skip_any_character_in(range, equality);

   //}


   //constexpr this_iterator _skip_any_character_in(const THIS_RAW_RANGE & range) noexcept
   //{

   //   return _skip_any_character_in(range, ::equals_const_reference < ITEM >);

   //}


   //template < ::comparison::equality < ITEM > EQUALITY >
   //constexpr this_iterator skip_any_character_in(const THIS_RAW_RANGE & range, EQUALITY equality) noexcept
   //{

   //   return BASE_ARRAY::skip_any_character_in(range, equality);

   //}


   //constexpr this_iterator skip_any_character_in(const THIS_RAW_RANGE & range) noexcept
   //{

   //   return skip_any_character_in(range, ::equals_const_reference < ITEM >);

   //}


   //constexpr bool _find_first_character_in_prefix(this_iterator & p, const THIS_RAW_RANGE & range) noexcept
   //{

   //   return BASE_ARRAY::_find_first_character_in_prefix(range, equality);

   //}


   //template < ::comparison::equality < ITEM > EQUALITY >
   //constexpr this_iterator _find_first_character_in(const THIS_RAW_RANGE & range, EQUALITY equality) noexcept
   //{

   //   return BASE_ARRAY::_find_first_character_in(range, equality);

   //}


   //constexpr this_iterator _find_first_character_in(const THIS_RAW_RANGE & range) noexcept
   //{

   //   return _find_first_character_in(range, ::equals_const_reference < ITEM >);

   //}


   //template < ::comparison::equality < ITEM > EQUALITY >
   //constexpr this_iterator find_first_character_in(const THIS_RAW_RANGE & range, EQUALITY equality) noexcept
   //{

   //   return BASE_ARRAY::find_first_character_in(range, equality);

   //}


   //constexpr this_iterator find_first_character_in(const THIS_RAW_RANGE & range) noexcept
   //{

   //   return find_first_character_in(range, ::equals_const_reference < ITEM >);

   //}


   //template < ::comparison::equality < ITEM > EQUALITY >
   //constexpr this_iterator _skip(ARG_ITEM  item, EQUALITY equality) noexcept
   //{

   //   return BASE_ARRAY::_skip(range, equality);

   //}


   //constexpr this_iterator _skip(ARG_ITEM  item) noexcept
   //{

   //   return _skip(item, ::equals_const_reference < ITEM >);

   //}


   //template < ::comparison::equality < ITEM > EQUALITY >
   //constexpr this_iterator skip(ARG_ITEM  item, EQUALITY equality) noexcept
   //{

   //   return BASE_ARRAY::skip(item, equality);

   //}


   //constexpr this_iterator skip(ARG_ITEM  item) noexcept
   //{

   //   return skip(item, ::equals_const_reference < ITEM >);

   //}


   //template < ::comparison::equality < ITEM > EQUALITY >
   //constexpr this_iterator _rear_find_item(ITEM item, EQUALITY equality) noexcept
   //{

   //   return BASE_ARRAY::_rear_find_item(item, equality);

   //}


   //constexpr this_iterator _rear_find_item(ITEM item) noexcept
   //{

   //   return _rear_find_item(item, ::equals_const_reference < ITEM >);

   //}


   //template < ::comparison::equality < ITEM > EQUALITY >
   //constexpr this_iterator rear_find_item(ITEM item, EQUALITY equality) noexcept
   //{

   //   return BASE_ARRAY::rear_find_item(item, equality);

   //}


   //constexpr this_iterator rear_find_item(ITEM item) noexcept
   //{

   //   return rear_find_item(item, ::equals_const_reference < ITEM >);

   //}


   //constexpr bool _rear_skip_any_character_in_prefix(this_iterator & p, const THIS_RAW_RANGE & range) noexcept
   //{

   //   return BASE_ARRAY::_rear_skip_any_character_in_prefix(p, range);

   //}


   //template < ::comparison::equality < ITEM > EQUALITY >
   //constexpr this_iterator _rear_skip_any_character_in(const THIS_RAW_RANGE & range, EQUALITY equality) noexcept
   //{

   //   return BASE_ARRAY::_rear_skip_any_character_in(range, equality);

   //}


   //constexpr this_iterator _rear_skip_any_character_in(const THIS_RAW_RANGE & range) noexcept
   //{

   //   return _rear_skip_any_character_in(range, ::equals_const_reference < ITEM >);

   //}


   //template < ::comparison::equality < ITEM > EQUALITY >
   //constexpr this_iterator rear_skip_any_character_in(const THIS_RAW_RANGE & range, EQUALITY equality) noexcept
   //{

   //   return BASE_ARRAY::rear_skip_any_character_in(range, equality);

   //}



};


template<typename ITERATOR_TYPE>
auto begin(::range<ITERATOR_TYPE> & t)
{

   return t.begin();

}

template<typename ITERATOR_TYPE>
auto end(::range<ITERATOR_TYPE> & t)
{

   return t.begin();

}

template<primitive_range RANGE>
void end_skip_any_character_in_null(RANGE & range)
{

   while (range.is_set(range.end()++));

}


template<typename ITEM, ::comparison::equality<ITEM> EQUALITY>
constexpr bool _initialize_range_contains_null_terminated(bool & b, ::range<const ITEM *> range, const ITEM * pzPrefix,
                                                          EQUALITY equality)
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

template<typename ITEM, ::comparison::equality<ITEM> EQUALITY>
constexpr bool _range_begins_null_terminated(::range<const ITEM *> range, const ITEM * pzPrefix, EQUALITY equality)
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

template<typename ITEM, ::comparison::equality<ITEM> EQUALITY>
constexpr bool range_begins_null_terminated(::range<const ITEM *> range, const ITEM * pzPrefix, EQUALITY equality)
{

   bool b;

   if (_initialize_range_begins_null_terminated(b, range, pzPrefix, equality))
   {

      return b;

   }

   return _range_begin_null_terminated(range, pzPrefix, equality);

}


template<typename ITEM, ::comparison::equality<ITEM> EQUALITY>
constexpr bool null_terminated_ends(const ITEM * pz, const ITEM * pzSuffix, EQUALITY equality)
{

   return ::range<const ITEM *>(pz, equality).ends({ pzSuffix, find_first_null_character(pzSuffix) }, equality);

}



