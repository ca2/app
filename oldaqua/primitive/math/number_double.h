#pragma once


//#include "math_value.h"


namespace math
{


   class CLASS_DECL_AQUA number_double :
      virtual public value_impl
   {
   public:

      virtual void set_value_string(const char * psz);
      virtual string get_value_string();


   };

   
   CLASS_DECL_AQUA bool convert_to_double(double & d, string str);


} // namespace math



