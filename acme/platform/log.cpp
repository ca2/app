// Created by camilo on 2021-07-17 23:30 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "log.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/platform/acme.h"
#include "acme/platform/application.h"


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


void log::initialize(::particle * pparticle)
{

   ::logger::initialize(pparticle);

   ::file::path pathHome;

#ifdef WINDOWS

   pathHome = getenv("USERPROFILE");

#else

   pathHome = getenv("HOME");

#endif

   auto pathLog = pathHome / "log.txt";

   if (file_exists(pathLog))
   {

      m_bLog = true;

   }
   else if(::system()->has_argument("--log"))
   {

      ::output_debug_string("--log argument present\n");

      m_bLog = true;

   }


   //if (file_system()->is_true(directory_system()->system() / "log.txt"))
   //{

   //   m_bLog = true;

   //}

   //return estatus;

   ::system()->m_bOutputDebugString = m_bLog;


}


void log::initialize_log(enum_trace_level etracelevelMin, const ::atom& atom)
{

   //return ::success;




}


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




//bool g_bVerboseLog = true;
//
//
//void set_verbose_log(bool bVerbose)
//{
//
//   g_bVerboseLog = bVerbose;
//
//}


//bool is_verbose_log()
//{
//
//   return ::platform::platform::s_pplatform->m_papplication->m_bVerbose.is_set_true();
//
//}
