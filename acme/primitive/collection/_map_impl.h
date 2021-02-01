#pragma once


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::InitHashTable(
   ::u32 nHashSize, bool bAllocNow)
   //
   // Used to force allocation of a hash table or to override the default
   //   hash table size_i32 of (which is fairly small)
{

   ASSERT_VALID(this);
   ASSERT(m_nCount == 0);
   ASSERT(nHashSize > 0);

   m_hashtable.InitHashTable(nHashSize,bAllocNow);

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::dump(dump_context& dumpcontext) const
{

   ::matter::dump(dumpcontext);

   dumpcontext << "with " << m_nCount << " elements";
   if (dumpcontext.GetDepth() > 0)
   {
      // Dump in format "[key] -> value"

      const assoc* passoc = get_start();
      while (passoc != nullptr)
      {
         passoc = get_next(passoc);
         dumpcontext << "\n\t[";
         dump_elements<KEY>(dumpcontext, &passoc->element1(), 1);
         dumpcontext << "] = ";
         dump_elements<VALUE>(dumpcontext, &passoc->element2(), 1);
      }
   }

   dumpcontext << "\n";
}



