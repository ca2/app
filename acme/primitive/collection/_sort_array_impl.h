#pragma once


//template < class TYPE, class ARG_TYPE, class BASE_ARRAY >
//index_array & sort_array < TYPE, ARG_TYPE, BASE_ARRAY >::
//defer_update(const ::id & id)
//{
//
//   __pointer(sort_index) & sortindex = m_indexmap[fCompare];
//
//   if(sortindex.is_null())
//      sortindex = __new(sort_index);
//
//   if(!sortindex->m_bUpdated)
//   {
//      ::papaya::array::ensure_sequence(sortindex->m_indexa,(index) 0,(index)this->get_upper_bound());
//      ::sort::array::quick_sort((BASE_ARRAY &) *this, fCompare, sortindex->m_indexa);
//      sortindex->m_bUpdated = true;
//   }
//
//   return sortindex->m_indexa;
//
//}


//
//template < typename ARG_TYPE >
//bool default_less < ARG_TYPE > ::less(ARG_TYPE a1, ARG_TYPE a2)
//{
//
//    return a1 < a2;
//
//}
//
//
//template < typename ARG_TYPE >
//template < typename ARRAY >
//void sort_data < ARG_TYPE > ::sort(ARRAY * parray)
//{
//
//  if (m_bSorted)
//  {
//
//     return;
//
//  }
//
//  auto & pia = m_pindexa;
//
//  if (!pia)
//  {
//
//     pia = __new(index_array);
//
//  }
//
//  ::papaya::array::ensure_sequence(*pia, (index)0, (index)parray->get_upper_bound());
//
//  ::sort::array::quick_sort(*parray, m_pless, *pia);
//
//  m_bSorted = true;
//
//}
//
//
//template < typename ARG_TYPE >
//inline void sort_map < ARG_TYPE > ::mark_dirty()
//{
//
//    for (auto & psort : this->values())
//    {
//
//        psort->mark_dirty();
//
//    }
//
//}
//
//
//template < class TYPE, class ARG_TYPE, class BASE_ARRAY >
//void sort_array < TYPE, ARG_TYPE, BASE_ARRAY >::copy(const BASE_ARRAY & src)
//{
//
//   ::papaya::array::copy(*m_parray, src);
//
//   m_map.mark_dirty();
//
//}
//
//
//namespace sort
//{
//
//
//   template < class iterator, class COMPARE >
//   void quick_sort(const iterator& a, const iterator& b)
//   {
//      typename iterator::BASE_TYPE t;
//      raw_array < iterator > stackLowerBound;
//      raw_array < iterator > stackUpperBound;
//      iterator iLowerBound;
//      iterator iUpperBound;
//      iterator iLPos, iUPos, iMPos;
//      //   u32 t;
//
//      if (a.get_count() >= 2)
//      {
//         stackLowerBound.push(a);
//         stackUpperBound.push(b);
//         while (true)
//         {
//            iLowerBound = stackLowerBound.pop();
//            iUpperBound = stackUpperBound.pop();
//            iLPos = iLowerBound;
//            iMPos = iLowerBound;
//            iUPos = iUpperBound;
//            while (true)
//            {
//               while (true)
//               {
//                  if (iMPos == iUPos)
//                     break;
//                  if (COMPARE().operator()(*iMPos, *iUPos))
//                     --iUPos;
//                  else
//                  {
//                     t = *iMPos;
//                     *iMPos = *iUPos;
//                     *iUPos = t;
//                     break;
//                  }
//               }
//               if (iMPos == iUPos)
//                  break;
//               iMPos = iUPos;
//               while (true)
//               {
//                  if (iMPos == iLPos)
//                     break;
//                  if (COMPARE().operator()(*iLPos, *iMPos))
//                     ++iLPos;
//                  else
//                  {
//                     t = *iMPos;
//                     *iMPos = *iLPos;
//                     *iLPos = t;
//                     break;
//                  }
//               }
//               if (iMPos == iLPos)
//                  break;
//               iMPos = iLPos;
//            }
//            if (iLowerBound < iMPos - 1)
//            {
//               stackLowerBound.push(iLowerBound);
//               stackUpperBound.push(iMPos - 1);
//            }
//            if (iMPos + 1 < iUpperBound)
//            {
//               stackLowerBound.push(iMPos + 1);
//               stackUpperBound.push(iUpperBound);
//            }
//            if (stackLowerBound.get_size() == 0)
//               break;
//         }
//      }
//
//   };
//
//
//} // namespace sort
