#include "framework.h"


namespace turboc
{


   switcher_view::switcher_view(::layered * pobjectContext):
      ::object(pobject),
      ::user::split_layout(pobject),
      ::user::split_view(pobject),
      place_holder_container(pobject)
   {

   }


   switcher_view::~switcher_view()
   {

   }


   void switcher_view::assert_valid() const
   {

      ::user::split_view::assert_valid();

   }


   void switcher_view::dump(dump_context & dumpcontext) const
   {

      ::user::split_view::dump(dumpcontext);

   }


   void switcher_view::on_update(::aura::impact * pSender,e_update eupdate,object* pupdate)
   {
      ::user::split_view::on_subject(psubject, pcontext);
   }


   void switcher_view::on_create_split_impact()
   {

      if(get_pane_count() > 0)
         return;

      SetPaneCount(2);

      SetSplitOrientation(e_orientation_horizontal);

      set_position(0,24);

      initialize_split_layout();

      m_ptopview = create_view < top_view >(NULL,::rectangle_i32(),NULL,"switcher_top");

      if(m_ptopview == NULL)
      {

         System.message_box(NULL,"Could not create folder edit view");

      }

      SetPane(0,m_ptopview,false);

      m_pview = create_view < lite_view >();

      m_pview->m_bAlternate = true;

      if(m_pview == NULL)
      {

         System.message_box(NULL,"Could not create file list ::aura::impact");

      }

      m_ptopview->m_pview = m_pview;


      SetPane(1,m_pview,false);


   }



   void switcher_view::on_control_event(::user::control_event * pevent)
   {

      if(pevent->m_eevent == ::user::e_event_button_clicked)
      {

         if(pevent->m_puie->m_id == "switcher_toggle")
         {

            __pointer(view) pview = m_pview;

            if(base_class < lite_view >::bases(pview))
            {

               m_pview = create_view < full_view >();

            }
            else
            {

               m_pview = create_view < lite_view >();

            }

            if(m_pview == NULL)
            {

               System.message_box(NULL,"Could not create file list ::aura::impact");

            }

            m_pview->m_bAlternate = true;

            m_ptopview->m_pview = m_pview;

            SetPane(1,m_pview,false);

            pview->DestroyWindow();

         }

      }

      return true;

   }

} // namespace turboc



