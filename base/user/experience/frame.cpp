#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/experience/_experience.h"
#endif


namespace experience
{


   frame::frame()
   {

      m_bHollow = true;
      m_bFirstLayoutDone = false;

      //m_rectControlBoxMarginFullScreen.set(0, 0, 0, 0);
      //m_rectControlBoxMarginZoomed.set(0, 0, 0, 0);
      //m_rectControlBoxMarginNormal.set(0, 0, 0, 0);

      m_rectControlBoxMargin.set(5, 5, 5, 5);

      m_rectMarginFullScreen.set(0, 0, 0, 0);
      m_rectMarginZoomed.set(0, 0, 0, 0);
      m_rectMarginNormal.set(5, 5, 5, 5);

      m_iControlBoxRight = 0;
      m_bControlBoxAlignRight = true;
      m_bInitialControlBoxPosition = true;

   }


   frame::~frame()
   {

   }


   //void frame::set_style(const char * pszStyle)
   //{

   //   m_strStyle = pszStyle;

   //}

   
   int frame::adjust_client_height(int iHeight)
   {

      return iHeight + get_caption_height();

   }


   int frame::adjust_client_width(int iWidth)
   {

      return iWidth + 20;
      
   }


   void frame::OnMove(__pointer(::user::interaction) pframewindow)
   {

      UNREFERENCED_PARAMETER(pframewindow);

   }


   void frame::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      UNREFERENCED_PARAMETER(pgraphics);

   }


   void frame::frame_on_attach()
   {

      if (m_pframewindow)
      {

         if (m_pframewindow->size_manager() != nullptr)
         {

            m_pframewindow->size_manager()->SetSWPFlags(0);

         }

      }

   }


   void frame::frame_on_detach()
   {

   }


   bool frame::is_control_box_moveable()
   {

      return false;

   }


   size frame::GetMinSize()
   {

      return m_pframewindow->get_window_minimum_size();

   }


   void frame::OnNcCalcSize(RECT32 * prect)
   {

      if(m_pframewindow->m_bUseNc)
      {

         //calc_window_client_rect(prect,rect(prect));


      }

   }


   void frame::OnActivate()
   {
   }


   bool frame::_001OnCommand(WPARAM wparam, LPARAM lparam, LRESULT & lresult)

   {

      UNREFERENCED_PARAMETER(wparam);
      UNREFERENCED_PARAMETER(lparam);

      UNREFERENCED_PARAMETER(lresult);

      return false;

   }


   void frame::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto pframewindow = m_pframewindow;

      sync_lock sl(pframewindow->mutex());

      ::rect rectWindow;

      pframewindow->get_window_rect(rectWindow);

      if (rectWindow.is_empty())
      {

         return;

      }

      if (m_pcontrolbox.is_set())
      {

         m_pcontrolbox->reset_layout(pgraphics);

      }

      m_iCaptionHeight = calc_caption_height();

      ::rect rectClient;

      title_bar_layout();

      update_window_client_rect();

      pframewindow->get_client_rect(rectClient);

      get_window_client_rect(rectClient);

      if (pframewindow != nullptr)
      {

         if (pframewindow->GetStyle() & FWS_SNAPTOBARS)
         {

            ::rect rect(0, 0, 32767, 32767);

            pframewindow->RepositionBars(0, 0xffff, "pane_first", pframewindow->reposQuery,
                                 &rect, &rect, FALSE);
            rect.offset(rectClient.top_left());
            ::rect rectBorder;
            pframewindow->GetBorderRect(rectBorder);
            pframewindow->RepositionBars(0, 0xffff, "pane_first", pframewindow->reposExtra,
                                 &rectBorder, &rect, TRUE);
            pframewindow->SetBorderRect(rectBorder);
            pframewindow->CalcWindowRect(&rect);
            OnNcCalcSize(&rect);
            //::rect rectSnap(0, 0, 0, 0);
            //CalcWndClient(rectSnap, rectSnap);
            //rect.deflate(rectSnap);
            pframewindow->set_size(rect.size());
            pframewindow->display();
//                  pframewindow->display();(zorder_none, 0, 0, rect.width(), rect.height(),
//                                     SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);

         }
         else
         {

            ::rect rectBorder;

            pframewindow->GetBorderRect(rectBorder);

            pframewindow->RepositionBars(0, 0xffff, "pane_first", pframewindow->reposExtra, &rectBorder, &rectClient);

            pframewindow->SetBorderRect(rectBorder);

         }

      }

   }


   void frame::on_reposition()
   {


   }


   color32_t frame::get_border_main_body_color()
   {

      return m_colorMoveableBorder;

   }


   bool frame::_001OnLButtonDown(::message::mouse * pmouse)
   {

      if(!m_pframewindow->layout().is_zoomed() && !m_pframewindow->layout().is_full_screen())
      {

         if (m_pframewindow->size_manager()->_001OnLButtonDown(pmouse))
         {

            return true;

         }

         if (m_pframewindow->move_manager()->_001OnLButtonDown(pmouse))
         {

            return true;

         }

      }

      return false;

   }


   bool frame::_001OnLButtonUp(::message::mouse * pmouse)
   {

      if(!m_pframewindow->layout().is_zoomed() && !m_pframewindow->layout().is_full_screen())
      {

         if(m_pframewindow->dock_manager()->_001OnLButtonUp(pmouse))
            return true;

         if(m_pframewindow->size_manager()->_001OnLButtonUp(pmouse))
            return true;

         if(m_pframewindow->move_manager()->_001OnLButtonUp(pmouse))
            return true;

      }

      return false;
   }


   bool frame::_001OnMouseMove(::message::mouse * pmouse)
   {

      auto psession = Session;

      psession->m_pointCursor = pmouse->m_point;

      if(!m_pframewindow->layout().is_zoomed() && !m_pframewindow->layout().is_full_screen())
      {

         if (!m_pframewindow->move_manager()->window_is_moving()
            && !m_pframewindow->size_manager()->window_is_sizing())
         {

            if (m_pframewindow->dock_manager()->window_is_docking())
            {

               __pointer(::message::mouse) pmouseHold = pmouse;

               //m_pframewindow->prodevian_pred([this, pmouseHold->()
               //{

                  m_pframewindow->dock_manager()->_001OnMouseMove(pmouseHold);

               //});

               return true;

            }
            else
            {

               if (m_pframewindow->dock_manager()->_001OnMouseMove(pmouse))
               {

                  return true;

               }

            }

         }

         if (!m_pframewindow->size_manager()->window_is_sizing())
         {

            if (m_pframewindow->move_manager()->window_is_moving())
            {

               __pointer(::message::mouse) pmouseHold = pmouse;

               //m_pframewindow->prodevian_pred([this, pmouseHold->()
               //{

                  m_pframewindow->move_manager()->_001OnMouseMove(pmouseHold);

               //});

               return true;

            }
            else
            {

               if (m_pframewindow->move_manager()->_001OnMouseMove(pmouse))
               {

                  return true;

               }

            }

         }

         if (m_pframewindow->size_manager()->window_is_sizing())
         {

            __pointer(::message::mouse) pmouseHold = pmouse;

            //m_pframewindow->prodevian_pred([this, pmouseHold->()
            //{

               m_pframewindow->size_manager()->_001OnMouseMove(pmouseHold);

            //});

            return true;

         }
         else
         {

            if (m_pframewindow->size_manager()->_001OnMouseMove(pmouse))
            {

               return true;

            }

         }

      }

      return false;

   }


   bool frame::_001OnNcLButtonDown(::message::mouse * pmouse)
   {

      if(!m_pframewindow->layout().is_zoomed() && !m_pframewindow->layout().is_full_screen())
      {

         if(m_pframewindow->dock_manager()->_001OnLButtonDown(pmouse))
            return true;

         if(m_pframewindow->size_manager()->_001OnLButtonDown(pmouse))
            return true;

         if(m_pframewindow->move_manager()->_001OnLButtonDown(pmouse))
            return true;

      }

      return false;
   }

   bool frame::_001OnNcLButtonUp(::message::mouse * pmouse)
   {

      if(!m_pframewindow->layout().is_zoomed() && !m_pframewindow->layout().is_full_screen())
      {

         if (m_pframewindow->dock_manager()->_001OnLButtonUp(pmouse))
         {

            return true;

         }

         if (m_pframewindow->size_manager()->_001OnLButtonUp(pmouse))
         {

            return true;

         }

         if (m_pframewindow->move_manager()->_001OnLButtonUp(pmouse))
         {

            return true;

         }

      }

      return false;

   }


   bool frame::_001OnNcMouseMove(::message::mouse * pmouse)
   {

      if(!m_pframewindow->layout().is_zoomed() && !m_pframewindow->layout().is_full_screen())
      {

         if(!m_pframewindow->move_manager()->window_is_moving()
               && !m_pframewindow->size_manager()->window_is_sizing()
               && m_pframewindow->dock_manager()->_001OnMouseMove(pmouse))
            return true;

         if(!m_pframewindow->move_manager()->window_is_moving()
               && m_pframewindow->size_manager()->_001OnMouseMove(pmouse))
            return true;

         if(m_pframewindow->move_manager()->_001OnMouseMove(pmouse))
            return true;

      }

      return false;

   }


   bool frame::_001OnNcHitTest(const ::point & point,LRESULT & nHitTest)
   {

      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(nHitTest);

      return false;

   }


   bool frame::_001OnTimer(::u32 uEvent)
   {

      UNREFERENCED_PARAMETER(uEvent);

      return false;

   }


   //bool frame::_001OnSize(u32 nType,i32 cx,i32 cy)
   //{

   //   UNREFERENCED_PARAMETER(cx);
   //   UNREFERENCED_PARAMETER(cy);

   //   return false;

   //}


/*       bool frame::_001OnMove(i32 x, i32 y)
   {

      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);

      return false;

   }*/


   i32 frame::get_caption_height()
   {

      return m_iCaptionHeight;

   }


   i32 frame::calc_caption_height(edisplay edisplay)
   {

      if (edisplay == e_display_full_screen)
      {

         return 0;

      }

      if (edisplay == e_display_minimal)
      {

         return 0;

      }

      rect rectMargin = get_margin_rect();

      rect rectControlBoxMargin = get_control_box_margin_rect();

      i32 iMargin = rectMargin.top + rectControlBoxMargin.top + rectControlBoxMargin.bottom;

      i32 iCaptionHeight = 0;

      if (m_pcontrolbox)
      {

         iCaptionHeight = max(m_pcontrolbox->calc_control_box_height() + iMargin, iCaptionHeight);

      }

      return iCaptionHeight;

   }


   i32 frame::calc_caption_height()
   {

      return calc_caption_height(m_pframewindow->layout().design().display());

   }


//   i32 frame::calc_control_box_left(bool bLayout)
//   {
//
//      auto pframewindow = m_pframewindow;
//
//      ::rect rectClient;
//
//      pframewindow->get_client_rect(rectClient);
//
//      rect * prectMargin = get_margin_rect();
//
//      //rect * prectControlBox = get_control_box_rect();
//
//      i32 x;
//
//      x = rectClient.right - rectMargin.right - prectControlBox->width();
//
//      return x;
//
//   }


   void frame::title_bar_layout()
   {

      bool bVisible = false;

      auto pframewindow = m_pframewindow;

      if(::is_null(pframewindow))
      {

         return;

      }

      try
      {

         if (m_pframewindow->layout().is_full_screen())
         {

            bVisible = false;

         }
         else if (m_pframewindow->layout().is_this_screen_visible())
         {

            bVisible = true;

         }
         else
         {

            bVisible = false;

         }

      }
      catch (...)
      {

      }

      ::rect rectClient;

      pframewindow->get_client_rect(rectClient);

      if (rectClient.is_empty())
      {

         return;

      }

      rect rectControlBoxMargin = get_control_box_margin_rect();

      rect rectMargin = get_margin_rect();

      i32 iControlBoxWidth = m_pcontrolbox->calc_control_box_normal_width();

      i32 iControlBoxHeight = m_pcontrolbox->calc_control_box_height();

      m_rectCaption.left = rectClient.left + rectMargin.left;
      m_rectCaption.top = rectClient.top + rectMargin.top;
      m_rectCaption.right = rectClient.right - rectMargin.right;
      m_rectCaption.bottom = m_rectCaption.top + iControlBoxHeight + rectControlBoxMargin.top + rectControlBoxMargin.bottom;

      m_rectClient = rectClient;

      m_rectClient.deflate(rectMargin);

      m_iControlBoxPosition = rectClient.right;

      if(m_iControlBoxPosition < rectClient.left)
      {

         m_iControlBoxPosition = rectClient.left;

      }
      else if(m_iControlBoxPosition > rectClient.right - iControlBoxWidth)
      {

         m_iControlBoxPosition = rectClient.right - iControlBoxWidth;

      }


      ::rect rectControlBox;

      rectControlBox.left = m_iControlBoxPosition;
      rectControlBox.right = rectControlBox.left + iControlBoxWidth;
      rectControlBox.top = m_rectCaption.top;
      rectControlBox.bottom = m_rectCaption.bottom;

      if (m_pframewindow->layout().is_this_screen_visible() && !is_iconic(m_pframewindow->layout().design().display()))
      {

         get_control_box()->place(rectControlBox);

      }

      m_rectWindow = rectClient;

      ::rect rectIcon;

      bool bIcon = get_element_rect(rectIcon, ElementTopLeftIcon);

      if (bIcon)
      {

         m_pointWindowIcon.x = rectIcon.left;

      }

      m_pointMoveGripMinimal.x = m_pointWindowIcon.x - 2;

      m_pointMoveGripMinimal.y = rectMargin.top + rectControlBoxMargin.top;

      m_pointWindowIcon.y = rectMargin.top + iControlBoxHeight - rectIcon.height();



      if (bIcon)
      {

         m_rectWindowText.left = rectIcon.right + 5;

      }
      else
      {

         m_rectWindowText.left = m_rectCaption.left + 5;

      }

      m_rectWindowText.top = rectMargin.top;
      m_rectWindowText.right = rectClient.width() - rectMargin.right;
      m_rectWindowText.bottom = m_rectWindowText.top + iControlBoxHeight;

      m_rectCaptionTextBk.left = rectMargin.left;
      m_rectCaptionTextBk.top = rectMargin.top;
      m_rectCaptionTextBk.right = rectClient.width() - rectMargin.right;
      m_rectCaptionTextBk.bottom = iControlBoxHeight;

      if (bVisible)
      {

         get_control_box()->display();

         get_control_box()->order(::zorder_top_most);

      }
      else
      {

         get_control_box()->hide();

      }

      get_control_box()->set_need_layout();

   }


   void frame::on_initialize_experience_frame()
   {


   }


   void frame::on_initialize_appearance()
   {

      if (!m_pcontrolbox)
      {

         __compose(m_pcontrolbox, m_pexperience->m_plibrary->create_object(this, "control_box"));

         m_pcontrolbox->m_pframewindow = m_pframewindow;

         auto pframewindow = m_pframewindow;

         m_pcontrolbox->create_window(pframewindow, 1);

         m_pcontrolbox->update_control_box_buttons();

      }

      on_style_change();

      on_initialize_experience_frame();

   }



   __pointer(control_box) frame::get_control_box()
   {

      return m_pcontrolbox;

   }


   //void frame::update_window_style()
   //{

   //}


   //void frame::update_window()
   //{

   //   update_window_style();

   //}


   string frame::get_default_user_style() const
   {

      return "LightBlue";

   }


   void frame::set_moveable_border_color(const ::color & colorParam)
   {

      m_colorMoveableBorder = colorParam;

      ::color color;

      color = colorParam;
      color.hls_rate(0.0, 0.5, 0.0);
      m_colorMoveableBorderHilight = color.get_rgb() | (0xff << 24);

      color = colorParam;
      color.hls_rate(0.0, -0.3, 0.0);
      m_colorMoveableBorderShadow = color.get_rgb() | (0xff << 24);

      color = colorParam;
      color.hls_rate(8.0, -0.8, 0.0);
      m_colorMoveableBorderDkShadow = color.get_rgb() | (0xff << 24);

      m_colorCaptionTextBk = m_colorMoveableBorderShadow;

   }


   bool frame::get_window_client_rect(RECT32 * prect)
   {

      if (string(type_name()).contains_ci("file"))
      {


         output_debug_string("frame::get_window_client_rect file");

      }

      *prect = m_rectClient;

      return true;

   }


   bool frame::get_draw_client_rect(RECT32 * prect)

   {

      ::rect rect;

      if(!get_window_client_rect(rect))
      {

         return false;

      }

      rect.offset(-rect.top_left());

      *prect = rect;


      return true;

   }


   void frame::update_window_client_rect()
   {

      auto pframewindow  = m_pframewindow;

      ASSERT(pframewindow != nullptr);

      if (pframewindow == nullptr)
      {

         return;

      }

      ::rect rectClient;

      pframewindow->::user::interaction::get_client_rect(rectClient);

      //calc_window_client_rect(m_rectClient, rectClient);

   }


   void frame::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
   {

      if (psubject->m_id == id_user_style_change)
      {

         on_style_change();

      }

   }


   void frame::on_style_change()
   {

      auto estyle = m_pframewindow->m_estyle;

      auto color = m_pframewindow->m_puserstyle->get_style_moveable_border_color(estyle);

      set_moveable_border_color(color);

   }


//   void frame::calc_window_client_rect(RECT32 * prect, const rect & rectWindow)
//   {
//
//      ::rect rect(rectWindow);
//
//      if (m_pframewindow->frame_is_transparent())
//      {
//
//         *prect = rect;
//
//
//         return;
//
//      }
//
//      ::rect * prectMargin = get_margin_rect();
//
//      int iTopDeflate;
//
//      int iLeftDeflate;
//
//      if(m_pframewindow->layout().is_full_screen())
//      {
//
//         iTopDeflate = 0;
//
//         iLeftDeflate = 0;
//
//      }
//      else if(m_pframewindow->layout().is_minimal())
//      {
//
//         iTopDeflate = rectMargin.top;
//
//         iLeftDeflate = rectMargin.left;
//
//      }
//      else
//      {
//
//         iTopDeflate = get_caption_height();
//
//         iLeftDeflate = rectMargin.left;
//
//      }
//
//      int iRightDeflate;
//
//      if(m_pframewindow->layout().is_minimal())
//      {
//
//         iRightDeflate = rect.right + 2;
//
//         ::rect rectIcon;
//
//         if(get_element_rect(rectIcon,ElementTopLeftIcon))
//         {
//
//            iRightDeflate += calc_caption_height(::e_display_normal);
//
//         }
//
//         iRightDeflate += calc_caption_height(::e_display_normal); // for the ElementMoveGripMinimal
//
//      }
//      else
//      {
//
//         iRightDeflate = rectMargin.right;
//
//      }
//
//      rect.deflate(iLeftDeflate,iTopDeflate,iRightDeflate, rectMargin.bottom);
//
//      *prect = rect;
//
//   }


   rect frame::get_margin_rect()
   {

      if (m_pframewindow->layout().is_full_screen())
      {

         return m_rectMarginFullScreen;

      }
      else if (m_pframewindow->layout().is_zoomed())
      {

         return m_rectMarginZoomed;

      }
      else
      {

         return m_rectMarginDock;

      }

   }


   rect frame::get_control_box_margin_rect()
   {

      return m_rectControlBoxMargin;

   }


   void frame::on_defer_display()
   {

      if (m_pframewindow->layout().is_this_screen_visible())
      {

         if (m_pframewindow->get_parent() == nullptr)
         {

            if (!(m_pframewindow->m_ewindowflag & e_window_flag_disable_window_placement_snapping)
               //&& !m_pframewindow->layout().is_moving()
               //&& !m_pframewindow->layout().is_sizing()
               && !m_pframewindow->layout().is_docking()
               //&& !::is_docking_appearance(m_pframewindow->layout().sketch().display())
               && m_pframewindow->layout().sketch().display() != e_display_zoomed
               && m_pframewindow->layout().sketch().display() != e_display_full_screen)
            {

               defer_frame_placement_snapping();

            }

         }

         sync_dock_grip_border();

      }

   }


   void frame::defer_frame_placement_snapping()
   {

      string strType;

      strType = m_pframewindow->type_name();

      if (strType.contains("playlist"))
      {

         INFO("frame playlist");

      }

      auto edisplay = m_pframewindow->layout().sketch().display();

      ::rect rect;

      ::rect rectRequest;

      bool bPreserveSize;

      rectRequest = m_pframewindow->layout().sketch().screen_rect();

      bool bMoving = m_pframewindow->move_manager()->window_is_moving();

      bool bSizing = m_pframewindow->size_manager()->window_is_sizing();

      if (bMoving)
      {

         auto pointMove = m_pframewindow->move_manager()->m_pointMove;

         //auto sizeMinimum = m_pframewindow->get_window_minimum_size();

         //auto sizeMove = m_pframewindow->m_windowrect.m_rectRestored.size().max(sizeMinimum);

         //rectRequest.set(pointMove, sizeMove);

         rectRequest.move_to(pointMove);

         bPreserveSize = true;

      }
      else if(bSizing)
      {

         bPreserveSize = false;

      }
      else
      {

         // arbitrary placement,
         // storage placement,
         // initialization placement...
         // (not sizing and not moving...)

         bPreserveSize = true;

      }

      auto iWkspace = m_pframewindow->get_best_zoneing(edisplay, &rect, rectRequest, bPreserveSize);

      if(edisplay != m_pframewindow->layout().sketch().display() ||
         (::is_docking_appearance(edisplay) && iWkspace != m_pframewindow->m_windowrect.m_iWkspace))
      {

         if (m_pframewindow->layout().m_millisLastSketchToDesign.elapsed() < 800_tick)
         {

            if (edisplay != m_pframewindow->layout().design().display())
            {

               edisplay = m_pframewindow->layout().design().display();

            }

         }

         if (is_docking_appearance(edisplay))
         {

             if (m_pframewindow->size_manager()->window_is_sizing())
             {

                 m_pframewindow->size_manager()->window_stop_sizing(false);

             }

         }

         if (edisplay == e_display_normal)
         {

            if (m_pframewindow->move_manager()->window_is_moving())
            {

               if (m_pframewindow->move_manager()->consider_move())
               {

                  m_pframewindow->layout().sketch() = m_pframewindow->move_manager()->m_pointMove;

               }

            }

            m_pframewindow->layout().sketch() = rect.size();

         }
         else
         {

            m_pframewindow->layout().sketch() = rect;

         }

         if (is_docking_appearance(edisplay))
         {

            m_pframewindow->m_windowrect.m_rectSnapped = rect;

         }

         m_pframewindow->m_windowrect.m_iWkspace = iWkspace;

         m_pframewindow->layout().sketch() = edisplay;

      }
      else if (is_docking_appearance(edisplay))
      {

         if (m_pframewindow->size_manager()->window_is_sizing())
         {

            m_pframewindow->m_windowrect.m_rectRestored = rect;

            m_pframewindow->m_windowrect.m_rectSnapped = rect;

            m_pframewindow->layout().sketch() = rect;

         }
         else if (m_pframewindow->move_manager()->window_is_moving())
         {

            m_pframewindow->m_windowrect.m_rectSnapped = rect;

            m_pframewindow->layout().sketch() = rect;

            m_pframewindow->set_reposition();

         }

      }

      auto sizeMin = m_pframewindow->get_window_minimum_size();

      auto size = m_pframewindow->layout().sketch().size();

      size.ensure_at_least(sizeMin);

      m_pframewindow->layout().sketch() = size;

   }


   void frame::sync_dock_grip_border()
   {

      edisplay edisplay = m_pframewindow->layout().sketch().display();

      auto rectMargin = m_rectMarginNormal;

      e_grip egrip;
      e_border eborder;
      e_dock edock;

      if (!m_pframewindow->is_this_screen_visible() || is_zoomed(edisplay) || is_full_screen(edisplay))
      {

         egrip = e_grip_none;
         eborder = e_border_none;
         edock = e_dock_none;

         rectMargin.Null();

      }
      else if (is_docking_appearance(edisplay))
      {

         if (!(edisplay & e_display_bottom))
         {

            egrip |= e_grip_bottom;
            eborder |= e_border_bottom;
            edock |= e_dock_bottom;

            if (!(edisplay & e_display_left))
            {

               egrip |= e_grip_bottom_left;

            }

         }

         if (!(edisplay & e_display_top))
         {

            egrip |= e_grip_top;
            eborder |= e_border_top;
            edock |= e_dock_top;

            if (!(edisplay & e_display_right))
            {

               egrip |= e_grip_top_right;

            }

         }

         if (!(edisplay & e_display_left))
         {

            egrip |= e_grip_left;
            eborder |= e_border_left;
            edock |= e_dock_left;

            if (!(edisplay & e_display_top))
            {

               egrip |= e_grip_top_left;

            }

         }

         if (!(edisplay & e_display_right))
         {

            egrip |= e_grip_right;
            eborder |= e_border_right;
            edock |= e_dock_right;

            if (!(edisplay & e_display_bottom))
            {

               egrip |= e_grip_bottom_right;

            }

         }

         if (edisplay & e_display_top)
         {

            rectMargin.top = 0;

         }

         if(edisplay & e_display_bottom)
         {

            rectMargin.bottom = 0;

         }

         if (edisplay & e_display_right)
         {

            rectMargin.right = 0;

         }

         if (edisplay & e_display_left)
         {

            rectMargin.left = 0;

         }

      }
      else
      {

         egrip = e_grip_all;
         eborder = e_border_all;
         edock = e_dock_all;

      }

      string strType = m_pframewindow->type_name();

      if (strType.contains("filemanager"))
      {

         //INFO("filemanager");

      }

      if (m_pframewindow->m_eupdown == ::user::interaction::updown_down)
      {

         egrip = e_grip_none;
         edock = e_dock_none;

      }

      m_pframewindow->m_psizemanager->SetGripMask(egrip);
      m_pframewindow->m_pmovemanager->SetBorderMask(eborder);
      m_pframewindow->set_dock_mask(edock);

      if (rectMargin != m_rectMarginDock)
      {

         m_rectMarginDock = rectMargin;

         m_pframewindow->set_need_layout();

      }

   }


   bool frame::get_element_rect(RECT32 * prect,enum_element eelement)
   {

      return false;

   }


   void frame::get_parent_rect(RECT32 * prect)

   {

      if (m_pframewindow->layout().is_full_screen())
      {

         m_pframewindow->best_monitor(prect);


      }
      else if (m_pframewindow->layout().is_zoomed())
      {

         m_pframewindow->get_window_rect(prect);


      }
      else
      {

         m_pframewindow->get_window_rect(prect);


      }

   }


//   rect * frame::get_control_box_rect()
//   {
//
//      if(m_pframewindow->layout().is_full_screen())
//      {
//
//         return &m_rectControlBoxFullScreen;
//
//      }
//      else if(m_pframewindow->layout().is_zoomed())
//      {
//
//         return &m_rectControlBoxZoomed;
//
//      }
//      else
//      {
//
//         return &m_rectControlBoxNormal;
//
//      }
//
//   }


   e_hittest frame::_001HitTest(const ::point & point)
   {

      UNREFERENCED_PARAMETER(point);

      return hittest_client;

   }


   void frame::GetFrameRect(rect * prect)
   {

      m_pframewindow->::user::interaction::get_client_rect(prect);

   }


   //void frame::nextstyle(::user::style_context * pcontext)
   //{

   //   m_pframewindow->nextstyle(pcontext);

   //}


} // namespace experience


