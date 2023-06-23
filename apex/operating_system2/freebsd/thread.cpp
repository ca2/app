#include "framework.h"
//#include "apex/operating_system/ansios/ansios.h"
#include "_freebsd.h"



namespace linux
{


//   thread::thread(::particle * pparticle) :
//      ::object(pparticle),
//      ::ansios::thread_impl(pparticle),
//      ::thread_impl(pparticle)
//   {
//
//
//   }
//
//
//   thread::~thread()
//   {
//
//
//   }


} // namespace linux


void __node_init_app_thread(::thread * pthread)
{

   UNREFERENCED_PARAMETER(pthread);

}


bool __node_init_thread(::thread * pthread)
{

//   try
//   {
//
//      pthread->m_pimpl->::exception_translator::attach();
//
//   }
//   catch(...)
//   {
//
//      return false;
//
//   }

   return true;

}


bool __node_term_thread(::thread * pthread)
{

   //__clear_mq(__type_name(pthread), true);

   return true;

}






















