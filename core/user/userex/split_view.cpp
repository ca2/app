#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif

#include "base/user/user/split_pane.h"


namespace userex
{


   split_view::split_view()
   {

   }


   split_view::~split_view()
   {

   }


   void split_view::install_message_routing(::channel * pchannel)
   {

      ::user::split_view::install_message_routing(pchannel);
      ::user::impact_host::install_message_routing(pchannel);

   }


   bool split_view::on_new_view_creator_data(::user::impact_data * pimpactdata)
   {

      ::index iPane = pimpactdata->m_id.index();

      if (iPane < 0)
      {

         return false;

      }

      auto ppane = m_splitpanecompositea[iPane].get();

      if (!pimpactdata->m_pplaceholder)
      {

         pimpactdata->m_pplaceholder = get_new_place_holder(ppane->m_rectangle);

         ppane->m_pplaceholder = pimpactdata->m_pplaceholder;

      }

      if (ppane->m_pplaceholder == nullptr)
      {

         return false;

      }

      pimpactdata->m_pimpactdata = (void *) ppane;

      return true;

   }


   void split_view::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::split_view::handle(ptopic, pcontext);
      ::user::impact_host::handle(ptopic, pcontext);

   }


   bool split_view::on_prepare_impact_data(::user::impact_data* pimpactdata)
   {

      pimpactdata->m_id = pimpactdata->m_idTitle;

      pimpactdata->m_pplaceholder = get_pane_holder((::index) pimpactdata->m_iId);

      return true;

   }


   bool split_view::create_pane(i32 iPane, bool bFixedSize, ::id id)
   {

      ASSERT(iPane >= 0);

      ASSERT(iPane < get_pane_count());

      auto ppane = m_splitpanecompositea[iPane].get();

      ppane->m_bFixedSize = bFixedSize;

      ppane->m_id = id;

      ::rectangle_i32 rectangleClient;

      ppane->m_pplaceholder->get_client_rect(rectangleClient);

      ::user::impact_data * pdata = create_impact(id);

      if (pdata == nullptr)
      {

         return false;

      }

      return true;

   }


   void split_view::on_command_probe(::message::command * pcommand)
   {

   }


   void split_view::on_command(::message::command * pcommand)
   {

   }


} // namespace userex
