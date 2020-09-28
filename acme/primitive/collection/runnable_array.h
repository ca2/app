#pragma once


class CLASS_DECL_ACME runnable_array :
   public __pointer_array(elemental)
{
public:

   using __pointer_array(elemental)::pointer_array;

   template < typename PRED >
   runnable_array & operator +=(PRED pred);

};




