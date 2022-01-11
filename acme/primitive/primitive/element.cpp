// Created by camilo on 2021-08-01 23:42 Thomas Month!! <3ThomasBS__!!
#include "framework.h"


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

   return ::success_none;

}


//void element::handle(enum_message emessage, i64 iData, ::element * pelement)
//{
//
//   return ::success;
//
//}
//


void element::handle(::subject * psubject, ::context * pcontext)
{


}


void element::handle(::message::message * pmessage)
{


}


DURATION element::timeout() const
{

   return { .m_iSecond = 64 }; // : // 64s ~ 1 minute

}


void element::operator()()
{

   void estatus;

   try
   {

      estatus = run();

   }
   catch (...)
   {

      estatus = ::error_exception;

   }

   return estatus;

}


void element::operator()(::message::message * pmessage)
{


}


void element::operator()(const ::payload & payload)
{

}


void element::run()
{

   while(true)
   {

      auto estatus = step();

      if(!estatus)
      {

         break;

      }

   }

   return ::success;

}


void element::step()
{

   return ::error_failed;

}


::payload element::realize()
{

   return ::success;

}


void element::set_generic_object_name(const char* pszName)
{

   return ::success_none;

}


void element::set_application_id(const char* pszApplicationId)
{

   return error_none;

}


void element::set_library_name(const char* pszLibraryName)
{

   return error_none;

}


void element::wait()
{

   return error_failed;

}


void element::wait(const ::duration & duration)
{

   return error_failed;

}


void element::add_composite(::element * pelement OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   //__throw(error_not_implemented);

   pelement->increment_reference_count();

   return ::success;

   //return ::error_not_implemented;

}


void element::add_reference(::element* pelement OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   return ::success_none;

}


void element::release_composite2(::element * pelement OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   return ::success_none;

}


void element::finalize_composite(::element* pelement OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   return ::success_none;

}


void element::release_reference(::element* pelement OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   return ::success_none;

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

   auto estatus = initialize_matter(pobject);

   return estatus;

}



void element::initialize_matter(::matter* pmatter)
{

   return ::success;

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

   return ::success;


}



