#pragma once


template < typename KEY, typename ARG_KEY, typename PAYLOAD >
void set < KEY, ARG_KEY, PAYLOAD >::InitHashTable(
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


template < typename KEY, typename ARG_KEY, typename PAYLOAD >
void set < KEY, ARG_KEY, PAYLOAD >::dump(dump_context& dumpcontext) const
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
   //      dump_elements<KEY>(dumpcontext, &passociation->key(), 1);
   //   }
   //}

   //dumpcontext << "\n";
}



