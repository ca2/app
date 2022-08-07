#pragma once


namespace user
{


   //class CLASS_DECL_AURA create_struct
   //{
   //public:


   //   void *               lpCreateParams;
   //   hinstance            hInstance;
   //   void *               hMenu;
   //   oswindow             hwndParent;
   //   int                  cy;
   //   int                  cx;
   //   int                  y;
   //   int                  x;
   //   long                 style;
   //   platform_char *      lpszName;
   //   platform_char *      lpszClass;
   //   u32                  dwExStyle;


   //};


   class CLASS_DECL_AURA system :
      virtual public ::object
   {
   public:


      __pointer(::user::primitive)           m_puserprimitiveOwner;
      ::procedure                              m_procedureSuccess;
      ::procedure                              m_procedureFailure;
      __pointer(::user::interaction_impl)    m_puserinteractionimpl;
      __pointer(::create)                    m_pcreate;
      __pointer(::windowing::window)         m_pwindow;

      tristate                                m_bWindowFrame;
      ::type                                 m_typeNewImpact;
      __pointer(::object)                    m_pdocumentCurrent;
      __pointer(::user::primitive)           m_puserprimitiveNew;

      __pointer(::object)                    m_ptemplateNewDocument;

      __pointer(::user::primitive)           m_puserprimitiveLastImpact;
      __pointer(::user::primitive)           m_puserprimitiveCurrentFrame;
      __pointer(::matter)                    m_pimpactdata;


      system(const system&);
      system(
         //u32 uExStyle = 0,
         //const char* pszClassName = 0,
         //const char* pszWindowName = 0,
         //u32 uStyle = 0,
         //const ::rectangle_i32& rectangle = nullptr,
         ::create* pcreate = nullptr);

      //system(
      //   const ::rectangle_i32& rectangle,
      //   //::u32 uExStyle = 0,
      //   //::u32 uStyle = 0,
      //   ::create* pcreate = nullptr);

      void create_common_construct();

      //void set_class_name(const ::string & pszClassName);

      //void set_window_name(const ::string & pszWindowName);

      //void set_rect(const ::rectangle_i32& rectangle);

      //void get_rect(RECTANGLE_I32* prectangle);

      void add_visible(bool bAdd = true);

      //inline auto get_rect() { ::rectangle_i32 rectangle(e_no_initialize); get_rect(&rectangle); return rectangle; }

      __pointer(::user::interaction) create_impact(::user::interaction * puserinteractionParent, const ::atom & atom);


   };


} // namespace windowing_win32



