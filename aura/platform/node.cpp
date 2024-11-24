//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
#include "acme/exception/interface_only.h"
#include "acme/platform/system.h"
#include "aura/platform/session.h"
#include "aura/user/user/user.h"


//#ifdef LINUX
//#include "aura/operating_system/linux/x11.h"
//#endif
//#include "aura/user/micro/message_box.h"


namespace aura
{


   node::node()
   {

      //m_pauranode = this;

      m_bUnhookX = true;

   }


   node::~node()
   {


   }


   void node::on_initialize_particle()
   {

      //auto estatus =
      
      ::apex::node::on_initialize_particle();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //message_box_factory();

      //system() = this;

      //return estatus;

   }


   void node::dpi_os_initialize()
   {

      throw ::exception(error_failed);

   }


   //void node::message_box_factory()
   //{

   //   //factory()->add_factory_item < ::user::default_message_box, ::user::message_box >();

   //}


   string node::system_options_html()
   {

      return ::apex::node::system_options_html();

      //string strFooter__;

      //strFooter__ += system_options_main_body();

      //strFooter__ += ::apex::node::system_options_html();

      //return strFooter__;

   }


   ::image::image_pointer node::get_file_image_by_type_identifier(int iSize, const ::scoped_string & scopedstrTypeIdentifier)
   {
      
      throw ::interface_only();
      
      return nullptr;
      
   }


   ::image::image_pointer node::get_file_image(int iSize, const ::file::path & path)
   {
      
      throw ::interface_only();
      
      return nullptr;
      
   }


   void node::defer_dock_application(bool bDock)
   {
      
   }


//   void node::set_application_menu(::application_menu * pmenu, ::apex::application * papp)
//   {
//
//   }


   //::windowing::windowing * node::windowing()
   //{

   //   if(!m_pwindowingAuraNode)
   //   {

   //      system()->do_graphics_and_windowing_system_factory();

   //   }

   //   return m_pwindowingAuraNode;

   //}


//   void * node::node_wrap_window(void * pdisplay, huge_integer window)
//   {
//
//      return nullptr;
//
//   }


//   void node::user_fork(const ::procedure & procedure)
//   {
//
//#ifdef LINUX
//
//      x11_fork([routine]()
//               {
//
//                  routine();
//
//               });
//
//#endif
//
//   }

   
   //pointer< ::extended::sequence < ::conversation > > node::message_box(::user::interaction * puserinteraction, const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox)
   //{

   //   auto pmessagebox = puserinteraction->__øcreate < ::user::message_box >();

   //   auto pfuture = pmessagebox->::extended::asynchronous<::conversation>::sequence();

   //   auto pextendedfuture = pmessagebox->show(puserinteraction, strMessage, strTitle, emessagebox);

   //   return pextendedfuture;

   //}


   void node::BeginWaitCursor()
   {

   }


   void node::EndWaitCursor()
   {

   }


   void node::RestoreWaitCursor()
   {

   }


#ifdef WINDOWS_DESKTOP


   void* node::HICON_from_image(::image::image *pimage)
   {

      throw ::interface_only();

      return nullptr;

   }


#endif


   //::pointer<::conversation>node::create_new_message_box_conversation()
   //{

   //   return __create_new < ::micro_message_box >();

   //}


   bool node::defer_windowing_post(const ::procedure & procedure)
   {

      return false;

   }


   ::pointer < ::aqua::media_item > node::create_media_item_from_platform_media_item(platform_media_item_t * pplatformmediaitem)
   {

      throw ::interface_only();

      return nullptr;

   }



} // namespace aura



