#include "framework.h"
#include "font_impact.h"
#include "top_impact.h"
#include "top_edit_impact.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "aura/user/user/frame.h"
#include "aura/graphics/write_text/font_list.h"
#include "base/user/user/document.h"
#include "core/user/user/font_list.h"


namespace userex
{


   font_impact::font_impact()
   {

      m_atom = "font_impact";

      m_pimpact = nullptr;

      m_ptopview = nullptr;

      m_bSourceFontSel = true;

   }


   font_impact::~font_impact()
   {

   }


   //void font_impact::assert_ok() const
   //{

   //   ::user::split_impact::assert_ok();

   //}


   //void font_impact::dump(dump_context& dumpcontext) const
   //{

   //   ::user::split_impact::dump(dumpcontext);

   //}


   void font_impact::install_message_routing(::channel* pchannel)
   {

      ::user::split_impact::install_message_routing(pchannel);

      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &font_impact::on_message_create);
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


   void font_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::split_impact::handle(ptopic, pcontext);

      if (ptopic->m_atom == id_after_change_text)
      {

         if (m_ptopview != nullptr && ptopic->m_puserelement == m_ptopview->m_peditimpact)
         {

            synchronous_lock synchronouslock(m_pimpact->m_pfontlist->synchronization());

            string strText;

            m_ptopview->m_peditimpact->_001GetText(strText);

            m_pimpact->m_pfontlist->m_strText = strText;

         }

      }
      else if (ptopic->user_element_id() == FONTSEL_IMPACT)
      {

         if (ptopic->m_atom == ::id_after_change_cur_sel)
         {

            if (m_bSourceFontSel)
            {

               string strText;

               strText = m_pimpact->m_pfontlist->m_strFontFamily;

               m_ptopview->m_peditimpact->_001SetText(strText, ::e_source_sync);

               m_ptopview->m_peditimpact->m_pfont.defer_create(this);

               m_ptopview->m_peditimpact->m_pfont->set_family_name(strText);

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

      m_ptopview = create_impact < top_impact >(nullptr, get_pane_holder(0), "top_impact");

      if (m_ptopview == nullptr)
      {

         output_error_message("Could not create folder edit impact");

      }

      m_pimpact = create_impact < ::user::font_list_impact >(nullptr, get_pane_holder(1), FONTSEL_IMPACT);

      if (m_pimpact == nullptr)
      {

         output_error_message("Could not create file list ::user::impact");

      }

      if(get_document()->m_pviewTopic == nullptr)
      {

         get_document()->m_pviewTopic = m_pimpact;

      }

      m_pimpact->set_font_list_type(::write_text::e_font_list_wide);

   }


   void font_impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::split_impact::on_layout(pgraphics);

   }


   bool font_impact::set_sel_by_name(string str)
   {

      if (m_bSourceFontSel)
      {

         m_ptopview->m_peditimpact->_001SetText(str, ::e_source_sync);

         m_ptopview->m_peditimpact->m_pfont.defer_create(this);

         m_ptopview->m_peditimpact->m_pfont->set_family_name(str);

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


   //void font_impact::handle(::topic * ptopic, ::context * pcontext)
   //{

   //   ::user::impact::handle(ptopic, pcontext);

   //   if (ptopic->m_puserelement->m_atom == impact_font_sel)
   //   {

   //      if (ptopic->m_atom == ::id_after_change_cur_sel)
   //      {

   //         if (m_bSourceFontSel)
   //         {

   //            string strText;

   //            strText = m_pimpact->m_pfontlist->m_strFontFamily;

   //            m_ptopview->m_peditimpact->_001SetText(strText, ::e_source_sync);

   //            m_ptopview->m_peditimpact->m_pfont.defer_create(this);

   //            m_ptopview->m_peditimpact->m_pfont->set_family_name(strText);

   //            m_pimpact->m_pfontlist->m_strText = "";

   //         }

   //      }

   //   }

   //}


} // namespace userex



