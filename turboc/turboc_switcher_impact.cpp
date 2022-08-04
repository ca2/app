#include "framework.h"


namespace turboc
{


   switcher_impact::switcher_impact(::object * pobject):
      ::object(pobject),
      ::user::split_layout(pobject),
      ::user::split_impact(pobject),
      place_holder_container(pobject)
   {

   }


   switcher_impact::~switcher_impact()
   {

   }


   void switcher_impact::assert_ok() const
   {

      ::user::split_impact::assert_ok();

   }


   void switcher_impact::dump(dump_context & dumpcontext) const
   {

      ::user::split_impact::dump(dumpcontext);

   }


   void switcher_impact::on_update(::aura::impact * pSender,e_update eupdate,object* pupdate)
   {
      ::user::split_impact::handle(ptopic, pcontext);
   }


   void switcher_impact::on_create_split_impact()
   {

      if(get_pane_count() > 0)
         return;

      SetPaneCount(2);

      SetSplitOrientation(e_orientation_horizontal);

      set_position(0,24);

      initialize_split_layout();

      m_ptopview = create_impact < top_impact >(NULL,::rectangle_i32(),NULL,"switcher_top");

      if(m_ptopview == NULL)
      {

         message_box(NULL,"Could not create folder edit impact");

      }

      SetPane(0,m_ptopview,false);

      m_pimpact = create_impact < lite_impact >();

      m_pimpact->m_bAlternate = true;

      if(m_pimpact == NULL)
      {

         message_box(NULL,"Could not create file list ::aura::impact");

      }

      m_ptopview->m_pimpact = m_pimpact;


      SetPane(1,m_pimpact,false);


   }



   void switcher_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      if(ptopic->m_atom == ::id_click)
      {

         if(ptopic->user_element_id() == "switcher_toggle")
         {

            __pointer(impact) pimpact = m_pimpact;

            if(base_class < lite_impact >::bases(pimpact))
            {

               m_pimpact = create_impact < full_impact >();

            }
            else
            {

               m_pimpact = create_impact < lite_impact >();

            }

            if(m_pimpact == NULL)
            {

               message_box(NULL,"Could not create file list ::aura::impact");

            }

            m_pimpact->m_bAlternate = true;

            m_ptopview->m_pimpact = m_pimpact;

            SetPane(1,m_pimpact,false);

            pimpact->DestroyWindow();

         }

      }

      return true;

   }

} // namespace turboc



