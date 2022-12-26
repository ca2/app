#pragma once


#include "string_iterator.h"
#include "string_meta_data.h"
#include "string_range.h"
#include "acme/memory/string_memory_allocator.h"



template < typename ITERATOR_TYPE >
using string_natural_pointer =
::natural_pointer < ::string_range < ITERATOR_TYPE >,
   ::string_meta_data <
   dereference <
   typename get_type_item_pointer < ITERATOR_TYPE >::type
   >
   >, string_memory_allocator >;


enum enum_canonical
{

   e_canonical,

};



template < typename ITERATOR_TYPE >
class string_base :
   public string_natural_pointer < ITERATOR_TYPE >
{
public:


   using NATURAL_POINTER = string_natural_pointer < ITERATOR_TYPE >;
   using NATURAL_META_DATA = typename NATURAL_POINTER::NATURAL_META_DATA;
   using PRIMITIVE_STRING_TAG = PRIMITIVE_STRING_TAG_TYPE;
   using ITEM_POINTER = typename get_type_item_pointer< ITERATOR_TYPE>::type;
   using ITEM = dereference < ITEM_POINTER >;
   using CHARACTER = ITEM;
   using RANGE = ::string_range < ITERATOR_TYPE >;
   using this_iterator = typename RANGE::this_iterator;
   using iterator = typename RANGE::iterator;
   using const_iterator = typename RANGE::const_iterator;
   //using THIS_RAW_RANGE = typename RANGE::THIS_RAW_RANGE;
   using SCOPED_STRING = scoped_string_base < ITERATOR_TYPE >;


   string_base() { }
   string_base(enum_no_initialize) : NATURAL_POINTER(e_no_initialize) { }
   string_base(enum_zero_initialize) : NATURAL_POINTER(e_zero_initialize) { }
   string_base(nullptr_t) { }
   string_base(enum_for_moving) { }
   string_base(enum_get_buffer, strsize len) { get_string_buffer(len); }
   //string_base(const ::ansi_character * psz);
   //string_base(const ::wd16_character * psz);
   //string_base(const ::wd32_character * psz);
   string_base(const ::ansi_string & ansistr) : NATURAL_POINTER(e_no_initialize) { construct5(ansistr); }
   string_base(const ::wd16_string & wd16str) : NATURAL_POINTER(e_no_initialize) { construct5(wd16str); }
   string_base(const ::wd32_string & wd32str) : NATURAL_POINTER(e_no_initialize) { construct5(wd32str); }
   string_base(string_base && str) : NATURAL_POINTER(e_no_initialize) { this->m_begin = str.m_begin; this->m_end = str.m_end; str.m_begin = nullptr; str.m_end = nullptr; }


//   template<typed_range<::ansi_character *> RANGE>
//   string_base(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct2(str); }
//   template<typed_range<const ::ansi_character *> RANGE>
//   string_base(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct2(str); }
//   template<typed_range<::wd16_character *> RANGE>
//   string_base(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct2(str); }
//   template<typed_range<const ::wd16_character *> RANGE>
//   string_base(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct2(str); }
//   template<typed_range<::wd32_character *> RANGE>
//   string_base(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct2(str); }
//   template<typed_range<const ::wd32_character *> RANGE>
//   string_base(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct2(str); }


   template<typed_range<::ansi_character *> RANGE>
   explicit string_base(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct5(str); }
   template<typed_range<::wd16_character *> RANGE>
   explicit string_base(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct5(str); }
   template<typed_range<::wd32_character *> RANGE>
   explicit string_base(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct5(str); }


   template<typed_range<const ::ansi_character *> RANGE>
   explicit string_base(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct5(str); }
   template<typed_range<const ::wd16_character *> RANGE>
   explicit string_base(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct5(str); }
   template<typed_range<const ::wd32_character *> RANGE>
   explicit string_base(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct5(str); }



//   template<typed_range<::ansi_character *> RANGE>
//   string_base(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct2(str); }
////   template<typed_range<const ::ansi_character *> RANGE>
////   string_base(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct2(str, start, count); }
//   template<typed_range<::wd16_character *> RANGE>
//   string_base(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct2(str); }
////   template<typed_range<const ::wd16_character *> RANGE>
////   string_base(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct2(str, start, count); }
//   template<typed_range<::wd32_character *> RANGE>
//   string_base(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct2(str); }
////   template<typed_range<const ::wd32_character *> RANGE>
////   string_base(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct2(str, start, count); }

   //   string_base(const ::const_ansi_range & ansirange) : NATURAL_POINTER(e_no_initialize){construct2(ansirange);}
//   string_base(const ::const_wd16_range & wd16range) : NATURAL_POINTER(e_no_initialize){construct2(wd16range);}
//   string_base(const ::const_wd32_range & wd32range) : NATURAL_POINTER(e_no_initialize){construct2(wd32range);}
   string_base(const const_ansi_range & ansirange) : NATURAL_POINTER(e_no_initialize) { construct2(ansirange.begin(), ansirange.size()); }
   string_base(const const_wd16_range & wd16range) : NATURAL_POINTER(e_no_initialize) { construct2(wd16range.begin(), wd16range.size()); }
   string_base(const const_wd32_range & wd32range) : NATURAL_POINTER(e_no_initialize) { construct2(wd32range.begin(), wd32range.size()); }
   //string_base(const const_ansi_range & ansirange, strsize len) : NATURAL_POINTER(e_no_initialize)  { construct2(ansirange, 0, len); }
   //string_base(const const_wd16_range & wd16range, strsize len) : NATURAL_POINTER(e_no_initialize)  { construct2(wd16range, 0, len); }
   //string_base(const const_wd32_range & wd32range, strsize len) : NATURAL_POINTER(e_no_initialize)  { construct2(wd32range, 0, len); }
   //string_base(const const_ansi_range & ansirange, strsize len) : NATURAL_POINTER(e_no_initialize)  { construct2(ansirange, start, len); }
   //string_base(const const_wd16_range & wd16range, strsize len) : NATURAL_POINTER(e_no_initialize)  { construct2(wd16range, start, len); }
   //string_base(const const_wd32_range & wd32range, strsize len) : NATURAL_POINTER(e_no_initialize)  { construct2(wd32range, start, len); }
    template < primitive_character CHARACTER2 >
    string_base(const CHARACTER2 * start, const CHARACTER2 * end) : string_base(start, end-start) {}
   template < primitive_character CHARACTER2 >
   string_base(const CHARACTER2 * start) : string_base(start, string_safe_length(start)) {}
   template < primitive_character CHARACTER2 >
   string_base(const CHARACTER2 * start, strsize len) : string_base(e_no_initialize) { construct2(start, len); }
//   template < primitive_character CHARACTER2 >
//   string_base(const CHARACTER2 * pszSource, strsize len);
   template < primitive_character CHARACTER2, strsize sizeMaximumLength >
   string_base(const inline_string < CHARACTER2, sizeMaximumLength > & inlinestring) :
      string_base(inlinestring.begin(), inlinestring.end())
   { }
   //   string_base(const ::ansi_character * pansichar, strsize len);
      //string_base(::str < iterator > str) : string_base((const_iterator)str.begin(), (const_iterator)str.end()) {}
      //string_base(::str < const_iterator > str) : string_base(str.begin(), str.end()) {}
      //string_base(::block block) : string_base((const_iterator)block.begin(), (const_iterator)block.end()) {}
      //string_base(const string_base & str);
       //string_base(const ::wd16_character * pwd16char);
   //   string_base(const ::wd16_character * pwd16char, strsize len);
      //string_base(const ::wd32_character * pwd32char);
   //   string_base(const ::wd32_character * pwd32char, strsize len);
   //   string_base(const ::wd32_character * pwd32char, strsize len, strsize pos) : string_base(pwd32char + pos, len) { }
      //template < primitive_character CHARACTER2 >
   string_base(const_iterator begin, const_iterator end) : string_base(begin, end - begin) { }
   //string_base(const string_base & str) : string_base(str, 0, str.size()) { }
   //string_base(const string_base & str, strsize len) : string_base(str, 0, len) { }
   //string_base(const string_base & str, strsize len);
//   template < primitive_character CHARACTER2 >
//   string_base(const ::range < const CHARACTER2 * > & strSource) : string_base(strSource, 0, strSource.size()) {}
//   template < primitive_character CHARACTER2 >
//   string_base(const ::range < const CHARACTER2 * > & strSource, strsize len) : string_base(strSource, 0, minimum(strSource.size(), len)) {}
//   template < primitive_character CHARACTER2 >
//   string_base(const ::range < const CHARACTER2 * > & strSource, strsize len);
   //string_base(const simple_ansistring& simpleansistr);
   //string_base(const simple_wd16string& simplewd16str);
   //string_base(const simple_wd32string& simplewd32str);
   template < primitive_character CHARACTER2 >
   string_base(CHARACTER2 chSrc, strsize repeat);
   string_base(::ansi_character ansich) : string_base(&ansich, 1) {}
   string_base(::wd16_character wd16ch) : string_base(&wd16ch, 1) {}
   string_base(::wd32_character wd32ch) : string_base(&wd32ch, 1) {}
   string_base(const ::scoped_string & scopedstr);
   string_base(const ::scoped_wstring & str);
   string_base(const ::atom & atom);
   string_base(const ::payload & payload);
   string_base(const ::property & property);
   //template < has_as_string HAS_AS_STRING >
   //string_base(const HAS_AS_STRING & has_as_string) : string_base(has_as_string.as_string()) {}
   inline ~string_base() {}




   static consteval bool is_null_terminated() { return true; }

   void default_construct()
   {

      NATURAL_POINTER::natural_pointer_default_construct();

   }


   void construct(typename NATURAL_POINTER::NATURAL_META_DATA * pNew)
   {

      NATURAL_POINTER::create_assign_natural_meta_data(pNew);

   }

   template < primitive_character CHARACTER2 >
   inline void construct2(const CHARACTER2 * psz, strsize len);

   template < primitive_character CHARACTER2 >
   inline void construct5(const ::range < const CHARACTER2 * > & str);
//   template < primitive_character CHARACTER2 >
//   inline void construct2(const ::range < const CHARACTER2 * > & str);
//   template < primitive_character CHARACTER2 >
//   inline void construct2(const ::range < const CHARACTER2 * > & str);


   template < primitive_character CHARACTER2 >
   strsize start_count_length(strsize & start, strsize & count, const CHARACTER2 * pszSource);
   //void start_count(strsize & start, strsize & count, strsize len);

   inline const string_base & to_string() const { return *this; }



   using NATURAL_POINTER::begin;
   using NATURAL_POINTER::end;

   
   this_iterator & begin(this_iterator begin)
   {

      return erase_beginning(begin);

   }

   
   this_iterator & end(this_iterator end)
   {

      return truncate(end);

   }

   
   //#if OSBIT == 64
   //   inline const CHARACTER & operator [](int i) const { return this->data()[i]; }
   //#endif



   //inline operator const CONST_STRING_RANGE & () const noexcept { return this->data(); }

//#if defined(_UWP)
   //inline operator String ^ () const { return ref memory_new String(wd16_string(*this)); }
//#endif

   string_base to_string_base() const { return *this; }
   const RANGE & to_string_base() { return *this; }

   using RANGE::operator ==;
   using RANGE::operator <=>;

   bool operator==(const string_base & str) const { return this->equals(str); }
   ::std::strong_ordering operator<=>(const string_base & str) const { return this->order(str); }

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
//   string_base & operator = (string_base && string_base) { NATURAL_POINTER::operator=(::move(string_base)); return *this; }
   string_base & operator = (ansi_character ansich) { assign(ansich); return *this; }
   string_base & operator = (wd16_character wd16ch) { assign(wd16ch); return *this; }
   string_base & operator = (wd32_character wd32ch) { assign(wd32ch); return *this; }
   string_base & operator = (const ansi_character * pansisz) { assign(pansisz); return *this; }
   string_base & operator = (const wd16_character * pwd16sz) { assign(pwd16sz); return *this; }
   string_base & operator = (const wd32_character * pwd32sz) { assign(pwd32sz); return *this; }
   string_base & operator = (const ::atom & atom);
   string_base & operator = (const ::payload & payload);
   string_base & operator = (const ::property & property);
   template < strsize n >
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
   string_base & operator = (const const_ansi_range & ansirange) {assign(ansirange.begin(), ansirange.end()); return *this;}
   string_base & operator = (const const_wd16_range & wd16range) {assign(wd16range.begin(), wd16range.end()); return *this;}
   string_base & operator = (const const_wd32_range & wd32range) {assign(wd32range.begin(), wd32range.end()); return *this;}
   string_base & operator = (const ansi_string & ansistr) {assign(ansistr.begin(), ansistr.end()); return *this;}
   string_base & operator = (const wd16_string & wd16str) {assign(wd16str.begin(), wd16str.end()); return *this;}
   string_base & operator = (const wd32_string & wd32str) {assign(wd32str.begin(), wd32str.end()); return *this;}
      //template < primitive_character CHARACTER2 >
      //string_base & operator = (const ::range < const CHARACTER2 * > & str);
      //string_base & operator = (string_base && str);
   string_base & operator = (const ::inline_number_string & inline_number_string) {assign(inline_number_string.begin(), inline_number_string.end()); return *this;}
   string_base & operator = (const scoped_ansi_string & ansistr);
   string_base & operator = (const scoped_wd16_string & wd16str);
   string_base & operator = (const scoped_wd32_string & wd32str);
      //string_base & operator = (const string_base & str);
      //string_base & operator = (const string_base & str);
      //string_base & operator = (::ansi_character ansich);
      //string_base & operator = (::wd16_character wd16ch);
   //   string_base & operator = (::wd32_character wd32ch);
   //#ifdef WINDOWS
     // string_base & operator = (const USHORT * pshSrc) { return operator=((const ::wd16_character *)pshSrc); }
   //#endif
   //#ifdef _UWP
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
//   template < has_as_string HAS_AS_STRING >
//   string_base & operator += (const HAS_AS_STRING & has_as_string) { return operator+=(has_as_string.as_string()); }


//   template < int t_nSize >
//   inline string_base & operator +=(const static_string<CHARACTER, t_nSize > & ansistrSrc);
//
//   template < typename TYPE >
//   inline string_base & operator +=(const TYPE & t);
//

//   template < primitive_character CHARACTER2 >
//   string_base operator + (const CHARACTER2 * psz) const { auto str = *this; str.append(psz); return ::move(str); }


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
//      trim_right(string_base("\\/"));
//
//      strRight.trim_left(string_base("\\/"));
//
//      return this->operator += ("/" + strRight);
//
//   }


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

   inline string_base & assign(const string_base & str);
   inline string_base & assign(string_base && str);

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
   
   template < primitive_character CHARACTER2 >
   inline string_base & assign(const CHARACTER2 * start, const CHARACTER2 * end);

   template < primitive_character CHARACTER2 >
   inline string_base & assign(const CHARACTER2 * pszSrc, strsize len);
   //inline string_base& assign(const wd16_string& wd16str);
   //inline string_base& assign(const wd32_string& wd32str);
//   template < primitive_character CHARACTER2 >
//   inline string_base & assign(const CHARACTER2 * pszSrc, strsize len)
//   {
//      return assign(pszSrc, 0, len);
//   }
   //template < primitive_block BLOCK >
   //inline string_base& assign(const BLOCK & pszSrc, strsize len);
   template < primitive_character CHARACTER2 >
   inline string_base & _assign(const CHARACTER2 * pszSrc, strsize len);
   //inline string_base& assign(const ::wd16_character* pwd16szSrc, strsize len);
   //inline string_base& assign(const ::wd32_character* pwd32szSrc, strsize len);
   template < primitive_character CHARACTER2 >
   inline string_base & assign(CHARACTER2 chSrc, strsize repeat);
   //   inline string_base & assign(::ansi_character ansich, strsize repeat);
   //   inline string_base & assign(::wd16_character wd16ch, strsize repeat);
   //   inline string_base & assign(::wd32_character wd32ch, strsize repeat);

   //template <class InputIterator>
   //inline string_base & assign(InputIterator first, InputIterator last);

   //template < int t_nSize >
   //inline string_base & assign(const static_string<CHARACTER, t_nSize > & ansistrSrc);

   inline string_base & append(strsize len, CHARACTER ch);
   template < primitive_character CHARACTER2 >
   inline string_base & append_character_array(const CHARACTER2 * psz, strsize len)
   { auto pszEnd = psz + len; if(*(pszEnd - 1) == 0) pszEnd--; append(psz, pszEnd - psz); }

   inline string_base & append_character(::wd32_character wch);
   inline string_base & append_character(::ansi_character ch);
   inline string_base & append_character(::wd16_character wch);


   inline string_base & append(const ::const_ansi_range & range);
   inline string_base & append(const ::const_wd16_range & range);
   inline string_base & append(const ::const_wd32_range & range);
   
   inline string_base & append(const ::ansi_character * psz) { return append(::const_ansi_range(psz)); }
   inline string_base & append(const ::wd16_character * psz) { return append(::const_wd16_range(psz)); }
   inline string_base & append(const ::wd32_character * psz) { return append(::const_wd32_range(psz)); }

   inline string_base & append(const ::ansi_character * psz, strsize size) { return append(::const_ansi_range(psz, size)); }
   inline string_base & append(const ::wd16_character * psz, strsize size) { return append(::const_wd16_range(psz, size)); }
   inline string_base & append(const ::wd32_character * psz, strsize size) { return append(::const_wd32_range(psz, size)); }


   template < primitive_character CHARACTER2 >
   inline string_base < ITERATOR_TYPE > & _append(const CHARACTER2 * pszSrc, strsize count);

   //inline string_base & append(const ::wd16_character * pszSrc);
   //inline string_base & append(const ::wd16_character * pszSrc, strsize nLength);
   //inline string_base & append(const wd16_string & ansistrSrc);

   //inline string_base & append(const ::wd32_character * pszSrc);
   //inline string_base & append(const ::wd32_character * pszSrc, strsize nLength);
   //inline string_base & append(const wd32_string & ansistrSrc);

   //template < typename STATIC_TYPE_CHAR, int t_nSize >
   //inline string_base& append(const static_string<STATIC_TYPE_CHAR, t_nSize > & ansistrSrc);
   inline string_base & append(const ::atom & atom);
   inline string_base & append(const ::payload & payload);
   inline string_base & append(const ::property & property);


   inline void empty()
   {

      ASSERT(this->metadata()->m_countReference >= 1);

      if (this->has_char())
      {

         this->natural_release();

      }

   }




   inline CHARACTER * get_string_buffer()
   {

      auto p = this->metadata();

      ASSERT(p->m_countReference >= 1);

      if (p->natural_is_shared())
      {

         fork_string(p->length());

      }

      return this->data();

   }


   inline CHARACTER * get_string_buffer(strsize size)
   {

      //if (this->is_string())
      //{

      auto p = this->metadata();

      ASSERT(p->m_countReference >= 1);

      if (::is_null(p) || p->natural_is_shared() || size > p->length())
      {

         fork_string(size);

      }
      else
      {

         this->metadata()->set_data_length(size);

      }

      //}
      //else
      //{

      //   fork_string(size);

      //}

      return this->data();

   }


   inline CHARACTER * defer_get_string_buffer(strsize size, const string_base & str)
   {

      auto p = this->metadata();

      ASSERT(p->m_countReference >= 1);

      if (::is_null(p) || p->natural_is_shared() || size > p->length() || p->contains_data(str))
      {

         fork_string(size);

      }

      this->metadata()->set_length(size);

      return this->data();

   }



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

   string_base & release_string_buffer(strsize nNewLength = -1);
   inline this_iterator & truncate(this_iterator p);
   template < primitive_integral INTEGRAL >
   inline this_iterator & truncate(INTEGRAL count) {return truncate(this->m_begin + count);}

   inline this_iterator & erase_beginning(this_iterator p);

   inline void set_at(strsize iChar, CHARACTER ch);

   CHARACTER * fork_string(strsize strsize);

   CHARACTER * create_string(strsize strsize);

   void prepare_write(strsize nLength)
   {

      auto p = this->metadata();

      if (p->natural_is_shared() || nLength >= this->get_storage_length())
      {

         fork_string(nLength);

      }

   }

   string_base if_empty(string_base ansistr) { return this->is_empty() ? ansistr : *this; }


   void push_back(CHARACTER ch);



   void reserve(strsize res_arg = 0);

   string_base & erase(strsize start = 0, strsize count = -1);

   const_iterator insert(strsize iIndex, CHARACTER ch);

   const_iterator insert(strsize iIndex, const string_base & str);

   const_iterator replace_character(CHARACTER charNew, CHARACTER charOld, strsize start = 0);

   template < typename EQUALITY >
   ::count _replace_with(const SCOPED_STRING & scopedstrNew, const SCOPED_STRING & scopedstrOld, strsize start, EQUALITY equality);


   ::count replace_with(const SCOPED_STRING & scopedstrNew, const SCOPED_STRING & scopedstrOld, strsize start = 0)
   {

      return _replace_with(scopedstrNew, scopedstrOld, start, ::comparison::comparison<CHARACTER>());

   }


   ::count case_insensitive_replace_with(const SCOPED_STRING & scopedstrNew, const SCOPED_STRING & scopedstrOld, strsize start = 0)
   {

      return _replace_with(scopedstrNew, scopedstrOld, start, ::comparison::case_insensitive<CHARACTER>());

   }

   ::count replace_with_count(const SCOPED_STRING & scopedstrNew, const SCOPED_STRING & scopedstrOld, strsize iStart = 0);

   ::count replace_with_ci_count(const SCOPED_STRING & scopedstrNew, const SCOPED_STRING & scopedstrOld, strsize iStart = 0);

   ::count find_replace(CHARACTER charOld, CHARACTER charNew, strsize iStart = 0)
   {

      return replace_with(charNew, charOld, iStart);

   }

   ::count find_replace(const SCOPED_STRING & scopedstrOld, const SCOPED_STRING & scopedstrNew, strsize start = 0)
   {

      return _replace_with(scopedstrNew, scopedstrOld, start, comparison::comparison<CHARACTER>());

   }


   ::count case_insensitive_find_replace(const SCOPED_STRING & scopedstrOld, const SCOPED_STRING & scopedstrNew, strsize start = 0)
   {

      return _replace_with(scopedstrNew, scopedstrOld, start, comparison::case_insensitive<CHARACTER>());

   }


   // replace all occurrences of string_base 'pszOld' with string_base 'pszNew'
   //template < raw_pointer_castable < CHARACTER_TYPE > PCHAROLD, raw_pointer_castable < CHARACTER_TYPE > PCHARNEW >
   ::count find_replace_count(const SCOPED_STRING & scopedstrOld, const SCOPED_STRING & scopedstrNew, strsize iStart = 0)
   {

      return replace_with_count(scopedstrNew, scopedstrOld, iStart);

   }


   //template < raw_pointer_castable < CHARACTER_TYPE > PCHAROLD, raw_pointer_castable < CHARACTER_TYPE > PCHARNEW >
   ::count find_replace_ci_count(const SCOPED_STRING & scopedstrOld, const SCOPED_STRING & scopedstrNew, strsize iStart = 0)
   {

      return replace_with_ci_count(scopedstrNew, scopedstrOld, iStart);

   }


   //// replace all occurrences of character 'chOld' with character 'chNew'
   //strsize xxx_replace(CHARACTER charOld, CHARACTER charNew, strsize iStart = 0);

   //// replace all occurrences of string_base 'pszOld' with string_base 'pszNew'
   //template < raw_pointer_castable < CHARACTER_TYPE > PCHAROLD, raw_pointer_castable < CHARACTER_TYPE > PCHARNEW >
   //strsize xxx_replace(PCHAROLD pcharOld, PCHARNEW pcharNew, strsize iStart = 0);

   //template < raw_pointer_castable < CHARACTER_TYPE > PCHAROLD, raw_pointer_castable < CHARACTER_TYPE > PCHARNEW >
   //strsize xxx_replace_ci(PCHAROLD pcharOld, PCHARNEW pcharNew, strsize iStart = 0);

   //// replace all occurrences of string_base 'pszOld' with string_base 'pszNew'
   //template < raw_pointer_castable < CHARACTER_TYPE > PCHAROLD, raw_pointer_castable < CHARACTER_TYPE > PCHARNEW >
   //::count xxx_replace_count(PCHAROLD pcharOld, PCHARNEW pcharNew, strsize iStart = 0);

   //template < raw_pointer_castable < CHARACTER_TYPE > PCHAROLD, raw_pointer_castable < CHARACTER_TYPE > PCHARNEW >
   //::count xxx_replace_ci_count(PCHAROLD pcharOld, PCHARNEW pcharNew, strsize iStart = 0);

   //::count utf8_replace(const string_base &scopedstrOld, const string_base &scopedstrNew, strsize iStart = 0);

   string_base & replace(const_iterator start, const_iterator end, const SCOPED_STRING & scopedstr);
   string_base & replace_index(strsize start, strsize end, const SCOPED_STRING & scopedstr)
   {

      return replace(this->begin() + start, this->begin() + end, scopedstr);

   }
   //string_base & replace(strsize iStart, strsize nCount, const SCOPED_STRING & scopedstr, strsize nLen);

   // erase all occurrences of character 'chRemove'
   const_iterator erase_character(CHARACTER chRemove);

   string_base Tokenize(const SCOPED_STRING & scopedstrTokens, strsize & iStart) const;



   const_iterator begins_eat_any_character_in(const SCOPED_STRING & scopedstrCharacters = 0) const RELEASENOTHROW
   {

      auto i = skip_any_character_in(scopedstrCharacters);

      if(i > 0)
      {

         erase_beginning(i);

      }

      return i;

   }


   //strsize get_token(const string_base &strSeparators, strsize pos = -1) const RELEASENOTHROW;
   //strsize get_token(const string_base &strSeparators) const RELEASENOTHROW;
   //strsize get_token(const CHARACTER * pszSeparators, strsize pos = -1) const RELEASENOTHROW;
   //strsize get_token(CHARACTER chSeparator, strsize pos = -1) const RELEASENOTHROW;

   //strsize _get_token(const string_base &strSeparators, strsize pos = -1) const RELEASENOTHROW;
   //strsize _get_token(const string_base &strSeparators) const RELEASENOTHROW;
   //strsize _get_token(const CHARACTER * pszSeparators, strsize pos = -1) const RELEASENOTHROW;
   //strsize _get_token(CHARACTER chSeparator, strsize pos = -1) const RELEASENOTHROW;


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


   //inline bool begins(const CHARACTER * pszPrefix) const;

   //inline bool begins(const string_base &strPrefix) const;
   //inline bool ends(const string_base &strSuffix) const;

   inline bool begins_eat(const SCOPED_STRING & scopedstrPrefix);
   inline bool ends_eat(const SCOPED_STRING & scopedstrSuffix);

   inline bool case_insensitive_begins_eat(const SCOPED_STRING & scopedstrPrefix);
   inline bool case_insensitive_ends_eat(const SCOPED_STRING & scopedstrSuffix);


   inline bool begins_replace(const SCOPED_STRING & scopedstrNewPrefix, const SCOPED_STRING & scopedstrPrefix);

   inline bool case_insensitive_begins_replace(const SCOPED_STRING & scopedstrNewPrefix, const SCOPED_STRING & scopedstrPrefix);


   inline bool begins_eat(string_base & strRest, const SCOPED_STRING & scopedstr) const;
   inline bool ends_eat(string_base & strRest, const SCOPED_STRING & scopedstr) const;

   inline bool case_insensitive_begins_eat(string_base & strRest, const SCOPED_STRING & scopedstr) const;
   inline bool case_insensitive_ends_eat(string_base & strRest, const SCOPED_STRING & scopedstr) const;

   inline bool begins_eaten_ci(string_base & strEaten, const SCOPED_STRING & scopedstr) const;
   inline bool ends_eaten_ci(string_base & strEaten, const SCOPED_STRING & scopedstr) const;

   inline string_base & ensure_begins(const SCOPED_STRING & scopedstr);
   inline string_base & ensure_begins_ci(const SCOPED_STRING & scopedstr);

   inline string_base & ensure_ends(const SCOPED_STRING & scopedstr);
   inline string_base & ensure_ends_ci(const SCOPED_STRING & scopedstr);

   //inline bool begins(const string_base &str) const;
   //inline bool ends(const string_base &str) const;

   //inline bool case_insensitive_begins(const string_base &str) const;
   //inline bool case_insensitive_ends(const string_base &str) const;

   //inline bool begins_eat(const string_base &str);
   //inline bool ends_eat(const string_base &str);

   //inline bool case_insensitive_begins_eat(const string_base &str);
   //inline bool case_insensitive_ends_eat(const string_base &str);

   //inline string_base& ensure_begins(const string_base &strPrefix);
   //inline string_base& ensure_begins_ci(const string_base &strPrefix);

   //inline string_base& ensure_ends(const string_base &strSuffix);
   //inline string_base& ensure_ends_ci(const string_base &strSuffix);

   bool eat_before(string_base & strBefore, const SCOPED_STRING & scopedstrSeparator, bool bEatEverythingIfNotFound = false);
   bool eat_before_let_separator(string_base & strBefore, const SCOPED_STRING & scopedstrSeparator, bool bEatEverythingIfNotFound = false);

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

   // Convert the string_base to lowercase
   string_base lowered() const;

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
   string_base left_trimmed(const SCOPED_STRING & scopedstrTargets) const;


   string_base substr(strsize iFirst) const;

   string_base substr(const_iterator p) const { return ::move(substr(p, -1)); }
   string_base substr(const_iterator p, strsize count) const { return ::move(substr(p - this->begin(), count)); }

   template < primitive_integral START, primitive_integral COUNT >
   string_base substr(START start, COUNT count) const;
   template < primitive_integral START >
   string_base substr(START start, const_iterator p) const { return substr(start, (p - this->m_begin) - start); }


   inline memsize get_storage_size_in_bytes() const { return this->metadata()->memsize(); }
   inline strsize get_storage_length() const;


   inline strsize length() const { return (::strsize)this->metadata()->m_datasize; }
   inline strsize size() const { return this->length(); }
   inline memsize length_in_bytes() const;
   inline memsize length_in_bytes_with_null_terminator() const;

   string_base right(strsize nCount) const;

   string_base left(strsize count) const;

   string_base left(const_iterator p) const { return ::move(this->left(p - this->begin())); }

   string_base left_including_any_character_in(const SCOPED_STRING & scopedstrCharSet) const;

   string_base left_skipping_any_character_in(const SCOPED_STRING & scopedstrCharSet) const;


   void format(const CHARACTER * pszFormat, ...);

   void format_arguments(const CHARACTER * pszFormat, va_list args);

   void append_format(const CHARACTER * pszFormat, ...);

   void append_format_arguments(const CHARACTER * pszFormat, va_list args);

   //void FormatMessage(const CHARACTER * pszFormat, ...);




   // set the string_base to the value of environment ::payload 'pszVar'
   //bool xxxget_environment_variable(const string_base &strVar);

   // set the string_base to the value of environment ::payload 'pszVar'
   //bool xxxgetenv(const string_base &strVar);

   // Load the string_base from resource 'nID'
   //bool load_string(::particle * pparticle, atom atom);

   // Load the string_base from resource 'nID' in module 'hInstance'
   /*    bool load_string(HINSTANCE hInstance,strsize nID )
   {
   const STRINGRESOURCEIMAGE* pImage = gen_GetStringResourceImage( hInstance, nID );
   if( pImage == nullptr )
   {
   return( false );
   }

   strsize nLength = str_traits::GetcharLength( pImage->achString, pImage->nLength );
   CHARACTER * pszBuffer = GetBuffer( nLength );
   str_traits::ConvertTochar( pszBuffer, nLength, pImage->achString, pImage->nLength );
   release_string_buffer( nLength );

   return( true );
   }*/

   // Load the string_base from resource 'nID' in module 'hInstance', using language 'wLanguageID'
   /*bool load_string(HINSTANCE hInstance,strsize nID,::u16 wLanguageID )
   {
   const STRINGRESOURCEIMAGE* pImage = gen_GetStringResourceImage( hInstance, nID, wLanguageID );
   if( pImage == nullptr )
   {
   return( false );
   }

   strsize nLength = str_traits::GetcharLength( pImage->achString, pImage->nLength );
   CHARACTER * pszBuffer = GetBuffer( nLength );
   str_traits::ConvertTochar( pszBuffer, nLength, pImage->achString, pImage->nLength );
   release_string_buffer( nLength );

   return( true );
   }*/

   void resize(strsize n)
   {
      resize(n, '\0');
   }

   void resize(strsize n, CHARACTER c);




   string_base unichar_substr(strsize iFirst) const;
   string_base unichar_substr(strsize iFirst, strsize nCount) const;
   string_base unichar_left(strsize nCount) const;
   string_base unichar_mid(strsize iFirst) const;
   string_base unichar_mid(strsize iFirst, strsize nCount) const;


   //strsize char_get_count(strsize iCharCount) const;
   //ansi_string char_left(strsize nCount) const;
   //ansi_string char_mid(strsize iFirst) const;
   //ansi_string char_mid(strsize iFirst, strsize nCount) const;

   void clear();



   typedef strsize size_type;


};


// For MSVC, but not for GCC?
//inline ::string operator + (const ::string & strA, const ::string & strB)
//{
//
//   auto str = strA;
//
//   str += strB;
//
//   return str;
//
//}


//inline ::string operator+(const ::string & str, const ::const_ansi_range & range)
//{
//
//   auto strResult = str;
//
//   strResult.append(range);
//
//   return ::move(strResult);
//
//}


//inline ::string operator + (const ::string & str, char ch);

//inline ::string operator +(const ::string & str, const ::ansi_character * psz)
//{
//
//   return str + ::string(psz);
//
//}


//template < ::count c >
//inline ::string operator +(const ::string & str, const char(&sz)[c]);
//
//
//template < strsize m_sizeMaximumLength >
//inline ::string operator +(const ::string & str, const ::inline_string < char, m_sizeMaximumLength > & inlinestring);

//inline ::string operator +(const scoped_string & scopedstr, const ::string & str)
//{
//
//   return ::string(scopedstr) + str;
//
//}


//inline ::string operator +(char ch, const ::string & str);


// For MSVC, but not for GCC?
//template < ::count c >
//inline ::string operator +(const char(&sz)[c], const ::string & str)
//{
//
//   return ::string(sz) + str;
//
//}


//template < ::count c >
//inline ::string operator+(const ::const_ansi_range & str, const char(&sz)[c])
//{
//
//   return ::string(str) + sz;
//
//}


// For MSVC, but not for GCC?
//inline ::string operator+(const ::const_ansi_range & range, const ::string & str)
//{
//
//   return ::string(range) + str;
//
//}


//template < primitive_character CHARACTER, typename CHARACTER2 >
//constexpr ::string_base < const CHARACTER * > operator +(CHARACTER ch, ::str < const CHARACTER2 * > str)
//{
//
//   return ::move(::string_base < const CHARACTER * >(ch) + ::string_base < const CHARACTER * >(str));
//
//}


//template < primitive_character CHARACTER1, primitive_character CHARACTER2, strsize sizeMaximumLength >
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
//   return ::move(::string_base < const CHARACTER * >(str) + ::string_base < const CHARACTER * >(psz));
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
//template < ::count c >
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
//   this->m_begin = (::byte *)str.m_begin;
//   this->m_end = (::byte *) str.m_end;
//
//}


//template < ::count c, strsize m_sizeMaximumLength >
//inline ::string operator +(const char(&sz)[c], const ::inline_string < char, m_sizeMaximumLength > & inlinestring);


//template < ::count c, strsize m_sizeMaximumLength >
//inline ::string operator +(const ::inline_string < char, m_sizeMaximumLength > & inlinestring, const char(&sz)[c]);


CLASS_DECL_ACME::string _(const ::string & str);





template < primitive_character CHARACTER >
class argument_of < ::string_base < const CHARACTER * > >
{
public:

   using type = ::scoped_string_base < const CHARACTER * >;

};




//template < typename ITERATOR_TYPE >
//inline ::string_base < ITERATOR_TYPE > operator + (const string_range < ITERATOR_TYPE > & scopedstrA, const string_range < ITERATOR_TYPE > & scopedstrB )
//{
//
//   string_base < ITERATOR_TYPE > str;
//
//   auto len = scopedstrA.size() + scopedstrB.size();
//
//   auto p = str.get_string_buffer(len);
//
//   memcpy(p, scopedstrA, scopedstrA.size());
//
//   memcpy(p + scopedstrA.size(), scopedstrB, scopedstrB.size());
//
//   str.release_string_buffer(len);
//
//   return ::move(str);
//
//}


//template < strsize n, typename ITERATOR_TYPE >
//inline ::string_base < ITERATOR_TYPE > operator + (const char (&cha)[n], const string_range < ITERATOR_TYPE > & scopedstr)
//{
//
//   return ::move(::string_base < ITERATOR_TYPE >(cha) + scopedstr);
//
//}


// For MSVC, but not for GCC?
//template < typename ITERATOR_TYPE >
//inline ::string_base < ITERATOR_TYPE > operator + (const char * psz, const string_base < ITERATOR_TYPE > & str)
//{
//
//   return ::move(::string_base < ITERATOR_TYPE >(psz) + str);
//
//}



// For MSVC, but not for GCC?
//template < strsize n, typename ITERATOR_TYPE >
//inline ::string_base < ITERATOR_TYPE > operator + (const char(&cha)[n], const string_base < ITERATOR_TYPE > & str)
//{
//
//   return ::move(::string_base < ITERATOR_TYPE >(cha) + str);
//
//}



template < primitive_floating FLOATING >
inline ::string as_string(FLOATING f, const ::ansi_character * pszFormat = "%f");



template < >
inline u32hash u32_hash < const ansi_string & >(const ansi_string & ansistr);


template < >
inline u32hash u32_hash < const wide_string & >(const wide_string & widestr);


template < >
inline u32hash u32_hash < ansi_string >(ansi_string ansistr);


template < >
inline u32hash u32_hash < wide_string >(wide_string widestr);



template < primitive_character CHARACTER, character_range RANGE >
string_base < const CHARACTER * > operator + (const CHARACTER * psz, const RANGE & range)
{ 
   
   string_base < const CHARACTER * > str(psz); 
   
   return ::move(str + range); 

}



template < character_range RANGE1, character_range RANGE2 >
string_base < typename RANGE1::const_iterator > operator + (const RANGE1 & range1, const RANGE2 & range2)
{

   string_base < typename RANGE1::const_iterator > str(range1.begin(), range1.size());

   str.append(range2.begin(), range2.size());

   return str;

}


//template < typed_range < ::wd16_character * > WD16_RANGE >
//string_base operator + (const WD16_RANGE & range) const { auto str = *this; str.append(range.begin(), range.end()); return ::move(str); }
//
//template < typed_range < ::wd32_character * > WD32_RANGE >
//string_base operator + (const WD32_RANGE & range) const { auto str = *this; str.append(range.begin(), range.end()); return ::move(str); }
//
//template < typed_range < const ::ansi_character * > ANSI_RANGE >
//string_base operator + (const ANSI_RANGE & range) const { auto str = *this; str.append(range.begin(), range.end()); return ::move(str); }
//
//template < typed_range < const ::wd16_character * > WD16_RANGE >
//string_base operator + (const WD16_RANGE & range) const { auto str = *this; str.append(range.begin(), range.end()); return ::move(str); }
//
//template < typed_range < const ::wd32_character * > WD32_RANGE >
//string_base operator + (const WD32_RANGE & range) const { auto str = *this; str.append(range.begin(), range.end()); return ::move(str); }


template < primitive_character CHARACTER2, has_as_string HAS_AS_STRING >
::string_base < const CHARACTER2 * > operator + (const CHARACTER2 * psz, const HAS_AS_STRING & has_as_string)
{

   return ::move(::string_base < const CHARACTER2 * >(psz) + has_as_string.as_string());

}


template < character_range RANGE, has_as_string HAS_AS_STRING >
::string_base < typename RANGE::const_iterator > operator + (const RANGE & range, const HAS_AS_STRING & has_as_string)
{

   return ::move(::string_base < typename RANGE::const_iterator >(range) + has_as_string.as_string());

}


template < character_range RANGE, primitive_character CHARACTER >
::string_base < typename RANGE::const_iterator > operator + (const RANGE & range, const CHARACTER * psz)
{

   return ::move(::string_base < typename RANGE::const_iterator >(range) + ::string_base < typename RANGE::const_iterator >(psz));

}


//template < primitive_character CHARACTER, primitive_character CHARACTER2 >
//::string_base < const CHARACTER * > operator + (const CHARACTER * psz, const CHARACTER2 * psz2)
//{
//
//   return ::move(::string_base < const CHARACTER * >(psz) + ::string_base < const CHARACTER * >(psz2));
//
//}


//template < typename T >
//concept primitive_string =
//::std::is_base_of<T, ::ansi_string >::value ||
//::std::is_base_of<T, ::wd16_string >::value ||
//::std::is_base_of<T, ::wd32_string >::value;


//template < typename T >
//concept character_range_not_string = character_range<T> && !primitive_string<T>;
//
//
//template < typename T >
//concept character_range_not_string_neither_scoped_string = character_range<T> && !primitive_string<T> && !primitive_scoped_string<T>;


