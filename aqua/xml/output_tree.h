#pragma once


#include "tree_base.h"


namespace xml
{


   class CLASS_DECL_AQUA output_tree :
      public tree_base
   {
   public:


      ::pointer<::xml::document>    m_pdocument;
      ::pointer<node>               m_pnode;


      output_tree();
      output_tree(tree_schema * pschema);
      virtual ~output_tree();


      void set_attribute(const ::atom & atom, const ::payload & payload);

      //void set_attr(const char * pcszName, i64 iValue, bool bOptional = true);

      //void set_bool_attr(const char * pcszName, bool bValue, bool bOptional = true);

      //void set_double_attr(const char * pcszName, double dValue);

      void set_value(const scoped_string & strValue);

      virtual node * export_node(exportable & exportable);
      virtual node * export_node(const ::string & strName, exportable & exportable);

      virtual node * export_node(const ::string & strName, ::payload payload);


      virtual void set_node_name(const ::string & strName);


   };


}   // namespace xml


