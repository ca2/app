#pragma once


#include "axis/user/form/window.h"
#include "base/user/user/margin.h"
#include "base/user/user/show.h"


namespace user
{


   class CLASS_DECL_BASE form_impact:
      virtual public ::user::show < ::user::margin < ::user::form_window > >
   {
   public:


      string                           m_strPath;
      string                           m_strOpenOnCreate;
      ::int_rectangle                  m_rectangleOpen;



      using BASE_VIEW = ::user::show < ::user::margin < ::user::form_window > >;

      
      form_impact();
      ~form_impact() override;




      // inline ::axis::application * get_app() { return form_control::get_app(); }
      // inline ::axis::session * get_session() { return form_control::get_session(); }
      // inline ::axis::system * get_system() { return form_control::get_system(); }
      // //inline ::axis::user * axisuser() { return form_control::axisuser(); }


      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      bool open_document(const ::payload & payloadFile) override;
      
      bool open_html(const ::scoped_string & scopedstr) override;

      virtual bool Navigate(const ::scoped_string & scopedstrUrl);

      void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      template < typename FORM >
      void create_child_form()
      {

         m_pform = create_impact < FORM >(this, "child_form");

      }
      
      void soft_reload() override;

      void set_need_load_form_data() override;

      //void handle(::topic * ptopic, ::handler_context * phandlercontext) override;
      
      form_document * get_document();
      

   };


} // namespace user



