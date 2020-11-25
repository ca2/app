#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif
#include "aura/update.h"


namespace userex
{


   font_view::font_view()
   {

      m_id = "font_view";

      m_pview = nullptr;

      m_ptopview = nullptr;

      m_bSourceFontSel = true;

   }


   font_view::~font_view()
   {

   }


   void font_view::assert_valid() const
   {

      ::user::split_view::assert_valid();

   }


   void font_view::dump(dump_context& dumpcontext) const
   {

      ::user::split_view::dump(dumpcontext);

   }


   void font_view::install_message_routing(::channel* pchannel)
   {

      ::user::split_view::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &font_view::_001OnCreate);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &font_view::_001OnShowWindow);

   }


   void font_view::_001OnCreate(::message::message* pmessage)
   {

      pmessage->previous();

      set_impact_title("Font");

      GetParentFrame()->set_frame_title("Font");

   }

   
   void font_view::_001OnShowWindow(::message::message* /* pmessage */)
   {

      //SCAST_PTR(::message::show_window, pshowwindow, pmessage);
   

   }


   void font_view::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
   {

      ::user::split_view::on_subject(psubject, pcontext);

      ////__update(::update)
      {

         if (psubject->id() == id_after_change_text)
         {

            if (m_ptopview != nullptr && psubject->m_puserinteraction == m_ptopview->m_peditview)
            {

               sync_lock sl(m_pview->m_pfontlist->mutex());

               string strText;

               m_ptopview->m_peditview->_001GetText(strText);

               m_pview->m_pfontlist->m_strText = strText;

            }

         }

      }

   }


   void font_view::on_create_split_impact()
   {

      if (get_pane_count() > 0)
      {

         return;

      }

      SetPaneCount(2);

      SetSplitOrientation(orientation_horizontal);

      set_position(0, 24);

      initialize_split_layout();

      m_ptopview = create_view < top_view >(nullptr, get_pane_holder(0), "top_view");

      if (m_ptopview == nullptr)
      {

         message_box("Could not create folder edit view");

      }

      m_pview = create_view < ::user::font_list_view >(nullptr, get_pane_holder(1), FONTSEL_IMPACT);

      if (m_pview == nullptr)
      {

         message_box("Could not create file list ::user::impact");

      }

      if(get_document()->m_pviewTopic == nullptr)
      {

         get_document()->m_pviewTopic = m_pview;

      }

      m_pview->set_font_list_type(::draw2d::font_list::type_wide);

   }


   void font_view::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::split_view::on_layout(pgraphics);

   }


   bool font_view::set_sel_by_name(string str)
   {

      if (m_bSourceFontSel)
      {

         m_ptopview->m_peditview->_001SetText(str, source_sync);

         m_ptopview->m_peditview->m_pfont.defer_create();

         m_ptopview->m_peditview->m_pfont->set_family_name(str);

      }

      if (!m_pview || !m_pview->m_pfontlist)
      {

         return false;

      }

      if (m_bSourceFontSel)
      {

         m_pview->m_pfontlist->m_strText = "";

      }

      if (!m_pview->m_pfontlist->set_sel_by_name(str))
      {

         return false;

      }

      return true;

   }


   void font_view::on_control_event(::user::control_event * pevent)
   {

      ::user::impact::on_control_event(pevent);

      if (pevent->m_id == impact_font_sel)
      {

         if (pevent->m_eevent == ::user::event_after_change_cur_sel)
         {

            if (m_bSourceFontSel)
            {

               string strText;

               strText = m_pview->m_pfontlist->m_strFontFamily;

               m_ptopview->m_peditview->_001SetText(strText, source_sync);

               m_ptopview->m_peditview->m_pfont.defer_create();

               m_ptopview->m_peditview->m_pfont->set_family_name(strText);

               m_pview->m_pfontlist->m_strText = "";

            }

         }

      }

   }


} // namespace userex



