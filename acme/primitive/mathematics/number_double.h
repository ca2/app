#pragma once


#include "value.h"


namespace mathematics
{


   class CLASS_DECL_ACME number_double :
      virtual public value_impl
   {
   public:

      virtual void set_value_string(const scoped_string & str);
      virtual string get_value_string();


   };

   
   CLASS_DECL_ACME bool convert_to_double(double & d, string str);


} // namespace mathematics



