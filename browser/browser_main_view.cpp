#include "framework.h"


namespace browser
{


   main_impact::main_impact(::object * pobject):
      object(pobject),
      ::user::split_layout(pobject),
      ::user::split_view(pobject),
      place_holder_container(pobject)
   {

      m_ptopview = nullptr;
      m_pimpact    = nullptr;
      m_flagNonClient.add(non_client_background);
      m_flagNonClient.add(non_client_focus_rect);


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


   void main_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::split_view::handle(ptopic, pcontext);

   }


   void main_impact::on_create_split_impact()
   {

      if(get_pane_count() > 0)
         return;

      int iPane;

      if (papplication->m_bBrowserChat)
      {

         SetPaneCount(2);

         SetSplitOrientation(e_orientation_horizontal);

         set_position(0, 31);

         initialize_split_layout();

         m_ptopview = create_view < ::userex::top_view >(nullptr, nullptr, "top_view");

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

      //m_pimpact = create_view < lite_view >();

      m_pimpact = create_view < impact >(nullptr, get_pane_holder(iPane), "browser_view");

      if(m_pimpact == nullptr)
      {

         message_box(nullptr,"Could not create file list ::user::impact");

      }

      __pointer(::userex::top_edit_view) peditview = get_child_by_id("top_edit_view");

      peditview->m_bParseDataPacks = true;

      if(peditview.is_set())
      {

         string strText;

         m_pimpact->data_get("cur_text", strText);

         peditview->_001SetText(strText, ::e_source_initialize);

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


   void main_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      if(ptopic->m_atom == ::id_click)
      {

         if(ptopic->user_element_id() == "browser_toggle")
         {

            m_pimpact->m_prender->m_bLite = !m_pimpact->m_prender->m_bLite;


            m_pimpact->on_layout(pgraphics);

            ptopic->m_bRet = true;
            return;

         }

      }

      ::user::split_view::handle(ptopic, pcontext);

   }


} // namespace browser



