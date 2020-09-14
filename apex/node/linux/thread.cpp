#include "framework.h"
//#include "apex/node/ansios/ansios.h"
#include "_linux.h"



namespace linux
{


//   thread::thread(::layered * pobjectContext) :
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

   UNREFERENCED_PARAMETER(pthread);

}


bool __node_init_thread(::thread * pthread)
{

//   try
//   {
//
//      pthread->m_pimpl->::exception::translator::attach();
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

   //__clear_mq(pthread->type_name(), true);

   return true;

}






















