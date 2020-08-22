#pragma once


namespace xml
{


   class CLASS_DECL_AXIS output_tree :
      public tree_base
   {
   public:


      __pointer(::xml::document)     m_pdocument;
      __pointer(node)                m_pnode;


      output_tree(::object * pobjectContext, tree_schema * pschema);
      output_tree(::object * pobjectContext);
      virtual ~output_tree();


      void set_attribute(const ::id & id, const var & var);

      //void set_attr(const char * pcszName, i64 iValue, bool bOptional = true);

      //void set_bool_attr(const char * pcszName, bool bValue, bool bOptional = true);

      //void set_double_attr(const char * pcszName, double dValue);

      void set_value(const char * pszValue);

      virtual node * export_node(exportable & exportable);
      virtual node * export_node(const char * pcszName, exportable & exportable);

      virtual node * export_node(const char * pcszName, var var);


      virtual void SetNodeName(const char * pcszName);





   };


}   // namespace xml


