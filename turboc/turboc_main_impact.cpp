#include "framework.h"


namespace turboc
{


   main_impact::main_impact(::particle * pparticle):
      ::object(pparticle),
      ::user::split_layout(pparticle),
      ::user::split_impact(pparticle),
      place_holder_container(pparticle)
   {

   }


   main_impact::~main_impact()
   {

   }


   void main_impact::assert_ok() const
   {

      ::user::split_impact::assert_ok();

   }


   void main_impact::dump(dump_context & dumpcontext) const
   {

      ::user::split_impact::dump(dumpcontext);

   }


   void main_impact::on_update(::aura::impact * pSender,e_update eupdate,object* pupdate)
   {
      ::user::split_impact::handle(ptopic, phandlercontext);
   }


   void main_impact::on_create_split_impact()
   {

      if(get_pane_count() > 0)
         return;

      if(papp->m_bMultiverseChat)
      {

         SetPaneCount(2);

      }

      SetSplitOrientation(e_orientation_horizontal);

      set_position(0,24);

      initialize_split_layout();

      if(papp->m_bMultiverseChat)
      {

         m_ptopimpact = create_impact < top_impact >(NULL,::int_rectangle(),NULL,"turboc_top");

         if(m_ptopimpact == NULL)
         {

            message_box(NULL,"Could not create folder edit impact");

         }

         SetPane(0,m_ptopimpact,false);

      }

      //m_pimpact = create_impact < lite_impact >();

      m_pimpact = create_impact < impact >();

      if(m_pimpact == NULL)
      {

         message_box(NULL,"Could not create file list ::aura::impact");

      }

      m_ptopimpact->m_pimpact = m_pimpact;


      if(papp->m_bMultiverseChat)
      {
         SetPane(1,m_pimpact,false);

      }

      else
      {
         SetPane(1,m_pimpact,false);
      }


   }



   void main_impact::handle(::topic * ptopic, ::handler_context * pcontext)
   {

      if(ptopic->id() == ::id_click)
      {

         if(ptopic->user_interaction_id() == "turboc_toggle")
         {

            if(m_pimpact->m_bLite && !papp->m_bLoadAiFont)
            {

               papp->load_ai_font();

            }

            m_pimpact->m_bLite = !m_pimpact->m_bLite;


            m_pimpact->on_layout(pgraphics);

         }

      }

      return true;

   }


} // namespace turboc



