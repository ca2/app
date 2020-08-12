#pragma once



namespace user
{

#ifdef WINDOWS_DESKTOP

   struct CLASS_DECL_AURA TRAYDATA
   {
      HWND    m_oswindow;
      UINT        uID;
      UINT        uCallbackMessage;
      u32       Reserved[2];
      HICON       hIcon;
   };


   struct CLASS_DECL_AURA TrayItemInfo :
      virtual public object
   {
      oswindow    m_oswindow;
      UINT        uID;
      UINT        uCallbackMessage;
      string      sTip;
      string      sProcessPath;
      bool        bVisible;
   };

#endif

   CLASS_DECL_AURA char GetDriveLetter(const char * pDevicePath);

   CLASS_DECL_AURA oswindow FindTrayToolbarWindow();


   class CLASS_DECL_AURA notification_area :
      virtual public ::object
   {
   public:


      oswindow             m_oswindowTray;
      __pointer(image_list)         m_pil16;
#ifdef WINDOWS_DESKTOP
      __pointer_array(TrayItemInfo)    m_infoa;
#endif
      HFONT                m_hfontHidden;
      HFONT                m_hfontRegular;


      notification_area();
      virtual ~notification_area();

      virtual void Initialize(::object * pobject);

      void ListTrayIcons(i32 defindex = 0);
      void EditCopy(i32 iItem);
      void DoubleClick(i32 iItem);
      void RightClick(i32 iItem);
      void LeftClick(i32 iItem);
      void MoveLeft(i32 iItem);
      void MoveRight(i32 iItem);
      void Refresh();
      void PostMessageToTrayIcon(i32 iItem, LPARAM lParam);


   };


} // namespace user




