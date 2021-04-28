#include "framework.h"
#include "apex/platform/machine_event_data.h"
#include "apex/platform/machine_event.h"
#include "apex/platform/machine_event_central.h"
#include "acme/filesystem/filesystem/acme_dir.h"
#include <stdio.h>



machine_event::machine_event()
{

   m_bInitialized = false;

}


machine_event::~machine_event()
{

}


::e_status machine_event::initialize(::object * pobject)
{

   auto estatus = ::matter::initialize_matter(pobject);

   if (!estatus)
   {

      return estatus;

   }

   m_bInitialized = true;

   return true;

}





bool machine_event::read(machine_event_data * pdata)
{

   FILE * pfile = nullptr;

   try
   {

      pfile = fopen_dup(m_psystem->m_pacmedir->machine_event_file_path(), "r", _SH_DENYNO);

      if (pfile == nullptr)
      {

         __zero(pdata);

         return false;

      }

      pdata->read(pfile);

   }
   catch (...)
   {

   }

   fclose_dup(pfile);

   return true;

}


bool machine_event::write(machine_event_data * pdata)
{

   FILE * pfile = nullptr;

   try
   {

      dir::mk(dir::name(m_psystem->m_pacmedir->machine_event_file_path()));

      pfile = fopen_dup(m_psystem->m_pacmedir->machine_event_file_path(), "w", _SH_DENYWR);

      if (pfile == nullptr)
      {

         return false;

      }

      pdata->write(pfile);

   }
   catch (...)
   {

   }

   fclose_dup(pfile);

   return true;

}


