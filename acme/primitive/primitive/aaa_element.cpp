// Created by camilo on 2021-08-01 23:42 Thomas Month!! <3ThomasBS__!!
#include "framework.h"
#include "element.h"
#include "acme/exception/interface_only.h"
#include "acme/primitive/primitive/payload.h"


//element::~element()
//{
//
//
//}


//void element::handle(enum_message emessage, i64 iData, ::particle * pparticle)
//{
//
//   return ::success;
//
//}
//


//void element::handle(::topic * ptopic, ::context * pcontext)
//{
//
//
//}


//void element::handle(::message::message * pmessage)
//{
//
//
//}


//::duration element::timeout() const
//{
//
//   return 1_min;
//
//}
//
//
//void element::set_timeout(const ::duration & durationTimeout)
//{
//
//   throw interface_only();
//
//}
//
//
//
//::payload element::realize()
//{
//
//   //return ::success;
//   return ::success;
//
//}
//
//
////void element::call_run()
////{
////
////   //::e_status estatus;
////
////   //try
////   //{
////
////   /*estatus =*/ run();
////
////   //}
////   //catch (...)
////   //{
////
////   //   estatus = ::error_exception;
////
////   //}
////
////   //return estatus;
////
////}
//
//
//::particle * element::clone() const
//{
//
//   throw interface_only();
//
//   return nullptr;
//
//}
//
//
//void element::set_generic_object_name(const char* pszName)
//{
//
//   //return ::success_none;
//
//}
//
//
//void element::set_application_id(const char* pszApplicationId)
//{
//
//   //return error_none;
//
//}
//
//
//void element::set_library_name(const char* pszLibraryName)
//{
//
//   //return error_none;
//
//}
//
//
////::e_status element::wait()
////{
////
////   return ::success;
////
////}
////
////
////::e_status element::wait(const class ::wait & wait)
////{
////
////   return ::success;
////
////}
//
//
////void element::add_composite(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
////{
////
////   //throw ::not_implemented();
////
////   pelement->increment_reference_count();
////
////   //return ::success;
////
////   //return ::error_not_implemented;
////
////}
////
////
////void element::add_reference(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
////{
////
////   //return ::success_none;
////
////}
////
////
////void element::release_composite2(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
////{
////
////   //return ::success_none;
////
////}
////
////
////void element::finalize_composite(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
////{
////
////   //return ::success_none;
////
////}
////
////
////void element::release_reference(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
////{
////
////   //return ::success_none;
////
////}
//
//
//::particle* element::get_taskpool_container()
//{
//
//   return nullptr;
//
//}
//
//
//
//::task_pool* element::taskpool()
//{
//
//   auto pcontainer = get_taskpool_container();
//
//   if (pcontainer)
//   {
//
//      auto ptaskpool = pcontainer->taskpool();
//
//      if (ptaskpool)
//      {
//
//         return ptaskpool;
//
//      }
//
//   }
//
//   return nullptr;
//
//}
//
//
//
//
//
//
//
//
//bool element::should_run_async() const
//{
//
//   return false;
//
//}
//
//
//::enum_type element::get_payload_type() const
//{
//
//   return e_type_element;
//
//}
//
//
////void element::exchange(stream& s)
////{
////
////}
////
////
////void element::exchange(payload_stream& s)
////{
////
////}
//
////stream & element::write(stream& s) const
////{
////
////   return s;
////
////}
////
////
////stream& element::read(stream& s)
////{
////
////   return s;
////
////}
//
//
////void matter::finish(::property_object * pcontextobjectFinish)
//void element::destroy()
//{
//
//   //auto estatus = set_finish();
//
//   //if (estatus == error_pending)
//   //{
//
//   //   //acmesystem()->add_pending_finish(this);
//
//   //   return estatus;
//
//   //}
//
//   ////estatus = on_finish();
//
//   ////if (estatus == error_pending)
//   ////{
//
//   ////   //acmesystem()->add_pending_finish(this);
//
//   ////   return estatus;
//
//   ////}
//
//   //return estatus;
//
//   //return ::success;
//
//
//}
//
//
//void element::destroy_impl_data()
//{
//
//
//}
//
//
//void element::destroy_os_data()
//{
//
//
//}
//
//
//
//
//
//
////void element::write(::binary_stream < FILE > & stream) const
////{
////
////   throw interface_only();
////
////}
////
////
////void element::read(::binary_stream < FILE > & stream)
////{
////
////   throw interface_only();
////
////}
//
//
//
