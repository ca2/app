#pragma once


#include "hash_table.h"
#include "list_iterator.h"
#include "range.h"
#include "single.h"
#include "acme/primitive/primitive/particle.h"


template < typename NODE >
class node_set :
   virtual public ::particle,
   public ::range < ::list_iterator < ::set_node < NODE > * > >
{
public:


   using HASH_TABLE = set_dynamic_hash_table < NODE >;
   using ITEM = typename ::set_node < NODE >::ITEM;
   using ARG_ITEM = typename ::set_node < NODE >::ARG_ITEM;


   using node = ::set_node < NODE > ;
   using single = node;

   using ITEM_TYPE = node;

   using BASE_RANGE = ::range < ::list_iterator < node * > >;

   using CONTAINER_ITEM_TYPE = node;

   using iterator = typename BASE_RANGE::iterator;
   using const_iterator = typename BASE_RANGE::const_iterator;


   //__declare_iterator_struct_ok(set, iterator, m_pnode, ::is_set(this->m_pnode));


//   template < typename iterator > struct make_iterator : iterator
//   {
//
//      using CONTAINER = typename iterator::CONTAINER;
//
//      using iterator::iterator;
//
//      make_iterator()
//      {
//         this->m_pnode = (iterator)nullptr;
//         this->m_pcontainer = (CONTAINER*)nullptr;
//         this->m_pnodeBeg = (iterator)nullptr;
//         this->m_pnodeEnd = (iterator) nullptr;
//      }
//
//      make_iterator(const iterator iterator, const CONTAINER * pset = nullptr)
//      {
//         this->m_pnode = (iterator) iterator;
//         this->m_pcontainer = (CONTAINER *) pset;
//         this->m_pnodeBeg = (iterator) iterator;
//         this->m_pnodeEnd = (iterator) nullptr;
//      }
//
//
//      make_iterator(const make_iterator & iterator)
//      {
//         this->m_pnode = iterator.m_pnode;
//         this->m_pcontainer = iterator.m_pcontainer;
//         this->m_pnodeBeg = (iterator) iterator.m_pnodeBeg;
//         this->m_pnodeEnd = (iterator) iterator.m_pnodeEnd;
//      }
//
//
//      make_iterator begin() const
//      {
//
//         return make_iterator(this->m_pcontainer->get_start(), this->m_pcontainer);
//
//      }
//
//
//      make_iterator end() const
//      {
//
//         return make_iterator(nullptr, this->m_pcontainer);
//
//      }
//
//
//      make_iterator & operator ++ ()
//      {
//
//         this->m_pnode = this->m_pnode->m_next;
//
//         return *this;
//
//      }
//
//      template < typename PRED >
//      void each(PRED pred)
//      {
//
//         while (this->ok())
//         {
//
//#ifdef CPP17
//
//            if (returns_false(pred, true, this->operator *()))
//            {
//
//               break;
//
//            }
//
//#else
//
//            pred(this->operator *());
//
//            //if (returns_false(pred, true, this->operator *()))
//            //{
//
//              // break;
//
//            //}
//
//
//#endif
//
//            this->operator++();
//
//         }
//
//      }
//
//
//      make_iterator operator ++ (i32)
//      {
//
//         make_iterator iterator = this->m_pnode;
//
//         this->m_pnode = this->m_pnode->m_next;
//
//         return iterator;
//
//      }
//
//
//      bool operator == (const make_iterator & it) const
//      {
//
//         if (this == &it)
//         {
//
//            return true;
//
//         }
//
//         if (this->m_pnode == nullptr && it.m_pnode == nullptr && it.m_pcontainer == nullptr)
//         {
//
//            return true;
//
//         }
//
//         if (this->m_pcontainer != it.m_pcontainer)
//         {
//
//            return false;
//
//         }
//
//         return this->m_pnode == it.m_pnode;
//
//      }
//
//
//
//      bool operator != (const make_iterator & it) const
//      {
//
//         return !operator == (it);
//
//      }
//
//
//      make_iterator & operator = (const make_iterator & it)
//      {
//
//         if (this != &it)
//         {
//
//            this->m_pcontainer = it.m_pcontainer;
//
//            this->m_pnode = it.m_pnode;
//
//         }
//
//         return *this;
//
//      }
//
//   };
//
//
//   //__declare_iterator(dereferenced_value_iterator, this->m_pnode->item());
//   //__declare_iterator(value_iterator, &this->m_pnode->item());
//   __declare_iterator(key_iterator, &this->m_pnode->item());
//   __declare_iterator(iterator, this->m_pnode);
//

   //using deferenced_iterator = dereferenced_value_iterator;



   HASH_TABLE           m_hashtable;
   ::count              m_nCount;
   //iterator              m_begin;


   node_set();
   node_set(node singles[], i32 iCount);
   node_set(const ::std::initializer_list < NODE > & list);
   node_set(const node_set & m);
   virtual ~node_set();

   void construct();

   ::count get_count() const;
   ::count get_size() const;
   ::count size() const;
   ::count count() const;
   bool is_empty() const;
   bool empty() const;


   //inline iterator begin() { return iterator(get_start(), this); }
   //inline iterator end() { return iterator(nullptr, this); }


   //inline const_iterator begin() const { return const_iterator(((set *)this)->get_start(), this); }
   //inline const_iterator end() const { return consst_iterator(nullptr, (set *)this); }


   //lookup
   bool lookup(ARG_ITEM item, ITEM& rValue) const;
   const_iterator plookup(ARG_ITEM item) const;
   iterator plookup(ARG_ITEM item);


   bool should_set(ARG_ITEM item)
   { 
      
      if (has(item))
      {

         return false;

      }

      set_at(item);

      return true;

   }


   
   ITEM * pget(ARG_ITEM item);


   template < typename TITEM >
   auto pop(const TITEM & item)
   {

      auto value = operator[](item);

      erase_key(item);

      return value;

   }

   //Operations
   //lookup and add if not there
   ITEM & operator[](ARG_ITEM item);
   const ITEM & operator[](ARG_ITEM item) const;

   iterator get_item(ARG_ITEM item);
   const_iterator find_item(ARG_ITEM item) const;

   //add a memory_new (item) node
   inline iterator set_at(ARG_ITEM item);

   //add a memory_new (item, value) node
   void set_payload(const NODE& payload)
   {
      set_at(payload.item());
   }

   bool erase(iterator iterator);

   //removing existing (item, ?) node
   inline bool erase_item(ARG_ITEM item) { auto p = this->find_item(item);  return p ? this->erase(p) : false; }

   //template < typename iterator >
   //inline iterator erase(iterator it) { return ::acme::iterator::erase(*this, it); }

   template < typename iterator >
   inline void erase(const iterator & begin, const iterator & last)
   {

      for(auto it = begin; it != last; it++)
      {

         erase(it);

      }

   }


   inline bool unhash(iterator iterator);

   void erase_all();
   void clear();
   void Empty();

//   inline auto singles() { return iterator(nullptr, this); }
//   inline auto singles() const { return const_iterator(nullptr, this); }
////   inline auto values() const { return value_iterator(nullptr, this); }
//   inline auto keys() const { return key_iterator(nullptr, this); }



   ::count count(const ITEM & t) const;
   bool has(const ITEM & t) const;
   bool contains(const ITEM & t) const;

   //iterating all (item, value) singles
//   POSITION get_start_position() const;

   //const iterator get_start() const;
   //iterator get_start();

   //void get_next(iterator & rNextPosition, ITEM& rKey, ITEM& rValue) const;

   //const iterator get_next(const iteratorpnodeRet) const;
   //iterator get_next(const iteratorpnodeRet);

   //advanced features for derived classes
   ::u32 GetHashTableSize() const
   {
      
      return m_hashtable.GetHashTableSize();
      
   }
   
   
   void InitHashTable(::u32 hashSize,bool bAllocNow = true);


   ITEM get(ARG_ITEM argkey, ARG_ITEM valueDefault);


   //iterator next(iterator & iterator)
   //{
   //   if(iterator == nullptr)
   //   {
   //      iterator = get_start();
   //   }
   //   else
   //   {
   //      iterator = get_next(iterator);
   //   }
   //   return iterator;
   //}

   //const iterator next(const iterator & iterator) const
   //{
   //   if(iterator == nullptr)
   //   {
   //      iterator = get_start();
   //   }
   //   else
   //   {
   //      iterator = get_next(iterator);
   //   }
   //   return iterator;
   //}


   void assign(node_set & set)
   {

      auto it = set.begin();

      while(it.is_set())
      {

         set_payload(*it);

         it++;

      }

   }
   

   //inline iterator find_item(ARG_ITEM item) const { return find_node(item); }

   //inline iterator find(ARG_ITEM item) { return find_item(item); }
   //const_iterator find (ARG_ITEM item) const { return find_item(item); }


   iterator new_node(ARG_ITEM item);
   void free_node(iterator iterator);
   iterator find_item(ARG_ITEM, ::u32&, ::u32&) const;


   //// void assert_ok() const override;
   //// void dump(dump_context & dumpcontext) const override;



   template < class ARRAY >
   bool erase_key_array(ARRAY a)
   {

      bool bRemoved = false;

      for(index i = 0; i < a.get_count(); i++)
      {

         bRemoved |= erase_key(a[i]);

      }

      return bRemoved;

   }

   template < class ARRAY >
   ::count erase_node_array(ARRAY a)
   {

      ::count countRemoved = 0;

      for(index i = 0; i < a.get_count(); i++)
      {

         if(erase_node(a[i]))
         {

            countRemoved++;

         }

      }

      return countRemoved;

   }

//   virtual void on_after_read() {}

   //::range < iterator > elements()
   //{
   //   return range < iterator >(begin(),end());
   //}
   //
   //::range < const_iterator > elements() const
   //{
   //   return range < const_iterator >(begin(),end());
   //}

   //NODE & element_at(::index iIndex)
   //{
   //   return elements().element_at(iIndex);
   //}

   template < typename PRED >
   typename node_set < NODE >::iterator predicate_find(PRED pred)
   {

      auto point = this->get_start();

      while (point != nullptr)
      {

         if (pred(point))
         {

            return point;

         }

         point = this->get_next(point);

      }

      return nullptr;

   }

   node_set & operator = (const node_set & m);


   template < typename TYPE >
   ::pointer<TYPE>get_typed_ptr(index i = 0)
   {

      ::pointer<TYPE>p;

     for(auto & pvalue : *this)
     {

         p = pvalue;

         if(p)
         {

             if(i <= 0)
             {

                 return p;

             }

             i--;

         }

     }

     return nullptr;

   }


};


template < typename NODE >
inline ::count node_set < NODE >::get_count() const
{
   return m_nCount;
}

template < typename NODE >
inline ::count node_set < NODE >::get_size() const
{
   return m_nCount;
}

template < typename NODE >
inline ::count node_set < NODE >::count() const
{
   return m_nCount;
}

template < typename NODE >
inline ::count node_set < NODE >::size() const
{
   return m_nCount;
}

template < typename NODE >
node_set < NODE > & node_set < NODE >::operator = (const node_set & m)
{
   if(this != &m)
   {

      erase_all();

      for(auto & node : m)
      {

         set_at(node.item());

      }

   }
   return *this;
}

template < typename NODE >
inline bool node_set < NODE >::is_empty() const
{
   return m_nCount == 0;
}

template < typename NODE >
inline bool node_set < NODE >::empty() const
{
   return m_nCount == 0;
}


template < typename NODE >
inline typename node_set < NODE >::iterator node_set < NODE >::set_at(ARG_ITEM item)
{

   iterator iterator = get_item(item);

   //iterator->item() = newValue;

   return iterator;

}


//template < typename NODE >
//inline typename node_set < NODE >::iterator node_set < NODE >::get_start() const
//{
//   return (m_nCount == 0) ? nullptr : BEFORE_START_POSITION;
//}

//template < typename NODE >
//const typename node_set < NODE >::iterator node_set < NODE >::get_start() const
//{
//
//   return this->m_begin;
//
//}
//
//template < typename NODE >
//typename node_set < NODE >::iterator node_set < NODE >::get_start()
//{
//
//   return this->m_begin;
//
//}

/////////////////////////////////////////////////////////////////////////////
// node_set < NODE > out-of-line functions
template < typename NODE >
void node_set < NODE >::construct()
{

   m_nCount          = 0;
   this->m_begin      = nullptr;
   this->m_end = nullptr;

}


template < typename NODE >
node_set < NODE >::node_set()
{

   construct();

}


template < typename NODE >
node_set < NODE >::node_set(const ::std::initializer_list < NODE > & list)
{

   construct();

   for(auto & pair_item : list)
   {

      set_at(pair_item.item());

   }

}

template < typename NODE >
node_set < NODE >::node_set(node singles[], i32 iCount)
{
   construct();
   for(i32 i = 0; i < iCount; i++)
   {
      set_at(singles[i].item());
   }
}


template < typename NODE >
node_set < NODE >::node_set(const node_set & m)
{
   
   construct();

   for(auto & pair : m)
   {

      set_at(pair.item());

   }

}


template < typename NODE >
void node_set < NODE >::erase_all()
{

   //ASSERT_VALID(this);

   if(this->begin())
   {
      // destroy elements (items and loads - item load pair)

      iterator pnext;

      for (auto p = this->begin(); p; p = pnext)
      {

         pnext = p + 1;

         delete p.get();

      }

   }

   m_hashtable.erase_all();

   m_nCount = 0;
   //this->m_pnodeFree = nullptr;

   //if(m_pplex != nullptr)
   //{

   //   m_pplex->FreeDataChain();
   //   m_pplex = nullptr;

   //}

   this->m_begin = nullptr;

}


template < typename NODE >
inline void node_set < NODE >::clear()
{
   erase_all();
}

template < typename NODE >
inline void node_set < NODE >::Empty()
{
   clear();
}

template < typename NODE >
node_set < NODE >::~node_set()
{
   erase_all();
   ASSERT(m_nCount == 0);
}

template < typename NODE >
typename node_set < NODE >::iterator
node_set < NODE >::new_node(ARG_ITEM item)
{

   //if(this->m_pnodeFree == nullptr)
   //{
   //   // add another block
   //   //plex * newBlock = plex::create(m_pplex, m_nBlockSize, sizeof(set::node));
   //   //// chain them into free list
   //   //set::iterator iterator = (set::iterator) newBlock->data();
   //   //// free in reverse order to make it easier to debug
   //   //index i = m_nBlockSize - 1;
   //   //for (iterator = &iterator[i]; i >= 0; i--, iterator--)
   //   //{
   //   //   iterator->m_next = this->m_pnodeFree;
   //   //   this->m_pnodeFree = iterator;

   //   //}
   //   this->m_pnodeFree = memory_new node();

   //}

   //ENSURE(this->m_pnodeFree != nullptr);  // we must have something

   typename node_set < NODE >::iterator iterator =
   memory_new node(item);

   //this->m_pnodeFree  = this->m_pnodeFree->m_next;

   //zero_pointer(iterator);

   if(this->begin())
   {

      this->m_begin->m_back   = iterator.get();

   }

   iterator->m_next            = this->m_begin.get();

   this->m_begin               = iterator;

   this->m_begin->m_back      = nullptr;

   m_nCount++;

   ASSERT(m_nCount > 0);  // make sure we don't overflow

   return iterator;

}


template < typename NODE >
void node_set < NODE >::free_node(iterator iterator)
{

   auto next = iterator->m_next;

   if(iterator->m_next != nullptr)
   {

      iterator->m_next->m_back = iterator->m_back;

   }

   if(iterator->m_back != nullptr)
   {

      iterator->m_back->m_next = iterator->m_next;

   }

   if(this->m_begin == iterator)
   {

      this->m_begin = next;

      if(this->m_begin)
      {

         this->m_begin->m_back = nullptr;

      }

   }

   delete iterator.get();

   //iterator->m_next = this->m_pnodeFree;

   //this->m_pnodeFree = iterator;

   m_nCount--;

   ASSERT(m_nCount >= 0);  // make sure we don't underflow

   // if no more elements, cleanup completely
   if (m_nCount == 0)
   {

      erase_all();

   }

}


template < typename NODE >
typename node_set < NODE >::iterator
node_set < NODE >::find_item(ARG_ITEM item, ::u32& nHashBucket, ::u32& nHashValue) const
{

   if (is_empty())
   {

      return nullptr;

   }

   nHashValue = u32_hash<ARG_ITEM>(item).m_u;

   nHashBucket = nHashValue % m_hashtable.GetHashTableSize();

   for(auto p = m_hashtable.m_ppHash[nHashBucket]; p; p = p->m_nextHash)
   {

      if (EqualElements<ARG_ITEM>(p->item(), item))
      {

         return p;

      }

   }

   return nullptr;

}


template < typename NODE >
bool node_set < NODE >::lookup(ARG_ITEM item, ITEM& rValue) const
{

   ::u32 nHashBucket, nHashValue;

   auto p = find_item(item, nHashBucket, nHashValue);

   if (!p)
   {

      return false;  // not in set

   }

   rValue = p->item();

   return true;

}


//template < typename NODE >
//typename node_set < NODE >::iterator node_set < NODE >::find (ARG_ITEM item)
//{
//   return iterator(plookup(item), this);
//}
//
//template < typename NODE >
//typename node_set < NODE >::const_iterator node_set < NODE >::find (ARG_ITEM item) const
//{
//   return const_iterator((iterator) plookup(item), (set *) this);
//}


template < typename NODE >
typename node_set < NODE >::const_iterator node_set < NODE >::plookup(ARG_ITEM item) const
{

   return find_item(item);

}


template < typename NODE >
typename node_set < NODE >::iterator node_set < NODE >::plookup(ARG_ITEM item)
{

   ::u32 nHashBucket, nHashValue;

   auto p = find_item(item, nHashBucket, nHashValue);

   return p;

}


template < typename NODE >
typename node_set < NODE >::ITEM * node_set < NODE >::pget(ARG_ITEM item)
{

   auto p = plookup(item);

   if (!p)
   {

      return nullptr;

   }
      
   return &p->item();

}


template < typename NODE >
inline typename node_set < NODE >::const_iterator node_set < NODE >::find_item(ARG_ITEM item) const
{

   ::u32 nHashBucket, nHashValue;

   return find_item(item, nHashBucket, nHashValue);

}


template < typename NODE >
typename node_set < NODE >::iterator node_set < NODE >::get_item(ARG_ITEM item)
{

   ::u32 nHashBucket, nHashValue;

   auto p = find_item(item, nHashBucket, nHashValue);

   if(!p)
   {

      // not precise (memleak? a watch dog can restart from the last check point... continuable tasks need...) but self-healing(self-recoverable/not-fatal)...
      if (::is_null(m_hashtable.m_ppHash))
      {

         InitHashTable(m_hashtable.GetHashTableSize());

      }

      ENSURE(m_hashtable.m_ppHash);

      p = new_node(item);

      if(!m_hashtable.m_ppHash[nHashBucket])
      {

         m_hashtable.m_ppHash[nHashBucket]->m_pbackHash = &p->m_nextHash;

      }

      p->m_nextHash        = m_hashtable.m_ppHash[nHashBucket].get();

      m_hashtable.m_ppHash[nHashBucket] = p;

      p->m_pbackHash       = &m_hashtable.m_ppHash[nHashBucket].get();

   }

   return p;

}


template < typename NODE >
typename node_set < NODE >::ITEM & node_set < NODE >::operator[](ARG_ITEM item)
{

   return get_item(item)->item();

}


template < typename NODE >
const typename node_set < NODE >::ITEM & node_set < NODE >::operator[](ARG_ITEM item) const
{

   auto p = find_item(item);

   if (!p)
   {

      throw_exception(error_key_not_found);

   }

   return p->item();

}


template < typename NODE >
inline bool node_set < NODE >::erase(iterator iterator)
// erase - return true if erased
{

   if(iterator->m_nextHash != nullptr)
   {

      iterator->m_nextHash->m_pbackHash = iterator->m_pbackHash;

   }

   *iterator->m_pbackHash = iterator->m_nextHash;

   free_node(iterator);

   return true;

}


template < typename NODE >
inline ::count node_set < NODE >::count(const ITEM & item) const
{

   return this->plookup(item) ? 1 : 0;

}


template < typename NODE >
bool node_set < NODE >::has(const ITEM & item) const
{

   return this->plookup(item) ? 1 : 0;

}


template < typename NODE >
bool node_set < NODE >::contains(const ITEM & item) const
{

   return this->plookup(item) ? 1 : 0;

}


//template < typename NODE >
//void node_set < NODE >::get_next(iterator & iterator,
//      ITEM& rKey, ITEM& rValue) const
//{
//
//   rKey = iterator->item();
//
//   rValue = iterator->item();
//
//   iterator = iterator->m_next;
//
//}
//
//
//template < typename NODE >
//inline const typename node_set < NODE >::iterator
//node_set < NODE >::get_next(const iterator iterator) const
//{
//
//   return iterator->m_next;
//
//}
//
//
//template < typename NODE >
//inline typename node_set < NODE >::iterator
//node_set < NODE >::get_next(const iterator iterator)
//{
//
//   return iterator->m_next;
//
//}


template < typename NODE >
typename node_set < NODE >::ITEM node_set < NODE > ::
get(ARG_ITEM argkey, ARG_ITEM valueDefault)
{
   
   auto p = plookup(argkey);

   if (!p)
   {

      return valueDefault;

   }

   return p->item();

}


//template < typename NODE >
//void node_set < NODE >::assert_ok() const
//{
//
//   ::matter::assert_ok();
//
//   ASSERT(GetHashTableSize() > 0);
//
//   ASSERT(m_nCount == 0 || m_hashtable.m_ppHash != nullptr);
//   // non-empty set should have hash table
//
//}
//

using double_set = set < double >;

using dword_set = set < ::u32 >;

using uptr_set = set < ::uptr >;

//template < typename ITEM_TYPE >
//class item
//{
//
//
//   using ITEM = ITEM_TYPE;
//   using TYPE = ITEM;
//   using ARG_TYPE = argument_of < ITEM & >;
//
//
//   // Contract
//   // ITEM & item();
//   // ITEM & item();
//   // const ITEM & item() const;
//   // const ITEM & item() const;
//
//};


template < typename NODE >
using key_set = node_set < NODE >;


#define __declare_key(xkeytype, xkey) \
struct xkeytype : public ::item < xkeytype > \
{ \
\
   PAIR_DEFAULT_IMPL(xkeytype, ITEM, const ITEM &, xkey); \
   ITEM & item() { return xkey; } \
   const ITEM & item() const { return xkey; } \
}


#ifdef CPP17
#define __declare_key_tuple_size(item) \
template<> ALIENATED_ANDROID_ANARCHY ::std::tuple_size< item > : ::std::integral_constant<size_t, 1> {} }
#endif


#define __declare_set(xsettype, xkeyvaluetype, xkeytype, xkey, xvaluetype, xvalue) \
__declare_key_value(xkeyvaluetype, xkeytype, xkey, xvaluetype, xvalue); \
using xsettype = pair_set < xkeyvaluetype >


#ifdef CPP17
#define __declare_set_key_value(xsettype, xkeyvaluetype, xkeytype, xkey, xvaluetype, xvalue) \
__declare_set(xkeyvaluetype, xkeytype, xkey, xvaluetype, xvalue); \
__declare_pair_tuple_size(xsettype)
#else

#define __declare_set_key_value(xsettype, xkeyvaluetype, xkeytype, xkey, xvaluetype, xvalue) \
__declare_set(xkeyvaluetype, xkeytype, xkey, xvaluetype, xvalue);

#endif


using int_ptr_set = set < iptr >;

using index_set = set < index >;

using string_set = set < string >;




//#pragma once


template < typename NODE >
void node_set < NODE >::InitHashTable(
   ::u32 nHashSize, bool bAllocNow)
//
// Used to force allocation of a hash table or to override the default
//   hash table size_i32 of (which is fairly small)
{

   //ASSERT_VALID(this);
   ASSERT(this->m_nCount == 0);
   ASSERT(nHashSize > 0);

   this->m_hashtable.InitHashTable(nHashSize,bAllocNow);

}


//template < typename NODE >
//void node_set < NODE >::dump(dump_context& dumpcontext) const
//{
//
//   ::matter::dump(dumpcontext);
//
//   //dumpcontext << "with " << this->m_nCount << " elements";
//   //if (dumpcontext.GetDepth() > 0)
//   //{
//   //   // Dump in format "[item] -> value"
//
//   //   const iterator iterator = get_start();
//   //   while (iterator != nullptr)
//   //   {
//   //      iterator = get_next(iterator);
//   //      dumpcontext << "\n\t[";
//   //      dump_elements<ITEM>(dumpcontext, &iterator->item(), 1);
//   //   }
//   //}
//
//   //dumpcontext << "\n";
//}
//
//
//




template < typename NODE >
inline bool node_set < NODE >::unhash(iterator iterator)
// erase - return true if erased
{

   if(::is_set(iterator->m_nextHash))
   {

      iterator->m_nextHash->m_pbackHash = iterator->m_pbackHash;

   }

   *iterator->m_pbackHash = iterator->m_nextHash;

   return true;

}

