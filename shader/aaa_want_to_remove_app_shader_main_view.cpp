#include "framework.h"


namespace simple_shader
{


   main_view::main_view(::object * pobject):
      object(pobject),
      ::user::split_layout(pobject),
      ::user::split_view(pobject),
      ::userex::split_view(pobject),
      place_holder_container(pobject)
   {

      m_ptopview = NULL;
      m_pview    = NULL;
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

      if (papplication->m_bMultiverseChat)
      {

         SetPaneCount(2);

         SetSplitOrientation(e_orientation_horizontal);

         set_position(0, 31);

         initialize_split_layout();

         m_ptopview = host_view < ::userex::top_view >(0, "top_view");

         if (m_ptopview == NULL)
         {

            message_box(NULL, "Could not create folder edit view");

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

      m_pview = host_view < view >(iPane, "simple_shader_view");

      if(m_pview == NULL)
      {

         message_box(NULL,"Could not create file list ::user::impact");

      }

      __pointer(::userex::top_edit_view) peditview = get_child_by_id("top_edit_view");

      if(peditview.is_set())
      {

         string strText;

         m_pview->data_get("cur_text",strText);

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


   bool main_view::BaseOnControlEvent(::user::control_event * pevent)
   {

      if(pevent->m_eevent == ::user::e_event_button_clicked)
      {

         if(pevent->m_puserinteraction->m_id == "simple_shader_toggle")
         {

            m_pview->on_layout(::draw2d::graphics_pointer & pgraphics);

            return true;

         }

      }

      return false;

   }

} // namespace simple_shader



