#include "framework.h"
#include "toolbar_control.h"


namespace user
{

   
   toolbar_control::~toolbar_control()
   {
      
      destroy_window();
      
   }


   //bool toolbar_control::create_window(u32 uStyle,const ::rectangle_i32 & rectangle, ::user::interaction * puiParent, ::atom atom)
   //{
   //   
   //   return create_window("ToolbarWindow32", nullptr, uStyle, puiParent, atom);
   //   
   //}


//   i32 toolbar_control::AddBitmap(i32 nNumButtons, ::draw2d::bitmap* pBitmap)
//   {
////#ifdef WINDOWS_DESKTOP
////      ASSERT(is_window());
////      TBADDBITMAP tbab;
////      tbab.hInst = nullptr;
////      tbab.nID = (UINT_PTR)pBitmap->get_os_data();
////      return (i32) send_message( TB_ADDBITMAP, (WPARAM)nNumButtons,
////         (LPARAM)&tbab);
////#else
////      throw ::exception(todo);
////#endif
//   }

//#ifdef WINDOWS_DESKTOP
//   void toolbar_control::SaveState(HKEY hKeyRoot, const ::string & pszSubKey,
//
//      const ::scoped_string & scopedstrValueName)
//
//   {
//      ASSERT(is_window());
//      TBSAVEPARAMSW tbs;
//      tbs.hkr = hKeyRoot;
//      tbs.pszSubKey = wstring(pszSubKey);
//
//      tbs.pszValueName = wstring(pszValueName);
//
//      send_message( TB_SAVERESTOREW, (WPARAM)true, (LPARAM)&tbs);
//   }
//
//   void toolbar_control::RestoreState(HKEY hKeyRoot, const ::string & pszSubKey,
//
//      const ::scoped_string & scopedstrValueName)
//
//   {
//      ASSERT(is_window());
//      TBSAVEPARAMSW tbs;
//      tbs.hkr = hKeyRoot;
//      tbs.pszSubKey = wstring(pszSubKey);
//
//      tbs.pszValueName =wstring( pszValueName);
//
//      send_message( TB_SAVERESTOREW, (WPARAM)false, (LPARAM)&tbs);
//   }
//#endif


   void toolbar_control::on_message_create(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

//#ifdef WINDOWS_DESKTOP
//      SetButtonStructSize(sizeof(TBBUTTON));
//#else
//      throw ::exception(todo);
//#endif

   }


//#ifdef WINDOWS_DESKTOP
//
//
//   HRESULT toolbar_control::GetDropTarget(IDropTarget** ppDropTarget)
//   {
//      ASSERT(is_window());
//      ASSERT(ppDropTarget);
////#ifdef WINDOWS_DESKTOP
////      return (HRESULT) send_message( TB_GETOBJECT, (WPARAM)&IID_IDropTarget, (LPARAM)ppDropTarget);
////#else
////      throw ::exception(todo);
////#endif
//
//      return 0;
//
//   }
//
//
//#endif


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

   /*bool toolbar_control::LoadToolBar(const ::string & pszResourceName)

   {
   ASSERT_VALID(this);
   ASSERT(pszResourceName != nullptr);


   // determine location of the bitmap in resource fork
   HINSTANCE hInst = ::aura::FindResourceHandle(pszResourceName, RT_TOOLBAR);

   HRSRC hRsrc = ::FindResource(hInst, pszResourceName, RT_TOOLBAR);

   if (hRsrc == nullptr)
   return false;

   HGLOBAL hGlobal = LoadResource(hInst, hRsrc);
   if (hGlobal == nullptr)
   return false;

   CToolBarCtrlData* pData = (CToolBarCtrlData*)LockResource(hGlobal);
   if (pData == nullptr)
   return false;
   ASSERT(pData->wVersion == 1);

   ::u32* pItems = memory_new ::u32[pData->wItemCount];
   for (i32 i = 0; i < pData->wItemCount; i++)
   pItems[i] = pData->items()[i];
   bool bResult = SetButtons(pItems, pData->wItemCount);
   delete[] pItems;

   if (bResult)
   {
   // set memory_new sizes of the buttons
   size_i32 sizeImage(pData->wWidth, pData->wHeight);
   size_i32 sizeButton(pData->wWidth + 7, pData->wHeight + 7);
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

         __is_valid_address(pIDArray, sizeof(::u32) * nIDCount, false));


      // delete all existing buttons
      /* linux i32 nCount = (i32)DefWindowProc(TB_BUTTONCOUNT, 0, 0);
      while (nCount--)
      VERIFY(DefWindowProc(TB_DELETEBUTTON, 0, 0));

      TBBUTTON button; memory_set(&button, 0, sizeof(TBBUTTON));
      button.iString = -1;
      if (pIDArray != nullptr)

      {
      // add memory_new buttons to the common control
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
      return false;
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
      return false;
      }
      }
      //   m_nCount = (i32)DefWindowProc(TB_BUTTONCOUNT, 0, 0);
      //   m_bDelayedButtonLayout = true; */

      return true;
   }

   i32 toolbar_control::GetButtonText(::u32 uId, string &str)
   {
      
      return 0;

//#ifdef WINDOWS_DESKTOP
//      __UNREFERENCED_PARAMETER(uId);
//      __UNREFERENCED_PARAMETER(str);
//      TBBUTTONINFOW tbbi;
//      tbbi.cbSize = sizeof(tbbi);
//      tbbi.dwMask = TBIF_TEXT;
//
//      //      i32 nSize = 256;
//      while(true)
//      {
//         /*         tbbi.pszText = str.GetBuffer(nSize);
//         if(!tbbi.pszText)
//         return 0;
//         tbbi.cchText = nSize;
//         if(GetButtonInfo(uId, &tbbi) != -1)
//         {
//         str.ReleaseBuffer();
//         return 1;
//         }
//         nSize += 256;*/
//      }
//#else
//      throw ::exception(todo);
//#endif
   }

   /////////////////////////////////////////////////////////////////////////////

   toolbar_control::toolbar_control()
   { }
   bool toolbar_control::EnableButton(i32 nID, bool bEnable)
   {
//#ifdef WINDOWS_DESKTOP
//      ASSERT(is_window()); return send_message( TB_ENABLEBUTTON, nID, MAKELPARAM(bEnable, 0)) != false;
//#else
//      throw ::exception(todo);
//#endif

      return false;

   }
   bool toolbar_control::CheckButton(i32 nID, bool bCheck)
   {
//#ifdef WINDOWS_DESKTOP
//      ASSERT(is_window()); return send_message( TB_CHECKBUTTON, nID, MAKELPARAM(bCheck, 0)) != false;
//#else
//      throw ::exception(todo);
//#endif

      return false;

   }
   bool toolbar_control::PressButton(i32 nID, bool bPress)
   {
//#ifdef WINDOWS_DESKTOP
//      ASSERT(is_window()); return send_message( TB_PRESSBUTTON, nID, MAKELPARAM(bPress, 0)) != false;
//#else
//      throw ::exception(todo);
//#endif

      return false;

   }


   bool toolbar_control::HideButton(i32 nID, bool bHide)
   {

//#ifdef WINDOWS_DESKTOP
//      ASSERT(is_window()); return send_message( TB_HIDEBUTTON, nID, MAKELPARAM(bHide, 0)) != false;
//#else
//      throw ::exception(todo);
//#endif

      return true;

   }


   bool toolbar_control::Indeterminate(i32 nID, bool bIndeterminate)
   {
//#ifdef WINDOWS_DESKTOP
//      ASSERT(is_window()); return send_message( TB_INDETERMINATE, nID, MAKELPARAM(bIndeterminate, 0)) != false;
//#else
//      throw ::exception(todo);
//#endif

      return false;

   }


   bool toolbar_control::IsButtonEnabled(i32 nID)
   {
//#ifdef WINDOWS_DESKTOP
//      ASSERT(is_window()); return send_message( TB_ISBUTTONENABLED, nID) != false;
//#else
//      throw ::exception(todo);
//#endif

      return false;

   }



   bool toolbar_control::IsButtonChecked(i32 nID)
   {
//#ifdef WINDOWS_DESKTOP
//      ASSERT(is_window()); return send_message( TB_ISBUTTONCHECKED, nID) != false;
//#else
//      throw ::exception(todo);
//#endif

      return false;

   }


   bool toolbar_control::IsButtonPressed(i32 nID)
   {
//#ifdef WINDOWS_DESKTOP
//      ASSERT(is_window()); return send_message( TB_ISBUTTONPRESSED, nID) != false;
//#else
//      throw ::exception(todo);
//#endif

      return false;

   }


   bool toolbar_control::IsButtonHidden(i32 nID)
   {
//#ifdef WINDOWS_DESKTOP
//      ASSERT(is_window()); return send_message( TB_ISBUTTONHIDDEN, nID) != false;
//#else
//      throw ::exception(todo);
//#endif

      return false;

   }


   bool toolbar_control::IsButtonIndeterminate(i32 nID)
   {
//#ifdef WINDOWS_DESKTOP
//      ASSERT(is_window()); return send_message( TB_ISBUTTONINDETERMINATE, nID) != false;
//#else
//      throw ::exception(todo);
//#endif

      return false;

   }


   bool toolbar_control::set_state(i32 nID, ::u32 nState)
   {
//#ifdef WINDOWS_DESKTOP
//      ASSERT(is_window()); 
//      return send_message( TB_SETSTATE, nID, (LPARAM) nState) != false;
//#else
//      throw ::exception(todo);
//#endif

      return false;

   }


   i32 toolbar_control::GetState(i32 nID)
   {
//#ifdef WINDOWS_DESKTOP
//      ASSERT(is_window()); return (i32) send_message( TB_GETSTATE, nID);
//#else
//      throw ::exception(todo);
//#endif

      return -1;

   }


//#ifdef WINDOWS_DESKTOP
//   bool toolbar_control::AddButtons(i32 nNumButtons, LPTBBUTTON pButtons)
//
//   {
//#ifdef WINDOWS_DESKTOP
//      ASSERT(is_window()); return send_message( TB_ADDBUTTONSW, nNumButtons, (LPARAM)pButtons) != false;
//
//#else
//      throw ::exception(todo);
//#endif
//   }
//   bool toolbar_control::InsertButton(i32 nIndex, LPTBBUTTON pButton)
//
//   {
//#ifdef WINDOWS_DESKTOP
//      ASSERT(is_window()); return send_message( TB_INSERTBUTTON, nIndex, (LPARAM)pButton) != false;
//
//#else
//      throw ::exception(todo);
//#endif
//   }
//#endif
//
//
//   bool toolbar_control::DeleteButton(i32 nIndex)
//   {
//#ifdef WINDOWS_DESKTOP
//      ASSERT(is_window()); return send_message( TB_DELETEBUTTON, nIndex) != false;
//#else
//      throw ::exception(todo);
//#endif
//   }
//
//
//
//#ifdef WINDOWS_DESKTOP
//
//   bool toolbar_control::GetButton(i32 nIndex, LPTBBUTTON pButton)
//
//   {
//
//      ASSERT(is_window()); return send_message( TB_GETBUTTON, nIndex, (LPARAM)pButton) != false;
//
//
//   }
//
//#endif




   i32 toolbar_control::GetButtonCount()
   {
//#ifdef WINDOWS_DESKTOP
//      ASSERT(is_window()); return (i32) send_message( TB_BUTTONCOUNT);
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return -1;

   }



   ::u32 toolbar_control::CommandToIndex(::u32 nID)
   {

//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); return (::u32) send_message( TB_COMMANDTOINDEX, nID);
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return 0;

   }


   void toolbar_control::Customize()
   {

//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); send_message( TB_CUSTOMIZE);
//
//#else
//
//      throw ::exception(todo);
//
//#endif

   }


   // pszStrings are separated by zeroes, last one is marked by two zeroes

   i32 toolbar_control::AddStrings(const ::string & pszStrings)
   {

//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); return (i32) send_message( TB_ADDSTRING, 0, (LPARAM)pszStrings);
//
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return -1;

   }


   bool toolbar_control::GetItemRect(i32 nIndex, RECTANGLE_I32 * prectangle)
   {

//#ifdef WINDOWS_DESKTOP
//
//      ASSERT(is_window()); return send_message( TB_GETITEMRECT, nIndex, (LPARAM)prectangle) != false;
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return false;

   }


   void toolbar_control::SetButtonStructSize(i32 nSize)
   {

//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); send_message( TB_BUTTONSTRUCTSIZE, nSize);
//
//#else
//
//      throw ::exception(todo);
//
//#endif

//      return -;

   }


   bool toolbar_control::SetButtonSize(const ::size_i32 & size)
   {

      return false;

//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); return send_message( TB_SETBUTTONSIZE, 0, MAKELPARAM(size.cx, size.cy)) != false;
//
//#else
//
//      throw ::exception(todo);
//
//#endif

   }


   bool toolbar_control::SetBitmapSize(const ::size_i32 & size)
   {

//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); return send_message( TB_SETBITMAPSIZE, 0, MAKELPARAM(size.cx, size.cy)) != false;
//
//#else
//
//      throw ::exception(todo);
//
//#endif

         return true;

   }


   void toolbar_control::AutoSize()
   {

//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); send_message( TB_AUTOSIZE);
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      //return false;

   }


   ::pointer<::user::interaction> toolbar_control::set_owner(::pointer<::user::interaction>window)
   {

//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); send_message( TB_SETPARENT, (WPARAM)pwindow.m_p);
//
//#else
//
//      throw ::exception(todo);
//
//#endif
      //return pwindow;

      return nullptr;

   }


   void toolbar_control::SetRows(i32 nRows, bool bLarger, RECTANGLE_I32 * prectangle)

   {

//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); send_message( TB_SETROWS, MAKELPARAM(nRows, bLarger), (LPARAM)prectangle);
//
//
//#else
//
//      throw ::exception(todo);
//
//#endif

   }


   i32 toolbar_control::GetRows()
   {

      return 0;

//
//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); return (i32) send_message( TB_GETROWS);
//
//#else
//
//      throw ::exception(todo);
//
//#endif

   }


   bool toolbar_control::SetCmdID(i32 nIndex, ::u32 nID)
   {

//#ifdef WINDOWS_DESKTOP
//
//      ASSERT(is_window()); return send_message(TB_SETCMDID, nIndex, (lparam) nID) != false;
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return false;

   }


   ::u32 toolbar_control::GetBitmapFlags()
   {

//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); return (::u32) send_message( TB_GETBITMAPFLAGS);
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return 0;

   }


   i32 toolbar_control::hit_test(POINT_I32 * ppt)
   {

//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); return (i32) send_message( TB_HITTEST, 0, (LPARAM)ppt);
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return -1;

   }


   u32 toolbar_control::GetExtendedStyle()
   {

//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); return (u32) send_message( TB_GETEXTENDEDSTYLE);
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return 0;

   }


   u32 toolbar_control::SetExtendedStyle(u32 dwExStyle)
   {

//#ifdef WINDOWS_DESKTOP
//
//      ASSERT(is_window()); return (u32) send_message( TB_SETEXTENDEDSTYLE, 0, (LPARAM) dwExStyle);
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return 0;


   }


   ::color::color toolbar_control::GetInsertMarkColor()
   {

//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); return (::color::color) send_message( TB_GETINSERTMARKCOLOR);
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return 0;

   }


   ::color::color toolbar_control::SetInsertMarkColor(::color::color clrNew)
   {

//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); return (::color::color) send_message( TB_SETINSERTMARKCOLOR, 0, (LPARAM) clrNew);
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return 0;

   }

   /////////////////////////////////////////////////////////////////////////////

   u32 toolbar_control::get_button_size()
   {

//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); return (u32) send_message( TB_GETBUTTONSIZE);
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return 0;

   }


   ::image_list* toolbar_control::GetDisabledImageList()
   {

//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); return nullptr;
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return 0;

   }


   ::image_list* toolbar_control::GetHotImageList()
   {

//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); return nullptr;
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return 0;

   }


   ::image_list* toolbar_control::GetImageList()
   {

//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); return nullptr;
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return nullptr;

   }


   u32 toolbar_control::GetStyle()
   {

//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); return (u32) send_message( TB_GETSTYLE);
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return 0;

   }


   ::i32 toolbar_control::GetMaxTextRows()
   {

//#ifdef WINDOWS_DESKTOP
//
//      ASSERT(is_window()); 
//      
//      return (::i32) send_message(TB_GETTEXTROWS);
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return 0;

   }


   bool toolbar_control::GetRect(i32 nID, RECTANGLE_I32 * prectangle)

   {

//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); return send_message( TB_GETRECT, nID, (LPARAM)prectangle) != false;
//
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return 0;

   }


   bool toolbar_control::IsButtonHighlighted(i32 nID)
   {

//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); return send_message( TB_ISBUTTONHIGHLIGHTED, nID) != false;
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return 0;

   }


//#ifdef WINDOWS_DESKTOP
//
//
//   void toolbar_control::LoadImages(i32 iBitmapID, HINSTANCE hinst)
//   {
//
//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); send_message( TB_LOADIMAGES, iBitmapID, (LPARAM)hinst);
//
//#else
//
//      throw ::exception(todo);
//
//#endif
//
//   }
//
//
//#endif


   bool toolbar_control::SetButtonWidth(i32 cxMin, i32 cxMax)
   {

//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); return send_message( TB_SETBUTTONWIDTH, 0, MAKELPARAM(cxMin, cxMax)) != false;
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return 0;

   }


   ::image_list* toolbar_control::SetDisabledImageList(::image_list* pImageList)
   {
//      __UNREFERENCED_PARAMETER(pImageList);
//#ifdef WINDOWS_DESKTOP
//
//      ASSERT(is_window());
//      return nullptr;
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return nullptr;

   }


   ::image_list* toolbar_control::SetHotImageList(::image_list* pImageList)
   {
//      __UNREFERENCED_PARAMETER(pImageList);
//#ifdef WINDOWS_DESKTOP
//
//      ASSERT(is_window());
//      return nullptr;
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return nullptr;

   }


   ::image_list* toolbar_control::SetImageList(::image_list* pImageList)
   {

//      __UNREFERENCED_PARAMETER(pImageList);
//
//#ifdef WINDOWS_DESKTOP
//
//      ASSERT(is_window());
//      return nullptr;
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return nullptr;

   }


   bool toolbar_control::SetIndent(i32 iIndent)
   {
//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); return send_message( TB_SETINDENT, iIndent) != false;
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return false;

   }


   bool toolbar_control::SetMaxTextRows(i32 iMaxRows)
   {
//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); return send_message( TB_SETMAXTEXTROWS, iMaxRows) != false;
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return false;

   }


   void toolbar_control::SetStyle(u32 dwStyle)
   {
//#ifdef WINDOWS_DESKTOP
//
//      ASSERT(is_window()); send_message( TB_SETSTYLE, 0, (LPARAM) dwStyle);
//
//#else
//
//      throw ::exception(todo);
//
//#endif

   }

//#ifdef WINDOWS_DESKTOP
//
//   bool toolbar_control::GetButtonInfo(i32 nID, TBBUTTONINFO* ptbbi)
//   {
//
//      ASSERT(is_window()); return send_message( TB_GETBUTTONINFO, nID, (LPARAM)ptbbi) != false;
//
//   }
//
//#endif
//

//#ifdef WINDOWS_DESKTOP
//
//   bool toolbar_control::GetButtonInfo(i32 nID, TBBUTTONINFOW* ptbbi)
//   {
//
//      ASSERT(is_window()); return send_message( TB_GETBUTTONINFOW, nID, (LPARAM)ptbbi) != false;
//
//   }
//
//#endif


//#ifdef WINDOWS_DESKTOP
//
//   bool toolbar_control::SetButtonInfo(i32 nID, TBBUTTONINFO* ptbbi)
//   {
//
//      ASSERT(is_window()); return send_message( TB_SETBUTTONINFO, nID, (LPARAM)ptbbi) != false;
//
//   }
//
//#endif


//#ifdef WINDOWS_DESKTOP
//
//   bool toolbar_control::SetButtonInfo(i32 nID, TBBUTTONINFOW* ptbbi)
//   {
//
//      ASSERT(is_window()); return send_message( TB_SETBUTTONINFOW, nID, (LPARAM)ptbbi) != false;
//
//
//   }
//
//#endif


   u32 toolbar_control::SetDrawTextFlags(u32 dwMask, u32 dwDTFlags)
   {

//#ifdef WINDOWS_DESKTOP
//
//      ASSERT(is_window()); return (u32) send_message( TB_SETDRAWTEXTFLAGS, dwMask, (LPARAM) dwDTFlags);
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return 0;

   }


   bool toolbar_control::GetAnchorHighlight()
   {
//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); return send_message( TB_GETANCHORHIGHLIGHT) != false;
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return false;

   }


   bool toolbar_control::SetAnchorHighlight(bool fAnchor)
   {
//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); return send_message( TB_SETANCHORHIGHLIGHT, fAnchor) != false;
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return false;

   }


   i32 toolbar_control::GetHotItem()
   {
//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); return (i32) send_message( TB_GETHOTITEM);
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return false;

   }


   i32 toolbar_control::SetHotItem(i32 nHot)
   {
//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); return (i32) send_message( TB_SETHOTITEM, nHot);
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return -1;

   }


//#ifdef WINDOWS_DESKTOP
//
//   void toolbar_control::GetInsertMark(TBINSERTMARK* ptbim)
//   {
//
//
//      ASSERT(is_window());
//
//      send_message( TB_GETINSERTMARK, 0, (LPARAM)ptbim);
//
//   }
//
//
//   void toolbar_control::SetInsertMark(TBINSERTMARK* ptbim)
//   {
//
//      ASSERT(is_window());
//
//      send_message( TB_SETINSERTMARK, 0, (LPARAM)ptbim);
//
//   }
//
//
//#endif


   bool toolbar_control::GetMaxSize(::SIZE_I32 * pSize)
   {
//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); return send_message( TB_GETMAXSIZE, 0, (LPARAM)pSize) != false;
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return false;

   }


//#ifdef WINDOWS_DESKTOP
//
//   bool toolbar_control::InsertMarkHitTest(POINT_I32 * ppt, LPTBINSERTMARK ptbim)
//   {
//
//   ASSERT(is_window()); return send_message( TB_INSERTMARKHITTEST, (WPARAM)ppt, (LPARAM)ptbim) != false;
//
//   }
//
//#endif


   bool toolbar_control::MapAccelerator(char chAccel, ::u32* pIDBtn)
   {
//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); return send_message( TB_MAPACCELERATOR, (WPARAM)chAccel, (LPARAM)pIDBtn) != false;
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return false;

   }


   bool toolbar_control::MarkButton(i32 nID, bool bHighlight)
   {
//#ifdef WINDOWS_DESKTOP
//
//   ASSERT(is_window()); return send_message( TB_MARKBUTTON, nID, MAKELPARAM(bHighlight, 0)) != false;
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return false;

   }


   bool toolbar_control::MoveButton(::u32 nOldPos, ::u32 nNewPos)
   {

//#ifdef WINDOWS_DESKTOP
//
//      ASSERT(is_window()); return send_message( TB_MOVEBUTTON, nOldPos, (LPARAM) nNewPos) != false;
//
//#else
//
//      throw ::exception(todo);
//
//#endif

      return false;

   }


} // namespace user



