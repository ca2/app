#pragma once


#include "set.h"
#include "acme/primitive/comparison/equals.h"


template < typename PAIR >
class pair_map :
   public ::node_set < ::make_pair < PAIR > >
{
public:


   using ITEM = typename ::make_pair < PAIR >::TYPE1;
   using PAYLOAD = typename ::make_pair < PAIR >::TYPE2;
   using BASE_SET = typename ::node_set < ::make_pair < PAIR > >;
   using HASH_TABLE = typename BASE_SET::HASH_TABLE;
   using BASE_ITEM = typename ::make_pair < PAIR >::TYPE1;
   using BASE_PAYLOAD = typename ::make_pair < PAIR >::TYPE2;
   using ARG_ITEM = typename ::make_pair < PAIR >::ARG_TYPE1;
   using ARG_PAYLOAD = typename ::make_pair < PAIR >::ARG_TYPE2;
   

   using node = typename BASE_SET::node;
   using pair = typename node::node;

   using iterator = typename BASE_SET::iterator;
   using const_iterator = typename BASE_SET::const_iterator;

   using key_iterator = ::element1_list_iterator < node * >;
   using value_iterator = ::element2_list_iterator < node * >;
   using const_key_iterator = typename key_iterator::const_iterator;
   using const_value_iterator = typename value_iterator::const_iterator;


   //using iterator_struct = BASE_SET::iterator_struct;
   //using const_iterator_struct = BASE_SET::const_iterator_struct;
   //using key_iterator = BASE_SET::key_iterator;
   //using iterator = BASE_SET::iterator;
   //using const_iterator = BASE_SET::const_iterator;
   //sing make_iterator = BASE_SET::make_iterator;

   //__declare_iterator_struct_ok(pair_map, iterator, m_pnode, ::is_set(this->m_pnode));


//   template < typename ITERATOR > 
//   struct make_iterator : public ITERATOR
//   {
//
//
//
//      using CONTAINER = typename ITERATOR::CONTAINER;
//
//      using ITERATOR::ITERATOR;
//
//      make_iterator()
//      {
//         this->m_pnode = (iterator)nullptr;
//         this->m_pcontainer = (CONTAINER*)nullptr;
//         this->m_pnodeBeg = (iterator)nullptr;
//         this->m_pnodeEnd = (iterator) nullptr;
//      }
//
//      make_iterator(const iterator iterator, const CONTAINER* pset = nullptr)
//      {
//         this->m_pnode = (iterator)iterator;
//         this->m_pcontainer = (CONTAINER*)pset;
//         this->m_pnodeBeg = (iterator)iterator;
//         this->m_pnodeEnd = (iterator) nullptr;
//      }
//
//
//      make_iterator(const make_iterator& iterator)
//      {
//         this->m_pnode = iterator.m_pnode;
//         this->m_pcontainer = iterator.m_pcontainer;
//         this->m_pnodeBeg = (iterator)iterator.m_pnodeBeg;
//         this->m_pnodeEnd = (iterator)iterator.m_pnodeEnd;
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
//      make_iterator& operator ++ ()
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
//      bool operator == (const make_iterator& it) const
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
//      bool operator != (const make_iterator& it) const
//      {
//
//         return !operator == (it);
//
//      }
//
//
//      make_iterator& operator = (const make_iterator& it)
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
//   __declare_iterator(dereferenced_value_iterator, this->m_pnode->element2());
//   __declare_iterator(value_iterator, &this->m_pnode->element2());
//   __declare_iterator(key_iterator, &this->m_pnode->element1());
//   __declare_iterator(iterator, this->m_pnode);


   //using deferenced_iterator = dereferenced_value_iterator;


   //HASH_TABLE           this->m_hashtable;
   //::count              this->m_nCount;
   //iterator              m_begin;


   pair_map();
   pair_map(node pairs[], i32 iCount);
   pair_map(const ::std::initializer_list < PAIR > & list);
   pair_map(const pair_map & m);
   ~pair_map();

   void construct();

   ::count get_count() const;
   ::count get_size() const;
   ::count size() const;
   ::count count() const;
   bool is_empty() const;
   bool empty() const;


   //inline iterator begin() { return iterator(get_start(), this); }
   //inline iterator end() { return iterator(nullptr, this); }


   //inline const_iterator begin() const { return ; }
   //inline const_iterator end() const { return {}; }


   //lookup
   bool lookup(ARG_ITEM item, PAYLOAD& rValue) const;
   const_iterator plookup(ARG_ITEM item) const;
   iterator plookup(ARG_ITEM item);

   
   PAYLOAD * pget(ARG_ITEM item);


   template < typename TITEM >
   auto pop(const TITEM & item)
   {

      auto value = operator[](item);

      erase_key(item);

      return value;

   }

   //Operations
   //lookup and add if not there
   inline PAYLOAD & operator[](ARG_ITEM item);
   inline const PAYLOAD & operator[](ARG_ITEM item) const;

   //inline iterator get_node(ARG_ITEM item);
   //iterator find_key(ARG_ITEM item) const;

   template < typename PAYLOAD2 >
   iterator find_payload(const PAYLOAD2 & payload) const;

   //add a memory_new (item, value) node
   iterator set_at(ARG_ITEM item, ARG_PAYLOAD newValue)
   {

      auto p = this->get_item(item);

      p->payload() = newValue;

      return p;

   }


   //add a memory_new (item, value) node
   void set_payload(const PAIR & pair)
   {
      
      set_at((ARG_ITEM) pair.element1(), (ARG_PAYLOAD) pair.element2());

   }


   //bool unhash(iterator iterator);

   //removing existing (item, ?) node
   //inline bool erase_item(ARG_ITEM item) { auto p = this->find_item(item);  return p ? this->erase(p) : false; }

   template < typename PAYLOAD2 >
   inline bool erase_payload(const PAYLOAD2 payload) { auto p = find_payload(payload);  return p ? erase(p) : false; }

   //template < typename ITERATOR >
   //inline ITERATOR erase(ITERATOR it) { return ::acme::iterator::erase(*this, it); }

   //template < typename ITERATOR >
   //inline void erase(const ITERATOR & begin, const ITERATOR & last)
   //{

     // for(auto it = begin; it != last; it++)
      //{

        // erase(it);

      //}

   //}

   //void erase_all();
   //void clear();
   //void Empty();

   
   inline auto items() { return ::range<key_iterator>(*(key_iterator *)&this->begin(), *(key_iterator *)&this->end()); }
   inline auto payloads() { return ::range<value_iterator>(*(value_iterator *)&this->begin(), *(value_iterator *)&this->end()); }
   inline auto items() const { return ::range<const_key_iterator>(*(key_iterator *)&this->begin(), *(key_iterator *)&this->end()); }
   inline auto payloads() const { return ::range<const_value_iterator>(*(value_iterator *)&this->begin(), *(value_iterator *)&this->end()); }


   //inline auto keys() const { return ::range<const_key_iterator>(*(const_key_iterator*)&this->begin(), *(const_key_iterator*)&this->end()); }
   //inline auto values() const { return ::range<const_value_iterator>(*(const_value_iterator*)&this->begin(), *(const_value_iterator*)&this->end()); }



   ::count count(const ITEM & t) const;
   bool has(const ITEM & t) const;
   bool contains(const ITEM & t) const;

   //iterating all (item, value) pairs
//   POSITION get_start_position() const;

   //inline const iterator get_start() const;
   //inline iterator get_start();

   //void get_next(iterator & rNextPosition, ITEM& rKey, PAYLOAD& rValue) const;

   //const iterator get_next(const iteratorpnodeRet) const;
   //iterator get_next(const iteratorpnodeRet);

   //advanced features for derived classes
   ::u32 GetHashTableSize() const
   {
      
      return this->m_hashtable.GetHashTableSize();
      
   }
   
   
   void InitHashTable(::u32 hashSize,bool bAllocNow = true);


   PAYLOAD get(ARG_ITEM argkey, ARG_PAYLOAD valueDefault);


   /*iterator next(iterator & iterator)
   {
      if(iterator == nullptr)
      {
         iterator = get_start();
      }
      else
      {
         iterator = get_next(iterator);
      }
      return iterator;
   }

   const iterator next(const iterator & iterator) const
   {
      if(iterator == nullptr)
      {
         iterator = get_start();
      }
      else
      {
         iterator = get_next(iterator);
      }
      return iterator;
   }*/


   void set(pair_map & pair_map)
   {
      
      for(auto & pair : pair_map)
      {

         set_at(pair.element1(), pair.element2());

      }

   }


   //inline iterator find_item(ARG_ITEM item) const { return find_node(item); }

   //using BASE_SET::find_item;
   //inline const_iterator find_item(ARG_ITEM item) const { return ((pair_map *) this)->find_item(item); }


   iterator new_node(ARG_ITEM item, ::u32 nHashBucket, ::u32 nHashValue);
   inline void hash(iterator, ::u32 nHashBucket, ::u32 nHashValue);
   void attach(iterator iterator, ::u32 nHashBucket, ::u32 nHashValue);
   bool erase(iterator iterator);
   void detach(iterator iterator);
   void hash(::u32& nHashBucket, ::u32& nHashValue, ARG_ITEM) const;
   inline iterator node_at(ARG_ITEM, ::u32 & nHashBucket, ::u32 & nHashValue) const;
   //inline const_iterator node_at(ARG_ITEM, ::u32& nHashBucket, ::u32& nHashValue) const;

   void transfer(iterator iterator, pair_map * ppair_map = nullptr);
   void transfer(pair_map* ppair_map, ARG_ITEM item);

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

   //virtual void on_after_read() override {}

   //s::range < iterator > elements()
   //{
   //   return ::range < iterator >(begin(),end());
   //}
   //::range < const_iterator > elements() const
   //{
   //   return ::range < const_iterator >(begin(),end());
   //}

   //PAIR & element_at(::index iIndex)
   //{
   //   return this->elements().element_at(iIndex);
   //}

   template < typename PRED >
   typename pair_map < PAIR >::iterator predicate_find(PRED pred)
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

   pair_map & operator = (const pair_map & m);


   template < typename TYPE >
   ::pointer<TYPE>get_typed_ptr(index i = 0)
   {

      ::pointer<TYPE>p;

     for(auto & node : *this)
     {

         p = (*node).element2();

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


template < typename PAIR >
inline ::count pair_map < PAIR >::get_count() const
{
   return this->m_nCount;
}

template < typename PAIR >
inline ::count pair_map < PAIR >::get_size() const
{
   return this->m_nCount;
}

template < typename PAIR >
inline ::count pair_map < PAIR >::count() const
{
   return this->m_nCount;
}

template < typename PAIR >
inline ::count pair_map < PAIR >::size() const
{
   return this->m_nCount;
}

template < typename PAIR >
pair_map < PAIR > & pair_map < PAIR >::operator = (const pair_map & m)
{
   if(this != &m)
   {

      this->erase_all();

      for(auto & node : m)
      {

         set_at((ARG_ITEM) node.element1(), (ARG_PAYLOAD) node.element2());

      }

   }
   return *this;
}


template < typename PAIR >
inline bool pair_map < PAIR >::is_empty() const
{

   return this->m_nCount == 0;

}


template < typename PAIR >
inline bool pair_map < PAIR >::empty() const
{

   return this->m_nCount == 0;

}


//template < typename PAIR >
//typename pair_map < PAIR >::iterator pair_map < PAIR >::set_at(ARG_ITEM item,ARG_PAYLOAD newValue)


//template < typename PAIR >
//inline typename pair_map < PAIR >::iterator pair_map < PAIR >::get_start() const
//{
//   return (this->m_nCount == 0) ? nullptr : BEFORE_START_POSITION;
//}

//template < typename PAIR >
//inline const typename pair_map < PAIR >::iterator pair_map < PAIR >::get_start() const
//{
//
//   return this->m_begin;
//
//}
//
//template < typename PAIR >
//typename pair_map < PAIR >::iterator pair_map < PAIR >::get_start()
//{
//
//   return this->m_begin.get();
//
//}


/////////////////////////////////////////////////////////////////////////////
// pair_map < PAIR > out-of-line functions
template < typename PAIR >
void pair_map < PAIR >::construct()
{

   this->m_nCount          = 0;

   this->m_begin      = nullptr;

   this->m_end = nullptr;
   
}


template < typename PAIR >
pair_map < PAIR >::pair_map()
{

   construct();

}


template < typename PAIR >
pair_map < PAIR >::pair_map(const ::std::initializer_list < PAIR > & list)
{

   construct();

   for(auto & pair : list)
   {

      set_at((ARG_ITEM) pair.element1(), (ARG_PAYLOAD) pair.element2());

   }

}

template < typename PAIR >
pair_map < PAIR >::pair_map(node pairs[], i32 iCount)
{
   construct();
   for(i32 i = 0; i < iCount; i++)
   {
      set_at(pairs[i].element1(), pairs[i].element2());
   }
}


template < typename PAIR >
pair_map < PAIR >::pair_map(const pair_map & m)
{
   
   construct();

   for(auto & pair : m)
   {

      set_at((ARG_ITEM) pair.element1(), (ARG_PAYLOAD) pair.element2());

   }

}

//
//template < typename PAIR >
//void pair_map < PAIR >::erase_all()
//{
//
//   //ASSERT_VALID(this);
//
//   if(::is_set(this->m_begin))
//   {
//      // destroy elements (values and keys)
//      iterator iteratorNext;
//
//      for (auto iterator = this->begin(); this->iterator_ok(iterator); iterator = iteratorNext)
//      {
//
//         iteratorNext = iterator + 1;
//
//         delete iterator.get();
//
//      }
//
//   }
//
//   this->m_hashtable.erase_all();
//
//   this->m_nCount = 0;
//   //this->m_pnodeFree = nullptr;
//
//   //if(m_pplex != nullptr)
//   //{
//
//   //   m_pplex->FreeDataChain();
//   //   m_pplex = nullptr;
//
//   //}
//
//   this->m_begin = nullptr;
//
//}


//template < typename PAIR >
//inline void pair_map < PAIR >::clear()
//{
//   erase_all();
//}
//
//template < typename PAIR >
//inline void pair_map < PAIR >::Empty()
//{
//   clear();
//}

template < typename PAIR >
pair_map < PAIR >::~pair_map()
{
   this->erase_all();
   ASSERT(this->m_nCount == 0);
}


template < typename PAIR >
void pair_map < PAIR >::attach(iterator p, ::u32 nHashBucket, ::u32 nHashValue)
{

   hash(p, nHashBucket, nHashValue);

   if (this->m_begin)
   {

      this->m_begin.back() = p.get();

   }

   p.next() = this->begin().get();

   this->begin() = p;

   this->begin().back() = nullptr;

   this->m_nCount++;

   ASSERT(this->m_nCount > 0);  // make sure we don't overflow

}




template < typename PAIR >
inline void pair_map < PAIR >::hash(iterator p, ::u32 nHashBucket, ::u32 nHashValue)
{

   // not precise (memleak? a watch dog can restart from the last check point... continuable tasks need...) but self-healing(self-recoverable/not-fatal)...
   if (::is_null(this->m_hashtable.m_ppHash))
   {

      InitHashTable(this->m_hashtable.GetHashTableSize());

   }

   if (::is_set(this->m_hashtable.m_ppHash[nHashBucket]))
   {
      
      this->m_hashtable.m_ppHash[nHashBucket]->m_pbackHash = &p->m_nextHash;

   }

   p->m_nextHash = this->m_hashtable.m_ppHash[nHashBucket].get();

   this->m_hashtable.m_ppHash[nHashBucket] = p;

   p->m_pbackHash = &this->m_hashtable.m_ppHash[nHashBucket].get();

}


template < typename PAIR >
typename pair_map < PAIR >::iterator
pair_map < PAIR >::new_node(ARG_ITEM item, ::u32 nHashBucket, ::u32 nHashValue)
{

   //if(this->m_pnodeFree == nullptr)
   //{
   //   // add another block
   //   //plex * newBlock = plex::create(m_pplex, m_nBlockSize, sizeof(pair_map::node));
   //   //// chain them into free list
   //   //pair_map::iterator iterator = (pair_map::iterator) newBlock->data();
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

   auto p = memory_new node(item);

   attach(p, nHashBucket, nHashValue);

   return p;

}


template < typename PAIR >
bool pair_map < PAIR >::erase(iterator iterator)
{

   detach(iterator);

   delete iterator.get();

   return true;

}


template < typename PAIR >
void pair_map < PAIR >::detach(iterator iterator)
{

   this->unhash(iterator);

   auto next = iterator->m_next;

   if (::is_set(iterator->m_next))
   {

      iterator->m_next->m_back = iterator->m_back;

   }

   if (::is_set(iterator->m_back))
   {

      iterator->m_back->m_next = iterator->m_next;

   }

   if (this->m_begin == iterator)
   {

      this->m_begin = next;

      if (::is_set(this->m_begin))
      {

         this->m_begin->m_back = nullptr;

      }

   }

   //delete iterator;

   //iterator->m_next = this->m_pnodeFree;

   //this->m_pnodeFree = iterator;

   this->m_nCount--;

   ASSERT(this->m_nCount >= 0);  // make sure we don't underflow

   // if no more elements, cleanup completely
   if (this->m_nCount == 0)
   {

      this->erase_all();

   }

}

template < typename PAIR >
void pair_map < PAIR >::hash(::u32& nHashBucket, ::u32& nHashValue, ARG_ITEM item) const
{

   nHashValue = u32_hash<ARG_ITEM>(item).m_u;

   nHashBucket = nHashValue % this->m_hashtable.GetHashTableSize();

}

//template < typename PAIR >
//inline typename pair_map < PAIR >::const_iterator
//pair_map < PAIR >::node_at(ARG_ITEM item, ::u32 & nHashBucket, ::u32 & nHashValue) const
//{
//
//   return (const_iterator &) ((pair_map *)this)->node_at(item, nHashBucket, nHashValue);
//
//}


template < typename PAIR >
inline typename pair_map < PAIR >::iterator
pair_map < PAIR >::node_at(ARG_ITEM item, ::u32& nHashBucket, ::u32& nHashValue) const
{

   hash(nHashBucket, nHashValue, item);

   if (get_count() <= 0)
   {

      return nullptr;

   }

   for(auto p = this->m_hashtable.m_ppHash[nHashBucket]; p; p = p->m_nextHash)
   {

      if (EqualElements<ARG_ITEM>(p->item(), item))
      {

         return p;

      }

   }

   return nullptr;

}

template < typename PAIR >
void pair_map < PAIR >::transfer(pair_map* ppair_map, ARG_ITEM item)
{

   ::u32 uHashBucket;

   ::u32 uHashValue;

   auto iterator = ppair_map->node_at(item, uHashBucket, uHashValue);

   ppair_map->detach(iterator);

   attach(iterator, uHashBucket, uHashValue);

}



template < typename PAIR >
void pair_map < PAIR >::transfer(iterator iterator, pair_map * ppair_map)
{

   if (ppair_map == this)
   {

      return;

   }

   if (::is_set(ppair_map))
   {

      ppair_map->detach(iterator);

   }

   ::u32 nHashBucket;

   ::u32 nHashValue;

   hash(nHashBucket, nHashValue, iterator->element1());

   attach(iterator, nHashBucket, nHashValue);

}


template < typename PAIR >
bool pair_map < PAIR >::lookup(ARG_ITEM item, PAYLOAD& rValue) const
{
   //ASSERT_VALID(this);

   ::u32 nHashBucket, nHashValue;

   auto p = node_at(item, nHashBucket, nHashValue);

   if (!p)
   {

      return false;  // not in pair_map

   }

   rValue = p->element2();

   return true;

}


//template < typename PAIR >
//typename pair_map < PAIR >::iterator pair_map < PAIR >::find (ARG_ITEM item)
//{
//   return iterator(plookup(item), this);
//}
//
//template < typename PAIR >
//typename pair_map < PAIR >::const_iterator pair_map < PAIR >::find (ARG_ITEM item) const
//{
//   return const_iterator((iterator) plookup(item), (pair_map *) this);
//}


template < typename PAIR >
typename pair_map < PAIR >::const_iterator pair_map < PAIR >::plookup(ARG_ITEM item) const
{

   ::u32 nHashBucket, nHashValue;

   auto p = node_at(item, nHashBucket, nHashValue);

   return p;

}


template < typename PAIR >
typename pair_map < PAIR >::iterator pair_map < PAIR >::plookup(ARG_ITEM item)
{

   ::u32 nHashBucket, nHashValue;

   iterator p = node_at(item, nHashBucket, nHashValue);

   return p;

}


template < typename PAIR >
typename pair_map < PAIR >::PAYLOAD * pair_map < PAIR >::pget(ARG_ITEM item)
{

   auto p = plookup(item);

   if (!p)
   {

      return nullptr;

   }

   return &p->payload();

}


//template < typename PAIR >
//inline typename pair_map < PAIR >::iterator pair_map < PAIR >::find_key(ARG_ITEM item) const
//{
//
//   ::u32 nHashBucket, nHashValue;
//
//   return node_at(item, nHashBucket, nHashValue);
//
//}


template < typename PAIR >
template < typename PAYLOAD2 >
inline typename pair_map < PAIR >::iterator pair_map < PAIR >::find_payload(const PAYLOAD2 & payload) const
{

   auto p = this->begin();

   while(p != this->end())
   {

      if(p->payload() == payload)
      {

         return p;

      }

   }

   return nullptr;

}


//template < typename PAIR >
//inline typename pair_map < PAIR >::iterator pair_map < PAIR >::get_item(ARG_ITEM item)
//{
//
//   ::u32 nHashBucket,nHashValue;
//
//   iterator p;
//
//   if(!(p = node_at(item,nHashBucket,nHashValue)))
//   {
//
//      p = this->new_node(item, nHashBucket, nHashValue);
//
//   }
//
//   return p;
//
//}


template < typename PAIR >
inline typename pair_map < PAIR >::PAYLOAD & pair_map < PAIR >::operator[](ARG_ITEM item)
{

   return this->get_item(item)->element2();

}


template < typename PAIR >
inline const typename pair_map < PAIR >::PAYLOAD & pair_map < PAIR >::operator[](ARG_ITEM item) const
{

   auto p = this->find_item(item);

   if(!p)
   {

      throw_exception(error_wrong_state);

   }

   return (const PAYLOAD &) p->payload();

}

//
//template < typename PAIR >
//inline bool pair_map < PAIR >::unhash(iterator iterator)
//// erase - return true if erased
//{
//
//   if(::is_set(iterator->m_nextHash))
//   {
//
//      iterator->m_nextHash->m_pbackHash = iterator->m_pbackHash;
//
//   }
//
//   *iterator->m_pbackHash = iterator->m_nextHash;
//
//   return true;
//
//}


template < typename PAIR >
inline ::count pair_map < PAIR >::count(const ITEM & item) const
{

   return this->plookup(item) ? 1 : 0;

}


template < typename PAIR >
bool pair_map < PAIR >::has(const ITEM & item) const
{

   return this->plookup(item) ? 1 : 0;

}


template < typename PAIR >
bool pair_map < PAIR >::contains(const ITEM & item) const
{

   return this->plookup(item) ? 1 : 0;

}


//template < typename PAIR >
//void pair_map < PAIR >::get_next(iterator & iterator,
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
//inline const typename pair_map < PAIR >::iterator
//pair_map < PAIR >::get_next(const iterator iterator) const
//{
//
//   return iterator->m_next;
//
//}

//
//template < typename PAIR >
//inline typename pair_map < PAIR >::iterator
//pair_map < PAIR >::get_next(const iterator iterator)
//{
//
//   return iterator->m_next;
//
//}


template < typename PAIR >
typename pair_map < PAIR >::PAYLOAD pair_map < PAIR > ::
get(ARG_ITEM argkey, ARG_PAYLOAD valueDefault)
{

   auto p = plookup(argkey);

   if(!p)
   {

      return valueDefault;

   }

   return p->payload();

}


//template < typename PAIR >
//void pair_map < PAIR >::assert_ok() const
//{
//
//   ::matter::assert_ok();
//
//   ASSERT(GetHashTableSize() > 0);
//
//   ASSERT(this->m_nCount == 0 || this->m_hashtable.m_ppHash != nullptr);
//   // non-empty pair_map should have hash table
//
//}
//


template < class PAYLOAD >
using double_map = map < double, PAYLOAD >;


using double_to_double = double_map < double >;


template < class PAYLOAD >
using dword_map = map < ::u32, PAYLOAD >;


template < class PAYLOAD >
using uptr_map = map < uptr, PAYLOAD >;


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
   // const ITEM & element1() const;
   // const PAYLOAD & element2() const;

};


//template < typename PAIR >
//using pair_pair_map = pair_map <  typename PAIR::TYPE1, typename PAIR::TYPE2 >;


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



template < typename PAIR >
void pair_map < PAIR >::InitHashTable(
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


//template < typename PAIR >
//void pair_map < PAIR >::dump(dump_context& dumpcontext) const
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



