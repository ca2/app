#include "framework.h"
#include "apex/platform/machine_event_data.h"
#include "apex/platform/machine_event.h"
#include "apex/platform/machine_event_central.h"
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

      pfile = fopen_dup(machine_event_file_path(), "r", _SH_DENYNO);

      if (pfile == nullptr)
      {

         ·zero_pointer(pdata);

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

      dir::mk(dir::name(machine_event_file_path()));

      pfile = fopen_dup(machine_event_file_path(), "w", _SH_DENYWR);

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


