#pragma once


namespace xml
{


   class CLASS_DECL_AQUA tree_schema :
      virtual public ::object
   {
   public:
   

      string_array m_stra;
      
      
      tree_schema();
      virtual ~tree_schema();

      string get_node_name(i32 iNameIndex);
      void set_node_name(i32 iNameIndex, const char * pcszNodeName);



   };
   

} // namespace xml



