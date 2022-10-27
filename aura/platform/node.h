//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
// Aura(Mummi) addition of micro message box!! 2022-05-08 Mother's day 2022!!
//
#pragma once


#ifdef LINUX

namespace linux
{

   class appindicator;

}

#endif


#include "apex/platform/node.h"


namespace aura
{


   class CLASS_DECL_AURA node :
      virtual public ::apex::node
   {
   public:


      ::pointer<::windowing::windowing>        m_pwindowing;
      bool                                      m_bUnhookX;


      node();
      ~node() override;


      virtual void on_initialize_particle() override;

      virtual void dpi_os_initialize();

      //virtual void message_box_factory();


      string system_options_html() override;



//#ifdef LINUX

  //    virtual ::linux::appindicator * appindicator_allocate();
    //  virtual void appindicator_destroy(::linux::appindicator * pappindicator);

//#endif


      virtual ::image_pointer get_file_image_by_type_identifier(int iSize, const char * pszTypeIdentifier);

      virtual ::image_pointer get_file_image(int iSize, const char * pszPath);
      
      virtual void defer_dock_application(bool bDock);

      void set_application_menu(::application_menu * pmenu, ::apex::application * papp) override;

//      virtual void * node_wrap_window(void * pdisplay, i64 window);

      //using apex::node::user_fork;

      //virtual void user_fork(const ::procedure & procedure) override;

      virtual ::windowing::windowing * windowing();


      //pointer< ::extended::sequence < ::conversation > > message_box(::user::interaction * puserinteraction, const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox) override;


      void BeginWaitCursor();
      void EndWaitCursor();
      void RestoreWaitCursor();

#ifdef WINDOWS_DESKTOP

      ///virtual void* HICON_from_ico_file(const ::block& block);
      virtual void* HICON_from_image(::image * pimage);

#endif


      //::pointer<::conversation>create_new_message_box_conversation() override;


      //pointer< ::sequence < ::conversation > > get_new_conversation_sequence() override;

      //pointer< ::sequence < ::conversation > > message_box(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox) override;


   };


} // namespace aura



