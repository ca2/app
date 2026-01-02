#pragma once


#include "set.h"
#include "acme/prototype/comparison/equals.h"


template < typename PAIR, enum_allocate t_eallocate >
class pair_map_base :
   public ::node_set_base < ::make_pair < PAIR >, t_eallocate >
{
public:
   //
   //
   using BASE_PAIR_MAP = ::node_set_base < ::make_pair < PAIR >, t_eallocate >;
   //
   //
   // using HASH_TABLE = typename BASE_PAIR_MAP::HASH_TABLE;
   // using KEY = typename ::make_pair < PAIR >::KEY;
   // using PAYLOAD = typename ::make_pair < PAIR >::PAYLOAD;
   // using ARG_KEY = typename ::make_pair < PAIR >::ARG_KEY;
   // using ARG_PAYLOAD = typename ::make_pair < PAIR >::ARG_PAYLOAD;
   //
   //
   // using BASE_NODE = typename BASE_PAIR_MAP::BASE_NODE;
   // using ITEM = typename BASE_PAIR_MAP::ITEM;
   //
   using iterator = typename BASE_PAIR_MAP::iterator;
   // using const_iterator = typename BASE_PAIR_MAP::const_iterator;
   //
   // using item_iterator = ::element1_list_iterator < BASE_NODE * >;
   // using payload_iterator = ::element2_list_iterator < BASE_NODE * >;
   // using const_item_iterator = typename item_iterator::const_iterator;
   // using const_payload_iterator = typename payload_iterator::const_iterator;


   //using iterator_struct = BASE_SET::iterator_struct;
   //using const_iterator_struct = BASE_SET::const_iterator_struct;
   //using key_iterator = BASE_SET::key_iterator;
   //using iterator = BASE_SET::iterator;
   //using const_iterator = BASE_SET::const_iterator;
   //sing make_iterator = BASE_SET::make_iterator;

   //__declare_iterator_struct_ok(pair_map_base, iterator, m_pnode, ::is_set(this->m_pnode));


   //using BASE_PAIR_MAP = ::node_set_base < ::make_pair < PAIR > >;

   using BASE_PAIR_MAP::BASE_PAIR_MAP;
   using BASE_PAIR_MAP::operator =;


   void pair_map_base_ok() const
   {

      BASE_PAIR_MAP::container_ok();

   }


   void container_ok() const
   {

      pair_map_base_ok();

   }


   template < typename STRING >
   iterator case_insensitive_find_key_containing(const STRING & str) const
   {

      auto iterator = this->begin();

      while (iterator)
      {

         if (iterator->element1().case_insensitive_contains(str))
         {

            return iterator;

         }

         ++iterator;

      }

      return nullptr;

   }



//    void assert_container_ok() const;
//
//
//    pair_map_base();
//    pair_map_base(const PAIR * iterator, ::collection::count c);
//    pair_map_base(const ::std::initializer_list < PAIR > & list_base);
//    pair_map_base(const pair_map_base & m);
//    ~pair_map_base();
//
//    void construct();
//
//
//    ::collection::count get_count() const;
//    ::collection::count get_size() const;
//    ::collection::count size() const;
//    ::collection::count count() const;
//    bool is_empty() const;
//    bool empty() const;
//
//
//
//    //find
//    //bool find(ARG_KEY key, PAYLOAD& rValue) const;
//    //const_iterator find(ARG_KEY key) const;
//    //iterator find(ARG_KEY key);
//
//
//    //PAYLOAD * defer_get(ARG_KEY key);
//
//
//    //inline typename pair_map_base < PAIR >::iterator get_item(ARG_KEY key);
//
//
//    template < typename TITEM >
//    auto pop(const TITEM & key)
//    {
//
//       auto value = operator[](key);
//
//       this->erase_item(key);
//
//       return value;
//
//    }
//
//    //Operations
//    //find and add if not there
//    inline PAYLOAD & operator[](ARG_KEY key);
//    inline const PAYLOAD & operator[](ARG_KEY key) const;
//
//    template < typename PAYLOAD2 >
//    iterator find_payload(const PAYLOAD2 & payload) const;
//
//    //add a øallocate<  >(key, value) node
//    iterator set_at(ARG_KEY key, ARG_PAYLOAD newValue)
//    {
//
//       auto p = this->get_node(key);
//
//       p->payload() = newValue;
//
//       return p;
//
//    }
//
//
//    //add a øallocate<  >(key, value) node
//    void set_pair(const PAIR & pair)
//    {
//
//       set_at((ARG_KEY) pair.element1(), (ARG_PAYLOAD) pair.element2());
//
//    }
//
//
//    //bool unhash(iterator iterator);
//
//    //removing existing (key, ?) node
//    //inline bool erase_item(ARG_KEY key) { auto p = this->find_item(key);  return p ? this->erase(p) : false; }
//
//    template < typename PAYLOAD2 >
//    inline bool erase_payload(const PAYLOAD2 payload) { auto p = find_payload(payload);  return p ? erase(p) : false; }
//
//
//
//    inline auto items() { return ::range<item_iterator>(*(item_iterator *)&this->begin(), *(item_iterator *)&this->end()); }
//    inline auto payloads() { return ::range<payload_iterator>(*(payload_iterator *)&this->begin(), *(payload_iterator *)&this->end()); }
//    inline auto items() const { return ::range<const_item_iterator>((item_iterator)this->begin(), (item_iterator)this->end()); }
//    inline auto payloads() const { return ::range<const_payload_iterator>((payload_iterator )this->begin(), (payload_iterator)this->end()); }
//    ::collection::count key_count(ARG_KEY key) const;
//    bool has_key(ARG_KEY key) const;
//    bool contains_key(ARG_KEY key) const;
//
//    //iterating all (key, value) pairs
// //   POSITION get_start_position() const;
//
//    //inline const iterator get_start() const;
//    //inline iterator get_start();
//
//    //void get_next(iterator & rNextPosition, ITEM& rKey, PAYLOAD& rValue) const;
//
//    //const iterator get_next(const iteratorpnodeRet) const;
//    //iterator get_next(const iteratorpnodeRet);
//
//    //advanced features for derived classes
//    unsigned int GetHashTableSize() const
//    {
//
//       return this->m_hashtable.GetHashTableSize();
//
//    }
//
//
//    void InitHashTable(unsigned int hashSize,bool bAllocNow = true);
//
//
//    PAYLOAD get(ARG_KEY key, ARG_PAYLOAD valueDefault);
//
//
//
//    void set(pair_map_base & pair_map_base)
//    {
//
//       for(auto & pair : pair_map_base)
//       {
//
//          set_at(pair.element1(), pair.element2());
//
//       }
//
//    }
//
//
//    //inline iterator find_item(ARG_KEY key) const { return find_node(key); }
//
//    //using BASE_SET::find_item;
//    //inline const_iterator find_item(ARG_KEY key) const { return ((pair_map_base *) this)->find_item(key); }
//
//
//    //BASE_NODE * new_node(ARG_KEY key, unsigned int nHashBucket, unsigned int nHashValue);
//    //inline void hash(BASE_NODE *, unsigned int nHashBucket, unsigned int nHashValue);
//    //void attach(iterator iterator, unsigned int nHashBucket, unsigned int nHashValue);
//    //bool erase(iterator iterator);
//    //void detach(iterator iterator);
//    //void hash(unsigned int& nHashBucket, unsigned int& nHashValue, ARG_KEY) const;
//    //inline iterator node_at(ARG_KEY, unsigned int & nHashBucket, unsigned int & nHashValue) const;
//    //inline const_iterator node_at(ARG_KEY, unsigned int& nHashBucket, unsigned int& nHashValue) const;
//
//    // void transfer(iterator iterator, pair_map_base * iterator_map = nullptr);
//    // void transfer(pair_map_base* iterator_map, ARG_KEY key);
//
//    //// void assert_ok() const override;
//    //// void dump(dump_context & dumpcontext) const override;
//
//
//    template < class ARRAY >
//    bool erase_key_array(ARRAY a)
//    {
//
//       bool bRemoved = false;
//
//       for(::collection::index i = 0; i < a.get_count(); i++)
//       {
//
//          bRemoved |= erase_key(a[i]);
//
//       }
//
//       return bRemoved;
//
//    }
//
//
//    template < class ARRAY >
//    ::collection::count erase_node_array(ARRAY a)
//    {
//
//       ::collection::count countRemoved = 0;
//
//       for(::collection::index i = 0; i < a.get_count(); i++)
//       {
//
//          if(erase_node(a[i]))
//          {
//
//             countRemoved++;
//
//          }
//
//       }
//
//       return countRemoved;
//
//    }
//
//    //virtual void on_after_read() override {}
//
//
//    //PAIR & element_at(::collection::index iIndex)
//    //{
//    //   return this->elements().element_at(iIndex);
//    //}
//
//    template < typename PRED >
//    typename pair_map_base < PAIR >::iterator predicate_find(PRED pred)
//    {
//
//       auto p = this->begin();
//
//       while (::is_ok(p))
//       {
//
//          if (pred(p))
//          {
//
//             return p;
//
//          }
//
//          p++;
//
//       }
//
//       return nullptr;
//
//    }
//
//    pair_map_base & operator = (const pair_map_base & m);
//
//
//    template < typename TYPE >
//    ::pointer<TYPE>get_typed_ptr(::collection::index i = 0)
//    {
//
//       ::pointer<TYPE>p;
//
//      for(auto & node : *this)
//      {
//
//          p = (*node).element2();
//
//          if(p)
//          {
//
//              if(i <= 0)
//              {
//
//                  return p;
//
//              }
//
//              i--;
//
//          }
//
//      }
//
//      return nullptr;
//
//    }


};

//
// template < typename PAIR >
// inline ::collection::count pair_map_base < PAIR >::get_count() const
// {
//    return this->m_count;
// }
//
// template < typename PAIR >
// inline ::collection::count pair_map_base < PAIR >::get_size() const
// {
//    return this->m_count;
// }
//
// template < typename PAIR >
// inline ::collection::count pair_map_base < PAIR >::count() const
// {
//    return this->m_count;
// }
//
// template < typename PAIR >
// inline ::collection::count pair_map_base < PAIR >::size() const
// {
//    return this->m_count;
// }
//
// template < typename PAIR >
// pair_map_base < PAIR > & pair_map_base < PAIR >::operator = (const pair_map_base & m)
// {
//    if(this != &m)
//    {
//
//       this->erase_all();
//
//       for(auto & node : m)
//       {
//
//          set_at((ARG_KEY) node.element1(), (ARG_PAYLOAD) node.element2());
//
//       }
//
//    }
//    return *this;
// }
//
//
// template < typename PAIR >
// inline bool pair_map_base < PAIR >::is_empty() const
// {
//
//    return this->m_count == 0;
//
// }
//
//
// template < typename PAIR >
// inline bool pair_map_base < PAIR >::empty() const
// {
//
//    return this->m_count == 0;
//
// }


//template < typename PAIR >
//typename pair_map_base < PAIR >::iterator pair_map_base < PAIR >::set_at(ARG_KEY key,ARG_PAYLOAD newValue)


//template < typename PAIR >
//inline typename pair_map_base < PAIR >::iterator pair_map_base < PAIR >::get_start() const
//{
//   return (this->m_count == 0) ? nullptr : BEFORE_START_POSITION;
//}

//
//
// /////////////////////////////////////////////////////////////////////////////
// // pair_map_base < PAIR > out-of-line functions
// template < typename PAIR >
// void pair_map_base < PAIR >::construct()
// {
//
//    this->m_count          = 0;
//
//    this->m_begin      = nullptr;
//
//    this->m_end = nullptr;
//
// }
//
//
// template < typename PAIR >
// pair_map_base < PAIR >::pair_map_base()
// {
//
//    construct();
//
// }
//
//
// template < typename PAIR >
// pair_map_base < PAIR >::pair_map_base(const ::std::initializer_list < PAIR > & list_base)
// {
//
//    construct();
//
//    for(auto & pair : list_base)
//    {
//
//       set_at((ARG_KEY) pair.element1(), (ARG_PAYLOAD) pair.element2());
//
//    }
//
// }
//
// template < typename PAIR >
// pair_map_base < PAIR >::pair_map_base(const PAIR * iterator, ::collection::count c)
// {
//    construct();
//    for(::collection::index i = 0; i < c; i++)
//    {
//       set_at((ARG_KEY) iterator[i].element1(), (ARG_PAYLOAD) iterator[i].element2());
//    }
// }
//
//
// template < typename PAIR >
// pair_map_base < PAIR >::pair_map_base(const pair_map_base & m)
// {
//
//    construct();
//
//    for(auto & pair : m)
//    {
//
//       set_at((ARG_KEY) pair.element1(), (ARG_PAYLOAD) pair.element2());
//
//    }
//
// }

//template < typename PAIR >
//inline void pair_map_base < PAIR >::clear()
//{
//   erase_all();
//}
//
//template < typename PAIR >
//inline void pair_map_base < PAIR >::Empty()
//{
//   clear();
//}
//
// template < typename PAIR >
// pair_map_base < PAIR >::~pair_map_base()
// {
//    this->erase_all();
//    ASSERT(this->m_count == 0);
// }
//

// template < typename PAIR >
// void pair_map_base < PAIR >::attach(iterator p, unsigned int nHashBucket, unsigned int nHashValue)
// {
//
//    hash(p, nHashBucket, nHashValue);
//
//    if (this->m_begin)
//    {
//
//       this->m_begin.back() = p.get();
//
//    }
//
//    p.next() = this->begin().get();
//
//    this->begin() = p;
//
//    this->begin().back() = nullptr;
//
//    this->m_count++;
//
//    ASSERT(this->m_count > 0);  // make sure we don't overflow
//
// }
//


//
// template < typename PAIR >
// inline void pair_map_base < PAIR >::hash(iterator p, unsigned int nHashBucket, unsigned int nHashValue)
// {
//
//    // not precise (memleak? a watch dog can restart from the last check point... continuable tasks need...) but self-healing(self-recoverable/not-fatal)...
//    if (::is_null(this->m_hashtable.m_ppHash))
//    {
//
//       InitHashTable(this->m_hashtable.GetHashTableSize());
//
//    }
//
//    if (::is_set(this->m_hashtable.m_ppHash[nHashBucket]))
//    {
//
//       this->m_hashtable.m_ppHash[nHashBucket]->m_pbackHash = &p.m_p->m_nextHash;
//
//    }
//
//    p.m_p->m_nextHash = this->m_hashtable.m_ppHash[nHashBucket];
//
//    this->m_hashtable.m_ppHash[nHashBucket] = p.m_p;
//
//    p.m_p->m_pbackHash = &this->m_hashtable.m_ppHash[nHashBucket];
//
// }
//
//
// template < typename PAIR >
// typename pair_map_base < PAIR >::iterator
// pair_map_base < PAIR >::new_node(ARG_KEY key, unsigned int nHashBucket, unsigned int nHashValue)
// {
//
//    //if(this->m_pnodeFree == nullptr)
//    //{
//    //   // add another block
//    //   //plex * newBlock = plex::create(m_pplex, m_nBlockSize, sizeof(pair_map_base::node));
//    //   //// chain them into free list_base
//    //   //pair_map_base::iterator iterator = (pair_map_base::iterator) newBlock->data();
//    //   //// free in reverse order to make it easier to debug
//    //   //::collection::index i = m_nBlockSize - 1;
//    //   //for (iterator = &iterator[i]; i >= 0; i--, iterator--)
//    //   //{
//    //   //   iterator->m_next = this->m_pnodeFree;
//    //   //   this->m_pnodeFree = iterator;
//
//    //   //}
//    //   this->m_pnodeFree = ___new node();
//
//    //}
//
//    //ENSURE(this->m_pnodeFree != nullptr);  // we must have something
//
//    auto p = øraw_new BASE_NODE (key);
//
//    attach(p, nHashBucket, nHashValue);
//
//    return p;
//
// }
//
//
// template < typename PAIR >
// bool pair_map_base < PAIR >::erase(iterator iterator)
// {
//
//    detach(iterator);
//
//    delete iterator.get();
//
//    return true;
//
// }
//
//
// template < typename PAIR >
// void pair_map_base < PAIR >::detach(iterator iterator)
// {
//
//    this->unhash(iterator);
//
//    auto next = iterator->m_next;
//
//    if (::is_set(iterator->m_next))
//    {
//
//       iterator->m_next->m_back = iterator->m_back;
//
//    }
//
//    if (::is_set(iterator->m_back))
//    {
//
//       iterator->m_back->m_next = iterator->m_next;
//
//    }
//
//    if (this->m_begin == iterator)
//    {
//
//       this->m_begin = next;
//
//       if (::is_set(this->m_begin))
//       {
//
//          this->m_begin->m_back = nullptr;
//
//       }
//
//    }
//
//    //delete iterator;
//
//    //iterator->m_next = this->m_pnodeFree;
//
//    //this->m_pnodeFree = iterator;
//
//    this->m_count--;
//
//    ASSERT(this->m_count >= 0);  // make sure we don't underflow
//
//    // if no more elements, cleanup completely
//    if (this->m_count == 0)
//    {
//
//       this->erase_all();
//
//    }
//
// }
//
// template < typename PAIR >
// void pair_map_base < PAIR >::hash(unsigned int& nHashBucket, unsigned int& nHashValue, ARG_KEY key) const
// {
//
//    nHashValue = ::as_hash32(key).m_u;
//
//    nHashBucket = nHashValue % this->m_hashtable.GetHashTableSize();
//
// }
//
// //template < typename PAIR >
// //inline typename pair_map_base < PAIR >::const_iterator
// //pair_map_base < PAIR >::node_at(ARG_KEY key, unsigned int & nHashBucket, unsigned int & nHashValue) const
// //{
// //
// //   return (const_iterator &) ((pair_map_base *)this)->node_at(key, nHashBucket, nHashValue);
// //
// //}
//
//
// template < typename PAIR >
// inline typename pair_map_base < PAIR >::iterator
// pair_map_base < PAIR >::node_at(ARG_KEY key, unsigned int& nHashBucket, unsigned int& nHashValue) const
// {
//
//    hash(nHashBucket, nHashValue, key);
//
//    if (get_count() <= 0)
//    {
//
//       return nullptr;
//
//    }
//
//    for(auto p = this->m_hashtable.m_ppHash[nHashBucket]; p; p = p->m_nextHash)
//    {
//
//       if (EqualElements<ARG_KEY>(p->key(), key))
//       {
//
//          return p;
//
//       }
//
//    }
//
//    return nullptr;
//
// }
//
// template < typename PAIR >
// void pair_map_base < PAIR >::transfer(pair_map_base* iterator_map, ARG_KEY key)
// {
//
//    unsigned int uHashBucket;
//
//    unsigned int uHashValue;
//
//    auto iterator = iterator_map->node_at(key, uHashBucket, uHashValue);
//
//    iterator_map->detach(iterator);
//
//    attach(iterator, uHashBucket, uHashValue);
//
// }
//
//
//
// template < typename PAIR >
// void pair_map_base < PAIR >::transfer(iterator iterator, pair_map_base * iterator_map)
// {
//
//    if (iterator_map == this)
//    {
//
//       return;
//
//    }
//
//    if (::is_set(iterator_map))
//    {
//
//       iterator_map->detach(iterator);
//
//    }
//
//    unsigned int nHashBucket;
//
//    unsigned int nHashValue;
//
//    hash(nHashBucket, nHashValue, iterator->element1());
//
//    attach(iterator, nHashBucket, nHashValue);
//
// }
//
//
// template < typename PAIR >
// bool pair_map_base < PAIR >::find(ARG_KEY key, PAYLOAD& rValue) const
// {
//
//    auto pnode = this->find_node(key);
//
//    if (!pnode)
//    {
//
//       return false;  // not in pair_map_base
//
//    }
//
//    rValue = pnode->element2();
//
//    return true;
//
// }
// template < typename PAIR >
// template < typename PAYLOAD2 >
// inline typename pair_map_base < PAIR >::iterator pair_map_base < PAIR >::find_payload(const PAYLOAD2 & payload) const
// {
//
//    auto p = this->begin();
//
//    while(p != this->end())
//    {
//
//       if(p->payload() == payload)
//       {
//
//          return p;
//
//       }
//
//    }
//
//    return nullptr;
//
// }


// template < typename PAIR >
// inline typename pair_map_base < PAIR >::iterator pair_map_base < PAIR >::get_item(ARG_KEY key)
// {
//
//    unsigned int nHashBucket,nHashValue;
//
//    iterator p;
//
//    if(!(p = node_at(key,nHashBucket,nHashValue)))
//    {
//
//       p = this->new_node(key, nHashBucket, nHashValue);
//
//    }
//
//    return p;
//
// }

//
// template < typename PAIR >
// inline typename pair_map_base < PAIR >::PAYLOAD & pair_map_base < PAIR >::operator[](ARG_KEY key)
// {
//
//    return this->get_node(key)->element2();
//
// }
//
//
// template < typename PAIR >
// inline const typename pair_map_base < PAIR >::PAYLOAD & pair_map_base < PAIR >::operator[](ARG_KEY key) const
// {
//
//    auto pnode = this->find_node(key);
//
//    if(!pnode)
//    {
//
//       throw_exception(error_wrong_state);
//
//    }
//
//    return (const PAYLOAD &) pnode->payload();
//
// }
//
//
// template < typename PAIR >
// inline ::collection::count pair_map_base < PAIR >::key_count(ARG_KEY key) const
// {
//
//    return this->find(key) ? 1 : 0;
//
// }
//
//
// template < typename PAIR >
// bool pair_map_base < PAIR >::has_key(ARG_KEY key) const
// {
//
//    return this->find(key) ? 1 : 0;
//
// }
//
//
// template < typename PAIR >
// bool pair_map_base < PAIR >::contains_key(ARG_KEY key) const
// {
//
//    return this->find(key) ? 1 : 0;
//
// }
//

//template < typename PAIR >
//void pair_map_base < PAIR >::get_next(iterator & iterator,
//      ITEM& rKey, PAYLOAD& rValue) const
//{
//
//   rKey = iterator->element1();
//
//   rValue = iterator->element2();
//
//   iterator = iterator->m_next;
//
//}
//
//
//template < typename PAIR >
//inline const typename pair_map_base < PAIR >::iterator
//pair_map_base < PAIR >::get_next(const iterator iterator) const
//{
//
//   return iterator->m_next;
//
//}

//
//template < typename PAIR >
//inline typename pair_map_base < PAIR >::iterator
//pair_map_base < PAIR >::get_next(const iterator iterator)
//{
//
//   return iterator->m_next;
//
//}
//
//
// template < typename PAIR >
// typename pair_map_base < PAIR >::PAYLOAD pair_map_base < PAIR > ::
// get(ARG_KEY argkey, ARG_PAYLOAD valueDefault)
// {
//
//    auto p = find(argkey);
//
//    if(!p)
//    {
//
//       return valueDefault;
//
//    }
//
//    return p->payload();
//
// }


//template < typename PAIR >
//void pair_map_base < PAIR >::assert_ok() const
//{
//
//   ::matter::assert_ok();
//
//   ASSERT(GetHashTableSize() > 0);
//
//   ASSERT(this->m_count == 0 || this->m_hashtable.m_ppHash != nullptr);
//   // non-empty pair_map_base should have hash table
//
//}
//


template < class PAYLOAD >
using double_map_base = map_base < double, PAYLOAD >;

template < class PAYLOAD >
using double_map = map_particle < double_map_base < PAYLOAD > >;

using double_to_double_base = double_map_base < double >;


template < class PAYLOAD >
using dword_map = map_base < unsigned int, PAYLOAD >;


template < class PAYLOAD >
using uptr_map = map_base < uptr, PAYLOAD >;


template < typename ITEM_TYPE, typename PAYLOAD_TYPE >
class key_payload
{
public:


   using ITEM = ITEM_TYPE;
   using PAYLOAD = PAYLOAD_TYPE;
   using TYPE1 = ITEM;
   using TYPE2 = PAYLOAD;
   using ARG_TYPE1 = argument_of < TYPE1 >;
   using ARG_TYPE2 = argument_of < TYPE2 >;


   // Contract
   // ITEM & element1();
   // PAYLOAD & element2();
   // ARG_KEY element1() const;
   // const PAYLOAD & element2() const;

};


//template < typename PAIR >
//using pair_pair_map = pair_map_base <  typename PAIR::TYPE1, typename PAIR::TYPE2 >;


#define __declare_key_value(xkeyvaluetype, xkeytype, xkey, xvaluetype, xvalue) \
struct xkeyvaluetype : public ::key_payload < xkeytype, xvaluetype > \
{ \
\
   PAIR_DEFAULT_IMPL(xkeyvaluetype, ITEM, PAYLOAD, const ITEM &, const PAYLOAD &, xkey, xvalue); \
}


#ifdef CPP17
#define __declare_pair_tuple_size(pair) \
template<> ALIENATED_ANDROID_ANARCHY ::std::tuple_size< pair > : ::std::integral_constant<size_t, 2> {} }
#endif


#define __declare_pair_map(xpair_maptype, xkeyvaluetype, xkeytype, xkey, xvaluetype, xvalue) \
__declare_key_value(xkeyvaluetype, xkeytype, xkey, xvaluetype, xvalue); \
using xpair_maptype = pair_pair_map < xkeyvaluetype >


#ifdef CPP17
#define __declare_pair_map_key_value(xpair_maptype, xkeyvaluetype, xkeytype, xkey, xvaluetype, xvalue) \
__declare_pair_map(xkeyvaluetype, xkeytype, xkey, xvaluetype, xvalue); \
__declare_pair_tuple_size(xpair_maptype)
#else

#define __declare_pair_map_key_value(xpair_maptype, xkeyvaluetype, xkeytype, xkey, xvaluetype, xvalue) \
__declare_pair_map(xkeyvaluetype, xkeytype, xkey, xvaluetype, xvalue);

#endif

//
//
// template < typename PAIR >
// void pair_map_base < PAIR >::InitHashTable(
//    unsigned int nHashSize, bool bAllocNow)
// //
// // Used to force allocation of a hash table or to override the default
// //   hash table int_size of (which is fairly small)
// {
//
//    //ASSERT_OK(this);
//    ASSERT(this->m_count == 0);
//    ASSERT(nHashSize > 0);
//
//    this->m_hashtable.InitHashTable(nHashSize,bAllocNow);
//
// }
//

//template < typename PAIR >
//void pair_map_base < PAIR >::dump(dump_context& dumpcontext) const
//{
//
//   ::matter::dump(dumpcontext);
//
//   //dumpcontext << "with " << this->m_count << " elements";
//   //if (dumpcontext.GetDepth() > 0)
//   //{
//   //   // Dump in format "[key] -> value"
//
//   //   const iterator iterator = get_start();
//   //   while (iterator != nullptr)
//   //   {
//   //      iterator = get_next(iterator);
//   //      dumpcontext << "\n\t[";
//   //      dump_elements<ITEM>(dumpcontext, &iterator->element1(), 1);
//   //      dumpcontext << "] = ";
//   //      dump_elements<PAYLOAD>(dumpcontext, &iterator->element2(), 1);
//   //   }
//   //}
//
//   //dumpcontext << "\n";
//}
//
//


template<typename MAP_BASE>
class map_particle :
   virtual public ::particle, 
   public MAP_BASE
{
public:


   using BASE_MAP = MAP_BASE;


   using BASE_MAP::BASE_MAP;
   using BASE_MAP::operator =;


};



