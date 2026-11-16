// Enhancing userex::dialog by camilo on 2026-11 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
#pragma once


#include "aura/user/user/form.h"
#include "aura/user/user/form_callback.h"
#include "berg/user/user/form_handler.h"


namespace userex
{


   class CLASS_DECL_CORE dialog :
      virtual public ::user::form,
      virtual public ::user::form_callback,
      virtual public ::berg::form_handler
   {
   public:


      ::pointer<::form_document>             m_pformdocument;
      ::pointer<simple_frame_window>         m_pframe;
      ::pointer<::user::form_impact>         m_pform;
      string                                 m_strMatter;
      ::pointer<::user::interaction> m_pdialogOwner;
      // Content sizing still runs; false disables user resizing and resize grips.
      bool m_bResizable = true;


      dialog();
      dialog(const ::scoped_string & scopedstrMatter, ::pointer<::user::interaction>puiParent);
      ~dialog() override;

      // The action button forwards its primary action to this dialog.
      void set_action_button(::user::button * pbutton);

      ::i32_size calculate_client_size(::draw2d::graphics_pointer & pgraphics);
      virtual void on_position_parent_frame();

      virtual void EndModalLoop(atom nResult);

      virtual bool show(const ::scoped_string & scopedstrMatter = nullptr);

      virtual void on_show(const ::scoped_string & scopedstrMatter);

      virtual void do_data_exchange(::user::data_exchange * pdx);


      virtual ::i32_bool on_init_dialog();


      virtual void OnCancel();
      virtual void OnOK();
      virtual void form_from_user();
      virtual void form_to_user();

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


   };


} // namespace userex

