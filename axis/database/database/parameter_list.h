// From definition.h by camilo on 2022-09-06 17:22 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/prototype/prototype/payload.h"


namespace database
{


   class CLASS_DECL_AXIS parameter_list
   {
   public:


      string_array        m_stra;
      row            m_row;


      ::payload & get_value(::collection::index i);
      const_char_pointer get_key(::collection::index i);
      ::collection::count get_size();
      bool is_empty();

      parameter_list & operator = (const parameter_list & paramlist);


   };


} // namespace database



