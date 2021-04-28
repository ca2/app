#pragma once


//
//
//
//template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, typename COMPARE = ::comparison::less < KEY >, bool m_bMultiKey = false >
//class sort_map :
//   virtual public ::matter
//{
//public:
//
//
//   typedef KEY          AXIS_KEY;
//   typedef ARG_KEY      AXIS_ARG_KEY;
//   typedef VALUE        AXIS_VALUE;
//   typedef ARG_VALUE    AXIS_ARG_VALUE;
//   typedef COMPARE      AXIS_COMPARE;
//
//
//   class node :
//      public ::pair < KEY,VALUE >
//   {
//   public:
//
//      node * left;
//      node * right;
//
//
//      node()
//      {
//         left = nullptr;
//         right = nullptr;
//      }
//
//      node(const KEY & element1)
//      {
//         this->element1() = element1;
//         left = nullptr;
//         right = nullptr;
//      }
//
//      node(const KEY & element1,const VALUE & element2)
//      {
//         this->element1() = element1;
//         this->element2() = element2;
//         left = nullptr;
//         right = nullptr;
//      }
//      node(const pair < KEY,VALUE > & pair)
//      {
//         this->element1() = pair.element1();
//         this->element2() = pair.element2();
//         left = nullptr;
//         right = nullptr;
//      }
//
//
//      void copy_value(const pair < KEY,VALUE > & key)
//      {
//
//         this->element1() = key.element1();
//         this->element2() = key.element2();
//
//      }
//
//
//      node * minimum() const
//      {
//         if(left == nullptr)
//            return (node *) this;
//         return left;
//      }
//
//
//      node * maximum() const
//      {
//         if(right == nullptr)
//            return (node *) this;
//         return right;
//      }
//
//      ::count children_count() const
//      {
//
//         ::count c = 0;
//
//         if(left != nullptr)
//            return left->children_count() + 1;
//
//         if(right != nullptr)
//            return right->children_count() + 1;
//
//         return c;
//
//      }
//
//      void erase_all()
//      {
//
//         if(left != nullptr)
//         {
//
//            left->erase_all();
//
//            delete left;
//
//            left = nullptr;
//
//         }
//
//         if(right != nullptr)
//         {
//
//            right->erase_all();
//
//            delete right;
//
//            right = nullptr;
//
//         }
//
//      }
//
//   };
//
//
//
//   class iterator
//   {
//   public:
//
//
//      node *         m_pnode;
//      sort_map *     m_pmap;
//
//
//      iterator()
//      {
//         m_pnode  = nullptr;
//         m_pmap   = nullptr;
//      }
//
//      iterator(const iterator & iterator)
//      {
//         m_pnode  = iterator.m_pnode;
//         m_pmap   = iterator.m_pmap;
//      }
//
//      iterator(node * pnode, sort_map * pmap)
//      {
//         m_pnode  = pnode;
//         m_pmap   = pmap;
//      }
//
//
//      node & operator * ()
//      {
//
//         return *m_pnode;
//
//      }
//
//
//      node * operator -> ()
//      {
//         return m_pnode;
//      }
//
//      node * operator -> () const
//      {
//         return m_pnode;
//      }
//
//
//      iterator & operator ++ ()
//      {
//         if(m_pnode != nullptr && m_pmap != nullptr)
//            m_pnode = m_pmap->get_next(m_pnode);
//         return *this;
//      }
//
//      iterator operator ++ (i32)
//      {
//         if(m_pnode != nullptr && m_pmap != nullptr)
//            m_pnode = m_pmap->get_next(m_pnode);
//         return *this;
//      }
//
//      bool operator == (const iterator & it) const
//      {
//         if(this == &it)
//            return true;
//         if(m_pnode == nullptr && it.m_pnode == nullptr && it.m_pmap == nullptr)
//            return true;
//         if(m_pmap != it.m_pmap)
//            return false;
//         return m_pnode == it.m_pnode;
//      }
//
//      bool operator != (const iterator & it) const
//      {
//         return !operator == (it);
//      }
//
//      iterator & operator = (const iterator & it)
//      {
//         if(this != &it)
//         {
//            m_pmap         = it.m_pmap;
//            m_pnode        = it.m_pnode;
//         }
//         return *this;
//      }
//
//   };
//
//   class const_iterator
//   {
//   public:
//
//
//      const node *         m_pnode;
//      const sort_map *     m_pmap;
//
//
//      const_iterator()
//      {
//         m_pnode  = nullptr;
//         m_pmap   = nullptr;
//      }
//
//      const_iterator(const iterator & iterator)
//      {
//         m_pnode  = iterator.m_pnode;
//         m_pmap   = iterator.m_pmap;
//      }
//
//      const_iterator(const const_iterator & iterator)
//      {
//         m_pnode  = iterator.m_pnode;
//         m_pmap   = iterator.m_pmap;
//      }
//
//      const_iterator(const node * pnode, const sort_map * pmap)
//      {
//         m_pnode  = pnode;
//         m_pmap   = pmap;
//      }
//
//      const node * operator -> ()
//      {
//         return m_pnode;
//      }
//
//      const node * operator -> () const
//      {
//         return m_pnode;
//      }
//
//
//      const_iterator & operator ++ ()
//      {
//         if(m_pnode != nullptr && m_pmap != nullptr)
//            m_pnode = m_pmap->get_next(m_pnode);
//         return *this;
//      }
//
//      const_iterator operator ++ (i32)
//      {
//         if(m_pnode != nullptr && m_pmap != nullptr)
//            m_pnode = m_pmap->get_next(m_pnode);
//         return *this;
//      }
//
//      bool operator == (const const_iterator & it) const
//      {
//         if(this == &it)
//            return true;
//         if(m_pnode == nullptr && it.m_pnode == nullptr && it.m_pmap == nullptr)
//            return true;
//         if(m_pmap != it.m_pmap)
//            return false;
//         return m_pnode == it.m_pnode;
//      }
//
//      bool operator != (const const_iterator & it) const
//      {
//         return !operator == (it);
//      }
//
//      const_iterator & operator = (const const_iterator & it)
//      {
//         if(this != &it)
//         {
//            m_pmap         = it.m_pmap;
//            m_pnode        = it.m_pnode;
//         }
//         return *this;
//      }
//
//      const_iterator & operator = (const iterator & it)
//      {
//         m_pmap         = it.m_pmap;
//         m_pnode        = it.m_pnode;
//         return *this;
//      }
//
//   };
//
//   node * m_pnode;
//   COMPARE m_compare;
//
//
//
//
//
//   sort_map(::count nBlockSize = 10);
//   sort_map(node nodes[], i32 iCount, ::count nBlockSize = 10);
//   virtual ~sort_map();
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
//      return iterator(get_start(), this);
//   }
//
//
//   iterator end()
//   {
//      return iterator(nullptr, this);
//   }
//
//   const_iterator begin() const
//   {
//      return const_iterator(get_start(), this);
//   }
//
//
//   const_iterator end() const
//   {
//      return const_iterator(nullptr, this);
//   }
//
//   iterator lower_bound (ARG_KEY k);
//   const_iterator lower_bound (ARG_KEY k) const;
//   iterator upper_bound (ARG_KEY k);
//   const_iterator upper_bound (ARG_KEY k) const;
//
//   ::count get_size() const;
//   ::count size() const;
//   ::count count() const;
//   bool is_empty() const;
//   bool empty() const;
//
//   // lookup
//   bool lookup(ARG_KEY key, VALUE& rValue) const;
//   const node *plookup(ARG_KEY key) const;
//   node *plookup(ARG_KEY key);
//
//
//   VALUE * pget(ARG_KEY key);
//
//   // Operations
//   // lookup and add if not there
//   VALUE & operator[](ARG_KEY key);
//
//   // add a new (key, value) node
//   void set_at(ARG_KEY key, ARG_VALUE newValue);
//
//   // removing existing (key, ?) node
//   ::count erase_key(ARG_KEY key);
//   void erase(iterator it);
//   ::count erase(const KEY & key);
//   void erase ( iterator element1(), iterator last );
//   void erase_all();
//   void clear();
//
//
//   bool erase_node(node * pnode);
//
//   bool delete_node(node * pnode, node * pnodeParent);
//
//
//   ::count count(const KEY & t) const;
//   bool has(const KEY & t) const;
//   bool contains(const KEY & t) const;
//
//
//   const node *get_start() const;
//   node *get_start();
//
//   void get_next(node *& rNextPosition, KEY& rKey, VALUE& rValue) const;
//
//   const node *get_next(const node * pnode) const;
//   node *get_next(const node * pnode);
//   const node *PGetPrevAssoc(const node * pnode) const;
//   node *PGetPrevAssoc(const node * pnode);
//
//   VALUE get(ARG_KEY argkey, ARG_VALUE valueDefault);
//
//   node * next(const node * pnode);
//   const node * next(const node * pnode) const;
//   node * prev(const node * pnode);
//   const node * prev(const node * pnode) const;
//
//
//   void set(sort_map & sort_map)
//   {
//      node * pnode = nullptr;
//      while(sort_map.next(pnode) != nullptr)
//      {
//         set_at(pnode->element1(), pnode->element2());
//      }
//   }
//
//   node * parent_node(const node * pnode) const;
//
//   node *   equally_keyed_next_node(const node * pnode) const;
//   node *   equally_keyed_prev_node(const node * pnode) const;
//   node *   find_node(ARG_KEY key) const;
//   node *   rfind_node(ARG_KEY key) const;
//
//   iterator find(ARG_KEY key);
//   const_iterator find(ARG_KEY key) const;
//   iterator rfind(ARG_KEY key);
//   const_iterator rfind(ARG_KEY key) const;
//
//   void    add_pair(ARG_KEY key, ARG_VALUE value);
//   void    insert(const pair < KEY, VALUE  > & pair);
//
//   node * minimum() const
//   {
//      if(m_pnode == nullptr)
//         return nullptr;
//      return m_pnode->minimum();
//   }
//
//   node * maximum() const
//   {
//      if(m_pnode == nullptr)
//         return nullptr;
//      return m_pnode->maximum();
//   }
//
//
//   inline bool compare(ARG_KEY a,ARG_KEY b) const
//   {
//      return m_compare(a,b);
//   }
//
//   inline bool is_equal(ARG_KEY a,ARG_KEY b) const
//   {
//      return !compare(a,b) && !compare(b,a);
//   }
//
//   inline bool compare(node a,node b) const
//   {
//      return compare(a.element1(),b.element1());
//   }
//
//   inline bool is_equal(node a,node b) const
//   {
//      return !compare(a,b) && !compare(b,a);
//   }
//
//
//   ::count get_count() const
//   {
//      if(m_pnode == nullptr)
//         return 0;
//      else
//         return m_pnode->children_count() + 1;
//   }
//
//};
//
///////////////////////////////////////////////////////////////////////////////
//// sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey > inline functions
//
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//inline ::count sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::get_size() const
//{
//
//   return this->get_count();
//
//}
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//inline ::count sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::count() const
//{
//
//   return  this->get_count();
//
//}
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//inline ::count sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::size() const
//{
//
//   return  this->get_count();
//
//}
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//inline bool sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::is_empty() const
//{
//
//   return m_pnode == nullptr;
//
//}
//
//
//
//template < class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class COMPARE,bool m_bMultiKey >
//inline bool sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::empty() const
//{
//
//   return this->is_empty();
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//inline void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::set_at(ARG_KEY key, ARG_VALUE newValue)
//{
//
//   add_pair(key, newValue);
//
//}
//
//
////template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
////inline typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::node * sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::get_start_position() const
////{
////
////   return (m_pnode == 0) ? nullptr : BEFORE_START_node *;
////
////}
////
////
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//const typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::node* sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::get_start() const
//{
//
//   return minimum();
//
//}
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::node* sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::get_start()
//{
//
//   return minimum();
//
//}
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::construct(::count nBlockSize)
//{
//
//   UNREFERENCED_PARAMETER(nBlockSize);
//
//   m_pnode = nullptr;
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::sort_map(::count nBlockSize)
//{
//
//   construct(nBlockSize);
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::sort_map(node nodes[], i32 iCount, ::count nBlockSize)
//{
//
//   construct(nBlockSize);
//
//   for(i32 i = 0; i < iCount; i++)
//   {
//
//      set_at(nodes[i].element1(), nodes[i].element2());
//
//   }
//
//}
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::erase_all()
//{
//
//   if(m_pnode == nullptr)
//      return;
//
//   m_pnode->erase_all();
//
//   delete m_pnode;
//
//   m_pnode = nullptr;
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//inline void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::clear()
//{
//
//   erase_all();
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::~sort_map()
//{
//
//   erase_all();
//
//}
//
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//bool sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::lookup(ARG_KEY key, VALUE& rValue) const
//{
//
//   node * passoc = plookup(key);
//
//   if (passoc == nullptr)
//      return false;
//
//   rValue = passoc->element2();
//
//   return true;
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//const typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::node* sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::plookup(ARG_KEY key) const
//{
//
//   index i;
//
//   if(!find_key(key, i))
//      return nullptr;
//
//   return this->m_ptra[i];
//
//}
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node* sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::plookup(ARG_KEY key)
//{
//
//   return find_node(key);
//
//}
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//VALUE * sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::pget(ARG_KEY key)
//{
//
//   node * point = plookup(key);
//
//   if(point == nullptr)
//      return nullptr;
//
//   return &point->element2();
//
//}
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//VALUE& sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::operator[](ARG_KEY key)
//{
//
//   ASSERT_VALID(this);
//
//   node * pnode = plookup(key);
//
//   if(pnode == nullptr)
//   {
//
//      add_pair(key, VALUE());
//
//      pnode = plookup(key);
//
//      ASSERT(pnode != nullptr);
//
//   }
//
//   return pnode->element2();  // return new matter
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//::count sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::erase_key(ARG_KEY key)
//{
//
//   ::count c = 0;
//
//   while(true)
//   {
//
//      node * pnode = find_node(key);
//
//      if(pnode == nullptr)
//         break;
//
//      erase_node(pnode);
//
//   }
//
//   return c;
//
//
//}
//
//
//template < class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class COMPARE,bool m_bMultiKey >
//bool sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::delete_node(node * pnode,node *pnodeParent)
//{
//
//   if(pnodeParent == nullptr)
//   {
//
//      pnodeParent = parent_node(pnode);
//
//   }
//
//   if(pnodeParent != nullptr)
//   {
//
//      if(pnodeParent->left == pnode)
//      {
//
//         pnodeParent->left = nullptr;
//
//      }
//      else if(pnodeParent->right == pnode)
//      {
//
//         pnodeParent->right = nullptr;
//
//      }
//
//      pnodeParent->copy_value(*pnode);
//
//   }
//
//   try
//   {
//
//      delete pnode;
//
//   }
//   catch(...)
//   {
//
//   }
//
//   return true;
//
//}
//
//
//template < class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class COMPARE,bool m_bMultiKey >
//bool sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::erase_node(node * pnode)
//{
//
//   if(pnode == m_pnode)
//   {
//
//      delete m_pnode;
//
//      m_pnode = nullptr;
//
//      return true;
//
//   }
//
//   if(pnode->left != nullptr)
//   {
//      if(pnode->right != nullptr)
//      {
//         node * succ = pnode->right->minimum();
//         pnode->copy_value(*succ);
//         return erase_node(succ);
//      }
//      else
//      {
//         return delete_node(pnode->left,pnode);
//      }
//   }
//   else if(pnode->right != nullptr)
//   {
//      return delete_node(pnode->right,pnode);
//   }
//   else
//   {
//
//      return delete_node(pnode,nullptr);
//
//   }
//
//}
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node *
//sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::equally_keyed_next_node(const typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node * pnode) const
//{
//
//   if(pnode == nullptr)
//      return nullptr;
//
//   node * pnodeSearch = pnode->right;
//
//   while(pnodeSearch != nullptr)
//   {
//
//      if(compare(*pnode,*pnodeSearch))
//      {
//
//         pnodeSearch = pnodeSearch->left;
//
//      }
//      else if(compare(*pnodeSearch,*pnode))
//      {
//
//         pnodeSearch = pnodeSearch->right;
//
//      }
//      else
//      {
//
//         break;
//
//      }
//
//   }
//
//   return pnodeSearch;
//
//}
//
//
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::iterator
//sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::find(ARG_KEY key)
//{
//
//   node * pnode = find_node(key);
//
//   if(pnode == nullptr)
//      return end();
//
//   return iterator(pnode, this);
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::const_iterator
//sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::find(ARG_KEY key) const
//{
//
//   node * pnode = find_node(key);
//
//   if(pnode == nullptr)
//      return end();
//
//   return const_iterator(pnode,this);
//
//}
//
//
//template < class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class COMPARE,bool m_bMultiKey >
//typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node *
//sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::parent_node(const node * pnode) const
//{
//
//   node * pnodeParent = nullptr;
//
//   node * pnodeSearch = m_pnode;
//
//   while(pnodeSearch != nullptr)
//   {
//
//      if(compare(*pnode,*pnodeSearch))
//      {
//
//         pnodeSearch = pnodeSearch->left;
//
//      }
//      else if(compare(*pnodeSearch,*pnode))
//      {
//
//         pnodeSearch = pnodeSearch->right;
//
//      }
//      else if(pnodeSearch == pnode)
//      {
//
//         return pnodeParent;
//
//      }
//
//      pnodeParent = pnodeSearch;
//
//   }
//
//   return nullptr;
//
//}
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node *
//sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::find_node(ARG_KEY key) const
//{
//
//   node * pnodeSearch = m_pnode;
//
//   while(pnodeSearch != nullptr)
//   {
//
//      if(compare(key,pnodeSearch->element1()))
//      {
//
//         pnodeSearch = pnodeSearch->left;
//
//      }
//      else if(compare(pnodeSearch->element1(),key))
//      {
//
//         pnodeSearch = pnodeSearch->right;
//
//      }
//      else
//      {
//
//         // in this ordinary tree, the highest nodes are the element1() ones inserted, even for multi key
//         break;
//
//      }
//
//   }
//
//   return pnodeSearch;
//
//}
//
//
//template < class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class COMPARE,bool m_bMultiKey >
//typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node *
//sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::equally_keyed_prev_node(const node * pnode) const
//{
//
//   node * pnodePrevious = nullptr;
//
//   node * pnodeSearch = m_pnode;
//
//   while(pnodeSearch != nullptr)
//   {
//
//      if(compare(*pnode,*pnodeSearch))
//      {
//
//         pnodeSearch = pnodeSearch->left;
//
//      }
//      else if(compare(*pnodeSearch,*pnode))
//      {
//
//         pnodeSearch = pnodeSearch->right;
//
//      }
//      else
//      {
//
//         if(pnodeSearch == pnode)
//            break;
//
//         pnodePrevious = pnodeSearch;
//
//      }
//
//   }
//
//   return pnodePrevious;
//
//}
//
//
//
//
//template < class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class COMPARE,bool m_bMultiKey >
//typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node *
//sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::rfind_node(ARG_KEY key) const
//{
//
//   node * pnodeLast = nullptr;
//
//   node * pnodeSearch = m_pnode;
//
//   while(pnodeSearch != nullptr)
//   {
//
//      if(compare(key,pnodeSearch->element1()))
//      {
//
//         pnodeSearch = pnodeSearch->left;
//
//      }
//      else if(compare(pnodeSearch->element1(),key))
//      {
//
//         pnodeSearch = pnodeSearch->right;
//
//      }
//      else
//      {
//
//         pnodeLast = pnodeSearch;
//
//      }
//
//   }
//
//   return pnodeLast;
//
//}
//
//
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::iterator
//sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::lower_bound (ARG_KEY k)
//{
//
//   node * pnode = find_node(k);
//
//   if(pnode == nullptr)
//      return end();
//   else
//      return iterator(pnode, this);
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::const_iterator
//sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::lower_bound (ARG_KEY k) const
//{
//
//   node * pnode = find_node(k);
//
//   if(pnode == nullptr)
//      return end();
//   else
//      return const_iterator(pnode,this);
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::iterator
//sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::upper_bound (ARG_KEY k)
//{
//
//   node * pnode = rfind_node(k);
//
//   if(pnode == nullptr)
//      return end();
//   else
//      return iterator(pnode,this);
//
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::const_iterator
//sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::upper_bound (ARG_KEY k) const
//{
//
//   node * pnode = rfind_node(k);
//
//   if(pnode == nullptr)
//      return end();
//   else
//      return const_iterator(pnode,this);
//
//
//}
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//::count sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::erase(const KEY & key)
//{
//
//   return erase_key(key) ? 1 : 0;
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::erase(iterator it)
//{
//
//   erase_key(it->element1());
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//::count sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::count(const KEY & key) const
//{
//
//   return this->plookup(key) != nullptr ? 1 : 0;
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//bool sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::has(const KEY & key) const
//{
//
//   return this->plookup(key) != nullptr;
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//bool sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::contains(const KEY & key) const
//{
//
//   return this->plookup(key) != nullptr;
//
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::erase(iterator element1(), iterator last)
//{
//
//   if(element1().m_pmap != this || last.m_pmap != this)
//      return;
//
//   node * pnode = element1().m_pnode;
//
//   node * pnodeNext;
//
//   while(pnode != nullptr)
//   {
//
//      pnodeNext = next(pnode);
//
//      erase_node(pnode);
//
//      if(pnode == last.m_pnode)
//         break;
//
//      pnode = pnodeNext;
//
//   }
//
//}
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::get_next(node *& rNextPosition, KEY& rKey, VALUE& rValue) const
//{
//
//   ASSERT_VALID(this);
//
//   ENSURE(this->m_ptra.get_count() > 0);  // never call on is_empty sort_map
//
//   index iRet = (index) rNextPosition;
//
//   if (iRet == (index) BEFORE_START_node *)
//   {
//      iRet = 1;
//   }
//
//   // find next association
//   index iNext = iRet + 1;
//   if(iNext > this->m_ptra.get_count())
//   {
//
//   }
//
//   rNextPosition  = (node *) iNext;
//
//   // fill in return data
//   rKey           = this->m_ptra[iRet - 1]->element1();
//   rValue         = this->m_ptra[iRet - 1]->element2();
//
//}
//
//template < class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class COMPARE,bool m_bMultiKey >
//const typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node*
//sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::next(const typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node * pnode) const
//{
//
//   return ((sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey > * ) this)->next(pnode);
//}
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::node*
//sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::next(const typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::node * pnode)
//{
//
//   if(pnode->right != nullptr)
//      return pnode->right->minimum();
//
//   node * pnodeNext = nullptr;
//
//   if(m_bMultiKey)
//   {
//
//      pnodeNext = equally_keyed_next_node(pnode);
//
//      if(pnodeNext != nullptr)
//         return pnodeNext;
//
//   }
//
//   node * pnodeRoot = m_pnode;
//
//   while(pnodeRoot != nullptr)
//   {
//
//      if(compare(*pnode, *pnodeRoot))
//      {
//
//         pnodeNext = pnodeRoot;
//
//         pnodeRoot = pnodeRoot->left;
//
//      }
//      else if(compare(*pnodeRoot,*pnode))
//      {
//
//         pnodeRoot = pnodeRoot->right;
//
//      }
//      else
//      {
//
//         break;
//
//      }
//
//   }
//
//   return pnodeNext;
//
//}
//
//template < class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class COMPARE,bool m_bMultiKey >
//const typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node*
//sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::prev(const typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node * pnode) const
//{
//
//   return ((sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey > *) this)->prev(pnode);
//}
//
//
//template < class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class COMPARE,bool m_bMultiKey >
//typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node*
//sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::prev(const typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node * pnode)
//{
//
//   if(pnode->right != nullptr)
//      return pnode->left->maximum();
//
//   node * pnodePrev = nullptr;
//
//   if(m_bMultiKey)
//   {
//
//      pnodePrev = equally_keyed_prev_node(pnode);
//
//      if(pnodePrev != nullptr)
//         return pnodePrev;
//
//   }
//
//   node * pnodeRoot = m_pnode;
//
//   while(pnodeRoot != nullptr)
//   {
//
//      if(compare(*pnodeRoot,*pnode))
//      {
//
//         pnodePrev = pnodeRoot;
//
//         pnodeRoot = pnodeRoot->right;
//
//      }
//      else if(compare(*pnode,*pnodeRoot))
//      {
//
//         pnodeRoot = pnodeRoot->left;
//
//      }
//      else
//      {
//
//         break;
//
//      }
//
//   }
//
//   return pnodePrev;
//
//}
//
//
//template < class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class COMPARE,bool m_bMultiKey >
//const typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node*
//sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::get_next(const typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node* pnode) const
//{
//
//   return next(pnode);
//
//}
//
//template < class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class COMPARE,bool m_bMultiKey >
//typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node*
//sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::get_next(const typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node* pnode)
//{
//
//
//   return next(pnode);
//
//}
//
//
//template < class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class COMPARE,bool m_bMultiKey >
//const typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node*
//sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::PGetPrevAssoc(const typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node* pnode) const
//{
//
//   return prev(pnode);
//
//}
//
//
//template < class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class COMPARE,bool m_bMultiKey >
//typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node*
//sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::PGetPrevAssoc(const typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node* pnode)
//{
//
//   return prev(pnode);
//
//}
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//VALUE sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey > ::
//get(ARG_KEY argkey, ARG_VALUE valueDefault)
//{
//   node * pnode = plookup(argkey);
//   if(pnode == nullptr)
//      return valueDefault;
//   else
//      return pnode->element2();
//}
//
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::dump(dump_context & dumpcontext) const
//{
//   matter::dump(dumpcontext);
//
//   dumpcontext << "with " << get_count() << " elements";
//   if (dumpcontext.GetDepth() > 0)
//   {
//      // Dump in format "[key] -> value"
//
//      const node * pnode = get_start();
//      while (pnode != nullptr)
//      {
//         pnode = get_next(pnode);
//         dumpcontext << "\n\t[";
//         dump_elements<KEY>(dumpcontext, &pnode->element1(), 1);
//         dumpcontext << "] = ";
//         dump_elements<VALUE>(dumpcontext, &pnode->element2(), 1);
//      }
//   }
//
//   dumpcontext << "\n";
//}
//
//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
//void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::assert_valid() const
//{
//
//   matter::assert_valid();
//
//}
//
//
//template < class type_map >
//class sort_attrib_map :
//   virtual public type_map
//{
//public:
//
//
//   sort_attrib_map(iptr nBlockSize = 10);
//   sort_attrib_map(const sort_attrib_map & sort_map);
//
//   sort_attrib_map & operator = (const sort_attrib_map & sort_map);
//
//   bool operator == (const sort_attrib_map & sort_map) const;
//
//
//};
//
//
//template < class type_map >
//sort_attrib_map < type_map >::sort_attrib_map(iptr nBlockSize) :
//   type_map(nBlockSize)
//{
//}
//
//template < class type_map >
//sort_attrib_map < type_map >::sort_attrib_map(const sort_attrib_map & attribmap)
//{
//   operator = (attribmap);
//}
//
//
//template < class type_map >
//bool sort_attrib_map < type_map >::operator == (const sort_attrib_map & attribmap) const
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
//template < class VALUE, typename ARG_VALUE = typename argument_of < VALUE >::type, class COMPARE = ::comparison::less < string > >
//class sort_string_map :
//   virtual public sort_attrib_map < sort_map < string, const string &, VALUE, ARG_VALUE, COMPARE > >
//{
//public:
//
//
//   sort_string_map(::count nBlockSize = 10);
//   sort_string_map(const sort_string_map & sort_map);
//
//
//   sort_string_map & operator = (const sort_string_map & sort_map);
//
//
//};
//
//template < class VALUE, class ARG_VALUE, class COMPARE >
//sort_string_map < VALUE, ARG_VALUE, COMPARE >::sort_string_map(::count nBlockSize) :
//   sort_map < string, const string &, VALUE, ARG_VALUE, COMPARE > (nBlockSize)
//{
//}
//
//template < class VALUE, class ARG_VALUE, class COMPARE >
//sort_string_map < VALUE, ARG_VALUE, COMPARE >::sort_string_map(const sort_string_map & sortmap) :
//   sort_attrib_map < sort_map < string, const string &, VALUE, ARG_VALUE, COMPARE > > (sortmap)
//{
//}
//
//template < class VALUE, class ARG_VALUE, class COMPARE >
//sort_string_map < VALUE, ARG_VALUE, COMPARE > & sort_string_map < VALUE, ARG_VALUE, COMPARE >::operator = (const sort_string_map & sortmap)
//{
//
//   if(this != &sortmap)
//   {
//
//      sort_attrib_map < sort_map < string, const string &, VALUE, ARG_VALUE, COMPARE > >::operator = (sortmap);
//
//   }
//
//   return *this;
//
//}
//
//template < class VALUE, typename ARG_VALUE = typename argument_of < VALUE >::type >
//class sort_strid_map :
//   virtual public sort_attrib_map < sort_map < id, const id &, VALUE, ARG_VALUE > >
//{
//public:
//
//   sort_strid_map(::count nBlockSize = 256);
//   sort_strid_map(const sort_strid_map & sort_map);
//
//
//   sort_strid_map & operator = (const sort_strid_map & sort_map);
//
//
//};
//
//
//template < class VALUE, class ARG_VALUE >
//sort_strid_map < VALUE, ARG_VALUE >::sort_strid_map(::count nBlockSize) :
//   sort_attrib_map < sort_map < id, const id &, VALUE, ARG_VALUE > > (nBlockSize)
//{
//}
//
//
//template < class VALUE, class ARG_VALUE >
//sort_strid_map < VALUE, ARG_VALUE >::sort_strid_map(const sort_strid_map & sortmap) :
//   sort_attrib_map < sort_map < id, const id &, VALUE, ARG_VALUE > > (sortmap)
//{
//}
//
//template < class VALUE, class ARG_VALUE >
//sort_strid_map < VALUE, ARG_VALUE > & sort_strid_map < VALUE, ARG_VALUE >::operator = (const sort_strid_map & sortmap)
//{
//
//   if(this != &sortmap)
//   {
//      sort_attrib_map < sort_map < id, const id &, VALUE, ARG_VALUE > >::operator = (sortmap);
//   }
//
//   return *this;
//
//}
//
//template < class VALUE, typename ARG_VALUE = typename argument_of < VALUE >::type, class COMPARE = ::comparison::binary < i32 > >
//class sort_int_map :
//   virtual public sort_attrib_map < sort_map < i32, i32, VALUE, ARG_VALUE, COMPARE > >
//{
//public:
//
//   sort_int_map(::count nBlockSize = 10);
//   sort_int_map(const sort_int_map & sort_map);
//
//
//   sort_int_map & operator = (const sort_int_map & sort_map);
//
//};
//
//template < class VALUE, class ARG_VALUE, class COMPARE >
//sort_int_map < VALUE, ARG_VALUE, COMPARE >::sort_int_map(::count nBlockSize) :
//   sort_map < i32, i32, VALUE, ARG_VALUE, COMPARE > (nBlockSize)
//{
//}
//
//template < class VALUE, class ARG_VALUE, class COMPARE >
//sort_int_map < VALUE, ARG_VALUE, COMPARE >::sort_int_map(const sort_int_map & sortmap) :
//   sort_attrib_map < sort_map < i32, i32, VALUE, ARG_VALUE, COMPARE > > (sortmap)
//{
//}
//
//template < class VALUE, class ARG_VALUE, class COMPARE >
//sort_int_map < VALUE, ARG_VALUE, COMPARE > & sort_int_map < VALUE, ARG_VALUE, COMPARE >::operator = (const sort_int_map & sortmap)
//{
//
//   if(this != &sortmap)
//   {
//      sort_attrib_map < sort_map < i32, i32, VALUE, ARG_VALUE, COMPARE > >::operator = (sortmap);
//   }
//
//   return *this;
//
//}
//
//typedef CLASS_DECL_ACME sort_attrib_map < sort_map < i32, i32, i32, i32 > > sort_int_to_int;
//typedef CLASS_DECL_ACME sort_attrib_map < sort_map < i32, i32, string, const string & > > sort_int_to_string;
//typedef CLASS_DECL_ACME sort_string_map < void *, void * > sort_string_to_ptr;
//
//template < class T >
//class CLASS_DECL_ACME sort_string_to_pointer :
//   virtual public string_to_ptr
//{
//public:
//
//   class node
//   {
//   public:
//      const string element1();
//      T * element2();
//   };
//
//   bool lookup(string key, T * & rValue) const
//   {
//      return string_to_ptr::lookup(key, rValue);
//   }
//   const node *plookup(string key) const
//   {
//      return reinterpret_cast < const sort_string_to_pointer::node * > (string_to_ptr::plookup(key));
//   }
//   node *plookup(string key)
//   {
//      return reinterpret_cast < sort_string_to_pointer::node * > (string_to_ptr::plookup(key));
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
//         return (T*) *point_i32;
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
//   node * get_start()
//   {
//      return (node *) string_to_ptr::get_start();
//   }
//
//   node * get_next(node * & rPnode)
//   {
//      return (node *) string_to_ptr::get_next((node * &) rPnode);
//   }
//
//};
//
//
//
//
//
//typedef CLASS_DECL_ACME sort_string_map < iptr, iptr > sort_string_to_intptr;
//
//typedef CLASS_DECL_ACME sort_string_map < string, const string & > sort_string_to_string_map;
//
//
//
//
//
///*
//
//inline void sort_map_test()
//{
//   sort_string_to_intptr m;
//
//   m.insert(pair< string, iptr>("Casa",1));
//   m.insert(pair< string,iptr>("Casa",2));
//   m.insert(pair< string,iptr>("Mummi",2));
//   m.insert(pair< string,iptr>("Mummi",3));
//   m.insert(pair< string,iptr>("Camilo",3));
//   m.insert(pair< string,iptr>("Camilo",4));
//   m.insert(pair< string,iptr>("Ca2",1));
//   m.insert(pair< string,iptr>("Ca2",2));
//   m.insert(pair< string,iptr>("Ca2",3));
//   m.insert(pair< string,iptr>("Ca2",4));
//   m.insert(pair< string,iptr>("Ca2",5));
//
//   sort_string_to_intptr::node * point = m.get_start();
//
//   point = m.get_next(point);
//
//   ::count c = m.get_count();
//
//   sort_string_to_intptr::iterator lower = m.lower_bound("Ca2");
//   sort_string_to_intptr::iterator upper = m.upper_bound("Ca2");
//
//}
//
//
//*/
//
//
