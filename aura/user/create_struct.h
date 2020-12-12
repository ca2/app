#pragma once


namespace user
{


   class CLASS_DECL_AURA create_struct :
      virtual public ::matter
   {
   public:

#ifdef WINDOWS
      CREATESTRUCTW        m_createstruct;
#else
      CREATESTRUCTA        m_createstruct;
#endif


#ifdef WINDOWS
      wstring     m_strClassName;
      wstring     m_strWindowName;
#else
      string      m_strClassName;
      string      m_strWindowName;
#endif

      ::user::interaction *                  m_puserinteractionOwner;
      ::promise::routine                     m_routineSuccess;
      ::promise::routine                     m_routineFailure;
      __pointer(::user::interaction_impl)    m_pimpl;
      __pointer(::create)                    m_pcreate;


      create_struct(const create_struct &);
      
      create_struct(
                  u32 uiExStyle = 0,
                  const char * pszClassName = 0,
                  const char * pszWindowName = 0,
                  u32 uStyle = 0,
                  ::rect rect = nullptr,
                  ::create * pcreate = nullptr);

      create_struct(const ::rect & rect);
      
      void set_class_name(const char * pszClassName);
      
      void set_window_name(const char * pszWindowName);

      void set_rect(const ::rect & rect);

      void get_rect(RECT32 * prect);

      void add_visible(bool bAdd = true);

      inline auto get_rect() { ::rect rect(no_init); get_rect(&rect); return rect; }

   };


} // namespace user


