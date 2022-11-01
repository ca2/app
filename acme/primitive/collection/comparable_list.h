#pragma once



template < class TYPE, class ARG_TYPE = const TYPE &, class LIST_TYPE = comparable_eq_list < TYPE, ARG_TYPE > >
class comparable_list :
   public LIST_TYPE
{
public:
   comparable_list();
   comparable_list(const comparable_list & array);

   void quick_sort(bool bAsc = true);

   TYPE maximum(TYPE minimum);

 

};

template < class TYPE, class ARG_TYPE, class LIST_TYPE>
comparable_list<  TYPE,  ARG_TYPE,  LIST_TYPE>::
comparable_list()
{
}


template < class TYPE, class ARG_TYPE, class LIST_TYPE>
comparable_list<  TYPE,  ARG_TYPE,  LIST_TYPE>::
comparable_list(const comparable_list<  TYPE,  ARG_TYPE,  LIST_TYPE> & l) :
LIST_TYPE(l)
{

}


template < class TYPE, class ARG_TYPE, class LIST_TYPE>
TYPE comparable_list<  TYPE,  ARG_TYPE,  LIST_TYPE>::
maximum(TYPE maximum)
{

   auto pnode = this->get_head();
   
   while(pnode != nullptr)
   {

      if(pnode->m_value > maximum)
      {

         maximum = pnode->m_value;

      }

      pnode = pnode->m_pnext;

   }

   return maximum;

}



#include "sort.h"





template < class TYPE, class ARG_TYPE, class ARRAY_TYPE>
void comparable_list<  TYPE,  ARG_TYPE,  ARRAY_TYPE>::
quick_sort(bool bAscendent)
{

   sort::quick_sort(*this, bAscendent);

}
