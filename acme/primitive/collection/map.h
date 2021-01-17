#pragma once


#define new ACME_NEW


template < typename PAIR, const int DEFAULT_HASH_TABLE_SIZE = 17 >
class map_dynamic_hash_table
{
public:

   typedef map_association < PAIR >  assoc;

   assoc *           m_assocHashDefault[DEFAULT_HASH_TABLE_SIZE];
   assoc **          m_ppassocHash;
   ::u32              m_nHashTableSize;

   map_dynamic_hash_table()
   {

      m_ppassocHash = nullptr;

      m_nHashTableSize = DEFAULT_HASH_TABLE_SIZE;

   }


   ::u32 GetHashTableSize() const
   {

      return m_nHashTableSize;

   }


   void InitHashTable(::u32 nHashSize, bool bAllocNow = TRUE)
   {

      if(m_ppassocHash != nullptr && m_ppassocHash != m_assocHashDefault && m_nHashTableSize > DEFAULT_HASH_TABLE_SIZE)
      {

         delete[] m_ppassocHash;

      }

      m_ppassocHash = nullptr;

      if(bAllocNow)
      {

         if (nHashSize <= DEFAULT_HASH_TABLE_SIZE)
         {

            m_ppassocHash = m_assocHashDefault;

         }
         else
         {

            m_ppassocHash = new assoc *[nHashSize];

            ENSURE(m_ppassocHash != nullptr);

         }

         ::zero(m_ppassocHash, sizeof(assoc*) * nHashSize);

      }

      m_nHashTableSize = nHashSize;

   }

   void remove_all()
   {

      if(m_ppassocHash != nullptr && m_ppassocHash != m_assocHashDefault && m_nHashTableSize > DEFAULT_HASH_TABLE_SIZE)
      {

         delete[] m_ppassocHash;

      }

      m_ppassocHash = nullptr;

   }


};


template < int m_nHashTableSize, typename PAIR >
class map_fixed_hash_table
{
public:


   typedef map_association < PAIR > assoc;


   assoc *           m_ppassocHash[m_nHashTableSize];

   map_fixed_hash_table()
   {
      zero(m_ppassocHash,sizeof(m_ppassocHash));
   }


   ::u32 GetHashTableSize() const
   {
      return m_nHashTableSize;
   }
   void InitHashTable(::u32 hashSize,bool bAllocNow = TRUE) {  }

   void remove_all()
   {
      zero(m_ppassocHash,sizeof(m_ppassocHash));
   }

};


template < typename ARGUMENT >
class argument_of
{
public:

   using type = typename smaller_type < ARGUMENT, const ARGUMENT & >::type;

};


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
class map :
   public ::matter
{
public:


   typedef map_dynamic_hash_table < PAIR >         HASH_TABLE;
   typedef KEY                                     BASE_KEY;
   typedef ARG_KEY                                 BASE_ARG_KEY;
   typedef VALUE                                   BASE_VALUE;
   typedef ARG_VALUE                               BASE_ARG_VALUE;


   typedef ::map_association < PAIR >              assoc;
   typedef typename assoc::pair                    pair;


   __declare_iterator_struct_ok(map, assoc *, m_passoc, ::is_set(this->m_passoc));


   template < typename ITERATOR > struct make_iterator : ITERATOR
   {

      using CONTAINER = typename ITERATOR::CONTAINER;

      using ITERATOR::ITERATOR;

      make_iterator()
      {
         this->m_passoc = (assoc*)nullptr;
         this->m_pcontainer = (CONTAINER*)nullptr;
         this->m_passocBeg = (assoc*)nullptr;
         this->m_passocEnd = (assoc*) nullptr;
      }

      make_iterator(const assoc * passoc, const CONTAINER * pmap = nullptr)
      {
         this->m_passoc = (assoc *) passoc;
         this->m_pcontainer = (CONTAINER *) pmap;
         this->m_passocBeg = (assoc *) passoc;
         this->m_passocEnd = (assoc *) nullptr;
      }


      make_iterator(const make_iterator & iterator)
      {
         this->m_passoc = iterator.m_passoc;
         this->m_pcontainer = iterator.m_pcontainer;
         this->m_passocBeg = (assoc *) iterator.m_passocBeg;
         this->m_passocEnd = (assoc *) iterator.m_passocEnd;
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

         this->m_passoc = this->m_passoc->m_pnext;

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

         make_iterator iterator = this->m_passoc;

         this->m_passoc = this->m_passoc->m_pnext;

         return iterator;

      }


      bool operator == (const make_iterator & it) const
      {

         if (this == &it)
         {

            return true;

         }

         if (this->m_passoc == nullptr && it.m_passoc == nullptr && it.m_pcontainer == nullptr)
         {

            return true;

         }

         if (this->m_pcontainer != it.m_pcontainer)
         {

            return false;

         }

         return this->m_passoc == it.m_passoc;

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

            this->m_passoc = it.m_passoc;

         }

         return *this;

      }

   };


   __declare_iterator(dereferenced_value_iterator, this->m_passoc->element2());
   __declare_iterator(value_iterator, &this->m_passoc->element2());
   __declare_iterator(key_iterator, &this->m_passoc->element1());
   __declare_iterator(iterator, this->m_passoc);


   using deferenced_iterator = dereferenced_value_iterator;


   HASH_TABLE           m_hashtable;
   ::count              m_nCount;
   assoc *              m_passocHead;


   map();
   map(assoc pairs[], i32 iCount);
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
   const assoc * plookup(ARG_KEY key) const;
   assoc * plookup(ARG_KEY key);

   
   VALUE * pget(ARG_KEY key);


   template < typename TKEY >
   auto pop(const TKEY & key)
   {

      auto value = operator[](key);

      remove_key(key);

      return value;

   }

   //Operations
   //lookup and add if not there
   VALUE & operator[](ARG_KEY key);
   const VALUE & operator[](ARG_KEY key) const;

   assoc * get_assoc(ARG_KEY key);
   assoc * get_assoc(ARG_KEY key) const
   {
      return ((map *) this)->get_assoc(key);
   }
   assoc * find_assoc(ARG_KEY key) const;

   //add a new (key, value) assoc
   assoc * set_at(ARG_KEY key, ARG_VALUE newValue);

   bool remove_item(assoc * passoc);

   //removing existing (key, ?) assoc
   inline bool remove_key(ARG_KEY key) { auto pitem = find_item(key);  return ::is_set(pitem) ? remove_item(pitem) : false; }

   template < typename ITERATOR >
   inline ITERATOR erase(ITERATOR it) { return ::papaya::iterator::erase(*this, it); }

   template < typename ITERATOR >
   inline void erase(const ITERATOR & begin, const ITERATOR & last) { ::erase(*this, begin, last); }

   void remove_all();
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

   const assoc * get_start() const;
   assoc * get_start();

   void get_next(assoc * & rNextPosition, KEY& rKey, VALUE& rValue) const;

   const assoc * get_next(const assoc *passocRet) const;
   assoc * get_next(const assoc *passocRet);

   //advanced features for derived classes
   ::u32 GetHashTableSize() const
   {
      return m_hashtable.GetHashTableSize();
   }
   void InitHashTable(::u32 hashSize,bool bAllocNow = TRUE);


   VALUE get(ARG_KEY argkey, ARG_VALUE valueDefault);


   assoc * next(assoc * & passoc)
   {
      if(passoc == nullptr)
      {
         passoc = get_start();
      }
      else
      {
         passoc = get_next(passoc);
      }
      return passoc;
   }

   const assoc * next(const assoc * & passoc) const
   {
      if(passoc == nullptr)
      {
         passoc = get_start();
      }
      else
      {
         passoc = get_next(passoc);
      }
      return passoc;
   }


   void set(map & map)
   {
      assoc * passoc = nullptr;
      while(map.next(passoc) != nullptr)
      {
         set_at(passoc->element1(), passoc->element2());
      }
   }

   inline assoc * find_item(ARG_KEY key) const { return find_assoc(key); }

   inline iterator find(ARG_KEY key) { return { find_item(key), this }; }
   const_iterator find (ARG_KEY key) const { return { find_item(key), this }; }


   assoc * new_assoc(ARG_KEY key);
   void free_assoc(assoc * passoc);
   assoc * get_assoc_at(ARG_KEY, ::u32&, ::u32&) const;


   virtual void assert_valid() const override;
   virtual void dump(dump_context & dumpcontext) const override;



   template < class ARRAY >
   bool remove_key_array(ARRAY a)
   {

      bool bRemoved = false;

      for(index i = 0; i < a.get_count(); i++)
      {

         bRemoved |= remove_key(a[i]);

      }

      return bRemoved;

   }

   template < class ARRAY >
   ::count remove_assoc_array(ARRAY a)
   {

      ::count countRemoved = 0;

      for(index i = 0; i < a.get_count(); i++)
      {

         if(remove_assoc(a[i]))
         {

            countRemoved++;

         }

      }

      return countRemoved;

   }

   virtual void on_after_read() {}

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
      return elements().element_at(iIndex);
   }

   template < typename PRED >
   typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::assoc * pred_find(PRED pred)
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
   __pointer(TYPE) get_typed_ptr(index i = 0)
   {

      __pointer(TYPE) p;

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
   return m_nCount;
}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline ::count map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::get_size() const
{
   return m_nCount;
}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline ::count map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::count() const
{
   return m_nCount;
}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline ::count map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::size() const
{
   return m_nCount;
}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
map< KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR > & map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::operator = (const map & m)
{
   if(this != &m)
   {

      remove_all();

      for(auto & assoc : m)
      {

         set_at(assoc.element1(),assoc.element2());

      }

   }
   return *this;
}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline bool map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::is_empty() const
{
   return m_nCount == 0;
}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline bool map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::empty() const
{
   return m_nCount == 0;
}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::assoc * map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::set_at(ARG_KEY key,ARG_VALUE newValue)
{

   assoc * passoc = get_assoc(key);

   passoc->element2() = newValue;

   return passoc;

}


//template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
//inline typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::assoc * map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::get_start() const
//{
//   return (m_nCount == 0) ? nullptr : BEFORE_START_POSITION;
//}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
const typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::assoc* map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::get_start() const
{

   return this->m_passocHead;

}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::assoc* map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::get_start()
{

   return this->m_passocHead;

}

//template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
//inline ::u32 map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::GetHashTableSize() const
//{
//
//   return m_nHashTableSize;
//
//}

/////////////////////////////////////////////////////////////////////////////
// map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR > out-of-line functions
template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::construct()
{

   //m_ppassocHash     = nullptr;
   //m_nHashTableSize  = 17;  // default size
   m_nCount          = 0;
//   this->m_passocFree      = nullptr;
//   m_pplex           = nullptr;
   // m_nBlockSize      = nBlockSize;
   this->m_passocHead      = nullptr;
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

   for(auto & pair_item : list)
   {

      set_at(pair_item.m_element1, pair_item.m_element2);

   }

}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::map(assoc pairs[], i32 iCount)
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
void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::remove_all()
{

   ASSERT_VALID(this);

   if(this->m_passocHead != nullptr)
   {
      // destroy elements (values and keys)

      assoc * passoc;

      assoc * passocNext = nullptr;

      for (passoc = this->m_passocHead; passoc != nullptr; passoc = passocNext)
      {

         passocNext = passoc->m_pnext;

         delete passoc;

      }

   }

   m_hashtable.remove_all();

   m_nCount = 0;
   //this->m_passocFree = nullptr;

   //if(m_pplex != nullptr)
   //{

   //   m_pplex->FreeDataChain();
   //   m_pplex = nullptr;

   //}

   this->m_passocHead = nullptr;

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::clear()
{
   remove_all();
}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::Empty()
{
   clear();
}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::~map()
{
   remove_all();
   ASSERT(m_nCount == 0);
}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::assoc *
map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::new_assoc(ARG_KEY key)
{

   //if(this->m_passocFree == nullptr)
   //{
   //   // add another block
   //   //plex * newBlock = plex::create(m_pplex, m_nBlockSize, sizeof(map::assoc));
   //   //// chain them into free list
   //   //map::assoc* passoc = (map::assoc*) newBlock->data();
   //   //// free in reverse order to make it easier to debug
   //   //index i = m_nBlockSize - 1;
   //   //for (passoc = &passoc[i]; i >= 0; i--, passoc--)
   //   //{
   //   //   passoc->m_pnext = this->m_passocFree;
   //   //   this->m_passocFree = passoc;

   //   //}
   //   this->m_passocFree = new assoc();

   //}

   //ENSURE(this->m_passocFree != nullptr);  // we must have something

   typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::assoc * passoc =
   new assoc(key);

   //this->m_passocFree  = this->m_passocFree->m_pnext;

   //zero_pointer(passoc);

   if(this->m_passocHead != nullptr)
   {

      this->m_passocHead->m_pprev   = passoc;

   }

   passoc->m_pnext            = this->m_passocHead;

   this->m_passocHead               = passoc;

   this->m_passocHead->m_pprev      = nullptr;

   m_nCount++;

   ASSERT(m_nCount > 0);  // make sure we don't overflow

   return passoc;

}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::free_assoc(assoc * passoc)
{

   assoc * pnext = passoc->m_pnext;

   if(passoc->m_pnext != nullptr)
   {

      passoc->m_pnext->m_pprev = passoc->m_pprev;

   }

   if(passoc->m_pprev != nullptr)
   {

      passoc->m_pprev->m_pnext = passoc->m_pnext;

   }

   if(this->m_passocHead == passoc)
   {

      this->m_passocHead = pnext;

      if(this->m_passocHead != nullptr)
      {

         this->m_passocHead->m_pprev = nullptr;

      }

   }

   delete passoc;

   //passoc->m_pnext = this->m_passocFree;

   //this->m_passocFree = passoc;

   m_nCount--;

   ASSERT(m_nCount >= 0);  // make sure we don't underflow

   // if no more elements, cleanup completely
   if (m_nCount == 0)
      remove_all();

}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::assoc *
map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::get_assoc_at(ARG_KEY key, ::u32& nHashBucket, ::u32& nHashValue) const
// find association (or return nullptr)
{

   nHashValue = u32_hash<ARG_KEY>(key);

   nHashBucket = nHashValue % m_hashtable.GetHashTableSize();

   if(get_count() <= 0)
      return nullptr;

   // see if it exists
   assoc * passoc;

   for(passoc = m_hashtable.m_ppassocHash[nHashBucket]; passoc != nullptr; passoc = passoc->m_pnextHash)
   {

      if(EqualElements<ARG_KEY>(passoc->element1(), key))
         return passoc;

   }

   return nullptr;

}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
bool map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::lookup(ARG_KEY key, VALUE& rValue) const
{
   //ASSERT_VALID(this);

   ::u32 nHashBucket, nHashValue;

   assoc* passoc = get_assoc_at(key, nHashBucket, nHashValue);

   if (passoc == nullptr)
      return FALSE;  // not in map

   rValue = passoc->element2();

   return TRUE;

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
//   return const_iterator((assoc *) plookup(key), (map *) this);
//}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
const typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::assoc* map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::plookup(ARG_KEY key) const
{
   //ASSERT_VALID(this);

   ::u32 nHashBucket, nHashValue;
   assoc* passoc = get_assoc_at(key, nHashBucket, nHashValue);
   return passoc;
}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::assoc* map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::plookup(ARG_KEY key)
{
   //ASSERT_VALID(this);

   ::u32 nHashBucket, nHashValue;
   assoc* passoc = get_assoc_at(key, nHashBucket, nHashValue);
   return passoc;
}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
VALUE * map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::pget(ARG_KEY key)
{
   assoc * point = plookup(key);
   if(point)
      return &point->element2();
   else
      return nullptr;
}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::assoc * map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::find_assoc(ARG_KEY key) const
{

   ASSERT_VALID(this);

   ::u32 nHashBucket, nHashValue;

   return get_assoc_at(key, nHashBucket, nHashValue);

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::assoc * map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::get_assoc(ARG_KEY key)
{

   ASSERT_VALID(this);

   ::u32 nHashBucket,nHashValue;

   assoc * passoc;

   if((passoc = get_assoc_at(key,nHashBucket,nHashValue)) == nullptr)
   {

      // not precise (memleak? a watch dog can restart from the last check point... continuable tasks need...) but self-healing(self-recoverable/not-fatal)...
      if(void_ptr_is_null(m_hashtable.m_ppassocHash))
         InitHashTable(m_hashtable.GetHashTableSize());

      ENSURE(m_hashtable.m_ppassocHash);

      passoc = new_assoc(key);

      if(m_hashtable.m_ppassocHash[nHashBucket] != nullptr)
      {
         m_hashtable.m_ppassocHash[nHashBucket]->m_ppprevHash = &passoc->m_pnextHash;
      }

      passoc->m_pnextHash        = m_hashtable.m_ppassocHash[nHashBucket];

      m_hashtable.m_ppassocHash[nHashBucket] = passoc;

      passoc->m_ppprevHash       = &m_hashtable.m_ppassocHash[nHashBucket];

   }

   return passoc;

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
VALUE& map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::operator[](ARG_KEY key)
{

   return get_assoc(key)->element2();  // return new matter

}

template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
const VALUE & map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::operator[](ARG_KEY key) const
{

   return get_assoc(key)->element2();  // return new matter

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline bool map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::remove_item(assoc * passoc)
// erase - return TRUE if removed
{

   if(passoc->m_pnextHash != nullptr)
   {

      passoc->m_pnextHash->m_ppprevHash = passoc->m_ppprevHash;

   }

   *passoc->m_ppprevHash = passoc->m_pnextHash;

   free_assoc(passoc);

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
void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::get_next(assoc * & passoc,
      KEY& rKey, VALUE& rValue) const
{

   rKey = passoc->element1();

   rValue = passoc->element2();

   passoc = passoc->m_pnext;

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline const typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::assoc*
map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::get_next(const assoc * passoc) const
{

   return passoc->m_pnext;

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
inline typename map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::assoc*
map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::get_next(const assoc * passoc)
{

   return passoc->m_pnext;

}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
VALUE map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR > ::
get(ARG_KEY argkey, ARG_VALUE valueDefault)
{
   assoc * passoc = plookup(argkey);
   if(passoc == nullptr)
      return valueDefault;
   else
      return passoc->element2();
}


template < typename KEY, typename VALUE, typename ARG_KEY, typename ARG_VALUE, typename PAIR >
void map < KEY, VALUE, ARG_KEY, ARG_VALUE, PAIR >::assert_valid() const
{

   ::matter::assert_valid();

   ASSERT(GetHashTableSize() > 0);

   ASSERT(m_nCount == 0 || m_hashtable.m_ppassocHash != nullptr);
   // non-empty map should have hash table

}


#define ptrptr(T1, T2) map < T1 *, T1 *, T2 *, T2 * >


template < class VALUE, typename ARG_VALUE = typename argument_of < VALUE >::type >
using colorrefmap = map < color32_t, VALUE, typename argument_of < color32_t >::type, ARG_VALUE >;


template < class VALUE, typename ARG_VALUE = typename argument_of < VALUE >::type >
using double_map = map < double, VALUE, typename argument_of < double >::type, ARG_VALUE >;

using double_to_double = double_map < double >;

template < class VALUE, typename ARG_VALUE = typename argument_of < VALUE >::type >
using dword_map = map < ::u32, VALUE, typename argument_of < uptr >::type, ARG_VALUE >;

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
   KEY & key() { return xkey; } \
   VALUE & value() { return xvalue; } \
   const KEY & key() const { return xkey; } \
   const VALUE & value() const { return xvalue; } \
}


#ifdef CPP17
#define __declare_pair_tuple_size(pair) \
template<> ALIENATED_ANDROID_ANARCHY ::std::tuple_size< pair > : ::std::integral_constant<size_t, 2> {} }
#endif


#define __declare_key_value_map(xmaptype, xkeyvaluetype, xkeytype, xkey, xvaluetype, xvalue) \
__declare_key_value(xkeyvaluetype, xkeytype, xkey, xvaluetype, xvalue); \
using xmaptype = pair_map < xkeyvaluetype >


#ifdef CPP17
#define __declare_map_key_value(xmaptype, xkeyvaluetype, xkeytype, xkey, xvaluetype, xvalue) \
__declare_key_value_map(xkeyvaluetype, xkeytype, xkey, xvaluetype, xvalue); \
__declare_pair_tuple_size(xmaptype)
#else

#define __declare_map_key_value(xmaptype, xkeyvaluetype, xkeytype, xkey, xvaluetype, xvalue) \
__declare_key_value_map(xkeyvaluetype, xkeytype, xkey, xvaluetype, xvalue);

#endif


using int_ptr_to_string = map < iptr, iptr, string, const string & >;

using int_ptr_to_int_ptr_to_string = map < iptr, iptr, int_ptr_to_string, const int_ptr_to_string & >;

using index_string = map < index, string >;

using index_to_index_to_string = map < index, index_string >;



