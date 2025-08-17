#include "framework.h"
#include "split_layout.h"
#include "split_pane.h"
#include "split_bar.h"
#include "acme/constant/message.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/handler/request.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/user/user/style.h"
#include "aura/platform/session.h"
#include "aura/user/user/interaction_array.h"


namespace user
{


   const int split_layout::m_iMarging = 5;

   split_layout::split_layout()
   {

      m_bSplitBar = true;
      m_bInitialized = true;
      m_iState = stateInitial;
      m_cxBorder = 1;
      m_cyBorder = 1;
      m_iPaneCount = 0;

      m_flagNonClient.erase(e_non_client_background);
      m_flagNonClient.erase(e_non_client_focus_rect);

   }


   split_layout::~split_layout()
   {

   }


   void split_layout::install_message_routing(::channel * pchannel)
   {

      place_holder_container::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &split_layout::on_message_create);
      MESSAGE_LINK(e_message_show_window, pchannel, this, &split_layout::on_message_show_window);

   }


   void split_layout::on_message_create(::message::message* pmessage)
   {

      pmessage->previous();

   }


   void split_layout::on_message_show_window(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      //::pointer<::message::show_window>pshowwindow(pmessage);

      //bool bIsWindowVisible = pshowwindow->m_bShow;

      //::collection::count iSplitBarCount = get_split_count();

      //split_pane * pcomponent;

      //::pointer<::user::interaction>puserinteraction;

      //int i;

      //for (i = 0; i < iSplitBarCount; i++)
      //{

      //   puserinteraction = m_splitbara.element_at(i);

      //   if (!bIsWindowVisible)
      //   {

      //      puserinteraction->display(e_display_none);

      //   }
      //   else
      //   {

      //      puserinteraction->display(e_display_normal);

      //   }

      //}

      //::int_rectangle rectangleX;

      //for (i = 0; i < get_pane_count(); i++)
      //{

      //   int_rectangle & rectanglePane = m_panea[i]->m_rectangle;

      //   pcomponent = m_panea.element_at(i);

      //   if (pcomponent == nullptr)
      //   {

      //      continue;

      //   }

      //   puserinteraction = pcomponent->m_pplaceholder;

      //   if ( puserinteraction == nullptr)
      //   {

      //      continue;

      //   }

      //   rectangleX = rectanglePane;

      //   rectangleX.deflate(m_cxBorder, m_cyBorder);

      //   if (rectanglePane.area() <= 0 || !bIsWindowVisible)
      //   {

      //      puserinteraction->display(e_display_none);

      //   }
      //   else
      //   {

      //      puserinteraction->display(e_display_normal);

      //   }

      //}

   }


   bool split_layout::SetPaneCount(::collection::count iPaneCount)
   {

      m_iPaneCount = iPaneCount;

      m_panea.set_size(iPaneCount);

      m_splitbara.set_size(iPaneCount - 1);

      for(::collection::index i = 0; i < m_splitbara.get_count(); i++)
      {

         if(!m_splitbara[i])
         {

            //auto estatus = 
            
            øconstruct(m_splitbara[i]);

            //if (!estatus)
            {

               ::user::split_bar & splitbar = *m_splitbara[i];

               splitbar.m_iIndex = i;

               splitbar.create_child(this);

               //if (splitbar.create_child(this))
               {

                  splitbar.m_dwPosition = 0;

                  splitbar.m_dwPosition = 0;

               }

            }

         }

      }

      for(::collection::index i = 0; i < m_panea.get_count(); i++)
      {

         auto& ppane = m_panea[i];

         if(!ppane)
         {

            //auto estatus =
            
            øconstruct_new(ppane);

            ////if (!estatus)
            //{

            //   return false;

            //}

            ppane->m_bFixedSize =  false;

         }

      }

      return true;

   }


   bool split_layout::initialize_split_layout()
   {

#ifdef _DEBUG

      ::collection::count iPaneCount = m_iPaneCount;

#endif

      m_bInitialized = false;

      ASSERT(iPaneCount > 0);

      for(::collection::index i = 0; i < m_panea.get_count(); i++)
      {

         øconstruct_new(m_panea[i]);

         if(m_panea[i]->m_pplaceholder.is_null())
         {

            m_panea[i]->m_pplaceholder = get_new_place_holder(m_panea[i]->m_rectangleHosting);

         }

      }

      set_need_layout();

      m_bInitialized = true;

      return true;

   }


   void split_layout::SetSplitOrientation(enum_orientation eorientationSplit)
   {

      m_eorientationSplit = eorientationSplit;

   }


   void split_layout::RelayChildEvent(::collection::index iIndex, const MESSAGE * pMsg)
   {

      if (!m_bInitialized)
      {

         return;

      }

      ::int_rectangle splitRect;

      CalcSplitBarRect(iIndex, splitRect);

      if(pMsg->m_emessage == e_message_left_button_down)
      {

         if(session()->is_mouse_button_pressed(::user::e_mouse_left_button))
         {
            
            ::user::split_bar & splitbar = *m_splitbara.element_at(iIndex);
            
            splitbar.set_mouse_capture();

            m_iIndex = iIndex;

            m_iState = stateDragging;

         }

      }
      else if(pMsg->m_emessage == e_message_left_button_up)
      {

         if(m_iState != stateInitial)
         {

            defer_release_mouse_capture();

            m_iState = stateInitial;

         }

      }
      else if(pMsg->m_emessage == e_message_mouse_move)
      {

//         int   fwKeys = (int) pMsg->wParam;        // key flags


         //auto point = _001ScreenToClient(pointCursor);

         //if((fwKeys & MK_LBUTTON) > 0 && (m_iState == stateDragging) && (iIndex == m_iIndex))
         //{

         //   _synchronous_lock synchronouslock(this->synchronization());
         //   //critical_section_lock synchronouslock(m_pmutex);
         //   {
         //      //      informationf("split_layout::RelayChildEvent LOWORD(pMsg->lParam) %d\n", LOWORD(lpMsg->lParam));

         //      //      informationf("split_layout::RelayChildEvent HIWORD(pMsg->lParam) %d\n", HIWORD(lpMsg->lParam));




         //      int nPos;
         //      bool bMove;
         //      nPos = GetPos(point.x(), point.y());
         //      if(m_iIndex <= 0)
         //      {
         //         bMove = nPos > GetMinPos();
         //      }
         //      else
         //      {
         //         bMove = nPos > (int) m_splitbara[m_iIndex - 1]->m_dwPosition;
         //      }
         //      if(get_pane_count() >= m_iIndex )
         //      {
         //         bMove = bMove && nPos < GetMaxPos();
         //      }
         //      else
         //      {
         //         bMove = bMove && nPos < (int) m_splitbara[m_iIndex]->m_dwPosition;
         //      }
         //      if(bMove)
         //      {
         //         bMove = nPos != (int) m_splitbara[m_iIndex]->m_dwPosition;
         //      }
         //      informationf("split_layout::RelayChildEvent nPos %d\nOldPos", m_splitbara[m_iIndex]->m_dwPosition);
         //      informationf("split_layout::RelayChildEvent nPos %d\n", nPos);
         //      if(bMove)
         //      {

         //         m_splitbara[m_iIndex]->m_dwPosition = nPos;
         //         m_splitbara[m_iIndex]->m_dRate = 0.0;

         //         set_need_layout();

               //}

         //   }

         //}
         //else
         //{
         //   m_iState = stateInitial;
         //}
      }

   }


   int split_layout::GetPos(int xPos, int yPos)
   {

      if (m_eorientationSplit == e_orientation_horizontal)
      {

         return yPos;

      }
      else
      {

         return xPos;

      }

   }


   int split_layout::GetMinPos(enum_layout elayout)
   {

      auto rectangleX = this->rectangle(elayout);

      if (m_eorientationSplit == e_orientation_horizontal)
      {

         return rectangleX.top();

      }
      else
      {

         return rectangleX.left();

      }

   }


   int split_layout::GetMaxPos(enum_layout elayout)
   {

      auto rectangleX = this->rectangle(elayout);

      if (m_eorientationSplit == e_orientation_horizontal)
      {

         return rectangleX.bottom();

      }
      else
      {

         return rectangleX.right();

      }

   }


   void split_layout::on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::place_holder_container::on_perform_top_down_layout(pgraphics);

      bool bIsWindowVisible = is_this_visible();

      auto rectangle = this->rectangle(e_layout_layout);

      if (rectangle.is_empty())
      {

         return;

      }

      int iDimension = get_normal_dimension(e_layout_layout);

      unsigned int dwPosition;

      double dRate;

      if(iDimension > 0)
      {

         for(int i = 0 ; i < m_splitbara.get_count(); i++)
         {

            if (m_splitbara[i]->m_dRate >= 0.0)
            {

               if ((m_splitbara[i]->m_dRate < m_splitbara[i]->m_dMinimumRate
                     || m_splitbara[i]->m_dRate > m_splitbara[i]->m_dMaximumRate)
                     && m_splitbara[i]->m_dwPosition > 0)
               {

                  dwPosition = m_splitbara[i]->m_dwPosition;

                  dRate = (double)dwPosition / (double)iDimension;

                  m_splitbara[i]->m_dRate = dRate;

               }

               if (m_splitbara[i]->m_dRate < m_splitbara[i]->m_dMinimumRate)
               {

                  m_splitbara[i]->m_dRate = m_splitbara[i]->m_dMinimumRate;

               }
               else if (m_splitbara[i]->m_dRate > m_splitbara[i]->m_dMaximumRate)
               {

                  m_splitbara[i]->m_dRate = m_splitbara[i]->m_dMaximumRate;

               }

               m_splitbara[i]->m_dwPosition = minimum(m_splitbara[i]->m_dwMaxPosition, (unsigned int)(m_splitbara[i]->m_dRate * iDimension));

            }
            else
            {

               m_splitbara[i]->m_dwPosition = minimum(m_splitbara[i]->m_dwMaxPosition, (unsigned int)(m_splitbara[i]->m_dwPosition));

            }

         }

      }

      ::int_rectangle rectangleBar;

      int i;

      ::collection::count iSplitBarCount = get_split_count();

      if (iSplitBarCount < 0)
      {

         return;

      }

      split_pane * ppane;

      //::pointer<::user::interaction>puserinteraction;

      //unsigned int uBaseFlags = SWP_NOZORDER;
      //unsigned int uBaseFlags = 0;

      //unsigned int uFlags = uBaseFlags;

      m_splitbara.set_size(iSplitBarCount);


      for(i = 0; i < iSplitBarCount; i++)
      {

         if (!m_splitbara.element_at(i))
         {

            øconstruct_new(m_splitbara.element_at(i));

         }

         auto psplitbar = m_splitbara.element_at(i);

         bool bIsPaneVisible = is_pane_visible(i);

         bool bFixedSize = m_panea[i]->m_bFixedSize;

         if (!m_bSplitBar || !bIsPaneVisible || !bIsWindowVisible || bFixedSize)
         {

            psplitbar->hide();

            continue;

         }

         CalcSplitBarRect(i, rectangleBar);

         //uFlags = uBaseFlags;

         if (bIsWindowVisible)
         {

            psplitbar->order(e_zorder_top);

            psplitbar->place(rectangleBar);

            psplitbar->display();

         }

      }

      for(i = 0; i < get_pane_count(); i++)
      {

         ppane = m_panea.element_at(i);

         ::int_rectangle & rectanglePane = ppane->m_rectanglePane;

         ::int_rectangle & rectangleClient = ppane->m_rectangleHosting;

         CalcPaneRect(i, rectanglePane, e_layout_layout);

         auto pplaceholder = ppane->m_pplaceholder;

         if (!pplaceholder)
         {

            continue;

         }

         pplaceholder->m_bLockGraphicalUpdate = false;

         rectangleClient = rectanglePane;

         rectangleClient.deflate(m_cxBorder,m_cyBorder);

         //if(rectangleClient != pplaceholder->parent_client_rectangle())
         //{

            pplaceholder->place(rectangleClient, ::user::e_layout_layout, pgraphics);

            pplaceholder->order(e_zorder_top);

            //pplaceholder->m_rectangleClient = rectangleClient;

            //pplaceholder->m_rectangleClient.offset(-pplaceholder->m_rectangleClient.top_left());

            //if (pplaceholder->const_layout().sketch().is_visible())
            //{

            //   pplaceholder->display();

            //   pplaceholder->set_need_layout();

            //   pplaceholder->set_need_redraw({ rectangleClient });

            //   //puserinteraction->post_redraw();

            //}
            //else
            //{

            //   pplaceholder->hide();

            //}

         //}

      }

   }


   void split_layout::set_position(::collection::index iIndex, int nPos)
   {

      ASSERT(iIndex >= 0);

      ASSERT(iIndex < get_split_count());

      if (iIndex < 0 && iIndex >= get_split_count())
      {

         return;

      }

      m_splitbara[iIndex]->m_dwPosition    = nPos;

      m_splitbara[iIndex]->m_dRate         = -1.0; // disable rate evaluation at first

   }


   void split_layout::set_position_rate(::collection::index iIndex, double dRate, double dMinimumRate, double dMaximumRate)
   {

      ASSERT(iIndex >= 0);

      ASSERT(iIndex < get_split_count());

      if (iIndex < 0 && iIndex >= get_split_count())
      {

         return;

      }

      m_splitbara[iIndex]->m_dRate         = dRate;
      m_splitbara[iIndex]->m_dMinimumRate  = dMinimumRate;
      m_splitbara[iIndex]->m_dMaximumRate  = dMaximumRate;
      m_splitbara[iIndex]->m_dwPosition    = (unsigned int) -1; // disable position evaluation at first on on_layout

   }


   int split_layout::get_position(::collection::index iIndex)
   {

      ASSERT(iIndex >= 0);

      ASSERT(iIndex < get_split_count());

      return m_splitbara[iIndex]->m_dwPosition;

   }


   ::collection::count split_layout::get_split_count()
   {

      return get_pane_count() - 1;

   }


   ::collection::count split_layout::get_pane_count()
   {

      return (int) m_panea.get_count();

   }

   ::collection::count split_layout::get_visible_pane_count()
   {

      if (!m_bInitialized)
      {

         return get_pane_count();

      }

      ::collection::count c = 0;

      for (::collection::index i = 0; i < get_pane_count(); i++)
      {

         if (is_pane_visible((int) (i)))
         {

            c++;

         }

      }

      return c;

   }


   bool split_layout::is_pane_visible(int iPane)
   {

      if (iPane < 0)
      {

         return false;

      }

      if (iPane >= m_panea.get_size())
      {

         return false;

      }

      split_pane * ppane = m_panea[iPane];

      if (ppane == nullptr)
      {

         return false;

      }

      ::pointer<::user::place_holder>pholder = ppane->m_pplaceholder;

      if (pholder == nullptr)
      {

         return true; // assume future place_holder by default is visible

      }

      _synchronous_lock synchronouslock(this->synchronization());

      auto pacmeuserinteractionaChildren = pholder->m_pacmeuserinteractionaChildren;

      if (!pacmeuserinteractionaChildren)
      {

         return true;

      }

      if (pacmeuserinteractionaChildren->is_empty())
      {

         return true; // assume future child by default is visible

      }

      ::cast < ::user::interaction > puserinteractionFirst = pacmeuserinteractionaChildren->first();

      if (!puserinteractionFirst->const_layout().sketch().is_visible())
      {

         return false;

      }

      return true;

   }


   void split_layout::CalcPaneRect(::collection::index iPane, ::int_rectangle & rectangle, enum_layout elayout)
   {

      int nMinPos = GetMinPos(iPane, elayout);

      int nMaxPos = GetMaxPos(iPane, elayout);

      CalcPaneRect(nMinPos, nMaxPos, rectangle, elayout);

   }


   void split_layout::CalcPaneRect(int nMinPos, int nMaxPos, ::int_rectangle & rectangle, enum_layout elayout)
   {

      rectangle = this->rectangle(elayout);

      if(m_eorientationSplit == e_orientation_horizontal)
      {

         rectangle.top()      = nMinPos;


         rectangle.bottom()   = nMaxPos;


      }
      else
      {

         rectangle.left()   = nMinPos;


         rectangle.right()   = nMaxPos;


      }

   }


   int split_layout::get_normal_dimension(enum_layout elayout)
   {

      auto rectangleX = this->rectangle(elayout);

      if(m_eorientationSplit == e_orientation_horizontal)
      {

         return rectangleX.height();

      }
      else
      {

         return rectangleX.width();

      }

   }


   int split_layout::get_ortogonal_dimension(enum_layout elayout)
   {

      auto rectangleX = this->rectangle(elayout);

      if(m_eorientationSplit == e_orientation_horizontal)
      {

         return rectangleX.width();

      }
      else
      {

         return rectangleX.height();

      }

   }


   void split_layout::CalcSplitBarRect(::collection::index iIndex, ::int_rectangle & rectangle, enum_layout elayout)
   {

      ASSERT(iIndex >= 0);

      ASSERT(iIndex < get_split_count());

      if (iIndex >= m_splitbara.get_count())
      {

         return;

      }

      int nPos = 0;

      ::collection::index i = 0;

      while (i <= iIndex)
      {

         if (is_pane_visible((int)(i)))
         {

            nPos = m_splitbara[iIndex]->m_dwPosition;

         }

         i++;

      }

      rectangle = this->rectangle(elayout);

      if(m_eorientationSplit == e_orientation_horizontal)
      {

         nPos = maximum(nPos, rectangle.top() + m_iMarging / 2);

         nPos = minimum(nPos, rectangle.bottom() - m_iMarging / 2);

         rectangle.top()      = nPos - m_iMarging / 2;

         rectangle.bottom()   = nPos + m_iMarging / 2;

      }
      else
      {

         nPos = maximum(nPos, rectangle.left() + m_iMarging / 2);

         nPos = minimum(nPos, rectangle.right() - m_iMarging / 2);

         rectangle.left()   = nPos - m_iMarging / 2;

         rectangle.right()   = nPos + m_iMarging / 2;

      }

   }


   bool split_layout::InsertPaneAt(::collection::index iIndex, ::user::interaction * puserinteraction, bool bFixedSize, ::atom atom)
   {

      auto  pbar =øcreate_new<split_bar>();

      m_splitbara.insert_at(iIndex, pbar);

      pbar->m_iIndex = iIndex;

      pbar->create_child(this);

      auto & ppane = m_panea.add_new_at(iIndex);

      øconstruct_new(ppane);

      ppane->m_pplaceholder = place_hold(puserinteraction, ppane->m_rectangleHosting);

      if (ppane->m_pplaceholder == nullptr)
      {

         return false;

      }

      ppane->id() = atom.is_empty() ? (::atom) iIndex : atom;

      ppane->m_bFixedSize = bFixedSize;

      return true;

   }


   bool split_layout::RemovePaneAt(::collection::index iIndex)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      ASSERT(iIndex >= 0);

      ASSERT(iIndex < get_pane_count());

      m_panea.erase_at(iIndex);

      ::collection::count iSplitBarCount = get_pane_count();

      m_splitbara.erase_all();

      ::collection::index i;

      for(i = 0; i < iSplitBarCount; i++)
      {

         auto & psplitbar = m_splitbara.add_new();
         
         øconstruct(psplitbar);

         psplitbar->m_iIndex = i;

         psplitbar->create_child(this);

         //if (!splitbar.create_child(this))
         //{

         //   return false;

         //}

      }

      return true;

   }


   bool split_layout::SetPane(::collection::index iIndex, ::user::interaction * puserinteraction, bool bFixedSize, atom atom)
   {

      ASSERT(iIndex >= 0);

      ASSERT(iIndex < get_pane_count());

      auto ppane = m_panea.element_at(iIndex);

      if(ppane->m_pplaceholder != nullptr)
      {

         if (!ppane->m_pplaceholder->place_hold(puserinteraction))
         {

            return false;

         }

      }
      else
      {

         ::int_rectangle rectangleHosting;

         rectangleHosting = ppane->m_rectangleHosting;

         ppane->m_pplaceholder = place_hold(puserinteraction, rectangleHosting);

         if (!ppane->m_pplaceholder)
         {

            return false;

         }

      }

      ppane->id() = atom.is_empty() ? (::atom) iIndex : atom;

      m_panea[iIndex]->m_bFixedSize = bFixedSize;

      return true;

   }


   void split_layout::SetPaneFixedSize(::collection::index iIndex, const ::int_size & size)
   {

      __UNREFERENCED_PARAMETER(iIndex);

      __UNREFERENCED_PARAMETER(size);

      ASSERT(iIndex >= 0);

      ASSERT(iIndex < get_pane_count());

   }


   int split_layout::GetMinPos(::collection::index iPane, enum_layout elayout)
   {

      if (get_split_count() <= 0 || iPane <= 0)
      {

         return GetMinPos(elayout);

      }
      else
      {

         ::int_rectangle rectangle;

         CalcSplitBarRect(iPane - 1, rectangle, elayout);

         if(m_eorientationSplit == e_orientation_horizontal)
         {

            return rectangle.bottom();

         }
         else
         {

            return rectangle.right();

         }

      }

   }

   int split_layout::GetMaxPos(::collection::index iPane, enum_layout elayout)
   {

      if (get_split_count() <= 0 || iPane >= get_split_count())
      {

         return GetMaxPos(elayout);

      }
      else
      {

         ::int_rectangle rectangle;

         CalcSplitBarRect(iPane, rectangle, elayout);

         if(m_eorientationSplit == e_orientation_horizontal)
         {

            return rectangle.top();

         }
         else
         {

            return rectangle.left();

         }

      }

   }

   enum_orientation split_layout::GetSplitOrientation()
   {

      return m_eorientationSplit;

   }


//   void split_layout::RelayEventSplitBar(::collection::index iSplitBar, ::enum_message emessage, ::wparam wparam, ::lparam lparam)
//   {
//
//      ASSERT(false);
//
//      if(!m_bInitialized)
//         return;
//
//      ::int_rectangle splitRect;
//
//      CalcSplitBarRect(iSplitBar, &splitRect);
//
//      if(atom == e_message_left_button_down)
//      {
//
//         int   fwKeys = (int) wParam;        // key flags
////         int xPos = splitRect.left() + (short) LOWORD(lParam);  // horizontal position of cursor
////         int yPos = splitRect.top() + (short) HIWORD(lParam);  // vertical position of cursor
//         if((fwKeys & MK_LBUTTON) > 0)
//         {
//            ::user::split_bar * pSplitBar = m_splitbara.element_at(iSplitBar);
//            pSplitBar->SetCapture();
//            m_iIndex = iSplitBar;
//            m_iState = stateDragging;
//         }
//      }
//      else if(atom == e_message_left_button_up)
//      {
////         int   fwKeys = wParam;        // key flags
////         int xPos = splitRect.left() + (short) LOWORD(lParam);  // horizontal position of cursor
////         int yPos = splitRect.top() + (short) HIWORD(lParam);  // vertical position of cursor
//         if(m_iState != stateInitial)
//         {
//
//            
//
//            auto puser = user();
//
//            auto pwindowing = system()->windowing();
//
//            pwindowing->release_mouse_capture();
//
//            m_iState = stateInitial;
//
//         }
//
//      }
//#ifdef WINDOWS_DESKTOP
//      else if(atom == e_message_capture_changed)
//      {
//      }
//#endif
//      else if(atom == e_message_mouse_move)
//      {
//         int   fwKeys = (int) wParam;        // key flags
//         int xPos = splitRect.left() + (short) LOWORD(lParam);  // horizontal position of cursor
//         int yPos = splitRect.top() + (short) HIWORD(lParam);  // vertical position of cursor
//         if((fwKeys & MK_LBUTTON) > 0 && (m_iState == stateDragging) && (iSplitBar == m_iIndex))
//         {
//            //critical_section_lock lock(m_pmutex);
//
//            _synchronous_lock synchronouslock(this->synchronization());
//
//            {
//               informationf("split_layout::RelayChildEvent LOWORD(lParam) %d\n", LOWORD(lParam));
//               informationf("split_layout::RelayChildEvent HIWORD(lParam) %d\n", HIWORD(lParam));
//
//
//               int nPos;
//               bool bMove;
//               nPos = GetPos(xPos, yPos);
//               if(m_iIndex <= 0)
//               {
//                  bMove = nPos > GetMinPos();
//               }
//               else
//               {
//                  bMove = nPos > (int) m_splitbara[m_iIndex - 1]->m_dwPosition;
//               }
//               if(get_pane_count() >= m_iIndex )
//               {
//                  bMove = bMove && nPos < GetMaxPos();
//               }
//               else
//               {
//                  bMove = bMove && nPos < (int) m_splitbara[m_iIndex]->m_dwPosition;
//               }
//               if(bMove)
//               {
//                  bMove = nPos != (int) m_splitbara[m_iIndex]->m_dwPosition;
//               }
//               if(bMove)
//               {
//
//                  m_splitbara[m_iIndex]->m_dwPosition = nPos;
//                  m_splitbara[m_iIndex]->m_dRate = 0.0;
//
//                  set_need_layout();
//
//               }
//
//            }
//
//         }
//         else
//         {
//
//            m_iState = stateInitial;
//
//         }
//
//      }
//
//   }


   int_rectangle & split_layout::get_pane_rect(::collection::index iPane)
   {

      ASSERT(iPane >= 0);

      ASSERT(iPane < get_pane_count());

      if (iPane < 0 || iPane >= get_pane_count())
      {

         throw ::exception(error_bad_argument);

      }

      return m_panea[iPane]->m_rectangleHosting;

   }


   ::user::place_holder * split_layout::get_pane_holder(::collection::index iPane)
   {

      ASSERT(iPane >= 0);

      ASSERT(iPane < get_pane_count());

      if (iPane < 0 || iPane >= get_pane_count())
      {

         return nullptr;

      }

      return m_panea[iPane]->m_pplaceholder;

   }


   ::user::interaction * split_layout::get_pane_window(::collection::index iPane)
   {

      ::pointer<::user::place_holder>pholder = get_pane_holder(iPane);

      if (pholder == nullptr)
      {

         return nullptr;

      }

      return pholder->get_hold();

   }


   atom split_layout::get_pane_id(::collection::index iPane)
   {

      ASSERT(iPane >= 0);

      ASSERT(iPane < get_pane_count());

      if (iPane < 0 || iPane >= get_pane_count())
      {

         return atom();

      }

      auto & ppane = m_panea[iPane];

      return ppane->id();

   }


   split_pane * split_layout::get_pane_by_id(::atom atom)
   {

      for(::collection::index iPane = 0; iPane < m_panea.get_count(); iPane++)
      {

         if (m_panea[iPane]->id() == atom)
         {

            return m_panea[iPane].get();

         }

      }

      return nullptr;

   }


   void split_layout::draw_control_background(::draw2d::graphics_pointer & pgraphics)
   {

      //return;

      auto pstyle = get_style(pgraphics);

      auto colorBackground = get_color(pstyle, e_element_background);

      if (colorBackground.m_uchOpacity > 0)
      {

         auto rectangleX = this->rectangle();

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         pgraphics->fill_rectangle(rectangleX, colorBackground);

      }

   }


   void split_layout::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ///return;

      ::user::place_holder_container::_001OnNcDraw(pgraphics);

   }


   void split_layout::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //return;

      auto pstyle = get_style(pgraphics);

      if (pstyle)
      {

         if (!pstyle->_001OnDrawSplitLayout(pgraphics, this))
         {

            _001OnDrawSplitLayout(pgraphics);

         }

      }

   }


   void split_layout::_001OnDrawSplitLayout(::draw2d::graphics_pointer & pgraphics)
   {


   }

   
   //::int_rectangle split_layout::hosting_rectangle(::user::enum_layout elayout)
   //{

   //   return m_rectangleHosting;

   //}



} // namespace user



