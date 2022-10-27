﻿// Created by camilo on 2022-05-08 20:20 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "type.h"
#include "acme/parallelization/single_lock.h"
#include "acme/handler/topic.h"
#include "acme/platform/context.h"
#include "acme/platform/system.h"
#include "acme/primitive/primitive/particle_factory.h"


particle::~particle()
{

   ::release(m_pparticleSynchronization);

}



void particle::initialize(::particle * pparticle)
{

   if (!m_pcontext)
   {

      m_pcontext = pparticle->m_pcontext;

   }

   on_initialize_particle();

}


#ifdef _DEBUG


i64 particle::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   auto c = ++m_countReference;

#if OBJECT_REFERENCE_COUNT_DEBUG

   add_ref_history(pReferer, pszObjRefDbg);

#endif

   return c;

}


i64 particle::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
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


i64 particle::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   i64 i = decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   if (i == 0)
   {

      delete_this();

   }

   return i;

}


#endif


void particle::set_synchronization(::particle *pparticleSynchronization)
{

   if (::is_set(pparticleSynchronization))
   {

      pparticleSynchronization->increment_reference_count();

   }

   ::release(m_pparticleSynchronization);

   m_pparticleSynchronization = pparticleSynchronization;

}


void particle::defer_create_synchronization()
{

   if (!m_pparticleSynchronization)
   {

      set_synchronization(::__create< ::mutex >(this));

   }

}


const char * __sz_defer_skip(const char * psz, const char * pszSkip)
{

   auto len = strlen(pszSkip);

   auto n = strncmp(psz, pszSkip, len);

   if(n)
   {

      return psz;

   }

   return psz + len;

}


const char * particle::topic_text() const
{

   return __sz_defer_skip(typeid(*this).name(), "class ");

}


//string matter::class_title() const
//{
//
//   auto strTypeName =  __type_name(this);
//
//   auto findLastColonColon = strTypeName.reverse_find("::");
//
//   if(findLastColonColon < 0)
//   {
//
//      return strTypeName;
//
//   }
//
//   return strTypeName.Mid(findLastColonColon + 2);
//
//}


const char * particle::class_title() const
{

   auto pszName =  typeid(*this).name();

   auto pszLastColon = strrchr(pszName, ':');

   if(!pszLastColon)
   {

      return pszName;

   }

   return pszLastColon + 1;

}



enum_type particle::get_payload_type() const
{

   return e_type_element;

}


void particle::destroy()
{


}


void particle::delete_this()
{

   if (!(m_eflagElement & e_flag_statically_allocated))
   {

      delete this;

   }

}




//void particle::initialize(::particle * pparticle)
//{
//
//   ///initialize_matter(pparticle);
//
//   on_initialize_particle();
//
//}


void particle::on_initialize_particle()
{


}

//void particle::initialize_matter(::matter * pmatter)
//{
//
//   //return ::success;
//
//}


//void particle::run()
//{
//
//
//}


::acme::application * particle::get_context_application()
{

   if (acmesystem()->m_pacmeapplicationMain)
   {

      return acmesystem()->m_pacmeapplicationMain;

   }

   if (acmesystem()->m_pacmeapplicationStartup)
   {

      return acmesystem()->m_pacmeapplicationStartup;

   }

   return nullptr;

}


::acme_file * particle::acmefile()
{

   return m_pcontext->acmefile();

}


::acme_path * particle::acmepath()
{

   return m_pcontext->acmepath();

}


::acme_directory * particle::acmedirectory()
{

   return m_pcontext->acmedirectory();

}


::acme::node * particle::acmenode()
{

   return m_pcontext->acmenode();

}


::acme::system * particle::acmesystem()
{

   return m_pcontext->acmesystem();

}


void particle::handle(::topic * ptopic, ::context * pcontext)
{


}


::topic_pointer particle::create_topic(const ::atom & atom)
{

   auto ptopic = __new(::topic(atom));

   ptopic->m_pcontext = m_pcontext;

   return ::move(ptopic);

}


::extended_topic_pointer particle::create_extended_topic(const ::atom & atom)
{

   return acmesystem()->create_extended_topic(atom);

}



void particle::install_message_routing(::channel * pchannel)
{


}


void particle::init_task()
{


}


void particle::call_run()
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


void particle::run()
{

   while (true)
   {

      /*auto estatus =*/ step();

      //if(!estatus)
      //{

      //   break;

      //}

   }

   //return ::success;

}


bool particle::step()
{

   //return ::error_failed;
   return false;

}


void particle::on_sequence()
{


}


strsize particle::sz_len() const
{

   return strlen(__type_name(this)) + 1;

}


void particle::to_sz(char * sz, strsize len) const
{

   strncpy(sz, __type_name(this), len);

}



enum_trace_category particle::trace_category() const
{

   return e_trace_category_general;

}


enum_trace_category particle::trace_category(const ::particle * pparticle) const
{

   return pparticle->trace_category();

}



void particle::trace_arguments(enum_trace_level etracelevel, enum_trace_category etracecategory, const char * pszFormat, va_list & arguments)
{


   tracer(m_pcontext, etracelevel, etracecategory).format_output_arguments(pszFormat, arguments);

}


void particle::trace_log_information_arguments(enum_trace_category etracecategory, const char * pszFormat, va_list & arguments)
{

   tracer(m_pcontext, e_trace_level_information, etracecategory).format_output_arguments(pszFormat, arguments);

}


void particle::trace_log_warning_arguments(enum_trace_category etracecategory, const char * pszFormat, va_list & arguments)
{

   tracer(m_pcontext, e_trace_level_warning, etracecategory).format_output_arguments(pszFormat, arguments);

}


void particle::trace_log_error_arguments(enum_trace_category etracecategory, const char * pszFormat, va_list & arguments)
{

   tracer(m_pcontext, e_trace_level_error, etracecategory).format_output_arguments(pszFormat, arguments);

}


void particle::trace_log_fatal_arguments(enum_trace_category etracecategory, const char * pszFormat, va_list & arguments)
{

   tracer(m_pcontext, e_trace_level_fatal, etracecategory).format_output_arguments(pszFormat, arguments);

}




void particle::trace_arguments(enum_trace_level etracelevel, const char * pszFormat, va_list & arguments)
{


   tracer(m_pcontext, etracelevel, trace_category()).format_output_arguments(pszFormat, arguments);

}


void particle::trace_log_information_arguments(const char * pszFormat, va_list & arguments)
{

   tracer(m_pcontext, e_trace_level_information, trace_category()).format_output_arguments(pszFormat, arguments);

}


void particle::trace_log_warning_arguments(const char * pszFormat, va_list & arguments)
{

   tracer(m_pcontext, e_trace_level_warning, trace_category()).format_output_arguments(pszFormat, arguments);

}


void particle::trace_log_error_arguments(const char * pszFormat, va_list & arguments)
{

   tracer(m_pcontext, e_trace_level_error, trace_category()).format_output_arguments(pszFormat, arguments);

}


void particle::trace_log_fatal_arguments(const char * pszFormat, va_list & arguments)
{

   tracer(m_pcontext, e_trace_level_fatal, trace_category()).format_output_arguments(pszFormat, arguments);

}


void particle::trace(enum_trace_level etracelevel, enum_trace_category etracecategory, const char * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   trace_arguments(etracelevel, etracecategory, psz, arguments);

   va_end(arguments);

}


void particle::trace_log_information(enum_trace_category etracecategory, const char * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   trace_arguments(e_trace_level_information, etracecategory, psz, arguments);

   va_end(arguments);

}


void particle::trace_log_warning(enum_trace_category etracecategory, const char * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   trace_arguments(e_trace_level_warning, etracecategory, psz, arguments);

   va_end(arguments);

}


void particle::trace_log_error(enum_trace_category etracecategory, const char * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   trace_arguments(e_trace_level_error, etracecategory, psz, arguments);

   va_end(arguments);

}


void particle::trace_log_fatal(enum_trace_category etracecategory, const char * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   trace_arguments(e_trace_level_fatal, etracecategory, psz, arguments);

   va_end(arguments);

}


void particle::trace(enum_trace_level etracelevel, const char * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   trace_arguments(etracelevel, trace_category(), psz, arguments);

   va_end(arguments);

}


void particle::trace_log_information(const char * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   trace_arguments(e_trace_level_information, trace_category(), psz, arguments);

   va_end(arguments);

}


void particle::trace_log_warning(const char * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   trace_arguments(e_trace_level_warning, trace_category(), psz, arguments);

   va_end(arguments);

}


void particle::trace_log_error(const char * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   trace_arguments(e_trace_level_error, trace_category(), psz, arguments);

   va_end(arguments);

}


void particle::trace_log_fatal(const char * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   trace_arguments(e_trace_level_fatal, trace_category(), psz, arguments);

   va_end(arguments);

}






//particle::particle(const char * lpszName)
//{
//
//   m_bOwner = true;
//
//#ifdef WINDOWS
//
//   m_hsync = nullptr;
//
//#endif
//
//   if (lpszName == nullptr)
//   {
//
//      m_pszName = nullptr;
//
//   }
//   else
//   {
//
//      m_pszName = strdup(lpszName);
//
//   }
//
//}


//#ifdef WINDOWS
//
//
//particle::particle(HSYNC hsyncobject, const char * lpszName) :
//   m_hsync(hsyncobject)
//{
//
//   m_bOwner = false;
//
//   if (lpszName == nullptr)
//   {
//
//      m_pszName = nullptr;
//
//   }
//   else
//   {
//
//      m_pszName = strdup(lpszName);
//
//   }
//
//}
//
//
//#endif


//particle::~particle()
//{
//
//#ifdef WINDOWS
//
//   if (m_bOwner && m_hsync != nullptr)
//   {
//
//      ::CloseHandle((HANDLE) m_hsync);
//
//      m_hsync = nullptr;
//
//   }
//
//#endif
//
//   //if (m_pszName != nullptr)
//   //{
//
//   //   ::free(m_pszName);
//
//   //}
//
//}


::e_status particle::lock()
{

   return wait();

}


::e_status particle::lock(const class ::wait & wait)
{

   return this->wait(wait);

}


void particle::_lock()
{

   _wait();

}


bool particle::_lock(const class ::wait & wait)
{

   return this->_wait(wait);

}


void particle::_wait()
{

   _wait(::duration::infinite());

}


::e_status particle::wait()
{

   auto ptask = ::get_task();

   if (::is_null(ptask))
   {

      ptask = ::get_system();

   }

   if (::is_null(ptask))
   {

      _wait();

      return ::success;

   }

   while (true)
   {

      auto bOk =  _wait(100_ms);

      if(bOk)
      {

         return ::success;

      }

      if (!ptask->task_get_run())
      {

         return error_failed;

      }

   }

}


::e_status particle::wait(const class ::wait & wait)
{

   if (wait < 200_ms)
   {

      auto bOk = this->_wait(wait);

      if(!bOk)
      {

         return error_wait_timeout;

      }

      return ::success;

   }

   if(wait.is_infinite())
   {

      return this->wait();

   }

   auto ptask = ::get_task();

   if (::is_null(ptask))
   {

      ptask = ::get_system();

   }

   if (::is_null(ptask))
   {

      auto bOk = this->_wait(wait);

      if(!bOk)
      {

         return error_wait_timeout;

      }

      return ::success;

   }

   auto waitStart = ::wait::now();

   while(true)
   {

      auto waitElapsed = waitStart.elapsed();

      if (waitElapsed > wait)
      {

         return error_wait_timeout;

      }

      auto waitNow = ::minimum(waitElapsed, 100_ms);

      bool bOk = _wait(waitNow);

      if (bOk)
      {

         return ::success;

      }

      if(!ptask->task_get_run())
      {

         return error_failed;

      }

   }

}


void particle::unlock()
{

   ///return false;

}


void particle::unlock(::i32 /* lCount */, ::i32 * /* pPrevCount=nullptr */)
{

   //return false;

}


bool particle::_wait(const class ::wait & wait)
{

#ifdef WINDOWS

   if (!m_hsync)
   {

      return true;

   }

   //auto milliseconds = wait.operator u32();
   //unsigned int ui;
   //if (wait.m_d <= 0.)
   //{
   //   ui = 0;

   //}
   //else if (wait.m_d >= 0xffffffffu)
   //{

   //   ui = 0xffffffffu;
   //}
   //else
   //{

   //   ui = (::u32) (wait.m_d * 1'000.0);

   //}

   ////return (::u32)m_d <= 0. ? 0 : (m_d >= 0xffffffffu ? 0xffffffffu : (::u32)(m_d * 1'000.0));
   //if (milliseconds < 1'000'000'000)
   //{

   //   output_debug_string("milliseconds < 1'000'000'000");

   //}

   auto windowsWaitResult = ::WaitForSingleObjectEx(m_hsync, wait, false);

   auto estatus = windows_wait_result_to_status(windowsWaitResult);

   if (estatus == error_wait_timeout)
   {

      return false;

   }
   else if (estatus == signaled_base)
   {

#ifdef _DEBUG

      auto pmutex = dynamic_cast < ::pointer< ::mutex >> (this);

      if (::is_set(pmutex))
      {

         pmutex->m_strThread = ::task_get_name();
         pmutex->m_itask = ::get_current_itask();
         ::output_debug_string("");

      }

#endif

      return true;

   }
   else
   {

      throw ::exception(estatus);

      return false;

   }

#endif

   throw ::exception(error_interface_only);

   return false;

}


void particle::acquire_ownership()
{

   //m_bOwner = true;

   set_own_synchronization();

}


[[maybe_unused]] void particle::release_ownership()
{

   //m_bOwner = false;
   unset_own_synchronization();

}


//void particle::assert_ok() const
//{
//
//   matter::assert_ok();
//
//}


//void particle::dump(dump_context & dumpcontext) const
//{
//
//#ifdef WINDOWS
//   dumpcontext << "Object ";
//   dumpcontext << m_hsync;
//#endif
//
//   dumpcontext << " named " << m_pszName << "\n";
//
//   matter::dump(dumpcontext);
//
//}


//HSYNC particle::hsync() const
//{
//
//#ifdef WINDOWS
//
//   return m_hsync;
//
//#else
//
//   return (particle *) this;
//
//#endif
//
//}


//bool particle::unlock(::i32 /* lCount */, LPLONG /* pPrevCount=nullptr */)
//
//{
//
//   return true;
//
//}


//bool particle::unlock()
//{
//
//   return true;
//
//}




void particle::init_wait()
{


}


void particle::exit_wait()
{


}




//particle_result particle::wait()
//{
//
//   return wait(duration::infinite());
//
//}


//sync_callback::~sync_callback()
//{
//}


bool particle::is_locked() const
{

   // CRITICAL SECTIONS does *NOT* support is locked and timed locks
   ASSERT(dynamic_cast <critical_section *> (const_cast <particle *> (this)) == nullptr);

   single_lock synchronouslock(const_cast <particle *> (this));

   bool bWasLocked = false;

   try
   {

      synchronouslock.lock(duration::zero());

   }
   catch (...)
   {

      bWasLocked = true;

   }

   if (!bWasLocked)
   {

      synchronouslock.unlock();

   }

   return bWasLocked;

}

//
//particle_lock::~particle_lock()
//{
//
//
//}
//
//
//


void particle::set_finish()
{


}



