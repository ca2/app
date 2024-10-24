#include "framework.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "apex/platform/machine_event_data.h"
#include "apex/platform/machine_event.h"
#include "apex/platform/machine_event_central.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include <stdio.h>



machine_event::machine_event()
{

   m_bInitialized = false;

}


machine_event::~machine_event()
{

}


void machine_event::initialize(::particle * pparticle)
{

//   auto estatus = 
   ::particle::initialize(pparticle);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   m_bInitialized = true;

   //return true;

}





bool machine_event::read(machine_event_data * pdata)
{

   //FILE * pfile = nullptr;

   try
   {

      //pfile = fopen(directory_system()->machine_event_file_path(), "r", _SH_DENYNO);

      auto pfile = file_system()->get_reader(directory_system()->machine_event_file_path(), ::file::e_open_no_exception_on_open);

      if (pfile.nok())
      {

         pdata->m_fixed.m_bRequestCloseApplication = false;
         pdata->m_fixed.m_bSpaUpgrade = false;

         pdata->m_memoryCommand.clear();

         return false;

      }

      pdata->read(pfile);

      return true;

   }
   catch (...)
   {

   }

   //fclose(pfile);

   return false;

}


bool machine_event::write(machine_event_data * pdata)
{

   //FILE * pfile = nullptr;

   try
   {

      //directory_system()->create(::file_path_folder(directory_system()->machine_event_file_path()));

      //pfile = fopen(directory_system()->machine_event_file_path(), "w", _SH_DENYWR);
     // pfile = fopen(directory_system()->machine_event_file_path(), "w");

      auto pfile = file_system()->get_writer(directory_system()->machine_event_file_path());

      if (pfile == nullptr)
      {

         return false;

      }

      pdata->write(pfile);

      return true;

   }
   catch (...)
   {

   }

   //fclose(pfile);

   return false;

}


