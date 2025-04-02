#include "framework.h"


namespace simple_drawing
{


   main_impact::main_impact(::particle * pparticle):
      object(pparticle),
      ::user::split_layout(pparticle),
      ::user::split_view(pparticle),
      ::userex::split_view(pparticle),
      place_holder_container(pparticle)
   {

      m_ptopimpact = NULL;
      m_pimpact    = NULL;
      m_flagNonClient.add(e_non_client_background);
      m_flagNonClient.add(e_non_client_focus_rect);


   }


   main_impact::~main_impact()
   {

   }


   void main_impact::assert_ok() const
   {

      ::user::split_view::assert_ok();

   }


   void main_impact::dump(dump_context & dumpcontext) const
   {

      ::user::split_view::dump(dumpcontext);

   }


   void main_impact::handle(::topic * ptopic, ::handler_context * pcontext)
   {

      ::user::split_view::handle(ptopic, pcontext);

   }


   void main_impact::on_create_split_impact()
   {

      if(get_pane_count() > 0)
         return;

      int iPane;

      if (papp->m_bMultiverseChat)
      {

         SetPaneCount(2);

         SetSplitOrientation(e_orientation_horizontal);

         set_position(0, 31);

         initialize_split_layout();

         m_ptopimpact = host_view < ::userex::top_view >(0, "top_view");

         if (m_ptopimpact == NULL)
         {

            message_box(NULL, "Could not create folder edit impact");

         }

         SetPane(0, m_ptopimpact, false);

         iPane = 1;

      }
      else
      {

         SetPaneCount(1);

         initialize_split_layout();

         iPane = 0;

      }

      //m_pimpact = create_view < lite_view >();

      m_pimpact = host_view < impact >(iPane, "simple_drawing_view");

      if(m_pimpact == NULL)
      {

         message_box(NULL,"Could not create file list ::user::impact");

      }

      ::pointer<::userex::top_edit_view>peditview = get_child_by_id("top_edit_view");

      if(peditview.is_set())
      {

         string strText;

         m_pimpact->datastream()->get("cur_text",strText);

         peditview->set_text(strText, ::e_source_initialize);

      }

//      SetPane(iPane,m_pimpact,false);

   }


   void main_impact::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::split_view::_001OnNcDraw(pgraphics);

   }


   void main_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::split_view::_001OnDraw(pgraphics);

   }


   bool main_impact::BaseOnControlEvent(::user::control_event * pevent)
   {

      if(ptopic->id() == ::id_click)
      {

         if(ptopic->user_interaction_id() == "simple_drawing_toggle")
         {

            m_pimpact->on_layout(pgraphics);

            return true;

         }

      }

      return false;

   }

} // namespace simple_drawing



