#pragma once


namespace user
{


   class CLASS_DECL_BASE form_view:
      virtual public ::user::show < ::user::margin < ::user::form_window > >
   {
   public:


      string                           m_strPath;
      string                           m_strOpenOnCreate;
      ::rectangle_i32                  m_rectOpen;



      using BASE_VIEW = ::user::show < ::user::margin < ::user::form_window > >;

      
      form_view();
      virtual ~form_view();


      inline ::base::application * get_application() const { return form_control::get_application(); }
      inline ::base::session * get_session() const { return form_control::get_session(); }
      inline ::base::system * get_system() const { return form_control::get_system(); }
      inline ::base::user * user() const { return form_control::user(); }


      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;

      virtual ::e_status open_document(const ::payload & varFile) override;
      
      virtual ::e_status open_html(const string & str) override;

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
      
      form_document * get_document();
      

   };


} // namespace user



