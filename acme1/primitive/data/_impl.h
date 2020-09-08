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
//      s << (i32)iLevel;
//
//      __save_object(s, ptreeitem->m_pdataitem);
//
//   }
//
//   s << (i32)-1;
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
//   i32 iPreviousLevel = 0;
//
//   i32 iLevel = 0;
//
//   while (true)
//   {
//
//      iPreviousLevel = iLevel;
//
//      s >> iLevel;
//
//      if (s.fail())
//      {
//
//         break;
//
//      }
//
//      if (iLevel < 0)
//      {
//
//         break;
//
//      }
//
//      auto pitem = __load_object< ::data::item>(s);
//
//      if (iLevel == iPreviousLevel)
//      {
//
//         ptreeitem = tree.insert_item(pitem, ::data::RelativeLastSibling, ptreeitem);
//
//      }
//      else if (iLevel > iPreviousLevel)
//      {
//
//         ptreeitem = tree.insert_item(pitem, ::data::RelativeFirstChild, ptreeitem);
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
//         ptreeitem = tree.insert_item(pitem, ::data::RelativeLastSibling, ptreeitem);
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
