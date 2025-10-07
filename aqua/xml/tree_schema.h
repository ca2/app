#pragma once


//#include "acme/prototype/collection/string_array.h"
////#include "acme/prototype/prototype/object.h"


namespace xml
{


   class CLASS_DECL_AQUA tree_schema :
      virtual public ::object
   {
   public:
   

      string_array_base m_stra;
      
      
      tree_schema();
      virtual ~tree_schema();

      string get_node_name(int iNameIndex);
      void set_node_name(int iNameIndex, const ::scoped_string & scopedstrNodeName);



   };
   

} // namespace xml



