#include "framework.h"
#include "acme/constant/timer.h"


namespace userstack
{


   impact::impact(::particle * pparticle) :
      ::object(pparticle),
      m_pfont(e_create)
   {

      m_pfont->create_point_font(pnode->font_name(e_font_sans_ex), 8.4);
      m_bDestroy = false;
      m_iV = 123;
      m_iVH = 49;
      m_iVW = 123;
      m_i_veriwell = 256;
      m_i_veriwell_h = 49;
      m_i_veriwell_w = 74;
      m_i_winactionarea = 4;
      m_i_winactionarea_h = 49;
      m_i_winactionarea_w = 49;
      m_ppaneimpact = nullptr;

   }


   impact::~impact()
   {

   }


   void impact::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_destroy, pchannel, this, &impact::on_message_destroy);
      MESSAGE_LINK(e_message_paint, pchannel, this, &impact::_001OnPaint);
      MESSAGE_LINK(e_message_create, pchannel, this, &impact::on_message_create);
      MESSAGE_LINK(e_message_context_menu, pchannel, this, &impact::on_message_context_menu);
      //MESSAGE_LINK(e_message_set_cursor, pchannel, this, &impact::on_message_set_cursor);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &impact::on_message_left_button_up);

//

   }
   /////////////////////////////////////////////////////////////////////////////
   // ::impact drawing

   void impact::OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      __UNREFERENCED_PARAMETER(pgraphics);

   }

   /////////////////////////////////////////////////////////////////////////////
   // ::impact diagnostics


   void impact::assert_ok() const
   {
      ::user::impact::assert_ok();
   }

   void impact::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }


   /////////////////////////////////////////////////////////////////////////////
   // ::impact message handlers

   // vmpLightImpact.cpp : implementation of the ::impact class
   //


   /////////////////////////////////////////////////////////////////////////////
   // ::impact


   bool impact::pre_create_window(::user::system * pusersystem)
   {

      return ::user::impact::pre_create_window(pusersystem);
   }


   void impact::handle(::topic * ptopic, ::context * pcontext)
   {

      __UNREFERENCED_PARAMETER(ptopic);

   }


   void impact::on_message_destroy(::message::message * pmessage)
   {
      ::user::impact::on_message_destroy(pmessage);

   }



   void impact::_001OnPaint(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);


   }


   void impact:: _001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {


   }

   void impact::on_message_create(::message::message * pmessage)
   {
      if(pmessage->previous())
         return;

      set_timer(888888, 2000, nullptr);

      ::pointer<frame>pframe = get_typed_parent < frame > ();

      pframe->m_pimpact = this;
      pframe->m_pdocument = get_document();


      string strImageDir = directory()->appdata() / "image";
      m_straImagePath.m_pprovider = get_app();
      m_straImagePath.rls(strImageDir);

      for(int i = 0; i < m_straImagePath.get_size();)
      {
         if(directory()->is(m_straImagePath[i]))
         {
            m_straImagePath.erase_at(i);
         }
         else
         {
            i++;
         }
      }



      set_timer(e_timer_backimpact, 83, nullptr);  // maximum. 12 fps
      set_timer(21977, 20 * 1000, nullptr);  // maximum. 12 fps

      check_apps();

/*      m_pimageBk = load_matter_image("casweden1.png");


/*      m_pimageV = load_matter_image("wild_mountains_and_valleys-123.png");
/*      m_pimage_veriwell = load_matter_image("veriwell_2008_green_h49.png");
/*      m_pimage_winactionarea = load_matter_image("winactionarea.png");

      if(!psession->m_bShowPlatform)
      {
         return;
      }

      m_ppaneimpact = (create_impact(::type < pane_impact >(), get_document(), this, 102));


   }

   void impact::on_message_context_menu(::message::message * pmessage)
   {
//      ::pointer<::message::context_menu>pcontextmenu(pmessage);
//      ::int_point point = pcontextmenu->GetPoint();

   }

   void impact::_001OnTabClick(int iTab)
   {
      if(iTab == 1)
      {
         message_box(nullptr, "Playlist");
      }
   }

   void impact::on_message_set_cursor(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      pmouse->m_ecursor = cursor_arrow;

      pmessage->previous();

   }

   void impact::pre_translate_message(::message::message * pmessage)
   {
      ::user::impact::pre_translate_message(pmessage);
   }


   ::user::document * impact::get_document()
   {

      return ::user::impact::get_document();

   }


   void impact::on_timer(::timer * ptimer)
   {

      BASE::on_timer(ptimer);

      switch(ptimer->m_uTimer)
      {
      case e_timer_backimpact:
      {
         //gcom::backimpact::user_interaction::image_change_post_event(gcom::backimpact::event_timer);
      }
      break;
      }

      if(ptimer->m_uTimer == 21977)
      {
         check_apps();
      }
      else if(ptimer->m_uTimer == 888888)
      {
         psession->check_topic_file_change();
      }

   }


   void impact::GetAreaThumbRect(::int_rectangle * lprect, int iArea)
   {
      
      ::int_rectangle rectangleX = this->rectangle();
      
      if(iArea == m_iV)
      {
         lprect->bottom() = rectangleX.bottom();
         lprect->top() = lprect->bottom() - m_iVH;
         lprect->left() = 1;
         lprect->right() = lprect->left() + m_iVW;
      }
      else if(iArea == m_i_veriwell)
      {
         lprect->bottom() = rectangleX.bottom();
         lprect->top() = lprect->bottom() - m_i_veriwell_h;
         lprect->left() = 1 + m_iVW + 5;
         lprect->right() = lprect->left() + m_i_veriwell_w;
      }
      else if(iArea == m_i_winactionarea)
      {
         lprect->bottom() = rectangleX.bottom();
         lprect->top() = lprect->bottom() - m_i_winactionarea_h;
         lprect->left() = 1 + m_iVW + 5 + m_i_veriwell_w + 5;
         lprect->right() = lprect->left() + m_i_winactionarea_w;
      }
   }


   void impact::on_message_left_button_up(::message::message * pmessage)
   {
      auto pmouse = pmessage->m_union.m_pmouse;
      pmouse->m_lresult = 1;
      kill_timer(5432180);
      auto point = pmouse->m_point;
      screen_to_client()(point);
   }

   void impact::check_apps()
   {
      //   if(::IsDebuggerPresent())
      //    return;
      //if(!m_bEnsureApps)
      // return;
#ifdef WINDOWS_DESKTOP
      if(::IsWindow(m_oswindowWinactionarea) &&
            ::IsWindow(m_oswindowCommand) &&
            ::IsWindow(m_oswindowWinutil) &&
            ::IsWindow(m_oswindowBergedge))
      {
         return;
      }
      m_oswindowWinservice1       =  ::FindWindowW(nullptr, L"::ca2::account::message_wnd::winservice_1");
      m_oswindowWinactionarea     =  ::FindWindowW(nullptr, L"::ca2::account::message_wnd::winactionarea");
      m_oswindowCommand           =  ::FindWindowW(nullptr, L"::ca2::account::message_wnd::command");
      m_oswindowWinutil           =  ::FindWindowW(nullptr, L"::ca2::account::message_wnd::winutil");
      m_oswindowBergedge          =  ::FindWindowW(nullptr, L"::ca2::account::message_wnd::bergedge");
#else
      throw ::exception(todo);
#endif
   }


   ::item_pointer impact::on_hit_test(const ::int_point &point, ::user::e_zorder ezorder)
   {
      
      ::int_rectangle rectangleArea;
      
      GetAreaThumbRect(rectangleArea, m_iV);

      if(rectangleArea.contains(item.m_pointHitTest))
      {
      
         item ={ ::e_element_area, m_iV };

         return;
         
      }

      GetAreaThumbRect(rectangleArea, m_i_veriwell);

      if(rectangleArea.contains(item.m_pointHitTest))
      {

         item = { ::e_element_area, m_i_veriwell };

         return;

      }

      GetAreaThumbRect(rectangleArea, m_i_winactionarea);

      if(rectangleArea.contains(item.m_pointHitTest))
      {
         
         item = { ::e_element_area, m_i_winactionarea };

         return;

      }
      
      item = ::e_element_none;
      
   }


   unsigned int c_cdecl impact::ThreadProcShowWindow(LPVOID lpparam)
   {
      __UNREFERENCED_PARAMETER(lpparam);
      return 0;
   }


   void impact::mt_show_window(oswindow oswindow, int iShow)
   {
      __UNREFERENCED_PARAMETER(oswindow);
      __UNREFERENCED_PARAMETER(iShow);
   }

   /*void impact::on_layout(::draw2d::graphics_pointer & pgraphics)
   {
      auto rectangleX = this->rectangle();
      if(m_ppaneimpact != nullptr)
      {
         m_ppaneimpact->set_window_position(e_zorder_top, rectangleX.top(), rectangleX.left(), rectangleX.width(), rectangleX.height(), SWP_SHOWWINDOW);
      }
      else
      {
         user::interaction * pinteraction = get_top_child();
         if(pinteraction != nullptr)
         {
            pinteraction->set_window_position(e_zorder_top, rectangleX.top(), rectangleX.left(), rectangleX.width(), rectangleX.height(), SWP_SHOWWINDOW);
         }
      }
      ::user::show < ::user::interaction >::on_layout(pgraphics);
      gcom::backimpact::user::interaction::on_layout(pgraphics);
   }*/

   void impact::_000OnMouse(::message::mouse * pmouse)
   {
      try
      {
         if(!_001IsPointInside(pmouse->m_point))
            return;
      }
      catch(...)
      {
         return;
      }
      // these try catchs are needed for multi threading : multi threaded windows: the hell
      // Now I understand why Microsoft (TM) Windows (R) windows are single threaded.
      user::interaction * pinteraction = top_child();
      try
      {
         while(pinteraction != nullptr)
         {

            try
            {

               if(pinteraction->is_window_visible() && pinteraction->_001IsPointInside(pmouse->m_point))
               {

                  try
                  {

                     pinteraction->_000OnMouse(pmouse);

                     if (pmouse->m_bRet)
                     {

                        return;

                     }

                  }
                  catch(...)
                  {

                  }

               }

               pinteraction = pinteraction->under_sibling();

            }
            catch(...)
            {

            }

         }

      }
      catch(...)
      {

      }

      try
      {

         if(m_pimpl == nullptr)
            return;

         route_message(pmouse);

         if(pmouse->m_lresult != 0)
            return;

      }
      catch(...)
      {
      }
   }


}  // namespace userstack



