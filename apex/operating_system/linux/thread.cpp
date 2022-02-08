#include "framework.h"
//#include "apex/operating_system/ansios/ansios.h"
#include "_linux.h"



namespace linux
{


//   thread::thread(::object * pobject) :
//      ::object(pobject),
//      ::ansios::thread_impl(pobject),
//      ::thread_impl(pobject)
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

   __UNREFERENCED_PARAMETER(pthread);

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






















