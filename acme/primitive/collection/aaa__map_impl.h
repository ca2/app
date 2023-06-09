#pragma once


template < typename KEY, typename PAYLOAD, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
void map < KEY, PAYLOAD, ARG_KEY, ARG_VALUE, PAIR >::InitHashTable(
   ::u32 nHashSize, bool bAllocNow)
   //
   // Used to force allocation of a hash table or to override the default
   //   hash table size_i32 of (which is fairly small)
{

   ASSERT_VALID(this);
   ASSERT(this->m_nCount == 0);
   ASSERT(nHashSize > 0);

   this->m_hashtable.InitHashTable(nHashSize,bAllocNow);

}


template < typename KEY, typename PAYLOAD, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
void map < KEY, PAYLOAD, ARG_KEY, ARG_VALUE, PAIR >::dump(dump_context& dumpcontext) const
{

   ::matter::dump(dumpcontext);

   //dumpcontext << "with " << this->m_nCount << " elements";
   //if (dumpcontext.GetDepth() > 0)
   //{
   //   // Dump in format "[key] -> value"

   //   const association* passociation = get_start();
   //   while (passociation != nullptr)
   //   {
   //      passociation = get_next(passociation);
   //      dumpcontext << "\n\t[";
   //      dump_elements<KEY>(dumpcontext, &passociation->element1(), 1);
   //      dumpcontext << "] = ";
   //      dump_elements<PAYLOAD>(dumpcontext, &passociation->element2(), 1);
   //   }
   //}

   //dumpcontext << "\n";
}



