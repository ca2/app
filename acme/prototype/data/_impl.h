#pragma once


//inline stream & operator <<(stream & s, const ::data::tree & tree)
//{
//
//   auto ptreeitem = tree.get_base_item();
//
//   index iLevel = 0;
//
//   while (true)
//   {
//
//      ptreeitem = ptreeitem->get_child_next_or_parent();
//
//      if (!ptreeitem)
//      {
//
//         break;
//
//      }
//
//      iLevel = ptreeitem->m_iLevel;
//
//      s << (int)iLevel;
//
//      __save_object(s, ptreeitem->m_pdataitem);
//
//   }
//
//   s << (int)-1;
//
//   return s;
//
//}
//
//
//
//inline stream & operator >>(stream & s, ::data::tree & tree)
//{
//
//   auto ptreeitem = tree.get_base_item();
//
//   int iPreviousLevel = 0;
//
//   int iLevel = 0;
//
//   while (true)
//   {
//
//      iPreviousLevel = iLevel;
//
//      s >> iLevel;
//
//      //if (s.fail())
//      //{
//
//      //   break;
//
//      //}
//
//      if (iLevel < 0)
//      {
//
//         break;
//
//      }
//
//      auto pitem = __load_object< ::item>(s);
//
//      if (iLevel == iPreviousLevel)
//      {
//
//         ptreeitem = tree.insert_item(pitem, ::data::e_relative_last_sibling, ptreeitem);
//
//      }
//      else if (iLevel > iPreviousLevel)
//      {
//
//         ptreeitem = tree.insert_item(pitem, ::data::e_relative_first_child, ptreeitem);
//
//      }
//      else
//      {
//
//         while (iLevel < iPreviousLevel)
//         {
//
//            ptreeitem = ptreeitem->get_parent();
//
//            iPreviousLevel--;
//
//         }
//
//         ptreeitem = tree.insert_item(pitem, ::data::e_relative_last_sibling, ptreeitem);
//
//      }
//
//   }
//
//   return s;
//
//}
//
//
//
