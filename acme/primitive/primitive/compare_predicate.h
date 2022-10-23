#pragma once


template < typename ARG_TYPE >
class less_predicate_base :
   virtual public particle
{
public:

   virtual int less(ARG_TYPE a1, ARG_TYPE a2) = 0;

};


template < typename ARG_TYPE, typename PRED >
class less_predicate :
   public less_predicate_base < ARG_TYPE >
{
public:


   PRED m_predicate;


   less_predicate(PRED pred) : m_predicate(pred) {}

   virtual int less(ARG_TYPE a1, ARG_TYPE a2)
   {

      return m_predicate(a1, a2);

   }

};
