#include "platform.h"
//#include "acme/node/ansios/ansios.h"
#include "_sunos.h"
#include "acme/operating_system/posix/shared_memory.h"

//
//namespace linux
//{
//
//   ::i32 function()
//   {
//      return 0;
//   }
//
//
////   ::u32 GetTempPath(string & str)
////   {
////      return ::GetTempPathW(MAX_PATH * 8, wstring_adaptor(str, MAX_PATH * 8));
////   }
//
//} // namespace linux
//



//void CLASS_DECL_ACME __lnx_term()
//{
//
//
//
//}
//


//void motif_factory(::factory::factory * pfactory);

void sunos_factory(::factory::factory * pfactory)
{

  // motif_factory(pfactory);

}








void operating_system_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item< ::posix::shared_memory, ::shared_memory>();

}




//~ ::u32 get_tick()
//~ {
   //~ timeval ts;
   //~ gettimeofday(&ts,0);
   //~ return (ts.tv_sec * 1000 + (ts.tv_usec / 1000)) % 0xffffffffu;

//~ }

//~ thread_int_ptr < ::u32 > g_dwLastError;

//~ CLASS_DECL_ACME ::u32 get_last_error()
//~ {

   //~ ::time g_tickLastError;

//~ }

//~ CLASS_DECL_ACME ::u32 set_last_error(::u32 dw)
//~ {

   //~ ::u32 dwLastError = g_dwLastError;

   //~ g_dwLastError = dw;

   //~ return dwLastError;

//~ }


//~ CLASS_DECL_ACME bool _istlead(::i32 ch)
//~ {

   //~ return false;

//~ }


//~ void sleep(::u32 dwMillis)
//~ {
   //~ timespec t;
   //~ t.tv_sec = dwMillis / 1000;
   //~ t.tv_nsec = (dwMillis % 1000) * 1000 * 1000;
   //~ nanosleep(&t, nullptr);
//~ }







//~ void informationf(const ::scoped_string & scopedstr)
//~ {

   //~ informationf(scopedstr);

//~ }
