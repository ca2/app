#pragma once



//template < class KEY, class ARG_KEY, class PAYLOAD, class ARG_VALUE, class COMPARE >
//index fifo_map < KEY, ARG_KEY, PAYLOAD, ARG_VALUE, COMPARE >::add_key(ARG_KEY key)
//{
//
//   index i;
//
//   if(!find_key(key, i))
//   {
//
//      m_ptra.add(aaa_primitive_new pair(this, key));
//
//      i = m_ptra.get_upper_bound();
//
//   }
//
//   return i;
//
//}
//
//
//
//template < class KEY, class ARG_KEY, class PAYLOAD, class ARG_VALUE, class COMPARE >
//index fifo_map < KEY, ARG_KEY, PAYLOAD, ARG_VALUE, COMPARE >::add_pair(ARG_KEY key, ARG_VALUE newValue)
//{
//
//   index i;
//
//   if(!find_key(key, i))
//   {
//
//      m_ptra.add(aaa_primitive_new pair(key));
//
//      i = m_ptra.get_upper_bound();
//
//   }
//
//   m_ptra[i]->element2() = newValue;
//
//   return i;
//
//}
//
//
//template < class type_map >
//fifo_attrib_map < type_map > & fifo_attrib_map < type_map >::operator = (const fifo_attrib_map & attribmap)
//{
//
//   if(this != &attribmap)
//   {
//
//      this->erase_all();
//
//      typename type_map::pair * ppair;
//
//      for(::collection::index i = 0; i < attribmap.m_ptra.get_count(); i++)
//      {
//
//         ppair      = aaa_primitive_new typename type_map::pair(this, attribmap.m_ptra[i]->element1());
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
