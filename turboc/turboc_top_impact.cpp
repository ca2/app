#include "framework.h"


namespace turboc
{


   top_impact::top_impact(::object * pobject):
      ::object(pobject),
      ::user::split_layout(pobject),
      ::user::split_impact(pobject),
      place_holder_container(pobject)
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
      ::user::split_impact::handle(ptopic, pcontext);
   }


   void top_impact::on_create_split_impact()
   {

      if(get_pane_count() > 0)
         return;

      SetPaneCount(2);

      SetSplitOrientation(e_orientation_vertical);

      set_position_rate(0,0.84);

      initialize_split_layout();

      m_peditview = create_view < edit_impact >();

      if(m_peditview == NULL)
      {

         message_box(NULL,"Could not create folder edit impact");

      }

      m_peditview->m_ptopview = this;

      SetPane(0,m_peditview,false);

      if(m_atom == "turboc_top")
      {

         m_ptoggleview = create_view < toggle_impact >(NULL,::rectangle_i32(),NULL,"turboc_toggle");

      }
      else
      {

         m_ptoggleview = create_view < toggle_impact >(NULL,::rectangle_i32(),NULL,"switcher_toggle");

      }

      if(m_ptoggleview == NULL)
      {

         message_box(NULL,"Could not create file list ::aura::impact");

      }

      m_ptoggleview->m_ptopview = this;

      SetPane(1,m_ptoggleview,false);


   }





} // namespace turboc



