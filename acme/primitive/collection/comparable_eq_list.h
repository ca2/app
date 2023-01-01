#pragma once


#include "list.h"


template < class TYPE, class ARG_TYPE  = const TYPE&, class LIST_TYPE = ::list < TYPE, ARG_TYPE > >
class comparable_eq_list :
   public LIST_TYPE
{
public:


   using node = typename ::list < TYPE, ARG_TYPE >::node;
   using base_list = LIST_TYPE;
   using iterator = typename base_list::iterator;
   using const_iterator = typename base_list::const_iterator;


   comparable_eq_list();
   comparable_eq_list(const comparable_eq_list & array);


   iterator find_first_item(const TYPE &t, iterator start = nullptr, iterator end = nullptr) const;
   iterator find_last_item(const TYPE &t, iterator start = nullptr, iterator end = nullptr) const;
   ::count get_count() const;
   ::count get_count(const TYPE & t, iterator start = nullptr, iterator end = nullptr, ::count countMax = -1) const;
   bool contains(const TYPE & t, iterator start = nullptr, iterator end = nullptr, ::count countMin = 1, ::count countMax = -1) const;
   bool rear_contains(const TYPE & t, iterator start = nullptr, iterator end = nullptr, ::count countMin = 1, ::count countMax = -1) const;
   bool erase_first_item(const TYPE & t);
   bool erase_last_item(const TYPE & t);
   bool erase_first_item(const TYPE & t, iterator & p, iterator end = nullptr);
   bool erase_last_item(const TYPE & t, iterator & p, iterator end = nullptr);
   ::count erase_item(const TYPE & t, iterator start = nullptr, iterator end = nullptr, ::count countMin = 0, ::count countMax = -1);
   ::count rear_erase_item(const TYPE & t, iterator start = nullptr, iterator end = nullptr, ::count countMin = 0, ::count countMax = -1);
   ::count erase_list(const comparable_eq_list & l);


   bool add_tail_unique(ARG_TYPE t);
   bool add_head_unique(ARG_TYPE t);


   void merge_tail(const comparable_eq_list & l); // add_tail
   void merge_head(const comparable_eq_list & l); // add_tail
   void intersect(const comparable_eq_list & l);


   comparable_eq_list< TYPE, ARG_TYPE, LIST_TYPE > & operator -= (const TYPE & t);
   comparable_eq_list< TYPE, ARG_TYPE, LIST_TYPE > & operator &= (const comparable_eq_list< TYPE, ARG_TYPE, LIST_TYPE > & l);
   comparable_eq_list< TYPE, ARG_TYPE, LIST_TYPE > & operator -= (const comparable_eq_list< TYPE, ARG_TYPE, LIST_TYPE > & l);
   comparable_eq_list< TYPE, ARG_TYPE, LIST_TYPE > & operator |= (const comparable_eq_list< TYPE, ARG_TYPE, LIST_TYPE > & l);


   comparable_eq_list< TYPE, ARG_TYPE, LIST_TYPE > operator -(const comparable_eq_list< TYPE, ARG_TYPE, LIST_TYPE > & l) const;


};


template < class TYPE, class ARG_TYPE, class LIST_TYPE>
comparable_eq_list<  TYPE,  ARG_TYPE,  LIST_TYPE>::
comparable_eq_list()
{

}


template < class TYPE, class ARG_TYPE, class LIST_TYPE>
comparable_eq_list<  TYPE,  ARG_TYPE,  LIST_TYPE>::
comparable_eq_list(const comparable_eq_list<  TYPE,  ARG_TYPE,  LIST_TYPE> & l) :
LIST_TYPE(l)
{

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
typename comparable_eq_list < TYPE, ARG_TYPE, LIST_TYPE >::iterator comparable_eq_list < TYPE, ARG_TYPE, LIST_TYPE >::
find_first_item(const TYPE & t, iterator p, iterator end) const
{

   if(!p)
   {

      p = this->begin();

   }

   while(p != end)
   {

      if(*p == t)
      {

         return p;

      }

      p++;

   }

   return nullptr;

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
typename comparable_eq_list < TYPE, ARG_TYPE, LIST_TYPE >::iterator comparable_eq_list < TYPE, ARG_TYPE, LIST_TYPE >::
find_last_item(const TYPE & t, iterator start, iterator p) const
{

   if(!p)
   {

      p = this->get_tail();

   }

   while(p != start)
   {

      if(*p == t)
      {

         return p;

      }

      p--;
   }

   return nullptr;

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
inline ::count comparable_eq_list < TYPE, ARG_TYPE, LIST_TYPE >::
get_count() const
{

   return LIST_TYPE::get_count();

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
::count comparable_eq_list < TYPE, ARG_TYPE, LIST_TYPE >::
get_count(const TYPE & t, iterator start, iterator end, ::count countMax) const
{

   ::count count = 0;

   while((countMax >= 0 && count <= countMax) && (start = find_first(t, start, end)))
   {

      count++;

   }

   return count;

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
bool comparable_eq_list < TYPE, ARG_TYPE, LIST_TYPE >::
contains(const TYPE & t, iterator p, iterator end, ::count countMin, ::count countMax) const
{

   ::count count = 0;

   while((count < countMin || (countMax >= 0 && count <= countMax)) && (p = find_first_item(t, p, end)))
   {

      count++;

   }
   
   return count >= countMin && conditional(countMax >= 0, count <= countMax);

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
bool comparable_eq_list < TYPE, ARG_TYPE, LIST_TYPE >::
rear_contains(const TYPE & t, iterator p, iterator end, ::count countMin, ::count countMax) const
{

   ::count count = 0;

   while((count < countMin || (countMax >= 0 && count <= countMax))  && (p = find_last(t, p, end)))
   {

      count++;

   }

   return count >= countMin && conditional(countMax >= 0, count <= countMax);

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
bool comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE>::add_tail_unique(ARG_TYPE t)
{

   if(contains(t))
   {

      return false;

   }

   this->add_tail(t);

   return true;

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
bool comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE>::add_head_unique(ARG_TYPE t)
{

   if(contains(t))
   {

      return false;

   }

   this->add_head(t);

   return true;

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
void comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE>::
intersect(const comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE> & a)
{

   auto pnode = this->get_head();

   while (pnode)
   {

      if(!a.contains(pnode->m_value))
      {

         this->erase(pnode->m_value);

      }

      pnode = pnode->m_pnext;

   }

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
void comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE>::
merge_tail(const comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE> & l)
{

   auto pnode = l.get_head();

   while(pnode)
   {

      if(!contains(pnode->m_value))
      {

         this->add_tail(pnode->m_value);

      }

      pnode = pnode->m_pnext;

   }

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
void comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE>::
merge_head(const comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE> & l)
{

   auto pnode = l.get_tail();

   while(pnode)
   {

      if(!contains(pnode->m_value))
      {

         add_head(pnode->m_value);

      }

      pnode = pnode->m_pprevious;

   }

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
inline comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE> &  comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE>::
operator &= (const comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE> & l)
{

   intersect(l);

   return *this;

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
inline comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE> &  comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE>::
operator -= (const TYPE & t)
{

   erase(t);

   return *this;

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
inline comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE> &  comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE>::
operator -= (const comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE> & l)
{

   erase(l);

   return *this;

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
inline comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE> comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE>::
operator - (const comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE> & l) const
{

   comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE> aRet(*this);

   aRet.erase(l);

   return aRet;

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
inline comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE> &  comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE>::
operator |= (const comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE> & l)
{

   merge_tail(l);

   return *this;

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
bool comparable_eq_list < TYPE, ARG_TYPE , LIST_TYPE >::
erase_first_item(const TYPE & t)
{

   iterator p = this->find_first(t);

   if (!p)
   {

      return false;

   }

   this->erase_item(p);

   return true;

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
bool comparable_eq_list < TYPE, ARG_TYPE , LIST_TYPE >::erase_first_item(const TYPE & t, iterator & p, iterator end)
{

   if((p = this->find_first_item(t, p, end)) != nullptr)
   {

      auto pErase = p;

      p = p + 1;

      this->erase(pErase);

      return true;

   }

   return false;

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
::count comparable_eq_list < TYPE, ARG_TYPE , LIST_TYPE >::
erase_item(const TYPE & t, iterator p, iterator end, ::count countMin, ::count countMax)
{

   ::count count = 0;

   if(contains(t, p, end, countMin, countMax))
   {

      while (conditional(countMax >= 0, count < countMax) && erase_first_item(t, p, end))
      {

         count++;

      }

   }

   return count;

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
bool comparable_eq_list < TYPE, ARG_TYPE , LIST_TYPE >::
erase_last_item(const TYPE & t)
{

   auto p = find_last_item(t);

   if(p)
   {

      this->erase(p);

      return true;

   }

   return false;

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
bool comparable_eq_list < TYPE, ARG_TYPE , LIST_TYPE >::
erase_last_item(const TYPE & t, iterator & p, iterator end)
{

   if(p = find_last_item(t, p, end))
   {

      auto pErase = p;

      p--;

      this->erase_item(pErase);

      return true;

   }

   return false;

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
::count comparable_eq_list < TYPE, ARG_TYPE , LIST_TYPE >::
rear_erase_item(const TYPE & t, iterator p, iterator end, ::count countMin, ::count countMax)
{

   ::count count = 0;

   if(contains(t, p, end, countMin, countMax))
   {

      while (conditional(countMax >= 0, count < countMax) && erase_last(t, p, end))
      {

         count++;

      }

   }

   return count;

}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
::count comparable_eq_list < TYPE, ARG_TYPE , LIST_TYPE >::erase_list(const comparable_eq_list & l)
{

   ::count count = 0;

   auto p = l.get_head();

   while(p)
   {

      count += erase(*p);

      p++;

   }

   return count;

}



