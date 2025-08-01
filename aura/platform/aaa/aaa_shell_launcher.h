#pragma once


namespace aura
{


#ifndef UNIVERSAL_WINDOWS


   // created near revision 4405
   // this type information can be used with the information that the class below is replacing Shell Execute calls from windows original implementations,
   // to detect erronous adaptations of replacement


   class CLASS_DECL_AURA shell_launcher
   {
   public:


      oswindow          m_oswindow;
      string            m_strOperation;
      string            m_strFile;
      string            m_strParameters;
      string            m_strDirectory;
      ::e_display        m_edisplay;
      ::user::e_activation     XXXXm_eactivation;
      duration          m_durationTimeout;

#ifdef WINDOWS

      HINSTANCE   m_h;
      HINSTANCE   m_hinstApp;       // out when SEE_MASK_NOCLOSEPROCESS is specified
      ULONG       m_fMask;          // in, SEE_MASK_XXX values
      void *      m_lpIDList;       // in, valid when SEE_MASK_IDLIST is specified, PCIDLIST_ABSOLUTE, for use with SEE_MASK_IDLIST & SEE_MASK_INVOKEIDLIST
      const char *      m_vssClass;       // in, valid when SEE_MASK_CLASSNAME is specified
      HKEY        m_hkeyClass;      // in, valid when SEE_MASK_CLASSKEY is specified
      unsigned int       m_dwHotKey;       // in, valid when SEE_MASK_HOTKEY is specified
      union
      {
         HANDLE   m_hIcon;          // not used
         HANDLE   n_hMonitor;
      };
      HANDLE      m_hProcess;       // out, valid when SEE_MASK_NOCLOSEPROCESS specified

#else

      bool        m_bOk;
      int         m_dwResult;
      int         m_pid;

#endif

   protected:


      int         m_iMode;


   public:


      shell_launcher(duration durationTimeout = ::one_minute());
      shell_launcher(oswindow oswindow, const ::scoped_string & scopedstrOperation, const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParameters, const ::scoped_string & scopedstrDirectory, ::e_display edisplay, duration durationTimeout = ::one_minute());


      void execute();


      bool succeeded();


   };


#endif


} // namespace aura



