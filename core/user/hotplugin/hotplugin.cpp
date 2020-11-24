#include "framework.h"

//#include "hotplugin.h"


namespace hotplugin
{


   ::aura::system * g_paurasystem = nullptr;


   int g_iSystemCount = 0;


   u32 c_cdecl base_system_main(LPVOID pVoid);



   CLASS_DECL_BASE ::aura::system * get_aura_system()
   {

      return g_paurasystem;

   }


   CLASS_DECL_BASE bool defer_start_base_system()
   {

      if(g_paurasystem != nullptr)
         return true;

      g_iSystemCount++;

      __throw(todo(nullptr));

//      try
//      {

//         g_paxissystem = new ::axis::system(nullptr, );

//         if(file_exists(::dir::system() / "config\\plugin\\npca2_beg_debug_box.txt"))
//         {

//            debug_box("hotplugin boxmain NP_Initialize","ZZZzzz hotplugin box",e_message_box_ok);

//         }
//         if(file_exists(::dir::system() / "config\\plugin\\npca2_beg_sleep.txt"))
//         {

//            millis_sleep(10000);

//         }

//         ::set_thread(g_paxissystem);

//         g_paxissystem->m_bMatterFromHttpCache = true;

//         g_paxissystem->m_bSystemSynchronizedCursor = false;

// #ifdef WINDOWS

//         g_paxissystem->m_hinstance = (HINSTANCE)get_hinstance();

// #endif

//         xxdebug_box("box1","box1",MB_ICONINFORMATION);

// #ifdef WINDOWS

//         set_main_hthread((hthread_t) GetCurrentThread());

//         set_main_ithread(GetCurrentThreadId());

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


   //u32 c_cdecl base_system_main(LPVOID pVoid)

   //{

   //   //i32 iReturnCode = 0;

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


   CLASS_DECL_BASE HINSTANCE get_hinstance()
   {

      return g_hinstance;

   }


   CLASS_DECL_BASE void set_hinstance(HINSTANCE hinstance)
   {

      g_hinstance = hinstance;

   }


#endif


   CLASS_DECL_BASE void defer_stop_base_system()
   {

      g_iSystemCount--;

      if(g_iSystemCount == 0)
      {

         if(g_paurasystem != nullptr)
         {

            g_paurasystem->finalize();

            g_paurasystem = nullptr;

         }

         //__wait_threading_count(minutes(1));

         ::parallelization::wait_threads(1_min);

      }

   }

} // namespace hotplugin


