#pragma once


//#include "math_value.h"


namespace mathematics
{


   class CLASS_DECL_ACME number_float :
      virtual public value_impl
   {
   public:

      virtual void set_value_string(const char * psz);
      virtual string get_value_string();
   };


} // namespace mathematics



