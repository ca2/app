#include "framework.h"


namespace turboc
{


   main_view::main_view(::object * pobject):
      ::object(pobject),
      ::user::split_layout(pobject),
      ::user::split_view(pobject),
      place_holder_container(pobject)
   {

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


   void main_view::on_update(::aura::impact * pSender,e_update eupdate,object* pupdate)
   {
      ::user::split_view::on_subject(psubject, pcontext);
   }


   void main_view::on_create_split_impact()
   {

      if(get_pane_count() > 0)
         return;

      if(papplication->m_bMultiverseChat)
      {

         SetPaneCount(2);

      }

      SetSplitOrientation(e_orientation_horizontal);

      set_position(0,24);

      initialize_split_layout();

      if(papplication->m_bMultiverseChat)
      {

         m_ptopview = create_view < top_view >(NULL,::rectangle_i32(),NULL,"turboc_top");

         if(m_ptopview == NULL)
         {

            message_box(NULL,"Could not create folder edit view");

         }

         SetPane(0,m_ptopview,false);

      }

      //m_pview = create_view < lite_view >();

      m_pview = create_view < view >();

      if(m_pview == NULL)
      {

         message_box(NULL,"Could not create file list ::aura::impact");

      }

      m_ptopview->m_pview = m_pview;


      if(papplication->m_bMultiverseChat)
      {
         SetPane(1,m_pview,false);

      }

      else
      {
         SetPane(1,m_pview,false);
      }


   }



   void main_view::on_control_event(::user::control_event * pevent)
   {

      if(pevent->m_eevent == ::user::e_event_button_clicked)
      {

         if(pevent->m_puserinteraction->m_id == "turboc_toggle")
         {

            if(m_pview->m_bLite && !papplication->m_bLoadAiFont)
            {

               papplication->load_ai_font();

            }

            m_pview->m_bLite = !m_pview->m_bLite;


            m_pview->on_layout(::draw2d::graphics_pointer & pgraphics);

         }

      }

      return true;

   }


} // namespace turboc



