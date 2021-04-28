#include "framework.h"
#include "aqua/xml.h"


namespace xml
{


   property_set_exchange::property_set_exchange(::object * pobject)
   {

      m_ppropertyset = nullptr;

   }


   property_set_exchange::~property_set_exchange()
   {

   }


   void property_set_exchange::xml_export(class output_tree & xmlot)
   {

      ASSERT(m_ppropertyset != nullptr);

      if (m_ppropertyset == nullptr)
      {

         return;

      }

      var_exchange varexchange;

      for(auto & pproperty : *m_ppropertyset)
      {

         varexchange.m_pvar = pproperty;

         xmlot.export_node(pproperty->m_id, varexchange);

      }

   }


   void property_set_exchange::xml_import(class input_tree & xmlit)
   {
      ASSERT(m_ppropertyset != nullptr);
      if(m_ppropertyset == nullptr)
         return;

      var_exchange varexchange;

      for(auto & pproperty : *m_ppropertyset)
      {

         varexchange.m_pvar = pproperty;

         xmlit.import_node(pproperty->m_id, varexchange);

      }

   }


} // namespace xml



