#pragma once


namespace user
{


   class CLASS_DECL_AURA create_struct :
#ifdef WINDOWS
      public CREATESTRUCTW
#else
      public CREATESTRUCTA
#endif
   {
   public:

#ifdef WINDOWS
      wstring     m_strClassName;
      wstring     m_strWindowName;
#else
      string      m_strClassName;
      string      m_strWindowName;
#endif
      ::user::interaction * m_puserinteractionOwner;

      create_struct(const create_struct &);
      
      create_struct(
                  u32 uiExStyle = 0,
                  const char * pszClassName = 0,
                  const char * pszWindowName = 0,
                  u32 uStyle = 0,
                  ::rect rect = nullptr,
                  void * pvCreateParams = nullptr);

      create_struct(const ::rect & rect);
      
      void set_class_name(const char * pszClassName);
      
      void set_window_name(const char * pszWindowName);

      void set_rect(const ::rect & rect);

      void get_rect(RECT32 * prect);

      void add_visible(bool bAdd = true);

      inline auto get_rect() { ::rect rect(no_init); get_rect(&rect); return rect; }

   };


} // namespace user


