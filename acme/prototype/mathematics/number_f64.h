#pragma once


#include "value.h"


namespace mathematics
{


   class CLASS_DECL_ACME number_f64 :
      virtual public value_impl
   {
   public:

      virtual void set_value_string(const ::scoped_string & scopedstr);
      virtual string get_value_string();


   };

   
   CLASS_DECL_ACME bool convert_to_f64(::f64 & d, const ::scoped_string & scopedstr);


} // namespace mathematics



