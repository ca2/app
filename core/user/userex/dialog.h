#pragma once


#include "aura/user/user/form_callback.h"



class CLASS_DECL_CORE dialog :
   virtual public ::user::form_callback
{
public:


   __pointer(::form_document)             m_pdocument;
   __pointer(simple_frame_window)         m_pframe;
   __pointer(::user::form_impact)           m_pform;
   string                                 m_strMatter;


   dialog();
   dialog(const ::string & pszMatter, __pointer(::user::interaction) puiParent);
   virtual ~dialog();

   virtual void on_position_parent_frame();

   virtual void EndModalLoop(atom nResult);

   virtual bool show(const ::string & pszMatter = nullptr);

   virtual void on_show(const ::string & pszMatter);

   virtual void do_data_exchange(::user::data_exchange * pdx);


   virtual int_bool on_init_dialog();


   // MFC dialog compatibility : TODO, ca2fy, at least the member function names
   virtual void OnCancel();
   virtual void OnOK();
   //virtual bool update_data(bool bSave);
   // update_data true
   virtual void form_from_user();
   // update_data false
   virtual void form_to_user();
   //virtual bool OnInitDialog();
   // substituir, replace _001Initialize
   
   virtual void handle(::topic * ptopic, ::context * pcontext) override;


};


