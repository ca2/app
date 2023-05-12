// Created by camilo on 2023-04-15 19:17 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "application.h"
#include "main_window.h"
#include "acme/exception/interface_only.h"
#include "acme/platform/node.h"


namespace operating_system
{


   application::application()
   {

      m_processidentifier = -1;

   }

   
   application::~application()
   {


   }

   
void application::open_by_process_identifier(::process_identifier processidentifier)
{

   m_processidentifier = processidentifier;

}


void application::open_by_module_path(const ::scoped_string & scopedstr)
   {

      throw interface_only();

   }


   void application::post_close()
   {

      auto pmainwindow = __create < ::operating_system::main_window >();

      pmainwindow->from_application(this);

      pmainwindow->post_close();

   }


   void application::post_exit()
   {

      auto pmainwindow = __create < ::operating_system::main_window >();

      pmainwindow->from_application(this);

      pmainwindow->post_application_exit();

   }


   ::string application::name()
   {

      auto pathModule = this->module_path();
      
      return pathModule.title();
      
   }


   ::string application::main_window_title()
   {
   
      throw interface_only();
      
      return {};
      
   }

   
   ::count application::window_count() const
   {

      throw interface_only();
      
      return -1;
      
   }


   ::file::path application::module_path()
   {
   
      return acmenode()->process_identifier_module_path(m_processidentifier);
      
   }


} // namespace operating_system



