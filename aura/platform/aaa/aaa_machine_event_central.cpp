#include "framework.h"
//#include "aqua/xml.h"
#include "aura/platform/machine_event_data2.h"
#include "aura/platform/machine_event2.h"
#include "aura/platform/machine_event_central2.h"


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

      return ::success;

   }

   auto estatus = ::object::initialize(pparticle);

   if (!estatus)
   {

      return estatus;

   }


   // todo (camilo) instead of sleeping (at machine_event_central::run) , wait for change messages pooling in the machine happening data file.

   // meanwhile, not being used, so exit... It is a problem for Instrumentation Profiling, as function timing (and not cpu usage), counts.
#if 0

   if(!begin())
      return false;

#endif

   m_bInitialized = true;

   return m_bInitialized;

}


void     machine_event_central::run()
{

   // todo (camilo) instead of sleeping, wait for change messages pooling in the machine happening data file.

   // meanwhile, not being used, so exit... It is a problem for Instrumentation Profiling, as function timing (and not cpu usage), counts.

#if 0

   while(task_get_run())
   {

      {
         synchronous_lock lockMachineEvent(&m_machineevent.m_pmutex);

         //machine_event_data data;

         //m_machineevent.read(&data);

         //::auraacmesystem()->process_machine_event_data(&data);
      }

      sleep(500_ms);

   }

#endif

   return ::success;

}


bool machine_event_central::is_close_application()
{

   synchronous_lock lockMachineEvent(&m_machineevent.m_pmutex);

   machine_event_data data;

   m_machineevent.read(&data);

   ::auraacmesystem()->process_machine_event_data(&data);

   return data.m_fixed.m_bRequestCloseApplication;

}


//void machine_event_central::command(::pointer<::xml::node>pnode)
//{
//
//   synchronous_lock lockMachineEvent(&m_machineevent.m_pmutex);
//
//   machine_event_data data;
//
//   m_machineevent.read(&data);
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
//   //m_machineevent.write(&data);
//
//   sleep(500_ms);
//
//}
