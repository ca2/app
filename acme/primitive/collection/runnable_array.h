#pragma once


class CLASS_DECL_ACME runnable_array :
   public __pointer_array(element)
{
public:

   using __pointer_array(element)::pointer_array;

   template < typename PRED >
   runnable_array & operator +=(PRED pred);

};




