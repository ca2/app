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
   using RANGE = ::string_range < ITERATOR_TYPE >;
   using this_iterator = typename RANGE::this_iterator;
   using iterator = typename RANGE::iterator;
   using const_iterator = typename RANGE::const_iterator;


   ::string_base < ITERATOR_TYPE > m_str;

   scoped_string_base() {}
   scoped_string_base(nullptr_t): RANGE(nullptr) {}
   scoped_string_base(const ::ansi_string & str) :m_str(str), RANGE(m_str) {}
   scoped_string_base(const ::wd16_string & str) :m_str(str), RANGE(m_str) {}
   scoped_string_base(const ::wd32_string & str) :m_str(str), RANGE(m_str) {}
   scoped_string_base(const ::ansi_character * psz) :m_str(e_no_initialize), RANGE(e_no_initialize) { _construct1(psz); }
   scoped_string_base(const ::wd16_character * psz) :m_str(e_no_initialize), RANGE(e_no_initialize) { _construct1(psz); }
   scoped_string_base(const ::wd32_character * psz) :m_str(e_no_initialize), RANGE(e_no_initialize) { _construct1(psz); }
   scoped_string_base(const ::atom & atom);
   scoped_string_base(const ::payload & payload);
   scoped_string_base(const ::property & property) : scoped_string_base((const ::payload &)property) {}


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


   operator CHARACTER * () { return this->begin(); }
   operator const CHARACTER * () const { return this->begin(); }


};


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



