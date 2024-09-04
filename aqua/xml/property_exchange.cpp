#include "framework.h"
#include "property_exchange.h"
#include "var_exchange.h"
#include "output_tree.h"
#include "input_tree.h"
#include "document.h"


namespace xml
{


   property_set_exchange::property_set_exchange(::particle * pparticle)
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

      for(auto & property : *m_ppropertyset)
      {

         varexchange.m_ppayload = &property;

         xmlot.export_node(property.m_atom, varexchange);

      }

   }


   void property_set_exchange::xml_import(class input_tree & xmlit)
   {
      ASSERT(m_ppropertyset != nullptr);
      if(m_ppropertyset == nullptr)
         return;

      var_exchange varexchange;

      for(auto & property : *m_ppropertyset)
      {

         varexchange.m_ppayload = &property;

         xmlit.import_node(property.m_atom, varexchange);

      }

   }


} // namespace xml



