#include "framework.h"


namespace browser
{


   switcher_view::switcher_view(::object * pobject):
      object(pobject),
      ::user::split_layout(pobject),
      ::user::split_view(pobject),
      place_holder_container(pobject)
   {

      m_pimpact = nullptr;

      m_ptopview = nullptr;

   }


   switcher_view::~switcher_view()
   {

   }


   void switcher_view::assert_ok() const
   {

      ::user::split_view::assert_ok();

   }


   void switcher_view::dump(dump_context & dumpcontext) const
   {

      ::user::split_view::dump(dumpcontext);

   }


   void switcher_view::handle(::topic * ptopic, ::context * pcontext)
   {
      ::user::split_view::handle(ptopic, pcontext);
   }


   void switcher_view::on_create_split_impact()
   {

      if(get_pane_count() > 0)
         return;

      SetPaneCount(2);

      SetSplitOrientation(e_orientation_horizontal);

      set_position(0,24);

      initialize_split_layout();

      m_ptopview = create_view < ::userex::top_view >(nullptr, get_pane_holder(0),"top_view");

      if(m_ptopview == nullptr)
      {

         message_box(nullptr,"Could not create folder edit impact");

      }

      //SetPane(0,m_ptopview,false);

      m_pimpact = create_view < impact >(nullptr,get_pane_holder(1),"browser_switcher_view");

      if(m_pimpact == nullptr)
      {

         message_box(nullptr,"Could not create file list ::user::impact");

      }

   }



   void switcher_view::handle(::topic * ptopic, ::context * pcontext)
   {

      if(ptopic->m_atom == ::id_click)
      {

         if(ptopic->user_element_id() == "switcher_toggle")
         {

            __pointer(impact) pimpact = m_pimpact;

            pimpact->m_prender->m_bLite = !pimpact->m_prender->m_bLite;

            ptopic->m_bRet = true;
            return;

         }
         else if(ptopic->user_element_id() == "browser_toggle")
         {

            m_pimpact->m_prender->m_bLite = !m_pimpact->m_prender->m_bLite;


            m_pimpact->on_layout(pgraphics);

            ptopic->m_bRet = true;
            return;

         }

      }

      ::user::split_view::handle(ptopic, pcontext);

   }

   void switcher_view::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::split_view::_001OnNcDraw(pgraphics);

   }


   void switcher_view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::split_view::_001OnDraw(pgraphics);

   }


} // namespace browser



