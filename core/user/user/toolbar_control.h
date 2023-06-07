#pragma once


#include "aura/user/user/interaction.h"


struct IDropTarget; // forward declaration


namespace user
{


   class CLASS_DECL_CORE toolbar_control :
      public ::user::interaction
   {
   public:


      toolbar_control();

      //bool LoadToolBar(const ::string & pszResourceName);

      //bool LoadToolBar(::u32 nIDResource);
      bool SetButtons(const ::u32* pIDArray, i32 nIDCount);




      //using ::user::interaction::create_window;
      //bool create_window(u32 uStyle, const ::rectangle_i32 & rectangle, ::user::interaction * puiParent, ::atom atom);
      //bool create_child(::user::interaction * puserinteraction);


      bool IsButtonEnabled(i32 nID);
      bool IsButtonChecked(i32 nID);
      bool IsButtonPressed(i32 nID);
      bool IsButtonHidden(i32 nID);
      bool IsButtonIndeterminate(i32 nID);
      bool set_state(i32 nID, ::u32 nState);
      i32 GetState(i32 nID);
//#ifdef WINDOWS_DESKTOP
//      bool GetButton(i32 nIndex, LPTBBUTTON pButton);
//
//#endif
      i32 GetButtonCount();
      bool GetItemRect(i32 nIndex, ::rectangle_i32 * prectangle);

      bool GetRect(i32 nID, ::rectangle_i32 * prectangle);

      void SetButtonStructSize(i32 nSize);
      u32 get_button_size();
      bool SetButtonSize(const ::size_i32 & size);
      bool SetBitmapSize(const ::size_i32 & size);
      ::pointer<::user::interaction> set_owner(::pointer<::user::interaction>window);
      void SetRows(i32 nRows, bool bLarger, ::rectangle_i32 * prectangle);

      i32 GetRows();
      bool SetCmdID(i32 nIndex, ::u32 nID);
      ::u32 GetBitmapFlags();
      ::image_list* GetDisabledImageList();
      ::image_list* GetHotImageList();
      ::image_list* GetImageList();
      u32 GetStyle();
      i32 GetMaxTextRows();
      bool IsButtonHighlighted(i32 nID);
      bool SetButtonWidth(i32 cxMin, i32 cxMax);
      ::image_list* SetDisabledImageList(::image_list* pImageList);
      ::image_list* SetHotImageList(::image_list* pImageList);
      ::image_list* SetImageList(::image_list* pImageList);


//#ifdef WINDOWS_DESKTOP
//      HRESULT GetDropTarget(IDropTarget** ppDropTarget);
//#endif


      bool SetIndent(i32 iIndent);
      bool SetMaxTextRows(i32 iMaxRows);
      void SetStyle(u32 dwStyle);


//#ifdef WINDOWS_DESKTOP
//      bool GetButtonInfo(i32 nID, TBBUTTONINFOW* ptbbi);
//      bool SetButtonInfo(i32 nID, TBBUTTONINFOW* ptbbi);
//#endif


      u32 SetDrawTextFlags(u32 dwMask, u32 dwDTFlags);
      bool GetAnchorHighlight();
      bool SetAnchorHighlight(bool fAnchor = true);
      i32 GetHotItem();
      i32 SetHotItem(i32 nHot);
//#ifdef WINDOWS_DESKTOP
//      void GetInsertMark(TBINSERTMARK* ptbim);
//      void SetInsertMark(TBINSERTMARK* ptbim);
//#endif
      bool GetMaxSize(::size_i32 * pSize);
//#ifdef WINDOWS_DESKTOP
//      bool InsertMarkHitTest(::point_i32 * ppt, LPTBINSERTMARK ptbim);
//#endif
      u32 GetExtendedStyle();
      u32 SetExtendedStyle(u32 dwExStyle);
      ::color::color GetInsertMarkColor();
      ::color::color SetInsertMarkColor(::color::color clrNew);

   
   public:
      bool EnableButton(i32 nID, bool bEnable = true);
      bool CheckButton(i32 nID, bool bCheck = true);
      bool PressButton(i32 nID, bool bPress = true);
      bool HideButton(i32 nID, bool bHide = true);
      bool Indeterminate(i32 nID, bool bIndeterminate = true);
      //i32 AddBitmap(i32 nNumButtons, ::draw2d::bitmap* pBitmap);


//#ifdef WINDOWS_DESKTOP
//
//      bool AddButtons(i32 nNumButtons, LPTBBUTTON pButtons);
//
//      bool InsertButton(i32 nIndex, LPTBBUTTON pButton);
//
//#endif
//

      bool DeleteButton(i32 nIndex);
      ::u32 CommandToIndex(::u32 nID);


//#ifdef WINDOWS_DESKTOP
//
//      void SaveState(HKEY hKeyRoot, const ::string & pszSubKey, const ::string & pszValueName);
//      void RestoreState(HKEY hKeyRoot, const ::string & pszSubKey, const ::string & pszValueName);
//      void LoadImages(i32 iBitmapID, HINSTANCE hinst);
//
//#endif


      bool MapAccelerator(char chAccel, ::u32* pIDBtn);
      bool MarkButton(i32 nID, bool fHighlight = true);
      bool MoveButton(::u32 nOldPos, ::u32 nNewPos);
      i32 hit_test(::point_i32 * ppt);

      void Customize();
      i32 AddStrings(const ::string & pszStrings);

      void AutoSize();

      i32 GetButtonText(::u32 uID, string &str);
      virtual ~toolbar_control();

      DECLARE_MESSAGE_HANDLER(on_message_create);

   };


} // namespace user


