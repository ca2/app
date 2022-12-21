// Created by camilo on 2012-12-18 18:44 <3ThomasBorregaardSorensen!!
#pragma once



template < typename ITERATOR_TYPE >
class scoped_string_base :
   public string_range < ITERATOR_TYPE >
{
public:


   using RANGE = string_range < ITERATOR_TYPE >;
   using ITEM_POINTER = typename get_type_item_pointer< ITERATOR_TYPE>::type;
   using ITEM = dereference < ITEM_POINTER >;
   using CHARACTER = ITEM;
   //using RANGE = ::string_range < ITERATOR_TYPE >;
   using this_iterator = typename RANGE::this_iterator;
   using iterator = typename RANGE::iterator;
   using const_iterator = typename RANGE::const_iterator;


   ::string_base < ITERATOR_TYPE > m_str;

   scoped_string_base() {}
   scoped_string_base(nullptr_t): RANGE(nullptr) {}
   scoped_string_base(const ::ansi_string & str) :m_str(str), RANGE(m_str) {}
   scoped_string_base(const ::wd16_string & str) :m_str(str), RANGE(m_str) {}
   scoped_string_base(const ::wd32_string & str) :m_str(str), RANGE(m_str) {}
   scoped_string_base(const ::block & block) :m_str(e_no_initialize), RANGE((const_iterator)block.begin(), (const_iterator)block.end()) {}
   scoped_string_base(const ::ansi_character * psz) :m_str(e_no_initialize), RANGE(e_no_initialize) { _construct1(psz); }
   scoped_string_base(const ::wd16_character * psz) :m_str(e_no_initialize), RANGE(e_no_initialize) { _construct1(psz); }
   scoped_string_base(const ::wd32_character * psz) :m_str(e_no_initialize), RANGE(e_no_initialize) { _construct1(psz); }
   scoped_string_base(const ::const_ansi_range & range) :m_str(e_no_initialize), RANGE(range) { }
   scoped_string_base(const ::const_wd16_range & range) :m_str(e_no_initialize), RANGE(range) { }
   scoped_string_base(const ::const_wd32_range & range) :m_str(e_no_initialize), RANGE(range) { }
   //explicit scoped_string_base(const ::atom & atom);
   //explicit scoped_string_base(const ::payload & payload);
   //explicit scoped_string_base(const ::property & property) : scoped_string_base((const ::payload &)property) {}
   scoped_string_base(const ::inline_number_string & inline_number_string) : RANGE(inline_number_string) {}
   template < primitive_character CHARACTER2 >
   scoped_string_base(const CHARACTER2 * start) : scoped_string_base(start, string_safe_length(start)) {}
   template < primitive_character CHARACTER2 >
   scoped_string_base(const CHARACTER2 * start, strsize len) : scoped_string_base(start, start + len) {}
   template < primitive_character CHARACTER2 >
   scoped_string_base(const CHARACTER2 * start, const CHARACTER2 * end) :m_str(e_no_initialize), RANGE(start, end) { }


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
         m_str = psz;
         RANGE::operator=(m_str);
      }
   }

   inline bool operator ==(const ::ansi_string & str) const { return this->equals(scoped_string_base(str)); }
   inline bool operator ==(const ::wd16_string & str) const { return this->equals(scoped_string_base(str)); }
   inline bool operator ==(const ::wd32_string & str) const { return this->equals(scoped_string_base(str)); }
   inline bool operator ==(const ::ansi_character * psz) const { return this->equals(psz); }
   inline bool operator ==(const ::wd16_character * psz) const { return this->equals(psz); }
   inline bool operator ==(const ::wd32_character * psz) const { return this->equals(psz); }
   //inline bool operator ==(const ::scoped_ansi_string & str) const { return this->equals(scoped_string_base(str)); }
   //inline bool operator ==(const ::scoped_wd16_string & str) const { return this->equals(scoped_string_base(str)); }
   //inline bool operator ==(const ::scoped_wd32_string & str) const { return this->equals(scoped_string_base(str)); }


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



