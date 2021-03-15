//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"


namespace apex
{

   node::node()
   {

      m_papexnode = this;

   }


   node::~node()
   {


   }


   void node::set_application_menu(::apex::application_menu * pmenu, ::apex::application * papplication)
   {

   }


   ::file::path node::get_desktop_file_path(::apex::application * papplication) const
   {

      return "";

   }


   void node::defer_notify_startup_complete()
   {


   }


   ::e_status node::start()
   {

      __pointer(::apex::system) psystem = get_system();

      auto estatus = psystem->on_start();

      if(!estatus)
      {

         return estatus;

      }

      return estatus;


   }


#ifdef WINDOWS


   ::e_status node::register_dll(const ::file::path & pathDll)
   {

      __throw(error_interface_only);

      return error_interface_only;

   }


#endif

   void node::on_os_dark_mode_change()
   {

      __pointer(::apex::system) psystem = get_system();

      psystem->deliver(id_os_dark_mode);

   }


} // namespace apex



