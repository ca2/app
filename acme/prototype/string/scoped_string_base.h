// Created by camilo on 2012-12-18 18:44 <3ThomasBorregaardSorensen!!
#pragma once


template < typename ITERATOR_TYPE >
class scoped_string_base :
   public const_string_range < ITERATOR_TYPE >
{
public:

//   union
//   {
//       ::ansi_character    m_chaTempuStock[8];
//       ::wd16_character    m_shaTempoStore[4];
//       ::wd32_character    m_iaTempiWarehouse[2];
//       long long               m_llTempeMart;
//
//   };

   using PRIMITIVE_SCOPED_STRING_TAG = PRIMITIVE_SCOPED_STRING_TAG_TYPE;

   using BASE_RANGE = const_string_range < ITERATOR_TYPE >;
   using ITEM_POINTER = get_type_item_pointer< ITERATOR_TYPE>;
   using ITEM = dereference < ITEM_POINTER >;
   using CHARACTER = ITEM;
   using this_iterator = typename BASE_RANGE::this_iterator;
   using iterator = typename BASE_RANGE::iterator;
   using const_iterator = typename BASE_RANGE::const_iterator;
   using STRING = ::string_base < ITERATOR_TYPE >;


   scoped_string_base(no_initialize_t) :BASE_RANGE(no_initialize_t{}) {}
   scoped_string_base():BASE_RANGE(nullptr) {}
   scoped_string_base(nullptr_t) :BASE_RANGE(nullptr) {}
   scoped_string_base(const range < const CHARACTER * > & range) : BASE_RANGE(range) { }
   template < other_primitive_character <CHARACTER> OTHER_CHARACTER >
   scoped_string_base(const range < const OTHER_CHARACTER* >& range) : BASE_RANGE(no_initialize_t{}) { this->construct_str(range); }
   //scoped_string_base(const scoped_ansi_string & scopedstr) : BASE_RANGE(nullptr) { construct_range(scopedstr); }
   //scoped_string_base(const scoped_wd16_string & scopedstr) : BASE_RANGE(nullptr) { construct_range(scopedstr); }
   //scoped_string_base(const scoped_wd32_string & scopedstr) : BASE_RANGE(nullptr) { construct_range(scopedstr); }

   template < typed_primitive_string <CHARACTER> STRING2 >
   scoped_string_base(const STRING2& str) : 
      BASE_RANGE(no_initialize_t{})
   { 
      this->m_begin = str.m_begin;
      this->m_end = str.m_end;
      this->m_erange = str.m_erange;
   }
   template < other_primitive_string <CHARACTER> STRING2 >
   scoped_string_base(const STRING2& str) : 
      BASE_RANGE(no_initialize_t{})
   {
      //construct_range(str);
      this->str(str);

   }

   //template < typename ITERATOR_TYPE2, int t_size >
   //scoped_string_base(const const_string_range_static_array<ITERATOR_TYPE2, t_size >& a) : 
   //   BASE_RANGE(no_initialize_t{}) 
   //{ 
   //
   //   this->str(a);
   //
   //}

   template < has_as_string HAS_AS_STRING >
   scoped_string_base(const HAS_AS_STRING & has_as_string) : BASE_RANGE(nullptr) { this->str(has_as_string.as_string()); }

   template < has_get_string HAS_GET_STRING >
   scoped_string_base(const HAS_GET_STRING & has_get_string) : BASE_RANGE(nullptr) { this->str(has_get_string.get_string()); }

//   template < primitive_character CHARACTER2 >
//   scoped_string_base(CHARACTER2 character) : BASE_RANGE(no_initialize_t{})
//   {
//      if constexpr(sizeof(CHARACTER2) == 1 && sizeof(CHARACTER) == 1)
//      {
//         m_chaTempuStock[0] =character;
//         this->m_begin = m_chaTempuStock;
//         this->m_end = this->m_begin + 1;
//
//      } else {
//         auto len = utf_to_utf_length(m_chaTempuStock, &character, 1);
//         utf_to_utf(m_chaTempuStock, &character, 1);
//         this->m_begin = m_chaTempuStock;
//         this->m_end = this->m_begin + len;
//      }
//   }

   //template < character_range_not_string_neither_scoped_string CHARACTER_RANGE >
   //scoped_string_base(const CHARACTER_RANGE & range) : BASE_RANGE(nullptr) { construct_range(range); }

    //   scoped_string_base(const ::block & block) :m_str(e_zero_initialize), BASE_RANGE((const_iterator)block.begin(), (const_iterator)block.end()) {}
//   scoped_string_base(const ::ansi_character ch) :m_str(ch), BASE_RANGE(m_str) { }
//   scoped_string_base(const ::wd16_character ch) :m_str(ch), BASE_RANGE(m_str) { }
//   scoped_string_base(const ::wd32_character ch) :m_str(ch), BASE_RANGE(m_str) { }
   //scoped_string_base(const ::ansi_character * psz) :m_str(e_zero_initialize), BASE_RANGE(e_zero_initialize) { _construct1(psz); }
   //scoped_string_base(const ::wd16_character * psz) :m_str(e_zero_initialize), BASE_RANGE(e_zero_initialize) { _construct1(psz); }
   //scoped_string_base(const ::wd32_character * psz) :m_str(e_zero_initialize), BASE_RANGE(e_zero_initialize) { _construct1(psz); }
//   scoped_string_base(const ::const_ansi_range & range) :m_str(e_zero_initialize), BASE_RANGE(range) { }
//   scoped_string_base(const ::const_wd16_range & range) :m_str(e_zero_initialize), BASE_RANGE(range) { }
//   scoped_string_base(const ::const_wd32_range & range) :m_str(e_zero_initialize), BASE_RANGE(range) { }
//   scoped_string_base(const ::atom & atom):m_str(atom.as_string()), BASE_RANGE(m_str) { }
//   scoped_string_base(const ::payload & payload):m_str(payload.as_string()), BASE_RANGE(m_str) { }
//   scoped_string_base(const ::property & property):m_str(property.as_string()), BASE_RANGE(m_str) { }
   
   
   scoped_string_base(const ::inline_number_string & inlinenumberstring) :
      BASE_RANGE(no_initialize_t{})
   {
   
      this->construct_str(inlinenumberstring);
   
   }

   
   template < character_count n >
   scoped_string_base(const CHARACTER (&s)[n]) :
      BASE_RANGE(no_initialize_t{})
   {

      if constexpr (n >= 1)
      {

         if (s[n - 1] == CHARACTER{})
         {

            this->m_begin = s;
            this->m_end = s + n - 1;
            this->m_erange = e_range_null_terminated;

            return;

         }

      }

      this->m_begin = s;
      this->m_end = s + n;
      this->m_erange = e_range_none;

   }


   template < other_primitive_character <CHARACTER> OTHER_CHARACTER, character_count n >
   scoped_string_base(const CHARACTER(&s)[n]) : 
      BASE_RANGE(no_initialize_t{})
   {

      this->construct_str(s);
   
   }


   template < character_pointer CHARACTER_POINTER >
   scoped_string_base(CHARACTER_POINTER start) : scoped_string_base(start, start + string_safe_length(start), e_range_null_terminated) {}


   template < character_pointer CHARACTER_POINTER >
   scoped_string_base(CHARACTER_POINTER start, character_count length) : BASE_RANGE(no_initialize_t{}) { construct5(start, length); }


   void default_construct()
   {

      this->m_begin = nullptr;
      this->m_end = nullptr;
      this->m_erange = e_range_none;

   }


   template < typed_character_pointer < typename scoped_string_base < ITERATOR_TYPE >::CHARACTER > CHARACTER_POINTER >
   inline void construct5(CHARACTER_POINTER pSrc, character_count len)
   {

      if (::is_null(pSrc) || len <= 0)
      {

         default_construct();

         return;

      }

      this->m_begin = pSrc;
      this->m_end = pSrc + len;
      this->m_erange = *this->m_end ? e_range_none : e_range_null_terminated;

   }


   template < other_character_pointer < typename scoped_string_base < ITERATOR_TYPE >::CHARACTER > OTHER_CHARACTER_POINTER >
   inline void construct5(OTHER_CHARACTER_POINTER pSrc, character_count src_len)
   {

      if (::is_null(pSrc) || src_len <= 0)
      {

         default_construct();

         return;

      }

      this->construct_str({ pSrc, src_len });

   }


   //template < primitive_character CHARACTER2 >
   //scoped_string_base(const CHARACTER2 * start) : scoped_string_base(start, start + string_safe_length(start)) {}
   //template < primitive_character CHARACTER2 >
   //scoped_string_base(const CHARACTER2 * start, character_count len) : scoped_string_base(start, start + len) {}
   template < typed_character_pointer < typename scoped_string_base < ITERATOR_TYPE >::CHARACTER > CHARACTER_POINTER >
   scoped_string_base(CHARACTER_POINTER start, CHARACTER_POINTER end) :
      BASE_RANGE(no_initialize_t{})
   {

      if (::is_null(start) || end <= start)
      {

         default_construct();

         return;

      }

      this->m_begin = start;
      this->m_end = end;
      this->m_erange = *this->m_end ? e_range_none : e_range_null_terminated;

   }


   template < other_character_pointer < typename scoped_string_base < ITERATOR_TYPE >::CHARACTER > OTHER_CHARACTER_POINTER >
   scoped_string_base(OTHER_CHARACTER_POINTER start, OTHER_CHARACTER_POINTER end) :
      scoped_string_base(start, end - start) { }

   
   template < typed_character_pointer < typename scoped_string_base < ITERATOR_TYPE >::CHARACTER > CHARACTER_POINTER >
   scoped_string_base(CHARACTER_POINTER start, CHARACTER_POINTER end, enum_range erange) :
      BASE_RANGE(start, end, erange) { }


   template < other_character_pointer < typename scoped_string_base < ITERATOR_TYPE >::CHARACTER > OTHER_CHARACTER_POINTER >
   scoped_string_base(OTHER_CHARACTER_POINTER start, OTHER_CHARACTER_POINTER end, enum_range erange) :
      scoped_string_base(start, end) { }


   ~scoped_string_base()
   {

      //if (::is_set(this) && (this->m_erange & e_range_scoped_string_allocation))
      //if (::is_set(this) && (this->m_erange & e_range_string))

      destroy();

   }


   void _destroy()
   {

      ((STRING*)this)->__destroy();

   }


   void destroy()
   {
    
      if (this->m_erange & e_range_scoped_ownership
      && this->m_erange& e_range_string)
      {

         _destroy();

         this->m_erange = e_range_none;

      }

      // don't need to cleanup if above flags are not set

      //this->m_begin = nullptr;

      //this->m_end = nullptr;

      //this->m_erange = e_range_none;

   }

   //template < character_count n >
   //scoped_string_base(const char (&cha)[n]) :m_str(e_zero_initialize), BASE_RANGE(e_zero_initialize) { _construct1(cha); }


   
   void construct_str(const STRING & str)
   { 

      this->m_begin = str.m_begin;

      this->m_end = str.m_end;

      this->m_erange = str.m_erange;

      if (str.m_erange & e_range_string)
      //if(str.m_erange & e_range_string)
      {

         auto pbasedata = ((STRING*)this)->base_data_from_data(this->m_begin);

         pbasedata->base_data_increment_reference_count();

         this->m_erange = (enum_range)(this->m_erange | e_range_scoped_ownership);

      }
      
      //return *((STRING *)this);
   
   }

   STRING & str(const STRING& str)
   {

      this->destroy();
      
      this->construct_str(str);
   
      return *(STRING*)this;

   }


   STRING & fork()
   {

      return this->str({this->m_begin, this->m_end});

   }


   //template < primitive_character CHARACTER2 >
   //void _construct1(const CHARACTER2 * psz)
   //{
   //   
   //   if constexpr (sizeof(CHARACTER2) == sizeof(CHARACTER))
   //   {

   //      this->m_begin = psz;
   //      this->m_end = psz + string_safe_length(psz);

   //   }
   //   else
   //   {

   //      this->str(psz);

   //   }

   //}


   /// Returns:
/// end of line, and;
/// next line or null if no next line


   //void construct_range(const ::range < const CHARACTER* >& range)
   //{

   //   this->m_begin = (ITERATOR_TYPE)range.m_begin;
   //   this->m_end = (ITERATOR_TYPE)range.m_end;
   //   this->m_erange = range.m_erange;

   //}

   template < other_primitive_character < CHARACTER > OTHER_CHARACTER >
   void construct_range(const ::range < const OTHER_CHARACTER* >& range)
   {

      this->str(range);

   }


   inline bool operator ==(const ::ansi_string & str) const { return this->equals((const scoped_string_base&)str); }
   inline bool operator ==(const ::wd16_string & str) const { return this->equals((const scoped_string_base&)str); }
   inline bool operator ==(const ::wd32_string & str) const { return this->equals((const scoped_string_base&)str); }
   inline bool operator ==(const ::ansi_character * psz) const { return this->equals(psz); }
   inline bool operator ==(const ::wd16_character * psz) const { return this->equals(psz); }
   inline bool operator ==(const ::wd32_character * psz) const { return this->equals(psz); }
   inline bool operator ==(const ::scoped_ansi_string & str) const { return this->equals((const scoped_string_base&)str); }
   inline bool operator ==(const ::scoped_wd16_string & str) const { return this->equals((const scoped_string_base&)str); }
   inline bool operator ==(const ::scoped_wd32_string & str) const { return this->equals((const scoped_string_base&)str); }

   const CHARACTER * null_terminated() const
   { 

      if (!(this->m_erange & e_range_string) && (this->m_erange & e_range_null_terminated))
      {

         ((scoped_string_base *)this)->fork();

      }

      return this->m_begin;

   }


   operator const CHARACTER * () const { return this->null_terminated(); }

   const CHARACTER * c_str() const { return this->null_terminated(); }


   ::block as_block() const { return { (unsigned char *)this->begin(), this->size() * sizeof(CHARACTER) }; }


};


//inline block::block(const ::scoped_string & scopedstr):
//        block((iterator)scopedstr.begin(), (iterator)scopedstr.end())
//{
//
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE >::string_base(const ::scoped_string & scopedstr)
//{
//
//   if (sizeof(typename scoped_string::ITEM) == sizeof(CHARACTER)
//      && (range.m_erange & e_range_string))
//   {
//
//      this->m_begin = (ITERATOR_TYPE)range.m_begin;
//      this->m_end = (ITERATOR_TYPE)range.m_end;
//      this->m_erange = range.m_erange;
//
//   }
//   else
//   {
//
//      this->str(range);
//
//   }
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE >::string_base(const ::scoped_wstring & scopedstr) :
//   string_base(scopedstr.begin(), scopedstr.size())
//{
//   construct5(scopedstr);
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator = (const scoped_ansi_string & scopedansistring)
//{
//
//   assign(scopedansistring.begin(), scopedansistring.end());
//
//   return *this;
//
//}


//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator = (const scoped_wd16_string & scopedwd16string)
//{
//
//   assign(scopedwd16string.begin(), scopedwd16string.end());
//
//   return *this;
//
//}
//
//
//template < typename ITERATOR_TYPE >
//inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator = (const scoped_wd32_string & scopedwd32string)
//{
//
//   assign(scopedwd32string.begin(), scopedwd32string.end());
//
//   return *this;
//
//}


//template < typename ITERATOR_TYPE, primitive_string STRING >
//inline string_base < ITERATOR_TYPE > operator + (const scoped_string_base < ITERATOR_TYPE > & scopedstr, const STRING & str)
//{
//
//   return ::transfer(::string(scopedstr) + str);
//
//}

//template < typename ITERATOR_TYPE1, typename ITERATOR_TYPE2 >
//inline string_base < ITERATOR_TYPE1 > operator + (const scoped_string_base < ITERATOR_TYPE1 > & scopedstr1, const scoped_string_base < ITERATOR_TYPE2 > & scopedstr2)
//{
//
//   return ::transfer(::string(scopedstr1) + ::string(scopedstr2));
//
//}


//template < primitive_character CHARACTER1, primitive_character CHARACTER2 >
//inline ::ansi_string operator + (const ::range < const CHARACTER1 * > & scopedstr1, const ::range < const CHARACTERE & scopedstr2)
//{
//
//   ::ansi_string str(scopedstr1);
//
//   str.append(scopedstr2);
//
//   return ::transfer(str);
//
//}


//inline ::wd16_string operator + (const ::scoped_wd16_string & scopedstr1, const ::scoped_wd16_string & scopedstr2)
//{
//
//   ::wd16_string str(scopedstr1);
//
//   str.append(scopedstr2);
//
//   return ::transfer(str);
//
//}
//
//
//inline ::wd32_string operator + (const ::scoped_wd32_string & scopedstr1, const ::scoped_wd32_string & scopedstr2)
//{
//
//   ::wd32_string str(scopedstr1);
//
//   str.append(scopedstr2);
//
//   return ::transfer(str);
//
//}



template<primitive_character CHARACTER>
inline ::hash32 _scoped_string_unsigned_int_hash(const ::scoped_string_base<const CHARACTER *> & scopedstr) 
{

   if (scopedstr.is_empty()) 
   {

      return {0};

   }

   unsigned int uHash = 0;

   auto p = scopedstr.m_begin;

   while (p < scopedstr.m_end) uHash = (uHash << 5) + *(p++);

   return {uHash};

}


template < >
inline ::hash32 as_hash32 < scoped_ansi_string >(const scoped_ansi_string & scopedstr);


template < >
inline ::hash32 as_hash32 < scoped_wd16_string >(const scoped_wd16_string & scopedstr);


template < >
inline ::hash32 as_hash32 < scoped_wd32_string >(const scoped_wd32_string & scopedstr);




#include  "acme/prototype/mathematics/_string.h"


#ifdef __STD_FORMAT__


template < >
struct std::formatter<::scoped_string > :
   public ::std::formatter< ::std::string_view >
{
   auto format(const ::scoped_string& scopedstr, std::format_context& ctx) const {
      return formatter<::std::string_view>::format({ scopedstr.begin(), scopedstr.end() }, ctx);
   }
};


#endif


inline ::block as_block(const ::scoped_string & scopedstr)
{

   ::block block;

   block.m_begin = (decltype(block.m_begin))scopedstr.m_begin;
   block.m_end = (decltype(block.m_end))scopedstr.m_end;
   block.m_erange = scopedstr.m_erange;

   return block;

}



