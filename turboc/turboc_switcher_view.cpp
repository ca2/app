#include "framework.h"


namespace turboc
{


   switcher_view::switcher_view(::object * pobject):
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
      ::user::split_view::handle(psubject, pcontext);
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

         message_box(NULL,"Could not create folder edit impact");

      }

      SetPane(0,m_ptopview,false);

      m_pimpact = create_view < lite_view >();

      m_pimpact->m_bAlternate = true;

      if(m_pimpact == NULL)
      {

         message_box(NULL,"Could not create file list ::aura::impact");

      }

      m_ptopview->m_pimpact = m_pimpact;


      SetPane(1,m_pimpact,false);


   }



   void switcher_view::handle(::subject * psubject, ::context * pcontext)
   {

      if(psubject->m_id == ::e_subject_click)
      {

         if(psubject->user_element_id() == "switcher_toggle")
         {

            __pointer(impact) pview = m_pimpact;

            if(base_class < lite_view >::bases(pview))
            {

               m_pimpact = create_view < full_view >();

            }
            else
            {

               m_pimpact = create_view < lite_view >();

            }

            if(m_pimpact == NULL)
            {

               message_box(NULL,"Could not create file list ::aura::impact");

            }

            m_pimpact->m_bAlternate = true;

            m_ptopview->m_pimpact = m_pimpact;

            SetPane(1,m_pimpact,false);

            pview->DestroyWindow();

         }

      }

      return true;

   }

} // namespace turboc



