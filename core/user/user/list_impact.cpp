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

      //if (ptopic->m_atom == ID_INITIAL_UPDATE)
      //{

      //   update_impact();

      //}

   }


   void list_impact::on_selection_change()
   {

      BASE_VIEW::on_selection_change();

      //if (get_parent_frame() != nullptr)
      //{

      //   get_parent_frame()->set_active_impact(this);

      //}

   }

} // namespace user




