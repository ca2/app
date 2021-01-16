#pragma once


#include "acme/primitive/collection/var_array.h"
#include "acme/primitive/primitive/property_set.h"
#include "acme/primitive/primitive/memory.h"


template < typename Type, typename RawType >
Type string_array_base < Type, RawType >::safe_at(::index nIndex, Type tDefault) const
{

   if (nIndex < 0 || nIndex >= this->get_size())
   {

      return tDefault;

   }

   return this->element_at(nIndex);

}

template < typename Type, typename RawType >
Type string_array_base < Type, RawType >::safe_at(::index nIndex, Type tDefault)
{
   if (nIndex < 0 || nIndex >= this->get_size())
      return tDefault;

   return this->element_at(nIndex);

}


template < typename Type, typename RawType >
Type string_array_base < Type, RawType >::get_at(::index nIndex) const
{
   if (nIndex < 0 || nIndex >= this->m_nSize)
      __throw(index_out_of_bounds());
   return get_data()[nIndex];
}

//template < typename Type, typename RawType >
//void string_array_base < Type, RawType >::set_at(::index nIndex, const char * newElement)
//{
//   if (nIndex < 0 || nIndex >= this->m_nSize)
//      __throw(index_out_of_bounds());
//   get_data()[nIndex] = newElement;
//}
//

template < typename Type, typename RawType >
void string_array_base < Type, RawType >::set_at(::index nIndex, const Type & newElement)
{
   if (nIndex < 0 || nIndex >= this->m_nSize)
      __throw(index_out_of_bounds());
   get_data()[nIndex] = newElement;
}


template < typename Type, typename RawType >
Type & string_array_base < Type, RawType >::element_at(::index nIndex)
{
   if (nIndex < 0 || nIndex >= this->m_nSize)
      __throw(index_out_of_bounds());
   return get_data()[nIndex];
}


template < typename Type, typename RawType >
const Type & string_array_base < Type, RawType >::element_at(::index nIndex) const
{
   if (nIndex < 0 || nIndex >= this->m_nSize)
      __throw(index_out_of_bounds());
   return get_data()[nIndex];
}



//
//template < typename Type, typename RawType >
//::index string_array_base < Type, RawType >::add(const property & prop)
//{
//
//   return add(prop.get_value());
//
//}


template < class Type, class RawType >
string_array_base < Type, RawType >  & string_array_base < Type, RawType > ::operator = (payload varSrc)
{
   this->remove_all();
   if (varSrc.get_type() == ::e_type_stra)
   {
      varSrc.get_array(*this);
   }
   else
   {
      if (varSrc.get_count() == 1)
      {
         add((Type)varSrc.get_string());
      }
      else if (varSrc.get_count() > 1)
      {
         varSrc.get_array(*this);
      }
   }
   return *this;
}





template < typename Type, typename RawType >
memory string_array_base < Type, RawType > ::GetFormatV004()
{

   strsize iTotalLength = 0;

   ::index i;

   for (i = 0; i < this->m_nSize; i++)
   {
      iTotalLength += this->element_at(i).get_length();
      iTotalLength++;
   }

   if (iTotalLength == 0)
   {
      iTotalLength = 2;
   }
   else
   {
      iTotalLength++;
   }

   memory mem;

   mem.set_size(iTotalLength * sizeof(char));

   char * lpsz = (char *)mem.get_data();

   __memset(lpsz, 0x00, iTotalLength * sizeof(char));

   char * lpszN = lpsz;

   strsize iLength;

   for (i = 0; i < this->m_nSize; i++)
   {

      Type * pstr = &this->element_at(i);

      iLength = pstr->get_length();

#ifdef WINDOWS
      strcat_s(lpszN, (size_t) iLength, *pstr);
#else
      ansi_concatenate(lpszN, *pstr);
#endif

#ifdef WINDOWS_DESKTOP
      iLength = strlen(lpszN);
#elif defined(_UWPDOW)
      iLength = wcsnbcnt(lpszN, iLength);
#else
      iLength = strlen(lpszN);
#endif

      lpszN = (char *)((byte *)lpszN) + iLength + sizeof(char);

   }

   if (iTotalLength == 2)
   {
      __memset(lpsz, 0x00, iTotalLength * sizeof(char));
   }
   else
   {
      __memset(lpszN, 0x00, sizeof(char));
   }

   return mem;

}


//template < typename Type, typename RawType >
//template < typename TYPE >
//inline ::index string_array_base < Type, RawType > ::add(const TYPE & type)
//{
//
//    return ::papaya::array::add(*this, type);
//
//}


template < typename Type, typename RawType >
void string_array_base < Type, RawType >::get_quick_sort_ci(index_array & ia)
{
   index_array stackLowerBound;
   index_array stackUpperBound;
   ::index iLowerBound;
   ::index iUpperBound;
   ::index iLPos,iUPos,iMPos;
   Type t;
   ia.remove_all();
   ::papaya::array::append_sequence(ia,(::index)0,(::index)get_upper_bound());
   if(this->get_size() >= 2)
   {
      stackLowerBound.push(0);
      stackUpperBound.push(this->get_size() - 1);
      while(true)
      {
         iLowerBound = stackLowerBound.pop();
         iUpperBound = stackUpperBound.pop();
         iLPos = iLowerBound;
         iMPos = iLowerBound;
         iUPos = iUpperBound;
         while(true)
         {
            while(true)
            {
               if(iMPos == iUPos)
                  break;
               if(this->element_at(ia[iMPos]).compare_ci(this->element_at(ia[iUPos])) <= 0)
                  iUPos--;
               else
               {
                  ::index i = ia[iMPos];
                  ia[iMPos] = ia[iUPos];
                  ia[iUPos] = i;
                  break;
               }
            }
            if(iMPos == iUPos)
               break;
            iMPos = iUPos;
            while(true)
            {
               if(iMPos == iLPos)
                  break;

               if(this->element_at(ia[iLPos]).compare_ci(this->element_at(ia[iMPos])) <= 0)
                  iLPos++;
               else
               {
                  ::index i = ia[iLPos];
                  ia[iLPos] = ia[iMPos];
                  ia[iMPos] = i;
                  break;
               }
            }
            if(iMPos == iLPos)
               break;
            iMPos = iLPos;
         }
         if(iLowerBound < iMPos - 1)
         {
            stackLowerBound.push(iLowerBound);
            stackUpperBound.push(iMPos - 1);
         }
         if(iMPos + 1 < iUpperBound)
         {
            stackLowerBound.push(iMPos + 1);
            stackUpperBound.push(iUpperBound);
         }
         if(stackLowerBound.get_size() == 0)
            break;
      }
   }

}





template < class Type, class RawType >
inline void string_array_base < Type, RawType > ::debug_output(::index iStart, ::count inCountLastOut)
{

   ::output_debug_string(implode(STR_NEWLINE, iStart, inCountLastOut));

}



