#include "framework.h"


namespace acid
{


   void application::_001EnableShellOpen()
   {

   }


   string application::get_version()
   {

      return "1.0.0";

   }


   //bool application::impl_process_init()
   //{

   //   return true;

   //}


   //bool application::impl_init1()
   //{

   //   return true;

   //}


   //bool application::impl_init2()
   //{

   //   return true;

   //}


   //bool application::impl_init3()
   //{

   //   return true;

   //}

   //void application::impl_process_term()
   //{

   //   set_os_data(nullptr);

   //}


   //void application::impl_term1()
   //{

   //}


   //void application::impl_term2()
   //{

   //}


   //void application::impl_term3()
   //{

   //}


//   void application::show_wait_cursor(bool bShow)
//   {
//
//
//   }


   //void application::get_time(struct timeval *p)
   //{

   //   gettimeofday(p, nullptr);

   //}


   //void application::set_env_var(const string & payload,const string & value)
   //{

   //   setenv(payload, value, 1);

   //}


   //itask_t application::get_thread_id()
   //{

   //   return ::pthread_self();

   //}


   bool application::os_on_start_application()
   {
      return true;

   }


   //bool application::request(::create * pdata)
   //{

   //   m_pcommand =  pdata;

   //   string strCmdLine          = pdata->m_strCommandLine;

   //   SetCurrentHandles();

   //   __init_thread();

   //   return true;

   //}


   // string system::draw2d_get_default_implementation_name()
   // {

   //    return "draw2d_cairo";

   // }


   string application::multimedia_audio_get_default_implementation_name()
   {

      return system()->implementation_name("audio", "opensles");

   }


   string application::multimedia_audio_mixer_get_default_implementation_name()
   {

      return system()->implementation_name("audio_mixer", "opensles");

   }


   string application::veriwell_multimedia_music_midi_get_default_implementation_name()
   {

      return "";

   }


} // namespace android




