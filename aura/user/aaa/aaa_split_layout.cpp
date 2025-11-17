#include "framework.h"


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

      USER_MESSAGE_LINK(::user::e_message_create, pchannel, this, &split_layout::on_message_create);
      USER_MESSAGE_LINK(::user::e_message_show_window, pchannel, this, &split_layout::on_message_show_window);

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

      //split_layout::Pane * pcomponent;

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

      //::double_rectangle rectangleX;

      //for (i = 0; i < get_pane_count(); i++)
      //{

      //   rectangle & rectanglePane = m_panea[i]->m_rect;

      //   pcomponent = m_panea.element_at(i);

      //   if (pcomponent == nullptr)
      //   {

      //      continue;

      //   }

      //   puserinteraction = pcomponent->m_pholder;

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
            
            auto estatus = øconstruct(m_splitbara[i]);

            if (!estatus)
            {
            
               ::user::split_bar & splitbar = m_splitbara(i);

               splitbar.m_iIndex = i;

               if (splitbar.create_window(this))
               {

                  splitbar.m_dwPosition = 0;

                  splitbar.m_dwPosition = 0;

               }

            }

         }

      }

      for(::collection::index i = 0; i < m_panea.get_count(); i++)
      {

         if(m_panea[i].is_null())
         {

            m_panea[i] = øallocate ::user::split_pane();

            m_panea(i).m_bFixedSize =  false;

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

         if(m_panea[i]->m_pholder.is_null())
         {

            m_panea[i]->m_pholder = get_new_place_holder(m_panea[i]->m_rectangleX);

         }

      }

      m_bInitialized = true;

      return true;

   }


   void split_layout::SetSplitOrientation(enum_orientation eorientationSplit)
   {

      m_eorientationSplit = eorientationSplit;

   }


   void split_layout::RelayChildEvent(::collection::index iIndex, const MESSAGE * pMsg)

   {

      if(!m_bInitialized)
         return;

      ::double_rectangle splitRect;
      CalcSplitBarRect(iIndex, &splitRect);
      ::int_point pointCursor = pMsg->pt;

      if(pMsg->message == ::user::e_message_left_button_down)

      {

//         int   fwKeys = (int) pMsg->wParam;        // key flags

         if(psession->is_mouse_button_pressed(::user::e_mouse_left_button))
         {
            ::user::split_bar & splitbar = *m_splitbara.element_at(iIndex);
            splitbar.SetCapture();
            m_iIndex = iIndex;
            m_iState = stateDragging;
         }
      }
      else if(pMsg->message == ::user::e_message_left_button_up)

      {

         if(m_iState != stateInitial)
         {

            psession->ReleaseCapture();

            m_iState = stateInitial;

         }

      }
      else if(pMsg->message == ::user::e_message_capture_changed)

      {

      }
      else if(pMsg->message == ::user::e_message_mouse_move)

      {

         int   fwKeys = (int) pMsg->wParam;        // key flags


         auto point = pointCursor;

         screen_to_client(&point);

         if((fwKeys & MK_LBUTTON) > 0 && (m_iState == stateDragging) && (iIndex == m_iIndex))
         {

            synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
            //cslock synchronouslock(m_pmutex);
            {
               //      informationf("split_layout::RelayChildEvent LOWORD(pMsg->lParam) %d\n", LOWORD(lpMsg->lParam));

               //      informationf("split_layout::RelayChildEvent HIWORD(pMsg->lParam) %d\n", HIWORD(lpMsg->lParam));




               int nPos;
               bool bMove;
               nPos = GetPos(point.x, point.y);
               if(m_iIndex <= 0)
               {
                  bMove = nPos > GetMinPos();
               }
               else
               {
                  bMove = nPos > (int) m_splitbara[m_iIndex - 1]->m_dwPosition;
               }
               if(get_pane_count() >= m_iIndex )
               {
                  bMove = bMove && nPos < GetMaxPos();
               }
               else
               {
                  bMove = bMove && nPos < (int) m_splitbara[m_iIndex]->m_dwPosition;
               }
               if(bMove)
               {
                  bMove = nPos != (int) m_splitbara[m_iIndex]->m_dwPosition;
               }
               informationf("split_layout::RelayChildEvent nPos %d\nOldPos", m_splitbara[m_iIndex]->m_dwPosition);
               FORMATTED_ informationf("split_layout::RelayChildEvent nPos %d\n", nPos);
               if(bMove)
               {

                  m_splitbara[m_iIndex]->m_dwPosition = nPos;
                  m_splitbara[m_iIndex]->m_dRate = 0.0;
               
                  set_need_layout();

               }

            }

         }
         else
         {
            m_iState = stateInitial;
         }
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


   int split_layout::GetMinPos()
   {

      ::double_rectangle rectangleX;

      this->rectangle(rectangleX);

      if (m_eorientationSplit == e_orientation_horizontal)
      {

         return rectangleX.top();

      }
      else
      {

         return rectangleX.left();

      }

   }


   int split_layout::GetMaxPos()
   {

      ::double_rectangle rectangleX;

      this->rectangle(rectangleX);

      if (m_eorientationSplit == e_orientation_horizontal)
      {

         return rectangleX.bottom();

      }
      else
      {

         return rectangleX.right();

      }

   }


   void split_layout::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      bool bIsWindowVisible = is_this_visible();

      auto rectangleX = this->rectangle();

      if (rectangleX.is_empty())
      {

         return;

      }

      int iDimension = get_normal_dimension();

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

      ::double_rectangle rectangleBar;

      int i;

      ::collection::count iSplitBarCount = get_split_count();

      split_layout::Pane * pcomponent;

      ::pointer<::user::interaction>puserinteraction;

      unsigned int uBaseFlags = SWP_NOZORDER;

      unsigned int uFlags = uBaseFlags;

      for(i = 0; i < iSplitBarCount; i++)
      {

         puserinteraction = m_splitbara.element_at(i);

         if (!m_bSplitBar || !is_pane_visible(i) || !bIsWindowVisible || m_panea[i]->m_bFixedSize)
         {

            puserinteraction->hide();

            continue;

         }

         CalcSplitBarRect(i, &rectangleBar);

         uFlags = uBaseFlags;


         if (bIsWindowVisible)
         {

            puserinteraction->order(e_zorder_top);

            puserinteraction->place(rectangleBar);

            puserinteraction->display();

         }

      }

      for(i = 0; i < get_pane_count(); i++)
      {

         ::double_rectangle & rectanglePane = m_panea[i]->m_rect;

         ::double_rectangle & rectangleX = m_panea[i]->m_rectangleX;

         CalcPaneRect(i,&rectanglePane);

         pcomponent = m_panea.element_at(i);

         puserinteraction = pcomponent->m_pholder;

         if (puserinteraction == nullptr)
         {

            continue;

         }

         rectangleX = rectanglePane;

         rectangleX.deflate(m_cxBorder,m_cyBorder);

         puserinteraction->order(e_zorder_top);

         puserinteraction->place(rectangleX);

         if (puserinteraction->is_request_visible())
         {

            puserinteraction->display();

         }
         else
         {

            puserinteraction->hide();

         }

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

      split_layout::Pane * ppane = m_panea[iPane];

      if (ppane == nullptr)
      {

         return false;

      }

      ::pointer<::user::place_holder>pholder = ppane->m_pholder;

      if (pholder == nullptr)
      {

         return true; // assume future place_holder by default is visible

      }

      if (pholder->m_uiptraChild.is_empty())
      {

         return true; // assume future child by default is visible

      }

      if (!pholder->m_uiptraChild[0]->is_request_visible())
      {

         return false;

      }

      return true;

   }


   void split_layout::CalcPaneRect(::collection::index iPane, RECT32 * prect)

   {

      int nMinPos = GetMinPos(iPane);

      int nMaxPos = GetMaxPos(iPane);

      CalcPaneRect(nMinPos, nMaxPos, prect);


   }

   void split_layout::CalcPaneRect(int nMinPos, int nMaxPos, RECT32 * prect)

   {

      this->rectangle(prect);


      if(m_eorientationSplit == e_orientation_horizontal)
      {

         prect->top()      = nMinPos;


         prect->bottom()   = nMaxPos;


      }
      else
      {

         prect->left()   = nMinPos;


         prect->right()   = nMaxPos;


      }

   }


   int split_layout::get_normal_dimension()
   {

      ::double_rectangle rectangleX;

      this->rectangle(rectangleX);

      if(m_eorientationSplit == e_orientation_horizontal)
      {

         return rectangleX.height();

      }
      else
      {

         return rectangleX.width();

      }

   }


   int split_layout::get_ortogonal_dimension()
   {

      ::double_rectangle rectangleX;

      this->rectangle(rectangleX);

      if(m_eorientationSplit == e_orientation_horizontal)
      {

         return rectangleX.width();

      }
      else
      {

         return rectangleX.height();

      }

   }


   void split_layout::CalcSplitBarRect(::collection::index iIndex, RECT32 * prect)

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


      this->rectangle(prect);


      if(m_eorientationSplit == e_orientation_horizontal)
      {

         nPos = maximum(nPos, prect->top() + m_iMarging / 2);


         nPos = minimum(nPos, prect->bottom() - m_iMarging / 2);


         prect->top()      = nPos - m_iMarging / 2;


         prect->bottom()   = nPos + m_iMarging / 2;


      }
      else
      {

         nPos = maximum(nPos, prect->left() + m_iMarging / 2);


         nPos = minimum(nPos, prect->right() - m_iMarging / 2);


         prect->left()   = nPos - m_iMarging / 2;


         prect->right()   = nPos + m_iMarging / 2;


      }

   }


   bool split_layout::InsertPaneAt(::collection::index iIndex, ::user::interaction * puserinteraction, bool bFixedSize, ::atom atom)
   {

      ::collection::count iSplitBarCount = get_pane_count();

      m_splitbara.erase_all();

      ::collection::index i;

      for(i = 0; i < iSplitBarCount; i++)
      {

         auto  pbar =øcreate_new<split_bar>();

         m_splitbara.insert_at(iIndex, pbar);

         ::user::split_bar & splitbar = *m_splitbara.element_at(i);

         splitbar.m_iIndex = i;

         if (!splitbar.create_window(this))
         {

            return false;

         }

      }

      m_panea.insert_at(iIndex, aaa_primitive_new Pane);

      ASSERT(iIndex >= 0);

      ASSERT(iIndex < get_pane_count());

      split_layout::Pane * pcomponent = m_panea.element_at(iIndex);

      if(pcomponent->m_pholder != nullptr)
      {

         if (!pcomponent->m_pholder->place_hold(puserinteraction))
         {

            return false;

         }

      }
      else
      {

         pcomponent->m_pholder = place_hold(puserinteraction,pcomponent->m_rectangleX);

         if (pcomponent->m_pholder == nullptr)
         {

            return false;

         }

      }

      pcomponent->id() = atom.is_empty() ? (::atom) iIndex : atom;

      m_panea[iIndex]->m_bFixedSize = bFixedSize;

      return true;

   }


   bool split_layout::RemovePaneAt(::collection::index iIndex)
   {

      synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      ASSERT(iIndex >= 0);

      ASSERT(iIndex < get_pane_count());

      m_panea.erase_at(iIndex);

      ::collection::count iSplitBarCount = get_pane_count();

      m_splitbara.erase_all();

      ::collection::index i;

      for(i = 0; i < iSplitBarCount; i++)
      {

         m_splitbara.add_new(this);

         ::user::split_bar & splitbar = *m_splitbara.element_at(i);

         splitbar.m_iIndex = i;

         if (!splitbar.create_window(this))
         {

            return false;

         }

      }

      return true;

   }


   bool split_layout::SetPane(::collection::index iIndex, ::user::interaction * puserinteraction, bool bFixedSize, atom atom)
   {

      ASSERT(iIndex >= 0);

      ASSERT(iIndex < get_pane_count());

      split_layout::Pane * pcomponent = m_panea.element_at(iIndex);

      if(pcomponent->m_pholder != nullptr)
      {

         if (!pcomponent->m_pholder->place_hold(puserinteraction))
         {

            return false;

         }

      }
      else
      {

         ::double_rectangle rectanglePane;

         pcomponent->m_pholder->rectangle(rectanglePane);

         pcomponent->m_pholder = place_hold(puserinteraction, rectanglePane);

         if (pcomponent->m_pholder == nullptr)
         {

            return false;

         }

      }

      pcomponent->id() = atom.is_empty() ? (::atom) iIndex : atom;

      m_panea[iIndex]->m_bFixedSize = bFixedSize;

      return true;

   }


   void split_layout::SetPaneFixedSize(::collection::index iIndex, SIZE32 * pSize)
   {

      __UNREFERENCED_PARAMETER(iIndex);

      __UNREFERENCED_PARAMETER(pSize);

      ASSERT(iIndex >= 0);

      ASSERT(iIndex < get_pane_count());
      //    m_aFixedSize.element_at(iIndex) = *pSize;

   }


   int split_layout::GetMinPos(::collection::index iPane)
   {

      if (get_split_count() <= 0 || iPane <= 0)
      {

         return GetMinPos();

      }
      else
      {

         ::double_rectangle rectangle;

         CalcSplitBarRect(iPane - 1, rectangle);

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

   int split_layout::GetMaxPos(::collection::index iPane)
   {

      if (get_split_count() <= 0 || iPane >= get_split_count())
      {

         return GetMaxPos();

      }
      else
      {

         ::double_rectangle rectangle;

         CalcSplitBarRect(iPane, rectangle);

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


   void split_layout::RelayEventSplitBar(::collection::index iSplitBar, ::enum_message emessage, ::wparam wparam, ::lparam lparam)
   {

      ASSERT(false);

      if(!m_bInitialized)
         return;

      ::double_rectangle splitRect;

      CalcSplitBarRect(iSplitBar, &splitRect);

      if(emessage == ::user::e_message_left_button_down)
      {

         int   fwKeys = (int) wParam;        // key flags
//         int xPos = splitRect.left() + (short) LOWORD(lParam);  // horizontal position of cursor
//         int yPos = splitRect.top() + (short) HIWORD(lParam);  // vertical position of cursor
         if((fwKeys & MK_LBUTTON) > 0)
         {
            ::user::split_bar * pSplitBar = m_splitbara.element_at(iSplitBar);
            pSplitBar->SetCapture();
            m_iIndex = iSplitBar;
            m_iState = stateDragging;
         }
      }
      else if(emessage == ::user::e_message_left_button_up)
      {
//         int   fwKeys = wParam;        // key flags
//         int xPos = splitRect.left() + (short) LOWORD(lParam);  // horizontal position of cursor
//         int yPos = splitRect.top() + (short) HIWORD(lParam);  // vertical position of cursor
         if(m_iState != stateInitial)
         {
            psession->ReleaseCapture();
            m_iState = stateInitial;
         }
      }
      else if(emessage == ::user::e_message_capture_changed)
      {
      }
      else if(emessage == ::user::e_message_mouse_move)
      {
         int   fwKeys = (int) wParam;        // key flags
         int xPos = splitRect.left() + (short) LOWORD(lParam);  // horizontal position of cursor
         int yPos = splitRect.top() + (short) HIWORD(lParam);  // vertical position of cursor
         if((fwKeys & MK_LBUTTON) > 0 && (m_iState == stateDragging) && (iSplitBar == m_iIndex))
         {
            //cslock lock(m_pmutex);
            
            synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

            {
               informationf("split_layout::RelayChildEvent LOWORD(lParam) %d\n", LOWORD(lParam));
               informationf("split_layout::RelayChildEvent HIWORD(lParam) %d\n", HIWORD(lParam));


               int nPos;
               bool bMove;
               nPos = GetPos(xPos, yPos);
               if(m_iIndex <= 0)
               {
                  bMove = nPos > GetMinPos();
               }
               else
               {
                  bMove = nPos > (int) m_splitbara[m_iIndex - 1]->m_dwPosition;
               }
               if(get_pane_count() >= m_iIndex )
               {
                  bMove = bMove && nPos < GetMaxPos();
               }
               else
               {
                  bMove = bMove && nPos < (int) m_splitbara[m_iIndex]->m_dwPosition;
               }
               if(bMove)
               {
                  bMove = nPos != (int) m_splitbara[m_iIndex]->m_dwPosition;
               }
               if(bMove)
               {

                  m_splitbara[m_iIndex]->m_dwPosition = nPos;
                  m_splitbara[m_iIndex]->m_dRate = 0.0;
                  
                  set_need_layout();

               }
               
            }

         }
         else
         {

            m_iState = stateInitial;

         }

      }

   }


   rectangle & split_layout::get_pane_rect(::collection::index iPane)
   {

      ASSERT(iPane >= 0);

      ASSERT(iPane < get_pane_count());

      if (iPane < 0 || iPane >= get_pane_count())
      {

         throw ::exception(error_bad_argument);

      }

      return m_panea[iPane]->m_rectangleX;

   }


   ::pointer<::user::place_holder>split_layout::get_pane_holder(::collection::index iPane)
   {

      ASSERT(iPane >= 0);

      ASSERT(iPane < get_pane_count());

      if (iPane < 0 || iPane >= get_pane_count())
      {

         return nullptr;

      }

      return m_panea[iPane]->m_pholder;

   }


   ::pointer<::user::interaction>split_layout::get_pane_window(::collection::index iPane)
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

      Pane & pane = m_panea(iPane);

      return pane.id();

   }


   ::collection::index split_layout::get_pane_by_id(::atom atom)
   {

      for(::collection::index iPane = 0; iPane < m_panea.get_count(); iPane++)
      {

         if (m_panea[iPane]->id() == atom)
         {

            return iPane;

         }

      }

      return -1;

   }


   split_layout::Pane::Pane()
   {

      m_pholder = nullptr;

      m_rect.Null();

      m_rectangleX.Null();

      m_sizeFixed = ::size(0, 0);

   }


   void split_layout::draw_control_background(::draw2d::graphics_pointer & pgraphics)
   {

      auto pstyle = get_style(pgraphics);

      auto colorBackground = get_color(pstyle, e_element_background);

      if (colorBackground.m_iA > 0)
      {

         ::double_rectangle rectangleX;

         this->rectangle(rectangleX);

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         pgraphics->fill_rectangle(rectangleX, colorBackground);

      }

   }


   void split_layout::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

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


} // namespace user



