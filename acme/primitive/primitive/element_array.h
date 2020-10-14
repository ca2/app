#pragma once


using element_array_base = __pointer_array(element);


class CLASS_DECL_ACME element_array :
   virtual public element_array_base
{
public:


   using element_array_base::element_array_base;


   virtual ~element_array();

   void call_update(::i64 iUpdate);


};



