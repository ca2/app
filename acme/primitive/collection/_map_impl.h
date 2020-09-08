#pragma once


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR >
void map < KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR >::InitHashTable(
   UINT nHashSize, bool bAllocNow)
   //
   // Used to force allocation of a hash table or to override the default
   //   hash table size of (which is fairly small)
{

   ASSERT_VALID(this);
   ASSERT(m_nCount == 0);
   ASSERT(nHashSize > 0);

   m_hashtable.InitHashTable(nHashSize,bAllocNow);

}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR >
void map < KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR >::dump(dump_context& dumpcontext) const
{

   ::generic::dump(dumpcontext);

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



