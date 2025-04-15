#include "framework.h"


namespace turboc
{


   top_impact::top_impact(::particle * pparticle):
      ::object(pparticle),
      ::user::split_layout(pparticle),
      ::user::split_impact(pparticle),
      place_holder_container(pparticle)
   {

   }


   top_impact::~top_impact()
   {

   }


   void top_impact::assert_ok() const
   {

      ::user::split_impact::assert_ok();

   }


   void top_impact::dump(dump_context & dumpcontext) const
   {

      ::user::split_impact::dump(dumpcontext);

   }


   void top_impact::on_update(::aura::impact * pSender,e_update eupdate,object* pupdate)
   {
      ::user::split_impact::handle(ptopic, phandlercontext);
   }


   void top_impact::on_create_split_impact()
   {

      if(get_pane_count() > 0)
         return;

      SetPaneCount(2);

      SetSplitOrientation(e_orientation_vertical);

      set_position_rate(0,0.84);

      initialize_split_layout();

      m_peditimpact = create_impact < edit_impact >();

      if(m_peditimpact == NULL)
      {

         message_box(NULL,"Could not create folder edit impact");

      }

      m_peditimpact->m_ptopimpact = this;

      SetPane(0,m_peditimpact,false);

      if(id() == "turboc_top")
      {

         m_ptoggleimpact = create_impact < toggle_impact >(NULL,::int_rectangle(),NULL,"turboc_toggle");

      }
      else
      {

         m_ptoggleimpact = create_impact < toggle_impact >(NULL,::int_rectangle(),NULL,"switcher_toggle");

      }

      if(m_ptoggleimpact == NULL)
      {

         message_box(NULL,"Could not create file list ::aura::impact");

      }

      m_ptoggleimpact->m_ptopimpact = this;

      SetPane(1,m_ptoggleimpact,false);


   }





} // namespace turboc



