#pragma once


namespace user
{


   class CLASS_DECL_BASE form_view:
      virtual public ::user::show < ::user::margin < ::user::form_window > >
   {
   public:


      string                           m_strPath;
      string                           m_strOpenOnCreate;
      ::rectangle_i32                  m_rectangleOpen;



      using BASE_VIEW = ::user::show < ::user::margin < ::user::form_window > >;

      
      form_view();
      ~form_view() override;


      inline ::base::application * get_app() const { return form_control::get_app(); }
      inline ::base::session * get_session() const { return form_control::get_session(); }
      inline ::base::system * get_system() const { return form_control::get_system(); }
      inline ::base::user * user() const { return form_control::user(); }


      void handle(::topic * ptopic, ::context * pcontext) override;

      bool open_document(const ::payload & payloadFile) override;
      
      bool open_html(const ::string & str) override;

      virtual bool Navigate(const ::string & pszUrl);

      void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      template < typename FORM >
      void create_child_form()
      {

         m_pform = create_view < FORM >(this, "child_form");

      }
      
      void soft_reload() override;

      void set_need_load_form_data() override;

      //virtual void handle(::topic * ptopic, ::context * pcontext) override;
      
      form_document * get_document();
      

   };


} // namespace user



