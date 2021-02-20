#pragma once


namespace windows
{


   class CLASS_DECL_APEX shell_launcher :
      virtual public ::apex::shell_launcher
   {
   public:

      HWND              m_hwnd;
      HINSTANCE         m_hinstance;
      HINSTANCE         m_hinstanceApp;   // out when SEE_MASK_NOCLOSEPROCESS is specified
      ULONG             m_fMask;          // in, SEE_MASK_XXX values
      void *            m_lpIDList;       // in, valid when SEE_MASK_IDLIST is specified, PCIDLIST_ABSOLUTE, for use with SEE_MASK_IDLIST & SEE_MASK_INVOKEIDLIST
      const char *      m_vssClass;       // in, valid when SEE_MASK_CLASSNAME is specified
      HKEY              m_hkeyClass;      // in, valid when SEE_MASK_CLASSKEY is specified
      u32               m_dwHotKey;       // in, valid when SEE_MASK_HOTKEY is specified
      union
      {
         HANDLE         m_hIcon;          // not used
         HANDLE         n_hMonitor;
      };
      HANDLE            m_hProcess;       // out, valid when SEE_MASK_NOCLOSEPROCESS specified


      shell_launcher();
      virtual ~shell_launcher();


      virtual ::e_status launch() override;


      //virtual ::e_status status() const override;


   };


} // namespace apex



