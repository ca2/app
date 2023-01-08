//
// Created by camilo on 23/12/2022 01:38 <3ThomasBorregaardSorensen!!
//
#pragma once



template < typename Type, typename RawType, ::enum_type m_etypeContainer >
template < typename PRED >
Type string_array_base < Type, RawType, m_etypeContainer > ::predicate_implode(PRED pred, const RawType &strSeparator,::index i,::count inCountLastOut) const
{

   Type str;

   if (!this->prepare_first_in_count_last_out(i, inCountLastOut))
   {

      return str;

   }

   str = pred(this->first());

   if (i == inCountLastOut)
   {

      return str;

   }

   while(i < inCountLastOut)
   {

      i++;

      str += strSeparator;

      str += pred(this->element_at(i));

   }

   return str;

}





static inline void ConstructElement(string * pNewData)
{
   ((string *)pNewData)->default_construct();
}

static inline void DestructElement(string * pOldData)
{
   pOldData->~string();
}


static inline void ConstructElement(wstring * pNewData)
{
   ((wstring *)pNewData)->default_construct();
}

static inline void DestructElement(wstring * pOldData)
{
   pOldData->~wstring();
}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
inline Type & string_array_base < Type, RawType, m_etypeContainer >::last(::index i)
{
return this->element_at(get_upper_bound(i));
}

template < typename Type, typename RawType, ::enum_type m_etypeContainer >
inline Type string_array_base < Type, RawType, m_etypeContainer >::last(::index i) const
{
return this->element_at(get_upper_bound(i));
}

template < typename Type, typename RawType, ::enum_type m_etypeContainer >
inline Type & string_array_base < Type, RawType, m_etypeContainer >::first(::index i)
{
return this->element_at(get_lower_bound(i));
}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
inline Type string_array_base < Type, RawType, m_etypeContainer >::first(::index i) const
{

return this->element_at(get_lower_bound(i));

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
inline ::count string_array_base < Type, RawType, m_etypeContainer >::get_size() const
{

   return this->size();

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
inline ::count string_array_base < Type, RawType, m_etypeContainer >::get_count() const
{

   return this->size();

}

template < typename Type, typename RawType, ::enum_type m_etypeContainer >
inline ::index string_array_base < Type, RawType, m_etypeContainer >::get_lower_bound(::index i) const
{
return i;
}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
inline ::index string_array_base < Type, RawType, m_etypeContainer >::get_upper_bound(::index i) const
{

return this->size() + i;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
inline ::index string_array_base < Type, RawType, m_etypeContainer >::get_middle_index(::index i) const
{

return get_upper_bound() / 2 + i;

}







template < typename Type, typename RawType, ::enum_type m_etypeContainer >
string_array_base < Type, RawType, m_etypeContainer >::~string_array_base()
{

   // // ASSERT_VALID(this);

}




//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//::count string_array_base < Type, RawType, m_etypeContainer >::add(const string_array_base < Type, RawType, m_etypeContainer >& src)
//{
//
//   if(this == &src)
//   {
//
//      string_array_base < Type, RawType, m_etypeContainer > thisCopy(src);
//
//      return add(thisCopy);
//
//   }
//
//    // ASSERT_VALID(this);
//   ASSERT(this != &src);   // cannot append to itself
//
//   ::count nOldSize = this->size();
//
//   ::count nAddSize = src.size();
//
//   this->set_size(nOldSize + nAddSize);
//
//   CopyElements(&this->m_begin[nOldSize],src.m_begin, nAddSize);
//
//   return nOldSize;
//
//}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
string_array_base < Type, RawType, m_etypeContainer > &
string_array_base < Type, RawType, m_etypeContainer >::c_stra(string_array_base < Type, RawType, m_etypeContainer > & stra) const
{

   for (auto & str : *this)
   {

      stra.add(str.c_str());

   }

   return stra;

}

template < typename Type, typename RawType, ::enum_type m_etypeContainer >
string_array_base < Type, RawType, m_etypeContainer >
string_array_base < Type, RawType, m_etypeContainer >::c_stra() const
{

   string_array_base < Type, RawType, m_etypeContainer > stra;

   return c_stra(stra);

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer >::copy(const string_array_base < Type, RawType, m_etypeContainer >& src)
{

   if(this == &src)
      return;

   // // ASSERT_VALID(this);

   auto nSrcSize = src.size();

   this->set_size(nSrcSize);

   CopyElements(this->m_begin, src.m_begin, nSrcSize);

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
template < primitive_array ARRAY >
void string_array_base < Type, RawType, m_etypeContainer >::copy(const ARRAY & src)
{

   this->set_size((::count) src.size());

   for(::index i = 0; i < this->size(); i++)
   {

      get_data()[i] = as_string(src[i]);

   }

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
Type & string_array_base < Type, RawType, m_etypeContainer >::set_at_grow(::index nIndex,const Type & newElement)
{
// // ASSERT_VALID(this);
ASSERT(nIndex >= 0);

if(nIndex >= this->size())
this->set_size(nIndex + 1);

return get_data()[nIndex] = newElement;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer >::_007FindLine(const RawType &strKey, ::index iStart) const
{

   for(::index i = iStart; i < get_count(); i++)
   {

      if(element_at(i).trimmed().case_insensitive_begins("[") && i > 0)
      {

         return -1;

      }

      if(element_at(i).case_insensitive_begins(strKey + "="))
      {

         return i;

      }

   }

   return -1;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer >::_007SetLine(const RawType &strKey, const RawType &strValue, ::index iStart)
{

   ::index iKeyIndex = _007FindLine(strKey, iStart);

   Type strNewLine = strKey + "=" + strValue;

   if(iKeyIndex >= 0)
   {

      this->operator[](iKeyIndex) = strNewLine;

   }
   else
   {

      this->add(strNewLine);

   }

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer >::_007GetLine(RawType & strValue, const RawType &strKey, ::index iStart) const
{

   ::index iKeyIndex = _007FindLine(strKey, iStart);

   if(iKeyIndex < 0)
   {

      return -1;

   }

   strValue = this->operator[](iKeyIndex).substr(strKey.size() + 1);

   return iKeyIndex;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
RawType string_array_base < Type, RawType, m_etypeContainer >::_007GetLine(const RawType &strKey, ::index iStart) const
{

   RawType strValue;

   if(_007GetLine(strValue, strKey, iStart) < 0)
   {

      return "";

   }

   return strValue;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer >::_007FindSection(const RawType &strSection) const
{

   ::index iSectionIndex = this->find_first_begins_ci(strSection);

   return iSectionIndex;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer >::_007FindLine(const RawType &strSection, const RawType &strKey) const
{

   ::index iSectionIndex = this->_007FindSection(strSection);

   if(iSectionIndex < 0)
   {

      return -1;

   }

   return this->_007FindLine(strKey, iSectionIndex + 1);

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer >::_007OpenSection(const RawType &strSection)
{

   ::index iSectionIndex = this->_007FindSection(strSection);

   if(iSectionIndex < 0)
   {

      this->add("");

      iSectionIndex = this->add(strSection);

   }

   return iSectionIndex;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer >::_007SetLine(const RawType &strSection, const RawType &strKey, const RawType &strValue)
{

   ::index iSectionIndex = this->_007OpenSection(strSection);

   if(iSectionIndex < 0)
   {

      this->add("");

      iSectionIndex = this->add(strSection);

   }

   this->_007SetLine(strKey, strValue, iSectionIndex + 1);

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer >::_007GetLine(RawType & strValue, const RawType &strSection, const RawType &strKey) const
{

   ::index iSectionIndex = this->_007FindSection(strSection);

   if(iSectionIndex < 0)
   {

      return -1;

   }

   return _007GetLine(strValue, strKey, iSectionIndex + 1);

}

template < typename Type, typename RawType, ::enum_type m_etypeContainer >
RawType string_array_base < Type, RawType, m_etypeContainer >::_007GetLine(const RawType &strSection, const RawType &strKey) const
{

   RawType strValue;

   if(_007GetLine(strValue, strSection, strKey) < 0)
   {

      return "";

   }

   return strValue;

}







template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer >::insert_empty(::index nIndex,::count nCount)
{
// // ASSERT_VALID(this);
ASSERT(nIndex >= 0);    // will expand to meet need
ASSERT(nCount > 0);     // zero or negative size_i32 not allowed

if(nIndex >= this->size())
{
// adding after the end of the array
this->set_size(nIndex + nCount);  // grow so nIndex is valid
}
else
{
// inserting in the middle of the array
::count nOldSize = (::count) this->size();
this->set_size((::count) (this->size() + nCount));  // grow it to memory_new size_i32
// shift old data up to fill gap
__memmov(&get_data()[nIndex + nCount],&get_data()[nIndex],(nOldSize - nIndex) * sizeof(Type));

// re-init slots we copied from
for(::index i = nIndex; i < nIndex + nCount; i++)
{

get_data()[i].default_construct();

}

}

// insert memory_new value in the gap
ASSERT(nIndex + nCount <= this->size());
}

template < typename Type, typename RawType, ::enum_type m_etypeContainer >
Type & string_array_base < Type, RawType, m_etypeContainer >::insert_empty(::index nIndex)
{

//    // ASSERT_VALID(this);

ASSERT(nIndex >= 0);    // will expand to meet need

if(nIndex >= this->size())
{

this->set_size(nIndex + 1);

}
else
{

auto nOldSize = this->size();

this->set_size(nOldSize + 1);

__memmov(this->ptr_at(nIndex + 1), this->ptr_at(nIndex), (nOldSize - nIndex) * sizeof(Type));

for(::index i = nIndex; i < nIndex + 1; i++)
{

new (this->ptr_at(nIndex)) RawType();

}

}

ASSERT(nIndex + 1 <= this->size());

return get_data()[nIndex];

}



template < typename Type, typename RawType, ::enum_type m_etypeContainer >
Type & string_array_base < Type, RawType, m_etypeContainer >::insert_at(::index nIndex,const Type & strElement)
{

return insert_empty(nIndex) = strElement;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer >::insert_at(::index nIndex, const Type & strElement,::count nCount)
{

// make room for memory_new elements
insert_empty(nIndex,nCount);



// copy elements into the is_empty space
//Type temp = newElement;
while(nCount--)
get_data()[nIndex++] = strElement;

}



template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer >::insert_at(::index nStartIndex,const string_array_base < Type, RawType, m_etypeContainer > & NewArray)
{
//    // ASSERT_VALID(this);
ASSERT(&NewArray != nullptr);
//   ASSERT_KINDOF(string_array_base < Type, RawType, m_etypeContainer >, &NewArray);
//   ASSERT_VALID(&NewArray);
ASSERT(nStartIndex >= 0);

if(NewArray.get_size() > 0)
{
insert_at(nStartIndex,NewArray.get_at(0),NewArray.get_size());
for(::index i = 0; i < NewArray.get_size(); i++)
set_at(nStartIndex + i,NewArray.get_at(i));
}
}


//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//void string_array_base < Type, RawType, m_etypeContainer >::dump(dump_context & dumpcontext) const
//{
//   //matter::dump(dumpcontext);
//
//   dumpcontext << "with " << this->size() << " elements";
//   if(dumpcontext.GetDepth() > 0)
//   {
//      for(::index i = 0; i < this->size(); i++)
//         dumpcontext << "\n\t[" << i << "] = " << get_data()[i].c_str();
//   }
//
//   dumpcontext << "\n";
//}
//
//
//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//void string_array_base < Type, RawType, m_etypeContainer >::assert_ok() const
//{
//
//   matter::assert_ok();
//
//   if(this->m_begin == nullptr)
//   {
//
//      ASSERT(this->size() == 0);
//      ASSERT(this->m_nMaxSize == 0);
//
//   }
//   else
//   {
//
//      ASSERT(this->size() >= 0);
//      ASSERT(this->m_nMaxSize >= 0);
//      ASSERT(this->size() <= this->m_nMaxSize);
//      ASSERT(__is_valid_address(this->m_begin, (memsize_cast) (this->m_nMaxSize * sizeof(Type))));
//
//   }
//
//}




template < typename Type, typename RawType, ::enum_type m_etypeContainer >
string_array_base < Type, RawType, m_etypeContainer > string_array_base < Type, RawType, m_etypeContainer >::slice(::index i, ::count inCountLastOut) const
{

string_array_base stra;

if(this->prepare_first_in_count_last_out(i, inCountLastOut))
{

for(; i <= inCountLastOut; i++)
{

stra.add(this->element_at(i));

}

}

return stra;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
string_array_base < Type, RawType, m_etypeContainer > & string_array_base < Type, RawType, m_etypeContainer >::operator =(const string_array_base < Type, RawType, m_etypeContainer > & tokena)
{

   copy(tokena);

   return *this;

}


//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//inline Type & string_array_base < Type, RawType, m_etypeContainer >::add_new()
//{
//
//   this->allocate(this->size() + 1);
//
//   return this->last();
//
//}
//
//
//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//::index string_array_base < Type, RawType, m_etypeContainer >::add_new(::count c)
//{
//
//   if(i == -1)
//   {
//
//      return add(Type(psz));
//
//   }
//   else
//   {
//
//      insert_at(i,Type(psz));
//
//      return get_upper_bound();
//
//   }
//
//}


//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//Type & string_array_base < Type, RawType, m_etypeContainer >::new_element(::count c)
//{
//
//   add_new(nullptr,c);
//
//   if(i == -1)
//   {
//
//      return last();
//
//   }
//   else
//   {
//
//      return this->element_at(i);
//
//   }
//
//}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
Type & string_array_base < Type, RawType, m_etypeContainer >::add_get(const Type & newElement)
{

   ::index nIndex = this->size();

   return set_at_grow(nIndex, newElement);

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer >::erase_duplicates()
{

   for(::index i = 1; i < this->get_size();)
   {

      if(find_first(this->element_at(i), 0, i - 1) >= 1)
      {

         this->erase_at(i);

      }
      else
      {

         i++;

      }

   }

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer >::erase_duplicates_ci()
{

   for(::index i = 1; i < this->get_size();)
   {

      if(find_first_ci(this->element_at(i), 0, i - 1) >= 1)
      {

         this->erase_at(i);

      }
      else
      {

         i++;

      }

   }

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
const Type* string_array_base < Type, RawType, m_etypeContainer >::get_data() const
{
   return (const Type*)this->m_begin;
}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
Type* string_array_base < Type, RawType, m_etypeContainer >::get_data()
{
   return (Type*)this->m_begin;
}



template < typename Type, typename RawType, ::enum_type m_etypeContainer >
string_array_base < Type, RawType, m_etypeContainer > ::string_array_base(const string_array_base < Type, RawType, m_etypeContainer > & array) :
        BASE_ARRAY((const BASE_ARRAY&) array)
{
}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
string_array_base < Type, RawType, m_etypeContainer > ::string_array_base(CHARACTER* const* ppsz, ::count c)
{

   this->set_size(c);

   for (::index i = 0; i < c; i++)
   {

      this->element_at(i) = ppsz[i];

   }

}


//#ifdef _UWP
//
//
//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//string_array_base < Type, RawType, m_etypeContainer > ::string_array_base(Platform::Array < Platform::String ^ > ^ refstra)
//{
//
//   for (unsigned int u = 0; u < refstra->Length; u++)
//   {
//
//      Type str;
//
//      str = refstra[u]->Begin();
//
//      add(str);
//
//   }
//
//}
//
//
//#endif


#include "acme/primitive/string/tokenizer.h"


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer > ::add_tokens(const RawType &str, const RawType &strSeparator,bool bAddEmpty)
{

   ::tokenizer strTokenizer(str);

   Type strToken;

   if(bAddEmpty)
   {

      while(strTokenizer.get_next_token(strToken,strSeparator,false))
      {

         string_array_base::add(strToken);

      }

   }
   else
   {

      while(strTokenizer.get_next_token(strToken,strSeparator,false))
      {

         if (!strToken.is_empty())
         {

            string_array_base::add(strToken);

         }

      }

   }

}



template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer > ::_001AddTokens(const RawType &str)

{

   ::tokenizer strTokenizer(str);


   Type strToken;

   while(strTokenizer._001GetNextToken(strToken))
   {

      string_array_base::add(strToken);

   }

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer > ::add_smallest_tokens(const RawType &str, const RawStringArray & straSeparator, bool bAddEmpty, bool bWithSeparator)
{

   ::tokenizer strTokenizer(str);

   Type strToken;

   if(bAddEmpty)
   {

      while(strTokenizer.get_next_smallest_token(strToken, straSeparator, bWithSeparator))
      {

         string_array_base::add(strToken);

      }

   }
   else
   {

      while(strTokenizer.get_next_smallest_token(strToken,straSeparator,bWithSeparator))
      {

         if (!strToken.is_empty())
         {

            string_array_base::add(strToken);

         }

      }

   }

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
template < bool bAddEmpty >
typename Type::const_iterator string_array_base < Type, RawType, m_etypeContainer > ::_____add_lines_rn(const SCOPED_STRING & scopedstr)
{

   auto range = scopedstr();

   while(true)
   {

      auto p = range.find_first_character_in("\n\r");

      if(::is_null(p))
      {

         return range.begin();

      }

      auto pNext = p;

      if(*pNext == 'r')
      {

         pNext++;

         if(pNext >= range.end())
         {

            return pNext;

         }
         else if(*pNext == '\n')
         {

            pNext++;

         }

      }
      else // if(*p == 'n')
      {

         pNext++;

      }

      __add_lines_suffix<bAddEmpty>(range.begin(), p);

      range.begin(pNext);

   };

}





template < typename Type, typename RawType, ::enum_type m_etypeContainer >
template < bool bAddEmpty >
void string_array_base < Type, RawType, m_etypeContainer > ::_add_lines(const SCOPED_STRING &strParam)
{

   auto pN = strParam.find_first('\n');

   auto pR = strParam.find_first('\r');

   typename Type::const_iterator p;

   if(pN)
   {

      if(pR)
      {

         p = _____add_lines_rn<bAddEmpty>(strParam);

      }
      else
      {

         p = _____add_lines<'\n', bAddEmpty>(strParam);

      }

   }
   else if(pR)
   {

      p = _____add_lines<'\r', bAddEmpty>(strParam);

   }
   else
   {

      p = strParam.begin();

   }

   __add_lines_suffix<bAddEmpty>(p, strParam.end());

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer > ::get_format_string(Type & str,const RawType &strSeparator) const

{
   str.empty();
   if(this->size() > 0)
   {
      str = get_at(0);
   }
   for(::index i = 1; i < this->size(); i++)
   {
      str += strSeparator + get_at(i);

   }
}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::add_unique(const Type & newElement)
{

   auto iFind = find_first(newElement);

   if (iFind >= 0)
   {

      return -1;

   }

   return string_array_base::add(newElement);

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::count string_array_base < Type, RawType, m_etypeContainer > ::append_unique(const string_array_base & newElements)
{

   ::count count = 0;

   for(auto & newElement : newElements)
   {

      if (add_unique(newElement) >= 0)
      {

         count++;

      }

   }

   return count;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::add_unique_ci(const Type & newElement)

{

   ::index iFind = find_first_ci(newElement);

   if (iFind >= 0)
   {

      return -1;

   }

   string_array_base::add(newElement);

   return get_upper_bound();

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::count string_array_base < Type, RawType, m_etypeContainer > ::append_unique_ci(const string_array_base & straNewElements)
{

   ::count count = 0;

   for(auto & newElement : straNewElements)
   {

      if (add_unique_ci(newElement) >= 0)
      {

         count++;

      }

   }

   return count;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::find_first(const RawType &str, ::index iFind, ::index iLast) const
{

   if (this->prepare_first_last(iFind, iLast))
   {

      for (; iFind <= iLast; iFind++)
      {

         if (this->element_at(iFind).order(str) == 0)
         {

            return iFind;

         }

      }

   }

   return -1;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::find_first_ci(const RawType &str,::index iFind,::index iLast) const
{

   if (this->prepare_first_last(iFind, iLast))
   {

      for (; iFind <= iLast; iFind++)
      {

         if (this->element_at(iFind).case_insensitive_order(str) == 0)
         {

            return iFind;

         }

      }

   }

   return -1;

}




















template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::rear_find(const RawType &str, ::index iFind, ::index iLast) const
{

   if (this->prepare_first_last(iFind, iLast))
   {

      for (; iLast >= iFind; iLast--)
      {

         if (this->element_at(iLast).order(str) == 0)
         {

            return iLast;

         }

      }

   }

   return -1;

}

template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::reverse_find_ci(const RawType &str, ::index iFind, ::index iLast) const
{

   if (this->prepare_first_last(iFind, iLast))
   {

      for (; iLast >= iFind; iLast--)
      {

         if (this->element_at(iLast).case_insensitive_order(str) == 0)
         {

            return iLast;

         }

      }

   }

   return -1;

}






template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::count string_array_base < Type, RawType, m_etypeContainer > ::count(const RawType &str, ::index iFind, ::index iLast) const
{

   ::count count = 0;

   if (this->prepare_first_last(iFind, iLast))
   {

      for (; iFind <= iLast; iFind++)
      {

         if (this->element_at(iFind).order(str) == 0)
         {

            count++;

         }

      }

   }

   return count;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::count string_array_base < Type, RawType, m_etypeContainer > ::count_ci(const RawType &str, ::index iFind, ::index iLast) const
{

   ::count count = 0;

   if (this->prepare_first_last(iFind, iLast))
   {

      for (; iFind <= iLast; iFind++)
      {

         if (this->element_at(iFind).case_insensitive_order(str) == 0)
         {

            count++;

         }

      }

   }

   return count;

}




template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::find_last_ci(const RawType &str, ::index iFind, ::index iLast) const
{

   return reverse_find_ci(str, iFind, iLast);

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::find_last(const RawType &str, ::index iFind, ::index iLast) const
{

   return rear_find(str, iFind, iLast);

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::_066Find(const RawType &strParam) const
{

   RawString str(strParam);

   ::index iSel = this->find_first(str);

   if (iSel < 0)
   {

      iSel = this->find_first_ci(str);

      if(iSel < 0)
      {

         ::index iHalfLen = (::index) (str.length() / 2);

         for(::index iTruncate = (::index) str.length(); iTruncate >= iHalfLen; iTruncate--)
         {

            str.truncate(iTruncate);

            iSel = this->find_first(str);

            if(iSel >= 0)
            {

               break;

            }

            iSel = this->find_first_ci(str);

            if(iSel >= 0)
            {

               break;

            }

         }

      }

   }

   return iSel;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::find_first_contains(const RawType &strSubstring, ::index iFind, ::index iLast, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
{

   if (this->prepare_first_last(iFind, iLast))
   {

      return _find_first_contains(strSubstring, iFind, iLast, ppszBeg, ppszEnd);

   }

   return -1;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::_find_first_contains(const RawType &strSubstring, ::index iFind, ::index iLast, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
{

   for (; iFind <= iLast; iFind++)
   {

      if (this->element_at(iFind).contains(strSubstring, ppszBeg, ppszEnd))
      {

         return iFind;

      }

   }

   return -1;

}




template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::find_first_contains_ci(const RawType &strSubstring,::index iFind,::index iLast, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
{

   if (this->prepare_first_last(iFind, iLast))
   {

      return _find_first_contains_ci(strSubstring, iFind, iLast, ppszBeg, ppszEnd);

   }

   return -1;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::_find_first_contains_ci(const RawType &strSubstring, ::index iFind, ::index iLast, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
{

   for (; iFind <= iLast; iFind++)
   {

      if (this->element_at(iFind).case_insensitive_contains(strSubstring, ppszBeg, ppszEnd))
      {

         return iFind;

      }

   }

   return -1;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::prefix_find_first_ci(const RawType &strTopic,::index iFind,::index iLast) const
{

   if (this->prepare_first_last(iFind, iLast))
   {

      for (; iFind <= iLast; iFind++)
      {

         if (strTopic.case_insensitive_begins(this->element_at(iFind)))
         {

            return iFind;

         }

      }

   }

   return -1;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::prefix_find_first(const RawType &strTopic, ::index iFind, ::index iLast) const
{

   if (this->prepare_first_last(iFind, iLast))
   {

      for (; iFind <= iLast; iFind++)
      {

         if (strTopic.begins(this->element_at(iFind)))
         {

            return iFind;

         }

      }

   }

   return -1;

}




template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::substring_find_first(const RawType &strTopic, ::index iFind, ::index iLast, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
{

   if (this->prepare_first_last(iFind, iLast))
   {

      for (; iFind <= iLast; iFind++)
      {

         auto pBeg = strTopic.find(this->element_at(iFind));

         if (::is_set(pBeg))
         {

            if (ppszBeg)
            {

               *ppszBeg = pBeg;

            }

            if (ppszEnd)
            {

               *ppszEnd = pBeg + this->element_at(iFind).size();

            }

            return iFind;

         }

      }

   }

   return -1;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::substring_find_first_ci(const RawType &strTopic, ::index iFind, ::index iLast, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
{

   if (this->prepare_first_last(iFind, iLast))
   {

      for (; iFind <= iLast; iFind++)
      {

         auto pBeg = strTopic.find(this->element_at(iFind));

         if (::is_set(pBeg))
         {

            if (ppszBeg)
            {

               *ppszBeg = pBeg;

            }

            if (ppszEnd)
            {

               *ppszEnd = pBeg + this->element_at(iFind).size();

            }

            return iFind;

         }

      }

   }

   return -1;

}




template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::find_first_suffixed_ci(const RawType &strSuffix, ::index iFind, ::index iLast) const
{

   if (this->prepare_first_last(iFind, iLast))
   {

      return _find_first_suffixed_ci(strSuffix, iFind, iLast);

   }

   return -1;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::find_first_suffixed(const RawType &strSuffix, ::index iFind, ::index iLast) const
{

   if (this->prepare_first_last(iFind, iLast))
   {

      return _find_first_suffixed(strSuffix, iFind, iLast);

   }

   return -1;

}



template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::find_first_begins_eat(Type & strFoundAndEaten, const RawType &strSuffix, ::index iFind, ::index iLast) const
{

   iFind = find_first_begins(strSuffix, iFind, iLast);

   if (iFind < 0)
   {

      return iFind;

   }

   strFoundAndEaten = element_at(iFind).substr(strSuffix.size());

   return iFind;

}



template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::find_first_begins_eat_ci(Type & strFoundAndEaten,const RawType &strPrefix, ::index iFind,::index iLast) const
{

   iFind  = find_first_begins_ci(strPrefix,iFind,iLast);

   if (iFind < 0)
   {

      return iFind;

   }

   strFoundAndEaten = element_at(iFind).substr(strPrefix.size());

   return iFind;

}




template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::find_first_ends_eat(Type & strFoundAndEaten, const RawType &strSuffix, ::index iFind, ::index iLast) const
{

   iFind = find_first_ends(strSuffix, iFind, iLast);

   if (iFind < 0)
   {

      return iFind;

   }

   strFoundAndEaten = element_at(iFind).right(strSuffix.size());

   return iFind;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::find_first_ends_eat_ci(Type & strFoundAndEaten, const RawType &strSuffix, ::index iFind, ::index iLast) const
{

   iFind = find_first_ends_ci(strSuffix, iFind, iLast);

   if (iFind < 0)
   {

      return iFind;

   }

   strFoundAndEaten = element_at(iFind).right(strSuffix.size());

   return iFind;

}



template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::find_first_contains_eat(Type & strFoundAndEaten, const RawType &strSubstring, ::index iFind, ::index iLast) const
{

   const CHARACTER * pszBeg = nullptr;

   const CHARACTER * pszEnd = nullptr;

   iFind = find_first_contains(strSubstring, iFind, iLast, &pszBeg, &pszEnd);

   if (iFind < 0)
   {

      return iFind;

   }

   const CHARACTER * pszFind = element_at(iFind);

   strFoundAndEaten = RawType(pszFind, pszBeg - pszFind) + RawType(pszEnd);

   return iFind;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::find_first_contains_eat_ci(Type & strFoundAndEaten, const RawType &strTopic, ::index iFind, ::index iLast) const
{

   const CHARACTER * pszBeg = nullptr;

   const CHARACTER * pszEnd = nullptr;

   iFind = find_first_contains_ci(strTopic, iFind, iLast, &pszBeg, &pszEnd);

   if (iFind < 0)
   {

      return iFind;

   }

   const CHARACTER * pszFind = element_at(iFind);

   strFoundAndEaten = RawType(pszFind, pszBeg - pszFind) + RawType(pszEnd);

   return iFind;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::find_first_prefixed(const RawType &strPrefix,::index iFind,::index iLast) const
{

   if (this->prepare_first_last(iFind, iLast))
   {

      return _find_first_prefixed(strPrefix, iFind, iLast);

   }

   return -1;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::find_first_prefixed_ci(const RawType &strPrefix, ::index iFind, ::index iLast) const
{

   if (this->prepare_first_last(iFind, iLast))
   {

      return _find_first_prefixed_ci(strPrefix, iFind, iLast);

   }

   return -1;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::_find_first_prefixed(const RawType &strPrefix, ::index iFind, ::index iLast) const
{

   for (; iFind <= iLast; iFind++)
   {

      if (this->element_at(iFind).begins(strPrefix))
      {

         return iFind;

      }

   }

   return -1;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::_find_first_prefixed_ci(const RawType &strPrefix, ::index iFind, ::index iLast) const
{

   for (; iFind <= iLast; iFind++)
   {

      if (this->element_at(iFind).case_insensitive_begins(strPrefix))
      {

         return iFind;

      }

   }

   return -1;

}

template < typename Type, typename RawType, ::enum_type m_etypeContainer >
bool string_array_base < Type, RawType, m_etypeContainer > ::_067ContainsCi(const RawType &str, ::index iFind, ::index iLast, ::count countMin, ::count countMax) const
{

   ::count count = 0;

   while ((count < countMin || (countMax >= 0 && count <= countMax)) && (iFind = find_first_ci(str, iFind, iLast)) >= 0)
   {
      count++;

   }

   return count >= countMin && conditional(countMax >= 0, count <= countMax);

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
bool string_array_base < Type, RawType, m_etypeContainer > ::_067Contains(const RawType &str, ::index iFind, ::index iLast, ::count countMin, ::count countMax) const
{

   ::count count = 0;

   while ((count < countMin || (countMax >= 0 && count <= countMax)) && (iFind = find_first(str, iFind, iLast)) >= 0)
   {

      count++;

   }

   return count >= countMin && conditional(countMax >= 0, count <= countMax);

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
bool string_array_base < Type, RawType, m_etypeContainer > ::_067ContainsSubstringCi(const RawType &str, ::index iFind, ::index iLast, ::count countMin, ::count countMax) const
{

   ::count count = 0;

   while ((count < countMin || (countMax >= 0 && count <= countMax)) && (iFind = find_first_contains_ci(str, iFind, iLast)) >= 0)
   {

      count++;

   }

   return count >= countMin && conditional(countMax >= 0, count <= countMax);

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
bool string_array_base < Type, RawType, m_etypeContainer > ::_067ContainsSubstring(const RawType &str, ::index iFind, ::index iLast, ::count countMin, ::count countMax) const
{

   ::count count = 0;

   while ((count < countMin || (countMax >= 0 && count <= countMax)) && (iFind = find_first_contains(str, iFind, iLast)) >= 0)
   {

      count++;

   }

   return count >= countMin && conditional(countMax >= 0, count <= countMax);

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::erase_first_ci(const RawType &str,::index iFind,::index iLast)
{

   if ((iFind = find_first_ci(str, iFind, iLast)) >= 0)
   {

      this->erase_at(iFind);

   }

   return iFind;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::erase_first(const RawType &str,::index iFind,::index iLast)
{

   if ((iFind = find_first(str, iFind, iLast)) >= 0)
   {

      this->erase_at(iFind);

   }

   return iFind;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::erase_last_ci(const RawType &str, ::index iFind, ::index iLast)
{

   if ((iFind = find_last_ci(str, iFind, iLast)) >= 0)
   {

      this->erase_at(iFind);

   }

   return iFind;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::erase_last(const RawType &str, ::index iFind, ::index iLast)
{

   if ((iFind = find_last(str, iFind, iLast)) >= 0)
   {

      this->erase_at(iFind);


   }

   return iFind;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::count string_array_base < Type, RawType, m_etypeContainer > ::_067RemoveCi(const RawType &str, ::index iFind, ::index iLast, ::count countMin, ::count countMax)
{

   ::count count = 0;

   if (_067ContainsCi(str, iFind, iLast, countMin, countMax))
   {

      while (conditional(countMax >= 0, count < countMax) && (iFind = erase_first_ci(str, iFind, iLast)) >= 0)
      {

         count++;

      }

   }

   return count;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::count string_array_base < Type, RawType, m_etypeContainer > ::_067Remove(const RawType &str,::index iFind,::index iLast,::count countMin,::count countMax)
{

   ::count count = 0;

   if (_067Contains(str, iFind, iLast, countMin, countMax))
   {

      while (conditional(countMax >= 0, count < countMax) && (iFind = erase_first(str, iFind, iLast)) >= 0)
      {
         count++;

      }

   }

   return count;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::count string_array_base < Type, RawType, m_etypeContainer > ::erase_ci(const RawType &str, ::index iFind, ::index iLast)
{

   ::count count = 0;

   while ((iFind = erase_first_ci(str, iFind, iLast)) >= 0)
   {

      count++;

   }

   return count;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::count string_array_base < Type, RawType, m_etypeContainer > ::erase(const RawType &str, ::index iFind, ::index iLast)
{

   ::count count = 0;

   while ((iFind = erase_first(str, iFind, iLast)) >= 0)
   {

      count++;

   }

   return count;

}



template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::count string_array_base < Type, RawType, m_etypeContainer > ::erase_ci(const string_array_base & stra)
{

   ::count count = 0;

   for(::index i = 0; i < stra.get_size(); i++)
   {

      count += erase_ci(stra[i]);

   }

   return count;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::count string_array_base < Type, RawType, m_etypeContainer > ::erase(const string_array_base & stra)
{

   ::count count = 0;

   for(::index i = 0; i < stra.get_size(); i++)
   {

      count += erase(stra[i]);

   }

   return count;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer > ::trim_left(const RawType &strChars)
{
   for(::index i = 0; i < this->size(); i++)
   {
      this->operator[](i).trim_left(strChars);
   }
}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer > ::trim_right(const RawType &strChars)
{
   for(::index i = 0; i < this->size(); i++)
   {
      this->operator[](i).trim_right(strChars);
   }
}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer > ::trim(const RawType &strChars)
{
   for(::index i = 0; i < this->size(); i++)
   {
      this->operator[](i).trim(strChars);
   }
}



template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer > ::trim_left()
{
   for(::index i = 0; i < this->size(); i++)
   {
      this->operator[](i).trim_left();
   }
}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer > ::trim_right()
{
   for(::index i = 0; i < this->size(); i++)
   {
      this->operator[](i).trim_right();
   }
}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer > ::trim()
{
   for(::index i = 0; i < this->size(); i++)
   {
      this->operator[](i).trim();
   }
}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::add_normal(const Type & newElement)

{
   return string_array_base::add(newElement);

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::count string_array_base < Type, RawType, m_etypeContainer > ::erase_empty()
{

   ::count count = 0;

   for(::index i = 0; i < this->get_size();)
   {

      if(this->element_at(i).is_empty())
      {

         this->erase_at(i);

         count++;

      }
      else
      {

         i++;

      }

   }

   return count;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::count string_array_base < Type, RawType, m_etypeContainer > ::erase_empty_begin()
{

   ::count count = 0;

   for (::index i = 0; i < this->get_size();)
   {
      if (this->element_at(i).is_empty())
      {
         this->erase_at(i);
         count++;
      }
      else
      {
         break;
      }
   }
   return count;
}

template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::count string_array_base < Type, RawType, m_etypeContainer > ::erase_empty_end()
{

   ::count count = 0;
   ::index i;
   while((i = this->get_upper_bound()) >= 0)
   {
      if (this->element_at(i).is_empty())
      {
         this->erase_at(i);
         count++;
      }
      else
      {
         break;
      }
   }
   return count;
}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::count string_array_base < Type, RawType, m_etypeContainer > ::erase_empty_trimmed_begin()
{
   ::count count = 0;
   for (::index i = 0; i < this->get_size();)
   {
      if (this->element_at(i).trimmed().is_empty())
      {
         this->erase_at(i);
         count++;
      }
      else
      {
         break;
      }
   }
   return count;
}

template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::count string_array_base < Type, RawType, m_etypeContainer > ::erase_empty_trimmed_end()
{
   ::count count = 0;
   ::index i;
   while ((i = this->get_upper_bound()) >= 0)
   {
      if (this->element_at(i).trimmed().is_empty())
      {
         this->erase_at(i);
         count++;
      }
      else
      {
         break;
      }
   }
   return count;
}


//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//string_array_base < Type, RawType, m_etypeContainer >  & string_array_base < Type, RawType, m_etypeContainer > ::operator =(const i64_array & ia)
//{
//
//   this->_001CopyContainer(ia);
//
//   return *this;
//
//}


/*::index string_array_base < Type, RawType, m_etypeContainer > ::CountPrefixNoCase(const RawType &strPrefix)

{
Type str;
if(strPrefix != nullptr)

str = strPrefix;

if(str.is_empty())
{
return this->get_size();
}
else
{
::index iCount = 0;
::index iLen = str.length();
for(::index i = 0; i < this->get_size(); i++)
{
Type & strLeft = this->element_at(i).left(iLen);
if(strLeft.length() == iLen)
{
if(case_insensitive_order(strLeft, str) == 0)
{
iCount++;
}
}
}
return iCount;
}
}*/

/*void string_array_base < Type, RawType, m_etypeContainer > ::ExtractPrefixNoSortNoCase(
string_array_base < Type, RawType, m_etypeContainer >  &stra,
const RawType &str,

::index iLength,
::index iMinLength)
{
ASSERT(iLength >= iMinLength);
erase_all();
Type str;
if(str != nullptr)

str = str;

if(str.is_empty())
{
for(::index i = 0; i < stra.get_size(); i++)
{
Type & strMid = stra[i].left(iLength);
if(strMid.length() >= iMinLength)
{
if(FindFirstNoSortNoCase(strMid) < 0)
{
add(strMid);
}
}
}
}
else
{
::index iLen = maximum(str.length(), iMinLength);
for(::index i = 0; i < stra.get_size(); i++)
{
Type & strMid = stra[i].left(iLength);
if(strMid.length() >= iLen)
{
if(case_insensitive_order(strMid.left(iLen), str) == 0)
{
if(FindFirstNoSortNoCase(strMid) < 0)
{
add(strMid);
}
}
}
}
}

}

::index string_array_base < Type, RawType, m_etypeContainer > ::FindFirstNoSortNoCase(const RawType &str)

{
for(::index i = 0; i < this->get_size(); i++)
{
if(case_insensitive_order(str, this->element_at(i)) == 0)

{
return i;
}
}
return -1;
}
*/



//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//inline stream & operator << (stream & ostream, string_array_base < Type, RawType, m_etypeContainer > & a)
//{
//
//   return ostream.stream_array(a);
//
//}


//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//inline stream & operator >> (stream & istream, string_array_base < Type, RawType, m_etypeContainer > & a)
//{
//
//   return istream.stream_array(a);
//
//}






template < typename Type, typename RawType, ::enum_type m_etypeContainer >
Type string_array_base < Type, RawType, m_etypeContainer > ::implode(const RawType &strSeparator,::index i, ::count inCountLastOut) const
{

   Type str;

   if (!this->prepare_first_in_count_last_out(i, inCountLastOut))
   {

      return ::transfer(str);

   }

   str = this->element_at(i);

   if(i == inCountLastOut)
   {

      return str;

   }

   while (i < inCountLastOut)
   {

      i++;

      str += strSeparator;

      str += this->element_at(i);

   }

   return ::transfer(str);

}



template < typename Type, typename RawType, ::enum_type m_etypeContainer >
Type string_array_base < Type, RawType, m_etypeContainer > ::reverse_implode(const RawType &strSeparator,::index i,::count inCountLastOut) const
{

   Type str;

   if (!this->prepare_first_in_count_last_out(i, inCountLastOut))
   {

      return str;

   }

   str = this->element_at(inCountLastOut);

   if(i == inCountLastOut)
   {

      return str;

   }

   while (i < inCountLastOut)
   {

      inCountLastOut--;

      str += strSeparator;

      str += this->element_at(inCountLastOut);

   }

   return str;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
string_array_base < Type, RawType, m_etypeContainer >  & string_array_base < Type, RawType, m_etypeContainer > ::explode(const RawType &strSeparator,const RawType &str, bool bAddEmpty)
{

   this->erase_all();

   add_tokens(str, strSeparator, bAddEmpty);

   return * this;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
string_array_base < Type, RawType, m_etypeContainer >  & string_array_base < Type, RawType, m_etypeContainer > ::_001Explode(const RawType &str)
{

   this->erase_all();

   _001AddTokens(str);

   return * this;

}





template < typename Type, typename RawType, ::enum_type m_etypeContainer >
bool string_array_base < Type, RawType, m_etypeContainer > ::operator == (const typename string_array_base < Type, RawType, m_etypeContainer >::RawStringArray & a) const
{

   if (a.get_size() != get_size())
   {

      return false;

   }

   for (::index i = 0; i < get_size(); i++)
   {

      if (a[i] != element_at(i))
      {

         return false;

      }

   }

   return true;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
bool string_array_base < Type, RawType, m_etypeContainer > ::operator != (const typename string_array_base < Type, RawType, m_etypeContainer >::RawStringArray & a) const
{

   return !operator == (a);

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer > ::replace_with(const RawType &strNew, const RawType &strOld)
{

   for(::index i = 0; i < this->get_size(); i++)
   {

      this->element_at(i).replace_with(strNew, strOld);

   }

}





template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer > ::surround(const RawType &strPrefix,const RawType &strSuffix,::index iStart,::count inCountLastOut)
{

   if (!this->prepare_first_in_count_last_out(iStart, inCountLastOut))
   {

      return;

   }

   //Type strPrefix(strPrefix);

   //Type strSuffix(strSuffix);

   for(::index i = iStart; i <= inCountLastOut; i++)
   {

      this->element_at(i) = strPrefix + this->element_at(i) + strSuffix;

   }

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
Type string_array_base < Type, RawType, m_etypeContainer > ::surround_and_implode(const RawType &strSeparator,const RawType &strPrefix,const RawType &strSuffix,::index iStart,::count inCountLastOut)
{

   Type str;

   if (this->prepare_first_in_count_last_out(iStart, inCountLastOut))
   {

      Type strSeparator(strSeparator);
      Type strPrefix(strPrefix);
      Type strSuffix(strSuffix);

      str = strPrefix + this->element_at(iStart) + strSuffix;

      iStart++;

      for(::index i = iStart; i <= inCountLastOut; i++)
      {

         str += strSeparator + strPrefix + this->element_at(i) + strSuffix;

      }

   }

   return str;

}


//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//string_array_base < Type, RawType, m_etypeContainer >  & string_array_base < Type, RawType, m_etypeContainer > ::operator -=(const string_array_base & stra)
//{
//
//   erase(stra);
//
//   return *this;
//
//}


//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//string_array_base < Type, RawType, m_etypeContainer >  & string_array_base < Type, RawType, m_etypeContainer > ::operator +=(const string_array_base & stra)
//{
//
//   add(stra);
//
//   return *this;
//
//}


//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//string_array_base < Type, RawType, m_etypeContainer >  string_array_base < Type, RawType, m_etypeContainer > ::operator -(const string_array_base & straParam) const
//{
//   string_array_base < Type, RawType, m_etypeContainer >  stra(*this);
//   stra -= straParam;
//   return stra;
//}


//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//string_array_base < Type, RawType, m_etypeContainer >  string_array_base < Type, RawType, m_etypeContainer > ::operator +(const string_array_base & straParam) const
//{
//   string_array_base < Type, RawType, m_etypeContainer >  stra(*this);
//   stra += straParam;
//   return stra;
//}






template < typename Type, typename RawType, ::enum_type m_etypeContainer >
bool string_array_base < Type, RawType, m_etypeContainer > ::move_ci(const RawType &str,::index iIndex)

{
   ::index i = find_first_ci(str);

   if(i < 0)
      return false;
   this->erase_at(i);
   insert_at(iIndex,str);

   return true;
}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
bool string_array_base < Type, RawType, m_etypeContainer > ::preferred(const RawType &str)

{
   return move_ci(str,0);

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::count string_array_base < Type, RawType, m_etypeContainer > ::preferred(string_array_base < Type, RawType, m_etypeContainer >  & stra)
{
   ::count count = 0;
   for(::index i = stra.get_upper_bound(); i >= 0; i--)
   {
      if(preferred(stra[i]))
         count++;
   }
   return count;
}



template < typename Type, typename RawType, ::enum_type m_etypeContainer >
Type string_array_base < Type, RawType, m_etypeContainer > ::pop(::index i)
{
i = get_upper_bound(i);
Type strRet = this->element_at(i);
this->erase_at(i);
return strRet;
}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer > ::slice(string_array_base < Type, RawType, m_etypeContainer >  & stra,::index iOffset,::count count)
{

   ::index iEnd;

   if(count < 0)
      iEnd = get_upper_bound(count);
   else
      iEnd = iOffset + count - 1;

   for(::index i = iOffset; i <= iEnd; i++)
   {
      stra.add(this->element_at(i));
   }

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer > ::erase(::index iOffset,::count count)
{

for(::index i = iOffset + count - 1; i >= iOffset; i--)
{

this->erase_at(i);

}
}



template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer > ::splice(const string_array_base < Type, RawType, m_etypeContainer >  & stra,::index iOffset,::count count)
{

   erase(iOffset, count);

   insert_at(iOffset,stra);

}



template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer > ::splice(const string_array_base < Type, RawType, m_etypeContainer >  & stra,::index iOffset,string_array_base < Type, RawType, m_etypeContainer >  & straRemoved,::count count)
{

   slice(straRemoved, iOffset, count);

   erase(iOffset, count);

   insert_at(iOffset,stra);

}



template < typename Type, typename RawType, ::enum_type m_etypeContainer >
bool string_array_base < Type, RawType, m_etypeContainer > ::is_empty(::count countMinimum) const
{

return this->get_size() < countMinimum;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
bool string_array_base < Type, RawType, m_etypeContainer > ::has_elements(::count countMinimum) const
{


return this->get_count() >= countMinimum;
}


//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//::count string_array_base < Type, RawType, m_etypeContainer > ::begins(string_array_base < Type, RawType, m_etypeContainer > & straPrefixed, const RawType &strPrefix, ::index iFirst, ::index iLast)
//{
//
//   ::count count = 0;
//
//   if (this->prepare_first_last(iFirst, iLast))
//   {
//
//      while (true)
//      {
//
//         iFirst = _find_first_prefixed(strPrefix, iFirst, iLast);
//
//         if (iFirst < 0)
//         {
//
//            return count;
//
//         }
//
//         straPrefixed.add(this->element_at(iFirst));
//
//         iFirst++;
//
//         count++;
//
//      }
//
//   }
//
//   return count;
//
//}
//
//
//
//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//::count string_array_base < Type, RawType, m_etypeContainer > ::case_insensitive_begins(string_array_base < Type, RawType, m_etypeContainer > & straPrefixed,const RawType &strPrefix,::index iFirst,::index iLast)
//{
//
//   ::count count = 0;
//
//   if (this->prepare_first_last(iFirst, iLast))
//   {
//
//      while(true)
//      {
//
//         iFirst = find_first_begins_ci(strPrefix,iFirst,iLast);
//
//         if (iFirst < 0)
//         {
//
//            return count;
//
//         }
//
//         straPrefixed.add(this->element_at(iFirst));
//
//         iFirst++;
//
//         count++;
//
//      }
//
//   }
//
//   return count;
//
//}
//
//
//


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
template < primitive_array INDEX_ARRAY >
::count string_array_base < Type, RawType, m_etypeContainer > ::begins(INDEX_ARRAY & iaPrefixed, const RawType &strPrefix, ::index iFirst, ::index iLast)
{

::count count = 0;

if (this->prepare_first_last(iFirst, iLast))
{

while (true)
{

iFirst = _find_first_prefixed(strPrefix, iFirst, iLast);

if (iFirst < 0)
{

return count;

}

iaPrefixed.add(this->element_at(iFirst));

iFirst++;

count++;

}

}

return count;

}



template < typename Type, typename RawType, ::enum_type m_etypeContainer >
template < primitive_array INDEX_ARRAY >
::count string_array_base < Type, RawType, m_etypeContainer > ::case_insensitive_begins(INDEX_ARRAY & iaPrefixed, const RawType &strPrefix, ::index iFirst, ::index iLast)
{

::count count = 0;

if (this->prepare_first_last(iFirst, iLast))
{

while (true)
{

iFirst = _find_first_prefixed_ci(strPrefix, iFirst, iLast);

if (iFirst < 0)
{

return count;

}

iaPrefixed.add(iFirst);

iFirst++;

count++;

}

}

return count;

}



//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//::count string_array_base < Type, RawType, m_etypeContainer > ::ends(string_array_base < Type, RawType, m_etypeContainer >& straSuffixed, const RawType &strSuffix, ::index iFirst, ::index iLast)
//{
//
//   ::count count = 0;
//
//   if (this->prepare_first_last(iFirst, iLast))
//   {
//
//      while (true)
//      {
//
//         iFirst = find_first_ends(strSuffix, iFirst, iLast);
//
//         if (iFirst < 0)
//         {
//
//            return count;
//
//         }
//
//         straSuffixed.add(this->element_at(iFirst));
//
//         iFirst++;
//
//         count++;
//
//      }
//
//   }
//
//   return count;
//
//}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
template < primitive_array STRING_ARRAY >
::count string_array_base < Type, RawType, m_etypeContainer > ::case_insensitive_ends(STRING_ARRAY & straSuffixed, const RawType &strSuffix, ::index iFirst, ::index iLast)
{

::count count = 0;

if (this->prepare_first_last(iFirst, iLast))
{

while (true)
{

iFirst = _find_first_suffixed_ci(strSuffix, iFirst, iLast);

if (iFirst < 0)
{

return count;

}

straSuffixed.add(this->element_at(iFirst));

iFirst++;

count++;

}

}

return count;

}




template < typename Type, typename RawType, ::enum_type m_etypeContainer >
template < primitive_array STRING_ARRAY >
::count string_array_base < Type, RawType, m_etypeContainer > ::ends(STRING_ARRAY & iaSuffixed, const RawType &strSuffix, ::index iFirst, ::index iLast)
{

::count count = 0;

if (this->prepare_first_last(iFirst, iLast))
{

while (true)
{

iFirst = _find_first_suffixed(strSuffix, iFirst, iLast);

if (iFirst < 0)
{

return count;

}

iaSuffixed.add(this->element_at(iFirst));

iFirst++;

count++;

}

}

return count;

}



//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//::count string_array_base < Type, RawType, m_etypeContainer > ::case_insensitive_ends(index_array & iaSuffixed, const RawType &strSuffix, ::index iFirst, ::index iLast)
//{
//
//   ::count count = 0;
//
//   if (this->prepare_first_last(iFirst, iLast))
//   {
//
//      while (true)
//      {
//
//         iFirst = _find_first_suffixed_ci(strSuffix, iFirst, iLast);
//
//         if (iFirst < 0)
//         {
//
//            return count;
//
//         }
//
//         iaSuffixed.add(iFirst);
//
//         iFirst++;
//
//         count++;
//
//      }
//
//   }
//
//   return count;
//
//}
//
//
//
//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//::count string_array_base < Type, RawType, m_etypeContainer > ::search_ci(string_array_base < Type, RawType, m_etypeContainer > & stra, const RawType &str, ::index iFirst, ::index iLast)
//{
//
//   ::count count = 0;
//
//   if (this->prepare_first_last(iFirst, iLast))
//   {
//
//      while (true)
//      {
//
//         iFirst = _find_first_contains_ci(str, iFirst, iLast);
//
//         if (iFirst < 0)
//         {
//
//            return count;
//
//         }
//
//         stra.add(this->element_at(iFirst));
//
//         iFirst++;
//
//         count++;
//
//      }
//
//   }
//
//   return count;
//
//}
//
//
//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//::count string_array_base < Type, RawType, m_etypeContainer > ::search(string_array_base < Type, RawType, m_etypeContainer > & stra, const RawType &str, ::index iFirst, ::index iLast)
//{
//
//   ::count count = 0;
//
//   if (this->prepare_first_last(iFirst, iLast))
//   {
//
//      while (true)
//      {
//
//         iFirst = _find_first_contains(str, iFirst, iLast);
//
//         if (iFirst < 0)
//         {
//
//            return count;
//
//         }
//
//         stra.add(this->element_at(iFirst));
//
//         iFirst++;
//
//         count++;
//
//      }
//
//   }
//
//   return count;
//
//}

template < typename Type, typename RawType, ::enum_type m_etypeContainer >
template < primitive_array STRING_ARRAY >
::count string_array_base < Type, RawType, m_etypeContainer > ::search(STRING_ARRAY & iaResult, const RawType &strTopic, ::index iFirst, ::index iLast)
{

::count count = 0;

if (this->prepare_first_last(iFirst, iLast))
{

while (true)
{

iFirst = _find_first_contains(strTopic, iFirst, iLast);

if (iFirst < 0)
{

return count;

}

iaResult.add(iFirst);

iFirst++;

count++;

}

}

return count;

}



template < typename Type, typename RawType, ::enum_type m_etypeContainer >
template < primitive_array STRING_ARRAY >
::count string_array_base < Type, RawType, m_etypeContainer > ::search_ci(STRING_ARRAY & ia, const RawType &strTopic, ::index iFirst, ::index iLast)
{

::count count = 0;

if (this->prepare_first_last(iFirst, iLast))
{

while (true)
{

iFirst = _find_first_contains_ci(strTopic, iFirst, iLast);

if (iFirst < 0)
{

return count;

}

ia.add(iFirst);

iFirst++;

count++;

}

}

return count;

}



template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::count string_array_base < Type, RawType, m_etypeContainer > ::filter_begins(const RawType &str, ::index iFirst, ::index iLast)
{

   ::count count = 0;

   if (this->prepare_first_last(iFirst, iLast))
   {

      ::index i = iFirst;

      ::index iFind;

      while (true)
      {

         iFind = find_first_begins(str, i, iLast);

         if (iFind < 0)
         {

            this->erase_at(i, iLast - i + 1);

            return count;

         }

         this->erase_at(i, iFind - i);

         iLast -= iFind - i;

         i++;

         count++;

      }

   }

   return count;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::count string_array_base < Type, RawType, m_etypeContainer > ::filter_begins_ci(const RawType &str,::index iFirst,::index iLast)
{

   ::count count = 0;

   if (this->prepare_first_last(iFirst, iLast))
   {

      ::index i = iFirst;

      ::index iFind;

      while(true)
      {

         iFind = find_first_begins_ci(str,i,iLast);

         if(iFind < 0)
         {

            this->erase_at(i,iLast - i + 1);

            return count;

         }

         this->erase_at(i,iFind - i);

         iLast -= iFind - i;

         i++;

         count++;

      }

   }

   return count;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
template < typename Pred >
::count string_array_base < Type, RawType, m_etypeContainer > ::filter(Pred pred, ::index iFirst, ::index iLast)
{

   ::count count = 0;

   if (this->prepare_first_last(iFirst, iLast))
   {

      for(::index i = iFirst; i <= iLast;)
      {

         if(pred(element_at(i)))
         {

            i++;

         }
         else
         {

            this->erase_at(i);

            count++;

            iLast--;

         }

      }

   }

   return count;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
template < typename Pred >
::count string_array_base < Type, RawType, m_etypeContainer > ::filter_out(Pred pred,::index iFirst,::index iLast)
{

   ::count count = 0;

   if (this->prepare_first_last(iFirst, iLast))
   {

      for(::index i = iFirst; i <= iLast;)
      {

         if(!pred(element_at(i)))
         {

            i++;

         }
         else
         {

            this->erase_at(i);

            count++;

            iLast--;

         }

      }

   }

   return count;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
template < typename Pred, typename ArrayOut >
::count string_array_base < Type, RawType, m_etypeContainer > ::filter_out(Pred pred, ArrayOut & a, ::index iFirst,::index iLast)
{

   ::count count = 0;

   if (this->prepare_first_last(iFirst, iLast))
   {

      for(::index i = iFirst; i <= iLast;)
      {

         if(!pred(element_at(i)))
         {

            i++;

         }
         else
         {

            a.add(this->element_at(i));

            this->erase_at(i);

            count++;

            iLast--;

         }

      }

   }

   return count;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::get_random_index() const
{

   if(this->is_empty())
   {

      return -1;

   }

   return (::index)(rand() % get_size());

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
Type & string_array_base < Type, RawType, m_etypeContainer > ::random_element()
{

   if(this->is_empty())
   {

      throw_exception(error_wrong_state, "invalid call");

   }

   return this->element_at(get_random_index());

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
const Type & string_array_base < Type, RawType, m_etypeContainer > ::random_element() const
{

   if(this->is_empty())
   {

      throw_exception(error_wrong_state, "invalid call");

   }

   return this->element_at(get_random_index());

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
Type string_array_base < Type, RawType, m_etypeContainer > ::pop_random_element()
{

   if(this->is_empty())
   {

      throw_exception(error_wrong_state, "invalid call");

   }

   ::index i = get_random_index();

   Type str = this->element_at(i);

   this->erase_at(i);

   return str;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer > ::make_lower()
{

   for(::index i = 0; i < this->get_count(); i++)
   {

      this->element_at(i).make_lower();

   }

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer > ::make_upper()
{

   for(::index i = 0; i < this->get_count(); i++)
   {

      this->element_at(i).make_upper();

   }

}









template < typename Type, typename RawType, ::enum_type m_etypeContainer >
Type string_array_base < Type, RawType, m_etypeContainer > ::encode_v16()
{
   //Type strEncode;
   //for(::index u = 0; u < this->get_count(); u++)
   //{
   //   Type & str = this->element_at(u);
   //   strEncode += hex::lower_from((const char*)str,str.length());
   //   strEncode += "00";
   //   /*      for(::index uj = 0; uj < str.size(); uj++)
   //   {
   //   char sz[32];
   //   ansi_from_i64(sz, str[uj], 16);
   //   if(ansi_length(sz) == 0)
   //   {
   //   strEncode += "00";
   //   }
   //   else if(ansi_length(sz) == 1)
   //   {
   //   strEncode += "0";
   //   strEncode += sz;
   //   }
   //   else if(ansi_length(sz) == 2)
   //   {
   //   strEncode += sz;
   //   }
   //   }*/

   //}
   //return strEncode;

   return Type();

}




template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer > ::decode_v16(const RawType &str)
{
   //::index iSize = 1024;
   //char * str = nullptr;
   //if(psz == nullptr)
   //   return;
   //while(*psz != '\0')
   //{
   //   psz++;
   //   if(*psz == '\0')
   //      break;
   //   char sz[3];
   //   sz[0] = psz[-1];
   //   sz[1] = psz[0];
   //   sz[2] = '\0';
   //   const RawType &strEnd;
   //   ::index iConversion = ::ansi_to_i32(sz,&pszEnd,16);
   //   char ch = static_cast <char> (iConversion);
   //   if(ch == '\0')
   //   {
   //      add(str);
   //      str = nullptr;
   //      iSize = 1024;
   //   }
   //   else
   //   {
   //      if(str == nullptr)
   //      {
   //         str = (char *)memory_allocate(iSize);
   //      }
   //      else if(iSize < (ansi_length(str) + 1))
   //      {
   //         char * strOld = str;
   //         iSize += 1024;
   //         char * strNew = (char *)memory_allocate(iSize);
   //         ansi_copy(strNew,strOld);
   //         str = strNew;
   //      }
   //      sz[0] = ch;
   //      sz[1] = '\0';
   //      ansi_copy(str,sz);
   //   }
   //   psz++;
   //}

}




template < typename Type, typename RawType, ::enum_type m_etypeContainer >
inline ::count string_array_base < Type, RawType, m_etypeContainer >::count_except(const RawType &str)
{

   ::count c = get_count();

   for (::index i = 0; i < get_count(); i++)
   {

      if (this->element_at(i) == str)
      {

         c--;

      }

   }

   return c;

}

template < typename Type, typename RawType, ::enum_type m_etypeContainer >
inline ::count string_array_base < Type, RawType, m_etypeContainer > ::count_except_ci(const RawType &str)
{

   ::count c = get_count();

   for (::index i = 0; i < get_count(); i++)
   {

      if (this->element_at(i).case_insensitive_order(str) == 0)
      {

         c--;

      }

   }

   return c;

}



template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::count string_array_base < Type, RawType, m_etypeContainer > ::count_except(const string_array_base < Type, RawType, m_etypeContainer >  & stra)
{

   ::count c = get_count();

   for(::index i = 0; i < get_count(); i++)
   {

      if (stra.contains(element_at(i)))
      {

         c--;

      }

   }

   return c;

}




template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::count string_array_base < Type, RawType, m_etypeContainer > ::count_except_ci(const string_array_base < Type, RawType, m_etypeContainer >  & stra)
{

   ::count c = get_count();

   for(::index i = 0; i < get_count(); i++)
   {

      if (stra.case_insensitive_contains(element_at(i)))
      {

         c--;

      }

   }

   return c;

}



template < typename Type, typename RawType, ::enum_type m_etypeContainer >
Type & string_array_base < Type, RawType, m_etypeContainer > ::get_network_payload(Type & str, bool bNewLine) const
{

   str += "[";

   if(get_count() > 0)
   {

      str += "\"";

      str += element_at(0);

      str += "\"";

   }

   for(::index i = 1; i < get_count(); i++)
   {

      if (bNewLine)
      {

         str += ", \r\n";

      }
      else
      {

         str += ", ";

      }

      str += "\"";

      str += element_at(i);

      str += "\"";

   }

   if (bNewLine)
   {

      str += "\r\n";

   }

   str += "]";

   return str;

}





template < typename Type, typename RawType, ::enum_type m_etypeContainer >
Type string_array_base < Type, RawType, m_etypeContainer > ::_008Implode(const RawType &strSeparator, const RawType &strLastSeparator, ::index iStart, ::count inCountLastOut) const
{

   Type str;

   if(!this->prepare_first_in_count_last_out(iStart, inCountLastOut))
   {

      return str;

   }

   for (::index i = iStart; i <= inCountLastOut; i++)
   {

      if (i > iStart)
      {

         if (i == inCountLastOut)
         {

            str += strLastSeparator;

         }
         else
         {

            str += strSeparator;

         }

      }

      str += this->element_at(i);

   }

   return str;

}



template < typename Type, typename RawType, ::enum_type m_etypeContainer >
Type string_array_base < Type, RawType, m_etypeContainer > ::_008IfImplode(const RawType &strIfHasElementPrefix, const RawType &strSeparator, const RawType &strLastSeparator, bool bUseLast, ::index iStart, ::count inCountLastOut) const
{

   Type str;

   if(!this->prepare_first_in_count_last_out(iStart, inCountLastOut))
   {

      return str;

   }

   if (inCountLastOut >= iStart)
   {

      str += strIfHasElementPrefix;

   }

   for (::index i = iStart; i <= inCountLastOut; i++)
   {

      if (i > iStart)
      {

         if (i == inCountLastOut && bUseLast)
         {

            str += strLastSeparator;

         }
         else
         {

            str += strSeparator;

         }

      }

      str += this->element_at(i);

   }

   return str;

}


//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//Type string_array_base < Type, RawType, m_etypeContainer > ::_008IfImplode(const RawType &strIfHasElementPrefix, const RawType &strSeparator, const RawType &strLastSeparator, bool bUseLast, ::index iStart, ::index iEnd) const
//{
//
//   Type str;
//
//   _008IfImplode(str, strIfHasElementPrefix, strSeparator, strLastSeparator, bUseLast, iStart, iEnd);
//
//   return str;
//
//}




template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::array < const ::ansi_character * > string_array_base < Type, RawType, m_etypeContainer > ::c_ansi_get(bool bMemoryAlloc) const
{

   ::array < const ::ansi_character * > psza;

   for(::index i = 0; i < get_size(); i++)
   {

      char * psz = nullptr;

      if(bMemoryAlloc)
      {

         psz = ansi_duplicate(element_at(i));

      }
      else
      {

         psz = strdup(element_at(i));

      }

      psza.add(psz);

   }

   return psza;

}


//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//::array < const ::wide_character * > string_array_base < Type, RawType, m_etypeContainer > ::c_wide_get(bool bMemoryAlloc) const
//{
//
//   ::array < const ::wide_character * > psza;
//
//   for (::index i = 0; i < get_size(); i++)
//   {
//
//      ::wide_character * pwsz = nullptr;
//
//      if(bMemoryAlloc)
//      {
//
//         pwsz = wide_duplicate(wstring(element_at(i)));
//
//      }
//      else
//      {
//
//         pwsz = wcsdup(wstring(element_at(i)));
//
//
//      }
//
//      psza.add(pwsz);
//
//   }
//
//   return psza;
//
//}


/// expect strings allocated with malloc (sic, not memory_allocate) or strdup and array allocated with malloc (sic, not memory_allocate)
template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer > ::c_add(char ** ppsz, ::count c, bool bMemoryAlloc)
{

   for (::index i = 0; i < c; i++)
   {

      auto psz = ppsz[i];

      auto str = Type(psz);

      this->add(str);

      if(bMemoryAlloc)
      {

         memory_free(psz);

      }
      else
      {

         free(psz);

      }

   }

   if (ppsz != nullptr)
   {

      if(bMemoryAlloc)
      {

         memory_free(ppsz);

      }
      else
      {

         free(ppsz);

      }

   }

}




/// expect strings allocated with malloc (sic, not memory_allocate) or strdup and array allocated with malloc (sic, not memory_allocate)
template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer > ::c_add(char ** ppszParam, bool bMemoryAlloc)
{

   auto ppsz = ppszParam;

   while(ppsz != nullptr)
   {

      auto psz = *ppsz;

      auto str = Type(psz);

      this->add(str);

      if(bMemoryAlloc)
      {

         memory_free(psz);

      }
      else
      {

         free(psz);

      }
      ppsz++;

   }

   if(bMemoryAlloc)
   {

      memory_free(ppszParam);

   }
   else
   {

      free(ppszParam);

   }

}

/// expect strings allocated with malloc (sic, not memory_allocate) or wcsdup and array allocated with malloc (sic, not memory_allocate)
template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer > ::c_add(wchar_t ** ppwsz, ::count c, bool bMemoryAlloc)
{

   for (::index i = 0; i < c; i++)
   {

      auto pwsz = ppwsz[i];

      auto str = Type(pwsz);

      this->add(str);

      if(bMemoryAlloc)
      {

         memory_free(pwsz);

      }
      else
      {

         free(pwsz);

      }
   }

   if(ppwsz != nullptr)
   {

      if(bMemoryAlloc)
      {

         memory_free(ppwsz);

      }
      else
      {

         free(ppwsz);

      }
   }

}


/// expect strings allocated with malloc (sic, not memory_allocate) or wcsdup and array allocated with malloc (sic, not memory_allocate)
template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer > ::c_add(wchar_t ** ppwszParam, bool bMemoryAlloc)
{

   auto ppwsz = ppwszParam;

   while (ppwsz != nullptr)
   {

      auto pwsz = *ppwsz;

      Type str(pwsz);

      this->add(str);

      if(bMemoryAlloc)
      {

         memory_free(pwsz);

      }
      else
      {

         free(pwsz);

      }
      ppwsz++;

   }

   if(ppwszParam != nullptr)
   {

      if(bMemoryAlloc)
      {

         memory_free(ppwsz);

      }
      else
      {

         free(ppwsz);

      }
   }

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer > ::order()
{

   this->predicate_sort([](Type & a, Type & b)
                        {

                            return a.order(b) < 0;

                        });

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer > ::case_insensitive_order()
{

   this->predicate_sort([](Type & a, Type & b)
                        {
                            return a.case_insensitive_order(b) < 0;
                        });

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer > ::collate_order()
{

   this->predicate_sort([](Type & a, Type & b)
                        {
                            return a.collate(b) < 0;
                        });

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer > ::collate_sort_ci()
{

   this->predicate_sort([](Type & a, Type & b)
                        {
                            return a.case_insensitive_collate(b) < 0;
                        });

}













template < typename Type, typename RawType, ::enum_type m_etypeContainer >
Type string_array_base < Type, RawType, m_etypeContainer >::safe_at(::index nIndex, Type tDefault) const
{

if (nIndex < 0 || nIndex >= this->get_size())
{

return tDefault;

}

return this->element_at(nIndex);

}

template < typename Type, typename RawType, ::enum_type m_etypeContainer >
Type string_array_base < Type, RawType, m_etypeContainer >::safe_at(::index nIndex, Type tDefault)
{
if (nIndex < 0 || nIndex >= this->get_size())
return tDefault;

return this->element_at(nIndex);

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
Type string_array_base < Type, RawType, m_etypeContainer >::get_at(::index nIndex) const
{
if (nIndex < 0 || nIndex >= this->size())
throw_exception(error_index_out_of_bounds);
return get_data()[nIndex];
}

//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//void string_array_base < Type, RawType, m_etypeContainer >::set_at(::index nIndex, const char * newElement)
//{
//   if (nIndex < 0 || nIndex >= this->size())
//      throw_exception(error_index_out_of_bounds);
//   get_data()[nIndex] = newElement;
//}
//

template < typename Type, typename RawType, ::enum_type m_etypeContainer >
void string_array_base < Type, RawType, m_etypeContainer >::set_at(::index nIndex, const Type & newElement)
{
if (nIndex < 0 || nIndex >= this->size())
throw_exception(error_index_out_of_bounds);
get_data()[nIndex] = newElement;
}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
Type & string_array_base < Type, RawType, m_etypeContainer >::element_at(::index nIndex)
{
if (nIndex < 0 || nIndex >= this->size())
throw_exception(error_index_out_of_bounds);
return get_data()[nIndex];
}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
const Type & string_array_base < Type, RawType, m_etypeContainer >::element_at(::index nIndex) const
{
if (nIndex < 0 || nIndex >= this->size())
throw_exception(error_index_out_of_bounds);
return get_data()[nIndex];
}



//
//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//::index string_array_base < Type, RawType, m_etypeContainer >::add(const property & prop)
//{
//
//   return add(prop.get_value());
//
//}

////#include "acme/primitive/primitive/payload.h"

//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//string_array_base < Type, RawType, m_etypeContainer >  & string_array_base < Type, RawType, m_etypeContainer > ::operator = (const ::payload & payload)
//{
//
//   this->erase_all();
//
//   if (payload.get_type() == ::e_type_string_array)
//   {
//
//      payload.get_array(*this);
//
//   }
//   else
//   {
//
//      if (payload.get_count() == 1)
//      {
//
//         add((Type)payload.string());
//
//      }
//      else if (payload.get_count() > 1)
//      {
//
//         payload.get_array(*this);
//
//      }
//
//   }
//
//   return *this;
//
//}


//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//memory string_array_base < Type, RawType, m_etypeContainer > ::GetFormatV004()
//{
//
//   strsize iTotalLength = 0;
//
//   ::index i;
//
//   for (i = 0; i < this->size(); i++)
//   {
//      iTotalLength += this->element_at(i).get_length();
//      iTotalLength++;
//   }
//
//   if (iTotalLength == 0)
//   {
//      iTotalLength = 2;
//   }
//   else
//   {
//      iTotalLength++;
//   }
//
//   memory mem;
//
//   mem.set_size(iTotalLength * sizeof(char));
//
//   char * lpsz = (char *)mem.get_data();
//
//   memory_set(lpsz, 0x00, iTotalLength * sizeof(char));
//
//   char * lpszN = lpsz;
//
//   strsize iLength;
//
//   for (i = 0; i < this->size(); i++)
//   {
//
//      Type * pstr = &this->element_at(i);
//
//      iLength = pstr->get_length();
//
//#ifdef WINDOWS
//      strcat_s(lpszN, (size_t) iLength, *pstr);
//#else
//      ansi_concatenate(lpszN, *pstr);
//#endif
//
//#ifdef WINDOWS_DESKTOP
//      iLength = strlen(lpszN);
//#elif defined(_UWPDOW)
//      iLength = wcsnbcnt(lpszN, iLength);
//#else
//      iLength = strlen(lpszN);
//#endif
//
//      lpszN = (char *)((byte *)lpszN) + iLength + sizeof(char);
//
//   }
//
//   if (iTotalLength == 2)
//   {
//      memory_set(lpsz, 0x00, iTotalLength * sizeof(char));
//   }
//   else
//   {
//      memory_set(lpszN, 0x00, sizeof(char));
//   }
//
//   return mem;
//
//}


//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//template < typename TYPE >
//inline ::index string_array_base < Type, RawType, m_etypeContainer > ::add(const TYPE & type)
//{
//
//    return ::acme::array::add(*this, type);
//
//}

//
//template < typename Type, typename RawType, ::enum_type m_etypeContainer >
//template < primitive_array INDEX_ARRAY >
//void string_array_base < Type, RawType, m_etypeContainer >::get_quick_sort_ci(INDEX_ARRAY & ia)
//{
//
//   INDEX_ARRAY stackLowerBound;
//   INDEX_ARRAY stackUpperBound;
//   ::index iLowerBound;
//   ::index iUpperBound;
//   ::index iLPos,iUPos,iMPos;
//   Type t;
//   ia.erase_all();
//   ::acme::array::append_sequence(ia,(::index)0,(::index)get_upper_bound());
//   if(this->get_size() >= 2)
//   {
//      stackLowerBound.push(0);
//      stackUpperBound.push(this->get_size() - 1);
//      while(true)
//      {
//         iLowerBound = stackLowerBound.pop();
//         iUpperBound = stackUpperBound.pop();
//         iLPos = iLowerBound;
//         iMPos = iLowerBound;
//         iUPos = iUpperBound;
//         while(true)
//         {
//            while(true)
//            {
//               if(iMPos == iUPos)
//                  break;
//               if(this->element_at(ia[iMPos]).case_insensitive_order(this->element_at(ia[iUPos])) <= 0)
//                  iUPos--;
//               else
//               {
//                  ::index i = ia[iMPos];
//                  ia[iMPos] = ia[iUPos];
//                  ia[iUPos] = i;
//                  break;
//               }
//            }
//            if(iMPos == iUPos)
//               break;
//            iMPos = iUPos;
//            while(true)
//            {
//               if(iMPos == iLPos)
//                  break;
//
//               if(this->element_at(ia[iLPos]).case_insensitive_order(this->element_at(ia[iMPos])) <= 0)
//                  iLPos++;
//               else
//               {
//                  ::index i = ia[iLPos];
//                  ia[iLPos] = ia[iMPos];
//                  ia[iMPos] = i;
//                  break;
//               }
//            }
//            if(iMPos == iLPos)
//               break;
//            iMPos = iLPos;
//         }
//         if(iLowerBound < iMPos - 1)
//         {
//            stackLowerBound.push(iLowerBound);
//            stackUpperBound.push(iMPos - 1);
//         }
//         if(iMPos + 1 < iUpperBound)
//         {
//            stackLowerBound.push(iMPos + 1);
//            stackUpperBound.push(iUpperBound);
//         }
//         if(stackLowerBound.get_size() == 0)
//            break;
//      }
//   }
//
//}
//




template < typename Type, typename RawType, ::enum_type m_etypeContainer >
inline void string_array_base < Type, RawType, m_etypeContainer > ::debug_output(::index iStart, ::count inCountLastOut)
{

::output_debug_string(implode(STR_NEWLINE, iStart, inCountLastOut));

}





template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::suffix_find_first_ci(const RawType &strTopic, ::index iFind, ::index iLast) const
{

   if (this->prepare_first_last(iFind, iLast))
   {

      for (; iFind <= iLast; iFind++)
      {

         if (strTopic.case_insensitive_ends(this->element_at(iFind)))
         {

            return iFind;

         }

      }

   }

   return -1;

}





template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::suffix_find_first(const RawType &strTopic, ::index iFind, ::index iLast) const
{

   if (this->prepare_first_last(iFind, iLast))
   {

      for (; iFind <= iLast; iFind++)
      {

         if (strTopic.ends(this->element_at(iFind)))
         {

            return iFind;

         }

      }

   }

   return -1;

}




template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::_find_first_suffixed(const RawType &strSuffix, ::index iFind, ::index iLast) const
{

   for (; iFind < iLast; iFind++)
   {

      if (this->element_at(iFind).ends(strSuffix))
      {

         return iFind;

      }

   }

   return -1;

}


template < typename Type, typename RawType, ::enum_type m_etypeContainer >
::index string_array_base < Type, RawType, m_etypeContainer > ::_find_first_suffixed_ci(const RawType &strSuffix, ::index iFind, ::index iLast) const
{

   for (; iFind < iLast; iFind++)
   {

      if (this->element_at(iFind).case_insensitive_ends(strSuffix))
      {

         return iFind;

      }

   }

   return -1;

}


