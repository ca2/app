#pragma once


namespace user
{


   class CLASS_DECL_BASE form_view:
      virtual public ::user::show < ::user::margin < ::user::form_window > >
   {
   public:


      string                           m_strPath;
      string                           m_strOpenOnCreate;
      ::rect                           m_rectOpen;



      using BASE_VIEW = ::user::show < ::user::margin < ::user::form_window > >;

      
      form_view();
      virtual ~form_view();


      virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;

      virtual ::estatus open_document(const payload & varFile) override;
      
      virtual ::estatus open_html(const string & str) override;

      virtual bool Navigate(const char* pszUrl);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      template < typename FORM >
      void create_child_form()
      {

         m_pform = create_view < FORM >(this, "child_form");

      }
      
      virtual void soft_reload() override;

      virtual void set_need_load_form_data() override;

      virtual void on_control_event(::user::control_event * pevent) override;

   };


} // namespace user

















































