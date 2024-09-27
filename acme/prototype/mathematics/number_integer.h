#pragma once


#include "value.h"


namespace mathematics
{


   class CLASS_DECL_ACME number_integer :
      virtual public value_impl
   {
   public:



      virtual void set_value_string(const ::scoped_string & scopedstr);
      virtual string get_value_string();


   };


} // namespace mathematics




