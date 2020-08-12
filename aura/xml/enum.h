#pragma once


namespace xml
{

   
   enum e_node
   {
      
      node_element,     // general node '<element>...</element>' or <element/>
      node_pi,          // <?xml version="1.0" ?>
      node_comment,     // <!-- comment -->
      node_cdata,       // <![CDATA[ cdata ]]>
      node_document,    // internal virtual root
      node_text        // special node_element - final node element
         
   };


   enum e_parse_error
   {
      
      parse_error_welformed = 0,
      parse_error_alone_not_closed,
      parse_error_not_closed,
      parse_error_not_nested,
      parse_error_attr_no_value
         
   };
   

} //namespace xml




