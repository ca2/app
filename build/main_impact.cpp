#include "framework.h"


namespace app_core_build
{


   main_impact::main_impact()
   {

      m_ptopview = nullptr;
      m_pimpact    = nullptr;
      m_flagNonClient.add(e_non_client_background);
      m_flagNonClient.add(e_non_client_focus_rect);
      m_strImpactId = "hellomultiverse_impact";


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


   document * main_impact::get_document()
   {

      return  ::user::impact::get_document()->cast < document >();

   }


   void main_impact::on_create_split_impact()
   {

      if(get_pane_count() > 0)
      {
         
         return;
         
      }

      int iPane;

      if (m_papp->m_bMultiverseChat)
      {

         SetPaneCount(2);

         SetSplitOrientation(e_orientation_horizontal);

         set_position(0, 31);

         initialize_split_layout();

         m_ptopview = create_impact < ::userex::top_impact >(nullptr, get_pane_holder(0), "top_impact");

         if (m_ptopview == nullptr)
         {

            output_error_message("Could not create folder edit impact");

         }

         iPane = 1;

      }
      else
      {

         SetPaneCount(1);

         initialize_split_layout();

         iPane = 0;

      }

      m_pimpact = create_impact < ::app_core_build::impact >(nullptr,get_pane_holder(iPane), m_strImpactId);

      if(m_pimpact == nullptr)
      {

         output_error_message("Could not create file list ::user::impact");

      }


   }


   void main_impact::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::split_impact::_001OnNcDraw(pgraphics);

   }


   void main_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::split_impact::_001OnDraw(pgraphics);

   }


   //void main_impact::handle(::topic * ptopic, ::context * pcontext)
   //{

   //   if(ptopic->m_atom == ::id_click)
   //   {

   //      if(ptopic->user_interaction()->m_atom == "hellomultiverse_toggle")
   //      {

   //         m_pimpact->m_prender->m_bLite = !m_pimpact->m_prender->m_bLite;

   //         m_pimpact->set_need_layout();

   //         ptopic->m_bRet = true;

   //         return;

   //      }

   //   }

   //   ::user::split_impact::handle(ptopic, pcontext);

   //}


} // namespace app_core_build



