#include "framework.h"


namespace helloworld
{


   main_impact::main_impact(::particle * pparticle):
      object(pparticle),
      ::user::split_layout(pparticle),
      ::user::split_impact(pparticle),
      place_holder_container(pparticle)
   {

      m_ptopview = nullptr;
      m_pimpact    = nullptr;
      m_flagNonClient.add(e_non_client_background);
      m_flagNonClient.add(e_non_client_focus_rect);


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

      if (papp->m_bWorldChat)
      {

         SetPaneCount(2);

         SetSplitOrientation(e_orientation_horizontal);

         set_position(0, 31);

         initialize_split_layout();

         m_ptopview = create_impact < ::userex::top_impact >(nullptr, nullptr, "top_impact");

         if (m_ptopview == nullptr)
         {

            message_box(nullptr, "Could not create folder edit impact");

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

      m_pimpact = create_impact < impact >(nullptr, get_pane_holder(iPane), "helloworld_impact");

      if(m_pimpact == nullptr)
      {

         message_box(nullptr,"Could not create file list ::user::impact");

      }

      ::pointer<::userex::top_edit_impact>peditview = get_child_by_id("top_edit_impact");

      if(peditview.is_set())
      {

         string strText;

         m_pimpact->datastream()->get("cur_text",strText);

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


   void main_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      if(ptopic->m_atom == ::id_click)
      {

         if(ptopic->user_element_id() == "helloworld_toggle")
         {

            m_pimpact->m_prender->m_bLite = !m_pimpact->m_prender->m_bLite;


            m_pimpact->on_layout(pgraphics);

            return true;

         }

      }

      return false;

   }

} // namespace helloworld



