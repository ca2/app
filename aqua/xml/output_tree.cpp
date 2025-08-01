#include "framework.h"
#include "output_tree.h"
#include "document.h"
////#include "acme/exception/exception.h"


namespace xml
{


   output_tree::output_tree()
   {

      m_pdocument = nullptr;
      m_pnode = nullptr;

   }


   output_tree::output_tree(tree_schema * pschema) :
      tree_base(pschema)
   {
      
      m_pdocument = nullptr;
      m_pnode = nullptr;

   }


   output_tree::~output_tree()
   {
   }


   ::xml::node * output_tree::export_node(const ::scoped_string & scopedstrName, exportable & exportable)
   {

      if(m_pnode == nullptr)
      {
         
         if(m_pdocument == nullptr)
         {
         
            throw ::exception(error_failed, "Cannot output to a nullptr document");

         }

         m_pnode = m_pdocument->root();
         m_pnode->set_name(scopedstrName);

         exportable.xml_export(*this);

         return m_pdocument->root();

      }
      else
      {

         ::xml::node * pnodePrev = m_pnode;

         ::xml::node * pnode = m_pnode->add_child(scopedstrName);

         m_pnode = pnode;

         exportable.xml_export(*this);

         m_pnode = pnodePrev;

         return pnode;

      }

   }


   ::xml::node * output_tree::export_node(exportable & exportable)
   {

      return export_node("", exportable);

   }


   ::xml::node * output_tree::export_node(const ::scoped_string & scopedstrName, ::payload payload)
   {

      m_varexchange.m_ppayload = &payload;

      return export_node(scopedstrName, m_varexchange);

   }


   void output_tree::set_attribute(const ::atom & atom, const ::payload & payload)
   {

      m_pnode->set_attribute(atom, payload);

   }


   //void output_tree::set_attr(const ::scoped_string & scopedstrName, long long iValue, bool bOptional)

   //{
   //   if (iValue == 0 && bOptional)
   //      return;
   //   m_pnode->set_attr(pcszName, iValue);

   //}

   //void output_tree::set_bool_attr(const ::scoped_string & scopedstrName, bool bValue, bool bOptional)

   //{
   //   if (!bValue && bOptional)
   //   {
   //      return;
   //   }
   //   m_pnode->set_attr(pcszName, bValue ? 1 : 0);

   //}

   //void output_tree::set_double_attr(const ::scoped_string & scopedstrName, double dValue)

   //{
   //   m_pnode->set_attr(pcszName, as_string(dValue));

   //}


   void output_tree::set_value(const ::scoped_string & scopedstrValue)
   {

      m_pnode->set_value(scopedstrValue);

   }


   void output_tree::set_node_name(const ::scoped_string & scopedstrName)
   {

      m_pnode->set_name(scopedstrName);

   }


} // namespace xml
