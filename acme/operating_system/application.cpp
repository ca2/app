// Created by camilo on 2023-04-15 19:17 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "application.h"
#include "acme/exception/interface_only.h"


namespace operating_system
{


   application::application()
   {

      m_processidentifier = -1;

   }

   
   application::~application()
   {


   }

   
   void application::open_by_module_path(const ::scoped_string & scopedstr)
   {

      throw interface_only();

   }


   void application::post_close()
   {

      throw interface_only();

   }


} // namespace operating_system



