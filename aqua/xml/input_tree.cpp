#include "framework.h"
#include "input_tree.h"
#include "document.h"
////#include "acme/exception/exception.h"


namespace xml
{


   input_tree::input_tree(const ::scoped_string & scopedstrXml)
   {

      m_pdocument = __allocate ::xml::document();

      m_pdocument->load(scopedstrXml);

   }


   input_tree::input_tree()
   {

      m_pdocument = __allocate ::xml::document();

   }


   input_tree::input_tree(tree_schema * pschema) :
      tree_base(pschema)
   {

      m_pdocument = __allocate ::xml::document();

   }


   input_tree::~input_tree()
   {

   }


   ::xml::node * input_tree::import_node(const ::scoped_string & scopedstrName, importable & importable)
   {

      ::xml::node * pnodePrev = m_pnode;

      if(!m_pnode)
      {

         m_pnode = m_pdocument->root();

         string strNodeName;

         strNodeName = m_pnode->get_name();

         if(strNodeName != scopedstrName)
         {
            
            m_pnode = nullptr;
            
            throw ::exception(error_failed, "Node not found");

         }
         
         importable.xml_import(*this);

         return m_pdocument->root();

      }
      else
      {

         ::xml::node * pnode = m_pnode->get_child(scopedstrName);

         m_pnode = pnode;

         importable.xml_import(*this);

         m_pnode = pnodePrev;

         return pnode;

      }
   }


   node * input_tree::import_node(const ::scoped_string & scopedstrName, ::property_set & set, importable & importable)
   {

      ::xml::node * pnodePrev = m_pnode;

      if(!m_pnode)
      {

         m_pnode = m_pdocument->root();

         if(m_pnode->get_name() != scopedstrName)
         {

            ASSERT(false);

            m_pnode = nullptr;

            throw ::exception(error_failed, "Node not found");

         }

         if (!m_pnode->contains(set))
         {

            return ((::xml::node *) nullptr);

         }

         importable.xml_import(*this);

         return m_pdocument->root();

      }
      else
      {

         ::xml::node * pnode = m_pnode->child_at(m_pnode->find(scopedstrName, set));

         m_pnode = pnode;

         importable.xml_import(*this);

         m_pnode = pnodePrev;

         return pnode;

      }

   }


   void input_tree::get_value(string & strValue)
   {

      strValue = m_pnode->get_value();

   }


   ::xml::node * input_tree::import_node(const ::scoped_string & scopedstrName, ::payload & payload)
   {

      m_varexchange.m_ppayload = &payload;

      return import_node(scopedstrName, m_varexchange);

   }


} // namespace xml



