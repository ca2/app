//
// Created by camilo on 12/12/21 05:08 PM <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"


namespace app_build
{


   build::build()
   {
m_bStdout = false;
   }


   build::~build()
   {

   }


   void build::prepare_build()
   {

      //return ::success;

   }


   void build::do_build()
   {

      //return ::success;

   }


   void build::run()
   {

      //auto estatus =
      //
      prepare_build();

//      if (!estatus)
//      {
//
//         return estatus;
//
//      }

      //estatus =
      //
      do_build();

//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;

   }


   void build::write_log(const ::string & str)
   {

      if (str.has_char())
      {

         acmefile()->append(acmedirectory()->home() /"build.log", str);

         if(m_bStdout)
         {

            printf("%s", str.c_str());

         }

//         if (m_puserinteraction)
//         {
//
//            m_puserinteraction->set_need_redraw();
//
//            m_puserinteraction->post_redraw();
//
//         }

      }

   }


   void build::run_command(const ::string & strCommand)
   {

      bool bTimeout = false;

      ::operating_system::process_pointer process(e_create, this);

      process->create_child_process(strCommand,true, get_current_dir_name(), ::e_priority_highest);

         //::system(str + " > " + "\"" + strClog + "\"");

      auto tickStart = ::time::now();

      string strLog;

      while (::task_get_run())
      {

         string strRead = process->read();

         write_log(strRead);

         if (process->has_exited())
         {

            break;

         }

         preempt(100_ms);

         if (tickStart.elapsed() > 890_s) // 14 minutes
         {

            bTimeout = true;

            break;

         }

      }

      string strRead = process->read();

      write_log(strRead);

      if(bTimeout)
      {

         throw ::exception(error_wait_timeout);

      }

      //return ::success;

   }


} // namespace app_core_build



