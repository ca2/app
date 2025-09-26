#include "framework.h"


namespace browser
{


   switcher_impact::switcher_impact(::particle * pparticle):
      object(pparticle),
      ::user::split_layout(pparticle),
      ::user::split_impact(pparticle),
      place_holder_container(pparticle)
   {

      m_pimpact = nullptr;

      m_ptopimpact = nullptr;

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


   void switcher_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {
      ::user::split_impact::handle(ptopic, phandlercontext);
   }


   void switcher_impact::on_create_split_impact()
   {

      if(get_pane_count() > 0)
         return;

      SetPaneCount(2);

      SetSplitOrientation(e_orientation_horizontal);

      set_position(0,24);

      initialize_split_layout();

      m_ptopimpact = create_impact < ::userex::top_impact >(nullptr, get_pane_holder(0),"top_impact");

      if(m_ptopimpact == nullptr)
      {

         message_box(nullptr,"Could not create folder edit impact");

      }

      //SetPane(0,m_ptopimpact,false);

      m_pimpact = create_impact < impact >(nullptr,get_pane_holder(1),"browser_switcher_impact");

      if(m_pimpact == nullptr)
      {

         message_box(nullptr,"Could not create file list_base ::user::impact");

      }

   }



   void switcher_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      if(ptopic->id() == ::id_click)
      {

         if(ptopic->user_interaction_id() == "switcher_toggle")
         {

            ::pointer<impact>pimpact = m_pimpact;

            pimpact->m_prender->m_bLite = !pimpact->m_prender->m_bLite;

            ptopic->m_bRet = true;
            return;

         }
         else if(ptopic->user_interaction_id() == "browser_toggle")
         {

            m_pimpact->m_prender->m_bLite = !m_pimpact->m_prender->m_bLite;


            m_pimpact->on_layout(pgraphics);

            ptopic->m_bRet = true;
            return;

         }

      }

      ::user::split_impact::handle(ptopic, phandlercontext);

   }

   void switcher_impact::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::split_impact::_001OnNcDraw(pgraphics);

   }


   void switcher_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::split_impact::_001OnDraw(pgraphics);

   }


} // namespace browser



