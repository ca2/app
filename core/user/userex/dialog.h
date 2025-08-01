#pragma once


#include "aura/user/user/form_callback.h"



class CLASS_DECL_CORE dialog :
   virtual public ::user::form_callback
{
public:


   ::pointer<::form_document>             m_pformdocument;
   ::pointer<simple_frame_window>         m_pframe;
   ::pointer<::user::form_impact>         m_pform;
   string                                 m_strMatter;


   dialog();
   dialog(const ::scoped_string & scopedstrMatter, ::pointer<::user::interaction>puiParent);
   ~dialog() override;

   virtual void on_position_parent_frame();

   virtual void EndModalLoop(atom nResult);

   virtual bool show(const ::scoped_string & scopedstrMatter = nullptr);

   virtual void on_show(const ::scoped_string & scopedstrMatter);

   virtual void do_data_exchange(::user::data_exchange * pdx);


   virtual int_bool on_init_dialog();


   virtual void OnCancel();
   virtual void OnOK();
   virtual void form_from_user();
   virtual void form_to_user();
   
   void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


};


