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
   using THIS_RAW_RANGE = typename RANGE::THIS_RAW_RANGE;


   string_base() { }
   string_base(enum_no_initialize) : NATURAL_POINTER(e_no_initialize) { }
   string_base(nullptr_t) { }
   string_base(enum_for_moving) { }
   string_base(enum_get_buffer, strsize len) { get_string_buffer(len); }
   string_base(const ::ansi_string & ansistr) : NATURAL_POINTER(e_no_initialize) { construct2(ansistr); }
   string_base(const ::wd16_string & wd16str) : NATURAL_POINTER(e_no_initialize) { construct2(wd16str); }
   string_base(const ::wd32_string & wd32str) : NATURAL_POINTER(e_no_initialize) { construct2(wd32str); }
   string_base(string_base && str) : NATURAL_POINTER(e_no_initialize) { this->m_begin = str.m_begin; this->m_end = str.m_end; str.m_begin = nullptr; str.m_end = nullptr; }


   template<typed_range<::ansi_character *> RANGE>
   string_base(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct2(str); }
   template<typed_range<const ::ansi_character *> RANGE>
   string_base(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct2(str); }
   template<typed_range<::wd16_character *> RANGE>
   string_base(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct2(str); }
   template<typed_range<const ::wd16_character *> RANGE>
   string_base(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct2(str); }
   template<typed_range<::wd32_character *> RANGE>
   string_base(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct2(str); }
   template<typed_range<const ::wd32_character *> RANGE>
   string_base(const RANGE & str) : NATURAL_POINTER(e_no_initialize) { construct2(str); }


   template<typed_range<::ansi_character *> RANGE>
   string_base(const RANGE & str, strsize count) : NATURAL_POINTER(e_no_initialize) { construct2(str, count); }
   template<typed_range<const ::ansi_character *> RANGE>
   string_base(const RANGE & str, strsize count) : NATURAL_POINTER(e_no_initialize) { construct2(str, count); }
   template<typed_range<::wd16_character *> RANGE>
   string_base(const RANGE & str, strsize count) : NATURAL_POINTER(e_no_initialize) { construct2(str, count); }
   template<typed_range<const ::wd16_character *> RANGE>
   string_base(const RANGE & str, strsize count) : NATURAL_POINTER(e_no_initialize) { construct2(str, count); }
   template<typed_range<::wd32_character *> RANGE>
   string_base(const RANGE & str, strsize count) : NATURAL_POINTER(e_no_initialize) { construct2(str, count); }
   template<typed_range<const ::wd32_character *> RANGE>
   string_base(const RANGE & str, strsize count) : NATURAL_POINTER(e_no_initialize) { construct2(str, count); }



   template<typed_range<::ansi_character *> RANGE>
   string_base(const RANGE & str, strsize start, strsize count) : NATURAL_POINTER(e_no_initialize) { construct2(str, start, count); }
   template<typed_range<const ::ansi_character *> RANGE>
   string_base(const RANGE & str, strsize start, strsize count) : NATURAL_POINTER(e_no_initialize) { construct2(str, start, count); }
   template<typed_range<::wd16_character *> RANGE>
   string_base(const RANGE & str, strsize start, strsize count) : NATURAL_POINTER(e_no_initialize) { construct2(str, start, count); }
   template<typed_range<const ::wd16_character *> RANGE>
   string_base(const RANGE & str, strsize start, strsize count) : NATURAL_POINTER(e_no_initialize) { construct2(str, start, count); }
   template<typed_range<::wd32_character *> RANGE>
   string_base(const RANGE & str, strsize start, strsize count) : NATURAL_POINTER(e_no_initialize) { construct2(str, start, count); }
   template<typed_range<const ::wd32_character *> RANGE>
   string_base(const RANGE & str, strsize start, strsize count) : NATURAL_POINTER(e_no_initialize) { construct2(str, start, count); }

   //   string_base(const ::const_ansi_raw_range & ansirange) : NATURAL_POINTER(e_no_initialize){construct2(ansirange);}
//   string_base(const ::const_wd16_raw_range & wd16range) : NATURAL_POINTER(e_no_initialize){construct2(wd16range);}
//   string_base(const ::const_wd32_raw_range & wd32range) : NATURAL_POINTER(e_no_initialize){construct2(wd32range);}
   //string_base(const const_ansi_raw_range & ansirange) : NATURAL_POINTER(e_no_initialize) { construct2(ansirange, 0, -1); }
   //string_base(const const_wd16_raw_range & wd16range) : NATURAL_POINTER(e_no_initialize) { construct2(wd16range, 0, -1); }
   //string_base(const const_wd32_raw_range & wd32range) : NATURAL_POINTER(e_no_initialize) { construct2(wd32range, 0, -1); }
   //string_base(const const_ansi_raw_range & ansirange, strsize len) : NATURAL_POINTER(e_no_initialize)  { construct2(ansirange, 0, len); }
   //string_base(const const_wd16_raw_range & wd16range, strsize len) : NATURAL_POINTER(e_no_initialize)  { construct2(wd16range, 0, len); }
   //string_base(const const_wd32_raw_range & wd32range, strsize len) : NATURAL_POINTER(e_no_initialize)  { construct2(wd32range, 0, len); }
   //string_base(const const_ansi_raw_range & ansirange, strsize start, strsize len) : NATURAL_POINTER(e_no_initialize)  { construct2(ansirange, start, len); }
   //string_base(const const_wd16_raw_range & wd16range, strsize start, strsize len) : NATURAL_POINTER(e_no_initialize)  { construct2(wd16range, start, len); }
   //string_base(const const_wd32_raw_range & wd32range, strsize start, strsize len) : NATURAL_POINTER(e_no_initialize)  { construct2(wd32range, start, len); }
   template < primitive_character CHARACTER2 >
   string_base(const CHARACTER2 * pszSource) : string_base(pszSource, 0, string_safe_length(pszSource)) {}
   template < primitive_character CHARACTER2 >
   string_base(const CHARACTER2 * pszSource, strsize len) : string_base(pszSource, 0, len) {}
   template < primitive_character CHARACTER2 >
   string_base(const CHARACTER2 * pszSource, strsize start, strsize len);
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
   //string_base(const string_base & str, strsize start, strsize len);
//   template < primitive_character CHARACTER2 >
//   string_base(const ::string_range < const CHARACTER2 * > & strSource) : string_base(strSource, 0, strSource.size()) {}
//   template < primitive_character CHARACTER2 >
//   string_base(const ::string_range < const CHARACTER2 * > & strSource, strsize len) : string_base(strSource, 0, minimum(strSource.size(), len)) {}
//   template < primitive_character CHARACTER2 >
//   string_base(const ::string_range < const CHARACTER2 * > & strSource, strsize start, strsize len);
   //string_base(const simple_ansistring& simpleansistr);
   //string_base(const simple_wd16string& simplewd16str);
   //string_base(const simple_wd32string& simplewd32str);
   template < primitive_character CHARACTER2 >
   string_base(CHARACTER2 chSrc, strsize repeat);
   string_base(::ansi_character ansich) : string_base(&ansich, 1) {}
   string_base(::wd16_character wd16ch) : string_base(&wd16ch, 1) {}
   string_base(::wd32_character wd32ch) : string_base(&wd32ch, 1) {}
   //string_base(const character & character, strsize repeat = 1) :string_base(character.m_wd32char, repeat) {}
   string_base(const ::atom & atom);
   string_base(const ::payload & payload);
   string_base(const ::property & property);
   //template < has_as_string HAS_AS_STRING >
   //string_base(const HAS_AS_STRING & has_as_string) : string_base(has_as_string.as_string()) {}
   inline ~string_base() {}


   string_base & operator = (const ansi_string & str)
   {
      if constexpr (sizeof(CHARACTER) == sizeof(ansi_character))
      {
         NATURAL_POINTER::operator=(str);
      }
      else
      {
         assign(str);
      }
      return *this;
   }
   string_base & operator = (const wd16_string & str)
   {
      if constexpr (sizeof(CHARACTER) == sizeof(wd16_character))
      {
         NATURAL_POINTER::operator=(str);
      }
      else
      {
         assign(str);
      }
      return *this;
   }
   string_base & operator = (const wd32_string & str)
   {
      if constexpr (sizeof(CHARACTER) == sizeof(wd32_character))
      {
         NATURAL_POINTER::operator=(str);
      }
      else
      {
         assign(str);
      }
      return *this;
   }
   string_base & operator = (string_base && string_base) { NATURAL_POINTER::operator=(::move(string_base)); return *this; }
   string_base & operator = (ansi_character ansich) { assign(ansich); return *this; }
   string_base & operator = (wd16_character wd16ch) { assign(wd16ch); return *this; }
   string_base & operator = (wd32_character wd32ch) { assign(wd32ch); return *this; }
   string_base & operator = (const ansi_character * pansisz) { assign(pansisz); return *this; }
   string_base & operator = (const wd16_character * pwd16sz) { assign(pwd16sz); return *this; }
   string_base & operator = (const wd32_character * pwd32sz) { assign(pwd32sz); return *this; }
   string_base & operator = (const ::atom & atom);
   string_base & operator = (const ::payload & payload);
   string_base & operator = (const ::property & property);


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
   inline void construct2(const ::range < const CHARACTER2 * > & str);
   template < primitive_character CHARACTER2 >
   inline void construct2(const ::range < const CHARACTER2 * > & str, strsize count);
   template < primitive_character CHARACTER2 >
   inline void construct2(const ::range < const CHARACTER2 * > & str, strsize start, strsize count);

   strsize offset_of(const CHARACTER * p) const { return ::offset_of(p, data()); }

   template < primitive_character CHARACTER2 >
   strsize start_count_length(strsize & start, strsize & count, const CHARACTER2 * pszSource);
   void start_count(strsize & start, strsize & count, strsize len);

   inline const string_base & to_string() const { return *this; }

   inline CHARACTER * data() { return (CHARACTER *)this->begin(); }

   inline const CHARACTER * data() const { return this->begin(); }

   inline const CHARACTER * c_str() const { return this->data(); }

   inline const CHARACTER * c_str_for_printf() const { return this->data(); }

   inline operator const CHARACTER * () const { return this->data(); }

   inline operator CHARACTER * () { return this->data(); }

   inline const CHARACTER * ptr_at(::index i) { return this->data() + i; }
   inline const CHARACTER * ptr_at(::index i) const { return this->data() + i; }

   inline const CHARACTER * reverse_ptr(::index i) { return this->data() + length() + i; }
   inline const CHARACTER * reverse_ptr(::index i) const { return this->data() + length() + i; }

   inline const CHARACTER & operator [](index i) const { return this->data()[i]; }

   //#if OSBIT == 64
   //   inline const CHARACTER & operator [](int i) const { return this->data()[i]; }
   //#endif

   inline CHARACTER get_at(strsize i) const { return this->data()[i]; }

   //inline operator const CONST_STRING_RANGE & () const noexcept { return this->data(); }

//#if defined(_UWP)
   //inline operator String ^ () const { return ref memory_new String(wd16_string(*this)); }
//#endif

   string_base to_string_base() const { return *this; }
   const RANGE & to_string_base() { return *this; }

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
      //string_base & operator = (const ansi_string & ansistr);
      //string_base & operator = (const wd16_string & wd16str);
      //string_base & operator = (const wd32_string & wd32str);
      //template < primitive_character CHARACTER2 >
      //string_base & operator = (const ::string_range < const CHARACTER2 * > & str);
      //string_base & operator = (string_base && str);
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
      //string_base & operator += (const ::ansi_character * pszsrc);
      //string_base & operator += (const CHARACTER * pszsrc);
      //string_base & operator += (const ::wd32_character * pszsrc);
   string_base & operator += (const string_base & str);
   //string_base & operator += (const string_base &str);
   //string_base & operator += (const const_wd16_raw_range & ansirange);
   //string_base & operator += (const const_wd32_raw_range & ansirange);
//   string_base & operator += (const inline_number_string & inlinenumberstring);
   //string_base & operator += (CHARACTER ansich);
//   string_base & operator += (::wd16_character wd16ch);
//   string_base & operator += (::wd32_character wd32ch);
//   string_base & operator += (const ::atom & atom);
//   string_base & operator += (const ::payload & payload);
//   string_base & operator += (const ::property & property);
//   template < has_as_string HAS_AS_STRING >
//   string_base & operator += (const HAS_AS_STRING & has_as_string) { return operator+=(has_as_string.as_string()); }


//   template < int t_nSize >
//   inline string_base & operator +=(const static_string<CHARACTER, t_nSize > & ansistrSrc);
//
//   template < typename TYPE >
//   inline string_base & operator +=(const TYPE & t);
//

   // maybe it doesn't because of ambiguity with global
   // + operators... (in all compilers MSVC++, LLVM, GCC...)
   //template < typename TYPE >
   //inline string_base operator +(const TYPE & t) const;

   // maybe it doesn't because of ambiguity with global
   // + operators... (in all compilers MSVC++, LLVM, GCC...)
   //inline string_base operator +(const ::string_base < CHARACTER > & str) const;

   // so exhaustively implementing them at least
   // for most relevant and proper acme types
   //string_base operator + (::const_ansi_raw_range ansirange) const;
   //string_base operator + (::const_wd16_raw_range wd16range) const;
   //string_base operator + (::const_wd32_raw_range wd32range) const;
   //string_base operator + (const ansi_string & ansistr) const;
   //string_base operator + (const wd16_string & wd16str)  const;
   //string_base operator + (const wd32_string & wd32str)  const;
   //string_base operator + (const inline_number_string & inlinenumberstring) const;
   //string_base operator + (::ansi_character ansich)  const;
   //string_base operator + (::wd16_character wd16ch)  const;
   //string_base operator + (::wd32_character wd32ch)  const;
   //template < primitive_character CHARACTER2 >
   //string_base operator + (const array_range < CHARACTER2 > & block)  const { return *this + string_base(block); }


   operator ::block() const { return { (::byte *)c_str(), length_in_bytes() }; }
   //template < primitive_payload PAYLOAD >
   //string_base operator + (const PAYLOAD & payload) const { return *this + payload.as_string(); }

   //template < primitive_atom ATOM >
   //string_base operator + (const ATOM & atom) const { return *this + atom.as_string(); }


   template < typename TYPE >
   inline string_base & operator /=(const TYPE & t)
      //  template < typename TYPE >
     //inline string_base & operator /=(const ::string_base < CHARACTER > & str)
   {

      string_base strRight(t);

      trim_right(string_base("\\/"));

      strRight.trim_left(string_base("\\/"));

      return this->operator += ("/" + strRight);

   }


   template < typename TYPE >
   inline string_base operator /(const TYPE & t) const
      //inline string_base operator /(const ::string_base < CHARACTER > & str) const
   {

      string_base strRight(t);

      string_base str(*this);

      str /= strRight;

      return str;

   }

   inline string_base & assign(const string_base & str);
   inline string_base & assign(string_base && str);

   //   template < primitive_character CHARACTER2 >
   //   inline string_base& assign(const ::string_range < const CHARACTER2 * > & str);
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
   inline string_base & assign(const CHARACTER2 * pszSrc, strsize start, strsize len);
   //inline string_base& assign(const wd16_string& wd16str, strsize pos, strsize n);
   //inline string_base& assign(const wd32_string& wd32str, strsize pos, strsize n);
   template < primitive_character CHARACTER2 >
   inline string_base & assign(const CHARACTER2 * pszSrc, strsize len)
   {
      return assign(pszSrc, 0, len);
   }
   //template < primitive_block BLOCK >
   //inline string_base& assign(const BLOCK & pszSrc, strsize start, strsize len);
   template < primitive_character CHARACTER2 >
   inline string_base & _assign(const CHARACTER2 * pszSrc, strsize start, strsize len);
   //inline string_base& assign(const ::wd16_character* pwd16szSrc, strsize len);
   //inline string_base& assign(const ::wd32_character* pwd32szSrc, strsize len);
   template < primitive_character CHARACTER2 >
   inline string_base & assign(CHARACTER2 chSrc, strsize repeat);
   //   inline string_base & assign(::ansi_character ansich, strsize repeat);
   //   inline string_base & assign(::wd16_character wd16ch, strsize repeat);
   //   inline string_base & assign(::wd32_character wd32ch, strsize repeat);

   template <class InputIterator>
   inline string_base & assign(InputIterator first, InputIterator last);

   //template < int t_nSize >
   //inline string_base & assign(const static_string<CHARACTER, t_nSize > & ansistrSrc);

   inline string_base & append(strsize len, CHARACTER ch);

   inline string_base & append_character(::wd32_character wch);
   inline string_base & append_character(::ansi_character ch);
   inline string_base & append_character(::wd16_character wch);


   inline string_base & append(const ::const_ansi_raw_range & str);
   inline string_base & append(const ::const_wd16_raw_range & str);
   inline string_base & append(const ::const_wd32_raw_range & str);
   //inline string_base & append(const ::ansi_character * pszSrc);
   template < primitive_character CHARACTER2 >
   inline string_base & append(const CHARACTER2 * pszSrc, strsize nLength);
   //inline string_base & append(const ansi_string & ansistrSrc);

   //inline string_base & append(const ::wd16_character * pszSrc);
   //inline string_base & append(const ::wd16_character * pszSrc, strsize nLength);
   //inline string_base & append(const wd16_string & ansistrSrc);

   //inline string_base & append(const ::wd32_character * pszSrc);
   //inline string_base & append(const ::wd32_character * pszSrc, strsize nLength);
   //inline string_base & append(const wd32_string & ansistrSrc);

   //template < typename STATIC_TYPE_CHAR, int t_nSize >
   //inline string_base& append(const static_string<STATIC_TYPE_CHAR, t_nSize > & ansistrSrc);



   inline void Empty()
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


   inline strsize get_upper_bound(strsize i = -1) const noexcept { return this->size() + i; }

   inline void get_string(CHARACTER * psz) const noexcept;

   inline const CHARACTER * get_string() const noexcept { return this->data(); }

   inline bool is_empty() const noexcept { return *this->data() == '\0'; }

   inline bool is_empty(const string_base & str)
   {
      if (!is_empty()) return false;
      operator =(str);
      return true;
   }

   inline static string_base empty_string() { return string_base(); }

   inline void empty() { Empty(); }

   inline bool has_char() const noexcept { return !this->is_empty(); }

   string_base & release_string_buffer(strsize nNewLength = -1);
   //   inline void release_string_buffer(strsize nNewLength);
   inline void truncate(strsize nNewLength);
   inline void erase_beginning(strsize i);

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

   string_base if_empty(string_base ansistr) { return is_empty() ? ansistr : *this; }


   //#if defined(_UWP) && defined(__cplusplus_winrt)
   //   inline operator String ^ () const;
   //   inline operator String ^ ();
   //#endif
   //

      //void construct() noexcept;


   void push_back(CHARACTER ch);


   bool equals(const string_base & str) const noexcept;
   bool case_insensitive_equals(const string_base & str) const noexcept;

   bool equasl(const string_base & str, strsize n) const noexcept;
   bool case_insensitive_equals(const string_base & str, strsize n) const noexcept;

   bool equals(strsize iStart, strsize iCount, const string_base & str) const noexcept;
   bool case_insensitive_equals(strsize iStart, strsize iCount, const string_base & str) const noexcept;

   bool equals(strsize iStart, strsize iCount, const string_base & str, strsize iStart2, strsize iCount2) const noexcept;
   bool case_insensitive_equals(strsize iStart, strsize iCount, const string_base & str, strsize iStart2, strsize iCount2) const noexcept;


   //::std::strong_ordering order(const string_base &str) const noexcept;
   //using NATURAL_POINTER::order;

   ::std::strong_ordering order(const string_base & str) const noexcept;
   ::std::strong_ordering case_insensitive_order(const string_base & str) const noexcept;
   ::std::strong_ordering collate(const string_base & str) const noexcept;
   ::std::strong_ordering case_insensitive_collate(const string_base & str) const noexcept;

   ::std::strong_ordering order(const string_base & str, strsize n) const noexcept;
   ::std::strong_ordering case_insensitive_order(const string_base & str, strsize n) const noexcept;
   ::std::strong_ordering collate(const string_base & str, strsize n) const noexcept;
   ::std::strong_ordering case_insensitive_collate(const string_base & str, strsize n) const noexcept;

   ::std::strong_ordering order(strsize iStart, strsize iCount, const string_base & str) const noexcept;
   ::std::strong_ordering case_insensitive_order(strsize iStart, strsize iCount, const string_base & str) const noexcept;
   ::std::strong_ordering collate(strsize iStart, strsize iCount, const string_base & str) const noexcept;
   ::std::strong_ordering case_insensitive_collate(strsize iStart, strsize iCount, const string_base & str) const noexcept;

   ::std::strong_ordering order(strsize iStart, strsize iCount, const string_base & str, strsize iStart2, strsize iCount2) const noexcept;
   ::std::strong_ordering case_insensitive_order(strsize iStart, strsize iCount, const string_base & str, strsize iStart2, strsize iCount2) const noexcept;
   ::std::strong_ordering collate(strsize iStart, strsize iCount, const string_base & str, strsize iStart2, strsize iCount2) const noexcept;
   ::std::strong_ordering case_insensitive_collate(strsize iStart, strsize iCount, const string_base & str, strsize iStart2, strsize iCount2) const noexcept;

   //inline int operator<=>(const string_base &str) const { return order(str); }
   //inline bool operator==(const string_base &str) const { return size() != str.size() ? false : !order(str); }
   //inline bool operator>(const string_base &str) const { return order(ansistr) > 0; }
   //inline bool operator<(const string_base &str) const { return order(ansistr) < 0; }
   //inline bool operator!=(const string_base &str) const { return !operator ==(ansistr); }
   //inline bool operator>=(const string_base &str) const { return !operator <(ansistr); }
   //inline bool operator<=(const string_base &str) const { return !operator >(ansistr); }


   //inline bool operator==(const string_base &str) const { return order(ansistr) == 0; }
   //inline bool operator>(const string_base &str) const { return order(ansistr) > 0; }
   //inline bool operator<(const string_base &str) const { return order(ansistr) < 0; }
   //inline bool operator!=(const string_base &str) const { return !operator ==(ansistr); }
   //inline bool operator>=(const string_base &str) const { return !operator <(ansistr); }
   //inline bool operator<=(const string_base &str) const { return !operator >(ansistr); }


   inline bool contains(CHARACTER ch, strsize start = 0, strsize count = -1) const;
   inline bool contains(const string_base & str, strsize start = 0, strsize count = -1) const;
   //inline bool contains(const string_base &str, strsize start = 0, strsize count = -1) const;
   inline bool contains(CHARACTER ch, strsize start, strsize count, const CHARACTER ** ppszBeg) const;
   inline bool contains(const string_base & str, strsize start, strsize count, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd = nullptr) const;
   //inline bool contains(const string_base &str, strsize start, strsize count, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd = nullptr) const;

   template < primitive_array STRING_ARRAY >
   inline bool contains_any(const STRING_ARRAY & stra) const;

   template < primitive_array STRING_ARRAY >
   inline bool contains_all(const STRING_ARRAY & stra) const;

   inline bool contains_ci(CHARACTER ch, strsize start = 0, strsize count = -1) const;
   inline bool contains_ci(const string_base & str, strsize start = 0, strsize count = -1) const;
   //inline bool contains_ci(const string_base &str, strsize start = 0, strsize count = -1) const;
   inline bool contains_ci(CHARACTER ch, strsize start, strsize count, const CHARACTER ** ppszBeg) const;
   inline bool contains_ci(const string_base & str, strsize start, strsize count, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd = nullptr) const;
   //inline bool contains_ci(const string_base &str, strsize start, strsize count, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd = nullptr) const;

   template < primitive_array STRING_ARRAY >
   inline bool contains_any_ci(const STRING_ARRAY & stra) const;

   template < primitive_array STRING_ARRAY >
   inline bool contains_all_ci(const STRING_ARRAY & stra) const;


   //inline bool contains_wci(CHARACTER ch, strsize start = 0, strsize count = -1) const;
   inline bool contains_wci(const string_base & str, strsize start = 0, strsize count = -1) const;
   //inline bool contains_wci(const string_base &str, strsize start = 0, strsize count = -1) const;
   //inline bool contains_wci(CHARACTER ch, strsize start, strsize count, const CONST_STRING_RANGE &* ppszBeg) const;
   inline bool contains_wci(const string_base & str, strsize start, strsize count, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd = nullptr) const;
   //inline bool contains_wci(const string_base &str, strsize start, strsize count, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd = nullptr) const;

   template < primitive_array STRING_ARRAY >
   inline bool contains_any_wci(const STRING_ARRAY & stra) const;

   template < primitive_array STRING_ARRAY >
   inline bool contains_all_wci(const STRING_ARRAY & stra) const;


   void reserve(strsize res_arg = 0);

   // Delete 'nCount' characters, starting at index 'iIndex'
   string_base & erase(strsize iIndex = 0, strsize nCount = -1);

   //string_base& erase(strsize start = 0, strsize count = -1);


   template < typename PRED >
   bool is_every_char(PRED pred)
   {

      for (index i = 0; i < this->length(); i++)
      {

         if (!pred(this->operator[](i)))
         {

            return false;

         }

      }

      return true;

   }


   template < typename NUMBER >
   NUMBER & translate_index(NUMBER & number)
   {

      if (number < 0)
      {

         number += this->size() + 1;

         if (number < 0)
         {

            number = 0;

         }

      }
      else if (number > this->size())
      {

         number = this->size();

      }

      return number;

   }

   // Insert character 'ch' before index 'iIndex'
   strsize Insert(strsize iIndex, CHARACTER ch);

   // Insert string_base 'psz' before index 'iIndex'
   strsize Insert(strsize iIndex, const string_base & str);

   // replace all occurrences of character 'chOld' with character 'chNew'
   strsize replace_character(CHARACTER charNew, CHARACTER charOld, strsize iStart = 0);


   template < ::comparison::equality < CHARACTER > EQUALITY >
   ::count _occurrence_count_of(const THIS_RAW_RANGE & range, strsize start, EQUALITY equality)
   {

      strsize nLen = range.size();

      strsize count = 0;

      RANGE rangeThis(this->begin() + start, this->end());

      while ((rangeThis.begin() = rangeThis.find(range, equality)) != nullptr)
      {

         count++;

         rangeThis.begin() += nLen;

      }

      return count;

   }


   ::count occurrence_count_of(const THIS_RAW_RANGE & range, strsize start = 0)
   {

      return _occurrence_count_of(range, start, ::comparison::comparison<CHARACTER>());

   }

   ::count case_insensitive_occurrence_count_of(const THIS_RAW_RANGE & range, strsize start = 0)
   {

      return _occurrence_count_of(range, start, ::comparison::case_insensitive<CHARACTER>());

   }


   // replace all occurrences of string_base 'pszOld' with string_base 'pszNew'
   template < ::comparison::equality < CHARACTER > EQUALITY >
   strsize _replace_with(const THIS_RAW_RANGE & rangeNew, const THIS_RAW_RANGE & rangeOld, strsize start, EQUALITY equality)
   {

      // nSourceLen is in XCHARs
      strsize nSourceLen = rangeOld.size();

      if (nSourceLen == 0)
      {

         return(0);

      }

      // nReplacementLen is in XCHARs
      strsize nReplacementLen = rangeNew.size();

      // loop once to figure out the size_i32 of the result string_base < ITERATOR_TYPE >
      auto count = _occurrence_count_of(rangeOld, start, equality);

      // if any changes were made, make them
      if (count > 0)
      {

         // if the buffer is too small, just
         //   allocate a memory_new buffer (slow but sure)
         strsize nOldLength = size();

         strsize nNewLength = nOldLength + (nReplacementLen - nSourceLen) * count;

         CHARACTER * pszBuffer = get_string_buffer(maximum(nNewLength, nOldLength));

         RANGE range(pszBuffer, pszBuffer + nOldLength);

         // loop again to actually do the work
         while (range.begin() < range.end())
         {

            CHARACTER * pszTarget;

            while ((pszTarget = (CHARACTER *)range.find(rangeOld, equality)) != nullptr)
            {

               strsize nBalance = nOldLength - strsize(pszTarget - pszBuffer + nSourceLen);

               memmove(pszTarget + nReplacementLen, pszTarget + nSourceLen, nBalance * sizeof(CHARACTER));

               memcpy(pszTarget, rangeNew.begin(), nReplacementLen * sizeof(CHARACTER));

               range.m_begin = pszTarget + nReplacementLen;

               pszTarget[nReplacementLen + nBalance] = 0;

               nOldLength += (nReplacementLen - nSourceLen);

            }

            range.m_begin += string_safe_length(range.m_begin) + 1;

         }

         ASSERT(pszBuffer[nNewLength] == 0);

         release_string_buffer(nNewLength);

      }

      return count;

   }


   strsize replace_with(const THIS_RAW_RANGE & rangeNew, const THIS_RAW_RANGE & rangeOld, strsize start = 0)
   {

      return _replace_with(rangeNew, rangeOld, start, comparison::comparison<CHARACTER>());

   }


   strsize case_insensitive_replace_with(const THIS_RAW_RANGE & rangeNew, const THIS_RAW_RANGE & rangeOld, strsize start = 0)
   {

      return _replace_with(rangeNew, rangeOld, start, ::comparison::case_insensitive<CHARACTER>());

   }

   // replace all occurrences of string_base 'pszOld' with string_base 'pszNew'
   //template < raw_pointer_castable < CHARACTER_TYPE > PCHARNEW, raw_pointer_castable < CHARACTER_TYPE > PCHAROLD >

   ::count replace_with_count(const string_base & strNew, const string_base & strOld, strsize iStart = 0);

   //template < raw_pointer_castable < CHARACTER_TYPE > PCHARNEW, raw_pointer_castable < CHARACTER_TYPE > PCHAROLD >

   ::count replace_with_ci_count(const string_base & strNew, const string_base & strOld, strsize iStart = 0);

   // replace all occurrences of character 'chOld' with character 'chNew'
   strsize find_replace(CHARACTER charOld, CHARACTER charNew, strsize iStart = 0)
   {
      return replace_with(charNew, charOld, iStart);
   }

   // replace all occurrences of string_base 'pszOld' with string_base 'pszNew'
   //template < raw_pointer_castable < CHARACTER_TYPE > PCHAROLD, raw_pointer_castable < CHARACTER_TYPE > PCHARNEW >
   strsize find_replace(const THIS_RAW_RANGE & rangeOld, const THIS_RAW_RANGE & rangeNew, strsize start = 0)
   {
      return _replace_with(rangeNew, rangeOld, start, comparison::comparison<CHARACTER>());
   }

   //template < raw_pointer_castable < CHARACTER_TYPE > PCHAROLD, raw_pointer_castable < CHARACTER_TYPE > PCHARNEW >
   strsize case_insensitive_find_replace(const THIS_RAW_RANGE & rangeOld, const THIS_RAW_RANGE & rangeNew, strsize start = 0)
   {
      return _replace_with(rangeNew, rangeOld, start, comparison::case_insensitive<CHARACTER>());
   }

   // replace all occurrences of string_base 'pszOld' with string_base 'pszNew'
   //template < raw_pointer_castable < CHARACTER_TYPE > PCHAROLD, raw_pointer_castable < CHARACTER_TYPE > PCHARNEW >
   ::count find_replace_count(const string_base & strOld, const string_base & strNew, strsize iStart = 0)
   {
      return replace_with_count(strNew, strOld, iStart);
   }

   //template < raw_pointer_castable < CHARACTER_TYPE > PCHAROLD, raw_pointer_castable < CHARACTER_TYPE > PCHARNEW >
   ::count find_replace_ci_count(const string_base & strOld, const string_base & strNew, strsize iStart = 0)
   {
      return replace_with_ci_count(strNew, strOld, iStart);
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

   //::count utf8_replace(const string_base &strOld, const string_base &strNew, strsize iStart = 0);

   string_base & replace(strsize iStart, strsize nCount, const string_base & str);
   string_base & replace(strsize iStart, strsize nCount, const string_base & str, strsize nLen);

   // erase all occurrences of character 'chRemove'
   strsize erase_character(CHARACTER chRemove);

   string_base Tokenize(const string_base & strTokens, strsize & iStart) const;


   // find routines

   // find the first occurrence of character 'ch', starting at index 'iStart'
   strsize find(CHARACTER ch) const RELEASENOTHROW;
   strsize find(CHARACTER ch, strsize start) const RELEASENOTHROW;
   strsize find(CHARACTER ch, strsize start, strsize count) const RELEASENOTHROW;
   strsize case_insensitive_find(CHARACTER ch, strsize start = 0, strsize count = -1) const RELEASENOTHROW;

   strsize find_skip_or_length(CHARACTER ch, strsize start = 0) const RELEASENOTHROW
   {

      while (true)
      {

         if (this->data()[start] == '\0')
         {

            return start;

         }

         if (this->data()[start] == ch)
         {

            start++;

            return start;

         }

         start++;

      }

   }

   strsize scan_whitespace(strsize start = 0) const RELEASENOTHROW;
   strsize span_whitespace(strsize start = 0) const RELEASENOTHROW;
   strsize rear_scan_whitespace(strsize start = 0) const RELEASENOTHROW;
   strsize rear_span_whitespace(strsize start = 0) const RELEASENOTHROW;

   // look for a specific sub-string_base

   //bool _find_prefix(strsize & i, const string_base &str, strsize & start, strsize count, strsize & blockLen, strsize & nEndPosition, const CHARACTER ** ppszTail) const RELEASENOTHROW;

   // find the first occurrence of string_base 'block', starting at index 'iStart'
   strsize find(const string_base & str, strsize start = 0, strsize count = -1) const RELEASENOTHROW;
   strsize case_insensitive_find(const string_base & str, strsize start = 0, strsize count = -1) const RELEASENOTHROW;
   strsize unicode_find(const string_base & str, strsize start = 0, strsize count = -1) const RELEASENOTHROW;
   strsize case_insensitive_unicode_find(const string_base & str, strsize start = 0, strsize count = -1) const RELEASENOTHROW;

   // find the first occurrence of string_base 'block', starting at index 'iStart', if found returns the index of first character after the end of the found string_base
   strsize rear_find(const string_base & str, strsize start, strsize count) const RELEASENOTHROW;
   strsize rear_case_insensitive_find(const string_base & str, strsize start = 0, strsize count = -1) const RELEASENOTHROW;
   strsize rear_unicode_find(const string_base & str, strsize start = 0, strsize count = -1) const RELEASENOTHROW;
   strsize rear_case_insensitive_unicode_find(const string_base & str, strsize start = 0, strsize count = -1) const RELEASENOTHROW;

   // find the first occurrence of any of the characters in string_base 'pszCharSet'
   strsize scan(const THIS_RAW_RANGE & rangeCharacters, strsize iStart = 0) const RELEASENOTHROW;
   strsize scan(const THIS_RAW_RANGE & rangeCharacters, strsize iStart, strsize n) const RELEASENOTHROW;
   strsize scan(const CHARACTER * blockCharacters, strsize iStart = 0) const RELEASENOTHROW;

   strsize _scan(const THIS_RAW_RANGE & rangeCharacters, strsize iStart = 0) const RELEASENOTHROW;
   strsize _scan(const THIS_RAW_RANGE & rangeCharacters, strsize iStart, strsize n) const RELEASENOTHROW;
   strsize _scan(const CHARACTER * blockCharacters, strsize iStart = 0) const RELEASENOTHROW;

   strsize find_first(CHARACTER chSeparator, strsize iStart = 0) const RELEASENOTHROW;

   //strsize find_first_in(const string_base &str, strsize pos = 0) const RELEASENOTHROW;
   //strsize find_first_in(const string_base &str, strsize pos, strsize n) const RELEASENOTHROW;
   ////strsize find_first_in(const string_base &str, strsize pos = 0) const RELEASENOTHROW;
   //strsize find_first_in(CHARACTER ca, strsize pos = 0) const RELEASENOTHROW;

   strsize span(const THIS_RAW_RANGE & rangeCharacters, strsize pos = 0) const RELEASENOTHROW;
   strsize span(const THIS_RAW_RANGE & rangeCharacters, strsize pos, strsize n) const RELEASENOTHROW;
   strsize span(const CHARACTER * pszCharacters, strsize pos = 0) const RELEASENOTHROW;
   strsize skip(CHARACTER chSkip, strsize pos = 0) const RELEASENOTHROW;

   strsize _span(const THIS_RAW_RANGE & rangeCharacters, strsize pos = 0) const RELEASENOTHROW;
   strsize _span(const THIS_RAW_RANGE & rangeCharacters, strsize pos, strsize n) const RELEASENOTHROW;
   strsize _span(const CHARACTER * pszCharacters, strsize pos = 0) const RELEASENOTHROW;
   strsize _skip(CHARACTER chSkip, strsize pos = 0) const RELEASENOTHROW;

   //strsize get_token(const string_base &strSeparators, strsize pos = -1) const RELEASENOTHROW;
   //strsize get_token(const string_base &strSeparators, strsize pos, strsize n) const RELEASENOTHROW;
   //strsize get_token(const CHARACTER * pszSeparators, strsize pos = -1) const RELEASENOTHROW;
   //strsize get_token(CHARACTER chSeparator, strsize pos = -1) const RELEASENOTHROW;

   //strsize _get_token(const string_base &strSeparators, strsize pos = -1) const RELEASENOTHROW;
   //strsize _get_token(const string_base &strSeparators, strsize pos, strsize n) const RELEASENOTHROW;
   //strsize _get_token(const CHARACTER * pszSeparators, strsize pos = -1) const RELEASENOTHROW;
   //strsize _get_token(CHARACTER chSeparator, strsize pos = -1) const RELEASENOTHROW;

   //strsize find_last_not_in(const string_base &str, strsize pos = -1) const RELEASENOTHROW;
   //strsize find_last_not_in(const string_base &str, strsize pos, strsize n) const RELEASENOTHROW;
   ////strsize find_last_not_in(const string_base &str, strsize pos = -1) const RELEASENOTHROW;
   //strsize find_last_not_in(CHARACTER ca, strsize pos = -1) const RELEASENOTHROW;

   strsize rear_scan(const THIS_RAW_RANGE & rangeCharacters, strsize count = -1) const RELEASENOTHROW;
   strsize rear_scan(const THIS_RAW_RANGE & rangeCharacters, strsize iStart, strsize n) const RELEASENOTHROW;
   //strsize rear_scan(const CHARACTER * blockCharacters, strsize count = -1) const RELEASENOTHROW;

   strsize _rear_scan(const THIS_RAW_RANGE & rangeCharacters, strsize count = -1) const RELEASENOTHROW;
   strsize _rear_scan(const THIS_RAW_RANGE & rangeCharacters, strsize iStart, strsize n) const RELEASENOTHROW;
   //strsize _rear_scan(const CHARACTER * blockCharacters, strsize iStart = -1) const RELEASENOTHROW;

   //strsize find_first_of(const string_base &str, strsize pos = 0) const RELEASENOTHROW;
   //strsize find_first_of(const string_base &str, strsize pos, strsize n) const RELEASENOTHROW;
   //strsize find_first_of(const CHARACTER * pszCharacters, strsize iStart = 0) const RELEASENOTHROW;
   //strsize find_first_of(CHARACTER ca, strsize pos = 0) const RELEASENOTHROW;
   //strsize find_first_of(CHARACTER ca, strsize pos, strsize count) const RELEASENOTHROW;

   //strsize find_first_not_of(const string_base &str, strsize pos = 0) const RELEASENOTHROW;
   //strsize find_first_not_of(const string_base &str, strsize pos, strsize n) const RELEASENOTHROW;
   //strsize find_first_not_of(const string_base &str, strsize pos = 0) const RELEASENOTHROW;
   //strsize find_first_not_of(CHARACTER ca, strsize pos = 0) const RELEASENOTHROW;

   strsize rear_span(const string_base & str, strsize count = -1) const RELEASENOTHROW;
   strsize rear_span(const string_base & str, strsize start, strsize count = -1) const RELEASENOTHROW;
   //strsize rear_span(const CHARACTER * psz, strsize pos = -1) const RELEASENOTHROW;

   strsize rear_skip(CHARACTER ca, strsize count = -1) const RELEASENOTHROW;
   strsize rear_skip(CHARACTER ca, strsize start, strsize count = -1) const RELEASENOTHROW;


   strsize _rear_span(const string_base & str, strsize count = -1) const RELEASENOTHROW;
   strsize _rear_span(const string_base & str, strsize pos, strsize n) const RELEASENOTHROW;


   strsize _rear_span(CHARACTER ca, strsize count = -1) const RELEASENOTHROW;
   strsize _rear_span(CHARACTER ca, strsize start, strsize count = -1) const RELEASENOTHROW;


   //strsize _rear_span(const CHARACTER * psz, strsize pos = -1) const RELEASENOTHROW;
   //strsize _rear_skip(CHARACTER ca, strsize pos = -1) const RELEASENOTHROW;


   //strsize find_last_of(const string_base &str, strsize pos = -1) const RELEASENOTHROW;
   //strsize find_last_of(const string_base &str, strsize pos, strsize n) const RELEASENOTHROW;
   ////strsize find_last_of(const string_base &str, strsize pos = -1) const RELEASENOTHROW;
   //strsize find_last_of(CHARACTER ca, strsize pos = -1) const RELEASENOTHROW;

   // find the last occurrence of character 'ch'
   strsize rear_find(CHARACTER ch, strsize iStart = -1) const RELEASENOTHROW;

   // find the last occurrence of string_base 'sz'
   strsize rear_find(const string_base & str, strsize iStart = -1) const RELEASENOTHROW;

   //strsize rear_find(CHARACTER ch, strsize iStart = -1) const RELEASENOTHROW
   //{
   //   return rear_find(ch, iStart);
   //};
   //strsize rear_find(const string_base &str, strsize iStart = -1) const RELEASENOTHROW
   //{
   //   return rear_find(sz, iStart);
   //};

   string_base intersection(const string_base & str) const;


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

      return data();

   }


   unicode_iterator < CHARACTER > unicode_end() const
   {

      return data() + size();

   }


   //inline bool begins(const CHARACTER * pszPrefix) const;

   //inline bool begins(const string_base &strPrefix) const;
   //inline bool ends(const string_base &strSuffix) const;

   inline bool case_insensitive_begins(const string_base & strPrefix) const;
   inline bool case_insensitive_ends(const string_base & strSuffix) const;

   inline bool begins_eat(const string_base & str);
   inline bool ends_eat(const string_base & str);

   inline bool case_insensitive_begins_eat(const string_base & str);
   inline bool case_insensitive_ends_eat(const string_base & str);

   inline bool begins_eat(string_base & strRest, const string_base & str) const;
   inline bool ends_eat(string_base & strRest, const string_base & str) const;

   inline bool case_insensitive_begins_eat(string_base & strRest, const string_base & str) const;
   inline bool case_insensitive_ends_eat(string_base & strRest, const string_base & str) const;

   inline bool begins_eaten_ci(string_base & strEaten, const string_base & str) const;
   inline bool ends_eaten_ci(string_base & strEaten, const string_base & str) const;

   inline string_base & ensure_begins(const string_base & str);
   inline string_base & ensure_begins_ci(const string_base & str);

   inline string_base & ensure_ends(const string_base & str);
   inline string_base & ensure_ends_ci(const string_base & str);

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

   bool eat_before(string_base & strBefore, const string_base & strSeparator, bool bEatEverythingIfNotFound = false);
   bool eat_before_let_separator(string_base & strBefore, const string_base & strSeparator, bool bEatEverythingIfNotFound = false);

   CHARACTER last_char(strsize count = -1) const;

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
   string_base & trim(const string_base & strTargets);

   // trimming anything (either side)

   // erase all trailing occurrences of character 'chTarget'
   string_base & trim_right(CHARACTER chTarget);

   // erase all trailing occurrences of any of the characters in string_base 'pszTargets'
   ///template < pointer_castable < CHARACTER > PCHAR >
   //string_base & trim_right(PCHAR pcharTargets);
   string_base & trim_right(const THIS_RAW_RANGE & rangeTargets);

   // erase all leading occurrences of character 'chTarget'
   string_base & trim_left(CHARACTER chTarget);

   // erase all leading occurrences of any of the characters in string_base 'pszTargets'
   //template < pointer_castable < CHARACTER > PCHAR >
   //string_base& trim_left(PCHAR pchTargets);
   string_base & trim_left(const THIS_RAW_RANGE & rangeTargets);


   // erase all trailing whitespace
   string_base right_trimmed() const;

   // erase all leading whitespace
   string_base left_trimmed() const;

   // erase all leading and trailing whitespace
   string_base trimmed() const;

   // erase all leading and trailing occurrences of character 'chTarget'
   string_base trimmed(CHARACTER chTarget) const;

   // erase all leading and trailing occurrences of any of the characters in the string_base 'pszTargets'
   string_base trimmed(const string_base & strTargets) const;

   // trimming anything (either side)

   // erase all trailing occurrences of character 'chTarget'
   string_base right_trimmed(CHARACTER chTarget) const;

   // erase all trailing occurrences of any of the characters in string_base 'pszTargets'
   string_base right_trimmed(const string_base & strCharacters) const;

   // erase all leading occurrences of character 'chTarget'
   string_base left_trimmed(CHARACTER chTarget) const;

   // erase all leading occurrences of any of the characters in string_base 'pszTargets'
   string_base left_trimmed(const string_base & strTargets) const;


   // Convert the string_base to the OEM character set
   void AnsiToOem();

   // Convert the string_base to the ANSI character set
   void OemToAnsi();

   // Very simple sub-string_base extraction

   // Return the substring starting at index 'iFirst'
   string_base Mid(strsize iFirst) const;

   string_base substr(strsize iFirst) const;

   // Return the substring starting at index 'iFirst', with length 'nCount'
   string_base Mid(strsize iFirst, strsize nCount) const;


   string_base substr(strsize iFirst, strsize nCount) const;


   inline memsize get_storage_size_in_bytes() { return this->metadata()->memsize(); }
   inline strsize get_storage_length();


   inline strsize get_length() const { return (::strsize)this->metadata()->m_datasize; }
   inline memsize length_in_bytes() const;
   inline memsize length_in_bytes_with_null_terminator() const;
   inline strsize length() const { return this->get_length(); }
   inline strsize size() const { return this->length(); }

   // Return the substring consisting of the rightmost 'nCount' characters
   string_base Right(strsize nCount) const;

   // Return the substring consisting of the leftmost 'nCount' characters
   string_base Left(strsize nCount) const;

   // Return the substring consisting of the leftmost characters in the set 'pszCharSet'
   string_base scan_including(const string_base & strCharSet, strsize iStart = 0, strsize iCount = -1) const;

   // Return the substring consisting of the leftmost characters not in the set 'pszCharSet'
   string_base span_excluding(const string_base & strCharSet, strsize iStart = 0, strsize iCount = -1) const;


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



   inline strsize unichar_count() const;
   inline memsize char_type_count(strsize iChar) const;


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




   //bool equals(const string_base &str) const;
   //bool case_insensitive_equals(const string_base &str) const;

   inline bool operator==(const string_base & str) const { return this->equals(str); }
   //inline bool operator==(const string_base &str) const { return this->equals(str); }
   inline bool operator==(const CHARACTER * psz) const { return this->equals(psz); }
   inline ::std::strong_ordering operator<=>(const string_base & str) const { return this->order(str); }
   //inline ::std::strong_ordering operator<=>(const string_base &str) const { return this->order(str); }
   inline ::std::strong_ordering operator<=>(const CHARACTER * psz) const { return this->order(psz); }
   //inline int operator<=>(CHARACTER ch) const;
   //inline bool operator==(CHARACTER ch) const;
   //inline bool operator==(CHARACTER ch) const;
   //inline bool operator>(const string_base &str2) const;
   //inline bool operator>(CHARACTER ch) const;
   //inline bool operator<(const string_base &str2) const;
   //inline bool operator<(CHARACTER ch) const;
   //inline bool operator!=(const string_base &str) const { return !operator ==(psz); }
   //inline bool operator!=(CHARACTER ch) const { return !operator ==(ch); }
   //inline bool operator>=(const string_base &str) const { return !operator <(psz); }
   //inline bool operator>=(CHARACTER ch) const { return !operator <(ch); }
   //inline bool operator<=(const CHARACTER * psz) const { return !operator >(psz); }
   //inline bool operator<=(CHARACTER ch) const { return !operator >(ch); }


   typedef strsize size_type;


};



inline ::string operator + (const ::string & strA, const ::string & strB)
{

   auto str = strA;

   str += strB;

   return str;

}


inline ::string operator+(const ::string & str, const ::const_ansi_raw_range & range)
{

   return str + ::string(range);

}


inline ::string operator + (const ::string & str, char ch)
{

   return str + ::string(ch);

}


inline ::string operator +(const ::string & str, const char * psz)
{

   return str + ::string(psz);

}


template < ::count c >
inline ::string operator +(const ::string & str, const char(&sz)[c])
{

   return str + ::string(sz);

}


template < strsize m_sizeMaximumLength >
inline ::string operator +(const ::string & str, const ::inline_string < char, m_sizeMaximumLength > & inlinestring)
{

   return str + ::string(inlinestring);

}


inline ::string operator +(const char * psz, const ::string & str)
{

   return ::string(psz) + str;

}


inline ::string operator +(char ch, const ::string & str)
{

   return ::string(ch) + str;

}


template < ::count c >
inline ::string operator +(const char(&sz)[c], const ::string & str)
{

   return ::string(sz) + str;

}


template < ::count c >
inline ::string operator+(const ::const_ansi_raw_range & str, const char(&sz)[c])
{

   return ::string(str) + sz;

}


inline ::string operator+(const ::const_ansi_raw_range & range, const ::string & str)
{

   return ::string(range) + str;

}


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


inline ::wstring operator + (::wstring wstrA, ::wstring wstrB)
{

   wstrA += wstrB;

   return wstrA;

}


inline ::wstring operator +(const ::wide_character * pwsz, ::wstring wstr)
{

   return ::wstring(pwsz) + wstr;

}


template < ::count c >
inline ::wstring operator +(const ::wide_character(&wsz)[c], ::wstring wstr)
{

   return ::wstring(wsz) + wstr;

}

//
//block::block(const string_base &str)
//   
//{
//   this->m_begin = (::byte *)str.m_begin;
//   this->m_end = (::byte *) str.m_end;
//
//}


template < ::count c, strsize m_sizeMaximumLength >
inline ::string operator +(const char(&sz)[c], const ::inline_string < char, m_sizeMaximumLength > & inlinestring)
{

   return ::move(::string(sz) + ::string(inlinestring));

}



template < ::count c, strsize m_sizeMaximumLength >
inline ::string operator +(const ::inline_string < char, m_sizeMaximumLength > & inlinestring, const char(&sz)[c])
{

   return ::move(::string(inlinestring) + ::string(sz));

}



CLASS_DECL_ACME::string _(const ::string & str);



