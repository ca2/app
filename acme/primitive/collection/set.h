#pragma once


//#define memory_new ACME_NEW


//#include "_iterator.h"
#include "hash_table.h"
#include "list_iterator.h"
#include "range.h"
#include "single.h"
#include "acme/primitive/primitive/particle.h"


template < typename KEY, typename ARG_KEY, typename PAYLOAD >
class set :
   virtual public ::particle,
   virtual public ::range < ::list_iterator < ::map_association < PAYLOAD > * > >
{
public:


   typedef set_dynamic_hash_table < PAYLOAD >      HASH_TABLE;
   typedef KEY                                     BASE_KEY;
   typedef ARG_KEY                                 BASE_ARG_KEY;


   using association= ::map_association < PAYLOAD > ;
   using single = association ;

   using ITEM_TYPE = association;

   using BASE_RANGE = ::range < ::list_iterator < association * > >;

   using CONTAINER_ITEM_TYPE = association;

   using iterator = BASE_RANGE::iterator;
   using const_iterator = BASE_RANGE::const_iterator;


   //__declare_iterator_struct_ok(set, iterator, m_passociation, ::is_set(this->m_passociation));


//   template < typename iterator > struct make_iterator : iterator
//   {
//
//      using CONTAINER = typename iterator::CONTAINER;
//
//      using iterator::iterator;
//
//      make_iterator()
//      {
//         this->m_passociation = (iterator)nullptr;
//         this->m_pcontainer = (CONTAINER*)nullptr;
//         this->m_passociationBeg = (iterator)nullptr;
//         this->m_passociationEnd = (iterator) nullptr;
//      }
//
//      make_iterator(const iterator iterator, const CONTAINER * pset = nullptr)
//      {
//         this->m_passociation = (iterator) iterator;
//         this->m_pcontainer = (CONTAINER *) pset;
//         this->m_passociationBeg = (iterator) iterator;
//         this->m_passociationEnd = (iterator) nullptr;
//      }
//
//
//      make_iterator(const make_iterator & iterator)
//      {
//         this->m_passociation = iterator.m_passociation;
//         this->m_pcontainer = iterator.m_pcontainer;
//         this->m_passociationBeg = (iterator) iterator.m_passociationBeg;
//         this->m_passociationEnd = (iterator) iterator.m_passociationEnd;
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
//         this->m_passociation = this->m_passociation->m_next;
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
//         make_iterator iterator = this->m_passociation;
//
//         this->m_passociation = this->m_passociation->m_next;
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
//         if (this->m_passociation == nullptr && it.m_passociation == nullptr && it.m_pcontainer == nullptr)
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
//         return this->m_passociation == it.m_passociation;
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
//            this->m_passociation = it.m_passociation;
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
//   //__declare_iterator(dereferenced_value_iterator, this->m_passociation->key());
//   //__declare_iterator(value_iterator, &this->m_passociation->key());
//   __declare_iterator(key_iterator, &this->m_passociation->key());
//   __declare_iterator(iterator, this->m_passociation);
//

   //using deferenced_iterator = dereferenced_value_iterator;



   HASH_TABLE           m_hashtable;
   ::count              m_nCount;
   //iterator              m_begin;


   set();
   set(association singles[], i32 iCount);
   set(const ::std::initializer_list < PAYLOAD > & list);
   set(const set & m);
   virtual ~set();

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
   bool lookup(ARG_KEY key, KEY& rValue) const;
   const iterator plookup(ARG_KEY key) const;
   iterator plookup(ARG_KEY key);


   bool should_set(ARG_KEY key)
   { 
      
      if (has(key))
      {

         return false;

      }

      set_at(key);

      return true;

   }


   
   KEY * pget(ARG_KEY key);


   template < typename TKEY >
   auto pop(const TKEY & key)
   {

      auto value = operator[](key);

      erase_key(key);

      return value;

   }

   //Operations
   //lookup and add if not there
   KEY & operator[](ARG_KEY key);
   const KEY & operator[](ARG_KEY key) const;

   iterator get_association(ARG_KEY key);
   iterator get_association(ARG_KEY key) const
   {
      return ((set *) this)->get_association(key);
   }
   iterator find_association(ARG_KEY key) const;

   //add a memory_new (key) association
   inline iterator set_at(ARG_KEY key);

   //add a memory_new (key, value) association
   virtual void set_payload(const PAYLOAD& payload)
   {
      set_at(payload.key());
   }

   bool erase_item(iterator iterator);

   //removing existing (key, ?) association
   inline bool erase_key(ARG_KEY key) { auto pitem = find_item(key);  return ::is_set(pitem) ? erase_item(pitem) : false; }

   template < typename iterator >
   inline iterator erase(iterator it) { return ::acme::iterator::erase(*this, it); }

   template < typename iterator >
   inline void erase(const iterator & begin, const iterator & last)
   {

      for(auto it = begin; it != last; it++)
      {

         erase(it);

      }

   }

   void erase_all();
   void clear();
   void Empty();

//   inline auto singles() { return iterator(nullptr, this); }
//   inline auto singles() const { return const_iterator(nullptr, this); }
////   inline auto values() const { return value_iterator(nullptr, this); }
//   inline auto keys() const { return key_iterator(nullptr, this); }



   ::count count(const KEY & t) const;
   bool has(const KEY & t) const;
   bool contains(const KEY & t) const;

   //iterating all (key, value) singles
//   POSITION get_start_position() const;

   //const iterator get_start() const;
   //iterator get_start();

   //void get_next(iterator & rNextPosition, KEY& rKey, KEY& rValue) const;

   //const iterator get_next(const iteratorpassociationRet) const;
   //iterator get_next(const iteratorpassociationRet);

   //advanced features for derived classes
   ::u32 GetHashTableSize() const
   {
      
      return m_hashtable.GetHashTableSize();
      
   }
   
   
   void InitHashTable(::u32 hashSize,bool bAllocNow = true);


   KEY get(ARG_KEY argkey, ARG_KEY valueDefault);


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


   void _set(set & set)
   {

      auto it = set.begin();

      while(it.is_set())
      {

         set_payload(*it);

         it++;

      }

   }
   

   inline iterator find_item(ARG_KEY key) const { return find_association(key); }

   inline iterator find(ARG_KEY key) { return find_item(key); }
   const_iterator find (ARG_KEY key) const { return find_item(key); }


   iterator new_association(ARG_KEY key);
   void free_association(iterator iterator);
   iterator get_association_at(ARG_KEY, ::u32&, ::u32&) const;


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
   ::count erase_association_array(ARRAY a)
   {

      ::count countRemoved = 0;

      for(index i = 0; i < a.get_count(); i++)
      {

         if(erase_association(a[i]))
         {

            countRemoved++;

         }

      }

      return countRemoved;

   }

   virtual void on_after_read() {}

   //::range < iterator > elements()
   //{
   //   return range < iterator >(begin(),end());
   //}
   //
   //::range < const_iterator > elements() const
   //{
   //   return range < const_iterator >(begin(),end());
   //}

   //PAYLOAD & element_at(::index iIndex)
   //{
   //   return elements().element_at(iIndex);
   //}

   template < typename PRED >
   typename set < KEY, ARG_KEY, PAYLOAD >::iterator predicate_find(PRED pred)
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

   set & operator = (const set & m);


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


template < typename KEY, typename ARG_KEY, typename PAYLOAD >
inline ::count set < KEY, ARG_KEY, PAYLOAD >::get_count() const
{
   return m_nCount;
}

template < typename KEY, typename ARG_KEY, typename PAYLOAD >
inline ::count set < KEY, ARG_KEY, PAYLOAD >::get_size() const
{
   return m_nCount;
}

template < typename KEY, typename ARG_KEY, typename PAYLOAD >
inline ::count set < KEY, ARG_KEY, PAYLOAD >::count() const
{
   return m_nCount;
}

template < typename KEY, typename ARG_KEY, typename PAYLOAD >
inline ::count set < KEY, ARG_KEY, PAYLOAD >::size() const
{
   return m_nCount;
}

template < typename KEY, typename ARG_KEY, typename PAYLOAD >
set< KEY, ARG_KEY, PAYLOAD > & set < KEY, ARG_KEY, PAYLOAD >::operator = (const set & m)
{
   if(this != &m)
   {

      erase_all();

      for(auto & association : m)
      {

         set_at(association.key());

      }

   }
   return *this;
}

template < typename KEY, typename ARG_KEY, typename PAYLOAD >
inline bool set < KEY, ARG_KEY, PAYLOAD >::is_empty() const
{
   return m_nCount == 0;
}

template < typename KEY, typename ARG_KEY, typename PAYLOAD >
inline bool set < KEY, ARG_KEY, PAYLOAD >::empty() const
{
   return m_nCount == 0;
}


template < typename KEY, typename ARG_KEY, typename PAYLOAD >
inline typename set < KEY, ARG_KEY, PAYLOAD >::iterator set < KEY, ARG_KEY, PAYLOAD >::set_at(ARG_KEY key)
{

   iterator iterator = get_association(key);

   //iterator->key() = newValue;

   return iterator;

}


//template < typename KEY, typename ARG_KEY, typename PAYLOAD >
//inline typename set < KEY, ARG_KEY, PAYLOAD >::iterator set < KEY, ARG_KEY, PAYLOAD >::get_start() const
//{
//   return (m_nCount == 0) ? nullptr : BEFORE_START_POSITION;
//}

//template < typename KEY, typename ARG_KEY, typename PAYLOAD >
//const typename set < KEY, ARG_KEY, PAYLOAD >::iterator set < KEY, ARG_KEY, PAYLOAD >::get_start() const
//{
//
//   return this->m_begin;
//
//}
//
//template < typename KEY, typename ARG_KEY, typename PAYLOAD >
//typename set < KEY, ARG_KEY, PAYLOAD >::iterator set < KEY, ARG_KEY, PAYLOAD >::get_start()
//{
//
//   return this->m_begin;
//
//}

/////////////////////////////////////////////////////////////////////////////
// set < KEY, ARG_KEY, PAYLOAD > out-of-line functions
template < typename KEY, typename ARG_KEY, typename PAYLOAD >
void set < KEY, ARG_KEY, PAYLOAD >::construct()
{

   m_nCount          = 0;
   this->m_begin      = nullptr;
   this->m_end = nullptr;

}


template < typename KEY, typename ARG_KEY, typename PAYLOAD >
set < KEY, ARG_KEY, PAYLOAD >::set()
{

   construct();

}


template < typename KEY, typename ARG_KEY, typename PAYLOAD >
set < KEY, ARG_KEY, PAYLOAD >::set(const ::std::initializer_list < PAYLOAD > & list)
{

   construct();

   for(auto & pair_item : list)
   {

      set_at(pair_item.key());

   }

}

template < typename KEY, typename ARG_KEY, typename PAYLOAD >
set < KEY, ARG_KEY, PAYLOAD >::set(association singles[], i32 iCount)
{
   construct();
   for(i32 i = 0; i < iCount; i++)
   {
      set_at(singles[i].key());
   }
}


template < typename KEY, typename ARG_KEY, typename PAYLOAD >
set < KEY, ARG_KEY, PAYLOAD >::set(const set & m)
{
   
   construct();

   for(auto & pair : m)
   {

      set_at(pair.key());

   }

}


template < typename KEY, typename ARG_KEY, typename PAYLOAD >
void set < KEY, ARG_KEY, PAYLOAD >::erase_all()
{

   //ASSERT_VALID(this);

   if(this->m_begin != nullptr)
   {
      // destroy elements (values and keys)

      iterator iteratorNext;

      for (auto iterator = this->m_begin; iterator.is_set(); iterator = iteratorNext)
      {

         iteratorNext = iterator->m_next;

         delete iterator.get();

      }

   }

   m_hashtable.erase_all();

   m_nCount = 0;
   //this->m_passociationFree = nullptr;

   //if(m_pplex != nullptr)
   //{

   //   m_pplex->FreeDataChain();
   //   m_pplex = nullptr;

   //}

   this->m_begin = nullptr;

}


template < typename KEY, typename ARG_KEY, typename PAYLOAD >
inline void set < KEY, ARG_KEY, PAYLOAD >::clear()
{
   erase_all();
}

template < typename KEY, typename ARG_KEY, typename PAYLOAD >
inline void set < KEY, ARG_KEY, PAYLOAD >::Empty()
{
   clear();
}

template < typename KEY, typename ARG_KEY, typename PAYLOAD >
set < KEY, ARG_KEY, PAYLOAD >::~set()
{
   erase_all();
   ASSERT(m_nCount == 0);
}

template < typename KEY, typename ARG_KEY, typename PAYLOAD >
typename set < KEY, ARG_KEY, PAYLOAD >::iterator
set < KEY, ARG_KEY, PAYLOAD >::new_association(ARG_KEY key)
{

   //if(this->m_passociationFree == nullptr)
   //{
   //   // add another block
   //   //plex * newBlock = plex::create(m_pplex, m_nBlockSize, sizeof(set::association));
   //   //// chain them into free list
   //   //set::iterator iterator = (set::iterator) newBlock->data();
   //   //// free in reverse order to make it easier to debug
   //   //index i = m_nBlockSize - 1;
   //   //for (iterator = &iterator[i]; i >= 0; i--, iterator--)
   //   //{
   //   //   iterator->m_next = this->m_passociationFree;
   //   //   this->m_passociationFree = iterator;

   //   //}
   //   this->m_passociationFree = memory_new association();

   //}

   //ENSURE(this->m_passociationFree != nullptr);  // we must have something

   typename set < KEY, ARG_KEY, PAYLOAD >::iterator iterator =
   memory_new association(key);

   //this->m_passociationFree  = this->m_passociationFree->m_next;

   //zero_pointer(iterator);

   if(this->m_begin != nullptr)
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


template < typename KEY, typename ARG_KEY, typename PAYLOAD >
void set < KEY, ARG_KEY, PAYLOAD >::free_association(iterator iterator)
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

      if(this->m_begin != nullptr)
      {

         this->m_begin->m_back = nullptr;

      }

   }

   delete iterator.get();

   //iterator->m_next = this->m_passociationFree;

   //this->m_passociationFree = iterator;

   m_nCount--;

   ASSERT(m_nCount >= 0);  // make sure we don't underflow

   // if no more elements, cleanup completely
   if (m_nCount == 0)
   {

      erase_all();

   }

}


template < typename KEY, typename ARG_KEY, typename PAYLOAD >
typename set < KEY, ARG_KEY, PAYLOAD >::iterator
set < KEY, ARG_KEY, PAYLOAD >::get_association_at(ARG_KEY key, ::u32& nHashBucket, ::u32& nHashValue) const
// find association (or return nullptr)
{

   nHashValue = u32_hash<ARG_KEY>(key).m_u;

   nHashBucket = nHashValue % m_hashtable.GetHashTableSize();

   if (get_count() <= 0)
   {

      return nullptr;

   }

   for(auto iterator = m_hashtable.m_ppassociationHash[nHashBucket]; ::is_set(iterator); iterator = iterator->m_nextHash)
   {

      if (EqualElements<ARG_KEY>(iterator->key(), key))
      {

         return iterator;

      }

   }

   return nullptr;

}

template < typename KEY, typename ARG_KEY, typename PAYLOAD >
bool set < KEY, ARG_KEY, PAYLOAD >::lookup(ARG_KEY key, KEY& rValue) const
{
   //ASSERT_VALID(this);

   ::u32 nHashBucket, nHashValue;

   auto iterator = get_association_at(key, nHashBucket, nHashValue);

   if (iterator.is_null())
   {

      return false;  // not in set

   }

   rValue = iterator->key();

   return true;

}

//template < typename KEY, typename ARG_KEY, typename PAYLOAD >
//typename set < KEY, ARG_KEY, PAYLOAD >::iterator set < KEY, ARG_KEY, PAYLOAD >::find (ARG_KEY key)
//{
//   return iterator(plookup(key), this);
//}
//
//template < typename KEY, typename ARG_KEY, typename PAYLOAD >
//typename set < KEY, ARG_KEY, PAYLOAD >::const_iterator set < KEY, ARG_KEY, PAYLOAD >::find (ARG_KEY key) const
//{
//   return const_iterator((iterator) plookup(key), (set *) this);
//}


template < typename KEY, typename ARG_KEY, typename PAYLOAD >
const typename set < KEY, ARG_KEY, PAYLOAD >::iterator set < KEY, ARG_KEY, PAYLOAD >::plookup(ARG_KEY key) const
{
   //ASSERT_VALID(this);

   ::u32 nHashBucket, nHashValue;

   auto iterator = get_association_at(key, nHashBucket, nHashValue);

   return iterator;

}


template < typename KEY, typename ARG_KEY, typename PAYLOAD >
typename set < KEY, ARG_KEY, PAYLOAD >::iterator set < KEY, ARG_KEY, PAYLOAD >::plookup(ARG_KEY key)
{

   ::u32 nHashBucket, nHashValue;

   auto iterator = get_association_at(key, nHashBucket, nHashValue);

   return iterator;

}


template < typename KEY, typename ARG_KEY, typename PAYLOAD >
KEY * set < KEY, ARG_KEY, PAYLOAD >::pget(ARG_KEY key)
{

   auto iterator = plookup(key);

   if (iterator.is_null())
   {

      return nullptr;

   }
      
   return &iterator->key();

}


template < typename KEY, typename ARG_KEY, typename PAYLOAD >
inline typename set < KEY, ARG_KEY, PAYLOAD >::iterator set < KEY, ARG_KEY, PAYLOAD >::find_association(ARG_KEY key) const
{

   ::u32 nHashBucket, nHashValue;

   return get_association_at(key, nHashBucket, nHashValue);

}


template < typename KEY, typename ARG_KEY, typename PAYLOAD >
typename set < KEY, ARG_KEY, PAYLOAD >::iterator set < KEY, ARG_KEY, PAYLOAD >::get_association(ARG_KEY key)
{

   ::u32 nHashBucket,nHashValue;

   iterator iterator;

   if((iterator = get_association_at(key,nHashBucket,nHashValue)) == nullptr)
   {

      // not precise (memleak? a watch dog can restart from the last check point... continuable tasks need...) but self-healing(self-recoverable/not-fatal)...
      if (::is_null(m_hashtable.m_ppassociationHash))
      {

         InitHashTable(m_hashtable.GetHashTableSize());

      }

      ENSURE(m_hashtable.m_ppassociationHash);

      iterator = new_association(key);

      if(m_hashtable.m_ppassociationHash[nHashBucket] != nullptr)
      {
         m_hashtable.m_ppassociationHash[nHashBucket]->m_pbackHash = &iterator->m_nextHash;
      }

      iterator->m_nextHash        = m_hashtable.m_ppassociationHash[nHashBucket];

      m_hashtable.m_ppassociationHash[nHashBucket] = iterator.get();

      iterator->m_pbackHash       = &m_hashtable.m_ppassociationHash[nHashBucket];

   }

   return iterator;

}


template < typename KEY, typename ARG_KEY, typename PAYLOAD >
KEY& set < KEY, ARG_KEY, PAYLOAD >::operator[](ARG_KEY key)
{

   return get_association(key)->key();  // return memory_new matter

}

template < typename KEY, typename ARG_KEY, typename PAYLOAD >
const KEY & set < KEY, ARG_KEY, PAYLOAD >::operator[](ARG_KEY key) const
{

   return get_association(key)->key();  // return memory_new matter

}


template < typename KEY, typename ARG_KEY, typename PAYLOAD >
inline bool set < KEY, ARG_KEY, PAYLOAD >::erase_item(iterator iterator)
// erase - return true if erased
{

   if(iterator->m_nextHash != nullptr)
   {

      iterator->m_nextHash->m_pbackHash = iterator->m_pbackHash;

   }

   *iterator->m_pbackHash = iterator->m_nextHash;

   free_association(iterator);

   return true;

}


template < typename KEY, typename ARG_KEY, typename PAYLOAD >
inline ::count set < KEY, ARG_KEY, PAYLOAD >::count(const KEY & key) const
{

   return this->plookup(key) != nullptr ? 1 : 0;

}


template < typename KEY, typename ARG_KEY, typename PAYLOAD >
bool set < KEY, ARG_KEY, PAYLOAD >::has(const KEY & key) const
{

   return this->plookup(key) != nullptr ? 1 : 0;

}


template < typename KEY, typename ARG_KEY, typename PAYLOAD >
bool set < KEY, ARG_KEY, PAYLOAD >::contains(const KEY & key) const
{

   return this->plookup(key) != nullptr ? 1 : 0;

}


//template < typename KEY, typename ARG_KEY, typename PAYLOAD >
//void set < KEY, ARG_KEY, PAYLOAD >::get_next(iterator & iterator,
//      KEY& rKey, KEY& rValue) const
//{
//
//   rKey = iterator->key();
//
//   rValue = iterator->key();
//
//   iterator = iterator->m_next;
//
//}
//
//
//template < typename KEY, typename ARG_KEY, typename PAYLOAD >
//inline const typename set < KEY, ARG_KEY, PAYLOAD >::iterator
//set < KEY, ARG_KEY, PAYLOAD >::get_next(const iterator iterator) const
//{
//
//   return iterator->m_next;
//
//}
//
//
//template < typename KEY, typename ARG_KEY, typename PAYLOAD >
//inline typename set < KEY, ARG_KEY, PAYLOAD >::iterator
//set < KEY, ARG_KEY, PAYLOAD >::get_next(const iterator iterator)
//{
//
//   return iterator->m_next;
//
//}


template < typename KEY, typename ARG_KEY, typename PAYLOAD >
KEY set < KEY, ARG_KEY, PAYLOAD > ::
get(ARG_KEY argkey, ARG_KEY valueDefault)
{
   iterator iterator = plookup(argkey);
   if(iterator == nullptr)
      return valueDefault;
   else
      return iterator->key();
}


//template < typename KEY, typename ARG_KEY, typename PAYLOAD >
//void set < KEY, ARG_KEY, PAYLOAD >::assert_ok() const
//{
//
//   ::matter::assert_ok();
//
//   ASSERT(GetHashTableSize() > 0);
//
//   ASSERT(m_nCount == 0 || m_hashtable.m_ppassociationHash != nullptr);
//   // non-empty set should have hash table
//
//}
//

using double_set = set < double >;

using dword_set = set < ::u32 >;

using uptr_set = set < ::uptr >;

template < typename KEY_TYPE >
class key
{
public:


   using KEY = KEY_TYPE;
   using TYPE = KEY;
   using ARG_TYPE = typename argument_of < KEY & >::type;


   // Contract
   // KEY & key();
   // KEY & key();
   // const KEY & key() const;
   // const KEY & key() const;

};


template < typename PAYLOAD >
using key_set = set <  typename PAYLOAD::TYPE, typename PAYLOAD::ARG_TYPE, PAYLOAD >;


#define __declare_key(xkeytype, xkey) \
struct xkeytype : public ::key < xkeytype > \
{ \
\
   PAIR_DEFAULT_IMPL(xkeytype, KEY, const KEY &, xkey); \
   KEY & key() { return xkey; } \
   const KEY & key() const { return xkey; } \
}


#ifdef CPP17
#define __declare_key_tuple_size(key) \
template<> ALIENATED_ANDROID_ANARCHY ::std::tuple_size< key > : ::std::integral_constant<size_t, 1> {} }
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


template < typename KEY, typename ARG_KEY, typename PAYLOAD >
void set < KEY, ARG_KEY, PAYLOAD >::InitHashTable(
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


//template < typename KEY, typename ARG_KEY, typename PAYLOAD >
//void set < KEY, ARG_KEY, PAYLOAD >::dump(dump_context& dumpcontext) const
//{
//
//   ::matter::dump(dumpcontext);
//
//   //dumpcontext << "with " << this->m_nCount << " elements";
//   //if (dumpcontext.GetDepth() > 0)
//   //{
//   //   // Dump in format "[key] -> value"
//
//   //   const iterator iterator = get_start();
//   //   while (iterator != nullptr)
//   //   {
//   //      iterator = get_next(iterator);
//   //      dumpcontext << "\n\t[";
//   //      dump_elements<KEY>(dumpcontext, &iterator->key(), 1);
//   //   }
//   //}
//
//   //dumpcontext << "\n";
//}
//
//
//
