#pragma once


namespace xml
{

   



   enum e_parse_error
   {
      
      parse_error_welformed = 0,
      parse_error_alone_not_closed,
      parse_error_not_closed,
      parse_error_not_nested,
      parse_error_attr_no_value
         
   };
   

} //namespace xml




