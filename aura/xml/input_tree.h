#pragma once


namespace xml
{


   class importable;
   class attribute_array;


   class CLASS_DECL_AURA input_tree :
      public tree_base
   {
   public:


      __pointer(::xml::document)     m_pdocument;
      __pointer(::xml::node)         m_pnode;


      input_tree(::object * pobjectContext, const string & strXml);
      input_tree(::object * pobjectContext);
      input_tree(::object * pobjectContext, tree_schema * pschema);
      virtual ~input_tree();


      virtual node * import_node(const char * pcszName, importable & importable);

      virtual node * import_node(const char * pcszName, property_set & set, importable & importable);

      virtual node * import_node(const char * pcszName, var & var);



      template < typename TYPE >
      bool load_attribute(const ::id & id, TYPE & t, const var & var = type_new)
      {

         if (m_pnode->find_attribute(id, t))
         {

            return true;

         }

         t = var;

         return false;

      }

      //virtual bool load_attr(const char * pcszName, bool & b);

      //virtual bool load_attr(const char * pcszName, double & d);

      //virtual bool load_attr(const char * pcszName, i32 & iValue);

      //virtual bool get_attr(const char * pcszName, string & strValue, string strDefault = "");

      //virtual bool get_attr(const char * pcszName, bool & b, bool bDefault = false);

      //virtual bool get_attr(const char * pcszName, double & d, double dDefault = 0.0);

      //virtual bool get_attr(const char * pcszName, i32 & iValue, int iDefault = 0);

      virtual void get_value(string & strValue);

   };


} // namespace xml





