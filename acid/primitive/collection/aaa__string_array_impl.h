#pragma once


//#include "acid/primitive/primitive/property_set.h"
//#include "acid/primitive/primitive/memory.h"
//
//
//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//Type string_array_base < Type, RawType, t_etypeContainer >::safe_at(::collection::index nIndex, Type tDefault) const
//{
//
//   if (nIndex < 0 || nIndex >= this->get_size())
//   {
//
//      return tDefault;
//
//   }
//
//   return this->element_at(nIndex);
//
//}
//
//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//Type string_array_base < Type, RawType, t_etypeContainer >::safe_at(::collection::index nIndex, Type tDefault)
//{
//   if (nIndex < 0 || nIndex >= this->get_size())
//      return tDefault;
//
//   return this->element_at(nIndex);
//
//}
//
//
//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//Type string_array_base < Type, RawType, t_etypeContainer >::get_at(::collection::index nIndex) const
//{
//   if (nIndex < 0 || nIndex >= this->m_nSize)
//      throw ::exception(error_index_out_of_bounds);
//   return get_data()[nIndex];
//}
//
////template < typename Type, typename RawType, ::enum_type t_etypeContainer >
////void string_array_base < Type, RawType, t_etypeContainer >::set_at(::collection::index nIndex, const char * newElement)
////{
////   if (nIndex < 0 || nIndex >= this->m_nSize)
////      throw ::exception(error_index_out_of_bounds);
////   get_data()[nIndex] = newElement;
////}
////
//
//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//void string_array_base < Type, RawType, t_etypeContainer >::set_at(::collection::index nIndex, const Type & newElement)
//{
//   if (nIndex < 0 || nIndex >= this->m_nSize)
//      throw ::exception(error_index_out_of_bounds);
//   get_data()[nIndex] = newElement;
//}
//
//
//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//Type & string_array_base < Type, RawType, t_etypeContainer >::element_at(::collection::index nIndex)
//{
//   if (nIndex < 0 || nIndex >= this->m_nSize)
//      throw ::exception(error_index_out_of_bounds);
//   return get_data()[nIndex];
//}
//
//
//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//const Type & string_array_base < Type, RawType, t_etypeContainer >::element_at(::collection::index nIndex) const
//{
//   if (nIndex < 0 || nIndex >= this->m_nSize)
//      throw ::exception(error_index_out_of_bounds);
//   return get_data()[nIndex];
//}
//
//
//
////
////template < typename Type, typename RawType, ::enum_type t_etypeContainer >
////::collection::index string_array_base < Type, RawType, t_etypeContainer >::add(const property & prop)
////{
////
////   return add(prop.get_value());
////
////}
//
//
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
//
//
////template < typename Type, typename RawType, ::enum_type t_etypeContainer >
////memory string_array_base < Type, RawType, t_etypeContainer > ::GetFormatV004()
////{
////
////   strsize iTotalLength = 0;
////
////   ::collection::index i;
////
////   for (i = 0; i < this->m_nSize; i++)
////   {
////      iTotalLength += this->element_at(i).get_length();
////      iTotalLength++;
////   }
////
////   if (iTotalLength == 0)
////   {
////      iTotalLength = 2;
////   }
////   else
////   {
////      iTotalLength++;
////   }
////
////   memory mem;
////
////   mem.set_size(iTotalLength * sizeof(char));
////
////   char * lpsz = (char *)mem.get_data();
////
////   memory_set(lpsz, 0x00, iTotalLength * sizeof(char));
////
////   char * lpszN = lpsz;
////
////   strsize iLength;
////
////   for (i = 0; i < this->m_nSize; i++)
////   {
////
////      Type * pstr = &this->element_at(i);
////
////      iLength = pstr->get_length();
////
////#ifdef WINDOWS
////      strcat_s(lpszN, (size_t) iLength, *pstr);
////#else
////      ansi_concatenate(lpszN, *pstr);
////#endif
////
////#ifdef WINDOWS_DESKTOP
////      iLength = strlen(lpszN);
////#elif defined(_UWPDOW)
////      iLength = wcsnbcnt(lpszN, iLength);
////#else
////      iLength = strlen(lpszN);
////#endif
////
////      lpszN = (char *)((::u8 *)lpszN) + iLength + sizeof(char);
////
////   }
////
////   if (iTotalLength == 2)
////   {
////      memory_set(lpsz, 0x00, iTotalLength * sizeof(char));
////   }
////   else
////   {
////      memory_set(lpszN, 0x00, sizeof(char));
////   }
////
////   return mem;
////
////}
//
//
////template < typename Type, typename RawType, ::enum_type t_etypeContainer >
////template < typename TYPE >
////inline ::collection::index string_array_base < Type, RawType, t_etypeContainer > ::add(const TYPE & type)
////{
////
////    return ::papaya::array::add(*this, type);
////
////}
//
//
//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//void string_array_base < Type, RawType, t_etypeContainer >::get_quick_sort_ci(index_array & ia)
//{
//   index_array stackLowerBound;
//   index_array stackUpperBound;
//   ::collection::index iLowerBound;
//   ::collection::index iUpperBound;
//   ::collection::index iLPos,iUPos,iMPos;
//   Type t;
//   ia.erase_all();
//   ::papaya::array::append_sequence(ia,(::collection::index)0,(::collection::index)get_upper_bound());
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
//                  ::collection::index i = ia[iMPos];
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
//                  ::collection::index i = ia[iLPos];
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
//
//
//
//
//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//inline void string_array_base < Type, RawType, t_etypeContainer > ::debug_output(::collection::index iStart, ::collection::count inCountLastOut)
//{
//
//   ::information(implode(STR_NEWLINE, iStart, inCountLastOut));
//
//}
//
//
//
//
//
//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//::collection::index string_array_base < Type, RawType, t_etypeContainer > ::suffix_find_first_ci(const Type& pcszTopic, ::collection::index iFind, ::collection::index iLast) const
//{
//
//   if (this->prepare_first_last(iFind, iLast))
//   {
//
//      for (; iFind <= iLast; iFind++)
//      {
//
//         if (string_ends_ci(pcszTopic, this->element_at(iFind)))
//         {
//
//            return iFind;
//
//         }
//
//      }
//
//   }
//
//   return -1;
//
//}
//
//
//
//
//
//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//::collection::index string_array_base < Type, RawType, t_etypeContainer > ::suffix_find_first(const Type& pcszTopic, ::collection::index iFind, ::collection::index iLast) const
//{
//
//   if (this->prepare_first_last(iFind, iLast))
//   {
//
//      for (; iFind <= iLast; iFind++)
//      {
//
//         if (string_ends(pcszTopic, this->element_at(iFind)))
//         {
//
//            return iFind;
//
//         }
//
//      }
//
//   }
//
//   return -1;
//
//}
//
//
//
//
//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//::collection::index string_array_base < Type, RawType, t_etypeContainer > ::_find_first_suffixed(const Type & strSuffix, ::collection::index iFind, ::collection::index iLast) const
//{
//
//   for (; iFind < iLast; iFind++)
//   {
//
//      if (string_ends(this->element_at(iFind), strSuffix))
//      {
//
//         return iFind;
//
//      }
//
//   }
//
//   return -1;
//
//}
//
//
//template < typename Type, typename RawType, ::enum_type t_etypeContainer >
//::collection::index string_array_base < Type, RawType, t_etypeContainer > ::_find_first_suffixed_ci(const Type & strSuffix, ::collection::index iFind, ::collection::index iLast) const
//{
//
//   for (; iFind < iLast; iFind++)
//   {
//
//      if (string_ends_ci(this->element_at(iFind), strSuffix))
//      {
//
//         return iFind;
//
//      }
//
//   }
//
//   return -1;
//
//}
//
