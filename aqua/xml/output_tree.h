#pragma once


namespace xml
{


   class CLASS_DECL_AQUA output_tree :
      public tree_base
   {
   public:


      __pointer(::xml::document)     m_pdocument;
      __pointer(node)                m_pnode;


      output_tree();
      output_tree(tree_schema * pschema);
      virtual ~output_tree();


      void set_attribute(const ::atom & atom, const ::payload & payload);

      //void set_attr(const char * pcszName, i64 iValue, bool bOptional = true);

      //void set_bool_attr(const char * pcszName, bool bValue, bool bOptional = true);

      //void set_double_attr(const char * pcszName, double dValue);

      void set_value(const char * pszValue);

      virtual node * export_node(exportable & exportable);
      virtual node * export_node(const char * pcszName, exportable & exportable);

      virtual node * export_node(const char * pcszName, ::payload payload);


      virtual void SetNodeName(const char * pcszName);





   };


}   // namespace xml


