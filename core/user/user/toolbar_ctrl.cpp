#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/user/_user.h"
#endif


namespace user
{

   
   toolbar_control::~toolbar_control()
   {
      
      DestroyWindow();
      
   }


   //bool toolbar_control::create_window(u32 uStyle,const ::rect & rect, ::user::interaction * puiParent, ::id id)
   //{
   //   
   //   return create_window("ToolbarWindow32", nullptr, uStyle, puiParent, id);
   //   
   //}


   i32 toolbar_control::AddBitmap(i32 nNumButtons, ::draw2d::bitmap* pBitmap)
   {
#ifdef WINDOWS_DESKTOP
      ASSERT(is_window());
      TBADDBITMAP tbab;
      tbab.hInst = nullptr;
      tbab.nID = (UINT_PTR)pBitmap->get_os_data();
      return (i32) send_message( TB_ADDBITMAP, (WPARAM)nNumButtons,
         (LPARAM)&tbab);
#else
      __throw(todo());
#endif
   }

#ifdef WINDOWS_DESKTOP
   void toolbar_control::SaveState(HKEY hKeyRoot, const char * pszSubKey,

      const char * pszValueName)

   {
      ASSERT(is_window());
      TBSAVEPARAMSW tbs;
      tbs.hkr = hKeyRoot;
      tbs.pszSubKey = wstring(pszSubKey);

      tbs.pszValueName = wstring(pszValueName);

      send_message( TB_SAVERESTOREW, (WPARAM)TRUE, (LPARAM)&tbs);
   }

   void toolbar_control::RestoreState(HKEY hKeyRoot, const char * pszSubKey,

      const char * pszValueName)

   {
      ASSERT(is_window());
      TBSAVEPARAMSW tbs;
      tbs.hkr = hKeyRoot;
      tbs.pszSubKey = wstring(pszSubKey);

      tbs.pszValueName =wstring( pszValueName);

      send_message( TB_SAVERESTOREW, (WPARAM)FALSE, (LPARAM)&tbs);
   }
#endif


   void toolbar_control::_001OnCreate(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

#ifdef WINDOWS_DESKTOP
      SetButtonStructSize(sizeof(TBBUTTON));
#else
      __throw(todo());
#endif

   }


#ifdef WINDOWS_DESKTOP


   HRESULT toolbar_control::GetDropTarget(IDropTarget** ppDropTarget)
   {
      ASSERT(is_window());
      ASSERT(ppDropTarget);
#ifdef WINDOWS_DESKTOP
      return (HRESULT) send_message( TB_GETOBJECT, (WPARAM)&IID_IDropTarget, (LPARAM)ppDropTarget);
#else
      __throw(todo());
#endif
   }


#endif


   struct CToolBarCtrlData
   {
      ::u16 wVersion;
      ::u16 wWidth;
      ::u16 wHeight;
      ::u16 wItemCount;
      //::u16 aItems[wItemCount]

      ::u16* items()
      { return (::u16*)(this+1); }
   };

   /*bool toolbar_control::LoadToolBar(const char * pszResourceName)

   {
   ASSERT_VALID(this);
   ASSERT(pszResourceName != nullptr);


   // determine location of the bitmap in resource fork
   HINSTANCE hInst = ::aura::FindResourceHandle(pszResourceName, RT_TOOLBAR);

   HRSRC hRsrc = ::FindResource(hInst, pszResourceName, RT_TOOLBAR);

   if (hRsrc == nullptr)
   return FALSE;

   HGLOBAL hGlobal = LoadResource(hInst, hRsrc);
   if (hGlobal == nullptr)
   return FALSE;

   CToolBarCtrlData* pData = (CToolBarCtrlData*)LockResource(hGlobal);
   if (pData == nullptr)
   return FALSE;
   ASSERT(pData->wVersion == 1);

   ::u32* pItems = new ::u32[pData->wItemCount];
   for (i32 i = 0; i < pData->wItemCount; i++)
   pItems[i] = pData->items()[i];
   bool bResult = SetButtons(pItems, pData->wItemCount);
   delete[] pItems;

   if (bResult)
   {
   // set new sizes of the buttons
   size sizeImage(pData->wWidth, pData->wHeight);
   size sizeButton(pData->wWidth + 7, pData->wHeight + 7);
   //      SetSizes(sizeButton, sizeImage);

   // load bitmap now that sizes are known by the toolbar control
   LoadImages((i32)(::u16) (long *)pszResourceName, __get_resource_handle());

   }

   UnlockResource(hGlobal);
   

   return bResult;
   }*/

   bool toolbar_control::SetButtons(const ::u32* pIDArray, i32 nIDCount)

   {
      ASSERT_VALID(this);
      ASSERT(nIDCount >= 1);  // must be at least one of them
      ASSERT(pIDArray == nullptr ||

         __is_valid_address(pIDArray, sizeof(::u32) * nIDCount, FALSE));


      // delete all existing buttons
      /* linux i32 nCount = (i32)DefWindowProc(TB_BUTTONCOUNT, 0, 0);
      while (nCount--)
      VERIFY(DefWindowProc(TB_DELETEBUTTON, 0, 0));

      TBBUTTON button; __memset(&button, 0, sizeof(TBBUTTON));
      button.iString = -1;
      if (pIDArray != nullptr)

      {
      // add new buttons to the common control
      i32 iImage = 0;
      for (i32 i = 0; i < nIDCount; i++)
      {
      button.fsState = TBSTATE_ENABLED;
      if ((button.idCommand = *pIDArray++) == 0)

      {
      // separator
      button.fsStyle = TBSTYLE_SEP;
      // width of separator includes 8 pixel overlap
      ASSERT(gen_ComCtlVersion != -1);
      if ((GetStyle() & TBSTYLE_FLAT) || gen_ComCtlVersion == VERSION_IE4)
      button.iBitmap = 6;
      else
      button.iBitmap = 8;
      }
      else
      {
      // a command button with image
      button.fsStyle = TBSTYLE_BUTTON;
      button.iBitmap = iImage++;
      }
      if (!DefWindowProc(TB_ADDBUTTONSW, 1, (LPARAM)&button))
      return FALSE;
      }
      }
      else
      {
      // add 'blank' buttons
      button.fsState = TBSTATE_ENABLED;
      for (i32 i = 0; i < nIDCount; i++)
      {
      ASSERT(button.fsStyle == TBSTYLE_BUTTON);
      if (!DefWindowProc(TB_ADDBUTTONSW, 1, (LPARAM)&button))
      return FALSE;
      }
      }
      //   m_nCount = (i32)DefWindowProc(TB_BUTTONCOUNT, 0, 0);
      //   m_bDelayedButtonLayout = TRUE; */

      return TRUE;
   }

   i32 toolbar_control::GetButtonText(::u32 uId, string &str)
   {
#ifdef WINDOWS_DESKTOP
      UNREFERENCED_PARAMETER(uId);
      UNREFERENCED_PARAMETER(str);
      TBBUTTONINFOW tbbi;
      tbbi.cbSize = sizeof(tbbi);
      tbbi.dwMask = TBIF_TEXT;

      //      i32 nSize = 256;
      while(true)
      {
         /*         tbbi.pszText = str.GetBuffer(nSize);
         if(!tbbi.pszText)
         return 0;
         tbbi.cchText = nSize;
         if(GetButtonInfo(uId, &tbbi) != -1)
         {
         str.ReleaseBuffer();
         return 1;
         }
         nSize += 256;*/
      }
#else
      __throw(todo());
#endif
   }

   /////////////////////////////////////////////////////////////////////////////

   toolbar_control::toolbar_control()
   { }
   bool toolbar_control::EnableButton(i32 nID, bool bEnable)
   {
#ifdef WINDOWS_DESKTOP
      ASSERT(is_window()); return send_message( TB_ENABLEBUTTON, nID, MAKELPARAM(bEnable, 0)) != FALSE;
#else
      __throw(todo());
#endif

   }
   bool toolbar_control::CheckButton(i32 nID, bool bCheck)
   {
#ifdef WINDOWS_DESKTOP
      ASSERT(is_window()); return send_message( TB_CHECKBUTTON, nID, MAKELPARAM(bCheck, 0)) != FALSE;
#else
      __throw(todo());
#endif

   }
   bool toolbar_control::PressButton(i32 nID, bool bPress)
   {
#ifdef WINDOWS_DESKTOP
      ASSERT(is_window()); return send_message( TB_PRESSBUTTON, nID, MAKELPARAM(bPress, 0)) != FALSE;
#else
      __throw(todo());
#endif
   }


   bool toolbar_control::HideButton(i32 nID, bool bHide)
   {

#ifdef WINDOWS_DESKTOP
      ASSERT(is_window()); return send_message( TB_HIDEBUTTON, nID, MAKELPARAM(bHide, 0)) != FALSE;
#else
      __throw(todo());
#endif
   }


   bool toolbar_control::Indeterminate(i32 nID, bool bIndeterminate)
   {
#ifdef WINDOWS_DESKTOP
      ASSERT(is_window()); return send_message( TB_INDETERMINATE, nID, MAKELPARAM(bIndeterminate, 0)) != FALSE;
#else
      __throw(todo());
#endif
   }


   bool toolbar_control::IsButtonEnabled(i32 nID)
   {
#ifdef WINDOWS_DESKTOP
      ASSERT(is_window()); return send_message( TB_ISBUTTONENABLED, nID) != FALSE;
#else
      __throw(todo());
#endif
   }



   bool toolbar_control::IsButtonChecked(i32 nID)
   {
#ifdef WINDOWS_DESKTOP
      ASSERT(is_window()); return send_message( TB_ISBUTTONCHECKED, nID) != FALSE;
#else
      __throw(todo());
#endif
   }


   bool toolbar_control::IsButtonPressed(i32 nID)
   {
#ifdef WINDOWS_DESKTOP
      ASSERT(is_window()); return send_message( TB_ISBUTTONPRESSED, nID) != FALSE;
#else
      __throw(todo());
#endif
   }


   bool toolbar_control::IsButtonHidden(i32 nID)
   {
#ifdef WINDOWS_DESKTOP
      ASSERT(is_window()); return send_message( TB_ISBUTTONHIDDEN, nID) != FALSE;
#else
      __throw(todo());
#endif
   }


   bool toolbar_control::IsButtonIndeterminate(i32 nID)
   {
#ifdef WINDOWS_DESKTOP
      ASSERT(is_window()); return send_message( TB_ISBUTTONINDETERMINATE, nID) != FALSE;
#else
      __throw(todo());
#endif
   }


   bool toolbar_control::set_state(i32 nID, ::u32 nState)
   {
#ifdef WINDOWS_DESKTOP
      ASSERT(is_window()); 
      return send_message( TB_SETSTATE, nID, (LPARAM) nState) != FALSE;
#else
      __throw(todo());
#endif
   }


   i32 toolbar_control::GetState(i32 nID)
   {
#ifdef WINDOWS_DESKTOP
      ASSERT(is_window()); return (i32) send_message( TB_GETSTATE, nID);
#else
      __throw(todo());
#endif
   }


#ifdef WINDOWS_DESKTOP
   bool toolbar_control::AddButtons(i32 nNumButtons, LPTBBUTTON pButtons)

   {
#ifdef WINDOWS_DESKTOP
      ASSERT(is_window()); return send_message( TB_ADDBUTTONSW, nNumButtons, (LPARAM)pButtons) != FALSE;

#else
      __throw(todo());
#endif
   }
   bool toolbar_control::InsertButton(i32 nIndex, LPTBBUTTON pButton)

   {
#ifdef WINDOWS_DESKTOP
      ASSERT(is_window()); return send_message( TB_INSERTBUTTON, nIndex, (LPARAM)pButton) != FALSE;

#else
      __throw(todo());
#endif
   }
#endif


   bool toolbar_control::DeleteButton(i32 nIndex)
   {
#ifdef WINDOWS_DESKTOP
      ASSERT(is_window()); return send_message( TB_DELETEBUTTON, nIndex) != FALSE;
#else
      __throw(todo());
#endif
   }



#ifdef WINDOWS_DESKTOP

   bool toolbar_control::GetButton(i32 nIndex, LPTBBUTTON pButton)

   {

      ASSERT(is_window()); return send_message( TB_GETBUTTON, nIndex, (LPARAM)pButton) != FALSE;


   }

#endif




   i32 toolbar_control::GetButtonCount()
   {
#ifdef WINDOWS_DESKTOP
      ASSERT(is_window()); return (i32) send_message( TB_BUTTONCOUNT);

#else

      __throw(todo());

#endif
   }
   ::u32 toolbar_control::CommandToIndex(::u32 nID)
   {

#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return (::u32) send_message( TB_COMMANDTOINDEX, nID);

#else

      __throw(todo());

#endif

   }

   void toolbar_control::Customize()
   {

#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); send_message( TB_CUSTOMIZE);

#else

      __throw(todo());

#endif

   }

   // pszStrings are separated by zeroes, last one is marked by two zeroes

   i32 toolbar_control::AddStrings(const char * pszStrings)

   {

#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return (i32) send_message( TB_ADDSTRING, 0, (LPARAM)pszStrings);


#else

      __throw(todo());

#endif

   }

   bool toolbar_control::GetItemRect(i32 nIndex, RECT32 * prect)

   {

#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return send_message( TB_GETITEMRECT, nIndex, (LPARAM)prect) != FALSE;


#else

      __throw(todo());

#endif

   }

   void toolbar_control::SetButtonStructSize(i32 nSize)
   {

#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); send_message( TB_BUTTONSTRUCTSIZE, nSize);

#else

      __throw(todo());

#endif

   }

   bool toolbar_control::SetButtonSize(const ::size & size)
   {

#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return send_message( TB_SETBUTTONSIZE, 0, MAKELPARAM(size.cx, size.cy)) != FALSE;

#else

      __throw(todo());

#endif

   }

   bool toolbar_control::SetBitmapSize(const ::size & size)
   {

#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return send_message( TB_SETBITMAPSIZE, 0, MAKELPARAM(size.cx, size.cy)) != FALSE;

#else

      __throw(todo());

#endif

   }


   void toolbar_control::AutoSize()
   {

#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); send_message( TB_AUTOSIZE);

#else

      __throw(todo());

#endif

   }


   __pointer(::user::interaction)  toolbar_control::set_owner(__pointer(::user::interaction) pwindow)
   {

#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); send_message( TB_SETPARENT, (WPARAM)pwindow.m_p);

#else

      __throw(todo());

#endif
      return pwindow;

   }


   void toolbar_control::SetRows(i32 nRows, bool bLarger, RECT32 * prect)

   {

#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); send_message( TB_SETROWS, MAKELPARAM(nRows, bLarger), (LPARAM)prect);


#else

      __throw(todo());

#endif

   }


   i32 toolbar_control::GetRows()
   {

#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return (i32) send_message( TB_GETROWS);

#else

      __throw(todo());

#endif

   }


   bool toolbar_control::SetCmdID(i32 nIndex, ::u32 nID)
   {

#ifdef WINDOWS_DESKTOP

      ASSERT(is_window()); return send_message(TB_SETCMDID, nIndex, (LPARAM) nID) != FALSE;

#else

      __throw(todo());

#endif

   }


   ::u32 toolbar_control::GetBitmapFlags()
   {

#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return (::u32) send_message( TB_GETBITMAPFLAGS);

#else

      __throw(todo());

#endif

   }


   i32 toolbar_control::hit_test(POINT32 * ppt)
   {

#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return (i32) send_message( TB_HITTEST, 0, (LPARAM)ppt);

#else

      __throw(todo());

#endif

   }


   u32 toolbar_control::GetExtendedStyle()
   {

#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return (u32) send_message( TB_GETEXTENDEDSTYLE);

#else

      __throw(todo());

#endif

   }


   u32 toolbar_control::SetExtendedStyle(u32 dwExStyle)
   {

#ifdef WINDOWS_DESKTOP

      ASSERT(is_window()); return (u32) send_message( TB_SETEXTENDEDSTYLE, 0, (LPARAM) dwExStyle);

#else

      __throw(todo());

#endif

   }


   color32_t toolbar_control::GetInsertMarkColor()
   {

#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return (color32_t) send_message( TB_GETINSERTMARKCOLOR);

#else

      __throw(todo());

#endif

   }


   color32_t toolbar_control::SetInsertMarkColor(color32_t clrNew)
   {

#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return (color32_t) send_message( TB_SETINSERTMARKCOLOR, 0, (LPARAM) clrNew);

#else

      __throw(todo());

#endif

   }

   /////////////////////////////////////////////////////////////////////////////

   u32 toolbar_control::get_button_size()
   {

#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return (u32) send_message( TB_GETBUTTONSIZE);

#else

      __throw(todo());

#endif

   }


   ::image_list* toolbar_control::GetDisabledImageList()
   {

#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return nullptr;

#else

      __throw(todo());

#endif

   }


   ::image_list* toolbar_control::GetHotImageList()
   {

#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return nullptr;

#else

      __throw(todo());

#endif

   }


   ::image_list* toolbar_control::GetImageList()
   {

#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return nullptr;

#else

      __throw(todo());

#endif

   }


   u32 toolbar_control::GetStyle()
   {

#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return (u32) send_message( TB_GETSTYLE);

#else

      __throw(todo());

#endif

   }


   ::i32 toolbar_control::GetMaxTextRows()
   {

#ifdef WINDOWS_DESKTOP

      ASSERT(is_window()); 
      
      return (::i32) send_message(TB_GETTEXTROWS);

#else

      __throw(todo());

#endif

   }


   bool toolbar_control::GetRect(i32 nID, RECT32 * prect)

   {

#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return send_message( TB_GETRECT, nID, (LPARAM)prect) != FALSE;


#else

      __throw(todo());

#endif

   }


   bool toolbar_control::IsButtonHighlighted(i32 nID)
   {

#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return send_message( TB_ISBUTTONHIGHLIGHTED, nID) != FALSE;

#else

      __throw(todo());

#endif

   }


#ifdef WINDOWS_DESKTOP


   void toolbar_control::LoadImages(i32 iBitmapID, HINSTANCE hinst)
   {

#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); send_message( TB_LOADIMAGES, iBitmapID, (LPARAM)hinst);

#else

      __throw(todo());

#endif

   }


#endif


   bool toolbar_control::SetButtonWidth(i32 cxMin, i32 cxMax)
   {

#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return send_message( TB_SETBUTTONWIDTH, 0, MAKELPARAM(cxMin, cxMax)) != FALSE;

#else

      __throw(todo());

#endif

   }


   ::image_list* toolbar_control::SetDisabledImageList(::image_list* pImageList)
   {
      UNREFERENCED_PARAMETER(pImageList);
#ifdef WINDOWS_DESKTOP

      ASSERT(is_window());
      return nullptr;

#else

      __throw(todo());

#endif

   }


   ::image_list* toolbar_control::SetHotImageList(::image_list* pImageList)
   {
      UNREFERENCED_PARAMETER(pImageList);
#ifdef WINDOWS_DESKTOP

      ASSERT(is_window());
      return nullptr;

#else

      __throw(todo());

#endif

   }


   ::image_list* toolbar_control::SetImageList(::image_list* pImageList)
   {

      UNREFERENCED_PARAMETER(pImageList);

#ifdef WINDOWS_DESKTOP

      ASSERT(is_window());
      return nullptr;

#else

      __throw(todo());

#endif

   }


   bool toolbar_control::SetIndent(i32 iIndent)
   {
#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return send_message( TB_SETINDENT, iIndent) != FALSE;

#else

      __throw(todo());

#endif

   }
   bool toolbar_control::SetMaxTextRows(i32 iMaxRows)
   {
#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return send_message( TB_SETMAXTEXTROWS, iMaxRows) != FALSE;

#else

      __throw(todo());

#endif

   }
   void toolbar_control::SetStyle(u32 dwStyle)
   {
#ifdef WINDOWS_DESKTOP

      ASSERT(is_window()); send_message( TB_SETSTYLE, 0, (LPARAM) dwStyle);

#else

      __throw(todo());

#endif

   }

//#ifdef WINDOWS_DESKTOP
//
//   bool toolbar_control::GetButtonInfo(i32 nID, TBBUTTONINFO* ptbbi)
//   {
//
//      ASSERT(is_window()); return send_message( TB_GETBUTTONINFO, nID, (LPARAM)ptbbi) != FALSE;
//
//   }
//
//#endif
//

#ifdef WINDOWS_DESKTOP

   bool toolbar_control::GetButtonInfo(i32 nID, TBBUTTONINFOW* ptbbi)
   {

      ASSERT(is_window()); return send_message( TB_GETBUTTONINFOW, nID, (LPARAM)ptbbi) != FALSE;

   }

#endif


//#ifdef WINDOWS_DESKTOP
//
//   bool toolbar_control::SetButtonInfo(i32 nID, TBBUTTONINFO* ptbbi)
//   {
//
//      ASSERT(is_window()); return send_message( TB_SETBUTTONINFO, nID, (LPARAM)ptbbi) != FALSE;
//
//   }
//
//#endif


#ifdef WINDOWS_DESKTOP

   bool toolbar_control::SetButtonInfo(i32 nID, TBBUTTONINFOW* ptbbi)
   {

      ASSERT(is_window()); return send_message( TB_SETBUTTONINFOW, nID, (LPARAM)ptbbi) != FALSE;


   }

#endif


   u32 toolbar_control::SetDrawTextFlags(u32 dwMask, u32 dwDTFlags)
   {

#ifdef WINDOWS_DESKTOP

      ASSERT(is_window()); return (u32) send_message( TB_SETDRAWTEXTFLAGS, dwMask, (LPARAM) dwDTFlags);

#else

      __throw(todo());

#endif

   }
   bool toolbar_control::GetAnchorHighlight()
   {
#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return send_message( TB_GETANCHORHIGHLIGHT) != FALSE;

#else

      __throw(todo());

#endif

   }
   bool toolbar_control::SetAnchorHighlight(bool fAnchor)
   {
#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return send_message( TB_SETANCHORHIGHLIGHT, fAnchor) != FALSE;

#else

      __throw(todo());

#endif

   }
   i32 toolbar_control::GetHotItem()
   {
#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return (i32) send_message( TB_GETHOTITEM);

#else

      __throw(todo());

#endif

   }
   i32 toolbar_control::SetHotItem(i32 nHot)
   {
#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return (i32) send_message( TB_SETHOTITEM, nHot);

#else

      __throw(todo());

#endif

   }

#ifdef WINDOWS_DESKTOP

   void toolbar_control::GetInsertMark(TBINSERTMARK* ptbim)
   {


      ASSERT(is_window());

      send_message( TB_GETINSERTMARK, 0, (LPARAM)ptbim);

   }


   void toolbar_control::SetInsertMark(TBINSERTMARK* ptbim)
   {

      ASSERT(is_window());

      send_message( TB_SETINSERTMARK, 0, (LPARAM)ptbim);

   }


#endif


   bool toolbar_control::GetMaxSize(LPSIZE32 pSize)
   {
#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return send_message( TB_GETMAXSIZE, 0, (LPARAM)pSize) != FALSE;

#else

      __throw(todo());

#endif

   }


#ifdef WINDOWS_DESKTOP

   bool toolbar_control::InsertMarkHitTest(POINT32 * ppt, LPTBINSERTMARK ptbim)
   {

   ASSERT(is_window()); return send_message( TB_INSERTMARKHITTEST, (WPARAM)ppt, (LPARAM)ptbim) != FALSE;

   }

#endif


   bool toolbar_control::MapAccelerator(char chAccel, ::u32* pIDBtn)
   {
#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return send_message( TB_MAPACCELERATOR, (WPARAM)chAccel, (LPARAM)pIDBtn) != FALSE;

#else

      __throw(todo());

#endif

   }
   bool toolbar_control::MarkButton(i32 nID, bool bHighlight)
   {
#ifdef WINDOWS_DESKTOP

   ASSERT(is_window()); return send_message( TB_MARKBUTTON, nID, MAKELPARAM(bHighlight, 0)) != FALSE;

#else

      __throw(todo());

#endif

   }
   bool toolbar_control::MoveButton(::u32 nOldPos, ::u32 nNewPos)
   {

#ifdef WINDOWS_DESKTOP

      ASSERT(is_window()); return send_message( TB_MOVEBUTTON, nOldPos, (LPARAM) nNewPos) != FALSE;

#else

      __throw(todo());

#endif

   }


} // namespace user
