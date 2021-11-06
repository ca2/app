#include "framework.h"


//string_list::string_list()
//{
//
//}
//
//
//string_list::~string_list()
//{
//
//}
//
//
//typename string_list::node * string_list::find(const string & searchValue, node * startAfter) const
//{
//
//   ASSERT_VALID(this);
//
//   node* p = (node*) startAfter;
//
//   if (p == nullptr)
//   {
//      
//      p = m_phead;  // start at head
//
//   }
//   else
//   {
//      
//      ASSERT(__is_valid_address(p, sizeof(node)));
//
//      p = p->m_pnext;  // start after the one specified
//
//   }
//
//   for (; p != nullptr; p = p->m_pnext)
//   {
//
//      if (p->m_value == searchValue)
//         return (POSITION)p;
//
//   }
//
//   return nullptr;
//
//}
//
//
//
//void string_list::assert_valid() const
//{
//   matter::assert_valid();
//
//   if (m_count == 0)
//   {
//      // is_empty list
//      ASSERT(m_phead == nullptr);
//      ASSERT(m_pointail == nullptr);
//   }
//   else
//   {
//      // non-is_empty list
//      ASSERT(__is_valid_address(m_phead, sizeof(node)));
//      ASSERT(__is_valid_address(m_pointail, sizeof(node)));
//   }
//}
//
//
//void string_list::dump(dump_context & dumpcontext) const
//{
//   matter::dump(dumpcontext);
//
//   dumpcontext << "with " << m_count << " elements";
//   if (dumpcontext.GetDepth() > 0)
//   {
//      POSITION pos = get_head_position();
//      while (pos != nullptr)
//         dumpcontext << "\n\t" << get_next(pos);
//   }
//
//   dumpcontext << "\n";
//}

