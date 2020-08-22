#pragma once


//#include "math_value.h"


namespace math
{


   class CLASS_DECL_AURA binary_operation :
      virtual public value
   {
   public:


      enum e_type
      {
         type_addition,
         type_subtraction,
         type_multiplication,
         type_division,
      };


      e_type m_etype;


      value * m_pvalue1;
      value * m_pvalue2;


      binary_operation();
      virtual ~binary_operation();


      virtual void set_value_string(const char * psz);
      virtual string get_value_string(e_get_value egetvalue);


   };


} // namespace math



