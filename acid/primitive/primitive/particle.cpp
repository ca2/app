// Created by camilo on 2022-05-08 20:20 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "type.h"
#include "factory.h"
#include "acid/exception/exit.h"
#include "acid/exception/interface_only.h"
#include "acid/handler/extended_topic.h"
#include "acid/handler/topic.h"
#include "acid/parallelization/synchronous_lock.h"
#include "acid/platform/acid.h"
#include "acid/platform/application.h"
#include "acid/platform/context.h"
#include "acid/platform/node.h"
#include "acid/platform/reference_item_array.h"
#include "acid/platform/referencing_debugging.h"
#include "acid/platform/session.h"
#include "acid/platform/system.h"
#include "acid/nano/nano.h"
#include "acid/nano/user/user.h"
//#include "acid/primitive/primitive/payload.h"


CLASS_DECL_ACID void do_tasks();


#if defined(FREEBSD) || defined(OPENBSD) || defined(__APPLE__)
#include <stdio.h>
#endif


#if REFERENCING_DEBUGGING


bool g_bDefaultEnableObjectReferenceCountDebug = false;


//CLASS_DECL_ACID void on_construct_particle(::particle * pparticle);


particle::particle() :
   m_countReference(1)
{

#if REFERENCING_DEBUGGING
   
   if (!g_bDefaultEnableObjectReferenceCountDebug)
   {

      disable_referencing_debugging();

   }

   ::allocator::on_construct_particle(this);

#endif

}


//particle::particle(disable_referencing_debugging_t) :
//   m_countReference(1)
//{
//
//#if REFERENCING_DEBUGGING
//
//   disable_referencing_debugging();
//
//#endif
//
//   ::allocator::on_construct_particle(this);
//
//}


#endif


particle::~particle()
{

#if REFERENCING_DEBUGGING
   m_pparticleSynchronization.release();
   {

      //auto p = ::transfer(m_preferenceitema);

      //m_preferenceitema.release();

      ::allocator::on_destruct_particle(this);

//      ::acid::del(m_preferenceitema);

   }
#endif

}


void particle::initialize(::particle * pparticle)
{

   //if (::is_set(pparticle))
   //{

   //   if (pparticle->m_preferenceitema)
   //   {

   //      if (m_preferenceitema)
   //      {

   //         if (!m_preferenceitema->m_pparticleParent)
   //         {

   //            pparticle->m_preferenceitema->m_item2a.add_item(m_preferenceitema);

   //            m_preferenceitema->m_pparticleParent = pparticle;

   //            ::acid::get()->m_preferencingdebugging->m_item2a.erase_last(m_preferenceitema);

   //         }


   //      }

   //   }

   //}

//#if REFERENCING_DEBUGGING
//
//   if (is_referencing_debugging_enabled())
//   {
//
//      m_preferenceitema->initialize_reference_item_array(::acid::get()->m_preferencingdebugging);
//
//   }
//
//#endif

   if (!m_pcontext)
   {

      m_pcontext = pparticle->m_pcontext;

      on_initialize_particle();

   }

}


void particle::finalize()
{



}




void particle::set_synchronization(::particle *pparticleSynchronization)
{

   m_pparticleSynchronization = pparticleSynchronization;

}


void particle::defer_create_synchronization()
{

   if (!m_pparticleSynchronization)
   {

#if REFERENCING_DEBUGGING

      refdbg_top_track toptrack(this);

#endif

      set_synchronization(__create< ::mutex >(nullptr));

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


::platform::platform * particle::platform() const
{

   return ::is_set(m_pcontext) ? m_pcontext->m_pplatform : _platform();

}


class ::platform::platform * particle::_platform() const
{

   return ::acid::get()->m_pplatform;

}


//void particle::destroy()
//{
//
//
//}



::string particle::get_debug_title() const
{

   auto pparticle = (::particle *) this;

   return ::type(*pparticle).name();

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


::acid::application * particle::application() const
{

   return m_pcontext ? m_pcontext->m_paceapplication : nullptr;

}


//::aura::application * particle::auraapplication() const
//{
//
//   return m_pcontext && m_pcontext->m_paceapplication ? m_pcontext->m_paceapplication->m_pauraapplication : nullptr;
//
//}


::acid::session* particle::session() const
{

   return m_pcontext ? m_pcontext->m_pacesession : nullptr;

}


::ace_file * particle::acefile() const
{

   return m_pcontext->acefile();

}


::ace_path * particle::acepath() const
{

   return m_pcontext->acepath();

}


::ace_directory * particle::acedirectory() const
{

   return m_pcontext->acedirectory();

}


::acid::node * particle::node() const
{

   return m_pcontext->node();

}


::mathematics::mathematics * particle::mathematics() const
{

   auto psystem = system();

   return ::is_set(psystem) ? psystem->mathematics() : nullptr;

}


::primitive::primitive * particle::primitive() const
{

   auto psystem = system();

   return ::is_set(psystem) ? psystem->primitive() : nullptr;

}


class ::imaging * particle::imaging() const
{

   auto psystem = system();

   return ::is_set(psystem) ? psystem->imaging() : nullptr;

}


class ::user::user * particle::user() const
{

   auto psession = session();

   return ::is_set(psession) ? psession->user() : nullptr;

}


class ::draw2d::draw2d * particle::draw2d() const
{

   auto psystem = system();

   return ::is_set(psystem) ? psystem->draw2d() : nullptr;

}


class ::write_text::write_text * particle::write_text() const
{

   auto psystem = system();

   return ::is_set(psystem) ? psystem->write_text() : nullptr;

}


::acid::system * particle::system() const
{

   return ::is_set(m_pcontext) ? m_pcontext->system() : nullptr;

}


::acid::context* particle::context() const
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


//::os_context * particle::os_context() const
//{
//
//   return m_pcontext->os_context();
//
//}


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

   //informationf("particle::factory(\"%s\", \"%s\");\n", strComponent.c_str(), strImplementation.c_str());

   return platform()->factory(strComponent, strImplementation);

}


void particle::handle(::topic * ptopic, ::context * pcontext)
{


}


void particle::call_handle(::topic* ptopic, ::context* pcontext)
{

   handle(ptopic, pcontext);

}


void particle::call_handle_message(::message::message* pmessage)
{

   handle_message(pmessage);

}


void particle::call_handle_item(::item* pitem)
{

   handle_item(pitem);

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


void subparticle::init_task()
{


}


void subparticle::call_run()
{

   m_eflagElement += e_flag_running;

   try
   {

      run();

   }
   catch (const ::exit_exception& exception)
   {

      throw exception;

   }
   catch (...)
   {

   }

   m_eflagElement -= e_flag_running;

}


void subparticle::run()
{

   while (true)
   {

      if(!subparticle_step())
      {

         break;

      }

   }

}


bool subparticle::subparticle_step()
{

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


void particle::print_line(const ::scoped_string & scopedstr) const
{
   
   ::string strLine(scopedstr);
   
   strLine += "\n";

   printf("%s", strLine.c_str());
   
   fflush(stdout);

}


void particle::print_out(const ::scoped_string & scopedstr) const
{
   
   ::string strLine(scopedstr);
   
   printf("%s", strLine.c_str());
   
   fflush(stdout);

}


void printf_line(const ::ansi_character * pszFormat, ...)
{

   va_list arguments;

   va_start(arguments, pszFormat);

   ::string strLine(pszFormat);

   strLine += "\n";

   vprintf(strLine.c_str(), arguments);

   va_end(arguments);

   fflush(stdout);

}


void particle::printf_line(const ::ansi_character * pszFormat, ...) const
{

   va_list arguments;

   va_start(arguments, pszFormat);
   
   ::string strLine(pszFormat);
   
   strLine += "\n";

   vprintf(strLine.c_str(), arguments);

   va_end(arguments);
   
   fflush(stdout);

}


void particle::printf_out(const ::ansi_character * pszFormat, ...) const
{

   va_list arguments;

   va_start(arguments, pszFormat);

   vprintf(pszFormat, arguments);

   va_end(arguments);
   
   fflush(stdout);

}


void particle::err_line(const ::scoped_string & scopedstr) const
{
   
   ::string strLine(scopedstr);
   
   strLine += "\n";

   printf("%s", strLine.c_str());
   
   fflush(stdout);

}


void particle::err_out(const ::scoped_string & scopedstr) const
{
   
   ::string strLine(scopedstr);
   
   printf("%s", strLine.c_str());
   
   fflush(stdout);

}


void particle::errf_line(const ::ansi_character * pszFormat, ...) const
{

   va_list arguments;

   va_start(arguments, pszFormat);
   
   ::string strLine(pszFormat);
   
   strLine += "\n";

   vfprintf(stderr, strLine.c_str(), arguments);

   va_end(arguments);
   
   fflush(stderr);

}


void particle::errf_out(const ::ansi_character * pszFormat, ...) const
{

   va_list arguments;

   va_start(arguments, pszFormat);

   vfprintf(stderr, pszFormat, arguments);

   va_end(arguments);
   
   fflush(stderr);

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


void particle::trace(enum_trace_level etracelevel, const ::scoped_string & scopedstr) const
{

   auto statement = ::transfer(log_statement());

   statement(etracelevel)(trace_category());

   statement << scopedstr;

}


void particle::information(const scoped_string & scopedstr) const
{
   trace(e_trace_level_information, scopedstr);
}
void particle::warning(const scoped_string & scopedstr) const
{
   trace(e_trace_level_warning, scopedstr);
}
void particle::error(const scoped_string & scopedstr) const
{
   trace(e_trace_level_error, scopedstr);
}
void particle::fatal(const scoped_string & scopedstr) const
{
   trace(e_trace_level_fatal, scopedstr);
}



class tracer * particle::tracer() const
{

   auto ptask = get_task();

   if (!ptask)
   {

      auto pplatform = this->platform();

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


::trace_statement particle::debug() const
{

   return ::transfer(trace_statement()(e_trace_level_debug));

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


void particle::debugf(const ::ansi_character * pszFormat, ...) const
{

   va_list arguments;

   va_start(arguments, pszFormat);

   formatf_trace(e_trace_level_debug, pszFormat, arguments);

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

      //try { throw "errorABC1"; } catch(...){}

      printf_line("particle::wait ptask is NULL, going to do NOT transacted wait");

      _wait();

      return ::success;

   }

   //printf_line("particle::wait ptask is SET, going to DO transacted wait");

   while (true)
   {

      do_tasks();

      //try { throw "errorABC2"; } catch(...){}

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

      ::do_tasks();

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
//         ::acid::get()->platform()->informationf("");
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

      synchronouslock.wait(0_s);

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

   auto ptopic = __allocate< ::topic >(atom);
   
   ptopic->initialize(pparticleCall);

   return ::transfer(ptopic);

}


::extended_topic_pointer create_extended_topic(::particle * pparticleCall, const ::atom & atom)
{

   return ::transfer(pparticleCall->system()->create_extended_topic(atom));

}


CLASS_DECL_ACID void __call(::particle * pparticle, const ::atom & atom, i64 wParam, i64 lParam, ::particle * pparticleCall)
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


void particle::handle_message(::message::message * pmessage)
{


}


void particle::handle_item(::item * pmessage)
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


//void particle::add_composite(::particle * pparticle)
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
//void particle::add_reference(::particle * pparticle)
//{
//
//   //return ::success_none;
//
//}
//
//
//void particle::release_composite2(::particle * pparticle)
//{
//
//   //return ::success_none;
//
//}
//
//
//void particle::finalize_composite(::particle * pparticle)
//{
//
//   //return ::success_none;
//
//}
//
//
//void particle::release_reference(::particle * pparticle)
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


void * particle::new_object(const char * psz)
{
   
   throw interface_only();
   
   return nullptr;
   
}


void particle::write_to_stream(::binary_stream & stream)
{

   throw interface_only();

}


void particle::read_from_stream(::binary_stream & stream)
{

   throw interface_only();

}


CLASS_DECL_ACID ::pointer < ::particle > detach_pointer(::lparam& lparam)
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


 ::pointer<particle>particle::__call__id_create(const ::atom & atom, ::factory::factory * pfactory)
{

    if (::is_null(pfactory))
    {

       pfactory = platform()->factory();

    }

   auto pfactoryitem = pfactory->get_factory_item(atom);

   if (!pfactoryitem)
   {

      throw ::exception(error_no_factory);

   }

   auto p = pfactoryitem->__call__create_particle();

   if (!p)
   {

      throw ::no_memory();

   }

   p->initialize(this);

   return p;

}


pointer < ::sequencer < ::conversation > > particle::message_box(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails)
{

   return system()->nano()->user()->message_box(strMessage, strTitle, emessagebox, strDetails);

}


pointer < ::sequencer < ::conversation > > particle::exception_message_box(const ::exception& exception, const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails)
{

   return system()->nano()->user()->exception_message_box(exception, strMessage, strTitle, emessagebox, strDetails);

}


pointer < ::sequencer < ::conversation > > particle::message_console(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails)
{

   return system()->nano()->user()->message_console(strMessage, strTitle, emessagebox, strDetails);

}


pointer < ::sequencer < ::conversation > > particle::exception_message_console(const ::exception& exception, const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails)
{

   return system()->nano()->user()->exception_message_console(exception, strMessage, strTitle, emessagebox, strDetails);

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

   node()->user_send(procedure);

}


void particle::user_post(const ::procedure & procedure)
{

   node()->user_post(procedure);

}


//::pointer < particle > particle::clone() const
//{
//
//   throw ::interface_only();
//
//   return nullptr;
//
//}

//
//CLASS_DECL_ACID class tracer * tracer()
//{
//
//   auto ptask = get_task();
//
//   if (!ptask)
//   {
//
//      return this->platform()->m_pcontext;
//
//   }
//
//   return ptask;
//
//}


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

      synchronouslock._lock();

   }
   while(procedurelist.has_element());

}


#if REFERENCING_DEBUGGING


::particle * particle::__call__add_referer2(const ::reference_referer & referer) const
{

   ::allocator::defer_add_referer(referer);

   return (::particle *) this;

}


CLASS_DECL_ACID ::allocator::accessor * __call__add_referer(const ::reference_referer & referer, ::reference_referer ** ppreferer)
{

   auto preferer = ::allocator::defer_add_referer(referer);

   if (ppreferer)
   {

      *ppreferer = preferer;

   }

   return ::allocator::g_pacessorDefault;

}


#endif



//#if defined(__GNUC__)
//#pragma message("defined(__GNUC__)")
//#else
//#pragma message("!defined(__GNUC__)")
//#endif
