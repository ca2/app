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

   //      this->m_pnode = this->m_pnode.next();

   //      return *this;

   //   }


   //   make_iterator operator ++ (i32)
   //   {

   //      make_iterator iterator = this->m_pnode;

   //      this->m_pnode = this->m_pnode.next();

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


   //iterator         this->begin();
   //iterator         this->end();
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
   TYPE & get_at(iterator p) { return *p; }
   const TYPE & get_at(iterator p) const { return *p; }
   void set_at(iterator p, ARG_TYPE newElement) { *p = newElement; }

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

   //bool erase_item(ARG_ITEM item);

   iterator detach(iterator iterator);

   /*inline iterator erase(iterator it) 
   {

      auto pnext = p;

      if (p)
      {

         pnext++;

         this->erase(p);

      }

      return pnext;

   }*/

   template < typename ITERATOR >
   inline void erase(const ITERATOR & begin, const ITERATOR & end)
   {

      for (auto it = begin; it != end; it++)
      {

         erase(it);

      }

   }

   //   // void assert_ok() const override;
   //   // void dump(dump_context & dumpcontext) const override;



      //void Serialize(CArchive&);
    //(head and tail)
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

   ::count detach(iterator p, iterator end);

   iterator insert(iterator position, ARG_TYPE newElement);
   //iterator insert(iterator position, iterator it);
   iterator insert(iterator position, iterator iterator);
   iterator insert(iterator position, list < TYPE, ARG_TYPE > & l);
   iterator insert(iterator position, iterator p, iterator end);

   iterator insert_before(iterator position, ARG_TYPE newElement);
   //iterator insert_before(iterator position, iterator it);
   iterator insert_before(iterator position, iterator iterator);
   iterator insert_before(iterator position, list < TYPE, ARG_TYPE > & l);
   iterator insert_before(iterator position, iterator p, iterator end);

   iterator insert_after(iterator position, ARG_TYPE newElement);
   //iterator insert_after(iterator position, iterator it);
   iterator insert_after(iterator position, iterator iterator);
   iterator insert_after(iterator position, list < TYPE, ARG_TYPE > & l);
   iterator insert_after(iterator position, iterator p, iterator end);

   //iterator insert(iterator position, ARG_TYPE newElement);
   ////iterator insert(iterator position, iterator it);
   //iterator insert(iterator position, iterator iterator);
   //iterator insert(iterator position, list < TYPE, ARG_TYPE > & l);
   //iterator insert(iterator position, iterator p, iterator end);

   //iterator insert_before(iterator position, ARG_TYPE newElement);
   ////iterator insert_before(iterator position, iterator it);
   //iterator insert_before(iterator position, iterator iterator);
   //iterator insert_before(iterator position, list < TYPE, ARG_TYPE > & l);
   //iterator insert_before(iterator position, iterator p, iterator end);

   //iterator insert_after(iterator position, ARG_TYPE newElement);
   ////iterator insert_after(iterator position, iterator it);
   //iterator insert_after(iterator position, iterator iterator);
   //iterator insert_after(iterator position, list < TYPE, ARG_TYPE > & l);
   //iterator insert_after(iterator position, iterator p, iterator end);


   void splice(iterator position, list & l);
   void splice(iterator position, list & l, iterator i);
   void splice(iterator position, list & l, iterator p, iterator end);
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
   this->begin() = nullptr;
   this->end() = nullptr;

}


template<class TYPE, class ARG_TYPE>
list<TYPE, ARG_TYPE>::list(const list & l)
{

   this->m_count = 0;
   this->begin() = nullptr;
   this->end() = nullptr;

   copy(l);

}


template<class TYPE, class ARG_TYPE>
inline void list < TYPE, ARG_TYPE >::from(list < TYPE, ARG_TYPE > & l, iterator p)
{

   l.end() = nullptr;

   l.begin() = p;

   l.m_count = 0;

   if (!p)
   {

      return;

   }

   while (true)
   {

      if (!p.next())
      {

         l.end() = p;

         break;

      }

      p++;

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
   return this->begin().topic();
}
template<class TYPE, class ARG_TYPE>
inline const TYPE & list<TYPE, ARG_TYPE>::head() const
{
   return this->begin().topic();
}
template<class TYPE, class ARG_TYPE>
inline TYPE & list<TYPE, ARG_TYPE>::tail()
{
   return this->end().topic();
}
template<class TYPE, class ARG_TYPE>
inline const TYPE & list<TYPE, ARG_TYPE>::tail() const
{
   return this->end().topic();
}
//template<class TYPE, class ARG_TYPE>
//inline typename list<TYPE, ARG_TYPE>::iterator list<TYPE, ARG_TYPE>::begin() const
//{
//   return this->begin();
//}
//template<class TYPE, class ARG_TYPE>
//inline typename list<TYPE, ARG_TYPE>::iterator list<TYPE, ARG_TYPE>::end() const
//{
//   return (iterator) this->end();
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

   return *this->end();

}


template<class TYPE, class ARG_TYPE>
inline const TYPE & list < TYPE, ARG_TYPE >::back() const
{

   return *this->end();

}


template<class TYPE, class ARG_TYPE>
list<TYPE, ARG_TYPE>::list(class list && l)
{

   this->m_count = l.m_count;
   this->begin() = l.begin();
   this->end() = l.end();

   l.begin() = nullptr;
   l.end() = nullptr;

}


template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::erase_all()
{

   iterator pnext;

   for (auto p = this->begin(); p.is_set(); p = pnext)
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

   this->begin() = nullptr;

   this->end() = nullptr;

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

   auto p = l.end();

   while (p)
   {

      add_head(p.topic());

      p--;

   }

}

template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::copy_tail(const list < TYPE, ARG_TYPE > & l)
{

   ASSERT_VALID(this);

   auto p = l.end();

   while (p)
   {

      add_tail(*p);

      p++;

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

   auto p = l.end();

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
   ASSERT(this->begin().is_set());  // don't call on is_empty list !!!

   auto old = this->begin();
   
   auto returnValue = *old;

   this->begin() = old.next();
   
   if (this->begin())
   {

      this->begin().back() = nullptr;

   }
   else
   {

      this->end() = nullptr;

   }

   delete old.get();

   this->m_count--;

   return returnValue;

}


template<class TYPE, class ARG_TYPE>
TYPE list<TYPE, ARG_TYPE>::pick_tail()
{
   ASSERT_VALID(this);
   ASSERT(this->end().is_set());  // don't call on is_empty list !!!

   auto old = this->end();

   auto returnValue = old.topic();

   this->end() = old.back();

   if (this->end())
   {

      this->end().next() = nullptr;

   }
   else
   {

      this->begin() = nullptr;

   }

   this->m_count--;

   delete old.get();

   return returnValue;

}


template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::erase_head()
{

   ASSERT_VALID(this);
   ASSERT(this->begin().is_set());  // don't call on is_empty list !!!

   auto pOld = this->begin();

   this->begin() = pOld.next();

   if (this->begin())
   {

      this->begin().back() = nullptr;

   }
   else
   {

      this->end() = nullptr;

   }

   delete pOld.get();

   this->m_count--;

}

template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::erase_tail()
{
   ASSERT_VALID(this);
   ASSERT(this->end().is_set());  // don't call on is_empty list !!!

   auto old = this->end();

   this->end() = old.back();

   if (!this->end())
   {

      this->end().next() = nullptr;
   }
      
   else
   {

      this->begin() = nullptr;

   }

   this->m_count--;

   delete old.get();

}



template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_before(iterator position, list < TYPE, ARG_TYPE > & l)
{

   if (l.m_count <= 0)
      return position;

   this->m_count += l.m_count;

   if (position)
   {

      if (position.back())
      {

         position.back().next() = l.begin();

      }

      l.begin().back() = position.back();

      position.back() = l.end();

      if (position == this->begin())
      {

         this->begin() = l.begin();

         this->begin().back() = nullptr;

      }

   }
   else
   {

      l.begin().back() = this->end();

      this->end() = l.begin();

      if (!this->begin())
      {

         this->begin() = l.begin();

      }

   }

   l.end().next() = position;

   return l.begin();

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_before(iterator position, iterator p, iterator end)
{

   ::count count = end - p;

   if (count < 0)
   {

      return nullptr;

   }

   this->m_count += count;

   if (position.is_set())
   {

      if (position.back())
      {

         position.back().next() = p;

      }

      p.back() = position.back();

      position.back() = end;

      if (position == this->begin())
      {

         this->begin() = p;

         this->begin().back() = nullptr;

      }

   }
   else
   {

      p.back() = this->end();

      this->end() = p;

      if (!this->begin())
      {

         this->begin() = p;

      }

   }

   end.next() = position;

   return p;

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

   if (position.is_set())
   {

      if (position.next())
      {

         position.next().back() = l.end();

      }

      l.end().next() = position.next();

      position.next() = l.begin();

      if (position == this->end())
      {

         this->end() = l.end();

         this->end().next() = nullptr;

      }

   }
   else
   {

      l.begin().next() = this->begin();

      this->begin() = l.end();

      if (this->end() == nullptr)
      {

         this->end() = l.end();

      }

   }

   l.begin().back() = position;

   return l.begin();

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_after(iterator position, iterator p, iterator end)
{

   ::count count = end - p;

   if (count <= 0)
   {

      return position;

   }

   this->m_count += count;

   if (position)
   {

      if (position.next())
      {

         position.next().back() = end;

      }

      end.next() = position.next();

      position.next() = p;

      if (position == this->end())
      {

         this->end() = end;

         this->end().next() = nullptr;

      }

   }
   else
   {

      p.next() = this->begin();

      this->begin() = end;

      if (this->end() == nullptr)
      {

         this->end() = end;

      }

   }

   p.back() = position;

   return p;

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
         
         if (position2 != this->begin())
         {
            if (this->end() == position2)
            {
               this->end() = position2.back();
            }
            if (position2.back())
            {
               position2.back().next() = position2.next();
            }
            if (position2.next())
            {
               position2.next().back() = position2.back();
            }
            position2.back() = nullptr;
            position2.next() = this->begin();
            this->begin() = position2;
         }
      }
   }
   else if (position2 == nullptr)
   {
      if (position1 != this->end())
      {
         if (this->begin() == position1)
         {
            this->begin() = position1.next();
         }
         if (position1.back())
         {
            position1.back().next() = position1.next();
         }
         if (position1.next())
         {
            position1.next().back() = position1.next();
         }
         position1.next() = nullptr;
         position1.back() = this->end();

         this->end() = position1;

      }

   }
   else
   {
      
      iterator position1Back = position1.back();
      
      iterator position1Next = position1.next();

      if (position1.back())
      {
         position1.back().next() = position2;
      }
      if (position1.next())
      {
         position1.next().back() = position2;
      }
      if (position2.back())
      {
         position2.back().next() = position1;
      }
      if (position2.next())
      {
         position2.next().back() = position1;
      }
      position1.back() = position2.back();
      position1.next() = position2.next();
      position2.back() = position1Back;
      position2.next() = position1Next;
      if (position1 == this->begin())
      {
         this->begin() = position2;
      }
      if (position1 == this->end())
      {
         this->end() = position2;
      }
      if (position2 == this->begin())
      {
         this->begin() = position1;
      }
      if (position2 == this->end())
      {
         this->end() = position1;
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
typename list < TYPE, ARG_TYPE >::iterator list<TYPE, ARG_TYPE>::detach(iterator p)
{

   ASSERT_VALID(this);

   if (!p)
   {

      return nullptr;

   }

   if (p == this->begin())
   {

      this->begin() = p.next();

   }

   if (p.back())
   {
      
      p.back().next() = p.next();

   }

   if (p == this->end())
   {
      this->end() = p.back();
   }

   if (p.next())
   {
      p.next().back() = p.back();
   }

   p.back() = nullptr;

   p.next() = nullptr;

   this->m_count--;

   return p;

}


template < class TYPE, class ARG_TYPE >
::count list<TYPE, ARG_TYPE>::detach(iterator p, iterator end)
{

   ASSERT_VALID(this);

   if (end)
   {

      if (end == this->end())
      {
         
         this->end() = end.back();

      }
      else
      {

         end.next().back() = end.back();

      }

   }
   else
   {

      this->end() = p.back();

   }

   if (p == this->begin())
   {

      this->begin() = p.next();

   }
   else
   {
      
      p.back().next() = p.next();

   }

   ::count count = 0;

   while (p != end)
   {

      //back = iterator;

      p++;

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
//typename list < TYPE, ARG_TYPE >::iterator list<TYPE, ARG_TYPE>::splice(const_iterator position, const_iterator p, const_iterator end)
//{
//
//   return splice(position, *((list *) p.m_pcontainer), p, end);
//
//}


template < class TYPE, class ARG_TYPE >
void list<TYPE, ARG_TYPE>::splice(iterator position, list & l)
{

   auto p = l.begin();

   auto end = l.end();

   l.detach(p, end);

   insert_before(position, p, end);

}


template < class TYPE, class ARG_TYPE >
void list<TYPE, ARG_TYPE>::splice(iterator position, list & l, iterator i)
{

   l.detach(i);

   insert_before(position, i);

}

template < class TYPE, class ARG_TYPE >
void list<TYPE, ARG_TYPE>::splice(iterator i, list & l, iterator p, iterator end)
{

   l.detach(p, end);

   insert_before(i, p, end);

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
//   auto iterator = this->begin();
//
//   while (index > 0)
//   {
//
//      iterator = iterator.next();
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
//   auto iterator = this->begin();
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
//      iterator = iterator.next();
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
//   auto iterator = this->end();
//
//   while (index > 0)
//   {
//
//      iterator = position1.back();
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
//      ASSERT(this->begin() == nullptr);
//      ASSERT(this->end() == nullptr);
//
//   }
//   else
//   {
//
//      // non-is_empty list
//      ASSERT(::is_set(this->begin()));
//      ASSERT(::is_set(this->end()));
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
      this->begin() = l.begin();
      this->end() = l.end();

   }

   return *this;

}

#endif










#pragma once


template<class TYPE, class ARG_TYPE>
typename list<TYPE, ARG_TYPE>::iterator list<TYPE, ARG_TYPE>::add_head(ARG_TYPE newElement)
{

   ASSERT_VALID(this);

   typename list < TYPE, ARG_TYPE >::iterator p;

   p = memory_new typename list < TYPE, ARG_TYPE >::node(newElement);

   p.back() = nullptr;

   p.next() = this->begin();

   if (this->begin())
   {

      this->begin().back() = p;

   }
   else
   {

      this->end() = p;

   }

   this->begin() = p;

   this->m_count++;

   return p;

}


template<class TYPE, class ARG_TYPE>
typename list<TYPE, ARG_TYPE>::iterator list<TYPE, ARG_TYPE>::add_tail(ARG_TYPE newElement)
{

   ASSERT_VALID(this);

   typename list < TYPE, ARG_TYPE >::iterator p;

   p = memory_new typename list < TYPE, ARG_TYPE >::node(newElement);

   p.back() = this->end();

   p.next() = nullptr;

   //pnodeNew->m_element = newElement;

   if (this->end())
      this->end().next() = p;
   else
      this->begin() = p;

   this->end() = p;

   this->m_count++;

   return p;

}


template<class TYPE, class ARG_TYPE>
typename list<TYPE, ARG_TYPE>::iterator list<TYPE, ARG_TYPE>::insert_before(iterator position, ARG_TYPE newElement)
{
   ASSERT_VALID(this);

   if (position == nullptr)
      return add_head(newElement); // insert before nothing -> head of the list

   // Insert it before position
   auto old = position;
   iterator p;
   p = memory_new typename list < TYPE, ARG_TYPE >::node(newElement);
   p.back() = old.back();
   p.next() = old;
   p.topic() = newElement;

   if (old.back())
   {
//      ASSERT(__is_valid_address(pOldNode->m_back, sizeof(typename list < TYPE, ARG_TYPE >::node)));
      old.back().next() = p;
   }
   else
   {
      ASSERT(old == this->begin());
      this->begin() = p;
   }
   
   old.back() = p;

   return p;

}


template<class TYPE, class ARG_TYPE>
typename list<TYPE, ARG_TYPE>::iterator list<TYPE, ARG_TYPE>::insert_after(iterator position, ARG_TYPE newElement)
{
   ASSERT_VALID(this);

   if (position == nullptr)
      return add_tail(newElement); // insert after nothing -> tail of the list

   // Insert it before position
   auto old = position;
   ASSERT(__is_valid_address(old.get(), sizeof(typename list < TYPE, ARG_TYPE >::node)));
   iterator p;
   p = memory_new typename list < TYPE, ARG_TYPE >::node(newElement);
   p.back() = old;
   p.next() = old.next();
   p.topic() = newElement;

   if (old.next())
   {
      ASSERT(__is_valid_address(old.next().get(), sizeof(typename list < TYPE, ARG_TYPE >::node)));
      old.next().back() = p;
   }
   else
   {
      ASSERT(old == this->end());
      this->end() = p;
   }

   old.next() = p;

   return p;

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
//typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert(iterator i, iterator p, iterator end)
//{
//
//   
//
//   
//
//   return insert_before(i, p, end);
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
//typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_before(iterator i, iterator p, iterator end)
//{
//
//   
//   return insert_before(i, p, end);
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
//typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_after(iterator i, iterator p, iterator end)
//{
//
//   
//
//   
//
//   return insert_after(i, p, end);
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
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert(iterator position, iterator p, iterator end) // same as insert before
{

   return insert_before(position, p, end);

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
//   //      iterator = iterator.next();
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



