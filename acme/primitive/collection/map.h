#pragma once


//#define memory_new ACME_NEW

#include "set.h"
#include "acme/primitive/comparison/equals.h"


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
class map :
   virtual public ::set < KEY, ARG_KEY, PAIR >
{
public:


   typedef typename ::set < KEY, ARG_KEY, PAIR >      BASE_SET;
   typedef typename BASE_SET::HASH_TABLE                       HASH_TABLE;
   typedef typename BASE_SET::BASE_KEY                         BASE_KEY;
   typedef typename BASE_SET::BASE_ARG_KEY                     BASE_ARG_KEY;
   typedef VALUE                                      BASE_VALUE;
   typedef ARG_VALUE                                  BASE_ARG_VALUE;
   

   using association = typename BASE_SET::association;
   using pair = typename association::payload;

   using ITEM_TYPE = association;

   using iterator = typename BASE_SET::iterator;
   using const_iterator = typename BASE_SET::const_iterator;

   using key_iterator = ::first_item_list_iterator < association * >;
   using value_iterator = ::second_item_list_iterator < association * >;
   using const_key_iterator = typename key_iterator::const_iterator;
   using const_value_iterator = typename value_iterator::const_iterator;


   //using iterator_struct = BASE_SET::iterator_struct;
   //using const_iterator_struct = BASE_SET::const_iterator_struct;
   //using key_iterator = BASE_SET::key_iterator;
   //using iterator = BASE_SET::iterator;
   //using const_iterator = BASE_SET::const_iterator;
   //sing make_iterator = BASE_SET::make_iterator;

   //__declare_iterator_struct_ok(map, iterator, m_passociation, ::is_set(this->m_passociation));


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
//         this->m_passociation = (iterator)nullptr;
//         this->m_pcontainer = (CONTAINER*)nullptr;
//         this->m_passociationBeg = (iterator)nullptr;
//         this->m_passociationEnd = (iterator) nullptr;
//      }
//
//      make_iterator(const iterator iterator, const CONTAINER* pset = nullptr)
//      {
//         this->m_passociation = (iterator)iterator;
//         this->m_pcontainer = (CONTAINER*)pset;
//         this->m_passociationBeg = (iterator)iterator;
//         this->m_passociationEnd = (iterator) nullptr;
//      }
//
//
//      make_iterator(const make_iterator& iterator)
//      {
//         this->m_passociation = iterator.m_passociation;
//         this->m_pcontainer = iterator.m_pcontainer;
//         this->m_passociationBeg = (iterator)iterator.m_passociationBeg;
//         this->m_passociationEnd = (iterator)iterator.m_passociationEnd;
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
//   __declare_iterator(dereferenced_value_iterator, this->m_passociation->element2());
//   __declare_iterator(value_iterator, &this->m_passociation->element2());
//   __declare_iterator(key_iterator, &this->m_passociation->element1());
//   __declare_iterator(iterator, this->m_passociation);


   //using deferenced_iterator = dereferenced_value_iterator;


   //HASH_TABLE           this->m_hashtable;
   //::count              this->m_nCount;
   //iterator              m_begin;


   map();
   map(association pairs[], i32 iCount);
   map(const ::std::initializer_list < PAIR > & list);
   map(const map & m);
   virtual ~map();

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
   bool lookup(ARG_KEY key, VALUE& rValue) const;
   const iterator plookup(ARG_KEY key) const;
   iterator plookup(ARG_KEY key);

   
   VALUE * pget(ARG_KEY key);


   template < typename TKEY >
   auto pop(const TKEY & key)
   {

      auto value = operator[](key);

      erase_key(key);

      return value;

   }

   //Operations
   //lookup and add if not there
   inline VALUE & operator[](ARG_KEY key);
   inline const VALUE & operator[](ARG_KEY key) const;

   inline iterator get_association(ARG_KEY key) const;
   iterator find_association(ARG_KEY key) const;

   //add a memory_new (key, value) association
   iterator set_at(ARG_KEY key, ARG_VALUE newValue)
   {

      iterator iterator = get_association(key);

      iterator->element2() = newValue;

      return iterator;

   }


   //add a memory_new (key, value) association
   virtual void set_payload(const PAIR & pair) override
   {
      set_at(pair.key(), pair.value());
   }


   bool unhash(iterator iterator);

   //removing existing (key, ?) association
   inline bool erase_key(ARG_KEY key) { auto iterator = find_association(key);  return ::is_set(iterator) ? erase(iterator) : false; }

   template < typename ITERATOR >
   inline ITERATOR erase(ITERATOR it) { return ::acme::iterator::erase(*this, it); }

   template < typename ITERATOR >
   inline void erase(const ITERATOR & begin, const ITERATOR & last)
   {

      for(auto it = begin; it != last; it++)
      {

         erase(it);

      }

   }

   void erase_all();
   void clear();
   void Empty();

   inline auto keys() { return ::range<key_iterator>(*(const_key_iterator *)&this->begin(), *(const_key_iterator *)&this->end()); }
   inline auto values() { return ::range<value_iterator>(*(const_value_iterator *)&this->begin(), *(const_value_iterator *)&this->end()); }
   //inline auto keys() const { return ::range<const_key_iterator>(*(const_key_iterator*)&this->begin(), *(const_key_iterator*)&this->end()); }
   //inline auto values() const { return ::range<const_value_iterator>(*(const_value_iterator*)&this->begin(), *(const_value_iterator*)&this->end()); }



   ::count count(const KEY & t) const;
   bool has(const KEY & t) const;
   bool contains(const KEY & t) const;

   //iterating all (key, value) pairs
//   POSITION get_start_position() const;

   //inline const iterator get_start() const;
   //inline iterator get_start();

   //void get_next(iterator & rNextPosition, KEY& rKey, VALUE& rValue) const;

   //const iterator get_next(const iteratorpassociationRet) const;
   //iterator get_next(const iteratorpassociationRet);

   //advanced features for derived classes
   ::u32 GetHashTableSize() const
   {
      
      return this->m_hashtable.GetHashTableSize();
      
   }
   
   
   void InitHashTable(::u32 hashSize,bool bAllocNow = true);


   VALUE get(ARG_KEY argkey, ARG_VALUE valueDefault);


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


   void set(map & map)
   {
      
      for(auto & pair : map)
      {

         set_at(pair.element1(), pair.element2());

      }

   }


   //inline iterator find_item(ARG_KEY key) const { return find_association(key); }

   inline iterator find(ARG_KEY key) { return find_association(key); }
   inline const_iterator find (ARG_KEY key) const { return find_association(key); }


   iterator new_association(ARG_KEY key, ::u32 nHashBucket, ::u32 nHashValue);
   inline void hash(iterator, ::u32 nHashBucket, ::u32 nHashValue);
   void attach(iterator iterator, ::u32 nHashBucket, ::u32 nHashValue);
   bool erase(iterator iterator);
   void detach(iterator iterator);
   void hash(::u32& nHashBucket, ::u32& nHashValue, ARG_KEY) const;
   inline iterator association_at(ARG_KEY, ::u32 & nHashBucket, ::u32 & nHashValue) const;
   //inline const_iterator association_at(ARG_KEY, ::u32& nHashBucket, ::u32& nHashValue) const;

   void move(iterator iterator, map * pmap = nullptr);
   void move(map* pmap, ARG_KEY key);

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

   virtual void on_after_read() override {}

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
   typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::iterator predicate_find(PRED pred)
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

   map & operator = (const map & m);


   template < typename TYPE >
   ::pointer<TYPE>get_typed_ptr(index i = 0)
   {

      ::pointer<TYPE>p;

     for(auto & association : *this)
     {

         p = (*association).element2();

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


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline ::count map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::get_count() const
{
   return this->m_nCount;
}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline ::count map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::get_size() const
{
   return this->m_nCount;
}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline ::count map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::count() const
{
   return this->m_nCount;
}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline ::count map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::size() const
{
   return this->m_nCount;
}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
map< KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR > & map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::operator = (const map & m)
{
   if(this != &m)
   {

      erase_all();

      for(auto & association : m)
      {

         set_at(association.element1(),association.element2());

      }

   }
   return *this;
}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline bool map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::is_empty() const
{
   return this->m_nCount == 0;
}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline bool map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::empty() const
{
   return this->m_nCount == 0;
}


//template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
//typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::iterator map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::set_at(ARG_KEY key,ARG_VALUE newValue)


//template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
//inline typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::iterator map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::get_start() const
//{
//   return (this->m_nCount == 0) ? nullptr : BEFORE_START_POSITION;
//}

//template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
//inline const typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::iterator map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::get_start() const
//{
//
//   return this->m_begin;
//
//}
//
//template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
//typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::iterator map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::get_start()
//{
//
//   return this->m_begin.get();
//
//}


/////////////////////////////////////////////////////////////////////////////
// map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR > out-of-line functions
template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::construct()
{

   this->m_nCount          = 0;

   this->m_begin      = nullptr;

   this->m_end = nullptr;
   
}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::map()
{

   construct();

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::map(const ::std::initializer_list < PAIR > & list)
{

   construct();

   for(auto & pair : list)
   {

      set_at(pair.m_element1, pair.m_element2);

   }

}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::map(association pairs[], i32 iCount)
{
   construct();
   for(i32 i = 0; i < iCount; i++)
   {
      set_at(pairs[i].element1(), pairs[i].element2());
   }
}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::map(const map & m)
{
   
   construct();

   for(auto & pair : m)
   {

      set_at(pair.element1(), pair.element2());

   }

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::erase_all()
{

   //ASSERT_VALID(this);

   if(::is_set(this->m_begin))
   {
      // destroy elements (values and keys)
      iterator iteratorNext;

      for (auto iterator = this->begin(); this->iterator_ok(iterator); iterator = iteratorNext)
      {

         iteratorNext = iterator + 1;

         delete iterator.get();

      }

   }

   this->m_hashtable.erase_all();

   this->m_nCount = 0;
   //this->m_passociationFree = nullptr;

   //if(m_pplex != nullptr)
   //{

   //   m_pplex->FreeDataChain();
   //   m_pplex = nullptr;

   //}

   this->m_begin = nullptr;

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::clear()
{
   erase_all();
}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::Empty()
{
   clear();
}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::~map()
{
   erase_all();
   ASSERT(this->m_nCount == 0);
}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::attach(iterator iterator, ::u32 nHashBucket, ::u32 nHashValue)
{

   //this->m_passociationFree  = this->m_passociationFree->m_next;

//zero_pointer(iterator);

   hash(iterator, nHashBucket, nHashValue);

   if (::is_set(this->m_begin))
   {

      this->m_begin->m_back = iterator.get();

   }

   iterator->m_next = this->m_begin.get();

   this->m_begin = iterator;

   this->m_begin->m_back = nullptr;

   this->m_nCount++;

   ASSERT(this->m_nCount > 0);  // make sure we don't overflow

   //return iterator;

}




template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::hash(iterator iterator, ::u32 nHashBucket, ::u32 nHashValue)
{

   // not precise (memleak? a watch dog can restart from the last check point... continuable tasks need...) but self-healing(self-recoverable/not-fatal)...
   if (::is_null(this->m_hashtable.m_ppassociationHash))
   {

      InitHashTable(this->m_hashtable.GetHashTableSize());

   }

   if (::is_set(this->m_hashtable.m_ppassociationHash[nHashBucket]))
   {
      
      this->m_hashtable.m_ppassociationHash[nHashBucket]->m_pbackHash = &iterator->m_nextHash;

   }

   iterator->m_nextHash = this->m_hashtable.m_ppassociationHash[nHashBucket];

   this->m_hashtable.m_ppassociationHash[nHashBucket] = iterator.get();

   iterator->m_pbackHash = &this->m_hashtable.m_ppassociationHash[nHashBucket];

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::iterator
map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::new_association(ARG_KEY key, ::u32 nHashBucket, ::u32 nHashValue)
{

   //if(this->m_passociationFree == nullptr)
   //{
   //   // add another block
   //   //plex * newBlock = plex::create(m_pplex, m_nBlockSize, sizeof(map::association));
   //   //// chain them into free list
   //   //map::iterator iterator = (map::iterator) newBlock->data();
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

   auto iterator = memory_new association(key);

   attach(iterator, nHashBucket, nHashValue);

   return iterator;

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
bool map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::erase(iterator iterator)
{

   detach(iterator);

   delete iterator.get();

   return true;

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::detach(iterator iterator)
{

   unhash(iterator);

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

   //iterator->m_next = this->m_passociationFree;

   //this->m_passociationFree = iterator;

   this->m_nCount--;

   ASSERT(this->m_nCount >= 0);  // make sure we don't underflow

   // if no more elements, cleanup completely
   if (this->m_nCount == 0)
      erase_all();

}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::hash(::u32& nHashBucket, ::u32& nHashValue, ARG_KEY key) const
{

   nHashValue = u32_hash<ARG_KEY>(key).m_u;

   nHashBucket = nHashValue % this->m_hashtable.GetHashTableSize();

}

//template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
//inline typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::const_iterator
//map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::association_at(ARG_KEY key, ::u32 & nHashBucket, ::u32 & nHashValue) const
//{
//
//   return (const_iterator &) ((map *)this)->association_at(key, nHashBucket, nHashValue);
//
//}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::iterator
map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::association_at(ARG_KEY key, ::u32& nHashBucket, ::u32& nHashValue) const
{

   hash(nHashBucket, nHashValue, key);

   if (get_count() <= 0)
   {

      return nullptr;

   }

   for(auto iterator = this->m_hashtable.m_ppassociationHash[nHashBucket]; ::is_set(iterator); iterator = iterator->m_nextHash)
   {

      if (EqualElements<ARG_KEY>(iterator->element1(), key))
      {

         return iterator;

      }

   }

   return nullptr;

}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::move(map* pmap, ARG_KEY key)
{

   ::u32 uHashBucket;

   ::u32 uHashValue;

   auto iterator = pmap->association_at(key, uHashBucket, uHashValue);

   pmap->detach(iterator);

   attach(iterator, uHashBucket, uHashValue);

}



template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::move(iterator iterator, map * pmap)
{

   if (pmap == this)
   {

      return;

   }

   if (::is_set(pmap))
   {

      pmap->detach(iterator);

   }

   ::u32 nHashBucket;

   ::u32 nHashValue;

   hash(nHashBucket, nHashValue, iterator->element1());

   attach(iterator, nHashBucket, nHashValue);

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
bool map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::lookup(ARG_KEY key, VALUE& rValue) const
{
   //ASSERT_VALID(this);

   ::u32 nHashBucket, nHashValue;

   iterator iterator = association_at(key, nHashBucket, nHashValue);

   if (iterator == nullptr)
   {

      return false;  // not in map

   }

   rValue = iterator->element2();

   return true;

}


//template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
//typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::iterator map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::find (ARG_KEY key)
//{
//   return iterator(plookup(key), this);
//}
//
//template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
//typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::const_iterator map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::find (ARG_KEY key) const
//{
//   return const_iterator((iterator) plookup(key), (map *) this);
//}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
const typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::iterator map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::plookup(ARG_KEY key) const
{
   //ASSERT_VALID(this);

   ::u32 nHashBucket, nHashValue;
   iterator iterator = association_at(key, nHashBucket, nHashValue);
   return iterator;
}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::iterator map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::plookup(ARG_KEY key)
{

   ::u32 nHashBucket, nHashValue;

   iterator iterator = association_at(key, nHashBucket, nHashValue);

   return iterator;

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
VALUE * map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::pget(ARG_KEY key)
{

   auto iterator = plookup(key);

   if (iterator.is_null())
   {

      return nullptr;

   }

   return &iterator->element2();

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::iterator map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::find_association(ARG_KEY key) const
{

   ::u32 nHashBucket, nHashValue;

   return association_at(key, nHashBucket, nHashValue);

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::iterator map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::get_association(ARG_KEY key) const
{

   ::u32 nHashBucket,nHashValue;

   iterator iterator;

   if((iterator = association_at(key,nHashBucket,nHashValue)).is_null())
   {

      iterator = ((map*)this)->new_association(key, nHashBucket, nHashValue);

   }

   return iterator;

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline VALUE& map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::operator[](ARG_KEY key)
{

   return get_association(key)->element2();  // return memory_new matter

}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline const VALUE & map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::operator[](ARG_KEY key) const
{

   return get_association(key)->element2();  // return memory_new matter

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline bool map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::unhash(iterator iterator)
// erase - return true if erased
{

   if(::is_set(iterator->m_nextHash))
   {

      iterator->m_nextHash->m_pbackHash = iterator->m_pbackHash;

   }

   *iterator->m_pbackHash = iterator->m_nextHash;

   return true;

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline ::count map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::count(const KEY & key) const
{

   return this->plookup(key) != nullptr ? 1 : 0;

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
bool map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::has(const KEY & key) const
{

   return this->plookup(key) != nullptr ? 1 : 0;

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
bool map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::contains(const KEY & key) const
{

   return this->plookup(key) != nullptr ? 1 : 0;

}


//template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
//void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::get_next(iterator & iterator,
//      KEY& rKey, VALUE& rValue) const
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
//template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
//inline const typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::iterator
//map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::get_next(const iterator iterator) const
//{
//
//   return iterator->m_next;
//
//}

//
//template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
//inline typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::iterator
//map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::get_next(const iterator iterator)
//{
//
//   return iterator->m_next;
//
//}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
VALUE map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR > ::
get(ARG_KEY argkey, ARG_VALUE valueDefault)
{
   iterator iterator = plookup(argkey);
   if(iterator == nullptr)
      return valueDefault;
   else
      return iterator->element2();
}


//template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
//void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::assert_ok() const
//{
//
//   ::matter::assert_ok();
//
//   ASSERT(GetHashTableSize() > 0);
//
//   ASSERT(this->m_nCount == 0 || this->m_hashtable.m_ppassociationHash != nullptr);
//   // non-empty map should have hash table
//
//}
//

template < class VALUE, typename ARG_VALUE = typename argument_of < VALUE >::type >
using double_map = map < double, VALUE, typename argument_of < double >::type, ARG_VALUE >;

using double_to_double = double_map < double >;

template < class VALUE, typename ARG_VALUE = typename argument_of < VALUE >::type >
using dword_map = map < ::u32, VALUE, typename argument_of < ::u32 >::type, ARG_VALUE >;

template < class VALUE, typename ARG_VALUE = typename argument_of < VALUE >::type >
using uptr_map = map < uptr, VALUE, typename argument_of < uptr >::type, ARG_VALUE >;

template < typename KEY_TYPE, typename VALUE_TYPE >
class key_value
{
public:


   using KEY = KEY_TYPE;
   using VALUE = VALUE_TYPE;
   using TYPE1 = KEY;
   using TYPE2 = VALUE;
   using ARG_TYPE1 = typename argument_of < TYPE1 >::type;
   using ARG_TYPE2 = typename argument_of < TYPE2 >::type;


   // Contract
   // KEY & element1();
   // VALUE & element2();
   // const KEY & element1() const;
   // const VALUE & element2() const;

};


template < typename PAIR >
using pair_map = map <  typename PAIR::TYPE1, typename PAIR::TYPE2, typename PAIR::ARG_TYPE1, const typename PAIR::ARG_TYPE2, PAIR >;


#define __declare_key_value(xkeyvaluetype, xkeytype, xkey, xvaluetype, xvalue) \
struct xkeyvaluetype : public ::key_value < xkeytype, xvaluetype > \
{ \
\
   PAIR_DEFAULT_IMPL(xkeyvaluetype, KEY, VALUE, const KEY &, const VALUE &, xkey, xvalue); \
}


#ifdef CPP17
#define __declare_pair_tuple_size(pair) \
template<> ALIENATED_ANDROID_ANARCHY ::std::tuple_size< pair > : ::std::integral_constant<size_t, 2> {} }
#endif


#define __declare_map(xmaptype, xkeyvaluetype, xkeytype, xkey, xvaluetype, xvalue) \
__declare_key_value(xkeyvaluetype, xkeytype, xkey, xvaluetype, xvalue); \
using xmaptype = pair_map < xkeyvaluetype >


#ifdef CPP17
#define __declare_map_key_value(xmaptype, xkeyvaluetype, xkeytype, xkey, xvaluetype, xvalue) \
__declare_map(xkeyvaluetype, xkeytype, xkey, xvaluetype, xvalue); \
__declare_pair_tuple_size(xmaptype)
#else

#define __declare_map_key_value(xmaptype, xkeyvaluetype, xkeytype, xkey, xvaluetype, xvalue) \
__declare_map(xkeyvaluetype, xkeytype, xkey, xvaluetype, xvalue);

#endif



template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::InitHashTable(
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


//template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
//void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::dump(dump_context& dumpcontext) const
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
//   //      dump_elements<KEY>(dumpcontext, &iterator->element1(), 1);
//   //      dumpcontext << "] = ";
//   //      dump_elements<VALUE>(dumpcontext, &iterator->element2(), 1);
//   //   }
//   //}
//
//   //dumpcontext << "\n";
//}
//
//




