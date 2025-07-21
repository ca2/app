#pragma once



namespace helloaxis
{


   class CLASS_DECL_APP_CORE_HELLOAXIS application :
      virtual public ::axis::application
   {
      public:


         enum enum_type
         {

            type_normal,
            type_mili,

         };

         enum_type                                 m_etype;
         string                                 m_strHelloAxis;
         string                                 m_strHelloAxisDefault;
         string                                 m_strAlternateHelloAxis;
         string                                 m_strAlternateHelloAxisDefault;

         bool                                   m_bAxisChat;

         ::user::document *                     m_pdocMenu;

         ::pointer < ::mutex >                                  m_pmutexAiFont;
         int                                m_iErrorAiFont;
         bool                                   m_bLoadAiFont;
         void *                                 m_faceAi; // FT_Face m_faceAi;

         application(::particle * pparticle);
         ~application() override;
      
      __DECLARE_APPLICATION_RELEASE_TIME();


         virtual void init_instance() override;
         virtual int  exit_application() override;

         virtual void on_request(::request * prequest) override;

         virtual long long increment_reference_count() override;
         virtual long long decrement_reference_count() override;

         void paint(HWND hwnd, HDC hdc);

         void paint(HWND hwnd, ::draw2d::graphics_pointer & pgraphics);

   };


} // namespace helloaxis



