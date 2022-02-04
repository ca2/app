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

      m_pimpact = nullptr;

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

      MESSAGE_LINK(e_message_create, pchannel, this, &font_view::on_message_create);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &font_view::on_message_show_window);

   }


   void font_view::on_message_create(::message::message* pmessage)
   {

      pmessage->previous();

      set_impact_title("Font");

      get_parent_frame()->set_frame_title("Font");

   }

   
   void font_view::on_message_show_window(::message::message* /* pmessage */)
   {

   }


   void font_view::handle(::topic * psubject, ::context * pcontext)
   {

      ::user::split_view::handle(psubject, pcontext);

      if (psubject->id() == id_after_change_text)
      {

         if (m_ptopview != nullptr && psubject->m_puserelement == m_ptopview->m_peditview)
         {

            synchronous_lock synchronouslock(m_pimpact->m_pfontlist->mutex());

            string strText;

            m_ptopview->m_peditview->_001GetText(strText);

            m_pimpact->m_pfontlist->m_strText = strText;

         }

      }
      else if (psubject->user_element_id() == impact_font_sel)
      {

         if (psubject->m_id == ::id_after_change_cur_sel)
         {

            if (m_bSourceFontSel)
            {

               string strText;

               strText = m_pimpact->m_pfontlist->m_strFontFamily;

               m_ptopview->m_peditview->_001SetText(strText, ::e_source_sync);

               m_ptopview->m_peditview->m_pfont.defer_create(this);

               m_ptopview->m_peditview->m_pfont->set_family_name(strText);

               m_pimpact->m_pfontlist->m_strText = "";

            }

         }

      }

      ::user::impact::handle(psubject, pcontext);




   }


   void font_view::on_create_split_impact()
   {

      if (get_pane_count() > 0)
      {

         return;

      }

      SetPaneCount(2);

      SetSplitOrientation(e_orientation_horizontal);

      set_position(0, 24);

      initialize_split_layout();

      m_ptopview = create_view < top_view >(nullptr, get_pane_holder(0), "top_view");

      if (m_ptopview == nullptr)
      {

         output_error_message("Could not create folder edit impact");

      }

      m_pimpact = create_view < ::user::font_list_view >(nullptr, get_pane_holder(1), FONTSEL_IMPACT);

      if (m_pimpact == nullptr)
      {

         output_error_message("Could not create file list ::user::impact");

      }

      if(get_document()->m_pviewTopic == nullptr)
      {

         get_document()->m_pviewTopic = m_pimpact;

      }

      m_pimpact->set_font_list_type(::write_text::font_list::type_wide);

   }


   void font_view::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::split_view::on_layout(pgraphics);

   }


   bool font_view::set_sel_by_name(string str)
   {

      if (m_bSourceFontSel)
      {

         m_ptopview->m_peditview->_001SetText(str, ::e_source_sync);

         m_ptopview->m_peditview->m_pfont.defer_create(this);

         m_ptopview->m_peditview->m_pfont->set_family_name(str);

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


   //void font_view::handle(::topic * psubject, ::context * pcontext)
   //{

   //   ::user::impact::handle(psubject, pcontext);

   //   if (psubject->m_puserelement->m_id == impact_font_sel)
   //   {

   //      if (psubject->m_id == ::id_after_change_cur_sel)
   //      {

   //         if (m_bSourceFontSel)
   //         {

   //            string strText;

   //            strText = m_pimpact->m_pfontlist->m_strFontFamily;

   //            m_ptopview->m_peditview->_001SetText(strText, ::e_source_sync);

   //            m_ptopview->m_peditview->m_pfont.defer_create(this);

   //            m_ptopview->m_peditview->m_pfont->set_family_name(strText);

   //            m_pimpact->m_pfontlist->m_strText = "";

   //         }

   //      }

   //   }

   //}


} // namespace userex



