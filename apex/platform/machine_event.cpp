#include "framework.h"
#include "acme/exception/exception.h"
#include "apex/platform/machine_event_data.h"
#include "apex/platform/machine_event.h"
#include "apex/platform/machine_event_central.h"
#include "acme/filesystem/filesystem/acme_directory.h"
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

   FILE * pfile = nullptr;

   try
   {

      //pfile = fopen(acmedirectory()->machine_event_file_path(), "r", _SH_DENYNO);

      pfile = fopen(acmedirectory()->machine_event_file_path(), "r");

      if (pfile == nullptr)
      {

         memset(pdata, 0, sizeof(*pdata));

         return false;

      }

      pdata->read(pfile);

   }
   catch (...)
   {

   }

   fclose(pfile);

   return true;

}


bool machine_event::write(machine_event_data * pdata)
{

   FILE * pfile = nullptr;

   try
   {

      acmedirectory()->create(::file_path_folder(acmedirectory()->machine_event_file_path()));

      //pfile = fopen(acmedirectory()->machine_event_file_path(), "w", _SH_DENYWR);
      pfile = fopen(acmedirectory()->machine_event_file_path(), "w");

      if (pfile == nullptr)
      {

         return false;

      }

      pdata->write(pfile);

   }
   catch (...)
   {

   }

   fclose(pfile);

   return true;

}


