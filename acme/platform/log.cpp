// Created by camilo on 2021-07-17 23:30 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "log.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
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

   if (file_exists(pathHome / "log.txt"))
   {

      m_bLog = true;

   }

   //if (acmefile()->is_true(acmedirectory()->system() / "log.txt"))
   //{

   //   m_bLog = true;

   //}

   //return estatus;

   ::acme::acme::g_p->m_bOutputDebugString = m_bLog;


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


bool is_verbose_log()
{

   //return g_bVerboseLog;

   return ::acme::acme::g_p->m_pacmeapplication->m_bVerbose;

}
