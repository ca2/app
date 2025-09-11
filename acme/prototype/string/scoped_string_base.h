// Created by camilo on 2012-12-18 18:44 <3ThomasBorregaardSorensen!!
#pragma once


#include "scoped_string_base.h"
#include "scoped_string_base.h"
#include "acme/prototype/string/c_string.h"


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


   using BASE_RANGE = ::const_string_range < ITERATOR_TYPE >;
   using RAW_CHARACTER_RANGE = typename BASE_RANGE::RAW_CHARACTER_RANGE;


   using PRIMITIVE_SCOPED_STRING_TAG = PRIMITIVE_SCOPED_STRING_TAG_TYPE;

   using ITEM_POINTER = get_type_item_pointer< ITERATOR_TYPE>;
   using ITEM = dereference < ITEM_POINTER >;
   using CHARACTER = ITEM;
   using this_iterator = typename BASE_RANGE::this_iterator;
   using iterator = typename BASE_RANGE::iterator;
   using const_iterator = typename BASE_RANGE::const_iterator;
   using STRING = ::string_base < ITERATOR_TYPE >;
   using BASE_DATA = BASE_RANGE::BASE_DATA;


   scoped_string_base(no_initialize_t) : BASE_RANGE(no_initialize_t{}) { }

   scoped_string_base(): BASE_RANGE(nullptr) { }

   scoped_string_base(nullptr_t) : BASE_RANGE(nullptr) { }


   template < typed_character_pointer < typename scoped_string_base < ITERATOR_TYPE >::CHARACTER > CHARACTER_POINTER >
   scoped_string_base(CHARACTER_POINTER start, CHARACTER_POINTER end, enum_range erange = e_range_none, BASE_DATA * pbasedata = nullptr) :
      BASE_RANGE(start, end, erange, pbasedata) {}


   template < other_character_pointer < typename scoped_string_base < ITERATOR_TYPE >::CHARACTER > OTHER_CHARACTER_POINTER >
   scoped_string_base(OTHER_CHARACTER_POINTER start, OTHER_CHARACTER_POINTER end, enum_range erange = e_range_none) :
      BASE_RANGE(no_initialize_t{})
   {

      if (::is_null(start) || end <= start)
      {

         this->set_null();

         return;

      }

      this->construct_owned_string( start, end, erange );

   }


   template < character_pointer CHARACTER_POINTER >
   scoped_string_base(CHARACTER_POINTER start) : scoped_string_base(start, ::string_safe_length(start)) { }


   template < character_pointer CHARACTER_POINTER >
   scoped_string_base(CHARACTER_POINTER start, character_count length) : scoped_string_base(start, start + length) { }

   template < character_count length >
   scoped_string_base(const CHARACTER (&s)[length]) :
      BASE_RANGE(no_initialize_t{})
   {

      //if constexpr (length >= 1)
      //{

      //   if (s[length - 1] == CHARACTER{})
      //   {

      //      if (length - 1 <= 0)
      //      {

      //         this->set_null();

      //         return;

      //      }

      //      this->m_begin = s;

      //      this->m_end = s + length - 1;

      //      this->m_erange = e_range_none;

      //      this->m_pbasedata = nullptr;

      //      return;

      //   }

      //}

      this->m_begin = s;

      this->m_end = s + string_safe_length2(s, length);

      this->m_erange = e_range_none;

      this->m_pbasedata = nullptr;

   }


   template < other_primitive_character <CHARACTER> OTHER_CHARACTER, character_count length >
   scoped_string_base(const CHARACTER(&s)[length]) :
      BASE_RANGE(no_initialize_t{})
   {

      this->construct_owned_string(
         {
            s,
            string_safe_length(s, length)
         });

   }


   scoped_string_base(const ::character_range < const CHARACTER * > & range) : scoped_string_base(range.m_begin, range.m_end, range.m_erange, range.m_pbasedata) { }

   template < other_primitive_character <CHARACTER> OTHER_CHARACTER >
   scoped_string_base(const ::character_range < const OTHER_CHARACTER* > & range) : scoped_string_base(range.m_begin, range.m_end, range.m_erange) { this->construct_owned_string(range.m_begin, range.m_end, range.m_erange); }

   // template < typed_primitive_string <CHARACTER> STRING2 >
   // scoped_string_base(const STRING2& str) : BASE_RANGE(str) { }
   //
   // template < other_primitive_string <CHARACTER> STRING2 >
   // scoped_string_base(const STRING2& str) : BASE_RANGE(no_initialize_t{}) { this->construct_owned_string(str); }


   template < has_as_string HAS_AS_STRING >
   scoped_string_base(const HAS_AS_STRING & has_as_string) : BASE_RANGE(no_initialize_t{}) { this->transfer_construct_owned_string(::transfer(has_as_string.as_string())); }


   template < has_get_string HAS_GET_STRING >
   scoped_string_base(const HAS_GET_STRING & has_get_string) : BASE_RANGE(no_initialize_t{}) { this->transfer_construct_owned_string(::transfer(has_get_string.get_string())); }


   // template < primitive_character SOME_CHARACTER, character_count m_sizeMaximumLength >
   // scoped_string_base(const ::inline_string < SOME_CHARACTER,  & inlinenumberstring) :
   //    BASE_RANGE(no_initialize_t{})
   // {
   //
   //    this->construct_owned_string(inlinenumberstring);
   //
   // }


   scoped_string_base(const c::string & cstring) :
   BASE_RANGE(no_initialize_t{})
   {

      if constexpr (sizeof(CHARACTER) == 1)
      {

         this->m_begin = cstring.m_psz;

         this->m_end = this->m_begin + string_safe_length(this->m_begin);

         //this->m_erange = e_range_null_terminated;

         this->m_erange = e_range_none;

      }
      else
      {

         this->construct_owned_string(cstring);

      }

   }


   ITERATOR_TYPE c_str() const
   {

      if (!this->is_null_terminated())
      {

         ((scoped_string_base *)this)->create_owned_string();

      }

      return this->m_begin;

   }


   // template < typed_character_pointer < typename scoped_string_base < ITERATOR_TYPE >::CHARACTER > CHARACTER_POINTER >
   // inline void construct_with_length(CHARACTER_POINTER pSrc, character_count length)
   // {
   //
   //    if (::is_null(pSrc) || length <= 0)
   //    {
   //
   //       null_construct();
   //
   //       return;
   //
   //    }
   //
   //    this->m_begin = pSrc;
   //
   //    this->m_end = pSrc + length;
   //
   //    this->m_erange = *this->m_end ? e_range_none : e_range_null_terminated;
   //
   // }
   //
   //
   // template < other_character_pointer < typename scoped_string_base < ITERATOR_TYPE >::CHARACTER > OTHER_CHARACTER_POINTER >
   // inline void construct_with_length(OTHER_CHARACTER_POINTER p, character_count length)
   // {
   //
   //    if (::is_null(p) || length <= 0)
   //    {
   //
   //       null_construct();
   //
   //       return;
   //
   //    }
   //
   //    this->construct_owned_string({ p, length });
   //
   // }


   // template < typed_character_pointer < typename scoped_string_base < ITERATOR_TYPE >::CHARACTER > CHARACTER_POINTER >
   // scoped_string_base(CHARACTER_POINTER start, CHARACTER_POINTER end) :
   //    BASE_RANGE(no_initialize_t{})
   // {
   //
   //    if (::is_null(start) || end <= start)
   //    {
   //
   //       null_construct();
   //
   //       return;
   //
   //    }
   //
   //    this->m_begin = start;
   //
   //    this->m_end = end;
   //
   //    this->m_erange = *this->m_end ? e_range_none : e_range_null_terminated;
   //
   // }
   //
   //
   // template < other_character_pointer < typename scoped_string_base < ITERATOR_TYPE >::CHARACTER > OTHER_CHARACTER_POINTER >
   // scoped_string_base(OTHER_CHARACTER_POINTER start, OTHER_CHARACTER_POINTER end) :
   //    scoped_string_base(start, end - start) { }
   //
   //


   ~scoped_string_base()
   {

      destroy();

   }


   // void __release()
   // {
   //
   //    ((STRING*)this)->__release();
   //
   // }
   //

   void destroy()
   {

      if (!(this->m_erange & e_range_scoped_ownership))
      {

         ::release_base_data(this->m_pbasedata);

         //this->m_erange = e_range_none;

      }
      //else
      //{

         //// don't need to cleanup if above flags are not set
         // Actually you are asking to destroy...
         // ... so it should be clean/clear after...
         // ... and reported as empty or null....

         this->m_begin = nullptr;

         this->m_end = nullptr;

         this->m_erange = e_range_none;

      //}

   }


   // scoped_string_base & _append(const scoped_string_base & scopedstr)
   // {
   //
   //    if (this->m_erange & e_range_scoped_ownership
   //    && ::is_set(this->m_pbasedata)
   //    {
   //
   //       ((STRING *)this)->append(scopedstr);
   //
   //    }
   //    else
   //    {
   //
   //       auto data = this->data();
   //       auto size = this->size();
   //       this->m_begin = nullptr;
   //       this->m_end = nullptr;
   //       this->m_erange = e_range_none;
   //
   //       string_concatenate(*((STRING *)this), data, size, scopedstr.data(), scopedstr.size());
   //
   //    }
   //
   //    return *this;
   //
   // }
   //
   //
   // scoped_string_base & append(const scoped_string_base & scopedstr)
   // {
   //    if (this->has_character())
   //    {
   //       //::string str(m_scopedstrLine + ::string(buf + x, i - x));
   //       //m_scopedstrLine.destroy();
   //       //m_scopedstrLine = str;
   //       this->_append(scopedstr);
   //    }
   //    else
   //    {
   //       this->assign(scopedstr);
   //       //m_scopedstrLine.destroy();
   //       //m_scopedstrLine.construct_str({buf + x, i - x});
   //    }
   //
   //    return *this;
   //
   // }


   // scoped_string_base & _append(const scoped_string_base & scopedstr)
   // {
   //
   //    if (this->m_erange& e_range_string)
   //    {
   //
   //       ((STRING *)this)->append(scopedstr);
   //
   //    }
   //    else
   //    {
   //
   //       auto data = this->data();
   //
   //       auto size = this->size();
   //
   //       this->m_begin = nullptr;
   //
   //       this->m_end = nullptr;
   //
   //       this->m_erange = e_range_none;
   //
   //       string_concatenate(*((STRING *)this), data, size, scopedstr.data(), scopedstr.size());
   //
   //    }
   //
   //    return *this;
   //
   // }


   // scoped_string_base & append(const scoped_string_base & scopedstr)
   // {
   //    if (this->has_character())
   //    {
   //       //::string str(m_scopedstrLine + ::string(buf + x, i - x));
   //       //m_scopedstrLine.destroy();
   //       //m_scopedstrLine = str;
   //       this->_append(scopedstr);
   //    }
   //    else
   //    {
   //       this->assign(scopedstr);
   //       //m_scopedstrLine.destroy();
   //       //m_scopedstrLine.construct_owned_string({buf + x, i - x});
   //    }
   //
   //    return *this;
   //
   // }



   // scoped_string_base & operator +=(const scoped_string_base & scopedstr)
   // {
   //
   //    // if (this->m_erange & e_range_scoped_ownership
   //    // && this->m_erange& e_range_string)
   //    // {
   //    //
   //    //    ((STRING *)this)->append(scopedstr);
   //    //
   //    // }
   //    // else
   //    // {
   //    //
   //    //    auto data = this->data();
   //    //    auto size = this->size();
   //    //    this->m_begin = nullptr;
   //    //    this->m_end = nullptr;
   //    //
   //    //    this->construct_owned_string(string_concatenate(data, size, scopedstr.data(), scopedstr.size()));
   //    //
   //    // }
   //
   //    return this->append(scopedstr);
   //
   // }


   // scoped_string_base & assign_range(const scoped_string_base & scopedstr)
   // {
   //
   //    if (this->m_begin == scopedstr.m_begin
   //       && this->m_end == scopedstr.m_end)
   //    {
   //
   //       this->m_erange = scopedstr.m_erange;
   //
   //    }
   //    else if (this->m_erange& e_range_string
   //    && !((STRING *)this)->is_shared()
   //    && scopedstr.length_in_bytes() < ((STRING *)this)->storage_size())
   //    {
   //
   //       *((STRING *)this) = scopedstr;
   //
   //    }
   //    else
   //    {
   //
   //       this->m_begin = scopedstr.m_begin;
   //       this->m_end = scopedstr.m_end;
   //       this->m_erange = scopedstr.m_erange;
   //
   //    }
   //
   //    return *this;
   //
   // }


   // scoped_string_base & assign_copy(const STRING & str)
   // {
   //
   //    if (this->m_erange& e_range_string)
   //    {
   //
   //       *((STRING *)this) = str;
   //
   //    }
   //    else
   //    {
   //
   //       this->m_begin = nullptr;
   //       this->m_end = nullptr;
   //
   //       construct_owned_string(str.m_begin, str.m_end, str.m_erange);
   //
   //    }
   //
   //    return *this;
   //
   // }


   // scoped_string_base & assign(const scoped_string_base & scopedstr)
   // {
   //
   //    if (this->m_erange & e_range_string)
   //    {
   //
   //       if (scopedstr.m_erange & e_range_string)
   //       {
   //
   //          *((STRING *)this) = scopedstr;
   //
   //       }
   //       else
   //       {
   //
   //          this->destroy();
   //
   //          this->construct_owned_string(scopedstr);
   //
   //       }
   //
   //    }
   //    else if (scopedstr.m_erange& e_range_string)
   //    {
   //
   //
   //       this->m_begin = nullptr;
   //
   //       this->m_end = nullptr;
   //
   //       this->construct_owned_string(scopedstr);
   //
   //
   //    }
   //    else
   //    {
   //
   //       this->m_begin = scopedstr.m_begin;
   //
   //       this->m_end = scopedstr.m_end;
   //
   //       this->m_erange = scopedstr.m_erange;
   //
   //    }
   //
   //    return *this;
   //
   // }


   // scoped_string_base & operator = (const scoped_string_base & scopedstr)
   // {
   //
   //    return this->assign(scopedstr);
   //
   // }


   //template < character_count n >
   //scoped_string_base(const char (&cha)[n]) :m_str(e_zero_initialize), BASE_RANGE(e_zero_initialize) { _construct1(cha); }
   //template < typed_character_pointer < typename scoped_string_base < ITERATOR_TYPE >::CHARACTER > CHARACTER_POINTER >
   //void construct_owned_string(ITERATOR_TYPE start, ITERATOR_TYPE end, enum_range erange = e_range_none)
   //requires (sizeof(get_iterator_item < ITERATOR_TYPE >) == sizeof(CHARACTER))
   //{

   //   auto length = end - start;

   //   auto lengthNew = string_safe_length(start, length);

   //   auto pbasedata = this->create_string_data2(lengthNew, e_range_scoped_ownership);

   //   auto pdata = pbasedata->data();

   //   this->m_begin = pdata;

   //   memory_transfer(pdata, start, lengthNew);

   //   this->_set_length(lengthNew);

   //}


   void create_owned_string()
   {

      auto pdataThis = this->m_pbasedata;

      construct_owned_string(this->m_begin, this->m_end);

      if (pdataThis)
      {

         ::release_base_data(pdataThis);

      }

   }


   template < typename SOME_ITERATOR_TYPE >
   void construct_owned_string(SOME_ITERATOR_TYPE start, SOME_ITERATOR_TYPE end, enum_range erange = e_range_none)
   {

      this->construct_string(start, end, (enum_range)(erange | e_range_scoped_ownership));

   }


   void transfer_construct_owned_string(STRING && str)
   {

      this->m_begin = str.m_begin;

      this->m_end = str.m_end;

      this->m_erange = (enum_range) (str.m_erange | e_range_scoped_ownership);

      this->m_pbasedata = str.m_pbasedata;

      str.m_begin = nullptr;

      str.m_end = nullptr;

      str.m_erange = e_range_none;

      str.m_pbasedata = nullptr;

   }


   // template < typename OTHER_ITERATOR_TYPE >
   // void construct_owned_string(const ::range < OTHER_ITERATOR_TYPE > & characterrange)
   // {
   //
   //    create_string(*this, characterrange);
   //
   //    this->m_erange = (enum_range) (this->m_erange | e_range_scoped_ownership);
   //
   // }


   // STRING & str(const STRING& str)
   // {
   //
   //    this->destroy();
   //
   //    this->construct_owned_string(str);
   //
   //    return *(STRING*)this;
   //
   // }


   // STRING & fork()
   // {
   //
   //    return this->str({this->m_begin, this->m_end});
   //
   // }


   //template < primitive_character CHARACTER2 >
   //void _construct1(const CHARACTER2 * psz)
   //{
   //   
   //   if constexpr (sizeof(CHARACTER2) == sizeof(CHARACTER))
   //   {

   //      this->m_begin = psz;
   //      this->m_end = psz + string_safe_length(scopedstr);

   //   }
   //   else
   //   {

   //      this->str(scopedstr);

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

   STRING as_string() const;

   //inline bool operator ==(const ::ansi_string & str) const { return this->equals((const scoped_string_base&)str); }
   //inline bool operator ==(const ::wd16_string & str) const { return this->equals((const scoped_string_base&)str); }
   //inline bool operator ==(const ::wd32_string & str) const { return this->equals((const scoped_string_base&)str); }
   //inline bool operator ==(const_char_pointer psz) const { return this->equals(psz); }
   //inline bool operator ==(const ::wd16_character * psz) const { return this->equals(psz); }
   //inline bool operator ==(const ::wd32_character * psz) const { return this->equals(psz); }
   //inline bool operator ==(const ::scoped_ansi_string & str) const { return this->equals((const scoped_string_base&)str); }
   //inline bool operator ==(const ::scoped_wd16_string & str) const { return this->equals((const scoped_string_base&)str); }
   //inline bool operator ==(const ::scoped_wd32_string & str) const { return this->equals((const scoped_string_base&)str); }



   template < typename RANGE >
   bool operator ==(const RANGE & str) const requires
      (::std::is_base_of_v < ::range < const typename scoped_string_base < ITERATOR_TYPE >::CHARACTER* >, RANGE >
      && !
      (::std::is_base_of_v < scoped_string_base < ITERATOR_TYPE >, RANGE >
         || ::std::is_same_v < scoped_string_base < ITERATOR_TYPE >, RANGE >))
   {

      return this->equals((const scoped_string_base&)str);

   }


   template < typename OTHER_CHARACTER >
   bool operator ==(const ::range < const OTHER_CHARACTER* >& range) const
   requires other_primitive_character < OTHER_CHARACTER, CHARACTER >
   {

      return this->equals((const scoped_string_base&)range);

   }


   template < primitive_character CHARACTER >
   bool operator ==(const CHARACTER* p) const
   {

      return this->equals(p);

   }

   // const CHARACTER * null_terminated() const
   // {
   //
   //    if (!(this->m_erange & e_range_string) && (this->m_erange & e_range_null_terminated))
   //    {
   //
   //       ((scoped_string_base *)this)->fork();
   //
   //    }
   //
   //    return this->m_begin;
   //
   // }


   //operator const CHARACTER * () const { return this->null_terminated(); }

   //const CHARACTER * c_str() const { return this->null_terminated(); }


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


//#ifdef __STD_FORMAT__


template < >
struct std::formatter<::scoped_string > :
   public ::std::formatter< ::std::string_view >
{
   template < typename FormatContext >
   auto format(const ::scoped_string& scopedstr, FormatContext & context) const {
      return formatter<::std::string_view>::format({ scopedstr.begin(), scopedstr.end() }, context);
   }
};


//#endif


inline ::block as_block(const ::scoped_string & scopedstr)
{

   ::block block;

   block.m_begin = (decltype(block.m_begin))scopedstr.m_begin;
   block.m_end = (decltype(block.m_end))scopedstr.m_end;
   block.m_erange = scopedstr.m_erange;

   return block;

}


template <  >
inline bool EqualElements(const ::scoped_string_base < const char * > & element1, const ::scoped_string_base < const char * > & element2)
{

   return element1.equals(element2);

}


template <  >
inline bool EqualElements(const ::scoped_string_base < const wchar_t * >& element1, const ::scoped_string_base < const wchar_t* >& element2)
{

   return element1.equals(element2);

}


//
//template < >
//struct std::formatter<::scoped_string > :
//   public ::std::formatter< ::std::string_view >
//{
//   auto format(const ::scoped_string& scopedstr, std::format_context& ctx) const {
//      return ::std::formatter<::std::string_view>::format(::std::string_view{ scopedstr.begin(), scopedstr.end() }, ctx);
//   }
//};



