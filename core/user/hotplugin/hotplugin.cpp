#include "framework.h"

//#include "hotplugin.h"


namespace hotplugin
{


   ::aura::system * g_paurasystem = nullptr;


   int g_iSystemCount = 0;


   unsigned int c_cdecl base_system_main(LPVOID pVoid);



   CLASS_DECL_BERG ::aura::system * get_aura_system()
   {

      return g_paurasystem;

   }


   CLASS_DECL_BERG bool defer_start_base_system()
   {

      if(g_paurasystem != nullptr)
         return true;

      g_iSystemCount++;

      throw ::exception(todo(nullptr));

//      try
//      {

//         g_paxissystem = ___new ::axis::system (nullptr, );

//         if(file_system()->exists(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "config\\plugin\\npca2_beg_debug_box.txt"))
//         {

//            debug_box("hotplugin boxmain NP_Initialize","ZZZzzz hotplugin box",::user::e_message_box_ok);

//         }
//         if(file_system()->exists(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "config\\plugin\\npca2_beg_sleep.txt"))
//         {

//            sleep(10000_ms);

//         }

//         ::set_thread(g_paxissystem);

//         g_paxissystem->m_bMatterFromHttpCache = true;

//         g_paxissystem->m_bSystemSynchronizedCursor = false;

// #ifdef WINDOWS

//         g_paxissystem->m_hinstance = (HINSTANCE)get_hinstance();

// #endif

//         xxdebug_box("box1","box1",::user::e_message_box_icon_information);

// #ifdef WINDOWS

//         set_main_user_htask((htask) GetCurrentThread());

//         set_main_user_itask(GetCurrentThreadId());

// #endif

//         g_paxissystem->m_bReady = false;

//         ::create_thread(nullptr,0,&base_system_main,nullptr,0,nullptr);

//      }
//      catch(...)
//      {

//         return false;

//         // debug_box("failed to create system", "npca2", 0);
//         //      return nullptr;
//      }

//      return true;

   }


   //unsigned int c_cdecl base_system_main(LPVOID pVoid)

   //{

   //   //int iReturnCode = 0;

   //   try
   //   {

   //      if(!g_paxissystem->pre_run())
   //      {

   //         g_paxissystem->m_result.add(error_failed);

   //         g_paxissystem->m_bReady = true;

   //         return -1;

   //      }

   //   }
   //   catch(...)
   //   {

   //      g_paxissystem->m_result.add(error_failed);

   //      g_paxissystem->m_bReady = true;

   //      return -1;

   //   }

   //   g_paxissystem->main();

   //   return g_paxissystem->get_result_status();

   //}


#ifdef WINDOWS


   HINSTANCE g_hinstance = nullptr; // hotplugin plugin dll HINSTANCE


   CLASS_DECL_BERG HINSTANCE get_hinstance()
   {

      return g_hinstance;

   }


   CLASS_DECL_BERG void set_hinstance(HINSTANCE hinstance)
   {

      g_hinstance = hinstance;

   }


#endif


   CLASS_DECL_BERG void defer_stop_base_system()
   {

      g_iSystemCount--;

      if(g_iSystemCount == 0)
      {

         if(g_paurasystem != nullptr)
         {

            g_paurasystem->destroy();

            g_paurasystem = nullptr;

         }

         //__wait_threading_count(minutes(1));

         ::parallelization::wait_threads(1_min);

      }

   }

} // namespace hotplugin


