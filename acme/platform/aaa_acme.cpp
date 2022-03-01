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


   void acme::initialize_matter(::matter * pmatter)
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

   void acme::datetime_to_file_time(::file_time_t* pfile_time, const ::earth::time& time)
   {

      throw ::interface_only();
   }


} // namespace acme



