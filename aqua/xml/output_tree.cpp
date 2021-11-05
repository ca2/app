#include "framework.h"
#include "aqua/xml.h"


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

   node * output_tree::export_node(const char * pcszName, exportable & exportable)

   {
      if(m_pnode == nullptr)
      {
         
         if(m_pdocument == nullptr)
         {
         
            throw ::exception("Cannot output to a nullptr document");

         }

         m_pnode = m_pdocument->root();
         m_pnode->set_name(pcszName);

         exportable.xml_export(*this);
         return m_pdocument->root();
      }
      else
      {
         node * pnodePrev = m_pnode;
         node * pnode = m_pnode->add_child(pcszName);

         m_pnode = pnode;
         exportable.xml_export(*this);
         m_pnode = pnodePrev;
         return pnode;
      }
   }

   node * output_tree::export_node(exportable & exportable)
   {
      return export_node("", exportable);
   }


   node * output_tree::export_node(const char * pcszName, ::payload payload)

   {
      m_varexchange.m_ppayload = &payload;
      return export_node(pcszName, m_varexchange);

   }


   void output_tree::set_attribute(const ::id & id, const ::payload & payload)
   {

      m_pnode->set_attribute(id, payload);

   }


   //void output_tree::set_attr(const char * pcszName, i64 iValue, bool bOptional)

   //{
   //   if (iValue == 0 && bOptional)
   //      return;
   //   m_pnode->set_attr(pcszName, iValue);

   //}

   //void output_tree::set_bool_attr(const char * pcszName, bool bValue, bool bOptional)

   //{
   //   if (!bValue && bOptional)
   //   {
   //      return;
   //   }
   //   m_pnode->set_attr(pcszName, bValue ? 1 : 0);

   //}

   //void output_tree::set_double_attr(const char * pcszName, double dValue)

   //{
   //   m_pnode->set_attr(pcszName, __string(dValue));

   //}


   void output_tree::set_value(const char * pszValue)
   {

      m_pnode->set_value(pszValue);

   }

   void output_tree::SetNodeName(const char * pcszName)

   {
      m_pnode->set_name(pcszName);

   }

} // namespace xml
