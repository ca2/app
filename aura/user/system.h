#pragma once


namespace user
{


   class CLASS_DECL_AURA system :
      virtual public ::context_object
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





      bool                             m_bAutoWindowFrame;
      bool                             m_bWindowFrame;
      ::type                           m_typeNewView;
      //::user::document *             m_pdocumentCurrent;
      ::object * m_pdocumentCurrent;
      ::user::primitive * m_puiNew;

      // multiple document interface children
      //::user::impact_system *          m_ptemplateNewDocument;
      ::object * m_ptemplateNewDocument;

      // original view/frame
      ::user::primitive * m_puiLastView;
      ::user::primitive * m_puiCurrentFrame;
      //__pointer(impact_data)         m_pimpactdata;
      __pointer(::matter)              m_pimpactdata;


      //create();
      //virtual ~create();




      system(const system &);
      
      system(
                  u32 uExStyle = 0,
                  const char * pszClassName = 0,
                  const char * pszWindowName = 0,
                  u32 uStyle = 0,
                  ::rect rect = nullptr,
                  ::create * pcreate = nullptr);

      system(
         const ::rect & rect,
         ::u32 uExStyle = 0,
         ::u32 uStyle = 0,
         ::create * pcreate = nullptr);

      void create_common_construct();

      void set_class_name(const char * pszClassName);
      
      void set_window_name(const char * pszWindowName);

      void set_rect(const ::rect & rect);

      void get_rect(RECT32 * prect);

      void add_visible(bool bAdd = true);

      inline auto get_rect() { ::rect rect(e_no_init); get_rect(&rect); return rect; }

   };


} // namespace user


