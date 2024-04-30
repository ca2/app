//
// Created by camilo on 23/12/2022 01:38 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/primitive/string/c/ancient/_c.h"


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
template < typename PRED >
Type string_array_base < Type, RawType, t_etypeContainer > ::predicate_implode(PRED pred, const RawType &strSeparator,::raw::index i,::raw::count inCountLastOut) const
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
inline Type & string_array_base < Type, RawType, t_etypeContainer >::last(::raw::index i)
{
return this->element_at(get_upper_bound(i));
}

template < typename Type, typename RawType, ::enum_type t_etypeContainer >
inline Type string_array_base < Type, RawType, t_etypeContainer >::last(::raw::index i) const
{
return this->element_at(get_upper_bound(i));
}

template < typename Type, typename RawType, ::enum_type t_etypeContainer >
inline Type & string_array_base < Type, RawType, t_etypeContainer >::first(::raw::index i)
{
return this->element_at(get_lower_bound(i));
}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
inline Type string_array_base < Type, RawType, t_etypeContainer >::first(::raw::index i) const
{

return this->element_at(get_lower_bound(i));

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
inline ::raw::count string_array_base < Type, RawType, t_etypeContainer >::get_size() const
{

   return this->size();

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
inline ::raw::count string_array_base < Type, RawType, t_etypeContainer >::get_count() const
{

   return this->size();

}

template < typename Type, typename RawType, ::enum_type t_etypeContainer >
inline ::raw::index string_array_base < Type, RawType, t_etypeContainer >::get_lower_bound(::raw::index i) const
{
return i;
}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
inline ::raw::index string_array_base < Type, RawType, t_etypeContainer >::get_upper_bound(::raw::index i) const
{

return this->size() + i;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
inline ::raw::index string_array_base < Type, RawType, t_etypeContainer >::get_middle_index(::raw::index i) const
{

return get_upper_bound() / 2 + i;

}







template < typename Type, typename RawType, ::enum_type t_etypeContainer >
string_array_base < Type, RawType, t_etypeContainer >::~string_array_base()
{

   // // ASSERT_VALID(this);

}




//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//::raw::count string_array_base < Type, RawType, t_etypeContainer >::add(const string_array_base < Type, RawType, t_etypeContainer >& src)
//{
//
//   if(this == &src)
//   {
//
//      string_array_base < Type, RawType, t_etypeContainer > thisCopy(src);
//
//      return add(thisCopy);
//
//   }
//
//    // ASSERT_VALID(this);
//   ASSERT(this != &src);   // cannot append to itself
//
//   ::raw::count nOldSize = this->size();
//
//   ::raw::count nAddSize = src.size();
//
//   this->set_size(nOldSize + nAddSize);
//
//   CopyElements(&this->m_begin[nOldSize],src.m_begin, nAddSize);
//
//   return nOldSize;
//
//}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
string_array_base < Type, RawType, t_etypeContainer > &
string_array_base < Type, RawType, t_etypeContainer >::c_stra(string_array_base < Type, RawType, t_etypeContainer > & stra) const
{

   for (auto & str : *this)
   {

      stra.add(str.c_str());

   }

   return stra;

}

template < typename Type, typename RawType, ::enum_type t_etypeContainer >
string_array_base < Type, RawType, t_etypeContainer >
string_array_base < Type, RawType, t_etypeContainer >::c_stra() const
{

   string_array_base < Type, RawType, t_etypeContainer > stra;

   return c_stra(stra);

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer >::copy(const string_array_base < Type, RawType, t_etypeContainer >& src)
{

   if(this == &src)
      return;

   // // ASSERT_VALID(this);

   auto nSrcSize = src.size();

   this->set_size(nSrcSize);

   CopyElements(this->m_begin, src.m_begin, nSrcSize);

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
template < primitive_array ARRAY >
void string_array_base < Type, RawType, t_etypeContainer >::copy(const ARRAY & src)
{

   this->set_size((::raw::count) src.size());

   for(::raw::index i = 0; i < this->size(); i++)
   {

      get_data()[i] = as_string(src[i]);

   }

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
Type & string_array_base < Type, RawType, t_etypeContainer >::set_at_grow(::raw::index nIndex,const Type & newElement)
{
// // ASSERT_VALID(this);
ASSERT(nIndex >= 0);

if(nIndex >= this->size())
this->set_size(nIndex + 1);

return get_data()[nIndex] = newElement;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer >::_007FindLine(const RawType &strKey, ::raw::index iStart) const
{

   for(::raw::index i = iStart; i < get_count(); i++)
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer >::_007SetLine(const RawType &strKey, const RawType &strValue, ::raw::index iStart)
{

   ::raw::index iKeyIndex = _007FindLine(strKey, iStart);

   Type strNewLine = strKey + "=" + strValue;

   if(iKeyIndex >= 0)
   {

      this->element_at(iKeyIndex) = strNewLine;

   }
   else
   {

      this->add(strNewLine);

   }

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer >::_007GetLine(RawType & strValue, const RawType &strKey, ::raw::index iStart) const
{

   ::raw::index iKeyIndex = _007FindLine(strKey, iStart);

   if(iKeyIndex < 0)
   {

      return -1;

   }

   strValue = this->element_at(iKeyIndex).substr(strKey.size() + 1);

   return iKeyIndex;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
RawType string_array_base < Type, RawType, t_etypeContainer >::_007GetLine(const RawType &strKey, ::raw::index iStart) const
{

   RawType strValue;

   if(_007GetLine(strValue, strKey, iStart) < 0)
   {

      return "";

   }

   return strValue;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer >::_007FindSection(const RawType &strSection) const
{

   ::raw::index iSectionIndex = this->find_first_begins_ci(strSection);

   return iSectionIndex;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer >::_007FindLine(const RawType &strSection, const RawType &strKey) const
{

   ::raw::index iSectionIndex = this->_007FindSection(strSection);

   if(iSectionIndex < 0)
   {

      return -1;

   }

   return this->_007FindLine(strKey, iSectionIndex + 1);

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer >::_007OpenSection(const RawType &strSection)
{

   ::raw::index iSectionIndex = this->_007FindSection(strSection);

   if(iSectionIndex < 0)
   {

      this->add("");

      iSectionIndex = this->add(strSection);

   }

   return iSectionIndex;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer >::_007SetLine(const RawType &strSection, const RawType &strKey, const RawType &strValue)
{

   ::raw::index iSectionIndex = this->_007OpenSection(strSection);

   if(iSectionIndex < 0)
   {

      this->add("");

      iSectionIndex = this->add(strSection);

   }

   this->_007SetLine(strKey, strValue, iSectionIndex + 1);

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer >::_007GetLine(RawType & strValue, const RawType &strSection, const RawType &strKey) const
{

   ::raw::index iSectionIndex = this->_007FindSection(strSection);

   if(iSectionIndex < 0)
   {

      return -1;

   }

   return _007GetLine(strValue, strKey, iSectionIndex + 1);

}

template < typename Type, typename RawType, ::enum_type t_etypeContainer >
RawType string_array_base < Type, RawType, t_etypeContainer >::_007GetLine(const RawType &strSection, const RawType &strKey) const
{

   RawType strValue;

   if(_007GetLine(strValue, strSection, strKey) < 0)
   {

      return "";

   }

   return strValue;

}







template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer >::insert_empty(::raw::index nIndex,::raw::count nCount)
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
::raw::count nOldSize = (::raw::count) this->size();
this->set_size((::raw::count) (this->size() + nCount));  // grow it to new size_i32
// shift old data up to fill gap
memory_transfer(&get_data()[nIndex + nCount],&get_data()[nIndex],(nOldSize - nIndex) * sizeof(Type));

// re-init slots we copied from
for(::raw::index i = nIndex; i < nIndex + nCount; i++)
{

get_data()[i].default_construct();

}

}

// insert new value in the gap
ASSERT(nIndex + nCount <= this->size());
}

template < typename Type, typename RawType, ::enum_type t_etypeContainer >
Type & string_array_base < Type, RawType, t_etypeContainer >::insert_empty(::raw::index nIndex)
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

memory_transfer(this->ptr_at(nIndex + 1), this->ptr_at(nIndex), (nOldSize - nIndex) * sizeof(Type));

for(::raw::index i = nIndex; i < nIndex + 1; i++)
{

new (this->ptr_at(nIndex)) RawType();

}

}

ASSERT(nIndex + 1 <= this->size());

return get_data()[nIndex];

}



template < typename Type, typename RawType, ::enum_type t_etypeContainer >
Type & string_array_base < Type, RawType, t_etypeContainer >::insert_at(::raw::index nIndex,const Type & strElement)
{

return insert_empty(nIndex) = strElement;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer >::insert_at(::raw::index nIndex, const Type & strElement,::raw::count nCount)
{

// make room for new elements
insert_empty(nIndex,nCount);



// copy elements into the is_empty space
//Type temp = newElement;
while(nCount--)
get_data()[nIndex++] = strElement;

}



template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer >::insert_at(::raw::index nStartIndex,const string_array_base < Type, RawType, t_etypeContainer > & NewArray)
{
//    // ASSERT_VALID(this);
ASSERT(&NewArray != nullptr);
//   ASSERT_KINDOF(string_array_base < Type, RawType, t_etypeContainer >, &NewArray);
//   ASSERT_VALID(&NewArray);
ASSERT(nStartIndex >= 0);

if(NewArray.get_size() > 0)
{
insert_at(nStartIndex,NewArray.get_at(0),NewArray.get_size());
for(::raw::index i = 0; i < NewArray.get_size(); i++)
set_at(nStartIndex + i,NewArray.get_at(i));
}
}


//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//void string_array_base < Type, RawType, t_etypeContainer >::dump(dump_context & dumpcontext) const
//{
//   //matter::dump(dumpcontext);
//
//   dumpcontext << "with " << this->size() << " elements";
//   if(dumpcontext.GetDepth() > 0)
//   {
//      for(::raw::index i = 0; i < this->size(); i++)
//         dumpcontext << "\n\t[" << i << "] = " << get_data()[i].c_str();
//   }
//
//   dumpcontext << "\n";
//}
//
//
//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//void string_array_base < Type, RawType, t_etypeContainer >::assert_ok() const
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
//      ASSERT(is_memory_segment_ok(this->m_begin, (memsize_cast) (this->m_nMaxSize * sizeof(Type))));
//
//   }
//
//}




template < typename Type, typename RawType, ::enum_type t_etypeContainer >
string_array_base < Type, RawType, t_etypeContainer > string_array_base < Type, RawType, t_etypeContainer >::slice(::raw::index i, ::raw::count inCountLastOut) const
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
string_array_base < Type, RawType, t_etypeContainer > & string_array_base < Type, RawType, t_etypeContainer >::operator =(const string_array_base < Type, RawType, t_etypeContainer > & tokena)
{

   copy(tokena);

   return *this;

}


//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//inline Type & string_array_base < Type, RawType, t_etypeContainer >::add_new()
//{
//
//   this->allocate(this->size() + 1);
//
//   return this->last();
//
//}
//
//
//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//::raw::index string_array_base < Type, RawType, t_etypeContainer >::add_new(::raw::count c)
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


//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//Type & string_array_base < Type, RawType, t_etypeContainer >::new_element(::raw::count c)
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
Type & string_array_base < Type, RawType, t_etypeContainer >::add_get(const Type & newElement)
{

   ::raw::index nIndex = this->size();

   return set_at_grow(nIndex, newElement);

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer >::erase_duplicates()
{

   for(::raw::index i = 1; i < this->get_size();)
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer >::erase_duplicates_ci()
{

   for(::raw::index i = 1; i < this->get_size();)
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
const Type* string_array_base < Type, RawType, t_etypeContainer >::get_data() const
{
   return (const Type*)this->m_begin;
}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
Type* string_array_base < Type, RawType, t_etypeContainer >::get_data()
{
   return (Type*)this->m_begin;
}



template < typename Type, typename RawType, ::enum_type t_etypeContainer >
string_array_base < Type, RawType, t_etypeContainer > ::string_array_base(const string_array_base < Type, RawType, t_etypeContainer > & array) :
        BASE_ARRAY((const BASE_ARRAY&) array)
{
}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
string_array_base < Type, RawType, t_etypeContainer > ::string_array_base(CHARACTER* const* ppsz, ::raw::count c)
{

   this->set_size(c);

   for (::raw::index i = 0; i < c; i++)
   {

      this->element_at(i) = ppsz[i];

   }

}


//#ifdef UNIVERSAL_WINDOWS
//
//
//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//string_array_base < Type, RawType, t_etypeContainer > ::string_array_base(Platform::Array < Platform::String ^ > ^ refstra)
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::add_tokens(const RawType &str, const RawType &strSeparator,bool bAddEmpty)
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



template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::_001AddTokens(const RawType &str)

{

   ::tokenizer strTokenizer(str);


   Type strToken;

   while(strTokenizer._001GetNextToken(strToken))
   {

      string_array_base::add(strToken);

   }

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::add_smallest_tokens(const RawType &str, const RawStringArray & straSeparator, bool bAddEmpty, bool bWithSeparator)
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::add_words(const RawType &str)
{

   ::tokenizer strTokenizer(str);

   Type strWord;

   while(strTokenizer.get_word(strWord))
   {

      string_array_base::add(strWord);

   }

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
template < bool bAddEmpty >
typename Type::const_iterator string_array_base < Type, RawType, t_etypeContainer > ::_____add_lines_rn(const SCOPED_STRING & scopedstr)
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

      if(*pNext == '\r')
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





template < typename Type, typename RawType, ::enum_type t_etypeContainer >
template < bool bAddEmpty >
void string_array_base < Type, RawType, t_etypeContainer > ::_add_lines(const SCOPED_STRING &strParam)
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::get_format_string(Type & str,const RawType &strSeparator) const

{
   str.empty();
   if(this->size() > 0)
   {
      str = get_at(0);
   }
   for(::raw::index i = 1; i < this->size(); i++)
   {
      str += strSeparator + get_at(i);

   }
}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::add_unique(const Type & newElement)
{

   auto iFind = find_first(newElement);

   if (iFind >= 0)
   {

      return -1;

   }

   return string_array_base::add(newElement);

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::append_unique(const string_array_base & newElements)
{

   ::raw::count count = 0;

   for(auto & newElement : newElements)
   {

      if (add_unique(newElement) >= 0)
      {

         count++;

      }

   }

   return count;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::case_insensitive_add_unique(const Type & newElement)

{

   ::raw::index iFind = find_first_ci(newElement);

   if (iFind >= 0)
   {

      return -1;

   }

   string_array_base::add(newElement);

   return get_upper_bound();

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::case_insensitive_append_unique(const string_array_base & straNewElements)
{

   ::raw::count count = 0;

   for(auto & newElement : straNewElements)
   {

      if (case_insensitive_add_unique(newElement) >= 0)
      {

         count++;

      }

   }

   return count;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::find_first(const RawType &str, ::raw::index iFind, ::raw::index iLast) const
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::find_first_ci(const RawType &str,::raw::index iFind,::raw::index iLast) const
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




















template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::rear_find(const RawType &str, ::raw::index iFind, ::raw::index iLast) const
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

template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::reverse_find_ci(const RawType &str, ::raw::index iFind, ::raw::index iLast) const
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






template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::count(const RawType &str, ::raw::index iFind, ::raw::index iLast) const
{

   ::raw::count count = 0;

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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::count_ci(const RawType &str, ::raw::index iFind, ::raw::index iLast) const
{

   ::raw::count count = 0;

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




template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::find_last_ci(const RawType &str, ::raw::index iFind, ::raw::index iLast) const
{

   return reverse_find_ci(str, iFind, iLast);

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::find_last(const RawType &str, ::raw::index iFind, ::raw::index iLast) const
{

   return rear_find(str, iFind, iLast);

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::_066Find(const RawType &strParam) const
{

   RawString str(strParam);

   ::raw::index iSel = this->find_first(str);

   if (iSel < 0)
   {

      iSel = this->find_first_ci(str);

      if(iSel < 0)
      {

         ::raw::index iHalfLen = (::raw::index) (str.length() / 2);

         for(::raw::index iTruncate = (::raw::index) str.length(); iTruncate >= iHalfLen; iTruncate--)
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::find_first_contains(const RawType &strSubstring, ::raw::index iFind, ::raw::index iLast, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
{

   if (this->prepare_first_last(iFind, iLast))
   {

      return _find_first_contains(strSubstring, iFind, iLast, ppszBeg, ppszEnd);

   }

   return -1;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::_find_first_contains(const RawType &strSubstring, ::raw::index iFind, ::raw::index iLast, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
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




template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::find_first_contains_ci(const RawType &strSubstring,::raw::index iFind,::raw::index iLast, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
{

   if (this->prepare_first_last(iFind, iLast))
   {

      return _find_first_contains_ci(strSubstring, iFind, iLast, ppszBeg, ppszEnd);

   }

   return -1;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::_find_first_contains_ci(const RawType &strSubstring, ::raw::index iFind, ::raw::index iLast, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::prefix_find_first_ci(const RawType &strTopic,::raw::index iFind,::raw::index iLast) const
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::prefix_find_first(const RawType &strTopic, ::raw::index iFind, ::raw::index iLast) const
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




template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::substring_find_first(const RawType &strTopic, ::raw::index iFind, ::raw::index iLast, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::substring_find_first_ci(const RawType &strTopic, ::raw::index iFind, ::raw::index iLast, const CHARACTER ** ppszBeg, const CHARACTER ** ppszEnd) const
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




template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::find_first_suffixed_ci(const RawType &strSuffix, ::raw::index iFind, ::raw::index iLast) const
{

   if (this->prepare_first_last(iFind, iLast))
   {

      return _find_first_suffixed_ci(strSuffix, iFind, iLast);

   }

   return -1;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::find_first_suffixed(const RawType &strSuffix, ::raw::index iFind, ::raw::index iLast) const
{

   if (this->prepare_first_last(iFind, iLast))
   {

      return _find_first_suffixed(strSuffix, iFind, iLast);

   }

   return -1;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::find_first_begins_eat(Type & strFoundAndEaten, const RawType &strSuffix, ::raw::index iFind, ::raw::index iLast) const
{

   iFind = find_first_begins(strSuffix, iFind, iLast);

   if (iFind < 0)
   {

      return iFind;

   }

   strFoundAndEaten = element_at(iFind).substr(strSuffix.size());

   return iFind;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::find_first_with_starting_word_eat(Type & strFoundAndEaten, const RawType &strStartingWord, ::raw::index iFind, ::raw::index iLast) const
{

   iFind = find_first_with_starting_word(strStartingWord, iFind, iLast);

   if (iFind < 0)
   {

      return iFind;

   }

   strFoundAndEaten = element_at(iFind).substr(strStartingWord.size());

   return iFind;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::find_first_begins_eat_ci(Type & strFoundAndEaten,const RawType &strPrefix, ::raw::index iFind,::raw::index iLast) const
{

   iFind  = find_first_begins_ci(strPrefix,iFind,iLast);

   if (iFind < 0)
   {

      return iFind;

   }

   strFoundAndEaten = element_at(iFind).substr(strPrefix.size());

   return iFind;

}




template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::find_first_ends_eat(Type & strFoundAndEaten, const RawType &strSuffix, ::raw::index iFind, ::raw::index iLast) const
{

   iFind = find_first_ends(strSuffix, iFind, iLast);

   if (iFind < 0)
   {

      return iFind;

   }

   strFoundAndEaten = element_at(iFind).right(strSuffix.size());

   return iFind;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::find_first_ends_eat_ci(Type & strFoundAndEaten, const RawType &strSuffix, ::raw::index iFind, ::raw::index iLast) const
{

   iFind = find_first_ends_ci(strSuffix, iFind, iLast);

   if (iFind < 0)
   {

      return iFind;

   }

   strFoundAndEaten = element_at(iFind).right(strSuffix.size());

   return iFind;

}



template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::find_first_contains_eat(Type & strFoundAndEaten, const RawType &strSubstring, ::raw::index iFind, ::raw::index iLast) const
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::find_first_contains_eat_ci(Type & strFoundAndEaten, const RawType &strTopic, ::raw::index iFind, ::raw::index iLast) const
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::find_first_prefixed(const RawType &strPrefix,::raw::index iFind,::raw::index iLast) const
{

   if (this->prepare_first_last(iFind, iLast))
   {

      return _find_first_prefixed(strPrefix, iFind, iLast);

   }

   return -1;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::find_first_with_starting_word(const RawType &strPrefix,::raw::index iFind,::raw::index iLast) const
{

   if (this->prepare_first_last(iFind, iLast))
   {

      return _find_first_with_starting_word(strPrefix, iFind, iLast);

   }

   return -1;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::find_first_prefixed_ci(const RawType &strPrefix, ::raw::index iFind, ::raw::index iLast) const
{

   if (this->prepare_first_last(iFind, iLast))
   {

      return _find_first_prefixed_ci(strPrefix, iFind, iLast);

   }

   return -1;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::_find_first_prefixed(const RawType &strPrefix, ::raw::index iFind, ::raw::index iLast) const
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::_find_first_with_starting_word(const RawType &strStartingWord, ::raw::index iFind, ::raw::index iLast) const
{

   for (; iFind <= iLast; iFind++)
   {

      if (this->element_at(iFind).starts_with_word(strStartingWord))
      {

         return iFind;

      }

   }

   return -1;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::_find_first_prefixed_ci(const RawType &strPrefix, ::raw::index iFind, ::raw::index iLast) const
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

template < typename Type, typename RawType, ::enum_type t_etypeContainer >
bool string_array_base < Type, RawType, t_etypeContainer > ::_067ContainsCi(const RawType &str, ::raw::index iFind, ::raw::index iLast, ::raw::count countMin, ::raw::count countMax) const
{

   ::raw::count count = 0;

   while ((count < countMin || (countMax >= 0 && count <= countMax)) && (iFind = find_first_ci(str, iFind, iLast)) >= 0)
   {
      count++;

   }

   return count >= countMin && conditional(countMax >= 0, count <= countMax);

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
bool string_array_base < Type, RawType, t_etypeContainer > ::_067Contains(const RawType &str, ::raw::index iFind, ::raw::index iLast, ::raw::count countMin, ::raw::count countMax) const
{

   ::raw::count count = 0;

   while ((count < countMin || (countMax >= 0 && count <= countMax)) && (iFind = find_first(str, iFind, iLast)) >= 0)
   {

      count++;

   }

   return count >= countMin && conditional(countMax >= 0, count <= countMax);

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
bool string_array_base < Type, RawType, t_etypeContainer > ::_067ContainsSubstringCi(const RawType &str, ::raw::index iFind, ::raw::index iLast, ::raw::count countMin, ::raw::count countMax) const
{

   ::raw::count count = 0;

   while ((count < countMin || (countMax >= 0 && count <= countMax)) && (iFind = find_first_contains_ci(str, iFind, iLast)) >= 0)
   {

      count++;

   }

   return count >= countMin && conditional(countMax >= 0, count <= countMax);

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
bool string_array_base < Type, RawType, t_etypeContainer > ::_067ContainsSubstring(const RawType &str, ::raw::index iFind, ::raw::index iLast, ::raw::count countMin, ::raw::count countMax) const
{

   ::raw::count count = 0;

   while ((count < countMin || (countMax >= 0 && count <= countMax)) && (iFind = find_first_contains(str, iFind, iLast)) >= 0)
   {

      count++;

   }

   return count >= countMin && conditional(countMax >= 0, count <= countMax);

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::erase_first_ci(const RawType &str,::raw::index iFind,::raw::index iLast)
{

   if ((iFind = find_first_ci(str, iFind, iLast)) >= 0)
   {

      this->erase_at(iFind);

   }

   return iFind;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::erase_first(const RawType &str,::raw::index iFind,::raw::index iLast)
{

   if ((iFind = find_first(str, iFind, iLast)) >= 0)
   {

      this->erase_at(iFind);

   }

   return iFind;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::erase_last_ci(const RawType &str, ::raw::index iFind, ::raw::index iLast)
{

   if ((iFind = find_last_ci(str, iFind, iLast)) >= 0)
   {

      this->erase_at(iFind);

   }

   return iFind;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::erase_last(const RawType &str, ::raw::index iFind, ::raw::index iLast)
{

   if ((iFind = find_last(str, iFind, iLast)) >= 0)
   {

      this->erase_at(iFind);


   }

   return iFind;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::_067RemoveCi(const RawType &str, ::raw::index iFind, ::raw::index iLast, ::raw::count countMin, ::raw::count countMax)
{

   ::raw::count count = 0;

   if (_067ContainsCi(str, iFind, iLast, countMin, countMax))
   {

      while (conditional(countMax >= 0, count < countMax) && (iFind = erase_first_ci(str, iFind, iLast)) >= 0)
      {

         count++;

      }

   }

   return count;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::_067Remove(const RawType &str,::raw::index iFind,::raw::index iLast,::raw::count countMin,::raw::count countMax)
{

   ::raw::count count = 0;

   if (_067Contains(str, iFind, iLast, countMin, countMax))
   {

      while (conditional(countMax >= 0, count < countMax) && (iFind = erase_first(str, iFind, iLast)) >= 0)
      {
         count++;

      }

   }

   return count;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::erase_ci(const RawType &str, ::raw::index iFind, ::raw::index iLast)
{

   ::raw::count count = 0;

   while ((iFind = erase_first_ci(str, iFind, iLast)) >= 0)
   {

      count++;

   }

   return count;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::erase(const RawType &str, ::raw::index iFind, ::raw::index iLast)
{

   ::raw::count count = 0;

   while ((iFind = erase_first(str, iFind, iLast)) >= 0)
   {

      count++;

   }

   return count;

}



template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::erase_ci(const string_array_base & stra)
{

   ::raw::count count = 0;

   for(::raw::index i = 0; i < stra.get_size(); i++)
   {

      count += erase_ci(stra[i]);

   }

   return count;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::erase(const string_array_base & stra)
{

   ::raw::count count = 0;

   for(::raw::index i = 0; i < stra.get_size(); i++)
   {

      count += erase(stra[i]);

   }

   return count;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::trim_left(const RawType &strChars)
{
   for(::raw::index i = 0; i < this->size(); i++)
   {
      this->element_at(i).trim_left(strChars);
   }
}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::trim_right(const RawType &strChars)
{
   for(::raw::index i = 0; i < this->size(); i++)
   {
      this->element_at(i).trim_right(strChars);
   }
}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::trim(const RawType &strChars)
{
   for(::raw::index i = 0; i < this->size(); i++)
   {
      this->element_at(i).trim(strChars);
   }
}



template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::trim_left()
{
   for(::raw::index i = 0; i < this->size(); i++)
   {
      this->element_at(i).trim_left();
   }
}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::trim_right()
{
   for(::raw::index i = 0; i < this->size(); i++)
   {
      this->element_at(i).trim_right();
   }
}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::trim()
{
   for(::raw::index i = 0; i < this->size(); i++)
   {
      this->element_at(i).trim();
   }
}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::add_normal(const Type & newElement)

{
   return string_array_base::add(newElement);

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::erase_empty()
{

   ::raw::count count = 0;

   for(::raw::index i = 0; i < this->get_size();)
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::erase_empty_begin()
{

   ::raw::count count = 0;

   for (::raw::index i = 0; i < this->get_size();)
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

template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::erase_empty_end()
{

   ::raw::count count = 0;
   ::raw::index i;
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::erase_empty_trimmed_begin()
{
   ::raw::count count = 0;
   for (::raw::index i = 0; i < this->get_size();)
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

template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::erase_empty_trimmed_end()
{
   ::raw::count count = 0;
   ::raw::index i;
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


//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//string_array_base < Type, RawType, t_etypeContainer >  & string_array_base < Type, RawType, t_etypeContainer > ::operator =(const i64_array & ia)
//{
//
//   this->_001CopyContainer(ia);
//
//   return *this;
//
//}


/*::raw::index string_array_base < Type, RawType, t_etypeContainer > ::CountPrefixNoCase(const RawType &strPrefix)

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
::raw::index iCount = 0;
::raw::index iLen = str.length();
for(::raw::index i = 0; i < this->get_size(); i++)
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

/*void string_array_base < Type, RawType, t_etypeContainer > ::ExtractPrefixNoSortNoCase(
string_array_base < Type, RawType, t_etypeContainer >  &stra,
const RawType &str,

::raw::index iLength,
::raw::index iMinLength)
{
ASSERT(iLength >= iMinLength);
erase_all();
Type str;
if(str != nullptr)

str = str;

if(str.is_empty())
{
for(::raw::index i = 0; i < stra.get_size(); i++)
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
::raw::index iLen = maximum(str.length(), iMinLength);
for(::raw::index i = 0; i < stra.get_size(); i++)
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

::raw::index string_array_base < Type, RawType, t_etypeContainer > ::FindFirstNoSortNoCase(const RawType &str)

{
for(::raw::index i = 0; i < this->get_size(); i++)
{
if(case_insensitive_order(str, this->element_at(i)) == 0)

{
return i;
}
}
return -1;
}
*/



//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//inline stream & operator << (stream & ostream, string_array_base < Type, RawType, t_etypeContainer > & a)
//{
//
//   return ostream.stream_array(a);
//
//}


//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//inline stream & operator >> (stream & istream, string_array_base < Type, RawType, t_etypeContainer > & a)
//{
//
//   return istream.stream_array(a);
//
//}






template < typename Type, typename RawType, ::enum_type t_etypeContainer >
Type string_array_base < Type, RawType, t_etypeContainer > ::implode(const RawType &strSeparator,::raw::index i, ::raw::count inCountLastOut) const
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



template < typename Type, typename RawType, ::enum_type t_etypeContainer >
Type string_array_base < Type, RawType, t_etypeContainer > ::reverse_implode(const RawType &strSeparator,::raw::index i,::raw::count inCountLastOut) const
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
string_array_base < Type, RawType, t_etypeContainer >  & string_array_base < Type, RawType, t_etypeContainer > ::explode(const RawType &strSeparator,const RawType &str, bool bAddEmpty)
{

   this->erase_all();

   add_tokens(str, strSeparator, bAddEmpty);

   return * this;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
string_array_base < Type, RawType, t_etypeContainer >  & string_array_base < Type, RawType, t_etypeContainer > ::_001Explode(const RawType &str)
{

   this->erase_all();

   _001AddTokens(str);

   return * this;

}





template < typename Type, typename RawType, ::enum_type t_etypeContainer >
bool string_array_base < Type, RawType, t_etypeContainer > ::operator == (const typename string_array_base < Type, RawType, t_etypeContainer >::RawStringArray & a) const
{

   if (a.get_size() != get_size())
   {

      return false;

   }

   for (::raw::index i = 0; i < get_size(); i++)
   {

      if (a[i] != element_at(i))
      {

         return false;

      }

   }

   return true;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
bool string_array_base < Type, RawType, t_etypeContainer > ::operator != (const typename string_array_base < Type, RawType, t_etypeContainer >::RawStringArray & a) const
{

   return !operator == (a);

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::replace_with(const RawType &strNew, const RawType &strOld)
{

   for(::raw::index i = 0; i < this->get_size(); i++)
   {

      this->element_at(i).replace_with(strNew, strOld);

   }

}





template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::surround(const RawType &strPrefix,const RawType &strSuffix,::raw::index iStart,::raw::count inCountLastOut)
{

   if (!this->prepare_first_in_count_last_out(iStart, inCountLastOut))
   {

      return;

   }

   //Type strPrefix(strPrefix);

   //Type strSuffix(strSuffix);

   for(::raw::index i = iStart; i <= inCountLastOut; i++)
   {

      this->element_at(i) = strPrefix + this->element_at(i) + strSuffix;

   }

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
Type string_array_base < Type, RawType, t_etypeContainer > ::surround_and_implode(const RawType &strSeparator,const RawType &strPrefix,const RawType &strSuffix,::raw::index iStart,::raw::count inCountLastOut)
{

   Type str;

   if (this->prepare_first_in_count_last_out(iStart, inCountLastOut))
   {

      Type strSeparator(strSeparator);
      Type strPrefix(strPrefix);
      Type strSuffix(strSuffix);

      str = strPrefix + this->element_at(iStart) + strSuffix;

      iStart++;

      for(::raw::index i = iStart; i <= inCountLastOut; i++)
      {

         str += strSeparator + strPrefix + this->element_at(i) + strSuffix;

      }

   }

   return str;

}


//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//string_array_base < Type, RawType, t_etypeContainer >  & string_array_base < Type, RawType, t_etypeContainer > ::operator -=(const string_array_base & stra)
//{
//
//   erase(stra);
//
//   return *this;
//
//}


//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//string_array_base < Type, RawType, t_etypeContainer >  & string_array_base < Type, RawType, t_etypeContainer > ::operator +=(const string_array_base & stra)
//{
//
//   add(stra);
//
//   return *this;
//
//}


//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//string_array_base < Type, RawType, t_etypeContainer >  string_array_base < Type, RawType, t_etypeContainer > ::operator -(const string_array_base & straParam) const
//{
//   string_array_base < Type, RawType, t_etypeContainer >  stra(*this);
//   stra -= straParam;
//   return stra;
//}


//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//string_array_base < Type, RawType, t_etypeContainer >  string_array_base < Type, RawType, t_etypeContainer > ::operator +(const string_array_base & straParam) const
//{
//   string_array_base < Type, RawType, t_etypeContainer >  stra(*this);
//   stra += straParam;
//   return stra;
//}






template < typename Type, typename RawType, ::enum_type t_etypeContainer >
bool string_array_base < Type, RawType, t_etypeContainer > ::move_ci(const RawType &str,::raw::index iIndex)

{
   ::raw::index i = find_first_ci(str);

   if(i < 0)
      return false;
   this->erase_at(i);
   insert_at(iIndex,str);

   return true;
}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
bool string_array_base < Type, RawType, t_etypeContainer > ::preferred(const RawType &str)

{
   return move_ci(str,0);

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::preferred(string_array_base < Type, RawType, t_etypeContainer >  & stra)
{
   ::raw::count count = 0;
   for(::raw::index i = stra.get_upper_bound(); i >= 0; i--)
   {
      if(preferred(stra[i]))
         count++;
   }
   return count;
}



template < typename Type, typename RawType, ::enum_type t_etypeContainer >
Type string_array_base < Type, RawType, t_etypeContainer > ::pop(::raw::index i)
{
i = get_upper_bound(i);
Type strRet = this->element_at(i);
this->erase_at(i);
return strRet;
}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::slice(string_array_base < Type, RawType, t_etypeContainer >  & stra,::raw::index iOffset,::raw::count count)
{

   ::raw::index iEnd;

   if(count < 0)
      iEnd = get_upper_bound(count);
   else
      iEnd = iOffset + count - 1;

   for(::raw::index i = iOffset; i <= iEnd; i++)
   {
      stra.add(this->element_at(i));
   }

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::erase(::raw::index iOffset,::raw::count count)
{

for(::raw::index i = iOffset + count - 1; i >= iOffset; i--)
{

this->erase_at(i);

}
}



template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::splice(const string_array_base < Type, RawType, t_etypeContainer >  & stra,::raw::index iOffset,::raw::count count)
{

   erase(iOffset, count);

   insert_at(iOffset,stra);

}



template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::splice(const string_array_base < Type, RawType, t_etypeContainer >  & stra,::raw::index iOffset,string_array_base < Type, RawType, t_etypeContainer >  & straRemoved,::raw::count count)
{

   slice(straRemoved, iOffset, count);

   erase(iOffset, count);

   insert_at(iOffset,stra);

}



template < typename Type, typename RawType, ::enum_type t_etypeContainer >
bool string_array_base < Type, RawType, t_etypeContainer > ::is_empty(::raw::count countMinimum) const
{

return this->get_size() < countMinimum;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
bool string_array_base < Type, RawType, t_etypeContainer > ::has_elements(::raw::count countMinimum) const
{


return this->get_count() >= countMinimum;
}


//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//::raw::count string_array_base < Type, RawType, t_etypeContainer > ::begins(string_array_base < Type, RawType, t_etypeContainer > & straPrefixed, const RawType &strPrefix, ::raw::index iFirst, ::raw::index iLast)
//{
//
//   ::raw::count count = 0;
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
//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//::raw::count string_array_base < Type, RawType, t_etypeContainer > ::case_insensitive_begins(string_array_base < Type, RawType, t_etypeContainer > & straPrefixed,const RawType &strPrefix,::raw::index iFirst,::raw::index iLast)
//{
//
//   ::raw::count count = 0;
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
template < primitive_array INDEX_ARRAY >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::begins(INDEX_ARRAY & iaPrefixed, const RawType &strPrefix, ::raw::index iFirst, ::raw::index iLast)
{

::raw::count count = 0;

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



template < typename Type, typename RawType, ::enum_type t_etypeContainer >
template < primitive_array INDEX_ARRAY >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::case_insensitive_begins(INDEX_ARRAY & iaPrefixed, const RawType &strPrefix, ::raw::index iFirst, ::raw::index iLast)
{

::raw::count count = 0;

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



//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//::raw::count string_array_base < Type, RawType, t_etypeContainer > ::ends(string_array_base < Type, RawType, t_etypeContainer >& straSuffixed, const RawType &strSuffix, ::raw::index iFirst, ::raw::index iLast)
//{
//
//   ::raw::count count = 0;
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
template < primitive_array STRING_ARRAY >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::case_insensitive_ends(STRING_ARRAY & straSuffixed, const RawType &strSuffix, ::raw::index iFirst, ::raw::index iLast)
{

::raw::count count = 0;

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




template < typename Type, typename RawType, ::enum_type t_etypeContainer >
template < primitive_array STRING_ARRAY >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::ends(STRING_ARRAY & iaSuffixed, const RawType &strSuffix, ::raw::index iFirst, ::raw::index iLast)
{

::raw::count count = 0;

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



//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//::raw::count string_array_base < Type, RawType, t_etypeContainer > ::case_insensitive_ends(index_array & iaSuffixed, const RawType &strSuffix, ::raw::index iFirst, ::raw::index iLast)
//{
//
//   ::raw::count count = 0;
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
//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//::raw::count string_array_base < Type, RawType, t_etypeContainer > ::search_ci(string_array_base < Type, RawType, t_etypeContainer > & stra, const RawType &str, ::raw::index iFirst, ::raw::index iLast)
//{
//
//   ::raw::count count = 0;
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
//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//::raw::count string_array_base < Type, RawType, t_etypeContainer > ::search(string_array_base < Type, RawType, t_etypeContainer > & stra, const RawType &str, ::raw::index iFirst, ::raw::index iLast)
//{
//
//   ::raw::count count = 0;
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

template < typename Type, typename RawType, ::enum_type t_etypeContainer >
template < primitive_array STRING_ARRAY >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::search(STRING_ARRAY & iaResult, const RawType &strTopic, ::raw::index iFirst, ::raw::index iLast)
{

::raw::count count = 0;

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



template < typename Type, typename RawType, ::enum_type t_etypeContainer >
template < primitive_array STRING_ARRAY >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::search_ci(STRING_ARRAY & ia, const RawType &strTopic, ::raw::index iFirst, ::raw::index iLast)
{

::raw::count count = 0;

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



template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::filter_begins(const RawType &str, ::raw::index iFirst, ::raw::index iLast)
{

   ::raw::count count = 0;

   if (this->prepare_first_last(iFirst, iLast))
   {

      ::raw::index i = iFirst;

      ::raw::index iFind;

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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::filter_begins_ci(const RawType &str,::raw::index iFirst,::raw::index iLast)
{

   ::raw::count count = 0;

   if (this->prepare_first_last(iFirst, iLast))
   {

      ::raw::index i = iFirst;

      ::raw::index iFind;

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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
template < typename Pred >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::filter(Pred pred, ::raw::index iFirst, ::raw::index iLast)
{

   ::raw::count count = 0;

   if (this->prepare_first_last(iFirst, iLast))
   {

      for(::raw::index i = iFirst; i <= iLast;)
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
template < typename Pred >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::filter_out(Pred pred,::raw::index iFirst,::raw::index iLast)
{

   ::raw::count count = 0;

   if (this->prepare_first_last(iFirst, iLast))
   {

      for(::raw::index i = iFirst; i <= iLast;)
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
template < typename Pred, typename ArrayOut >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::filter_out(Pred pred, ArrayOut & a, ::raw::index iFirst,::raw::index iLast)
{

   ::raw::count count = 0;

   if (this->prepare_first_last(iFirst, iLast))
   {

      for(::raw::index i = iFirst; i <= iLast;)
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::get_random_index() const
{

   if(this->is_empty())
   {

      return -1;

   }

   return (::raw::index)(rand() % get_size());

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
Type & string_array_base < Type, RawType, t_etypeContainer > ::random_element()
{

   if(this->is_empty())
   {

      throw_exception(error_wrong_state, "invalid call");

   }

   return this->element_at(get_random_index());

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
const Type & string_array_base < Type, RawType, t_etypeContainer > ::random_element() const
{

   if(this->is_empty())
   {

      throw_exception(error_wrong_state, "invalid call");

   }

   return this->element_at(get_random_index());

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
Type string_array_base < Type, RawType, t_etypeContainer > ::pop_random_element()
{

   if(this->is_empty())
   {

      throw_exception(error_wrong_state, "invalid call");

   }

   ::raw::index i = get_random_index();

   Type str = this->element_at(i);

   this->erase_at(i);

   return str;

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::make_lower()
{

   for(::raw::index i = 0; i < this->get_count(); i++)
   {

      this->element_at(i).make_lower();

   }

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::make_upper()
{

   for(::raw::index i = 0; i < this->get_count(); i++)
   {

      this->element_at(i).make_upper();

   }

}









template < typename Type, typename RawType, ::enum_type t_etypeContainer >
Type string_array_base < Type, RawType, t_etypeContainer > ::encode_v16()
{
   //Type strEncode;
   //for(::raw::index u = 0; u < this->get_count(); u++)
   //{
   //   Type & str = this->element_at(u);
   //   strEncode += hex::lower_from((const char*)str,str.length());
   //   strEncode += "00";
   //   /*      for(::raw::index uj = 0; uj < str.size(); uj++)
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




template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::decode_v16(const RawType &str)
{
   //::raw::index iSize = 1024;
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
   //   ::raw::index iConversion = ::ansi_to_i32(sz,&pszEnd,16);
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
   //         str = (char *)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(iSize);
   //      }
   //      else if(iSize < (ansi_length(str) + 1))
   //      {
   //         char * strOld = str;
   //         iSize += 1024;
   //         char * strNew = (char *)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(iSize);
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




template < typename Type, typename RawType, ::enum_type t_etypeContainer >
inline ::raw::count string_array_base < Type, RawType, t_etypeContainer >::count_except(const RawType &str)
{

   ::raw::count c = get_count();

   for (::raw::index i = 0; i < get_count(); i++)
   {

      if (this->element_at(i) == str)
      {

         c--;

      }

   }

   return c;

}

template < typename Type, typename RawType, ::enum_type t_etypeContainer >
inline ::raw::count string_array_base < Type, RawType, t_etypeContainer > ::count_except_ci(const RawType &str)
{

   ::raw::count c = get_count();

   for (::raw::index i = 0; i < get_count(); i++)
   {

      if (this->element_at(i).case_insensitive_order(str) == 0)
      {

         c--;

      }

   }

   return c;

}



template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::count_except(const string_array_base < Type, RawType, t_etypeContainer >  & stra)
{

   ::raw::count c = get_count();

   for(::raw::index i = 0; i < get_count(); i++)
   {

      if (stra.contains(element_at(i)))
      {

         c--;

      }

   }

   return c;

}




template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::count string_array_base < Type, RawType, t_etypeContainer > ::count_except_ci(const string_array_base < Type, RawType, t_etypeContainer >  & stra)
{

   ::raw::count c = get_count();

   for(::raw::index i = 0; i < get_count(); i++)
   {

      if (stra.case_insensitive_contains(element_at(i)))
      {

         c--;

      }

   }

   return c;

}



template < typename Type, typename RawType, ::enum_type t_etypeContainer >
Type & string_array_base < Type, RawType, t_etypeContainer > ::get_network_payload(Type & str, bool bNewLine) const
{

   str += "[";

   if(get_count() > 0)
   {

      str += "\"";

      str += element_at(0);

      str += "\"";

   }

   for(::raw::index i = 1; i < get_count(); i++)
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





template < typename Type, typename RawType, ::enum_type t_etypeContainer >
Type string_array_base < Type, RawType, t_etypeContainer > ::_008Implode(const RawType &strSeparator, const RawType &strLastSeparator, ::raw::index iStart, ::raw::count inCountLastOut) const
{

   Type str;

   if(!this->prepare_first_in_count_last_out(iStart, inCountLastOut))
   {

      return str;

   }

   for (::raw::index i = iStart; i <= inCountLastOut; i++)
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



template < typename Type, typename RawType, ::enum_type t_etypeContainer >
Type string_array_base < Type, RawType, t_etypeContainer > ::_008IfImplode(const RawType &strIfHasElementPrefix, const RawType &strSeparator, const RawType &strLastSeparator, bool bUseLast, ::raw::index iStart, ::raw::count inCountLastOut) const
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

   for (::raw::index i = iStart; i <= inCountLastOut; i++)
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


//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//Type string_array_base < Type, RawType, t_etypeContainer > ::_008IfImplode(const RawType &strIfHasElementPrefix, const RawType &strSeparator, const RawType &strLastSeparator, bool bUseLast, ::raw::index iStart, ::raw::index iEnd) const
//{
//
//   Type str;
//
//   _008IfImplode(str, strIfHasElementPrefix, strSeparator, strLastSeparator, bUseLast, iStart, iEnd);
//
//   return str;
//
//}




template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::array < const ::ansi_character * > string_array_base < Type, RawType, t_etypeContainer > ::c_ansi_get(bool bMemoryAlloc) const
{

   ::array < const ::ansi_character * > psza;

   for(::raw::index i = 0; i < get_size(); i++)
   {

      char * psz = nullptr;

      if(bMemoryAlloc)
      {

         psz = ansi_duplicate(element_at(i));

      }
      else
      {

         psz = libc_strdup(element_at(i));

      }

      psza.add(psz);

   }

   return psza;

}


//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//::array < const ::wide_character * > string_array_base < Type, RawType, t_etypeContainer > ::c_wide_get(bool bMemoryAlloc) const
//{
//
//   ::array < const ::wide_character * > psza;
//
//   for (::raw::index i = 0; i < get_size(); i++)
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


/// expect strings allocated with malloc (sic, not ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate) or strdup and array allocated with malloc (sic, not ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate)
template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::c_add(char ** ppsz, ::raw::count c, bool bMemoryAlloc)
{

   for (::raw::index i = 0; i < c; i++)
   {

      auto psz = ppsz[i];

      auto str = Type(psz);

      this->add(str);

      if(bMemoryAlloc)
      {

         ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(psz);

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

         ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(ppsz);

      }
      else
      {

         free(ppsz);

      }

   }

}




/// expect strings allocated with malloc (sic, not ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate) or strdup and array allocated with malloc (sic, not ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate)
template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::c_add(char ** ppszParam, bool bMemoryAlloc)
{

   auto ppsz = ppszParam;

   while(ppsz != nullptr)
   {

      auto psz = *ppsz;

      auto str = Type(psz);

      this->add(str);

      if(bMemoryAlloc)
      {

         ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_array)->free(psz);

      }
      else
      {

         free(psz);

      }
      ppsz++;

   }

   if(bMemoryAlloc)
   {

      ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(ppszParam);

   }
   else
   {

      free(ppszParam);

   }

}

/// expect strings allocated with malloc (sic, not ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate) or wcsdup and array allocated with malloc (sic, not ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate)
template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::c_add(wchar_t ** ppwsz, ::raw::count c, bool bMemoryAlloc)
{

   for (::raw::index i = 0; i < c; i++)
   {

      auto pwsz = ppwsz[i];

      auto str = Type(pwsz);

      this->add(str);

      if(bMemoryAlloc)
      {

         ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(pwsz);

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

         ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(ppwsz);

      }
      else
      {

         free(ppwsz);

      }
   }

}


/// expect strings allocated with malloc (sic, not ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate) or wcsdup and array allocated with malloc (sic, not ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate)
template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::c_add(wchar_t ** ppwszParam, bool bMemoryAlloc)
{

   auto ppwsz = ppwszParam;

   while (ppwsz != nullptr)
   {

      auto pwsz = *ppwsz;

      Type str(pwsz);

      this->add(str);

      if(bMemoryAlloc)
      {

         ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(pwsz);

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

         ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(ppwsz);

      }
      else
      {

         free(ppwsz);

      }
   }

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::order()
{

   this->predicate_sort([](Type & a, Type & b)
                        {

                            return a.order(b) < 0;

                        });

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::case_insensitive_order()
{

   this->predicate_sort([](Type & a, Type & b)
                        {
                            return a.case_insensitive_order(b) < 0;
                        });

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::collate_order()
{

   this->predicate_sort([](Type & a, Type & b)
                        {
                            return a.collate(b) < 0;
                        });

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer > ::collate_sort_ci()
{

   this->predicate_sort([](Type & a, Type & b)
                        {
                            return a.case_insensitive_collate(b) < 0;
                        });

}













template < typename Type, typename RawType, ::enum_type t_etypeContainer >
Type string_array_base < Type, RawType, t_etypeContainer >::safe_at(::raw::index nIndex, Type tDefault) const
{

if (nIndex < 0 || nIndex >= this->get_size())
{

return tDefault;

}

return this->element_at(nIndex);

}

template < typename Type, typename RawType, ::enum_type t_etypeContainer >
Type string_array_base < Type, RawType, t_etypeContainer >::safe_at(::raw::index nIndex, Type tDefault)
{
if (nIndex < 0 || nIndex >= this->get_size())
return tDefault;

return this->element_at(nIndex);

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
Type string_array_base < Type, RawType, t_etypeContainer >::get_at(::raw::index nIndex) const
{
if (nIndex < 0 || nIndex >= this->size())
throw_exception(error_index_out_of_bounds);
return get_data()[nIndex];
}

//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//void string_array_base < Type, RawType, t_etypeContainer >::set_at(::raw::index nIndex, const char * newElement)
//{
//   if (nIndex < 0 || nIndex >= this->size())
//      throw_exception(error_index_out_of_bounds);
//   get_data()[nIndex] = newElement;
//}
//

template < typename Type, typename RawType, ::enum_type t_etypeContainer >
void string_array_base < Type, RawType, t_etypeContainer >::set_at(::raw::index nIndex, const Type & newElement)
{
if (nIndex < 0 || nIndex >= this->size())
throw_exception(error_index_out_of_bounds);
get_data()[nIndex] = newElement;
}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
Type & string_array_base < Type, RawType, t_etypeContainer >::element_at(::raw::index nIndex)
{
if (nIndex < 0 || nIndex >= this->size())
throw_exception(error_index_out_of_bounds);
return get_data()[nIndex];
}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
const Type & string_array_base < Type, RawType, t_etypeContainer >::element_at(::raw::index nIndex) const
{
if (nIndex < 0 || nIndex >= this->size())
throw_exception(error_index_out_of_bounds);
return get_data()[nIndex];
}



//
//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//::raw::index string_array_base < Type, RawType, t_etypeContainer >::add(const property & prop)
//{
//
//   return add(prop.get_value());
//
//}

////#include "acme/primitive/primitive/payload.h"

//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//string_array_base < Type, RawType, t_etypeContainer >  & string_array_base < Type, RawType, t_etypeContainer > ::operator = (const ::payload & payload)
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


//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//memory string_array_base < Type, RawType, t_etypeContainer > ::GetFormatV004()
//{
//
//   strsize iTotalLength = 0;
//
//   ::raw::index i;
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
//      lpszN = (char *)((::u8 *)lpszN) + iLength + sizeof(char);
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


//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//template < typename TYPE >
//inline ::raw::index string_array_base < Type, RawType, t_etypeContainer > ::add(const TYPE & type)
//{
//
//    return ::acme::array::add(*this, type);
//
//}

//
//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//template < primitive_array INDEX_ARRAY >
//void string_array_base < Type, RawType, t_etypeContainer >::get_quick_sort_ci(INDEX_ARRAY & ia)
//{
//
//   INDEX_ARRAY stackLowerBound;
//   INDEX_ARRAY stackUpperBound;
//   ::raw::index iLowerBound;
//   ::raw::index iUpperBound;
//   ::raw::index iLPos,iUPos,iMPos;
//   Type t;
//   ia.erase_all();
//   ::acme::array::append_sequence(ia,(::raw::index)0,(::raw::index)get_upper_bound());
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
//                  ::raw::index i = ia[iMPos];
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
//                  ::raw::index i = ia[iLPos];
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
inline void debug_output(::particle * pparticle, string_array_base < Type, RawType, t_etypeContainer > & stra, ::raw::index iStart, ::raw::count inCountLastOut)
{

   pparticle->informationf(stra.implode(STR_NEWLINE, iStart, inCountLastOut));

}


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::suffix_find_first_ci(const RawType &strTopic, ::raw::index iFind, ::raw::index iLast) const
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::suffix_find_first(const RawType &strTopic, ::raw::index iFind, ::raw::index iLast) const
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::_find_first_suffixed(const RawType &strSuffix, ::raw::index iFind, ::raw::index iLast) const
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


template < typename Type, typename RawType, ::enum_type t_etypeContainer >
::raw::index string_array_base < Type, RawType, t_etypeContainer > ::_find_first_suffixed_ci(const RawType &strSuffix, ::raw::index iFind, ::raw::index iLast) const
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



