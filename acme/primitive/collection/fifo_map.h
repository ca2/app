#pragma once


//template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, typename PAIR = ::pair < KEY, VALUE > >
//class stable_map :
//   virtual public ::array < PAIR >
//{
//public:
//
//};
//

//
//template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE = ::comparison::binary < KEY > >
//class fifo_map :
//   virtual public ::matter
//{
//public:
//
//
//   typedef KEY                         AXIS_KEY;
//   typedef ARG_KEY                     AXIS_ARG_KEY;
//   typedef VALUE                       AXIS_VALUE;
//   typedef ARG_VALUE                   AXIS_ARG_VALUE;
//   typedef COMPARE                     AXIS_COMPARE;
//
//
//   typedef ::pair < KEY, VALUE >       pair;
//
//
//   class iterator
//   {
//   public:
//
//
//      index          m_i;
//      fifo_map *     m_pmap;
//
//
//      iterator()
//      {
//         m_i      = 0;
//         m_pmap   = nullptr;
//      }
//
//      iterator(const iterator & iterator)
//      {
//         m_i      = iterator.m_i;
//         m_pmap   = iterator.m_pmap;
//      }
//
//      iterator(index i, fifo_map * pmap)
//      {
//         if(i < 0)
//            m_i = 0;
//         else if(i >= pmap->m_ptra.get_size())
//            m_i = 0;
//         else
//            m_i = i + 1;
//         m_pmap   = pmap;
//      }
//
//      pair * operator -> ()
//      {
//         return m_pmap->m_ptra[m_i - 1];
//      }
//
//      const pair * operator -> () const
//      {
//         return m_pmap->m_ptra[m_i - 1];
//      }
//
//
//      iterator & operator ++ ()
//      {
//         if(m_i != 0 && m_pmap != nullptr)
//         {
//            m_i++;
//            if(m_i > m_pmap->m_ptra.get_size())
//            {
//               m_i = 0;
//            }
//         }
//         return *this;
//      }
//
//      iterator operator ++ (i32)
//      {
//         if(m_i != 0 && m_pmap != nullptr)
//         {
//            m_i++;
//            if(m_i > m_pmap->m_ptra.get_size())
//            {
//               m_i = 0;
//            }
//         }
//         return *this;
//      }
//
//      bool operator == (const iterator & it) const
//      {
//
//         if(this == &it)
//            return true;
//
//         if(m_i == 0 && it.m_i == 0)
//            return true;
//
//         return m_pmap == it.m_pmap && m_i == it.m_i;
//
//      }
//
//      bool operator != (const iterator & it) const
//      {
//
//         return !operator == (it);
//
//      }
//
//      iterator & operator = (const iterator & it)
//      {
//
//         if(this != &it)
//         {
//
//            m_pmap         = it.m_pmap;
//
//            m_i            = it.m_i;
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
//   address_array < pair * >   m_ptra;
//
//
//   fifo_map(::count nBlockSize = 10);
//   fifo_map(pair pairs[], i32 iCount, ::count nBlockSize = 10);
//   virtual ~fifo_map();
//
//
//   void construct(::count nBlockSize = 10);
//
//
//   virtual void assert_valid() const override;
//   virtual void dump(dump_context & dumpcontext) const override;
//
//
//
//
//   iterator begin()
//   {
//      return iterator(0, this);
//   }
//
//
//   iterator end()
//   {
//      return iterator(-1, this);
//   }
//
//   ::count get_count() const;
//   ::count get_size() const;
//   ::count size() const;
//   ::count count() const;
//   bool is_empty() const;
//
//   // lookup
//   bool lookup(ARG_KEY key, VALUE& rValue) const;
//   const pair *plookup(ARG_KEY key) const;
//   pair *plookup(ARG_KEY key);
//
//
//   VALUE * pget(ARG_KEY key);
//
//   // Operations
//   // lookup and add if not there
//   VALUE & operator[](ARG_KEY key);
//
//   // add a new (key, value) pair
//   void set_at(ARG_KEY key, ARG_VALUE newValue);
//
//   // removing existing (key, ?) pair
//   bool remove_key(ARG_KEY key);
//   void erase(iterator it);
//   ::count erase(const KEY & key);
//   void erase ( iterator first, iterator last );
//   void remove_all();
//   void clear();
//
//
//   ::count count(const KEY & t) const;
//   bool has(const KEY & t) const;
//   bool contains(const KEY & t) const;
//
//   // iterating all (key, value) pairs
//   const pair * get_start() const;
//   pair * get_start();
//
//   void get_next(pair * & rNextPosition, KEY& rKey, VALUE& rValue) const;
//
//   const pair * get_next(const pair *ppairRet) const;
//   pair * get_next(const pair *ppairRet);
//
//   VALUE get(ARG_KEY argkey, ARG_VALUE valueDefault);
//
//   pair * next(pair * & ppair)
//   {
//      if(ppair == nullptr)
//      {
//         ppair = get_start();
//      }
//      else
//      {
//         ppair = get_next(ppair);
//      }
//      return ppair;
//   }
//
//   const pair * next(const pair * & ppair) const
//   {
//      if(ppair == nullptr)
//      {
//         ppair = get_start();
//      }
//      else
//      {
//         ppair = get_next(ppair);
//      }
//      return ppair;
//   }
//
//
//   void set(fifo_map & fifo_map)
//   {
//      pair * ppair = nullptr;
//      while(fifo_map.next(ppair) != nullptr)
//      {
//         set_at(ppair->element1(), ppair->element2());
//      }
//   }
//
//
//   index    find_pair(pair * ppair) const;
//   bool     find_key(ARG_KEY key, index & i) const;
//
//   index    add_key(ARG_KEY key);
//   index    add_pair(ARG_KEY key, ARG_VALUE value);
//
//   // sort by key
//   void sort(bool bAsc = true);
//
//};
//
///////////////////////////////////////////////////////////////////////////////
//// fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE > inline functions
//
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//inline ::count fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::get_count() const
//{ return m_ptra.get_count(); }
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//inline ::count fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::get_size() const
//{ return m_ptra.get_count(); }
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//inline ::count fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::count() const
//{ return m_ptra.get_count(); }
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//inline ::count fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::size() const
//{ return m_ptra.get_count(); }
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//inline bool fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::is_empty() const
//{ return m_ptra.get_count() == 0; }
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//inline void fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::set_at(ARG_KEY key, ARG_VALUE newValue)
//{  add_pair(key, newValue); }
//
////template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
////inline typename fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::pair *  fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::get_start() const
////{ return (m_ptra.get_count() == 0) ? nullptr : BEFORE_START_POSITION; }
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//const typename fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::pair* fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::get_start() const
//{
//
//   ASSERT_VALID(this);
//
//   if(m_ptra.get_count() <= 0)
//      return nullptr;
//
//   return m_ptra[0];
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//typename fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::pair* fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::get_start()
//{
//
//   if(m_ptra.get_count() <= 0)
//      return nullptr;
//
//   return m_ptra[0];
//
//}
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//void fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::construct(::count nBlockSize)
//{
//
//   UNREFERENCED_PARAMETER(nBlockSize);
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::fifo_map(::count nBlockSize)
//{
//
//   construct(nBlockSize);
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::fifo_map(pair pairs[], i32 iCount, ::count nBlockSize)
//{
//
//   construct(nBlockSize);
//
//   for(i32 i = 0; i < iCount; i++)
//   {
//
//      set_at(pairs[i].element1(), pairs[i].element2());
//
//   }
//
//}
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//void fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::remove_all()
//{
//
//   ASSERT_VALID(this);
//
//   for(index i = 0; i < m_ptra.get_count(); i++)
//   {
//
//      delete m_ptra[i];
//
//   }
//
//   m_ptra.remove_all();
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//inline void fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::clear()
//{
//
//   remove_all();
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::~fifo_map()
//{
//
//   remove_all();
//
//}
//
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//bool fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::lookup(ARG_KEY key, VALUE& rValue) const
//{
//
//   pair * ppair = plookup(key);
//
//   if (ppair == nullptr)
//      return false;
//
//   rValue = ppair->element2();
//
//   return TRUE;
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//const typename fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::pair* fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::plookup(ARG_KEY key) const
//{
//
//   index i;
//
//   if(!find_key(key, i))
//      return nullptr;
//
//   return m_ptra[i];
//
//}
//
//
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//typename fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::pair* fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::plookup(ARG_KEY key)
//{
//
//   index i;
//
//   if(!find_key(key, i))
//      return nullptr;
//
//   return m_ptra[i];
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//VALUE * fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::pget(ARG_KEY key)
//{
//
//   pair * point = plookup(key);
//
//   if(point)
//      return &point->element2();
//   else
//      return nullptr;
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//VALUE& fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::operator[](ARG_KEY key)
//{
//
//   ASSERT_VALID(this);
//
//   pair * ppair = plookup(key);
//
//   if(ppair == nullptr)
//   {
//
//      add_key(key);
//
//      ppair = plookup(key);
//
//      ASSERT(ppair != nullptr);
//
//   }
//
//   return ppair->element2();  // return new matter
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//bool fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::remove_key(ARG_KEY key)
//// remove key - return TRUE if removed
//{
//
//   ASSERT_VALID(this);
//
//   index i;
//
//   if(!find_key(key, i))
//      return false;  // nothing in the table
//
//   delete m_ptra[i];
//
//   m_ptra.remove_at(i);
//
//   return true;
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//::index fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::find_pair(pair * ppair) const
//{
//
//   if(ppair == nullptr)
//      return m_ptra.get_size();
//
//   if(ppair == (pair *) (uptr) -1)
//      return 0;
//
//   return m_ptra.find_first(ppair);
//
//
//}
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//bool fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::find_key(ARG_KEY key, index & i) const
//{
//
//   for(i = 0; i < m_ptra.get_size(); i++)
//   {
//
//      if(m_ptra[i]->element1() == key)
//         return true;
//
//   }
//
//   return false;
//
//}
//
//
//// sort by key
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//void fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::sort(bool bAsc)
//{
//
//   if(bAsc)
//   {
//
//      for(index i = 0; i < m_ptra.get_size(); i++)
//      {
//
//         for(index j = i + 1; j < m_ptra.get_size(); j++)
//         {
//
//            if(m_ptra[i]->element1() > m_ptra[j]->element1())
//            {
//
//               pair * ppair = m_ptra[i];
//               m_ptra[i] = m_ptra[j];
//               m_ptra[j] = ppair;
//
//            }
//
//         }
//
//
//      }
//   }
//   else
//   {
//
//      for(index i = 0; i < m_ptra.get_size(); i++)
//      {
//
//         for(index j = i + 1; j < m_ptra.get_size(); j++)
//         {
//
//            if(m_ptra[i]->element1() < m_ptra[j]->element1())
//            {
//
//               pair * ppair = m_ptra[i];
//               m_ptra[i] = m_ptra[j];
//               m_ptra[j] = ppair;
//
//            }
//
//         }
//
//      }
//
//   }
//
//}
//
//
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//::count fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::erase(const KEY & key)
//{
//
//   return remove_key(key) ? 1 : 0;
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//void fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::erase(iterator it)
//{
//
//   remove_key(it->element1());
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//::count fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::count(const KEY & key) const
//{
//
//   return this->plookup(key) != nullptr ? 1 : 0;
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//bool fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::has(const KEY & key) const
//{
//
//   return this->plookup(key) != nullptr;
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//bool fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::contains(const KEY & key) const
//{
//
//   return this->plookup(key) != nullptr;
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//void fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::erase(iterator first, iterator last)
//{
//
//   if(first.m_pmap != this || last.m_pmap != this)
//      return;
//
//   index iFirst;
//
//   if(first.m_ppair == (pair *) (uptr) (-1))
//      iFirst = 0;
//   else
//      iFirst = m_ptra.find(first.m_ppair);
//
//   if(iFirst < 0)
//      return;
//
//   if(last.m_ppair == nullptr)
//      iFirst = 0;
//   else
//      iFirst = m_ptra.find(first.m_ppair);
//
//   if(iFirst < 0)
//      return;
//
//
//
//}
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//void fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::get_next(pair * & rNextPosition, KEY& rKey, VALUE& rValue) const
//{
//
//   ASSERT_VALID(this);
//
//   ENSURE(m_ptra.get_count() > 0);  // never call on is_empty fifo_map
//
//   index iRet = (index) rNextPosition;
//
//   if (iRet == (index) BEFORE_START_POSITION)
//   {
//      iRet = 1;
//   }
//
//   // find next pairiation
//   index iNext = iRet + 1;
//   if(iNext > m_ptra.get_count())
//   {
//
//   }
//
//   rNextPosition  = (POSITION) iNext;
//
//   // fill in return data
//   rKey           = m_ptra[iRet - 1]->element1();
//   rValue         = m_ptra[iRet - 1]->element2();
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//const typename fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::pair*
//fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::get_next(const pair * pPairRet) const
//{
//
//   ASSERT_VALID(this);
//
//   ENSURE(m_ptra.get_count() > 0);  // never call on is_empty fifo_map
//
//   index iRet = (index) find_pair(const_cast < pair * > (pPairRet));
//
//   // find next pairiation
//   iRet++;
//
//   if(iRet >= m_ptra.get_count())
//   {
//
//      return nullptr;
//
//   }
//
//   return m_ptra[iRet];
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//typename fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::pair*
//fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::get_next(const pair* pPairRet)
//{
//
//   ASSERT_VALID(this);
//
//   ENSURE(m_ptra.get_count() > 0);  // never call on is_empty fifo_map
//
//   index iRet = (index) find_pair(const_cast < pair * > (pPairRet));
//
//   // find next pairiation
//   iRet++;
//
//   if(iRet >= m_ptra.get_count())
//   {
//
//      return nullptr;
//
//   }
//
//   return m_ptra[iRet];
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//VALUE fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE > ::
//get(ARG_KEY argkey, ARG_VALUE valueDefault)
//{
//   pair * ppair = plookup(argkey);
//   if(ppair == nullptr)
//      return valueDefault;
//   else
//      return ppair->element2();
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//void fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::dump(dump_context & dumpcontext) const
//{
//   matter::dump(dumpcontext);
//
//   dumpcontext << "with " << m_ptra.get_count() << " elements";
//   if (dumpcontext.GetDepth() > 0)
//   {
//      // Dump in format "[key] -> value"
//
//      const pair * ppair = get_start();
//      while (ppair != nullptr)
//      {
//         ppair = get_next(ppair);
//         dumpcontext << "\n\t[";
//         dump_elements<KEY>(dumpcontext, &ppair->element1(), 1);
//         dumpcontext << "] = ";
//         dump_elements<VALUE>(dumpcontext, &ppair->element2(), 1);
//      }
//   }
//
//   dumpcontext << "\n";
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
//void fifo_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::assert_valid() const
//{
//
//   matter::assert_valid();
//
//}
//
//
//template < class type_map >
//class fifo_attrib_map :
//   virtual public type_map
//{
//public:
//
//
//   fifo_attrib_map(iptr nBlockSize = 10);
//   fifo_attrib_map(const fifo_attrib_map & fifo_map);
//
//   fifo_attrib_map & operator = (const fifo_attrib_map & fifo_map);
//
//   bool operator == (const fifo_attrib_map & fifo_map) const;
//
//
//};
//
//
//template < class type_map >
//fifo_attrib_map < type_map >::fifo_attrib_map(iptr nBlockSize) :
//   type_map(nBlockSize)
//{
//}
//
//template < class type_map >
//fifo_attrib_map < type_map >::fifo_attrib_map(const fifo_attrib_map & attribmap)
//{
//   operator = (attribmap);
//}
//
//
//template < class type_map >
//bool fifo_attrib_map < type_map >::operator == (const fifo_attrib_map & attribmap) const
//{
//
//   if(this == &attribmap)
//      return true;
//
//   if(this->m_ptra.get_size() != attribmap.get_size())
//      return false;
//
//   for(index i = 0; i < attribmap.m_ptra.get_count(); i++)
//   {
//
//      if(attribmap.m_ptra[i]->element1()       != this->m_ptra[i]->element1()
//            || attribmap.m_ptra[i]->element2()     != this->m_ptra[i]->element2())
//      {
//
//         return false;
//
//      }
//
//   }
//
//   return true;
//
//}
//
//
//template < class VALUE, class ARG_VALUE = const VALUE &, class COMPARE = ::comparison::binary < string > >
//class fifo_string_map :
//   virtual public fifo_attrib_map < fifo_map < string, const string &, VALUE, ARG_VALUE, COMPARE > >
//{
//public:
//
//
//   fifo_string_map(::count nBlockSize = 10);
//   fifo_string_map(const fifo_string_map & fifo_map);
//
//
//   fifo_string_map & operator = (const fifo_string_map & fifo_map);
//
//
//};
//
//template < class VALUE, class ARG_VALUE, class COMPARE >
//fifo_string_map < VALUE, ARG_VALUE, COMPARE >::fifo_string_map(::count nBlockSize) :
//   fifo_map < string, const string &, VALUE, ARG_VALUE, COMPARE > (nBlockSize)
//{
//}
//
//template < class VALUE, class ARG_VALUE, class COMPARE >
//fifo_string_map < VALUE, ARG_VALUE, COMPARE >::fifo_string_map(const fifo_string_map & fifo_map) :
//   fifo_attrib_map < ::fifo_map < string, const string &, VALUE, ARG_VALUE, COMPARE > > (fifo_map)
//{
//}
//
//template < class VALUE, class ARG_VALUE, class COMPARE >
//fifo_string_map < VALUE, ARG_VALUE, COMPARE > & fifo_string_map < VALUE, ARG_VALUE, COMPARE >::operator = (const fifo_string_map & fifo_map)
//{
//
//   if(this != &fifo_map)
//   {
//
//      fifo_attrib_map < ::fifo_map < string, const string &, VALUE, ARG_VALUE, COMPARE > >::operator = (fifo_map);
//
//   }
//
//   return *this;
//
//}
//
//template < class VALUE, class ARG_VALUE = const VALUE &   >
//class fifo_strid_map :
//   virtual public fifo_attrib_map < fifo_map < id, const id &, VALUE, ARG_VALUE > >
//{
//public:
//
//   fifo_strid_map(::count nBlockSize = 256);
//   fifo_strid_map(const fifo_strid_map & fifo_map);
//
//
//   fifo_strid_map & operator = (const fifo_strid_map & fifo_map);
//
//
//};
//
//
//template < class VALUE, class ARG_VALUE>
//fifo_strid_map < VALUE, ARG_VALUE>::fifo_strid_map(::count nBlockSize) :
//   fifo_attrib_map < fifo_map < id, const id &, VALUE, ARG_VALUE > > (nBlockSize)
//{
//}
//
//
//template < class VALUE, class ARG_VALUE >
//fifo_strid_map < VALUE, ARG_VALUE>::fifo_strid_map(const fifo_strid_map & fifo_map) :
//   fifo_attrib_map < ::fifo_map < id, const id &, VALUE, ARG_VALUE > > (fifo_map)
//{
//}
//
//template < class VALUE, class ARG_VALUE >
//fifo_strid_map < VALUE, ARG_VALUE > & fifo_strid_map < VALUE, ARG_VALUE >::operator = (const fifo_strid_map & fifo_map)
//{
//
//   if(this != &fifo_map)
//   {
//      fifo_attrib_map < ::fifo_map < id, const id &, VALUE, ARG_VALUE > >::operator = (fifo_map);
//   }
//
//   return *this;
//
//}
//
//template < class VALUE, class ARG_VALUE = const VALUE &, class COMPARE = ::comparison::binary < i32 > >
//class fifo_int_map :
//   virtual public fifo_attrib_map < fifo_map < i32, i32, VALUE, ARG_VALUE, COMPARE > >
//{
//public:
//
//   fifo_int_map(::count nBlockSize = 10);
//   fifo_int_map(const fifo_int_map & fifo_map);
//
//
//   fifo_int_map & operator = (const fifo_int_map & fifo_map);
//
//};
//
//template < class VALUE, class ARG_VALUE, class COMPARE >
//fifo_int_map < VALUE, ARG_VALUE, COMPARE >::fifo_int_map(::count nBlockSize) :
//   fifo_map < i32, i32, VALUE, ARG_VALUE, COMPARE > (nBlockSize)
//{
//}
//
//template < class VALUE, class ARG_VALUE, class COMPARE >
//fifo_int_map < VALUE, ARG_VALUE, COMPARE >::fifo_int_map(const fifo_int_map & fifo_map) :
//   fifo_attrib_map < ::fifo_map < i32, i32, VALUE, ARG_VALUE, COMPARE > > (fifo_map)
//{
//}
//
//template < class VALUE, class ARG_VALUE, class COMPARE >
//fifo_int_map < VALUE, ARG_VALUE, COMPARE > & fifo_int_map < VALUE, ARG_VALUE, COMPARE >::operator = (const fifo_int_map & fifo_map)
//{
//
//   if(this != &fifo_map)
//   {
//      fifo_attrib_map < ::fifo_map < i32, i32, VALUE, ARG_VALUE, COMPARE > >::operator = (fifo_map);
//   }
//
//   return *this;
//
//}
//
//typedef CLASS_DECL_ACME fifo_attrib_map < fifo_map < i32, i32, i32, i32 > > fifo_int_to_int;
//typedef CLASS_DECL_ACME fifo_attrib_map < fifo_map < i32, i32, string, const string & > > fifo_int_to_string;
//typedef CLASS_DECL_ACME fifo_string_map < void *, void * > fifo_string_to_ptr;
//
//template < class T >
//class CLASS_DECL_ACME fifo_string_to_pointer :
//   virtual public string_to_ptr
//{
//public:
//
//   class pair
//   {
//   public:
//      const string first;
//      T * second;
//   };
//
//   bool lookup(string key, T * & rValue) const
//   {
//      return string_to_ptr::lookup(key, rValue);
//   }
//   const pair *plookup(string key) const
//   {
//      return reinterpret_cast < const fifo_string_to_pointer::pair * > (string_to_ptr::plookup(key));
//   }
//   pair *plookup(string key)
//   {
//      return reinterpret_cast < fifo_string_to_pointer::pair * > (string_to_ptr::plookup(key));
//   }
//
//
//   T ** pget(string key)
//   {
//      return (T**) string_to_ptr::pget(key);
//   }
//   T * get(string key)
//   {
//      T ** point = (T **) string_to_ptr::pget(key);
//      if(point == nullptr)
//         return nullptr;
//      else
//         return (T*) *point;
//   }
//
//   // Operations
//   // lookup and add if not there
//   T * & operator[](string key)
//   {
//      return (T * &) string_to_ptr::operator[](key);
//   }
//
//
//   pair * get_start()
//   {
//      return (pair *) string_to_ptr::get_start();
//   }
//
//   pair * get_next(pair * & rPpair)
//   {
//      return (pair *) string_to_ptr::get_next((string_to_ptr::pair * &) rPpair);
//   }
//
//};
//
//
//typedef CLASS_DECL_ACME fifo_string_map < iptr, iptr > fifo_string_to_intptr;
//
//typedef CLASS_DECL_ACME fifo_string_map < string, const string & > fifo_string_to_string_map;
//
//
//
