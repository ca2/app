#include "framework.h"
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


   void list_view::update(::update * pupdate)
   {

      BASE_VIEW::update(pupdate);

      if (pupdate->m_id == id_initial)
      {

         _001OnUpdateItemCount();

      }

   }


   void list_view::_001OnSelectionChange()
   {

      BASE_VIEW::_001OnSelectionChange();

      if (GetParentFrame() != nullptr)
      {

         GetParentFrame()->SetActiveView(this);

      }

   }

} // namespace user




