#include "framework.h"
#include "font_impact.h"
#include "top_impact.h"
#include "top_edit_impact.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/handler/topic.h"
#include "aura/graphics/write_text/font_list.h"
#include "aura/user/user/frame_interaction.h"
//#include "aura/user/user/primitive_impl.h"
#include "base/user/user/document.h"
#include "core/user/user/font_list_impact.h"


namespace userex
{


   font_impact::font_impact()
   {

      id() = "font_impact";

      m_pimpact = nullptr;

      m_ptopimpact = nullptr;

      m_bSourceFontSel = true;

   }


   font_impact::~font_impact()
   {

   }



   void font_impact::install_message_routing(::channel* pchannel)
   {

      ::user::split_impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &font_impact::on_message_create);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &font_impact::on_message_show_window);

   }


   void font_impact::on_message_create(::message::message* pmessage)
   {

      pmessage->previous();

      set_impact_title("Font");

      parent_frame()->set_frame_title("Font");

   }

   
   void font_impact::on_message_show_window(::message::message* /* pmessage */)
   {

   }


   void font_impact::handle(::topic * ptopic, ::handler_context * pcontext)
   {

      ::user::split_impact::handle(ptopic, pcontext);

      if (ptopic->id() == id_after_change_text)
      {

         if (m_ptopimpact != nullptr && ptopic->m_puserelement == m_ptopimpact->m_peditimpact)
         {

            synchronous_lock synchronouslock(m_pimpact->m_pfontlist->synchronization());

            string strText;

            m_ptopimpact->m_peditimpact->get_text(strText);

            m_pimpact->m_pfontlist->m_strText = strText;

         }

      }
      else if (ptopic->user_interaction_id() == FONTSEL_IMPACT)
      {

         if (ptopic->id() == ::id_after_change_cur_sel)
         {

            if (m_bSourceFontSel)
            {

               string strText;

               strText = m_pimpact->m_pfontlist->m_strFontFamily;

               m_ptopimpact->m_peditimpact->set_text(strText, ::e_source_sync);

               __defer_construct(m_ptopimpact->m_peditimpact->m_pfont);

               m_ptopimpact->m_peditimpact->m_pfont->set_family_name(strText);

               m_pimpact->m_pfontlist->m_strText = "";

            }

         }

      }

      ::user::impact::handle(ptopic, pcontext);

   }


   void font_impact::on_create_split_impact()
   {

      if (get_pane_count() > 0)
      {

         return;

      }

      SetPaneCount(2);

      SetSplitOrientation(e_orientation_horizontal);

      auto preferredDensity = preferred_density();

      set_position(0, (int) (24.f * preferredDensity));

      initialize_split_layout();

      m_ptopimpact = create_impact < top_impact >(nullptr, get_pane_holder(0), "top_impact");

      if (m_ptopimpact == nullptr)
      {

         output_error_message("Could not create folder edit impact");

      }

      m_pimpact = create_impact < ::user::font_list_impact >(nullptr, get_pane_holder(1), FONTSEL_IMPACT);

      if (m_pimpact == nullptr)
      {

         output_error_message("Could not create file list ::user::impact");

      }

      if(get_document()->m_pimpactTopic == nullptr)
      {

         get_document()->m_pimpactTopic = m_pimpact;

      }

      m_pimpact->set_font_list_type(::write_text::e_font_list_wide);

   }


   void font_impact::defer_do_graphics(::draw2d::graphics_pointer & pgraphics)
   {

      //m_pprimitiveimpl->defer_do_graphics(pgraphics);

      ::user::split_impact::defer_do_graphics(pgraphics);

   }


   void font_impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::split_impact::on_layout(pgraphics);

   }


   bool font_impact::set_sel_by_name(string str)
   {

      if (m_bSourceFontSel)
      {

         m_ptopimpact->m_peditimpact->set_text(str, ::e_source_sync);

         __defer_construct(m_ptopimpact->m_peditimpact->m_pfont);

         m_ptopimpact->m_peditimpact->m_pfont->set_family_name(str);

      }

      if (!m_pimpact || !m_pimpact->m_pfontlist)
      {

         return false;

      }

      if (m_bSourceFontSel)
      {

         m_pimpact->m_pfontlist->m_strText = "";

      }

      if (!m_pimpact->set_sel_by_name(str))
      {

         return false;

      }

      return true;

   }


   //void font_impact::handle(::topic * ptopic, ::handler_context * pcontext)
   //{

   //   ::user::impact::handle(ptopic, pcontext);

   //   if (ptopic->user_interaction_id() == impact_font_sel)
   //   {

   //      if (ptopic->id() == ::id_after_change_cur_sel)
   //      {

   //         if (m_bSourceFontSel)
   //         {

   //            string strText;

   //            strText = m_pimpact->m_pfontlist->m_strFontFamily;

   //            m_ptopimpact->m_peditimpact->set_text(strText, ::e_source_sync);

   //            m_ptopimpact->m_peditimpact->m_pfont.defer_create(this);

   //            m_ptopimpact->m_peditimpact->m_pfont->set_family_name(strText);

   //            m_pimpact->m_pfontlist->m_strText = "";

   //         }

   //      }

   //   }

   //}


} // namespace userex



