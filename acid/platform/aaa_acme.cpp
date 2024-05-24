// Created by camilo on 2021-03-21 18:11 <3ThomasBS_!!
#include "framework.h"
#include "node.h"
#include "acid/filesystem/filesystem/ace_directory.h"
#include "acid/memory/counter.h"


namespace acid
{


   acid::acid()
   {

   }


   acid::~acid()
   {


   }


   void acid::initialize_matter(::matter * pmatter)
   {

      auto estatus = ::matter::initialize_matter(pmatter);

      if (!estatus)
      {

         return estatus;

      }

      initialize_memory_counter();

      return estatus;

   }



   void acid::initialize_memory_counter()
   {

      ::initialize_memory_counter(this);

   }

   //::file::path acid::roaming()
   //{

   //   return "";

   //}


   //::file::path acid::program_data()
   //{

   //   return "";

   //}


   void acid::install_crash_dump_reporting(const string& strModuleNameWithTheExeExtension)
   {




   }

   void acid::datetime_to_file_time(::file_time_t* pfile_time, const ::earth::time& time)
   {

      throw ::interface_only();
   }


} // namespace acid



