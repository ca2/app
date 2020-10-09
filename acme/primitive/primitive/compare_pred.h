#pragma once


template < typename ARG_TYPE >
class less_pred_base :
   virtual public element
{
public:

   virtual int less(ARG_TYPE a1, ARG_TYPE a2) = 0;

};


template < typename ARG_TYPE, typename PRED >
class less_pred :
   public less_pred_base < ARG_TYPE >
{
public:


   PRED m_pred;


   less_pred(PRED pred) : m_pred(pred) {}

   virtual int less(ARG_TYPE a1, ARG_TYPE a2)
   {

      return m_pred(a1, a2);

   }

};