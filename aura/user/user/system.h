#pragma once


////#include "acme/prototype/prototype/object.h"


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
   //   unsigned int                  dwExStyle;


   //};


   class CLASS_DECL_AURA system :
      virtual public ::property_object
   {
   public:


      ::pointer<::user::interaction_base>              m_puserprimitiveOwner;
      ::procedure                               m_procedureSuccess;
      ::procedure                               m_procedureFailure;
      //::pointer<::windowing::window>       m_pwindow;
      ::pointer<::request>                      m_prequest;
      ::pointer<::windowing::window>            m_pwindow;

      ::logic::boolean                          m_bWindowFrame;
      ::type_atom                               m_typeatomNewImpact;
      ::pointer<::object>                       m_pdocumentCurrent;
      ::pointer<::user::interaction_base>              m_puserprimitiveNew;

      ::pointer<::object>                       m_ptemplateNewDocument;

      ::pointer<::user::interaction_base>              m_puserprimitiveLastImpact;
      ::pointer<::user::interaction_base>              m_puserprimitiveCurrentFrame;
      ::pointer<::matter>                       m_pimpactdata;
      ::pointer_array<::graphics::output_purpose>     m_graphicsoutputpurposea;


      system(const system&);
      system(
         //unsigned int uExStyle = 0,
         //const ::scoped_string & scopedstrClassName = 0,
         //const ::scoped_string & scopedstrWindowName = 0,
         //unsigned int uStyle = 0,
         //const ::int_rectangle& rectangle = nullptr,
         ::request* prequest = nullptr);

      //system(
      //   const ::int_rectangle& rectangle,
      //   //unsigned int uExStyle = 0,
      //   //unsigned int uStyle = 0,
      //   ::create* pcreate = nullptr);

      void create_common_construct();

      void add(::graphics::output_purpose * pgraphicsoutputpurpose);

      //void set_class_name(const ::scoped_string & scopedstrClassName);

      //void set_window_name(const ::scoped_string & scopedstrWindowName);

      //void set_rect(const ::int_rectangle& rectangle);

      //void get_rect(::int_rectangle* prectangle);

      void add_visible(bool bAdd = true);

      //inline auto get_rect() { ::int_rectangle rectangle(no_initialize_t{}); get_rect(&rectangle); return rectangle; }

      ::pointer<::user::interaction>create_impact(::user::interaction * puserinteractionParent, const ::atom & atom);


      void destroy() override;

   };


} // namespace windowing_win32



