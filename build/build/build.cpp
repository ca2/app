//
// Created by camilo on 12/12/21 05:08 PM <3ThomasBorregaardSorensen!!
//
#include "framework.h"


namespace app_core_build
{


   build::build()
   {

   }


   build::~build()
   {

   }


   ::e_status build::prepare_build()
   {

      return ::success;

   }


   ::e_status build::do_build()
   {

      return ::success;

   }


   ::e_status build::run()
   {

      auto estatus = prepare_build();

      if (!estatus)
      {

         return estatus;

      }

      estatus = do_build();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void build::write_log(const ::string & str)
   {

      if (str.has_char())
      {

         m_psystem->m_pacmefile->append(m_psystem->m_pacmedir->home() /"build.log", str);

         if (m_puserinteraction)
         {

            m_puserinteraction->set_need_redraw();

            m_puserinteraction->post_redraw();

         }

      }

   }


   ::e_status build::run_command(const ::string & strCommand)
   {

      bool bTimeout = false;

      ::operating_system::process_pointer process(e_create, this);

      process->create_child_process(strCommand,true, get_current_dir_name(), ::e_priority_highest);

         //::system(str + " > " + "\"" + strClog + "\"");

      auto tickStart = ::duration::now();

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

         return error_timeout;

      }

      return ::success;

   }


} // namespace app_core_build



