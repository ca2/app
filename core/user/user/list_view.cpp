#include "framework.h"
#include "core/user/user/_user.h"
#include "aura/update.h"


namespace user
{


   list_view::list_view()
   {

   }


   list_view::~list_view()
   {

   }


   void list_view::install_message_routing(::channel * pchannel)
   {

      BASE_VIEW::install_message_routing(pchannel);

   }


   void list_view::handle(::topic * ptopic, ::context * pcontext)
   {

      BASE_VIEW::handle(ptopic, pcontext);

      if (ptopic->m_atom == id_initial)
      {

         _001OnUpdateItemCount();

      }

   }


   void list_view::_001OnSelectionChange()
   {

      BASE_VIEW::_001OnSelectionChange();

      //if (get_parent_frame() != nullptr)
      //{

      //   get_parent_frame()->set_active_view(this);

      //}

   }

} // namespace user




