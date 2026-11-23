// From application_build_helper to implement.cpp by camilo on 2021-12-17 21:04 BRT <3ThomasBorregaardSørensen!!
#include "platform.h"
#include "application.h"
#include "launch.h"


IMPLEMENT_APPLICATION_FACTORY(launch);

namespace launch
{


   application::application()
   {

      m_iExitCode = 0;

   }


   application::~application()
   {

   }


   void application::do_launch()
   {
   
      construct_newø(m_plaunch);

      m_plaunch->m_plaunchapplication = this;

      m_plaunch->m_strLaunchAppId = m_strLaunchAppId;

      m_plaunch->do_launch();

   }


   void application::on_launch_main_status(const ::scoped_string& scopedstrMain)
   {

      print_line(scopedstrMain);

   }


   void application::on_launch_detail_status(const ::scoped_string& scopedstrDetail)
   {


   }


   void application::on_launch_error_status(const ::scoped_string& scopedstrDetail)
   {


   }


   void application::on_going_to_launch()
   {


   }


   void application::on_launched()
   {
   
   
   } 


   void application::run()
   {


      if (m_bRunAsLaunch)
      {

         do_launch();

      }
      else
      {

         ::platform::application::run();


      }


   }


} // namespace launch
