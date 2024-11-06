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

      //bool LoadToolBar(unsigned int nIDResource);
      bool SetButtons(const unsigned int* pIDArray, int nIDCount);




      //using ::user::interaction::create_window;
      //bool create_window(unsigned int uStyle, const ::int_rectangle & rectangle, ::user::interaction * puiParent, ::atom atom);
      //bool create_child(::user::interaction * puserinteraction);


      bool IsButtonEnabled(int nID);
      bool IsButtonChecked(int nID);
      bool IsButtonPressed(int nID);
      bool IsButtonHidden(int nID);
      bool IsButtonIndeterminate(int nID);
      bool set_state(int nID, unsigned int nState);
      int GetState(int nID);
//#ifdef WINDOWS_DESKTOP
//      bool GetButton(int nIndex, LPTBBUTTON pButton);
//
//#endif
      int GetButtonCount();
      bool GetItemRect(int nIndex, ::int_rectangle * prectangle);

      bool GetRect(int nID, ::int_rectangle * prectangle);

      void SetButtonStructSize(int nSize);
      unsigned int get_button_size();
      bool SetButtonSize(const ::int_size & size);
      bool SetBitmapSize(const ::int_size & size);
      ::pointer<::user::interaction> set_owner(::pointer<::user::interaction>window);
      void SetRows(int nRows, bool bLarger, ::int_rectangle * prectangle);

      int GetRows();
      bool SetCmdID(int nIndex, unsigned int nID);
      unsigned int GetBitmapFlags();
      ::image::image_list* GetDisabledImageList();
      ::image::image_list* GetHotImageList();
      ::image::image_list* GetImageList();
      unsigned int GetStyle();
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
      void SetStyle(unsigned int dwStyle);


//#ifdef WINDOWS_DESKTOP
//      bool GetButtonInfo(int nID, TBBUTTONINFOW* ptbbi);
//      bool SetButtonInfo(int nID, TBBUTTONINFOW* ptbbi);
//#endif


      unsigned int SetDrawTextFlags(unsigned int dwMask, unsigned int dwDTFlags);
      bool GetAnchorHighlight();
      bool SetAnchorHighlight(bool fAnchor = true);
      int GetHotItem();
      int SetHotItem(int nHot);
//#ifdef WINDOWS_DESKTOP
//      void GetInsertMark(TBINSERTMARK* ptbim);
//      void SetInsertMark(TBINSERTMARK* ptbim);
//#endif
      bool GetMaxSize(::int_size * pSize);
//#ifdef WINDOWS_DESKTOP
//      bool InsertMarkHitTest(::int_point * ppt, LPTBINSERTMARK ptbim);
//#endif
      unsigned int GetExtendedStyle();
      unsigned int SetExtendedStyle(unsigned int dwExStyle);
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
      unsigned int CommandToIndex(unsigned int nID);


//#ifdef WINDOWS_DESKTOP
//
//      void SaveState(HKEY hKeyRoot, const ::string & pszSubKey, const ::string & pszValueName);
//      void RestoreState(HKEY hKeyRoot, const ::string & pszSubKey, const ::string & pszValueName);
//      void LoadImages(int iBitmapID, HINSTANCE hinst);
//
//#endif


      bool MapAccelerator(char chAccel, unsigned int* pIDBtn);
      bool MarkButton(int nID, bool fHighlight = true);
      bool MoveButton(unsigned int nOldPos, unsigned int nNewPos);
      int hit_test(::int_point * ppt);

      void Customize();
      int AddStrings(const ::string & pszStrings);

      void AutoSize();

      int GetButtonText(unsigned int uID, string &str);
      virtual ~toolbar_control();

      DECLARE_MESSAGE_HANDLER(on_message_create);

   };


} // namespace user


