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


   const i32 split_layout::m_iMarging = 5;

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

      //i32 i;

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

      //::rectangle_i32 rectangleX;

      //for (i = 0; i < get_pane_count(); i++)
      //{

      //   rectangle_i32 & rectanglePane = m_panea[i]->m_rectangle;

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
            
            __construct(m_splitbara[i]);

            //if (!estatus)
            {

               ::user::split_bar & splitbar = m_splitbara(i);

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
            
            __construct_new(ppane);

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

         __construct_new(m_panea[i]);

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

      ::rectangle_i32 splitRect;

      CalcSplitBarRect(iIndex, splitRect);

      if(pMsg->m_atom == e_message_left_button_down)
      {

         if(session()->is_mouse_button_pressed(::user::e_mouse_left_button))
         {
            
            ::user::split_bar & splitbar = *m_splitbara.element_at(iIndex);
            
            splitbar.set_mouse_capture();

            m_iIndex = iIndex;

            m_iState = stateDragging;

         }

      }
      else if(pMsg->m_atom == e_message_left_button_up)
      {

         if(m_iState != stateInitial)
         {

            defer_release_mouse_capture();

            m_iState = stateInitial;

         }

      }
      else if(pMsg->m_atom == e_message_mouse_move)
      {

//         i32   fwKeys = (i32) pMsg->wParam;        // key flags


         //auto point = _001ScreenToClient(pointCursor);

         //if((fwKeys & MK_LBUTTON) > 0 && (m_iState == stateDragging) && (iIndex == m_iIndex))
         //{

         //   _synchronous_lock synchronouslock(this->synchronization());
         //   //critical_section_lock synchronouslock(m_pmutex);
         //   {
         //      //      informationf("split_layout::RelayChildEvent LOWORD(pMsg->lParam) %d\n", LOWORD(lpMsg->lParam));

         //      //      informationf("split_layout::RelayChildEvent HIWORD(pMsg->lParam) %d\n", HIWORD(lpMsg->lParam));




         //      i32 nPos;
         //      bool bMove;
         //      nPos = GetPos(point.x(), point.y());
         //      if(m_iIndex <= 0)
         //      {
         //         bMove = nPos > GetMinPos();
         //      }
         //      else
         //      {
         //         bMove = nPos > (i32) m_splitbara[m_iIndex - 1]->m_dwPosition;
         //      }
         //      if(get_pane_count() >= m_iIndex )
         //      {
         //         bMove = bMove && nPos < GetMaxPos();
         //      }
         //      else
         //      {
         //         bMove = bMove && nPos < (i32) m_splitbara[m_iIndex]->m_dwPosition;
         //      }
         //      if(bMove)
         //      {
         //         bMove = nPos != (i32) m_splitbara[m_iIndex]->m_dwPosition;
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


   i32 split_layout::GetPos(i32 xPos, i32 yPos)
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


   i32 split_layout::GetMinPos(enum_layout elayout)
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


   i32 split_layout::GetMaxPos(enum_layout elayout)
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

      i32 iDimension = get_normal_dimension(e_layout_layout);

      u32 dwPosition;

      double dRate;

      if(iDimension > 0)
      {

         for(i32 i = 0 ; i < m_splitbara.get_count(); i++)
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

               m_splitbara[i]->m_dwPosition = minimum(m_splitbara[i]->m_dwMaxPosition, (u32)(m_splitbara[i]->m_dRate * iDimension));

            }
            else
            {

               m_splitbara[i]->m_dwPosition = minimum(m_splitbara[i]->m_dwMaxPosition, (u32)(m_splitbara[i]->m_dwPosition));

            }

         }

      }

      ::rectangle_i32 rectangleBar;

      i32 i;

      ::collection::count iSplitBarCount = get_split_count();

      if (iSplitBarCount < 0)
      {

         return;

      }

      split_pane * ppane;

      //::pointer<::user::interaction>puserinteraction;

      //::u32 uBaseFlags = SWP_NOZORDER;
      //::u32 uBaseFlags = 0;

      //::u32 uFlags = uBaseFlags;

      m_splitbara.set_size(iSplitBarCount);


      for(i = 0; i < iSplitBarCount; i++)
      {

         if (!m_splitbara.element_at(i))
         {

            __construct_new(m_splitbara.element_at(i));

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

         ::rectangle_i32 & rectanglePane = ppane->m_rectanglePane;

         ::rectangle_i32 & rectangleClient = ppane->m_rectangleHosting;

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


   void split_layout::set_position(::collection::index iIndex, i32 nPos)
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
      m_splitbara[iIndex]->m_dwPosition    = (u32) -1; // disable position evaluation at first on on_layout

   }


   i32 split_layout::get_position(::collection::index iIndex)
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

      return (i32) m_panea.get_count();

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

      auto puserinteractionpointeraChild = pholder->m_puserinteractionpointeraChild;

      if (!puserinteractionpointeraChild)
      {

         return true;

      }

      if (puserinteractionpointeraChild->has_no_interaction())
      {

         return true; // assume future child by default is visible

      }

      if (!puserinteractionpointeraChild->first_interaction()->const_layout().sketch().is_visible())
      {

         return false;

      }

      return true;

   }


   void split_layout::CalcPaneRect(::collection::index iPane, ::rectangle_i32 & rectangle, enum_layout elayout)
   {

      i32 nMinPos = GetMinPos(iPane, elayout);

      i32 nMaxPos = GetMaxPos(iPane, elayout);

      CalcPaneRect(nMinPos, nMaxPos, rectangle, elayout);

   }


   void split_layout::CalcPaneRect(i32 nMinPos, i32 nMaxPos, ::rectangle_i32 & rectangle, enum_layout elayout)
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


   i32 split_layout::get_normal_dimension(enum_layout elayout)
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


   i32 split_layout::get_ortogonal_dimension(enum_layout elayout)
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


   void split_layout::CalcSplitBarRect(::collection::index iIndex, ::rectangle_i32 & rectangle, enum_layout elayout)
   {

      ASSERT(iIndex >= 0);

      ASSERT(iIndex < get_split_count());

      if (iIndex >= m_splitbara.get_count())
      {

         return;

      }

      i32 nPos = 0;

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

      auto  pbar =__create_new<split_bar>();

      m_splitbara.insert_at(iIndex, pbar);

      pbar->m_iIndex = iIndex;

      pbar->create_child(this);

      auto & ppane = m_panea.add_new_at(iIndex);

      __construct_new(ppane);

      ppane->m_pplaceholder = place_hold(puserinteraction, ppane->m_rectangleHosting);

      if (ppane->m_pplaceholder == nullptr)
      {

         return false;

      }

      ppane->m_atom = atom.is_empty() ? (::atom) iIndex : atom;

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
         
         __construct(psplitbar);

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

         ::rectangle_i32 rectangleHosting;

         rectangleHosting = ppane->m_rectangleHosting;

         ppane->m_pplaceholder = place_hold(puserinteraction, rectangleHosting);

         if (!ppane->m_pplaceholder)
         {

            return false;

         }

      }

      ppane->m_atom = atom.is_empty() ? (::atom) iIndex : atom;

      m_panea[iIndex]->m_bFixedSize = bFixedSize;

      return true;

   }


   void split_layout::SetPaneFixedSize(::collection::index iIndex, const ::size_i32 & size)
   {

      __UNREFERENCED_PARAMETER(iIndex);

      __UNREFERENCED_PARAMETER(size);

      ASSERT(iIndex >= 0);

      ASSERT(iIndex < get_pane_count());

   }


   i32 split_layout::GetMinPos(::collection::index iPane, enum_layout elayout)
   {

      if (get_split_count() <= 0 || iPane <= 0)
      {

         return GetMinPos(elayout);

      }
      else
      {

         ::rectangle_i32 rectangle;

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

   i32 split_layout::GetMaxPos(::collection::index iPane, enum_layout elayout)
   {

      if (get_split_count() <= 0 || iPane >= get_split_count())
      {

         return GetMaxPos(elayout);

      }
      else
      {

         ::rectangle_i32 rectangle;

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


//   void split_layout::RelayEventSplitBar(::collection::index iSplitBar, const ::atom & atom, WPARAM wParam, LPARAM lParam)
//   {
//
//      ASSERT(false);
//
//      if(!m_bInitialized)
//         return;
//
//      ::rectangle_i32 splitRect;
//
//      CalcSplitBarRect(iSplitBar, &splitRect);
//
//      if(atom == e_message_left_button_down)
//      {
//
//         i32   fwKeys = (i32) wParam;        // key flags
////         i32 xPos = splitRect.left() + (i16) LOWORD(lParam);  // horizontal position of cursor
////         i32 yPos = splitRect.top() + (i16) HIWORD(lParam);  // vertical position of cursor
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
////         i32   fwKeys = wParam;        // key flags
////         i32 xPos = splitRect.left() + (i16) LOWORD(lParam);  // horizontal position of cursor
////         i32 yPos = splitRect.top() + (i16) HIWORD(lParam);  // vertical position of cursor
//         if(m_iState != stateInitial)
//         {
//
//            
//
//            auto puser = user();
//
//            auto pwindowing = system()->windowing();
//
//            pwindowing->release_capture();
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
//         i32   fwKeys = (i32) wParam;        // key flags
//         i32 xPos = splitRect.left() + (i16) LOWORD(lParam);  // horizontal position of cursor
//         i32 yPos = splitRect.top() + (i16) HIWORD(lParam);  // vertical position of cursor
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
//               i32 nPos;
//               bool bMove;
//               nPos = GetPos(xPos, yPos);
//               if(m_iIndex <= 0)
//               {
//                  bMove = nPos > GetMinPos();
//               }
//               else
//               {
//                  bMove = nPos > (i32) m_splitbara[m_iIndex - 1]->m_dwPosition;
//               }
//               if(get_pane_count() >= m_iIndex )
//               {
//                  bMove = bMove && nPos < GetMaxPos();
//               }
//               else
//               {
//                  bMove = bMove && nPos < (i32) m_splitbara[m_iIndex]->m_dwPosition;
//               }
//               if(bMove)
//               {
//                  bMove = nPos != (i32) m_splitbara[m_iIndex]->m_dwPosition;
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


   rectangle_i32 & split_layout::get_pane_rect(::collection::index iPane)
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

      return ppane->m_atom;

   }


   split_pane * split_layout::get_pane_by_id(::atom atom)
   {

      for(::collection::index iPane = 0; iPane < m_panea.get_count(); iPane++)
      {

         if (m_panea[iPane]->m_atom == atom)
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

      if (colorBackground.m_u8Opacity > 0)
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

   
   //::rectangle_i32 split_layout::hosting_rectangle(::user::enum_layout elayout)
   //{

   //   return m_rectangleHosting;

   //}



} // namespace user



