//
// Created by camilo on 2024-10-24 11:33 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "node_aura.h"


namespace platform
{


   ///virtual void on_initialize_particle() override{}

   void aura_node_layer::dpi_os_initialize()
   {
   }


   //virtual void message_box_factory(){}


   //string system_options_html() override{}


   //#ifdef LINUX

   //    virtual ::linux::appindicator * appindicator_allocate(){}
   //  virtual void appindicator_destroy(::linux::appindicator * pappindicator){}

   //#endif


   ::image::image_pointer aura_node_layer::get_file_image_by_type_identifier(
      int iSize, const ::scoped_string& scopedstrTypeIdentifier)
   {
      return {};
   }


   ::image::image_pointer aura_node_layer::get_file_image(int iSize, const ::file::path& path)
   {
      return {};
   }


   void aura_node_layer::defer_dock_application(bool bDock)
   {
   }


   //      void set_application_menu(::application_menu * pmenu, ::apex::application * papp) override{}

   //      virtual void * node_wrap_window(void * pdisplay, long long window){}

   //using apex::node::user_fork{}

   //virtual void user_fork(const ::procedure & procedure) override{}

   //virtual ::windowing::windowing * windowing(){}


   //pointer< ::extended::sequence < ::conversation > > message_box(::user::interaction * puserinteraction, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox) override{}


   void aura_node_layer::BeginWaitCursor()
   {
   }


   void aura_node_layer::EndWaitCursor()
   {
   }


   void aura_node_layer:: RestoreWaitCursor()
   {
   }

#ifdef WINDOWS_DESKTOP

   ///virtual void* HICON_from_ico_file(const ::block& block){}
   void*  aura_node_layer::HICON_from_image(::image::image* pimage)
   {

      return nullptr;

   }

#endif


   //::pointer<::conversation>create_new_message_box_conversation() override{}


   //pointer< ::sequence < ::conversation > > get_new_conversation_sequence() override{}

   //pointer< ::sequence < ::conversation > > message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box& emessagebox) override{}


   bool  aura_node_layer::defer_windowing_post(const ::procedure& procedure)
   {

return false;

   }


   ::pointer<::aqua::media_item>  aura_node_layer::create_media_item_from_platform_media_item(
      platform_media_item_t* pplatformmediaitem)
   {

return {};

   }


} // namespace platform
