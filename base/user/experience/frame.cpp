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

      m_rectControlBoxMarginFullScreen.set(0, 0, 0, 0);
      m_rectControlBoxMarginZoomed.set(0, 0, 0, 0);
      m_rectControlBoxMarginNormal.set(0, 0, 0, 0);

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


   void frame::set_style(const char * pszStyle)
   {

      m_strStyle = pszStyle;

   }

   int frame::adjust_client_height(int iHeight)
   {

      return iHeight + get_caption_height();

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


   void frame::OnNcCalcSize(RECT * prect)
   {

      if(m_pframewindow->m_bUseNc)
      {

         calc_window_client_rect(prect,rect(prect));


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


   COLORREF frame::get_border_main_body_color()
   {

      return 0;

   }


   bool frame::_001OnLButtonDown(::message::mouse * pmouse)
   {

      if(!m_pframewindow->layout().is_zoomed() && !m_pframewindow->layout().is_full_screen())
      {

         //if(m_pframewindow->dock_manager()->_001OnLButtonDown(pmouse->)
         // return true;

         if(m_pframewindow->size_manager()->_001OnLButtonDown(pmouse))
            return true;

         if(m_pframewindow->move_manager()->_001OnLButtonDown(pmouse))
            return true;

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

      pmouse->m_point = Session.get_cursor_pos();

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


   bool frame::_001OnTimer(UINT nIDEvent)
   {

      UNREFERENCED_PARAMETER(nIDEvent);

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

      if (edisplay == display_full_screen)
      {

         return 0;

      }

      if (edisplay == display_minimal)
      {

         return 0;

      }

//      update_dock_grip_border_and_display();

      rect * prectMargin = get_margin_rect();

      rect * prectControlBoxMargin = get_control_box_margin_rect();

      i32 iMargin = prectMargin->top + prectControlBoxMargin->top + prectControlBoxMargin->bottom;

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


   i32 frame::calc_control_box_left(bool bLayout)
   {

      auto pframewindow = m_pframewindow;

      ::rect rectClient;

      pframewindow->get_window_rect(rectClient);

      rectClient -= rectClient.top_left();

      //rect * prectControlBoxMargin = get_control_box_margin_rect();

      rect * prectMargin = get_margin_rect();

      rect * prectControlBox = get_control_box_rect();

      ::rect rectParent;

      get_parent_rect(rectParent);

      i32 x;

      x = rectClient.right - prectMargin->right - prectControlBox->width();

      //if (!m_bFirstLayoutDone)
      {

         //x = rectClient.right - m_iControlBoxRight - prectControlBox->width();

//         m_bFirstLayoutDone = true;

      }
      //else
      //{

      //   m_bControlBoxAlignRight = prectControlBox->center().x > rectClient.center().x || rectClient.width() < prectControlBox->width();

      //   if (bLayout && is_control_box_moveable())
      //   {

      //      if (m_bControlBoxAlignRight)
      //      {

      //         x = rectClient.right - m_iControlBoxRight - prectControlBox->width();

      //      }
      //      else
      //      {

      //         x = prectControlBox->left;

      //      }

      //   }
      //   else
      //   {

      //      x = prectControlBox->left;

      //   }

      //}

      //rectParent -= rectParent.top_left();

      //if (x > rectParent.right - prectMargin->right - prectControlBoxMargin->right - prectControlBox->width())
      //   x = rectParent.right - prectMargin->right - prectControlBoxMargin->right - prectControlBox->width();

      //if (x < rectParent.left + prectMargin->left + prectControlBoxMargin->left)
      //   x = rectParent.left + prectMargin->left + prectControlBoxMargin->left;

      return x;

   }


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

            auto pointCursor = Session.get_cursor_pos();

            if (pointCursor.y <= get_control_box()->layout().origin().y)
            {

               bVisible = true;

            }
            else
            {

               bVisible = false;

            }

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

      pframewindow->get_window_rect(rectClient);

      if (!rectClient.is_empty())
      {


         bool bInitialControlBoxPosition = true;

         auto edisplayState = pframewindow->layout().design().display();

         rect * prectControlBoxMargin = get_control_box_margin_rect();

         rect * prectMargin = get_margin_rect();

         i32 cx = rectClient.width();

         int iControlBoxHeight = m_pcontrolbox->calc_control_box_height();

         ::rect rect;

         ::rect rectWindow;

         m_pframewindow->get_window_rect(rectWindow);

         ::rect rectParent(rectWindow);

         m_pframewindow->_001ScreenToClient(rectParent);

         m_rectCaption.left = rectClient.left + prectMargin->left + prectControlBoxMargin->left;
         m_rectCaption.top = rectClient.top + prectMargin->top + prectControlBoxMargin->top;
         m_rectCaption.right = rectClient.right - +prectMargin->right + prectControlBoxMargin->right;
         m_rectCaption.bottom = m_rectCaption.top + iControlBoxHeight;

         bool bShow = true;

         if (!is_control_box_moveable() || m_bInitialControlBoxPosition || bInitialControlBoxPosition)
         {

            m_bInitialControlBoxPosition = false;

            //int iControlBoxWidthFullScreen = m_pcontrolbox->calc_control_box_full_screen_width();
            //int iControlBoxWidthZoomed = m_pcontrolbox->calc_control_box_zoomed_width();
            //int iControlBoxWidthNormal = m_pcontrolbox->calc_control_box_normal_width();

            int iControlBoxWidthFullScreen = cx;
            //int iControlBoxWidthZoomed = cx;
            //int iControlBoxWidthNormal = cx;


            m_rectControlBoxFullScreen.left = cx - iControlBoxWidthFullScreen;
            m_rectControlBoxFullScreen.right = cx;
            m_rectControlBoxFullScreen.top = 0;
            m_rectControlBoxFullScreen.bottom = m_rectControlBoxFullScreen.top + iControlBoxHeight;

            m_rectControlBoxZoomed = m_rectControlBoxFullScreen;

            m_rectControlBoxNormal = m_rectControlBoxFullScreen;

            //m_rectControlBoxZoomed.right = cx - m_rectControlBoxMarginZoomed.right - m_rectMarginZoomed.right;
            //m_rectControlBoxZoomed.left = m_rectControlBoxZoomed.right - iControlBoxWidthZoomed;
            //m_rectControlBoxZoomed.top = m_rectMarginZoomed.top + m_rectControlBoxMarginZoomed.top;
            //m_rectControlBoxZoomed.bottom = m_rectControlBoxZoomed.top + iControlBoxHeight;

            //m_rectControlBoxNormal.right = cx - m_rectControlBoxMarginNormal.right - m_rectMarginNormal.right;
            //m_rectControlBoxNormal.left = m_rectControlBoxNormal.right - iControlBoxWidthNormal;
            //m_rectControlBoxNormal.top = m_rectMarginNormal.top + m_rectControlBoxMarginNormal.top;
            //m_rectControlBoxNormal.bottom = m_rectControlBoxNormal.top + iControlBoxHeight;

         }

         ::rect * prectControlBox;

         int iControlBoxRightMargin;

         if (m_pframewindow->layout().is_full_screen())
         {

            prectControlBox = &m_rectControlBoxFullScreen;

            pframewindow->best_monitor(rectParent);

            bShow = !(m_bInitialControlBoxPosition || bInitialControlBoxPosition);

         }
         else if (m_pframewindow->layout().is_zoomed())
         {

            prectControlBox = &m_rectControlBoxZoomed;

            pframewindow->get_window_rect(rectParent);

         }
         else
         {

            prectControlBox = &m_rectControlBoxNormal;

            pframewindow->get_window_rect(rectParent);

            m_rectControlBoxNormal._001Constraint(m_rectCaption);

         }

         rectParent -= rectParent.top_left();

         iControlBoxRightMargin = prectControlBoxMargin->right;

         int x = calc_control_box_left(!bInitialControlBoxPosition);

         int y = prectMargin->top + prectControlBoxMargin->top;

         prectControlBox->top = y;

         prectControlBox->bottom = y + iControlBoxHeight;

         prectControlBox->right = x + prectControlBox->width();

         prectControlBox->left = x;

         if (m_pframewindow->layout().is_this_screen_visible() && !is_iconic(m_pframewindow->layout().design().display()))
         {

            auto rectControlBoxWindow = get_control_box()->layout().parent_client_rect();

            if (*prectControlBox != rectControlBoxWindow)
            {

               get_control_box()->place(prectControlBox);

            }

         }

         m_rectWindow = rectClient;

         ::rect rectIcon = nullptr;

         if (m_pframewindow->layout().is_minimal())
         {

            if (get_element_rect(rectIcon, ElementTopLeftIcon))
            {

               m_pointWindowIcon.x = get_control_box_rect()->left - 2 - get_control_box_rect()->height();

            }
            else
            {

               m_pointWindowIcon.x = get_control_box_rect()->left;

            }

         }
         else
         {

            get_element_rect(rectIcon, ElementTopLeftIcon);

            m_pointWindowIcon.x = prectMargin->left + prectControlBoxMargin->left + 5;

         }

         m_pointMoveGripMinimal.x = m_pointWindowIcon.x - 2 - get_control_box_rect()->height();

         m_pointMoveGripMinimal.y = prectMargin->top + prectControlBoxMargin->top;

         m_pointWindowIcon.y = prectMargin->top + ((iControlBoxHeight - rectIcon.height()) / 2);

         if (m_pframewindow->m_picon != nullptr)
         {

            m_rectWindowText.left = m_pointWindowIcon.x + rectIcon.width() + 5;

         }
         else
         {

            m_rectWindowText.left = m_pointWindowIcon.x;

         }

         m_rectWindowText.top = m_pointWindowIcon.y;
         m_rectWindowText.right = rectClient.width() - prectMargin->right;
         m_rectWindowText.bottom = prectMargin->top + iControlBoxHeight;

         m_rectCaptionTextBk.left = prectMargin->left;
         m_rectCaptionTextBk.top = prectMargin->top;
         m_rectCaptionTextBk.right = rectClient.width() - prectMargin->right;
         m_rectCaptionTextBk.bottom = prectControlBox->bottom + prectControlBoxMargin->bottom;

         m_rectCaptionTextBk.bottom = prectControlBox->bottom + prectControlBoxMargin->bottom;

      }

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

      }

      m_pcontrolbox->update_control_box_buttons();

      on_style_change();

      //update_drawing_objects();

      //update_window();

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


   bool frame::get_window_client_rect(RECT * prect)

   {

      if (string(type_name()).contains_ci("file"))
      {


         output_debug_string("frame::get_window_client_rect file");

      }

      *prect = m_rectClient;


      return true;

   }


   bool frame::get_draw_client_rect(RECT * prect)

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
         return;

      ::rect rectClient;

      pframewindow->::user::interaction::get_client_rect(rectClient);

      calc_window_client_rect(m_rectClient, rectClient);

   }


   void frame::on_style_change()
   {

   }


   void frame::calc_window_client_rect(RECT * prect, const rect &  rectWindow)
   {

      ::rect rect(rectWindow);

      if (m_pframewindow->frame_is_transparent())
      {

         *prect = rect;


         return;

      }

      ::rect * prectMargin = get_margin_rect();

      int iTopDeflate;

      int iLeftDeflate;

      if(m_pframewindow->layout().is_full_screen())
      {

         iTopDeflate = 0;

         iLeftDeflate = 0;

      }
      else if(m_pframewindow->layout().is_minimal())
      {

         iTopDeflate = prectMargin->top;

         iLeftDeflate = prectMargin->left;

      }
      else
      {

         iTopDeflate = get_caption_height();

         iLeftDeflate = prectMargin->left;

      }

      int iRightDeflate;

      if(m_pframewindow->layout().is_minimal())
      {

         iRightDeflate = (rect.right - get_control_box_rect()->left) + 2 ;

         ::rect rectIcon;

         if(get_element_rect(rectIcon,ElementTopLeftIcon))
         {

            iRightDeflate += calc_caption_height(::display_normal);

         }

         iRightDeflate += calc_caption_height(::display_normal); // for the ElementMoveGripMinimal

      }
      else
      {

         iRightDeflate = prectMargin->right;

      }

      rect.deflate(iLeftDeflate,iTopDeflate,iRightDeflate, prectMargin->bottom);

      *prect = rect;

   }


   rect * frame::get_margin_rect()
   {

      if (m_pframewindow->layout().is_full_screen())
      {

         return &m_rectMarginFullScreen;

      }
      else if (m_pframewindow->layout().is_zoomed())
      {

         return &m_rectMarginZoomed;

      }
      else
      {

         return &m_rectMarginDock;

      }

   }


   rect * frame::get_control_box_margin_rect()
   {

      if (m_pframewindow->layout().is_full_screen())
      {

         return &m_rectControlBoxMarginFullScreen;

      }
      else if (m_pframewindow->layout().is_zoomed())
      {

         return &m_rectControlBoxMarginZoomed;

      }
      else
      {

         return &m_rectControlBoxMarginDock;

      }

   }


   i64 g_i_on_defer_display = 0;


   void frame::on_defer_display()
   {

      if (m_pframewindow->layout().is_this_screen_visible())
      {

         if (m_pframewindow->GetParent() == nullptr)
         {

            if (!(m_pframewindow->m_ewindowflag & window_flag_disable_window_placement_snapping)
               //&& !m_pframewindow->layout().is_moving()
               //&& !m_pframewindow->layout().is_sizing()
               && !m_pframewindow->layout().is_docking()
               //&& !::is_docking_appearance(m_pframewindow->layout().sketch().display())
               && m_pframewindow->layout().sketch().display() != display_zoomed
               && m_pframewindow->layout().sketch().display() != display_full_screen)
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

         if (m_pframewindow->layout().m_tickLastSketchToDesign.elapsed() < 800_tick)
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

         if (edisplay == display_normal)
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

      auto rectControlBoxMargin = m_rectControlBoxMarginNormal;

      egrip egrip;
      eborder eborder;
      edock edock;

      if (!m_pframewindow->is_this_screen_visible() || is_zoomed(edisplay) || is_full_screen(edisplay))
      {

         egrip = grip_none;
         eborder = border_none;
         edock = dock_none;

         rectMargin.Null();
         rectControlBoxMargin.Null();

      }
      else if (is_docking_appearance(edisplay))
      {

         if (!(edisplay & display_bottom))
         {

            egrip |= grip_bottom;
            eborder |= border_bottom;
            edock |= dock_bottom;

            if (!(edisplay & display_left))
            {

               egrip |= grip_bottom_left;

            }

         }

         if (!(edisplay & display_top))
         {

            egrip |= grip_top;
            eborder |= border_top;
            edock |= dock_top;

            if (!(edisplay & display_right))
            {

               egrip |= grip_top_right;

            }

         }

         if (!(edisplay & display_left))
         {

            egrip |= grip_left;
            eborder |= border_left;
            edock |= dock_left;

            if (!(edisplay & display_top))
            {

               egrip |= grip_top_left;

            }

         }

         if (!(edisplay & display_right))
         {

            egrip |= grip_right;
            eborder |= border_right;
            edock |= dock_right;

            if (!(edisplay & display_bottom))
            {

               egrip |= grip_bottom_right;

            }

         }

         if (edisplay & display_top)
         {

            rectMargin.top = 0;
            rectControlBoxMargin.top = 0;

         }

         if(edisplay & display_bottom)
         {

            rectMargin.bottom = 0;

         }

         if (edisplay & display_right)
         {

            rectMargin.right = 0;
            rectControlBoxMargin.right = 0;

         }

         if (edisplay & display_left)
         {

            rectMargin.left = 0;
            rectControlBoxMargin.left = 0;

         }

      }
      else
      {

         egrip = grip_all;
         eborder = border_all;
         edock = dock_all;

      }

      string strType = m_pframewindow->type_name();

      if (strType.contains("filemanager"))
      {

         //INFO("filemanager");

      }

      if (m_pframewindow->m_eupdown == ::user::interaction::updown_down)
      {

         egrip = grip_none;
         edock = dock_none;

      }

      m_pframewindow->m_psizemanager->SetGripMask(egrip);
      m_pframewindow->m_pmovemanager->SetBorderMask(eborder);
      m_pframewindow->set_dock_mask(edock);

   if (rectMargin != m_rectMarginDock || rectControlBoxMargin != m_rectControlBoxMarginDock)
      {

         m_rectMarginDock = rectMargin;

         m_rectControlBoxMarginDock = rectControlBoxMargin;

         m_pframewindow->set_need_layout();

      }

   }


   bool frame::get_element_rect(RECT * prect,e_element eelement)
   {

      return false;

   }


   void frame::get_parent_rect(RECT * prect)

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


   rect * frame::get_control_box_rect()
   {

      if(m_pframewindow->layout().is_full_screen())
      {

         return &m_rectControlBoxFullScreen;

      }
      else if(m_pframewindow->layout().is_zoomed())
      {

         return &m_rectControlBoxZoomed;

      }
      else
      {

         return &m_rectControlBoxNormal;

      }

   }


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


