#pragma once


template<class TYPE, class ARG_TYPE>
typename list<TYPE, ARG_TYPE>::node * list<TYPE, ARG_TYPE>::add_head(ARG_TYPE newElement)
{

   ASSERT_VALID(this);

   typename list < TYPE, ARG_TYPE >::node * pnodeNew = aaa_primitive_new typename list < TYPE, ARG_TYPE >::node(newElement, nullptr, this->m_phead);

   if(this->m_phead != nullptr)
      this->m_phead->m_pprevious = pnodeNew;
   else
      this->m_ptail = pnodeNew;

   this->m_phead = pnodeNew;

   this->m_count++;

   return pnodeNew;

}

template<class TYPE, class ARG_TYPE>
typename list<TYPE, ARG_TYPE>::node * list<TYPE, ARG_TYPE>::add_tail(ARG_TYPE newElement)
{
   ASSERT_VALID(this);

   auto pnodeNew = aaa_primitive_new typename list < TYPE, ARG_TYPE >::node(newElement, this->m_ptail, nullptr);

   pnodeNew->m_value = newElement;

   if (this->m_ptail != nullptr)
      this->m_ptail->m_pnext = pnodeNew;
   else
      this->m_phead = pnodeNew;

   this->m_ptail = pnodeNew;

   this->m_count++;

   return pnodeNew;

}


template<class TYPE, class ARG_TYPE>
typename list<TYPE, ARG_TYPE>::node * list<TYPE, ARG_TYPE>::insert_before(typename list<TYPE, ARG_TYPE>::node * position, ARG_TYPE newElement)
{
   ASSERT_VALID(this);

   if (position == nullptr)
      return add_head(newElement); // insert before nothing -> head of the list

   // Insert it before position
   auto pOldNode = position;
   auto pnodeNew = aaa_primitive_new typename list < TYPE, ARG_TYPE >::node(newElement, pOldNode->m_pprevious, pOldNode);
   pnodeNew->m_value = newElement;

   if (pOldNode->m_pprevious != nullptr)
   {
      ASSERT(is_memory_segment_ok(pOldNode->m_pprevious, sizeof(typename list < TYPE, ARG_TYPE >::node)));
      pOldNode->m_pprevious->m_pnext = pnodeNew;
   }
   else
   {
      ASSERT(pOldNode == this->m_phead);
      this->m_phead = pnodeNew;
   }
   pOldNode->m_pprevious = pnodeNew;
   return pnodeNew;
}

template<class TYPE, class ARG_TYPE>
typename list<TYPE, ARG_TYPE>::node * list<TYPE, ARG_TYPE>::insert_after(typename list<TYPE, ARG_TYPE>::node * position, ARG_TYPE newElement)
{
   ASSERT_VALID(this);

   if (position == nullptr)
      return add_tail(newElement); // insert after nothing -> tail of the list

   // Insert it before position
   auto pOldNode = position;
   ASSERT(is_memory_segment_ok(pOldNode, sizeof(typename list < TYPE, ARG_TYPE >::node)));
   auto pnodeNew = aaa_primitive_new typename list < TYPE, ARG_TYPE >::node(newElement, pOldNode, pOldNode->m_pnext);
   pnodeNew->m_value = newElement;

   if (pOldNode->m_pnext != nullptr)
   {
      ASSERT(is_memory_segment_ok(pOldNode->m_pnext, sizeof(typename list < TYPE, ARG_TYPE >::node)));
      pOldNode->m_pnext->m_pprevious = pnodeNew;
   }
   else
   {
      ASSERT(pOldNode == this->m_ptail);
      this->m_ptail = pnodeNew;
   }
   pOldNode->m_pnext = pnodeNew;
   return pnodeNew;
}






//string_list::node * string_list::find(const string & searchValue, node * startAfter) const
//{
//
//   if (::is_set(startAfter))
//   {
//
//      return ::find_payload(*this, searchValue, iterator(startAfter, this));
//
//   }
//   else
//   {
//
//      return ::find_payload(*this, searchValue);
//
//   }
//
//}


template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::dump(dump_context& dumpcontext) const
{

   matter::dump(dumpcontext);

   //dumpcontext << "with " << this->m_count << " elements";

   //if (dumpcontext.GetDepth() > 0)
   //{

   //   auto pnode = this->get_head();

   //   while (::is_set(pnode))
   //   {

   //      dumpcontext << "\n";

   //      dump_elements(dumpcontext, &pnode->m_value, 1);

   //      pnode = pnode->m_pnext;

   //   }

   //}

   //dumpcontext << "\n";

}


//template < typename TYPE >
//inline stream& operator <<(stream& stream, const string_list& list)
//{
//
//   stream << list.get_count();
//
//   for (auto& pitem : list)
//   {
//      stream << *pitem;
//   }
//
//   return stream;
//
//}
//
//
//template < typename TYPE >
//inline stream& operator >>(stream& stream, string_list& list)
//{
//
//   int iSize;
//   stream >> iSize;
//   string str;
//   for (int i = 0; i < iSize; i++)
//   {
//      stream >> str;
//      list.add_tail(str);
//   }
//   return stream;
//}
//



