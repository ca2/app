//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
#ifdef LINUX
#include "aura/node/operating_system/linux/x11.h"
#endif


namespace aura
{


   node::node()
   {

      m_pauranode = this;

   }


   node::~node()
   {


   }


   ::e_status node::on_initialize_object()
   {

      auto estatus = ::apex::node::on_initialize_object();

      if (!estatus)
      {

         return estatus;

      }

      message_box_factory();

      m_psystem->m_pauranode = this;

      return estatus;

   }


   void node::dpi_os_initialize()
   {

      throw exception::exception(error_failed);

   }


   void node::message_box_factory()
   {

      create_factory < ::user::default_message_box, ::user::message_box >();

   }


//#ifdef LINUX
//
//   ::linux::appindicator * node::appindicator_allocate()
//   {
//
//      return nullptr;
//
//   }
//
//
//   void node::appindicator_destroy(::linux::appindicator * pappindicator)
//   {
//
//      //return nullptr;
//
//   }
//
//
//#endif


   ::image_pointer node::get_file_image_by_type_identifier(int iSize, const char * pszTypeIdentifier)
   {
      
      __throw(error_interface_only);
      
      return nullptr;
      
   }


   ::image_pointer node::get_file_image(int iSize, const char * pszPath)
   {
      
      __throw(error_interface_only);
      
      return nullptr;
      
   }


   void node::defer_dock_application(bool bDock)
   {
      
   }


   void node::set_application_menu(::application_menu * pmenu, ::application * papplication)
   {

   }


//   void * node::node_wrap_window(void * pdisplay, i64 window)
//   {
//
//      return nullptr;
//
//   }


//   void node::user_fork(const ::routine & routine)
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

   
   __pointer(::extended::sequence < ::conversation >) node::message_box(::user::interaction * puserinteraction, const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox)
   {

      auto pmessagebox = __create < ::user::message_box >();

      auto pfuture = pmessagebox->::extended::asynchronous<::conversation>::future();

      auto pextendedfuture = pmessagebox->show(puserinteraction, strMessage, strTitle, emessagebox);

      return pextendedfuture;

   }


} // namespace aura



