#include "framework.h"
#include "input_tree.h"
#include "document.h"
////#include "acme/exception/exception.h"


namespace xml
{


   input_tree::input_tree(const ::string & strXml)
   {

      m_pdocument = __new(::xml::document);

      m_pdocument->load(strXml);

   }


   input_tree::input_tree()
   {

      m_pdocument = __new(::xml::document);

   }


   input_tree::input_tree(tree_schema * pschema) :
      tree_base(pschema)
   {

      m_pdocument = __new(::xml::document);

   }


   input_tree::~input_tree()
   {

   }


   node * input_tree::import_node(const ::string & strName, importable & importable)
   {

      node * pnodePrev = m_pnode;

      if(!m_pnode)
      {

         m_pnode = m_pdocument->root();

         string strNodeName;

         strNodeName = m_pnode->get_name();

         if(strNodeName != strName)
         {
            
            m_pnode = nullptr;
            
            throw ::exception(error_failed, "Node not found");

         }
         
         importable.xml_import(*this);

         return m_pdocument->root();

      }
      else
      {

         node * pnode = m_pnode->get_child(strName);

         m_pnode = pnode;

         importable.xml_import(*this);

         m_pnode = pnodePrev;

         return pnode;

      }
   }


   node * input_tree::import_node(const ::string & strName, property_set & set, importable & importable)
   {

      node * pnodePrev = m_pnode;

      if(!m_pnode)
      {

         m_pnode = m_pdocument->root();

         if(m_pnode->get_name() != strName)
         {

            ASSERT(false);

            m_pnode = nullptr;

            throw ::exception(error_failed, "Node not found");

         }

         if (!m_pnode->contains(set))
         {

            return ((node *) nullptr);

         }

         importable.xml_import(*this);

         return m_pdocument->root();

      }
      else
      {

         node * pnode = m_pnode->child_at(m_pnode->find(strName, set));

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


   node * input_tree::import_node(const ::string & strName, ::payload & payload)
   {

      m_varexchange.m_ppayload = &payload;

      return import_node(strName, m_varexchange);

   }


} // namespace xml



