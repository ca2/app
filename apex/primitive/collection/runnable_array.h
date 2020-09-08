#pragma once


class CLASS_DECL_APEX runnable_array :
   public __pointer_array(context_object)
{
public:

   using __pointer_array(context_object)::pointer_array;

   template < typename PRED >
   runnable_array & operator +=(PRED pred);

};




