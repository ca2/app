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

      //bool LoadToolBar(::u32 nIDResource);
      bool SetButtons(const ::u32* pIDArray, i32 nIDCount);




      using ::user::interaction::create_window;
      bool create_window(u32 uStyle, const ::rect & rect, ::user::interaction * puiParent, ::id id);


      bool IsButtonEnabled(i32 nID);
      bool IsButtonChecked(i32 nID);
      bool IsButtonPressed(i32 nID);
      bool IsButtonHidden(i32 nID);
      bool IsButtonIndeterminate(i32 nID);
      bool set_state(i32 nID, ::u32 nState);
      i32 GetState(i32 nID);
#ifdef WINDOWS_DESKTOP
      bool GetButton(i32 nIndex, LPTBBUTTON pButton);

#endif
      i32 GetButtonCount();
      bool GetItemRect(i32 nIndex, RECT32 * prect);

      bool GetRect(i32 nID, RECT32 * prect);

      void SetButtonStructSize(i32 nSize);
      u32 get_button_size();
      bool SetButtonSize(const ::size & size);
      bool SetBitmapSize(const ::size & size);
      __pointer(::user::interaction)  set_owner(__pointer(::user::interaction) pwindow);
      void SetRows(i32 nRows, bool bLarger, RECT32 * prect);

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


#ifdef WINDOWS_DESKTOP
      HRESULT GetDropTarget(IDropTarget** ppDropTarget);
#endif


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
      bool GetMaxSize(LPSIZE32 pSize);
#ifdef WINDOWS_DESKTOP
      bool InsertMarkHitTest(POINT32 * ppt, LPTBINSERTMARK ptbim);
#endif
      u32 GetExtendedStyle();
      u32 SetExtendedStyle(u32 dwExStyle);
      color32_t GetInsertMarkColor();
      color32_t SetInsertMarkColor(color32_t clrNew);

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
      ::u32 CommandToIndex(::u32 nID);


#ifdef WINDOWS_DESKTOP

      void SaveState(HKEY hKeyRoot, const char * pszSubKey, const char * pszValueName);
      void RestoreState(HKEY hKeyRoot, const char * pszSubKey, const char * pszValueName);
      void LoadImages(i32 iBitmapID, HINSTANCE hinst);

#endif


      bool MapAccelerator(char chAccel, ::u32* pIDBtn);
      bool MarkButton(i32 nID, bool fHighlight = TRUE);
      bool MoveButton(::u32 nOldPos, ::u32 nNewPos);
      i32 hit_test(POINT32 * ppt);

      void Customize();
      i32 AddStrings(const char * pszStrings);

      void AutoSize();

      i32 GetButtonText(::u32 uID, string &str);
      virtual ~toolbar_control();

      DECL_GEN_SIGNAL(_001OnCreate);

   };


} // namespace user


