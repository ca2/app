#include "framework.h"


namespace turboc
{


   top_view::top_view(::context_object * pcontextobject):
      ::object(pobject),
      ::user::split_layout(pobject),
      ::user::split_view(pobject),
      place_holder_container(pobject)
   {

   }


   top_view::~top_view()
   {

   }


   void top_view::assert_valid() const
   {

      ::user::split_view::assert_valid();

   }


   void top_view::dump(dump_context & dumpcontext) const
   {

      ::user::split_view::dump(dumpcontext);

   }


   void top_view::on_update(::aura::impact * pSender,e_update eupdate,object* pupdate)
   {
      ::user::split_view::on_subject(psubject, pcontext);
   }


   void top_view::on_create_split_impact()
   {

      if(get_pane_count() > 0)
         return;

      SetPaneCount(2);

      SetSplitOrientation(e_orientation_vertical);

      set_position_rate(0,0.84);

      initialize_split_layout();

      m_peditview = create_view < edit_view >();

      if(m_peditview == NULL)
      {

         message_box(NULL,"Could not create folder edit view");

      }

      m_peditview->m_ptopview = this;

      SetPane(0,m_peditview,false);

      if(m_id == "turboc_top")
      {

         m_ptoggleview = create_view < toggle_view >(NULL,::rectangle_i32(),NULL,"turboc_toggle");

      }
      else
      {

         m_ptoggleview = create_view < toggle_view >(NULL,::rectangle_i32(),NULL,"switcher_toggle");

      }

      if(m_ptoggleview == NULL)
      {

         message_box(NULL,"Could not create file list ::aura::impact");

      }

      m_ptoggleview->m_ptopview = this;

      SetPane(1,m_ptoggleview,false);


   }





} // namespace turboc



