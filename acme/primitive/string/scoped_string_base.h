// Created by camilo on 2012-12-18 18:44 <3ThomasBorregaardSorensen!!
#pragma once



template < typename ITERATOR_TYPE >
class scoped_string_base :
   public string_range < ITERATOR_TYPE >
{
public:



   using PRIMITIVE_SCOPED_STRING_TAG = PRIMITIVE_SCOPED_STRING_TAG_TYPE;

   using RANGE = string_range < ITERATOR_TYPE >;
   using ITEM_POINTER = typename get_type_item_pointer< ITERATOR_TYPE>::type;
   using ITEM = dereference < ITEM_POINTER >;
   using CHARACTER = ITEM;
   using this_iterator = typename RANGE::this_iterator;
   using iterator = typename RANGE::iterator;
   using const_iterator = typename RANGE::const_iterator;
   using STRING = ::string_base < ITERATOR_TYPE >;


   scoped_string_base():RANGE(e_zero_initialize) {}
   scoped_string_base(nullptr_t) :RANGE(e_zero_initialize) {}
   scoped_string_base(const scoped_ansi_string & scopedstr) : RANGE(e_zero_initialize) { construct_range(scopedstr); }
   scoped_string_base(const scoped_wd16_string & scopedstr) : RANGE(e_zero_initialize) { construct_range(scopedstr); }
   scoped_string_base(const scoped_wd32_string & scopedstr) : RANGE(e_zero_initialize) { construct_range(scopedstr); }

   template < primitive_string STRING >
   scoped_string_base(const STRING & str) : RANGE(e_no_initialize) { this->str(str); }

   template < has_as_string HAS_AS_STRING >
   scoped_string_base(const HAS_AS_STRING & has_as_string) : RANGE(e_no_initialize) { this->str(has_as_string.as_string()); }

   template < has_get_string HAS_GET_STRING >
   scoped_string_base(const HAS_GET_STRING & has_get_string) : RANGE(e_no_initialize) { this->str(has_get_string.get_string()); }

   template < primitive_character CHARACTER2 >
   scoped_string_base(CHARACTER2 character) : RANGE(e_no_initialize) { this->str(character); }

   template < character_range_not_string_neither_scoped_string CHARACTER_RANGE >
   scoped_string_base(const CHARACTER_RANGE & range) : RANGE(e_zero_initialize) { construct_range(range); }

    //   scoped_string_base(const ::block & block) :m_str(e_zero_initialize), RANGE((const_iterator)block.begin(), (const_iterator)block.end()) {}
//   scoped_string_base(const ::ansi_character ch) :m_str(ch), RANGE(m_str) { }
//   scoped_string_base(const ::wd16_character ch) :m_str(ch), RANGE(m_str) { }
//   scoped_string_base(const ::wd32_character ch) :m_str(ch), RANGE(m_str) { }
   //scoped_string_base(const ::ansi_character * psz) :m_str(e_zero_initialize), RANGE(e_zero_initialize) { _construct1(psz); }
   //scoped_string_base(const ::wd16_character * psz) :m_str(e_zero_initialize), RANGE(e_zero_initialize) { _construct1(psz); }
   //scoped_string_base(const ::wd32_character * psz) :m_str(e_zero_initialize), RANGE(e_zero_initialize) { _construct1(psz); }
//   scoped_string_base(const ::const_ansi_range & range) :m_str(e_zero_initialize), RANGE(range) { }
//   scoped_string_base(const ::const_wd16_range & range) :m_str(e_zero_initialize), RANGE(range) { }
//   scoped_string_base(const ::const_wd32_range & range) :m_str(e_zero_initialize), RANGE(range) { }
//   scoped_string_base(const ::atom & atom):m_str(atom.as_string()), RANGE(m_str) { }
//   scoped_string_base(const ::payload & payload):m_str(payload.as_string()), RANGE(m_str) { }
//   scoped_string_base(const ::property & property):m_str(property.as_string()), RANGE(m_str) { }
//   scoped_string_base(const ::inline_number_string & inline_number_string) : RANGE(inline_number_string) {}
   template < primitive_character CHARACTER2 >
   scoped_string_base(const CHARACTER2 * start) : scoped_string_base(start, string_safe_length(start)) {}
   template < primitive_character CHARACTER2 >
   scoped_string_base(const CHARACTER2 * start, strsize len) : scoped_string_base(start, start + len) {}
   template < primitive_character CHARACTER2 >
   scoped_string_base(const CHARACTER2 * start, const CHARACTER2 * end) :
      RANGE(e_zero_initialize) 
   { 
   
      if constexpr (sizeof(CHARACTER2) == sizeof(CHARACTER))
      {

         this->m_begin = start;
         this->m_end = end;

      }
      else
      {

         this->str({ start, end - start });

      }

   }


   //template < strsize n >
   //scoped_string_base(const char (&cha)[n]) :m_str(e_zero_initialize), RANGE(e_zero_initialize) { _construct1(cha); }


   STRING & str() { return (STRING &)*this; }
   STRING & str(const STRING & str) { return (this->str()) = str; }


   template < primitive_character CHARACTER2 >
   void _construct1(const CHARACTER2 * psz)
   {
      
      if constexpr (sizeof(CHARACTER2) == sizeof(CHARACTER))
      {

         this->m_begin = psz;
         this->m_end = psz + string_safe_length(psz);

      }
      else
      {

         this->str(psz);

      }

   }


   template < typename GENERIC_RANGE >
   void construct_range(const GENERIC_RANGE & range)
   {

      if constexpr (sizeof(typename GENERIC_RANGE::ITEM) == sizeof(CHARACTER))
      {

         RANGE::operator = (range);

      }
      else
      {

         this->str(range);

      }

   }

   inline bool operator ==(const ::ansi_string & str) const { return this->equals(scoped_string_base(str)); }
   inline bool operator ==(const ::wd16_string & str) const { return this->equals(scoped_string_base(str)); }
   inline bool operator ==(const ::wd32_string & str) const { return this->equals(scoped_string_base(str)); }
   inline bool operator ==(const ::ansi_character * psz) const { return this->equals(psz); }
   inline bool operator ==(const ::wd16_character * psz) const { return this->equals(psz); }
   inline bool operator ==(const ::wd32_character * psz) const { return this->equals(psz); }
   inline bool operator ==(const ::scoped_ansi_string & str) const { return this->equals(scoped_string_base(str)); }
   inline bool operator ==(const ::scoped_wd16_string & str) const { return this->equals(scoped_string_base(str)); }
   inline bool operator ==(const ::scoped_wd32_string & str) const { return this->equals(scoped_string_base(str)); }


   operator CHARACTER * () { return this->begin(); }
   operator const CHARACTER * () const { return this->begin(); }

   const CHARACTER * c_str() const { return this->begin(); }


};


//inline block::block(const ::scoped_string & scopedstr):
//        block((iterator)scopedstr.begin(), (iterator)scopedstr.end())
//{
//
//
//}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE >::string_base(const ::scoped_string & scopedstr):
   string_base(scopedstr.begin(), scopedstr.size())
{

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE >::string_base(const ::scoped_wstring & scopedstr) :
   string_base(scopedstr.begin(), scopedstr.size())
{


}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator = (const scoped_ansi_string & scopedansistring)
{

   assign(scopedansistring.begin(), scopedansistring.end());

   return *this;

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator = (const scoped_wd16_string & scopedwd16string)
{

   assign(scopedwd16string.begin(), scopedwd16string.end());

   return *this;

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > & string_base < ITERATOR_TYPE >::operator = (const scoped_wd32_string & scopedwd32string)
{

   assign(scopedwd32string.begin(), scopedwd32string.end());

   return *this;

}


template < typename ITERATOR_TYPE >
inline string_base < ITERATOR_TYPE > operator + (const scoped_string_base < ITERATOR_TYPE > & scopedstr, const string_base < ITERATOR_TYPE > & str)
{

   return ::move(::string(scopedstr) + str);

}

//template < typename ITERATOR_TYPE1, typename ITERATOR_TYPE2 >
//inline string_base < ITERATOR_TYPE1 > operator + (const scoped_string_base < ITERATOR_TYPE1 > & scopedstr1, const scoped_string_base < ITERATOR_TYPE2 > & scopedstr2)
//{
//
//   return ::move(::string(scopedstr1) + ::string(scopedstr2));
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
//   return ::move(str);
//
//}


//inline ::wd16_string operator + (const ::scoped_wd16_string & scopedstr1, const ::scoped_wd16_string & scopedstr2)
//{
//
//   ::wd16_string str(scopedstr1);
//
//   str.append(scopedstr2);
//
//   return ::move(str);
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
//   return ::move(str);
//
//}



template<primitive_character CHARACTER>
inline u32hash _scoped_string_u32_hash(::scoped_string_base<const CHARACTER *> scopedstr) {

   if (scopedstr.is_empty()) {

      return {0};

   }

   u32 uHash = 0;

   while (scopedstr.m_begin < scopedstr.m_end) uHash = (uHash << 5) + *(scopedstr.m_begin++);

   return {uHash};

}


template<>
inline u32hash u32_hash<scoped_ansi_string>(scoped_ansi_string scopedstr) {

   return _scoped_string_u32_hash<::ansi_character>((::scoped_string_base<const ::ansi_character *>) scopedstr);

}


template<>
inline u32hash u32_hash<scoped_wd16_string>(scoped_wd16_string scopedstr) {

   return _scoped_string_u32_hash<::wd16_character>((::scoped_string_base<const ::wd16_character *>) scopedstr);

}


template<>
inline u32hash u32_hash<scoped_wd32_string>(scoped_wd32_string scopedstr) {

   return _scoped_string_u32_hash<::wd32_character>((::scoped_string_base<const ::wd32_character *>) scopedstr);

}



