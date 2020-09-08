#pragma once


class CLASS_DECL_ACME runnable_array :
   public __pointer_array(generic)
{
public:

   using __pointer_array(generic)::pointer_array;

   template < typename PRED >
   runnable_array & operator +=(PRED pred);

};




