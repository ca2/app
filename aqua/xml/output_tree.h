#pragma once


#include "tree_base.h"


namespace xml
{


   class CLASS_DECL_AQUA output_tree :
      public tree_base
   {
   public:


      ::pointer<::xml::document>       m_pdocument;
      ::pointer<::xml::node>           m_pnode;


      output_tree();
      output_tree(tree_schema * pschema);
      ~output_tree() override;


      void set_attribute(const ::atom & atom, const ::payload & payload);

      //void set_attr(const ::scoped_string & scopedstrName, i64 iValue, bool bOptional = true);

      //void set_bool_attr(const ::scoped_string & scopedstrName, bool bValue, bool bOptional = true);

      //void set_double_attr(const ::scoped_string & scopedstrName, double dValue);

      void set_value(const ::scoped_string & scopedstrValue);

      virtual ::xml::node * export_node(exportable & exportable);
      virtual ::xml::node * export_node(const ::string & strName, exportable & exportable);

      virtual ::xml::node * export_node(const ::string & strName, ::payload payload);


      virtual void set_node_name(const ::string & strName);


   };


}   // namespace xml


