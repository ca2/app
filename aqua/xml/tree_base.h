#pragma once


namespace xml
{

   
   class CLASS_DECL_AQUA tree_base :
      virtual public ::object
   {
   public:


      var_exchange   m_varexchange;


      //The schema of the tree
      tree_schema * m_pschema;


      tree_base(tree_schema * pschema);
      tree_base();
      virtual ~tree_base();

      string get_node_name(i32 iNameIndex);

      void set_schema(tree_schema * pschema);
      tree_schema & get_schema();

   
   };

   
} // namespace xml



