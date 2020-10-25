#pragma once


struct IDropTarget; // forward declaration


namespace user
{


   class CLASS_DECL_CORE toolbar_control :
      public ::user::interaction
   {
   public:


      toolbar_control();

      //bool LoadToolBar(const char * pszResourceName);

      //bool LoadToolBar(UINT nIDResource);
      bool SetButtons(const UINT* pIDArray, i32 nIDCount);




      using ::user::interaction::create_window;
      bool create_window(u32 uStyle, const ::rect & rect, ::user::interaction * puiParent, ::id id);


      bool IsButtonEnabled(i32 nID);
      bool IsButtonChecked(i32 nID);
      bool IsButtonPressed(i32 nID);
      bool IsButtonHidden(i32 nID);
      bool IsButtonIndeterminate(i32 nID);
      bool set_state(i32 nID, UINT nState);
      i32 GetState(i32 nID);
#ifdef WINDOWS_DESKTOP
      bool GetButton(i32 nIndex, LPTBBUTTON pButton);

#endif
      i32 GetButtonCount();
      bool GetItemRect(i32 nIndex, RECT * prect);

      bool GetRect(i32 nID, RECT * prect);

      void SetButtonStructSize(i32 nSize);
      u32 get_button_size();
      bool SetButtonSize(const ::size & size);
      bool SetBitmapSize(const ::size & size);
      __pointer(::user::interaction)  SetOwner(__pointer(::user::interaction) pwindow);
      void SetRows(i32 nRows, bool bLarger, RECT * prect);

      i32 GetRows();
      bool SetCmdID(i32 nIndex, UINT nID);
      UINT GetBitmapFlags();
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
      HRESULT GetDropTarget(IDropTarget** ppDropTarget);
      bool SetIndent(i32 iIndent);
      bool SetMaxTextRows(i32 iMaxRows);
      void SetStyle(u32 dwStyle);
#ifdef WINDOWS_DESKTOP
      bool GetButtonInfo(i32 nID, TBBUTTONINFOW* ptbbi);
      bool SetButtonInfo(i32 nID, TBBUTTONINFOW* ptbbi);
#endif
      u32 SetDrawTextFlags(u32 dwMask, u32 dwDTFlags);
      bool GetAnchorHighlight();
      bool SetAnchorHighlight(bool fAnchor = TRUE);
      i32 GetHotItem();
      i32 SetHotItem(i32 nHot);
#ifdef WINDOWS_DESKTOP
      void GetInsertMark(TBINSERTMARK* ptbim);
      void SetInsertMark(TBINSERTMARK* ptbim);
#endif
      bool GetMaxSize(LPSIZE pSize);
#ifdef WINDOWS_DESKTOP
      bool InsertMarkHitTest(LPPOINT ppt, LPTBINSERTMARK ptbim);
#endif
      u32 GetExtendedStyle();
      u32 SetExtendedStyle(u32 dwExStyle);
      COLORREF GetInsertMarkColor();
      COLORREF SetInsertMarkColor(COLORREF clrNew);

   // Operations
   public:
      bool EnableButton(i32 nID, bool bEnable = TRUE);
      bool CheckButton(i32 nID, bool bCheck = TRUE);
      bool PressButton(i32 nID, bool bPress = TRUE);
      bool HideButton(i32 nID, bool bHide = TRUE);
      bool Indeterminate(i32 nID, bool bIndeterminate = TRUE);
      i32 AddBitmap(i32 nNumButtons, ::draw2d::bitmap* pBitmap);
#ifdef WINDOWS_DESKTOP
      bool AddButtons(i32 nNumButtons, LPTBBUTTON pButtons);

      bool InsertButton(i32 nIndex, LPTBBUTTON pButton);

#endif
      bool DeleteButton(i32 nIndex);
      UINT CommandToIndex(UINT nID);
#ifdef WINDOWS_DESKTOP
      void SaveState(HKEY hKeyRoot, const char * pszSubKey, const char * pszValueName);

      void RestoreState(HKEY hKeyRoot, const char * pszSubKey, const char * pszValueName);

#endif
      void LoadImages(i32 iBitmapID, HINSTANCE hinst);
      bool MapAccelerator(char chAccel, UINT* pIDBtn);
      bool MarkButton(i32 nID, bool fHighlight = TRUE);
      bool MoveButton(UINT nOldPos, UINT nNewPos);
      i32 hit_test(LPPOINT ppt);

      void Customize();
      i32 AddStrings(const char * pszStrings);

      void AutoSize();

      i32 GetButtonText(UINT uiID, string &str);
      virtual ~toolbar_control();

      DECL_GEN_SIGNAL(_001OnCreate);

   };


} // namespace user


