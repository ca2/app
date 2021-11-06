#pragma once

template < class TYPE, class ARG_TYPE  = const TYPE&, class LIST_TYPE = ::list < TYPE, ARG_TYPE > >
class comparable_eq_list :
   public LIST_TYPE
{
public:

   using node = typename ::list < TYPE, ARG_TYPE >::node;

   comparable_eq_list();
   comparable_eq_list(const comparable_eq_list & array);

   node * find_first(const TYPE &t, node * pnode = nullptr, node * pnodeLast = nullptr) const;
   node * find_last(const TYPE &t, node * pnode = nullptr, node * pnodeLast = nullptr) const;
   ::count get_count() const;
   ::count get_count(const TYPE & t, node * start = nullptr, node * pnodeLast = nullptr, ::count countMax = -1) const;
   bool contains(const TYPE & t, node * pnodeStart = nullptr, node * pnodeLast = nullptr, ::count countMin = 1, ::count countMax = -1) const;
   bool rcontains(const TYPE & t, node * pnodeStart = nullptr, node * pnodeLast = nullptr, ::count countMin = 1, ::count countMax = -1) const;
   bool erase_first(const TYPE & t);
   bool erase_last(const TYPE & t);
   bool erase_first(const TYPE & t, node * & pnode, node * pnodeLast = nullptr);
   bool erase_last(const TYPE & t, node * & pnode, node * pnodeLast = nullptr);
   ::count erase(const TYPE & t, node * pnode = nullptr, node * pnodeLast = nullptr, ::count countMin = 0, ::count countMax = -1);
   ::count rerase(const TYPE & t, node * pnode = nullptr, node * pnodeLast = nullptr, ::count countMin = 0, ::count countMax = -1);
   ::count erase(const comparable_eq_list & l);



   // add
   bool add_tail_unique(ARG_TYPE t);
   bool add_head_unique(ARG_TYPE t);


   // set
   void merge_tail(const comparable_eq_list & l); // add_tail
   void merge_head(const comparable_eq_list & l); // add_tail
   void intersect(const comparable_eq_list & l);

   // set operators
   comparable_eq_list< TYPE, ARG_TYPE, LIST_TYPE > & operator -= (const TYPE & t);
   comparable_eq_list< TYPE, ARG_TYPE, LIST_TYPE > & operator &= (const comparable_eq_list< TYPE, ARG_TYPE, LIST_TYPE > & l);
   comparable_eq_list< TYPE, ARG_TYPE, LIST_TYPE > & operator -= (const comparable_eq_list< TYPE, ARG_TYPE, LIST_TYPE > & l);
   comparable_eq_list< TYPE, ARG_TYPE, LIST_TYPE > & operator |= (const comparable_eq_list< TYPE, ARG_TYPE, LIST_TYPE > & l); // add_tail

   comparable_eq_list< TYPE, ARG_TYPE, LIST_TYPE > operator -(const comparable_eq_list< TYPE, ARG_TYPE, LIST_TYPE > & l) const;

   //// helper functions (note: O(n) speed)
   //iterator pnodeFind(ARG_TYPE searchValue, iterator startAfter = nullptr);
   //// defaults to starting at the HEAD, return nullptr if not found
   //void erase(ARG_TYPE elem);


   //const_iterator pnodeFind(ARG_TYPE searchValue, const_iterator startAfter = nullptr) const
   //{

   //   return ((comparable_list *) this)->pnodeFind(searchValue, startAfter);

   //}

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
typename comparable_eq_list < TYPE, ARG_TYPE, LIST_TYPE >::node * comparable_eq_list < TYPE, ARG_TYPE, LIST_TYPE >::
find_first(const TYPE & t, node * pnode, node * pnodeLast) const
{
   if(pnode == nullptr)
      pnode = this->get_head();
   if(pnode == nullptr)
      pnode = this->get_tail();
   while(pnode)
   {
      if(pnode->m_value == t)
         return pnode;
      if(pnode == pnodeLast)
         break;
      pnode = pnode->m_pnext;
   }
   return nullptr;
}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
typename comparable_eq_list < TYPE, ARG_TYPE, LIST_TYPE >::node * comparable_eq_list < TYPE, ARG_TYPE, LIST_TYPE >::
find_last(const TYPE & t, node * pnode, node * pnodeLast) const
{
   if(pnode == nullptr)
      pnode = this->get_tail();
   if(pnode == nullptr)
      pnode = this->get_head();
   while(pnode)
   {
      if(pnode->m_value == t)
         return pnode;
      if(pnode == pnodeLast)
         break;
      pnode->m_pprevious;
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
get_count(const TYPE & t, node * pnodeFind, node * pnodeLast, ::count countMax) const
{
   ::count count = 0;
   while((countMax >= 0 && count <= countMax)
      && (pnodeFind = find_first(t, pnodeFind, pnodeLast)) >= 0)
      count++;
   return count;
}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
bool comparable_eq_list < TYPE, ARG_TYPE, LIST_TYPE >::
contains(const TYPE & t, node * pnodeFind, node * pnodeLast, ::count countMin, ::count countMax) const
{
   ::count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax))
      && (pnodeFind = find_first(t, pnodeFind, pnodeLast)) != nullptr)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
bool comparable_eq_list < TYPE, ARG_TYPE, LIST_TYPE >::
rcontains(const TYPE & t, node * pnodeFind, node * pnodeLast, ::count countMin, ::count countMax) const
{
   ::count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax))
      && (pnodeFind = find_last(t, pnodeFind, pnodeLast)) != nullptr)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
bool comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE>::add_tail_unique(ARG_TYPE t)
{
   if(contains(t))
      return false;
   this->add_tail(t);
   return true;
}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
bool comparable_eq_list<TYPE, ARG_TYPE, LIST_TYPE>::add_head_unique(ARG_TYPE t)
{
   if(contains(t))
      return false;
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
erase_first(const TYPE & t)
{
   node * pnodeFind = this->find_first(t);
   if(pnodeFind != nullptr)
   {
      this->erase_item(pnodeFind);
      return true;
   }
   return false;
}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
bool comparable_eq_list < TYPE, ARG_TYPE , LIST_TYPE >::
erase_first(const TYPE & t, node * & pnodeFind, node * pnodeLast)
{
   if((pnodeFind = this->find_first(t, pnodeFind, pnodeLast)) != nullptr)
   {
      node * pnodeRemove = pnodeFind;
      pnodeFind = pnodeFind->m_pnext;
      this->erase_item(pnodeRemove);
      return true;
   }
   return false;
}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
::count comparable_eq_list < TYPE, ARG_TYPE , LIST_TYPE >::
erase(const TYPE & t, node * pnodeFind, node * pnodeLast, ::count countMin, ::count countMax)
{
   ::count count = 0;
   if(contains(t, pnodeFind, pnodeLast, countMin, countMax))
      while(conditional(countMax >= 0, count < countMax) && erase_first(t, pnodeFind, pnodeLast))
         count++;
   return count;
}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
bool comparable_eq_list < TYPE, ARG_TYPE , LIST_TYPE >::
erase_last(const TYPE & t)
{
   node * pnodeFind = find_last(t);
   if(pnodeFind != nullptr)
   {
      this->erase_item(pnodeFind);
      return true;
   }
   return false;
}


template <class TYPE, class ARG_TYPE, class LIST_TYPE>
bool comparable_eq_list < TYPE, ARG_TYPE , LIST_TYPE >::
erase_last(const TYPE & t, node * & pnodeFind, node * pnodeLast)
{
   if((pnodeFind = find_last(t, pnodeFind, pnodeLast)) != nullptr)
   {
      node * pnodeRemove = pnodeFind;
      pnodeFind = pnodeFind->m_pprevious;
      this->erase_item(pnodeRemove);
      return true;
   }
   return false;
}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
::count comparable_eq_list < TYPE, ARG_TYPE , LIST_TYPE >::
rerase(const TYPE & t, node * pnodeFind, node * pnodeLast, ::count countMin, ::count countMax)
{
   ::count count = 0;
   if(contains(t, pnodeFind, pnodeLast, countMin, countMax))
      while(conditional(countMax >= 0, count < countMax) && erase_last(t, pnodeFind, pnodeLast))
         count++;
   return count;
}

template <class TYPE, class ARG_TYPE, class LIST_TYPE>
::count comparable_eq_list < TYPE, ARG_TYPE , LIST_TYPE >::erase(const comparable_eq_list & l)
{

   ::count count = 0;

   auto pnode = l.get_head();

   while(pnode != nullptr)
   {

      count += erase(pnode->m_value);

      pnode = pnode->m_pnext;

   }

   return count;

}
