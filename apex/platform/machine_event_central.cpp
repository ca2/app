#include "framework.h"
#include "acme/parallelization/synchronous_lock.h"
#include "apex/platform/machine_event_data.h"
#include "apex/platform/machine_event.h"
#include "apex/platform/machine_event_central.h"
#include "apex/platform/application.h"
#include "apex/platform/system.h"


machine_event_central::machine_event_central()
{

   m_bInitialized = false;

}


machine_event_central::~machine_event_central()
{

}


void machine_event_central::initialize(::particle * pparticle)
{

   if (m_bInitialized)
   {

      return;

   }

   //auto estatus = 
   
   ::object::initialize(pparticle);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //estatus = 
   
   øconstruct_new(m_pmachinehappening);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   // todo (camilo) instead of sleeping (at machine_event_central::run) , wait for machine messages pooling in the machine happening data file.

   // meanwhile, not being used, so exit... It is a problem for Instrumentation Profiling, as function timing (and not cpu usage), counts.
#if 0

   if(!begin())
      return false;

#endif

   m_bInitialized = true;

   //return m_bInitialized;

}


void machine_event_central::run()
{

   // todo (camilo) instead of sleeping, wait for machine messages pooling in the machine happening data file.

   // meanwhile, not being used, so exit... It is a problem for Instrumentation Profiling, as function timing (and not cpu usage), counts.

   while(task_get_run())
   {

      {
         _synchronous_lock lockMachineEvent(m_pmachinehappening->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         //machine_event_data data;

         //m_machinehappening.read(&data);

         //psystem->process_machine_event_data(&data);
      }

      sleep(500_ms);

   }

   //return ::success;

}


bool machine_event_central::is_close_application()
{

   _synchronous_lock lockMachineEvent(m_pmachinehappening->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   machine_event_data data;

   m_pmachinehappening->read(&data);

   auto psystem = system();

   psystem->process_machine_event_data(&data);

   return data.m_fixed.m_bRequestCloseApplication;

}


//void machine_event_central::command(::pointer<::xml::node>pnode)
//{
//
//   _synchronous_lock lockMachineEvent(&m_machinehappening.m_pmutex);
//
//   machine_event_data data;
//
//   m_machinehappening.read(&data);
//
//   throw ::exception(todo("xml->network_payload"));
//
//   //xml::document doc;
//
//   //if(data.m_blobCommand.m_pchData != nullptr)
//   //{
//
//   //   doc.load(data.m_blobCommand.m_pchData);
//
//   //}
//
//   //if(doc.get_name().is_empty())
//   //   doc.set_name("command");
//
//   //doc.add_child(pnode);
//
//   //data.m_blobCommand = doc.get_xml();
//
//   //m_machinehappening.write(&data);
//
//   sleep(500_ms);
//
//}
