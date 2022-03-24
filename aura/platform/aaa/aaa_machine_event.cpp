#include "framework.h"
#include "aura/platform/machine_event_data2.h"
#include "aura/platform/machine_event2.h"
#include "aura/platform/machine_event_central2.h"
#include <stdio.h>


machine_event::machine_event()
{

   m_bInitialized = false;

   initialize();

}


machine_event::~machine_event()
{

}


bool machine_event::initialize()
{

   if(m_bInitialized)
   {

      return true;

   }

   m_bInitialized = true;

   return true;

}


::file::path machine_event_file_path()
{

   return ::dir::appdata() / "machine/event/machine_event.bin";

}


bool machine_event::read(machine_event_data * pdata)
{

   FILE * pfile = nullptr;

   try
   {

      pfile = FILE_open(machine_event_file_path(), "r", _SH_DENYNO);

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

               auto psystem = m_psystem;

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->create(::file_path_folder(machine_event_file_path()));

      pfile = FILE_open(machine_event_file_path(), "w", _SH_DENYWR);

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


