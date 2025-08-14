// iterator refactoring and range base class by camilo on 2022-12-09 20:12 <3ThomasBorregaardSorensen!!
#pragma once


#include "list_node.h"
#include "acme/platform/auto_pointer.h"


template < class TYPE, class ARG_TYPE >
class list_base :
   public ::range < ::list_iterator < ::list_node < TYPE > * > >
{
public:


   using is_list_base = true_type;

   using NODE = ::list_node < TYPE >;

   using ITERATOR = ::list_iterator < NODE * >;

   using RANGE = ::range < ITERATOR >;

   using ITEM = typename NODE::ITEM;

   using ARG_ITEM = ARG_TYPE;

   using this_iterator = typename RANGE::this_iterator;

   using iterator = typename RANGE::iterator;

   using const_iterator = typename RANGE::const_iterator;

   //__declare_iterator_struct_ok(list_base, iterator, m_pnode, ::is_set(this->m_pnode));

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


   //   make_iterator m_begin
   //   {

   //      return make_iterator(this->m_pcontainer->get_start(), this->m_pcontainer);

   //   }

      void list_base_ok() const;

      void container_ok() const
      {

         list_base_ok();

      }

      iterator end()
      {

         return nullptr;

      }


   //   make_iterator & operator ++ ()
   //   {

   //      this->m_pnode = this->m_pnode.next();

   //      return *this;

   //   }


   //   make_iterator operator ++ (int)
   //   {

   //      make_iterator iterator = this->m_pnode;

   //      this->m_pnode = this->m_pnode.next();

   //      return iterator;

   //   }

   //   make_iterator & operator -- ()
   //   {

   //      this->m_pnode = this->m_pnode->back();

   //      return *this;

   //   }


   //   make_iterator operator -- (int)
   //   {

   //      make_iterator iterator = this->m_pnode;

   //      this->m_pnode = this->m_pnode->back();

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
   ::collection::count        m_count;




   list_base();
   list_base(const list_base & l);
   list_base(class list_base && l);
   ~list_base() ;

   //inline list_base();
   //inline list_base(const class list_base < TYPE, ARG_TYPE > & l);
   //inline list_base(const class list_base < TYPE, ARG_TYPE > & l);

   inline static void from(list_base < TYPE, ARG_TYPE > & l, iterator p);
   inline static list_base < TYPE, ARG_TYPE >  from(iterator p);

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
   //   return ((list_base *)this)->index_iterator(nIndex);
   //}

   //const_iterator reverse_index_iterator(index nIndex) const
   //{
   //   return ((list_base *)this)->reverse_index_iterator(nIndex);
   //}


   //index iterator_index(const_iterator it) const
   //{

   //   return ((list_base *)this)->iterator_index(it, (list_base *)this));

   //}


   // getting/modifying an matter at a given position
   TYPE & get_at(iterator p) { return *p; }
   const TYPE & get_at(iterator p) const { return *p; }
   void set_at(iterator p, ARG_TYPE newElement) { *p = newElement; }

   // iteration
   //iterator m_begin const;
   //iterator m_end const;


   //iterator lower_bound()
   //{
   //   return iterator(nullptr, this);
   //}


   //iterator m_begin
   //{
   //   return iterator(m_begin, this);
   //}


   //iterator m_end
   //{
   //   return iterator(nullptr, this);
   //}


   //iterator upper_bound()
   //{
   //   return iterator(m_end, this);
   //}

   //const_iterator lower_bound() const
   //{
   //   return const_iterator(nullptr, this);
   //}


   //const_iterator m_begin const
   //{
   //   return const_iterator(m_begin, this);
   //}


   const_iterator end() const
   {
      
      return nullptr;

   }


   //const_iterator upper_bound() const
   //{
   //   return const_iterator(m_end, this);
   //}



   //inline iterator get_start() const { return m_begin; }

   void erase(iterator iterator);

   void erase_defer_next(iterator & iterator);

   void erase_defer_back(iterator & iterator);

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
      // ::collection::count of elements
   ::collection::count get_count() const;
   ::collection::count get_size() const;
   ::collection::count size() const;
   bool is_empty(::collection::count countMinimum = 1) const;
   bool has_elements(::collection::count countMinimum = 1) const;
   bool has_element() const;
   bool empty(::collection::count countMinimum = 1) const;

   // peek at head or tail
   TYPE & head();
   const TYPE & head() const;
   TYPE & tail();
   const TYPE & tail() const;

   
   // get head or tail (and erase it) - don't call on is_empty list_base !
   void erase_head();
   void erase_tail();

   ::auto_pointer < ::list_node < TYPE > > pick_auto_head();
   ::auto_pointer < ::list_node < TYPE > > pick_auto_tail();

   TYPE pick_head();
   TYPE pick_tail();

   void _add_head_node(NODE * p);
   void _add_tail_node(NODE * p);

   // add before head or after tail
   iterator add_head(ARG_TYPE newElement);
   iterator add_tail(ARG_TYPE newElement);
   iterator transfer_head(TYPE && newElement);
   iterator transfer_tail(TYPE && newElement);

   void push_front(ARG_TYPE newElement);
   void add(ARG_TYPE newElement);

   // add another list_base of elements before head or after tail
   void copy_head(const list_base < TYPE, ARG_TYPE > & l);
   void copy_tail(const list_base < TYPE, ARG_TYPE > & l);
   void copy(const list_base < TYPE, ARG_TYPE > & l);

   // erase all elements
   void erase_all();
   void clear();

   TYPE & front();
   const TYPE & front() const;
   this_iterator & back() { return (this_iterator &) this->m_end; }
   const_iterator & back() const { return (const_iterator &)this->m_end; }

   TYPE pop_front();

   //TYPE& get_next(iterator& rPosition); // return *position++
   //const TYPE& get_next(iterator& rPosition) const; // return *position++
   //TYPE& get_previous(iterator& rPosition); // return *position--
   //const TYPE& get_previous(iterator& rPosition) const; // return *position--


   void erase_at(::collection::index i);





   //iterator detach(iterator position);
   //iterator detach(iterator it);

   ::collection::count detach(iterator p, iterator end);

   iterator insert(iterator position, ARG_TYPE newElement);
   //iterator insert(iterator position, iterator it);
   iterator insert(iterator position, iterator iterator);
   iterator insert(iterator position, list_base < TYPE, ARG_TYPE > & l);
   iterator insert(iterator position, iterator p, iterator end);

   iterator insert_before(iterator position, ARG_TYPE newElement);
   //iterator insert_before(iterator position, iterator it);
   iterator insert_before(iterator position, iterator iterator);
   iterator insert_before(iterator position, list_base < TYPE, ARG_TYPE > & l);
   iterator insert_before(iterator position, iterator p, iterator end);

   iterator insert_after(iterator position, ARG_TYPE newElement);
   //iterator insert_after(iterator position, iterator it);
   iterator insert_after(iterator position, iterator iterator);
   iterator insert_after(iterator position, list_base < TYPE, ARG_TYPE > & l);
   iterator insert_after(iterator position, iterator p, iterator end);

   //iterator insert(iterator position, ARG_TYPE newElement);
   ////iterator insert(iterator position, iterator it);
   //iterator insert(iterator position, iterator iterator);
   //iterator insert(iterator position, list_base < TYPE, ARG_TYPE > & l);
   //iterator insert(iterator position, iterator p, iterator end);

   //iterator insert_before(iterator position, ARG_TYPE newElement);
   ////iterator insert_before(iterator position, iterator it);
   //iterator insert_before(iterator position, iterator iterator);
   //iterator insert_before(iterator position, list_base < TYPE, ARG_TYPE > & l);
   //iterator insert_before(iterator position, iterator p, iterator end);

   //iterator insert_after(iterator position, ARG_TYPE newElement);
   ////iterator insert_after(iterator position, iterator it);
   //iterator insert_after(iterator position, iterator iterator);
   //iterator insert_after(iterator position, list_base < TYPE, ARG_TYPE > & l);
   //iterator insert_after(iterator position, iterator p, iterator end);


   void splice(iterator position, list_base & l);
   void splice(iterator position, list_base & l, iterator i);
   void splice(iterator position, list_base & l, iterator p, iterator end);
   void __swap(iterator position1, iterator position2);


   list_base < TYPE, ARG_TYPE > & operator = (const class list_base & l);
#ifdef MOVE_SEMANTICS
   list_base < TYPE, ARG_TYPE > & operator = (class list_base && l);
#endif


   template < typename PRED >
   void each(PRED pred)
   {

      auto p = this->m_begin;

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
inline list_base < TYPE, ARG_TYPE >::list_base()
{

   this->m_count = 0;
   this->m_begin = nullptr;
   this->m_end = nullptr;

}


template<class TYPE, class ARG_TYPE>
list_base<TYPE, ARG_TYPE>::list_base(const list_base & l)
{

   this->m_count = 0;
   this->m_begin = nullptr;
   this->m_end = nullptr;

   copy(l);

}


template<class TYPE, class ARG_TYPE>
inline void list_base < TYPE, ARG_TYPE >::from(list_base < TYPE, ARG_TYPE > & l, iterator p)
{

   l.m_end = nullptr;

   l.m_begin = p;

   l.m_count = 0;

   if (!p)
   {

      return;

   }

   while (true)
   {

      if (!p.next())
      {

         l.m_end = p;

         break;

      }

      p++;

      l.m_count++;

   }

   l.m_count++;

}

template<class TYPE, class ARG_TYPE>
inline list_base < TYPE, ARG_TYPE > list_base < TYPE, ARG_TYPE >::from(iterator p)
{

   list_base < TYPE, ARG_TYPE >  l;

   from(l, p);

   return l;

}



template<class TYPE, class ARG_TYPE>
inline ::collection::count list_base<TYPE, ARG_TYPE>::get_count() const
{

   return this->m_count;

}

template<class TYPE, class ARG_TYPE>
inline bool list_base<TYPE, ARG_TYPE>::has_element() const
{

   return get_count() > 0;

}


template<class TYPE, class ARG_TYPE>
inline ::collection::count list_base<TYPE, ARG_TYPE>::get_size() const
{

   return this->m_count;

}


template<class TYPE, class ARG_TYPE>
inline ::collection::count list_base<TYPE, ARG_TYPE>::size() const
{
   return this->m_count;
}

template<class TYPE, class ARG_TYPE>
inline bool list_base<TYPE, ARG_TYPE>::is_empty(::collection::count countMinimum) const
{
   return this->m_count < countMinimum;
}

template<class TYPE, class ARG_TYPE>
inline bool list_base<TYPE, ARG_TYPE>::empty(::collection::count countMinimum) const
{
   return this->m_count < countMinimum;
}

template<class TYPE, class ARG_TYPE>
inline bool list_base<TYPE, ARG_TYPE>::has_elements(::collection::count countMinimum) const
{
   return this->m_count >= countMinimum;
}

template<class TYPE, class ARG_TYPE>
inline TYPE & list_base<TYPE, ARG_TYPE>::head()
{
   return this->m_begin.topic();
}
template<class TYPE, class ARG_TYPE>
inline const TYPE & list_base<TYPE, ARG_TYPE>::head() const
{
   return this->m_begin.topic();
}
template<class TYPE, class ARG_TYPE>
inline TYPE & list_base<TYPE, ARG_TYPE>::tail()
{
   return this->m_end.topic();
}
template<class TYPE, class ARG_TYPE>
inline const TYPE & list_base<TYPE, ARG_TYPE>::tail() const
{
   return this->m_end.topic();
}
//template<class TYPE, class ARG_TYPE>
//inline typename list_base<TYPE, ARG_TYPE>::iterator list_base<TYPE, ARG_TYPE>::m_begin const
//{
//   return this->m_begin;
//}
//template<class TYPE, class ARG_TYPE>
//inline typename list_base<TYPE, ARG_TYPE>::iterator list_base<TYPE, ARG_TYPE>::m_end const
//{
//   return (iterator) this->m_end;
//}

template<class TYPE, class ARG_TYPE>
inline TYPE & list_base < TYPE, ARG_TYPE >::front()
{
   return get_at(this->m_begin);
}


template<class TYPE, class ARG_TYPE>
inline const TYPE & list_base < TYPE, ARG_TYPE >::front() const
{
   
   return get_at(this->m_begin);

}


template<class TYPE, class ARG_TYPE>
inline TYPE list_base < TYPE, ARG_TYPE >::pop_front()
{

   auto p = this->m_begin;

   TYPE t = *p;

   this->erase(p);

   return t;

}


//template<class TYPE, class ARG_TYPE>
//inline TYPE & list_base < TYPE, ARG_TYPE >::back()
//{
//
//   return *this->m_end;
//
//}
//
//
//template<class TYPE, class ARG_TYPE>
//inline const TYPE & list_base < TYPE, ARG_TYPE >::back() const
//{
//
//   return *this->m_end;
//
//}


template<class TYPE, class ARG_TYPE>
list_base<TYPE, ARG_TYPE>::list_base(class list_base && l)
{

   this->m_count = l.m_count;
   this->m_begin = l.m_begin;
   this->m_end = l.m_end;

   l.m_begin = nullptr;
   l.m_end = nullptr;

}


template<class TYPE, class ARG_TYPE>
void list_base<TYPE, ARG_TYPE>::erase_all()
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
void list_base<TYPE, ARG_TYPE>::clear()
{

   erase_all();

}

template<class TYPE, class ARG_TYPE>
list_base<TYPE, ARG_TYPE>::~list_base()
{
   erase_all();
   ASSERT(this->m_count == 0);
}


template<class TYPE, class ARG_TYPE>
void list_base<TYPE, ARG_TYPE>::push_front(ARG_TYPE newElement)
{

   add_head(newElement);

}

template<class TYPE, class ARG_TYPE>
void list_base<TYPE, ARG_TYPE>::add(ARG_TYPE newElement)
{

   add_tail(newElement);

}

template<class TYPE, class ARG_TYPE>
void list_base<TYPE, ARG_TYPE>::copy_head(const list_base < TYPE, ARG_TYPE > & l)
{

   ASSERT_OK(this);

   auto p = l.m_end;

   while (p)
   {

      add_head(p.topic());

      p--;

   }

}

template<class TYPE, class ARG_TYPE>
void list_base<TYPE, ARG_TYPE>::copy_tail(const list_base < TYPE, ARG_TYPE > & l)
{

   ASSERT_OK(this);

   auto p = l.m_end;

   while (p)
   {

      add_tail(*p);

      p++;

   }

}


template<class TYPE, class ARG_TYPE>
void list_base<TYPE, ARG_TYPE>::copy(const list_base < TYPE, ARG_TYPE > & l)
{

   //ASSERT_OK(this);

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
::auto_pointer < ::list_node < TYPE > > list_base<TYPE, ARG_TYPE>::pick_auto_head()
{

   ASSERT_OK(this);

   ASSERT(this->m_begin.is_set());  // don't call on is_empty list_base !!!

   auto pnodeBegin = this->m_begin.m_p;

   if (!pnodeBegin->back().m_p) // this->m_begin.back() must be null,
      // this is what is expected at the head (this->m_begin)
   {

      if (!pnodeBegin->next().m_p)
      {

         this->m_begin.m_p = nullptr;

         this->m_end.m_p = nullptr;

         ASSERT(this->m_count == 1);

         this->m_count = 0;

      }
      else
      {

         ASSERT(pnodeBegin->next().back().m_p == pnodeBegin);

         this->m_begin.m_p = pnodeBegin->next().m_p;

         this->m_begin.back().m_p = nullptr;

         this->m_count--;

      }

      return ::transfer(pnodeBegin);

   }
   else
   {

      throw "this->m_begin isn't pointing to the beggining of list_base?";

   }

}


template<class TYPE, class ARG_TYPE>
::auto_pointer < ::list_node < TYPE > > list_base<TYPE, ARG_TYPE>::pick_auto_tail()
{

   ASSERT_OK(this);

   ASSERT(this->m_end.is_set());  // don't call on is_empty list_base !!!

   auto pnodeEnd = this->m_end.m_p;

   if (!pnodeEnd->next().m_p) // this->m_end.next() must be null,
      // this is what is expected at the tail (this->m_end)
   {

      if (!pnodeEnd->back().m_p)
      {

         this->m_end.m_p = nullptr;

         this->m_begin.m_p = nullptr;

         ASSERT(this->m_count == 1);

         this->m_count = 0;

      }
      else
      {

         ASSERT(pnodeEnd->back().next().m_p == pnodeEnd);

         this->m_end.m_p = pnodeEnd->back().m_p;

         this->m_end.next().m_p = nullptr;

         this->m_count--;

      }

      return ::transfer(pnodeEnd);

   }
   else
   {

      throw "this->m_end isn't pointing to the end of list_base?";

   }

}


template<class TYPE, class ARG_TYPE>
TYPE list_base<TYPE, ARG_TYPE>::pick_head()
{

   return ::transfer(pick_auto_head()->topic());

}


template<class TYPE, class ARG_TYPE>
TYPE list_base<TYPE, ARG_TYPE>::pick_tail()
{

   return ::transfer(pick_auto_tail()->topic());

}


template<class TYPE, class ARG_TYPE>
void list_base<TYPE, ARG_TYPE>::erase_head()
{

   ASSERT_OK(this);

   ASSERT(this->m_begin.is_set());  // don't call on is_empty list_base !!!

   auto pnodeBegin = this->m_begin.m_p;

   if (!pnodeBegin->back().m_p) // this->m_begin.back() must be null,
      // this is what is expected at the head (this->m_begin)
   {

      if (!pnodeBegin->next().m_p)
      {

         this->m_begin.m_p = nullptr;

         this->m_end.m_p = nullptr;

         ASSERT(this->m_count == 1);

         this->m_count = 0;

      }
      else
      {

         ASSERT(pnodeBegin->next().back().m_p == pnodeBegin);

         this->m_begin.m_p = pnodeBegin->next().m_p;

         this->m_begin.back().m_p = nullptr;

         this->m_count--;

      }

      delete pnodeBegin;

   }
   else
   {

      throw "this->m_begin isn't pointing to the beggining of list_base?";

   }

}


template<class TYPE, class ARG_TYPE>
void list_base<TYPE, ARG_TYPE>::erase_tail()
{

   ASSERT_OK(this);
   
   ASSERT(this->m_end.is_set());  // don't call on is_empty list_base !!!

   auto pnodeEnd = this->m_end.m_p;

   if (!pnodeEnd->next().m_p) // this->m_end.next() must be null,
      // this is what is expected at the tail (this->m_end)
   {

      if (!pnodeEnd->back().m_p)
      {

         this->m_end.m_p = nullptr;

         this->m_begin.m_p = nullptr;

         ASSERT(this->m_count == 1);

         this->m_count = 0;

      }
      else
      {

         ASSERT(pnodeEnd->back().next().m_p == pnodeEnd);

         this->m_end.m_p = pnodeEnd->back().m_p;

         this->m_end.next().m_p = nullptr;

         this->m_count--;

      }

      delete pnodeEnd;

   }
   else
   {

      throw "this->m_end isn't pointing to the end of list_base?";

   }

}


template<class TYPE, class ARG_TYPE>
typename list_base < TYPE, ARG_TYPE >::iterator list_base < TYPE, ARG_TYPE > ::insert_before(iterator position, list_base < TYPE, ARG_TYPE > & l)
{

   if (l.m_count <= 0)
      return position;

   this->m_count += l.m_count;

   if (position)
   {

      if (position.back())
      {

         position.back().next() = l.m_begin;

      }

      l.m_begin.back() = position.back();

      position.back() = l.m_end;

      if (position == this->m_begin)
      {

         this->m_begin = l.m_begin;

         this->m_begin.back() = nullptr;

      }

   }
   else
   {

      l.m_begin.back() = this->m_end;

      this->m_end = l.m_begin;

      if (!this->m_begin)
      {

         this->m_begin = l.m_begin;

      }

   }

   l.m_end.next() = position;

   return l.m_begin;

}


template<class TYPE, class ARG_TYPE>
typename list_base < TYPE, ARG_TYPE >::iterator list_base < TYPE, ARG_TYPE > ::insert_before(iterator position, iterator p, iterator end)
{

   ::collection::count count = end - p;

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

      if (position == this->m_begin)
      {

         this->m_begin = p;

         this->m_begin.back() = nullptr;

      }

   }
   else
   {

      p.back() = this->m_end;

      this->m_end = p;

      if (!this->m_begin)
      {

         this->m_begin = p;

      }

   }

   end.next() = position;

   return p;

}


//template<class TYPE, class ARG_TYPE>
//typename list_base < TYPE, ARG_TYPE >::iterator list_base<TYPE, ARG_TYPE>::insert_after(iterator position, iterator it)
//{
//
//   return insert_after(position, it);
//
//}


template<class TYPE, class ARG_TYPE>
typename list_base < TYPE, ARG_TYPE >::iterator list_base < TYPE, ARG_TYPE > ::insert_after(iterator position, iterator iterator)
{

   list_base < TYPE, ARG_TYPE > l;

   list_base < TYPE, ARG_TYPE >::from(l, iterator);

   return insert_before(position, l);

}



template<class TYPE, class ARG_TYPE>
typename list_base < TYPE, ARG_TYPE >::iterator list_base < TYPE, ARG_TYPE > ::insert_after(iterator position, list_base < TYPE, ARG_TYPE > & l)
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

         position.next().back() = l.m_end;

      }

      l.m_end.next() = position.next();

      position.next() = l.m_begin;

      if (position == this->m_end)
      {

         this->m_end = l.m_end;

         this->m_end.next() = nullptr;

      }

   }
   else
   {

      l.m_begin.next() = this->m_begin;

      this->m_begin = l.m_end;

      if (!this->m_end)
      {

         this->m_end = l.m_end;

      }

   }

   l.m_begin.back() = position;

   return l.m_begin;

}


template<class TYPE, class ARG_TYPE>
typename list_base < TYPE, ARG_TYPE >::iterator list_base < TYPE, ARG_TYPE > ::insert_after(iterator position, iterator p, iterator end)
{

   ::collection::count count = end - p;

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

      if (position == this->m_end)
      {

         this->m_end = end;

         this->m_end.next() = nullptr;

      }

   }
   else
   {

      p.next() = this->m_begin;

      this->m_begin = end;

      if (!this->m_end)
      {

         this->m_end = end;

      }

   }

   p.back() = position;

   return p;

}



//template<class TYPE, class ARG_TYPE>
//typename list_base < TYPE, ARG_TYPE >::iterator list_base<TYPE, ARG_TYPE>::insert_before(iterator position, iterator it)
//{
//
//   return insert_before(position, it);
//
//}


template<class TYPE, class ARG_TYPE>
void list_base<TYPE, ARG_TYPE>::__swap(iterator position1, iterator position2)
{
   ASSERT_OK(this);

   if (!position1)
   {

      if (!position2)
      {

         return;

      }
      else
      {
         
         if (position2 != this->m_begin)
         {

            if (this->m_end == position2)
            {

               this->m_end = position2.back();

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

            position2.next() = this->m_begin;

            this->m_begin = position2;

         }

      }

   }
   else if (!position2)
   {
      if (position1 != this->m_end)
      {

         if (this->m_begin == position1)
         {

            this->m_begin = position1.next();

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

         position1.back() = this->m_end;

         this->m_end = position1;

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

      if (position1 == this->m_begin)
      {

         this->m_begin = position2;

      }

      if (position1 == this->m_end)
      {

         this->m_end = position2;

      }

      if (position2 == this->m_begin)
      {

         this->m_begin = position1;

      }

      if (position2 == this->m_end)
      {

         this->m_end = position1;

      }

   }

}


template<class TYPE, class ARG_TYPE>
void list_base<TYPE, ARG_TYPE>::erase_at(::collection::index i)
{

   this->erase(this->m_begin + i);

}


//template<class TYPE, class ARG_TYPE>
//bool list_base<TYPE, ARG_TYPE>::erase_item(ARG_ITEM item)
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
void list_base<TYPE, ARG_TYPE>::erase(iterator pErase)
{

   ASSERT_OK(this);

   auto p = detach(pErase);

   delete p.get();

}


template<class TYPE, class ARG_TYPE>
void list_base<TYPE, ARG_TYPE>::erase_defer_next(iterator& p)
{

   ASSERT_OK(this);

   auto pNext = p.next();

   this->erase(p);

   p = pNext;

}


template<class TYPE, class ARG_TYPE>
void list_base<TYPE, ARG_TYPE>::erase_defer_back(iterator& p)
{

   ASSERT_OK(this);

   auto pBack = p.back();

   this->erase(p);

   p = pBack;

}



template < class TYPE, class ARG_TYPE >
typename list_base < TYPE, ARG_TYPE >::iterator list_base<TYPE, ARG_TYPE>::detach(iterator p)
{

   ASSERT_OK(this);

   if (!p)
   {

      return nullptr;

   }

   if (this->m_begin == this->m_end)
   {

      if (p != this->m_begin)
      {

         // item is not part of the list_base
         throw ::exception(::error_not_found);

      }

      this->m_begin = nullptr;

      this->m_end = nullptr;

   }

   if (p == this->m_begin || !p.back())
   {

      this->m_begin = p.next();

   }
   else
   {

      p.back().next() = p.next();

   }

   if (p == this->m_end || !p.next())
   {

      this->m_end = p.back();

   }
   else
   {

      p.next().back() = p.back();

   }

   this->m_count--;

   return p;

}


template < class TYPE, class ARG_TYPE >
::collection::count list_base<TYPE, ARG_TYPE>::detach(iterator p, iterator end)
{

   ASSERT_OK(this);

   if (!end || !p)
   {

      throw ::exception(error_bad_argument);

   }

   if (end == this->m_end || !end.next())
   {
         
      this->m_end = end.back();

   }
   else
   {

      end.next().back() = end.back();

   }

   if (p == this->m_begin || ! p.back())
   {

      this->m_begin = p.next();

   }
   else
   {
      
      p.back().next() = p.next();

   }

   ::collection::count count = 0;

   while (p != end)
   {

      //back = iterator;

      p++;

      count++;

   }

   p.back() = nullptr;

   end.next() = nullptr;

   return count;

}


//template < class TYPE, class ARG_TYPE >
//typename list_base < TYPE, ARG_TYPE >::iterator list_base<TYPE, ARG_TYPE>::splice(iterator position, const_iterator i)
//{
//
//   return splice(position, *((list_base *) i.m_pcontainer), i);
//
//}

//template < class TYPE, class ARG_TYPE >
//typename list_base < TYPE, ARG_TYPE >::iterator list_base<TYPE, ARG_TYPE>::splice(const_iterator position, const_iterator p, const_iterator end)
//{
//
//   return splice(position, *((list_base *) p.m_pcontainer), p, end);
//
//}


template < class TYPE, class ARG_TYPE >
void list_base<TYPE, ARG_TYPE>::splice(iterator position, list_base & l)
{

   auto p = l.m_begin;

   auto end = l.m_end;

   l.detach(p, end);

   insert_before(position, p, end);

}


template < class TYPE, class ARG_TYPE >
void list_base<TYPE, ARG_TYPE>::splice(iterator position, list_base & l, iterator i)
{

   l.detach(i);

   insert_before(position, i);

}

template < class TYPE, class ARG_TYPE >
void list_base<TYPE, ARG_TYPE>::splice(iterator i, list_base & l, iterator p, iterator end)
{

   l.detach(p, end);

   insert_before(i, p, end);

}


//template<class TYPE, class ARG_TYPE>
//typename list_base<TYPE, ARG_TYPE>::iterator list_base<TYPE, ARG_TYPE>::index_iterator(::collection::index index)
//{
//
//   //ASSERT_OK(this);
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
//index list_base<TYPE, ARG_TYPE>::iterator_index(iterator it)
//{
//
//   ASSERT_OK(this);
//
//   auto iterator = this->m_begin;
//
//   ::collection::index i = 0;
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
//inline typename list_base < TYPE, ARG_TYPE >::iterator list_base < TYPE, ARG_TYPE >::reverse_index_iterator(::collection::index index)
//{
//
//   //ASSERT_OK(this);
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
//void list_base<TYPE, ARG_TYPE>::assert_ok() const
//{
//
//   matter::assert_ok();
//
//   if (this->m_count == 0)
//   {
//
//      // is_empty list_base
//
//      ASSERT(this->m_begin == nullptr);
//      ASSERT(this->m_end == nullptr);
//
//   }
//   else
//   {
//
//      // non-is_empty list_base
//      ASSERT(::is_set(this->m_begin));
//      ASSERT(::is_set(this->m_end));
//
//   }
//
//}


template<class TYPE, class ARG_TYPE>
list_base < TYPE, ARG_TYPE > &
list_base<TYPE, ARG_TYPE>::operator = (const class list_base & l)
{

   if (&l != this)
   {

      copy(l);

   }

   return *this;

}


#ifdef MOVE_SEMANTICS

template<class TYPE, class ARG_TYPE>
list_base < TYPE, ARG_TYPE > &
list_base<TYPE, ARG_TYPE>::operator = (class list_base && l)
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



template<class TYPE, class ARG_TYPE>
void list_base<TYPE, ARG_TYPE>::_add_head_node(NODE * p)
{

   p->back().m_p = nullptr;

   p->next().m_p = this->m_begin.m_p;

   if (this->m_begin.m_p)
   {

      this->m_begin.back().m_p = p;

   }
   else
   {

      this->m_end.m_p = p;

   }

   this->m_begin.m_p = p;

   this->m_count++;

}


template<class TYPE, class ARG_TYPE>
void list_base<TYPE, ARG_TYPE>::_add_tail_node(NODE * p)
{

   p->m_back.m_p = this->m_end.m_p;

   p->m_next.m_p = nullptr;

   if (this->m_end.m_p)
   {

      this->m_end.m_p->m_next.m_p = p;

   }
   else
   {

      this->m_begin.m_p = p;

   }

   this->m_end.m_p = p;

   this->m_count++;

}


template<class TYPE, class ARG_TYPE>
typename list_base<TYPE, ARG_TYPE>::iterator list_base<TYPE, ARG_TYPE>::add_head(ARG_TYPE newElement)
{

   //ASSERT_OK(this);

   auto p = __raw_new typename list_base < TYPE, ARG_TYPE >::NODE (newElement);

   _add_head_node(p);

   return p;

}


template<class TYPE, class ARG_TYPE>
typename list_base<TYPE, ARG_TYPE>::iterator list_base<TYPE, ARG_TYPE>::add_tail(ARG_TYPE newElement)
{

   ASSERT_OK(this);

   auto p = __raw_new typename list_base < TYPE, ARG_TYPE >::NODE(newElement);

   _add_tail_node(p);

   return p;

}


template<class TYPE, class ARG_TYPE>
typename list_base<TYPE, ARG_TYPE>::iterator list_base<TYPE, ARG_TYPE>::transfer_head(TYPE && newElement)
{

   ASSERT_OK(this);

   auto p = __raw_new typename list_base < TYPE, ARG_TYPE >::NODE (::transfer(newElement));

   _add_head_node(p);

   return p;

}


template<class TYPE, class ARG_TYPE>
typename list_base<TYPE, ARG_TYPE>::iterator list_base<TYPE, ARG_TYPE>::transfer_tail(TYPE && newElement)
{

   ASSERT_OK(this);

   auto p = __raw_new typename list_base < TYPE, ARG_TYPE >::NODE (::transfer(newElement));

   _add_tail_node(p);

   return p;

}


template<class TYPE, class ARG_TYPE>
typename list_base<TYPE, ARG_TYPE>::iterator list_base<TYPE, ARG_TYPE>::insert_before(iterator position, ARG_TYPE newElement)
{
   ASSERT_OK(this);

   if (!position)
   {

      return add_head(newElement); // insert before nothing -> head of the list_base

   }

   // Insert it before position
   auto old = position;
   iterator p;
   p = __raw_new typename list_base < TYPE, ARG_TYPE >::NODE (newElement);
   p.back() = old.back();
   p.next() = old;
   p.topic() = newElement;

   if (old.back())
   {
//      ASSERT(is_memory_segment_ok(pOldNode->back(), sizeof(typename list_base < TYPE, ARG_TYPE >::node)));
      old.back().next() = p;
   }
   else
   {
      ASSERT(old == this->m_begin);
      this->m_begin = p;
   }
   
   old.back() = p;

   return p;

}


template<class TYPE, class ARG_TYPE>
typename list_base<TYPE, ARG_TYPE>::iterator list_base<TYPE, ARG_TYPE>::insert_after(iterator position, ARG_TYPE newElement)
{
   ASSERT_OK(this);

   if (!position)
   {

      return add_tail(newElement); // insert after nothing -> tail of the list_base

   }

   // Insert it before position
   auto old = position;
   ASSERT(is_memory_segment_ok(old.get(), sizeof(typename list_base < TYPE, ARG_TYPE >::NODE)));
   iterator p;
   p = __raw_new typename list_base < TYPE, ARG_TYPE >::NODE(newElement);
   p.back() = old;
   p.next() = old.next();
   p.topic() = newElement;

   if (old.next())
   {
      ASSERT(is_memory_segment_ok(old.next().get(), sizeof(typename list_base < TYPE, ARG_TYPE >::NODE)));
      old.next().back() = p;
   }
   else
   {
      ASSERT(old == this->m_end);
      this->m_end = p;
   }

   old.next() = p;

   return p;

}







template<class TYPE, class ARG_TYPE>
typename list_base < TYPE, ARG_TYPE >::iterator list_base < TYPE, ARG_TYPE > ::insert(iterator i, ARG_TYPE newElement) // same as insert before
{

   

   return insert_before(i, newElement);

}

//
//template<class TYPE, class ARG_TYPE>
//typename list_base < TYPE, ARG_TYPE >::iterator list_base < TYPE, ARG_TYPE > ::insert(iterator i, iterator it) // same as insert before
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
////typename list_base < TYPE, ARG_TYPE >::iterator list_base < TYPE, ARG_TYPE > ::insert(iterator i, iterator iterator)
////{
////
////   
////
////   return insert_before(i, iterator);
////
////}


template<class TYPE, class ARG_TYPE>
typename list_base < TYPE, ARG_TYPE >::iterator list_base < TYPE, ARG_TYPE > ::insert(iterator i, list_base < TYPE, ARG_TYPE > & l)
{

   

   return insert_before(i, l);

}


//template<class TYPE, class ARG_TYPE>
//typename list_base < TYPE, ARG_TYPE >::iterator list_base < TYPE, ARG_TYPE > ::insert(iterator i, iterator p, iterator end)
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
//typename list_base < TYPE, ARG_TYPE >::iterator list_base < TYPE, ARG_TYPE > ::insert_before(iterator i, ARG_TYPE newElement)
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
//typename list_base < TYPE, ARG_TYPE >::iterator list_base < TYPE, ARG_TYPE > ::insert_before(iterator i, iterator it)
//{
//
//   
//
//   return insert_before(i, it);
//
//}




//template<class TYPE, class ARG_TYPE>
//typename list_base < TYPE, ARG_TYPE >::iterator list_base < TYPE, ARG_TYPE > ::insert_before(iterator i, iterator iterator)
//{
//
//   
//
//   return insert_before(i, iterator);
//
//}

//
//template<class TYPE, class ARG_TYPE>
//typename list_base < TYPE, ARG_TYPE >::iterator list_base < TYPE, ARG_TYPE > ::insert_before(iterator i, list_base < TYPE, ARG_TYPE > & l)
//{
//
//   return insert_before(i, l);
//
//}


//template<class TYPE, class ARG_TYPE>
//typename list_base < TYPE, ARG_TYPE >::iterator list_base < TYPE, ARG_TYPE > ::insert_before(iterator i, iterator p, iterator end)
//{
//
//   
//   return insert_before(i, p, end);
//
//}


//template<class TYPE, class ARG_TYPE>
//typename list_base < TYPE, ARG_TYPE >::iterator list_base < TYPE, ARG_TYPE > ::insert_after(iterator i, ARG_TYPE newElement)
//{
//
//   
//
//   return insert_after(i, newElement);
//
//}


//template<class TYPE, class ARG_TYPE>
//typename list_base < TYPE, ARG_TYPE >::iterator list_base < TYPE, ARG_TYPE > ::insert_after(iterator i, iterator it)
//{
//
//   
//
//   return insert_after(i, it);
//
//}


//template<class TYPE, class ARG_TYPE>
//typename list_base < TYPE, ARG_TYPE >::iterator list_base < TYPE, ARG_TYPE > ::insert_after(iterator i, iterator iterator)
//{
//
//   
//
//   return insert_after(i, iterator);
//
//}


//template<class TYPE, class ARG_TYPE>
//typename list_base < TYPE, ARG_TYPE >::iterator list_base < TYPE, ARG_TYPE > ::insert_after(iterator i, list_base < TYPE, ARG_TYPE > & l)
//{
//
//   
//
//   return insert_after(i, l);
//
//}


//template<class TYPE, class ARG_TYPE>
//typename list_base < TYPE, ARG_TYPE >::iterator list_base < TYPE, ARG_TYPE > ::insert_after(iterator i, iterator p, iterator end)
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
//typename list_base < TYPE, ARG_TYPE >::iterator list_base < TYPE, ARG_TYPE > ::insert(iterator position, ARG_TYPE newElement)
//{
//
//   return insert_before(position, newElement);
//
//}


template<class TYPE, class ARG_TYPE>
typename list_base < TYPE, ARG_TYPE >::iterator list_base < TYPE, ARG_TYPE > ::insert(iterator position, iterator it)
{

   return insert_before(position, it);

}


//template<class TYPE, class ARG_TYPE>
//typename list_base < TYPE, ARG_TYPE >::iterator list_base < TYPE, ARG_TYPE > ::insert(iterator position, iterator iterator) // same as insert before
//{
//
//   return insert_before(position, iterator);
//
//}



//template<class TYPE, class ARG_TYPE>
//typename list_base < TYPE, ARG_TYPE >::iterator list_base < TYPE, ARG_TYPE > ::insert(iterator position, list_base < TYPE, ARG_TYPE > & l) // same as insert before
//{
//
//   return insert_before(position, l);
//
//}


template<class TYPE, class ARG_TYPE>
typename list_base < TYPE, ARG_TYPE >::iterator list_base < TYPE, ARG_TYPE > ::insert(iterator position, iterator p, iterator end) // same as insert before
{

   return insert_before(position, p, end);

}



template<class TYPE, class ARG_TYPE>
typename list_base < TYPE, ARG_TYPE >::iterator list_base < TYPE, ARG_TYPE > ::insert_before(iterator position, iterator iterator)
{

   list_base < TYPE, ARG_TYPE > l;

   list_base < TYPE, ARG_TYPE >::from(l, iterator);

   return insert_before(position, l);

}







//string_list_base::iterator string_list_base::find(const string & searchValue, iterator startAfter) const
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
//void list_base<TYPE, ARG_TYPE>::dump(dump_context& dumpcontext) const
//{
//
//   matter::dump(dumpcontext);
//
//   //dumpcontext << "with " << this->m_count << " elements";
//
//   //if (dumpcontext.GetDepth() > 0)
//   //{
//
//   //   auto iterator = this->m_begin;
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
//inline stream& operator <<(stream& stream, const string_list_base& list_base)
//{
//
//   stream << list_base.get_count();
//
//   for (auto& pitem : list_base)
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
//inline stream& operator >>(stream& stream, string_list_base& list_base)
//{
//
//   int iSize;
//   stream >> iSize;
//   string str;
//   for (int i = 0; i < iSize; i++)
//   {
//      stream >> str;
//      list_base.add_tail(str);
//   }
//   return stream;
//}
//



template<typename LIST_BASE>
class list_particle :
   virtual public ::particle,
   public LIST_BASE
{
public:


   using BASE_LIST = LIST_BASE;


   using BASE_LIST::BASE_LIST;
   using BASE_LIST::operator =;


};



