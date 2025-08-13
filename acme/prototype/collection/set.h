#pragma once


#include "hash_table.h"
#include "list_iterator.h"
#include "range.h"
#include "single.h"



template < typename ITEM >
class node_set_base :
   public ::range < ::list_iterator < ::set_node < ITEM > * > >
{
public:


   using BASE_RANGE = ::range < ::list_iterator < ::set_node < ITEM > * > >;


   using BASE_NODE = ::set_node < ITEM > ;
   using BASE_ITEM = typename BASE_NODE::BASE_ITEM;
   using HASH_TABLE = set_dynamic_hash_table < ITEM >;
   using KEY = typename BASE_NODE::KEY;
   using ARG_KEY = typename BASE_NODE::ARG_KEY;
   using PAYLOAD = typename BASE_NODE::PAYLOAD;
   using ARG_PAYLOAD = typename BASE_NODE::ARG_PAYLOAD;

   using CONST_ARG_KEY = const non_const<typename BASE_NODE::ARG_KEY>;

   using iterator = typename BASE_RANGE::iterator;
   using const_iterator = typename BASE_RANGE::const_iterator;

   using item_iterator = ::element1_list_iterator < BASE_NODE * >;
   using payload_iterator = ::element2_list_iterator < BASE_NODE * >;
   using const_item_iterator = typename item_iterator::const_iterator;
   using const_payload_iterator = typename payload_iterator::const_iterator;


   HASH_TABLE                       m_hashtable;
   ::collection::count              m_count;


   node_set_base();
   template <typename T, ::collection::count count>
   node_set_base(const T (&itema)[count]) :
      node_set_base(itema, count)
   {

   }
   node_set_base(BASE_ITEM * pitem, int iCount);
   node_set_base(const ::std::initializer_list < BASE_ITEM > & list_base);
   node_set_base(const node_set_base & m);

   //
   // pair_map_base();
   // pair_map_base(const PAIR * ppair, ::collection::count c);
   // pair_map_base(const ::std::initializer_list < PAIR > & list_base);
   // pair_map_base(const pair_map_base & m);
   // ~pair_map_base();

   ~node_set_base();

   void construct();

   ::collection::count get_count() const;
   ::collection::count get_size() const;
   ::collection::count size() const;
   ::collection::count count() const;
   bool is_empty() const;
   bool empty() const;


   bool lookup(ARG_KEY key, PAYLOAD& payload) const;
   const_iterator plookup(ARG_KEY key) const;
   iterator plookup(ARG_KEY key);


   bool should_set(ARG_KEY key)
   { 
      
      if (has_key(key))
      {

         return false;

      }

      set_key(key);

      return true;

   }


   PAYLOAD * pget(ARG_KEY key);
   const PAYLOAD * pget(ARG_KEY key) const
   {

      return ((node_set_base *)this)->pget(key);

   }


   template < typename TKEY >
   auto pop(const TKEY & KEY)
   {

      auto value = operator[](KEY);

      erase_key(KEY);

      return value;

   }

   //Operations
   //lookup and add if not there
   PAYLOAD & operator[](ARG_KEY key);
   const PAYLOAD & operator[](ARG_KEY key) const;

   iterator find_node(ARG_KEY key);
   const_iterator find_node(ARG_KEY key) const;

   inline iterator set_key(ARG_KEY key);

   iterator set_item(const BASE_ITEM & item)
   {

      return set_at((ARG_KEY) item.key(), (ARG_PAYLOAD) item.payload());

   }

   bool erase(iterator iterator);

   bool toggle(ARG_KEY key)
   {

      auto pnode = this->find_node(key);

      if (pnode)
      {

         this->erase(pnode);

         return false;

      }
      else
      {

         set_item(key);

         return true;

      }

   }

   inline bool erase_key(ARG_KEY key) { auto p = this->find_node(key);  return p ? this->erase(p) : false; }

   template < typename iterator >
   inline void erase_range(const iterator & begin, const iterator & last)
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


   ::collection::count key_count(ARG_KEY key) const;
   bool has_key(ARG_KEY key) const;
   bool contains_key(ARG_KEY key) const;


   unsigned int GetHashTableSize() const
   {
      
      return m_hashtable.GetHashTableSize();
      
   }
   
   
   void InitHashTable(unsigned int hashSize,bool bAllocNow = true);


   PAYLOAD get(ARG_KEY argkey, ARG_PAYLOAD valueDefault);


   void assign(node_set_base & set)
   {

      auto it = set.begin();

      while(it.is_set())
      {

         set_item(*it);

         it++;

      }

   }
   


   iterator new_node(ARG_KEY key);
   void free_node(iterator pnode);
   iterator find_node(ARG_KEY key, unsigned int&, unsigned int&) const;
   iterator get_node(ARG_KEY key);


   template < primitive_container CONTAINER >
   ::collection::count erase_nodes(CONTAINER container)
   {

      ::collection::count countRemoved = 0;

      for(auto & KEY : container)
      {

         if(this->erase(KEY))
         {

            countRemoved++;

         }

      }

      return countRemoved;

   }


   template < typename PRED >
   typename iterator predicate_find(PRED pred)
   {

      auto p = this->begin();

      while (p)
      {

         if (pred(p))
         {

            return p.m_p;

         }

         p++;

      }

      return nullptr;

   }

   node_set_base & operator = (const node_set_base & m);


   template < typename TYPE >
   ::pointer<TYPE>get_typed_ptr(::collection::index i = 0)
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


   template < primitive_container CONTAINER >
   void add_keys(const CONTAINER& container)
   {

      for (auto& item : container)
      {

         this->set_key(item.key());

      }

   }


   template < primitive_container CONTAINER >
   void erase_keys(const CONTAINER& container)
   {

      for (auto& KEY : container)
      {

         this->erase_key(KEY);

      }

   }


   void container_ok() const;


   //void construct();


   // ::collection::count get_count() const;
   // ::collection::count get_size() const;
   // ::collection::count size() const;
   // ::collection::count count() const;
   // bool is_empty() const;
   // bool empty() const;
   //


   //lookup
   //bool lookup(ARG_KEY key, PAYLOAD& rValue) const;
   //const_iterator plookup(ARG_KEY key) const;
   //iterator plookup(ARG_KEY key);


   //PAYLOAD * pget(ARG_KEY key);


   //inline typename pair_map_base < PAIR >::iterator get_item(ARG_KEY key);


   // template < typename TITEM >
   // auto pop(const TITEM & key)
   // {
   //
   //    auto value = operator[](key);
   //
   //    this->erase_item(key);
   //
   //    return value;
   //
   // }
   //
   // // //Operations
   // //lookup and add if not there
   // inline PAYLOAD & operator[](ARG_KEY key);
   // inline const PAYLOAD & operator[](ARG_KEY key) const;

   template < typename PAYLOAD2 >
   iterator find_payload(const PAYLOAD2 & payload) const;

   iterator set_at(ARG_KEY key, ARG_PAYLOAD payload)
   {

      auto p = this->get_node(key);

      p->defer_set_payload(payload);

      return p;

   }


   //bool unhash(iterator iterator);

   //removing existing (key, ?) node
   //inline bool erase_item(ARG_KEY key) { auto p = this->find_item(key);  return p ? this->erase(p) : false; }

   template < typename PAYLOAD2 >
   inline bool erase_payload(const PAYLOAD2 payload) { auto p = find_payload(payload);  return p ? erase(p) : false; }



   inline auto items() { return ::range<item_iterator>(*(item_iterator *)&this->begin(), *(item_iterator *)&this->end()); }
   inline auto payloads() { return ::range<payload_iterator>(*(payload_iterator *)&this->begin(), *(payload_iterator *)&this->end()); }
   inline auto items() const { return ::range<const_item_iterator>((item_iterator)this->begin(), (item_iterator)this->end()); }
   inline auto payloads() const { return ::range<const_payload_iterator>((payload_iterator )this->begin(), (payload_iterator)this->end()); }



   //
   // ::collection::count key_count(ARG_KEY key) const;
   // bool has_key(ARG_KEY key) const;
   // bool contains_key(ARG_KEY key) const;

   //iterating all (key, value) pairs
//   POSITION get_start_position() const;

   //inline const iterator get_start() const;
   //inline iterator get_start();

   //void get_next(iterator & rNextPosition, ITEM& rKey, PAYLOAD& rValue) const;

   //const iterator get_next(const iteratorpnodeRet) const;
   //iterator get_next(const iteratorpnodeRet);

   // //advanced features for derived classes
   // unsigned int GetHashTableSize() const
   // {
   //
   //    return this->m_hashtable.GetHashTableSize();
   // //
   // // }
   //
   //
   // void InitHashTable(unsigned int hashSize,bool bAllocNow = true);
   //
   //
   // PAYLOAD get(ARG_KEY key, ARG_PAYLOAD valueDefault);
   //


   void set(node_set_base & nodesetbase)
   {

      for(auto & item : nodesetbase)
      {

         set_item(item);

      }

   }


   //inline iterator find_item(ARG_KEY key) const { return find_node(key); }

   //using BASE_SET::find_item;
   //inline const_iterator find_item(ARG_KEY key) const { return ((pair_map_base *) this)->find_item(key); }


   //BASE_NODE * new_node(ARG_KEY key, unsigned int nHashBucket, unsigned int nHashValue);
   inline void hash(iterator iterator, unsigned int nHashBucket, unsigned int nHashValue);
   void attach(iterator iterator, unsigned int nHashBucket, unsigned int nHashValue);
   //bool erase(iterator iterator);
   void detach(iterator iterator);
   void hash(unsigned int& nHashBucket, unsigned int& nHashValue, ARG_KEY) const;
   //inline iterator node_at(ARG_KEY, unsigned int & nHashBucket, unsigned int & nHashValue) const;
   //inline const_iterator node_at(ARG_KEY, unsigned int& nHashBucket, unsigned int& nHashValue) const;

   // void transfer(iterator iterator, pair_map_base * ppair_map = nullptr);
   // void transfer(pair_map_base* ppair_map, ARG_KEY key);

   //// void assert_ok() const override;
   //// void dump(dump_context & dumpcontext) const override;


   template < class ARRAY >
   bool erase_key_array(ARRAY a)
   {

      bool bRemoved = false;

      for(::collection::index i = 0; i < a.get_count(); i++)
      {

         bRemoved |= erase_key(a[i]);

      }

      return bRemoved;

   }


   template < class ARRAY >
   ::collection::count erase_node_array(ARRAY a)
   {

      ::collection::count countRemoved = 0;

      for(::collection::index i = 0; i < a.get_count(); i++)
      {

         if(erase_node(a[i]))
         {

            countRemoved++;

         }

      }

      return countRemoved;

   }

   //virtual void on_after_read() override {}


   //PAIR & element_at(::collection::index iIndex)
   //{
   //   return this->elements().element_at(iIndex);
   //}
   //
   // template < typename PRED >
   // typename BASE_NODE * predicate_find(PRED pred)
   // {
   //
   //    auto pnode = this->begin();
   //
   //    while (::is_ok(pnode))
   //    {
   //
   //       if (pred(pnode))
   //       {
   //
   //          return p;
   //
   //       }
   //
   //       p++;
   //
   //    }
   //
   //    return nullptr;
   //
   // }

   // node_set_base & operator = (const node_set_base & m);
   //
   //
   // template < typename TYPE >
   // ::pointer<TYPE>get_typed_ptr(::collection::index i = 0)
   // {
   //
   //    ::pointer<TYPE>p;
   //
   //   for(auto & node : *this)
   //   {
   //
   //       p = (*node).element2();
   //
   //       if(p)
   //       {
   //
   //           if(i <= 0)
   //           {
   //
   //               return p;
   //
   //           }
   //
   //           i--;
   //
   //       }
   //
   //   }
   //
   //   return nullptr;
   //
   // }
   //


   void transfer(iterator iterator, node_set_base * pnodesetbase = nullptr);
   void transfer(node_set_base * pnodesetbase, ARG_KEY key);


};


template < typename NODE >
inline ::collection::count node_set_base < NODE >::get_count() const
{
   return m_count;
}

template < typename NODE >
inline ::collection::count node_set_base < NODE >::get_size() const
{
   return m_count;
}

template < typename NODE >
inline ::collection::count node_set_base < NODE >::count() const
{
   return m_count;
}

template < typename NODE >
inline ::collection::count node_set_base < NODE >::size() const
{
   return m_count;
}

template < typename NODE >
node_set_base < NODE > & node_set_base < NODE >::operator = (const node_set_base & m)
{

   if(this != &m)
   {

      erase_all();

      for(auto & item : m)
      {

         set_item(item);

      }

   }

   return *this;

}


template < typename NODE >
inline bool node_set_base < NODE >::is_empty() const
{

   return m_count == 0;

}


template < typename NODE >
inline bool node_set_base < NODE >::empty() const
{

   return m_count == 0;

}


template < typename NODE >
inline typename node_set_base < NODE >::iterator
node_set_base < NODE >::set_key(ARG_KEY key)
{

   auto iterator = get_node(key);

   return iterator;

}


template < typename NODE >
void node_set_base < NODE >::construct()
{

   m_count          = 0;
   this->m_begin      = nullptr;
   this->m_end = nullptr;

}


template < typename NODE >
node_set_base < NODE >::node_set_base()
{

   construct();

}


template < typename NODE >
node_set_base < NODE >::node_set_base(const ::std::initializer_list < BASE_ITEM > & items)
{

   construct();

   for(auto & item : items)
   {

      set_item(item);

   }

}


template < typename NODE >
node_set_base < NODE >::node_set_base(BASE_ITEM * pitem, int iCount)
{

   construct();

   for(int i = 0; i < iCount; i++)
   {

      set_item(pitem[i]);

   }

}


template < typename NODE >
node_set_base < NODE >::node_set_base(const node_set_base & m)
{
   
   construct();

   for(auto & item : m)
   {

      set_item(item);

   }

}


template < typename NODE >
void node_set_base < NODE >::erase_all()
{

   //ASSERT_OK(this);

   if(this->begin())
   {
      // destroy elements (KEYs and loads - KEY load pair)

      iterator pnext;

      for (auto p = this->begin(); p; p = pnext)
      {

         pnext = p + 1;

         //__delete(p.get());
         delete p.get();

      }

   }

   m_hashtable.erase_all();

   m_count = 0;
   //this->m_pnodeFree = nullptr;

   //if(m_pplex != nullptr)
   //{

   //   m_pplex->FreeDataChain();
   //   m_pplex = nullptr;

   //}

   this->m_begin = nullptr;

}


template < typename NODE >
inline void node_set_base < NODE >::clear()
{
   erase_all();
}

template < typename NODE >
inline void node_set_base < NODE >::Empty()
{
   clear();
}

template < typename NODE >
node_set_base < NODE >::~node_set_base()
{
   erase_all();
   ASSERT(m_count == 0);
}


template < typename NODE >
typename node_set_base < NODE >::iterator node_set_base < NODE >::new_node(ARG_KEY key)
{

   auto pnode = __raw_new BASE_NODE (key);

   if(this->m_begin)
   {

      this->m_begin.m_p->m_back   = pnode;

   }

   pnode->m_next              = this->m_begin.get();

   this->m_begin              = pnode;

   this->m_begin.m_p->m_back  = nullptr;

   m_count++;

   ASSERT(m_count > 0);  // make sure we don't overflow

   return pnode;

}


template < typename NODE >
void node_set_base < NODE >::free_node(iterator iterator)
{

   auto pnode = iterator.m_p;

   auto next = pnode->m_next;

   if(pnode->m_next != nullptr)
   {

      pnode->m_next->m_back = pnode->m_back;

   }

   if(pnode->m_back != nullptr)
   {

      pnode->m_back->m_next = pnode->m_next;

   }

   if(this->m_begin == pnode)
   {

      this->m_begin = next;

      if(this->m_begin)
      {

         this->m_begin.m_p->m_back = nullptr;

      }

   }

   //__delete(iterator.get());

   delete pnode;

   //iterator->m_next = this->m_pnodeFree;

   //this->m_pnodeFree = iterator;

   m_count--;

   ASSERT(m_count >= 0);  // make sure we don't underflow

   // if no more elements, cleanup completely
   if (m_count == 0)
   {

      erase_all();

   }

}


template < typename NODE >
typename node_set_base < NODE >::iterator
node_set_base < NODE >::find_node(ARG_KEY key, unsigned int& nHashBucket, unsigned int& nHashValue) const
{

   nHashValue = ::as_hash32(key).m_u;

   nHashBucket = nHashValue % m_hashtable.GetHashTableSize();

   if (is_empty())
   {

      return nullptr;

   }

   for(auto p = m_hashtable.m_ppHash[nHashBucket]; p; p = p->m_nextHash)
   {

      if (EqualElements<ARG_KEY>(p->key(), key))
      {

         return p;

      }

   }

   return nullptr;

}


template < typename NODE >
bool node_set_base < NODE >::lookup(ARG_KEY key, PAYLOAD & payload) const
{

   unsigned int nHashBucket, nHashValue;

   auto p = find_node(key, nHashBucket, nHashValue);

   if (!p)
   {

      return false;  // not in set

   }

   payload = p->payload();

   return true;

}


//template < typename NODE >

template < typename NODE >
typename node_set_base < NODE >::const_iterator
node_set_base < NODE >::plookup(ARG_KEY key) const
{

   return ((node_set_base *)this)->plookup(key);

}


template < typename NODE >
typename node_set_base < NODE >::iterator
node_set_base < NODE >::plookup(ARG_KEY key)
{

   auto pnode = find_node(key);

   return pnode;

}


template < typename NODE >
typename node_set_base < NODE >::PAYLOAD *
node_set_base < NODE >::pget(ARG_KEY key)
{

   auto p = plookup(key);

   if (!p)
   {

      return nullptr;

   }
      
   return &p->payload();

}


template < typename NODE >
inline typename node_set_base < NODE >::iterator
node_set_base < NODE >::find_node(ARG_KEY key)
{

   unsigned int nHashBucket, nHashValue;

   auto iterator = ((node_set_base *)this)->find_node(key, nHashBucket, nHashValue);

   return iterator;

}


template < typename NODE >
inline typename node_set_base < NODE >::const_iterator
node_set_base < NODE >::find_node(ARG_KEY key) const
{

   return ((node_set_base *)this)->find_node(key);

}


template < typename NODE >
typename node_set_base < NODE >::iterator
node_set_base < NODE >::get_node(ARG_KEY key)
{

   unsigned int nHashBucket, nHashValue;

   auto iterator = find_node(key, nHashBucket, nHashValue);

   auto pnode = iterator.m_p;

   if(!pnode)
   {

      // not precise (memleak? a watch dog can restart from the last check point... continuable tasks need...) but self-healing(self-recoverable/not-fatal)...
      if (::is_null(m_hashtable.m_ppHash))
      {

         InitHashTable(m_hashtable.GetHashTableSize());

      }

      ENSURE(m_hashtable.m_ppHash);

      auto iteratorNew = new_node(key);

      pnode = iteratorNew.m_p;

      if(m_hashtable.m_ppHash[nHashBucket])
      {

         m_hashtable.m_ppHash[nHashBucket]->m_pbackHash = &pnode->m_nextHash;

      }

      pnode->m_nextHash        = m_hashtable.m_ppHash[nHashBucket];

      m_hashtable.m_ppHash[nHashBucket] = pnode;

      pnode->m_pbackHash       = &m_hashtable.m_ppHash[nHashBucket];

   }

   return pnode;

}


template < typename NODE >
typename node_set_base < NODE >::PAYLOAD & node_set_base < NODE >::operator[](ARG_KEY key)
{

   return get_node(key)->payload();

}


template < typename NODE >
const typename node_set_base < NODE >::PAYLOAD & node_set_base < NODE >::operator[](ARG_KEY key) const
{

   auto p = find_node(key);

   if (!p)
   {

      throw_exception(error_key_not_found);

   }

   return p->payload();

}


template < typename NODE >
inline bool node_set_base < NODE >::erase(iterator iterator)
{

   if(iterator.m_p->m_nextHash != nullptr)
   {

      iterator.m_p->m_nextHash->m_pbackHash = iterator.m_p->m_pbackHash;

   }

   *iterator.m_p->m_pbackHash = iterator.m_p->m_nextHash;

   free_node(iterator.m_p);

   return true;

}


template < typename NODE >
inline ::collection::count node_set_base < NODE >::key_count(ARG_KEY KEY) const
{

   return this->plookup(KEY) ? 1 : 0;

}


template < typename NODE >
bool node_set_base < NODE >::has_key(ARG_KEY KEY) const
{

   return this->plookup(KEY) ? 1 : 0;

}


template < typename NODE >
bool node_set_base < NODE >::contains_key(ARG_KEY KEY) const
{

   return this->plookup(KEY) ? 1 : 0;

}


//template < typename NODE >
//void node_set_base < NODE >::get_next(iterator & iterator,
//      KEY& rKey, KEY& payload) const
//{
//
//   rKey = iterator->KEY();
//
//   payload = iterator->KEY();
//
//   iterator = iterator->m_next;
//
//}
//
//
//template < typename NODE >
//inline const typename node_set_base < NODE >::iterator
//node_set_base < NODE >::get_next(const iterator iterator) const
//{
//
//   return iterator->m_next;
//
//}
//
//
//template < typename NODE >
//inline typename node_set_base < NODE >::iterator
//node_set_base < NODE >::get_next(const iterator iterator)
//{
//
//   return iterator->m_next;
//
//}


template < typename NODE >
typename node_set_base < NODE >::PAYLOAD node_set_base < NODE > ::get(ARG_KEY key, ARG_PAYLOAD payloadDefault)
{
   
   auto p = plookup(key);

   if (!p)
   {

      return payloadDefault;

   }

   return p->payload();

}


//template < typename NODE >
//void node_set_base < NODE >::assert_ok() const
//{
//
//   ::matter::assert_ok();
//
//   ASSERT(GetHashTableSize() > 0);
//
//   ASSERT(m_count == 0 || m_hashtable.m_ppHash != nullptr);
//   // non-empty set should have hash table
//
//}
//

using double_set = set < double >;

using dword_set = set < unsigned int >;

using uptr_set = set < ::uptr >;

//template < typename KEY_TYPE >
//class KEY
//{
//
//
//   using KEY = KEY_TYPE;
//   using TYPE = KEY;
//   using ARG_TYPE = argument_of < KEY & >;
//
//
//   // Contract
//   // KEY & KEY();
//   // KEY & KEY();
//   // ARG_KEY KEY() const;
//   // ARG_KEY KEY() const;
//
//};


template < typename NODE >
using key_set = node_set_base < NODE >;


#define __declare_key(xkeytype, xkey) \
struct xkeytype : public ::KEY < xkeytype > \
{ \
\
   PAIR_DEFAULT_IMPL(xkeytype, KEY, ARG_KEY, xkey); \
   KEY & KEY() { return xkey; } \
   ARG_KEY KEY() const { return xkey; } \
}


#ifdef CPP17
#define __declare_key_tuple_size(KEY) \
template<> ALIENATED_ANDROID_ANARCHY ::std::tuple_size< KEY > : ::std::integral_constant<size_t, 1> {} }
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


using iptr_set = set < iptr >;

using index_set = set < ::collection::index >;

using string_set = set < string >;




//#pragma once


template < typename NODE >
void node_set_base < NODE >::InitHashTable(
   unsigned int nHashSize, bool bAllocNow)
//
// Used to force allocation of a hash table or to override the default
//   hash table int_size of (which is fairly small)
{

   //ASSERT_OK(this);
   ASSERT(this->m_count == 0);
   ASSERT(nHashSize > 0);

   this->m_hashtable.InitHashTable(nHashSize,bAllocNow);

}


template < typename NODE >
inline bool node_set_base < NODE >::unhash(iterator iterator)
// erase - return true if erased
{

   if(::is_set(iterator.m_p->m_nextHash))
   {

      iterator.m_p->m_nextHash->m_pbackHash = iterator.m_p->m_pbackHash;

   }

   *iterator.m_p->m_pbackHash = iterator.m_p->m_nextHash;

   return true;

}


template < typename ITEM >
void node_set_base < ITEM >::transfer(node_set_base* pnodesetbase, ARG_KEY key)
{

   unsigned int uHashBucket;

   unsigned int uHashValue;

   auto pnode = pnodesetbase->find_node(key, uHashBucket, uHashValue);

   if (pnode)
   {

      pnodesetbase->detach(pnode);

      attach(pnode, uHashBucket, uHashValue);

   }

}


template < typename ITEM >
void node_set_base < ITEM >::transfer(iterator iterator, node_set_base * pnodesetbase)
{

   if (pnodesetbase == this)
   {

      return;

   }

   if (::is_set(pnodesetbase))
   {

      pnodesetbase->detach(iterator);

   }

   unsigned int nHashBucket;

   unsigned int nHashValue;

   hash(nHashBucket, nHashValue, iterator->key());

   attach(iterator, nHashBucket, nHashValue);

}



template < typename ITEM >
void node_set_base < ITEM >::attach(iterator iterator, unsigned int nHashBucket, unsigned int nHashValue)
{

   hash(iterator, nHashBucket, nHashValue);

   auto pnode = iterator.m_p;

   if (this->m_begin)
   {

      this->m_begin.m_p->m_back = pnode;

   }

   pnode->m_next = this->begin().m_p;

   this->begin() = pnode;

   this->begin().m_p->m_back = nullptr;

   this->m_count++;

   ASSERT(this->m_count > 0);  // make sure we don't overflow

}


template < typename ITEM >
void node_set_base < ITEM >::hash(iterator iterator, unsigned int nHashBucket, unsigned int nHashValue)
{

   auto pnode = iterator.m_p;

   // not precise (memleak? a watch dog can restart from the last check point... continuable tasks need...) but self-healing(self-recoverable/not-fatal)...
   if (::is_null(this->m_hashtable.m_ppHash))
   {

      InitHashTable(this->m_hashtable.GetHashTableSize());

   }

   if (::is_set(this->m_hashtable.m_ppHash[nHashBucket]))
   {

      this->m_hashtable.m_ppHash[nHashBucket]->m_pbackHash = &pnode->m_nextHash;

   }

   pnode->m_nextHash = this->m_hashtable.m_ppHash[nHashBucket];

   this->m_hashtable.m_ppHash[nHashBucket] = pnode;

   pnode->m_pbackHash = &this->m_hashtable.m_ppHash[nHashBucket];

}


template < typename ITEM >
void node_set_base < ITEM >::hash(unsigned int& nHashBucket, unsigned int& nHashValue, ARG_KEY key) const
{

   nHashValue = ::as_hash32(key).m_u;

   nHashBucket = nHashValue % this->m_hashtable.GetHashTableSize();

}


template < typename ITEM >
void node_set_base < ITEM >::detach(iterator iterator)
{

   auto pnode = iterator.m_p;

   this->unhash(iterator);

   auto next = pnode->m_next;

   if (::is_set(pnode->m_next))
   {

      pnode->m_next->m_back = pnode->m_back;

   }

   if (::is_set(pnode->m_back))
   {

      pnode->m_back->m_next = pnode->m_next;

   }

   if (this->m_begin == pnode)
   {

      this->m_begin = next;

      if (::is_set(this->m_begin))
      {

         this->m_begin.m_p->m_back = nullptr;

      }

   }

   //delete iterator;

   //iterator->m_next = this->m_pnodeFree;

   //this->m_pnodeFree = iterator;

   this->m_count--;

   ASSERT(this->m_count >= 0);  // make sure we don't underflow

   // if no more elements, cleanup completely
   if (this->m_count == 0)
   {

      this->erase_all();

   }

}


