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
   

   typedef typename BASE_SET::association             association;
   typedef typename association::payload              pair;

   //using iterator_struct = BASE_SET::iterator_struct;
   //using const_iterator_struct = BASE_SET::const_iterator_struct;
   //using key_iterator = BASE_SET::key_iterator;
   //using iterator = BASE_SET::iterator;
   //using const_iterator = BASE_SET::const_iterator;
   //sing make_iterator = BASE_SET::make_iterator;

   __declare_iterator_struct_ok(map, association *, m_passociation, ::is_set(this->m_passociation));


   template < typename ITERATOR > 
   struct make_iterator : public ITERATOR
   {



      using CONTAINER = typename ITERATOR::CONTAINER;

      using ITERATOR::ITERATOR;

      make_iterator()
      {
         this->m_passociation = (association*)nullptr;
         this->m_pcontainer = (CONTAINER*)nullptr;
         this->m_passociationBeg = (association*)nullptr;
         this->m_passociationEnd = (association*) nullptr;
      }

      make_iterator(const association* passociation, const CONTAINER* pset = nullptr)
      {
         this->m_passociation = (association*)passociation;
         this->m_pcontainer = (CONTAINER*)pset;
         this->m_passociationBeg = (association*)passociation;
         this->m_passociationEnd = (association*) nullptr;
      }


      make_iterator(const make_iterator& iterator)
      {
         this->m_passociation = iterator.m_passociation;
         this->m_pcontainer = iterator.m_pcontainer;
         this->m_passociationBeg = (association*)iterator.m_passociationBeg;
         this->m_passociationEnd = (association*)iterator.m_passociationEnd;
      }


      make_iterator begin() const
      {

         return make_iterator(this->m_pcontainer->get_start(), this->m_pcontainer);

      }


      make_iterator end() const
      {

         return make_iterator(nullptr, this->m_pcontainer);

      }


      make_iterator& operator ++ ()
      {

         this->m_passociation = this->m_passociation->m_pnext;

         return *this;

      }

      template < typename PRED >
      void each(PRED pred)
      {

         while (this->ok())
         {

#ifdef CPP17

            if (returns_false(pred, true, this->operator *()))
            {

               break;

            }

#else

            pred(this->operator *());

            //if (returns_false(pred, true, this->operator *()))
            //{

              // break;

            //}


#endif

            this->operator++();

         }

      }


      make_iterator operator ++ (i32)
      {

         make_iterator iterator = this->m_passociation;

         this->m_passociation = this->m_passociation->m_pnext;

         return iterator;

      }


      bool operator == (const make_iterator& it) const
      {

         if (this == &it)
         {

            return true;

         }

         if (this->m_passociation == nullptr && it.m_passociation == nullptr && it.m_pcontainer == nullptr)
         {

            return true;

         }

         if (this->m_pcontainer != it.m_pcontainer)
         {

            return false;

         }

         return this->m_passociation == it.m_passociation;

      }



      bool operator != (const make_iterator& it) const
      {

         return !operator == (it);

      }


      make_iterator& operator = (const make_iterator& it)
      {

         if (this != &it)
         {

            this->m_pcontainer = it.m_pcontainer;

            this->m_passociation = it.m_passociation;

         }

         return *this;

      }

   };


   __declare_iterator(dereferenced_value_iterator, this->m_passociation->element2());
   __declare_iterator(value_iterator, &this->m_passociation->element2());
   __declare_iterator(key_iterator, &this->m_passociation->element1());
   __declare_iterator(iterator, this->m_passociation);


   using deferenced_iterator = dereferenced_value_iterator;


   //HASH_TABLE           this->m_hashtable;
   //::count              this->m_nCount;
   //association *              m_passociationHead;


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


   inline iterator begin() { return iterator(get_start(), this); }
   inline iterator end() { return iterator(nullptr, this); }


   inline const_iterator begin() const { return const_iterator(((map *)this)->get_start(), this); }
   inline const_iterator end() const { return const_iterator(nullptr, (map *)this); }


   //lookup
   bool lookup(ARG_KEY key, VALUE& rValue) const;
   const association * plookup(ARG_KEY key) const;
   association * plookup(ARG_KEY key);

   
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

   inline association * get_association(ARG_KEY key);
   inline association * get_association(ARG_KEY key) const
   {
      return ((map *) this)->get_association(key);
   }
   association * find_association(ARG_KEY key) const;

   //add a memory_new (key, value) association
   association * set_at(ARG_KEY key, ARG_VALUE newValue)
   {

      association* passociation = get_association(key);

      passociation->element2() = newValue;

      return passociation;

   }


   //add a memory_new (key, value) association
   virtual void set_payload(const PAIR & pair) override
   {
      set_at(pair.key(), pair.value());
   }


   bool unhash(association * passociation);

   //removing existing (key, ?) association
   inline bool erase_key(ARG_KEY key) { auto passociation = find_association(key);  return ::is_set(passociation) ? erase(passociation) : false; }

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

   inline auto pairs() { return iterator(nullptr, this); }
   inline auto pairs() const { return const_iterator(nullptr, this); }
   inline auto values() const { return value_iterator(nullptr, this); }
   inline auto keys() const { return key_iterator(nullptr, this); }



   ::count count(const KEY & t) const;
   bool has(const KEY & t) const;
   bool contains(const KEY & t) const;

   //iterating all (key, value) pairs
//   POSITION get_start_position() const;

   inline const association * get_start() const;
   inline association * get_start();

   void get_next(association * & rNextPosition, KEY& rKey, VALUE& rValue) const;

   const association * get_next(const association *passociationRet) const;
   association * get_next(const association *passociationRet);

   //advanced features for derived classes
   ::u32 GetHashTableSize() const
   {
      
      return this->m_hashtable.GetHashTableSize();
      
   }
   
   
   void InitHashTable(::u32 hashSize,bool bAllocNow = true);


   VALUE get(ARG_KEY argkey, ARG_VALUE valueDefault);


   association * next(association * & passociation)
   {
      if(passociation == nullptr)
      {
         passociation = get_start();
      }
      else
      {
         passociation = get_next(passociation);
      }
      return passociation;
   }

   const association * next(const association * & passociation) const
   {
      if(passociation == nullptr)
      {
         passociation = get_start();
      }
      else
      {
         passociation = get_next(passociation);
      }
      return passociation;
   }


   void set(map & map)
   {
      association * passociation = nullptr;
      while(map.next(passociation) != nullptr)
      {
         set_at(passociation->element1(), passociation->element2());
      }
   }

   //inline association * find_item(ARG_KEY key) const { return find_association(key); }

   inline iterator find(ARG_KEY key) { return { find_association(key), this }; }
   const_iterator find (ARG_KEY key) const { return { find_association(key), this }; }


   association * new_association(ARG_KEY key, ::u32 nHashBucket, ::u32 nHashValue);
   inline void hash(association *, ::u32 nHashBucket, ::u32 nHashValue);
   void attach(association * passociation, ::u32 nHashBucket, ::u32 nHashValue);
   bool erase(association * passociation);
   void detach(association* passociation);
   void hash(::u32& nHashBucket, ::u32& nHashValue, ARG_KEY) const;
   inline association * get_association_at(ARG_KEY, ::u32& nHashBucket, ::u32& nHashValue) const;

   void move(association* passociation, map * pmap = nullptr);
   void move(map* pmap, ARG_KEY key);

   //// void assert_ok() const override;
   //void dump(dump_context & dumpcontext) const override;



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

   ::range < iterator > elements()
   {
      return range < iterator >(begin(),end());
   }
   const_range < const_iterator > elements() const
   {
      return const_range < const_iterator >(begin(),end());
   }

   PAIR & element_at(::index iIndex)
   {
      return this->elements().element_at(iIndex);
   }

   template < typename PRED >
   typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::association * predicate_find(PRED pred)
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

     for(auto & pvalue : values())
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
//typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::association * map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::set_at(ARG_KEY key,ARG_VALUE newValue)


//template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
//inline typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::association * map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::get_start() const
//{
//   return (this->m_nCount == 0) ? nullptr : BEFORE_START_POSITION;
//}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline const typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::association* map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::get_start() const
{

   return this->m_passociationHead;

}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::association* map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::get_start()
{

   return this->m_passociationHead;

}


/////////////////////////////////////////////////////////////////////////////
// map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR > out-of-line functions
template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::construct()
{

   this->m_nCount          = 0;

   this->m_passociationHead      = nullptr;
   
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

   if(this->m_passociationHead != nullptr)
   {
      // destroy elements (values and keys)

      association * passociation;

      association * passociationNext = nullptr;

      for (passociation = this->m_passociationHead; passociation != nullptr; passociation = passociationNext)
      {

         passociationNext = passociation->m_pnext;

         delete passociation;

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

   this->m_passociationHead = nullptr;

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
void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::attach(association * passociation, ::u32 nHashBucket, ::u32 nHashValue)
{

   //this->m_passociationFree  = this->m_passociationFree->m_pnext;

//zero_pointer(passociation);

   hash(passociation, nHashBucket, nHashValue);

   if (this->m_passociationHead != nullptr)
   {

      this->m_passociationHead->m_pprev = passociation;

   }

   passociation->m_pnext = this->m_passociationHead;

   this->m_passociationHead = passociation;

   this->m_passociationHead->m_pprev = nullptr;

   this->m_nCount++;

   ASSERT(this->m_nCount > 0);  // make sure we don't overflow

   //return passociation;

}




template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::hash(association* passociation, ::u32 nHashBucket, ::u32 nHashValue)
{

   // not precise (memleak? a watch dog can restart from the last check point... continuable tasks need...) but self-healing(self-recoverable/not-fatal)...
   if (::is_null(this->m_hashtable.m_ppassociationHash))
   {

      InitHashTable(this->m_hashtable.GetHashTableSize());

   }

   if (this->m_hashtable.m_ppassociationHash[nHashBucket] != nullptr)
   {
      
      this->m_hashtable.m_ppassociationHash[nHashBucket]->m_ppprevHash = &passociation->m_pnextHash;

   }

   passociation->m_pnextHash = this->m_hashtable.m_ppassociationHash[nHashBucket];

   this->m_hashtable.m_ppassociationHash[nHashBucket] = passociation;

   passociation->m_ppprevHash = &this->m_hashtable.m_ppassociationHash[nHashBucket];

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::association *
map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::new_association(ARG_KEY key, ::u32 nHashBucket, ::u32 nHashValue)
{

   //if(this->m_passociationFree == nullptr)
   //{
   //   // add another block
   //   //plex * newBlock = plex::create(m_pplex, m_nBlockSize, sizeof(map::association));
   //   //// chain them into free list
   //   //map::association* passociation = (map::association*) newBlock->data();
   //   //// free in reverse order to make it easier to debug
   //   //index i = m_nBlockSize - 1;
   //   //for (passociation = &passociation[i]; i >= 0; i--, passociation--)
   //   //{
   //   //   passociation->m_pnext = this->m_passociationFree;
   //   //   this->m_passociationFree = passociation;

   //   //}
   //   this->m_passociationFree = memory_new association();

   //}

   //ENSURE(this->m_passociationFree != nullptr);  // we must have something

   auto passociation = memory_new association(key);

   attach(passociation, nHashBucket, nHashValue);

   return passociation;

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
bool map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::erase(association * passociation)
{

   detach(passociation);

   delete passociation;

   return true;

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::detach(association* passociation)
{

   unhash(passociation);

   association* pnext = passociation->m_pnext;

   if (passociation->m_pnext != nullptr)
   {

      passociation->m_pnext->m_pprev = passociation->m_pprev;

   }

   if (passociation->m_pprev != nullptr)
   {

      passociation->m_pprev->m_pnext = passociation->m_pnext;

   }

   if (this->m_passociationHead == passociation)
   {

      this->m_passociationHead = pnext;

      if (this->m_passociationHead != nullptr)
      {

         this->m_passociationHead->m_pprev = nullptr;

      }

   }

   //delete passociation;

   //passociation->m_pnext = this->m_passociationFree;

   //this->m_passociationFree = passociation;

   this->m_nCount--;

   ASSERT(this->m_nCount >= 0);  // make sure we don't underflow

   // if no more elements, cleanup completely
   if (this->m_nCount == 0)
      erase_all();

}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::hash(::u32& nHashBucket, ::u32& nHashValue, ARG_KEY key) const
{

   nHashValue = u32_hash<ARG_KEY>(key);

   nHashBucket = nHashValue % this->m_hashtable.GetHashTableSize();

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::association *
map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::get_association_at(ARG_KEY key, ::u32& nHashBucket, ::u32& nHashValue) const
// find association (or return nullptr)
{

   hash(nHashBucket, nHashValue, key);

   if(get_count() <= 0)
      return nullptr;

   // see if it exists
   association * passociation;

   for(passociation = this->m_hashtable.m_ppassociationHash[nHashBucket]; passociation != nullptr; passociation = passociation->m_pnextHash)
   {

      if(EqualElements<ARG_KEY>(passociation->element1(), key))
         return passociation;

   }

   return nullptr;

}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::move(map* pmap, ARG_KEY key)
{

   ::u32 uHashBucket;

   ::u32 uHashValue;

   auto passociation = pmap->get_association_at(key, uHashBucket, uHashValue);

   pmap->detach(passociation);

   attach(passociation, uHashBucket, uHashValue);

}



template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::move(association* passociation, map * pmap)
{

   if (pmap == this)
   {

      return;

   }

   if (::is_set(pmap))
   {

      pmap->detach(passociation);

   }

   ::u32 nHashBucket;

   ::u32 nHashValue;

   hash(nHashBucket, nHashValue, passociation->element1());

   attach(passociation, nHashBucket, nHashValue);

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
bool map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::lookup(ARG_KEY key, VALUE& rValue) const
{
   //ASSERT_VALID(this);

   ::u32 nHashBucket, nHashValue;

   association* passociation = get_association_at(key, nHashBucket, nHashValue);

   if (passociation == nullptr)
      return false;  // not in map

   rValue = passociation->element2();

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
//   return const_iterator((association *) plookup(key), (map *) this);
//}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
const typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::association* map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::plookup(ARG_KEY key) const
{
   //ASSERT_VALID(this);

   ::u32 nHashBucket, nHashValue;
   association* passociation = get_association_at(key, nHashBucket, nHashValue);
   return passociation;
}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::association* map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::plookup(ARG_KEY key)
{
   //ASSERT_VALID(this);

   ::u32 nHashBucket, nHashValue;
   association* passociation = get_association_at(key, nHashBucket, nHashValue);
   return passociation;
}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
VALUE * map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::pget(ARG_KEY key)
{
   association * point = plookup(key);
   if(point)
      return &point->element2();
   else
      return nullptr;
}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::association * map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::find_association(ARG_KEY key) const
{

   //ASSERT_VALID(this);

   ::u32 nHashBucket, nHashValue;

   return get_association_at(key, nHashBucket, nHashValue);

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::association * map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::get_association(ARG_KEY key)
{

   //ASSERT_VALID(this);

   ::u32 nHashBucket,nHashValue;

   association * passociation;

   if((passociation = get_association_at(key,nHashBucket,nHashValue)) == nullptr)
   {

      passociation = new_association(key, nHashBucket, nHashValue);

   }

   return passociation;

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
inline bool map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::unhash(association * passociation)
// erase - return true if erased
{

   if(passociation->m_pnextHash != nullptr)
   {

      passociation->m_pnextHash->m_ppprevHash = passociation->m_ppprevHash;

   }

   *passociation->m_ppprevHash = passociation->m_pnextHash;

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


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::get_next(association * & passociation,
      KEY& rKey, VALUE& rValue) const
{

   rKey = passociation->element1();

   rValue = passociation->element2();

   passociation = passociation->m_pnext;

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline const typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::association*
map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::get_next(const association * passociation) const
{

   return passociation->m_pnext;

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::association*
map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::get_next(const association * passociation)
{

   return passociation->m_pnext;

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
VALUE map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR > ::
get(ARG_KEY argkey, ARG_VALUE valueDefault)
{
   association * passociation = plookup(argkey);
   if(passociation == nullptr)
      return valueDefault;
   else
      return passociation->element2();
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
   using ARG_TYPE1 = typename argument_of < KEY & >::type;
   using TYPE2 = VALUE;
   using ARG_TYPE2 = typename argument_of < const VALUE & >::type;


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
//   //   const association* passociation = get_start();
//   //   while (passociation != nullptr)
//   //   {
//   //      passociation = get_next(passociation);
//   //      dumpcontext << "\n\t[";
//   //      dump_elements<KEY>(dumpcontext, &passociation->element1(), 1);
//   //      dumpcontext << "] = ";
//   //      dump_elements<VALUE>(dumpcontext, &passociation->element2(), 1);
//   //   }
//   //}
//
//   //dumpcontext << "\n";
//}
//
//




