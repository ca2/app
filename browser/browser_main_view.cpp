#include "framework.h"


namespace browser
{


   main_view::main_view(::layered * pobjectContext):
      object(pobject),
      ::user::split_layout(pobject),
      ::user::split_view(pobject),
      place_holder_container(pobject)
   {

      m_ptopview = nullptr;
      m_pview    = nullptr;
      m_flagNonClient.add(non_client_background);
      m_flagNonClient.add(non_client_focus_rect);


   }


   main_view::~main_view()
   {

   }


   void main_view::assert_valid() const
   {

      ::user::split_view::assert_valid();

   }


   void main_view::dump(dump_context & dumpcontext) const
   {

      ::user::split_view::dump(dumpcontext);

   }


   void main_view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      ::user::split_view::on_subject(psubject, pcontext);

   }


   void main_view::on_create_split_impact()
   {

      if(get_pane_count() > 0)
         return;

      int iPane;

      if (Application.m_bBrowserChat)
      {

         SetPaneCount(2);

         SetSplitOrientation(e_orientation_horizontal);

         set_position(0, 31);

         initialize_split_layout();

         m_ptopview = create_view < ::userex::top_view >(nullptr, nullptr, "top_view");

         if (m_ptopview == nullptr)
         {

            System.message_box(nullptr, "Could not create folder edit view");

         }

         SetPane(0, m_ptopview, false);

         iPane = 1;

      }
      else
      {

         SetPaneCount(1);

         initialize_split_layout();

         iPane = 0;

      }

      //m_pview = create_view < lite_view >();

      m_pview = create_view < view >(nullptr, get_pane_holder(iPane), "browser_view");

      if(m_pview == nullptr)
      {

         System.message_box(nullptr,"Could not create file list ::user::impact");

      }

      __pointer(::userex::top_edit_view) peditview = get_child_by_id("top_edit_view");

      peditview->m_bParseDataPacks = true;

      if(peditview.is_set())
      {

         string strText;

         m_pview->data_get("cur_text", strText);

         peditview->_001SetText(strText, ::e_source_initialize);

      }

//      SetPane(iPane,m_pview,false);

   }


   void main_view::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::split_view::_001OnNcDraw(pgraphics);

   }


   void main_view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::split_view::_001OnDraw(pgraphics);

   }


   void main_view::on_control_event(::user::control_event * pevent)
   {

      if(pevent->m_eevent == ::user::e_event_button_clicked)
      {

         if(pevent->m_puie->m_id == "browser_toggle")
         {

            m_pview->m_prender->m_bLite = !m_pview->m_prender->m_bLite;


            m_pview->on_layout(::draw2d::graphics_pointer & pgraphics);

            pevent->m_bRet = true;
            return;

         }

      }

      ::user::split_view::on_control_event(pevent);

   }


} // namespace browser



