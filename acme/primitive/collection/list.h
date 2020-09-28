#pragma once


template < class TYPE, class ARG_TYPE = const TYPE & >
class list :
   public ::elemental
{
public:


   class node
   {
   public:


      node *   m_pnext;
      node *   m_pprevious;
      TYPE     m_value;


      node(ARG_TYPE t, node * pprev, node * pnext) : m_value(t), m_pprevious(pprev), m_pnext(pnext) { }


   };

   __declare_iterator_struct_ok(list, node *, m_pnode, ::is_set(this->m_pnode));


   template < typename ITERATOR > struct make_iterator : ITERATOR
   {

      using CONTAINER = typename ITERATOR::CONTAINER;

      using ITERATOR::ITERATOR;

      make_iterator(const node * pnode = nullptr, const CONTAINER * plist = nullptr)
      {

         this->m_pnode = (node *)pnode;
         this->m_pcontainer = (CONTAINER *)plist;
         this->m_pnodeBeg = (node *)pnode;
         this->m_pnodeEnd = (node *)nullptr;

      }


      make_iterator(const iterator_struct & p)
      {

         this->m_pnode = (node *) p.m_pnode;
         this->m_pcontainer = (CONTAINER *) p.m_pcontainer;
         this->m_pnodeBeg = (node *)p.m_pnodeBeg;
         this->m_pnodeEnd = (node *)p.m_pnodeEnd;

      }

      make_iterator(const const_iterator_struct & p)
      {

         this->m_pnode = (node *)p.m_pnode;
         this->m_pcontainer = (CONTAINER *)p.m_pcontainer;
         this->m_pnodeBeg = (node *)p.m_pnodeBeg;
         this->m_pnodeEnd = (node *)p.m_pnodeEnd;

      }


      make_iterator begin()
      {

         return make_iterator(this->m_pcontainer->get_start(), this->m_pcontainer);

      }


      make_iterator end()
      {

         return make_iterator(nullptr, this->m_pcontainer);

      }


      make_iterator & operator ++ ()
      {

         this->m_pnode = this->m_pnode->m_pnext;

         return *this;

      }


      make_iterator operator ++ (i32)
      {

         make_iterator iterator = this->m_pnode;

         this->m_pnode = this->m_pnode->m_pnext;

         return iterator;

      }

      make_iterator & operator -- ()
      {

         this->m_pnode = this->m_pnode->m_pprevious;

         return *this;

      }


      make_iterator operator -- (i32)
      {

         make_iterator iterator = this->m_pnode;

         this->m_pnode = this->m_pnode->m_pprevious;

         return iterator;

      }

      bool operator == (const make_iterator & it) const
      {

         if (this == &it)
         {

            return true;

         }

         if (this->m_pnode == nullptr && it.m_pnode == nullptr && it.m_pcontainer == nullptr)
         {

            return true;

         }

         if (this->m_pcontainer != it.m_pcontainer)
         {

            return false;

         }

         return this->m_pnode == it.m_pnode;

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

            this->m_pnode = it.m_pnode;

         }

         return *this;

      }


   };


   __declare_iterator(dereferenced_value_iterator, this->m_pnode->m_value);
   __declare_iterator(value_iterator, &this->m_pnode->m_value);
   __declare_iterator(iterator, &this->m_pnode->m_value);

   using dereferenced_iterator = dereferenced_value_iterator;


   node *         m_phead;
   node *         m_ptail;
   ::count        m_count;


   list();
   list(const list & l);
   list(class list && l);
   virtual ~list();

   //inline list();
   //inline list(const class list < TYPE, ARG_TYPE > & l);
   //inline list(const class list < TYPE, ARG_TYPE > & l);

   inline static void from(list < TYPE, ARG_TYPE > & l, node * point);
   inline static list < TYPE, ARG_TYPE >  from(node * point);

   // helper functions (note: O(n) speed)
   // defaults to starting at the HEAD, return nullptr if not found
   iterator index_iterator(index nIndex);
   // get the 'nIndex'th element (may return nullptr)
   index iterator_index(iterator iterator);
   // get the reverse 'nIndex' of the position (may return -1)
   iterator reverse_index_iterator(index nIndex);

   inline auto values() const { return value_iterator(nullptr, this); }

   const_iterator index_iterator(index nIndex) const
   {
      return ((list *)this)->index_iterator(nIndex);
   }

   const_iterator reverse_index_iterator(index nIndex) const
   {
      return ((list *)this)->reverse_index_iterator(nIndex);
   }


   index iterator_index(const_iterator it) const
   {
      return ((list *)this)->iterator_index(iterator((node *)(node *)it.m_pnode, (list *)this));
   }


   // getting/modifying an element at a given position
   TYPE & get_at(node * pnode) { return pnode->m_value; }
   const TYPE & get_at(node * pnode) const { return pnode->m_value; }
   void set_at(node * pnode, ARG_TYPE newElement) { pnode->m_value = newElement; }

   // iteration
   node * get_head() const;
   node * get_tail() const;


   iterator lower_bound()
   {
      return iterator(nullptr, this);
   }


   iterator begin()
   {
      return iterator(get_head(), this);
   }


   iterator end()
   {
      return iterator(nullptr, this);
   }


   iterator upper_bound()
   {
      return iterator(get_tail(), this);
   }

   const_iterator lower_bound() const
   {
      return const_iterator(nullptr, this);
   }


   const_iterator begin() const
   {
      return const_iterator(get_head(), this);
   }


   const_iterator end() const
   {
      return const_iterator(nullptr, this);
   }

   const_iterator upper_bound() const
   {
      return const_iterator(get_tail(), this);
   }



   inline node * get_start() const { return get_head(); }

   void remove_item(node * pnode);

   node * detach(node * pnode);

   template < typename ITERATOR > inline ITERATOR erase(ITERATOR it) { return ::papaya::iterator::erase(*this, it); }

   template < typename ITERATOR >
   inline void erase(const ITERATOR & begin, const ITERATOR & last) { ::erase(*this, begin, last); }

   virtual void assert_valid() const override;
   virtual void dump(dump_context & dumpcontext) const override;



   //void Serialize(CArchive&);
// Attributes (head and tail)
   // ::count of elements
   ::count get_count() const;
   ::count get_size() const;
   ::count size() const;
   bool is_empty(::count countMinimum = 1) const;
   bool has_elements(::count countMinimum = 1) const;
   bool empty(::count countMinimum = 1) const;

   // peek at head or tail
   TYPE& head();
   const TYPE& head() const;
   TYPE& tail();
   const TYPE& tail() const;

   // Operations
   // get head or tail (and remove it) - don't call on is_empty list !
   void remove_head();
   void remove_tail();

   TYPE pop_head();
   TYPE pop_tail();

   // add before head or after tail
   node * add_head(ARG_TYPE newElement);
   node * add_tail(ARG_TYPE newElement);

   void push_front(ARG_TYPE newElement);
   void push_back(ARG_TYPE newElement);

   // add another list of elements before head or after tail
   void copy_head(const list < TYPE, ARG_TYPE > & l);
   void copy_tail(const list < TYPE, ARG_TYPE > & l);
   void copy(const list < TYPE, ARG_TYPE > & l);

   // remove all elements
   void remove_all();
   void clear();

   TYPE & front();
   const TYPE & front() const;
   TYPE & back();
   const TYPE & back() const;

   TYPE pop_front();

   //TYPE& get_next(node *& rPosition); // return *position++
   //const TYPE& get_next(node *& rPosition) const; // return *position++
   //TYPE& get_previous(node *& rPosition); // return *position--
   //const TYPE& get_previous(node *& rPosition) const; // return *position--


   void remove_at(index i);





   //node * detach(node * position);
   //node * detach(iterator it);

   ::count detach(iterator first, iterator last);

   iterator insert(iterator position, ARG_TYPE newElement);
   iterator insert(iterator position, iterator it);
   iterator insert(iterator position, node * pnode);
   iterator insert(iterator position, list < TYPE, ARG_TYPE > & l);
   iterator insert(iterator position, iterator first, iterator last);

   iterator insert_before(iterator position, ARG_TYPE newElement);
   iterator insert_before(iterator position, iterator it);
   iterator insert_before(iterator position, node * pnode);
   iterator insert_before(iterator position, list < TYPE, ARG_TYPE > & l);
   iterator insert_before(iterator position, iterator first, iterator last);

   iterator insert_after(iterator position, ARG_TYPE newElement);
   iterator insert_after(iterator position, iterator it);
   iterator insert_after(iterator position, node * pnode);
   iterator insert_after(iterator position, list < TYPE, ARG_TYPE > & l);
   iterator insert_after(iterator position, iterator first, iterator last);

   node * insert(node * position, ARG_TYPE newElement);
   node * insert(node * position, iterator it);
   node * insert(node * position, node * pnode);
   node * insert(node * position, list < TYPE, ARG_TYPE > & l);
   node * insert(node * position, iterator first, iterator last);

   node * insert_before(node * position, ARG_TYPE newElement);
   node * insert_before(node * position, iterator it);
   node * insert_before(node * position, node * pnode);
   node * insert_before(node * position, list < TYPE, ARG_TYPE > & l);
   node * insert_before(node * position, iterator first, iterator last);

   node * insert_after(node * position, ARG_TYPE newElement);
   node * insert_after(node * position, iterator it);
   node * insert_after(node * position, node * pnode);
   node * insert_after(node * position, list < TYPE, ARG_TYPE > & l);
   node * insert_after(node * position, iterator first, iterator last);


   void splice(iterator position, list & l);
   void splice(iterator position, list & l, iterator i);
   void splice(iterator position, list & l, iterator first, iterator last);
   void __swap(node * position1, node * position2);


   list < TYPE, ARG_TYPE > & operator = (const class list & l);
#ifdef MOVE_SEMANTICS
   list < TYPE, ARG_TYPE > & operator = (class list && l);
#endif


   template < typename PRED >
   void each(PRED pred)
   {

      auto p = begin();

      while (p.ok())
      {

#ifdef CPP17

         if (returns_false(pred, true, *p))
         {

            break;

         }

#else

         pred(*p);


#endif

         p++;

      }

   }

};


template<class TYPE, class ARG_TYPE>
inline list < TYPE, ARG_TYPE >::list()
{

   this->m_count = 0;
   this->m_phead = nullptr;
   this->m_ptail = nullptr;

}


template<class TYPE, class ARG_TYPE>
list<TYPE, ARG_TYPE>::list(const list & l)
{

   this->m_count = 0;
   this->m_phead = nullptr;
   this->m_ptail = nullptr;

   copy(l);

}


template<class TYPE, class ARG_TYPE>
inline void list < TYPE, ARG_TYPE >::from(list < TYPE, ARG_TYPE > & l, node * pnode)
{

   l.m_ptail = nullptr;

   l.m_phead = pnode;

   l.m_count = 0;

   if (pnode == nullptr)
      return;

   while (true)
   {

      if (pnode->m_pnext == nullptr)
      {

         l.m_ptail = pnode;

         break;

      }

      pnode = pnode->m_pnext;

      l.m_count++;

   }

   l.m_count++;

}

template<class TYPE, class ARG_TYPE>
inline list < TYPE, ARG_TYPE > list < TYPE, ARG_TYPE >::from(node * point)
{

   list < TYPE, ARG_TYPE >  l;
   from(l, point);
   return l;

}



template<class TYPE, class ARG_TYPE>
inline ::count list<TYPE, ARG_TYPE>::get_count() const
{

   return this->m_count;

}


template<class TYPE, class ARG_TYPE>
inline ::count list<TYPE, ARG_TYPE>::get_size() const
{

   return this->m_count;

}


template<class TYPE, class ARG_TYPE>
inline ::count list<TYPE, ARG_TYPE>::size() const
{
   return this->m_count;
}

template<class TYPE, class ARG_TYPE>
inline bool list<TYPE, ARG_TYPE>::is_empty(::count countMinimum) const
{
   return this->m_count < countMinimum;
}

template<class TYPE, class ARG_TYPE>
inline bool list<TYPE, ARG_TYPE>::empty(::count countMinimum) const
{
   return this->m_count < countMinimum;
}

template<class TYPE, class ARG_TYPE>
inline bool list<TYPE, ARG_TYPE>::has_elements(::count countMinimum) const
{
   return this->m_count >= countMinimum;
}

template<class TYPE, class ARG_TYPE>
inline TYPE& list<TYPE, ARG_TYPE>::head()
{
   return this->m_phead->m_value;
}
template<class TYPE, class ARG_TYPE>
inline const TYPE& list<TYPE, ARG_TYPE>::head() const
{
   return this->m_phead->m_value;
}
template<class TYPE, class ARG_TYPE>
inline TYPE& list<TYPE, ARG_TYPE>::tail()
{
   return this->m_ptail->m_value;
}
template<class TYPE, class ARG_TYPE>
inline const TYPE& list<TYPE, ARG_TYPE>::tail() const
{
   return this->m_ptail->m_value;
}
template<class TYPE, class ARG_TYPE>
inline typename list<TYPE, ARG_TYPE>::node * list<TYPE, ARG_TYPE>::get_head() const
{
   return this->m_phead;
}
template<class TYPE, class ARG_TYPE>
inline typename list<TYPE, ARG_TYPE>::node * list<TYPE, ARG_TYPE>::get_tail() const
{
   return (node *) this->m_ptail;
}

template<class TYPE, class ARG_TYPE>
inline TYPE & list < TYPE, ARG_TYPE >::front()
{
   return get_at(this->get_head());
}

template<class TYPE, class ARG_TYPE>
inline const TYPE & list < TYPE, ARG_TYPE >::front() const
{
   return get_at(this->get_head());
}

template<class TYPE, class ARG_TYPE>
inline TYPE list < TYPE, ARG_TYPE >::pop_front()
{
   auto it = this->begin();
   TYPE t = *it;
   this->erase(it);
   return t;
}

template<class TYPE, class ARG_TYPE>
inline TYPE & list < TYPE, ARG_TYPE >::back()
{
   return this->get_at(this->get_tail());
}

template<class TYPE, class ARG_TYPE>
inline const TYPE & list < TYPE, ARG_TYPE >::back() const
{
   return get_at(this->get_tail());
}
template<class TYPE, class ARG_TYPE>
list<TYPE, ARG_TYPE>::list(class list && l)
{

   this->m_count = l.m_count;
   this->m_phead = l.m_phead;
   this->m_ptail = l.m_ptail;

   l.m_phead = nullptr;
   l.m_ptail = nullptr;

}

template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::remove_all()
{

   ASSERT_VALID(this);


   node * pnode;

   node * pnext;

   for (pnode = this->m_phead; pnode != nullptr; pnode = pnext)
   {

      pnext = pnode->m_pnext;

      try
      {

         delete pnode;

      }
      catch (...)
      {

      }

   }

   this->m_phead = nullptr;

   this->m_ptail = nullptr;

   this->m_count = 0;

}

template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::clear()
{

   remove_all();

}

template<class TYPE, class ARG_TYPE>
list<TYPE, ARG_TYPE>::~list()
{
   remove_all();
   ASSERT(this->m_count == 0);
}


template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::push_front(ARG_TYPE newElement)
{

   add_head(newElement);

}

template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::push_back(ARG_TYPE newElement)
{

   add_tail(newElement);

}

template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::copy_head(const list < TYPE, ARG_TYPE >  & l)
{

   ASSERT_VALID(this);

   node * pnode = l.m_ptail;

   while (pnode != nullptr)
   {
      add_head(pnode->m_value);
      pnode = pnode->m_pprevious;
   }

}

template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::copy_tail(const list < TYPE, ARG_TYPE >  & l)
{

   ASSERT_VALID(this);

   node * pnode = l.m_ptail;

   while (pnode != nullptr)
   {
      add_tail(pnode->m_value);
      pnode = pnode->m_pnext;
   }

}

template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::copy(const list < TYPE, ARG_TYPE >  & l)
{

   ASSERT_VALID(this);

   if (this == &l)
      return;

   remove_all();

   node * pnode = l.m_ptail;

   while (pnode != nullptr)
   {
      add_head(pnode->m_value);
      pnode = pnode->m_pprevious;
   }

}

template<class TYPE, class ARG_TYPE>
TYPE list<TYPE, ARG_TYPE>::pop_head()
{
   ASSERT_VALID(this);
   ASSERT(this->m_phead != nullptr);  // don't call on is_empty list !!!
   ASSERT(__is_valid_address(this->m_phead, sizeof(node)));

   node* pnodeOld = this->m_phead;
   TYPE returnValue = pnodeOld->m_value;

   this->m_phead = pnodeOld->m_pnext;
   if (this->m_phead != nullptr)
      this->m_phead->m_pprevious = nullptr;
   else
      this->m_ptail = nullptr;
   delete pnodeOld;

   this->m_count--;

   return returnValue;
}

template<class TYPE, class ARG_TYPE>
TYPE list<TYPE, ARG_TYPE>::pop_tail()
{
   ASSERT_VALID(this);
   ASSERT(this->m_ptail != nullptr);  // don't call on is_empty list !!!
   ASSERT(__is_valid_address(this->m_ptail, sizeof(node)));

   node* pnodeOld = this->m_ptail;
   TYPE returnValue = pnodeOld->m_value;

   this->m_ptail = pnodeOld->m_pprevious;
   if (this->m_ptail != nullptr)
      this->m_ptail->m_pnext = nullptr;
   else
      this->m_phead = nullptr;
   this->m_count--;
   delete pnodeOld;
   return returnValue;
}

template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::remove_head()
{
   ASSERT_VALID(this);
   ASSERT(this->m_phead != nullptr);  // don't call on is_empty list !!!
   ASSERT(__is_valid_address(this->m_phead, sizeof(node)));

   node* pnodeOld = this->m_phead;

   this->m_phead = pnodeOld->m_pnext;
   if (this->m_phead != nullptr)
      this->m_phead->m_pprevious = nullptr;
   else
      this->m_ptail = nullptr;
   delete pnodeOld;

   this->m_count--;

}

template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::remove_tail()
{
   ASSERT_VALID(this);
   ASSERT(this->m_ptail != nullptr);  // don't call on is_empty list !!!
   ASSERT(__is_valid_address(this->m_ptail, sizeof(node)));

   node* pnodeOld = this->m_ptail;

   this->m_ptail = pnodeOld->m_pprevious;
   if (this->m_ptail != nullptr)
      this->m_ptail->m_pnext = nullptr;
   else
      this->m_phead = nullptr;
   this->m_count--;
   delete pnodeOld;
}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert(iterator i, ARG_TYPE newElement) // same as insert before
{

   ASSERT(this == i.m_pcontainer);

   return insert_before(i, newElement);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert(iterator i, iterator it) // same as insert before
{

   ASSERT(this == i.m_pcontainer);

   return insert_before(i, it);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert(iterator i, node * pnode)
{

   ASSERT(this == i.m_pcontainer);

   return insert_before(i, pnode);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert(iterator i, list < TYPE, ARG_TYPE > & l)
{

   ASSERT(this == i.m_pcontainer);

   return insert_before(i, l);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert(iterator i, iterator first, iterator last)
{

   ASSERT(this == i.m_pcontainer);

   ASSERT(first.m_pcontainer == last.m_pcontainer);

   return insert_before(i, first, last);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_before(iterator i, ARG_TYPE newElement)
{

   ASSERT(this == i.container());

   return iterator(insert_before(i.item(), newElement), this);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_before(iterator i, iterator it)
{

   ASSERT(this == i.m_pcontainer);

   return iterator((node *)insert_before((node *)i.m_pnode, it), this);

}




template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_before(iterator i, node * pnode)
{

   ASSERT(this == i.m_pcontainer);

   return iterator((node *)insert_before((node *)i.m_pnode, pnode), this);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_before(iterator i, list < TYPE, ARG_TYPE >  & l)
{

   ASSERT(this == i.m_pcontainer);

   return iterator((node *)insert_before((node *)i.m_pnode, l), this);

}

template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_before(iterator i, iterator first, iterator last)
{

   ASSERT(this == i.m_pcontainer);

   ASSERT(first.m_pcontainer == last.m_pcontainer);

   return iterator((node *)insert_before((node *)i.m_pnode, first, last), this);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_after(iterator i, ARG_TYPE newElement)
{

   ASSERT(this == i.m_pcontainer);

   return iterator((node *)insert_after((node *)i.m_pnode, newElement), this);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_after(iterator i, iterator it)
{

   ASSERT(this == i.m_pcontainer);

   return iterator((node *)insert_after((node *)i.m_pnode, it), this);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_after(iterator i, node * pnode)
{

   ASSERT(this == i.m_pcontainer);

   return iterator((node *)insert_after((node *)i.m_pnode, pnode), this);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_after(iterator i, list < TYPE, ARG_TYPE >  & l)
{

   ASSERT(this == i.m_pcontainer);

   return iterator((node *)insert_after((node *)i.m_pnode, l), this);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_after(iterator i, iterator first, iterator last)
{

   ASSERT(this == i.m_pcontainer);

   ASSERT(first.m_pcontainer == last.m_pcontainer);

   return iterator((node *)insert_after((node *)i.m_pnode, first, last), this);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::node * list < TYPE, ARG_TYPE > ::insert(node * position, ARG_TYPE newElement)
{

   return insert_before(position, newElement);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::node * list < TYPE, ARG_TYPE > ::insert(node * position, iterator it)
{

   return insert_before(position, it);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::node * list < TYPE, ARG_TYPE > ::insert(node * position, node * pnode) // same as insert before
{

   return insert_before(position, pnode);

}



template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::node * list < TYPE, ARG_TYPE > ::insert(node * position, list < TYPE, ARG_TYPE > & l) // same as insert before
{

   return insert_before(position, l);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::node * list < TYPE, ARG_TYPE > ::insert(node * position, iterator first, iterator last) // same as insert before
{

   return insert_before(position, first, last);

}



template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::node * list < TYPE, ARG_TYPE > ::insert_before(node * position, node * pnode)
{

   list < TYPE, ARG_TYPE > l;

   list < TYPE, ARG_TYPE >::from(l, pnode);

   return insert_before(position, l);

}




template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::node * list < TYPE, ARG_TYPE > ::insert_before(node * position, list < TYPE, ARG_TYPE > & l)
{

   if (l.m_count <= 0)
      return position;

   this->m_count += l.m_count;

   node * pnode = (node *) position;

   if (pnode != nullptr)
   {

      if (pnode->m_pprevious != nullptr)
      {

         pnode->m_pprevious->m_pnext = l.m_phead;

      }

      l.m_phead->m_pprevious = pnode->m_pprevious;

      pnode->m_pprevious = l.m_ptail;

      if (pnode == this->m_phead)
      {

         this->m_phead = l.m_phead;

         this->m_phead->m_pprevious = nullptr;

      }

   }
   else
   {

      l.m_phead->m_pprevious = this->m_ptail;

      this->m_ptail = l.m_phead;

      if (this->m_phead == nullptr)
      {

         this->m_phead = l.m_phead;

      }

   }

   l.m_ptail->m_pnext = pnode;

   return (node *)l.m_phead;

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::node * list < TYPE, ARG_TYPE > ::insert_before(node * position, iterator first, iterator last)
{

   ::count count = last - first;

   if (count < 0)
   {

      return nullptr;

   }

   this->m_count += count;

   node * pnode = (node *)position;

   if (pnode != nullptr)
   {

      if (pnode->m_pprevious != nullptr)
      {

         pnode->m_pprevious->m_pnext = first.m_pnode;

      }

      first.m_pnode->m_pprevious = pnode->m_pprevious;

      pnode->m_pprevious = last.m_pnode;

      if (pnode == this->m_phead)
      {

         this->m_phead = first.m_pnode;

         this->m_phead->m_pprevious = nullptr;

      }

   }
   else
   {

      first.m_pnode->m_pprevious = this->m_ptail;

      this->m_ptail = first.m_pnode;

      if (this->m_phead == nullptr)
      {

         this->m_phead = first.m_pnode;

      }

   }

   last.m_pnode->m_pnext = pnode;

   return (node *)first.m_pnode;

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::node * list<TYPE, ARG_TYPE>::insert_after(node * position, iterator it)
{

   return insert_after(position, (node *)it.m_pnode);

}

template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::node * list < TYPE, ARG_TYPE > ::insert_after(node * position, node * pnode)
{

   list < TYPE, ARG_TYPE > l;

   list < TYPE, ARG_TYPE >::from(l, pnode);

   return insert_before(position, l);

}



template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::node * list < TYPE, ARG_TYPE > ::insert_after(node * position, list < TYPE, ARG_TYPE > & l)
{

   if (l.m_count <= 0)
      return position;

   this->m_count += l.m_count;

   node * pnode = (node *) position;

   if (pnode != nullptr)
   {

      if (pnode->m_pnext != nullptr)
      {

         pnode->m_pnext->m_pprevious = l.m_ptail;

      }

      l.m_ptail->m_pnext = pnode->m_pnext;

      pnode->m_pnext = l.m_phead;

      if (pnode == this->m_ptail)
      {

         this->m_ptail = l.m_ptail;

         this->m_ptail->m_pnext = nullptr;

      }

   }
   else
   {

      l.m_phead->m_pnext = this->m_phead;

      this->m_phead = l.m_ptail;

      if (this->m_ptail == nullptr)
      {

         this->m_ptail = l.m_ptail;

      }

   }

   l.m_phead->m_pprevious = pnode;

   return (node *)l.m_phead;

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::node * list < TYPE, ARG_TYPE > ::insert_after(node * position, iterator first, iterator last)
{

   ::count count = last - first;

   if (count <= 0)
   {

      return position;

   }

   this->m_count += count;

   node * pnode = (node *)position;

   if (pnode != nullptr)
   {

      if (pnode->m_pnext != nullptr)
      {

         pnode->m_pnext->m_pprevious = last.m_pnode;

      }

      last.m_pnode->m_pnext = pnode->m_pnext;

      pnode->m_pnext = first.m_pnode;

      if (pnode == this->m_ptail)
      {

         this->m_ptail = last.m_pnode;

         this->m_ptail->m_pnext = nullptr;

      }

   }
   else
   {

      first.m_pnode->m_pnext = this->m_phead;

      this->m_phead = last.m_pnode;

      if (this->m_ptail == nullptr)
      {

         this->m_ptail = last.m_pnode;

      }

   }

   first.m_pnode->m_pprevious = pnode;

   return (node *)first.m_pnode;

}



template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::node * list<TYPE, ARG_TYPE>::insert_before(node * position, iterator it)
{

   return insert_before(position, (node *)it.m_pnode);

}


template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::__swap(node * position1, node * position2)
{
   ASSERT_VALID(this);

   if (position1 == nullptr)
   {
      if (position2 == nullptr)
      {
         return;
      }
      else
      {
         node * pnode = (node *) position2;
         if (pnode != this->m_phead)
         {
            if (this->m_ptail == pnode)
            {
               this->m_ptail = pnode->m_pprevious;
            }
            if (pnode->m_pprevious != nullptr)
            {
               pnode->m_pprevious->m_pnext = pnode->m_pnext;
            }
            if (pnode->m_pnext != nullptr)
            {
               pnode->m_pnext->m_pprevious = pnode->m_pprevious;
            }
            pnode->m_pprevious = nullptr;
            pnode->m_pnext = this->m_phead;
            this->m_phead = pnode;
         }
      }
   }
   else if (position2 == nullptr)
   {
      node * pnode = (node *) position1;
      if (pnode != this->m_ptail)
      {
         if (this->m_phead == pnode)
         {
            this->m_phead = pnode->m_pnext;
         }
         if (pnode->m_pnext != nullptr)
         {
            pnode->m_pprevious->m_pprevious = pnode->m_pprevious;
         }
         if (pnode->m_pnext != nullptr)
         {
            pnode->m_pprevious->m_pnext = pnode->m_pnext;
         }
         pnode->m_pnext = nullptr;
         pnode->m_pprevious = this->m_ptail;
         this->m_ptail = pnode;
      }
   }
   else
   {
      node * pnode1 = (node *) position1;
      node * pnode2 = (node *) position2;
      node * pnodeSwapPrev = pnode1->m_pprevious;
      node * pnodeSwapNext = pnode1->m_pnext;
      if (pnode1->m_pprevious != nullptr)
      {
         pnode1->m_pprevious->m_pnext = pnode2;
      }
      if (pnode1->m_pnext != nullptr)
      {
         pnode1->m_pnext->m_pprevious = pnode2;
      }
      if (pnode2->m_pprevious != nullptr)
      {
         pnode2->m_pprevious->m_pnext = pnode1;
      }
      if (pnode2->m_pnext != nullptr)
      {
         pnode2->m_pnext->m_pprevious = pnode1;
      }
      pnode1->m_pprevious = pnode2->m_pprevious;
      pnode1->m_pnext = pnode2->m_pnext;
      pnode2->m_pprevious = pnodeSwapPrev;
      pnode2->m_pnext = pnodeSwapNext;
      if (pnode1 == this->m_phead)
      {
         this->m_phead = pnode2;
      }
      if (pnode1 == this->m_ptail)
      {
         this->m_ptail = pnode2;
      }
      if (pnode2 == this->m_phead)
      {
         this->m_phead = pnode1;
      }
      if (pnode2 == this->m_ptail)
      {
         this->m_ptail = pnode1;
      }
   }


}




template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::remove_at(index i)
{

   this->erase(this->index_iterator(i));

}

template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::remove_item(node * pnode)
{

   ASSERT_VALID(this);

   node * pnodeOld = detach(pnode);

   ASSERT(__is_valid_address(pnodeOld, sizeof(node)));

   delete pnodeOld;

}



template < class TYPE, class ARG_TYPE >
typename list < TYPE, ARG_TYPE >::node * list<TYPE, ARG_TYPE>::detach(node * pnode)
{

   ASSERT_VALID(this);

   if (pnode == nullptr)
      return nullptr;

   if (pnode == this->m_phead)
   {
      this->m_phead = pnode->m_pnext;
   }

   if (pnode->m_pprevious != nullptr)
   {
      ASSERT(__is_valid_address(pnode->m_pprevious, sizeof(node)));
      pnode->m_pprevious->m_pnext = pnode->m_pnext;
   }

   if (pnode == this->m_ptail)
   {
      this->m_ptail = pnode->m_pprevious;
   }

   if (pnode->m_pnext != nullptr)
   {
      ASSERT(__is_valid_address(pnode->m_pnext, sizeof(node)));
      pnode->m_pnext->m_pprevious = pnode->m_pprevious;
   }

   pnode->m_pprevious = nullptr;

   pnode->m_pnext = nullptr;

   this->m_count--;

   return pnode;

}


template < class TYPE, class ARG_TYPE >
::count list<TYPE, ARG_TYPE>::detach(iterator first, iterator last)
{

   ASSERT_VALID(this);

   node * pnodeFirst = (node *) first.m_pnode;

   node * pnodeLast = (node *) last.m_pnode;

   if (pnodeLast != nullptr)
   {

      if (pnodeLast == this->m_ptail)
      {
         this->m_ptail = pnodeLast->m_pprevious;
      }
      else
      {
         ASSERT(__is_valid_address(pnodeLast->m_pnext, sizeof(node)));
         pnodeLast->m_pnext->m_pprevious = pnodeLast->m_pprevious;
      }

   }
   else
   {
      this->m_ptail = pnodeFirst->m_pprevious;
   }

   if (pnodeFirst == this->m_phead)
   {
      this->m_phead = pnodeFirst->m_pnext;
   }
   else
   {
      ASSERT(__is_valid_address(pnodeFirst->m_pprevious, sizeof(node)));
      pnodeFirst->m_pprevious->m_pnext = pnodeFirst->m_pnext;
   }

   ::count count = 0;

   node * pnode = pnodeFirst;

   node * pprev = nullptr;

   while (pnode != pnodeLast)
   {
      pprev = pnode;
      pnode = pnode->m_pnext;
      count++;
   }

   return count;

}


//template < class TYPE, class ARG_TYPE >
//typename list < TYPE, ARG_TYPE >::iterator list<TYPE, ARG_TYPE>::splice(iterator position, const_iterator i)
//{

//   return splice(position, *((list *) i.m_pcontainer), i);

//}

//template < class TYPE, class ARG_TYPE >
//typename list < TYPE, ARG_TYPE >::iterator list<TYPE, ARG_TYPE>::splice(const_iterator position, const_iterator first, const_iterator last)
//{

//   return splice(position, *((list *) first.m_pcontainer), first, last);

//}


template < class TYPE, class ARG_TYPE >
void list<TYPE, ARG_TYPE>::splice(iterator position, list & l)
{

   auto first = l.begin();

   auto last = l.end();

   l.detach(first, last);

   insert_before(position, first, last);

}


template < class TYPE, class ARG_TYPE >
void list<TYPE, ARG_TYPE>::splice(iterator position, list & l, iterator i)
{

   UNREFERENCED_PARAMETER(l);

   l.detach(i.item());

   insert_before(position, i);

}

template < class TYPE, class ARG_TYPE >
void list<TYPE, ARG_TYPE>::splice(iterator i, list & l, iterator first, iterator last)
{

   UNREFERENCED_PARAMETER(l);

   l.detach(first.item(), last.item());

   insert_before(i, first, last);

}


template<class TYPE, class ARG_TYPE>
typename list<TYPE, ARG_TYPE>::iterator list<TYPE, ARG_TYPE>::index_iterator(index index)
{

   ASSERT_VALID(this);

   if (index >= this->m_count || index < 0)
   {

      return end();

   }

   auto pnode = this->m_phead;

   while (index > 0)
   {

      ASSERT(__is_valid_address(pnode, sizeof(decltype(*pnode))));

      pnode = pnode->m_pnext;

      index--;

   }

   return iterator((node *) pnode, this);

}


template<class TYPE, class ARG_TYPE>
index list<TYPE, ARG_TYPE>::iterator_index(iterator it)
{

   ASSERT_VALID(this);

   auto pnode = this->m_phead;

   index i = 0;

   while (pnode != nullptr)
   {

      if (it.m_pnode == pnode)
      {

         return i;

      }

      ASSERT(__is_valid_address(pnode, sizeof(decltype(*pnode))));

      pnode = pnode->m_pnext;

      i++;

   }

   return -1;

}


template<class TYPE, class ARG_TYPE>
inline typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE >::reverse_index_iterator(index index)
{

   ASSERT_VALID(this);

   if (index >= m_count || index < 0)
   {

      return end();

   }

   auto * pnode = m_ptail;

   while (index > 0)
   {

      ASSERT(__is_valid_address(pnode, sizeof(decltype(*pnode))));

      pnode = pnode->m_pprevious;

      index--;

   }

   return iterator((node *) pnode, this);

}

/*

template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   elemental::Serialize(ar);

   if (ar.IsStoring())
   {
      ar.WriteCount(this->m_count);
      for (node* pnode = this->m_phead; pnode != nullptr; pnode = pnode->m_pnext)
      {
         ASSERT(__is_valid_address(pnode, sizeof(node)));
         TYPE* pData;
         //
         // in some cases the & operator might be overloaded, and we cannot use it to obtain
         //the address of a given elemental.  We then use the following trick to get the address
         //
         pData = reinterpret_cast< TYPE* >( &reinterpret_cast< i32& >( static_cast< TYPE& >( pnode->m_value ) ) );
         SerializeElements<TYPE>(ar, pData, 1);
      }
   }
   else
   {
      uptr nNewCount = ar.ReadCount();
      while (nNewCount--)
      {
         TYPE newData[1];
         SerializeElements<TYPE>(ar, newData, 1);
         add_tail(newData[0]);
      }
   }
}*/




template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::assert_valid() const
{

   elemental::assert_valid();

   if (this->m_count == 0)
   {
      // is_empty list
      ASSERT(this->m_phead == nullptr);
      ASSERT(this->m_ptail == nullptr);
   }
   else
   {
      // non-is_empty list
      ASSERT(__is_valid_address(this->m_phead, sizeof(node)));
      ASSERT(__is_valid_address(this->m_ptail, sizeof(node)));
   }
}


template<class TYPE, class ARG_TYPE>
list < TYPE, ARG_TYPE > &
list<TYPE, ARG_TYPE>::operator = (const class list & l)
{

   if (&l != this)
   {

      copy(l);

   }

   return *this;

}


#ifdef MOVE_SEMANTICS

template<class TYPE, class ARG_TYPE>
list < TYPE, ARG_TYPE > &
list<TYPE, ARG_TYPE>::operator = (class list && l)
{

   if (&l != this)
   {

      this->m_count = l.m_count;
      this->m_phead = l.m_phead;
      this->m_ptail = l.m_ptail;

   }

   return *this;

}

#endif








