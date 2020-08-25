#pragma once


namespace hi5
{


   namespace twitter
   {


      class CLASS_DECL_CORE authorization :
         virtual public ::user::form_callback,
         virtual public ::user::impact_creator,
         virtual public ::user::tab_callback,
         virtual public ::user::style
      {
      public:


         string                                    m_strPin;
         string                                    m_strAuthorizationUrl;
         i32                                   m_iView;
         __pointer(::user::single_document_template)      m_ptemplatePane;
         __pointer(::user::document)                      m_pdocument;
         __pointer(::user::tab_view)                      m_ptabview;
         __pointer(::form_document)                       m_pdocAuth;
         __pointer(::form_document)                       m_pdocMessage;
         __pointer(::user::form_view)                     m_pviewAuth;
         bool                                      m_bAuth;
         string                                    m_strForm;
         string                                    m_strLicense;
         bool                                      m_bLicense;
         bool                                      m_bInteractive;

         authorization(::object * pobject,const char * pszAuthorizationUrl, const char * pszForm, bool bAuth = false, bool bInteractive = true);
         virtual ~authorization();

         void ensure_main_document();
         void display_main_frame();
         void page1();
         void pageMessage(const char * pszMatter, property_set & set);

         string get_pin();

         void on_create_impact(::user::impact_data * pimpactdata) override;
         virtual void on_change_cur_sel();


         virtual void on_control_event(::user::control_event * pevent) override;

         virtual bool style_translucency(::user::e_translucency & etranslucency, ::user::e_element);


      };


   } // namespace twitter


} // namespace hi5




