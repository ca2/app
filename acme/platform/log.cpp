// Created by camilo on 2021-07-17 23:30 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"


//
//namespace trace
//{


   log::log()
   {

      m_bLog = true;
      m_bExtendedLog = false;
      m_bLogFileName = false;
      m_bLogFunctionName = false;
      m_bLogThreadName = false;

   }


   log::~log()
   {


   }


   void log::initialize(::object* pobject)
   {

      ::logger::initialize(pobject);

      ::file::path pathHome;

#ifdef WINDOWS

      pathHome = getenv("USERPROFILE");

#else

      pathHome = getenv("HOME");

#endif

      if (file_exists(pathHome / "log.txt"))
      {

         m_bLog = true;

      }

      //if (m_psystem->m_pacmefile->is_true(m_psystem->m_pacmedirectory->system() / "log.txt"))
      //{

      //   m_bLog = true;

      //}

      //return estatus;

   }


   void log::initialize_log(enum_trace_level etracelevelMin, const ::atom& atom)
   {

      //return ::success;

   }


   //void log::print(const char* pszFormat, ...)
   //{

   //   va_list valist;

   //   va_start(valist, pszFormat);

   //   print_v(pszFormat, valist);

   //   va_end(valist);

   //}


   //void log::print_v(const char* pszFormat, va_list valist)
   //{

   //   __tracef(e_trace_level_information, nullptr, nullptr, -1, pszFormat, valist);

   //}


   void log::process_init()
   {

      //return ::success;

   }


   void log::set_extended_log(bool bSet)
   {

      m_bExtendedLog = bSet;

   }


   bool log::get_extended_log()
   {

      return m_bExtendedLog;

   }

//} // namespace trace
//
//
//





bool g_bVerboseLog = false;


void set_verbose_log(bool bVerbose)
{

   g_bVerboseLog = bVerbose;

}


bool is_verbose_log()
{

   return g_bVerboseLog;

}
