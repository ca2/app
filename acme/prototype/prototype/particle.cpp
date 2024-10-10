// Created by camilo on 2022-05-08 20:20 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "type.h"
#include "factory.h"
#include "acme/exception/exit.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/file/exception.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/handler/extended_topic.h"
#include "acme/handler/topic.h"
#include "acme/memory/memory_allocate.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/acme.h"
#include "acme/platform/application.h"
#include "acme/platform/context.h"
#include "acme/platform/node.h"
#include "acme/platform/reference_item_array.h"
#include "acme/platform/referencing_debugging.h"
#include "acme/platform/session.h"
#include "acme/platform/system.h"
#include "acme/nano/nano.h"
#include "acme/user/micro/user.h"
//#include "acme/prototype/prototype/payload.h"


CLASS_DECL_ACME void do_tasks();


#if defined(__BSD__) || defined(__APPLE__)
#include <stdio.h>
#endif


#if REFERENCING_DEBUGGING


bool g_bDefaultEnableObjectReferenceCountDebug = false;


//CLASS_DECL_ACME void on_construct_particle(::particle * pparticle);


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

//      ::acme::del(m_preferenceitema);

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

   //            ::acme::get()->m_preferencingdebugging->m_item2a.erase_last(m_preferenceitema);

   //         }


   //      }

   //   }

   //}

//#if REFERENCING_DEBUGGING
//
//   if (is_referencing_debugging_enabled())
//   {
//
//      m_preferenceitema->initialize_reference_item_array(::acme::get()->m_preferencingdebugging);
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


::particle * particle::get_context_particle()
{

   return m_pcontext;

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


::platform::platform * particle::platform()
{

   return ::platform::get();
   //return ::is_set(m_pcontext) ? m_pcontext->m_pplatform : _platform();

}


class ::platform::platform * particle::_platform() const
{

   return ::acme::get()->m_pplatform;

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


::acme::node * particle::node() const
{

   return m_pcontext->node();

}


::mathematics::mathematics * particle::mathematics() const
{

   auto psystem = system();

   return ::is_set(psystem) ? psystem->mathematics() : nullptr;

}


::prototype::prototype * particle::prototype() const
{

   auto psystem = system();

   return ::is_set(psystem) ? psystem->prototype() : nullptr;

}


::image::image_context* particle::image() const
{

   return m_pcontext ? m_pcontext->image() : nullptr;

}



class ::image::imaging * particle::imaging() const
{

   auto psystem = system();

   return ::is_set(psystem) ? psystem->imaging() : nullptr;

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


class ::user::user * particle::user() const
{

   auto psession = session();

   return ::is_set(psession) ? psession->user() : nullptr;

}



::acme::system * particle::system() const
{

   return ::is_set(m_pcontext) ? m_pcontext->system() : ::platform::get()->system();

}


::acme::context* particle::context() const
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



::internet::internet* particle::internet() const
{

   return system()->internet();

}


::url::url_context* particle::url() const
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



::file::watcher * particle::file_watcher()
{

   return m_pcontext->file_watcher();

}


::http::context * particle::http() const
{

   return m_pcontext->http();

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


void particle::operator()(::topic * ptopic, ::context * pcontext)
{

   handle(ptopic, pcontext);

}


//void particle::operator()(::sequencer & sequencer)
//{
//
//   run();
//
//   complete_step(sequencer);
//
//}


//void particle::operator()(::sequence * psequence)
//{
//
//   run();
//
//   aggregate(psequence);
//
//}


//::sequencer particle::get_current_sequencer()
//{
//
//   return nullptr;
//
//}


//void particle::set_current_sequencer(const ::sequencer & sequencer)
//{
//
//
//}
//
//
//void particle::aggregate(::sequencer & sequencer)
//{
//
//   set_current_sequencer(sequencer);
//
//   run();
//
//   complete_step(sequencer);
//
//}


void particle::handle(::topic * ptopic, ::context * pcontext)
{


}


//void particle::aggregate(::sequence * psequence)
//{
//
//}


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


void particle::install_message_routing(::channel * pchannel)
{


}


void subparticle::init_task()
{


}


void subparticle::call()
{

   //m_eflagElement += e_flag_running;

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

   //m_eflagElement -= e_flag_running;

}


bool particle::_is_ok() const
{

   return has_ok_flag();

}


void particle::delete_this()
{

   if (!(m_eflagElement & e_flag_statically_allocated))
   {

      //__delete(this, m_pAllocation);

      //delete m_pAllocation;

      delete this;

   }

}



void particle::on_sequence()
{


}


::payload particle::get_result_payload()
{

   return {};

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
   
   fwrite(scopedstr.begin(), 1, scopedstr.size(), stdout);
   
   fflush(stdout);

}


//void printf_line(const ::ansi_character * pszFormat, ...)
//{
//
//   va_list arguments;
//
//   va_start(arguments, pszFormat);
//
//   ::string strLine(pszFormat);
//
//   strLine += "\n";
//
//   vprintf(strLine.c_str(), arguments);
//
//   va_end(arguments);
//
//   fflush(stdout);
//
//}


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
//         ::acme::get()->platform()->informationf("");
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

   auto ptopic = __new ::topic(atom);
   
   ptopic->initialize(pparticleCall);

   return ::transfer(ptopic);

}


::extended_topic_pointer create_extended_topic(::particle * pparticleCall, const ::atom & atom)
{

   return ::transfer(pparticleCall->system()->create_extended_topic(atom));

}


CLASS_DECL_ACME lresult __call(::particle * pparticle, const ::atom & atom, i64 wParam, i64 lParam)
{


   throw "what?!?!?!";

   //if (::is_null(pparticleCall))
   //{

   //   auto psystem = pparticle->system();

   //   auto ptopic = psystem->create_topic(atom);

   //   if(wParam != 0 || lParam != 0)
   //   {

   //      ptopic->payload("wparam") = wParam;
   //      ptopic->payload("lparam") = lParam;

   //   }

   //   pparticle->handle(ptopic, nullptr);

   //}
   //else
   //{

   //   auto pextendedtopic = create_extended_topic(pparticleCall, atom);

   //   if(wParam != 0 || lParam != 0)
   //   {

   //      pextendedtopic->payload("wparam") = wParam;
   //      pextendedtopic->payload("lparam") = lParam;

   //   }

   //   pextendedtopic->m_pparticle = pparticleCall;

   //   pparticle->handle(pextendedtopic, nullptr);

   //}

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


lresult particle::message_call(const ::atom & atom, wparam wParam, lparam lParam)
{

   return message_handler(atom, wParam, lParam);

}


lresult particle::message_handler(const ::atom & atom, wparam wParam, lparam lParam)
{

   return __call(this, atom, wParam, lParam);

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



void * particle::new_object(const char * psz)
{
   
   throw interface_only();
   
   return nullptr;
   
}



CLASS_DECL_ACME ::particle_pointer detach_pointer(::lparam& lparam)
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


 ::pointer<subparticle>particle::__call__id_create(const ::atom & atom, ::factory::factory * pfactory)
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
//
//
//::pointer < ::message_box > particle::message_box(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails, ::nano::graphics::icon * picon)
//{
//   
//   ::micro::user * pmicrouser = nullptr;
//   
//   try
//   {
//      
//      pmicrouser = system()->micro_user();
//      
//   }
//   catch (...)
//   {
//   
//      
//   }
//   
//   if(::is_set(pmicrouser))
//   {
//    
//      return pmicrouser->message_box(strMessage, strTitle, emessagebox, strDetails, picon);
//      
//   }
//   
//   auto pmessagebox = __initialize_new ::message_box(strMessage, strTitle, emessagebox, strDetails, picon);
//
//   return pmessagebox;
//
//}


//::pointer < ::message_box > particle::exception_message_box(const ::exception& exception, const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails, ::nano::graphics::icon * picon)
//{
//
//   return system()->micro_user()->exception_message_box(exception, strMessage, strTitle, emessagebox, strDetails, picon);
//
//}
//
//
//::pointer < ::message_box > particle::message_console(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails, ::nano::graphics::icon * picon)
//{
//
//   return system()->micro_user()->message_console(strMessage, strTitle, emessagebox, strDetails, picon);
//
//}
//
//
//::pointer < ::message_box > particle::exception_message_console(const ::exception& exception, const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails, ::nano::graphics::icon * picon)
//{
//
//   return system()->micro_user()->exception_message_console(exception, strMessage, strTitle, emessagebox, strDetails, picon);
//
//}


void particle::app_post(const ::procedure & procedure)
{

   application()->post(procedure);

}


::task_pointer particle::app_fork(const ::procedure & procedure)
{

   return application()->fork(procedure);

}


void particle::task_post(const ::procedure & procedure)
{

   ::get_task()->post(procedure);

}


::task_pointer particle::task_fork(const ::procedure & procedure)
{

   return ::get_task()->fork(procedure);

}


void particle::_user_send(const ::procedure & procedure)
{

   node()->user_send(procedure);

}


void particle::_user_post(const ::procedure & procedure)
{

   node()->user_post(procedure);

}


void particle::_main_send(const ::procedure & procedure)
{

   user_send(procedure);

}


void particle::_main_post(const ::procedure & procedure)
{

   user_post(procedure);

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
//CLASS_DECL_ACME class tracer * tracer()
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


CLASS_DECL_ACME ::allocator::accessor * __call__add_referer(const ::reference_referer & referer, ::reference_referer ** ppreferer)
{

   auto preferer = ::allocator::defer_add_referer(referer);

   if (ppreferer)
   {

      *ppreferer = preferer;

   }

   return ::allocator::g_pacessorDefault;

}


#endif


memory_file_pointer particle::create_memory_file()
{

   return __create_new< ::memory_file >();

}



memory_file_pointer particle::create_memory_file(::memory_base& memory)
{

   return __new ::memory_file(memory);

}


memory_file_pointer particle::create_memory_file(const ::block& block)
{

   return __new ::memory_file(block);

}


memory_file_pointer particle::create_memory_file_as_copy(const memory& memory)
{

   return __new ::memory_file(__new ::memory (memory));

}


memory_file_pointer particle::create_memory_file_by_reading(::file::file* pfile)
{

   auto pmemoryfile = create_memory_file();

   auto left = pfile->right_size();

   if (left > UINTPTR_MAX)
   {

      throw ::exception(error_no_memory);

   }

   auto ptrleft = (::memsize)left;

   pmemoryfile->full_data_set_size(ptrleft);

   auto amountRead = pfile->read(pmemoryfile->full_data());

   if (amountRead != pmemoryfile->full_data_size())
   {

      throw ::file::exception(error_failed, { e_error_code_type_unknown, -1 }, pfile->m_path, pfile->m_eopen, "Read bytes less than recorded left bytes");

   }

   //pmemoryfile->m_pbyte = pmemoryfile->data();

   //pmemoryfile->m_memsize = (memsize) pmemoryfile->size();

   return pmemoryfile;

}



//#if defined(__GNUC__)
//#pragma message("defined(__GNUC__)")
//#else
//#pragma message("!defined(__GNUC__)")
//#endif



CLASS_DECL_ACME::trace_statement debug()
{

   return ::transfer(::platform::get()->system()->debug());

}


CLASS_DECL_ACME::trace_statement information()
{

   return ::transfer(::platform::get()->system()->information());

}


CLASS_DECL_ACME::trace_statement warning()
{

   return ::transfer(::platform::get()->system()->warning());

}



CLASS_DECL_ACME::trace_statement error()
{

   return ::transfer(::platform::get()->system()->error());

}



CLASS_DECL_ACME::trace_statement fatal()
{

   return ::transfer(::platform::get()->system()->fatal());

}





CLASS_DECL_ACME void debugf(const ::ansi_character* pszFormat, ...)
{

   va_list arguments;

   va_start(arguments, pszFormat);

   ::platform::get()->system()->formatf_trace(e_trace_level_debug, pszFormat, arguments);

   va_end(arguments);

}


CLASS_DECL_ACME void informationf(const ::ansi_character* pszFormat, ...)
{

   va_list arguments;

   va_start(arguments, pszFormat);

   ::platform::get()->system()->formatf_trace(e_trace_level_information, pszFormat, arguments);

   va_end(arguments);

}


CLASS_DECL_ACME void warningf(const ::ansi_character* pszFormat, ...)
{

   va_list arguments;

   va_start(arguments, pszFormat);

   ::platform::get()->system()->formatf_trace(e_trace_level_warning, pszFormat, arguments);

   va_end(arguments);

}


CLASS_DECL_ACME void errorf(const ::ansi_character* pszFormat, ...)
{

   va_list arguments;

   va_start(arguments, pszFormat);

   ::platform::get()->system()->formatf_trace(e_trace_level_error, pszFormat, arguments);

   va_end(arguments);

}


CLASS_DECL_ACME void fatalf(const ::ansi_character* pszFormat, ...)
{

   va_list arguments;

   va_start(arguments, pszFormat);

   ::platform::get()->system()->formatf_trace(e_trace_level_fatal, pszFormat, arguments);

   va_end(arguments);

}

//void particle::complete_step(::sequencer & sequencer)
//{
//
//
//}


//void particle::user_send()
//{
//
//   user_send(this);
//
//}



//void particle::user_post()
//{
//
//   user_post(this);
//
//}


//void particle::main_send()
//{
//
//   main_send(this);
//
//}


//post_continuation particle::user_async()
//{
//
//
//}


//send_continuation particle::user_sync()
//{
//
//
//}


//post_continuation particle::main_async()
//{
//
//
//}


//send_continuation particle::main_sync()
//{
//
//
//}



//void particle::main_post()
//{
//
//   main_post(this);
//
//}

class ::time particle::get_default_run_timeout()
{

   return ::default_run_timeout();

}


//void particle::send(const ::procedure & procedure)
//{
//
//   m_pcontext->send(procedure);
//
//}


void particle::_post(const ::procedure & procedure)
{

   m_pcontext->_post(procedure);

}


void particle::_send(const ::procedure & procedure)
{

   m_pcontext->_send(procedure);

}


void particle::_call_procedure(enum_dispatch edispatch, const procedure & procedure)
{

   if (edispatch == e_dispatch_send)
   {

      _send(procedure);

   }
   else if (edispatch == e_dispatch_main_send)
   {

      _main_send(procedure);

   }
   else if (edispatch == e_dispatch_user_send)
   {

      _user_send(procedure);

   }
   else if (edispatch == e_dispatch_main_post)
   {

      _main_post(procedure);

   }
   else if (edispatch == e_dispatch_user_post)
   {

      _user_post(procedure);

   }
   else
   {

      _post(procedure);

   }

}




