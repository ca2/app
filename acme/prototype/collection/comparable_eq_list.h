#pragma once


#include "list.h"


template < class TYPE, class ARG_TYPE  = const TYPE&, class LIST_BASE = ::list_base < TYPE, ARG_TYPE > >
class comparable_eq_list_base :
   public LIST_BASE
{
public:


   using BASE_LIST = LIST_BASE;
   using node = typename BASE_LIST::NODE;
   using iterator = typename BASE_LIST::iterator;
   using const_iterator = typename BASE_LIST::const_iterator;


   using BASE_LIST::BASE_LIST;
   using BASE_LIST::operator =;
   //comparable_eq_list_base();
   //comparable_eq_list_base(const comparable_eq_list_base & array);


   iterator find_first_item(const TYPE &t, iterator start = nullptr, iterator end = nullptr) const;
   iterator find_last_item(const TYPE &t, iterator start = nullptr, iterator end = nullptr) const;
   ::collection::count get_count() const;
   ::collection::count get_count(const TYPE & t, iterator start = nullptr, iterator end = nullptr, ::collection::count countMax = -1) const;
   bool contains(const TYPE & t, iterator start = nullptr, iterator end = nullptr, ::collection::count countMin = 1, ::collection::count countMax = -1) const;
   bool rear_contains(const TYPE & t, iterator start = nullptr, iterator end = nullptr, ::collection::count countMin = 1, ::collection::count countMax = -1) const;
   bool erase_first(const TYPE & t);
   bool erase_last(const TYPE & t);
   bool erase_first(const TYPE & t, iterator & p, iterator end = nullptr);
   bool erase_last(const TYPE & t, iterator & p, iterator end = nullptr);

   using BASE_LIST::erase;
   //::collection::count erase(const TYPE & t, iterator start = nullptr, iterator end = nullptr, ::collection::count countMin = 0, ::collection::count countMax = -1);
   ::collection::count erase(const TYPE & t, iterator start = nullptr, iterator end = nullptr);
   //::collection::count rear_erase(const TYPE & t, iterator start = nullptr, iterator end = nullptr, ::collection::count countMin = 0, ::collection::count countMax = -1);
   template < primitive_container CONTAINER >
   ::collection::count erase(const CONTAINER & container);


   bool add_tail_unique(ARG_TYPE t);
   bool add_head_unique(ARG_TYPE t);


   bool add_unique(ARG_TYPE t)
   {

      auto pFind = this->find_first_item(t);

      if (pFind)
      {

         return false;

      }

      this->add_tail(t);

      return true;

   }


   void change(ARG_TYPE t, bool bAdd)
   {

      auto pFind = this->find_first_item(t);

      if(pFind)
      {

         if (!bAdd)
         {

            this->erase(pFind);

         }

      }
      else
      {

         if (bAdd)
         {

            this->add(t);

         }

      }

   }


   void toggle(ARG_TYPE t)
   {

      auto pFind = this->find_first_item(t);

      if (pFind)
      {

         this->erase(pFind);

      }
      else
      {

         this->add(t);

      }

   }


   template < primitive_container CONTAINER >
   void merge_tail(const CONTAINER & container);
   template < primitive_container CONTAINER >
   void merge_head(const CONTAINER & container);
   template < primitive_container CONTAINER >
   void intersect(const CONTAINER & container);


   comparable_eq_list_base< TYPE, ARG_TYPE, LIST_BASE > & operator -= (const TYPE & t);
   template < primitive_container CONTAINER >
   comparable_eq_list_base< TYPE, ARG_TYPE, LIST_BASE > & operator &= (const CONTAINER & container);
   template < primitive_container CONTAINER >
   comparable_eq_list_base< TYPE, ARG_TYPE, LIST_BASE > & operator -= (const CONTAINER & container);
   template < primitive_container CONTAINER >
   comparable_eq_list_base< TYPE, ARG_TYPE, LIST_BASE > & operator |= (const CONTAINER & container);

   template < primitive_container CONTAINER >
   comparable_eq_list_base< TYPE, ARG_TYPE, LIST_BASE > operator -(const CONTAINER & container) const;


};


//template < class TYPE, class ARG_TYPE, class LIST_BASE>
//comparable_eq_list_base<  TYPE,  ARG_TYPE,  LIST_BASE>::
//comparable_eq_list_base()
//{
//
//}


//template < class TYPE, class ARG_TYPE, class LIST_BASE>
//comparable_eq_list_base<  TYPE,  ARG_TYPE,  LIST_BASE>::
//comparable_eq_list_base(const comparable_eq_list_base<  TYPE,  ARG_TYPE,  LIST_BASE> & l) :
//LIST_BASE(l)
//{
//
//}


template <class TYPE, class ARG_TYPE, class LIST_BASE>
typename comparable_eq_list_base < TYPE, ARG_TYPE, LIST_BASE >::iterator comparable_eq_list_base < TYPE, ARG_TYPE, LIST_BASE >::
find_first_item(const TYPE & t, iterator p, iterator end) const
{

   if(!p)
   {

      p = this->begin();

   }

   while(!::iterator_is_end(p, end))
   {

      if(*p == t)
      {

         return p;

      }

      p++;

   }

   return nullptr;

}


template <class TYPE, class ARG_TYPE, class LIST_BASE>
typename comparable_eq_list_base < TYPE, ARG_TYPE, LIST_BASE >::iterator comparable_eq_list_base < TYPE, ARG_TYPE, LIST_BASE >::
find_last_item(const TYPE & t, iterator start, iterator p) const
{

   if(!p)
   {

      p = this->end();

   }

   while(p && p != start)
   {

      if(*p == t)
      {

         return p;

      }

      p--;
   }

   return nullptr;

}


template <class TYPE, class ARG_TYPE, class LIST_BASE>
inline ::collection::count comparable_eq_list_base < TYPE, ARG_TYPE, LIST_BASE >::
get_count() const
{

   return LIST_BASE::get_count();

}


template <class TYPE, class ARG_TYPE, class LIST_BASE>
::collection::count comparable_eq_list_base < TYPE, ARG_TYPE, LIST_BASE >::
get_count(const TYPE & t, iterator start, iterator end, ::collection::count countMax) const
{

   ::collection::count count = 0;

   while((countMax >= 0 && count <= countMax) && (start = find_first_item(t, start, end)))
   {

      count++;

   }

   return count;

}


template <class TYPE, class ARG_TYPE, class LIST_BASE>
bool comparable_eq_list_base < TYPE, ARG_TYPE, LIST_BASE >::
contains(const TYPE & t, iterator p, iterator end, ::collection::count countMin, ::collection::count countMax) const
{

   ::collection::count count = 0;

   while((count < countMin || (countMax >= 0 && count <= countMax)) && (p = find_first_item(t, p, end)))
   {

      count++;

   }
   
   return count >= countMin && conditional(countMax >= 0, count <= countMax);

}


template <class TYPE, class ARG_TYPE, class LIST_BASE>
bool comparable_eq_list_base < TYPE, ARG_TYPE, LIST_BASE >::
rear_contains(const TYPE & t, iterator p, iterator end, ::collection::count countMin, ::collection::count countMax) const
{

   ::collection::count count = 0;

   while((count < countMin || (countMax >= 0 && count <= countMax))  && (p = find_last_item(t, p, end)))
   {

      count++;

   }

   return count >= countMin && conditional(countMax >= 0, count <= countMax);

}


template <class TYPE, class ARG_TYPE, class LIST_BASE>
bool comparable_eq_list_base<TYPE, ARG_TYPE, LIST_BASE>::add_tail_unique(ARG_TYPE t)
{

   if(contains(t))
   {

      return false;

   }

   this->add_tail(t);

   return true;

}


template <class TYPE, class ARG_TYPE, class LIST_BASE>
bool comparable_eq_list_base<TYPE, ARG_TYPE, LIST_BASE>::add_head_unique(ARG_TYPE t)
{

   if(contains(t))
   {

      return false;

   }

   this->add_head(t);

   return true;

}


template <class TYPE, class ARG_TYPE, class LIST_BASE>
template < primitive_container CONTAINER >
void comparable_eq_list_base<TYPE, ARG_TYPE, LIST_BASE>::
intersect(const CONTAINER & container)
{

   auto p = this->begin();

   while(p)
   {

      if (!::contains(container, *p))
      {

         this->erase_defer_next(p);

      }
      else
      {

         p++;

      }

   }

}


template <class TYPE, class ARG_TYPE, class LIST_BASE>
template < primitive_container CONTAINER >
void comparable_eq_list_base<TYPE, ARG_TYPE, LIST_BASE>::
merge_tail(const CONTAINER & container)
{

   for (auto& item : container)
   {

      this->add_tail_unique(item);

   }

}


template <class TYPE, class ARG_TYPE, class LIST_BASE>
template < primitive_container CONTAINER >
void comparable_eq_list_base<TYPE, ARG_TYPE, LIST_BASE>::
merge_head(const CONTAINER & container)
{

   for (auto& item : container)
   {

      this->add_head_unique(item);

   }

}



template <class TYPE, class ARG_TYPE, class LIST_BASE>
template < primitive_container CONTAINER >
inline comparable_eq_list_base<TYPE, ARG_TYPE, LIST_BASE> &  comparable_eq_list_base<TYPE, ARG_TYPE, LIST_BASE>::
operator &= (const CONTAINER & container)
{

   this->intersect(container);

   return *this;

}


template <class TYPE, class ARG_TYPE, class LIST_BASE>
inline comparable_eq_list_base<TYPE, ARG_TYPE, LIST_BASE> &  comparable_eq_list_base<TYPE, ARG_TYPE, LIST_BASE>::
operator -= (const TYPE & t)
{

   this->erase(t);

   return *this;

}


template <class TYPE, class ARG_TYPE, class LIST_BASE>
template < primitive_container CONTAINER >
inline comparable_eq_list_base<TYPE, ARG_TYPE, LIST_BASE> &  comparable_eq_list_base<TYPE, ARG_TYPE, LIST_BASE>::
operator -= (const CONTAINER & container)
{

   this->erase(container);

   return *this;

}


template <class TYPE, class ARG_TYPE, class LIST_BASE>
template < primitive_container CONTAINER >
inline comparable_eq_list_base<TYPE, ARG_TYPE, LIST_BASE> comparable_eq_list_base<TYPE, ARG_TYPE, LIST_BASE>::
operator - (const CONTAINER & container) const
{

   auto list = *this;

   list.erase(container);

   return ::transfer(list);

}


template <class TYPE, class ARG_TYPE, class LIST_BASE>
template < primitive_container CONTAINER >
inline comparable_eq_list_base<TYPE, ARG_TYPE, LIST_BASE> &  comparable_eq_list_base<TYPE, ARG_TYPE, LIST_BASE>::
operator |= (const CONTAINER & container)
{

   this->merge_tail(container);

   return *this;

}


template <class TYPE, class ARG_TYPE, class LIST_BASE>
bool comparable_eq_list_base < TYPE, ARG_TYPE , LIST_BASE >::
erase_first(const TYPE & t)
{

   iterator p = this->find_first_item(t);

   if (!p)
   {

      return false;

   }

   this->erase(p);

   return true;

}


template <class TYPE, class ARG_TYPE, class LIST_BASE>
bool comparable_eq_list_base < TYPE, ARG_TYPE , LIST_BASE >::erase_first(const TYPE & t, iterator & p, iterator end)
{

   if((p = this->find_first_item(t, p, end)))
   {

      auto pErase = p;

      p++;

      this->erase(pErase);

      return true;

   }

   return false;

}


//template <class TYPE, class ARG_TYPE, class LIST_BASE>
//::collection::count comparable_eq_list_base < TYPE, ARG_TYPE , LIST_BASE >::
//erase(const TYPE & t, iterator p, iterator end, ::collection::count countMin, ::collection::count countMax)
//{
//
//   ::collection::count count = 0;
//
//   if(contains(t, p, end, countMin, countMax))
//   {
//
//      while (conditional(countMax >= 0, count < countMax) && erase_first(t, p, end))
//      {
//
//         count++;
//
//      }
//
//   }
//
//   return count;
//
//}



template<class TYPE, class ARG_TYPE, class LIST_BASE>
::collection::count comparable_eq_list_base<TYPE, ARG_TYPE, LIST_BASE>::erase(const TYPE &t, iterator p, iterator end)
{

   if (!p)
   {

      p = this->m_begin;

   }

   // if (!end)
   // {
   //
   //    end = this->m_end;
   //
   // }

   ::collection::count count = 0;

   while (!::iterator_is_end(p, end))
   {

      if (*p == t)
      {

         auto pNext = p + 1;

         this->erase(p);

         p = pNext;

         count++;

      }
      else
      {

         p++;

      }






   }

   return count;
}


template <class TYPE, class ARG_TYPE, class LIST_BASE>
bool comparable_eq_list_base < TYPE, ARG_TYPE , LIST_BASE >::
erase_last(const TYPE & t)
{

   auto p = find_last_item(t);

   if(p)
   {

      this->erase(p);

      return true;

   }

   return false;

}


template <class TYPE, class ARG_TYPE, class LIST_BASE>
bool comparable_eq_list_base < TYPE, ARG_TYPE , LIST_BASE >::
erase_last(const TYPE & t, iterator & p, iterator end)
{

   if((p = find_last_item(t, p, end)))
   {

      auto pErase = p;

      p--;

      this->erase(pErase);

      return true;

   }

   return false;

}


//template <class TYPE, class ARG_TYPE, class LIST_BASE>
//::collection::count comparable_eq_list_base < TYPE, ARG_TYPE , LIST_BASE >::
//rear_erase(const TYPE & t, iterator p, iterator end, ::collection::count countMin, ::collection::count countMax)
//{
//
//   ::collection::count count = 0;
//
//   if(contains(t, p, end, countMin, countMax))
//   {
//
//      while (conditional(countMax >= 0, count < countMax) && erase_last(t, p, end))
//      {
//
//         count++;
//
//      }
//
//   }
//
//   return count;
//
//}


template <class TYPE, class ARG_TYPE, class LIST_BASE>
template < primitive_container CONTAINER >
::collection::count comparable_eq_list_base < TYPE, ARG_TYPE , LIST_BASE >::erase(const CONTAINER & container)
{

   ::collection::count count = 0;

   for(auto & item : container)
   {

      count += this->erase_item(item);

   }

   return count;

}



