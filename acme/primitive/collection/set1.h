#pragma once


#define new ACME_NEW


template < typename ELEMENT, const int DEFAULT_HASH_TABLE_SIZE = 17 >
class set_dynamic_hash_table
{
public:

   typedef set_element_item < ELEMENT >  SET_ELEMENT_ITEM;

   SET_ELEMENT_ITEM * m_assocHashDefault[DEFAULT_HASH_TABLE_SIZE];
   SET_ELEMENT_ITEM ** m_ppassocHash;
   ::u32              m_nHashTableSize;

   set_dynamic_hash_table()
   {

      m_ppassocHash = nullptr;

      m_nHashTableSize = DEFAULT_HASH_TABLE_SIZE;

   }


   ::u32 GetHashTableSize() const
   {

      return m_nHashTableSize;

   }


   void InitHashTable(::u32 nHashSize, bool bAllocNow = true)
   {

      if (m_ppassocHash != nullptr && m_ppassocHash != m_assocHashDefault && m_nHashTableSize > DEFAULT_HASH_TABLE_SIZE)
      {

         delete[] m_ppassocHash;

      }

      m_ppassocHash = nullptr;

      if (bAllocNow)
      {

         if (nHashSize <= DEFAULT_HASH_TABLE_SIZE)
         {

            m_ppassocHash = m_assocHashDefault;

         }
         else
         {

            m_ppassocHash = new SET_ELEMENT_ITEM * [nHashSize];

            ENSURE(m_ppassocHash != nullptr);

         }

         ::zero(m_ppassocHash, sizeof(SET_ELEMENT_ITEM *) * nHashSize);

      }

      m_nHashTableSize = nHashSize;

   }

   void erase_all()
   {

      if (m_ppassocHash != nullptr && m_ppassocHash != m_assocHashDefault && m_nHashTableSize > DEFAULT_HASH_TABLE_SIZE)
      {

         delete[] m_ppassocHash;

      }

      m_ppassocHash = nullptr;

   }


};


template < int m_nHashTableSize, typename ELEMENT >
class set_fixed_hash_table
{
public:


   typedef set_element_item < ELEMENT > SET_ELEMENT_ITEM;


   SET_ELEMENT_ITEM * m_ppassocHash[m_nHashTableSize];

   set_fixed_hash_table()
   {
      zero(m_ppassocHash, sizeof(m_ppassocHash));
   }


   ::u32 GetHashTableSize() const
   {
      return m_nHashTableSize;
   }
   void InitHashTable(::u32 hashSize, bool bAllocNow = true) {  }

   void erase_all()
   {
      zero(m_ppassocHash, sizeof(m_ppassocHash));
   }

};


template <class ELEMENT, class ARG_ELEMENT = const ELEMENT & >
class set :
   public ::matter
{
public:


   typedef set_dynamic_hash_table < ELEMENT >      HASH_TABLE;
   typedef ELEMENT                                 BASE_ELEMENT;
   typedef ARG_ELEMENT                             BASE_ARG_ELEMENT;


   typedef ::set_element_item < ELEMENT >               SET_ELEMENT_ITEM;


   __declare_iterator_struct_ok(set, SET_ELEMENT_ITEM *, m_pelement, ::is_set(this->m_pelement));


   template < typename ITERATOR > struct make_iterator : ITERATOR
   {

      using CONTAINER = typename ITERATOR::CONTAINER;

      using ITERATOR::ITERATOR;

      make_iterator()
      {
         this->m_pelement = (SET_ELEMENT_ITEM *)nullptr;
         this->m_pcontainer = (CONTAINER *)nullptr;
         this->m_passocBeg = (SET_ELEMENT_ITEM *)nullptr;
         this->m_passocEnd = (SET_ELEMENT_ITEM *) nullptr;
      }

      make_iterator(const SET_ELEMENT_ITEM * pelement, const CONTAINER * pset = nullptr)
      {
         this->m_pelement = (SET_ELEMENT_ITEM *)pelement;
         this->m_pcontainer = (CONTAINER *)pset;
         this->m_pelementBeg = (SET_ELEMENT_ITEM *)pelement;
         this->m_pelementEnd = (SET_ELEMENT_ITEM *) nullptr;
      }


      make_iterator(const make_iterator & iterator)
      {
         this->m_pelement = iterator.m_pelement;
         this->m_pcontainer = iterator.m_pcontainer;
         this->m_pelementBeg = (SET_ELEMENT_ITEM *)iterator.m_pelementBeg;
         this->m_pelementEnd = (SET_ELEMENT_ITEM *)iterator.m_pelementEnd;
      }


      make_iterator begin() const
      {

         return make_iterator(this->m_pcontainer->get_start(), this->m_pcontainer);

      }


      make_iterator end() const
      {

         return make_iterator(nullptr, this->m_pcontainer);

      }


      make_iterator & operator ++ ()
      {

         this->m_pelement = this->m_pelement->m_pnext;

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

         make_iterator iterator = this->m_pelement;

         this->m_pelement = this->m_pelement->m_pnext;

         return iterator;

      }


      bool operator == (const make_iterator & it) const
      {

         if (this == &it)
         {

            return true;

         }

         if (this->m_pelement == nullptr && it.m_pelement == nullptr && it.m_pcontainer == nullptr)
         {

            return true;

         }

         if (this->m_pcontainer != it.m_pcontainer)
         {

            return false;

         }

         return this->m_pelement == it.m_pelement;

      }



      bool operator != (const make_iterator & it) const
      {

         return !operator == (it);

      }


      make_iterator & operator = (const make_iterator & it)
      {

         if (this != &it)
         {

            this->m_pcontainer = it.m_pcontainer;

            this->m_pelement = it.m_pelement;

         }

         return *this;

      }

   };


   __declare_iterator(dereferenced_value_iterator, this->m_pelement);
   __declare_iterator(value_iterator, &this->m_pelement);
   __declare_iterator(key_iterator, &this->m_pelement);
   __declare_iterator(iterator, this->m_pelement);


   using deferenced_iterator = dereferenced_value_iterator;


   HASH_TABLE           m_hashtable;
   ::count              m_nCount;
   SET_ELEMENT_ITEM *        m_pelementHead;


   set();
   set(SET_ELEMENT_ITEM pairs[], i32 iCount);
   set(const ::std::initializer_list < ELEMENT > & list);
   set(const set & m);
   virtual ~set();

   void construct();

   ::count get_count() const;
   ::count get_size() const;
   ::count size() const;
   ::count count() const;
   bool is_empty() const;
   bool empty() const;


   inline iterator begin() { return iterator(get_start(), this); }
   inline iterator end() { return iterator(nullptr, this); }


   inline const_iterator begin() const { return const_iterator(((set *)this)->get_start(), this); }
   inline const_iterator end() const { return const_iterator(nullptr, (set *)this); }


   //lookup
   bool contains(ARG_ELEMENT key) const;
   const SET_ELEMENT_ITEM * pfind(ARG_ELEMENT key) const;
   SET_ELEMENT_ITEM * pfind(ARG_ELEMENT key);

   ELEMENT * element_at(ARG_ELEMENT key);


   template < typename TELEMENT >
   auto pop(const TELEMENT & key)
   {

      auto value = operator[](key);

      erase_key(key);

      return value;

   }

   //Operations
   //lookup and add if not there
   ELEMENT & operator[](ARG_ELEMENT key);
   const ELEMENT & operator[](ARG_ELEMENT key) const;

   SET_ELEMENT_ITEM * get_assoc(ARG_ELEMENT key);
   SET_ELEMENT_ITEM * get_assoc(ARG_ELEMENT key) const
   {
      return ((set *)this)->get_assoc(key);
   }
   SET_ELEMENT_ITEM * find_element(ARG_ELEMENT key) const;

   //add a new (key, value) SET_ELEMENT_ITEM
   SET_ELEMENT_ITEM * add(ARG_ELEMENT key);

   bool erase(SET_ELEMENT_ITEM * pelement);

   //removing existing (key, ?) SET_ELEMENT_ITEM
   inline bool erase(ARG_ELEMENT key) { auto pitem = find_item(key);  return ::is_set(pitem) ? erase(pitem) : false; }

   template < typename ITERATOR >
   inline ITERATOR erase(ITERATOR it) { return ::papaya::iterator::erase(*this, it); }

   template < typename ITERATOR >
   inline void erase(const ITERATOR & begin, const ITERATOR & last) { ::erase(*this, begin, last); }

   void erase_all();
   void clear();
   void Empty();

   //inline ::range < iterator > elements() { return iterator(nullptr, this); }
   //inline const_range < const_iterator > elements() const { return const_iterator(nullptr, this); }
   inline auto values() const { return value_iterator(nullptr, this); }



   ::count count(const ELEMENT & t) const;
   bool has(const ELEMENT & t) const;
   //bool contains(const ELEMENT & t) const;

   //iterating all (key, value) pairs
//   POSITION get_start_position() const;

   const SET_ELEMENT_ITEM * get_start() const;
   SET_ELEMENT_ITEM * get_start();

   void get_next(SET_ELEMENT_ITEM *& rNextPosition, ELEMENT & rKey, ELEMENT & rValue) const;

   const SET_ELEMENT_ITEM * get_next(const SET_ELEMENT_ITEM * passocRet) const;
   SET_ELEMENT_ITEM * get_next(const SET_ELEMENT_ITEM * passocRet);

   //advanced features for derived classes
   ::u32 GetHashTableSize() const
   {
      return m_hashtable.GetHashTableSize();
   }
   void InitHashTable(::u32 hashSize, bool bAllocNow = true);


   ELEMENT get(ARG_ELEMENT argkey, ARG_ELEMENT valueDefault);


   SET_ELEMENT_ITEM * next(SET_ELEMENT_ITEM *& pelement)
   {
      if (pelement == nullptr)
      {
         pelement = get_start();
      }
      else
      {
         pelement = get_next(pelement);
      }
      return pelement;
   }

   const SET_ELEMENT_ITEM * next(const SET_ELEMENT_ITEM *& pelement) const
   {
      if (pelement == nullptr)
      {
         pelement = get_start();
      }
      else
      {
         pelement = get_next(pelement);
      }
      return pelement;
   }


   void copy(set & set)
   {
      SET_ELEMENT_ITEM * pelement = nullptr;
      while (set.next(pelement) != nullptr)
      {
         set_at(pelement->element1(), pelement->element2());
      }
   }

   inline SET_ELEMENT_ITEM * find_item(ARG_ELEMENT key) const { return find_element(key); }

   inline iterator find(ARG_ELEMENT key) { return { find_item(key), this }; }
   const_iterator find(ARG_ELEMENT key) const { return { find_item(key), this }; }


   SET_ELEMENT_ITEM * new_element(ARG_ELEMENT key);
   void free_element(SET_ELEMENT_ITEM * pelement);
   SET_ELEMENT_ITEM * get_element_at(ARG_ELEMENT, ::u32 &, ::u32 &) const;


   void assert_valid() const override;
   void dump(dump_context & dumpcontext) const override;



   template < class ARRAY >
   bool erase_key_array(ARRAY a)
   {

      bool bRemoved = false;

      for (index i = 0; i < a.get_count(); i++)
      {

         bRemoved |= erase_key(a[i]);

      }

      return bRemoved;

   }

   template < class ARRAY >
   ::count erase_assoc_array(ARRAY a)
   {

      ::count countRemoved = 0;

      for (index i = 0; i < a.get_count(); i++)
      {

         if (erase_assoc(a[i]))
         {

            countRemoved++;

         }

      }

      return countRemoved;

   }

   virtual void on_after_read() {}

   ::range < iterator > elements()
   {
      return range < iterator >(begin(), end());
   }
   const_range < const_iterator > elements() const
   {
      return const_range < const_iterator >(begin(), end());
   }

   ELEMENT & element_at(::index iIndex)
   {
      return elements().element_at(iIndex);
   }

   template < typename PRED >
   typename set < ELEMENT, ARG_ELEMENT >::SET_ELEMENT_ITEM * predicate_find(PRED pred)
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
   __pointer(TYPE) get_typed_ptr(index i = 0)
   {

      __pointer(TYPE) p;

      for (auto & pvalue : values())
      {

         p = pvalue;

         if (p)
         {

            if (i <= 0)
            {

               return p;

            }

            i--;

         }

      }

      return nullptr;

   }


};


template < class ELEMENT, class ARG_ELEMENT >
inline ::count set < ELEMENT, ARG_ELEMENT >::get_count() const
{
   return m_nCount;
}

template < class ELEMENT, class ARG_ELEMENT >
inline ::count set < ELEMENT, ARG_ELEMENT >::get_size() const
{
   return m_nCount;
}

template < class ELEMENT, class ARG_ELEMENT >
inline ::count set < ELEMENT, ARG_ELEMENT >::count() const
{
   return m_nCount;
}

template < class ELEMENT, class ARG_ELEMENT >
inline ::count set < ELEMENT, ARG_ELEMENT >::size() const
{
   return m_nCount;
}

template < class ELEMENT, class ARG_ELEMENT >
set< ELEMENT, ARG_ELEMENT > & set < ELEMENT, ARG_ELEMENT >::operator = (const set & m)
{
   if (this != &m)
   {

      erase_all();

      for (auto & SET_ELEMENT_ITEM : m)
      {

         set_at(SET_ELEMENT_ITEM.element1(), SET_ELEMENT_ITEM.element2());

      }

   }
   return *this;
}

template < class ELEMENT, class ARG_ELEMENT >
inline bool set < ELEMENT, ARG_ELEMENT >::is_empty() const
{
   return m_nCount == 0;
}

template < class ELEMENT, class ARG_ELEMENT >
inline bool set < ELEMENT, ARG_ELEMENT >::empty() const
{
   return m_nCount == 0;
}


template < class ELEMENT, class ARG_ELEMENT >
inline typename set < ELEMENT, ARG_ELEMENT >::SET_ELEMENT_ITEM * set < ELEMENT, ARG_ELEMENT >::add(ARG_ELEMENT element)
{

   SET_ELEMENT_ITEM * pelement = get_assoc(element);

   *pelement = element;

   return pelement;

}


//template < class ELEMENT, class ARG_ELEMENT >
//inline typename set < ELEMENT, ARG_ELEMENT >::SET_ELEMENT_ITEM * set < ELEMENT, ARG_ELEMENT >::get_start() const
//{
//   return (m_nCount == 0) ? nullptr : BEFORE_START_POSITION;
//}

template < class ELEMENT, class ARG_ELEMENT >
const typename set < ELEMENT, ARG_ELEMENT >::SET_ELEMENT_ITEM * set < ELEMENT, ARG_ELEMENT >::get_start() const
{

   return this->m_pelementHead;

}

template < class ELEMENT, class ARG_ELEMENT >
typename set < ELEMENT, ARG_ELEMENT >::SET_ELEMENT_ITEM * set < ELEMENT, ARG_ELEMENT >::get_start()
{

   return this->m_pelementHead;

}

//template < class ELEMENT, class ARG_ELEMENT >
//inline ::u32 set < ELEMENT, ARG_ELEMENT >::GetHashTableSize() const
//{
//
//   return m_nHashTableSize;
//
//}

/////////////////////////////////////////////////////////////////////////////
// set < ELEMENT, ARG_ELEMENT > out-of-line functions
template < class ELEMENT, class ARG_ELEMENT >
void set < ELEMENT, ARG_ELEMENT >::construct()
{

   //m_ppassocHash     = nullptr;
   //m_nHashTableSize  = 17;  // default size_i32
   m_nCount = 0;
   //   this->m_passocFree      = nullptr;
   //   m_pplex           = nullptr;
      // m_nBlockSize      = nBlockSize;
   this->m_pelementHead = nullptr;
}


template < class ELEMENT, class ARG_ELEMENT >
set < ELEMENT, ARG_ELEMENT >::set()
{

   construct();

}


template < class ELEMENT, class ARG_ELEMENT >
set < ELEMENT, ARG_ELEMENT >::set(const ::std::initializer_list < ELEMENT > & list)
{

   construct();

   for (auto & pair_item : list)
   {

      set_at(pair_item.m_element1, pair_item.m_element2);

   }

}

template < class ELEMENT, class ARG_ELEMENT >
set < ELEMENT, ARG_ELEMENT >::set(SET_ELEMENT_ITEM pairs[], i32 iCount)
{
   construct();
   for (i32 i = 0; i < iCount; i++)
   {
      set_at(pairs[i].element1(), pairs[i].element2());
   }
}

template < class ELEMENT, class ARG_ELEMENT >
set < ELEMENT, ARG_ELEMENT >::set(const set & m)
{
   construct();
   forallref(m)
   {
      set_at(item.element1(), item.element2());
   }
}

template < class ELEMENT, class ARG_ELEMENT >
void set < ELEMENT, ARG_ELEMENT >::erase_all()
{

   ASSERT_VALID(this);

   if (this->m_pelementHead != nullptr)
   {
      // destroy elements (values and keys)

      SET_ELEMENT_ITEM * pelement;

      SET_ELEMENT_ITEM * passocNext = nullptr;

      for (pelement = this->m_pelementHead; pelement != nullptr; pelement = passocNext)
      {

         passocNext = pelement->m_pnext;

         delete pelement;

      }

   }

   m_hashtable.erase_all();

   m_nCount = 0;
   //this->m_passocFree = nullptr;

   //if(m_pplex != nullptr)
   //{

   //   m_pplex->FreeDataChain();
   //   m_pplex = nullptr;

   //}

   this->m_pelementHead = nullptr;

}


template < class ELEMENT, class ARG_ELEMENT >
inline void set < ELEMENT, ARG_ELEMENT >::clear()
{
   erase_all();
}

template < class ELEMENT, class ARG_ELEMENT >
inline void set < ELEMENT, ARG_ELEMENT >::Empty()
{
   clear();
}

template < class ELEMENT, class ARG_ELEMENT >
set < ELEMENT, ARG_ELEMENT >::~set()
{
   erase_all();
   ASSERT(m_nCount == 0);
}

template < class ELEMENT, class ARG_ELEMENT >
typename set < ELEMENT, ARG_ELEMENT >::SET_ELEMENT_ITEM *
set < ELEMENT, ARG_ELEMENT >::new_element(ARG_ELEMENT key)
{

   //if(this->m_passocFree == nullptr)
   //{
   //   // add another block
   //   //plex * newBlock = plex::create(m_pplex, m_nBlockSize, sizeof(set::SET_ELEMENT_ITEM));
   //   //// chain them into free list
   //   //set::SET_ELEMENT_ITEM* pelement = (set::SET_ELEMENT_ITEM*) newBlock->data();
   //   //// free in reverse order to make it easier to debug
   //   //index i = m_nBlockSize - 1;
   //   //for (pelement = &pelement[i]; i >= 0; i--, pelement--)
   //   //{
   //   //   pelement->m_pnext = this->m_passocFree;
   //   //   this->m_passocFree = pelement;

   //   //}
   //   this->m_passocFree = new SET_ELEMENT_ITEM();

   //}

   //ENSURE(this->m_passocFree != nullptr);  // we must have something

   typename set < ELEMENT, ARG_ELEMENT >::SET_ELEMENT_ITEM * pelement =
      new SET_ELEMENT_ITEM(key);

   //this->m_passocFree  = this->m_passocFree->m_pnext;

   //zero_pointer(pelement);

   if (this->m_pelementHead != nullptr)
   {

      this->m_pelementHead->m_pprev = pelement;

   }

   pelement->m_pnext = this->m_pelementHead;

   this->m_pelementHead = pelement;

   this->m_pelementHead->m_pprev = nullptr;

   m_nCount++;

   ASSERT(m_nCount > 0);  // make sure we don't overflow

   return pelement;

}

template < class ELEMENT, class ARG_ELEMENT >
void set < ELEMENT, ARG_ELEMENT >::free_element(SET_ELEMENT_ITEM * pelement)
{

   SET_ELEMENT_ITEM * pnext = pelement->m_pnext;

   if (pelement->m_pnext != nullptr)
   {

      pelement->m_pnext->m_pprev = pelement->m_pprev;

   }

   if (pelement->m_pprev != nullptr)
   {

      pelement->m_pprev->m_pnext = pelement->m_pnext;

   }

   if (this->m_pelementHead == pelement)
   {

      this->m_pelementHead = pnext;

      if (this->m_pelementHead != nullptr)
      {

         this->m_pelementHead->m_pprev = nullptr;

      }

   }

   delete pelement;

   //pelement->m_pnext = this->m_passocFree;

   //this->m_passocFree = pelement;

   m_nCount--;

   ASSERT(m_nCount >= 0);  // make sure we don't underflow

   // if no more elements, cleanup completely
   if (m_nCount == 0)
      erase_all();

}

template < class ELEMENT, class ARG_ELEMENT >
typename set < ELEMENT, ARG_ELEMENT >::SET_ELEMENT_ITEM *
set < ELEMENT, ARG_ELEMENT >::get_element_at(ARG_ELEMENT key, ::u32 & nHashBucket, ::u32 & nHashValue) const
// find association (or return nullptr)
{

   nHashValue = u32_hash<ARG_ELEMENT>(key);

   nHashBucket = nHashValue % m_hashtable.GetHashTableSize();

   if (get_count() <= 0)
   {

      return nullptr;

   }

   // see if it exists
   SET_ELEMENT_ITEM * pelement;

   for (pelement = m_hashtable.m_ppassocHash[nHashBucket]; pelement != nullptr; pelement = pelement->m_pnextHash)
   {

      if (EqualElements<ARG_ELEMENT>(pelement->element(), key))
      {

         return pelement;

      }

   }

   return nullptr;

}


template < class ELEMENT, class ARG_ELEMENT >
bool set < ELEMENT, ARG_ELEMENT >::contains(ARG_ELEMENT element) const
{

   ::u32 nHashBucket, nHashValue;

   SET_ELEMENT_ITEM * pelement = get_element_at(element, nHashBucket, nHashValue);

   if (!pelement)
   {

      return false;  

   }

   return true;

}

//template < class ELEMENT, class ARG_ELEMENT >
//typename set < ELEMENT, ARG_ELEMENT >::iterator set < ELEMENT, ARG_ELEMENT >::find (ARG_ELEMENT key)
//{
//   return iterator(plookup(key), this);
//}
//
//template < class ELEMENT, class ARG_ELEMENT >
//typename set < ELEMENT, ARG_ELEMENT >::const_iterator set < ELEMENT, ARG_ELEMENT >::find (ARG_ELEMENT key) const
//{
//   return const_iterator((SET_ELEMENT_ITEM *) plookup(key), (set *) this);
//}


template < class ELEMENT, class ARG_ELEMENT >
const typename set < ELEMENT, ARG_ELEMENT >::SET_ELEMENT_ITEM * set < ELEMENT, ARG_ELEMENT >::pfind(ARG_ELEMENT key) const
{
   //ASSERT_VALID(this);

   ::u32 nHashBucket, nHashValue;
   SET_ELEMENT_ITEM * pelement = get_element_at(key, nHashBucket, nHashValue);
   return pelement;
}

template < class ELEMENT, class ARG_ELEMENT >
typename set < ELEMENT, ARG_ELEMENT >::SET_ELEMENT_ITEM * set < ELEMENT, ARG_ELEMENT >::pfind(ARG_ELEMENT key)
{
   //ASSERT_VALID(this);

   ::u32 nHashBucket, nHashValue;
   SET_ELEMENT_ITEM * pelement = get_element_at(key, nHashBucket, nHashValue);
   return pelement;
}

template < class ELEMENT, class ARG_ELEMENT >
ELEMENT * set < ELEMENT, ARG_ELEMENT >::element_at(ARG_ELEMENT key)
{
   SET_ELEMENT_ITEM * point = plookup(key);
   if (point)
      return &point->element2();
   else
      return nullptr;
}


template < class ELEMENT, class ARG_ELEMENT >
inline typename set < ELEMENT, ARG_ELEMENT >::SET_ELEMENT_ITEM * set < ELEMENT, ARG_ELEMENT >::find_element(ARG_ELEMENT key) const
{

   ASSERT_VALID(this);

   ::u32 nHashBucket, nHashValue;

   return get_element_at(key, nHashBucket, nHashValue);

}


template < class ELEMENT, class ARG_ELEMENT >
typename set < ELEMENT, ARG_ELEMENT >::SET_ELEMENT_ITEM * set < ELEMENT, ARG_ELEMENT >::get_assoc(ARG_ELEMENT key)
{

   ASSERT_VALID(this);

   ::u32 nHashBucket, nHashValue;

   SET_ELEMENT_ITEM * pelement;

   if ((pelement = get_element_at(key, nHashBucket, nHashValue)) == nullptr)
   {

      // not precise (memleak? a watch dog can restart from the last check point... continuable tasks need...) but self-healing(self-recoverable/not-fatal)...
      if (void_ptr_is_null(m_hashtable.m_ppassocHash))
         InitHashTable(m_hashtable.GetHashTableSize());

      ENSURE(m_hashtable.m_ppassocHash);

      pelement = new_element(key);

      if (m_hashtable.m_ppassocHash[nHashBucket] != nullptr)
      {
         m_hashtable.m_ppassocHash[nHashBucket]->m_ppprevHash = &pelement->m_pnextHash;
      }

      pelement->m_pnextHash = m_hashtable.m_ppassocHash[nHashBucket];

      m_hashtable.m_ppassocHash[nHashBucket] = pelement;

      pelement->m_ppprevHash = &m_hashtable.m_ppassocHash[nHashBucket];

   }

   return pelement;

}


template < class ELEMENT, class ARG_ELEMENT >
ELEMENT & set < ELEMENT, ARG_ELEMENT >::operator[](ARG_ELEMENT key)
{

   return get_assoc(key)->element2();  // return new matter

}

template < class ELEMENT, class ARG_ELEMENT >
const ELEMENT & set < ELEMENT, ARG_ELEMENT >::operator[](ARG_ELEMENT key) const
{

   return get_assoc(key)->element2();  // return new matter

}


template < class ELEMENT, class ARG_ELEMENT >
inline bool set < ELEMENT, ARG_ELEMENT >::erase(SET_ELEMENT_ITEM * pelement)
// erase - return true if erased
{

   if (pelement->m_pnextHash != nullptr)
   {

      pelement->m_pnextHash->m_ppprevHash = pelement->m_ppprevHash;

   }

   *pelement->m_ppprevHash = pelement->m_pnextHash;

   free_element(pelement);

   return true;

}


template < class ELEMENT, class ARG_ELEMENT >
inline ::count set < ELEMENT, ARG_ELEMENT >::count(const ELEMENT & key) const
{

   return this->plookup(key) != nullptr ? 1 : 0;

}

template < class ELEMENT, class ARG_ELEMENT >
bool set < ELEMENT, ARG_ELEMENT >::has(const ELEMENT & key) const
{

   return this->plookup(key) != nullptr ? 1 : 0;

}

//template < class ELEMENT, class ARG_ELEMENT >
//bool set < ELEMENT, ARG_ELEMENT >::contains(const ELEMENT & key) const
//{
//
//   return this->plookup(key) != nullptr ? 1 : 0;
//
//}


//template < class ELEMENT, class ARG_ELEMENT >
//void set < ELEMENT, ARG_ELEMENT >::erase(iterator it)
//{
//
//   erase_key(it->element1());
//
//}


template < class ELEMENT, class ARG_ELEMENT >
void set < ELEMENT, ARG_ELEMENT >::get_next(SET_ELEMENT_ITEM *& pelement,
   ELEMENT & rKey, ELEMENT & rValue) const
{

   rKey = pelement->element1();

   rValue = pelement->element2();

   pelement = pelement->m_pnext;

}


template < class ELEMENT, class ARG_ELEMENT >
inline const typename set < ELEMENT, ARG_ELEMENT >::SET_ELEMENT_ITEM *
set < ELEMENT, ARG_ELEMENT >::get_next(const SET_ELEMENT_ITEM * pelement) const
{

   return pelement->m_pnext;

}

template < class ELEMENT, class ARG_ELEMENT >
inline typename set < ELEMENT, ARG_ELEMENT >::SET_ELEMENT_ITEM *
set < ELEMENT, ARG_ELEMENT >::get_next(const SET_ELEMENT_ITEM * pelement)
{

   return pelement->m_pnext;

}

template < class ELEMENT, class ARG_ELEMENT >
ELEMENT set < ELEMENT, ARG_ELEMENT > ::
get(ARG_ELEMENT argkey, ARG_ELEMENT valueDefault)
{
   SET_ELEMENT_ITEM * pelement = plookup(argkey);
   if (pelement == nullptr)
      return valueDefault;
   else
      return pelement->element2();
}




template < class ELEMENT, class ARG_ELEMENT >
void set < ELEMENT, ARG_ELEMENT >::assert_valid() const
{

   ::matter::assert_valid();

   ASSERT(GetHashTableSize() > 0);

   ASSERT(m_nCount == 0 || m_hashtable.m_ppassocHash != nullptr);
   // non-empty set should have hash table

}



template < class ELEMENT, class ARG_ELEMENT >
void set < ELEMENT, ARG_ELEMENT >::dump(dump_context & dumpcontext) const
{
   
   //::object::dump_context(dumpcontext);

}



template <class ELEMENT, class ARG_ELEMENT >
void set < ELEMENT, ARG_ELEMENT >::InitHashTable(
   ::u32 nHashSize, bool bAllocNow)
{

   ASSERT_VALID(this);
   ASSERT(m_nCount == 0);
   ASSERT(nHashSize > 0);

   m_hashtable.InitHashTable(nHashSize, bAllocNow);

}

//#define ptrptr(T1, T2) set < T1 *, T1 *, T2 *, T2 * >



//template < class ELEMENT, class ARG_ELEMENT >
//stream & operator << (stream & s, set < ELEMENT, ARG_ELEMENT > & a)
//{
//
//   s.stream_set(a);
//
//   return s;
//
//}


//template < class ELEMENT, class ARG_ELEMENT >
//stream & operator >> (stream & s,set < ELEMENT, ARG_ELEMENT > & a)
//{
//
//   s.stream_set(a);
//
//   return s;
//
//}


template < class ELEMENT >
using isoset = set < ELEMENT, ELEMENT >;

using dword_set = isoset < ::u32 >;

using double_set = set < double >;

using uptr_set = set < uptr >;

using iptr_set = set < iptr >;

using string_set = set < string >;

using index_set = set < index >;






