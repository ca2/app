// Created by camilo on 2022-05-08 20:20 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "type.h"
#include "factory.h"
#include "acme/exception/interface_only.h"
#include "acme/handler/extended_topic.h"
#include "acme/handler/topic.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/acme.h"
#include "acme/platform/application.h"
#include "acme/platform/context.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/user/nano/nano.h"
//#include "acme/primitive/primitive/payload.h"


CLASS_DECL_ACME void do_tasks();


particle::~particle()
{

#if OBJECT_REFERENCE_COUNT_DEBUG

   if (::is_set(m_pobjectreferencecountdebug))
   {

      delete m_pobjectreferencecountdebug;

   }

#endif
   //::release(m_pparticleSynchronization);

}


void particle::initialize(::particle * pparticle)
{

   if (!m_pcontext)
   {

      m_pcontext = pparticle->m_pcontext;

      on_initialize_particle();

   }

}


#ifdef _DEBUG


i64 particle::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEFINITION)
{

   auto c = ++m_countReference;

#if OBJECT_REFERENCE_COUNT_DEBUG

   add_ref_history(pReferer, pszObjRefDbg);

#endif

   return c;

}


i64 particle::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEFINITION)
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


i64 particle::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEFINITION)
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

   m_pparticleSynchronization.release();

   m_pparticleSynchronization = pparticleSynchronization;

}


void particle::defer_create_synchronization()
{

   if (!m_pparticleSynchronization)
   {

      set_synchronization(::__create< ::mutex >(this));

   }

}


#ifdef WINDOWS


hsynchronization particle::get_synchronization_handle()
{

   return nullptr;

}


#endif


const char * __sz_defer_skip(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrSkip)
{

   auto len = scopedstrSkip.size();

   auto n = ansi_ncmp(scopedstr.begin(), scopedstrSkip.begin(), len);

   if(n)
   {

      return scopedstr.begin();

   }

   return scopedstr.begin() + len;

}


const char * particle::topic_text() const
{

   return __sz_defer_skip(typeid(*this).name(), "class ");

}


//string matter::class_title() const
//{
//
//   auto strTypeName =  ::type(this).name();
//
//   auto findLastColonColon = strTypeName.rear_find("::");
//
//   if(findLastColonColon < 0)
//   {
//
//      return strTypeName;
//
//   }
//
//   return strTypeName.substr(findLastColonColon + 2);
//
//}


//const char * particle::raw_class_title() const
//{
//
//   auto pszName =  typeid(*this).name();
//
//   auto pszLastColon = strrchr(pszName, ':');
//
//   if(!pszLastColon)
//   {
//
//      return pszName;
//
//   }
//
//   return pszLastColon + 1;
//
//}



enum_type particle::get_payload_type() const
{

   return e_type_element;

}


//void particle::destroy()
//{
//
//
//}


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


::acme::application * particle::application() const
{

   return m_pcontext ? m_pcontext->m_pacmeapplication : nullptr;

}


//::aura::application * particle::auraapplication() const
//{
//
//   return m_pcontext && m_pcontext->m_pacmeapplication ? m_pcontext->m_pacmeapplication->m_pauraapplication : nullptr;
//
//}


::acme::session* particle::session() const
{

   return m_pcontext ? m_pcontext->m_pacmesession : nullptr;

}


::acme_file * particle::acmefile() const
{

   return m_pcontext->acmefile();

}


::acme_path * particle::acmepath() const
{

   return m_pcontext->acmepath();

}


::acme_directory * particle::acmedirectory() const
{

   return m_pcontext->acmedirectory();

}


::acme::node * particle::acmenode() const
{

   return m_pcontext->acmenode();

}


::acme::system * particle::system() const
{

   return ::is_set(m_pcontext) ? m_pcontext->system() : nullptr;

}


::acme::context* particle::acmecontext() const
{

   return m_pcontext;

}


::apex::context* particle::apexcontext() const
{

   return m_pcontext ? m_pcontext->m_papexcontext : nullptr;

}


::aura::context* particle::auracontext() const
{

   return m_pcontext ? m_pcontext->m_pauracontext : nullptr;

}


::context_image* particle::context_image() const
{

   return m_pcontext ? m_pcontext->context_image() : nullptr;

}


//::platform::platform * particle::platform() const
//{
//
//   return m_pcontext->platform();
//
//}


::datetime::datetime* particle::datetime() const
{

   return system()->datetime();

}


::url::url* particle::url() const
{

   return system()->url();

}


::os_context * particle::os_context() const
{

   return m_pcontext->os_context();

}


::nano::nano * particle::nano() const
{

   return system()->nano();

}

::crypto::crypto* particle::crypto() const
{

   return system()->crypto();

}


::apex::application * particle::apexapplication() const
{

   auto papplication = application();

   return ::is_set(papplication) ? papplication->m_papexapplication : nullptr;

}


::dir_context * particle::dir() const
{

   return m_pcontext->dir();

}


::dir_system * particle::dirsystem() const
{

   return m_pcontext->dirsystem();

}


::file_context * particle::file() const
{

   return m_pcontext->file();

}


::file_system * particle::filesystem() const
{

   return m_pcontext->filesystem();

}


::factory::factory_pointer & particle::factory() const
{

   return platform()->factory();

}


::factory::factory_pointer & particle::factory(const ::string & strLibrary) const
{

   return platform()->factory(strLibrary);

}


::factory::factory_pointer& particle::factory(const ::string& strComponent, const ::string& strImplementation) const
{

   return platform()->factory(strComponent, strImplementation);

}


void particle::handle(::topic * ptopic, ::context * pcontext)
{


}


bool particle::_is_set() const
{

   return true;

}


bool particle::_is_ok() const
{

   return has_ok_flag();

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

   return ansi_len(::type(this).name()) + 1;

}


void particle::to_sz(char * sz, strsize len) const
{

   ansi_ncpy(sz, ::type(this).name(), len);

}



enum_trace_category particle::trace_category() const
{

   return e_trace_category_general;

}


enum_trace_category particle::trace_category(const ::particle * pparticle) const
{

   return pparticle->trace_category();

}



//void particle::trace_arguments(enum_trace_level etracelevel, enum_trace_category etracecategory, const ::ansi_character * pszFormat, va_list & arguments)
//{
//
//
//   get_tracer()(m_pcontext, etracelevel, etracecategory).format_output_arguments(pszFormat, arguments);
//
//}


//void particle::trace_log_information_arguments(enum_trace_category etracecategory, const ::ansi_character * pszFormat, va_list & arguments)
//{
//
//   get_tracer()(m_pcontext, e_trace_level_information, etracecategory).format_output_arguments(pszFormat, arguments);
//
//}
//
//
//void particle::trace_log_warning_arguments(enum_trace_category etracecategory, const ::ansi_character * pszFormat, va_list & arguments)
//{
//
//   get_tracer()(m_pcontext, e_trace_level_warning, etracecategory).format_output_arguments(pszFormat, arguments);
//
//}
//
//
//void particle::trace_log_error_arguments(enum_trace_category etracecategory, const ::ansi_character * pszFormat, va_list & arguments)
//{
//
//   get_tracer()(m_pcontext, e_trace_level_error, etracecategory).format_output_arguments(pszFormat, arguments);
//
//}
//
//
//void particle::trace_log_fatal_arguments(enum_trace_category etracecategory, const ::ansi_character * pszFormat, va_list & arguments)
//{
//
//   get_tracer()(m_pcontext, e_trace_level_fatal, etracecategory).format_output_arguments(pszFormat, arguments);
//
//}
//
//
//
//
//void particle::trace_arguments(enum_trace_level etracelevel, const ::ansi_character * pszFormat, va_list & arguments)
//{
//
//   get_tracer()(m_pcontext, etracelevel, trace_category()).format_output_arguments(pszFormat, arguments);
//
//}
//
//
//void particle::trace_log_information_arguments(const ::ansi_character * pszFormat, va_list & arguments)
//{
//
//   get_tracer()(m_pcontext, e_trace_level_information, trace_category()).format_output_arguments(pszFormat, arguments);
//
//}
//
//
//void particle::trace_log_warning_arguments(const ::ansi_character * pszFormat, va_list & arguments)
//{
//
//   get_tracer()(m_pcontext, e_trace_level_warning, trace_category()).format_output_arguments(pszFormat, arguments);
//
//}
//
//
//void particle::trace_log_error_arguments(const ::ansi_character * pszFormat, va_list & arguments)
//{
//
//   get_tracer()(m_pcontext, e_trace_level_error, trace_category()).format_output_arguments(pszFormat, arguments);
//
//}
//
//
//void particle::trace_log_fatal_arguments(const ::ansi_character * pszFormat, va_list & arguments)
//{
//
//   get_tracer()(m_pcontext, e_trace_level_fatal, trace_category()).format_output_arguments(pszFormat, arguments);
//
//}


//void particle::trace(enum_trace_level etracelevel, enum_trace_category etracecategory, const ::ansi_character * pszFormat, ...)
//{
//
//   va_list arguments;
//
//   va_start(arguments, pszFormat);
//
//   trace_arguments(etracelevel, etracecategory, pszFormat, arguments);
//
//   va_end(arguments);
//
//}
//
//
//void particle::trace_log_information(enum_trace_category etracecategory, const ::ansi_character * pszFormat, ...)
//{
//
//   va_list arguments;
//
//   va_start(arguments, pszFormat);
//
//   trace_arguments(e_trace_level_information, etracecategory, pszFormat, arguments);
//
//   va_end(arguments);
//
//}
//
//
//void particle::trace_log_warning(enum_trace_category etracecategory, const ::ansi_character * pszFormat, ...)
//{
//
//   va_list arguments;
//
//   va_start(arguments, pszFormat);
//
//   trace_arguments(e_trace_level_warning, etracecategory, pszFormat, arguments);
//
//   va_end(arguments);
//
//}
//
//
//void particle::trace_log_error(enum_trace_category etracecategory, const ::ansi_character * pszFormat, ...)
//{
//
//   va_list arguments;
//
//   va_start(arguments, pszFormat);
//
//   trace_arguments(e_trace_level_error, etracecategory, pszFormat, arguments);
//
//   va_end(arguments);
//
//}
//
//
//void particle::trace_log_fatal(enum_trace_category etracecategory, const ::ansi_character * pszFormat, ...)
//{
//
//   va_list arguments;
//
//   va_start(arguments, pszFormat);
//
//   trace_arguments(e_trace_level_fatal, etracecategory, pszFormat, arguments);
//
//   va_end(arguments);
//
//}


class tracer * particle::tracer() const
{

   auto ptask = get_task();

   if (!ptask)
   {

      auto pplatform = ::platform::get();

      if (::is_set(pplatform))
      {

         auto pcontext = pplatform->m_pcontext;

         if (::is_set(pcontext))
         {


            return pcontext;

         }

      }

   }

   return ptask;

}


::trace_statement particle::trace_statement() const
{

   auto ptracer = this->tracer();

   auto statement = ::transfer(::trace_statement(ptracer));

   trace_statement_prefix(statement);

   return ::transfer(statement);

}


::trace_statement & particle::trace_statement_prefix(::trace_statement & statement) const
{

   return statement;

}


::trace_statement particle::log_statement() const
{

   return ::transfer(trace_statement()((::particle *) this));

}


::trace_statement particle::information() const
{

   return ::transfer(trace_statement()(e_trace_level_information));

}


::trace_statement particle::warning() const
{

   return ::transfer(trace_statement()(e_trace_level_warning));

}


::trace_statement particle::error() const
{

   return ::transfer(trace_statement()(e_trace_level_error));

}


::trace_statement particle::fatal() const
{

   return ::transfer(trace_statement()(e_trace_level_fatal));

}


void particle::formatf_trace(enum_trace_level etracelevel, const ::ansi_character * pszFormat, va_list & arguments) const
{

   auto statement = ::transfer(log_statement());

   statement(etracelevel)(trace_category());

   statement.formatf_output_arguments(pszFormat, arguments);

}


void particle::tracef(enum_trace_level etracelevel, const ::ansi_character * pszFormat, ...) const
{

    va_list arguments;

    va_start(arguments, pszFormat);

    {

       auto statement = ::transfer(log_statement());

       statement(etracelevel)(trace_category());

       statement.formatf_output_arguments(pszFormat, arguments);

    }

    va_end(arguments);

 }


void particle::informationf(const ::ansi_character * pszFormat, ...) const
{

   va_list arguments;

   va_start(arguments, pszFormat);

   formatf_trace(e_trace_level_information, pszFormat, arguments);

   va_end(arguments);

}


void particle::warningf(const ::ansi_character * pszFormat, ...) const
{

   va_list arguments;

   va_start(arguments, pszFormat);

   formatf_trace(e_trace_level_warning, pszFormat, arguments);

   va_end(arguments);

}


void particle::errorf(const ::ansi_character * pszFormat, ...) const
{

   va_list arguments;

   va_start(arguments, pszFormat);

   formatf_trace(e_trace_level_error, pszFormat, arguments);

   va_end(arguments);

}


void particle::fatalf(const ::ansi_character * pszFormat, ...) const
{

   va_list arguments;

   va_start(arguments, pszFormat);

   formatf_trace(e_trace_level_fatal, pszFormat, arguments);

   va_end(arguments);

}


//trace_statement particle::trace(enum_trace_level etracelevel)
//{ 
//
//   auto & tracer = get_tracer();
//   
//   tracer(m_pcontext, etracelevel, trace_category()); 
//
//   return tracer;
//
//}


//trace_statement particle::trace_log_information()
//{
//   
//   auto & tracer = get_tracer();
//
//   tracer(m_pcontext, e_trace_level_information, trace_category());
//
//   return tracer;
//
//}
//
//
//trace_statement particle::trace_log_warning()
//{ 
//   
//   auto & tracer = get_tracer();
//   
//   tracer(m_pcontext, e_trace_level_warning, trace_category()); 
//
//   return tracer;
//
//}
//
//
//trace_statement particle::trace_log_error()
//{ 
//
//   auto & tracer = get_tracer();
//   
//   tracer(m_pcontext, e_trace_level_error, trace_category()); 
//
//   return tracer;
//
//}
//
//
//trace_statement particle::trace_log_fatal()
//{ 
//
//   auto & tracer = get_tracer();
//   
//   tracer(m_pcontext, e_trace_level_fatal, trace_category()); 
//
//   return tracer;
//
//}


//trace_statement particle::trace(enum_trace_level etracelevel, enum_trace_category etracecategory)
//{
//
//   auto & tracer = get_tracer();
//   
//   tracer(m_pcontext, etracelevel, etracecategory); 
//
//   return tracer;
//
//}
//
//
//trace_statement particle::trace_log_information(enum_trace_category etracecategory)
//{
//
//   auto & tracer = get_tracer();
//   
//   tracer(m_pcontext, e_trace_level_information, etracecategory); 
//
//   return tracer;
//
//}
//
//
//trace_statement particle::trace_log_warning(enum_trace_category etracecategory)
//{
//
//   auto & tracer = get_tracer();
//   
//   tracer(m_pcontext, e_trace_level_warning, etracecategory); 
//
//   return tracer;
//
//}
//
//
//trace_statement particle::trace_log_error(enum_trace_category etracecategory)
//{
//
//   auto & tracer = get_tracer();
//   
//   tracer(m_pcontext, e_trace_level_error, etracecategory); 
//
//   return tracer;
//
//}
//
//
//trace_statement particle::trace_log_fatal(enum_trace_category etracecategory)
//{
//
//   auto & tracer = get_tracer();
//   
//   tracer(m_pcontext, e_trace_level_fatal, etracecategory); 
//
//   return tracer;
//
//}
//
//
//void particle::trace(enum_trace_level etracelevel, const ::ansi_character * pszFormat, ...)
//{
//
//   va_list arguments;
//
//   va_start(arguments, pszFormat);
//
//   trace_arguments(etracelevel, trace_category(), pszFormat, arguments);
//
//   va_end(arguments);
//
//}
//
//
//





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


::e_status particle::lock(const class time & timeWait)
{

   return this->wait(timeWait);

}


void particle::_lock()
{

   _wait();

}


bool particle::_lock(const class time & timeWait)
{

   return this->_wait(timeWait);

}


void particle::_wait()
{

   _wait(::time::infinity());

}


::e_status particle::wait()
{

   auto ptask = ::get_task();

   if (::is_null(ptask))
   {

      ptask = system();

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

      do_tasks();

   }

}


::e_status particle::wait(const class time & timeWait)
{

   if (timeWait < 200_ms)
   {

      auto bOk = this->_wait(timeWait);

      if(!bOk)
      {

         return error_wait_timeout;

      }

      return ::success;

   }

   if(timeWait.is_infinite())
   {

      return this->wait();

   }

   auto ptask = ::get_task();

   if (::is_null(ptask))
   {

      ptask = system();

   }

   if (::is_null(ptask))
   {

      auto bOk = this->_wait(timeWait);

      if(!bOk)
      {

         return error_wait_timeout;

      }

      return ::success;

   }

   auto waitStart = ::time::now();

   while(true)
   {

      auto waitElapsed = waitStart.elapsed();

      if (waitElapsed > timeWait)
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


bool particle::_wait(const class time & timeWait)
{

//#ifdef WINDOWS
//
//   if (!m_hsynchronization)
//   {
//
//      return true;
//
//   }
//
//   //auto milliseconds = wait.operator u32();
//   //unsigned int ui;
//   //if (wait.m_d <= 0.)
//   //{
//   //   ui = 0;
//
//   //}
//   //else if (wait.m_d >= 0xffffffffu)
//   //{
//
//   //   ui = 0xffffffffu;
//   //}
//   //else
//   //{
//
//   //   ui = (::u32) (wait.m_d * 1'000.0);
//
//   //}
//
//   ////return (::u32)m_d <= 0. ? 0 : (m_d >= 0xffffffffu ? 0xffffffffu : (::u32)(m_d * 1'000.0));
//   //if (milliseconds < 1'000'000'000)
//   //{
//
//   //   informationf("milliseconds < 1'000'000'000");
//
//   //}
//
//   auto windowsWaitResult = ::WaitForSingleObjectEx(m_hsync, wait, false);
//
//   auto estatus = windows_wait_result_to_status(windowsWaitResult);
//
//   if (estatus == error_wait_timeout)
//   {
//
//      return false;
//
//   }
//   else if (estatus == signaled_base)
//   {
//
//#ifdef _DEBUG
//
//      auto pmutex = dynamic_cast < ::pointer< ::mutex >> (this);
//
//      if (::is_set(pmutex))
//      {
//
//         pmutex->m_strThread = ::task_get_name();
//         pmutex->m_itask = ::current_itask();
//         ::informationf("");
//
//      }
//
//#endif
//
//      return true;
//
//   }
//   else
//   {
//
//      throw ::exception(estatus);
//
//      return false;
//
//   }
//
//#endif
//
//   throw ::exception(error_interface_only);
//
   return true;

}


void particle::acquire_ownership()
{

   //m_bOwner = true;

   set_own_synchronization_flag();

}


[[maybe_unused]] void particle::release_ownership()
{

   //m_bOwner = false;
   clear_own_synchronization_flag();

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
//   return wait(time::infinite());
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

      synchronouslock.lock(0_s);

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


//::particle * particle::clone() const
//{
//
//   return nullptr;
//
//}



void particle::call_member(::i64 iId)
{

   //return ::success_none;

}




bool particle::is_branch_current() const
{

   return true;

}


::topic_pointer create_topic(::particle * pparticleCall, const ::atom & atom)
{

   auto ptopic = __new(::topic(atom));
   
   ptopic->initialize(pparticleCall);

   return ::transfer(ptopic);

}


::extended_topic_pointer create_extended_topic(::particle * pparticleCall, const ::atom & atom)
{

   return ::transfer(pparticleCall->system()->create_extended_topic(atom));

}


CLASS_DECL_ACME void __call(::particle * pparticle, const ::atom & atom, i64 wParam, i64 lParam, ::particle * pparticleCall)
{

   if (::is_null(pparticleCall))
   {

      auto psystem = pparticle->system();

      auto ptopic = psystem->create_topic(atom);

      if(wParam != 0 || lParam != 0)
      {

         ptopic->payload("wparam") = wParam;
         ptopic->payload("lparam") = lParam;

      }

      pparticle->handle(ptopic, nullptr);

   }
   else
   {

      auto pextendedtopic = create_extended_topic(pparticleCall, atom);

      if(wParam != 0 || lParam != 0)
      {

         pextendedtopic->payload("wparam") = wParam;
         pextendedtopic->payload("lparam") = lParam;

      }

      pextendedtopic->m_pparticle = pparticleCall;

      pparticle->handle(pextendedtopic, nullptr);

   }

}



//
//
//void handler::call(enum_message emessage, i64 iData, ::matter * pmatter)
//{
//
//   return __call(this, emessage, iData, pmatter);
//
//}
//
//
//void handler::call(enum_id eid, i64 iData, ::matter * pmatter)
//{
//
//   return __call(this, eid, iData, pmatter);
//
//}
//


void particle::call(const ::atom & atom, i64 wParam, i64 lParam, ::particle * pparticle)
{

   return __call(this, atom, wParam, lParam, pparticle);

}
//
//
//void particle::handle(::topic * ptopic, ::context * pcontext)
//{
//
//
//}


void particle::handle(::message::message * pmessage)
{


}


void particle::handle(::item * pmessage)
{


}


bool particle::_handle_uri(const ::string & strUri)
{

   return false;

}


bool particle::_handle_call(::payload & payload, const ::string & strObject, const ::string & strMember, ::property_set & propertyset)
{

   return false;

}


//bool handler::_handle_call(::payload & payload, const ::string & strMember, ::property_set & propertyset)
//{
//
//   return false;
//
//}

//bool handler::handle_text_command(const ::string & strTextCommand)
//{
//
//   return false;
//
//}


//
//void handler::call(enum_id eid, i64 iData, ::matter * pmatter)
//{
//
//   return __call(this, eid, iData, pmatter);
//
//}


//bool handler::on_interprocess_handle(::interprocess::target * ptarget, const ::string & strUri)
//{
//
//   return handle_uri(blockUri);
//
//}


class ::time particle::timeout() const
{

   return 1_min;

}


void particle::set_timeout(const class time & timeTimeout)
{

   throw interface_only();

}



::payload particle::realize()
{

   //return ::success;
   return ::success;

}


//void particle::call_run()
//{
//
//   //::e_status estatus;
//
//   //try
//   //{
//
//   /*estatus =*/ run();
//
//   //}
//   //catch (...)
//   //{
//
//   //   estatus = ::error_exception;
//
//   //}
//
//   //return estatus;
//
//}


::particle_pointer particle::clone()
{

   throw interface_only();

   return nullptr;

}


::user::user * particle::aurauser()
{

   return ::is_set(application()) ? application()->aurauser() : nullptr;

}


::axis::user * particle::axisuser()
{

   return ::is_set(application()) ? application()->axisuser() : nullptr;

}


::base::user * particle::baseuser()
{

   return ::is_set(application()) ? application()->baseuser() : nullptr;

}


::bred::user * particle::breduser()
{

   return ::is_set(application()) ? application()->breduser() : nullptr;

}


::core::user * particle::coreuser()
{

   return ::is_set(application()) ? application()->coreuser() : nullptr;

}


void particle::set_generic_object_name(const ::scoped_string & scopedstrName)
{

   //return ::success_none;

}


void particle::set_application_id(const ::scoped_string & scopedstrApplicationId)
{

   //return error_none;

}


void particle::set_library_name(const ::scoped_string & scopedstrLibraryName)
{

   //return error_none;

}


//::e_status particle::wait()
//{
//
//   return ::success;
//
//}
//
//
//::e_status particle::wait(const class time & timeWait)
//{
//
//   return ::success;
//
//}


//void particle::add_composite(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEFINITION)
//{
//
//   //throw ::not_implemented();
//
//   pelement->increment_reference_count();
//
//   //return ::success;
//
//   //return ::error_not_implemented;
//
//}
//
//
//void particle::add_reference(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEFINITION)
//{
//
//   //return ::success_none;
//
//}
//
//
//void particle::release_composite2(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEFINITION)
//{
//
//   //return ::success_none;
//
//}
//
//
//void particle::finalize_composite(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEFINITION)
//{
//
//   //return ::success_none;
//
//}
//
//
//void particle::release_reference(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEFINITION)
//{
//
//   //return ::success_none;
//
//}


::particle* particle::get_taskpool_container()
{

   return nullptr;

}



::task_pool* particle::taskpool()
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








bool particle::should_run_async() const
{

   return false;

}


//::enum_type particle::get_payload_type() const
//{
//
//   return e_type_element;
//
//}


//void particle::exchange(stream& s)
//{
//
//}
//
//
//void particle::exchange(payload_stream& s)
//{
//
//}

//stream & particle::write(stream& s) const
//{
//
//   return s;
//
//}
//
//
//stream& particle::read(stream& s)
//{
//
//   return s;
//
//}


//void matter::finish(::property_object * pcontextobjectFinish)
void particle::destroy()
{

   //auto estatus = set_finish();

   //if (estatus == error_pending)
   //{

   //   //system()->add_pending_finish(this);

   //   return estatus;

   //}

   ////estatus = on_finish();

   ////if (estatus == error_pending)
   ////{

   ////   //system()->add_pending_finish(this);

   ////   return estatus;

   ////}

   //return estatus;

   //return ::success;


}


void particle::destroy_impl_data()
{


}


void particle::destroy_os_data()
{


}


void particle::write_to_stream(::binary_stream & stream)
{

   throw interface_only();

}


void particle::read_from_stream(::binary_stream & stream)
{

   throw interface_only();

}


CLASS_DECL_ACME ::pointer < ::particle > detach_pointer(::lparam& lparam)
{

   auto p = ::pointer_transfer((particle*)lparam.m_lparam);

   lparam.m_lparam = 0;

   return ::transfer(p);

}


const char* particle::debug_note() const
{

   return nullptr;

}


void particle::kick_idle()
{


}


::file_pointer particle::get_file(const ::payload& payloadFile, ::file::e_open eopen, ::pointer < ::file::exception > * pfileexception)
{

   return m_pcontext->get_file(payloadFile, eopen, pfileexception);

}


 ::pointer<particle>particle::__id_create(const ::atom & atom, ::factory::factory * pfactory)
{

   auto pfactoryitem = pfactory->get_factory_item(atom);

   if (!pfactoryitem)
   {

      throw ::exception(error_no_factory);

   }

   auto p = pfactoryitem->create_particle();

   if (!p)
   {

      throw ::no_memory();

   }

   p->initialize(this);

   return p;

}


pointer < ::sequencer < ::conversation > > particle::message_box(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails)
{

   return system()->nano()->message_box(strMessage, strTitle, emessagebox, strDetails);

}


pointer < ::sequencer < ::conversation > > particle::exception_message_box(const ::exception& exception, const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails)
{

   return system()->nano()->exception_message_box(exception, strMessage, strTitle, emessagebox, strDetails);

}


pointer < ::sequencer < ::conversation > > particle::message_console(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails)
{

   return system()->nano()->message_console(strMessage, strTitle, emessagebox, strDetails);

}


pointer < ::sequencer < ::conversation > > particle::exception_message_console(const ::exception& exception, const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails)
{

   return system()->nano()->exception_message_console(exception, strMessage, strTitle, emessagebox, strDetails);

}


void particle::app_post(const ::procedure & procedure)
{

   application()->post_procedure(procedure);

}


::task_pointer particle::app_fork(const ::procedure & procedure)
{

   return application()->fork(procedure);

}


void particle::task_post(const ::procedure & procedure)
{

   ::get_task()->post_procedure(procedure);

}


::task_pointer particle::task_fork(const ::procedure & procedure)
{

   return ::get_task()->fork(procedure);

}


void particle::user_send(const ::procedure & procedure)
{

   acmenode()->user_send(procedure);

}


void particle::user_post(const ::procedure & procedure)
{

   acmenode()->user_post(procedure);

}


//::pointer < particle > particle::clone() const
//{
//
//   throw ::interface_only();
//
//   return nullptr;
//
//}


CLASS_DECL_ACME class tracer * tracer()
{

   auto ptask = get_task();

   if (!ptask)
   {

      return ::platform::get()->m_pcontext;

   }

   return ptask;

}






CLASS_DECL_ACME ::trace_statement log_statement()
{

   return ::transfer(trace_statement(tracer())((::particle *)nullptr));

}


::trace_statement information()
{

   return ::transfer(trace_statement(tracer())(e_trace_level_information));

}


::trace_statement warning()
{

   return ::transfer(trace_statement(tracer())(e_trace_level_warning));

}


::trace_statement error()
{

   return ::transfer(trace_statement(tracer())(e_trace_level_error));

}


::trace_statement fatal()
{

   return ::transfer(trace_statement(tracer())(e_trace_level_fatal));

}


void informationf(const ::ansi_character * pszFormat, ...)
{

   va_list arguments;

   va_start(arguments, pszFormat);

   {

      auto statement = log_statement();

      statement(e_trace_level_information);

      statement.formatf_output_arguments(pszFormat, arguments);

   }

   va_end(arguments);

}


void warningf(const ::ansi_character * pszFormat, ...)
{

   va_list arguments;

   va_start(arguments, pszFormat);

   {

      auto statement = log_statement();

      statement(e_trace_level_warning);

      statement.formatf_output_arguments(pszFormat, arguments);

   }

   va_end(arguments);

}


void errorf(const ::ansi_character * pszFormat, ...)
{

   va_list arguments;

   va_start(arguments, pszFormat);

   {

      auto statement = log_statement();

      statement(e_trace_level_error);

      statement.formatf_output_arguments(pszFormat, arguments);

   }

   va_end(arguments);

}


void fatalf(const ::ansi_character * pszFormat, ...)
{

   va_list arguments;

   va_start(arguments, pszFormat);

   {

      auto statement = log_statement();

      statement(e_trace_level_fatal);

      statement.formatf_output_arguments(pszFormat, arguments);

   }

   va_end(arguments);

}


void particle::process_owned_procedure_list(::procedure_list & procedurelist, bool & bHandled)
{

   _synchronous_lock synchronouslock(this->synchronization());

   if(procedurelist.is_empty())
   {

      return;

   }

   do
   {

      {

         auto routine = procedurelist.pick_head();

         synchronouslock.unlock();

         routine();

      }

      synchronouslock.lock();

   }
   while(procedurelist.has_element());

}



