#pragma once


//#include "math_value.h"


namespace math
{


   class CLASS_DECL_AURA number_float :
      virtual public value_impl
   {
   public:

      virtual void set_value_string(const char * psz);
      virtual string get_value_string();
   };


} // namespace math



