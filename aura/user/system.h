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
      virtual public ::context_object
   {
   public:


      __pointer(::user::primitive)           m_puserprimitiveOwner;
      ::routine                              m_routineSuccess;
      ::routine                              m_routineFailure;
      __pointer(::user::interaction_impl)    m_pimpl;
      __pointer(::create)                    m_pcreate;
      ::windowing::window *                  m_pwindow;

      bool                                   m_bAutoWindowFrame;
      bool                                   m_bWindowFrame;
      ::type                                 m_typeNewView;
      __pointer(::object)                    m_pdocumentCurrent;
      __pointer(::user::primitive)           m_puserprimitiveNew;

      __pointer(::object)                    m_ptemplateNewDocument;

      __pointer(::user::primitive)           m_puserprimitiveLastView;
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

      //void set_class_name(const char* pszClassName);

      //void set_window_name(const char* pszWindowName);

      //void set_rect(const ::rectangle_i32& rectangle);

      //void get_rect(RECTANGLE_I32* prectangle);

      void add_visible(bool bAdd = true);

      //inline auto get_rect() { ::rectangle_i32 rectangle(e_no_initialize); get_rect(&rectangle); return rectangle; }

   };


} // namespace windowing_win32



