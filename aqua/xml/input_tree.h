#pragma once


#include "tree_base.h"
#include "node.h"


namespace xml
{


   class importable;
   class attribute_array;


   class CLASS_DECL_AQUA input_tree :
      public tree_base
   {
   public:


      ::pointer<::xml::document>    m_pdocument;
      ::pointer<::xml::node>        m_pnode;


      input_tree();
      input_tree(const ::scoped_string & scopedstrXml);
      input_tree(tree_schema * pschema);
      ~input_tree() override;


      virtual ::xml::node * import_node(const ::scoped_string & scopedstrName, importable & importable);

      virtual ::xml::node * import_node(const ::scoped_string & scopedstrName, ::property_set & set, importable & importable);

      virtual ::xml::node * import_node(const ::scoped_string & scopedstrName, ::payload & payload);



      template < typename TYPE >
      bool load_attribute(const ::atom & atom, TYPE & t, const ::payload & payload = e_type_new)
      {

         if (m_pnode->_get_attribute(atom, t))
         {

            return true;

         }

         t = payload;

         return false;

      }

      //virtual bool load_attr(const ::scoped_string & scopedstrName, bool & b);

      //virtual bool load_attr(const ::scoped_string & scopedstrName, double & d);

      //virtual bool load_attr(const ::scoped_string & scopedstrName, int & iValue);

      //virtual bool get_attr(const ::scoped_string & scopedstrName, string & strValue, const ::scoped_string & scopedstrDefault = "");

      //virtual bool get_attr(const ::scoped_string & scopedstrName, bool & b, bool bDefault = false);

      //virtual bool get_attr(const ::scoped_string & scopedstrName, double & d, double dDefault = 0.0);

      //virtual bool get_attr(const ::scoped_string & scopedstrName, int & iValue, int iDefault = 0);

      virtual void get_value(string & strValue);

   };


} // namespace xml





