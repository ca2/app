#pragma once


#include "collection_iterable.h"


namespace str
{

   namespace iter
   {



   } // namespace iter


} // namespace str

template < typename ITERABLE >
class string_iterable :
   public ITERABLE
{
public:

   typedef typename ITERABLE::iterator    iterator;
   typedef typename ITERABLE              Iterable;
   typedef typename ITERABLE::iterator    iterator;
   typedef typename Iterable::BASE_TYPE   Type;
   typedef iterable                       Container;

   iterator add(const char * psz);

   iterator add(const unichar * pwsz);

   iterator add(char ch);

   iterator add(unichar wch);

   iterator add(const ::payload & payload);

   iterator add(const property & prop);

   iterator add(const id & id);

   iterator add(const Type & newElement);

   bool erase_empty()
   {

      return ::iter::erase_empty(*this);

   }

   Container & trim_right()
   {

      return ::iter::trim_right(*this);

   }

   Container & trim_left()
   {

      return ::iter::trim_left(*this);

   }


   Container & trim()
   {

      return ::iter::trim(*this);

   }


};


template < typename ITERABLE >
typename string_iterable < ITERABLE >::iterator string_iterable < ITERABLE >::add(const char * psz)
{
   index nIndex = this->m_nSize;
   set_at_grow(nIndex, psz);
   return m_pData + nIndex;
}


template < typename ITERABLE >
typename string_iterable < ITERABLE >::iterator string_iterable < ITERABLE >::add(const unichar * pwsz)
{
   index nIndex = this->m_nSize;
   set_at_grow(nIndex, (Type) ::str::international::unicode_to_utf8(pwsz));
   return m_pData + nIndex;
}



template < typename ITERABLE >
typename string_iterable < ITERABLE >::iterator string_iterable < ITERABLE >::add(char ch)
{
   if (ch == '\0')
      return add("");
   else
   {
      char str[16];
      str[0] = ch;
      str[1] = '\0';
      return add(str);
   }
}


template < typename ITERABLE >
typename string_iterable < ITERABLE >::iterator string_iterable < ITERABLE >::add(unichar wch)
{
   if (wch == L'\0')
      return add("");
   else
   {
      unichar wstr[16];
      wstr[0] = wch;
      wstr[1] = L'\0';
      return add(wstr);
   }
}


template < typename ITERABLE >
typename string_iterable < ITERABLE >::iterator string_iterable < ITERABLE >::add(const Type & newElement)
{

   index nIndex = this->m_nSize;

   set_at_grow(nIndex, newElement);

   return m_pData + nIndex;

}


//template < typename ITERABLE >
//void string_iterable < ITERABLE >::push_back(const Type & newElement)
//{
//   index nIndex = this->m_nSize;
//   set_at_grow(nIndex, newElement);
//}




template < typename ITERABLE >
typename string_iterable < ITERABLE >::iterator string_iterable < ITERABLE >::add(const id & id)
{
   if (id.is_null())
   {

      return end();

   }
   else
   {
      add(id);
   }
}




//// same as clear
//void string_iterable < ITERABLE >::erase_all()
//{
//   set_size(0);
//}
//
//// same as erase all
//void string_iterable < ITERABLE >::clear()
//{
//   set_size(0);
//}




template < typename ITERABLE >
typename ITERABLE::iterator string_iterable < ITERABLE >::add(const ::payload & payload)
{
   if (payload.is_empty())
   {
      return end();
   }
   else if (payload.get_type() == ::e_type_stra)
   {
      ::papaya::array::add(*this, payload.stra());
   }
   else if (payload.cast < string_array_base < Type > >() != nullptr)
   {
      ::papaya::array::add(*this, *payload.cast < string_array_base < Type > >());
   }
   else if (payload.get_type() == ::type_vara)
   {
      for (i32 i = 0; i < payload.vara().get_count(); i++)
      {
         add((Type) payload.vara()[i].get_string());
      }
   }
   else if (payload.get_type() == ::e_type_inta)
   {
      for (i32 i = 0; i < payload.inta().get_count(); i++)
      {
         add((Type) __str(payload.inta()[i]));
      }
   }
   else if (payload.get_type() == ::e_type_propset)
   {
      for (auto assoc : payload.propset())
      {
         add((Type) assoc.get_string());
      }
   }
   else
   {
      add((Type) payload.get_string());
   }

   return upper_bound();

}




template < typename ITERABLE >
typename ITERABLE::iterator string_iterable < ITERABLE >::add(const property & prop)
{

   return add(prop.get_value());

}
