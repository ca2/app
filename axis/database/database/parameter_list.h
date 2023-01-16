// From definition.h by camilo on 2022-09-06 17:22 <3ThomasBorregaardSørensen!!
#pragma once


//#include "acme/primitive/primitive/payload.h"


namespace database
{


   class CLASS_DECL_AXIS parameter_list
   {
   public:


      string_array        m_stra;
      row            m_row;


      ::payload & get_value(index i);
      const char * get_key(index i);
      ::count get_size();
      bool is_empty();

      parameter_list & operator = (const parameter_list & paramlist);


   };


} // namespace database



