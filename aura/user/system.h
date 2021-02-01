#pragma once


namespace user
{

   class CLASS_DECL_AURA create_struct
   {
   public:

      void *      lpCreateParams;
      hinstance   hInstance;
      void *      hMenu;
      oswindow    hwndParent;
      int         cy;
      int         cx;
      int         y;
      int         x;
      long        style;
      wchar_t *   lpszName;
      wchar_t *   lpszClass;
      u32         dwExStyle;
   };


   class CLASS_DECL_AURA system :
      virtual public ::context_object
   {
   public:

      create_struct        m_createstruct;
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
                  ::rectangle_i32 rectangle = nullptr,
                  ::create * pcreate = nullptr);

      system(
         const ::rectangle_i32 & rectangle,
         ::u32 uExStyle = 0,
         ::u32 uStyle = 0,
         ::create * pcreate = nullptr);

      void create_common_construct();

      void set_class_name(const char * pszClassName);
      
      void set_window_name(const char * pszWindowName);

      void set_rect(const ::rectangle_i32 & rectangle);

      void get_rect(RECTANGLE_I32 * prectangle);

      void add_visible(bool bAdd = true);

      inline auto get_rect() { ::rectangle_i32 rectangle(e_no_initialize); get_rect(&rectangle); return rectangle; }

   };


} // namespace user


