//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
#if !BROAD_PRECOMPILED_HEADER
////#include "aura/user/user/_component.h"
#endif
#ifdef LINUX
#include "aura/operating_system/linux/x11.h"
#endif
//#include "aura/user/micro/message_box.h"


namespace aura
{


   node::node()
   {

      m_pauranode = this;

      m_bUnhookX = true;

   }


   node::~node()
   {


   }


   void node::on_initialize_object()
   {

      //auto estatus =
      
      ::apex::node::on_initialize_object();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //message_box_factory();

      m_psystem->m_pauranode = this;

      //return estatus;

   }


   void node::dpi_os_initialize()
   {

      throw ::exception(error_failed);

   }


   //void node::message_box_factory()
   //{

   //   //::factory::add_factory_item < ::user::default_message_box, ::user::message_box >();

   //}


   string node::system_options_html()
   {

      return ::apex::node::system_options_html();

      //string strFooter__;

      //strFooter__ += system_options_main_body();

      //strFooter__ += ::apex::node::system_options_html();

      //return strFooter__;

   }


   ::image_pointer node::get_file_image_by_type_identifier(int iSize, const char * pszTypeIdentifier)
   {
      
      throw ::interface_only();
      
      return nullptr;
      
   }


   ::image_pointer node::get_file_image(int iSize, const char * pszPath)
   {
      
      throw ::interface_only();
      
      return nullptr;
      
   }


   void node::defer_dock_application(bool bDock)
   {
      
   }


   void node::set_application_menu(::application_menu * pmenu, ::apex::application * papp)
   {

   }


   ::windowing::windowing * node::windowing()
   {

      return m_pwindowing;

   }


//   void * node::node_wrap_window(void * pdisplay, i64 window)
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

   //   auto pmessagebox = puserinteraction->__create < ::user::message_box >();

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


   void* node::HICON_from_image(::image * pimage)
   {

      throw ::interface_only();

      return nullptr;

   }


#endif


   //::pointer<::conversation>node::create_new_message_box_conversation()
   //{

   //   return __create_new < ::micro_message_box >();

   //}

} // namespace aura



