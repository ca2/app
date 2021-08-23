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

      m_psystem->m_pauranode = this;

      return estatus;

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



} // namespace aura



