#pragma once


namespace xml
{

   
   enum enum_parse_error
   {
      
      e_parse_error_welformed = 0,
      e_parse_error_alone_not_closed,
      e_parse_error_not_closed,
      e_parse_error_not_nested,
      e_parse_error_attr_no_value
         
   };
   

} //namespace xml




