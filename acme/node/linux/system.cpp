//
// Created by camilo on 02/12/2020  <3tbs!!
// (as acme/os/linux/application_system_run.cpp)
// Created by Camilo 2020-12-29 16:25 BRT <3TBS, Mummi and bilbo!!
// (as acme/node/linux/system.cpp)
#include "framework.h"
#include "acme/os/x11/_x11.h"


namespace acme
{


   ::e_status system::os_application_system_run()
   {

      return ::success;

   }


   void system::os_construct()
   {

      auto lines = file_as_lines("/etc/os-release");

      ::string strId;

      if(lines.find_first_begins_eat_ci(strId, "id="))
      {

         strId.make_lower();

         if (strId == "ubuntu")
         {

            m_elinuxdistribution = e_linux_distribution_ubuntu;

         }

      }

      if(m_elinuxdistribution <= 0)
      {

         output_debug_string("WARNING: Unknown linux distribution with id \"" + strId + "\".");

      }

   }


   enum_operating_system system::get_operating_system() const
   {

       return e_operating_system_linux;

   }


   ::e_status system::defer_initialize_x11()
   {

      auto estatus = ::defer_initialize_x11();

      return estatus;

   }


} // namespace acme



