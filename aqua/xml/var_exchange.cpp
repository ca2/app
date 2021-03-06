#include "framework.h"
#include "aqua/xml.h"


namespace xml
{

   var_exchange::var_exchange()
   {
      m_pvar = nullptr;
   }

   var_exchange::~var_exchange()
   {

   }

   
   void var_exchange::xml_export(class output_tree & xmlot) const
   {
      
      ASSERT(m_pvar != nullptr);

      if (m_pvar == nullptr)
      {

         return;

      }

      node * pnode = xmlot.m_pnode;

      pnode->set_attribute("type", m_pvar->get_type());

      pnode->set_value(m_pvar->get_string());

   }


   void var_exchange::xml_import(class input_tree & xmlit)
   {
      ASSERT(m_pvar != nullptr);
      if(m_pvar == nullptr)
         return;
      node * pnode = xmlit.m_pnode;
      if(pnode == nullptr)
      {
         // property Node not found;
         //ASSERT(false);
         return;
      }
      
      i32 i = pnode->attribute("type");
      
      m_pvar->m_etype = (::enum_type) i;

      m_pvar->set_string(pnode->get_value());

   }


} // namespace xml



