#include "framework.h"
#include "list_impact.h"


namespace user
{


   list_impact::list_impact()
   {

   }


   list_impact::~list_impact()
   {

   }


   void list_impact::install_message_routing(::channel * pchannel)
   {

      BASE_VIEW::install_message_routing(pchannel);

   }


   void list_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      BASE_VIEW::handle(ptopic, pcontext);

      if (ptopic->m_atom == id_initial)
      {

         _001OnUpdateItemCount();

      }

   }


   void list_impact::_001OnSelectionChange()
   {

      BASE_VIEW::_001OnSelectionChange();

      //if (get_parent_frame() != nullptr)
      //{

      //   get_parent_frame()->set_active_impact(this);

      //}

   }

} // namespace user




