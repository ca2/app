// iterator refactoring and range base class by camilo on 2022-12-09 20:12 <3ThomasBorregaardSorensen!!
#pragma once


#include "list_node.h"


template < class TYPE, class ARG_TYPE >
class list :
   public ::particle,
   virtual public ::range < ::list_iterator < ::list_node < TYPE > * > >
{
public:


   using RANGE = ::range < ::list_iterator < ::list_node < TYPE > * > >;


   using node = ::list_node < TYPE >;


   using ITEM = typename node::ITEM;
   using ARG_ITEM = typename node::ARG_ITEM;


   using iterator = ::list_iterator < ::list_node < TYPE > * >;
   using const_iterator = ::const_list_iterator < ::list_node < TYPE > * >;


   //__declare_iterator_struct_ok(list, iterator, m_pnode, ::is_set(this->m_pnode));


   //template < typename ITERATOR > struct make_iterator : ITERATOR
   //{

   //   using CONTAINER = typename ITERATOR::CONTAINER;

   //   using ITERATOR::ITERATOR;

   //   make_iterator(const iterator iterator = nullptr, const CONTAINER * plist = nullptr)
   //   {

   //      this->m_pnode = (iterator)iterator;
   //      this->m_pcontainer = (CONTAINER *)plist;
   //      this->m_pnodeBeg = (iterator)iterator;
   //      this->m_pnodeEnd = (iterator)nullptr;

   //   }


   //   make_iterator(const iterator_struct & p)
   //   {

   //      this->m_pnode = (iterator) p;
   //      this->m_pcontainer = (CONTAINER *) p.m_pcontainer;
   //      this->m_pnodeBeg = (iterator)p.m_pnodeBeg;
   //      this->m_pnodeEnd = (iterator)p.m_pnodeEnd;

   //   }

   //   make_iterator(const const_iterator_struct & p)
   //   {

   //      this->m_pnode = (iterator)p;
   //      this->m_pcontainer = (CONTAINER *)p.m_pcontainer;
   //      this->m_pnodeBeg = (iterator)p.m_pnodeBeg;
   //      this->m_pnodeEnd = (iterator)p.m_pnodeEnd;

   //   }


   //   make_iterator begin()
   //   {

   //      return make_iterator(this->m_pcontainer->get_start(), this->m_pcontainer);

   //   }


   //   make_iterator end()
   //   {

   //      return make_iterator(nullptr, this->m_pcontainer);

   //   }


   //   make_iterator & operator ++ ()
   //   {

   //      this->m_pnode = this->m_pnode->m_next;

   //      return *this;

   //   }


   //   make_iterator operator ++ (i32)
   //   {

   //      make_iterator iterator = this->m_pnode;

   //      this->m_pnode = this->m_pnode->m_next;

   //      return iterator;

   //   }

   //   make_iterator & operator -- ()
   //   {

   //      this->m_pnode = this->m_pnode->m_back;

   //      return *this;

   //   }


   //   make_iterator operator -- (i32)
   //   {

   //      make_iterator iterator = this->m_pnode;

   //      this->m_pnode = this->m_pnode->m_back;

   //      return iterator;

   //   }

   //   bool operator == (const make_iterator & it) const
   //   {

   //      if (this == &it)
   //      {

   //         return true;

   //      }

   //      if (this->m_pnode == nullptr && it == nullptr && it.m_pcontainer == nullptr)
   //      {

   //         return true;

   //      }

   //      if (this->m_pcontainer != it.m_pcontainer)
   //      {

   //         return false;

   //      }

   //      return this->m_pnode == it;

   //   }


   //   bool operator != (const make_iterator & it) const
   //   {

   //      return !operator == (it);

   //   }


   //   make_iterator & operator = (const make_iterator & it)
   //   {

   //      if (this != &it)
   //      {

   //         this->m_pcontainer = it.m_pcontainer;

   //         this->m_pnode = it;

   //      }

   //      return *this;

   //   }


   //};

   using CONTAINER_ITEM_TYPE = ::list_node <TYPE >;

   //__declare_iterator(dereferenced_value_iterator, this->m_pnode->m_element);
   //__declare_iterator(value_iterator, &this->m_pnode->m_element);
   //__declare_iterator(iterator, &this->m_pnode->m_element);

   //using dereferenced_iterator = dereferenced_value_iterator;


   //iterator         this->m_begin;
   //iterator         this->m_end;
   ::count        m_count;




   list();
   list(const list & l);
   list(class list && l);
   ~list() override;

   //inline list();
   //inline list(const class list < TYPE, ARG_TYPE > & l);
   //inline list(const class list < TYPE, ARG_TYPE > & l);

   inline static void from(list < TYPE, ARG_TYPE > & l, iterator p);
   inline static list < TYPE, ARG_TYPE >  from(iterator p);

   //// helper functions (note: O(n) speed)
   //// defaults to starting at the HEAD, return nullptr if not found
   //iterator index_iterator(index nIndex);
   //// get the 'nIndex'th matter (may return nullptr)
   //index iterator_index(iterator iterator);
   //// get the reverse 'nIndex' of the position (may return -1)
   //iterator reverse_index_iterator(index nIndex);

   //inline auto values() const { return value_iterator(nullptr; }

   //const_iterator index_iterator(index nIndex) const
   //{
   //   return ((list *)this)->index_iterator(nIndex);
   //}

   //const_iterator reverse_index_iterator(index nIndex) const
   //{
   //   return ((list *)this)->reverse_index_iterator(nIndex);
   //}


   //index iterator_index(const_iterator it) const
   //{

   //   return ((list *)this)->iterator_index(it, (list *)this));

   //}


   // getting/modifying an matter at a given position
   TYPE & get_at(iterator iterator) { return iterator->m_element; }
   const TYPE & get_at(iterator iterator) const { return iterator->m_element; }
   void set_at(iterator iterator, ARG_TYPE newElement) { iterator->m_element = newElement; }

   // iteration
   //iterator begin() const;
   //iterator end() const;


   //iterator lower_bound()
   //{
   //   return iterator(nullptr, this);
   //}


   //iterator begin()
   //{
   //   return iterator(begin(), this);
   //}


   //iterator end()
   //{
   //   return iterator(nullptr, this);
   //}


   //iterator upper_bound()
   //{
   //   return iterator(end(), this);
   //}

   //const_iterator lower_bound() const
   //{
   //   return const_iterator(nullptr, this);
   //}


   //const_iterator begin() const
   //{
   //   return const_iterator(begin(), this);
   //}


   //const_iterator end() const
   //{
   //   return const_iterator(nullptr, this);
   //}

   //const_iterator upper_bound() const
   //{
   //   return const_iterator(end(), this);
   //}



   //inline iterator get_start() const { return begin(); }

   bool erase(iterator iterator);

   bool erase_item(ARG_ITEM item);

   iterator detach(iterator iterator);

   template < typename ITERATOR > inline ITERATOR erase(ITERATOR it) { return ::acme::iterator::erase(*this, it); }

   template < typename ITERATOR >
   inline void erase(const ITERATOR & begin, const ITERATOR & last)
   {

      for (auto it = begin; it != last; it++)
      {

         erase(it);

      }

   }

   //   // void assert_ok() const override;
   //   // void dump(dump_context & dumpcontext) const override;



      //void Serialize(CArchive&);
   // Attributes (head and tail)
      // ::count of elements
   ::count get_count() const;
   ::count get_size() const;
   ::count size() const;
   bool is_empty(::count countMinimum = 1) const;
   bool has_elements(::count countMinimum = 1) const;
   bool has_element() const;
   bool empty(::count countMinimum = 1) const;

   // peek at head or tail
   TYPE & head();
   const TYPE & head() const;
   TYPE & tail();
   const TYPE & tail() const;

   // Operations
   // get head or tail (and erase it) - don't call on is_empty list !
   void erase_head();
   void erase_tail();

   TYPE pick_head();
   TYPE pick_tail();

   // add before head or after tail
   iterator add_head(ARG_TYPE newElement);
   iterator add_tail(ARG_TYPE newElement);

   void push_front(ARG_TYPE newElement);
   void push_back(ARG_TYPE newElement);

   // add another list of elements before head or after tail
   void copy_head(const list < TYPE, ARG_TYPE > & l);
   void copy_tail(const list < TYPE, ARG_TYPE > & l);
   void copy(const list < TYPE, ARG_TYPE > & l);

   // erase all elements
   void erase_all();
   void clear();

   TYPE & front();
   const TYPE & front() const;
   TYPE & back();
   const TYPE & back() const;

   TYPE pop_front();

   //TYPE& get_next(iterator& rPosition); // return *position++
   //const TYPE& get_next(iterator& rPosition) const; // return *position++
   //TYPE& get_previous(iterator& rPosition); // return *position--
   //const TYPE& get_previous(iterator& rPosition) const; // return *position--


   void erase_at(index i);





   //iterator detach(iterator position);
   //iterator detach(iterator it);

   ::count detach(iterator first, iterator last);

   iterator insert(iterator position, ARG_TYPE newElement);
   //iterator insert(iterator position, iterator it);
   iterator insert(iterator position, iterator iterator);
   iterator insert(iterator position, list < TYPE, ARG_TYPE > & l);
   iterator insert(iterator position, iterator first, iterator last);

   iterator insert_before(iterator position, ARG_TYPE newElement);
   //iterator insert_before(iterator position, iterator it);
   iterator insert_before(iterator position, iterator iterator);
   iterator insert_before(iterator position, list < TYPE, ARG_TYPE > & l);
   iterator insert_before(iterator position, iterator first, iterator last);

   iterator insert_after(iterator position, ARG_TYPE newElement);
   //iterator insert_after(iterator position, iterator it);
   iterator insert_after(iterator position, iterator iterator);
   iterator insert_after(iterator position, list < TYPE, ARG_TYPE > & l);
   iterator insert_after(iterator position, iterator first, iterator last);

   //iterator insert(iterator position, ARG_TYPE newElement);
   ////iterator insert(iterator position, iterator it);
   //iterator insert(iterator position, iterator iterator);
   //iterator insert(iterator position, list < TYPE, ARG_TYPE > & l);
   //iterator insert(iterator position, iterator first, iterator last);

   //iterator insert_before(iterator position, ARG_TYPE newElement);
   ////iterator insert_before(iterator position, iterator it);
   //iterator insert_before(iterator position, iterator iterator);
   //iterator insert_before(iterator position, list < TYPE, ARG_TYPE > & l);
   //iterator insert_before(iterator position, iterator first, iterator last);

   //iterator insert_after(iterator position, ARG_TYPE newElement);
   ////iterator insert_after(iterator position, iterator it);
   //iterator insert_after(iterator position, iterator iterator);
   //iterator insert_after(iterator position, list < TYPE, ARG_TYPE > & l);
   //iterator insert_after(iterator position, iterator first, iterator last);


   void splice(iterator position, list & l);
   void splice(iterator position, list & l, iterator i);
   void splice(iterator position, list & l, iterator first, iterator last);
   void __swap(iterator position1, iterator position2);


   list < TYPE, ARG_TYPE > & operator = (const class list & l);
#ifdef MOVE_SEMANTICS
   list < TYPE, ARG_TYPE > & operator = (class list && l);
#endif


   template < typename PRED >
   void each(PRED pred)
   {

      auto p = this->begin();

      while (p.is_ok())
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
   this->m_begin = nullptr;
   this->m_end = nullptr;

}


template<class TYPE, class ARG_TYPE>
list<TYPE, ARG_TYPE>::list(const list & l)
{

   this->m_count = 0;
   this->m_begin = nullptr;
   this->m_end = nullptr;

   copy(l);

}


template<class TYPE, class ARG_TYPE>
inline void list < TYPE, ARG_TYPE >::from(list < TYPE, ARG_TYPE > & l, iterator iterator)
{

   l.m_end = nullptr;

   l.m_begin = iterator;

   l.m_count = 0;

   if (iterator == nullptr)
      return;

   while (true)
   {

      if (iterator->m_next == nullptr)
      {

         l.m_end = iterator;

         break;

      }

      iterator++;

      l.m_count++;

   }

   l.m_count++;

}

template<class TYPE, class ARG_TYPE>
inline list < TYPE, ARG_TYPE > list < TYPE, ARG_TYPE >::from(iterator p)
{

   list < TYPE, ARG_TYPE >  l;
   from(l, p);
   return l;

}



template<class TYPE, class ARG_TYPE>
inline ::count list<TYPE, ARG_TYPE>::get_count() const
{

   return this->m_count;

}

template<class TYPE, class ARG_TYPE>
inline bool list<TYPE, ARG_TYPE>::has_element() const
{

   return get_count() > 0;

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
inline TYPE & list<TYPE, ARG_TYPE>::head()
{
   return this->m_begin->m_element;
}
template<class TYPE, class ARG_TYPE>
inline const TYPE & list<TYPE, ARG_TYPE>::head() const
{
   return this->m_begin->m_element;
}
template<class TYPE, class ARG_TYPE>
inline TYPE & list<TYPE, ARG_TYPE>::tail()
{
   return this->m_end->m_element;
}
template<class TYPE, class ARG_TYPE>
inline const TYPE & list<TYPE, ARG_TYPE>::tail() const
{
   return this->m_end->m_element;
}
//template<class TYPE, class ARG_TYPE>
//inline typename list<TYPE, ARG_TYPE>::iterator list<TYPE, ARG_TYPE>::begin() const
//{
//   return this->m_begin;
//}
//template<class TYPE, class ARG_TYPE>
//inline typename list<TYPE, ARG_TYPE>::iterator list<TYPE, ARG_TYPE>::end() const
//{
//   return (iterator) this->m_end;
//}

template<class TYPE, class ARG_TYPE>
inline TYPE & list < TYPE, ARG_TYPE >::front()
{
   return get_at(this->begin());
}


template<class TYPE, class ARG_TYPE>
inline const TYPE & list < TYPE, ARG_TYPE >::front() const
{
   
   return get_at(this->begin());

}


template<class TYPE, class ARG_TYPE>
inline TYPE list < TYPE, ARG_TYPE >::pop_front()
{

   auto p = this->begin();

   TYPE t = *p;

   this->erase(p);

   return t;

}


template<class TYPE, class ARG_TYPE>
inline TYPE & list < TYPE, ARG_TYPE >::back()
{

   return *this->m_end;

}


template<class TYPE, class ARG_TYPE>
inline const TYPE & list < TYPE, ARG_TYPE >::back() const
{

   return *this->m_end;

}


template<class TYPE, class ARG_TYPE>
list<TYPE, ARG_TYPE>::list(class list && l)
{

   this->m_count = l.m_count;
   this->m_begin = l.m_begin;
   this->m_end = l.m_end;

   l.m_begin = nullptr;
   l.m_end = nullptr;

}


template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::erase_all()
{

   iterator pnext;

   for (auto p = this->m_begin; p.is_set(); p = pnext)
   {

      pnext = p + 1;

      try
      {

         delete p.m_p;

      }
      catch (...)
      {

      }

   }

   this->m_begin = nullptr;

   this->m_end = nullptr;

   this->m_count = 0;

}


template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::clear()
{

   erase_all();

}

template<class TYPE, class ARG_TYPE>
list<TYPE, ARG_TYPE>::~list()
{
   erase_all();
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
void list<TYPE, ARG_TYPE>::copy_head(const list < TYPE, ARG_TYPE > & l)
{

   ASSERT_VALID(this);

   auto iterator = l.m_end;

   while (iterator.is_set())
   {

      add_head(iterator->m_element);

      iterator--;

   }

}

template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::copy_tail(const list < TYPE, ARG_TYPE > & l)
{

   ASSERT_VALID(this);

   auto iterator = l.m_end;

   while (iterator.is_null())
   {

      add_tail(iterator->m_element);

      iterator++;

   }

}


template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::copy(const list < TYPE, ARG_TYPE > & l)
{

   ASSERT_VALID(this);

   if (this == &l)
   {

      return;

   }

   erase_all();

   auto p = l.m_end;

   while (p)
   {
      
      add_head(*p);
      
      p++;

   }

}


template<class TYPE, class ARG_TYPE>
TYPE list<TYPE, ARG_TYPE>::pick_head()
{
   ASSERT_VALID(this);
   ASSERT(this->m_begin.is_set());  // don't call on is_empty list !!!

   auto pnodeOld = this->m_begin;
   TYPE returnValue = *pnodeOld;

   this->m_begin = pnodeOld.m_p->m_next;
   if (this->m_begin.is_set())
      this->m_begin.m_p->m_back = nullptr;
   else
      this->m_end = nullptr;
   delete pnodeOld.get();

   this->m_count--;

   return returnValue;

}


template<class TYPE, class ARG_TYPE>
TYPE list<TYPE, ARG_TYPE>::pick_tail()
{
   ASSERT_VALID(this);
   ASSERT(this->m_end.is_set());  // don't call on is_empty list !!!

   auto pnodeOld = this->m_end;
   TYPE returnValue = pnodeOld->m_element;

   this->m_end = pnodeOld->m_back;
   if (this->m_end.is_set())
      this->m_end->m_next = nullptr;
   else
      this->m_begin = nullptr;
   this->m_count--;

   delete pnodeOld.get();

   return returnValue;

}


template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::erase_head()
{
   ASSERT_VALID(this);
   ASSERT(this->m_begin.is_set());  // don't call on is_empty list !!!

   auto pnodeOld = this->m_begin;

   this->m_begin = pnodeOld->m_next;
   if (this->m_begin.is_set())
      this->m_begin->m_back = nullptr;
   else
      this->m_end = nullptr;
   delete pnodeOld.get();

   this->m_count--;

}

template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::erase_tail()
{
   ASSERT_VALID(this);
   ASSERT(this->m_end.is_set());  // don't call on is_empty list !!!

   auto pnodeOld = this->m_end;

   this->m_end = pnodeOld->m_back;
   if (this->m_end.is_set())
      this->m_end->m_next = nullptr;
   else
      this->m_begin = nullptr;
   this->m_count--;
   delete pnodeOld.get();
}



template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_before(iterator position, list < TYPE, ARG_TYPE > & l)
{

   if (l.m_count <= 0)
      return position;

   this->m_count += l.m_count;

   iterator iterator = position;

   if (iterator.is_set())
   {

      if (iterator->m_back.is_set())
      {

         iterator->m_back->m_next = l.m_begin;

      }

      l.m_begin->m_back = iterator->m_back;

      iterator->m_back = l.m_end;

      if (iterator == this->m_begin)
      {

         this->m_begin = l.m_begin;

         this->m_begin->m_back = nullptr;

      }

   }
   else
   {

      l.m_begin->m_back = this->m_end;

      this->m_end = l.m_begin;

      if (this->m_begin == nullptr)
      {

         this->m_begin = l.m_begin;

      }

   }

   l.m_end->m_next = iterator;

   return l.m_begin;

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_before(iterator position, iterator first, iterator last)
{

   ::count count = last - first;

   if (count < 0)
   {

      return nullptr;

   }

   this->m_count += count;

   auto iterator = position;

   if (iterator.is_set())
   {

      if (iterator->m_back.is_set())
      {

         iterator->m_back->m_next = first;

      }

      first->m_back = iterator->m_back;

      iterator->m_back = last;

      if (iterator == this->m_begin)
      {

         this->m_begin = first;

         this->m_begin->m_back = nullptr;

      }

   }
   else
   {

      first->m_back = this->m_end;

      this->m_end = first;

      if (this->m_begin == nullptr)
      {

         this->m_begin = first;

      }

   }

   last->m_next = iterator;

   return first;

}


//template<class TYPE, class ARG_TYPE>
//typename list < TYPE, ARG_TYPE >::iterator list<TYPE, ARG_TYPE>::insert_after(iterator position, iterator it)
//{
//
//   return insert_after(position, it);
//
//}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_after(iterator position, iterator iterator)
{

   list < TYPE, ARG_TYPE > l;

   list < TYPE, ARG_TYPE >::from(l, iterator);

   return insert_before(position, l);

}



template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_after(iterator position, list < TYPE, ARG_TYPE > & l)
{

   if (l.m_count <= 0)
   {

      return position;

   }

   this->m_count += l.m_count;

   iterator iterator = position;

   if (iterator.is_set())
   {

      if (iterator->m_next.is_set())
      {

         iterator->m_next->m_back = l.m_end;

      }

      l.m_end->m_next = iterator->m_next;

      iterator->m_next = l.m_begin;

      if (iterator == this->m_end)
      {

         this->m_end = l.m_end;

         this->m_end->m_next = nullptr;

      }

   }
   else
   {

      l.m_begin->m_next = this->m_begin;

      this->m_begin = l.m_end;

      if (this->m_end == nullptr)
      {

         this->m_end = l.m_end;

      }

   }

   l.m_begin->m_back = iterator;

   return l.m_begin;

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_after(iterator position, iterator first, iterator last)
{

   ::count count = last - first;

   if (count <= 0)
   {

      return position;

   }

   this->m_count += count;

   auto iterator = position;

   if (iterator.is_set())
   {

      if (iterator->m_next.is_set())
      {

         iterator->m_next->m_back = last;

      }

      last->m_next = iterator->m_next;

      iterator->m_next = first;

      if (iterator == this->m_end)
      {

         this->m_end = last;

         this->m_end->m_next = nullptr;

      }

   }
   else
   {

      first->m_next = this->m_begin;

      this->m_begin = last;

      if (this->m_end == nullptr)
      {

         this->m_end = last;

      }

   }

   first->m_back = iterator;

   return first;

}



//template<class TYPE, class ARG_TYPE>
//typename list < TYPE, ARG_TYPE >::iterator list<TYPE, ARG_TYPE>::insert_before(iterator position, iterator it)
//{
//
//   return insert_before(position, it);
//
//}


template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::__swap(iterator position1, iterator position2)
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
         iterator iterator = position2;
         if (iterator != this->m_begin)
         {
            if (this->m_end == iterator)
            {
               this->m_end = iterator->m_back;
            }
            if (iterator->m_back.is_set())
            {
               iterator->m_back->m_next = iterator->m_next;
            }
            if (iterator->m_next.is_set())
            {
               iterator->m_next->m_back = iterator->m_back;
            }
            iterator->m_back = nullptr;
            iterator->m_next = this->m_begin;
            this->m_begin = iterator;
         }
      }
   }
   else if (position2 == nullptr)
   {
      iterator iterator = position1;
      if (iterator != this->m_end)
      {
         if (this->m_begin == iterator)
         {
            this->m_begin = iterator->m_next;
         }
         if (iterator->m_next.is_set())
         {
            iterator->m_back->m_back = iterator->m_back;
         }
         if (iterator->m_next.is_set())
         {
            iterator->m_back->m_next = iterator->m_next;
         }
         iterator->m_next = nullptr;
         iterator->m_back = this->m_end;
         this->m_end = iterator;
      }
   }
   else
   {
      iterator pnode1 = (iterator)position1;
      iterator pnode2 = (iterator)position2;
      iterator pnodeSwapPrev = pnode1->m_back;
      iterator pnodeSwapNext = pnode1->m_next;
      if (pnode1->m_back.is_set())
      {
         pnode1->m_back->m_next = pnode2;
      }
      if (pnode1->m_next.is_set())
      {
         pnode1->m_next->m_back = pnode2;
      }
      if (pnode2->m_back.is_set())
      {
         pnode2->m_back->m_next = pnode1;
      }
      if (pnode2->m_next.is_set())
      {
         pnode2->m_next->m_back = pnode1;
      }
      pnode1->m_back = pnode2->m_back;
      pnode1->m_next = pnode2->m_next;
      pnode2->m_back = pnodeSwapPrev;
      pnode2->m_next = pnodeSwapNext;
      if (pnode1 == this->m_begin)
      {
         this->m_begin = pnode2;
      }
      if (pnode1 == this->m_end)
      {
         this->m_end = pnode2;
      }
      if (pnode2 == this->m_begin)
      {
         this->m_begin = pnode1;
      }
      if (pnode2 == this->m_end)
      {
         this->m_end = pnode1;
      }
   }


}


template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::erase_at(index i)
{

   this->erase(this->begin() + i);

}


//template<class TYPE, class ARG_TYPE>
//bool list<TYPE, ARG_TYPE>::erase_item(ARG_ITEM item)
//{
//
//   auto p = find_item(item);
//
//   if(!p)
//   {
//
//      return false;
//
//   }
//
//   erase(p);
//
//   return true;
//
//}


template<class TYPE, class ARG_TYPE>
bool list<TYPE, ARG_TYPE>::erase(iterator pErase)
{

   ASSERT_VALID(this);

   auto p = detach(pErase);

   if(!p)
   {

      return false;

   }

   delete p.get();

   return true;

}


template < class TYPE, class ARG_TYPE >
typename list < TYPE, ARG_TYPE >::iterator list<TYPE, ARG_TYPE>::detach(iterator iterator)
{

   ASSERT_VALID(this);

   if (iterator == nullptr)
      return nullptr;

   if (iterator == this->m_begin)
   {
      this->m_begin = iterator.m_p->m_next;
   }

   if (iterator.m_p->m_back.is_set())
   {
      iterator.m_p->m_back.m_p->m_next = iterator.m_p->m_next;
   }

   if (iterator == this->m_end)
   {
      this->m_end = iterator.m_p->m_back;
   }

   if (iterator.m_p->m_next.is_set())
   {
      iterator.m_p->m_next.m_p->m_back = iterator.m_p->m_back;
   }

   iterator.m_p->m_back = nullptr;

   iterator.m_p->m_next = nullptr;

   this->m_count--;

   return iterator;

}


template < class TYPE, class ARG_TYPE >
::count list<TYPE, ARG_TYPE>::detach(iterator first, iterator last)
{

   ASSERT_VALID(this);

   iterator pnodeFirst = first;

   iterator pnodeLast = (iterator)last;

   if (pnodeLast.is_set())
   {

      if (pnodeLast == this->m_end)
      {
         this->m_end = pnodeLast->m_back;
      }
      else
      {
         pnodeLast->m_next->m_back = pnodeLast->m_back;
      }

   }
   else
   {
      this->m_end = pnodeFirst->m_back;
   }

   if (pnodeFirst == this->m_begin)
   {
      this->m_begin = pnodeFirst->m_next;
   }
   else
   {
      pnodeFirst->m_back->m_next = pnodeFirst->m_next;
   }

   ::count count = 0;

   iterator back;

   iterator iterator = pnodeFirst;

   while (iterator != pnodeLast)
   {

      back = iterator;

      iterator++;

      count++;

   }

   return count;

}


//template < class TYPE, class ARG_TYPE >
//typename list < TYPE, ARG_TYPE >::iterator list<TYPE, ARG_TYPE>::splice(iterator position, const_iterator i)
//{
//
//   return splice(position, *((list *) i.m_pcontainer), i);
//
//}

//template < class TYPE, class ARG_TYPE >
//typename list < TYPE, ARG_TYPE >::iterator list<TYPE, ARG_TYPE>::splice(const_iterator position, const_iterator first, const_iterator last)
//{
//
//   return splice(position, *((list *) first.m_pcontainer), first, last);
//
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

   l.detach(i);

   insert_before(position, i);

}

template < class TYPE, class ARG_TYPE >
void list<TYPE, ARG_TYPE>::splice(iterator i, list & l, iterator first, iterator last)
{

   l.detach(first, last);

   insert_before(i, first, last);

}


//template<class TYPE, class ARG_TYPE>
//typename list<TYPE, ARG_TYPE>::iterator list<TYPE, ARG_TYPE>::index_iterator(index index)
//{
//
//   //ASSERT_VALID(this);
//
//   if (index >= this->m_count || index < 0)
//   {
//
//      return nullptr;
//
//   }
//
//   auto iterator = this->m_begin;
//
//   while (index > 0)
//   {
//
//      iterator = iterator->m_next;
//
//      index--;
//
//   }
//
//   return iterator;
//
//}
//
//
//template<class TYPE, class ARG_TYPE>
//index list<TYPE, ARG_TYPE>::iterator_index(iterator it)
//{
//
//   ASSERT_VALID(this);
//
//   auto iterator = this->m_begin;
//
//   index i = 0;
//
//   while (iterator.is_set)
//   {
//
//      if (it == iterator)
//      {
//
//         return i;
//
//      }
//
//      iterator = iterator->m_next;
//
//      i++;
//
//   }
//
//   return -1;
//
//}
//
//
//template<class TYPE, class ARG_TYPE>
//inline typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE >::reverse_index_iterator(index index)
//{
//
//   //ASSERT_VALID(this);
//
//   if (index >= m_count || index < 0)
//   {
//
//      return nullptr();
//
//   }
//
//   auto iterator = this->m_end;
//
//   while (index > 0)
//   {
//
//      iterator = iterator->m_back;
//
//      index--;
//
//   }
//
//   return iterator;
//
//}
//
//
//template<class TYPE, class ARG_TYPE>
//void list<TYPE, ARG_TYPE>::assert_ok() const
//{
//
//   matter::assert_ok();
//
//   if (this->m_count == 0)
//   {
//
//      // is_empty list
//
//      ASSERT(this->m_begin == nullptr);
//      ASSERT(this->m_end == nullptr);
//
//   }
//   else
//   {
//
//      // non-is_empty list
//      ASSERT(::is_set(this->m_begin));
//      ASSERT(::is_set(this->m_end));
//
//   }
//
//}


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
      this->m_begin = l.m_begin;
      this->m_end = l.m_end;

   }

   return *this;

}

#endif










#pragma once


template<class TYPE, class ARG_TYPE>
typename list<TYPE, ARG_TYPE>::iterator list<TYPE, ARG_TYPE>::add_head(ARG_TYPE newElement)
{

   ASSERT_VALID(this);

   typename list < TYPE, ARG_TYPE >::iterator pnodeNew;

   pnodeNew.m_p = memory_new typename list < TYPE, ARG_TYPE >::node(newElement);

   pnodeNew.m_p->m_back = nullptr;

   pnodeNew.m_p->m_next = this->m_begin;

   if (this->m_begin.is_set())
      this->m_begin.m_p->m_back = pnodeNew;
   else
      this->m_end = pnodeNew;

   this->m_begin = pnodeNew;

   this->m_count++;

   return pnodeNew;

}


template<class TYPE, class ARG_TYPE>
typename list<TYPE, ARG_TYPE>::iterator list<TYPE, ARG_TYPE>::add_tail(ARG_TYPE newElement)
{

   ASSERT_VALID(this);

   auto pnodeNew = memory_new typename list < TYPE, ARG_TYPE >::node(newElement);

   pnodeNew->m_back = this->m_end;

   pnodeNew->m_next = nullptr;

   //pnodeNew->m_element = newElement;

   if (this->m_end.is_set())
      this->m_end.m_p->m_next = pnodeNew;
   else
      this->m_begin = pnodeNew;

   this->m_end = pnodeNew;

   this->m_count++;

   return pnodeNew;

}


template<class TYPE, class ARG_TYPE>
typename list<TYPE, ARG_TYPE>::iterator list<TYPE, ARG_TYPE>::insert_before(typename list<TYPE, ARG_TYPE>::iterator position, ARG_TYPE newElement)
{
   ASSERT_VALID(this);

   if (position == nullptr)
      return add_head(newElement); // insert before nothing -> head of the list

   // Insert it before position
   auto pOldNode = position;
   auto pnodeNew = memory_new typename list < TYPE, ARG_TYPE >::node(newElement);
   pnodeNew->m_back = pOldNode.m_p->m_back;
   pnodeNew->m_next = pOldNode;
   //pnodeNew->m_element = newElement;

   if (pOldNode.m_p->m_back.is_set())
   {
//      ASSERT(__is_valid_address(pOldNode->m_back, sizeof(typename list < TYPE, ARG_TYPE >::node)));
      pOldNode.m_p->m_back.m_p->m_next = pnodeNew;
   }
   else
   {
      ASSERT(pOldNode == this->m_begin);
      this->m_begin = pnodeNew;
   }
   pOldNode.m_p->m_back = pnodeNew;
   return pnodeNew;

}


template<class TYPE, class ARG_TYPE>
typename list<TYPE, ARG_TYPE>::iterator list<TYPE, ARG_TYPE>::insert_after(typename list<TYPE, ARG_TYPE>::iterator position, ARG_TYPE newElement)
{
   ASSERT_VALID(this);

   if (position == nullptr)
      return add_tail(newElement); // insert after nothing -> tail of the list

   // Insert it before position
   auto pOldNode = position;
   ASSERT(__is_valid_address(pOldNode.get(), sizeof(typename list < TYPE, ARG_TYPE >::node)));
   auto pnodeNew = memory_new typename list < TYPE, ARG_TYPE >::node(newElement);
   pnodeNew->m_back = pOldNode;
   pnodeNew->m_next = pOldNode->m_next;
   pnodeNew->m_element = newElement;

   if (pOldNode->m_next.is_set())
   {
      ASSERT(__is_valid_address(pOldNode->m_next.get(), sizeof(typename list < TYPE, ARG_TYPE >::node)));
      pOldNode->m_next->m_back = pnodeNew;
   }
   else
   {
      ASSERT(pOldNode == this->m_end);
      this->m_end = pnodeNew;
   }
   pOldNode->m_next = pnodeNew;
   return pnodeNew;
}







template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert(iterator i, ARG_TYPE newElement) // same as insert before
{

   

   return insert_before(i, newElement);

}

//
//template<class TYPE, class ARG_TYPE>
//typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert(iterator i, iterator it) // same as insert before
//{
//
//   
//
//   return insert_before(i, it);
//
//}
//
//
////template<class TYPE, class ARG_TYPE>
////typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert(iterator i, iterator iterator)
////{
////
////   
////
////   return insert_before(i, iterator);
////
////}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert(iterator i, list < TYPE, ARG_TYPE > & l)
{

   

   return insert_before(i, l);

}


//template<class TYPE, class ARG_TYPE>
//typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert(iterator i, iterator first, iterator last)
//{
//
//   
//
//   
//
//   return insert_before(i, first, last);
//
//}
//
//
//template<class TYPE, class ARG_TYPE>
//typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_before(iterator i, ARG_TYPE newElement)
//{
//
//   ASSERT(this == i.container());
//
//   return iterator(insert_before(i.item(), newElement), this);
//
//}
//
//
//template<class TYPE, class ARG_TYPE>
//typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_before(iterator i, iterator it)
//{
//
//   
//
//   return insert_before(i, it);
//
//}




//template<class TYPE, class ARG_TYPE>
//typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_before(iterator i, iterator iterator)
//{
//
//   
//
//   return insert_before(i, iterator);
//
//}

//
//template<class TYPE, class ARG_TYPE>
//typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_before(iterator i, list < TYPE, ARG_TYPE > & l)
//{
//
//   return insert_before(i, l);
//
//}


//template<class TYPE, class ARG_TYPE>
//typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_before(iterator i, iterator first, iterator last)
//{
//
//   
//   return insert_before(i, first, last);
//
//}


//template<class TYPE, class ARG_TYPE>
//typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_after(iterator i, ARG_TYPE newElement)
//{
//
//   
//
//   return insert_after(i, newElement);
//
//}


//template<class TYPE, class ARG_TYPE>
//typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_after(iterator i, iterator it)
//{
//
//   
//
//   return insert_after(i, it);
//
//}


//template<class TYPE, class ARG_TYPE>
//typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_after(iterator i, iterator iterator)
//{
//
//   
//
//   return insert_after(i, iterator);
//
//}


//template<class TYPE, class ARG_TYPE>
//typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_after(iterator i, list < TYPE, ARG_TYPE > & l)
//{
//
//   
//
//   return insert_after(i, l);
//
//}


//template<class TYPE, class ARG_TYPE>
//typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_after(iterator i, iterator first, iterator last)
//{
//
//   
//
//   
//
//   return insert_after(i, first, last);
//
//}


//template<class TYPE, class ARG_TYPE>
//typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert(iterator position, ARG_TYPE newElement)
//{
//
//   return insert_before(position, newElement);
//
//}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert(iterator position, iterator it)
{

   return insert_before(position, it);

}


//template<class TYPE, class ARG_TYPE>
//typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert(iterator position, iterator iterator) // same as insert before
//{
//
//   return insert_before(position, iterator);
//
//}



//template<class TYPE, class ARG_TYPE>
//typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert(iterator position, list < TYPE, ARG_TYPE > & l) // same as insert before
//{
//
//   return insert_before(position, l);
//
//}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert(iterator position, iterator first, iterator last) // same as insert before
{

   return insert_before(position, first, last);

}



template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_before(iterator position, iterator iterator)
{

   list < TYPE, ARG_TYPE > l;

   list < TYPE, ARG_TYPE >::from(l, iterator);

   return insert_before(position, l);

}







//string_list::iterator string_list::find(const string & searchValue, iterator startAfter) const
//{
//
//   if (::is_set(startAfter))
//   {
//
//      return ::find_payload(*this, searchValue, iterator(startAfter, this));
//
//   }
//   else
//   {
//
//      return ::find_payload(*this, searchValue);
//
//   }
//
//}


//template<class TYPE, class ARG_TYPE>
//void list<TYPE, ARG_TYPE>::dump(dump_context& dumpcontext) const
//{
//
//   matter::dump(dumpcontext);
//
//   //dumpcontext << "with " << this->m_count << " elements";
//
//   //if (dumpcontext.GetDepth() > 0)
//   //{
//
//   //   auto iterator = this->begin();
//
//   //   while (::is_set(iterator))
//   //   {
//
//   //      dumpcontext << "\n";
//
//   //      dump_elements(dumpcontext, &iterator->m_element, 1);
//
//   //      iterator = iterator->m_next;
//
//   //   }
//
//   //}
//
//   //dumpcontext << "\n";
//
//}


//template < typename TYPE >
//inline stream& operator <<(stream& stream, const string_list& list)
//{
//
//   stream << list.get_count();
//
//   for (auto& pitem : list)
//   {
//      stream << *pitem;
//   }
//
//   return stream;
//
//}
//
//
//template < typename TYPE >
//inline stream& operator >>(stream& stream, string_list& list)
//{
//
//   i32 iSize;
//   stream >> iSize;
//   string str;
//   for (i32 i = 0; i < iSize; i++)
//   {
//      stream >> str;
//      list.add_tail(str);
//   }
//   return stream;
//}
//



