#pragma once


//
//template < class KEY, class ARG_KEY, class PAYLOAD, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//void sort_map < KEY,ARG_KEY,PAYLOAD,ARG_VALUE,COMPARE, m_bMultiKey >::add_pair(ARG_KEY key,ARG_VALUE newValue)
//{
//
//   if(m_pnode == nullptr)
//   {
//      m_pnode = memory_new node(key,newValue);
//      return;
//   }
//
//   node * pnode = m_pnode;
//
//   while(true)
//   {
//      if(compare(key,pnode->element1()))
//      {
//
//         if(pnode->left == nullptr)
//         {
//
//            pnode->left = memory_new node(key,newValue);
//
//            return;
//
//         }
//         else
//         {
//
//            pnode = pnode->left;
//
//         }
//
//      }
//      else if(m_bMultiKey || compare(pnode->element1(), key))
//      {
//
//         if(pnode->right == nullptr)
//         {
//
//            pnode->right = memory_new node(key, newValue);
//
//            return;
//
//         }
//         else
//         {
//
//            pnode = pnode->right;
//
//         }
//
//      }
//      else
//      {
//
//         pnode->element2() = newValue;
//
//         return;
//
//      }
//
//   }
//
//
//}
//
//
//template < class KEY,class ARG_KEY,class PAYLOAD,class ARG_VALUE,class COMPARE, bool m_bMultiKey >
//void sort_map < KEY,ARG_KEY,PAYLOAD,ARG_VALUE,COMPARE, m_bMultiKey >::insert(const pair < KEY,PAYLOAD > & pair)
//{
//
//   add_pair(pair.element1(),pair.element2());
//
//}
//
//
//template < class type_map >
//sort_attrib_map < type_map > & sort_attrib_map < type_map >::operator = (const sort_attrib_map & attribmap)
//{
//
//   if(this != &attribmap)
//   {
//
//      this->erase_all();
//
//      typename type_map::pair * ppair;
//
//      for(index i = 0; i < attribmap.m_ptra.get_count(); i++)
//      {
//
//         ppair      = memory_new typename type_map::pair(attribmap.m_ptra[i]->element1());
//
//         ppair->element2()    = attribmap.m_ptra[i]->element2();
//
//         this->m_ptra.add(ppair);
//
//      }
//
//   }
//
//   return *this;
//
//}
