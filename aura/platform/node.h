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

      //
      // //::pointer<::windowing::windowing>         m_pwindowingAuraNode;
      // bool                                      m_bUnhookX;


      node();
      ~node() override;


      virtual void on_initialize_particle() override;

      virtual void dpi_os_initialize() override;

      //virtual void message_box_factory();


      string system_options_html() override;



//#ifdef LINUX

  //    virtual ::linux::appindicator * appindicator_allocate();
    //  virtual void appindicator_destroy(::linux::appindicator * pappindicator);

//#endif


      virtual ::image::image_pointer get_file_image_by_type_identifier(int iSize, const ::scoped_string & scopedstrTypeIdentifier) override;

      virtual ::image::image_pointer get_file_image(int iSize, const ::file::path & path) override;
      
      virtual void defer_dock_application(bool bDock) override;

//      void set_application_menu(::application_menu * pmenu, ::apex::application * papp) override;

//      virtual void * node_wrap_window(void * pdisplay, long long window);

      //using apex::node::user_fork;

      //virtual void user_fork(const ::procedure & procedure) override;

      //virtual ::windowing::windowing * windowing();


      //pointer< ::extended::sequence < ::conversation > > message_box(::user::interaction * puserinteraction, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox) override;


      void BeginWaitCursor() override;
      void EndWaitCursor() override;
      void RestoreWaitCursor() override;

#ifdef WINDOWS_DESKTOP

      ///virtual void* HICON_from_ico_file(const ::block& block);
      virtual void* HICON_from_image(::image::image *pimage);

#endif


      //::pointer<::conversation>create_new_message_box_conversation() override;


      //pointer< ::sequence < ::conversation > > get_new_conversation_sequence() override;

      //pointer< ::sequence < ::conversation > > message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box& emessagebox) override;


      virtual bool defer_windowing_post(const ::procedure & procedure) override;


      virtual ::pointer < ::aqua::media_item > create_media_item_from_platform_media_item(platform_media_item_t * pplatformmediaitem) override;


   };


} // namespace aura



