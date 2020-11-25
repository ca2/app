#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif


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

      Pane * ppane = (Pane *) m_panea.element_at(iPane);

      if (!pimpactdata->m_pplaceholder)
      {

         pimpactdata->m_pplaceholder = get_new_place_holder(ppane->m_rect);

         ppane->m_pplaceholder = pimpactdata->m_pplaceholder;

      }

      if (ppane->m_pplaceholder == nullptr)
      {

         return false;

      }

      pimpactdata->m_pimpactdata = (void *) ppane;

      return true;

   }


   void split_view::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
   {

      ::user::split_view::on_subject(psubject, pcontext);
      ::user::impact_host::on_subject(psubject, pcontext);

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

      Pane & pane = m_panea(iPane);

      pane.m_bFixedSize = bFixedSize;

      pane.m_id = id;

      ::rect rectClient;

      pane.m_pplaceholder->get_client_rect(rectClient);

      ::user::impact_data * pdata = create_impact(id);

      if (pdata == nullptr)
      {

         return false;

      }

      return true;

   }


   void split_view::on_command_probe(::user::command * pcommand)
   {

   }


   void split_view::on_command(::user::command * pcommand)
   {

   }


} // namespace userex
