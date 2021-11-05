#include "framework.h"
#include "core/user/simple/_simple.h"


#define TIMER_HOVER 321654

#define ITEMCHECKEDCX 3
#define ITEMCHECKEDCY 2
#define ITEMCHECKEDPADLEFT 2
#define ITEMCHECKEDPADTOP 2
#define ITEMCHECKEDPADRIGHT 2
#define ITEMCHECKEDPADBOTTOM 2


simple_menu_bar::simple_menu_bar()
{

   __compose_new(m_pmenu);

   m_bTracking = false;
   m_iTopMenuCount = 0;
   m_iTracking = -1;

}

simple_menu_bar::~simple_menu_bar()
{

   
}


void simple_menu_bar::install_message_routing(::channel * pchannel)
{

   simple_toolbar::install_message_routing(pchannel);

   //MESSAGE_LINK(e_message_mouse_move, pchannel, this, &simple_menu_bar::on_message_mouse_move);
   //MESSAGE_LINK(e_message_non_client_mouse_move, pchannel, this, &simple_menu_bar::_001OnNcMouseMove);
   MESSAGE_LINK(e_message_create, pchannel, this, &simple_menu_bar::on_message_create);
   MESSAGE_LINK(e_message_key_down, pchannel, this, &simple_menu_bar::on_message_key_down);
   MESSAGE_LINK(e_message_destroy, pchannel, this, &simple_menu_bar::on_message_destroy);

//#ifdef WINDOWS_DESKTOP
//
//   MESSAGE_LINK(WM_MENUCHAR, pchannel, this, &simple_menu_bar::_001OnMenuChar);
//
//#endif

   //MESSAGE_LINK(e_message_left_button_down, pchannel, this, &simple_menu_bar::on_message_left_button_down);
   //MESSAGE_LINK(e_message_language, pchannel, this, &simple_menu_bar::_001OnAppLanguage);

   //MESSAGE_LINK(e_message_erase_background               , pchannel, this, *simple_menu_bar::_001On);

}


/////////////////////////////////////////////////////////////////////////////
// simple_menu_bar message handlers

bool simple_menu_bar::LoadMenuBar(::u32 nIDResource)
{

   m_uResourceId = nIDResource;

   /*    m_menu.Initialize(
         m_pimagelist,
         m_pimagelistDisabled,
         m_prel,
         &m_pfont);

      m_menu.LoadMenu(m_uResourceId);*/


//#ifdef WINDOWS_DESKTOP
//   send_message(TB_SETUNICODEFORMAT, 1);
//   string str;
//
//   TBBUTTON tbb;
//   __memset(&tbb, 0, sizeof(tbb));
//   tbb.iBitmap = 0;
//   tbb.fsState = TBSTATE_ENABLED;
//   tbb.fsStyle = TBSTYLE_BUTTON;
//   tbb.dwData = 0;
//   tbb.iString = 0;
//
//   TBBUTTONINFOW tbbi;
//   tbbi.cbSize = sizeof(tbbi);
//   tbbi.dwMask = TBIF_STYLE | TBIF_TEXT;
//
//   /*   m_buttona.set_size(mda.get_size());
//      for(i = 0; i < mda.get_size(); i++)
//      {
//         m_buttona[i].m_wstr = mda.element_at(i).m_wstr;
//      }*/
//#endif

   m_bDelayedButtonLayout = true;
   //_001Layout();

   {
      //      pointer_array <SimpleMenu , SimpleMenu &> * psma = nullptr;
   }

   return true;
}

void simple_menu_bar::SetMenuID(::u32 uResourceId)
{
   m_uResourceId = uResourceId;
}

bool simple_menu_bar::pre_create_window(::user::system * pusersystem)
{
   return simple_toolbar::pre_create_window(pusersystem);
}


/*void simple_menu_bar::OnDropDown(NMHDR * pNotifyStruct, LRESULT* result )
{
    LPNMTOOLBAR pnmtb = (LPNMTOOLBAR) pNotifyStruct;


//    m_pwthreadTracking = (CMenuTrackingThreadV033*) __begin_thread(__type(CMenuTrackingThreadV033));
  //  m_pwthreadTracking->m_evInitialized.lock();
    //m_pwthreadTracking->m_puiMain->SendMessage(WM_USER, 3, (LPARAM) this);
    //m_pwthreadTracking->m_puiMain->SendMessage(WM_USER, 4, pnmtb->iItem);

    TRACE("MenuBarV033::OnDropDown simple_menu_bar::_track_popup_menu % d\n", pnmtb->iItem);

    _track_popup_menu(pnmtb->iItem);


    *result = TBDDRET_DEFAULT;
}*/

/*bool simple_menu_bar::GetMenu(SimpleMenu **ppmenu)
{
    *ppmenu = m_pmenu;
    return ;
}*/


void simple_menu_bar::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
{

   simple_toolbar::route_command(pcommand);

}


//void simple_menu_bar::on_message_mouse_move(::message::message * pmessage)
//{
//   auto pmouse = pmessage->m_union.m_pmouse;
//   _001Hover(pmouse->m_point);
//   pmessage->previous();
//}


bool simple_menu_bar::_track_popup_menu(index iItem)
{

   INFORMATION("simple_menu_bar::_track_popup_menu" << iItem);
   
   m_iTracking = iItem;
   m_itemPressed = iItem;
   set_need_redraw();
   ::rectangle_i32 rectangle;
   _001GetElementRect(iItem, rectangle, ::e_element_item, ::user::e_state_none);
   client_to_screen(rectangle);

   /*#ifdef WINDOWS_DESKTOP
       TPMPARAMS tpm;
       tpm.cbSize = sizeof(TPMPARAMS);
       tpm.rcExclude.top    = rectangle.top;
       tpm.rcExclude.left   = rectangle.left;
       tpm.rcExclude.bottom = rectangle.bottom;
       tpm.rcExclude.right  = rectangle.right;
   #endif*/

   return true;

}


//void simple_menu_bar::_001OnNcMouseMove(::message::message * pmessage)
//{
//
//   auto pmouse = pmessage->m_union.m_pmouse;
//
//   _001Hover(pmouse->m_point);
//
//   // trans   simple_toolbar::OnNcMouseMove(pmouse->m_nFlags, pmouse->m_point);
//
//}


void simple_menu_bar::pre_translate_message(::message::message * pmessage)
{

   __pointer(::user::message) pusermessage(pmessage);

   if (pusermessage->m_id == WM_USER && pusermessage->userinteraction() == this)
   {

      if (pusermessage->m_wparam == 33)
      {

         _track_popup_menu((index)pusermessage->m_lparam);

      }

   }

   INFORMATION("simple_menu_bar::pre_translate_message messageID="<<pusermessage->m_id.i64()<<" wParam="<<pusermessage->m_wparam.m_number<<" lParam=" << pusermessage->m_lparam.m_lparam);

   return simple_toolbar::pre_translate_message(pmessage);

}


void simple_menu_bar::on_message_create(::message::message * pmessage)
{

   //   __pointer(::message::create) pcreate(pmessage);

   if (pmessage->previous())
   {

      return;

   }

   /*   MessageFilterHookManager * pmfmh = nullptr;

      if(!MessageFilterHookManager::AppGetMessageFilterHookManager(&pmfmh))

      {
         pcreate->set_lresult(-1);
         pcreate->m_bRet = true;
         return;
      }

      ASSERT(pmfmh != nullptr);

      pmfmh->MessageFilterHook(this);*/


   //m_menuhook.Install((__pointer(::user::frame_window)) (__pointer(::user::interaction))this);

   //   SetFont(pdraw2d->fonts().GetMenuFont());

   UpdateWindow();

}


//#ifdef WINDOWS_DESKTOP
//
//
//LRESULT CALLBACK simple_menu_bar::MessageProc(index code, WPARAM wParam, LPARAM lParam)
//{
//
//   __UNREFERENCED_PARAMETER(wParam);
//
//   MESSAGE * pmsg = (MESSAGE *)lParam;
//
//   if (code == MSGF_MENU)
//   {
//      if (pmsg->message == e_message_mouse_move)
//      {
//
//         u32 fwKeys = (u32)pmsg->wParam; // key flags
//
//         auto point = __point((::lparam) pmsg->lParam); // horizontal position of cursor
//
//         //index yPos = HIWORD(pmsg->lParam);
//
//         FORMATTED_TRACE("simple_menu_bar::MessageProc %d %d %d \n", fwKeys, point.x, point.y);
//
//         //::point_i32 point(xPos, yPos);
//
//         screen_to_client(point);
//
//         _track_popup_menu(point);
//
//      }
//
//   }
//
//   return 0;
//
//}
//
//
//#endif


bool simple_menu_bar::_track_popup_menu(const ::point_i32 & point)
{
   //if (m_bTracking)
   //{
   //   
   //   hit_test(m_itemHitTest, point);

   //   if (m_itemHitTest.is_valid_item(m_iTopMenuCount) && item != m_iTracking)
   //   {
   //      TRACE("simple_menu_bar::OnMouseMove simple_menu_bar::_track_popup_menu % d\n", item.m_iItem);
   //      //            SendMessage(e_message_key_down, VK_ESCAPE);
   //      //            if(m_iTracking >= 0)
   //      //          {
   //      send_message(WM_CANCELMODE);
   //      //        }
   //      send_message(WM_USER, 33, item.m_iItem);
   //      //return _track_popup_menu(iItem);
   //   }
   //}

   return true;

}

void simple_menu_bar::on_message_key_down(::message::message * pmessage)
{
   // TODO: add your message handler code here and/or call default

   pmessage->previous();
}



/*bool simple_menu_bar::CalcSize(::user::toolbar_control & tbc, size_i32 & size)
{
    ::rectangle_i32 rectangleItem;
    ::rectangle_i32 rectangleSize(0, 0, 0, 0);

    for(index i = 0; i < tbc.GetButtonCount(); i++)
    {
        tbc.GetItemRect(i, rectangleItem);
        rectangleSize.union(rectangleSize, rectangleItem);
    }
    size = rectangleSize.size();
    return ;
}

bool simple_menu_bar::CalcSize(CToolBarCtrl & tbc, size_i32 & size)
{
    ::rectangle_i32 rectangleItem;
    ::rectangle_i32 rectangleSize(0, 0, 0, 0);

    for(index i = 0; i < tbc.GetButtonCount(); i++)
    {
        tbc.GetItemRect(i, rectangleItem);
        rectangleSize.union(rectangleSize, rectangleItem);
    }
    size = rectangleSize.size();
    return ;
}*/



void simple_menu_bar::on_message_destroy(::message::message * pmessage)
{
   pmessage->previous();

   /*   MessageFilterHookManager * pmfmh = nullptr;

      if(MessageFilterHookManager::AppGetMessageFilterHookManager(&pmfmh)

         && pmfmh != nullptr)

      {
         pmfmh->MessageFilterUnhook(this);

      }*/
}

bool simple_menu_bar::Initialize(
__pointer(::image_list)   imagelist,
__pointer(::image_list)   imagelistDisabled,
i32_spreadset * prel,
::write_text::font *        pfont)
{

   //   m_menuhook.Initialize(
   //    imagelist,
   //imagelistDisabled,
   //prel,
   //pfont);

   m_pimagelist = imagelist;
   m_pimagelistDisabled = imagelistDisabled;
   m_prel = prel;

   //m_pfont->operator=(*pfont);

   return true;

}


void simple_menu_bar::RemoveAllButtons()
{
   m_itema.erase_all();
}

void simple_menu_bar::_001OnMenuChar(::message::message * pmessage)
{
   pmessage->previous();
}

void simple_menu_bar::OnUpdateCmdUI(__pointer(::user::frame_window)pTarget, bool bDisableIfNoHndler)
{
   __UNREFERENCED_PARAMETER(pTarget);
   __UNREFERENCED_PARAMETER(bDisableIfNoHndler);
   return;
   /*   tool_command state;
      state.m_pOther = this;

      state.m_nIndexMax = (::u32)DefWindowProc(TB_BUTTONCOUNT, 0, 0);
      for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax; state.m_nIndex++)
      {
         // get buttons state
         TBBUTTON button;
         _GetButton(state.m_nIndex, &button);
         state.m_nID = button.idCommand;

         // ignore separators
         if (!(button.fsStyle & TBSTYLE_SEP))
         {
            // allow reflections
            if (::user::interaction::on_command(0,
               MAKELONG((index)CN_UPDATE_::message::command, e_message_command+WM_REFLECT_BASE),
               &state, nullptr))
               continue;

            // allow the toolbar itself to have update handlers
            if (::user::interaction::on_command(state.m_nID, CN_UPDATE_::message::command, &state, nullptr))
               continue;

            // allow the owner to process the update
            state.DoUpdate(pTarget, bDisableIfNoHndler);
         }
      }

      // update the dialog controls added to the toolbar
      UpdateDialogControls(pTarget, bDisableIfNoHndler);*/
}


// index simple_menu_bar::OnMessage(MPARAM mparam, NPARAM nparam, OPARAM oparam)
// {
//    __UNREFERENCED_PARAMETER(nparam);
//    __UNREFERENCED_PARAMETER(oparam);
//    if(mparam == MX_APPLANGUAGE)
//    {
//       ReloadMenuBar();
//    }
//    return 0;
// }



//void simple_menu_bar::_001OnAppLanguage(::message::message * pmessage)
//{
//
//   ReloadMenuBar();
//
//}


bool simple_menu_bar::ReloadMenuBar()
{

//#ifdef WINDOWS_DESKTOP
//
//   send_message(WM_CANCELMODE);
//
//#endif

   if (!LoadMenuBar(m_uResourceId))
      return false;

   set_need_redraw();

   return true;

}


/*void simple_menu_bar::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{
   ::rectangle_i32 rectangleClient;
   get_client_rect(rectangleClient);
   class imaging & imaging = psystem->imaging();
   if(m_iHover >= -1)
   {
      imaging.color_blend(
         pgraphics,
         rectangleClient.left,
         rectangleClient.top,
         rectangleClient.width(),
         rectangleClient.height(),
         rgb(255, 255, 250),
         128);
   }
   else
   {
      imaging.color_blend(
         pgraphics,
         rectangleClient.left,
         rectangleClient.top,
         rectangleClient.width(),
         rectangleClient.height(),
         rgb(230, 230, 225),
         56);
   }

   pgraphics->set(pdraw2d->fonts().GetMenuFont());
   pgraphics->SetBkMode(TRANSPARENT);
   for(index iItem = 0; iItem < m_buttona.get_size(); iItem++)
   {
      _001DrawItem(pgraphics, iItem);
   }

}
*/
/*bool simple_menu_bar::_001GetItemRect(index iItem, RECTANGLE_I32 * prectangle, enum_element eelement)

{
   if(iItem < 0 ||
      iItem >= m_buttona.get_size())
      return false;

   switch(eelement)
   {
   case e_element_item:
      prectangle->left   = m_buttona[iItem].m_rectangle.left + ITEMCHECKEDCX;

      prectangle->right  = m_buttona[iItem].m_rectangle.right + ITEMCHECKEDPADRIGHT;

      prectangle->top    = m_buttona[iItem].m_rectangle.top + ITEMCHECKEDCY;

      prectangle->bottom = m_buttona[iItem].m_rectangle.bottom;

      break;
   case element_item_hover:
      prectangle->left   = m_buttona[iItem].m_rectangle.left - ITEMCHECKEDPADLEFT;

      prectangle->right  = m_buttona[iItem].m_rectangle.right - ITEMCHECKEDCX + ITEMCHECKEDPADRIGHT;

      prectangle->top    = m_buttona[iItem].m_rectangle.top;

      prectangle->bottom = m_buttona[iItem].m_rectangle.bottom - ITEMCHECKEDCY;

      break;
   case e_element_text:
      prectangle->left   = m_buttona[iItem].m_rectangle.left + ITEMCHECKEDCX;

      prectangle->right  = m_buttona[iItem].m_rectangle.right;

      prectangle->top    = m_buttona[iItem].m_rectangle.top + ITEMCHECKEDCY;

      prectangle->bottom = m_buttona[iItem].m_rectangle.bottom;

      break;
   case element_text_hover:
      prectangle->left   = m_buttona[iItem].m_rectangle.left + ITEMCHECKEDPADLEFT;

      prectangle->right  = m_buttona[iItem].m_rectangle.right - ITEMCHECKEDPADRIGHT - ITEMCHECKEDCX;

      prectangle->top    = m_buttona[iItem].m_rectangle.top + ITEMCHECKEDPADTOP;

      prectangle->bottom = m_buttona[iItem].m_rectangle.bottom - ITEMCHECKEDPADBOTTOM - ITEMCHECKEDCY;

      break;
   default:
      break;
   }
   return true;
}*/

/*bool simple_menu_bar::_001CheckItem(index iItem, bool bCheck)
{
   if(iItem < 0 ||
      iItem >= m_buttona.get_size())
      return false;
//   m_buttona[iItem].m_bCheck = bCheck;
   return true;
}

index simple_menu_bar::_001HitTest(const POINT_I32 *ppoint)

{
   for(index iItem = 0; iItem < m_buttona.get_size(); iItem++)
   {
      if(m_buttona[iItem].m_rectangle.contains(*ppoint))

         return iItem;
   }
   ::rectangle_i32 rectangleClient;
   get_client_rect(rectangleClient);
   if(rectangleClient.contains(*ppoint))

      return -1;
   else
      return 0x80000000;
}*/

/*void simple_menu_bar::_001Layout()
{
   ::draw2d::memory_graphics pgraphics(this);;
   pgraphics->set(pdraw2d->fonts().GetMenuFont());

   ::size_i32 size;
   index ix = ITEMCHECKEDPADLEFT;
   index iy = 0;
   for(index iItem = 0; iItem < m_buttona.get_size(); iItem++)
   {
      ::GetTextExtentPoint32W(
         (HDC)pgraphics->get_os_data(),
         m_buttona[iItem].m_wstr,
         m_buttona[iItem].m_wstr.get_length(),
         &size);
      m_buttona[iItem].m_rectangle.left  = ix ;
      ix += size.cx + ITEMCHECKEDCX + ITEMCHECKEDPADLEFT + ITEMCHECKEDPADRIGHT;
      m_buttona[iItem].m_rectangle.right = ix;
      m_buttona[iItem].m_rectangle.top   = 0;
      iy = maximum(iy, size.cy);
   }
   for(iItem = 0; iItem < m_buttona.get_size(); iItem++)
   {
      m_buttona[iItem].m_rectangle.bottom = iy + ITEMCHECKEDCX + ITEMCHECKEDPADTOP + ITEMCHECKEDPADBOTTOM;
   }


}*/


//bool simple_menu_bar::create_window(::user::interaction * puiParent, u32 uStyle, ::id id)
//{
//
//   return create_window_ex(puiParent, 0, uStyle, id);
//
//}


//bool simple_menu_bar::create_window_ex(::user::interaction * puiParent, u32 dwCtrlStyle, u32 uStyle, ::id id)
//{
//
//   ASSERT_VALID(puiParent);   // must have a parent
//   ASSERT(!((uStyle & CBRS_SIZE_FIXED) && (uStyle & CBRS_SIZE_DYNAMIC)));
//
//   //SetBorders(rectangle);
//
//   // save the style
//   m_dwStyle = (uStyle & CBRS_ALL);
//   if (id == __IDW_TOOLBAR)
//      m_dwStyle |= CBRS_HIDE_INPLACE;
//
//   uStyle &= ~CBRS_ALL;
//#ifdef WINDOWS_DESKTOP
//   uStyle |= CCS_NOPARENTALIGN | CCS_NOMOVEY | CCS_NODIVIDER | CCS_NORESIZE;
//#endif
//   uStyle |= dwCtrlStyle;
//
//   //   ASSERT(gen_ComCtlVersion != -1);
//   //   _::aura::GetDropDownWidth();
//   //   ASSERT(gen_DropDownWidth != -1);
//
//   // create the oswindow
//   if (!::user::interaction::create_window(nullptr, nullptr, uStyle, puiParent, id))
//   {
//
//      return false;
//
//   }
//
//   // synchronization_object up the sizes
////   SetSizes(m_sizeButton, m_sizeImage);
//
//   // Note: Parent must resize itself for control bar to be resized
//
//   return true;
//
//}


//void simple_menu_bar::on_message_left_button_down(::message::message * pmessage)
//{
//   auto pmouse = pmessage->m_union.m_pmouse;
//
//   auto item = hit_test(pmouse->m_point);
//
//   if (item)
//   {
//
//      _001OnDropDown(item);
//
//   }
//   else
//   {
//      // trans  simple_toolbar::OnLButtonDown(pmouse->m_nFlags, pmouse->m_point);
//   }
//}

/*size_i32 simple_menu_bar::CalcDynamicLayout(index nLength, u32 dwMode)
{
    if ((nLength == -1) && !(dwMode & LM_MRUWIDTH) && !(dwMode & LM_COMMIT) &&
      ((dwMode & LM_HORZDOCK) || (dwMode & LM_VERTDOCK)))
   {
      return CalcFixedLayout(dwMode & LM_STRETCH, dwMode & LM_HORZDOCK);
   }
   return CalcLayout(dwMode, nLength);

}
size_i32 simple_menu_bar::CalcLayout(u32 dwMode, index nLength)
{
   _001Layout();
   size_i32 sizeResult;
   sizeResult.cx = 0;
   sizeResult.cy = 0;

   if(m_buttona.get_size() > 0)
   {
      sizeResult.cx = m_buttona[m_buttona.get_size() - 1].m_rectangle.right + ITEMCHECKEDPADRIGHT;
      sizeResult.cy = m_buttona[m_buttona.get_size() - 1].m_rectangle.bottom;
   }

   return sizeResult;
}

size_i32 simple_menu_bar::CalcFixedLayout(bool bStretch, bool bHorz)
{
   u32 dwMode = bStretch ? LM_STRETCH : 0;
   dwMode |= bHorz ? LM_HORZ : 0;

   return CalcLayout(dwMode, -1);
}
*/

/*void simple_menu_bar::_001DrawItem(::draw2d::graphics *graphics, index iItem)
{
   ::rectangle_i32 rectangleItem;
   ::rectangle_i32 rectangleText;

   SimpleMenuBarButton & button = m_buttona[iItem];


   enum_element eelement = e_element_item;
   enum_element eelementText = e_element_text;
   if(m_iTracking >= 0)
   {
      if(iItem == m_iTracking)
      {
         eelement = element_item_hover;
         eelementText = element_text_hover;
      }
   }
   else
   {
      if(iItem == m_iHover)
      {
         eelement = element_item_hover;
         eelementText = element_text_hover;
      }
   }

   _001GetItemRect(iItem, rectangleItem, eelement);
   _001GetItemRect(iItem, rectangleText, eelementText);

   if(eelement == element_item_hover)
   {
      ::rectangle_i32 rectangleShadow;
      _001GetItemRect(iItem, rectangleShadow, e_element_item);

      ::draw2d::pen_pointer ppenShadow(get_application(), PS_SOLID, 1, rgb(127, 127, 127));
      ::draw2d::brush_pointer pbrushShadow(get_application(), rgb(127, 127, 127));
      ::draw2d::pen * ppenOld = pgraphics->set(ppenShadow);
      ::draw2d::brush * pbrushOld = pgraphics->set(pbrushShadow);
      pgraphics->rectangle(rectangleShadow);

      ::draw2d::pen_pointer pen(get_application(), PS_SOLID, 1, rgb(92, 92, 92));
      ::draw2d::brush_pointer brush(get_application(), rgb(255, 255, 255));
      pgraphics->set(ppen);
      pgraphics->set(pbrush);
      pgraphics->rectangle(rectangleItem);
      pgraphics->set(ppenOld);
      pgraphics->set(pbrushOld);

      ::rectangle_i32 rectangle;
      _001GetItemRect(iItem, rectangle, e_element_text);
      pgraphics->set_text_color(rgb(192, 192, 192));
      draw2d::graphics_extension::_DrawText(pgraphics,
         button.m_wstr,
         rectangle,
         e_align_left_center);
   }

   pgraphics->set_text_color(rgb(0, 0, 0));
   draw2d::graphics_extension::_DrawText(pgraphics,
      button.m_wstr,
      rectangleText,
      e_align_left_center);


}
*/

/*SimpleMenuBarButton::SimpleMenuBarButton()
{
//   m_bCheck = false;
}*/

/*void simple_menu_bar::_001Hover(const ::point_i32 & point)
{
   _track_popup_menu(point);
   index iHover = -1;
   if(m_iTracking >= 0)
   {
      iHover   = m_iTracking;
      m_iHover = iHover;
   }
   else
   {
      iHover = _001HitTest(&point);
   }
   if(m_iHover != iHover)
   {
      m_iHover = iHover;
      if(m_iHover < -1 && m_iTracking < 0)
      {
         KillTimer(TIMER_HOVER);
      }
      else
      {
         SetTimer(TIMER_HOVER, 50, nullptr);
      }
      set_need_redraw();
   }
}

void simple_menu_bar::_001Hover()
{
   ::point_i32 point;
   GetCursorPos(&point);
   screen_to_client(point);
   _001Hover(point);
}*/

void simple_menu_bar::_001OnTimer(::timer * ptimer)
{
   simple_toolbar::_001OnTimer(ptimer);
//   if (ptimer->m_uEvent == TIMER_HOVER)
//   {
//      _001Hover();
//   }

   //   pmessage->previous();
}

/*
bool simple_menu_bar::OnEraseBkgnd(::draw2d::graphics_pointer & pgraphics)
{
   return true;
}
*/

/*index simple_menu_bar::_001GetHoverItem()
{
   return m_iHover;
}*/


void simple_menu_bar::_001OnDropDown(index iItem)
{

   _track_popup_menu(iItem);

}


bool simple_menu_bar::on_click(const ::item & item)
{
   
   return false;

}


//void simple_menu_bar::OnUpdateHover()
//{
//
//   if (m_itemHover)
//   {
//
//      //_track_popup_menu(m_iHover);
//
//   }
//
//}
//
//
//index simple_menu_bar::_001GetHoverItem()
//{
//
//   if (m_iTracking >= 0)
//   {
//
//      return m_iTracking;
//
//   }
//
//   return simple_toolbar::_001GetHoverItem();
//
//
//}


//void simple_menu_bar::_001OnAppLanguage(::message::message * pmessage)
//{
//   __pointer(::user::message) pusermessage(pmessage);
//   send_message(WM_CANCELMODE);
//   LoadMenuBar(m_uResourceId);
//   set_need_redraw();
//   pusermessage->m_bRet = false;
//}
