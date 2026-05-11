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

      //bool LoadToolBar(const ::scoped_string & scopedstrResourceName);

      //bool LoadToolBar(::u32 nIDResource);
      bool SetButtons(const ::u32* pIDArray, int nIDCount);




      //using ::user::interaction::create_window;
      //bool create_window(::u32 uStyle, const ::i32_rectangle & rectangle, ::user::interaction * puiParent, ::atom atom);
      //bool create_child(::user::interaction * puserinteraction);


      bool IsButtonEnabled(int nID);
      bool IsButtonChecked(int nID);
      bool IsButtonPressed(int nID);
      bool IsButtonHidden(int nID);
      bool IsButtonIndeterminate(int nID);
      bool set_state(int nID, ::u32 nState);
      int GetState(int nID);
//#ifdef WINDOWS_DESKTOP
//      bool GetButton(int nIndex, LPTBBUTTON pButton);
//
//#endif
      int GetButtonCount();
      bool GetItemRect(int nIndex, ::i32_rectangle * prectangle);

      bool GetRect(int nID, ::i32_rectangle * prectangle);

      void SetButtonStructSize(int nSize);
      ::u32 get_button_size();
      bool SetButtonSize(const ::i32_size & size);
      bool SetBitmapSize(const ::i32_size & size);
      ::pointer<::user::interaction> set_owner(::pointer<::user::interaction>window);
      void SetRows(int nRows, bool bLarger, ::i32_rectangle * prectangle);

      int GetRows();
      bool SetCmdID(int nIndex, ::u32 nID);
      ::u32 GetBitmapFlags();
      ::image::image_list* GetDisabledImageList();
      ::image::image_list* GetHotImageList();
      ::image::image_list* GetImageList();
      ::u32 GetStyle();
      int GetMaxTextRows();
      bool IsButtonHighlighted(int nID);
      bool SetButtonWidth(int cxMin, int cxMax);
      ::image::image_list* SetDisabledImageList(::image::image_list* pImageList);
      ::image::image_list* SetHotImageList(::image::image_list* pImageList);
      ::image::image_list* SetImageList(::image::image_list* pImageList);


//#ifdef WINDOWS_DESKTOP
//      HRESULT GetDropTarget(IDropTarget** ppDropTarget);
//#endif


      bool SetIndent(int iIndent);
      bool SetMaxTextRows(int iMaxRows);
      void SetStyle(::u32 dwStyle);


//#ifdef WINDOWS_DESKTOP
//      bool GetButtonInfo(int nID, TBBUTTONINFOW* ptbbi);
//      bool SetButtonInfo(int nID, TBBUTTONINFOW* ptbbi);
//#endif


      ::u32 SetDrawTextFlags(::u32 dwMask, ::u32 dwDTFlags);
      bool GetAnchorHighlight();
      bool SetAnchorHighlight(bool fAnchor = true);
      int GetHotItem();
      int SetHotItem(int nHot);
//#ifdef WINDOWS_DESKTOP
//      void GetInsertMark(TBINSERTMARK* ptbim);
//      void SetInsertMark(TBINSERTMARK* ptbim);
//#endif
      bool GetMaxSize(::i32_size * pSize);
//#ifdef WINDOWS_DESKTOP
//      bool InsertMarkHitTest(::i32_point * ppt, LPTBINSERTMARK ptbim);
//#endif
      ::u32 GetExtendedStyle();
      ::u32 SetExtendedStyle(::u32 dwExStyle);
      ::color::color GetInsertMarkColor();
      ::color::color SetInsertMarkColor(::color::color clrNew);

   
   public:
      bool EnableButton(int nID, bool bEnable = true);
      bool CheckButton(int nID, bool bCheck = true);
      bool PressButton(int nID, bool bPress = true);
      bool HideButton(int nID, bool bHide = true);
      bool Indeterminate(int nID, bool bIndeterminate = true);
      //int AddBitmap(int nNumButtons, ::draw2d::bitmap* pBitmap);


//#ifdef WINDOWS_DESKTOP
//
//      bool AddButtons(int nNumButtons, LPTBBUTTON pButtons);
//
//      bool InsertButton(int nIndex, LPTBBUTTON pButton);
//
//#endif
//

      bool DeleteButton(int nIndex);
      ::u32 CommandToIndex(::u32 nID);


//#ifdef WINDOWS_DESKTOP
//
//      void SaveState(HKEY hKeyRoot, const ::scoped_string & scopedstrSubKey, const ::scoped_string & scopedstrValueName);
//      void RestoreState(HKEY hKeyRoot, const ::scoped_string & scopedstrSubKey, const ::scoped_string & scopedstrValueName);
//      void LoadImages(int iBitmapID, HINSTANCE hinst);
//
//#endif


      bool MapAccelerator(char chAccel, ::u32* pIDBtn);
      bool MarkButton(int nID, bool fHighlight = true);
      bool MoveButton(::u32 nOldPos, ::u32 nNewPos);
      int hit_test(::i32_point * ppt);

      void Customize();
      int AddStrings(const ::scoped_string & scopedstrStrings);

      void AutoSize();

      int GetButtonText(::u32 uID, string &str);
      virtual ~toolbar_control();

      DECLARE_MESSAGE_HANDLER(on_message_create);

   };


} // namespace user


