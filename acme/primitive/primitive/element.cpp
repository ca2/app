﻿// Created by camilo on 2021-08-01 23:42 Thomas Month!! <3ThomasBS__!!
#include "framework.h"


element::~element()
{


}


void element::delete_this()
{
   
   delete this; 

}


#ifdef _DEBUG


i64 element::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   auto c = ++m_countReference;

#if OBJECT_REFERENCE_COUNT_DEBUG

   add_ref_history(pReferer, pszObjRefDbg);

#endif

   return c;

}


i64 element::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   auto c = --m_countReference;

#if OBJECT_REFERENCE_COUNT_DEBUG

   if (c > 0)
   {

      dec_ref_history(pReferer, pszObjRefDbg);

   }

#endif

   return c;

}


i64 element::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   i64 i = decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   if (i == 0)
   {

      delete_this();

   }

   return i;

}


#endif


void element::call_member(::i64 iId)
{

   //return ::success_none;

}


//void element::handle(enum_message emessage, i64 iData, ::element * pelement)
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


::duration element::timeout() const
{

   return 1_min;

}


void element::set_timeout(const ::duration & durationTimeout)
{

   throw interface_only();

}


void element::init_task()
{

   
}


void element::run()
{

   while(true)
   {

      /*auto estatus =*/ step();

      //if(!estatus)
      //{

      //   break;

      //}

   }

   //return ::success;

}


bool element::step()
{

   //return ::error_failed;
   return false;

}


::payload element::realize()
{

   //return ::success;
   return ::success;

}


void element::call_run()
{

   //::e_status estatus;

   //try
   //{

   /*estatus =*/ run();

   //}
   //catch (...)
   //{

   //   estatus = ::error_exception;

   //}

   //return estatus;

}


::element * element::clone() const
{

   throw interface_only();

   return nullptr;

}


void element::set_generic_object_name(const char* pszName)
{

   //return ::success_none;

}


void element::set_application_id(const char* pszApplicationId)
{

   //return error_none;

}


void element::set_library_name(const char* pszLibraryName)
{

   //return error_none;

}


//::e_status element::wait()
//{
//
//   return ::success;
//
//}
//
//
//::e_status element::wait(const class ::wait & wait)
//{
//
//   return ::success;
//
//}


void element::add_composite(::element * pelement OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   //throw ::not_implemented();

   pelement->increment_reference_count();

   //return ::success;

   //return ::error_not_implemented;

}


void element::add_reference(::element* pelement OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   //return ::success_none;

}


void element::release_composite2(::element * pelement OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   //return ::success_none;

}


void element::finalize_composite(::element* pelement OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   //return ::success_none;

}


void element::release_reference(::element* pelement OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   //return ::success_none;

}


::element* element::get_taskpool_container()
{

   return nullptr;

}



::task_pool* element::taskpool()
{

   auto pcontainer = get_taskpool_container();

   if (pcontainer)
   {

      auto ptaskpool = pcontainer->taskpool();

      if (ptaskpool)
      {

         return ptaskpool;

      }

   }

   return nullptr;

}


void element::initialize(::object* pobject)
{

   initialize_matter(pobject);

   on_initialize_object();

}


void element::on_initialize_object()
{


}


void element::initialize_matter(::matter* pmatter)
{

   //return ::success;

}



strsize element::sz_len() const
{

   return strlen(__type_name(this));

}


void element::to_sz(char * sz, strsize len) const
{

   strncpy(sz, __type_name(this), len);

}


bool element::should_run_async() const
{

   return false;

}


::enum_type element::get_payload_type() const
{

   return e_type_element;

}


void element::exchange(stream& s)
{

}


void element::exchange(payload_stream& s)
{

}

stream & element::write(stream& s) const
{

   return s;

}


stream& element::read(stream& s)
{

   return s;

}


//void matter::finish(::property_object * pcontextobjectFinish)
void element::destroy()
{

   //auto estatus = set_finish();

   //if (estatus == error_pending)
   //{

   //   //m_psystem->add_pending_finish(this);

   //   return estatus;

   //}

   ////estatus = on_finish();

   ////if (estatus == error_pending)
   ////{

   ////   //m_psystem->add_pending_finish(this);

   ////   return estatus;

   ////}

   //return estatus;

   //return ::success;


}


void element::destroy_impl_data()
{


}


void element::destroy_os_data()
{


}



void element::on_sequence()
{


}



