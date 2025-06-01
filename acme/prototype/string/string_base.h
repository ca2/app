// string_base Created by camilo on 2012-12-18 18:44 <3ThomasBorregaardSorensen!!
// string_base concept erased and merged into 
// string_base by Camilo on 2025-04-21 17:30 <3ThomasBorregaardSørensen!!
#pragma once


CLASS_DECL_ACME void __what__(int i);


#include "string_iterator.h"
//#ifdef   _STDIO_H_
//#error "already included?!?! WHAT?!?! (After including acme/prototype/string/string_base.h(1))"_ansi
//#endif
#include "string_heap_data.h"
//#ifdef   _STDIO_H_
//#error "already included?!?! WHAT?!?! (After including acme/prototype/string/string_base.h(2))"_ansi
//#endif
#include "const_string_range.h"
//#ifdef   _STDIO_H_
//#error "already included?!?! WHAT?!?! (After including acme/prototype/string/string_base.h(3))"_ansi
//#endif
#include "string_range.h"
//#ifdef   _STDIO_H_
//#error "already included?!?! WHAT?!?! (After including acme/prototype/string/string_base.h(4))"_ansi
//#endif
#include "mutable_string_range.h"
//#ifdef   _STDIO_H_
//#error "already included?!?! WHAT?!?! (After including acme/prototype/string/string_base.h(5))"_ansi
//#endif
#include "acme/prototype/prototype/function.h"
//#ifdef   _STDIO_H_
//#error "already included?!?! WHAT?!?! (After including acme/prototype/string/string_base.h(A))"_ansi
//#endif
//#include "acme/memory/string_memory_allocator.h"
#include "acme/memory/memory.h"
//#ifdef   _STDIO_H_
//#error "already included?!?! WHAT?!?! (After including acme/prototype/string/string_base.h(C))"_ansi
//#endif
#if defined(__STD_FORMAT)
#include <format>
#endif
//#ifdef   _STDIO_H_
//#error "already included?!?! WHAT?!?! (After including <format>)"_ansi
//#endif

template < typename ITERATOR_TYPE >
using string_natural_pointer =
::natural_pointer < 
   ::string_heap_data <
   dereference <
   get_type_item_pointer < ITERATOR_TYPE >
   >
   >, ::heap::e_memory_string >;


enum enum_canonical
{

   e_canonical,

};


template < typename ITERATOR_TYPE >
inline const_string_range < ITERATOR_TYPE > string_get_word_separated_by_spaces(const scoped_string_base < ITERATOR_TYPE > & str, ITERATOR_TYPE * ppfound = nullptr);

template < typename ITERATOR_TYPE >
inline const_string_range < ITERATOR_TYPE > string_get_word_with_separator_list(const scoped_string_base < ITERATOR_TYPE > & str, const scoped_string_base < ITERATOR_TYPE > & strSeparatorList, ITERATOR_TYPE * ppfound = nullptr);


template < typename ITERATOR_TYPE >
using get_word_function = ::function < const_string_range < ITERATOR_TYPE >(const scoped_string_base < ITERATOR_TYPE > &, ITERATOR_TYPE *) >;


template < typename ITERATOR_TYPE >
class string_base :
   public ::const_string_range < ITERATOR_TYPE >,
   public ::string_natural_pointer < ITERATOR_TYPE >
{
public:
   

   using BASE_RANGE = ::const_string_range < ITERATOR_TYPE >;
   using this_iterator = typename BASE_RANGE::this_iterator;
   using iterator = typename BASE_RANGE::iterator;
   using const_iterator = typename BASE_RANGE::const_iterator;



   using NATURAL_POINTER = string_natural_pointer < this_iterator >;
   using BASE_DATA = typename NATURAL_POINTER::BASE_DATA;
   //using META_DATA = typename NATURAL_POINTER::META_DATA;
   using PRIMITIVE_STRING_TAG = PRIMITIVE_STRING_TAG_TYPE;
   using ITEM_POINTER = get_type_item_pointer< this_iterator >;
   using ITEM = ::const_string_range < ITERATOR_TYPE >::ITEM;
   using CHARACTER = ::const_string_range < ITERATOR_TYPE >::CHARACTER;
   //using THIS_RAW_RANGE = typename BASE_RANGE::THIS_RAW_RANGE;
   using SCOPED_STRING = scoped_string_base < this_iterator >;


   string_base() { default_construct(); }
   string_base(no_initialize_t) : ::const_string_range < ITERATOR_TYPE >(no_initialize_t{}) {}
   string_base(nullptr_t) { default_construct(); }
   //string_base(enum_for_moving) { }
   //string_base(enum_get_buffer, character_count length) { get_buffer(length); }
   //string_base(const ::ansi_character * psz);
   //string_base(const ::wd16_character * psz);
   //string_base(const ::wd32_character * psz);
   //string_base(const ::std::string & str) : string_base(str.c_str()) { }

   string_base(const string_base& str) :
      ::const_string_range < ITERATOR_TYPE >(no_initialize_t{})
   { 
      
      construct1(str); 
   
   }
   
   
   //template < character_count n >
   //string_base(const CHARACTER (&s)[n]) :
   //   ::const_string_range<ITERATOR_TYPE>(no_initialize_t{})
   //{

   //   if constexpr (n >= 1)
   //   {

   //      if (s[n - 1] == CHARACTER{})
   //      {

   //         this->m_begin = s;
   //         this->m_end = s + n - 1;
   //         //this->m_erange = e_range_null_terminated
   //           // | e_range_string_literal;
   //         this->m_erange = e_range_null_terminated;
   //           // | e_range_string_literal;

   //         return;

   //      }

   //   }

   //   this->m_begin = s;
   //   this->m_end = s + string_safe_length(s);
   //   this->m_erange = e_range_none;
   //   //this->m_erange = e_range_none | e_range_string_literal;

   //}

   template < typename RANGE >
   string_base(const RANGE & str) requires
      (::std::is_base_of_v < ::range < const typename string_base < ITERATOR_TYPE >::CHARACTER* >, RANGE >
      && !
      (::std::is_base_of_v < string_base < ITERATOR_TYPE >, RANGE >
         || ::std::is_same_v < string_base < ITERATOR_TYPE >, RANGE >)) :
      ::const_string_range < ITERATOR_TYPE >(no_initialize_t{})
   {
      
      construct10(str);

   }


   template < typename RANGE, typename RANGE2 >
   string_base(const RANGE& range1, const RANGE2 & range2) requires
      ::std::is_base_of_v < ::range < const typename string_base < ITERATOR_TYPE >::CHARACTER* >, RANGE >
      &&
      ::std::is_base_of_v < ::range < const typename string_base < ITERATOR_TYPE >::CHARACTER* >, RANGE2 >:
      ::const_string_range < ITERATOR_TYPE >(no_initialize_t{})
   {

      construct40(range1, range2);

   }

   
   template < typename OTHER_CHARACTER >
   string_base(const ::range < const OTHER_CHARACTER* >& range)
   requires other_primitive_character < OTHER_CHARACTER, CHARACTER >:
      ::const_string_range < ITERATOR_TYPE >(no_initialize_t{})
   {

      construct20(range);

   }


   //string_base(const ::ansi_string & ansistr) : NATURAL_POINTER(no_initialize_t{}) { construct10(ansistr); }
   //string_base(const ::wd16_string & wd16str) : NATURAL_POINTER(no_initialize_t{}) { construct10(wd16str); }
   //string_base(const ::wd32_string & wd32str) : NATURAL_POINTER(no_initialize_t{}) { construct10(wd32str); }
   string_base(string_base && str) :
      ::const_string_range < ITERATOR_TYPE >(no_initialize_t{})
   { 
      this->m_begin = str.m_begin; 
      this->m_end = str.m_end;
      this->m_erange = str.m_erange;
      str.m_begin = nullptr; 
      str.m_end = nullptr; 
   }

   //void _construct(const ::ansi_string & ansistr) { construct10(ansistr); }
   //void _construct(const ::wd16_string & wd16str) { construct10(wd16str); }
   //void _construct(const ::wd32_string & wd32str) { construct10(wd32str); }
   //void _construct(string_base && str)
   //{
   //   this->m_begin = str.m_begin;
   //   this->m_end = str.m_end;
   //   this->m_erange = str.m_erange;
   //   str.m_begin = nullptr;
   //   str.m_end = nullptr;
   //}

//   template<typed_range<::ansi_character *> RANGE>
//   string_base(const RANGE & str) : NATURAL_POINTER(no_initialize_t{}) { construct2(str); }
//   template<typed_range<const ::ansi_character *> RANGE>
//   string_base(const RANGE & str) : NATURAL_POINTER(no_initialize_t{}) { construct2(str); }
//   template<typed_range<::wd16_character *> RANGE>
//   string_base(const RANGE & str) : NATURAL_POINTER(no_initialize_t{}) { construct2(str); }
//   template<typed_range<const ::wd16_character *> RANGE>
//   string_base(const RANGE & str) : NATURAL_POINTER(no_initialize_t{}) { construct2(str); }
//   template<typed_range<::wd32_character *> RANGE>
//   string_base(const RANGE & str) : NATURAL_POINTER(no_initialize_t{}) { construct2(str); }
//   template<typed_range<const ::wd32_character *> RANGE>
//   string_base(const RANGE & str) : NATURAL_POINTER(no_initialize_t{}) { construct2(str); }


   //template<typed_range<::ansi_character *> RANGE>
   //explicit string_base(const RANGE & str) : NATURAL_POINTER(no_initialize_t{}) { construct10(str); }
   //template<typed_range<::wd16_character *> RANGE>
   //explicit string_base(const RANGE & str) : NATURAL_POINTER(no_initialize_t{}) { construct10(str); }
   //template<typed_range<::wd32_character *> RANGE>
   //explicit string_base(const RANGE & str) : NATURAL_POINTER(no_initialize_t{}) { construct10(str); }


   //template<typed_range<const ::ansi_character *> RANGE>
   //explicit string_base(const RANGE & str) : NATURAL_POINTER(no_initialize_t{}) { construct10(str); }
   //template<typed_range<const ::wd16_character *> RANGE>
   //explicit string_base(const RANGE & str) : NATURAL_POINTER(no_initialize_t{}) { construct10(str); }
   //template<typed_range<const ::wd32_character *> RANGE>
   //explicit string_base(const RANGE & str) : NATURAL_POINTER(no_initialize_t{}) { construct10(str); }

   //template < int t_size >
   //inline string_base(const const_string_range_static_array < ITERATOR_TYPE, t_size >& a);

   //template < other_primitive_character < typename string_base < ITERATOR_TYPE >::CHARACTER > OTHER_CHARACTER, int t_size >
   //inline string_base(const const_string_range_static_array < const OTHER_CHARACTER *, t_size > & a);

//   template<typed_range<::ansi_character *> RANGE>
//   string_base(const RANGE & str) : NATURAL_POINTER(no_initialize_t{}) { construct2(str); }
////   template<typed_range<const ::ansi_character *> RANGE>
////   string_base(const RANGE & str) : NATURAL_POINTER(no_initialize_t{}) { construct2(str, start, count); }
//   template<typed_range<::wd16_character *> RANGE>
//   string_base(const RANGE & str) : NATURAL_POINTER(no_initialize_t{}) { construct2(str); }
////   template<typed_range<const ::wd16_character *> RANGE>
////   string_base(const RANGE & str) : NATURAL_POINTER(no_initialize_t{}) { construct2(str, start, count); }
//   template<typed_range<::wd32_character *> RANGE>
//   string_base(const RANGE & str) : NATURAL_POINTER(no_initialize_t{}) { construct2(str); }
////   template<typed_range<const ::wd32_character *> RANGE>
////   string_base(const RANGE & str) : NATURAL_POINTER(no_initialize_t{}) { construct2(str, start, count); }

   //   string_base(const ::const_ansi_range & ansirange) : NATURAL_POINTER(no_initialize_t{}){construct2(ansirange);}
//   string_base(const ::const_wd16_range & wd16range) : NATURAL_POINTER(no_initialize_t{}){construct2(wd16range);}
//   string_base(const ::const_wd32_range & wd32range) : NATURAL_POINTER(no_initialize_t{}){construct2(wd32range);}
   
   //xxxstring_base(const const_ansi_range & ansirange) : NATURAL_POINTER(no_initialize_t{}) { construct2(ansirange.begin(), ansirange.size()); }
   //xxxstring_base(const const_wd16_range & wd16range) : NATURAL_POINTER(no_initialize_t{}) { construct2(wd16range.begin(), wd16range.size()); }
   //xxxstring_base(const const_wd32_range & wd32range) : NATURAL_POINTER(no_initialize_t{}) { construct2(wd32range.begin(), wd32range.size()); }
   //string_base(const const_ansi_range & ansirange) : NATURAL_POINTER(no_initialize_t{}) { construct10(ansirange); }
   //string_base(const const_wd16_range & wd16range) : NATURAL_POINTER(no_initialize_t{}) { construct10(wd16range); }
   //string_base(const const_wd32_range & wd32range) : NATURAL_POINTER(no_initialize_t{}) { construct10(wd32range); }
   //string_base(const const_ansi_range & ansirange, character_count length) : NATURAL_POINTER(no_initialize_t{})  { construct2(ansirange, 0, length); }
   //string_base(const const_wd16_range & wd16range, character_count length) : NATURAL_POINTER(no_initialize_t{})  { construct2(wd16range, 0, length); }
   //string_base(const const_wd32_range & wd32range, character_count length) : NATURAL_POINTER(no_initialize_t{})  { construct2(wd32range, 0, length); }
   //string_base(const const_ansi_range & ansirange, character_count length) : NATURAL_POINTER(no_initialize_t{})  { construct2(ansirange, start, length); }
   //string_base(const const_wd16_range & wd16range, character_count length) : NATURAL_POINTER(no_initialize_t{})  { construct2(wd16range, start, length); }
   // 
   // 
   //string_base(const const_wd32_range & wd32range, character_count length) : NATURAL_POINTER(no_initialize_t{})  { construct2(wd32range, start, length); }
   template < primitive_block BLOCK >
   string_base(const BLOCK & block) : string_base((const CHARACTER *)block.begin(), (const CHARACTER *)block.end()) {}
   template < character_pointer CHARACTER_POINTER >
   string_base(CHARACTER_POINTER start, character_count length) : ::const_string_range<ITERATOR_TYPE>(no_initialize_t{}) { construct5(start, length); }
   template < character_pointer CHARACTER_POINTER >
   string_base(CHARACTER_POINTER start, CHARACTER_POINTER end) : string_base(start, end-start) { }
   template < character_pointer CHARACTER_POINTER >
   string_base(CHARACTER_POINTER s1, CHARACTER_POINTER e1, CHARACTER_POINTER s2, CHARACTER_POINTER e2);
   template < character_pointer CHARACTER_POINTER >
   string_base(CHARACTER_POINTER start) : string_base(start, string_safe_length(start), e_range_null_terminated) {}
   template < primitive_character CHARACTER2 >
   string_base(const CHARACTER2*start, character_count length, enum_range erange) :
      string_base(::range<const CHARACTER2 *> {start, length, erange}) {}
   //template < typename ITERATOR_TYPE2, int t_size >
   //string_base(const const_string_range_static_array < ITERATOR_TYPE2, t_size >& a);
   //   template < primitive_character CHARACTER2 >
//   string_base(const CHARACTER2 * pszSource, character_count length);
   template < primitive_character CHARACTER2, character_count sizeMaximumLength >
   string_base(const inline_string < CHARACTER2, sizeMaximumLength > & inlinestring) :
      string_base(inlinestring.begin(), inlinestring.end())
   { }
   //   string_base(const ::ansi_character * pansichar, character_count length);
      //string_base(::str < iterator > str) : string_base((const_iterator)str.begin(), (const_iterator)str.end()) {}
      //string_base(::str < const_iterator > str) : string_base(str.begin(), str.end()) {}
      //string_base(::block block) : string_base((const_iterator)block.begin(), (const_iterator)block.end()) {}
      //string_base(const string_base & str);
       //string_base(const ::wd16_character * pwd16char);
   //   string_base(const ::wd16_character * pwd16char, character_count length);
      //string_base(const ::wd32_character * pwd32char);
   //   string_base(const ::wd32_character * pwd32char, character_count length);
   //   string_base(const ::wd32_character * pwd32char, character_count length, character_count pos) : string_base(pwd32char + pos, length) { }
      //template < primitive_character CHARACTER2 >
   string_base(const_iterator begin, const_iterator end) : string_base(begin, end - begin) { }
   //string_base(const string_base & str) : string_base(str, 0, str.size()) { }
   //string_base(const string_base & str, character_count length) : string_base(str, 0, length) { }
   //string_base(const string_base & str, character_count length);
//   template < primitive_character CHARACTER2 >
//   string_base(const ::range < const CHARACTER2 * > & strSource) : string_base(strSource, 0, strSource.size()) {}
//   template < primitive_character CHARACTER2 >
//   string_base(const ::range < const CHARACTER2 * > & strSource, character_count length) : string_base(strSource, 0, minimum(strSource.size(), length)) {}
//   template < primitive_character CHARACTER2 >
//   string_base(const ::range < const CHARACTER2 * > & strSource, character_count length);
   //string_base(const simple_ansistring& simpleansistr);
   //string_base(const simple_wd16string& simplewd16str);
   //string_base(const simple_wd32string& simplewd32str);
   //template < other_primitive_character < typename string_base < ITERATOR_TYPE >::CHARACTER > OTHER_CHARACTER >
   template < typename OTHER_CHARACTER >
   string_base(OTHER_CHARACTER chSrc, character_count repeat = 1)
    requires other_primitive_character < OTHER_CHARACTER, CHARACTER > ;
   string_base(CHARACTER chSrc, character_count repeat = 1);
   //string_base(::ansi_character ansich) : string_base(&ansich, 1) {}
   //string_base(::wd16_character wd16ch) : string_base(&wd16ch, 1) {}
   //string_base(::wd32_character wd32ch) : string_base(&wd32ch, 1) {}
   //string_base(const ::string & cstr) :NATURAL_POINTER(no_initialize_t{}) { construct10(str); }
   //string_base(const ::scoped_wstring & scopedwstr) :NATURAL_POINTER(no_initialize_t{}) { construct10(scopedwstr); }
#if defined(__STD_FORMAT__)
   string_base(const ::std::string & str) : string_base(str.c_str()) { }
#endif
   string_base(const ::atom & atom);
   string_base(const ::payload & payload);
   string_base(const ::property & property);
   ////template < has_as_string HAS_AS_STRING >
   ////string_base(const HAS_AS_STRING & has_as_string) : string_base(has_as_string.as_string()) {}
   inline ~string_base() 
   {

      destroy();

   }


   inline void __destroy()
   {

      auto pbasedata = this->base_data_from_data(this->m_begin);

      this->base_data_release(pbasedata);

   }



   inline void _destroy()
   {

      if (this->is_string() && ::is_set(this->m_begin))
      {

         __destroy();

      }

   }

   
   inline void destroy()
   {

      this->_destroy();

      this->m_begin = nullptr;

      this->m_end = nullptr;

      this->m_erange = e_range_none;

   }



   const ::block as_block() const { return { (unsigned char *)this->begin(), this->character_count_in_bytes() }; }

   static consteval bool is_null_terminated() { return true; }

   void default_construct()
   {

      //NATURAL_POINTER::natural_pointer_default_construct();

      auto pbasedata = this->base_data_default_data();

      //if (this->m_begin != pbasedata->c_data())
      //{

         this->m_begin = pbasedata->c_data();
         this->m_end = pbasedata->c_data();
         this->m_erange = e_range_string_literal;

      //}


   }


   /*void construct(typename NATURAL_POINTER::BASE_DATA * pNew)
   {

      NATURAL_POINTER::create_assign_natural_meta_data(pNew);

   }*/


   void construct1(const string_base& str);


   //template < typename RANGE >
   //void construct10(const RANGE& range) requires 
   //   ::std::is_base_of_v < ::range < const typename string_base < ITERATOR_TYPE >::CHARACTER* >, RANGE >
   //   && !
   //   (::std::is_base_of_v < string_base < ITERATOR_TYPE >, RANGE >
   //      || ::std::is_same_v < string_base < ITERATOR_TYPE >, RANGE >)
   template < typename RANGE >
   void construct10(const RANGE& range)
   {

      if (range.m_erange & e_range_string)
      {

         this->construct1(*(const string_base*)&range);

      }
      else if (range.m_erange & e_range_string_literal)
      {

         this->m_begin = range.m_begin;
         this->m_end = range.m_end;
         this->m_erange = range.m_erange;

      }
      else
      {

         this->construct5(range.data(), range.size());

      }

   }


   //template < other_primitive_character < typename string_base < ITERATOR_TYPE >::CHARACTER > OTHER_CHARACTER >

   template < typename OTHER_CHARACTER >
   void construct20(const ::range < const OTHER_CHARACTER* >& range)
    requires other_primitive_character < OTHER_CHARACTER, CHARACTER > ;


   inline void construct1(const ITERATOR_TYPE psz, character_count length);

   inline void construct2(const ::range < const CHARACTER * > & range);


   inline void construct5(ITERATOR_TYPE pSrc, character_count length);

   template < typename OTHER_CHARACTER_POINTER >
   inline void construct5(OTHER_CHARACTER_POINTER pSrc, character_count length)
    requires other_character_pointer < OTHER_CHARACTER_POINTER, ITERATOR_TYPE > ;

   //template < primitive_character CHARACTER2 >
    //   //inline void construct10(const ::range < const CHARACTER2 * > & range);

    //template < other_primitive_character < typename string_base < ITERATOR_TYPE >::CHARACTER > OTHER_CHARACTER >
   template < typename OTHER_CHARACTER >
   inline void construct20(const OTHER_CHARACTER * psz, character_count length, enum_range erange)
    requires other_primitive_character < OTHER_CHARACTER, CHARACTER >;

   //template < primitive_character CHARACTER2 >
   //inline void construct40(const CHARACTER2* s1, character_count n1, const CHARACTER2* s2, character_count n2);



   template < typename RANGE1, typename RANGE2 >
   void construct40(const RANGE1& range1, const RANGE2& range2);

   //   template < primitive_character CHARACTER2 >
//   inline void construct2(const ::range < const CHARACTER2 * > & str);
//   template < primitive_character CHARACTER2 >
//   inline void construct2(const ::range < const CHARACTER2 * > & str);


   template < primitive_character CHARACTER2 >
   character_count start_count_length(character_count & start, character_count & count, const CHARACTER2 * pszSource);
   //void start_count(character_count & start, character_count & count, character_count length);

   inline const string_base & to_string() const { return *this; }

   
   inline const CHARACTER *c_str() const { return this->data(); }

   inline const CHARACTER *c_str_for_printf() const { return this->data(); }


   using const_string_range<ITERATOR_TYPE>::begin;
   using const_string_range<ITERATOR_TYPE>::end;

   
   this_iterator & begin(this_iterator begin)
   {

      return erase_beginning(begin);

   }

   
   this_iterator & end(this_iterator end)
   {

      return truncate(end);

   }


   bool contains_erase(const SCOPED_STRING& scopedstr)
   {

      if (scopedstr.is_empty())
      {

         return true;

      }


      bool bContains = false;

      while (true)
      {

         auto p = this->find(scopedstr);

         if (::is_null(p))
         {

            return bContains;

         }

         bContains = true;

         this->erase(p, scopedstr.size());

      }

   }

   
   //#if OSBIT == 64
   //   inline const CHARACTER & operator [](int i) const { return this->data()[i]; }
   //#endif



   //inline operator const CONST_STRING_RANGE & () const noexcept { return this->data(); }

//#if defined(UNIVERSAL_WINDOWS)
   //inline operator String ^ () const { return ref __allocate< String(wd16_string >(*this)); }
//#endif

   string_base to_string_base() const { return *this; }
   const BASE_RANGE & to_string_base() { return *this; }

   using BASE_RANGE::operator ==;
   using BASE_RANGE::operator <=>;

   bool operator==(const string_base & str) const { return this->equals(str); }
   ::std::strong_ordering operator<=>(const string_base & str) const { return this->order(str); }

   
   //template < typename T >
   //string_base & operator << (const T & t)
   //{

   //   assign(t);

   //   return *this;

   //}


   //string_base & operator = (const string_base & str);
//   {
//      return *this;
//   }
//   string_base & operator = (const wd16_string & str)
//   {
//      if constexpr (sizeof(CHARACTER) == sizeof(wd16_character))
//      {
//         NATURAL_POINTER::operator=(str);
//      }
//      else
//      {
//         assign(str);
//      }
//      return *this;
//   }
//   string_base & operator = (const wd32_string & str)
//   {
//      if constexpr (sizeof(CHARACTER) == sizeof(wd32_character))
//      {
//         NATURAL_POINTER::operator=(str);
//      }
//      else
//      {
//         assign(str);
//      }
//      return *this;
//   }
//   string_base & operator = (string_base && string_base) { NATURAL_POINTER::operator=(::transfer(string_base)); return *this; }
   string_base & operator = (ansi_character ansich) { assign(ansich); return *this; }
   string_base & operator = (wd16_character wd16ch) { assign(wd16ch); return *this; }
   string_base & operator = (wd32_character wd32ch) { assign(wd32ch); return *this; }
   string_base & operator = (const ansi_character * pansisz) { assign(pansisz); return *this; }
   string_base & operator = (const wd16_character * pwd16sz) { assign(pwd16sz); return *this; }
   string_base & operator = (const wd32_character * pwd32sz) { assign(pwd32sz); return *this; }
   string_base & operator = (const ::atom & atom);
   string_base & operator = (const ::payload & payload);
   string_base & operator = (const ::property & property);
   //template < typename ITERATOR_TYPE2, int t_size >
   //string_base& operator = (const const_string_range_static_array < ITERATOR_TYPE2, t_size >& a) { return assign(a); }
   template < character_count n >
   string_base & operator = (const ::inline_string < ::ansi_character, n > & inlinestring) { assign(inlinestring.begin(), inlinestring.size()); return *this; }
   //   template < has_as_string HAS_AS_STRING >
   //   string_base & operator = (const HAS_AS_STRING & has_as_string)
   //   {
   //
   //      return operator =(has_as_string.as_string());
   //
   //   }

      //string_base & operator = (const ::ansi_character * pansichar);
      //string_base & operator = (const ::wd16_character * pwd16char);
      //string_base & operator = (const ::wd32_character * pwd32char);
      //string_base & operator = (const natural_ansistring & ansistr);
      //string_base & operator = (const natural_wd16string & wd16str);
      //string_base & operator = (const natural_wd32string & wd32str);
   string_base & operator = (const const_ansi_range & ansirange) {assign_range(ansirange); return *this;}
   string_base & operator = (const const_wd16_range & wd16range) {assign_range(wd16range); return *this;}
   string_base & operator = (const const_wd32_range & wd32range) {assign_range(wd32range); return *this;}
   string_base & operator = (const ansi_string & ansistr) { assign_range(ansistr); return *this;}
   string_base & operator = (const wd16_string & wd16str) { assign_range(wd16str); return *this;}
   string_base & operator = (const wd32_string & wd32str) { assign_range(wd32str); return *this;}
   string_base & operator = (string_base && str) { assign_range(::transfer(str)); return *this; }

   template < primitive_block BLOCK >
   string_base & operator = (const BLOCK & block) { assign((const CHARACTER *)block.begin(), (const CHARACTER *)block.end()); return *this; }
      //template < primitive_character CHARACTER2 >
      //string_base & operator = (const ::range < const CHARACTER2 * > & str);
      //string_base & operator = (string_base && str);
   string_base & operator = (const ::inline_number_string & inline_number_string) {assign(inline_number_string.begin(), inline_number_string.end()); return *this;}
   string_base & operator = (const scoped_ansi_string & ansistr);
   string_base & operator = (const scoped_wd16_string & wd16str);
   string_base & operator = (const scoped_wd32_string & wd32str);
#ifdef __STD_FORMAT__
   string_base& operator = (const ::std::string &str) { operator =(str.c_str()); return *this; }
#endif
      //string_base & operator = (const string_base & str);
      //string_base & operator = (const string_base & str);
      //string_base & operator = (::ansi_character ansich);
      //string_base & operator = (::wd16_character wd16ch);
   //   string_base & operator = (::wd32_character wd32ch);
   //#ifdef WINDOWS
     // string_base & operator = (const USHORT * pshSrc) { return operator=((const ::wd16_character *)pshSrc); }
   //#endif
   //#ifdef UNIVERSAL_WINDOWS
     // string_base& operator = (String^& str) { return operator=(str->Begin()); }
   //#endif
      //string_base & operator = (const ::atom & atom);
      //string_base & operator = (const ::payload & payload);
      //string_base & operator = (const ::property & property);

   //   template < int t_nSize >
     // inline string_base & operator=(const static_string<CHARACTER, t_nSize > & ansistrSrc);

      //template < typename TYPE >
      //inline string_base & operator=(const TYPE & t);

      // maybe it doesn't because of ambiguity with global
      // += operators... (in all compilers MSVC++, LLVM, GCC...)
      //template < typename TYPE >
      //string_base& operator += (const TYPE & t);

      // maybe it doesn't because of ambiguity with global
      // += operators... (in all compilers MSVC++, LLVM, GCC...)
      //string_base & operator += (const ::string_base < CHARACTER > & str);


      // so exhaustively implementing them at least
      // for most relevant and proper acme types
   string_base & operator += (const ::ansi_character * psz) { append(psz); return *this; }
   string_base & operator += (const ::wd16_character * psz) { append(psz); return *this; }
   string_base & operator += (const ::wd32_character * psz) { append(psz); return *this; }
   string_base & operator += (::ansi_character ansich) { append(&ansich, 1); return *this; }
   string_base & operator += (::wd16_character wd16ch) { append(&wd16ch, 1); return *this; }
   string_base & operator += (::wd32_character wd32ch) { append(&wd32ch, 1); return *this; }
   string_base & operator += (const ::const_ansi_range & range) { append(range); return *this; }
   string_base & operator += (const ::const_wd16_range & range) { append(range); return *this; }
   string_base & operator += (const ::const_wd32_range & range) { append(range); return *this; }
   string_base & operator += (const inline_number_string & inlinenumberstring) { append((const ::const_ansi_range &)inlinenumberstring); return *this; }
   string_base & operator += (const ::atom & atom);
   string_base & operator += (const ::payload & payload);
   string_base & operator += (const ::property & property);
   //template < typename ITERATOR_TYPE2, int t_size >
   //string_base& operator += (const const_string_range_static_array < ITERATOR_TYPE2, t_size >& a) { return append(a); }
#ifdef __STD_FORMAT__
   string_base& operator += (const ::std::string& str) { operator +=(str.c_str()); return *this; }
#endif
//   template < has_as_string HAS_AS_STRING >
//   string_base & operator += (const HAS_AS_STRING & has_as_string) { return operator +=(has_as_string.as_string()); }


//   template < int t_nSize >
//   inline string_base & operator +=(const static_string<CHARACTER, t_nSize > & ansistrSrc);
//
//   template < typename TYPE >
//   inline string_base & operator +=(const TYPE & t);
//

//   template < primitive_character CHARACTER2 >
//   string_base operator + (const CHARACTER2 * psz) const { auto str = *this; str.append(psz); return ::transfer(str); }


    // maybe it doesn't because of ambiguity with global
   // + operators... (in all compilers MSVC++, LLVM, GCC...)
   //template < typename TYPE >
   //inline string_base operator +(const TYPE & t) const;

   // maybe it doesn't because of ambiguity with global
   // + operators... (in all compilers MSVC++, LLVM, GCC...)
   //inline string_base operator +(const ::string_base < CHARACTER > & str) const;

   // so exhaustively implementing them at least
   // for most relevant and proper acme types
   //string_base operator + (::const_ansi_range ansirange) const;
   //string_base operator + (::const_wd16_range wd16range) const;
   //string_base operator + (::const_wd32_range wd32range) const;
   //string_base operator + (const ansi_string & ansistr) const;
   //string_base operator + (const wd16_string & wd16str)  const;
   //string_base operator + (const wd32_string & wd32str)  const;
   //string_base operator + (const inline_number_string & inlinenumberstring) const;
   //string_base operator + (::ansi_character ansich)  const;
   //string_base operator + (::wd16_character wd16ch)  const;
   //string_base operator + (::wd32_character wd32ch)  const;
   //template < primitive_character CHARACTER2 >
   //string_base operator + (const array_range < CHARACTER2 > & block)  const { return *this + string_base(block); }


   //template < primitive_payload PAYLOAD >
   //string_base operator + (const PAYLOAD & payload) const { return *this + payload.as_string(); }

   //template < primitive_atom ATOM >
   //string_base operator + (const ATOM & atom) const { return *this + atom.as_string(); }


//   template < typename TYPE >
//   inline string_base & operator /=(const TYPE & t)
//      //  template < typename TYPE >
//     //inline string_base & operator /=(const ::string_base < CHARACTER > & str)
//   {
//
//      string_base strRight(t);
//
//      trim_right(string_base("\\/"_ansi));
//
//      strRight.trim_left(string_base("\\/"_ansi));
//
//      return this->operator += ("/"_ansi + strRight);
//
//   }



   string_base& surround(const SCOPED_STRING& scopedstr);

   string_base& surround(const SCOPED_STRING& scopedstrLeft, const SCOPED_STRING& scopedstrRight);

   string_base& double_quote(bool bEscape = false);

   string_base& single_quote(bool bEscape = false);

//   template < typename TYPE >
//   inline string_base operator /(const TYPE & t) const
//      //inline string_base operator /(const ::string_base < CHARACTER > & str) const
//   {
//
//      string_base strRight(t);
//
//      string_base str(*this);
//
//      str /= strRight;
//
//      return str;
//
//   }


   template < typed_character_range < CHARACTER > TYPED_CHARACTER_RANGE >
   inline string_base & assign_range(const TYPED_CHARACTER_RANGE & range)
   {

      if((::range<const CHARACTER *>*)(this) != (::range<const CHARACTER *>*)(&range))
      {

         BASE_DATA* pdata;

         if (this->m_erange & e_range_string)
         {

            pdata = BASE_DATA::base_data_from_data(this->m_begin);

            //this->__destroy();

         }
         else
         {

            pdata = nullptr;

         }

         construct10(range);

         if (pdata)
         {

            if (pdata->data() != this->begin())
            {

               this->base_data_release(pdata);

            }

         }

      }

      return *this;

   }


   template < typed_character_range < CHARACTER > TYPED_CHARACTER_RANGE >
   inline string_base & assign_range(TYPED_CHARACTER_RANGE && range)
   {

      if((::range<const CHARACTER *>*)(this) != (::range<const CHARACTER *>*)(&range))
      {

         if (this->m_erange & e_range_string)
         {

            this->__destroy();

         }

         this->m_begin = range.m_begin;
         this->m_end = range.m_end;
         this->m_erange = range.m_erange;

         range.m_begin = nullptr;
         range.m_end = nullptr;
         range.m_erange = e_range_none;

      }

      return *this;

   }
   template < other_character_range < CHARACTER > OTHER_CHARACTER_RANGE >
   inline string_base & assign_range(const OTHER_CHARACTER_RANGE & range)
   {

      this->assign(range.m_begin, range.m_end);

      return *this;

   }



   template < other_character_range < CHARACTER > OTHER_CHARACTER_RANGE >
   inline string_base & assign_range(OTHER_CHARACTER_RANGE && range)
   {

      this->assign(range.m_begin, range.m_end);

      range.m_begin = nullptr;
      range.m_end = nullptr;
      range.m_erange = e_range_none;

      return *this;

   }


   template < primitive_block BLOCK >
   inline string_base & assign(const BLOCK & block) { return assign((const CHARACTER *)block.data(),(const CHARACTER *) block.end()); }

   //   template < primitive_character CHARACTER2 >
   //   inline string_base& assign(const ::range < const CHARACTER2 * > & str);
      //inline string_base & assign(const ansi_string & ansistr);
      //inline string_base & assign(const wd16_string & wd16str);
      //inline string_base & assign(const wd32_string & wd32str);
      //inline string_base & assign(const ::ansi_character * pansiszSrc);
      //inline string_base & assign(const ::wd16_character * pwd16szSrc);
      //inline string_base & assign(const ::wd32_character * pwd32szSrc);
      //inline string_base & assign(::ansi_character ansich);
      //inline string_base & assign(::wd16_character wd16ch);
      //inline string_base & assign(::wd32_character wd32ch);


   inline string_base& assign(const_iterator start)
   {

      return assign(start, string_safe_length(start));

   }


   inline string_base& assign(const_iterator start, const_iterator end)
   {

      return assign(start, end - start);

   }

   template < primitive_character CHARACTER2 >
   inline string_base & assign(const CHARACTER2 * start, const CHARACTER2 * end);

   template < primitive_character CHARACTER2 >
   inline string_base & assign(const CHARACTER2 * pszSrc, character_count length);


   template < primitive_character CHARACTER2 >
   inline string_base & assign(const CHARACTER2 * pszSrc)
   {

      return assign(pszSrc, string_safe_length(pszSrc));

   }


   //inline string_base& assign(const wd16_string& wd16str);
   //inline string_base& assign(const wd32_string& wd32str);
//   template < primitive_character CHARACTER2 >
//   inline string_base & assign(const CHARACTER2 * pszSrc, character_count length)
//   {
//      return assign(pszSrc, 0, length);
//   }
   //template < primitive_block BLOCK >
   //inline string_base& assign(const BLOCK & pszSrc, character_count length);
   template < primitive_character CHARACTER2 >
   inline string_base & _assign(const CHARACTER2 * pszSrc, character_count length);
   //inline string_base& assign(const ::wd16_character* pwd16szSrc, character_count length);
   //inline string_base& assign(const ::wd32_character* pwd32szSrc, character_count length);
   template < primitive_character CHARACTER2 >
   inline string_base & assign(CHARACTER2 chSrc, character_count repeat = 1);
   //   inline string_base & assign(::ansi_character ansich, character_count repeat);
   //   inline string_base & assign(::wd16_character wd16ch, character_count repeat);
   //   inline string_base & assign(::wd32_character wd32ch, character_count repeat);

   //template <class InputIterator>
   //inline string_base & assign(InputIterator first, InputIterator last);

   //template < int t_nSize >
   //inline string_base & assign(const static_string<CHARACTER, t_nSize > & ansistrSrc);


   //template < int t_size >
   //inline string_base & assign(const const_string_range_static_array< const CHARACTER *, t_size > & a);

   //template < other_primitive_character < typename string_base < ITERATOR_TYPE >::CHARACTER > OTHER_CHARACTER, int t_size >
   //inline string_base & assign(const const_string_range_static_array< const OTHER_CHARACTER *, t_size > & a);






   inline string_base & append(character_count length, CHARACTER ch);
   template < primitive_character CHARACTER2 >
   inline string_base & append_character_array(const CHARACTER2 * psz, character_count length)
   { auto pszEnd = psz + length; if(*(pszEnd - 1) == 0) pszEnd--; append(psz, pszEnd - psz); }

   inline string_base & append_character(::wd32_character wch);
   inline string_base & append_character(::ansi_character ch);
   inline string_base & append_character(::wd16_character wch);


   //inline string_base & append(const ::const_ansi_range & range);
   //inline string_base & append(const ::const_wd16_range & range);
   //inline string_base & append(const ::const_wd32_range & range);


   inline string_base& append(const ::range < ITERATOR_TYPE >& range){ _append(range.m_begin, range.size());  return *this; }


   template < typename OTHER_CHARACTER >
   inline string_base& append(const ::range < const OTHER_CHARACTER* >& range)
    requires other_primitive_character < OTHER_CHARACTER, CHARACTER >
   {_append(range.m_begin, range.size()); return *this; }
   
   
   //inline string_base & append(const ::ansi_character * psz) { return _append(psz, string_safe_length(psz)); }
   //inline string_base & append(const ::wd16_character * psz) { return _append(psz, string_safe_length(psz)); }
   //inline string_base & append(const ::wd32_character * psz) { return _append(psz, string_safe_length(psz)); }

   inline string_base& append(ITERATOR_TYPE psz) { return _append(psz, string_safe_length(psz)); }

   template < typename OTHER_CHARACTER >
   inline string_base& append(const OTHER_CHARACTER * psz)
    requires other_primitive_character < OTHER_CHARACTER, CHARACTER >
   { return _append(psz, string_safe_length(psz)); }


   //inline string_base & append(const ::ansi_character * psz, character_count size) { return _append(psz, size); }
   //inline string_base & append(const ::wd16_character * psz, character_count size) { return _append(psz, size); }
   //inline string_base & append(const ::wd32_character * psz, character_count size) { return _append(psz, size); }


   inline string_base& append(const CHARACTER * psz, character_count size) { return _append(psz, size); }

   template < typename OTHER_CHARACTER >
   inline string_base& append(const OTHER_CHARACTER* psz, character_count size)
    requires other_primitive_character < OTHER_CHARACTER, CHARACTER >{ return _append(psz, size); }


   inline string_base < ITERATOR_TYPE > & _append(const CHARACTER * pszSrc, character_count count);

   template < typename OTHER_CHARACTER >
   inline string_base < ITERATOR_TYPE >& _append(const OTHER_CHARACTER * pszSrc, character_count count)
    requires other_primitive_character < OTHER_CHARACTER, CHARACTER >;

   //template <int t_size >
   //inline string_base < ITERATOR_TYPE > & append(const const_string_range_static_array < ITERATOR_TYPE, t_size > & a);

   //template <other_primitive_character<typename string_base < ITERATOR_TYPE >::CHARACTER> CHARACTER2, int t_size >
   //inline string_base < ITERATOR_TYPE > & append(const const_string_range_static_array < const CHARACTER2 *, t_size > & a);

   //inline string_base & append(const ::wd16_character * pszSrc);
   //inline string_base & append(const ::wd16_character * pszSrc, character_count nLength);
   //inline string_base & append(const wd16_string & ansistrSrc);

   //inline string_base & append(const ::wd32_character * pszSrc);
   //inline string_base & append(const ::wd32_character * pszSrc, character_count nLength);
   //inline string_base & append(const wd32_string & ansistrSrc);

   //template < int t_size >
   //inline string_base & append(const const_string_range_static_array< const CHARACTER *, t_size > & a);

   //template < other_primitive_character < typename string_base < ITERATOR_TYPE >::CHARACTER > OTHER_CHARACTER, int t_size >
   //inline string_base & append(const const_string_range_static_array< const OTHER_CHARACTER *, t_size > & a);
   inline string_base & append(const ::atom & atom);
   inline string_base & append(const ::payload & payload);
   inline string_base & append(const ::property & property);


   inline string_base & concatenate_with_separator(const SCOPED_STRING & scopedstrSeparator, const SCOPED_STRING & scopedstr);


   inline void empty()
   {

      if (this->is_string())
      {

         this->base_data_release(this->base_data_from_data(this->m_begin));

      }

      default_construct();

      //}
      //else
      //{


      //}

   }


   //inline CHARACTER * get_buffer(bool bPreserve = false)
   //{

   //   auto p = this->metadata();

   //   ASSERT(p->m_countReference >= 1);

   //   if (p->natural_is_shared())
   //   {

   //      fork_string(p->character_count(), bPreserve);

   //   }

   //   return (CHARACTER *) this->data();

   //}


   //template < bool t_bPreserve >
   //inline CHARACTER * _create_string(character_count character_count)
   //{

   //   auto pNew = this->base_data_create(character_count);

   //   auto pbuffer = pNew->data();

   //   if constexpr (t_bPreserve)
   //   {

   //      auto s = this->size();

   //      if (s > 0)
   //      {

   //         ::memory_copy(pbuffer, this->m_begin, minimum(s, character_count) * sizeof(CHARACTER));

   //      }

   //   }

   //   this->m_begin = new_begin;

   //   this->m_end = new_begin + character_count;

   //   this->set_string_flag();

   //   return new_begin;

   //}


   inline CHARACTER* construct_string(character_count character_count)
   {

      auto pbasedata = this->base_data_create(character_count + 1);

      auto p = pbasedata->data();

      this->m_begin = p;

      this->m_end = p + character_count;

      this->m_erange = e_range_string | e_range_null_terminated;

      return p;

   }


   template < bool t_bPreserve = false>
   inline CHARACTER * get_buffer(character_count characterCount = -1)
   {

      auto p = (CHARACTER *) this->m_begin;

      if (this->m_erange & e_range_string)
      {

         auto pbasedata = this->base_data_from_data(this->m_begin);

#ifdef _DEBUG

         if (::is_set(pbasedata) && pbasedata->m_countReference <= 0)
         {

            __what__(1);

         }

#endif

         if (::is_null(pbasedata) || pbasedata->base_data_is_shared() || characterCount > pbasedata->storage_character_count())
         {

            p = fork_string<true, t_bPreserve >(characterCount > 0 ? characterCount : this->size());

         }
         else
         {

            this->m_end = this->m_begin + (characterCount > 0 ? characterCount : this->size());

         }
         //else
         //{

         //   this->metadata()->set_character_count(characterCount);

         //   this->m_end = this->m_begin + characterCount;

         //}

      }
      else
      {

         p = create_string<t_bPreserve>(characterCount);

      }

      return p;

   }


   inline mutable_string_range < CHARACTER * > get_range_buffer(character_count characterCount)
   {

      auto p = get_buffer(characterCount);

      return { p, p + characterCount };

   }


   inline void release_range_buffer(const mutable_string_range < CHARACTER * > & range)
   {
      
      if(range.m_end > (this->m_begin + this->storage_character_count()))
      {
       
         throw_exception(error_invalid_buffer);
         
      }
      
      ::memory_transfer((CHARACTER *) this->m_begin, range.m_begin, range.size());
         
      release_buffer(range.size());

   }


   // inline CHARACTER * defer_get_string_buffer(character_count size, const string_base & str)
   // {

   //    auto p = this->metadata();

   //    ASSERT(p->m_countReference >= 1);

   //    if (::is_null(p) || p->natural_is_shared() || size > p->length() || p->contains_data(str))
   //    {

   //       fork_string(size);

   //    }

   //    this->metadata()->set_length(size);

   //    return this->data();

   // }


   inline void get_string(CHARACTER * psz) const noexcept;

//   inline const CHARACTER * get_string() const noexcept { return this->data(); }


   inline bool if_empty_set_to(const string_base & str)
   {

      if (!this->is_empty())
      {

         return false;

      }

      operator =(str);

      return true;

   }


   inline static string_base empty_string() { return string_base(); }

   string_base & release_buffer(character_count nNewLength = -1);

   inline this_iterator & truncate(this_iterator p);
   template < primitive_integral INTEGRAL >
   inline this_iterator & truncate(INTEGRAL count) {return truncate(this->m_begin + count);}

   template < primitive_integral INTEGRAL >
   inline string_base truncated(INTEGRAL count) const
   {

      if (this->length() <= count)
      {

         return *this;

      }

      return this->left(count);

   }

   //string_base right(character_count nCount) const { return *this = BASE_RANGE::right(nCount); }

   //string_base left(character_count count) const { return *this = BASE_RANGE::left(nCount); }

   //string_base left(const_iterator p) const { return *this = BASE_RANGE::left(p); }

   //string_base left_including_any_character_in(const SCOPED_STRING& scopedstrCharSet) const { return *this = BASE_RANGE::left_including_any_character_in(scopedstrCharSet); }

   //string_base left_skipping_any_character_in(const SCOPED_STRING& scopedstrCharSet) const { return *this = BASE_RANGE::left_skipping_any_character_in(scopedstrCharSet); }



   inline this_iterator & erase_beginning(this_iterator p);

   inline void set_at(character_count iChar, CHARACTER ch);


   //inline BASE_DATA * create_meta_data(character_count characterCount)
   //{

   //   auto newNullTerminatedByteCount = null_terminated_character_count_to_byte_length(this->begin(), characterCount);

   //   auto pbasedata = this->_create_meta_data(newNullTerminatedByteCount);

   //   pbasedata->m_countData = characterCount;

   //   return pbasedata;

   //}

   /// draft: all allocation, release and assignment done
   template < bool t_bPreserve >
   inline CHARACTER* create_string(character_count character_count)
   {

      return fork_string< false, t_bPreserve >(character_count);

   }


   /// draft: all allocation, release and assignment done
   template < bool t_bWasString, bool t_bPreserve >
   inline CHARACTER * fork_string(character_count characterCount)
   {

      BASE_DATA* pbasedataOld;

      auto old_size = this->size();

      auto new_size = characterCount;

      auto pold = (CHARACTER * )this->m_begin;

      /// if this string had heap string storage,
      /// checks if old storage can hold new requested size.
      if constexpr (t_bWasString)
      {

         pbasedataOld = this->base_data_from_data(this->m_begin);

         if (::is_set(pbasedataOld) &&
            !pbasedataOld->base_data_is_shared() &&
            new_size <= pbasedataOld->storage_character_count())
         {

            this->m_end = pold + new_size;

            pold[new_size] = CHARACTER{};

            return pold;

         }

      }

      memsize allocationSize = (new_size +1) * sizeof(CHARACTER);

      if constexpr(t_bWasString)
      {

         if (this->m_erange & e_range_buffer && allocationSize >= 16_KiB)
         {

            allocationSize *= 2;

         }

      }

      auto pbasedata = this->base_data_create(allocationSize);

      auto p = pbasedata->data();

      if constexpr (t_bWasString)
      {

         ASSERT(::is_null(pbasedataOld) || pbasedataOld->m_countReference >= 1);

      }

      if (::is_set(pold))
      {

         if constexpr (t_bPreserve)
         {

            auto sizeCopy = minimum(old_size, new_size);

            if (sizeCopy > 0)
            {

               memory_copy((void*)p, pold, sizeCopy * sizeof(CHARACTER));

            }

         }

         if constexpr (t_bWasString)
         {

            this->base_data_release(pbasedataOld);

         }

      }

      this->m_begin = p;

      this->m_end = p + new_size;

      this->m_erange = e_range_string;

      p[new_size] = CHARACTER{};

      return p;

   }


   ///// <summary>
   ///// this version of "create_string"_ansi releases existing string if 
   ///// it is e_range_string and optionally preserves it
   ///// </summary>
   ///// <param name="character_count"_ansi></param>
   ///// <returns></returns>
   ///// 
   //template < bool t_bPreserve = false >
   //CHARACTER * create_string(character_count character_count);
   ///// <summary>
   ///// this version of "create_string"_ansi doesn't release existing string
   ///// </summary>
   ///// <param name="character_count"_ansi></param>
   ///// <returns></returns>
   //CHARACTER * _create_string(character_count character_count);


   //template < bool t_bWasString, bool t_bPreserve >
   //CHARACTER * fork_string(character_count character_count);


   template < bool t_bPreserve >
   CHARACTER * defer_fork_string(character_count character_count)
   {

      if (this->m_erange & e_range_string)
      {

         return fork_string<false, t_bPreserve>(character_count);

      }

      auto pbasedata = this->base_data_from_data(this->m_begin);

      auto p = pbasedata->data();

      if (::is_null(pbasedata) || pbasedata->base_data_is_shared() || character_count > pbasedata->storage_character_count())
      {

         p = fork_string<true, t_bPreserve>(character_count);

      }

      return p;

   }


   //void _fork_string();

   //inline static BASE_DATA * create_meta_data(character_count characterCount);

   //void prepare_write(character_count nLength)
   //{

   //   auto p = this->metadata();

   //   if (p->natural_is_shared() || nLength >= this->storage_character_count())
   //   {

   //      fork_string(nLength);

   //   }

   //}



   const SCOPED_STRING & if_empty(const SCOPED_STRING & scopedstr) const { return this->is_empty() ? scopedstr : *((const SCOPED_STRING *) this); }
   bool set_if_empty(const SCOPED_STRING & scopedstr) { return this->is_empty() ? (*this = scopedstr, true) : false; }


   void add(CHARACTER ch);



   void reserve(character_count res_arg = 0);


   string_base& erase_end(character_count start) { return this->erase(start, (::character_count)this->index_of(this->end())); }


   string_base & erase(character_count start, character_count count);

   /// erase count characters from start
   string_base & erase(character_count count) { return this->erase((::character_count)0, count); }

   string_base & erase(const_iterator start, character_count count) { return this->erase(this->index_of(start), count); }

   string_base & erase(const_iterator start, const_iterator end = 0)
   {

      if (!end) end = this->end();

      return this->erase(this->index_of(start), this->index_of(end) - this->index_of(start));

   }

   ::collection::count insert(character_count iIndex, CHARACTER ch);

   ::collection::count insert(character_count iIndex, const string_base & str);

   ::collection::count replace_with(CHARACTER charNew, CHARACTER charOld, character_count start = 0);

   template < typename EQUALITY >
   ::collection::count _replace_with(const SCOPED_STRING & scopedstrNew, const SCOPED_STRING & scopedstrOld, character_count start, EQUALITY equality);


   ::collection::count replace_with(const SCOPED_STRING & scopedstrNew, const SCOPED_STRING & scopedstrOld, character_count start = 0)
   {

      return _replace_with(scopedstrNew, scopedstrOld, start, ::comparison::comparison<CHARACTER>());

   }


   ::collection::count case_insensitive_replace_with(const SCOPED_STRING & scopedstrNew, const SCOPED_STRING & scopedstrOld, character_count start = 0)
   {

      return _replace_with(scopedstrNew, scopedstrOld, start, ::comparison::case_insensitive<CHARACTER>());

   }

   ::collection::count replace_with_count(const SCOPED_STRING & scopedstrNew, const SCOPED_STRING & scopedstrOld, character_count iStart = 0);

   ::collection::count replace_with_ci_count(const SCOPED_STRING & scopedstrNew, const SCOPED_STRING & scopedstrOld, character_count iStart = 0);

   ::collection::count find_replace(CHARACTER charOld, CHARACTER charNew, character_count iStart = 0)
   {

      return replace_with(charNew, charOld, iStart);

   }

   ::collection::count find_replace(const SCOPED_STRING & scopedstrOld, const SCOPED_STRING & scopedstrNew, character_count start = 0)
   {

      return _replace_with(scopedstrNew, scopedstrOld, start, comparison::comparison<CHARACTER>());

   }


   ::collection::count case_insensitive_find_replace(const SCOPED_STRING & scopedstrOld, const SCOPED_STRING & scopedstrNew, character_count start = 0)
   {

      return _replace_with(scopedstrNew, scopedstrOld, start, comparison::case_insensitive<CHARACTER>());

   }


   // replace all occurrences of string_base 'pszOld' with string_base 'pszNew'
   //template < raw_pointer_castable < CHARACTER_TYPE > PCHAROLD, raw_pointer_castable < CHARACTER_TYPE > PCHARNEW >
   ::collection::count find_replace_count(const SCOPED_STRING & scopedstrOld, const SCOPED_STRING & scopedstrNew, character_count iStart = 0)
   {

      return replace_with_count(scopedstrNew, scopedstrOld, iStart);

   }


   //template < raw_pointer_castable < CHARACTER_TYPE > PCHAROLD, raw_pointer_castable < CHARACTER_TYPE > PCHARNEW >
   ::collection::count case_insensitive_find_replace_count(const SCOPED_STRING & scopedstrOld, const SCOPED_STRING & scopedstrNew, character_count iStart = 0)
   {

      return replace_with_ci_count(scopedstrNew, scopedstrOld, iStart);

   }


   //// replace all occurrences of character 'chOld' with character 'chNew'
   //character_count xxx_replace(CHARACTER charOld, CHARACTER charNew, character_count iStart = 0);

   //// replace all occurrences of string_base 'pszOld' with string_base 'pszNew'
   //template < raw_pointer_castable < CHARACTER_TYPE > PCHAROLD, raw_pointer_castable < CHARACTER_TYPE > PCHARNEW >
   //character_count xxx_replace(PCHAROLD pcharOld, PCHARNEW pcharNew, character_count iStart = 0);

   //template < raw_pointer_castable < CHARACTER_TYPE > PCHAROLD, raw_pointer_castable < CHARACTER_TYPE > PCHARNEW >
   //character_count case_insensitive_xxx_replace(PCHAROLD pcharOld, PCHARNEW pcharNew, character_count iStart = 0);

   //// replace all occurrences of string_base 'pszOld' with string_base 'pszNew'
   //template < raw_pointer_castable < CHARACTER_TYPE > PCHAROLD, raw_pointer_castable < CHARACTER_TYPE > PCHARNEW >
   //::collection::count xxx_replace_count(PCHAROLD pcharOld, PCHARNEW pcharNew, character_count iStart = 0);

   //template < raw_pointer_castable < CHARACTER_TYPE > PCHAROLD, raw_pointer_castable < CHARACTER_TYPE > PCHARNEW >
   //::collection::count xxx_replace_ci_count(PCHAROLD pcharOld, PCHARNEW pcharNew, character_count iStart = 0);

   //::collection::count utf8_replace(const string_base &scopedstrOld, const string_base &scopedstrNew, character_count iStart = 0);

   string_base & replace(const_iterator start, const_iterator end, const SCOPED_STRING & scopedstr);
   string_base & replace_index(character_count start, character_count end, const SCOPED_STRING & scopedstr)
   {

      return replace(this->begin() + start, this->begin() + end, scopedstr);

   }
   //string_base & replace(character_count iStart, character_count nCount, const SCOPED_STRING & scopedstr, character_count nLen);

   // erase all occurrences of character 'chRemove'
   ::collection::count erase_character(CHARACTER chRemove);

   string_base Tokenize(const SCOPED_STRING & scopedstrTokens, character_count & iStart) const;


   string_base & begins_eat_any_character_in(const SCOPED_STRING & scopedstrCharacters = 0) 
   {

      auto pbegin = this->skip_any_character_in(scopedstrCharacters);

      if(pbegin != this->begin())
      {

         this->erase_beginning(pbegin);

      }

      return *this;

   }


   //character_count get_token(const string_base &strSeparators, character_count pos = -1) const RELEASENOTHROW;
   //character_count get_token(const string_base &strSeparators) const RELEASENOTHROW;
   //character_count get_token(const CHARACTER * pszSeparators, character_count pos = -1) const RELEASENOTHROW;
   //character_count get_token(CHARACTER chSeparator, character_count pos = -1) const RELEASENOTHROW;

   //character_count _get_token(const string_base &strSeparators, character_count pos = -1) const RELEASENOTHROW;
   //character_count _get_token(const string_base &strSeparators) const RELEASENOTHROW;
   //character_count _get_token(const CHARACTER * pszSeparators, character_count pos = -1) const RELEASENOTHROW;
   //character_count _get_token(CHARACTER chSeparator, character_count pos = -1) const RELEASENOTHROW;


   string_base intersection(const SCOPED_STRING & scopedstr) const;


   string_base ansistr() const
   {
      return *this;
   }


   //const CHARACTER * begin() const
   //{

   //   return data();

   //}


   //const CHARACTER * end() const
   //{

   //   return data() + size();

   //}


   unicode_iterator < CHARACTER > unicode_begin() const
   {

      return this->data();

   }


   unicode_iterator < CHARACTER > unicode_end() const
   {

      return this->data() + this->size();

   }

   template < primitive_integral START >
   string_base unicode_substr(START start) const
   {

      return { (this->unicode_begin() + start).c_str(), this->end()};

   }


   template < primitive_integral START, primitive_integral COUNT >
   string_base unicode_substr(START start, COUNT count) const
   {

      return { (this->unicode_begin() + start).c_str(), (this->unicode_begin() + start + count).c_str()};

   }


   constexpr bool starts_with_word(const SCOPED_STRING& range, const ::get_word_function < ITERATOR_TYPE > & getwordfunction) const
   {

      return getwordfunction(*this, nullptr).order(range) == 0;


   }


   string_base get_word(const SCOPED_STRING& sSep, ITERATOR_TYPE * ppend = nullptr) const
   {

      return ::string_get_word_with_separator_list((const SCOPED_STRING &)*this, sSep, ppend);

   }


   constexpr bool case_insensitive_starts_with_word(const SCOPED_STRING& range, const get_word_function < ITERATOR_TYPE > & getwordfunction) const
   {

      return get_word(*this).case_insensitive_order(range) == 0;

   }


   constexpr bool starts_with_word(const SCOPED_STRING& range) const
   {

      return this->starts_with_word(range, &::string_get_word_separated_by_spaces < ITERATOR_TYPE >);

   }


   constexpr bool case_insensitive_starts_with_word(const SCOPED_STRING& range) const
   {

      return case_insensitive_starts_with_word(range, &::string_get_word_separated_by_spaces < ITERATOR_TYPE >);

   }


   //inline bool begins(const CHARACTER * pszPrefix) const;

   //inline bool begins(const string_base &strPrefix) const;
   //inline bool ends(const string_base &strSuffix) const;

   inline bool begins_eat(const SCOPED_STRING & scopedstrPrefix);
   inline bool ends_eat(const SCOPED_STRING & scopedstrSuffix);

   inline bool case_insensitive_begins_eat(const SCOPED_STRING & scopedstrPrefix);
   inline bool case_insensitive_ends_eat(const SCOPED_STRING & scopedstrSuffix);

   inline bool begins_erase_get_erased(string_base& strErased, const SCOPED_STRING& scopedstr);
   inline bool ends_erase_get_erased(string_base& strErased, const SCOPED_STRING& scopedstr);
   
   inline bool begins_replace(const SCOPED_STRING & scopedstrNewPrefix, const SCOPED_STRING & scopedstrPrefix);

   inline bool case_insensitive_begins_replace(const SCOPED_STRING & scopedstrNewPrefix, const SCOPED_STRING & scopedstrPrefix);

   inline bool begins_erase_get_remainder(string_base & strRemainder, const SCOPED_STRING & scopedstr) const;
   inline bool ends_erase_get_remainder(string_base & strRemainder, const SCOPED_STRING & scopedstr) const;

   inline bool case_insensitive_begins_erase_get_remainder(string_base & strRemainder, const SCOPED_STRING & scopedstr) const;
   inline bool case_insensitive_ends_erase_get_remainder(string_base & strRemainder, const SCOPED_STRING & scopedstr) const;

   inline string_base begins_bitten(const SCOPED_STRING & scopedstr) const;
   inline string_base ends_bitten(const SCOPED_STRING & scopedstr) const;

   inline string_base case_insensitive_begins_bitten(const SCOPED_STRING & scopedstr) const;
   inline string_base case_insensitive_ends_bitten(const SCOPED_STRING & scopedstr) const;

   inline string_base case_insensitive_begins_eaten(const SCOPED_STRING & scopedstr) const;
   inline string_base case_insensitive_ends_eaten(const SCOPED_STRING & scopedstr) const;

   inline string_base & ensure_prefix(const SCOPED_STRING & scopedstrPrefix);
   inline string_base & case_insensitive_ensure_prefix(const SCOPED_STRING & scopedstrPrefix);

   inline string_base & ensure_suffix(const SCOPED_STRING & scopedstrSuffix);
   inline string_base & case_insensitive_ensure_suffix(const SCOPED_STRING & scopedstrSuffix);

   inline string_base defer_prefixed(const SCOPED_STRING & scopedstrPrefix) const;
   inline string_base case_insensitive_defer_prefixed(const SCOPED_STRING & scopedstrPrefix) const;

   inline string_base defer_suffixed(const SCOPED_STRING & scopedstrSuffix) const;
   inline string_base case_insensitive_defer_suffixed(const SCOPED_STRING & scopedstrSuffix) const;

   //inline bool begins(const string_base &str) const;
   //inline bool ends(const string_base &str) const;

   //inline bool case_insensitive_begins(const string_base &str) const;
   //inline bool case_insensitive_ends(const string_base &str) const;

   //inline bool begins_eat(const string_base &str);
   //inline bool ends_eat(const string_base &str);

   //inline bool case_insensitive_begins_eat(const string_base &str);
   //inline bool case_insensitive_ends_eat(const string_base &str);

   //inline string_base& ensure_prefix(const string_base &strPrefix);
   //inline string_base& case_insensitive_ensure_prefix(const string_base &strPrefix);

   //inline string_base& ensure_ends(const string_base &strSuffix);
   //inline string_base& case_insensitive_ensure_ends(const string_base &strSuffix);

   bool eat_before(string_base & strBefore, const SCOPED_STRING & strSeparator, bool bEatEverythingIfNotFound = false);
   bool eat_before_let_separator(string_base & strBefore, const SCOPED_STRING & strSeparator, bool bEatEverythingIfNotFound = false);

   // manipulation

   // Convert the string_base to uppercase
   string_base & make_upper();

   // Convert the string_base to lowercase
   string_base & make_lower();

   // Reverse the string_base
   string_base & MakeReverse();

   string_base lower() const;

   string_base upper() const;


   // Convert the string_base to uppercase
   string_base uppered() const;

   //// Convert the string_base to lowercase
   //string_base lowered() const;

   // Convert the string_base to lowercase
   string_base reversed() const;

   // trimming

   // erase all trailing whitespace
   string_base & trim_right();

   // erase all leading whitespace
   string_base & trim_left();

   // erase all leading and trailing whitespace
   string_base & trim();

   // erase all leading and trailing occurrences of character 'chTarget'
   string_base & trim(CHARACTER chTarget);

   // erase all leading and trailing occurrences of any of the characters in the string_base 'pszTargets'
   string_base & trim(const SCOPED_STRING & scopedstrTargets);

   // trimming anything (either side)

   // erase all trailing occurrences of character 'chTarget'
   string_base & trim_right(CHARACTER chTarget);

   // erase all trailing occurrences of any of the characters in string_base 'pszTargets'
   ///template < pointer_castable < CHARACTER > PCHAR >
   //string_base & trim_right(PCHAR pcharTargets);
   string_base & trim_right(const SCOPED_STRING & scopedstrTargets);

   // erase all leading occurrences of character 'chTarget'
   string_base & trim_left(CHARACTER chTarget);

   // erase all leading occurrences of any of the characters in string_base 'pszTargets'
   //template < pointer_castable < CHARACTER > PCHAR >
   //string_base& trim_left(PCHAR pchTargets);
   string_base & trim_left(const SCOPED_STRING & scopedstrTargets);


   // erase all trailing whitespace
   string_base right_trimmed() const;

   // erase all leading whitespace
   string_base left_trimmed() const;

   // erase all leading and trailing whitespace
   string_base trimmed() const;

   // erase all leading and trailing occurrences of character 'chTarget'
   string_base trimmed(CHARACTER chTarget) const;

   // erase all leading and trailing occurrences of any of the characters in the string_base 'pszTargets'
   string_base trimmed(const SCOPED_STRING & scopedstrTargets) const;

   // trimming anything (either side)

   // erase all trailing occurrences of character 'chTarget'
   string_base right_trimmed(CHARACTER chTarget) const;

   // erase all trailing occurrences of any of the characters in string_base 'pszTargets'
   string_base right_trimmed(const SCOPED_STRING & scopedstrCharacters) const;

   // erase all leading occurrences of character 'chTarget'
   string_base left_trimmed(CHARACTER chTarget) const;

   // erase all leading occurrences of any of the characters in string_base 'pszTargets'
   string_base left_trimmed(const SCOPED_STRING & strTargets) const;


   bool pair_trim(CHARACTER character1, CHARACTER character2)
   {

      if (this->size() >= 2)
      {

         if (this->first() == character1 && this->last() == character2)
         {

            *this = this->substr(1, length() - 2);

            return true;

         }

      }

      return false;

   }


   string_base & pair_trim_quotes()
   {

      while (pair_trim('\"', '\"') || pair_trim('\'', '\''));

      return *this;

   }


   string_base paired_trim_quotes()
   {

      auto str = *this;

      str.pair_trim_quotes();

      return ::transfer(str);

   }


   //BASE_RANGE substr(const_iterator p) const { return ::transfer(substr(p, -1)); }

   //template < primitive_integral COUNT >
   //BASE_RANGE substr(const_iterator p, COUNT count) const { return ::transfer(substr(p - this->begin(), count)); }

   //template < primitive_integral START >
   //BASE_RANGE substr(START start) const;
   //template < primitive_integral START, primitive_integral COUNT >
   //BASE_RANGE substr(START start, COUNT count) const;
   //template < primitive_integral START >
   //BASE_RANGE substr(START start, const_iterator p) const { return substr(start, (p - this->m_begin) - start); }


   inline memsize storage_size() const
   { 

      if (!(this->m_erange & e_range_string))
      {

         return 0;

      }

      auto pbasedata = this->base_data_from_data(this->m_begin);
      
      return pbasedata->storage_size(); 
      
   }


   inline character_count storage_character_count() const
   {

      if (!(this->m_erange & e_range_string))
      {

         return 0;

      }

      auto s = this->storage_size();

      auto n = null_terminated_byte_length_to_character_count(this->m_begin, s);

      return n;

   }


   inline character_count length() const { return this->m_end - this->m_begin; }
   inline character_count size() const { return this->length(); }
   inline memsize character_count_in_bytes() const;
   inline memsize null_terminated_character_count_in_bytes() const;



   string_base & formatf(const CHARACTER * pszFormat, ...);

   string_base & formatf_arguments(const CHARACTER * pszFormat, va_list args);

   string_base & append_formatf(const CHARACTER * pszFormat, ...);

   string_base & append_formatf_arguments(const CHARACTER * pszFormat, va_list args);

   
#if defined(__STD_FORMAT__)

   template<typename... Ts>
   string_base & format(const ::std::format_string<Ts...> fmt, Ts&&... args)
   {

      return operator=(std::format(fmt, std::forward<Ts>(args)...));

   }

   template<typename... Ts>
   string_base & append_format(const std::format_string<Ts...> fmt, Ts&&... args)
   {

      return this->operator +=(std::format(fmt, std::forward<Ts>(args)...));

   }

   
#endif

   //void FormatMessage(const CHARACTER * pszFormat, ...);




   // set the string_base to the value of environment ::payload 'pszVar'
   //bool xxxget_environment_variable(const string_base &strVar);

   // set the string_base to the value of environment ::payload 'pszVar'
   //bool xxxgetenv(const string_base &strVar);

   // Load the string_base from resource 'nID'
   //bool load_string(::particle * pparticle, atom atom);

   // Load the string_base from resource 'nID' in module 'hInstance'
   /*    bool load_string(HINSTANCE hInstance,character_count nID )
   {
   const STRINGRESOURCEIMAGE* pImage = gen_GetStringResourceImage( hInstance, nID );
   if( pImage == nullptr )
   {
   return( false );
   }

   character_count nLength = str_traits::GetcharLength( pImage->achString, pImage->nLength );
   CHARACTER * pszBuffer = GetBuffer( nLength );
   str_traits::ConvertTochar( pszBuffer, nLength, pImage->achString, pImage->nLength );
   release_buffer( nLength );

   return( true );
   }*/

   // Load the string_base from resource 'nID' in module 'hInstance', using language 'wLanguageID'
   /*bool load_string(HINSTANCE hInstance,character_count nID,unsigned short wLanguageID )
   {
   const STRINGRESOURCEIMAGE* pImage = gen_GetStringResourceImage( hInstance, nID, wLanguageID );
   if( pImage == nullptr )
   {
   return( false );
   }

   character_count nLength = str_traits::GetcharLength( pImage->achString, pImage->nLength );
   CHARACTER * pszBuffer = GetBuffer( nLength );
   str_traits::ConvertTochar( pszBuffer, nLength, pImage->achString, pImage->nLength );
   release_buffer( nLength );

   return( true );
   }*/

   void resize(character_count n)
   {
      resize(n, '\0');
   }

   void resize(character_count n, CHARACTER c);




   string_base unichar_substr(character_count iFirst) const;
   string_base unichar_substr(character_count iFirst, character_count nCount) const;
   string_base unichar_left(character_count nCount) const;
   string_base unichar_mid(character_count iFirst) const;
   string_base unichar_mid(character_count iFirst, character_count nCount) const;


   //character_count char_get_count(character_count iCharCount) const;
   //ansi_string char_left(character_count nCount) const;
   //ansi_string char_mid(character_count iFirst) const;
   //ansi_string char_mid(character_count iFirst, character_count nCount) const;

   void clear();



   typedef character_count size_type;




};


// For MSVC, but not for GCC?
//inline ::string operator + (const ::string & cstrA, const ::string & cstrB)
//{
//
//   auto str = strA;
//
//   str += strB;
//
//   return str;
//
//}


//inline ::string operator +(const ::string & cstr, const ::const_ansi_range & range)
//{
//
//   auto strResult = str;
//
//   strResult.append(range);
//
//   return ::transfer(strResult);
//
//}


//inline ::string operator + (const ::string & cstr, char ch);

//inline ::string operator +(const ::string & cstr, const ::ansi_character * psz)
//{
//
//   return str + ::string(psz);
//
//}


//template < ::collection::count c >
//inline ::string operator +(const ::string & cstr, const char(&sz)[c]);
//
//
//template < character_count m_sizeMaximumLength >
//inline ::string operator +(const ::string & cstr, const ::inline_string < char, m_sizeMaximumLength > & inlinestring);

//inline ::string operator +(const string & str, const ::string & cstr)
//{
//
//   return ::string(str) + str;
//
//}


//inline ::string operator +(char ch, const ::string & cstr);


// For MSVC, but not for GCC?
//template < ::collection::count c >
//inline ::string operator +(const char(&sz)[c], const ::string & cstr)
//{
//
//   return ::string(sz) + str;
//
//}


//template < ::collection::count c >
//inline ::string operator +(const ::const_ansi_range & str, const char(&sz)[c])
//{
//
//   return ::string(str) + sz;
//
//}


// For MSVC, but not for GCC?
//inline ::string operator +(const ::const_ansi_range & range, const ::string & cstr)
//{
//
//   return ::string(range) + str;
//
//}


//template < primitive_character CHARACTER, typename CHARACTER2 >
//constexpr ::string_base < const CHARACTER * > operator +(CHARACTER ch, ::str < const CHARACTER2 * > str)
//{
//
//   return ::transfer(::string_base < const CHARACTER * >(ch) + ::string_base < const CHARACTER * >(str));
//
//}


//template < primitive_character CHARACTER1, primitive_character CHARACTER2, character_count sizeMaximumLength >
//inline ::string_base < const CHARACTER1 * > operator + (const CHARACTER1 * psz, const inline_string<CHARACTER2, sizeMaximumLength > & inlinestring)
//{
//
//   return ::string_base < const CHARACTER1 * >(psz) + ::string_base < const CHARACTER1 * >(inlinestring);
//
//}
//
//template < primitive_character CHARACTER, primitive_character CHARACTER2 >
//constexpr ::string_base < const CHARACTER * > operator + (::str < const CHARACTER * > str, const CHARACTER2 * psz)
//{
//
//   return ::transfer(::string_base < const CHARACTER * >(str) + ::string_base < const CHARACTER * >(psz));
//
//}


//inline ::wstring operator + (::wstring wstrA, ::wstring wstrB)
//{
//
//   wstrA += wstrB;
//
//   return wstrA;
//
//}


//inline ::wstring operator +(const ::wide_character * pwsz, ::wstring wstr)
//{
//
//   return ::wstring(pwsz) + wstr;
//
//}
//
//
//template < ::collection::count c >
//inline ::wstring operator +(const ::wide_character(&wsz)[c], ::wstring wstr)
//{
//
//   return ::wstring(wsz) + wstr;
//
//}

//
//block::block(const string_base &str)
//   
//{
//   this->m_begin = (unsigned char *)str.m_begin;
//   this->m_end = (unsigned char *) str.m_end;
//
//}


//template < ::collection::count c, character_count m_sizeMaximumLength >
//inline ::string operator +(const char(&sz)[c], const ::inline_string < char, m_sizeMaximumLength > & inlinestring);


//template < ::collection::count c, character_count m_sizeMaximumLength >
//inline ::string operator +(const ::inline_string < char, m_sizeMaximumLength > & inlinestring, const char(&sz)[c]);








template < primitive_character CHARACTER >
class argument_of_struct < ::string_base < const CHARACTER * > >
{
public:

   using type = ::scoped_string_base < const CHARACTER * >;

};




//template < typename ITERATOR_TYPE >
//inline ::string_base < ITERATOR_TYPE > operator + (const string_range < ITERATOR_TYPE > & strA, const string_range < ITERATOR_TYPE > & strB )
//{
//
//   string_base < ITERATOR_TYPE > str;
//
//   auto length = strA.size() + strB.size();
//
//   auto p = str.get_buffer(length);
//
//   ::memory_copy(p, strA, strA.size());
//
//   ::memory_copy(p + strA.size(), strB, strB.size());
//
//   str.release_buffer(length);
//
//   return ::transfer(str);
//
//}


//template < character_count n, typename ITERATOR_TYPE >
//inline ::string_base < ITERATOR_TYPE > operator + (const char (&cha)[n], const string_range < ITERATOR_TYPE > & str)
//{
//
//   return ::transfer(::string_base < ITERATOR_TYPE >(cha) + str);
//
//}


// For MSVC, but not for GCC?
//template < typename ITERATOR_TYPE >
//inline ::string_base < ITERATOR_TYPE > operator + (const char * psz, const string_base < ITERATOR_TYPE > & str)
//{
//
//   return ::transfer(::string_base < ITERATOR_TYPE >(psz) + str);
//
//}



// For MSVC, but not for GCC?
//template < character_count n, typename ITERATOR_TYPE >
//inline ::string_base < ITERATOR_TYPE > operator + (const char(&cha)[n], const string_base < ITERATOR_TYPE > & str)
//{
//
//   return ::transfer(::string_base < ITERATOR_TYPE >(cha) + str);
//
//}



template < primitive_floating FLOATING >
inline ::string as_string(FLOATING f, const ::ansi_character * pszFormat = "%f"_ansi);


inline ::string as_string(const ::block & block)
{
   
   char chNull = '\0';

   auto p = memory_find(block.data(), block.size(), &chNull, 1);

   auto offset = ((char *)p - (char *)block.data());

   if (::is_set(p) && offset < block.size())
   {

      return { (const char *) block.data(), offset };

   }
   else
   {

      return { (const char *) block.data(), block.size() };

   }

}


template < >
inline ::hash32 as_hash32 < const ansi_string & >(const ansi_string & ansistr);


template < >
inline ::hash32 as_hash32 < const wide_string & >(const wide_string & widestr);


template < >
inline ::hash32 as_hash32 < ansi_string >(const ansi_string & ansistr);


template < >
inline ::hash32 as_hash32 < wide_string >(const wide_string & widestr);




//template < typed_range < ::wd16_character * > WD16_RANGE >
//string_base operator + (const WD16_RANGE & range) const { auto str = *this; str.append(range.begin(), range.end()); return ::transfer(str); }
//
//template < typed_range < ::wd32_character * > WD32_RANGE >
//string_base operator + (const WD32_RANGE & range) const { auto str = *this; str.append(range.begin(), range.end()); return ::transfer(str); }
//
//template < typed_range < const ::ansi_character * > ANSI_RANGE >
//string_base operator + (const ANSI_RANGE & range) const { auto str = *this; str.append(range.begin(), range.end()); return ::transfer(str); }
//
//template < typed_range < const ::wd16_character * > WD16_RANGE >
//string_base operator + (const WD16_RANGE & range) const { auto str = *this; str.append(range.begin(), range.end()); return ::transfer(str); }
//
//template < typed_range < const ::wd32_character * > WD32_RANGE >
//string_base operator + (const WD32_RANGE & range) const { auto str = *this; str.append(range.begin(), range.end()); return ::transfer(str); }


template < primitive_character CHARACTER2, has_as_string HAS_AS_STRING >
::string_base < const CHARACTER2 * > operator + (const CHARACTER2 * psz, const HAS_AS_STRING & has_as_string)
{

   return ::transfer(::string_base < const CHARACTER2 * >(psz) + has_as_string.as_string());

}







//template < primitive_character CHARACTER, int t_size, character_count n >
//const_string_range_static_array < const CHARACTER *, t_size + 1 > operator + (const const_string_range_static_array < const CHARACTER *, t_size > & a, const CHARACTER(&s)[n])
//{
//
//   //return { a, ::as_string_literal< CHARACTER, n>(s) };
//    return { a, s };
//
//}


//template < primitive_character CHARACTER, int t_size, typed_character_pointer < CHARACTER > TYPED_CHARACTER_POINTER >
//const_string_range_static_array < const CHARACTER *, t_size + 1 > operator + (const const_string_range_static_array < const CHARACTER *, t_size > & a, TYPED_CHARACTER_POINTER psz)
//{
//
//   return { a, {psz, psz + string_safe_length(psz), e_range_null_terminated } };
//
//}



//template < primitive_character CHARACTER, primitive_character CHARACTER2 >
//::string_base < const CHARACTER * > operator + (const CHARACTER * psz, const CHARACTER2 * psz2)
//{
//
//   return ::transfer(::string_base < const CHARACTER * >(psz) + ::string_base < const CHARACTER * >(psz2));
//
//}


//template < typename T >
//concept primitive_string =
//::std::is_base_of<T, ::ansi_string >::value ||
//::std::is_base_of<T, ::wd16_string >::value ||
//::std::is_base_of<T, ::wd32_string >::value;



inline string & operator <<(string & str, const ::ansi_character * psz)
{

   str += psz;

   return str;

}


template < primitive_integral INTEGRAL >
inline string & operator <<(string & str, INTEGRAL i)
{

   str += ::as_string(i);

   return str;

}



using a_string_function = ::function < ::string(void) >;




// Created by speccylad(twitch)/turd(discord) trasncript by camilo on
// 2023-10-19 23:26 <3ThomasBorregaardSorensen!!
//#pragma once


//#include <format>



//template <> 
//struct std::formatter<::string> :
//   public std::formatter<std::string>
//{
//
//   template<typename Context>
//   auto format(const ::string& s, Context& ctx) const
//   {
//
//      return std::formatter<string>::format(std::format("{}"_ansi, s.c_str()), ctx);
//   }
//
//};


#if defined(__STD_FORMAT__)

// Simple specialization for strings in the Ca2 framework.
// This just uses ::string::c_str() to format.
// template<>
// struct std::formatter<::string> : std::formatter<std::string> {
//    template<class FormatContext>
//    auto format(const ::string & value, FormatContext & fc) const
//    {
//       return std::formatter<std::string>::format(value.c_str(), fc);
//    }
// };

template < >
struct std::formatter<::string > :
   public ::std::formatter< ::std::string_view >
{
   auto format(const ::string& str, std::format_context& ctx) const {
      return ::std::formatter<::std::string_view>::format(::std::string_view{ str.begin(), str.end() }, ctx);
   }
};


template<typename ...Args>
[[nodiscard]] inline ::string
format(const std::format_string<Args...> fmt, Args&&... args) noexcept
{

   return ::string(std::format<Args...>(fmt, std::forward<Args>(args)...).c_str());

}


#endif


[[nodiscard]] inline ::string formatf(const char * pszFormat, ...) noexcept
{
   
   ::string str;
   
   va_list argList;

   va_start(argList, pszFormat);

   str.formatf_arguments(pszFormat, argList);

   va_end(argList);

   return ::transfer(str);

}


template < typename ITERATOR_TYPE >
inline const_string_range < ITERATOR_TYPE > string_get_word_separated_by_spaces(const scoped_string_base < ITERATOR_TYPE > & scopedstr, ITERATOR_TYPE * pfound)
{

   auto find = scopedstr.find_first_whitespace();
   
   if(::is_set(pfound))
   {
      
      *pfound = find;
      
   }

   return { scopedstr.begin(), find };

}




template < typename ITERATOR_TYPE >
inline const_string_range < ITERATOR_TYPE > string_get_word_with_separator_list(const scoped_string_base < ITERATOR_TYPE > & scopedstr, const scoped_string_base < ITERATOR_TYPE > & scopedstrSeparatorList, ITERATOR_TYPE * pfound)
{

   auto end = scopedstr.find_first_character_in(scopedstrSeparatorList);
   
   auto find = end;

   if(::is_empty(end))
   {
      
      end = scopedstr.end();
      
      find = end;
      
   }
   else
   {
      
      find = scopedstr(find).skip_any_character_in(scopedstrSeparatorList);
   
      if(::is_empty(find))
      {
         
         find = scopedstr.end();
         
      }
      
   }

   if(::is_set(pfound))
   {

      *pfound = find;
      
   }

   return { scopedstr.begin(), end };

}



template<typename ITERATOR_TYPE>
string_base<ITERATOR_TYPE> const_string_range<ITERATOR_TYPE>::surrounded(const SCOPED_STRING& scopedstr) const
{

   return scopedstr + *this + scopedstr;

}

template<typename ITERATOR_TYPE>
string_base<ITERATOR_TYPE> const_string_range<ITERATOR_TYPE>::double_quoted(bool bEscape) const
{

   if (bEscape)
   {

      ::string_base<ITERATOR_TYPE> str(*this);

      str.find_replace("\\"_ansi, "\\\\"_ansi);

      str.find_replace("\""_ansi, "\\\""_ansi);

      return str.double_quoted(false);

   }

   return this->surrounded("\""_ansi);

}



template<typename ITERATOR_TYPE>
string_base<ITERATOR_TYPE> const_string_range<ITERATOR_TYPE>::single_quoted(bool bEscape) const
{

   if (bEscape)
   {

      ::string_base<ITERATOR_TYPE> str(*this);

      str.find_replace("\\"_ansi, "\\\\"_ansi);

      str.find_replace("\'"_ansi, "\\'"_ansi);

      return str.double_quoted(false);

   }

   return this->surrounded("\'"_ansi);

}


template<typename ITERATOR_TYPE>
typename const_string_range<ITERATOR_TYPE>::STRING_ARRAY const_string_range<ITERATOR_TYPE>::explode(const SCOPED_STRING & scopedstrSeparator, bool bAddEmpty) const
{

   STRING_ARRAY stra;

   stra.explode(scopedstrSeparator, *this, bAddEmpty);

   return stra;

}


template<typename ITERATOR_TYPE>
string_base<ITERATOR_TYPE> & string_base<ITERATOR_TYPE>::surround(const SCOPED_STRING& scopedstr)
{

   return operator=(this->surrounded(scopedstr));

}


template<typename ITERATOR_TYPE>
string_base<ITERATOR_TYPE>& string_base<ITERATOR_TYPE>::surround(const SCOPED_STRING& scopedstrLeft, const SCOPED_STRING& scopedstrRight)
{

   return operator=(this->surrounded(scopedstrLeft, scopedstrRight));

}


template<typename ITERATOR_TYPE>
string_base<ITERATOR_TYPE>& string_base<ITERATOR_TYPE>::double_quote(bool bEscape)
{

   return operator=(this->double_quoted(bEscape));

}


template<typename ITERATOR_TYPE>
string_base<ITERATOR_TYPE>& string_base<ITERATOR_TYPE>::single_quote(bool bEscape)
{

   return operator=(this->single_quoted(bEscape));

}


CLASS_DECL_ACME ::string _(const ::string & cstr);






template < primitive_character CHARACTER, other_primitive_character < CHARACTER > CHARACTER2 >
::string_base < const CHARACTER* > operator + (
   const ::range < const CHARACTER* >& range1,
   const ::range < const CHARACTER2* >& range2)
{

   return range1 + ::string_base < const CHARACTER* >(range2);

}


template < character_pointer CHARACTER_POINTER >
::string_base < const  non_const < erase_pointer<CHARACTER_POINTER>> * > operator + (
   CHARACTER_POINTER p,
   const ::range < const non_const< erase_pointer < CHARACTER_POINTER > > * > & range
   )
{

   return { {p, p + string_safe_length(p), _initialize_range_contains_null_terminated},
      range };

}


template < character_pointer CHARACTER_POINTER, other_character_range < ::decay < CHARACTER_POINTER > > OTHER_CHARACTER_RANGE >
::string_base < typename OTHER_CHARACTER_RANGE::const_iterator > operator + (
   CHARACTER_POINTER p,
   const OTHER_CHARACTER_RANGE & range
   )
{

   ::string_base < typename OTHER_CHARACTER_RANGE::const_iterator > str(p);

   str += range;

   return ::transfer(str);

}



template < typename ITERATOR_TYPE >
template < primitive_character CHARACTER >
character_count range<ITERATOR_TYPE>::__utf_length(CHARACTER * ptrigger, character_count *& plen) const
{

   return *plen++ = __utf_to_utf_length(ptrigger, this->m_begin, this->size());

}


template < typename ITERATOR_TYPE >
template < primitive_character CHARACTER >
void range<ITERATOR_TYPE>::__utf_concatenate_to(CHARACTER *& p, character_count *& plen) const
{

   utf_to_utf(p, this->m_begin, this->size());

   p += *plen++;

}






template < character_range RANGE, typed_character_pointer < typename RANGE::CHARACTER > CHARACTER_POINTER >
::string_base < typename RANGE::const_iterator > operator + (const RANGE& range, CHARACTER_POINTER psz)
{

   return { range, ::const_string_range <typename RANGE::const_iterator >(psz, psz + string_safe_length(psz), e_range_null_terminated) };

}




