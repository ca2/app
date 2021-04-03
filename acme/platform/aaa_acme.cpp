// Created by camilo on 2021-03-21 18:11 <3ThomasBS_!!
#include "framework.h"
#include "node.h"
#include "acme/filesystem/filesystem/acme_dir.h"
#include "acme/memory/counter.h"


namespace acme
{


   acme::acme()
   {

   }


   acme::~acme()
   {


   }


   ::e_status acme::initialize_matter(::matter * pmatter)
   {

      auto estatus = ::matter::initialize_matter(pmatter);

      if (!estatus)
      {

         return estatus;

      }

      initialize_memory_counter();

      return estatus;

   }



   void acme::initialize_memory_counter()
   {

      ::initialize_memory_counter(this);

   }

   //::file::path acme::roaming()
   //{

   //   return "";

   //}


   //::file::path acme::program_data()
   //{

   //   return "";

   //}


   void acme::install_crash_dump_reporting(const string& strModuleNameWithTheExeExtension)
   {




   }

   ::e_status acme::datetime_to_filetime(::filetime_t* pfiletime, const ::datetime::time& time)
   {

      return error_interface_only;
   }


} // namespace acme



