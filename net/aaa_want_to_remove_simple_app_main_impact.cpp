#include "framework.h"


namespace simple_drawing
{


   main_impact::main_impact(::object * pobject):
      object(pobject),
      ::user::split_layout(pobject),
      ::user::split_impact(pobject),
      ::userex::split_impact(pobject),
      place_holder_container(pobject)
   {

      m_ptopview = NULL;
      m_pimpact    = NULL;
      m_flagNonClient.add(non_client_background);
      m_flagNonClient.add(non_client_focus_rect);


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


   void main_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::split_impact::handle(ptopic, pcontext);

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

         m_ptopview = host_impact < ::userex::top_impact >(0, "top_impact");

         if (m_ptopview == NULL)
         {

            message_box(NULL, "Could not create folder edit impact");

         }

         SetPane(0, m_ptopview, false);

         iPane = 1;

      }
      else
      {

         SetPaneCount(1);

         initialize_split_layout();

         iPane = 0;

      }

      //m_pimpact = create_impact < lite_impact >();

      m_pimpact = host_impact < impact >(iPane, "simple_drawing_impact");

      if(m_pimpact == NULL)
      {

         message_box(NULL,"Could not create file list ::user::impact");

      }

      __pointer(::userex::top_edit_impact) peditview = get_child_by_id("top_edit_impact");

      if(peditview.is_set())
      {

         string strText;

         m_pimpact->data_get("cur_text",strText);

         peditview->_001SetText(strText, ::e_source_initialize);

      }

//      SetPane(iPane,m_pimpact,false);

   }


   void main_impact::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::split_impact::_001OnNcDraw(pgraphics);

   }


   void main_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::split_impact::_001OnDraw(pgraphics);

   }


   bool main_impact::BaseOnControlEvent(::user::control_event * pevent)
   {

      if(ptopic->m_atom == ::id_click)
      {

         if(ptopic->user_element_id() == "simple_drawing_toggle")
         {

            m_pimpact->on_layout(pgraphics);

            return true;

         }

      }

      return false;

   }

} // namespace simple_drawing


